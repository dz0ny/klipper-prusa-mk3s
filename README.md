# Kliper on Prusa MK3s
Structured Klipper config for Prusa MK3S/+ 3D printer

![image](https://user-images.githubusercontent.com/239513/141822711-2818978e-2b87-4110-9b93-e5f489c9cdc7.png)

## Install

1. Add following to the to `moonraker.conf`

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
4. Print
