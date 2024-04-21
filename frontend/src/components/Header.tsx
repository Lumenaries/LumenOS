import { MenuIcon } from "../components/UtilityIcons";

// TODO: Enhance header to display settings icon and battery levels
function Header(props) {
  return (
    <header class="mx-auto flex max-w-xl justify-between py-10">
      <div class="font-extrabold text-3xl">{props.children}</div>
      <div class="flex items-center">
        <MenuIcon />
      </div>
    </header>
  );
}

export default Header;
