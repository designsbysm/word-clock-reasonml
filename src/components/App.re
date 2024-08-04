let style =
  ReactDOM.Style.make(
    ~alignItems="center",
    ~boxSizing="border-box",
    ~display="flex",
    ~flexDirection="column",
    ~height="100vh",
    ~placeContent="center",
    (),
  );

[@react.component]
let make = _ => {
  let now = Js.Date.make();
  let hours = now |> Js.Date.getHours |> int_of_float;
  let minutes = now |> Js.Date.getMinutes |> int_of_float;

  Types.Word.getWordsList(~hours, ~minutes) |> Array.of_list |> Js.log;

  let grid =
    Types.Grid.make(
      ~rowCount=Types.Grid.number_of_rows,
      ~cellCount=Types.Grid.number_of_cells,
    );

  <div style> <Grid grid /> </div>;
};

// const [wordGrid, setWordGrid] = React.useState(getWordGrid());
// const [randomGrid] = React.useState(getRandomGrid());
// const [refresh, setRefresh] = React.useState(true);

// if (refresh) {
//   setInterval(() => {
//     setWordGrid(getWordGrid());
//   }, 60000);

//   setRefresh(false);
