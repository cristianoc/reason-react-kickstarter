let useInterval = (callback: _=> unit, delay: int) => {
  let savedCallback = React.useRef(callback);
  React.useEffect1(
    () => {
      React.Ref.setCurrent(savedCallback, callback);
      None;
    },
    [|callback|],
  );
  React.useEffect1(
    () => {
      let tick = React.Ref.current(savedCallback);
      let id = Js.Global.setInterval(tick, delay);
      Some(() => Js.Global.clearInterval(id));
    },
    [|delay|],
  );
};


[@react.component]
let make = () => {
  let (count, setCount) = React.useState(() => 0);

  useInterval(() => {
    setCount(count => count + 1);
    Js.log(count);
  }, 1000);

  <h1>(React.string(string_of_int(count)))</h1>;
}