#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

using namespace std;

//----------------------------------------------------------------------------------------------------------------
//
// Requires gcc 6. Run the following:
// source /cvmfs/sft.cern.ch/lcg/releases/LCG_87/gcc/6.2.0/x86_64-slc6/setup.sh
//
// then build with g++:
// g++ run_parallel.cpp -o run_parallel
//
// Requires two more files as a template (which will be automatically updated according to variables set below):
//  templateScriptPath - template of the bash script that will be copied for all jobs
//  condorConfigPath   - template of the condor config that also will be copied for all jobs
//
// There's not need to modify the scripts above!
//
// Set those variables:

const int nJobs         = 1000;
const int nEventsPerJob = 10;
const int jobOffset     = 1000;  // will start files numbering from the specified value

// Set this path to a valid EOS location. Make sure that you will not override already existing files!
string baseOutputPath     = "/eos/cms/store/group/phys_diffraction/lbyl_2018/pbpb_ee";
string superchicBasePath  = "/afs/cern.ch/work/j/jniedzie/private/light_by_light/superchic3.03/bin";
string lhapdfPath         = "/afs/cern.ch/work/j/jniedzie/private/light_by_light/superchic3.0/lhapdf";
string jobFlavour         = "espresso";         // condor-style job flavour
string baseConfigPath     = "input_ee.DAT";    // relative path to the base superchic config

// probably no need to modify those:
string gccPath            = "/cvmfs/sft.cern.ch/lcg/releases/LCG_87/gcc/6.2.0/x86_64-slc6/setup.sh";
string templateScriptPath = "run_superchic.sh"; // relative path to the template bash script
string condorConfigPath   = "run_parallel.sub"; // relative path to the template condor config

//
//----------------------------------------------------------------------------------------------------------------


int RandInt(int min, int max);
vector<string> tokenize(istream &str, string &line, char token);

void updateNjobs(string fileName, int value);

template <class T> void replaceOptionInFile(string fileName, string option, T value);
template <class T> void updateConfigFile(string fileName, string option, T value);
template <class T> void updateCondorConfig(string fileName, string option, T value);
template <class T> void updateRunScript(string fileName, string option, T value);
bool DirExists(const string &s);

int main()
{
  srand(time(NULL));
  
  system("mkdir -p log");
  system("mkdir -p output");
  system("mkdir -p error");
  system("mkdir -p parallel");
  
  for(int iJob=jobOffset;iJob<nJobs+jobOffset;iJob++){
    if((iJob-jobOffset)%100 == 0){
      cout<<"Processing job:"<<iJob-jobOffset<<endl;
    }
    
    string jobPath = "parallel/p"+to_string(iJob);
    string configPath = jobPath+"/input.DAT";
    
    if(DirExists(jobPath.c_str())){
      // if directory already exists, clean old events and just update the config
      system(("rm -fr "+jobPath+"/evrecs/*").c_str());
      system(("rm -fr "+jobPath+"/outputs/*").c_str());
      
      replaceOptionInFile(configPath, "[genunw]", ".true.");              // make sure to generate events
      replaceOptionInFile(configPath, "[nev]", nEventsPerJob);            // set correct number of events per job
      replaceOptionInFile(configPath, "[iseed]", RandInt(100,10000000));  // set random random seed
      replaceOptionInFile(configPath, "[outtg]", "''");                   // set proper output file name
    }
    else{
      // if directory is not there, create whole structure and link/copy needed files
      system(("mkdir -p "+jobPath).c_str());
      system(("mkdir -p "+jobPath+"/evrecs").c_str());
      system(("mkdir -p "+jobPath+"/outputs").c_str());
      system(("cd "+jobPath+"/;ln -s ../../PDFsets .").c_str());
      system(("cd "+jobPath+"/;ln -s ../../inputs .").c_str());
      system(("cd "+jobPath+"/;ln -s ../../superchic .").c_str());
      
      system(("cp "+baseConfigPath+" "+configPath).c_str());
      
      replaceOptionInFile(configPath, "[genunw]", ".true.");              // make sure to generate events
      replaceOptionInFile(configPath, "[nev]", nEventsPerJob);            // set correct number of events per job
      replaceOptionInFile(configPath, "[iseed]", RandInt(100,10000000));  // set random random seed
      replaceOptionInFile(configPath, "[outtg]", "''");                   // set proper output file name
    }
  }

  // Set all the paths and options in the shell main script
  updateCondorConfig(templateScriptPath, "jobOffset", jobOffset);
  updateCondorConfig(templateScriptPath, "output_path", baseOutputPath);
  updateCondorConfig(templateScriptPath, "superchic_path", superchicBasePath);
  updateCondorConfig(templateScriptPath, "gcc6_path", gccPath);
  updateCondorConfig(templateScriptPath, "lhapdf_path", lhapdfPath);
  
  // Set exec privilages to the shell script
  system(("chmod 777 "+templateScriptPath).c_str());
  
  // Set variables in the condor config
  updateConfigFile(condorConfigPath, "+JobFlavour", "\""+jobFlavour+"\"");
  updateNjobs(condorConfigPath, nJobs);
  
  // Finally, submit condor jobs
  system(("condor_submit "+condorConfigPath).c_str());
  
  return 0;
}


int RandInt(int min, int max)
{
  return min + (rand() % static_cast<int>(max - min + 1));
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

template <class T>
void replaceOptionInFile(string fileName, string option, T value)
{
  ofstream outFile("tmp.file");
  ifstream readFile(fileName.c_str());
  
  vector<string> line;
  string fullLine;
  
  while (readFile.good()){
    line = tokenize(readFile,fullLine, '!');
    
    if(line.size()>1){
      if(line[1].find(option) != string::npos) outFile << value<<"\t\t\t!"<<line[1] << endl;
      else                                     outFile << fullLine << endl;
    }
    else{
      outFile << fullLine << endl;
    }
  }
  readFile.close();
  
  system(("mv tmp.file " + fileName).c_str());
}

template <class T>
void updateConfigFile(string fileName, string option, T value)
{
  ofstream outFile("tmp.file");
  ifstream readFile(fileName.c_str()); // run_batch.sub
  
  vector<string> line;
  string fullLine;
  
  while (readFile.good()){
    line = tokenize(readFile,fullLine, '=');
    
    if(line.size()>1){
      if(line[0].find(option) != string::npos) outFile << line[0]<<"= "<<value<< endl;
      else                                     outFile << fullLine << endl;
    }
    else{
      outFile << fullLine << endl;
    }
  }
  readFile.close();
  
  system(("mv tmp.file " + fileName).c_str());
}

template <class T>
void updateCondorConfig(string fileName, string option, T value)
{
  ofstream outFile("tmp.sub");
  ifstream readFile(fileName.c_str()); // run_batch.sub
  
  vector<string> line;
  string fullLine;
  
  while (readFile.good()){
    line = tokenize(readFile,fullLine, '=');
    
    if(line.size()>1){
      if(line[0].find(option) != string::npos) outFile << line[0]<<"="<<value<< endl;
      else                                     outFile << fullLine << endl;
    }
    else{
      outFile << fullLine << endl;
    }
  }
  readFile.close();
  
  system(("mv tmp.sub " + fileName).c_str());
}

void updateNjobs(string fileName, int value)
{
  ofstream outFile("tmp.file");
  ifstream readFile(fileName.c_str()); // run_batch.sub
  
  vector<string> line;
  string fullLine;
  
  while (readFile.good()){
    line = tokenize(readFile,fullLine, ' ');
    
    if(line.size()>1){
      if(line[0].find("queue") != string::npos) outFile << "queue "<<value<< endl;
      else                                      outFile << fullLine << endl;
    }
    else{
      outFile << fullLine << endl;
    }
  }
  readFile.close();
  
  system(("mv tmp.file " + fileName).c_str());
}

template <class T>
void updateRunScript(string fileName, string option, T value)
{
  ofstream outFile("tmp.sh");
  ifstream readFile(fileName.c_str()); // run_sc.sh
  
  vector<string> line;
  string fullLine;
  
  while (readFile.good()){
    line = tokenize(readFile,fullLine, '<');
    
    if(line.size()>1){
      if(line[0].find(option) != string::npos) outFile << line[0]<<"< "<<value<< endl;
      else                                     outFile << fullLine << endl;
    }
    else{
      outFile << fullLine << endl;
    }
  }
  readFile.close();
  
  system(("mv tmp.sh " + fileName).c_str());
  system(("chmod 777 " + fileName).c_str());
}

bool DirExists(const string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}
