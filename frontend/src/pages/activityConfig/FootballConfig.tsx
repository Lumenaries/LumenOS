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

  return (
    <ActivityBaseConfig name="Football">
      <div class="grid grid-cols-1 gap-4">
        <ActivityField fields={quarters} default_field="1st Quarter" />
        <ActivityField fields={downs} default_field="1st Down" />
        <ActivityField fields={yards} default_field="10 Yards" />
      </div>
    </ActivityBaseConfig>
  );
}

export default FootballConfig;
