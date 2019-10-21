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

let query = () => GraphQL.fetch(Users.query, Users.parse);