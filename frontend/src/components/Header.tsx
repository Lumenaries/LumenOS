import { ToggleButton } from "../components/UtilityComponents";
import { MenuIcon } from "../components/UtilityIcons";

// TODO: Enhance header to display settings icon and battery levels
function Header(props) {
  return (
    <header class="mx-auto flex max-w-xl justify-between py-10">
      <div class="font-extrabold text-3xl">{props.children}</div>
      <div class="flex">
        <div class="mr-3">
          <ToggleButton />
        </div>
        <MenuIcon />
      </div>
    </header>
  );
}

export default Header;
