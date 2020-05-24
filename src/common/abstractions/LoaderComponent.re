module type LoaderConfig = {
  type dataType
};

module LoaderComponent(Config: LoaderConfig) {

  type state = Loadable.t(Config.dataType);

  [@react.component]
  let make = (
      ~fetchData: unit => Js.Promise.t(Config.dataType),
      ~renderView: _ => ReasonReact.reactElement
  ) => {

    let (state, setState) = React.useState(_ => Loadable.Loading);

    React.useEffect1(() => {
      switch(state) {
      | Loading => Js.Promise.(
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
    }, [|state|]);

    <div>
      {
        switch (state) {
          | Loading => <div>(ReasonReact.string("Loading"))</div>
          | Success(result) => renderView(result)
          | Error => <div>(ReasonReact.string("Error..."))</div>
        };
      }
    </div>
  };
};