
// Reco+ID
//double effData = 0.633;
//double effDataErr = 0.029;
//double effMC = 0.714;
//double effMCerr = 0.041;

// Trigger updated 11.01.2021
//double effData = 0.889;
//double effDataErr = 0.002;
//double effMC = 0.899;
//double effMCErr = 0.001;

// Reco+ID electron updated 11.01.2021
//double effData = 0.764;
//double effDataErr = 0.003;
//double effMC = 0.777;
//double effMCErr = 0.001;

// HF veto updated 15.01.2021
double effData = 0.944;
double effDataErr = 0.093;
double effMC = 1.0; 
double effMCErr =0.004;

// Charged exclusivity 13.01.2021
//double effData = 0.959;
//double effDataErr = 0.0079;
//double effMC = 0.999;
//double effMCErr = 0.0033;

// Neutral exclusivity 13.01.2021
//double effData = 0.684;
//double effDataErr = 0.006;
//double effMC = 0.809;
//double effMCErr = 0.003;

double getError(double A, double eA, double B, double eB);

void getScaleFactor()
{
  double scaleFactor = effData/effMC;
  double scaleFactorErr = getError(effData, effDataErr, effMC, effMCErr);
 
  cout<<"Scale factor: "<<scaleFactor<<" +/- "<<scaleFactorErr<<endl;
}

//Ratio Error
double getError(double A, double eA, double B, double eB){
  double f=A/B;
  double fA=eA/A;
  double fB=eB/B;
  double eR=  f*sqrt( (fA*fA + fB*fB )) ;
  return eR;
}
