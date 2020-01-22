//  prepareAcoplanarityPlots.cpp
//
//  Created by Jeremi Niedziela on 31/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/basicPlots.root";

// Only those datasets will be analyzed
const vector<EDataset> datasetsToAnalyze = {
//  kData,
//  kData_SingleEG3,
//  kData_recoEff,
//  kData_triggerEff,
//  kData_HFveto,
//  kData_exclusivity,
  kData_signal,
//  kMCqedSC,
//  kMCqedSC_SingleEG3,
//  kMCqedSC_recoEff,
//  kMCqedSC_triggerEff,
//  kMCqedSC_HFveto,
//  kMCqedSC_exclusivity,
  kMCqedSC_signal,
//  kMCqedSL,
//  kMClbl,
//  kMCcep
};

vector<tuple<string, int, double, double>> histParams = {
  // title                   nBins min   max
  {"lbl_acoplanarity"       , 20  , 0   , 0.1   },
  {"lbl_photon_et"          , 10  , 0   , 10.0  },
  {"lbl_photon_eta"         , 6   , -2.3, 2.3   },
  {"lbl_photon_phi"         , 8   , -4.0, 4.0   },
  {"lbl_diphoton_mass"      , 8   , 0   , 20.0  },
  {"lbl_diphoton_rapidity"  , 6   ,-3.0 , 3.0   },
  {"lbl_diphoton_pt"        , 5   , 0   , 1.0   },
  {"qed_acoplanarity"       , 30  , 0   , 0.06  },
  {"nTracks"                , 100 , 0   , 100   },
  {"nTracks_pt_geq_100_MeV" , 100 , 0   , 100   },
  {"nTracks_pt_lt_100_MeV"  , 100 , 0   , 100   },
  {"track_pt"               , 500 , 0   , 5     },
};

void fillHistograms(Event &event, const map<string, TH1D*> &hists, string datasetName)
{
  // Add all necessary selection criteria here
  // ...
  
  if(!event.HasDoubleEG2Trigger()) return;
  if(event.HasAdditionalTowers()) return;
  
  auto photons = event.GetGoodPhotons();
  
  if(photons.size() == 2 && event.GetNchargedTracks() == 0){
    double aco = physObjectProcessor.GetAcoplanarity(*photons[0], *photons[1]);
    hists.at("lbl_acoplanarity_"+datasetName)->Fill(aco);
    
    hists.at("lbl_photon_et_"+datasetName)->Fill(photons[0]->GetEt());
    hists.at("lbl_photon_et_"+datasetName)->Fill(photons[1]->GetEt());
    hists.at("lbl_photon_eta_"+datasetName)->Fill(photons[0]->GetEta());
    hists.at("lbl_photon_eta_"+datasetName)->Fill(photons[1]->GetEta());
    hists.at("lbl_photon_phi_"+datasetName)->Fill(photons[0]->GetPhi());
    hists.at("lbl_photon_phi_"+datasetName)->Fill(photons[1]->GetPhi());
    
    TLorentzVector diphoton = physObjectProcessor.GetObjectsSum(*photons[0], *photons[1]);
    
    hists.at("lbl_diphoton_mass_"+datasetName)->Fill(diphoton.M());
    hists.at("lbl_diphoton_rapidity_"+datasetName)->Fill(diphoton.Y());
    hists.at("lbl_diphoton_pt_"+datasetName)->Fill(diphoton.Pt());
  }
  
  auto electrons = event.GetGoodElectrons();
  
  if(electrons.size() == 2 && event.GetNchargedTracks() == 2){
    double aco = physObjectProcessor.GetAcoplanarity(*electrons[0], *electrons[1]);
    hists.at("qed_acoplanarity_"+datasetName)->Fill(aco);
  }
  
  
  int nTracks = event.GetNgeneralTracks();
  hists.at("nTracks_"+datasetName)->Fill(nTracks);
  
  for(int iTrack=0; iTrack<nTracks; iTrack++){
    double trackPt = event.GetGeneralTrack(iTrack)->GetPt();
    hists.at("track_pt_"+datasetName)->Fill(trackPt);
    
    int iBin = nTracks+1;
    if(trackPt < 0.1){
      hists.at("nTracks_pt_lt_100_MeV_"+datasetName)->SetBinContent(iBin, hists.at("nTracks_pt_lt_100_MeV_"+datasetName)->GetBinContent(iBin)+1);
    }
    else{
      hists.at("nTracks_pt_geq_100_MeV_"+datasetName)->SetBinContent(iBin, hists.at("nTracks_pt_geq_100_MeV_"+datasetName)->GetBinContent(iBin)+1);
    }
  }
}

/// Creates histograms, cut through and event counters for given dataset name, for each
/// histogram specified in `histParams` vector.
void InitializeHistograms(map<string, TH1D*> &hists, const string &datasetType)
{
  for(auto &[histName, nBins, min, max] : histParams){
    string title = histName + "_" + datasetType;
    hists[title] = new TH1D(title.c_str(), title.c_str(), nBins, min, max);
  }
}

int main()
{
  config = ConfigManager(configPath);
  
  map<string, TH1D*> hists;
  
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  
  for(auto dataset : datasetsToAnalyze){
    string name = datasetName.at(dataset);
    
    InitializeHistograms(hists, name);
    
    cout<<"Creating "<<name<<" plots"<<endl;
    
    auto events = make_unique<EventProcessor>(inFileNames.at(dataset));
    
    for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
         if(iEvent%1000 == 0) cout<<"Processing event "<<iEvent<<endl;
         if(iEvent >= config.params("maxEvents")) break;
         
         auto event = events->GetEvent(iEvent);
    
        fillHistograms(*event, hists, name);
    }
    
    outFile->cd();
    for(auto &[name, hist] : hists) hist->Write();
  }
  
  outFile->Close();
  
}
