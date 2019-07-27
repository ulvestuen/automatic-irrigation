# Automatic irrigation system



## OTA firmware update
Firmware update can be made by issuing the following command from within the folder `/<your local path>/automatic-irrigation/.pio/build/nodemcuv2/`:
```
curl -X POST http://<ip-address>/update -H 'content-type: multipart/form-data' -F update=@firmware.bin
```
This upload the current binary `firmware.bin` and restarts the microcontroller.