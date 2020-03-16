module type DataFetcherConfig = {type dataType;};

module DataFetcher = (Config: DataFetcherConfig) => {
  let useDataFetcher = (
    fetchData: unit => Js.Promise.t(Belt.Result.t(Config.dataType, 'b))
  ) => {

    let (state, setState) =   React.useState(_ => Loadable.Loading(None));
    
    React.useEffect1(() => {
      switch(state) {
        | Loading(_data) => ApiUtils.handleAPIRequest(
          () => fetchData(),
          data => setState(_ => Loadable.Live(data)),
          error => setState(_ => Loadable.Error(error))
        );
        | _ => ()
      };
      None;
    },[|state|])
    state
  }
}

