# Notes for next version
- Connect the FET driver (ir2104) according to the example schematic
- Use basic components everywhere
- Reuse as many components as possible
- Put actual pads on phase and power supply
- Find a solution where USB to battery power switch actually allows USB connection while switching over to battery power supply.
- Bigger (and more) testpoints
- Use (larger sized) pads meant for manual soldering
- Reduce the source impedance of the ADC's.
	- Otherwise your sampling time will become too large like it became with rev1
## Consider
- Separate the inverter-part from the MCU part