# Kliper on Prusa MK3s
Structured Klipper config for Prusa MK3S/+ 3D printer

![image](https://user-images.githubusercontent.com/239513/141822711-2818978e-2b87-4110-9b93-e5f489c9cdc7.png)
![image](https://user-images.githubusercontent.com/239513/141831204-89ced257-e67f-4b1f-add7-a3806cdd2617.png)
![image](https://user-images.githubusercontent.com/239513/141831245-11476041-240d-424a-8ff8-ffd8a03c08be.png)
![image](https://user-images.githubusercontent.com/239513/141831272-31b88652-ab3f-4978-8a4c-c54a83817dd1.png)

## Pre-Check

- Get Z offset value from your current firmware (Menu -> Calibration -> Z-offest), you will need it for Klipper config.
- Read https://github.com/dz0ny/klipper-prusa-mk3s/blob/main/printer.template.cfg
- Read https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller

## Install
1. Install https://docs.mainsail.xyz/setup/mainsail-os to SDCard and RPI Zero 2 W
2. Connect as described in https://help.prusa3d.com/en/article/raspberry-pi-zero-w-preparation-and-installation_2180
3. Add following to the to `moonraker.conf`

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
4. 4. Flash Klipper to your printer https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller

You will still need USB cable as you cannot flash via internal serial port. You can also use any othe computer to compile your firmware.

- For USB connection use FLASH_DEVICE=/dev/serial/by-id/Prusa... and PORT0 for serial in menuconfig
- For RPI native connection use FLASH_DEVICE=/dev/serial/by-id/Prusa... and PORT1 for serial in menuconfig

7. Print
