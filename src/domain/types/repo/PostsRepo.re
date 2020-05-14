let dummy_response = [%bs.raw
  {|
    {
      id: 2, title: "Post 2"
    }
  |};
]

let fetchPosts = () : Js.Promise.t(Belt.Result.t(Post.t, Decco.decodeError)) =>
  Js.Promise.(
    make((~resolve, ~reject as _) =>
        dummy_response
        |> Post.t_decode 
        |> (post) => resolve(. post)
    )
  )


module StateMapper = {
  let execute = (json: Js.Json.t) : Post.t => {
    Json.Decode.(
      {
        id: json |> field("id", int),
        title: json |> field("title", string),
      }
    )
  }
}
let fetchPostsV2 = () : Js.Promise.t(Post.t) =>
  Js.Promise.(
    make((~resolve, ~reject as _) =>
        dummy_response
        |> StateMapper.execute
        |> (post: Post.t) => resolve(. post)
    )
  )