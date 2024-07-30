module App = {
  let style =
    ReactDOM.Style.make(
      ~fontFamily="Inter, system-ui, Helvetica, Arial, sans-serif",
      ~fontSize="16px",
      ~fontSynthesis="none",
      ~fontWeight="400",
      ~lineHeight="1.5",
      ~margin="0 auto",
      ~maxWidth="1280px",
      ~minHeight="100vh",
      ~minWidth="320px",
      ~padding="2rem",
      (),
    );

  [@react.component]
  let make = _ =>
    <div style>
      {"ReasonML/ReasonReact/Melange Starter Project" |> React.string}
    </div>;
};

ReactDOM.querySelector("#root")
->(
    fun
    | Some(rootElement) =>
      ReactDOM.Client.createRoot(rootElement)
      ->ReactDOM.Client.render(<App />)
    | None =>
      Js.Console.error(
        "Failed to start React: couldn't find the #root element",
      )
  );
