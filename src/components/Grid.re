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
let make = _ => {
  <div style> {"Grid" |> React.string} <Row /> </div>;
};

// {wordGrid.map((row, index) => {
//   return <Row key={index} cells={row} random={randomGrid} row={index} words={wordGrid} />;
