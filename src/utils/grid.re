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
  let update = ref(row);

  words
  |> List.iter(word =>
       word
       |> (
         fun
         | Some({characters, start, _}: Types.Word.t) => {
             let characters = characters |> Js.String.split(~sep="");

             update :=
               update^
               |> List.mapi((index, {fallback, _}: Types.Grid.Cell.t) => {
                    let value =
                      index
                      - start
                      |> (
                        fun
                        | index when index >= 0 =>
                          characters->Belt.Array.get(index)
                        | _ => None
                      );

                    Types.Grid.Cell.make(~fallback, ~value);
                  });

             ();
           }

         | None => ()
       )
     );

  update^;
};

let applyWordListToGrid = (~words: Types.Word.wordList, grid: Types.Grid.t) => {
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
};

let clearWords = (grid: Types.Grid.t) =>
  grid
  |> List.map(row =>
       row
       |> List.map(({fallback, _}: Types.Grid.Cell.t) =>
            Types.Grid.Cell.make(~fallback, ~value=None)
          )
     );
