open Belt;

type t = {
  characters: string,
  line: int,
  start: int,
};

// IDEA: HashMap using variant keys

let hoursMap =
  [|
    (1, {characters: "ONE", line: 3, start: 7}),
    (2, {characters: "TWO", line: 3, start: 9}),
    (3, {characters: "THREE", line: 4, start: 0}),
    (4, {characters: "FOUR", line: 4, start: 5}),
    (5, {characters: "FIVE", line: 4, start: 9}),
    (6, {characters: "SIX", line: 5, start: 0}),
    (7, {characters: "SEVEN", line: 5, start: 4}),
    (8, {characters: "EIGHT", line: 5, start: 8}),
    (9, {characters: "NINE", line: 6, start: 0}),
    (10, {characters: "TEN", line: 6, start: 0}),
    (11, {characters: "ELEVEN", line: 6, start: 0}),
    (12, {characters: "TWELVE", line: 7, start: 0}),
  |]
  |> HashMap.Int.fromArray;

let minutesMap =
  [|
    (5, {characters: "FIVE", line: 2, start: 0}),
    (10, {characters: "TEN", line: 0, start: 6}),
    (15, {characters: "QUARTER", line: 1, start: 0}),
    (20, {characters: "TWENTY", line: 1, start: 7}),
    (30, {characters: "HALF", line: 0, start: 9}),
  |]
  |> HashMap.Int.fromArray;

let othersMap =
  [|
    ("a", {characters: "A", line: 0, start: 4}),
    ("its", {characters: "ITS", line: 0, start: 0}),
    ("minutes", {characters: "MINUTES", line: 2, start: 5}),
    ("oclock", {characters: "OCLOCK", line: 7, start: 7}),
    ("past", {characters: "PAST", line: 3, start: 0}),
    ("to", {characters: "TO", line: 3, start: 4}),
  |]
  |> HashMap.String.fromArray;

let isBetween = (~min, ~max, value) => value > min && value <= max;

let getHours = (~hours, ~minutes) =>
  (hours, minutes)
  |> (
    fun
    | (hours, minutes) when minutes > 30 => hours + 1
    | _ => hours
  )
  |> (
    fun
    | hours when hours == 0 => 12
    | hours when hours > 12 => hours - 12
    | hours => hours
  )
  |> HashMap.Int.get(hoursMap)
  |> (words => [words]);

let getMinutes = (~minutes) =>
  minutes
  |> (
    fun
    | minutes
        when
          minutes
          |> isBetween(~min=2, ~max=7)
          || minutes
          |> isBetween(~min=53, ~max=58) => [
        5 |> HashMap.Int.get(minutesMap),
        "minutes" |> HashMap.String.get(othersMap),
      ]
    | minutes
        when
          minutes
          |> isBetween(~min=7, ~max=13)
          || minutes
          |> isBetween(~min=47, ~max=53) => [
        10 |> HashMap.Int.get(minutesMap),
        "minutes" |> HashMap.String.get(othersMap),
      ]
    | minutes
        when
          minutes
          |> isBetween(~min=13, ~max=17)
          || minutes
          |> isBetween(~min=42, ~max=47) => [
        15 |> HashMap.Int.get(minutesMap),
        "a" |> HashMap.String.get(othersMap),
      ]
    | minutes
        when
          minutes
          |> isBetween(~min=17, ~max=25)
          || minutes
          |> isBetween(~min=35, ~max=42) => [
        20 |> HashMap.Int.get(minutesMap),
        "minutes" |> HashMap.String.get(othersMap),
      ]
    | minutes when minutes |> isBetween(~min=25, ~max=35) => [
        30 |> HashMap.Int.get(minutesMap),
        "a" |> HashMap.String.get(othersMap),
      ]
    | _ => []
  )
  |> (
    fun
    | [] => ["oclock" |> HashMap.String.get(othersMap)]
    | words =>
      minutes
      |> (
        fun
        | minutes when minutes > 30 => [
            "to" |> HashMap.String.get(othersMap),
          ]
        | _ => ["past" |> HashMap.String.get(othersMap)]
      )
      |> List.concat(words)
  );

let getWordsList = (~hours, ~minutes) =>
  List.concatMany([|
    ["its" |> HashMap.String.get(othersMap)],
    getMinutes(~minutes),
    getHours(~hours, ~minutes),
  |]);
