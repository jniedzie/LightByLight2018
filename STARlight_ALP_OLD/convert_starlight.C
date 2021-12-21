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

double electron_mass = 0.0005109989461; // GeV

TTree *pbpb_photonuclear_tree = 0;
int evtNum = -9999, partNum = -9999;
float mass = -9999., charge = -9999., pt = -9999., eta = -9999., phi = -9999.;
double y=-999., Et = -999., ptot=-999.;

void convert_starlight(const char* inFileName  = "slight.out",
                       const char* outFileName = "starlight.root")
{
  ifstream infile(inFileName);
  if (!infile.is_open()){
    cout<<"Can't open slight.out file"<<endl;
    return;
  }
  
  TFile *outFile = new TFile(outFileName,"recreate");
  
  TH1D *pidHist = new TH1D("Particle PID","Particle PID",201,-100,100);
  TH1D *ptHist = new TH1D("p_T dist","p_T dist",100,0,0.3);
  TH1D *phiHist = new TH1D("phi dist","phi dist",100,-4,4);
  TH1D *etaHist = new TH1D("eta dist","eta dist",100,-10,10);
  TH1D *diPtHist = new TH1D("dielectron p_t dist","dielectron p_t dist",100,0,0.5);
  TH1D *diYHist = new TH1D("dielectron y dist","dielectron y dist",100,-6,6);
  TH1D *massHist = new TH1D("dielectron m_inv","dielectron m_inv",100,0,2);
  
//  TTree*          outTree           = new TTree("starlightTree", "starlightTree");
//  TLorentzVector* parentParticle    = new TLorentzVector();
//  TClonesArray*   daughterParticles = new TClonesArray("TLorentzVector");
//  outTree->Branch("parent",    "TLorentzVector", &parentParticle,    32000, -1);
//  outTree->Branch("daughters", "TClonesArray",   &daughterParticles, 32000, -1);
  
  pbpb_photonuclear_tree = new TTree("pbpb_photonuclear_tree","Single & double photodissoc. Starlight-DPMJET, PbPb-2.76 TeV");
  pbpb_photonuclear_tree->Branch("evtNum",&evtNum,"evtNum/I");
  pbpb_photonuclear_tree->Branch("partNum",&partNum,"partNum/I");
  pbpb_photonuclear_tree->Branch("mass",&mass,"mass/F");
  pbpb_photonuclear_tree->Branch("charge",&charge,"charge/F");
  pbpb_photonuclear_tree->Branch("pt",&pt,"pt/F");
  pbpb_photonuclear_tree->Branch("eta",&eta,"eta/F");
  pbpb_photonuclear_tree->Branch("phi",&phi,"phi/F");
  
  string temp_string, temp;
  istringstream curstring;
  const unsigned int N = 2; // N_particles
  const unsigned int M = 1000; // N_events
  
  int i=0;
  int evt_n=0; // event_number, read from the input-file
  int nn=0; // event_counter, in the output file

  TLorentzVector particle(0.,0.,0.,0.);
  
  while (getline(infile,temp_string)) {
	
    curstring.clear(); // needed when using several tims istringstream::str(string)
    curstring.str(temp_string);

    if(strstr(temp_string.c_str(),"EVENT"))	{
      curstring >> temp >> evt_n;
      // EVENT:          1       2       1
      if(evt_n < M) {
        nn++;
      }
    }
    else if(strstr(temp_string.c_str(),"VERTEX")){
      float x,y,z,t;
      curstring >> temp >> x >> y >> z >> t;
		// VERTEX:   0.0000       0.0000       0.0000       0.0000          1      0      0      2
      if(evt_n < M){
//            output << "V " << evt_n << " 0 " << x << " " << y << " " << z << " " << t << " 0 " << N <<  " 0" << endl;
      }
    }
    else if(strstr(temp_string.c_str(),"TRACK")){
      
//      *parentParticle = TLorentzVector(0, 0, 0, 0);
      
      int useless, part_n, pdg_id_1, pdg_id_2;
      float px_1, py_1, pz_1;
      float px_2, py_2, pz_2;
      curstring >> temp >> useless >> px_1 >> py_1 >> pz_1 >> part_n >> useless >> useless >> pdg_id_1;
      
      getline(infile,temp_string);
      curstring.clear(); // needed when using several tims istringstream::str(string)
      curstring.str(temp_string);
      
      curstring >> temp >> useless >> px_2 >> py_2 >> pz_2 >> part_n >> useless >> useless >> pdg_id_2;
      
      double p_1 = sqrt(px_1*px_1+py_1*py_1+pz_1*pz_1);
      double theta_1 = acos(pz_1/p_1);
      double pt_1 = sqrt(px_1*px_1+py_1*py_1);
      double phi_1 = atan2(px_1,py_1);
      double eta_1 = -log(tan(theta_1/2.));
      double e_1 = p_1;
      
      double p_2 = sqrt(px_2*px_2+py_2*py_2+pz_2*pz_2);
      double theta_2 = acos(pz_2/p_2);
      double pt_2 = sqrt(px_2*px_2+py_2*py_2);
      double phi_2 = atan2(px_2,py_2);
      double eta_2 = -log(tan(theta_2/2.));
      double e_2 = p_2;
      
      double pairPt = sqrt(pow(px_1+px_2,2)+pow(py_1+py_2,2));
      double pairE = e_1+e_2;
      double pairPz = pz_1+pz_2;
      double pairY = 0.5*log((pairE+pairPz)/(pairE-pairPz));
      double m_inv = sqrt(pow(e_1+e_2,2)-(pow(px_1+px_2,2)+pow(py_1+py_2,2)+pow(pz_1+pz_2,2)));
      
      if(evt_n < M){
        pidHist->Fill(pdg_id_1);
        pidHist->Fill(pdg_id_2);
        ptHist->Fill(pt_1);
        ptHist->Fill(pt_2);
        phiHist->Fill(phi_1);
        phiHist->Fill(phi_2);
        etaHist->Fill(eta_1);
        etaHist->Fill(eta_2);
        diPtHist->Fill(pairPt);
        diYHist->Fill(pairY);
        massHist->Fill(m_inv);
        
        particle.SetPxPyPzE(px_1,py_1,pz_1,e_1);
        y = particle.Rapidity();
        eta = particle.PseudoRapidity();
        
        pt = particle.Pt();
        Et = particle.Et();
        //pz = particle.Pz();
        ptot = particle.P();
        phi = particle.Phi();
        pbpb_photonuclear_tree->Fill();
        
        particle.SetPxPyPzE(px_2,py_2,pz_2,e_2);
        y = particle.Rapidity();
        eta = particle.PseudoRapidity();
        
        pt = particle.Pt();
        Et = particle.Et();
        //pz = particle.Pz();
        ptot = particle.P();
        phi = particle.Phi();
        pbpb_photonuclear_tree->Fill();
        
        
//        new ( (*daughterParticles)[i] ) TLorentzVector(px_1,py_1,pz_1,e_1);
//        *parentParticle += *(static_cast<TLorentzVector*>(daughterParticles->At(i++)));
//
//        new ( (*daughterParticles)[i] ) TLorentzVector(px_2,py_2,pz_2,e_2);
//        *parentParticle += *(static_cast<TLorentzVector*>(daughterParticles->At(i++)));
        
      }
    }
//    daughterParticles->Compress();
//    outTree->Fill();
    
  } // reading loop of the input file
  infile.close();
  
  cout << nn << " events written"<<endl;
  
  outFile->cd();
  pbpb_photonuclear_tree->Write();
//  pidHist->Write();
//  ptHist->Write();
//  phiHist->Write();
//  etaHist->Write();
//  diPtHist->Write();
//  diYHist->Write();
//  massHist->Write();
  
  outFile->Close();
  delete outFile;
  return;
}

/* Explaination of the format :
 * +++ Event +++
 * E 1 -1.0000000000000000e+00 -1.0000000000000000e+00 -1.0000000000000000e+00 20 0 1 0 0
 *   1 : event number  			<-------
 *   -1 : event scale
 *   -1 : alpha_QCD
 *   -1 : alpha_QED
 *   20 : signal process ID
 *   0 : signal process vertex barcode
 *   1 : number of vertices 		<-------
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
 *    5 : barcode			<-------
 *    0 : pdg_id			<-------
 *   -2.0 : px				<-------
 *    1.2 : py				<-------
 *    8.1 : pz				<-------
 *    5.2 : e				<-------
 *    1 : status			<-------
 *    0 0  : polarization eta , phi
 *    0 0  : vertex and ?
 */
