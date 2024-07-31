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
let make = _ => {
  <div style=Styles.cell> {"Cell" |> React.string} </div>;
};

// import React from "react";

// const Cell: React.FC<{
//   cell: number;
//   random: string[][];
//   row: number;
//   words: string[][];
// }> = ({ cell, random, row, words }) => {
//   const char = words[row][cell];
//   const rand = random[row][cell];

//   return <div className={char ? "cell active" : "cell"}>{char || rand}</div>;
// };

// export default Cell;
