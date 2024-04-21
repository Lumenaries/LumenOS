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
  () => import("./pages/activityConfig/BaseballConfig")
);

const BasketballConfig = lazy(
  () => import("./pages/activityConfig/BasketballConfig")
);

const FootballConfig = lazy(
  () => import("./pages/activityConfig/FootballConfig")
);

const SoccerConfig = lazy(() => import("./pages/activityConfig/SoccerConfig"));

const TennisConfig = lazy(() => import("./pages/activityConfig/TennisConfig"));

const VolleyballConfig = lazy(
  () => import("./pages/activityConfig/VolleyballConfig")
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
