# LumenOS

This repository contains the software associated with the Portable LED
Scoreboard project for the University of Idaho's College of Engineering Senior
Capstone Design Program.

To learn more about the project, please see the `docs` directory.

The source code for the ESP32-S3 microcontroller is stored in the `main`
directory. The source code for the web frontend is stored in the `frontend/src`
directory.

## Troubleshooting

### Frontend

*Frontend file exists, but the server is unable to open it.*

The frontend files may not exist in the partition on the ESP32-S3. Run the
following command.

```
$ idf.py partition-table-flash
```
