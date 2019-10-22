type error = string;

type result('t) = {
  loading: bool,
  data: option('t),
  error: option(error),
};

let startResult = {loading: true, data: None, error: None};

let uri = "http://localhost:6789/graphql";

let useQuery = (~query, ~parser, ~variables) => {
  let (result, setResult) = React.useState(() => startResult);

  let json =
    Js.Json.stringifyAny({"query": query, "variables": variables})
    ->Option.getWithDefault("");

  let body = Fetch.BodyInit.make(json);
  let request = Fetch.RequestInit.make(~body, ~method_=Fetch.Post, ());

  React.useEffect1(
    () => {
      Fetch.fetchWithInit(uri, request)
      |> Js.Promise.then_(data => {
           setResult(_ => {...result, loading: true});
           Fetch.Response.json(data);
         })
      |> Repromise.Rejectable.fromJsPromise
      |> Repromise.Rejectable.andThen(data => {
           let data =
             Js.Json.decodeObject(data)
             ->Option.flatMap(d => Js.Dict.get(d, "data"))
             ->Option.map(parser);
           setResult(_ => {data, loading: false, error: None});
           Repromise.Rejectable.resolved(data);
         })
      |> Repromise.Rejectable.catch(e => {
           setResult(_ => {...result, loading: false, error: Some("error")});
           Repromise.Rejectable.rejected(e);
         })
      |> ignore;
      None;
    },
    [||],
  );

  result;
};