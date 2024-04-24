import { Show, createResource, createSignal, lazy } from "solid-js";

import ActivityBaseConfig from "../../components/ActivityBaseConfig";
import ActivityField from "../../components/ActivityField";

function FootballConfig() {
  // TODO: Add an API prop

  const quarters = ["1st Quarter", "2nd Quarter", "3rd Quarter", "4th Quarter"];

  const downs = ["1st Down", "2nd Down", "3rd Down", "4th Down"];

  const yards = ["1 Yard"];
  for (let i = 2; i < 100; i++) {
    yards.push(i + " Yards");
  }

  const endpoint = "/api/v1/football";

  const getFromEndpoint = async function () {
    const data = await fetch(endpoint);
    return data.json();
  };

  const [data] = createResource(getFromEndpoint);

  return (
    <Show when={!data.loading}>
      <ActivityBaseConfig
        name="Football"
        teamOneName={data().teamOne.name}
        teamTwoName={data().teamTwo.name}
        teamOneCurrentScore={data().teamOne.score}
        teamTwoCurrentScore={data().teamTwo.score}
        timerValue={data().timer.value}
      >
        <div class="grid grid-cols-1 gap-4">
          <ActivityField
            name="quarter"
            endpoint={endpoint}
            fields={quarters}
            currentIndex={quarters[data().quarter.value - 1]}
          />
          <ActivityField
            name="down"
            endpoint={endpoint}
            fields={downs}
            currentIndex={downs[data().down.value - 1]}
          />
          <ActivityField
            name="yards"
            endpoint={endpoint}
            fields={yards}
            currentIndex={yards[data().yards.value - 1]}
          />
        </div>
      </ActivityBaseConfig>
    </Show>
  );
}

export default FootballConfig;
