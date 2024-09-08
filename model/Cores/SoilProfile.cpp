#include"Basin.h"
#include <cmath>
int Basin::SoilProfile() {

  int r, c;
  double degree_day;

  
  
  for (unsigned int j = 0; j < _sortedGrid.row.size(); j++) {
	  r = _sortedGrid.row[j];
	  c = _sortedGrid.col[j];
  

  _snow_old->matrix[r][c] = _snow->matrix[r][c];
  _theta1_old->matrix[r][c] = _theta1->matrix[r][c];
  _theta2_old->matrix[r][c] = _theta2->matrix[r][c];
  _theta3_old->matrix[r][c] = _theta3->matrix[r][c];

  double d1 = _depth1->matrix[r][c];
  double d2 = _depth2->matrix[r][c];
  double d3 = _depth3->matrix[r][c];


  // snow module

  // snow accumulation first
  
  _SRfrac = std::min<double>(1.0,std::max<double>(0.0, (_snowThreshold->matrix[r][c] - _Ta_min->matrix[r][c]) / (_Ta_max->matrix[r][c] - _Ta_min->matrix[r][c])));
  _snow->matrix[r][c] += _Th->matrix[r][c] * _SRfrac;
  
  // then snow melt if temperature > snow rain threshold
  if (_Ta->matrix[r][c] > _snowThreshold->matrix[r][c]) {

    degree_day = (_degreeFactorMin->matrix[r][c] + _degreeFactorIncrease->matrix[r][c] * _P->matrix[r][c] > _degreeFactorMax->matrix[r][c]) ? _degreeFactorMax->matrix[r][c] : _degreeFactorMin->matrix[r][c] + _degreeFactorIncrease->matrix[r][c] * _P->matrix[r][c];
    _snowmelt->matrix[r][c] = degree_day*(_Ta->matrix[r][c] - _snowThreshold->matrix[r][c]);
    notLargerThan(_snowmelt->matrix[r][c], _snow->matrix[r][c]);
    _snow->matrix[r][c] -= _snowmelt->matrix[r][c];
  } else{
    _snowmelt->matrix[r][c] = 0;
  }
  
  _infilt->matrix[r][c] = _Th->matrix[r][c] * (1 - _SRfrac) + _snowmelt->matrix[r][c];
  
  // overland flow
  if (_infilt->matrix[r][c] > _Ic->matrix[r][c]){ //surface runoff Qs if Ic is exceeded
    _Qs->matrix[r][c] = _infilt->matrix[r][c] - _Ic->matrix[r][c];
    _infilt->matrix[r][c] = _Ic->matrix[r][c];
  } else {
    _Qs->matrix[r][c] = 0;
  }


  /********************** Preferential flow ********************/
  if (_infilt->matrix[r][c] > _PFthreshold->matrix[r][c]) {
    _preferential2->matrix[r][c] = _infilt->matrix[r][c] * _PFscale2->matrix[r][c];
    _preferential3->matrix[r][c] = _infilt->matrix[r][c] * _PFscale3->matrix[r][c];
  } else {
    _preferential2->matrix[r][c] = 0;
    _preferential3->matrix[r][c] = 0;
  }
  
  _infilt->matrix[r][c] -= (_preferential2->matrix[r][c] + _preferential3->matrix[r][c]);
  _theta2->matrix[r][c] += _preferential2->matrix[r][c] / d2;

  _theta3->matrix[r][c] += _preferential3->matrix[r][c] / d3;
  /********************** Soil layer 1 ********************/ 
  
  _theta1->matrix[r][c] += _infilt->matrix[r][c] / d1; // update storage in layer 1 


  // transpiration in layer 1
  if (_theta1->matrix[r][c] < _FC1->matrix[r][c]){
    _Tr1->matrix[r][c] = abs((_theta1->matrix[r][c]/_FC1->matrix[r][c]) * _Tp->matrix[r][c]);
  } else{  // if soil storage exceed the maximum cap
    _Tr1->matrix[r][c] = _Tp->matrix[r][c];
  }
  notLargerThan(_Tr1->matrix[r][c],  _theta1->matrix[r][c] * d1);
  _theta1->matrix[r][c] -= _Tr1->matrix[r][c] / d1;
  _Tp->matrix[r][c] -= _Tr1->matrix[r][c];
  

  if (isnan(_Tr1->matrix[r][c])){
    _Tr1->matrix[r][c] = 0;
  }
  if (_Tr1->matrix[r][c] < 0){
    _Tr1->matrix[r][c] = -1 * _Tr1->matrix[r][c];
  }
  // evaporation in layer 1
  if (_Ep->matrix[r][c] == 0){
    _Es->matrix[r][c] = 0;
  } else {
    if (_theta1->matrix[r][c] * d1 > _Ep->matrix[r][c]){
        _Es->matrix[r][c] = (_theta1->matrix[r][c]/_FC1->matrix[r][c]) * _Ep->matrix[r][c];
    } else{
        _Es->matrix[r][c] = (_theta1->matrix[r][c]/_FC1->matrix[r][c]) * _theta1->matrix[r][c] * d1;
    }
    _Es->matrix[r][c] *= _weight_Es->matrix[r][c];
    _theta1->matrix[r][c] -= _Es->matrix[r][c] / d1;
    _Ep->matrix[r][c] -= _Es->matrix[r][c];
  }

  
  // percolation into soil layer 2
  if (_infilt->matrix[r][c] > 0) {
    _Perc1->matrix[r][c] = _ks1->matrix[r][c] * pow ((_theta1->matrix[r][c]/_FC1->matrix[r][c]), _g1->matrix[r][c]);
    notLargerThan(_Perc1->matrix[r][c], _theta1->matrix[r][c] * d1);
    _theta1->matrix[r][c] -= _Perc1->matrix[r][c] /d1;
  } else {
    _Perc1->matrix[r][c] = 0;
  }

  

  /**********************Soil layer 2********************/ 
  _theta2->matrix[r][c] += _Perc1->matrix[r][c] /d2;  // update storage in layer 2

  if(_Tp->matrix[r][c] <= 0){ // tranpiration in layer 2
    _Tr2->matrix[r][c] = 0;
  } else {
    if (_theta2->matrix[r][c] < _FC2->matrix[r][c]){
        _Tr2->matrix[r][c] = abs((_theta2->matrix[r][c] / _FC2->matrix[r][c]) * _Tp->matrix[r][c]);
    } else {
        _Tr2->matrix[r][c] = _Tp->matrix[r][c];
    }

    notLargerThan(_Tr2->matrix[r][c], _theta2->matrix[r][c] * d2);
    _theta2->matrix[r][c] -= _Tr2->matrix[r][c] /d2;
    _Tp->matrix[r][c] -= _Tr2->matrix[r][c];
  }

  if (isnan(_Tr2->matrix[r][c])){
    _Tr2->matrix[r][c] = 0;
  }


  if (_Perc1->matrix[r][c] > 0){ //percolation into layer 3
    _Perc2->matrix[r][c] = _ks2->matrix[r][c] * pow(_theta2->matrix[r][c] / _FC2->matrix[r][c], _g2->matrix[r][c]);
    notLargerThan(_Perc2->matrix[r][c], _theta2->matrix[r][c] * d2);
    _theta2->matrix[r][c] -= _Perc2->matrix[r][c] / d2;
  }
  else {
    _Perc2->matrix[r][c] = 0;
  }



  /**********************Soil layer 2********************/ 

  _theta3->matrix[r][c] += _Perc2->matrix[r][c] / d3; //update storage in layer 3

  if(_Tp->matrix[r][c] <= 0){ //transpiration in layer 3
    _Tr3->matrix[r][c] = 0;
  } else {
    if(_theta3->matrix[r][c] < _FC3->matrix[r][c]){
        _Tr3->matrix[r][c] = abs(_theta3->matrix[r][c] / _FC3->matrix[r][c]) * _Tp->matrix[r][c];
        
    } else {
        _Tr3->matrix[r][c] = _Tp->matrix[r][c];
    }

    notLargerThan(_Tr3->matrix[r][c], _theta3->matrix[r][c]*d3);
    _theta3->matrix[r][c] -= _Tr3->matrix[r][c] / d3;
    _Tp->matrix[r][c] -= _Tr3->matrix[r][c];
  }

  if (isnan(_Tr3->matrix[r][c])){
    _Tr3->matrix[r][c] = 0;
  }
  _Tr->matrix[r][c] = _Tr1->matrix[r][c] + _Tr2->matrix[r][c] + _Tr3->matrix[r][c];   // Total transpiration


  if (_Perc2->matrix[r][c] > 0){ //Percolation to gw reservior
    _Perc3->matrix[r][c] = _Perc3_weight->matrix[r][c] * _ks3->matrix[r][c] * pow(_theta3->matrix[r][c] / _FC3->matrix[r][c], _g3->matrix[r][c]);
    notLargerThan(_Perc3->matrix[r][c], _theta3->matrix[r][c] * d3);
    _theta3->matrix[r][c] -= _Perc3->matrix[r][c] / d3;
  }
  else{
    _Perc3->matrix[r][c] = 0;
  }


  //if (isnan(_Perc3->matrix[r][c])){
  //  _Perc3->matrix[r][c] = 0;
  //}
  }

  //cout<<" "<<_theta3_old->matrix[r][c]<<" "<<_preferential3->matrix[r][c] / _depth3->matrix[r][c] <<" "<<_Perc2->matrix[r][c]/ _depth3->matrix[r][c]<<" "<<_Tr3->matrix[r][c]/ _depth3->matrix[r][c]<<" "<<_Perc3->matrix[r][c]/ _depth3->matrix[r][c]<<" "<<_theta3->matrix[r][c]<<endl;
  //cout<<_theta3->matrix[r][c]-_theta3_old->matrix[r][c]<<"  "<<(_preferential3->matrix[r][c]+_Perc2->matrix[r][c]-_Tr3->matrix[r][c]-_Perc3->matrix[r][c]) / _depth3->matrix[r][c] <<endl;
  //cout<<_theta3->matrix[r][c]-_theta3_old->matrix[r][c] - (_preferential3->matrix[r][c]+_Perc2->matrix[r][c]-_Tr3->matrix[r][c]-_Perc3->matrix[r][c]) / _depth3->matrix[r][c]<<endl;
  

  //tmp0 +=  _Perc1->matrix[r][c] + _preferential2->matrix[r][c];
  //tmp1 += _Perc2->matrix[r][c] + _preferential3->matrix[r][c];
  //tmp2 += _Perc3->matrix[r][c];
  //tmp3 += _theta3->matrix[r][c]-_theta3_old->matrix[r][c];
  //tmp4 += (_preferential3->matrix[r][c]+_Perc2->matrix[r][c]-_Tr3->matrix[r][c]-_Perc3->matrix[r][c]) / _depth3->matrix[r][c];
  //cout<<tmp0<<" "<<tmp1<<" "<<tmp2<<" "<<tmp3<<" "<<tmp4<<endl;
  
  return EXIT_SUCCESS;
}