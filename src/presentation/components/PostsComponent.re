module PostsViewComponent {
  [@react.component]
  let make = (~posts: list(Post.t)) => {
      <div>
        <li>
          (
            posts
            |> List.map((post: Post.t) => {
              <ul key=(string_of_int(post.id))>
                <h1>(ReasonReact.string(post.title))</h1>
              </ul>
            })
            |> Array.of_list
            |> ReasonReact.array
          )
        </li>
      </ div>
  };
};

module PostsComponent = {

  module PostsFetcherConfig = {
    type dataType = Post.t
  };
  
  module PostsFetcher = DataFetcher.DataFetcher(PostsFetcherConfig);

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