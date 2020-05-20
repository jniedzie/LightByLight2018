#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

string starlightPath = "../../STARlight_ALP/";
string sourceFilePath = "trunk/src/gammagammasingle.cpp";
string resultsPath = "results.txt";

vector<string> tokenize(istream &str, string &line, char token)
{
  vector<string> result;
  getline(str,line);
  stringstream lineStream(line);
  string cell;
  while(getline(lineStream,cell,token)){result.push_back(cell);}
  return result;
}

void setOption(string fileName, string option, int value)
{
  ofstream outFile("tmp.file");
  ifstream readFile(fileName.c_str()); // run_batch.sub
  
  vector<string> line;
  string fullLine;
  
  bool found = false;
  
  while (readFile.good()){
    line = tokenize(readFile,fullLine, ' ');
    
    if(line.size()>1){
      if(line[0].find("#define") != string::npos &&
         line[1].find(option)    != string::npos
         ){
        outFile << "#define " << option << " "<<value<< endl;
        found = true;
      }
      else outFile << fullLine << endl;
    }
    else outFile << fullLine << endl;
  }
  readFile.close();
  system(("mv tmp.file " + fileName).c_str());
  
  if(!found){
    cout<<"WARNING -- option "<<option<<" not found in file "<<fileName<<"!!"<<endl;
  }
}

double getCrossSection(double coupling)
{
  setOption(starlightPath+sourceFilePath, "ax_lambda", coupling);
  system(("cd "+starlightPath+";make -j8 > /dev/null").c_str());
  system((starlightPath+"/starlight > "+resultsPath+" 2>&1").c_str());
  
  ifstream readFile(resultsPath.c_str()); // run_batch.sub
  
  vector<string> line;
  string fullLine;
  
  while (readFile.good()){
    line = tokenize(readFile, fullLine, ' ');
    
    if(line.size()>1){
      if(line[0].find("Total") != string::npos &&
         line[1].find("cross") != string::npos &&
         line[2].find("section:") != string::npos
         ){
        for(string word : line) cout<<word<<"\t";
        cout<<endl;
        
        readFile.close();
        double multiplier = 1;
        if(line[4].find("microbarn")  != string::npos) multiplier = 1e3;
        if(line[4].find("picobarn")   != string::npos) multiplier = 1e-3;
        if(line[4].find("femtobarn")  != string::npos) multiplier = 1e-6;
        
        return multiplier*stod(line[3]);
      }
    }
  }
  cout<<"ERROR - STARLIGHT cross section not found!!!"<<endl;
  
  return -1;
}

int main(int argc, char* argv[])
{
  if(argc!=6){
    cout<<"Usage:"<<endl;
    cout<<"./findCoupling xsec_precision(nb) min_lambda(GeV) max_lambda(GeV) alp_mass(GeV) desired_xsec(nb) "<<endl;
    exit(0);
  }
  
  double crossSectionPrecision = atof(argv[1]);
  double minCoupling = atof(argv[2]);
  double maxCoupling = atof(argv[3]);
  double mass = atof(argv[4]);
  double desiredCrossSection = atof(argv[5]);
  
  
  cout<<"ALP mass: "<<mass<<" GeV"<<endl;
  cout<<"Desired cross section: "<<desiredCrossSection<<" nb"<<endl;
  cout<<"Cross section precision: "<<crossSectionPrecision<<" nb"<<endl;
  cout<<"Allowed coupling range: "<<minCoupling<<" -- "<<maxCoupling<<" GeV"<<endl;
  
  setOption(starlightPath+sourceFilePath, "ax_mass", mass);
  
  double currentCrossSection = -9999;
  bool recomputeMin = true;
  bool recomputeSplit = true;
  
  double crossSectionMin, crossSectionSplit;
  double splitCoupling;
  
  while (fabs(desiredCrossSection-currentCrossSection) > crossSectionPrecision) {
    
    splitCoupling = (minCoupling + maxCoupling)/2;
    
    if(recomputeMin){
      crossSectionMin = getCrossSection(minCoupling);
//      cout<<"MIN -- coupling:"<<minCoupling<<" x-sec:"<<crossSectionMin<<endl;
    }
    
    if(recomputeSplit){
      crossSectionSplit = getCrossSection(splitCoupling);
//      cout<<"SPLIT -- coupling:"<<splitCoupling<<" x-sec:"<<crossSectionSplit<<endl;
    }
    
    double meanCoupling;
    
    if((desiredCrossSection < crossSectionMin) &&
       (desiredCrossSection > crossSectionSplit)){
      meanCoupling = (minCoupling + splitCoupling)/2;
      maxCoupling = splitCoupling;
      recomputeMin = false;
    }
    else{
      meanCoupling = (splitCoupling + maxCoupling)/2;
      minCoupling = splitCoupling;
      recomputeMin = true;
    }
     
    currentCrossSection = getCrossSection(meanCoupling);
    
    cout<<"Lambda: "<<meanCoupling<<" coupling: "<<1./meanCoupling<<" cross-section: "<<currentCrossSection<<endl;
  }
  
  return 0;
}
