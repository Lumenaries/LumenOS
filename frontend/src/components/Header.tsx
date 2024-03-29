import { ToggleButton } from "../components/UtilityComponents";
import { MenuIcon } from "../components/UtilityIcons";

// TODO: Enhance header to display settings icon and battery levels
function Header(props) {
  return (
    <header class="py-10 font-poppins-extrabold text-3xl">
      <div class="mx-auto flex max-w-xl justify-between">
        {props.children}
        <div class="flex">
          <div class="mr-3">
            <ToggleButton />
          </div>
          <MenuIcon />
        </div>
      </div>
    </header>
  );
}

export default Header;
