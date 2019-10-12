module type LoaderConfig = {
  type dataType
};

module LoaderComponent(Config: LoaderConfig) {

  type state = Loadable.t(Config.dataType);

  [@react.component]
  let make = (
      ~fetchData: unit => Js.Promise.t(Config.dataType),
      ~renderView: (Config.dataType, _ => unit) => ReasonReact.reactElement, 
  ) => {

    let (state, setState) = React.useState(_ => Loadable.Loading);

    React.useEffect1(() => {
      switch(state) {
        | Loadable.Loading => Js.Promise.(
              fetchData()
              |> then_((result) => resolve(setState(_ => Loadable.Success(result))))
              |> catch(_error => {
                  resolve(setState(_ => Loadable.Error))
              })
              |> ignore
            )  
        | _ => ()
      }
      None;
    }, [| state |]);
      

    <div>
      {
        switch (state) {
          | Init => <div>(ReasonReact.string("Init..."))</div>
          | Loading => <div>(ReasonReact.string("Loading"))</div>
          | Success(result) => renderView(result,  _ => setState(_ => Loadable.Loading))
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