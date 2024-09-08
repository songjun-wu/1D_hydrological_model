#include "Control.h"

int Control::ReadConfigFile(string fname){
  ifstream input;
  vector<string> lines;
  string s;
  int aaa;

  // read all text in config file into string-based vector
  input.open(fname.c_str());
  if (!input.good()){
    throw runtime_error(string("file not found: ") + fname.c_str());
  }

  while (!input.eof()){
    input >> s;
    lines.push_back(s);
  }

  /* Folders */
  readInto(path_BasinFolder, "Maps_Folder", lines);
  readInto(path_ClimateFolder, "Clim_Maps_Folder", lines);
  readInto(path_ResultsFolder, "Output_Folder", lines);

  /* Tracking options */
  readInto(tracking_isotope, "Tracking_isotope", lines);
  readInto(ifreporteverytimestep, "ifreporteverytimestep", lines);

  /* Time variables */ 
  readInto(Simul_start, "Simul_start", lines);
  readInto(Simul_end, "Simul_end", lines);
  readInto(Simul_tstep, "Simul_tstep", lines);
  readInto(Clim_input_tstep, "Clim_input_tstep", lines);
  readInto(Report_interval, "Report_interval", lines);

  /* Catchment info in maps */
  readInto(fn_DEM, "DEM", lines);
  readInto(fn_LDD, "Flow_direction", lines);
  readInto(fn_chwidth, "Channel_width", lines);
  readInto(fn_chdepth, "Channel_depth", lines);
  readInto(fn_chlength, "Channel_length", lines);

  readInto(fn_depth1, "depth_soilLayer1", lines);
  readInto(fn_depth2, "depth_soilLayer2", lines);
  readInto(fn_depth3, "depth_soilLayer3", lines);
  readInto(fn_poro1, "porosity_soilLayer1", lines);
  readInto(fn_poro2, "porosity_soilLayer2", lines);
  readInto(fn_poro3, "porosity_soilLayer3", lines);

  /* initial storages */
  readInto(fn_init_I, "initial_I", lines);
  readInto(fn_init_snow, "initial_snow", lines);
  readInto(fn_init_theta1, "initial_theta1", lines);
  readInto(fn_init_theta2, "initial_theta2", lines);
  readInto(fn_init_theta3, "initial_theta3", lines);

  /* Climate input */
  readInto(fn_climzones, "climate_zones", lines);
  readInto(fn_P, "precipitation", lines);
  readInto(fn_Ta, "airTemperature", lines);
  readInto(fn_Ta_min, "airTemperature_min", lines);
  readInto(fn_Ta_max, "airTemperature_max", lines);
  readInto(fn_RH, "relativeHumidity", lines);
  readInto(fn_PET, "PET", lines);
  readInto(fn_LAI, "LAI", lines);
  

  /* Parameters in maps */

  readInto(fn_rainMultiplier, "param_rainMultiplier", lines);

  readInto(fn_PFthreshold, "param_PFthreshold", lines);
  readInto(fn_PFscale2, "param_PFscale2", lines);
  readInto(fn_PFscale3, "param_PFscale3", lines);

  readInto(fn_snowThreshold, "param_snowThreshold", lines);
  readInto(fn_degreeFactorMin, "param_degreeFactorMin", lines);
  readInto(fn_degreeFactorMax, "param_degreeFactorMax", lines);
  readInto(fn_degreeFactorIncrease, "param_degreeFactorIncrease", lines);

  readInto(fn_weight_Ei, "param_weight_Ei", lines);
  readInto(fn_weight_Es, "param_weight_Es", lines);

  readInto(fn_rE, "param_rE", lines);
  readInto(fn_alpha, "param_alpha", lines);
  readInto(fn_Ic, "param_Ic", lines);
  readInto(fn_ks1, "param_ks1", lines);
  readInto(fn_ks2, "param_ks2", lines);
  readInto(fn_ks3, "param_ks3", lines);
  readInto(fn_FC1, "param_FC1", lines);
  readInto(fn_FC2, "param_FC2", lines);
  readInto(fn_FC3, "param_FC3", lines);
  readInto(fn_g1, "param_g1", lines);
  readInto(fn_g2, "param_g2", lines);
  readInto(fn_g3, "param_g3", lines);
  readInto(fn_pI, "param_pI", lines);
  readInto(fn_ptheta1, "param_ptheta1", lines);
  readInto(fn_ptheta2, "param_ptheta2", lines);
  readInto(fn_ptheta3, "param_ptheta3", lines);
  readInto(fn_Perc3_weight, "param_leakage_weight", lines);
  readInto(fn_k, "param_k", lines);
  readInto(fn_x, "param_x", lines);


  /* Report session */
  readInto(fn_Gauge_to_Report, "Gauge_to_Report", lines);
  readInto(Report_Q, "Report_Q", lines);
  readInto(Report_snow, "Report_snow", lines);
  readInto(Report_theta1, "Report_theta1", lines);
  readInto(Report_theta2, "Report_theta2", lines);
  readInto(Report_theta3, "Report_theta3", lines);

  readInto(Report_Ei, "Report_Ei", lines);
  readInto(Report_Es, "Report_Es", lines);
  readInto(Report_Tr1, "Report_Tr1", lines);
  readInto(Report_Tr2, "Report_Tr2", lines);
  readInto(Report_Tr3, "Report_Tr3", lines);
  readInto(Report_Th, "Report_Th", lines);
  readInto(Report_snowmelt, "Report_snowmelt", lines);
  readInto(Report_Qs, "Report_Qs", lines);
  readInto(Report_infilt, "Report_infilt", lines);
  readInto(Report_preferential2, "Report_preferential2", lines);
  readInto(Report_preferential3, "Report_preferential3", lines);
  readInto(Report_Perc1, "Report_Perc1", lines);
  readInto(Report_Perc2, "Report_Perc2", lines);
  readInto(Report_Perc3, "Report_Perc3", lines);

  readInto(Report_I, "Report_I", lines);
  readInto(Report_D, "Report_D", lines);
  readInto(Report_Imax, "Report_Imax", lines);



  if (tracking_isotope==1){
    readInto(Report_d2hSW1, "Report_d2hSW1", lines);
    readInto(Report_d2hSW2, "Report_d2hSW2", lines);
    readInto(Report_d2hSW3, "Report_d2hSW3", lines);
  }

  /* Isotope tracking */
  if (tracking_isotope==1){
    readInto(fn_d2hP, "d2h_precip", lines);
    readInto(fn_d2HI, "d2h_I", lines);
    readInto(fn_d2Hsnow, "d2h_snow", lines);
    readInto(fn_d2HSW1, "d2h_SW1", lines);
    readInto(fn_d2HSW2, "d2h_SW2", lines);
    readInto(fn_d2HSW3, "d2h_SW3", lines);
  }
  return EXIT_SUCCESS;
}



template<class T>
void Control::readInto(T &value, string key, vector<string> lines){
  int position;

  position = find(lines.begin(), lines.end(), key)-lines.begin();

  if (position >= lines.size()){
    throw runtime_error(string("Folder not found: ") + key);
  } else {
    value = string_as_T<T>(lines[position+2]);
  }
}

template<class T>
T Control::string_as_T( const string& s )
{
	// Convert from a string to a T
	// Type T must support >> operator
	T t;
	istringstream ist(s);
	ist >> t;
	return t;
}