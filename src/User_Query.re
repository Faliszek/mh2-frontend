module User = [%graphql
  {|
  query User($id: String!) {
    user(id: $id) {
      id
      email
    }
  }
|}
];

let use = (~id, ()) =>
  GraphQL.useQuery(
    ~query=User.query,
    ~parser=User.parse,
    ~variables={"id": id},
  );