let fetchPosts = (): Js.Promise.t(list(Post.t)) =>
  Js.Promise.make((~resolve, ~reject as _) =>
    Js.Global.setTimeout(
      () =>
        resolve(. [Post.{id: 1, title: "Post 1"}, {id: 2, title: "Post 2"}]),
      3000,
    )
    |> ignore
  );