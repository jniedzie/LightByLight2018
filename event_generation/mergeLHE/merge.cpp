#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <future>


using namespace std;

template<class T> double duration(T t0,T t1)
{
  auto elapsed_secs = t1-t0;
  typedef std::chrono::duration<float> float_seconds;
  auto secs = std::chrono::duration_cast<float_seconds>(elapsed_secs);
  return secs.count();
}

inline std::chrono::time_point<std::chrono::steady_clock> now()
{
  return std::chrono::steady_clock::now();
}

int main(int argc, char* argv[])
{
  if(argc != 5){
    cout<<"./merge basePath baseFileName nFiles outPath"<<endl;
  }
  
  const string basePath     = argv[1];
  const string baseFileName = argv[2];
  const int nFiles          = atoi(argv[3]);
  const string outPath      = argv[4];
  
  cout<<"Base path: "<<basePath<<endl;
  cout<<"Base file name: "<<baseFileName<<endl;
  cout<<"N files to process: "<<nFiles<<endl;
  cout<<"Output path: "<<outPath<<endl;
  
  ofstream outfile(outPath, ofstream::out);
  
  bool firstFile = true;
  
  int nFileMerged = 0;
  
  auto start = now();
  
  for(int iFile=0; iFile<nFiles; iFile++){
    cout<<"Processing file "<<iFile<<endl;
    
    ifstream infile(basePath+baseFileName+to_string(iFile)+".lhe");
    if(infile.fail()){
      cout<<"\tfile does not exist. Skipping"<<endl;
      continue;
    }
    
    bool eventsBeginningReached = false;
    string line;
    
    while(getline(infile, line)){
      if(firstFile){
        if(line.find("</LesHouchesEvents>") == string::npos){
          outfile << line <<endl;
        }
      }
      else{
        if(eventsBeginningReached && line.find("</LesHouchesEvents>") == string::npos){
          outfile << line <<endl;
        }
        else if(line.find("</init>") != string::npos){
          eventsBeginningReached = true;
        }
      }
    }
    
    
    firstFile = false;
    nFileMerged++;
  }
  
  outfile << " </LesHouchesEvents>" << endl;
  outfile.close();
  
  cout<<"Merged "<<nFileMerged<<" files"<<endl;
  cout<<"Time: "<<duration(start, now())<<endl;
  
}
