import { Show, createSignal } from "solid-js";

import Header from "../components/Header";

function Advertisements() {
  const [ad, set_ad] = createSignal("");
  return (
    <>
      <Header>Advertisements</Header>
      <div class="flex justify-center font-normal">
        <div class="grid w-full max-w-xl grid-cols-1 gap-3">
          <label for="advertisement_message" class="font-bold">
            New Advertisement
          </label>
          <input
            id="advertisement_message"
            type="text"
            aria-label="advertisement message"
            name="advertisement message"
            placeholder="Enter ad message.."
            class="text-md block w-full rounded-lg border border-gray-300 bg-gray-50 p-2.5 placeholder:italic focus:border-gray-800 focus:outline-none focus:ring-0 focus:ring-gray-800"
            onChange={(e) => set_ad(e.currentTarget.value)}
          />
          <button
            type="submit"
            class="justify-self-start rounded-full bg-primary px-2 py-1 font-medium text-white"
          >
            Add
          </button>
          <Show when={ad() != ""}>
            <hr class="my-5 h-0.5 border-0 bg-accent" />
            <p class="justify-self-start">{ad}</p>
          </Show>
        </div>
      </div>
    </>
  );
}

export default Advertisements;
