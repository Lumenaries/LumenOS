function BaseIcon(props) {
  const icon_width = typeof props.width === "undefined" ? "125" : props.width;
  const icon_height =
    typeof props.height === "undefined" ? "125" : props.height;

  return (
    <svg
      xmlns="http://www.w3.org/2000/svg"
      width={icon_width}
      height={icon_height}
      viewBox="0 0 24 24"
      stroke-width="1.5"
      fill="none"
      stroke-linecap="round"
      stroke-linejoin="round"
      class="text-primary"
    >
      {props.children}
    </svg>
  );
}

function BaseballIcon(props) {
  return (
    <BaseIcon width={props.width} height={props.height}>
      <path stroke="none" d="M0 0h24v24H0z" fill="none" />
      <path d="M5.636 18.364a9 9 0 1 0 12.728 -12.728a9 9 0 0 0 -12.728 12.728z" />
      <path d="M12.495 3.02a9 9 0 0 1 -9.475 9.475" />
      <path d="M20.98 11.505a9 9 0 0 0 -9.475 9.475" />
      <path d="M9 9l2 2" />
      <path d="M13 13l2 2" />
      <path d="M11 7l2 1" />
      <path d="M7 11l1 2" />
      <path d="M16 11l1 2" />
      <path d="M11 16l2 1" />
    </BaseIcon>
  );
}

function BasketballIcon(props) {
  return (
    <BaseIcon width={props.width} height={props.height}>
      <path stroke="none" d="M0 0h24v24H0z" fill="none" />
      <path d="M12 12m-9 0a9 9 0 1 0 18 0a9 9 0 1 0 -18 0" />
      <path d="M5.65 5.65l12.7 12.7" />
      <path d="M5.65 18.35l12.7 -12.7" />
      <path d="M12 3a9 9 0 0 0 9 9" />
      <path d="M3 12a9 9 0 0 1 9 9" />
    </BaseIcon>
  );
}

function FootballIcon(props) {
  return (
    <BaseIcon width={props.width} height={props.height}>
      <path stroke="none" d="M0 0h24v24H0z" fill="none" />
      <path d="M15 9l-6 6" />
      <path d="M10 12l2 2" />
      <path d="M12 10l2 2" />
      <path d="M8 21a5 5 0 0 0 -5 -5" />
      <path d="M16 3c-7.18 0 -13 5.82 -13 13a5 5 0 0 0 5 5c7.18 0 13 -5.82 13 -13a5 5 0 0 0 -5 -5" />
      <path d="M16 3a5 5 0 0 0 5 5" />
    </BaseIcon>
  );
}

function SoccerIcon(props) {
  return (
    <BaseIcon width={props.width} height={props.height}>
      <path stroke="none" d="M0 0h24v24H0z" fill="none" />
      <path d="M12 12m-9 0a9 9 0 1 0 18 0a9 9 0 1 0 -18 0" />
      <path d="M12 7l4.76 3.45l-1.76 5.55h-6l-1.76 -5.55z" />
      <path d="M12 7v-4m3 13l2.5 3m-.74 -8.55l3.74 -1.45m-11.44 7.05l-2.56 2.95m.74 -8.55l-3.74 -1.45" />
    </BaseIcon>
  );
}

function TennisIcon(props) {
  return (
    <BaseIcon width={props.width} height={props.height}>
      <path stroke="none" d="M0 0h24v24H0z" fill="none" />
      <path d="M12 12m-9 0a9 9 0 1 0 18 0a9 9 0 1 0 -18 0" />
      <path d="M6 5.3a9 9 0 0 1 0 13.4" />
      <path d="M18 5.3a9 9 0 0 0 0 13.4" />
    </BaseIcon>
  );
}

function VolleyballIcon(props) {
  return (
    <BaseIcon width={props.width} height={props.height}>
      <path stroke="none" d="M0 0h24v24H0z" fill="none" />
      <path d="M12 12m-9 0a9 9 0 1 0 18 0a9 9 0 1 0 -18 0" />
      <path d="M12 12a8 8 0 0 0 8 4" />
      <path d="M7.5 13.5a12 12 0 0 0 8.5 6.5" />
      <path d="M12 12a8 8 0 0 0 -7.464 4.928" />
      <path d="M12.951 7.353a12 12 0 0 0 -9.88 4.111" />
      <path d="M12 12a8 8 0 0 0 -.536 -8.928" />
      <path d="M15.549 15.147a12 12 0 0 0 1.38 -10.611" />
    </BaseIcon>
  );
}

export {
  BaseballIcon,
  BasketballIcon,
  FootballIcon,
  SoccerIcon,
  TennisIcon,
  VolleyballIcon,
};
