#include "../include/Helpers.hpp"

string basePath = "../results/triggerEfficiencyQED";
//string basePath = "../results/triggerEfficiencyQED_EG3_or_EG5";
string outputPath = "../plots/triggerEfficiencyDependanceL1.pdf";
string outputPathScaleFactors = "../results/triggerScaleFactors.root";

vector<string> triggerCombinations = {
  //  "EG3",
  //  "EG5",
  //  "EG3_only",
  //  "EG5_only",
  "EG3_or_EG5"
};

vector<EDataset> datasetsToDraw = {
  kData,
//  kMCqedSC,
  kMCqedSL
};

vector<tuple<string, string, string, string>> variables = {
  {"effVsPt_lowEta"   , "SCEt"    , "SC E_{t} (GeV)"  , "#splitline{|#eta|#in[0.0, 1.2]}{SC E_{t} > 2 GeV}" },
  {"effVsPt_highEta"  , "SCEt"    , "SC E_{t} (GeV)"  , "#splitline{|#eta|#in[1.2, 2.4]}{SC E_{t} > 2 GeV}" },
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
  
  TCanvas *canvasScaleFactors = new TCanvas("Scale factors", "Scale factors", 1000, 1000);
  canvasScaleFactors->Divide(2,2);
  
  TLegend *mainLegend = new TLegend(0.2, 0.3, 0.8, 0.6);
  int iTriggerCombination = 0;
  
  TFile *outFile = new TFile(outputPathScaleFactors.c_str(), "recreate");
  
  for(string triggerCombination : triggerCombinations){
    
    bool firstVar = true;
    
    int iPad = 1;
    for(auto &[dirName, varName, axisName, legendText] : variables){
      TGraphAsymmErrors *graphData;
      TGraphAsymmErrors *graphMC;
      
      bool first = true;
      
      for(EDataset dataset : datasetsToDraw){
        
        string filePath = basePath + "_" + triggerCombination + "_" + datasetName.at(dataset)+".root";
        TFile *inFile = TFile::Open(filePath.c_str());
        
        if(!inFile){
          cout<<"ERROR -- couldn't open file: "<<filePath<<endl;
          continue;
        }
        
        
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
        graph->SetMarkerColor(datasetColor.at(dataset));
        graph->SetLineColor(datasetColor.at(dataset));
        
        graph->SetTitle("");
        //      graph->GetXaxis()->SetTitleSize(0.1);
        //      graph->GetYaxis()->SetTitleSize(0.1);
        graph->GetXaxis()->SetTitle(axisName.c_str());
        graph->GetYaxis()->SetTitle("Efficiency");
        graph->GetXaxis()->CenterTitle();
        
        canvas->cd(iPad);
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
        
        if(dataset == kData)    graphData = graph;
        if(dataset == kMCqedSC) graphMC   = graph;
        
        first = false;
      }
      
      //      graphData->Divide(graphMC);
      
      TGraphAsymmErrors *scaleFactorGraph = new TGraphAsymmErrors();
      
      for(int i=0; i<graphData->GetN(); i++){
        double xData, yData;  graphData->GetPoint(i, xData, yData);
        double xMC, yMC;      graphMC->GetPoint(i, xMC, yMC);
        
        double xDataErrLow  = graphData->GetErrorXlow(i);
        double xDataErrHigh = graphData->GetErrorXhigh(i);
        double yDataErrLow  = graphData->GetErrorYlow(i);
        double yDataErrHigh = graphData->GetErrorYhigh(i);
        double yMCerrLow    = graphMC->GetErrorYlow(i);
        double yMCerrHigh   = graphMC->GetErrorYhigh(i);
        
        double scaleFactor = yData/yMC;
        
        double sfErrLow  = scaleFactor * sqrt(pow(yDataErrLow/yData , 2) + pow(yMCerrLow/yMC , 2));
        double sfErrHigh = scaleFactor * sqrt(pow(yDataErrHigh/yData , 2) + pow(yMCerrHigh/yMC , 2));
        
        scaleFactorGraph->SetPoint(i, xData, scaleFactor);
        scaleFactorGraph->SetPointError(i, xDataErrLow, xDataErrHigh, sfErrLow, sfErrHigh);
      }
      
      
      canvasScaleFactors->cd(iPad);
      scaleFactorGraph->SetMarkerStyle(20);
      scaleFactorGraph->SetMarkerSize(1.0);
      scaleFactorGraph->SetMarkerColor(kBlack);

      scaleFactorGraph->Draw("APE");
    
      scaleFactorGraph->GetYaxis()->SetRangeUser(0, 2.0);
      scaleFactorGraph->GetYaxis()->SetTitle("SF (data/MC)");
      scaleFactorGraph->GetXaxis()->SetTitle(axisName.c_str());
      
      outFile->cd();
      
      if(dirName == "effVsPt_lowEta"){
        scaleFactorGraph->SetName("triggerScaleFactors_vsEt_etaBelow1p2");
        scaleFactorGraph->Write();
      }
      if(dirName == "effVsPt_highEta"){
        scaleFactorGraph->SetName("triggerScaleFactors_vsEt_etaAbove1p2");
        scaleFactorGraph->Write();
      }
      
      TLatex *text = new TLatex((scaleFactorGraph->GetXaxis()->GetXmax() - scaleFactorGraph->GetXaxis()->GetXmin())/2.,
                                0.1, legendText.c_str());
      text->Draw("same");
      
      iPad++;
      
    }
    
    iTriggerCombination++;
  }
  canvas->cd(4);
  mainLegend->Draw();
  
  canvas->SaveAs(outputPath.c_str());
  outFile->Close();
}
