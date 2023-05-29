# Linear Correction

This folder contains a Klipper implementation of the Prusa linear correction method, which is a useful technique for fixing zebra artifacts. The original Prusa implementation and more details can be found [here](https://help.prusa3d.com/article/extruder-linearity-correction-calibration_2254)] and [here](https://github.com/prusa3d/Prusa-Firmware/blob/8d1abf772dd930c3cfa8e5021d18c4d414359b04/Firmware/tmc2130.cpp#L838).

Each file in this repository is named with a factor of 1000, so for example, `linear-correction-30.cfg` corresponds to a linear correction factor of `1.030`.

The default Prusa linear correction is `0`, the corresponding file is `linear-correction-0.cfg`.

Linear correction can be especially useful if you have changed the `rotation_distance` parameter.

Currently, there is no way to run prusa test tower, you will have to run it manually. It can probably be implemented with custom macros based on `generate.c` code.
