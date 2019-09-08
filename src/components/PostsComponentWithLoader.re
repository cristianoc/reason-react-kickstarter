module PostsViewComponent {
  [@react.component]
  let make = (~posts: list(Post.t), ~refeshView: _ => _) => {
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
        <button onClick=((_event) => refeshView())>(ReasonReact.string("Refresh"))</button>
      </ div>
  };
};

module PostsComponentWithLoader {

  module  LoaderComponentConfig = {
    type dataType = list(Post.t)
  };

  module PostsLoaderComponent = LoaderComponent.LoaderComponent(LoaderComponentConfig);

  [@react.component]
  let make = () => {
    <PostsLoaderComponent
      fetchData=(() => Network.fetchPosts())
      renderView=(
        (posts: list(Post.t), refeshView: _ => _) => <PostsViewComponent posts refeshView />
      )/>
  };
};