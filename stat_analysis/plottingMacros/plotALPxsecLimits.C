vector<TGraphAsymmErrors*> GetGraphFromTxt(const char *fileName, double scale=1.0){
  cout<<"File:"<<fileName<<endl;
  ifstream inFile(fileName);
  
  vector<TGraphAsymmErrors*> graphs;
  for(int i=0; i<4; i++) graphs.push_back(new TGraphAsymmErrors());
  
  double mass, rObserved, r2p5, r16, r50, r84, r97p5;
  int i=0;
  while(inFile >> mass >> rObserved >> r2p5 >> r16 >> r50 >> r84 >> r97p5){
    cout<<mass<<"\t"<<rObserved<<"\t"<<r2p5<<"\t"<<r16<<"\t"<<r50<<"\t"<<r84<<"\t"<<r97p5<<endl;
    
    // observed
    graphs[0]->SetPoint(i, mass, scale*rObserved);
    
    // expected
    graphs[1]->SetPoint(i, mass, scale*r50);
    graphs[1]->SetPointError(i, 0, 0, 0, 0);
    
    // 1σ
    graphs[2]->SetPoint(i, mass, scale*r50);
    graphs[2]->SetPointError(i, 0, 0, scale*(r50-r16), scale*(r84-r50));
    
    // 2σ
    graphs[3]->SetPoint(i, mass, scale*r50);
    graphs[3]->SetPointError(i, 0, 0, scale*(r50-r2p5), scale*(r97p5-r50));
    
    i++;
  }
  inFile.close();
  return graphs;
}

void plotALPxsecLimits()
{
  vector<TGraphAsymmErrors*> limits = GetGraphFromTxt("../results/xsecMassLimits.txt");
  TLegend *legend = new TLegend(0.5, 0.6, 0.9, 0.9);
  TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
  canvas->cd();
  
  // 2σ
  limits[3]->SetFillColor(kYellow+1);
  limits[3]->Draw("A3");
  
  limits[3]->GetXaxis()->SetRangeUser(4, 100);
  gPad->SetLogx(true);
  gPad->SetLogy(true);
  limits[3]->GetYaxis()->SetRangeUser(0.05, 100.0);
  
  limits[3]->GetXaxis()->SetTitle("m_{a} (GeV)");
  limits[3]->GetYaxis()->SetTitle("95% CL upp. lim. on #sigma(#gamma#gamma #rightarrow a #rightarrow #gamma#gamma) (nb)");
  
  // 1σ
  limits[2]->SetFillColor(kGreen);
  limits[2]->Draw("3same");
  
  // expected
  limits[1]->SetLineStyle(0);
  limits[1]->SetLineColor(kBlack);
  limits[1]->SetLineWidth(2);
  limits[1]->Draw("Lsame");

  // observed
  limits[0]->SetLineStyle(2);
  limits[0]->SetLineColor(kBlack);
  limits[0]->SetLineWidth(2);
  limits[0]->Draw("Lsame");
  
  
  legend->AddEntry(limits[0], "Observed", "L");
  legend->AddEntry(limits[1], "Expected", "L");
  legend->AddEntry(limits[2], "68% expected", "F");
  legend->AddEntry(limits[3], "95% expected", "F");
  
  legend->Draw();
  
  canvas->SaveAs("limits_xsec.pdf");
}
