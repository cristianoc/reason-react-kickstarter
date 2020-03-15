
module type LoaderConfig = {
  type dataType
};

module LoaderComponent(Config: LoaderConfig) {

type action =
  | LoadData
  | OnLoadData(Config.dataType)
  | OnError;

  [@react.component]
  let make = (
      ~fetchData: unit => Js.Promise.t(Config.dataType),
      ~renderView: (Config.dataType, _ => unit) => ReasonReact.reactElement
  ) => {

    let (state, dispatch) =
      React.useReducer(
        (_state, action) =>
          switch(action) {
            | LoadData => Loadable.Loading
            | OnLoadData(data) => Loadable.Success(data)
            | OnError => Loadable.Error
          },
         Loadable.Loading
      );

    React.useEffect1(() => {
      switch(state) {
        | Loading => {
          open Js.Promise;
            fetchData()
              |> then_((result) => result -> OnLoadData -> dispatch -> resolve)
              |> catch(_error => {
                  resolve(dispatch(OnError))
              })
              |> ignore;
          }
        | _ => ()
      }
      None;
    }, [| state |]);
 
    <div>
      {
        switch (state) {
          | Loading => <div>(ReasonReact.string("Loading"))</div>
          | Success(result) => renderView(result,  _ => dispatch(LoadData))
          | Error => <div>(ReasonReact.string("Error..."))</div>
        };
      }
    </div>
  };
};

module LoaderComponentWithoutRefresh(Config: LoaderConfig) {
  
  module BaseLoaderComponent = LoaderComponent(Config);
  
  [@react.component]
  let make = (
    ~fetchData: unit =>  Js.Promise.t(Config.dataType),
    ~renderView: (Config.dataType) => ReasonReact.reactElement, 
   ) => {
      <BaseLoaderComponent
        fetchData=fetchData
        renderView=((data, _onRefresh) => { renderView(data) })
      />
    }
};