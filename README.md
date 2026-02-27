# survival_korgon

Kavu Island custom map for [Horizon's Zombie Survival mode](https://github.com/Horizon-Private-Server/horizon-deadlocked-patch/tree/develop/survival).

![thumbnail](HUD/preview.png)

## Dependencies

1. Docker
2. [Horizon Forge](https://github.com/Horizon-Private-Server/horizon-forge/wiki/Setup-Guide)
3. Git LFS

## Install Guide

1. Clone the repository into your Forge `/Assets/Maps/` folder. Make sure that the folder name matches the respective `.unity` file in the repo.
2. Open the `.unity` scene file in Forge.

For example:
```sh
cd ~/horizon-forge/Assets/Maps
git clone https://github.com/pavo9001/survival_korgon.git survival_korgon
```

## Building Notes

This map has differing visuals between DZO and PS2/emulator.
When building for PS2, make sure to toggle the DZO build off in the Build window and disabling the DZO only render in the inspector.
When building for DZO make sure to turn off everything but the DZO build on the Build window and disabling the PS2 render in the inspector.

![thumbnail](HUD/instruction_1.png)
![thumbnail](HUD/instruction_2.png)
