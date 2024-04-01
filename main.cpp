#include <iostream>
#include "Basin.h"



int main(){
  Control *oControl;
  Basin *oBasin;

  oControl = new Control;
  oBasin = new Basin(*oControl);
  oBasin->init();

  while (oControl->current_ts < oControl->Simul_end){
    oBasin->Canopy();
    oBasin->SoilProfile();

    
    if (oControl->tracking_isotope!=0){
      oBasin->tracking(*oControl);
    }

    
    if (oControl->ifreporteverytimestep == 1){
      oBasin->report(*oControl);
    } else{
      oBasin->updateOutput_all(*oControl);  
    }
    
    oBasin->updateClimateStatus(*oControl);
    oControl->current_ts += oControl->Simul_tstep;
  }

  if (oControl->ifreporteverytimestep == 0){
    
    oBasin->writeAlltoBin(*oControl);
  }

  //delete oControl;
  //delete oBasin;

  return 0;
}