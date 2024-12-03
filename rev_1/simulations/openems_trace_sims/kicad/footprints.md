# ATA6560
- main square: height: 1.7, width: 2.5 -> center in 0,0
- small pads: height: 0.8, width: 0.35

## Position of left-uppermost pad.
y-center: 3/2: 1.5
- yhigh: 3/2+0.8/2, ylow: 3/2-0.8/2

x-center: 2.5/2
-> Offset from side: (2.5-4*width-3*spacing_between_pads) / 2 = (2.5-4*0.35-3*0.2) / 2 = 0.25
- xhigh: -2.5/2+0.25+0.35, xlow: -2.5/2+0.25

## Other pads
- To get other pads on the same x-axis: do x_values + 0.65 (Contact pitch)
- To get to y on the other side, do y + 3 (contact pad spacing)

## Issue
If we compare the length measured using the contact pitch BSC 
-> we get a length (3*0.65+0.35) = 2.3 remaining
If we do the same using the values of width between and of the pads we get:
-> 0.35*4+0.2*3 = 2

So the problem is probably that the values used in the contact pads have a tolerance on them. Their max is 0.8 and 0.35 mm.
So the best way to actually draw the pad is to use the E-value.
- So do the calculation again assuming the distance from the side is not 0.25 but 0.1.
x-center: 2.5/2
-> Offset from side: 0.1
- xhigh: -2.5/2+0.1+0.35, xlow: -2.5/2+0.1
Use the pitch 0.65

- (-0.8 -> -1.15), (1.1 -> 1.9)
## NEW attempt with actual pads instead of rectangles
x_centre: -2.5/2+0.1+0.35/2
y_centre: 3/2
