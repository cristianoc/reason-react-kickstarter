module PostsViewComponent = {
  [@react.component]
  let make = (~posts: list(Post.post)) => {
    <div> <PostsList posts /> </div>;
  };
};

module UsersViewComponent = {
  [@react.component]
  let make = (~users: User.t) => {
    <div> <UserList users /> </div>;
  };
};

module PostsComponent = {
  //state-defintion
  //Loadable.t - variant Loading | Success |   Error
  type state = Loadable.t(Post.t);

  [@react.component]
  let make = () => {
    let (state, setState) = React.useState(_ => Loadable.Loading);

    let dataPromise = () => PostsRepo.fetchPostsV2(); // stores reference to a function which returns a promise

    //use-effect - adds the ability to perform side effects from a function
    React.useEffect1(
      () => {
        switch (state) {
        | Loading =>
          Js.Promise.(
            dataPromise()
            |> then_(result =>
                 resolve(setState(_ => Loadable.Success(result)))
               )
            |> catch(_error => {resolve(setState(_ => Loadable.Error))})
            |> ignore
          )
        | _ => ()
        };
        None;
      }, // function to be executed when component is unmounted (This is optional)
      [|state|],
    );

    //render
    switch (state) {
    | Loading => <div> {ReasonReact.string("Loading")} </div>
    | Success(posts) => <PostsViewComponent posts />
    | Error => <div> {ReasonReact.string("error")} </div>
    };
  };
};

module UsersComponent = {
  //state-defintion
  //Loadable.t - variant Loading | Success |   Error
  type state = Loadable.t(User.t);

  [@react.component]
  let make = () => {
    let (state, setState) = React.useState(_ => Loadable.Loading);

    //function to fetch data
    let dataPromise = () => UsersRepo.fetchUsers();

    //use-effect - adds the ability to perform side effects from a function
    React.useEffect1(
      () => {
        switch (state) {
        | Loading =>
          Js.Promise.(
            dataPromise()
            |> then_(result =>
                 resolve(setState(_ => Loadable.Success(result)))
               )
            |> catch(_error => {resolve(setState(_ => Loadable.Error))})
            |> ignore
          )
        | _ => ()
        };
        None;
      }, // function to be executed when component is unmounted (This is optional)
      [|state|],
    );

    //render
    switch (state) {
    | Loading => <div> {ReasonReact.string("Loading")} </div>
    | Success(users) => <UsersViewComponent users />
    | Error => <div> {ReasonReact.string("error")} </div>
    };
  };
};

let useLoadable = fetchData => {
  let (state, setState) = React.useState(_ => Loadable.Loading);

  React.useEffect1(
    () => {
      switch (state) {
      | Loading =>
        Js.Promise.(
          fetchData()
          |> then_(result => {
               resolve(setState(_ => Loadable.Success(result)))
             })
          |> catch(_error => resolve(setState(_ => Loadable.Error)))
          |> ignore
        )
      | _ => ()
      };
      None;
    },
    [|state|],
  );
  state;
};


module PostsComponentWithDataFetcher = {

  [@react.component]
  let make = () => {
    //data promise of type Post.t
    let data = useLoadable(() => PostsRepo.fetchPostsV2());
    switch (data) {
    | Loading => <div> {ReasonReact.string("Loading")} </div>
    | Success(posts) => <PostsViewComponent posts />
    | Error => <div> {ReasonReact.string("error")} </div>
    };
  };
};


module UsersComponentWithDataFetcher = {
  [@react.component]
  let make = () => {
    let data = useLoadable(() => UsersRepo.fetchUsers());
    switch (data) {
    | Loading => <div> {ReasonReact.string("Loading")} </div>
    | Success(users) => <UsersViewComponent users />
    | Error => <div> {ReasonReact.string("error")} </div>
    };
  };
};

module PostsComponentWithDataFetcherV2 = {
  module PostsFetcherConfig = {
    type dataType = Post.t;
  };

  let useDataFetcher = fetchData => {
    let (state, setState) = React.useState(_ => LoadableV2.Loading(None));

    React.useEffect1(
      () => {
        switch (state) {
        | Loading(_data) =>
          ApiUtils.handleAPIRequest(
            () => fetchData(),
            data => setState(_ => LoadableV2.Success(data)),
            error => setState(_ => LoadableV2.Error(error)),
          )
        | _ => ()
        };
        None;
      },
      [|state|],
    );
    state;
  };

  [@react.component]
  let make = () => {
    let data = useDataFetcher(() => PostsRepo.fetchPosts());

    switch (data) {
    | Loading(_data) => <div> {ReasonReact.string("Loading")} </div>
    | Success(posts) => <PostsViewComponent posts />
    | Error(error) => <div> {ReasonReact.string(error.message)} </div>
    };
  };
};