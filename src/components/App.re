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

  let (grid, setGrid) =
    React.useState(() =>
      Types.Grid.make(
        ~rowCount=Types.Grid.number_of_rows,
        ~cellCount=Types.Grid.number_of_cells,
      )
      |> Utils.Grid.addFallbacks
      |> Utils.Grid.applyWordListToGrid(
           ~words=Types.Word.getWordsList(~hours, ~minutes),
         )
    );

  React.useEffect0(() => {
    let intervalId =
      Js.Global.setInterval(
        ~f=
          () => {
            "refresh" |> Js.log;
            setGrid(grid => {
              grid
              |> Utils.Grid.clearWords
              |> Utils.Grid.applyWordListToGrid(
                   ~words=Types.Word.getWordsList(~hours, ~minutes),
                 )
            });
          },
        60000,
      );

    Some(() => Js.Global.clearInterval(intervalId));
  });

  <div style> <Grid grid /> </div>;
};
