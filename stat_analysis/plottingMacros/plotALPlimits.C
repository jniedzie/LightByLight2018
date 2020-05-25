
double yAxisMin = 7E-6; // 7e-6
double yAxisMax = 0.0025;

double logLabelSize = 0.10;
double labelSize = 0.045;
double titleSizeY = 0.12;
double titleSizeX = 0.050;

TGraph* GetGraphFromTxt(const char *fileName, double scale=1.0){
  
  cout<<"File:"<<fileName<<endl;
  ifstream inFile(fileName);
  TGraph *result = new TGraph();
  double x,y;
  int i=0;
  while (inFile >> x >> y){
//    cout<<x<<"\t"<<y<<endl;
    result->SetPoint(i++,x,scale*y);
  }
  inFile.close();
  return result;
}

vector<tuple<string, int, int, int, double, bool, bool, string, bool, bool>> graphParams = {
// inFileName                color     width   style   opacity   linear  log    options    BBonly   FFonly
  {"opal_2g_log_data"       , kCyan+2   , 2     , 1     , 0.4     , false , true  , "FL"  , false  , true  },
  {"lep_2g_log_data"        , kCyan+2   , 2     , 1     , 0.4     , false , true  , "FL"  , true   , false },
  {"beam_dump_data"         , kGray+2   , 2     , 1     , 0.1     , false , true  , "FL"  , false  , false },
  {"opal_2g_data"           , kCyan+2   , 2     , 1     , 0.4     , true  , false , "FL"  , false  , true  },
  {"lep_2g_data"            , kCyan+2   , 2     , 1     , 0.4     , true  , false , "FL"  , true   , false },
  {"opal_3g_data"           , kBlue     , 2     , 1     , 0.1     , true  , false , "FL"  , false  , false },
  {"atlas_z_2g_data"        , kViolet+1 , 2     , 1     , 0.1     , true  , false , "FL"  , true   , false },
  {"atlas_3g_data"          , kGreen+4  , 2     , 1     , 0.2     , true  , false , "FL"  , false  , false },
  {"atlas_2g_data"          , kGreen+2  , 2     , 1     , 0.1     , true  , false , "FL"  , false  , false },
//  {"cms_data"               , kRed      , 3     , 1     , 0.2     , true  , false , "L"   , false  , false },
//  {"jer_observed_data"      , kOrange+1 , 3     , 1     , 0.2     , true  , false , "L"   , false  , false },
  {"jer_expected_data"      , kGreen    , 5     , 2     , 0.2     , true  , false , "L"   , false  , false },
//  {"prediction_20nb_data"   , kRed      , 3     , 1     , 0.2     , true  , false , "L"   , false  , false },
//  {"cms_2015_reproduced"    , kRed      , 5     , 3     , 0.2     , true  , false , "L"   , false  , false },
  {"cms_2018_gen_level"     , kOrange+1 , 2     , 1     , 0.2     , true  , false , "L"   , false  , false },
//  {"cms_2018_gen_level_3p0" , kRed      , 2     , 1     , 0.2     , true  , false , "L"   , false  , false },
//  {"cms_2018_gen_level_4p0" , kViolet   , 2     , 1     , 0.2     , true  , false , "L"   , false  , false },
//  {"cms_2018_gen_level_4p5" , kBlue     , 5     , 1     , 0.2     , true  , false , "L"   , false  , false },
};

map<string, tuple<double, double, double, double, string>> legendParams = {
// path                  x1      y1      x2      y2     legend
  {"opal_2g_log_data" , { 0.08  , 0.75  , 1.85  , 0.95 , "e^{+}e^{-}#rightarrow2#gamma (OPAL)"        }},
  {"lep_2g_log_data" ,  { 0.08  , 0.75  , 1.85  , 0.95 , "e^{+}e^{-}#rightarrow2#gamma (LEP-I)"       }},
  {"beam_dump_data"   , { 0.205 , 0.10  , 0.65  , 0.30 , "#splitline{Beam}{dumps}"                    }},
  {"opal_3g_data"     , { 0.20  , 0.65  , 0.53  , 0.85 , "e^{+}e^{-}#rightarrow3#gamma (OPAL)"        }},
  {"atlas_3g_data"    , { 0.10  , 0.62  , 0.45  , 0.77 , "pp#rightarrow3#gamma (ATLAS)"               }},
  {"atlas_2g_data"    , { 0.55  , 0.70  , 0.88  , 0.90 , "pp#rightarrow2#gamma (ATLAS)"               }},
  {"cms_data"         , { 0.01  , 0.80  , 0.35  , 0.95 , "pp #rightarrow 2#gamma (CMS)"               }},
  {"atlas_z_2g_data"  , { -0.05 , 0.49  , 0.37  , 0.68 , "pp#rightarrowZ(3#gamma) (ATLAS)"            }},
};

void plotALPlimits(bool drawBB=false)
{
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  
  TPad *logPad = new TPad("logPad","logPad",0.0, 0.01, 0.3, 1.0);
  c1->cd();
  logPad->Draw();
  logPad->cd();
  logPad->SetLogx();
  logPad->SetLogy();
  logPad->SetRightMargin(0);
  logPad->SetLeftMargin(0.3);
  
  TPad *linPad = new TPad("linPad","linPad",0.3, 0.01, 1.0, 1.0);
  c1->cd();
  linPad->Draw();
  linPad->cd();
  linPad->SetLogx(0);
  linPad->SetLogy();
  linPad->SetLeftMargin(0);
  
  const char* prefix = drawBB ? "aBB_data" : "aFF_data";
  
//  double pi = TMath::Pi();
//  double alpha = 1/137.;
//  double c_1 = 10;
//  double c_2 = 0;
//  double c_gamma = c_2 + 5/3.0*c_1;
//  double scale = pi/(alpha*c_gamma);
//
//  cout<<"scale:"<<scale<<endl;
  
  bool firstLog = true;
  bool firstLin = true;
  
  map<string, TGraph*> graphs;
  
  for(auto &[path, color, width, style, opacity, linear, logarithmic, options, BBonly, FFonly] : graphParams){
    if(BBonly && !drawBB) continue;
    if(FFonly &&  drawBB) continue;
    
    graphs[path] = GetGraphFromTxt(Form("%s/%s.txt",prefix, path.c_str()));
    
    TGraph *graph = graphs[path];
    graph->SetLineColor(color);
    graph->SetLineWidth(width);
    graph->SetLineStyle(style);
    graph->SetFillColorAlpha(color,opacity);
    
    if(linear){
      linPad->cd();
      graph->Draw(firstLin ? ("A"+options+"Y+").c_str() : (options+"same").c_str());
      
      if(firstLin){
        graph->GetXaxis()->SetTitle("m_{a} (GeV)");
        graph->GetXaxis()->SetTitleSize(titleSizeX);
        graph->GetXaxis()->SetTitleOffset(0.85);
        graph->GetXaxis()->SetLabelSize(labelSize);
        graph->GetYaxis()->SetLabelSize(labelSize);
        
        graph->GetXaxis()->SetLimits(5,100);
        graph->GetYaxis()->SetRangeUser(yAxisMin,yAxisMax);
        
        firstLin = false;
      }
    }
    if(logarithmic){
      logPad->cd();
      graph->Draw(firstLog ? ("A"+options).c_str() : (options+"same").c_str());
      
      if(firstLog){
        graph->GetXaxis()->SetLimits(0.005,5);
        graph->GetXaxis()->SetLabelOffset(-0.076);
        
        graph->GetXaxis()->SetLabelSize(logLabelSize);
        graph->GetYaxis()->SetLabelSize(logLabelSize);
        graph->GetYaxis()->SetTitleSize(titleSizeY);
        
        graph->GetYaxis()->CenterTitle();
        graph->GetYaxis()->SetTitle(drawBB ?  "1/#Lambda (GeV^{-1}) #equiv g_{a#gamma,aB#tilde{B}}     " :
                                              "1/#Lambda (GeV^{-1}) #equiv g_{a#gamma,aF#tilde{F}}     ");
        
        graph->GetYaxis()->SetTitleOffset(1.0);
        graph->GetYaxis()->SetRangeUser(yAxisMin,yAxisMax);
        
        firstLog = false;
      }
    }
    
    if(legendParams.find(path) != legendParams.end()){
      auto &[x1, y1, x2, y2, legTitle] = legendParams[path];
      TLegend *legend = new TLegend(x1,y1,x2,y2);
      legend->SetTextColor(color);
      legend->SetFillStyle(0);
      legend->SetBorderSize(0);
      legend->AddEntry(new TGraph(),legTitle.c_str(),"");
      if(logarithmic){
        logPad->cd();
        legend->Draw();
      }
      if(linear){
        linPad->cd();
        legend->Draw();
      }
    }
  }
  

  
  linPad->cd();
  
  TLegend *leg = new TLegend(0.45,0.13,0.86,0.30);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
//  leg->AddEntry(graph_prediction_1nb,"Pb-Pb #sqrt{s_{NN}} = 5.5 TeV","l");
//  leg->AddEntry(graph_jer_250nb,"250 nb isoline","lp");
//  leg->AddEntry(graphs["jer_observed_data"],"PbPb (5.02 TeV) #rightarrow #gamma#gamma, CMS observed","lp");
//  leg->AddEntry(graphs["prediction_20nb_data"],"PbPb (5.52 TeV) #rightarrow #gamma#gamma, 20^{-1} nb projection","lp");
//  leg->AddEntry(graph_jer_expected,"PbPb (5.02 TeV) #rightarrow #gamma#gamma, expected","lp");
  
  leg->AddEntry(graphs["jer_expected_data"]     , "original 2015 (expected)"    , "l");
//  leg->AddEntry(graphs["prediction_20nb_data"]  , "20 nb^{-1} projection"       , "l");
//  leg->AddEntry(graphs["cms_2015_reproduced"]   , "reproduced 2015 (expected)"  , "l");
  leg->AddEntry(graphs["cms_2018_gen_level"]    , "new expected (|#eta| < 2.4)" , "l");
  leg->AddEntry(graphs["cms_2018_gen_level_3p0"], "new expected (|#eta| < 3.0)" , "l");
  leg->AddEntry(graphs["cms_2018_gen_level_4p0"], "new expected (|#eta| < 4.0)" , "l");
//  leg->AddEntry(graphs["cms_2018_gen_level_4p5"], "new expected (|#eta| < 4.5)" , "l");
  
  
  
  leg->Draw();
  
  TLegend *leg_linlog = new TLegend(-0.2,0.899,0.6,0.961);
  leg_linlog->SetTextColor(kBlack);
  leg_linlog->SetFillStyle(0);
  leg_linlog->SetBorderSize(0);
  leg_linlog->AddEntry(new TGraph(),"| linear scale #rightarrow","");
  leg_linlog->Draw();
  
  TLegend *leg_energy = new TLegend(0.35,0.77,0.90,1.08);
  leg_energy->SetTextColor(kBlack);
  leg_energy->SetFillStyle(0);
  leg_energy->SetBorderSize(0);
  leg_energy->AddEntry(new TGraph(),"PbPb 390 #mub^{-1}, #sqrt{s}_{NN} = 5.02 TeV","");
//  leg_energy->Draw();
  
  
  logPad->cd();

  TLegend *leg_cms_logo = new TLegend(0.00,0.71,1.20,1.15);
  leg_cms_logo->SetTextColor(kBlack);
  leg_cms_logo->SetFillStyle(0);
  leg_cms_logo->SetBorderSize(0);
  leg_cms_logo->SetTextFont(62);
  leg_cms_logo->AddEntry(new TGraph(),"CMS","");
//  leg_cms_logo->Draw();
  
  TLegend *leg_linlog2 = new TLegend(0.5,0.803,1.63,1.053);
  leg_linlog2->SetTextColor(kBlack);
  leg_linlog2->SetFillStyle(0);
  leg_linlog2->SetBorderSize(0);
  leg_linlog2->AddEntry(new TGraph(),"#leftarrow log |","");
  leg_linlog2->Draw();
  
  
  c1->SaveAs(drawBB ? "limits_coupling_BB.pdf" : "limits_coupling_FF.pdf");
}
