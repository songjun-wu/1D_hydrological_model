#include "Basin.h"

Basin::~Basin(){

  /* Catchment info in maps */
  delete _DEM;
  delete _LDD;
  delete _chwidth;
  delete _chdepth;
  delete _chlength;
  delete _Gauge_to_Report;

  delete _depth1;
  delete _depth2;
  delete _depth3;

  delete _poro1;
  delete _poro2;
  delete _poro3;


  /* Climate */
  if_P.close();
  if_Ta.close();
  if_Ta_min.close();
  if_Ta_max.close();
  if_RH.close();
  if_PET.close();
  if_LAI.close();

  delete _climzones;
  delete _P;
  delete _Ta;
  delete _Ta_min;
  delete _Ta_max;
  delete _RH;
  delete _PET;
  delete _LAI;



  /* Parameters */

  delete _PFthreshold;
  delete _PFscale2;
  delete _PFscale3;

  delete _snowThreshold;
  delete _degreeFactorMin;
  delete _degreeFactorMax;
  delete _degreeFactorIncrease;

  delete _rE;
  delete _alpha;
  delete _Ic;
  delete _ks1;
  delete _ks2;
  delete _ks3;
  delete _FC1;
  delete _FC2;
  delete _FC3;
  delete _g1;
  delete _g2;
  delete _g3;
  delete _pI;
  delete _ptheta1;
  delete _ptheta2;
  delete _ptheta3;
  delete _Perc3_weight;
  delete _k;
  delete _x;


  /* state variables used in simualtion */
  delete _I;
  delete _snow;
  delete _theta1;
  delete _theta2;
  delete _theta3;

  delete _I_old;
  delete _Imax_old;
  delete _snow_old;
  delete _theta1_old;
  delete _theta2_old;
  delete _theta3_old;

  delete _Ep;
  delete _Ei;
  delete _Es;
  delete _Tp;
  delete _Tr;
  delete _Tr1;
  delete _Tr2;
  delete _Tr3;
  delete _D;
  delete _Th;
  delete _snowmelt; 
  delete _Qs;
  delete _infilt;
  delete _preferential2;
  delete _preferential3;
  delete _Perc1;
  delete _Perc2;
  delete _Perc3;

  delete _SCF; 
  delete _value0;
  delete _Imax;


  /* Isotope tracking */
  

  if (_d2hP) delete _d2hP;

  if (_d2hI)   delete _d2hI;
  if (_d2hSnow)   delete _d2hSnow;
  if (_d2hSW1)   delete _d2hSW1;
  if (_d2hSW2)   delete _d2hSW2;
  if (_d2hSW3)   delete _d2hSW3;
  if (_d2hEi)   delete _d2hEi;
  if (_d2hEs)   delete _d2hEs;

  if (_d2hTh)   delete _d2hTh;
  if (_d2hSnowmelt)   delete _d2hSnowmelt;
  if (_d2hInfilt)   delete _d2hInfilt;
  if (_d2hPerc1)   delete _d2hPerc1;
  if (_d2hPerc2)   delete _d2hPerc2;
  if (_d2hPerc3)   delete _d2hPerc3;

}