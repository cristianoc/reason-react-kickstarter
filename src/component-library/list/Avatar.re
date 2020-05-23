[@react.component]
let make = (~children, ~src: string) => {
  <MaterialUi.Avatar src>
    {children}
  </MaterialUi.Avatar>
}