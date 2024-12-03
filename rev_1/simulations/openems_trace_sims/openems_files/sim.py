
import argparse

### Import Libraries
import os, tempfile
from pylab import *

from CSXCAD  import ContinuousStructure
from openEMS import openEMS
from openEMS.physical_constants import *

import shutil

APPCSXCAD_CMD = '~/opt/openEMS/bin/AppCSXCAD'

sim_enabled = True


### CONSTANTS
from openEMS.physical_constants import *
unit = 1e-3 # specify everything in um

## SIMULATION FOLDER SETUP
currDir = os.getcwd()
file_name = os.path.basename(__file__).strip('.py')
Plot_Path = os.path.join(currDir, file_name)
Sim_Path = os.path.join(Plot_Path, file_name)
if sim_enabled:
	if not (os.path.exists(Plot_Path)):
		os.mkdir(Plot_Path)
		os.mkdir(Sim_Path)
	else:
		shutil.rmtree(Sim_Path)
		os.mkdir(Sim_Path)

### FDTD setup
CSX = ContinuousStructure()
'''
#! WARNING: 
- Using the right excitation frequency range is very important here.
'''
max_timesteps = 150000
end_criteria = 1e-4
FDTD = openEMS(NrTS=max_timesteps, EndCriteria=end_criteria)
FDTD.SetCSX(CSX)

#######################################################################################################################################
# BOUNDARY CONDITIONS
#######################################################################################################################################
FDTD.SetBoundaryCond( ['MUR', 'MUR', 'MUR', 'MUR', 'MUR', 'MUR'] )

#######################################################################################################################################
# COORDINATE SYSTEM
#######################################################################################################################################
def mesh():
	x,y,z
      
openEMS_grid = CSX.GetGrid()
openEMS_grid.SetDeltaUnit(unit)


mesh.x = np.array([])
mesh.y = np.array([])
mesh.z = np.array([])


#######################################################################################################################################
# EXCITATION Gaussian
#######################################################################################################################################
# setup FDTD parameter & excitation function
# f0 = 1.5e9 # center frequency
# fc = 500e6 # 20 dB corner frequency

'''
#! WARNING: having the right 
'''
f0 = 1.5e6 # center frequency
fc = 0.5e6 # 20 dB corner frequency

FDTD.SetGaussExcite( f0, fc )



#######################################################################################################################################
# MATERIALS AND GEOMETRY
#######################################################################################################################################
PEC = CSX.AddMetal('PEC');

# ## MATERIAL - FR4
# material_1 = CSX.AddMaterial('FR4');
# material_1.SetMaterialProperty(epsilon=4.3, mue=1, kappa=0.000586)
# material_1.AddPolyhedronReader(os.path.join(currDir,'substrate_gen_model.stl'), priority=9600).ReadFile()

# ## MATERIAL - air
# material_2 = CSX.AddMaterial('air');
# material_2.SetMaterialProperty(epsilon=1, mue=1)
# material_2.AddPolyhedronReader(os.path.join(currDir,'airBox_gen_model.stl'), priority=9300).ReadFile()

## MATERIAL - copper
# material_3 = CSX.AddMetal('copper');
# material_3.AddPolyhedronReader(os.path.join(currDir,'exporting'), priority=9700).ReadFile()
# material_3.AddPolyhedronReader(os.path.join(currDir,'bottom gnd patch_gen_model.stl'), priority=9500).ReadFile()

## MATERIAL - PEC
material_4 = CSX.AddMetal('PEC')
material_4.AddPolyhedronReader(os.path.join(currDir,'exporting_stl.stl'), priority=9800).ReadFile()

