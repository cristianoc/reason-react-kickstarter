module type DataFetcherConfig = {type dataType;};

module Make = (Config: DataFetcherConfig) => {
  let useLoadable = (
    fetchData: unit => Js.Promise.t(Config.dataType)
  ) => {

    let (state, setState) =   React.useState(_ => Loadable.Loading);
    
    React.useEffect1(() => {
      switch(state) {
        | Loading =>
          Js.Promise.(   
            fetchData()
            |> then_((result) => {
              resolve(setState(_ => Loadable.Live(result)))
            })
            |> catch(_error=> resolve(setState(_ => Loadable.Error)))
            |> ignore
          );
        | _ => ()
      };
      None;
    },[|state|])
    state
  }
}

