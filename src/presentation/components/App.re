[@react.component]
let make = () => {
  <div className="flex flex-row space-x-4">
    // <MyFeed.PostsComponent />
    // <MyFeed.UsersComponent />
    <MyFeed.PostsComponentWithDataFetcher />
    <MyFeed.UsersComponentWithDataFetcher />
  </div>
}