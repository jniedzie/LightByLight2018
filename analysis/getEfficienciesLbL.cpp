//  getEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
//  Calculates MC driven efficiencies, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "ConfigManager.hpp"
#include "PhysObjectProcessor.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/efficienciesLbL.root";

vector<string> histParams = {
  "reco_id_eff", "trigger_eff", "trigger_single_eff", "trigger_double_eff", "charged_excl_eff", "neutral_excl_eff"
};

/// Checks if exactly two photon superclusters in the provided collections are matched
/// with generated photons within ΔR specified in the config.
bool HasTwoMatchingPhotons(const PhysObjects &genPhotons,
                           const PhysObjects &photonSCs)
{
  int nMatched=0;
  
  for(auto &genPhoton : genPhotons){
    for(auto &cluster : photonSCs){
      double deltaR = sqrt(pow(genPhoton->GetEta() - cluster->GetEta(), 2)+
                           pow(genPhoton->GetPhi() - cluster->GetPhi(), 2));
      if(deltaR < config.params("maxDeltaR")) nMatched++;
    }
  }
  
  return nMatched >= 2;
}

/// Application starting point
int main()
{
  config = ConfigManager(configPath);
  unique_ptr<EventProcessor> eventProcessor(new EventProcessor(inFileNames.at(kMClbl)));
  
  // Prepare counters and histograms
  int nGenEvents                               = 0;
  int nEventsPassingAll                        = 0;
  int nEventsIDmatched                         = 0;
  int nEventsPassingID                         = 0;
  int nEventsPassingIDandTrigger               = 0;
  int nEventsPassingIDandTriggerAndChargedExcl = 0;
  int nEventsPassingIDandTriggerAndBothExcl    = 0;
  
  float bins[] = { 0, 2, 3, 4, 5, 6, 8, 10, 13, 20 };
  map<string, TH1D*> hists;
  for(auto name : histParams){
    hists[name]         = new TH1D( name.c_str()        ,  name.c_str()        , 9, bins);
    hists[name+"_num"]  = new TH1D((name+"_num").c_str(), (name+"_num").c_str(), 9, bins);
    hists[name+"_den"]  = new TH1D((name+"_den").c_str(), (name+"_den").c_str(), 9, bins);
    hists[name+"_num"]->Sumw2();
    hists[name+"_den"]->Sumw2();
  }
 
  // Loop over events
  int iEvent;
  for(iEvent=0; iEvent<eventProcessor->GetNevents(); iEvent++){
    if(iEvent%10000 == 0) cout<<"Processing event "<<iEvent<<endl;
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = eventProcessor->GetEvent(iEvent);
    
    // Here we get gen and reco photons that pass acceptance (c_ACC) criteria
    auto goodGenPhotons  = event->GetPhysObjects(kGoodGenPhoton);
    auto photonsPassing = event->GetPhysObjects(kGoodPhoton);
    
    if(goodGenPhotons.size() != 2) continue;
    nGenEvents++;
    hists["reco_id_eff_den"]->Fill(goodGenPhotons.front()->GetEt());
    
    
    TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*goodGenPhotons[0], *goodGenPhotons[1]);
    
    // Check properties of this event
    bool hasLbLTrigger            = event->HasDoubleEG2Trigger();
    bool hasTwoPhotonsPassingID   = photonsPassing.size() == 2;
    bool passesNeutralExclusivity = ! event->HasAdditionalTowers();
    bool passesChargedExclusivity = event->GetPhysObjects(kGoodGeneralTrack).size() == 0;
    bool passesDiphotonCuts       = diphoton.Pt() < config.params("diphotonMaxPt");
    bool hasTwoMachingPhotons     = HasTwoMatchingPhotons(goodGenPhotons, event->GetPhysObjects(kPhoton));
    
    if(hasLbLTrigger &&
       hasTwoPhotonsPassingID &&
       passesNeutralExclusivity &&
       passesChargedExclusivity &&
       passesDiphotonCuts){
      nEventsPassingAll++;
    }

    if(hasLbLTrigger &&
       hasTwoPhotonsPassingID &&
       passesChargedExclusivity){
      nEventsPassingIDandTriggerAndChargedExcl++;
      hists["charged_excl_eff_num"]->Fill(diphoton.M());
      hists["neutral_excl_eff_den"]->Fill(diphoton.M());
    }
    
    if(hasLbLTrigger &&
       hasTwoPhotonsPassingID &&
       passesChargedExclusivity &&
       passesNeutralExclusivity){
      nEventsPassingIDandTriggerAndBothExcl++;
      hists["neutral_excl_eff_num"]->Fill(diphoton.M());
    }
    
    if(hasTwoPhotonsPassingID){
      nEventsPassingID++;
      hists["trigger_eff_den"]->Fill(diphoton.M());
      hists["trigger_single_eff_den"]->Fill(diphoton.M());
      hists["trigger_double_eff_den"]->Fill(diphoton.M());
    }
    
    if(hasTwoPhotonsPassingID &&
       hasLbLTrigger){
      nEventsPassingIDandTrigger++;
      hists["trigger_eff_num"]->Fill(diphoton.M());
      hists["charged_excl_eff_den"]->Fill(diphoton.M());
    }
    
    if(hasTwoPhotonsPassingID &&
       event->HasSingleEG3Trigger()){
      hists["trigger_single_eff_num"]->Fill(diphoton.M());
    }
    
    if(hasTwoPhotonsPassingID &&
       event->HasDoubleEG2Trigger()){
      hists["trigger_double_eff_num"]->Fill(diphoton.M());
    }
    
    if(hasTwoMachingPhotons){
      nEventsIDmatched++;
      hists["reco_id_eff_num"]->Fill(goodGenPhotons.front()->GetEt());
    }
  }
  
  // Print the results
  cout<<"\n\n------------------------------------------------------------------------"<<endl;
  cout<<"N event analyzed: "<<iEvent<<endl;
  cout<<"N gen events within limits: "<<nGenEvents<<endl;
  cout<<"N events passing all selections: "<<nEventsPassingAll<<endl;
  cout<<"N events with matched photons passing selection: "<<nEventsIDmatched<<endl;
  cout<<"N events passing ID: "<<nEventsPassingID<<endl;
  cout<<"N events passing ID and trigger: "<<nEventsPassingIDandTrigger<<endl;
  cout<<"N events passing ID, trigger and charged excl: "<<nEventsPassingIDandTriggerAndChargedExcl<<endl;
  cout<<"N events passing ID, trigger and both excl: "<<nEventsPassingIDandTriggerAndBothExcl<<endl;
  
  cout<<"Diphoton efficiency: "; PrintEfficiency(nEventsPassingAll, nGenEvents);
  cout<<"Reco+ID efficiency: "; PrintEfficiency(nEventsIDmatched, nGenEvents);
  cout<<"Trigger efficiency: "; PrintEfficiency(nEventsPassingIDandTrigger, nEventsPassingID);
  cout<<"Cherged exclusivity efficiency: "; PrintEfficiency(nEventsPassingIDandTriggerAndChargedExcl, nEventsPassingIDandTrigger);
  cout<<"Neutral exclusivity efficiency: "; PrintEfficiency(nEventsPassingIDandTriggerAndBothExcl, nEventsPassingIDandTriggerAndChargedExcl);
  
  cout<<"------------------------------------------------------------------------\n\n"<<endl;
  
  // Save histograms
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  outFile->cd();
  
  for(auto name : histParams){
    hists[name]->Divide(hists[name+"_num"], hists[name+"_den"], 1, 1, "B");
    hists[name]->Write();
    hists[name+"_num"]->Write();
    hists[name+"_den"]->Write();
  }
  
  outFile->Close();
  
  return 0;
}

