import { Show, createEffect, createSignal } from "solid-js";

import { LeftArrowIcon, RightArrowIcon } from "./UtilityIcons";

function ActivityField(props) {
  const fieldNames = props.fields;

  const getIndex = () => {
    if (props.index > 0 && props.index <= fieldNames.length) {
      return props.index - 1;
    } else {
      return 0;
    }
  };

  const [field, setField] = createSignal(getIndex());

  createEffect(() => {
    setField(getIndex());
  });

  const putToEndpoint = function () {
    fetch(props.endpoint, {
      method: "PUT",
      body: JSON.stringify({ [props.name]: field() + 1 }),
    });
  };

  const decreaseField = function () {
    if (field() != 0) {
      setField(field() - 1);
      putToEndpoint();
    }
  };

  const increaseField = function () {
    if (field() + 1 != fieldNames.length) {
      setField(field() + 1);
      putToEndpoint();
    }
  };

  return (
    <div class="grid grid-flow-dense grid-cols-4">
      <button class="flex touch-none justify-start" onClick={decreaseField}>
        <Show when={field() > 0}>
          <LeftArrowIcon />
        </Show>
      </button>
      <p class="col-span-2 flex items-center justify-center text-2xl">
        {fieldNames[field()]}
      </p>
      <button class="flex touch-none justify-end" onClick={increaseField}>
        <Show when={field() < fieldNames.length - 1}>
          <RightArrowIcon />
        </Show>
      </button>
    </div>
  );
}

export default ActivityField;
