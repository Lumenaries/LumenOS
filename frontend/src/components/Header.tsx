function Header(props) {
  return (
    <header class="mx-auto flex max-w-xl justify-between py-10 font-extrabold text-3xl">
      {props.children}
    </header>
  );
}

export default Header;
