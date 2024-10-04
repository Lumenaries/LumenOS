# lumen

This repository contains the software associated with the Portable LED
Scoreboard project for the University of Idaho's College of Engineering Senior
Capstone Design Program.

To learn more about the project, please see the `docs` directory.

The source code for the ESP32-S3 microcontroller is stored in the `src`
directory. The source code for the web frontend is stored in the `frontend/src`
directory.

* Demo

https://github.com/user-attachments/assets/002fa658-3faf-4c77-9a63-f6c103c0f548

* University of Idaho Senior Design EXPO Poster

![expo_poster](https://github.com/user-attachments/assets/703bd685-ae03-421d-b260-40aa2fd5bc68)


## Dependencies

This project requires `arduino core`. You have a few options here:

- Clone [arduino core](https://github.com/espressif/arduino-esp32) to `lib`

  ```
  $ git clone https://github.com/espressif/arduino-esp32.git lib/arduino
  ```

  We don't recommend this because it's such a large library (2+ GB), if you need
  to use it anywhere else, you'll end up waiting around for a while to
  redownload it.

- Clone [arduino core](https://github.com/espressif/arduino-esp32) to some
  directory like `~/sdk/esp/arduino` and export the `ARDUINO_ESP32_PATH`
  environment variable.

  ```
  $ mkdir -p ~/sdk/esp/arduino
  $ git clone https://github.com/espressif/arduino-esp32.git ~/sdk/esp/arduino/arduino
  $ export ARDUINO_ESP32_PATH="~/sdk/esp/arduino"
  ```

This project uses the `esp-idf` SDK. Please follow the instructions to install
[esp-idf v5.1](https://docs.espressif.com/projects/esp-idf/en/v5.1/esp32/get-started/index.html)
and source it.

`lumen` was written with the
[ESP32-S3](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)
in mind, but it'll probably work on other ESP32 variants.

```
$ idf.py set-target esp32s3
```

## Building

After setting up the dependencies, build the project.

1. Clone the repository and navigate to it

```
$ git clone https://github.com/Lumenaries/lumen.git; cd lumen
```

2. Initialize all of the submodules

```
$ git submodule update --init --recursive
```

3. Build the project

```
$ idf.py set-target esp32s3; idf.py build
```

4. Flash and monitor the project

```
$ idf.py -p /path/to/esp32s3 flash monitor
```

## Troubleshooting

### Configurations

_`button_gpio_config_t` has no non-static data member named `enable_power_save`_

Open `menuconfig`.

```
$ idf.py menuconfig
```

In `Component config`/`IoT Button`, select `GPIO BUTTON SUPPORT POWER SAVE`.

### Frontend

_Frontend file exists, but the server is unable to open it._

The frontend files may not exist in the partition on the ESP32-S3. Run the
following command.

```
$ idf.py partition-table-flash
```
