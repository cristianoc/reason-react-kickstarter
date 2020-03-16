module NetworkUtils = {
  let getDefaultHeaders = (): Js.t('a) => {
    {"Content-Type": "application/json", "Accept": "application/json"};
  };
};

let getRequest =
  (~requestUrl: string)
  : Js.Promise.t(ResponseType.t) => {
  Fetch.fetchWithInit(
    requestUrl,
    Fetch.RequestInit.make(
      ~method_=Get,
      ~headers=Fetch.HeadersInit.make(NetworkUtils.getDefaultHeaders()),
      ~credentials=Include,
      ~mode=CORS,
      (),
    )
  )
  |> Js.Promise.then_(ResponseHandler.ResponseWrapper.execute)
};
