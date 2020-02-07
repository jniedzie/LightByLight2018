#include "../include/Helpers.hpp"

string basePath = "../results/triggerEfficiencyQED";
string outputPath = "../plots/triggerEfficiencyDependanceL1.pdf";

vector<string> triggerCombinations = {
  "EG3",
  "EG5",
  "EG3_only",
//  "EG5_only",
  "EG3_or_EG5"
};

vector<EDataset> datasetsToDraw = {
  kData,
  kMCqedSC,
//  kMCqedSL
};

vector<tuple<string, string, string, string>> variables = {
  {"effVsPt_lowEta"   , "SCEt"    , "SC E_{t} (GeV)"  , "#splitline{|#eta|#in[0.0, 1.2]}{SC E_{t} > 2 GeV}" },
  {"effVsPt_highEta"  , "SCEt"    , "SC E_{t} (GeV)"  , "#splitline{|#eta|#in[1.2, 2.3]}{SC E_{t} > 2 GeV}" },
  {"effVsEta"         , "abseta"  , "|#eta|"          , "SC E_{t} > 2 GeV"                                  },
};

TGraphAsymmErrors *getEfficiencyPlot(RooDataSet *fitResults, string xVarName){
  
  const RooArgSet *set = fitResults->get();
  RooRealVar *xVar = (RooRealVar*)set->find(xVarName.c_str());
  RooRealVar *yVar = (RooRealVar*)set->find("efficiency");
  
  if(!xVar){
    cout<<"Coult not find variable: "<<xVarName<<endl;
    return nullptr;
  }
  
  const int nBins = xVar->getBinning().numBins();
  
  double xVal[nBins], xValErrHi[nBins], xValErrLo[nBins];
  double yVal[nBins], yValErrHi[nBins], yValErrLo[nBins];
  
  // Get values and their errors
  for (int i=0; i<nBins; i++) {
    fitResults->get(i);
    
    yVal[i] = yVar->getVal();
    xVal[i] = xVar->getVal();
    
    xValErrHi[i] = fabs(xVar->getErrorHi());
    xValErrLo[i] = fabs(xVar->getErrorLo());
    
    yValErrHi[i] = fabs(yVar->getErrorHi());
    yValErrLo[i] = fabs(yVar->getErrorLo());
  }
  return  new TGraphAsymmErrors(nBins, xVal, yVal, xValErrLo, xValErrHi, yValErrLo, yValErrHi);
}

void drawTriggerEfficiencyQED()
{
  TCanvas *canvas = new TCanvas("Trigger efficiency", "Trigger efficiency", 1000, 1000);
  canvas->Divide(2,2);
  
  TLegend *mainLegend = new TLegend(0.2, 0.3, 0.8, 0.6);
  
  bool first = true;
  for(EDataset dataset : datasetsToDraw){
    int iTriggerCombination = 0;
    
    for(string triggerCombination : triggerCombinations){
      
      string filePath = basePath + "_" + triggerCombination + "_" + datasetName.at(dataset)+".root";
      TFile *inFile = TFile::Open(filePath.c_str());
      
      int iPad = 1;
      bool firstVar = true;
      for(auto &[dirName, varName, axisName, legendText] : variables){
        
        string resultsPath = "triggerTree_"+datasetName.at(dataset)+"/"+dirName+"/fit_eff";
        RooDataSet *fitResults = (RooDataSet*)inFile->Get(resultsPath.c_str());
        
        if(!fitResults){
          cout<<"Could not find fit results: "<<resultsPath<<endl;
          continue;
        }
        
        auto graph = getEfficiencyPlot(fitResults, varName);
        
        graph->SetMaximum(1.1);
        graph->SetMinimum(0.0);
        
        graph->SetMarkerStyle(dataset == kData ? 20 : 21);
        graph->SetMarkerSize(1.0);
        graph->SetMarkerColor(kBlack + iTriggerCombination);
        graph->SetLineColor(kBlack + iTriggerCombination);
        
        graph->SetTitle("");
        //      graph->GetXaxis()->SetTitleSize(0.1);
        //      graph->GetYaxis()->SetTitleSize(0.1);
        graph->GetXaxis()->SetTitle(axisName.c_str());
        graph->GetYaxis()->SetTitle("Efficiency");
        graph->GetXaxis()->CenterTitle();
        
        canvas->cd(iPad++);
        graph->Draw(first ? "APZ" : "PZsame");
        
        if(firstVar){
          mainLegend->AddEntry(graph, (datasetDescription.at(dataset)+" "+triggerCombination).c_str(), "elp");
          firstVar=false;
        }
        if(first){
          TLatex *text = new TLatex((graph->GetXaxis()->GetXmax() - graph->GetXaxis()->GetXmin())/2.,
                                    0.1, legendText.c_str());
          text->Draw("same");
        }
      }
      first = false;
      iTriggerCombination++;
    }
  }
  canvas->cd(4);
  mainLegend->Draw();
  
  canvas->SaveAs(outputPath.c_str());
}
