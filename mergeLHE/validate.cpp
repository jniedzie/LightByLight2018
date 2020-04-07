#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <future>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


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
  if(argc != 4){
    cout<<"./merge basePath baseFileName nFiles"<<endl;
  }
  
  const string basePath     = argv[1];
  const string baseFileName = argv[2];
  const int nFiles          = atoi(argv[3]);
  
  cout<<"Base path: "<<basePath<<endl;
  cout<<"Base file name: "<<baseFileName<<endl;
  cout<<"N files to process: "<<nFiles<<endl;
  
  
  auto start = now();
  
  vector<pid_t> pid;
  
  cout<<"Scheduling jobs"<<endl;
  
  for(int iFile=0; iFile<nFiles; iFile++){
    if(iFile%100==0) cout<<"Processing file "<<iFile<<endl;
    
    string fileName = basePath+baseFileName+to_string(iFile)+".lhe";

    pid.push_back(fork());
    if(pid.back()==0){
      execl(("xmllint --noout "+fileName).c_str(), NULL);
      exit(0);
    }
  }
  
  cout<<"Waiting for jobs to finish"<<endl;

  for(int iFile=0; iFile<nFiles;iFile++){
    int status;
    waitpid(pid[iFile], &status, 0);

    if(WIFEXITED(status)){
      int exit_status = WEXITSTATUS(status);
      
      if(exit_status!=0){
        string fileName = basePath+baseFileName+to_string(iFile)+".lhe";
        cout<<"Exit status for file "<<fileName<<": "<<exit_status<<endl;
      }
    }
  }
  
  cout<<"Time: "<<duration(start, now())<<endl;
  
}
