let execute = (~json: Js.Json.t) : Post.t => {
  Json.Decode.{
    id: json |> field("id", int),
    title: json |> field("title", string),
  };
}