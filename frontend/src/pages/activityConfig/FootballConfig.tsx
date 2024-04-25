import {
  Show,
  createEffect,
  createResource,
  createSignal,
  lazy,
  onMount,
} from "solid-js";

import { useEvent } from "../../Event";
import ActivityBaseConfig from "../../components/ActivityBaseConfig";
import ActivityField from "../../components/ActivityField";

function FootballConfig() {
  const eventData = useEvent();

  const quarters = ["1st Quarter", "2nd Quarter", "3rd Quarter", "4th Quarter"];

  const downs = ["1st Down", "2nd Down", "3rd Down", "4th Down"];

  const yards = ["1 Yard"];
  for (let i = 2; i < 100; i++) {
    yards.push(i + " Yards");
  }

  const endpoint = "/api/v1/football";

  const [data, setData] = createSignal(null);

  // GET the relevant data on first load
  onMount(async () => {
    const res = await fetch(endpoint);
    const json = await res.json();

    if (json != null) {
      setData(json);
    }
  });

  // After first load, rely on server-sent events for updates
  createEffect(() => {
    if (eventData() != null) {
      setData(eventData());
    }
  });

  return (
    <Show when={data() != null && data().type == "football"}>
      <ActivityBaseConfig
        name="Football"
        teamOneName={data().teamOne.name}
        teamTwoName={data().teamTwo.name}
        teamOneCurrentScore={data().teamOne.score}
        teamTwoCurrentScore={data().teamTwo.score}
        timerValue={data().timer.value}
        timerIsRunning={data().timer.isRunning}
      >
        <div class="grid grid-cols-1 gap-4">
          <ActivityField
            name="quarter"
            endpoint={endpoint}
            fields={quarters}
            index={data().quarter.value}
          />
          <ActivityField
            name="down"
            endpoint={endpoint}
            fields={downs}
            index={data().down.value}
          />
          <ActivityField
            name="yards"
            endpoint={endpoint}
            fields={yards}
            index={data().yards.value}
          />
        </div>
      </ActivityBaseConfig>
    </Show>
  );
}

export default FootballConfig;
