type t = {
  characters: string,
  line: int,
  start: int,
};

type list = List.t(t);

type map = {
  hour1: t,
  hour2: t,
  hour3: t,
  hour4: t,
  hour5: t,
  hour6: t,
  hour7: t,
  hour8: t,
  hour9: t,
  hour10: t,
  hour11: t,
  hour12: t,
  minutes5: t,
  minutes10: t,
  minutes15: t,
  minutes20: t,
  minutes30: t,
  a: t,
  its: t,
  minutes: t,
  oclock: t,
  past: t,
  to_: t,
};

let map = {
  hour1: {
    characters: "ONE",
    line: 3,
    start: 7,
  },
  hour2: {
    characters: "TWO",
    line: 3,
    start: 9,
  },
  hour3: {
    characters: "THREE",
    line: 4,
    start: 0,
  },
  hour4: {
    characters: "FOUR",
    line: 4,
    start: 5,
  },
  hour5: {
    characters: "FIVE",
    line: 4,
    start: 9,
  },
  hour6: {
    characters: "SIX",
    line: 5,
    start: 0,
  },
  hour7: {
    characters: "SEVEN",
    line: 5,
    start: 4,
  },
  hour8: {
    characters: "EIGHT",
    line: 5,
    start: 8,
  },
  hour9: {
    characters: "NINE",
    line: 6,
    start: 0,
  },
  hour10: {
    characters: "TEN",
    line: 6,
    start: 0,
  },
  hour11: {
    characters: "ELEVEN",
    line: 6,
    start: 0,
  },
  hour12: {
    characters: "TWELVE",
    line: 7,
    start: 0,
  },
  minutes5: {
    characters: "FIVE",
    line: 2,
    start: 0,
  },
  minutes10: {
    characters: "TEN",
    line: 0,
    start: 6,
  },
  minutes15: {
    characters: "QUARTER",
    line: 1,
    start: 0,
  },
  minutes20: {
    characters: "TWENTY",
    line: 1,
    start: 7,
  },
  minutes30: {
    characters: "HALF",
    line: 0,
    start: 9,
  },
  a: {
    characters: "A",
    line: 0,
    start: 4,
  },
  its: {
    characters: "ITS",
    line: 0,
    start: 0,
  },
  minutes: {
    characters: "MINUTES",
    line: 2,
    start: 5,
  },
  oclock: {
    characters: "OCLOCK",
    line: 7,
    start: 7,
  },
  past: {
    characters: "PAST",
    line: 3,
    start: 0,
  },
  to_: {
    characters: "TO",
    line: 3,
    start: 4,
  },
};

let getHours: Js.Date.t => list =
  now => {
    let hours = now |> Js.Date.getHours;
    let minutes = now |> Js.Date.getMinutes;

    (hours, minutes)
    |> (
      fun
      | (hours, minutes) when minutes > 30. => hours +. 1.
      | _ => hours
    )
    |> (
      fun
      | hours when hours == 0. => 12.
      | hours when hours > 12. => hours -. 12.
      | hours => hours
    )
    |> (
      fun
      | hours when hours == 1. => [map.hour1]
      | hours when hours == 2. => [map.hour2]
      | hours when hours == 3. => [map.hour3]
      | hours when hours == 4. => [map.hour4]
      | hours when hours == 5. => [map.hour5]
      | hours when hours == 6. => [map.hour6]
      | hours when hours == 7. => [map.hour7]
      | hours when hours == 8. => [map.hour8]
      | hours when hours == 9. => [map.hour9]
      | hours when hours == 10. => [map.hour10]
      | hours when hours == 11. => [map.hour11]
      | hours when hours == 12. => [map.hour12]
      | _ => []
    );
  };

let getMinutes: Js.Date.t => list =
  now => {
    let minutes = now |> Js.Date.getMinutes;

    minutes
    |> (
      fun
      | minutes
          when minutes > 2. && minutes <= 7. || minutes > 53. && minutes < 58. =>
        [map.minutes5, map.minutes] |> Option.some
      | minutes
          when
            minutes > 7. && minutes <= 13. || minutes > 47. && minutes <= 53. =>
        [map.minutes10, map.minutes] |> Option.some
      | minutes
          when
            minutes > 13. && minutes <= 17. || minutes > 42. && minutes <= 47. =>
        [map.minutes15, map.a] |> Option.some
      | minutes
          when
            minutes > 17. && minutes <= 25. || minutes > 35. && minutes <= 42. =>
        [map.minutes20, map.minutes] |> Option.some
      | minutes when minutes > 25. && minutes <= 35. =>
        [map.minutes30, map.a] |> Option.some
      | _ => None
    )
    |> (
      fun
      | Some(words) =>
        minutes
        |> (
          fun
          | minutes when minutes > 30. => [map.to_]
          | _ => [map.past]
        )
        |> List.append(words)
      | None => [map.oclock]
    );
  };

let getWordsList: Js.Date.t => list =
  now => {
    [map.its]
    |> List.append(now |> getMinutes)
    |> List.append(now |> getHours);
  };
