import { Show, createSignal, lazy } from "solid-js";

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

  return (
    <ActivityBaseConfig name="Football">
      <div class="grid grid-cols-1 gap-4">
        <ActivityField
          name="quarter"
          endpoint={endpoint}
          fields={quarters}
          defaultField="1st Quarter"
        />
        <ActivityField
          name="down"
          endpoint={endpoint}
          fields={downs}
          defaultField="1st Down"
        />
        <ActivityField
          name="yards"
          endpoint={endpoint}
          fields={yards}
          defaultField="10 Yards"
        />
      </div>
    </ActivityBaseConfig>
  );
}

export default FootballConfig;
