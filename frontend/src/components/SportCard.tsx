import { A } from "@solidjs/router";

function SportCard(props) {
  return (
    <div>
      <A href={"/" + props.name.toLowerCase()} class="group">
        <div
          class="mb-2 flex justify-center"
          class="rounded-xl border border-2 border-primary stroke-primary p-1 group-hover:bg-primary group-hover:stroke-white"
        >
          {props.icon}
        </div>
        <p class="m-auto flex justify-center px-3 font-semibold text-xl group-hover:font-bold group-hover:tracking-normal group-hover:text-primary">
          {props.name}
        </p>
      </A>
    </div>
  );
}

export default SportCard;
