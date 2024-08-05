let number_of_cells = 13;
let number_of_rows = 8;

let getRandomCharacter = () => {
  let min = 65.;
  let max = 91.;

  Js.Math.random()
  *. (max -. min)
  +. min
  |> int_of_float
  |> Js.String.fromCharCode;
};

module Cell = {
  type t = {
    fallback: option(string),
    value: option(string),
  };

  let make = (~fallback, ~value) => {fallback, value};
};

module Row = {
  type t = List.t(Cell.t);

  let make = (~count) =>
    List.init(count, _ => Cell.make(~fallback=None, ~value=None));
};

type t = List.t(Row.t);

let make = (~rowCount, ~cellCount) =>
  List.init(rowCount, _ => Row.make(~count=cellCount));
