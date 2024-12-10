# PWM Configuration
## Configuration
IMPORTANT:
- The channels have to be enabled separately in the sub-menu (so the period needs to be set to nonzero).
- The n-channels should be started using
    - HAL_TIMEx_PWMN_Start()
- The regular channels should be started using
    - HAL_TIM_PWM_Start()

### Duty cycles determination with negative channels
- W_SWITCH: 7 %, (PB5: TIM8 CH3N)
    - Configured as 5000 / 65535 = 7.63 %
- W_SD: 15 %, (PB4: TIM8 CH2N)
    - Configured as 10000 / 65535 = 15.26 %

So the N-channels behave exactly the same as the regular channels when setting them up.

### Checking synchronicity of different timers with the same clock source
All the PWM signals are aligned, which is great.

### Making clocks run according to drive specifications
- SW: 
    - 3.3 V
        - NSD high -> HO: 3.3 V
        - NSD low -> LO: 0 V
    - 0 V
        - NSD high: 0 V
        - NSD low: 3.3 V

Note: we could also assume a period of 30, and simply decide to switch and not-switch the SW-output every other time.

So:
- NSD: needs to be high in order to control the ports.
- SW: controls which port is activated.

One way to control this is probably by attaching an interrupt to the NSD lines, and make the period 30 us. On every other NSD interrupt, the switch should then be switched on / off.

Assuming a period of 60 (us / ms / s), the time that each signal should be low/high with reference to U is displayed below:

Take the 

**PHASE U**

- U_SW: (TIM1, TIM3, TIM8)
    - t: 0->20: 3.3 V
    - t: 20->60: 0 V
- U_NSD: (TIM1, TIM3, TIM8)
    - t: 0->20: 3.3 V
    - t: 20->30: 0 V
    - t: 30->50: 3.3 V
    - t: 50->60: 0 V

**PHASE V**

- V_SW: (TIM1, TIM3, TIM8) (center aligned mode, period 60)
    - t: 0->20: 0 V
    - t: 20->40: 3.3 V
    - t: 40->60: 0 V
- V_NSD: (TIM16, TIM4, TIM8), (center aligned mode required)
    - t: 0->10: 3.3 V
    - t: 10->20: 0 V
    - t: 20->40: 3.3 V
    - t: 40->50: 0 V
    - t: 50->60: 3.3 V

**PHASE W**

- W_SW:  (TIM16, TIM17, TIM3, TIM8) 
    - t: 0->40: 0 V
    - t: 40->60: 3.3 V
- W_NSD: (TIM16, TIM17, TIM3, TIM8)
    - t: 0->10: 0 V
    - t: 10->30: 3.3 V
    - t: 30->40: 0 V
    - t: 40->60: 3.3 V

Notes:
- Phase U and W, 
    - SW aligned left vs right, T=60 
        - PA7: U: TIM8_CH1N
        - PB5: W: TIM8_CH3N
    - NSD aligned left vs right, T=30
        - PB0: U: TIM3_CH3
        - PB4: W: TIM3_CH1
- V_SW: PB1: TIM1_CH3N
- V_NSD: PB6: TIM4_CH1
    - Should be capable of centre PWM

### Implementation
There are 3 options
1. We have to shift to different (non-control) timers 
    - Implement their frequency
    - Shift them (dead-time) in software every time the frequency changes, since only advanced timers have dead-time built-in
2. We can try to generate an interrupt on every SD-PWM trigger
    - Change the respective SW output every other switch using an interrupt
3. Go full software 
    - Implement PWM manually simply thorugh GPIO peripheral
    - Will probably work ok up until the frequencies we need
        - Around 1 MHz
        - So 1/6 = 160 kHz period max which is pretty ok.

**Option 1**

We can try something like this also instead of interrupts:
- if (__HAL_TIM_GET_COUNTER(&htim16) - timer_val > SWITCH_TIME)
- adapt the  SWITCH_TIME variable in order to switch the other PWM as quickly as possible at the right time.
But only if the clock source is high enough and we can do enough checks here.

However we can also use One-pulse mode and restart it after each PWM.

At the same time we then need to use inverted pulse modes for certain PWM.
Apparently however, there are more timers which also have dead-time generation
- the 2 advanced timers (1, 8)
- 1 regular timer
- 2 other regular timers
So 5 timers in total. So dead time could work, since we only need dead time for max 4 timers if we align 2 with the clock start

Then we could just run them for one cycle and go again.
-> However then we would need some kind-of weird solution for the 30 vs 60 s. period.

But it is probably manageable to
1. Pick 6 clocks
2. 3 of which have SW-output
3. 3 of which have NSD-output
4. We choose 2 of SW and 2 of NSD with delay.
    - The 2 middle timers will need a center-aligned PWM signal
    - Other timers will need to be right aligned OR inverted.

When choosing the prescaler
- fCK_PSC / (PSC[15:0] + 1).

So choose the prescaler for the SW equal to 1, this way the frequency will be twice as large as the NS-frequency.

Bumping into a new issue here, which is that multiplying the clock frequency by a certain amount (e.g. by 2, doesn't actually mean the edge stays at the same place, it means the edge shifts too).

This means that any kind of clock scaling thus becomes not really usefull. 

We could introduce a delay for the relevant timers, aka 
- NSD: TIM3 AND TIM4

OR
- SW: TIM8 AND TIM1

It seems like just setting the dead-time as a random value doesn't introduce any shifts. Probably because of some wrong configuration.

Check again, if not go into the trigger and edge-comparison slave-master timer stuff:

https://community.st.com/t5/stm32-mcus-products/stm32f303re-pwms-utilizing-timers-with-phase-shift/td-p/635212

Video explains how one rising edge of one triggers another timer:
https://www.youtube.com/watch?v=QMAgD9SS5_E

**Edge comparison using OC-ref signals**

https://community.st.com/t5/stm32-mcus-products/output-compare-stm32f3discovery/td-p/692551
Compare basically means something changes when somehting else changes. So you can probably add an extra channel with an additional duty cycle shifting the timer.


**Edge triggers**