import { Show, createSignal, lazy } from "solid-js";

import { BaseConfig, Field } from "../../components/SportConfig";

function FootballConfig() {
  const quarters = ["1st Quarter", "2nd Quarter", "3rd Quarter", "4th Quarter"];

  const downs = ["1st Down", "2nd Down", "3rd Down", "4th Down"];

  const yards = ["1 Yard"];
  for (let i = 2; i < 100; i++) {
    yards.push(i + " Yards");
  }

  return (
    <BaseConfig name="Football">
      <div class="grid grid-cols-1 gap-4">
        <Field fields={quarters} default_field="1st Quarter" />
        <Field fields={downs} default_field="1st Down" />
        <Field fields={yards} default_field="10 Yards" />
      </div>
    </BaseConfig>
  );
}

export default FootballConfig;
