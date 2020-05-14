module PostsViewComponent {
  [@react.component]
  let make = (~posts: list(Post.t)) => {
      <div>
        <ul>
          (
            posts
            |> List.map((post: Post.t) => {
              <li key=(string_of_int(post.id))>
                (ReasonReact.string(post.title))
              </li>
            })
            |> Array.of_list
            |> ReasonReact.array
          )
        </ul>
      </ div>
  };
};

module PostsComponent = {
  
  type state = Loadable.t(Post.t);

  [@react.component]
  let make = () => {
      
    let (state, setState) = React.useState(_ => Loadable.Loading(None))

    React.useEffect1(() => {
      switch(state) {
      | Loading(_) => Js.Promise.(
        PostsRepo.fetchPostsV2()
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

    {
      switch(state) {
        | Loading(_data) => <div>(ReasonReact.string("Loading"))</div>
        | Live(post) => <PostsViewComponent posts=[post] />
        | Error => <div>(ReasonReact.string("error"))</div>
      }
    }
  }
}

module PostsComponentWithDataFetcher = {

  module PostsFetcherConfig = {
    type dataType = Post.t
  };
  
  module PostsFetcher = DataFetcher.DataFetcher(PostsFetcherConfig);

  [@react.component]
  let make = () => {
    let data = PostsFetcher.useDataFetcher(() => PostsRepo.fetchPostsV2());
    {
      switch(data) {
        | Loading(_data) => <div>(ReasonReact.string("Loading"))</div>
        | Live(post) => <PostsViewComponent posts=[post] />
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
        | Live(post) => <PostsViewComponent posts=[post] />
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