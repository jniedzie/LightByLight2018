/* Routine for the conversion of starlight data format
 * into something readable by CMSSW_1_4_5
 *
 * Modification by X. Rouby on a routine kindly offered by J. Hollar
 * Sept. 28, 2007
 *
 * Modified by J. Niedziela on 28.06.2018
 */

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;

// Build this macro with:
//
// g++ ConvertStarlightQEDtoLHE.C -o convert `root-config --libs` `root-config --cflags` -std=c++0x
//
// Then place "convert" executable in top directory, where you have "starlight" directory with
// "slight_XX.out" files and "lhe" directory, where the LHE files will be put.

// Constants
const double electronMass = 0.000511; // electron mass [GeV]

int main(int argc, char* argv[])
{
  if(argc != 4){
    cout<<"usage: convert n_events_per_file input_file output_file"<<endl;
    exit(0);
  }
  
  const unsigned int eventsPerFile = atoi(argv[1]);
  
  ifstream infile(argv[2]);
  if (! infile.is_open()) { cout << "\t ERROR: I can not open \"" << argv[2] << "\"" << endl; return 1; }
  
  char outfilename[1000];
  
  string temp_string, temp;
  istringstream curstring;
  
  double charge = 0.0;
  int eventIter=0;        // event iterator - reading from the input file
  int eventsInFileIter=0; // event iterator - writing to the output file
  bool newFile = true;
  ofstream output;
  
  // GENER: STL  1.0            1           1           1           1  200.00     999.999     CMS
//  getline(infile,temp_string); // The very first line is useless
  
  int currentFirstEvent = 1;
  
  bool firstFile = true;
  
  while(getline(infile,temp_string)){
    
    curstring.clear(); // needed when using several tims istringstream::str(string)
    curstring.str(temp_string);
    
    if(firstFile){
      output.open(argv[3]);
      
      output << "<LesHouchesEvents version=\"1.0\">"  << endl;
      output << "<header>" << endl;
      output << "This file was created from the output of the STARLIGHT generator" << endl;
      output << "</header>" << endl;
      
      output << "<init>" << endl;
      output << "2212  2212  0.50000000000E+04  0.50000000000E+04 0 0 10042 10042 2  1" << endl;
      output << "0.10508723460E+01  0.96530000000E-02  0.26731120000E-03   0" << endl;
      output << "</init>" << endl;
      
      firstFile = false;
    }
    
    if(strstr(temp_string.c_str(),"EVENT")){
      curstring >> temp >> eventIter;
      // EVENT:          1       2       1
      if(eventIter >= currentFirstEvent && eventIter < currentFirstEvent+eventsPerFile) {
        if(eventsInFileIter > 0) output << "</event>" << endl;
        
        output << "<event>" << endl;
        output << "4   0  0.2983460E-04  0.9118800E+02  0.7546772E-02  0.1300000E+00" << endl;
        // JH - note here we add in two fake photons as the beam particles. The energies don't matter - this is only for
        // the LHE event record.
        output << "22   -1    0    0    0    0  0.00000000000E+00  0.00000000000E+00 0.00000000000E+02  0.10000000000E+02  0.00000000000E+00 0.  1." << endl;
        output << "22   -1    0    0    0    0  0.00000000000E+00  0.00000000000E+00 0.00000000000E+00  0.10000000000E+02  0.00000000000E+00 0. -1." << endl;
        
        eventsInFileIter++;
      }
      else{
        output << "</event>" << endl;
        output << "</LesHouchesEvents>" << endl;
        output.close();
        
        cout<<eventsInFileIter<<" events written in "<<outfilename<<endl;
        cout<<"first no. of event written: "<<currentFirstEvent<<endl;
        cout<<"last no. of event written: "<<currentFirstEvent+eventsPerFile-1<<endl;
        
        output.open(argv[3]);
        
        output << "<LesHouchesEvents version=\"1.0\">"  << endl;
        output << "<header>" << endl;
        output << "This file was created from the output of the STARLIGHT generator" << endl;
        output << "</header>" << endl;
        
        output << "<init>" << endl;
        output << "2212  2212  0.50000000000E+04  0.50000000000E+04 0 0 10042 10042 2  1" << endl;
        output << "0.10508723460E+01  0.96530000000E-02  0.26731120000E-03   0" << endl;
        output << "</init>" << endl;
        
        output << "<event>" << endl;
        output << "4   0  0.2983460E-04  0.9118800E+02  0.7546772E-02  0.1300000E+00" << endl;
        // JH - note here we add in two fake photons as the beam particles. The energies don't matter - this is only for
        // the LHE event record.
        output << "22   -1    0    0    0    0  0.00000000000E+00  0.00000000000E+00 0.00000000000E+02  0.10000000000E+02  0.00000000000E+00 0.  1." << endl;
        output << "22   -1    0    0    0    0  0.00000000000E+00  0.00000000000E+00 0.00000000000E+00  0.10000000000E+02  0.00000000000E+00 0. -1." << endl;
        eventsInFileIter=1;
        
        currentFirstEvent=eventIter;
      }
    }
    else if(strstr(temp_string.c_str(),"VERTEX")){
      float x,y,z,t;
      curstring >> temp >> x >> y >> z >> t;
      // VERTEX:   0.0000       0.0000       0.0000       0.0000          1      0      0      2
      //      if(eventIter >=K && eventIter < K+M) output << "V " << eventIter << " 0 " << x << " " << y << " " << z << " " << t << " 0 " << N <<  " 0" << endl;
    }
    else if(strstr(temp_string.c_str(),"TRACK")){
      int useless, part_n, pdg_id;
      float px, py, pz;
      //TRACK:      6   2.9797       3.1399       84.461          1      1      0    -13
      curstring >> temp >> useless >> px >> py >> pz >> part_n >> useless >> useless >> pdg_id;
      
      if(pdg_id ==  11) charge = -1.;
      if(pdg_id == -11) charge =  1.;
      
      if(eventIter >=currentFirstEvent && eventIter < currentFirstEvent+eventsPerFile){
        output << pdg_id << " 1 1 2 0 0 " << px << " " << py << " " << pz << " " << sqrt(electronMass*electronMass + px*px + py*py + pz*pz) << " " << electronMass << " 0. " << charge << endl;
      }
    }
    
  } // reading loop of the input file
  
  // close the last file
  output << "</event>" << endl;
  output << "</LesHouchesEvents>" << endl;
  output.close();
  
  cout<<eventsInFileIter<<" events written in "<<outfilename<<endl;
  cout<<"first no. of event written: "<<currentFirstEvent<<endl;
  cout<<"last no. of event written: "<<currentFirstEvent+eventsPerFile-1<<endl;
  
  infile.close();
  
  return 0;
}

/* Explaination of the format :
 * +++ Event +++
 * E 1 -1.0000000000000000e+00 -1.0000000000000000e+00 -1.0000000000000000e+00 20 0 1 0 0
 *   1 : event number  <-------
 *   -1 : event scale
 *   -1 : alpha_QCD
 *   -1 : alpha_QED
 *   20 : signal process ID
 *   0 : signal process vertex barcode
 *   1 : number of vertices <-------
 *   0 : list of vertices
 *   0 : ?
 *
 * +++ Vertex +++
 * V -1 0 0 0 0 0 0 4 0
 *   -1 : vertex barcode (unique)       <-------
 *    0 : vertex id
 *    0 0 0 0 : vertex x,y,z,t
 *    0 : number of orphans
 *    4 : number of out particles       <-------
 *    0 : weights
 *
 * +++ Particle +++
 * P 5 2212 -2.0 1.2 8.1 5.2 1 0 0 0 0
 *    5 : barcode<-------
 *    0 : pdg_id<-------
 *   -2.0 : px<-------
 *    1.2 : py<-------
 *    8.1 : pz<-------
 *    5.2 : e<-------
 *    1 : status<-------
 *    0 0  : polarization eta , phi
 *    0 0  : vertex and ?
 */
