let buildList = (~children, ~header: string) => (
  <MaterialUi.List subheader=(React.string(header))>
    {children}
  </MaterialUi.List>
);

[@react.component]
let make = (~header:string, ~children) => buildList(~header, ~children);