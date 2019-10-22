module Users = [%graphql
  {|
  query Users {
    users {
      id
      email
    }
  }
|}
];

let use = (~variables=?, ()) =>
  GraphQL.useQuery(~query=Users.query, ~parser=Users.parse, ~variables);