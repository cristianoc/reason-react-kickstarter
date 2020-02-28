
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
         Loadable.Init
      );

     React.useEffect0(() => {
      switch(state) {
        | Loadable.Init => dispatch(LoadData);
        | _ => ()
      };
       None;
    });


    React.useEffect1(() => {
      switch(state) {
        | Loading => {
          open Js.Promise;
            fetchData()
              |> then_((result) => resolve(dispatch(OnLoadData(result))))
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
          | Init => <div>(ReasonReact.string("Init..."))</div>
          | Loading => <div>(ReasonReact.string("Loading"))</div>
          | Success(result) => renderView(result,  _ => dispatch(LoadData))
          | Error => <div>(ReasonReact.string("Error..."))</div>
        };
      }
    </div>
  };
};