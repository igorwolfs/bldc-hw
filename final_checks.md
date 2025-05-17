# Outline
- Present
- Continuous outline

# Drilling holes
- Alignment of drill holes vs gerbers
- Alignment of different layers (sometimes layers are mirrored)O
- Are vias and drillholes connected to the right traces as per design?

### Copper
- Alignment of different layers (sometimes they are mirrored)

### Silkscreen
- Check if silkscreen appears for all relevant components
KICAD8-BUG:
- Silkscreen is on the back.

### Soldermask
Make sure anywhere where you need to be able to measure or solder manually, no solder mask whatsoever is put.

### Plating
Make sure the relevant plating is present where it should be.

## Other
### Free DFM checks
Send your gerber files to a free DFM checker.

### Relevant websites
- GERBER: https://jlcpcb.com/help/article/how-to-generate-gerber-and-drill-files-in-kicad-7
- SMT: https://jlcpcb.com/help/article/How-to-generate-the-BOM-and-Centroid-file-from-KiCAD

### Checking manufacturing layer
- https://www.protoexpress.com/blog/what-should-pcb-fab-drawing-include/

# TIPS FOR LATER
- It is very important to have a systematically consistent design in everything: components, vias, THT, traces. Equal spacing here is also very important.
    - If your design is consistent, you will have less trouble checking Gerbers because everything will look consistent.
