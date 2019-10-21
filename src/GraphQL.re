open Belt;

let uri = "http://localhost:6789/graphql";

let fetch = (q, parser) => {
  let json =
    Js.Json.stringifyAny({"query": q, "variables": Js.Nullable.null})
    ->Option.getWithDefault("");

  let body = Fetch.BodyInit.make(json);
  let request = Fetch.RequestInit.make(~body, ~method_=Fetch.Post, ());

  Fetch.fetchWithInit(uri, request)
  |> Js.Promise.then_(Fetch.Response.json)
  |> Repromise.Rejectable.fromJsPromise
  |> Repromise.Rejectable.andThen(data => {
       let data =
         Js.Json.decodeObject(data)
         ->Option.flatMap(d => Js.Dict.get(d, "data"))
         ->Option.map(parser);

       Repromise.Rejectable.resolved(data);
     });
};