
vector<int> alpMasses = { 5, 6, 9, 11, 14, 16, 22, 30, 50, 90 };

TGraph* GetGraphFromTxt(const char *fileName, double scale=1.0){
  cout<<"File:"<<fileName<<endl;
  ifstream inFile(fileName);
  TGraph *result = new TGraph();
  double x,y;
  int i=0;
  while (inFile >> x >> y){
//    cout<<x<<"\t"<<y<<endl;
    result->SetPoint(i++,alpMasses[x],scale*y);
  }
  inFile.close();
  return result;
}

void plotALPxsecLimits()
{
  TGraph *limits = GetGraphFromTxt("../results/xsecMassLimits_old.txt");
  
  limits->Draw("AL");
  
  limits->GetXaxis()->SetRangeUser(4, 100);
  limits->GetYaxis()->SetRangeUser(6, 2000);
  
  gPad->SetLogx(true);
  gPad->SetLogy(true);
  
}
