# Importing PCB to openEMS
Execute the following commands:
```python 
from fcad_pcb import kicad
pcb = kicad.KicadFcad("/home/iwolfs/Documents/personal/projects/bldc_project/bldc/rev_1/simulations/openems_trace_sims/kicad/bldc_project.kicad_pcb")
pcb.make(copper_thickness=0.035, board_thickness=1.53, combo=False, fuseCoppers=True )
```
