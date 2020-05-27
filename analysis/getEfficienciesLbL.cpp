//  getEfficiencies
//
//  Created by Jeremi Niedziela on 22/07/2019.
//
//  Calculates MC driven efficiencies, as defined in the Analysis Note

#include "Helpers.hpp"
#include "EventProcessor.hpp"
#include "ConfigManager.hpp"
#include "PhysObjectProcessor.hpp"
#include "Logger.hpp"

string configPath = "configs/efficiencies.md";
string outputPath = "results/efficienciesLbL.root";

vector<string> histParams = {
  "reco_eff", "id_eff", "trigger_eff", "trigger_single_eff", "trigger_double_eff", "charged_excl_eff", "neutral_excl_eff", "reco_eff_eta","id_eff_eta"
};

//vector<string> histParams_eta = {
//  "reco_eff_eta", "id_eff_eta"
//};

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
  unique_ptr<EventProcessor> eventProcessor(new EventProcessor(inFileNames.at(kMClbl), kMClbl));
  
  // Prepare counters and histograms
  int nGenEvents                               = 0;
  int nEventsPassingAll                        = 0;
  int nEventsRecoMatched                       = 0;
  int nEventsPassingID                         = 0;
  int nEventsPassingIDandTrigger               = 0;
  int nEventsPassingIDandTriggerAndChargedExcl = 0;
  int nEventsPassingIDandTriggerAndBothExcl    = 0;
  
  float bins[] = { 0, 2, 3, 4, 5, 6, 8, 10, 13, 20 };
  map<string, TH1D*> hists;
  for(auto name : histParams){

   if(name.find("vs_eta") != string::npos){
     hists[name]         = new TH1D( name.c_str()        ,  name.c_str()        , 24, -2.4, 2.4);
     hists[name+"_num"]  = new TH1D((name+"_num").c_str(), (name+"_num").c_str(), 24, -2.4, 2.4);
     hists[name+"_den"]  = new TH1D((name+"_den").c_str(), (name+"_den").c_str(), 24, -2.4, 2.4);
   }
   else{
     hists[name]         = new TH1D( name.c_str()        ,  name.c_str()        , 9, bins);
     hists[name+"_num"]  = new TH1D((name+"_num").c_str(), (name+"_num").c_str(), 9, bins);
     hists[name+"_den"]  = new TH1D((name+"_den").c_str(), (name+"_den").c_str(), 9, bins);
   }
   hists[name+"_num"]->Sumw2();
   hists[name+"_den"]->Sumw2();
  }
  
  
  /* map<string, TH1D*> hists_eta;
     for(auto name : histParams_eta){
     hists_eta[name]         = new TH1D( name.c_str()        ,  name.c_str()        , 24, -2.4, 2.4);
     hists_eta[name+"_num"]  = new TH1D((name+"_num").c_str(), (name+"_num").c_str(), 24, -2.4, 2.4);
     hists_eta[name+"_den"]  = new TH1D((name+"_den").c_str(), (name+"_den").c_str(), 24, -2.4, 2.4);
     hists_eta[name+"_num"]->Sumw2();
     hists_eta[name+"_den"]->Sumw2();
     }*/
  
  // Loop over events
  int iEvent;
  for(iEvent=0; iEvent<eventProcessor->GetNevents(); iEvent++){
    if(iEvent%10000 == 0) Log(0)<<"Processing event "<<iEvent<<"\n";
    if(iEvent >= config.params("maxEvents")) break;
    
    auto event = eventProcessor->GetEvent(iEvent);
    
    // Here we get gen and reco photons that pass acceptance (c_ACC) criteria
    auto goodGenPhotons = event->GetPhysObjects(kGoodGenPhoton);
    auto photonsPassing = event->GetPhysObjects(kGoodPhoton);
    
    if(goodGenPhotons.size() != 2) continue;
    nGenEvents++;  
    hists["reco_eff_den"]->Fill(goodGenPhotons.front()->GetEt());
    hists["reco_eff_eta_den"]->Fill(goodGenPhotons.front()->GetEta());
 
    TLorentzVector diphoton;    
    //TLorentzVector diphoton = physObjectProcessor.GetDiphoton(*goodGenPhotons[0], *goodGenPhotons[1]);
    
    // Check properties of this event
    bool hasLbLTrigger            = event->HasTrigger(kDoubleEG2noHF) || event->HasTrigger(kSingleEG3noHF) || event->HasTrigger(kSingleEG5noHF); 
    bool hasTwoPhotonsPassingID   = photonsPassing.size() == 2;
    bool passesNeutralExclusivity = ! event->HasAdditionalTowers();
    bool passesChargedExclusivity = event->GetPhysObjects(kGoodGeneralTrack).size() == 0;
    bool passesDiphotonCuts;
    if(hasTwoPhotonsPassingID){
       diphoton                   = physObjectProcessor.GetDiphoton(*photonsPassing[0], *photonsPassing[1]);    
       passesDiphotonCuts         = diphoton.Pt() < config.params("diphotonMaxPt");
    }    
    bool hasTwoMachingPhotons     = HasTwoMatchingPhotons(goodGenPhotons, event->GetPhysObjects(kPhotonInAcceptance));
    
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
    
    if(hasTwoMachingPhotons && 
       hasTwoPhotonsPassingID){
      nEventsPassingID++;
      hists["id_eff_num"]->Fill(goodGenPhotons.front()->GetEt());
      hists["id_eff_eta_num"]->Fill(goodGenPhotons.front()->GetEta());
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
       event->HasTrigger(kSingleEG3noHF)){
      hists["trigger_single_eff_num"]->Fill(diphoton.M());
    }
    
    if(hasTwoPhotonsPassingID &&
	event->HasTrigger(kDoubleEG2noHF)){
      hists["trigger_double_eff_num"]->Fill(diphoton.M());
    }
    
    if(hasTwoMachingPhotons){
      nEventsRecoMatched++;
      hists["reco_eff_num"]->Fill(goodGenPhotons.front()->GetEt());
      hists["id_eff_den"]->Fill(goodGenPhotons.front()->GetEt());
      hists["reco_eff_eta_num"]->Fill(goodGenPhotons.front()->GetEta());
      hists["id_eff_eta_den"]->Fill(goodGenPhotons.front()->GetEta());
    }
  }
  
  // Print the results
  Log(0)<<"\n\n------------------------------------------------------------------------\n";
  Log(0)<<"N event analyzed: "<<iEvent<<"\n";
  Log(0)<<"N gen events within limits: "<<nGenEvents<<"\n";
  Log(0)<<"N events passing all selections: "<<nEventsPassingAll<<"\n";
  Log(0)<<"N events with reco photons in acceptance matched with Gen photons: "<<nEventsRecoMatched<<"\n";
  Log(0)<<"N events passing ID: "<<nEventsPassingID<<"\n";
  Log(0)<<"N events passing ID and trigger: "<<nEventsPassingIDandTrigger<<"\n";
  Log(0)<<"N events passing ID, trigger and charged excl: "<<nEventsPassingIDandTriggerAndChargedExcl<<"\n";
  Log(0)<<"N events passing ID, trigger and both excl: "<<nEventsPassingIDandTriggerAndBothExcl<<"\n";
  
  Log(0)<<"Diphoton efficiency: "; PrintEfficiency(nEventsPassingAll, nGenEvents);
  Log(0)<<"Reco     efficiency: "; PrintEfficiency(nEventsRecoMatched, nGenEvents);
  Log(0)<<"ID       efficiency: "; PrintEfficiency(nEventsPassingID, nEventsRecoMatched);
  Log(0)<<"Trigger efficiency: "; PrintEfficiency(nEventsPassingIDandTrigger, nEventsPassingID);
  Log(0)<<"Cherged exclusivity efficiency: "; PrintEfficiency(nEventsPassingIDandTriggerAndChargedExcl, nEventsPassingIDandTrigger);
  Log(0)<<"Neutral exclusivity efficiency: "; PrintEfficiency(nEventsPassingIDandTriggerAndBothExcl, nEventsPassingIDandTriggerAndChargedExcl);
  
  Log(0)<<"------------------------------------------------------------------------\n\n\n";
  
  // Save histograms
  TFile *outFile = new TFile(outputPath.c_str(), "recreate");
  outFile->cd();
  
  for(auto name : histParams){
    hists[name]->Divide(hists[name+"_num"], hists[name+"_den"], 1, 1, "B");
    hists[name]->Write();
    hists[name+"_num"]->Write();
    hists[name+"_den"]->Write();
  }
  
/*  for(auto name : histParams_eta){
    hists_eta[name]->Divide(hists_eta[name+"_num"], hists_eta[name+"_den"], 1, 1, "B");
    hists_eta[name]->Write();
    hists_eta[name+"_num"]->Write();
    hists_eta[name+"_den"]->Write();
  }*/
  outFile->Close();
  
  return 0;
}

