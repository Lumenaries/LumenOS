import Header from "../components/Header";
import { ToggleButton } from "../components/UtilityComponents";

// TODO: Adjust LED display brightness levels
function Settings() {
  return (
    <>
      <Header>Settings</Header>
      <div class="flex justify-center font-medium">
        <div class="grid w-full max-w-xl grid-cols-1 gap-3">
          <p class="font-bold text-lg">General</p>
          <div class="flex justify-between">
            <span class="my-auto font-bold">Buzzer on Timer End</span>
            <ToggleButton />
          </div>
        </div>
      </div>
    </>
  );
}

export default Settings;
