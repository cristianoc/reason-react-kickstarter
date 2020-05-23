module PostsViewComponent {
  [@react.component]
  let make = (~posts: list(Post.post)) => {
      <div>
       <TailiwindTable posts />
      </div>
  };
};

module UsersViewComponent {
  [@react.component]
  let make = (~users: User.t) => {
      Js.log(users);
      <div>
        <ListComponent header="Users">
          (
            users
            |> List.map((user: User.user) => {
              <ListItem key=(string_of_int(user.id))>
                <ListItemAvatar>
                  <Avatar src=(user.src)>
                    <ImageIcon.ImageIcon />
                  </Avatar>
                </ListItemAvatar>
                <ListItemText text=(user.name) />
              </ListItem>
            })
          )
        </ListComponent>
      </div>
  };
};

module PostsComponent = {
  //state-defintion
  //Loadable.t - variant Loading | Success |   Error
  type state = Loadable.t(Post.t);

  [@react.component]
  let make = () => {
      
    let (state, setState) = React.useState(_ => Loadable.Loading)

    let dataPromise = () => PostsRepo.fetchPostsV2();
    
    //use-effect - adds the ability to perform side effects from a function
    React.useEffect1(() => {
      switch(state) {
      | Loading => Js.Promise.(
        dataPromise()
        |> then_((result) => resolve(setState(_ => Loadable.Live(result))))
        |> catch(_error => {
          resolve(setState(_ => Loadable.Error))
        })
        |> ignore
      )
      | _ => ()
      }
      None; // function to be executed when component is unmounted (This is optional)
    }, [|state|]);

    //render
    {
      switch(state) {
        | Loading => <div>(ReasonReact.string("Loading"))</div>
        | Live(posts) => <PostsViewComponent posts />
        | Error => <div>(ReasonReact.string("error"))</div>
      }
    }
  }
}

module UsersComponent = {
    //state-defintion
  //Loadable.t - variant Loading | Success |   Error
  type state = Loadable.t(User.t);

  [@react.component]
  let make = () => {
      
    let (state, setState) = React.useState(_ => Loadable.Loading)

    //function to fetch data
    let dataPromise = () => UsersRepo.fetchUsers();
    
    //use-effect - adds the ability to perform side effects from a function
    React.useEffect1(() => {
      switch(state) {
      | Loading => Js.Promise.(
        dataPromise()
        |> then_((result) => resolve(setState(_ => Loadable.Live(result))))
        |> catch(_error => {
          resolve(setState(_ => Loadable.Error))
        })
        |> ignore
      )
      | _ => ()
      }
      None; // function to be executed when component is unmounted (This is optional)
    }, [|state|]);

    //render
    {
      switch(state) {
        | Loading => <div>(ReasonReact.string("Loading"))</div>
        | Live(users) => <UsersViewComponent users />
        | Error => <div>(ReasonReact.string("error"))</div>
      }
    }
  }
}


module PostsComponentWithDataFetcher = {

  module PostsFetcherConfig = {
    type dataType = Post.t
  };
  
  module PostsFetcher = DataFetcher.Make(PostsFetcherConfig);

  [@react.component]
  let make = () => {
    let data = PostsFetcher.useLoadable(() => PostsRepo.fetchPostsV2());
    {
      switch(data) {
        | Loading => <div>(ReasonReact.string("Loading"))</div>
        | Live(posts) => <PostsViewComponent posts />
        | Error => <div>(ReasonReact.string("error"))</div>
      }
    }
  }
};

module UsersComponentWithDataFetcher = {

  module UserFetcherConfig = {
    type dataType = User.t
  };
  
  module PostsFetcher = DataFetcher.Make(UserFetcherConfig);

  [@react.component]
  let make = () => {
    let data = PostsFetcher.useLoadable(() => UsersRepo.fetchUsers());
    {
      switch(data) {
        | Loading => <div>(ReasonReact.string("Loading"))</div>
        | Live(users) => <UsersViewComponent users />
        | Error => <div>(ReasonReact.string("error"))</div>
      }
    }
  }
};


module PostsComponentWithDataFetcherV2 = {

  module PostsFetcherConfig = {
    type dataType = Post.t
  };
  
  module PostsFetcher = DataFetcherV2.DataFetcher(PostsFetcherConfig);

  [@react.component]
  let make = () => {
    let data = PostsFetcher.useDataFetcher(() =>  PostsRepo.fetchPosts());
      
    {
      switch(data) {
        | Loading(_data) => <div>(ReasonReact.string("Loading"))</div>
        | Live(posts) => <PostsViewComponent posts />
        | Error(error) => <div>(ReasonReact.string(error.message))</div>
      }
    }
  }
};


// module PostsComponentWithLoaderComponent = {
//   module PostsLoaderConfig = {
//     type dataType = Post.t
//   };
  
//   module PostsLoader = LoaderComponent.LoaderComponent(PostsLoaderConfig);

//   [@react.component]
//   let make = () => {
//     <PostsLoader
//       fetchData=(() => PostsRepo.fetchPostsV2())
//       renderView=((post) => <PostsViewComponent posts=[post] />)
//     />
//   }
// };