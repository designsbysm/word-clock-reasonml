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
  now |> Types.Word.getWordsList |> Array.of_list |> Js.log;

  // now |> Utils.Words.getHourWords |> Array.of_list |> Js.log;
  // now |> Utils.Words.getMinuteWords |> Array.of_list |> Js.log;

  <div style> <Grid /> </div>;
};

// const [wordGrid, setWordGrid] = React.useState(getWordGrid());
// const [randomGrid] = React.useState(getRandomGrid());
// const [refresh, setRefresh] = React.useState(true);

// if (refresh) {
//   setInterval(() => {
//     setWordGrid(getWordGrid());
//   }, 60000);

//   setRefresh(false);
