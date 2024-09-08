import os
import sys
import time
import numpy as np
from pathlib import Path
from optparse import OptionParser

import modelTools_dev
import psutil


nrow = 3
ncol = 3
nodata = -9999.0
cellSize = 50
xllcorner = 442449
yllcorner = 5798066

startDate = "2017-01-01"
endDate = "2021-12-31"

spinup_days = 365

ntimestep = 1826



homePath =str(Path(os.getcwd()).parent) + '/'   # the directory of model and data


  
scratchPath = homePath + '/test_case/'  # the directory for test case

modelName = "ech2o_iso" # Name of model execution
modelPath = homePath+"model/release_linux/"  # path of model
inputPath = homePath+"data/"  # path of inputs
runPath = scratchPath+"run/"   # path for model running
resultPath = scratchPath+"results/"  # path for result saving

recomplie = True  # Do we need to recompile the model? Set to True for the first run on new device or when the codes are changed

nsample = 100


time0 = time.time()
print('RAM memory used:', psutil.virtual_memory()[2])

modelTools_dev.caliRun(inputPath, modelPath, modelName, runPath, nsample, nrow, ncol, nodata, cellSize, xllcorner, yllcorner, startDate, endDate, recomplie)  # run simuations
modelTools_dev.saveOutputs(inputPath, runPath, resultPath, nsample, validIdxMask=False)  # save outputs
time1 = time.time()
print('Simulation is done within '+str((time1-time0)//60) +'min !', '       RAM memory used:', psutil.virtual_memory()[2])



    

