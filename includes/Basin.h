#ifndef BASIN_H_
#define BASIN_H_

#include "dataType.h"
#include "Control.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Basin {
  /*Properties of the simulation*/
  int _rowNum, _colNum;
  double _dx, _nodata;
  sortedGrid _sortedGrid;

  /* Parameters */
  grid *_rainMultiplier; // rainfall multiplier, [-]
  grid *_PFthreshold; // preferential flow will be generated above this threshold, in m
  grid *_PFscale2;  // how much infiltration will directly reach layer 2, in decimal
  grid *_PFscale3;  // how much infiltration will directly reach layer 3, in decimal
  grid *_snowThreshold; // temperature threshold for snow accumulation [C]
  grid *_degreeFactorMin;  // Degree factor when there's no precipitation [m]
  grid *_degreeFactorMax;  // The maxima of degree factor [m]
  grid *_degreeFactorIncrease; // Increase of the Degree-day factor per m of increaseing precipitation
  grid *_weight_Ei; // weight to correct E from interception
  grid *_weight_Es; // weight to correct E from soil layer 1
  grid *_rE;    // extinction factor
  grid *_alpha;     // interception threshold parameter [m]  
  grid *_Ic;  // max Infiltration capacity, if exceeding surface runoff Qs generation [m]
  grid *_ks1;   // saturated hydraulic conductivity upper soil horizon [m]
  grid *_ks2;   // saturated hydraulic conductivity lower horizon [m]
  grid *_ks3;   // saturated hydraulic conductivity deepest horizon [m]
  grid *_FC1;   // field capacity in different soil layers [decimal]
  grid *_FC2;   //
  grid *_FC3;   //
  grid *_g1;   // nonlinear scaling parameter of upper horizon, if g1 = 1, linear case
  grid *_g2;   // nonlinear scaling parameter of lower horizon, if g2 = 1, linear case
  grid *_g3;   // nonlinear scaling parameter of deeper horizon, if g2 = 1, linear case
  grid *_pI;   // passive interception storage mixing volume [m]
  grid *_ptheta1;   // passive storage for mixing in different layers [decimal]
  grid *_ptheta2;  
  grid *_ptheta3;
  grid *_Perc3_weight;  // weight of percolation into gw reserviors
  grid *_k;   // seasonality factor CG model
  grid *_x;   // water vapour mixing ratio CG model

  /* Inputs */
  grid *_DEM; // surface evelation
  grid *_LDD; // flow direction
  grid *_chwidth;
  grid *_chdepth;
  grid *_chlength;
  grid *_Gauge_to_Report;
  sortedTSmask _Tsmask;  // grids to report

  grid *_depth1; // soil depth [m]
  grid *_depth2;
  grid *_depth3;
  grid *_poro1;  // soil porosity [m]
  grid *_poro2;
  grid *_poro3;


  /* Climate */
  grid *_climzones; //map with the zone extents and identifiers
  int _nzones; // the total number of zones
  ifstream if_P;
  ifstream if_Ta;
  ifstream if_Ta_min;
  ifstream if_Ta_max;
  ifstream if_RH;
  ifstream if_PET;
  ifstream if_LAI;
  ifstream if_d2hP;
  grid *_P; // precipitation
  grid *_Ta;  // air temperature
  grid *_Ta_min;  // min air temperature
  grid *_Ta_max;  // max air temperature
  grid *_RH;  // relative humidity
  grid *_PET; // potential evapotranspiration
  grid *_LAI; // leaf area index
  grid *_d2hP; // Deuterium in precipitation

  /* Storages */ 
  grid *_I;   // interception/canopy storage in m
  grid *_snow;  // snow pack in m
  grid *_theta1;  // soil moisture in layer 1 [decimal]
  grid *_theta2;  // soil moisture in layer 2 [decimal]
  grid *_theta3;  // soil moisture in layer 3 [decimal]

  grid *_I_old;   // interception/canopy storage in previous timestep
  grid *_Imax_old;  // the maximum storage of interception, estimated from LAI in previous timestep

  grid *_snow_old;  // snow pack in previous timestep [m]
  grid *_theta1_old;  // soil moisture in layer 1 in previous timestep [decimal]
  grid *_theta2_old;  // soil moisture in layer 2 in previous timestep [decimal]
  grid *_theta3_old;  // soil moisture in layer 3 in previous timestep [decimal]

  /* Evapotranspiration */
  grid *_Ep; // potential evaporation
  grid *_Ei;  //canopy evaporation
  grid *_Es; // soil evaporation
  grid *_Tp; // potential transpiration in mm
  grid *_Tr; // total transpiration
  grid *_Tr1; // transpiration in layer 1
  grid *_Tr2; // transpiration in layer 2
  grid *_Tr3; // transpiration in layer 3

  /* Fluxes */
  grid *_D; // interception
  grid *_Th; // throughfall
  grid *_snowmelt; // snow melt in m
  grid *_Qs; // overland flow
  grid *_infilt; // inflitration into soil layer 1
  grid *_preferential2; // preferential flow to layer 2
  grid *_preferential3; // preferential flow to layer 3
  grid *_Perc1;  // percolation into layer 2
  grid *_Perc2;  // percolation into layer 3
  grid *_Perc3;  // percolation into gw reserviors

  /* internal variables */
  grid *_SCF; // vegetation cover fraction
  int _SRfrac; // snow/rain ratio
  grid *_value0; 
  grid *_Imax;

  /* Isotope tracking */
  grid *_d2hI;   //d2H in interception
  grid *_d2hSnow; //d2H in snowpack
  grid *_d2hSW1;  //d2H in soil layer 1
  grid *_d2hSW2;  //d2H in soil layer 2
  grid *_d2hSW3;  //d2H in soil layer 3
  grid *_d2hEi;  //d2H in interception evaporation
  grid *_d2hEs;  //d2H in soil evaporation

  grid *_d2hTh;
  grid *_d2hSnowmelt;
  grid *_d2hInfilt;
  grid *_d2hPerc1;
  grid *_d2hPerc2;
  grid *_d2hPerc3;

  double *_snow_all;
  double *_theta1_all;
  double *_theta2_all;
  double *_theta3_all;
  double *_Ei_all;
  double *_Es_all;
  double *_Tr1_all;
  double *_Tr2_all;
  double *_Tr3_all;
  double *_Th_all;
  double *_snowmelt_all;
  double *_Qs_all;
  double *_infilt_all;
  double *__preferential2_all;
  double *__preferential3_all;
  double *_Perc1_all;
  double *_Perc2_all;
  double *_Perc3_all;
  double *_I_all;
  double *_D_all;
  double *_d2hSW1_all;
  double *_d2hSW2_all;
  double *_d2hSW3_all;
  
  double tmp0=0;
  double tmp1=0;
  double tmp2=0;
  double tmp3=0;
  double tmp4=0;

  /* constant */
  double RNDOFFERR = 1e-7;
  double PI = 3.14159;


  int getAsciiHeader(string fname);
  sortedGrid SortGridLDD();
  sortedTSmask sortTSmask();
  int initialiseClimateMaps(string fname, ifstream &ifHandle);
  int updateClimateMaps(ifstream &ifHandle, grid &climateMap);


  int updateOutput(const grid *input, double *arr, int currentTS);
  int writeToBin(double *arr, string varname, string filepath, int n);

  int reportMap(const grid *input, string varname, string filepath);
  int reportTS(const grid *input, string varname, string filepath);


  /*  functions  */
  double getSatVaporPressure(const double &T);
  double Calculate_beta(const double &theta, const double &fieldcap);
  void inoutMix(double V_old, double conc_old, double V_in, double conc_in, double V_out, double &conc_out, double V_passive, double &conc_new, int mixmode, int r, int c);
  void notLargerThan(double &Y, double X);

  // for isotope tracking
  int mixing_snow(int r, int c, int isotrackflag);
  int mixing_canopy(int r, int c, int isotrackflag);
  int mixing_soil(int r, int c, int isotrackflag);
  int fractionation(double V_old, double V_new, double di_p, double di_old, double &di_new, double &di_evap, double storageType, int r, int c, int iso);
  int fractionation_origin(double V_old, double V_new, double di_p, double di_old, double &di_new, double &di_evap, double storageType, int r, int c, int iso);
  

  public:
  Basin(Control &ctrl);
  int updateClimateStatus(Control &ctrl);


  //dtor
  ~Basin();

  int init();
  int Canopy();
  int SoilProfile();
  int report(Control &ctrl);
  int updateOutput_all(Control &ctrl);
  int writeAlltoBin(Control &ctrl);

  // for isotope tracking
  int tracking(Control &ctrl);


  

};

#endif /* BASIN_H_ */
