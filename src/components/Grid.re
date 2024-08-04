let style =
  ReactDOM.Style.make(
    ~display="grid",
    ~fontSize="5vmin",
    ~gridTemplateRows="repeat(8, 1fr)",
    ~height="90vmin",
    ~margin="5vmin",
    ~width="90vmin",
    (),
  );

[@react.component]
let make = (~grid: Types.Grid.t) =>
  <div style>
    {grid
     |> List.mapi((index, row) => <Row key={index |> string_of_int} row />)
     |> Array.of_list
     |> React.array}
  </div>;
