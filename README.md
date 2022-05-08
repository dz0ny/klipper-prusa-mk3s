# Kliper on Prusa MK3s
Structured Klipper config for Prusa MK3s/MK3s+ 3D printer, inspired by https://github.com/Rat-OS/RatOS-configuration

## Pre-Check

- Get Z offset value from your current firmware (Menu -> Calibration -> Z-offset), you will need it for the Klipper config.
- Your bed needs to be perpendicular (based on XYZ Calibration). If not you will have to do the skew calibration before printing or you risk crashing your nozzle to the bed.
- Read https://github.com/dz0ny/klipper-prusa-mk3s/blob/main/printer.template.cfg
- Read https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller

## Install
1. Install https://docs.mainsail.xyz/setup/mainsail-os to SDCard and RPI Zero 2 W
2. Connect as described in https://help.prusa3d.com/en/article/raspberry-pi-zero-w-preparation-and-installation_2180
3. Update all components under Machine tab, otherwise config might not be able to load
4. Add the following to the to `moonraker.conf`

```yml
[update_manager prusa]
type: git_repo
origin: https://github.com/dz0ny/klipper-prusa-mk3s.git
path: ~/klipper_config/config
primary_branch: main
is_system_service: False
```

2. Copy https://github.com/dz0ny/klipper-prusa-mk3s/blob/main/printer.template.cfg to `printer.cfg` 
3. Adjust config to your hardware
4. Flash Klipper to your printer https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller

You will still need a USB cable as you cannot flash via an internal serial port. You can also use any other computer to compile your firmware.

To use this config, the firmware should be compiled for the AVR atmega2560. To use via serial, in "make menuconfig" select "Enable extra low-level configuration options" and select **serial1** (the RasPi serial) or **serial0** when you plan to connect via the USB.

To flash:
`make flash FLASH_DEVICE=/dev/serial/by-id/usb-Prusa_Research__prusa3d.com__Original_Prusa_i3_MK3_CZPX0620X004XK70128-if00`

7. Print


## Nice things
[Klipper mesh on print area only install guide](https://gist.github.com/ChipCE/95fdbd3c2f3a064397f9610f915f7d02)


## Screenshots
![image](https://user-images.githubusercontent.com/239513/141822711-2818978e-2b87-4110-9b93-e5f489c9cdc7.png)
![image](https://user-images.githubusercontent.com/239513/141831204-89ced257-e67f-4b1f-add7-a3806cdd2617.png)
![image](https://user-images.githubusercontent.com/239513/141831245-11476041-240d-424a-8ff8-ffd8a03c08be.png)
![image](https://user-images.githubusercontent.com/239513/141831272-31b88652-ab3f-4978-8a4c-c54a83817dd1.png)
