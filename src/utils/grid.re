let addFallbacks = (grid: Types.Grid.t) =>
  grid
  ->Belt.HashMap.Int.toArray
  ->Belt.Array.mapWithIndex((index, (_, row)) =>
      (
        index,
        row
        ->Belt.HashMap.Int.toArray
        ->Belt.Array.mapWithIndex((index, (_, cell)) =>
            (
              index,
              {
                ...cell,
                // fallback: Types.Grid.getRandomCharacter() |> Option.some,
                fallback: index |> string_of_int |> Option.some,
              },
            )
          )
        ->Belt.HashMap.Int.fromArray,
      )
    )
  ->Belt.HashMap.Int.fromArray;

let clearWords = (grid: Types.Grid.t) =>
  grid
  ->Belt.HashMap.Int.toArray
  ->Belt.Array.mapWithIndex((index, (_, row)) =>
      (
        index,
        row
        ->Belt.HashMap.Int.toArray
        ->Belt.Array.mapWithIndex((index, (_, cell)) => {
            (
              // cell |> Js.log;
              index,
              {...cell, value: None},
            )
          })
        ->Belt.HashMap.Int.fromArray,
      )
    )
  ->Belt.HashMap.Int.fromArray;
