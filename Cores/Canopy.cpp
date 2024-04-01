#include"Basin.h"

int Basin::Canopy() {

  int r, c;
  double IAvail;  // input for canopy
  double Dmax; // max interception capacity
  double deltaCanopy; // the variation of canopy storage in m

  for (unsigned int j = 0; j < _sortedGrid.row.size(); j++) {
	  r = _sortedGrid.row[j];
	  c = _sortedGrid.col[j];
  


  _I_old->matrix[r][c] = _I->matrix[r][c]; // canopy storage before precipitation addition, interception, transpiration and evaporation

  _P->matrix[r][c] = _P->matrix[r][c] * _rainMultiplier->matrix[r][c];

  _SCF->matrix[r][c] = 1 - exp(_rE->matrix[r][c] * _LAI->matrix[r][c]);     // surface cover fraction, rExtinct = -0.463 Rutter (1972)
  _Tp->matrix[r][c] = (_PET->matrix[r][c] * _SCF->matrix[r][c]);          // fraction potential canopy ET (Ei plus Tr when I = 0) AJN
  _Ep->matrix[r][c] = (_PET->matrix[r][c] * (1-_SCF->matrix[r][c]));        // fraction potential soil evaporation only AJN


  // Interception, simplified Simunek et al (2008) model
  /*
  _Imax->matrix[r][c] = (_alpha->matrix[r][c] * _LAI->matrix[r][c])* (1 - (1 / (1 + ((_SCF->matrix[r][c] * _P->matrix[r][c])/(_alpha->matrix[r][c] * _LAI->matrix[r][c])))));  // in m


  IAvail = _I->matrix[r][c] + _P->matrix[r][c];
  
  if (IAvail>_Imax->matrix[r][c]){ // if no enough space for incoming precipitation, or because of the decrease of Imax
    _Th->matrix[r][c] = IAvail - _Imax->matrix[r][c];
    _I->matrix[r][c] = _Imax->matrix[r][c];
    _D->matrix[r][c] = _I->matrix[r][c] - _I_old->matrix[r][c] < 0 ? 0 : _I->matrix[r][c] - _I_old->matrix[r][c];
    
  } else {  // if availble storage > incoming preciptation
    _Th->matrix[r][c] = 0;
    _I->matrix[r][c] += _P->matrix[r][c];
    _D->matrix[r][c] = _P->matrix[r][c];
  }
  */
  
  _Imax->matrix[r][c] = (_alpha->matrix[r][c] * _LAI->matrix[r][c]); // maximum canopy storage in m
  Dmax = (_alpha->matrix[r][c] * _LAI->matrix[r][c])* (1 - (1 / (1 + ((_SCF->matrix[r][c] * _P->matrix[r][c])/(_alpha->matrix[r][c] * _LAI->matrix[r][c])))));  // max interception capacity in m

  IAvail = _Imax->matrix[r][c] - (_I_old->matrix[r][c] + _P->matrix[r][c]);
  if (IAvail < 0) {
    deltaCanopy = _Imax->matrix[r][c] - _I_old->matrix[r][c];
  } else {
    deltaCanopy = _P->matrix[r][c];
  }
  deltaCanopy = deltaCanopy >= Dmax ? Dmax : deltaCanopy;
  _I->matrix[r][c] += deltaCanopy;
  _Th->matrix[r][c] = _P->matrix[r][c] - deltaCanopy;
  
  _D->matrix[r][c] = deltaCanopy >= 0 ? deltaCanopy : 0;



  /*
 
  if (IAvail<0){
    _Th->matrix[r][c] = _I->matrix[r][c] - _Imax->matrix[r][c]; // throughfall activated 
    IAvail = 0;
    _I->matrix[r][c] = _Imax->matrix[r][c];
    _D->matrix[r][c] = 0;
  } else if (IAvail==0){
    _Th->matrix[r][c] = 0;
    _D->matrix[r][c] = 0;
    _I->matrix[r][c] = _Imax->matrix[r][c];
  } else {
    _D->matrix[r][c] += _P->matrix[r][c];  // interception
    _I->matrix[r][c] = _I->matrix[r][c] + _D->matrix[r][c];
    _Th->matrix[r][c] = 0;   // no throughfall
  }
  */

  // update the canopy water balance change via evaporation

  if (_Ep->matrix[r][c] <= _I->matrix[r][c]){
      _Ei->matrix[r][c] = (_I->matrix[r][c] / _Imax->matrix[r][c]) *  _Ep->matrix[r][c];
  } else {
      _Ei->matrix[r][c] = (_I->matrix[r][c] / _Imax->matrix[r][c]) *  _I->matrix[r][c];
  }
  _Ei->matrix[r][c] *= _weight_Ei->matrix[r][c];
  _I->matrix[r][c] -= _Ei->matrix[r][c];
  _Ep->matrix[r][c] -= _Ei->matrix[r][c];
  
  /*
  if (_Ep->matrix[r][c] <= _I->matrix[r][c]){ // If sufficient water in store to meet full potential canopy ET (Tr), full volume taken from canopy
    _Ei->matrix[r][c] = _Ep->matrix[r][c];
    _I->matrix[r][c] = _I->matrix[r][c] - _Ei->matrix[r][c];
    _Ep->matrix[r][c] = 0;
  } else { // If potential canopy ET great_Der than canopy storage
    _Ei->matrix[r][c] = _I->matrix[r][c];
    _I->matrix[r][c] = 0;
    _Ep->matrix[r][c] = _Ep->matrix[r][c] - _Ei->matrix[r][c];
  }
  */
  
  }
 return EXIT_SUCCESS;
}
