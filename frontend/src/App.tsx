import NavBar from "./components/NavBar";

function App(props) {
  return (
    <div class="mx-5 mb-20">
      <NavBar />
      {props.children}
    </div>
  );
}

export default App;
