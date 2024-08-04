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
  let (now, setNow) = React.useState(() => Js.Date.make());
  let (grid, setGrid) =
    React.useState(() =>
      Types.Grid.make(
        ~rowCount=Types.Grid.number_of_rows,
        ~cellCount=Types.Grid.number_of_cells,
      )
      |> Utils.Grid.addFallbacks
    );

  React.useEffect2(
    () => {
      let hours = now |> Js.Date.getHours |> int_of_float;
      let minutes = now |> Js.Date.getMinutes |> int_of_float;

      setGrid(grid =>
        grid
        |> Utils.Grid.applyWordListToGrid(
             ~words=Types.Word.getWordsList(~hours, ~minutes),
           )
      );

      None;
    },
    (now, setGrid),
  );

  React.useEffect0(() => {
    let intervalId =
      Js.Global.setInterval(~f=() => {setNow(_ => Js.Date.make())}, 60000);

    Some(() => Js.Global.clearInterval(intervalId));
  });

  <div style> <Grid grid /> </div>;
};
