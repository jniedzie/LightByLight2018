
// Reco+ID
//double effData = 0.633;
//double effDataErr = 0.029;
//double effMC = 0.714;
//double effMCerr = 0.041;

// Trigger
//double effData = 0.95;
//double effDataErr = 0.01;
//double effMC = 0.91;
//double effMCerr = 0.02;

// HF veto
//double effData = 1.0;
//double effDataErr = 0.243;
//double effMC = 1.0;
//double effMCerr = 0.047;

// Charged exclusivity
//double effData = 1.000;
//double effDataErr = 0.059;
//double effMC = 1.000;
//double effMCerr = 0.117;

// Neutral exclusivity
double effData = 0.634;
double effDataErr = 0.043;
double effMC = 0.823;
double effMCerr = 0.101;

void getScaleFactor()
{
  double scaleFactor = effMC/effData;
  double scaleFactorErr = 1/effData * sqrt(effMCerr*effMCerr + effMC*effMC*effDataErr*effDataErr/(effData*effData));
  
  cout<<"Scale factor: "<<scaleFactor<<" +/- "<<scaleFactorErr<<endl;
}
