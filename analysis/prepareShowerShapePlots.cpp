//  prepareShowerShapePlots.cpp
//
//  Created by Jeremi Niedziela on 30/07/2019.

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "PhysObjectProcessor.hpp"
#include "ConfigManager.hpp"

string configPath = "configs/efficiencies.md";

vector<tuple<string, EDataset>> dataTypes = {
  { "Data"  , kData     },
  { "LbL"   , kMClbl    },
  { "QED"   , kMCqedSC  },
};

void fillHistograms(const unique_ptr<EventProcessor> &events,
                    const pair<TH1D*, TH1D*> &hists)
{
  for(int iEvent=0; iEvent<events->GetNevents(); iEvent++){
    if(iEvent%10000==0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params["maxEvents"]) break;
    
    auto event = events->GetEvent(iEvent);
    
    for(auto photon : event->GetPhotonSCs()){
//      if(photon->GetEt() < config.params["minEt"]) continue;
      if(fabs(photon->GetEta()) < maxEtaEB )      hists.first->Fill(photon->GetEtaWidth());
      else if(fabs(photon->GetEta()) < maxEtaEE)  hists.second->Fill(photon->GetEtaWidth());
    }
  }
}

int main()
{
  config = ConfigManager(configPath);
  map<string, pair<TH1D*, TH1D*>> hists;
  
  TFile *outFile = new TFile("results/showerShape.root", "recreate");
  
  for(auto &[name, dataset] : dataTypes){
    hists[name] = make_pair(new TH1D(("showerShapeBarrel"+name).c_str(),
                                     ("showerShapeBarrel"+name).c_str(), 100, 0, 0.1),
                            new TH1D(("showerShapeEndcap"+name).c_str(),
                                     ("showerShapeEndcap"+name).c_str(), 100, 0, 0.1));
  
    cout<<"Creating "<<name<<" plots"<<endl;
    
    unique_ptr<EventProcessor> events(new EventProcessor(dataset));
    fillHistograms(events, hists[name]);
    outFile->cd();
    hists[name].first->Write();
    hists[name].second->Write();
  }

  outFile->Close();
  
}
