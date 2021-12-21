/* Routine for the conversion of starlight data format
 * into something readable by CMSSW_1_4_5
 *
 * Modification by X. Rouby on a routine kindly offered by J. Hollar
 * Sept. 28, 2007
 */

#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

const double electronMass = 0.000511; //[GeV]
const double ALPmass = 10; // [GeV]

double mass = ALPmass;

const unsigned int nEventsPerFile = 10000;

void ConvertStarlightToLHE(int nFiles=10, int filesOffset=0){
  
  string filename = "data/qed/slight_1.out";
  ifstream infile(filename.c_str());
  if (!infile.is_open()){ cout << "\t ERROR: I can not open \"" << filename << "\"" << endl; exit(0);}
  
  
  ofstream output[nFiles];
  string temp_string, temp;
  istringstream curstring;
  double charge = 0.0;
  bool firstEvent;
  int evt_n=0; // event_number, read from the input-file
  int iFile=-1;
  int currentFirstEvent;
  TH1F *phiDist = new TH1F("phiDist","phiDist",100,-5.0,5.0);
  
  getline(infile,temp_string); // The very first line is useless
  
  while (getline(infile,temp_string)){
    curstring.clear(); // needed when using several tims istringstream::str(string)
    curstring.str(temp_string);
    
    if(strstr(temp_string.c_str(),"EVENT")){
      curstring >> temp >> evt_n;
      // EVENT:          1       2       1
      
      if(evt_n/nEventsPerFile != iFile){
        // Changing to next file
        iFile = evt_n/nEventsPerFile;
        
        if(iFile > 0){ // close previous file
          output[iFile-1] << "</LesHouchesEvents>" << endl;
          output[iFile-1].close();
        }
        if(iFile == nFiles) break;
        
        string outFileName = "data/qed/lhe/qed_ee_pbpb_"+to_string(iFile+filesOffset)+".lhe";
        output[iFile] = ofstream(outFileName);
        
        // Add header to each output file
        output[iFile] << "<LesHouchesEvents version=\"1.0\">"  << endl;
        output[iFile] << "<header>" << endl;
        output[iFile] << "This file was created from the output of the STARLIGHT generator" << endl;
        output[iFile] << "</header>" << endl;
        
        output[iFile] << "<init>" << endl;
        output[iFile] << "2212  2212  0.50000000000E+04  0.50000000000E+04 0 0 10042 10042 2  1" << endl;
        output[iFile] << "0.10508723460E+01  0.96530000000E-02  0.26731120000E-03   0" << endl;
        output[iFile] << "</init>" << endl;

        currentFirstEvent = iFile*nEventsPerFile+1;
        firstEvent=true;
        cout<<"Changing output file to:"<<iFile<<endl;
        cout<<"Current first event:"<<currentFirstEvent<<endl;
      }
        
      if(evt_n >= currentFirstEvent && evt_n < currentFirstEvent+nEventsPerFile){
        if(!firstEvent) output[iFile] << "</event>" << endl;
        else            firstEvent=false;
        
        output[iFile] << "<event>" << endl;
        output[iFile] << "4   0  0.2983460E-04  0.9118800E+02  0.7546772E-02  0.1300000E+00" << endl;
        // JH - note here we add in two fake photons as the beam particles. The energies don't matter - this is only for
        // the LHE event record.
        output[iFile] << "22   -1    0    0    0    0  0.00000000000E+00  0.00000000000E+00 0.00000000000E+02  0.10000000000E+02  0.00000000000E+00 0.  1." << endl;
        output[iFile] << "22   -1    0    0    0    0  0.00000000000E+00  0.00000000000E+00 0.00000000000E+00  0.10000000000E+02  0.00000000000E+00 0. -1." << endl;
      }
    }
    else if(strstr(temp_string.c_str(),"VERTEX")){
      float x,y,z,t;
      curstring >> temp >> x >> y >> z >> t;
      // VERTEX:   0.0000       0.0000       0.0000       0.0000          1      0      0      2
      //      if(evt_n >=K && evt_n < K+M) output << "V " << evt_n << " 0 " << x << " " << y << " " << z << " " << t << " 0 " << N <<  " 0" << endl;
      
    }
    else if(strstr(temp_string.c_str(),"TRACK")){
      int useless, part_n, pdg_id;
      float px, py, pz;
      //TRACK:      6   2.9797       3.1399       84.461          1      1      0    -13
      curstring >> temp >> useless >> px >> py >> pz >> part_n >> useless >> useless >> pdg_id;
      //P 5 2212 -2.0 1.2 8.1 5.2 1 0 0 0 0
      if(pdg_id == 11) charge = -1.;
      if(pdg_id == -11) charge = 1.;
      
      if(evt_n >= currentFirstEvent && evt_n < currentFirstEvent+nEventsPerFile){
        output[iFile] << pdg_id << " 1 1 2 0 0 " << px << " " << py << " " << pz << " " << sqrt(mass*mass + px*px + py*py + pz*pz) << " " << mass << " 0. " << charge << endl;
        double phi = atan2(py,px);
//        if(evt_n%1000==0) cout << "phi = " << phi << endl;
        phiDist->Fill(phi);
      }
    }
  } // reading loop of the input file
  
  infile.close();
  phiDist->Draw("e");
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
