# Matter On-Off Switch Application

This template can be used as a starting point to create Matter applications for the ESP32 controller.

To compile follow the [connectedhomeip](https://github.com/project-chip/connectedhomeip/blob/bc8c9ece127e42033543ecfa7b03341e6dcff1cc/docs/guides/esp32/setup_idf_chip.md) environment setup and [application usage](https://github.com/project-chip/connectedhomeip/blob/bc8c9ece127e42033543ecfa7b03341e6dcff1cc/docs/guides/esp32/build_app_and_commission.md) guides.

Please include a link to the connectedhomeip repo as follows:

```
mkdir third_party
cd third_party
ln -s <path_to>/connectedhomeip .
```

To start building the project. First set the chip (esp32, esp32s3, etc.)
```
idf.py set-target esp32
```
This will create the `sdkconfig` file based on the default configuration provided. If you wish to change someting use:
```
idf.py menuconfig
```
To build, flash and start the monitor use:
```
idf.py flash monitor
```
This example provides functionality for the `On-Off` cluster only. To support other clusters use the [code generation](https://github.com/project-chip/connectedhomeip/blob/bc8c9ece127e42033543ecfa7b03341e6dcff1cc/docs/code_generation.md) guide. 
Edit the `app.zap` file with the ZAP gui and then generate the `app.matter` file as follows:

```
cd main/zap
../../third_party/connectedhomeip/scripts/tools/zap/run_zaptool.sh app.zap
zap-cli -z ../../third_party/connectedhomeip/src/app/zap-templates/zcl/zcl.json -g /Users/milko/repos/connectedhomeip/src/app/zap-templates/matter-idl.json -i app.zap -o . generate
mv Clusters.matter app.matter
```
Add the directory with the provided cluster implementation in the `main/CMakeLists.txt` file for all enabled clusters:
```
"${CHIP_ROOT}/src/app/clusters/<cluster-implementation>"
```

And finally implement the cluster callback in the `DeviceCallbacks.cpp` file.



