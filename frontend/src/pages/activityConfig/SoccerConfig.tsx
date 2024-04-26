import {
  Show,
  createEffect,
  createSignal,
  onMount,
} from "solid-js";

import { useEvent } from "../../Event";
import ActivityBaseConfig from "../../components/ActivityBaseConfig";
import ActivityField from "../../components/ActivityField";

function SoccerConfig() {
  const eventData = useEvent();
  const endpoint = "/api/v1/soccer";
  const [data, setData] = createSignal(null);

  const halves = ["1st Half", "2nd Half"];

  onMount(async () => {
    const resp = await fetch(endpoint);
    const json = await resp.json();

    if (json != null) {
      setData(json);
    }
  });

  createEffect(() => {
    if (eventData() != null) {
      setData(eventData());
    }
  });

  return (
    <Show when={data() != null && data().type == "soccer"}>
      <ActivityBaseConfig
        name="Soccer"
        teamOneName={data().teamOne.name}
        teamTwoName={data().teamTwo.name}
        teamOneCurrentScore={data().teamOne.score}
        teamTwoCurrentScore={data().teamTwo.score}
        timerValue={data().timer.value}
        timerIsRunning={data().timer.isRunning}
      >
        <ActivityField
          name="half"
          endpoint={endpoint}
          fields={halves}
          index={data().half.value}
        />
      </ActivityBaseConfig>
    </Show>
  );
}

export default SoccerConfig;
