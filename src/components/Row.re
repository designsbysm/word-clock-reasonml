let style =
  ReactDOM.Style.make(
    ~alignContent="center",
    ~alignItems="stretch",
    ~display="grid",
    ~gridColumn="auto / auto",
    ~gridTemplateColumns="repeat(13, 1fr)",
    (),
  );

[@react.component]
let make = _ => {
  <div style> {"Row" |> React.string} <Cell /> </div>;
};

// import Cell from "./Cell";

// const Row: React.FC<{
//   cells: string[];
//   random: string[][];
//   row: number;
//   words: string[][];
// }> = ({ cells, row, random, words }) => {
//   return (
//     <div className="row">
//       {cells.map((_, index) => {
//         return <Cell key={index} cell={index} random={random} row={row} words={words} />;
//       })}
//     </div>
//   );
// };

// export default Row;
