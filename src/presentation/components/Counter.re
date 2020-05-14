let render = () => {
  Js.log("render");
  <div>(React.string("here"))</div>;
};

[@react.component]
let make = () => {
  let (list, setList) = React.useState(_ => []);
  let (count, setCount) = React.useState(_ => 1);
  
  React.useEffect0(() => {
    Js.log("here_1")
    Js.log(Array.of_list(list));
    setList(_ => List.append(list, [5]));
    None;
  });

  React.useEffect1(() => {
    Js.log("here_2")
    Js.log(Array.of_list(list));
    setList(_ => List.append(list, [6]));
    None;
  }, [|count|]);

  <div>
    <div>
      (
        render()
      )
    </div>
    (
      list
        |> List.map((number) => {
          (React.string(string_of_int(number)))
        })
        |> Array.of_list 
        |> React.array
    )
  </div>;
};