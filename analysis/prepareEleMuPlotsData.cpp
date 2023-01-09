//based on preparebasicPlots.cpp

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"
#include "EventDisplay.hpp"
#include "Logger.hpp"

  string configPath = "configs/efficiencies_eleNoIsolation_newThresholdsEta2p2.md";
  string outputPath = "Output/basicPlots_test.root";

bool saveCalosFailingNEE = true;
//bool saveTriphotonHists = true;
//bool checkTriggers = false;

//int nThreePhotonEvents = 0;


// Only those datasets will be analyzed
 const vector<EDataset> datasetsToAnalyze = {
   kData,kMCqedSC,
};

double luminosity = 1642.79;
double crossSection = 570;
double weight = (luminosity * crossSection)/1000000;


vector<string> suffixes = {
  "all"
};

vector<tuple<string, int, double, double>> histParams = {
 
   // title                                      nBins            min                   max

  {"dilepton_acoplanarity"       ,    40          ,       0       ,       0.4  },
  {"muon_pt"                     ,    14          ,     2.0        ,      16.0  },
  {"muon_eta"                    ,    10          ,    -2.5       ,       2.5  },
  {"muon_phi"                    ,    14          ,    -3.5       ,       3.5 },
  {"muon_px"                     ,    28          ,   -14.0       ,      14.0  },
  {"muon_py"                     ,    35          ,   -15.0       ,      20.0  },
  {"muon_pz"                     ,    20          ,   -20.0       ,      20.0  },
  {"e_pt"                        ,    16          ,     2.0       ,      18.0  },
  {"e_eta"                       ,    10          ,    -2.5       ,       2.5  },
  {"e_phi"                       ,    14          ,    -3.5       ,       3.5  },
  {"e_px"                        ,    30          ,   -15.0       ,      15.0  },
  {"e_py"                        ,    30          ,   -15.0       ,      15.0  },
  {"e_pz"                        ,    28          ,   -26.0       ,      30.0  },
  {"dilepton_mass"               ,    14          ,       0       ,      28.0  },
  {"dilepton_rapidity"           ,    20          ,    -2.5       ,       2.5  },
  {"dilepton_pt"                 ,    28          ,       0       ,      14.0  },
  {"dilepton_phi"                ,    30          ,     2.6       ,       3.2  },
  {"dilepton_Scalar_Pt"          ,    22          ,       0       ,      22.0  },
  {"dilepton_deltaEleR"          ,    20          ,       0       ,      10.0  },
  {"dilepton_deltaR"             ,    40          ,       0       ,       5.0  },
  {"dilepton_deltaRelectron"     ,    40          ,       0       ,       0.2  },
  {"dilepton_deltaRmuon"         ,    40          ,       0       ,       0.2  },
  {"dilepton_TauTauPz"           ,    30          ,   -30.0       ,      30.0  },
  {"dilepton_TauTauPx"           ,   120          ,   -30.0       ,      30.0  },
  {"dilepton_TauTauPy"           ,   120          ,   -30.0       ,      30.0  },
  {"dilepton_TauTauEta"          ,    10          ,     0.0       ,       5.0  },
  {"muon_InnerDz"                ,  2200          , -1100.0       ,    1100.0  },
  {"zdc_sum_energy"              ,  100          ,     0.0       ,    100000.0},
  {"zdc_sum_energy_pos"          ,  100          ,     0.0       ,    100000.0},
  {"zdc_sum_energy_neg"          ,  100          ,     0.0       ,    100000.0},
  {"NTrk"                        ,   25           ,     0.0       ,       25.0 },

 
};



//bool endsWith(const std::string &mainStr, const std::string &toMatch)
//{
 // if(mainStr.size() >= toMatch.size() &&
   //  mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
   // return true;
  //else
   // return false;
//}

///Muon
void fillMuonHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  for(auto muon : event.GetPhysObjects(EPhysObjType::kGoodMuon)){
    hists.at("muon_pt_" +suffix+datasetName)->Fill(muon->GetPt());
    hists.at("muon_eta_"+suffix+datasetName)->Fill(muon->GetEta());
    hists.at("muon_phi_"+suffix+datasetName)->Fill(muon->GetPhi());
 //   hists.at("muon_px_" +suffix+datasetName)->Fill(muon->GetPx());
   // cout<< "MuonPx"<< muon->GetPx() <<endl;
    //hists.at("muon_py_" +suffix+datasetName)->Fill(muon->GetPy());
//    hists.at("muon_pz_" +suffix+datasetName)->Fill(muon->GetPz());
  //  cout<< "MuonPx"<< muon->GetPx() <<endl;
    hists.at("muon_InnerDz_" +suffix+datasetName)->Fill(muon->GetInnerDz());
     cout << "MuonPT = " << muon->GetPt() << endl;
     cout << "muonEta = " << muon->GetEta() << endl;
     cout << "muonPhi = " << muon->GetPhi() << endl;
}   
///ZDC test
    double zdcEnergySum = 0;
    double zdcEnergySumPos = 0;
    double zdcEnergySumNeg = 0;

    for(auto zdc : event.GetPhysObjects(EPhysObjType::kZDC)){
    zdcEnergySum += zdc->GetEnergy();

     if(zdc->GetZside() > 0) zdcEnergySumPos += zdc->GetEnergy();
    else                    zdcEnergySumNeg += zdc->GetEnergy();
  }
  hists.at("zdc_sum_energy_"+suffix+datasetName)->Fill(zdcEnergySum);
  hists.at("zdc_sum_energy_pos_"+suffix+datasetName)->Fill(zdcEnergySumPos);
  hists.at("zdc_sum_energy_neg_"+suffix+datasetName)->Fill(zdcEnergySumNeg);
  cout << "zdcEnergySum:" << zdcEnergySum << endl;
  cout << "zdcEnergySum_Pos:" << zdcEnergySumPos << endl;
  cout << "zdcEnergySum_Neg:" << zdcEnergySumNeg << endl;




   
  
}

//Electron
void fillElectronHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
  for(auto electron : event.GetPhysObjects(EPhysObjType::kGoodElectron)){
    hists.at("e_pt_" +suffix+datasetName)->Fill(electron->GetPt());
    hists.at("e_eta_"+suffix+datasetName)->Fill(electron->GetEta());
    hists.at("e_phi_"+suffix+datasetName)->Fill(electron->GetPhi());
 //   hists.at("e_px_" +suffix+datasetName)->Fill(electron->GetPx());
  //  hists.at("e_py_" +suffix+datasetName)->Fill(electron->GetPy());
    //hists.at("e_pz_" +suffix+datasetName)->Fill(electron->GetPz());
    cout<< "electronPhi:"<< electron->GetPhi() <<endl;
    cout << "electronEta:" << electron->GetEta() << endl; 
    cout << "electronPt:"  << electron->GetPt() << endl;
}  
   ///ZDC
//  double zdcEnergySum = 0;
 // double zdcEnergySumPos = 0;
  //double zdcEnergySumNeg = 0;
  
 // for(auto zdc : event.GetPhysObjects(EPhysObjType::kZDC)){
 //   hists.at("lbl_zdc_energy_"+suffix+datasetName)->Fill(zdc->GetEnergy());//comment
   // zdcEnergySum += zdc->GetEnergy();
    
   // if(zdc->GetZside() > 0) zdcEnergySumPos += zdc->GetEnergy();
   // else                    zdcEnergySumNeg += zdc->GetEnergy();
 // }
 // hists.at("zdc_sum_energy_"+suffix+datasetName)->Fill(zdcEnergySum);
 // hists.at("zdc_sum_energy_pos_"+suffix+datasetName)->Fill(zdcEnergySumPos);
 // hists.at("zdc_sum_energy_neg_"+suffix+datasetName)->Fill(zdcEnergySumNeg);
 // cout << "zdcEnergySum:" << zdcEnergySum << endl;
 // cout << "zdcEnergySum_Pos:" << zdcEnergySumPos << endl;
 // cout << "zdcEnergySum_Neg:" << zdcEnergySumNeg << endl;
    
  

//This ZDC loop is working

  
}
//ZDC Date:21/09/2022
//void fillZDCHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
//{
 
  //if(suffix != "") suffix += "_";
  
 // double zdcEnergySumPos = 0;
  //double zdcEnergySumNeg = 0;
  
  //for(auto zdc : event.GetPhysObjects(EPhysObjType::kZDC)){
    //if(zdc->GetZside() > 0) zdcEnergySumPos += zdc->GetEnergy();
    //else                    zdcEnergySumNeg += zdc->GetEnergy();
 // }
  
 // hists.at("zdc_sum_energy_pos_"+suffix+datasetName)->Fill(zdcEnergySumPos);
 // hists.at("zdc_sum_energy_neg_"+suffix+datasetName)->Fill(zdcEnergySumNeg);
//}


//Electron+Muon
void fillEleMuHists(Event &event, const map<string, TH1D*> &hists, string datasetName, string suffix="")
{
   
  TLorentzVector elemu = physObjectProcessor.GetEleMu(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0],
                                                      *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);

  TLorentzVector muonpz = physObjectProcessor.Getmu(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0]);
  
  TLorentzVector elepz = physObjectProcessor.Getele(*event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);
  double TauTauEta = (physObjectProcessor.Getmu(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0]).Eta() - physObjectProcessor.Getele(*event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]).Eta());

 
  hists.at("dilepton_mass_"     +suffix+datasetName)->Fill(elemu.M());
  hists.at("dilepton_rapidity_" +suffix+datasetName)->Fill(elemu.Rapidity());
  hists.at("dilepton_pt_"       +suffix+datasetName)->Fill(elemu.Pt());
  hists.at("dilepton_TauTauPz_" +suffix+datasetName)->Fill(elemu.Pz());
  hists.at("dilepton_TauTauPx_" +suffix+datasetName)->Fill(elemu.Px());
  hists.at("dilepton_TauTauPy_" +suffix+datasetName)->Fill(elemu.Py());
  hists.at("dilepton_TauTauEta_" +suffix+datasetName)->Fill(fabs(TauTauEta));

  //cout<< "ditauPz:"<< elemu->GetPz() <<endl;
  hists.at("muon_pz_"+suffix+datasetName)->Fill(muonpz.Pz());
  hists.at("muon_px_"+suffix+datasetName)->Fill(muonpz.Px());
  hists.at("muon_py_"+suffix+datasetName)->Fill(muonpz.Py());
  hists.at("e_pz_"+suffix+datasetName)->Fill(elepz.Pz());
  hists.at("e_px_"+suffix+datasetName)->Fill(elepz.Px());
  hists.at("e_py_"+suffix+datasetName)->Fill(elepz.Py());
  
//////////////////////////////////////////////////////////////////////////////
//Delta R betweeen electron and muon
  for(auto track : event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack)){
      for(auto electron : event.GetPhysObjects(EPhysObjType::kGoodElectron)){
         if(track->GetCharge() == electron->GetCharge()){
//            double deltaRelectron = physObjectProcessor.GetDeltaR(*event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack)[0],
  //                                                      *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);
          double deltaRelectron = sqrt(pow(electron->GetEta() - track->GetEta(), 2) + pow(electron->GetPhi() - track->GetPhi(), 2));


          hists.at("dilepton_deltaRelectron_"+suffix+datasetName)->Fill(deltaRelectron);
          cout << "trackcharge1:" << track->GetCharge() << endl;
          cout << "deltaRelectron:" << deltaRelectron << endl;
         cout << "ElectronCharge:" << electron->GetCharge() << endl;
         cout << "ElectronPhi2:"  << electron->GetPhi() << endl;
     }
    }
   }

    for(auto track : event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack)){
      for(auto muon : event.GetPhysObjects(EPhysObjType::kGoodMuon)){
         if(track->GetCharge() == muon->GetCharge())
        {
//         double deltaRmuon = physObjectProcessor.GetDeltaR(*event.GetPhysObjects(EPhysObjType::kGoodGeneralTrack)[1],
  //                                                         *event.GetPhysObjects(EPhysObjType::kGoodMuon)[0]);
          double deltaRmuon = sqrt(pow(muon->GetEta() - track->GetEta(), 2) + pow(muon->GetPhi() - track->GetPhi(), 2));

         hists.at("dilepton_deltaRmuon_"+suffix+datasetName)->Fill(deltaRmuon);
         cout << "trackcharge2:" << track->GetCharge() << endl;
         cout << "deltaRmuon:" << deltaRmuon << endl;
         cout << "MuonCharge:" << muon->GetCharge() << endl;
         cout << "MuonPhi2:" << muon->GetPhi() << endl;
       }

   }
 }
/////////////////////////////////////////////////////////////////////////////////////////

}
////////////////////////////////////////////////////////////////////////////////////////////
void fillTrackHists(Event &event, const map<string, TH1D*> &hists, EDataset dataset, string suffix="")
{
       string name = datasetName.at(dataset);
        if(suffix != "") suffix += "_";
//       int nTracks = (int)event.GetPhysObjects(EPhysObjType::kGeneralTrack).size();
  //     cout << "nTracks = " << nTracks << endl;
//       hists.at("NTrk_"+suffix+name)->Fill(nTracks);
}




////////////////////////////////////////////////////////////////////////////////////////////////

//TauTau
void fillTauTauHistograms(Event &event, const map<string, TH1D*> &hists, EDataset dataset, vector<string> suffix_list)
{
  string name = datasetName.at(dataset);
  int cutThrough=0;

  double aco = physObjectProcessor.GetAcoplanarity(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0],
                                                   *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);
  //event.GetPhysObjects(EPhysObjType::kMuon)[0]->GetCharge() == event.GetPhysObjects(EPhysObjType::kElectron)[0]->GetCharge();
  double delPhi =  physObjectProcessor.GetdeltaPhi(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0],
                                                   *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);

  double scalarsumpt =  physObjectProcessor.GetScalarPt(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0],
                                                   *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);


//  double deltaEleR = physObjectProcessor.GetDeltaEleR(*event.GetPhysObjects(EPhysObjType::kGeneralTrack)[0],
  //                                                    *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0],
    //                                                  *event.GetPhysObjects(EPhysObjType::kGeneralTrack)[0],
      //                                                *event.GetPhysObjects(EPhysObjType::kGoodMuon)[0]);
 
 //deltaR for electron
//  double deltaRelectron = physObjectProcessor.GetDeltaR(*event.GetPhysObjects(EPhysObjType::kGeneralTrack)[0],
  //                                              *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);
  //deltaR for muon
 // double deltaRmuon = physObjectProcessor.GetDeltaR(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0],
   //                                             *event.GetPhysObjects(EPhysObjType::kGeneralTrack)[0]);



  double deltaR = physObjectProcessor.GetDeltaR(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0],
                                                *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);

// double tautauPz = physObjectProcessor.GetTauTauPz(*event.GetPhysObjects(EPhysObjType::kGoodMuon)[0],
  //                                                  *event.GetPhysObjects(EPhysObjType::kGoodElectron)[0]);


  int nTracks = (int)event.GetPhysObjects(EPhysObjType::kGeneralTrack).size();
       cout << "nTracks = " << nTracks << endl;



  for(string suffix : suffix_list){

    if(aco < 0.01 || aco > 0.4) continue;
    
    if(suffix != "") suffix += "_";
    hists.at("dilepton_acoplanarity_"+suffix+name)->Fill(aco);
    hists.at("dilepton_phi_"+suffix+name)->Fill(delPhi);
    hists.at("dilepton_Scalar_Pt_"+suffix+name)->Fill(scalarsumpt);
    //hists.at("dilepton_deltaEleR_"+suffix+name)->Fill(deltaEleR);
    hists.at("dilepton_deltaR_"+suffix+name)->Fill(deltaR);
    hists.at("NTrk_"+suffix+name)->Fill(nTracks);

   // hists.at("dilepton_deltaRelectron_"+suffix+name)->Fill(deltaRelectron);
  //  hists.at("dilepton_deltaRmuon_"+suffix+name)->Fill(deltaRmuon);

    //hists.at("dilepton_deltasumzp_"+suffix+name)->Fill(tautauPz);
    //cout<<"tautaupz:"<<tautauPz<<endl;
   

    fillMuonHists(  event, hists, name, suffix);
    fillEleMuHists(event, hists, name, suffix);
    fillElectronHists(event, hists, name, suffix);
 //   fillZDCHists(event, hists, name, suffix);
    //fillTrackHists(    event, hists, dataset, suffix);
  }
}


/// Creates histograms, cut through and event counters for given dataset name, for each
///// histogram specified in `histParams` vector.


void InitializeHistograms(map<string, TH1D*> &hists, string datasetType, string suffix="")
{
  if(suffix != "") suffix = "_" + suffix;

  for(auto &[histName, nBins, min, max] : histParams){
    string title = histName + suffix + "_" + datasetType;

    if(hists.find(title) != hists.end()) continue;
    hists[title] = new TH1D(title.c_str(), title.c_str(), nBins, min, max);
  }
}


int main(int argc, char* argv[])
{
  if(argc != 5){
    cout<<"This app requires 4 parameters.\n";
    cout<<"./prepareBasicPlots configPath inputPath outputPath datasetName[Data|QED_SC|QED_SL|LbL|CEP]\n";
    exit(0);
  }
  cout<<"Reading input arguments"<<endl;

  string inputPath = "";
  string sampleName = "";

  //if(argc == 5){
  configPath = argv[1];
  inputPath  = argv[2];
  outputPath = argv[3];
  sampleName = argv[4];
  //}
  cout<<"Config: "<<configPath<<endl;
  cout<<"Input: "<<inputPath<<endl;
  cout<<"Output: "<<outputPath<<endl;
  cout<<"Sample name: "<<sampleName<<endl;


  config = ConfigManager(configPath);

  map<string, TH1D*> hists;
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");


 //if (endsWith(inputPath, "root")){
   // cout << "root file" << endl;
    EDataset dataset = nDatasets;

    if(sampleName == "Data")    dataset = kData;
    if(sampleName == "QED_SC")  dataset = kMCqedSC;
    if(sampleName == "QED_SL")  dataset = kMCqedSL;
    if(sampleName == "LbL")     dataset = kMClbl;
    if(sampleName == "CEP")     dataset = kMCcep;
    cout<<"test1"<<endl;
    auto events = make_unique<EventProcessor>(inputPath, dataset);

    for(string suffix : suffixes){
      InitializeHistograms(hists, sampleName, suffix);
      cout<<"test2"<<endl;
    }


    if(dataset == nDatasets){
      Log(0)<<"ERROR -- unknown dataset name provided: "<<sampleName<<"\n";
      exit(0);
    }
    
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
      if(iEvent%10 == 0)  Log(0)<<"Processing event "<<iEvent<<"\n";
      //if(iEvent%10000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
      if(iEvent >= config.params("maxEvents")) break;
      cout<<"test3"<<endl;
      auto event = events->GetEvent(iEvent);
      cout<<"test4"<<endl;
      fillTauTauHistograms(*event, hists, dataset, suffixes);
      //fillDimuonHists(*event, hists, dataset);
    }

  cout << "Writing Histograms" <<endl;
  outFile->cd();
  for(auto &[histName, hist] : hists) hist->Write();


  outFile->Close();
  cout << "Finished" << endl;
}


   
