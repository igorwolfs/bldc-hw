# Issue
At a voltage above 10 volts
- The MC34063 chip doesn't stabilize the voltage to the required number (it stays around 8.5 V)
- The current oscillates between its minimal and maximally set value.
- The voltage stays below 10 volts due to the current limitation.

## Check 1
Check the output of the MC34063A at 10 Volts
- It seems unlikely that all the current goes there, since there's a thermal fuse there which limits the current.

### Observation
The value here seems to simply not increase. It stays around 8-9 volts.

## Check 2
Check the output voltage at 3.3 and 5 V
- Also seems unlikely the current is high there since there's also a thermal fuse present

### Observation
The 3.3 and 5 V outputs are stable

## Check 3
Check the voltage waveform at VBAT

### Observation
- Same waveform as for the 10 V supply

# Observations
- CAN RX is 5 volts (is it supposed to be?)
- 3.3 V is stable, 5 V is stable
- The Phase voltages oscillate depending on the switching, but their average ALWAYS stays between 3-5 volts
    - The voltage here goes up together with the supply.
    - The phase voltage is 1 V at 6 V
    - The phase voltage is 2 V at 7.1 V

## Why is the phase-voltage nonzero?
- They are connected together through the virtual ground.
- There is a factor 1 / 3 x the phase voltage which the virtual ground is supposed to be at.
- They are connected to the OPAMP input through the current resistor.
- The voltage only starts going up from the moment the CPU is supplied with power.
- There's likely curent leaking away through the mosfet switches
    - This can be observed through the sudden voltage spikes over the shunt 0.003 ohm resistor to about 4 volts

### N-channel FET observations
- Datasheet: For conduction: Vgs >= Vth + Vds is a requirement for conduction with Vth: 2-4 volts.
- https://www.lcsc.com/datasheet/lcsc_datasheet_1809041919_Infineon-Technologies-IRFZ44NPBF_C2586.pdf
    - Pin order (gate -> drain -> source)

- VBAT = 5 V
    - Vg: 1.9 V (5 V VBAT)
    - Vd: 5 V
    - Vs: 0.1 V
- VBAT = 7 V
    - Vg: 3.2 V
    - Vd: 7 V
    - Vs: 1.9 V
- VBAT = 9 V
    - Vg: 4.9 V
    - Vd: 9 V 
    - Vs: 3.7
- VBAT = 11 V (current limited to 1 amp)
    - Vg: jumps up and down around 5 V
    - Vd: 11 V
    - Vs: jumps between 5 and 11 volts

Main questions here
- How can it be that the source-voltage is nonzero from the start?
    - I probably should have pulled down the FET driving voltage
- Why do the problems start occuring from the moment the FET drivers get enough voltage to start operating?
    - There seem to be no shorts to ground possible, given the output state of the FET driver is 0 at all times
    - However this does contradict current spikes visible in the shunt resistor to ground.
        - There are peaks of 3.3 V visible here.
    - Voltage at the gate also does show spikes as high as 10 volts
    - Voltage after and before the gate resistor on the driver side show the same spikes
    - So the issue here is probably a connection straight through ground.

#### Try pulling the NSD pin low at all times, check if this issue still happens.
- Current consumption stays below 0.1 Amp
- Buck converter supplies steady 12 V to 

## Try buck converter switching 
- Wait 3 seconds
- Switch phase 1 HIGH
- Wait 3 seconds
- Switch phase 2 HIGH
- Wait 3 seconds
- Switch phase 3 HIGH
- Wait 3 seconds
- Switch phase 1 LOW
- Wait 3 seconds
- Switch phase 2 LOW
- Wait 3 seconds
- Switch phase 3 LOW

One phase of the buck converter each 3 seconds, with 3 seconds in between the switches to make sure the voltage has time to stabilize.

- Check on which up/down there's a voltage drop
    - FET to ground closed?
    - FET to vbat closed?

### Observation
It seems like 3 out of the 6 switches (either connection to ground or connection to VBAT), there is a voltage drop due to current limitation.

The gate on the high side stays high (around 15 V) for too long, it should probably be grounded.
