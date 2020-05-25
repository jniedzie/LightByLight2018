/**
 This macro will read raw output from combine containing limits on ALPs cross sections and plot those limits.
 Then, it will call "findCoupling" app to find couplings corresponding to those cross sections using STARlight and save them in an output file. From this output file, limits in coupling-mass plane can be plotted using a separate macro.
 
 One should set below the input and output paths, as well desired precision of the cross section when looking for the coupling. Limits in the lambda parameter (1/coupling) can also be modified in case the default range is no longer valid (although this may cause issues with STARlight compilation if number become too large).
 */
#include <fstream>
#include <iostream>
#include <string>

bool findCoupling = false;

string suffix = "";
vector<int> alpMasses = { 5, 6, 9, 11, 14, 16, 22, 30, 90 };

string inputPath        = "combineOutput"+suffix+".txt";
string couplingOutPath  = "results/couplingMassLimits"+suffix+".txt";
string xsecOutPath      = "results/xsecMassLimits"+suffix+".txt";

double rScale = 10;         // scale by X nb that was used as a reference cross section when generating limits
double xsecPrecision = 0.01; // relative precision on the cross section for ALP coupling search
double minLambda = 1000;    // (GeV) min lambda scale
double maxLambda = 1000000;  // (GeV) max lambda scale

double findValue(string text, string searchString = "Expected 50.0%: r <")
{
  if(text.find(searchString) == string::npos) return -1;
  
  istringstream iss(text);

  for (string line; std::getline(iss, line); ){
  
    auto found = line.find(searchString);
    if (found != string::npos){
      string number = line.substr(found + searchString.length());
      return stod(number);
    }
  }
  return -1;
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
  command += (to_string(xsecPrecision*xsec) + " ");
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
  
  cout<<"Desired cross section: "<<xsec<<" +/- "<<xsecPrecision*xsec<<" nb"<<endl;
  cout<<"Found cross section: "<<foundCrossSection<<" nb at coupling: "<<coupling<<" GeV"<<endl;
  
  return coupling;
}

void getLimits()
{
  ifstream inFile(inputPath);
  string line;
  
  vector<tuple<double, double, double, double, double, double, double, double>> massRcoupling;
  
  double mass, couplingExpected;
  double rObserved, r2p5, r16, r50, r84, r97p5;
  bool first = true;
  double value = -1;
  
  while(getline(inFile, line)){
    if(line.find("processing mass:") != string::npos){
      mass = findValue(line, "processing mass:");
      if(suffix=="_old") mass = alpMasses[mass];
    
      if(first){
        first = false;
        continue;
      }
      
      // fill in values for previous mass
      if(findCoupling){
        cout<<"Searching coupling for mass: "<<mass<<"\txsec: "<<r50<<endl;
        couplingExpected = getCoupling(mass, r50);
      }
      massRcoupling.push_back(make_tuple(mass, rObserved, r2p5, r16, r50, r84, r97p5, couplingExpected));
    }
    
    value = findValue(line, "Observed Limit: r < "); if(value >= 0) rObserved = rScale * value;
    value = findValue(line, "Expected  2.5%: r < "); if(value >= 0) r2p5      = rScale * value;
    value = findValue(line, "Expected 16.0%: r < "); if(value >= 0) r16       = rScale * value;
    value = findValue(line, "Expected 50.0%: r < "); if(value >= 0) r50       = rScale * value;
    value = findValue(line, "Expected 84.0%: r < "); if(value >= 0) r84       = rScale * value;
    value = findValue(line, "Expected 97.5%: r < "); if(value >= 0) r97p5     = rScale * value;
  }
  
  // fill in values for the last mass point
  if(findCoupling){
    cout<<"Searching coupling for mass: "<<mass<<"\txsec: "<<r50<<endl;
    couplingExpected = getCoupling(mass, r50);
  }
  massRcoupling.push_back(make_tuple(mass, rObserved, r2p5, r16, r50, r84, r97p5, couplingExpected));
  
  
  // save results to files
  ofstream outFileXsec(xsecOutPath);
  
  for(auto &[mass, rObserved, r2p5, r16, r50, r84, r97p5, couplingExpected] : massRcoupling){
    cout<<"mass: "<<mass<<"\txsec expected 50%: "<<r50<<" nb"<<endl;
    outFileXsec<<mass<<"\t"<<"\t"<<rObserved<<"\t"<<r2p5<<"\t"<<r16<<"\t"<<r50<<"\t"<<r84<<"\t"<<r97p5<<endl;
  }
  outFileXsec.close();
  
  if(findCoupling){
    ofstream outFileCoupling(couplingOutPath);
    
    for(auto &[mass, rObserved, r2p5, r16, r50, r84, r97p5, couplingExpected] : massRcoupling){
      cout<<"mass: "<<"\texpected coupling: "<<couplingExpected<<endl;
      outFileCoupling<<mass<<"\t"<<couplingExpected<<endl;
    }
    outFileCoupling.close();
  }
}
