ReactDOM.querySelector("#root")
->(
    fun
    | Some(rootElement) =>
      ReactDOM.Client.createRoot(rootElement)
      ->ReactDOM.Client.render(<Components.App />)
    | None =>
      Js.Console.error(
        "Failed to start React: couldn't find the #root element",
      )
  );
