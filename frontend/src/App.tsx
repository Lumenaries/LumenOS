import NavBar from "./components/NavBar";
import Events from "./Events";

function createSubscriber() {
  const eventStream = new EventSource("/api/v1/event");
  eventStream.onmessage = console.log

  return eventStream;
}

function App(props) {
  return (
    <div class="mx-5 mb-20">
      <NavBar />
      {props.children}
    </div>
  );
}

export default App;
