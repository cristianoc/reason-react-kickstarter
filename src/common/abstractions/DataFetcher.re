module type DataFetcherConfig = {type dataType;};

module Make = (Config: DataFetcherConfig) => {
  // argument is a function whose return type is a data promise of type Post.t
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
              resolve(setState(_ => Loadable.Success(result)))
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

