let dummy_response = [%bs.raw
  {|
    [{
      id: 2, title: "Fighting COVID 19 with Emapthy", image: "https://images.unsplash.com/photo-1494790108377-be9c29b29330?ixlib=rb-1.2.1&ixid=eyJhcHBfaWQiOjEyMDd9&auto=format&fit=facearea&facepad=2.2&w=160&h=160&q=80"
    },
    {
      id: 3, title: "I am Becasue we Are", image: "https://images.unsplash.com/photo-1500648767791-00dcc994a43e?ixlib=rb-1.2.1&ixid=eyJhcHBfaWQiOjEyMDd9&auto=format&fit=facearea&facepad=2.2&w=160&h=160&q=80"
    },
    {
      id: 4, title: "Making Abstractions Powerful with ReasonML", image: "https://images.unsplash.com/photo-1540845511934-7721dd7adec3?ixlib=rb-1.2.1&ixid=eyJhcHBfaWQiOjEyMDd9&auto=format&fit=facearea&facepad=2.2&w=160&h=160&q=80"
    }]
  |};
];

let fetchPosts = () : Js.Promise.t(Belt.Result.t(Post.t, Decco.decodeError)) =>
  Js.Promise.(
    make((~resolve, ~reject as _) =>
        dummy_response
        |> Post.t_decode 
        |> (posts) => resolve(. posts)
    )
  )


module StateMapper = {
  let decodePost = (json) : Post.post => {
      Json.Decode.(
      {
        id: json |> field("id", int),
        title: json |> field("title", string),
        image: json |> field("image", string),
      }
    )
  }

  let execute = (json) => {
    Json.Decode.(
      json |> list(decodePost)
    )
  }
}

let fetchPostsV2 = () : Js.Promise.t(Post.t) =>
  Js.Promise.(
    make((~resolve, ~reject as _) =>
      dummy_response
      |> StateMapper.execute
      |> (posts: Post.t) => resolve(. posts)
    )
  )