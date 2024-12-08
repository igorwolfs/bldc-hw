# ADC
## Converting temperature and battery voltage to real values

### Reference voltage
- VREFINT: 1.2-1.25 Volts (typically 1.23 V)-
- Internal reference VREFINT_CAL: reference voltage at 3.3 V: (0x1FFF F7BA, 0x1FFF F7BB)


### Temperature
The temperature is measured over
- 3.3 V
- R38: 33 kOhm resistor
- Temperature measurement
- 47 kOhm thermistor to GND: SDNT1005X473F4050FTF
    - Datasheet: https://wmsc.lcsc.com/wmsc/upload/file/pdf/v2/lcsc/2110081330_Sunlord-SDNT1005X473F4050FTF_C279702.pdf
    - Base resistance: 47 kOhm (at 25 degrees (298.15 K))
    - B-constant: 4050 (between 25->50 degrees (298.15 -> 323.15))

**Thermistor variation**
Temperature change: B(T1->T2) = T1*T2 / (T2-T1) * ln(R1 / R2)
So: ln(R1/R2) / Beta = 1/T1 - 1/T2
So the temperature T2 becomes
=> 1/T2 = 1/T1 - ln(R1/R2) / Beta


**Test**
Values at room temperature:
- 2357-2360


1. Resolution: 12-bit (2**12-1 steps) = 4095
2. Reference voltage assume 3.3
3. So vtemp = 3.3 * (2360/4095) = 1.90183150183
4. So Ith = (3.3-vtemp) / 33 kOhm = 42 uA
5. So Rth = vtemp / Ith = 44.9e3
6. So T2 = (1/298.15 - ln(47/45) / 4050)^(-1) - 273.15 = 26 degrees OK

**Internal temperature channel**
- Temperature range: -40 -> 124 degrees C
- Temperature (in °C) = {(V25 – VTS) / Avg_Slope} + 25
    - Average slope: 4-4.6 mV/degree C
    - V25: 1.34-1.42 V (Voltage at 25 degrees C)

Calibration value:
- TS_CAL1: 0x1FFF F7B8 - 0x1FFF F7B9 (acquired at 30 degrees)
- TS_CAL2: 0x1FFF F7C2 - 0x1FFF F7C3 (acquired at 110 degrees)
