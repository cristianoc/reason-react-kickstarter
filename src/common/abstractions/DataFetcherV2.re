module type DataFetcherConfig = {type dataType;};

module DataFetcher = (Config: DataFetcherConfig) => {
  let useDataFetcher = (
    fetchData: unit => Js.Promise.t(Belt.Result.t(Config.dataType, 'b))
  ) => {

    let (state, setState) =   React.useState(_ => LoadableV2.Loading(None));
    
    React.useEffect1(() => {
      switch(state) {
        | Loading(_data) => ApiUtils.handleAPIRequest(
          () => fetchData(),
          data => setState(_ => LoadableV2.Live(data)),
          error => setState(_ => LoadableV2.Error(error))
        );
        | _ => ()
      };
      None;
    },[|state|])
    state
  }
}

