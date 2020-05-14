/**
 This macro will read raw output from combine containing limits on ALPs cross sections and plot those limits.
 Then, it will call "findCoupling" app to find couplings corresponding to those cross sections using STARlight and save them in an output file. From this output file, limits in coupling-mass plane can be plotted using a separate macro.
 
 One should set below the input and output paths, as well desired precision of the cross section when looking for the coupling. Limits in the lambda parameter (1/coupling) can also be modified in case the default range is no longer valid (although this may cause issues with STARlight compilation if number become too large).
 */
#include <fstream>
#include <iostream>
#include <string>

string suffix = "";
vector<int> alpMasses = { 5, 6, 9, 11, 14, 16, 22, 30, 90 };

string inputPath        = "combineOutput"+suffix+".txt";
string couplingOutPath  = "results/couplingMassLimits"+suffix+".txt";
string xsecOutPath      = "results/xsecMassLimits"+suffix+".txt";

double rScale = 10;         // scale by X nb that was used as a reference cross section when generating limits
double xsecPrecision = 0.05; // (nb) precision on the cross section for ALP coupling search
double minLambda = 1000;    // (GeV) min lambda scale
double maxLambda = 100000;  // (GeV) max lambda scale

double findValue(string text, string searchString = "Expected 50.0%: r <")
{
  istringstream iss(text);

  for (string line; std::getline(iss, line); ){
  
    auto found = line.find(searchString);
    if (found != string::npos){
      string number = line.substr(found + searchString.length());
      return stod(number);
    }
  }
  return 0.0;
}

vector<string> tokenize(istream &str, string &line, char token)
{
  vector<string> result;
  getline(str,line);
  stringstream lineStream(line);
  string cell;
  while(getline(lineStream,cell,token)){result.push_back(cell);}
  return result;
}

double getCoupling(double mass, double xsec)
{
  string command = "cd combineToLimits;./findCoupling ";
  command += (to_string(xsecPrecision) + " ");
  command += (to_string(minLambda) + " ");
  command += (to_string(maxLambda) + " ");
  command += (to_string(mass) + " ");
  command += to_string(xsec);
  
  string outPath = "starlight_coupling.txt";
  
  system((command+" > "+outPath).c_str());
  
  ifstream inFile("combineToLimits/"+outPath);
  vector<string> line;
  string fullLine;
  
  double coupling, foundCrossSection;
  
  while (inFile.good()){
    line = tokenize(inFile, fullLine, ' ');
  
    if(line.size() < 1) continue;
    
    if(line[0]=="Lambda:"){
      coupling = stod(line[3]);
      foundCrossSection = stod(line[5]);
    }
  }
  
  cout<<"Desired cross section: "<<xsec<<" +/- "<<xsecPrecision<<" nb"<<endl;
  cout<<"Found cross section: "<<foundCrossSection<<" nb at coupling: "<<coupling<<" GeV"<<endl;
  
  return coupling;
}

void getLimits()
{
  ifstream inFile(inputPath);
  string line;
  
  vector<tuple<double, double, double>> massRcoupling;
  
  double mass, r, coupling;
  
  while(getline(inFile, line)){
    if(line.find("processing mass:") != string::npos){
      mass = findValue(line, "processing mass:");
      if(suffix=="_old") mass = alpMasses[mass];
    }
    
    if(line.find("Expected 50.0%:") != string::npos){
      r = rScale*findValue(line, "Expected 50.0%: r < ");
      
      cout<<"Searching coupling for mass: "<<mass<<"\txsec: "<<r<<endl;
      coupling = getCoupling(mass, r);
      
      massRcoupling.push_back(make_tuple(mass, r, coupling));
    }
  }
  
  ofstream outFileCoupling(couplingOutPath);
  ofstream outFileXsec(xsecOutPath);
  
  for(auto &[mass, r, coupling] : massRcoupling){
    cout<<"mass: "<<mass<<"\txsec: "<<r<<" nb"<<"\tcoupling: "<<coupling<<endl;
    outFileCoupling<<mass<<"\t"<<coupling<<endl;
    outFileXsec<<mass<<"\t"<<r<<endl;
  }
  outFileCoupling.close();
  outFileXsec.close();
}
