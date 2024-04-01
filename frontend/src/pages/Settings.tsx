import Header from "../components/Header";
import { ToggleButton } from "../components/UtilityComponents";

function Settings() {
  return (
    <>
      <Header>Settings</Header>
      <div class="flex justify-center font-medium">
        <div class="grid w-full max-w-xl grid-cols-1 gap-3">
          <p class="font-bold text-lg">Rename Teams</p>
          <div class="flex justify-between">
            <span class="my-auto font-bold">Team 1</span>
            <input
              type="text"
              aria-label="team 1 name"
              placeholder="Enter Team 1 Name..."
              class="max-w-30 block rounded-lg border border-gray-300 bg-gray-50 p-1 text-sm placeholder:italic focus:border-accent focus:outline-none focus:ring-0 focus:ring-gray-800"
            />
          </div>
          <div class="flex justify-between">
            <span class="my-auto font-bold">Team 2</span>
            <input
              type="text"
              aria-label="team 2 name"
              placeholder="Enter Team 2 Name..."
              class="max-w-30 block rounded-lg border border-gray-300 bg-gray-50 p-1 text-sm placeholder:italic focus:border-accent focus:outline-none focus:ring-0 focus:ring-gray-800"
            />
          </div>
          <hr class="my-5 h-0.5 border-0 bg-accent" />
          <p class="font-bold text-lg">General</p>
          <div class="flex justify-between">
            <span class="my-auto font-bold">Theme</span>
            <select class="rounded-lg border border-gray-300 bg-gray-50 p-1 font-normal text-sm text-gray-900">
              <option>Light</option>
              <option>Dark</option>
              <option>System Default</option>
            </select>
          </div>
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
