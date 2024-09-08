#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;


struct Control{

  int _rowNum0, _colNum0;
  double _dx0, _nodata0;

  /* Folders */
  string path_BasinFolder; //folder where basin property maps are located
  string path_ClimateFolder; //folder where weather maps series are located
  string path_ResultsFolder; //folder where results will be placed

  /*  Tracking options */
  int tracking_isotope;
  int ifreporteverytimestep;

  /* Time variables */ 
  int Simul_start;
  int Simul_end;
  int Simul_tstep;
  int Clim_input_tstep;
  int Report_interval;

  int current_ts;

  /* Catchment info in maps */
  string fn_DEM; // surface evelation
  string fn_LDD; // flow direction
  string fn_chwidth; //channel width (m)
  string fn_chdepth; //channel depth (m)
  string fn_chlength; //channel length (m)

  string fn_depth1; // soil depth [m]
  string fn_depth2;
  string fn_depth3;
  string fn_poro1;  // soil porosity [m]
  string fn_poro2;
  string fn_poro3;

  /* initial storages */
  string fn_init_I;
  string fn_init_snow;
  string fn_init_theta1;
  string fn_init_theta2;
  string fn_init_theta3;



  /* Climate input */
  string fn_climzones; //base climatic zones map with the grid geometry
  string fn_P; // precipitation in binary
  string fn_Ta; // air temperature
  string fn_Ta_min; // min air temperature
  string fn_Ta_max; // max air temperature
  string fn_RH; // relative humidity
  string fn_PET; // potential evapotranspiration in binary
  string fn_LAI; // leaf area index in binary
  string fn_d2hP; // d2h in precipitation in binary

  /* Parameters in maps */
  string fn_rainMultiplier; // rainfall multiplier, [-]
  string fn_PFthreshold; // preferential flow will be generated above this threshold, in m
  string fn_PFscale2;  // how much infiltration will directly reach layer 2, in decimal
  string fn_PFscale3;  // how much infiltration will directly reach layer 3, in decimal
  string fn_snowThreshold; // temperature threshold for snow accumulation [C]
  string fn_degreeFactorMin;  // Degree factor when there's no precipitation
  string fn_degreeFactorMax;  // The maxima of degree factor
  string fn_degreeFactorIncrease; // Increase of the Degree-day factor per mm of increaseing precipitation [s-1 C-1]
  string fn_weight_Ei; // weight to correct E from interception
  string fn_weight_Es; // weight to correct E from soil layer 1
  string fn_rE;  // extinction factor
  string fn_alpha;     // interception threshold parameter, default set to 4.5 mm (Simunek et al, 2008)  
  string fn_Ic;  // max Infiltration capacity, if exceeding surface runoff Qs generation
  string fn_ks1;   // saturated hydraulic conductivity upper soil horizon
  string fn_ks2;   // saturated hydraulic conductivity lower horizon
  string fn_ks3;   // saturated hydraulic conductivity deepest horizon
  string fn_FC1;   // field capacity in different soil layers [decimal]
  string fn_FC2;
  string fn_FC3;
  string fn_g1;   // nonlinear scaling parameter of upper horizon, if g1 = 1, linear case
  string fn_g2;   // nonlinear scaling parameter of lower horizon, if g2 = 1, linear case
  string fn_g3;   // nonlinear scaling parameter of deeper horizon, if g2 = 1, linear case
  string fn_pI;   // passive interception storage mixing volume 
  string fn_ptheta1;   // passive storage for mixing in different layers [decimal]
  string fn_ptheta2;  
  string fn_ptheta3;
  string fn_Perc3_weight; 
  string fn_k;   // seasonality factor CG model
  string fn_x;   // water vapour mixing ratio CG model

  /* Isotope tracking */
  string fn_d2HI;   //d2H in interception;
  string fn_d2Hsnow;   //d2H in interception;
  string fn_d2HSW1;  //d2H in soil layer 1;
  string fn_d2HSW2;  //d2H in soil layer 2;
  string fn_d2HSW3;  //d2H in soil layer 3;


  /* Report session */
  string fn_Gauge_to_Report;
  int Report_Q;
  int Report_snow;
  int Report_theta1;
  int Report_theta2;
  int Report_theta3;


  int Report_Ei;
  int Report_Es;
  int Report_Tr1;
  int Report_Tr2;
  int Report_Tr3;
  int Report_Th;
  int Report_snowmelt;
  int Report_Qs;
  int Report_infilt;
  int Report_preferential2;
  int Report_preferential3;
  int Report_Perc1;
  int Report_Perc2;
  int Report_Perc3;

  int Report_I;
  int Report_D;
  int Report_Imax;


  int Report_d2hSW1;
  int Report_d2hSW2;
  int Report_d2hSW3;
  

  public:
  //ctor from raster ascii file
  Control();
  //dtor


  int getAsciiHeader(string fname);
  int ReadConfigFile(string confilename = "config.ini");

  template<class T> static T string_as_T( const string& s);
  template<class T> void readInto(T &value, string key, vector<string> lines);
  
};

