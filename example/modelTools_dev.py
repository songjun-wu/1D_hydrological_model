import os
import numpy as np
import pandas as pd
import pyDOE
import pcraster
import shutil
import datetime


def saveToASCII(data, fname, path, dtype, nodata, cellSize, xllcorner, yllcorner):
    if not os.path.exists(path):
        os.makedirs(path)

    data = data.astype(np.double)

    if dtype=='int':
        np.savetxt(path + fname + '.asc', data, fmt='%d')
    else:
        np.savetxt(path + fname + '.asc', data)

    line1 = 'ncols         '+str(data.shape[0])
    line2 = 'nrows         '+str(data.shape[1])
    line3 = 'xllcorner     '+str(xllcorner)
    line4 = 'yllcorner     '+str(yllcorner)
    line5 = 'cellsize      '+str(cellSize)
    line6 = 'NODATA_value  '+str(nodata)
    with open(path + fname + '.asc', 'r+') as f:
        content = f.read()
        f.seek(0,0)
        f.write(line1+'\n'+line2+'\n'+line3+'\n'+line4+'\n'+line5+'\n'+line6+'\n'+content)

def sortEnv(inpath, modelPath, modelName, path, recomplie):
    if os.path.exists(path):
        shutil.rmtree(path)
        os.makedirs(path)
    else:
        os.makedirs(path)

    if not os.path.exists(path+'output/'):
        os.makedirs(path+'output/')

    shutil.copytree(inpath+'spatial', path+'spatial')

    os.chdir(modelPath)
    if recomplie:
        os.system('make clean')
    os.system('make')
    os.symlink(modelPath+modelName, path+modelName)

    for j in range(4):
        fname = 'config'+str(j)+'.ini'
        f = open(inpath + 'configs/' + fname, 'r')
        lines = f.readlines()
        for i in range(len(lines)):
            if '# Paths' in lines[i]:
                lines[i+1] = 'Maps_Folder = ./spatial/\n'
                lines[i+2] = 'Clim_Maps_Folder = '+ inpath + 'climate/\n'
                lines[i+3] = 'Output_Folder = ./output/\n'
        f.close()
        

        f = open(inpath + 'configs/' + fname, 'w')
        f.writelines(lines)
        f.close()

def getvalidIDX(inpath):
    depths = ['20','40','100']
    sites = ['crop','g2e','syntropic','fa']  #cropland, grassland, syntropic, and forest
    
    df = pd.read_csv(inpath+'obs.csv', index_col='time')

    TSlen = len(df.index)

    for i in range(len(depths)):
        locals()['validIDX_theta_'+str(i)] = []   # one dim; nvegType * validIDX; suffix (0-3) means soil layer 1-3 
        locals()['validIDX_d2hSW_'+str(i)] = []
        for j in range(len(sites)):
            idx_swc = np.where(np.logical_not(np.isnan(df.loc[:,sites[j]+"_swc_"+depths[i]]).values))[0]
            idx_iso = np.where(np.logical_not(np.isnan(df.loc[:,sites[j]+"_iso_"+depths[i]]).values))[0]
            
            locals()['validIDX_theta_'+str(i)].append(idx_swc)
            locals()['validIDX_d2hSW_'+str(i)].append(idx_iso)


    return locals()['validIDX_theta_0'], locals()['validIDX_theta_1'], locals()['validIDX_theta_2'], locals()['validIDX_d2hSW_0'], locals()['validIDX_d2hSW_1'], locals()['validIDX_d2hSW_2']
            
def createInputs(path, nrow, ncol, nodata, cellSize, xllcorner, yllcorner, startDate, endDate):
    
    spatialPath = path + "/spatial/"
    climatePath = path+"/climate/"

    if not os.path.exists(spatialPath):
        os.makedirs(spatialPath)
    if not os.path.exists(climatePath):
        os.makedirs(climatePath)

    startDate = datetime.datetime.strptime(startDate, "%Y-%m-%d")
    endDate = datetime.datetime.strptime(endDate, "%Y-%m-%d")


    # Catchment input
    dem = np.full((nrow,nrow), nodata)
    dem[1,1] = 55.0
    saveToASCII(dem, "dem", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)   # DEM.asc

    ref_map = pcraster.setclone(dem.shape[0], dem.shape[1], cellSize, 0.0, 0.0)
    _dem = pcraster.numpy2pcr(pcraster.Scalar, np.array(dem), nodata)
    _ldd = pcraster.lddcreate(_dem, 1e31, 1e31, 1e31, 1e31)
    ldd = (pcraster.pcr2numpy(_ldd, nodata)).astype(np.intc)
    ldd[ldd>10] = nodata
    saveToASCII(ldd, "ldd", spatialPath, "int", nodata, cellSize, xllcorner, yllcorner)  # LDD.asc - flow direction

    arr = np.full((nrow,nrow), 0)
    saveToASCII(arr, "chanWidth", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)  # channel width

    arr = np.full((nrow,nrow), 0)
    saveToASCII(arr, "chanDepth", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)  # channel depth

    arr = np.full((nrow,nrow), 0)
    saveToASCII(arr, "chanLength", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)  # channel length

    arr = np.full((nrow,nrow), nodata)
    arr[1,1] = 0
    saveToASCII(arr, "climzones", spatialPath, "int", nodata, cellSize, xllcorner, yllcorner)  # base climatic zones map with the grid geometry

    arr = np.full((nrow,nrow), nodata)
    arr[1,1] = 1
    saveToASCII(arr, "Tsmask", spatialPath, "int", nodata, cellSize, xllcorner, yllcorner)  # what gauges need to be reported?

    arr = np.full((nrow,nrow), nodata)                                                    # Soil depth of 3 layers
    arr[1,1] = 0.2
    saveToASCII(arr, "depth1", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

    arr = np.full((nrow,nrow), nodata)
    arr[1,1] = 0.2
    saveToASCII(arr, "depth2", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

    arr = np.full((nrow,nrow), nodata)                                                    # Soil porosity of 3 layers
    arr[1,1] = 0.9
    saveToASCII(arr, "porosity1", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

    arr = np.full((nrow,nrow), nodata)
    arr[1,1] = 0.9
    saveToASCII(arr, "porosity2", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

    arr = np.full((nrow,nrow), nodata)
    arr[1,1] = 0.9
    saveToASCII(arr, "porosity3", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

    # fixed parameters
    # global parameters
    arr[1,1] = 1
    saveToASCII(arr, "param_rainMultiplier", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
    arr[1,1] = 0.6
    saveToASCII(arr, "param_depth3", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

    
    arr[1,1] = 0.3  
    saveToASCII(arr, "param_k", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
    arr[1,1] = 0.3
    saveToASCII(arr, "param_x", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

    arr[1,1] = 0.5/1000
    saveToASCII(arr, "param_alpha_0", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
    arr[1,1] = 0.5/1000
    saveToASCII(arr, "param_alpha_1", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
    arr[1,1] = 1/1000
    saveToASCII(arr, "param_alpha_2", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
    arr[1,1] = 2/1000
    saveToASCII(arr, "param_alpha_3", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)


    arr[1,1] = 0/1000
    saveToASCII(arr, "param_degreeFactorMin", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
    arr[1,1] = 3/1000
    saveToASCII(arr, "param_degreeFactorMax", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
    arr[1,1] = 0.5
    saveToASCII(arr, "param_degreeFactorIncrease", spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

    for i in range(4):  # vegetation-dependent parameters
        arr[1,1] = 0
        saveToASCII(arr, "param_pI_"+str(i), spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
        arr[1,1] = 0
        saveToASCII(arr, "param_ptheta1_"+str(i), spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
        arr[1,1] = 0
        saveToASCII(arr, "param_ptheta2_"+str(i), spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
        arr[1,1] = 0
        saveToASCII(arr, "param_ptheta3_"+str(i), spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)
        arr[1,1] = 1
        saveToASCII(arr, "param_leakage_weight_"+str(i), spatialPath, "double", nodata, cellSize, xllcorner, yllcorner)

def param_sampling(savePath, nsample):  
    
    paramNames, paramMins, paramMaxs = getParamAttributes()

    sample = pyDOE.lhs(len(paramNames), nsample)


    for i in range(sample.shape[1]):
        sample[:,i] = sample[:,i] * (paramMaxs[i] - paramMins[i]) + paramMins[i]

    
    if not os.path.exists(savePath):
        os.makedirs(savePath)

    sample.flatten().tofile(savePath+'param.bin')

    return paramNames

def createParamMaps(inpath, savePath, param_names, param, nrow, ncol, nodata, cellSize, xllcorner, yllcorner):
    arr = np.full((nrow,nrow), nodata)

    for i in range(len(param)):
        arr[1,1] = param[i]
        saveToASCII(arr, param_names[i], savePath, "double", nodata, cellSize, xllcorner, yllcorner)

def saveOutputs(inputPath, runPath, savePath, nsample, validIdxMask):
    validIDX_theta_0, validIDX_theta_1, validIDX_theta_2, validIDX_d2hSW_0, validIDX_d2hSW_1, validIDX_d2hSW_2 = getvalidIDX(inputPath)
    if not os.path.exists(savePath):
        os.makedirs(savePath)

    depths = ["20","40","100"]
    sites = ["crop", "g2e", "syntropic", "fa"]





    outputPath = runPath + "/output/"

    param = np.fromfile(outputPath+"param.bin")         # save parameter
    with open(savePath+"param.bin", "wb+") as f2:  
        param.tofile(f2)

    
    for i in range(3):  # three depths
        data0 = np.fromfile(outputPath+'theta'+str(i+1)+'_TS.bin').reshape(4,nsample,-1)
        data1 = np.fromfile(outputPath+'d2hSW'+str(i+1)+'_TS.bin').reshape(4,nsample,-1)

        for j in range(4): # four vegetation types
            if (validIdxMask):
                with open(savePath+"theta_"+depths[i]+"_"+sites[j]+'.bin', "wb+") as f0:
                    data0[j,:,:][:,locals()['validIDX_theta_'+str(i)][j]].tofile(f0)
                with open(savePath+"d2hSW_"+depths[i]+"_"+sites[j]+'.bin', "wb+") as f1:
                    data1[j,:,:][:,locals()['validIDX_d2hSW_'+str(i)][j]].tofile(f1)
            else:
                with open(savePath+"theta_"+depths[i]+"_"+sites[j]+'.bin', "wb+") as f0:
                    data0[j,:,:].tofile(f0)
                with open(savePath+"d2hSW_"+depths[i]+"_"+sites[j]+'.bin', "wb+") as f1:
                    data1[j,:,:].tofile(f1)
        # filename would be "var_depth_vegetationType.bin"
    print('Results saved at   :     ', outputPath)
            
def caliRun(inputPath, modelPath, modelName, runPath, nsample, nrow, ncol, nodata, cellSize, xllcorner, yllcorner, startDate, endDate, recomplie):
    #createInputs(inputPath, nrow, ncol, nodata, cellSize, xllcorner, yllcorner, startDate, endDate)  
    sortEnv(inputPath, modelPath, modelName, runPath, recomplie)

    os.chdir(runPath)
    param_names = param_sampling(runPath + 'output/', nsample)

    param = np.fromfile(runPath + 'output/param.bin').reshape(-1, len(param_names)) 
    #for i in range(param.shape[0]):
    for i in range(4):  # four types of vegetation
        shutil.copy(inputPath+'configs/config'+str(i)+'.ini', runPath+'config.ini')
        for j in range(nsample):  # iteration over nsample
            createParamMaps(runPath + 'output/', runPath + 'spatial/', param_names, param[j,:], nrow, ncol, nodata, cellSize, xllcorner, yllcorner)    
            os.system(runPath+'/ech2o_iso')

    #plot(resultPath)

def getParamAttributes():
    paramName = ["param_rE" ,    "param_Ic", "param_snowThreshold",   "param_weight_Ei",    "param_weight_Es"] 
    paramMin  = [-0.5,           30/1000,    -2+273.15,               0.1,            0.1]
    paramMax  = [-0.1 ,          60/1000,    2+273.15,                0.9,            0.9]

    paramName_vegDependent =["param_ks1",   "param_ks2",    "param_ks3",    "param_FC1",    "param_FC2",    "param_FC3",    "param_g1", "param_g2", "param_g3", \
                            "param_PFthreshold", "param_PFscale2", "param_PFscale3"]
    paramMin_vegDependent  =[5/1000,        5/1000,         5/1000,         0.15,           0.15,           0.15,            1,          1,          1, \
                            0/1000,         0,                  0]
    paramMax_vegDependent  =[35/1000,       40/1000,        40/1000,        0.7,            0.7,            0.8,             7,          7,          7, \
                            8/1000,         0.4,                0.4]

    paramNames = np.array([])
    paramMins = np.array([])
    paramMaxs = np.array([])
    paramNames = np.append(paramNames, paramName)
    paramMins = np.append(paramMins, paramMin)
    paramMaxs = np.append(paramMaxs, paramMax)

    for i in range(len(paramName_vegDependent)):
        for j in range(4):
            paramNames = np.append(paramNames, paramName_vegDependent[i]+"_"+str(j))
            paramMins = np.append(paramMins, paramMin_vegDependent[i])
            paramMaxs = np.append(paramMaxs, paramMax_vegDependent[i])
    
    return paramNames, paramMins, paramMaxs
