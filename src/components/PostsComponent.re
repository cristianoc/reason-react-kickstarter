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

  type state = Loadable.t(Post.t);

  [@react.component]
  let make = () => {
    
    let (state, setState) = React.useState( _ => Loadable.Init);

    React.useEffect0(() => {
      setState(_ =>  Loadable.Loading)
      Js.Promise.(
        Network.fetchPosts()
        |> then_(result => resolve(setState(_ => Loadable.Success(result))))
        |> catch(_error => {
          resolve(setState(_ => Loadable.Error))
        })
        |> ignore
      ) 
      None;
    });
    <div>
      {
        switch(state) {
          | Init => <div>(ReasonReact.string("Init"))</div>
          | Loading => <div>(ReasonReact.string("Loading"))</div>
          | Success(posts) => <PostsViewComponent posts />
          | Error => <div>(ReasonReact.string("Error..."))</div>
        }
      }
    </div>
  }
};