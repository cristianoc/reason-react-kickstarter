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