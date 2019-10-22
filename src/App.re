[@react.component]
let make = () => {
  let users = Users_Query.use();

  let user = User_Query.use(~id="1", ());

  // switch (users) {
  // | {data: Some(data)} =>
  //   <div>
  //     {data##users->Array.map(u => u##id->React.string)->React.array}
  //   </div>
  // | {loading: true} => <div> "loading"->React.string </div>
  // | {error: Some(error), _} => <div> error->React.string </div>
  // | _ => React.null
  // };

  switch (user) {
  | {data: Some(data)} =>
    data##user
    ->Option.map(u => u##id->React.string)
    ->Option.getWithDefault(React.null)
  | _ => React.null
  };
};