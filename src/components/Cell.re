module Styles = {
  let active = ReactDOM.Style.make(~color="#fff", ());

  let cell =
    ReactDOM.Style.make(
      ~gridRow="auto / auto",
      ~justifyContent="center",
      ~display="grid",
      ~justifyItems="stretch",
      (),
    );

  let cellActive = ReactDOM.Style.combine(active, cell);
};

[@react.component]
let make = (~cell: Types.Grid.Cell.t) =>
  <div
    style={
      cell
      |> (
        fun
        | {value: Some(_), _} => Styles.cellActive
        | _ => Styles.cell
      )
    }>
    {cell
     |> (
       fun
       | {value: Some(value), _} => value
       | {fallback, _} => fallback
     )
     |> React.string}
  </div>;
