function ToggleButton() {
  return (
    <label class="inline-flex cursor-pointer items-center">
      <input type="checkbox" value="" class="peer sr-only" />
      <div class="peer-focus:ring-orange-300 peer relative h-6 w-11 rounded-full bg-gray-200 after:absolute after:start-[2px] after:top-[2px] after:h-5 after:w-5 after:rounded-full after:border after:border-gray-300 after:bg-white after:transition-all after:content-[''] peer-checked:bg-primary peer-checked:after:translate-x-full peer-checked:after:border-white peer-focus:outline-none peer-focus:ring-4 rtl:peer-checked:after:-translate-x-full"></div>
    </label>
  );
}

export { ToggleButton };
