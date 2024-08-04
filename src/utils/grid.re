let addFallbacks = (grid: Types.Grid.t) =>
  grid
  |> List.map(row =>
       row
       |> List.map(({value, _}: Types.Grid.Cell.t) =>
            Types.Grid.Cell.make(
              ~fallback=Types.Grid.getRandomCharacter() |> Option.some,
              ~value,
            )
          )
     );

let clearWords = (grid: Types.Grid.t) =>
  grid
  |> List.map(row =>
       row
       |> List.map(({fallback, _}: Types.Grid.Cell.t) =>
            Types.Grid.Cell.make(~fallback, ~value=None)
          )
     );
