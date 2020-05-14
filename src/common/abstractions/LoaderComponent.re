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

    let (state, setState) = React.useState(_ => Loadable.Loading(None));

    React.useEffect1(() => {
      switch(state) {
      | Loading(_) => Js.Promise.(
        fetchData()
        |> then_((result) => resolve(setState(_ => Loadable.Live(result))))
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
          | Loading(_result) => <div>(ReasonReact.string("Loading"))</div>
          | Live(result) => renderView(result)
          | Error => <div>(ReasonReact.string("Error..."))</div>
        };
      }
    </div>
  };
};