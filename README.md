# Kliper on Prusa MK3s
Structured Klipper config for Prusa MK3s/MK3s+ 3D printer, inspired by https://github.com/Rat-OS/RatOS-configuration

## Pre-Check

- Get Z offset value from your current firmware (Menu -> Calibration -> Z-offset), you will need it for the Klipper config.
- Your bed needs to be perpendicular (based on XYZ Calibration). If not you will have to do the skew calibration before printing or you risk crashing your nozzle to the bed.
- Read https://github.com/dz0ny/klipper-prusa-mk3s/blob/main/printer.template.cfg
- Read https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller

## Install
1. Install https://docs.mainsail.xyz/setup/mainsail-os to SDCard and whatever recommended Raspberry Pi hardware you have chosen
2. Connect to your Raspberry Pi via SSH terminal, a popular client is Putty.
3. Clone config ```git clone https://github.com/dz0ny/klipper-prusa-mk3s.git ~/printer_data/config/klipper-prusa-mk3s```

  > If you are adding this configuration after installing Klipper via [KIAUH](https://github.com/th33xitus/kiauh), the directory might be different - typically following `~/[printer_name]/printer_data/config`, where `[printer_name]` is the name you selected during the Kiauh installation
4. In your web browser, enter the URL or IP address of your MailSailOS instance
5. Within the MainSail web interface, Update all components under Machine tab, otherwise config might not be able to load
6. Within Mainsail's folder menus, add the following to the to `moonraker.conf` to enable automatic updates

```yml
[update_manager prusa]
type: git_repo
origin: https://github.com/dz0ny/klipper-prusa-mk3s.git
path: ~/printer_data/config/klipper-prusa-mk3s
primary_branch: main
is_system_service: False
managed_services: klipper
```

7. Within Mainsail's folder menus, copy https://github.com/dz0ny/klipper-prusa-mk3s/blob/main/printer.template.cfg to `printer.cfg` in your klipper config
8. Adjust config to your hardware
9. Flash Klipper to your printer https://www.klipper3d.org/Installation.html#building-and-flashing-the-micro-controller

You will still need a USB cable as you cannot flash via an internal serial port. You can also use any other computer to compile your firmware.

To use this config, the firmware should be compiled for the AVR atmega2560. To use via serial, in "make menuconfig" select "Enable extra low-level configuration options" and select **serial1** (the RasPi serial) or **serial0** when you plan to connect via the USB.

To flash:
`make flash FLASH_DEVICE=/dev/serial/by-id/usb-Prusa_Research__prusa3d.com__Original_Prusa_i3_MK3_CZPX0620X004XK70128-if00`

10. Print


## Nice things
[Klipper mesh on print area only install guide](https://gist.github.com/ChipCE/95fdbd3c2f3a064397f9610f915f7d02)


## Screenshots
![image](https://user-images.githubusercontent.com/239513/141822711-2818978e-2b87-4110-9b93-e5f489c9cdc7.png)
![image](https://user-images.githubusercontent.com/239513/141831204-89ced257-e67f-4b1f-add7-a3806cdd2617.png)
![image](https://user-images.githubusercontent.com/239513/141831245-11476041-240d-424a-8ff8-ffd8a03c08be.png)
![image](https://user-images.githubusercontent.com/239513/141831272-31b88652-ab3f-4978-8a4c-c54a83817dd1.png)
