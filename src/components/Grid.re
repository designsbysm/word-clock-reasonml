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
     ->Belt.HashMap.Int.toArray
     ->Belt.Array.mapWithIndex((index, (_, row)) =>
         <Row key={index |> string_of_int} row />
       )
     ->React.array}
  </div>;
