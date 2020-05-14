module type DataFetcherConfig = {type dataType;};

module DataFetcher = (Config: DataFetcherConfig) => {
  let useDataFetcher = (
    fetchData: unit => Js.Promise.t(Config.dataType)
  ) => {

    let (state, setState) =   React.useState(_ => Loadable.Loading(None));
    
    React.useEffect1(() => {
      switch(state) {
        | Loading(_data) =>
          Js.Promise.(   
            fetchData()
            |> then_((result) => {
              resolve(setState(_ => Loadable.Live(result)))
            })
            |>catch(_error=> resolve(setState(_ => Loadable.Error)))
            |> ignore
          );
        | _ => ()
      };
      None;
    },[|state|])
    state
  }
}

