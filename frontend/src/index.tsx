import { Route, Router } from "@solidjs/router";
import { lazy } from "solid-js";
import { render } from "solid-js/web";

const root = document.getElementById("root");

const App = lazy(() => import("./App"));
const Advertisements = lazy(() => import("./pages/Advertisements"));
const Games = lazy(() => import("./pages/Games"));
const Settings = lazy(() => import("./pages/Settings"));

const BaseballConfig = lazy(() =>
  import("./pages/SportConfig").then((module) => ({
    default: module.BaseballConfig,
  }))
);

const BasketballConfig = lazy(() =>
  import("./pages/SportConfig").then((module) => ({
    default: module.BasketballConfig,
  }))
);

const FootballConfig = lazy(() =>
  import("./pages/SportConfig").then((module) => ({
    default: module.FootballConfig,
  }))
);

const SoccerConfig = lazy(() =>
  import("./pages/SportConfig").then((module) => ({
    default: module.SoccerConfig,
  }))
);

const TennisConfig = lazy(() =>
  import("./pages/SportConfig").then((module) => ({
    default: module.TennisConfig,
  }))
);

const VolleyballConfig = lazy(() =>
  import("./pages/SportConfig").then((module) => ({
    default: module.VolleyballConfig,
  }))
);

if (import.meta.env.DEV && !(root instanceof HTMLElement)) {
  throw new Error(
    "Root element not found. Did you forget to add it to your index.html? Or maybe the id attribute got misspelled?"
  );
}

render(
  () => (
    <Router root={App}>
      <Route path="/" component={Games} />
      <Route path="/ads" component={Advertisements} />
      <Route path="/settings" component={Settings} />
      <Route path="/baseball" component={BaseballConfig} />
      <Route path="/basketball" component={BasketballConfig} />
      <Route path="/football" component={FootballConfig} />
      <Route path="/soccer" component={SoccerConfig} />
      <Route path="/tennis" component={TennisConfig} />
      <Route path="/volleyball" component={VolleyballConfig} />
    </Router>
  ),
  root!
);
