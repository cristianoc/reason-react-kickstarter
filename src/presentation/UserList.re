[@react.component]
let make = (~users: User.t) => {
  <ListComponent header="Users">
    (
      users
      |> List.map((user: User.user) => {
        <ListItem key=(string_of_int(user.id))>
          <ListItemAvatar>
            <Avatar src=(user.src)>
              <ImageIcon.ImageIcon />
            </Avatar>
          </ListItemAvatar>
          <ListItemText text=(user.name) />
        </ListItem>
      })
    )
  </ListComponent>
}