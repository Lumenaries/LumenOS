/** @type {import('tailwindcss').Config} */
const colors = require('tailwindcss/colors');

export default {
  content: [
    "./src/**/*.{js,jsx,ts,tsx}",
  ],
  theme: {
    extend: {},
    screens: {
      'xs': '0px',
      'sm': '576px',
      'md': '768px',
      'lg': '992px',
      'xl': '1200px',
      'xxl': '1400px',
    },
    fontFamily: {
      'normal': ['Poppins Normal', 'sans-serif'],
      'medium': ['Poppins Medium', 'sans-serif'],
      'semibold': ['Poppins Semi-bold', 'sans-serif'],
      'bold': ['Poppins Bold', 'sans-serif'],
      'extrabold': ['Poppins Extra Bold', 'sans-serif'],
      'black': ['Poppins Black', 'sans-serif'],
    },
    colors: {
      'gray': colors.gray,
      'white': colors.white,
      'blue': colors.blue,
      'violet': colors.violet,
      'black': colors.black,
      'text': '#121211',
      'background': '#f9f8f7',
      'primary': '#f78d40',
      'secondary': '#d6b9a425',
      'accent': '#d19b75',
    },
  },
  plugins: [],
}
