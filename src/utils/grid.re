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

let applyWordListToRow = (~words: Types.Word.wordList, row: Types.Grid.Row.t) => {
  // IDEA: remove HashMap?
  let cellMap = Belt.HashMap.Int.make(~hintSize=Types.Grid.number_of_cells);

  words
  |> List.iter(word =>
       word
       |> (
         fun
         | Some({characters, start, _}: Types.Word.t) =>
           characters
           |> Js.String.split(~sep="")
           |> Array.iteri((index, character) =>
                cellMap->Belt.HashMap.Int.set(index + start, character)
              )
         | None => ()
       )
     );

  row
  |> List.mapi((index, {fallback, _}: Types.Grid.Cell.t) =>
       Types.Grid.Cell.make(
         ~fallback,
         ~value=cellMap->Belt.HashMap.Int.get(index),
       )
     );
};

let applyWordListToGrid = (~words: Types.Word.wordList, grid: Types.Grid.t) =>
  grid
  |> List.mapi((index, row) =>
       row
       |> applyWordListToRow(
            ~words=
              words
              |> List.filter(cell =>
                   cell
                   |> (
                     fun
                     | Some(cell: Types.Word.t) => cell.line == index
                     | None => false
                   )
                 ),
          )
     );
