import { Show, createSignal } from "solid-js";

import { LeftArrowIcon, RightArrowIcon } from "./UtilityIcons";

function ActivityField(props) {
  const field_names = props.fields;

  const default_field = field_names.indexOf(props.default_field);

  const [field, set_field] = createSignal(
    default_field == -1 ? 0 : default_field
  );

  const decrease_field = function () {
    if (field() != 0) {
      set_field(field() - 1);

      // TODO: Use an API prop to PUT a JSON object of the updated value to an endpoint.
    }
  };

  const increase_field = function () {
    if (field() + 1 != field_names.length) {
      set_field(field() + 1);

      // TODO: Use an API prop to PUT a JSON object of the updated value to an endpoint.
    }
  };

  return (
    <div class="grid grid-flow-dense grid-cols-4">
      <button class="flex touch-none justify-start" onClick={decrease_field}>
        <Show when={field() > 0}>
          <LeftArrowIcon />
        </Show>
      </button>
      <p class="col-span-2 flex items-center justify-center text-2xl">
        {field_names[field()]}
      </p>
      <button class="flex touch-none justify-end" onClick={increase_field}>
        <Show when={field() < field_names.length - 1}>
          <RightArrowIcon />
        </Show>
      </button>
    </div>
  );
}

export default ActivityField;
