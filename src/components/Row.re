let style =
  ReactDOM.Style.make(
    ~alignContent="center",
    ~alignItems="stretch",
    ~display="grid",
    ~gridColumn="auto / auto",
    ~gridTemplateColumns="repeat(13, 1fr)",
    (),
  );

[@react.component]
let make = (~row: Types.Grid.Row.t) =>
  <div style>
    {row
     |> List.mapi((index, cell) =>
          <Cell cell key={index |> string_of_int} />
        )
     |> Array.of_list
     |> React.array}
  </div>;
