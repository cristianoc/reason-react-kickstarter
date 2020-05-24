[@react.component]
let make = () => {
  <div className="flex flex-row space-x-4">
    <MyFeed.PostsComponent />
    <div className="mt-12">
      <MyFeed.UsersComponent />
    </div>
    // <MyFeed.PostsComponentWithDataFetcher />
    // <MyFeed.UsersComponentWithDataFetcher />
  </div>
}