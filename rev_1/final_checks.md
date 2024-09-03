# Outline
- Present
- Continuous outline


# Drilling holes
- Alignment of drill holes vs gerbers
- Alignment of different layers (sometimes layers are mirrored
- Are vias and drillholes connected to the right traces as per design?


### Copper
- Alignment of different layers (sometimes they are mirrored)

### Silkscreen
- Check if silkscreen appears for all relevant components
KICAD8-BUG:
- Silkscreen is on the back.
- Silkscreen on back for testpoints
- Silkscreen for caps and diodes


### Soldermask
Make sure anywhere where you need to be able to measure or solder manually, no solder mask whatsoever is put.
- Testpoints top soldermask should be removed, kicad bug leads to bottom one removed


### Plating
Make sure the relevant plating is present where it should be.
- Plating present on testpoints
- No plating on mechanical holes (optional)


## Other
### Free DFM checks
Send your gerber files to a free DFM checker.

### Relevant websites
- GERBER: https://jlcpcb.com/help/article/how-to-generate-gerber-and-drill-files-in-kicad-7
- SMT: https://jlcpcb.com/help/article/How-to-generate-the-BOM-and-Centroid-file-from-KiCAD


### Checking manufacturing layer
- https://www.protoexpress.com/blog/what-should-pcb-fab-drawing-include/