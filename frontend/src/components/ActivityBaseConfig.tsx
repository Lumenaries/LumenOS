import { A } from "@solidjs/router";
import { Show, createEffect, createSignal } from "solid-js";

import Header from "./Header";
import {
  BackArrowIcon,
  MinusIcon,
  PauseIcon,
  PlayIcon,
  PlusIcon,
} from "./UtilityIcons";

// TODO: Add a configurable timer element
function ActivityBaseConfig(props) {
  const [isRunning, setRunning] = createSignal(props.timerIsRunning);

  createEffect(() => {
    setRunning(props.timerIsRunning);
  });

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
            <Timer
              sport={props.name.toUpperCase()}
              value={props.timerValue}
              isRunning={isRunning()}
              setRunning={setRunning}
            />
          </div>
          <Team
            sport={props.name.toUpperCase()}
            teamIndex="one"
            teamName={props.teamOneName}
            currentScore={props.teamOneCurrentScore}
            isRunning={isRunning()}
          />
          <Team
            sport={props.name}
            teamIndex="two"
            teamName={props.teamTwoName}
            currentScore={props.teamTwoCurrentScore}
            isRunning={isRunning()}
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
  const putIsRunning = function () {
    fetch(`/api/v1/${props.sport.toLowerCase()}`, {
      method: "PUT",
      body: JSON.stringify({ timer: { isRunning: props.isRunning } }),
    });
  };

  const putTimerValue = function () {
    const timerValue =
      Number.parseInt(minutes()) * 60 + Number.parseInt(seconds());
    fetch(`/api/v1/${props.sport.toLowerCase()}`, {
      method: "PUT",
      body: JSON.stringify({ timer: { value: timerValue } }),
    });
  };

  const [minutes, setMinutes] = createSignal(Math.floor(props.value / 60));
  const [seconds, setSeconds] = createSignal(props.value % 60);

  createEffect(() => {
    setMinutes(Math.floor(props.value / 60));
    setSeconds(props.value % 60);
  });

  const changeMinutes = function (minutes) {
    const parsed_min = Number.parseInt(minutes, 10);
    if (Number.isInteger(parsed_min)) {
      setMinutes(parsed_min);
    } else {
      setMinutes(getMinutes());
    }

    putTimerValue();
  };

  const changeSeconds = function (seconds) {
    const parsed_sec = Number.parseInt(seconds, 10);
    if (Number.isInteger(parsed_sec)) {
      setSeconds(parsed_sec);
    } else {
      setSeconds(seconds());
    }

    putTimerValue();
  };

  const timerAlarm = new Audio("audio/timerAlarm.mp3");

  createEffect(() => {
    if (minutes() === 0 && seconds() === 0) {
      timerAlarm.play();
    }
  });

  return (
    <div class="col-span-2 flex justify-center">
      <Show when={props.isRunning}>
        <span class="mr-3 font-medium text-5xl">
          {String(minutes()).padStart(2, "0")}
        </span>

        <span class="mr-3 font-medium text-5xl">:</span>

        <span class="mr-3 font-medium text-5xl">
          {String(seconds()).padStart(2, "0")}
        </span>
      </Show>

      <Show when={!props.isRunning}>
        <input
          type="text"
          id="timerMinutes"
          class="max-w-20 select-all rounded-lg border border-gray-300 bg-gray-50 px-1 text-center font-bold font-medium text-2xl text-5xl focus:border-accent focus:outline-none focus:ring-0 focus:ring-gray-800"
          value={String(minutes()).padStart(2, "0")}
          onChange={(e) => {
            changeMinutes(e.target.value);
            e.target.value = String(minutes()).padStart(2, "0");
          }}
          maxlength="2"
        />

        <span class="px-2 font-medium text-5xl">:</span>

        <input
          type="text"
          id="timerMinutes"
          class="max-w-20 select-all rounded-lg border border-gray-300 bg-gray-50 px-1 text-center font-bold font-medium text-2xl text-5xl focus:border-accent focus:outline-none focus:ring-0 focus:ring-gray-800"
          value={String(seconds()).padStart(2, "0")}
          onChange={(e) => {
            changeSeconds(e.target.value);
            e.target.value = String(seconds()).padStart(2, "0");
          }}
          maxlength="2"
        />
      </Show>

      <Show when={props.isRunning}>
        <button
          class="ml-3 touch-none"
          onClick={function () {
            props.setRunning(false);
            putIsRunning();
          }}
        >
          <PauseIcon />
        </button>
      </Show>

      <Show when={!props.isRunning}>
        <button
          class="ml-3 touch-none"
          onClick={function () {
            props.setRunning(true);
            putIsRunning();
          }}
        >
          <PlayIcon />
        </button>
      </Show>
    </div>
  );
}

function Team(props) {
  const [teamName, setTeamName] = createSignal(props.teamName);
  const [score, setScore] = createSignal(props.currentScore);

  createEffect(() => {
    setTeamName(props.teamName);
    setScore(props.currentScore);
  });

  const team = props.teamIndex === "one" ? "teamOne" : "teamTwo";
  const defaultTeamName = team === "teamOne" ? "Home" : "Away";

  const putTeamName = function () {
    fetch(`/api/v1/${props.sport.toLowerCase()}`, {
      method: "PUT",
      body: JSON.stringify({ [team]: { name: teamName() } }),
    });
  };

  const putScore = function () {
    fetch(`/api/v1/${props.sport.toLowerCase()}`, {
      method: "PUT",
      body: JSON.stringify({ [team]: { score: score() } }),
    });
  };

  const changeTeamName = function (name) {
    if (name != teamName()) {
      setTeamName(name.length > 0 ? name : defaultName);
      putTeamName();
    }
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
        <Show when={props.isRunning}>
          <p class="pb-5 pt-1 font-bold text-2xl">{teamName()}</p>
        </Show>
        <Show when={!props.isRunning}>
          <div class="pb-4">
            <input
              class="max-w-32 select-all rounded-lg border border-gray-300 bg-gray-50 p-1 text-center font-bold text-2xl uppercase focus:border-accent focus:outline-none focus:ring-0 focus:ring-gray-800"
              type="text"
              aria-label={`team ${props.teamIndex} name`}
              value={teamName()}
              size="10"
              maxlength="6"
              onChange={(e) => {
                changeTeamName(e.target.value);
              }}
            />
          </div>
        </Show>
      </div>

      <div class="flex">
        <button
          class="my-auto touch-none rounded-full bg-primary p-1 text-4xl text-white"
          onClick={decreaseScore}
        >
          <MinusIcon />
        </button>
        <div class="mx-3 min-w-16 text-center font-normal text-5xl sm:mx-10">
          {String(score()).padStart(2, "0")}
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
