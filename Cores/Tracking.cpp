#include"Basin.h"

int Basin::tracking(Control &ctrl){

  int r, c;

  for (unsigned int j = 0; j < _sortedGrid.row.size(); j++) {

    r = _sortedGrid.row[j];
	  c = _sortedGrid.col[j];

    mixing_snow(r, c, ctrl.tracking_isotope);
    mixing_canopy(r, c, ctrl.tracking_isotope);
    mixing_soil(r, c,  ctrl.tracking_isotope);
    
  }

  return EXIT_SUCCESS;
}




int Basin::mixing_canopy(int r, int c, int isotrackflag){

  // mixing canopy storage
  double V_old; // storage before evaporation
  double V_new; 
  double di_I_old=0;
  double di_canopy=0;
 
  // mixing the canopy storage with precipitation
  inoutMix(_I_old->matrix[r][c], _d2hI->matrix[r][c], (_P->matrix[r][c]-_Th->matrix[r][c]), _d2hP->matrix[r][c], 0, _value0->matrix[r][c], _pI->matrix[r][c], _d2hI->matrix[r][c], 0, r, c);
  _d2hTh->matrix[r][c] = _d2hP->matrix[r][c];

  /*
  // fractionation in canopy
  if (isotrackflag==1 or isotrackflag==2){
    V_old = _I->matrix[r][c] + _Ei->matrix[r][c]; 
    V_new = _I->matrix[r][c];
    
    if ((V_new/V_old) < 0.999 and V_new > RNDOFFERR){
      fractionation(V_old, V_new, _d2hP->matrix[r][c], _d2hI->matrix[r][c], _d2hI->matrix[r][c], _d2hEi->matrix[r][c], 0, r, c, isotrackflag);
    }
  }
  */
  return EXIT_SUCCESS;
}

int Basin::mixing_snow(int r, int c, int isotrackflag){

  double snow_in = _Th->matrix[r][c] * _SRfrac;
  double rain_in = _Th->matrix[r][c] * (1 - _SRfrac);
  
  if (_snow_old->matrix[r][c] < RNDOFFERR){
    _d2hSnow->matrix[r][c] = _d2hTh->matrix[r][c];
    _d2hSnowmelt->matrix[r][c] = _d2hTh->matrix[r][c];
  } else if (_snow_old->matrix[r][c] < _snow->matrix[r][c]){  // if snow accumalates more
    // Snowpack: last (same timestep) in, first melt
    inoutMix(_snow_old->matrix[r][c], _d2hSnow->matrix[r][c], snow_in - _snowmelt->matrix[r][c], _d2hTh->matrix[r][c], 0, _value0->matrix[r][c], 0, _d2hSnow->matrix[r][c], 0, r, c);
    _d2hSnowmelt->matrix[r][c] = _d2hTh->matrix[r][c];
  } else { // if snow melts more
    // Snowpack: no change (all recent snow has melted)
    // Snowmelt: mix of snowpack and throughfall
    inoutMix(_snowmelt->matrix[r][c]- snow_in, _d2hSnow->matrix[r][c], snow_in, _d2hTh->matrix[r][c], 0, _value0->matrix[r][c], 0, _d2hSnowmelt->matrix[r][c], 0, r, c);
  }

  //mixing throughfall
  inoutMix(rain_in, _d2hTh->matrix[r][c], _snowmelt->matrix[r][c], _d2hSnowmelt->matrix[r][c], 0, _value0->matrix[r][c], 0, _d2hInfilt->matrix[r][c], 0, r, c);

  return EXIT_SUCCESS;
}

int Basin::mixing_soil(int r, int c, int isotrackflag){

  double d1 = _depth1->matrix[r][c];
  double d2 = _depth2->matrix[r][c];
  double d3 = _depth3->matrix[r][c];

  /*  soil layer 1*/
  // fractionation due to soil evaporation
  if (isotrackflag==1 or isotrackflag==2){
    
    inoutMix(_theta1_old->matrix[r][c] * d1, _d2hSW1->matrix[r][c], _infilt->matrix[r][c], _d2hInfilt->matrix[r][c], _Perc1->matrix[r][c], _d2hPerc1->matrix[r][c], _ptheta1->matrix[r][c]*_depth1->matrix[r][c], _d2hSW1->matrix[r][c], 0, r, c);
  
    if (_preferential2->matrix[r][c] > 0){
      inoutMix(_theta2_old->matrix[r][c] * d2, _d2hSW2->matrix[r][c], _preferential2->matrix[r][c], _d2hInfilt->matrix[r][c], 0, _value0->matrix[r][c], 0, _d2hSW2->matrix[r][c], 0, r, c);
    }
    inoutMix((_theta2_old->matrix[r][c]) * d2 + _preferential2->matrix[r][c], _d2hSW2->matrix[r][c], _Perc1->matrix[r][c], _d2hPerc1->matrix[r][c], _Perc2->matrix[r][c], _d2hPerc2->matrix[r][c], _ptheta2->matrix[r][c]*_depth2->matrix[r][c], _d2hSW2->matrix[r][c], 0, r, c);

    if (_preferential3->matrix[r][c] > 0){
      inoutMix(_theta3_old->matrix[r][c] * d3, _d2hSW3->matrix[r][c], _preferential3->matrix[r][c], _d2hInfilt->matrix[r][c], 0, _value0->matrix[r][c], 0, _d2hSW3->matrix[r][c], 0, r, c);
    }
    inoutMix((_theta3_old->matrix[r][c] ) * d3 + _preferential3->matrix[r][c], _d2hSW3->matrix[r][c], _Perc2->matrix[r][c], _d2hPerc2->matrix[r][c], _Perc3->matrix[r][c], _d2hPerc3->matrix[r][c], _ptheta3->matrix[r][c]*_depth3->matrix[r][c], _d2hSW3->matrix[r][c], 0, r, c);
  }

    double V_new = _theta1->matrix[r][c] * d1;
    double V_old = V_new + _Es->matrix[r][c];
    fractionation(V_old, V_new, _d2hP->matrix[r][c], _d2hSW1->matrix[r][c],  _d2hSW1->matrix[r][c], _d2hEs->matrix[r][c], 1, r, c, isotrackflag);

  return EXIT_SUCCESS;
}


int Basin::fractionation(double V_old, double V_new, double di_p, double di_old, double &di_new, double &di_evap, double issoil, int r, int c, int iso){                       


  double Ta = _Ta->matrix[r][c];
  double rh = _RH->matrix[r][c];
  double alpha_p;  // equilibrium isotope fractionation factor (fraction)
  double eps_p; 			// equilibrium isotope fractionation factor (per mil)
  double eps_k = 0; 		// kinetic isotope fractionation factor (per mil)
  double eps; 			// total isotope fractionation factor (per mil)
  double di_atm = 0; 		// Atmospheric isotopic signatures (permil)
  double di_s; 			// Limiting isotopic composition (per mil)
  double m;  // Calculation factor (-)
  double n;	 // Parameter translating dominant water transport mode (-)

  double f; 			// Water loss fraction after evaporation (fraction)
  

  double ha_p = (issoil == 1) ? rh * 1 : (rh + 1)/2;  // corrected air humidity (at surface or above water). StorageType 0: canopy; 1: soil; 2: channel
  double hs = 1; //soil humitidy = 1
  //double beta = Calculate_beta(V_old, _FC1->matrix[r][c]);
  //double hs = beta + (1-beta)*ha_p;

  // ****  Horita and Wesolowski (1994) **** 
  if(iso == 1) // deuterium
    alpha_p = expl((1158.8*powl(Ta,3)*1e-9 - 1620.1*powl(Ta,2)*1e-6 + 794.84*Ta*1e-3 - \
		    161.04 + 2.9992*1e9/powl(Ta,3))/1000);
  else if (iso == 2) // oxygen 18
    alpha_p = expl((-7.685 + 6.7123*1000/Ta - 1.6664*1e6/powl(Ta,2) +
		    0.35041*1e9/powl(Ta,3))/1000);

  

  // **** Equilibrium enrichment (Skrzypek et al., 2015) ****
  eps_p = (alpha_p - 1) *1000;


  di_atm = (di_p - eps_p)/ alpha_p;  


  // **** Water transport mode: from diffusive (=1, dry soil) to turbulent (=0.5, water body) 
  n = issoil==1 ? 0.9755 : 0.5; // n=0.9755 value from Merlivat (1978) #permil notation


  // **** Kinetic fractionation factor epsilon_k ****
  double DiD = (iso==1) ? 0.9757 : 0.9727;
  eps_k = (hs-ha_p)*(1-DiD)*1000*n;


  // **** Generalized following Good et al. (2014) ****
  eps = hs * eps_p + eps_k;
  di_s = (ha_p*di_atm + eps) / (ha_p - eps/1000);
  m = (hs - ha_p + eps_k/1000) < RNDOFFERR ? 0 : (ha_p - eps/1000) / (hs - ha_p + eps_k/1000);


  //************* Isotopic Mixing *************
  double evap = (V_old - V_new);
  double Vavg = (V_old + V_new)/2;
  double Vdiff = (V_new - V_old);
  double corr = 0;   // Correction factor (mass-balance closure)

  

  if (V_old>0) {
    f = V_new/V_old;	// Evaporative loss fraction
    di_new = di_s - (di_s - di_old) * (powl(f,m) > 1 ? 1 : powl(f,m));  // New isotopic composition
  
    /*
    cout<<issoil<<" ";
    cout<< di_old <<"      ";
    cout<< hs <<" ";
    cout<< ha_p <<" ";
    cout<< di_atm <<" ";
    cout<< eps_p <<" ";
    cout<< eps_k <<" ";
    cout<< di_s <<"      ";
    cout<< f <<" ";
    cout<< m <<" ";
    cout<<(powl(f,m) > 1 ? 1 : powl(f,m))<<" ";
    cout<< di_new <<endl;
    */
    

    // Isotopic signature of evaporated water
    di_evap = (1 - ha_p + eps_k/1000) < RNDOFFERR ? di_new : (di_new - ha_p*di_atm - eps)/ (1 - ha_p + eps_k/1000);

    
    /*
    if(abs(di_evap - di_new) > RNDOFFERR){
      corr = -((Vdiff*di_old/2 - Vavg*di_old - evap*(ha_p*di_atm+eps)/(1-ha_p+eps_k/1000)) + 
	      di_new*(Vavg +Vdiff/2 + evap/(1-ha_p+eps_k/1000)))/
     	      (Vavg + Vdiff/2 + evap/(1-ha_p+eps_k/1000));
      di_new = di_new + corr;
      di_evap = (1 - ha_p + eps_k/1000) < RNDOFFERR ? di_new :(di_new - ha_p*di_atm - eps)/ (1 - ha_p + eps_k/1000);

      if(di_evap > di_new){      // Check here if di_evap > di_new (not possible)
	      di_new = di_old;
	      di_evap = di_old;
      }
    }
    */
    di_new = std::max<double>(-1000, di_new);
    di_evap = std::max<double>(-1000, di_evap);
  
  }

  
  return EXIT_SUCCESS;
}


int Basin::fractionation_origin(double V_old, double V_new, double di_p, double di_old, double &di_new, double &di_evap, double issoil, int r, int c, int iso){                       

  double Ta = _Ta->matrix[r][c];
  double rh = _RH->matrix[r][c];
  double alpha_p;  // equilibrium isotope fractionation factor (fraction)
  double eps_p; 			// equilibrium isotope fractionation factor (per mil)
  double eps_k = 0; 		// kinetic isotope fractionation factor (per mil)
  double eps; 			// total isotope fractionation factor (per mil)
  double di_atm = 0; 		// Atmospheric isotopic signatures (permil)
  double di_s; 			// Limiting isotopic composition (per mil)
  double m;  // Calculation factor (-)
  double n;	 // Parameter translating dominant water transport mode (-)

  double f; 			// Water loss fraction after evaporation (fraction)
  

  double ha_p = (issoil == 1) ? rh * 1 : (rh + 1)/2;  // corrected air humidity (at surface or above water). StorageType 0: canopy; 1: soil; 2: channel
  double hs = 1; //soil humitidy = 1

  // ****  Horita and Wesolowski (1994) **** 
  if(iso == 1) // deuterium
    alpha_p = expl((1158.8*powl(Ta,3)*1e-9 - 1620.1*powl(Ta,2)*1e-6 + 794.84*Ta*1e-3 - \
		    161.04 + 2.9992*1e9/powl(Ta,3))/1000);
  else if (iso == 2) // oxygen 18
    alpha_p = expl((-7.685 + 6.7123*1000/Ta - 1.6664*1e6/powl(Ta,2) +
		    0.35041*1e9/powl(Ta,3))/1000);

  

  // **** Equilibrium enrichment (Skrzypek et al., 2015) ****
  eps_p = (alpha_p - 1) *1000;

  di_atm = (di_p - eps_p)/ alpha_p;
  //double k = 0.9;   //todo
  //di_atm = (-58.7 - k*eps_p) / (1 + k*eps_p/1000); //todo
  

  // **** Water transport mode: from diffusive (=1, dry soil) to turbulent (=0.5, water body) 
  n = issoil==1 ? 0.9755 : 0.5; // n=0.9755 value from Merlivat (1978) #permil notation


  // **** Kinetic fractionation factor epsilon_k ****
  double DiD = (iso==1) ? 0.9757 : 0.9727;
  eps_k = (hs-ha_p)*(1-DiD)*1000*n;


  // **** Generalized following Good et al. (2014) ****
  eps = hs * eps_p + eps_k;
  di_s = (ha_p*di_atm + eps) / (ha_p - eps/1000); 
  m = (hs - ha_p + eps_k/1000) < RNDOFFERR ? 0 : (ha_p - eps/1000) / (hs - ha_p + eps_k/1000);
  //m = (ha_p - (eps_p/alpha_p + eps_k)/1000) / (hs - ha_p + eps_k/1000);


  //************* Isotopic Mixing *************
  double evap = (V_old - V_new); 
  double di_liquid; // desiccating water body

  if (V_old>0) {
    f = V_new/V_old;	// Evaporative loss fraction
    di_liquid = di_s - (di_s - di_old) * (powl(f,m) > 1 ? 1 : powl(f,m));  // desiccating water body
    //double x = 0.25;
    //di_new = di_s - (di_s - di_old) * powl((1-x),m);
    di_new = (V_old * di_old - evap * di_liquid) / V_old;

    // Isotopic signature of evaporated water, from Gibson 2016 
    di_evap = (1 - ha_p + eps_k/1000) < RNDOFFERR ? di_new : ((di_liquid - eps_p)/alpha_p - ha_p*di_atm - eps_k)/ (1 - ha_p + eps_k/1000);

    di_new = std::max<double>(-1000, di_new);
    di_evap = std::max<double>(-1000, di_evap);
  
  }
  
  return EXIT_SUCCESS;
}


