import { Route, Router } from "@solidjs/router";
import { lazy } from "solid-js";
import { render } from "solid-js/web";

import "./index.css";

const root = document.getElementById("root");

const App = lazy(() => import("./App"));
const Advertisements = lazy(() => import("./pages/Advertisements"));
const Activities = lazy(() => import("./pages/Activities"));
const Settings = lazy(() => import("./pages/Settings"));

const BaseballConfig = lazy(
  () => import("./pages/activity_config/BaseballConfig")
);

const BasketballConfig = lazy(
  () => import("./pages/activity_config/BasketballConfig")
);

const FootballConfig = lazy(
  () => import("./pages/activity_config/FootballConfig")
);

const SoccerConfig = lazy(() => import("./pages/activity_config/SoccerConfig"));

const TennisConfig = lazy(() => import("./pages/activity_config/TennisConfig"));

const VolleyballConfig = lazy(
  () => import("./pages/activity_config/VolleyballConfig")
);

if (import.meta.env.DEV && !(root instanceof HTMLElement)) {
  throw new Error(
    "Root element not found. Did you forget to add it to your index.html? Or maybe the id attribute got misspelled?"
  );
}

render(
  () => (
    <Router root={App}>
      <Route path="/" component={Activities} />
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
