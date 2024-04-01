#include "Basin.h"

double Basin::getSatVaporPressure(const double &T){ // T in C and e in Pa
	return 611 * expl((17.3 * (T-273.15))/(T +0.15 ));
 }




double Basin::Calculate_beta(const double &theta, const double &fieldcap){
	double beta;
	beta = (theta >= fieldcap) ? 1.0 : 0.25*powl( 1 - cos( theta * PI / fieldcap ) , 2 );
	return beta;
}


void Basin::inoutMix(double V_old, double conc_old, double V_in, double conc_in, double V_out, double &conc_out, double V_passive, double &conc_new, int mixmode, int r, int c){
	if (mixmode == 0){
		conc_new = (V_old + V_in > RNDOFFERR) ? ((V_old + V_passive) * conc_old + V_in * conc_in) / (V_old + V_passive + V_in) : conc_old;
		conc_out = conc_new;
	}

	if (mixmode == 1){
		double Vsum = 0.5*(V_old+V_in+std::max<double>(0,V_old-V_out));
		conc_new = 0.5*Vsum+V_in > RNDOFFERR ? 	((conc_old+1000)*(Vsum-0.5*V_in) + (conc_in+1000)*V_in)/ (Vsum + 0.5*V_in) -1000 : conc_old;
		conc_out = conc_new;
	}

	
}

void Basin::notLargerThan(double &Y, double X){
	Y = Y > X ? X : Y;
}