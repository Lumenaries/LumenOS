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
            <Timer sport={props.name} value={props.timerValue} />
          </div>
          <Score
            sport={props.name}
            teamName="Home"
            team="one"
            currentScore={props.teamOneCurrentScore}
          />
          <Score
            sport={props.name}
            teamName="Away"
            team="two"
            currentScore={props.teamTwoCurrentScore}
          />
          <Show when={typeof props.children === "object"}>
            <div class="col-span-2">{props.children}</div>
          </Show>
        </div>
      </div>
    </>
  );
}

function Timer(props) {
  const [isRunning, setRunning] = createSignal(false);

  const putIsRunning = function () {
    fetch(`/api/v1/${props.sport.toLowerCase()}`, {
      method: "PUT",
      body: JSON.stringify({ timer: { isRunning: isRunning() } }),
    });
  };

  const minutes = Math.floor(props.value / 60);
  const seconds = String(props.value % 60).padStart(2, '0');

  return (
    <div class="flex justify-center">
      <p class="mr-3 font-medium text-5xl">{minutes}:{seconds}</p>
      <Show when={isRunning()}>
        <button
          class="my-auto"
          onClick={function () {
            setRunning(false);
            putIsRunning();
          }}
        >
          <PauseIcon />
        </button>
      </Show>
      <Show when={!isRunning()}>
        <button
          class="my-auto"
          onClick={function () {
            setRunning(true);
            putIsRunning();
          }}
        >
          <PlayIcon />
        </button>
      </Show>
    </div>
  );
}

function Score(props) {
  const [teamName, setTeamName] = createSignal(props.teamName);
  const team = props.team === "two" ? "teamTwo" : "teamOne";
  const [score, setScore] = createSignal(props.currentScore);

  const putScore = function () {
    fetch(`/api/v1/${props.sport.toLowerCase()}`, {
      method: "PUT",
      body: JSON.stringify({ [team]: { score: score() } }),
    });
  };

  const decreaseScore = function () {
    if (score() != 0) {
      setScore(score() - 1);
      putScore();
    }
  };

  const increaseScore = function () {
    setScore(score() + 1);
    putScore();
  };

  return (
    <div>
      <div class="flex justify-center">
        <p class="pb-5 font-bold text-2xl">{teamName}</p>
      </div>

      <div class="flex">
        <button
          class="my-auto touch-none rounded-full bg-primary p-1 text-4xl text-white"
          onClick={decreaseScore}
        >
          <MinusIcon />
        </button>
        <div class="mx-3 min-w-16 text-center font-normal text-5xl sm:mx-10">
          {score}
        </div>
        <button
          class="my-auto touch-none rounded-full bg-primary p-1 text-4xl text-white"
          onClick={increaseScore}
        >
          <PlusIcon />
        </button>
      </div>
    </div>
  );
}

export default ActivityBaseConfig;
