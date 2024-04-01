#include "Basin.h"

int Basin::initialiseClimateMaps(string fname, ifstream &ifHandle){
  int max = 0;
  int r, c;
  ifHandle.open(fname, ios::binary);
  if (!ifHandle.good()){
    throw runtime_error("file now found    :" + fname);
  }
  for (unsigned int j = 0; j < _sortedGrid.row.size(); j++) {
	  r = _sortedGrid.row[j];
	  c = _sortedGrid.col[j];
    if (_climzones->matrix[r][c] > max){
      max = _climzones->matrix[r][c];
    }
  _nzones = max+1;

  
  return EXIT_SUCCESS;
  }
}

int Basin::updateClimateMaps(ifstream &ifHandle, grid &climateMap){
  double *data=NULL;
  int r, c;
  int zoneID;

  data = new double[_nzones];
  ifHandle.read((char *)data, sizeof(double)*_nzones);  
  
  for (unsigned int j = 0; j < _sortedGrid.row.size(); j++) {
	  r = _sortedGrid.row[j];
	  c = _sortedGrid.col[j];
    zoneID = _climzones->matrix[r][c];
    climateMap.matrix[r][c] = data[zoneID];
    }

  delete[] data;
  return EXIT_SUCCESS;
}

int Basin::updateClimateStatus(Control &ctrl){
    updateClimateMaps(if_P, *_P);
    updateClimateMaps(if_Ta, *_Ta);
    updateClimateMaps(if_Ta_min, *_Ta_min);
    updateClimateMaps(if_Ta_max, *_Ta_max);
      
    updateClimateMaps(if_RH, *_RH);
    updateClimateMaps(if_PET, *_PET);
    updateClimateMaps(if_LAI, *_LAI);
    if (ctrl.tracking_isotope==1){
      updateClimateMaps(if_d2hP, *_d2hP);
    }
    return EXIT_SUCCESS;
}