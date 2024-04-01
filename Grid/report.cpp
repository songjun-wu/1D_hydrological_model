#include"Basin.h"


int Basin::report(Control &ctrl){

    if (ctrl.Report_snow==1){
        reportTS(_snow, "snow", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_snow==2){
        reportMap(_snow, "snow", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_theta1==1){
        reportTS(_theta1, "theta1", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_theta1==2){
        reportMap(_theta1, "theta1", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_theta2==1){
        reportTS(_theta2, "theta2", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_theta2==2){
        reportMap(_theta2, "theta2", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_theta3==1){
        reportTS(_theta3, "theta3", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_theta1==2){
        reportMap(_theta3, "theta3", ctrl.path_ResultsFolder);
    }

    // evaptranspiration
    if (ctrl.Report_Ei==1){
        reportTS(_Ei, "Ei", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Ei==2){
        reportMap(_Ei, "Ei", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Es==1){
        reportTS(_Es, "Es", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Es==2){
        reportMap(_Es, "Es", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Tr1==1){
        reportTS(_Tr1, "Tr1", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Tr1==2){
        reportMap(_Tr1, "Tr1", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Tr2==1){
        reportTS(_Tr2, "Tr2", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Tr2==2){
        reportMap(_Tr2, "Tr2", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Tr3==1){
        reportTS(_Tr3, "Tr3", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Tr3==2){
        reportMap(_Tr3, "Tr3", ctrl.path_ResultsFolder);
    }

    // fluxes
    if (ctrl.Report_Th==1){
        reportTS(_Th, "Th", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Th==2){
        reportMap(_Th, "Th", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_snowmelt==1){
        reportTS(_snowmelt, "snowmelt", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_snowmelt==2){
        reportMap(_snowmelt, "snowmelt", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Qs==1){
        reportTS(_Qs, "Qs", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Qs==2){
        reportMap(_Qs, "Qs", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_infilt==1){
        reportTS(_infilt, "infilt", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_infilt==2){
        reportMap(_infilt, "infilt", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Perc1==1){
        reportTS(_Perc1, "Perc1", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Perc1==2){
        reportMap(_Perc1, "Perc1", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Perc2==1){
        reportTS(_Perc2, "Perc2", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Perc2==2){
        reportMap(_Perc2, "Perc2", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Perc3==1){
        reportTS(_Perc3, "Perc3", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Perc3==2){
        reportMap(_Perc3, "Perc3", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_I==1){
        reportTS(_I, "I", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_I==2){
        reportMap(_I, "I", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_D==1){
        reportTS(_D, "D", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_D==2){
        reportMap(_D, "D", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_Imax==1){
        reportTS(_Imax, "Imax", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_Imax==2){
        reportMap(_Imax, "Imax", ctrl.path_ResultsFolder);
    }

 
    if (ctrl.tracking_isotope==1){
    if (ctrl.Report_d2hSW1==1){
        reportTS(_d2hSW1, "d2hSW1", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_d2hSW1==2){
        reportMap(_d2hSW1, "d2hSW1", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_d2hSW2==1){
        reportTS(_d2hSW2, "d2hSW2", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_d2hSW2==2){
        reportMap(_d2hSW2, "d2hSW2", ctrl.path_ResultsFolder);
    }

    if (ctrl.Report_d2hSW3==1){
        reportTS(_d2hSW3, "d2hSW3", ctrl.path_ResultsFolder);
    } else if (ctrl.Report_d2hSW3==2){
        reportMap(_d2hSW3, "d2hSW3", ctrl.path_ResultsFolder);
    }
    }

    return 0;
}

sortedTSmask Basin::sortTSmask(){
  sortedTSmask TSmask;
  for(int i = 1; i < _rowNum-1; i++){
    for(int j = 1; j < _colNum-1; j++){ 
        if (_Gauge_to_Report->matrix[i][j] != 0){
            TSmask.row.push_back(i);
            TSmask.col.push_back(j);
        }
    }
  }
  return TSmask;
}


int Basin::writeAlltoBin(Control &ctrl){
    int ntimestep = ctrl.Simul_end / ctrl.Simul_tstep;
    int nTSmask = _Tsmask.row.size();
    int sampleSize = ntimestep * nTSmask;

    if (ctrl.ifreporteverytimestep == 0) {
    int ntimestep = ctrl.Simul_end / ctrl.Simul_tstep;
    int nTSmask = _Tsmask.row.size();
    int sampleSize = ntimestep * nTSmask;

    if (ctrl.Report_snow==1) writeToBin(_snow_all, "snow", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_theta1==1) writeToBin(_theta1_all, "theta1", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_theta2==1) writeToBin(_theta2_all, "theta2", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_theta3==1)writeToBin(_theta3_all, "theta3", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_Ei==1) writeToBin(_Ei_all, "Ei", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_Es==1)  writeToBin(_Es_all, "Es", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_Tr1==1) writeToBin(_Tr1_all, "Tr1", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_Tr2==1) writeToBin(_Tr2_all, "Tr2", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_Tr3==1) writeToBin(_Tr3_all, "Tr3", ctrl.path_ResultsFolder, sampleSize);

    if (ctrl.Report_Th==1) writeToBin(_Th_all, "Th", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_snowmelt==1) writeToBin(_snowmelt_all, "snowmelt", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_Qs==1) writeToBin(_Qs_all, "Qs", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_infilt==1) writeToBin(_infilt_all, "infilt", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_preferential2==1) writeToBin(__preferential2_all, "preferential2", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_preferential3==1) writeToBin(__preferential3_all, "preferential3", ctrl.path_ResultsFolder, sampleSize);


    if (ctrl.Report_Perc1==1) writeToBin(_Perc1_all, "Perc1", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_Perc2==1) writeToBin(_Perc2_all, "Perc2", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_Perc3==1) writeToBin(_Perc3_all, "Perc3", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_I==1) writeToBin(_I_all, "I", ctrl.path_ResultsFolder, sampleSize);
    if (ctrl.Report_D==1) writeToBin(_D_all, "D", ctrl.path_ResultsFolder, sampleSize);
    
    if (ctrl.tracking_isotope==1){
      if (ctrl.Report_d2hSW1==1) writeToBin(_d2hSW1_all, "d2hSW1", ctrl.path_ResultsFolder, sampleSize);
      if (ctrl.Report_d2hSW2==1) writeToBin(_d2hSW2_all, "d2hSW2", ctrl.path_ResultsFolder, sampleSize);
      if (ctrl.Report_d2hSW3==1) writeToBin(_d2hSW3_all, "d2hSW3", ctrl.path_ResultsFolder, sampleSize);
  }
    }

    return 0; 
}

int Basin::updateOutput_all(Control &ctrl){
    int currentTS = ctrl.current_ts / ctrl.Simul_tstep;

    if (ctrl.Report_snow==1) updateOutput(_snow, _snow_all, currentTS);
    if (ctrl.Report_theta1==1) updateOutput(_theta1, _theta1_all, currentTS);
    if (ctrl.Report_theta2==1) updateOutput(_theta2, _theta2_all, currentTS);
    if (ctrl.Report_theta3==1) updateOutput(_theta3, _theta3_all, currentTS);
    if (ctrl.Report_Ei==1) updateOutput(_Ei, _Ei_all, currentTS);
    if (ctrl.Report_Es==1) updateOutput(_Es, _Es_all, currentTS);
    if (ctrl.Report_Tr1==1) updateOutput(_Tr1, _Tr1_all, currentTS);
    if (ctrl.Report_Tr2==1) updateOutput(_Tr2, _Tr2_all, currentTS);
    if (ctrl.Report_Tr3==1) updateOutput(_Tr3, _Tr3_all, currentTS);

    if (ctrl.Report_Th==1) updateOutput(_Th, _Th_all, currentTS);
    if (ctrl.Report_snowmelt==1) updateOutput(_snowmelt, _snowmelt_all, currentTS);
    if (ctrl.Report_Qs==1) updateOutput(_Qs, _Qs_all, currentTS);
    if (ctrl.Report_infilt==1) updateOutput(_infilt, _infilt_all, currentTS);
    if (ctrl.Report_infilt==1) updateOutput(_preferential2, __preferential2_all, currentTS);
    if (ctrl.Report_infilt==1) updateOutput(_preferential3, __preferential2_all, currentTS);
    if (ctrl.Report_Perc1==1) updateOutput(_Perc1, _Perc1_all, currentTS);
    if (ctrl.Report_Perc2==1) updateOutput(_Perc2, _Perc2_all, currentTS);
    if (ctrl.Report_Perc3==1) updateOutput(_Perc3, _Perc3_all, currentTS);
    if (ctrl.Report_I==1) updateOutput(_I, _I_all, currentTS);
    if (ctrl.Report_D==1) updateOutput(_D, _D_all, currentTS);
    
    if (ctrl.tracking_isotope==1){
      if (ctrl.Report_d2hSW1==1) updateOutput(_d2hSW1, _d2hSW1_all, currentTS);
      if (ctrl.Report_d2hSW2==1) updateOutput(_d2hSW2, _d2hSW2_all, currentTS);
      if (ctrl.Report_d2hSW3==1) updateOutput(_d2hSW3, _d2hSW3_all, currentTS);
  }
    return 0; 
}

int Basin::updateOutput(const grid *input, double *arr, int currentTS){

    for (int i = 0; i<_Tsmask.row.size(); i++){
        arr[i + currentTS * _Tsmask.row.size()] = input->matrix[_Tsmask.row[i]][_Tsmask.col[i]];
    }

    return 0; 
}

int Basin::writeToBin(double *arr, string varname, string filepath, int n){
    fstream ofOutput;
    string filename;
    
    filename =  filepath + varname.c_str() + "_TS.bin";
    ofOutput.open(filename.c_str(), ios::binary|ios::app);
    ofOutput.write((char*)arr, sizeof(double)*n);
    ofOutput.close(); 
    return 0; 
}

int Basin::reportTS(const grid *input, string varname, string filepath){
    fstream ofOutput;
    double outdata[_Tsmask.row.size()];
    string filename;

    for (int i = 0; i<_Tsmask.row.size(); i++){
        outdata[i] = input->matrix[_Tsmask.row[i]][_Tsmask.col[i]];
    }

    filename =  filepath + varname.c_str() + "_TS.bin";
    ofOutput.open(filename.c_str(), ios::binary|ios::app);
    ofOutput.write((char*)&outdata, sizeof(double)*_Tsmask.row.size());

    ofOutput.close();   

    return 0;
}

int Basin::reportMap(const grid *input, string varname, string filepath){
  fstream ofOutput;
  double outdata[_rowNum*_colNum];
  string filename;

  for(int i = 0; i < _rowNum; i++){
     for(int j = 0; j < _colNum; j++){
        outdata[i*_rowNum + j] = input->matrix[i][j];
     }
  }

  filename =  filepath + varname.c_str() + "_map.bin";
  ofOutput.open(filename.c_str(), ios::binary|ios::app);

  ofOutput.write((char*)&outdata, sizeof(double)*_rowNum*_colNum);

  ofOutput.close();
  return 0;
}
