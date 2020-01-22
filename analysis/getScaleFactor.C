
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
//double effMCerr = 0.077;

// Charged exclusivity
double effData = ;
double effDataErr = ;
double effMC = 1.000;
double effMCerr = 0.224;

// Neutral exclusivity
//double effData = ;
//double effDataErr = ;
//double effMC = 0.850;
//double effMCerr = 0.198;

void getScaleFactor()
{
  double scaleFactor = effMC/effData;
  double scaleFactorErr = 1/effData * sqrt(effMCerr*effMCerr + effMC*effMC*effDataErr*effDataErr/(effData*effData));
  
  cout<<"Scale factor: "<<scaleFactor<<" +/- "<<scaleFactorErr<<endl;
}
