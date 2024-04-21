import { A } from "@solidjs/router";

import {
  AdIcon,
  ActivityBoardIcon,
  SettingsIcon,
} from "../components/UtilityIcons";

function NavBar() {
  return (
    <nav class="fixed bottom-0 left-0 z-50 h-16 w-full border-t border-gray-200 bg-background lg:h-20">
      <div class="mx-auto grid h-full max-w-lg grid-cols-3">
        <NavElement name="Activities" icon={<ActivityBoardIcon />} nav="/" />
        <NavElement name="Ads" icon={<AdIcon />} nav="/ads" />
        <NavElement name="Settings" icon={<SettingsIcon />} nav="/settings" />
      </div>
    </nav>
  );
}

function NavElement(props) {
  return (
    <A
      href={props.nav}
      class="group inline-flex flex-col items-center justify-center px-5 hover:bg-secondary"
      activeClass="bg-secondary active"
      inactiveClass="bg-background"
      end="true"
    >
      <div class="text-text group-hover:text-primary group-[.active]:text-primary">
        {props.icon}
      </div>
      <span class="font-medium text-sm font-medium text-text group-hover:font-bold group-hover:text-primary group-[.active]:font-bold group-[.active]:text-primary">
        {props.name}
      </span>
    </A>
  );
}

export default NavBar;
