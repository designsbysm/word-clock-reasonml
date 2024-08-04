let number_of_cells = 13;
let number_of_rows = 8;

let getRandomCharacter = () => {
  let min = 65.;
  let max = 90.;

  Js.Math.random()
  *. (max -. min)
  +. min
  |> int_of_float
  |> Js.String.fromCharCode;
};

module Cell = {
  type t = {
    fallback: string,
    value: option(string),
  };

  let make = (fallback, value) => {fallback, value};
};

module Row = {
  type t = Belt.HashMap.Int.t(Cell.t);

  let make = count =>
    count
    ->Belt.Array.make()
    ->Belt.Array.mapWithIndex((index, _) =>
        (index, Cell.make(getRandomCharacter(), None))
      )
    ->Belt.HashMap.Int.fromArray;
};

type t = Belt.HashMap.Int.t(Row.t);

let make = (~rowCount, ~cellCount) =>
  rowCount
  ->Belt.Array.make()
  ->Belt.Array.mapWithIndex((index, _) => (index, Row.make(cellCount)))
  ->Belt.HashMap.Int.fromArray;
