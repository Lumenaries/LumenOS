import { A } from "@solidjs/router";
import { Show, createSignal } from "solid-js";

import Header from "./Header";
import {
  BackArrowIcon,
  MinusIcon,
  PauseIcon,
  PlayIcon,
  PlusIcon,
} from "./UtilityIcons";

// TODO: Allow user to change team names
// TODO: Add a configurable timer element
function ActivityBaseConfig(props) {
  return (
    <>
      <Header>
        <div class="flex">
          <A href="/" class="my-auto">
            <BackArrowIcon />
          </A>
          <span class="my-auto ml-2 justify-center text-center">
            {props.name}
          </span>
        </div>
      </Header>
      <div class="flex justify-center font-normal">
        <div class="grid grid-cols-2 gap-10">
          <div class="col-span-2 text-center">
            <Timer />
          </div>
          <Score
            team_name="Home"
            team="one"
            default_score={props.default_score}
          />
          <Score
            team_name="Away"
            team="two"
            default_score={props.default_score}
          />
          <Show when={typeof props.children === "object"}>
            <div class="col-span-2">{props.children}</div>
          </Show>
        </div>
      </div>
    </>
  );
}

function Timer() {
  const [is_active, set_active] = createSignal(false);

  return (
    <div class="flex justify-center">
      <p class="mr-3 font-medium text-5xl">10:00</p>
      <Show when={is_active()}>
        <button
          class="my-auto"
          onClick={function () {
            set_active(false);
          }}
        >
          <PauseIcon />
        </button>
      </Show>
      <Show when={!is_active()}>
        <button
          class="my-auto"
          onClick={function () {
            set_active(true);
          }}
        >
          <PlayIcon />
        </button>
      </Show>
    </div>
  );
}

function Score(props) {
  const [team_name, set_team_name] = createSignal(props.team_name);
  const team = props.team;
  const [score, set_score] = createSignal(0);

  const decrease_score = function () {
    if (score() != 0) {
      set_score(score() - 1);
    }
  };

  const increase_score = function () {
    set_score(score() + 1);
  };

  return (
    <div>
      <div class="flex justify-center">
        <p class="pb-5 font-bold text-2xl">{team_name}</p>
      </div>

      <div class="flex">
        <button
          class="my-auto rounded-full bg-primary p-1 text-4xl text-white"
          onClick={decrease_score}
        >
          <MinusIcon />
        </button>
        <div class="mx-3 min-w-16 text-center font-normal text-5xl sm:mx-10">
          {score}
        </div>
        <button
          class="my-auto rounded-full bg-primary p-1 text-4xl text-white"
          onClick={increase_score}
        >
          <PlusIcon />
        </button>
      </div>
    </div>
  );
}

export default ActivityBaseConfig;
