[@react.component]
let make = (~text: string) => {
   <MaterialUi.ListItemText primary=(React.string(text)) secondary=(React.string("Active")) />
}