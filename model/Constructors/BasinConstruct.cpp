#include "Basin.h"

Basin::Basin(Control &ctrl){
  _rowNum = ctrl._rowNum0;
  _colNum = ctrl._colNum0;
  _dx = ctrl._dx0;
  _nodata = ctrl._nodata0;

  /* Catchment info in maps */
  _DEM = new grid(ctrl.path_BasinFolder + ctrl.fn_DEM, _rowNum, _colNum);
  _LDD = new grid(ctrl.path_BasinFolder + ctrl.fn_LDD, _rowNum, _colNum);
  _chwidth = new grid(ctrl.path_BasinFolder + ctrl.fn_chwidth, _rowNum, _colNum);
  _chdepth = new grid(ctrl.path_BasinFolder + ctrl.fn_chdepth, _rowNum, _colNum);
  _chlength = new grid(ctrl.path_BasinFolder + ctrl.fn_chlength, _rowNum, _colNum);
  _Gauge_to_Report = new grid(ctrl.path_BasinFolder + ctrl.fn_Gauge_to_Report, _rowNum, _colNum);

  _depth1 = new grid(ctrl.path_BasinFolder + ctrl.fn_depth1, _rowNum, _colNum);
  _depth2 = new grid(ctrl.path_BasinFolder + ctrl.fn_depth2, _rowNum, _colNum);
  _depth3 = new grid(ctrl.path_BasinFolder + ctrl.fn_depth3, _rowNum, _colNum);

  _poro1 = new grid(ctrl.path_BasinFolder + ctrl.fn_poro1, _rowNum, _colNum);
  _poro2 = new grid(ctrl.path_BasinFolder + ctrl.fn_poro2, _rowNum, _colNum);
  _poro3 = new grid(ctrl.path_BasinFolder + ctrl.fn_poro3, _rowNum, _colNum);


  /* Climate */
  _climzones = new grid(ctrl.path_BasinFolder + ctrl.fn_climzones, _rowNum, _colNum);
  _P = new grid(_rowNum, _colNum);
  _Ta = new grid(_rowNum, _colNum);
  _Ta_min = new grid(_rowNum, _colNum);
  _Ta_max = new grid(_rowNum, _colNum);
  _RH = new grid(_rowNum, _colNum);
  _PET = new grid(_rowNum, _colNum);
  _LAI = new grid(_rowNum, _colNum);



  /* Parameters */
  _rainMultiplier = new grid(ctrl.path_BasinFolder + ctrl.fn_rainMultiplier, _rowNum, _colNum);

  _PFthreshold = new grid(ctrl.path_BasinFolder + ctrl.fn_PFthreshold, _rowNum, _colNum);
  _PFscale2 = new grid(ctrl.path_BasinFolder + ctrl.fn_PFscale2, _rowNum, _colNum);
  _PFscale3 = new grid(ctrl.path_BasinFolder + ctrl.fn_PFscale3, _rowNum, _colNum);

  _snowThreshold = new grid(ctrl.path_BasinFolder + ctrl.fn_snowThreshold, _rowNum, _colNum);
  _degreeFactorMin = new grid(ctrl.path_BasinFolder + ctrl.fn_degreeFactorMin, _rowNum, _colNum);
  _degreeFactorMax = new grid(ctrl.path_BasinFolder + ctrl.fn_degreeFactorMax, _rowNum, _colNum);
  _degreeFactorIncrease = new grid(ctrl.path_BasinFolder + ctrl.fn_degreeFactorIncrease, _rowNum, _colNum);
  _weight_Ei = new grid(ctrl.path_BasinFolder + ctrl.fn_weight_Ei, _rowNum, _colNum);
  _weight_Es = new grid(ctrl.path_BasinFolder + ctrl.fn_weight_Es, _rowNum, _colNum);

  _rE = new grid(ctrl.path_BasinFolder + ctrl.fn_rE, _rowNum, _colNum);
  _alpha = new grid(ctrl.path_BasinFolder + ctrl.fn_alpha, _rowNum, _colNum);
  _Ic = new grid(ctrl.path_BasinFolder + ctrl.fn_Ic, _rowNum, _colNum);
  _ks1 = new grid(ctrl.path_BasinFolder + ctrl.fn_ks1, _rowNum, _colNum);
  _ks2 = new grid(ctrl.path_BasinFolder + ctrl.fn_ks2, _rowNum, _colNum);
  _ks3 = new grid(ctrl.path_BasinFolder + ctrl.fn_ks3, _rowNum, _colNum);
  _FC1 = new grid(ctrl.path_BasinFolder + ctrl.fn_FC1, _rowNum, _colNum);
  _FC2 = new grid(ctrl.path_BasinFolder + ctrl.fn_FC2, _rowNum, _colNum);
  _FC3 = new grid(ctrl.path_BasinFolder + ctrl.fn_FC3, _rowNum, _colNum);
  _g1 = new grid(ctrl.path_BasinFolder + ctrl.fn_g1, _rowNum, _colNum);
  _g2 = new grid(ctrl.path_BasinFolder + ctrl.fn_g2, _rowNum, _colNum);
  _g3 = new grid(ctrl.path_BasinFolder + ctrl.fn_g3, _rowNum, _colNum);
  _pI = new grid(ctrl.path_BasinFolder + ctrl.fn_pI, _rowNum, _colNum);
  _ptheta1 = new grid(ctrl.path_BasinFolder + ctrl.fn_ptheta1, _rowNum, _colNum);
  _ptheta2 = new grid(ctrl.path_BasinFolder + ctrl.fn_ptheta2, _rowNum, _colNum);
  _ptheta3 = new grid(ctrl.path_BasinFolder + ctrl.fn_ptheta3, _rowNum, _colNum);
  _Perc3_weight = new grid(ctrl.path_BasinFolder + ctrl.fn_Perc3_weight, _rowNum, _colNum);
  _k = new grid(ctrl.path_BasinFolder + ctrl.fn_k, _rowNum, _colNum);
  _x = new grid(ctrl.path_BasinFolder + ctrl.fn_x, _rowNum, _colNum);


  /* state variables used in simualtion */
  _I = new grid(ctrl.path_BasinFolder + ctrl.fn_init_I, _rowNum, _colNum);
  _snow = new grid(ctrl.path_BasinFolder + ctrl.fn_init_snow, _rowNum, _colNum);
  _theta1 = new grid(ctrl.path_BasinFolder + ctrl.fn_init_theta1, _rowNum, _colNum);
  _theta2 = new grid(ctrl.path_BasinFolder + ctrl.fn_init_theta2, _rowNum, _colNum);
  _theta3 = new grid(ctrl.path_BasinFolder + ctrl.fn_init_theta3, _rowNum, _colNum);

  _I_old = new grid(_rowNum, _colNum);
  _Imax_old = new grid(_rowNum, _colNum);
  _snow_old = new grid(_rowNum, _colNum);
  _theta1_old = new grid(_rowNum, _colNum);
  _theta2_old = new grid(_rowNum, _colNum);
  _theta3_old = new grid(_rowNum, _colNum);

  _Ep = new grid(_rowNum, _colNum);
  _Ei = new grid(_rowNum, _colNum);
  _Es = new grid(_rowNum, _colNum);
  _Tp = new grid(_rowNum, _colNum);
  _Tr = new grid(_rowNum, _colNum);
  _Tr1 = new grid(_rowNum, _colNum); 
  _Tr2 = new grid(_rowNum, _colNum); 
  _Tr3 = new grid(_rowNum, _colNum); 
  _D = new grid(_rowNum, _colNum); 
  _Th = new grid(_rowNum, _colNum);
  _snowmelt = new grid(_rowNum, _colNum); 
  _Qs = new grid(_rowNum, _colNum); 
  _infilt = new grid(_rowNum, _colNum);
  _preferential2 = new grid(_rowNum, _colNum);
  _preferential3 = new grid(_rowNum, _colNum);
  _Perc1 = new grid(_rowNum, _colNum);
  _Perc2 = new grid(_rowNum, _colNum); 
  _Perc3 = new grid(_rowNum, _colNum); 
  _SCF = new grid(_rowNum, _colNum); 

  _value0 = new grid(_rowNum, _colNum);
  _Imax = new grid(_rowNum, _colNum);

  _sortedGrid = SortGridLDD();
  _Tsmask = sortTSmask();
  
  /* Isotope tracking */
  if (ctrl.tracking_isotope==1){

    _d2hP = new grid(_rowNum, _colNum);

    _d2hI = new grid(ctrl.path_BasinFolder + ctrl.fn_d2HI, _rowNum, _colNum);
    _d2hSnow = new grid(_rowNum, _colNum);
    _d2hSW1 = new grid(ctrl.path_BasinFolder + ctrl.fn_d2HSW1, _rowNum, _colNum);
    _d2hSW2 = new grid(ctrl.path_BasinFolder + ctrl.fn_d2HSW2, _rowNum, _colNum);
    _d2hSW3 = new grid(ctrl.path_BasinFolder + ctrl.fn_d2HSW3, _rowNum, _colNum);
    _d2hEi = new grid(_rowNum, _colNum); 
    _d2hEs = new grid(_rowNum, _colNum);

    _d2hTh = new grid(_rowNum, _colNum);
    _d2hSnowmelt = new grid(_rowNum, _colNum);
    _d2hInfilt = new grid(_rowNum, _colNum);
    _d2hPerc1 = new grid(_rowNum, _colNum); 
    _d2hPerc2 = new grid(_rowNum, _colNum);
    _d2hPerc3 = new grid(_rowNum, _colNum);

  }

    if (ctrl.ifreporteverytimestep == 0) {
    int ntimestep = ctrl.Simul_end / ctrl.Simul_tstep;
    int nTSmask = _Tsmask.row.size();
    int sampleSize = ntimestep * nTSmask;

    if (ctrl.Report_snow==1) _snow_all = new double[sampleSize];
    if (ctrl.Report_theta1==1) _theta1_all = new double[sampleSize];
    if (ctrl.Report_theta2==1) _theta2_all = new double[sampleSize];
    if (ctrl.Report_theta3==1) _theta3_all = new double[sampleSize];
    if (ctrl.Report_Ei==1) _Ei_all = new double[sampleSize];
    if (ctrl.Report_Es==1)  _Es_all = new double[sampleSize];
    if (ctrl.Report_Tr1==1) _Tr1_all = new double[sampleSize];
    if (ctrl.Report_Tr2==1) _Tr2_all = new double[sampleSize];
    if (ctrl.Report_Tr3==1) _Tr3_all = new double[sampleSize];

    if (ctrl.Report_Th==1) _Th_all = new double[sampleSize];
    if (ctrl.Report_snowmelt==1) _snowmelt_all = new double[sampleSize];
    if (ctrl.Report_Qs==1) _Qs_all = new double[sampleSize];
    if (ctrl.Report_infilt==1) _infilt_all = new double[sampleSize];
    if (ctrl.Report_preferential2==1) __preferential2_all = new double[sampleSize];
    if (ctrl.Report_preferential3==1) __preferential3_all = new double[sampleSize];
    if (ctrl.Report_Perc1==1) _Perc1_all = new double[sampleSize];
    if (ctrl.Report_Perc2==1) _Perc2_all = new double[sampleSize];
    if (ctrl.Report_Perc3==1) _Perc3_all = new double[sampleSize];
    if (ctrl.Report_I==1) _I_all = new double[sampleSize];
    if (ctrl.Report_D==1) _D_all = new double[sampleSize];
    
    if (ctrl.tracking_isotope==1){
      if (ctrl.Report_d2hSW1==1) _d2hSW1_all = new double[sampleSize];
      if (ctrl.Report_d2hSW2==1) _d2hSW2_all = new double[sampleSize];
      if (ctrl.Report_d2hSW3==1) _d2hSW3_all = new double[sampleSize];
  }
    }

  /* Initialse climate maps */
  initialiseClimateMaps(ctrl.path_ClimateFolder + ctrl.fn_P, if_P);
  initialiseClimateMaps(ctrl.path_ClimateFolder + ctrl.fn_Ta, if_Ta);
  initialiseClimateMaps(ctrl.path_ClimateFolder + ctrl.fn_Ta_min, if_Ta_min);
  initialiseClimateMaps(ctrl.path_ClimateFolder + ctrl.fn_Ta_max, if_Ta_max);
  initialiseClimateMaps(ctrl.path_ClimateFolder + ctrl.fn_RH, if_RH);
  initialiseClimateMaps(ctrl.path_ClimateFolder + ctrl.fn_PET, if_PET);
  initialiseClimateMaps(ctrl.path_ClimateFolder + ctrl.fn_LAI, if_LAI);
  if (ctrl.tracking_isotope==1){
    initialiseClimateMaps(ctrl.path_ClimateFolder + ctrl.fn_d2hP, if_d2hP);
  }
  
  updateClimateStatus(ctrl);

}