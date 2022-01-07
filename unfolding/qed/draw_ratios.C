double syst_uncertainty = 0.11;
double syst_uncertainty_mc = 0.10;
int canvas_width = 1800;
int canvas_height = 700;

int mc_gen_color = kBlue;
int data_unfold_color = kRed;
int mc_reco_color = kBlack;
int data_reco_color = kOrange+1;


string MethID1 = "Bayes_unfo";
//  string MethID1 = "Svd_unfo"
//  string MethID1 = "BinByBin_unfo";

string mc_name = "QEDSL";

void make_hist(TH1D *& hist, string xtitle, string ytitle, int kstyle, float ksize, Color_t kcolor, int lstyle, int lwidth){
  // For the axis labels:
  hist->SetLabelColor(1, "XYZ");
  hist->SetLabelFont(42, "XYZ");
  hist->SetLabelOffset(0.007, "XYZ");
  hist->SetLabelSize(0.05, "XYZ");
  
  // For the axis titles:
  hist->SetTitleFont(42, "XYZ");
  hist->SetTitleSize(0.06, "XYZ");
  hist->GetXaxis()->SetTitleOffset(0.9);
  hist->GetYaxis()->SetTitleOffset(1.4);
  hist->SetMarkerColor(kcolor);
  hist->SetLineColor(kcolor);
  hist->SetMarkerStyle(kstyle);
  hist->SetMarkerSize(ksize);
  hist->GetYaxis()->SetTitle(ytitle.c_str());
  hist->GetXaxis()->SetTitle(xtitle.c_str());
  hist->SetLineStyle(lstyle);
  hist->SetLineWidth(lwidth);
}

TH1D* get_stat_uncertainty_hist(TH1D *input_hist, double uncertainty = syst_uncertainty){
  
  TH1D *output_hist = (TH1D*)input_hist->Clone();
  
  for(int iBin=1; iBin<=output_hist->GetNbinsX(); iBin++){
    double value = output_hist->GetBinContent(iBin);
    output_hist->SetBinError(iBin, uncertainty * value);
  }
  
  output_hist->SetFillColorAlpha(input_hist->GetLineColor(), 0.2);
  return output_hist;
}

void prepare_canvas(TCanvas *canvas){
  float T = 0.08;
  float B = 0.14;
  float L = 0.14;
  float R = 0.04;
  
  canvas->SetFillColor(0);
  canvas->SetBorderMode(0);
  canvas->SetFrameFillStyle(0);
  canvas->SetFrameBorderMode(0);
  canvas->SetLeftMargin( L );
  canvas->SetRightMargin( R );
  canvas->SetTopMargin( T );
  canvas->SetBottomMargin( B );
  canvas->SetTickx(0);
  canvas->SetTicky(0);
}

vector<TPad*> get_pads(){
  
  vector<TPad*> pads;
  
  double left_margin = 0.18;
  double right_margin = 0.1;
  
  auto pad_0 = new TPad("pad_0", "pad_0", 0.0, 0.25, 0.33, 1.00);
  pad_0->SetLeftMargin(left_margin);
  pad_0->SetBottomMargin(0);
  pad_0->SetRightMargin(right_margin);
  
  auto pad_1 = new TPad("pad_1", "pad_1", 0.0, 0.00, 0.33, 0.25);
  pad_1->SetLeftMargin(left_margin);
  pad_1->SetTopMargin(0);
  pad_1->SetBottomMargin(0.3);
  pad_1->SetRightMargin(right_margin);
  
  auto pad_2 = new TPad("pad_2", "pad_2", 0.33, 0.25, 0.66, 1.0);
  pad_2->SetLeftMargin(left_margin);
  pad_2->SetBottomMargin(0);
  pad_2->SetRightMargin(right_margin);
  
  auto pad_3 = new TPad("pad_3", "pad_3", 0.33, 0.00, 0.66, 0.25);
  pad_3->SetLeftMargin(left_margin);
  pad_3->SetTopMargin(0);
  pad_3->SetBottomMargin(0.3);
  pad_3->SetRightMargin(right_margin);
  
  auto pad_4 = new TPad("pad_4", "pad_4", 0.66, 0.25, 1.00, 1.0);
  pad_4->SetLeftMargin(left_margin);
  pad_4->SetBottomMargin(0);
  pad_4->SetRightMargin(right_margin);
  
  auto pad_5 = new TPad("pad_5", "pad_5", 0.66, 0.00, 1.00, 0.25);
  pad_5->SetLeftMargin(left_margin);
  pad_5->SetTopMargin(0);
  pad_5->SetBottomMargin(0.3);
  pad_5->SetRightMargin(right_margin);
  
  pads.push_back(pad_0);
  pads.push_back(pad_1);
  pads.push_back(pad_2);
  pads.push_back(pad_3);
  pads.push_back(pad_4);
  pads.push_back(pad_5);
  
  return pads;
}

TH1D* get_ratio(TH1D *hist_num, TH1D* hist_den){
  auto hist_ratio = (TH1D*)hist_num->Clone();
  hist_ratio->Divide(hist_den);
  
  hist_ratio->SetMinimum(0.5);
  hist_ratio->SetMaximum(1.5);
  
  hist_ratio->GetXaxis()->SetTitleFont(43);
  hist_ratio->GetXaxis()->SetTitleSize(20);
  hist_ratio->GetXaxis()->SetTitleOffset(4);
  hist_ratio->GetXaxis()->SetLabelFont(43);
  hist_ratio->GetXaxis()->SetLabelSize(20);
  
  hist_ratio->GetYaxis()->SetTitle("Ratio Data/MC");
  hist_ratio->GetYaxis()->SetTitleFont(43);
  hist_ratio->GetYaxis()->SetTitleSize(20);
  hist_ratio->GetYaxis()->SetTitleOffset(2);
  hist_ratio->GetYaxis()->SetLabelFont(43);
  hist_ratio->GetYaxis()->SetLabelSize(20);
  hist_ratio->GetYaxis()->SetNdivisions(5);
  
  hist_ratio->SetFillColorAlpha(kRed, 0.0);
  
  
  
  return hist_ratio;
}


void draw_ratios()
{
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2();
  gStyle->SetPadRightMargin(0.005);
  
  TFile *f1= new TFile(Form("unfolding_%s_histograms_%s.root", mc_name.c_str(), MethID1.c_str()),"r");
  
  TH1D *hist_pt_mc_gen          = (TH1D*)f1->Get("hGenPt_xSec");
  TH1D *hist_pt_data_unfolded   = (TH1D*)f1->Get("hUnfoDataPt_xSec");
  TH1D *hist_rapidity_mc_gen          = (TH1D*)f1->Get("hGenRap_xSec");
  TH1D *hist_rapidity_data_unfolded   = (TH1D*)f1->Get("hUnfoDataRap_xSec");
  TH1D *hist_invmass_mc_gen           = (TH1D*)f1->Get("hGenInvmass_xSec");
  TH1D *hist_invmass_data_unfolded    = (TH1D*)f1->Get("hUnfoDataInvmass_xSec");
  
  TLegend *legend = new TLegend(0.30, 0.68, 0.90, 0.9);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetTextFont(43);
  legend->SetTextSize(24);
  legend->AddEntry(hist_rapidity_data_unfolded,"Unfolded data (Bayes)","pl");
  legend->AddEntry(hist_rapidity_mc_gen, mc_name == "QEDSC" ? "Gen-level MC (Superchic)" : "Gen-level MC (Starlight)", "pl");
  
  
  TCanvas* canvas = new TCanvas("canvas","canvas", 50, 50, canvas_width, canvas_height);
//  prepare_canvas(canvas);
  
  vector<TPad*> pads = get_pads();
  
  // Pt
  string x_title = "p_{T}^{ee} (GeV)";
  string y_title = "d#sigma_{ee}/dp_{T}^{ee} (#mub / 0.05 GeV)";
  
  hist_pt_data_unfolded->SetMaximum(7000);
  hist_pt_data_unfolded->SetMinimum(1e-3);
  
  make_hist(hist_pt_data_unfolded, x_title, y_title, 20, 1.0, data_unfold_color, 1, 2);
  make_hist(hist_pt_mc_gen, x_title, y_title, 20, 1.0, mc_gen_color, 1, 2);
  
  auto hist_pt_data_unfolded_syst = get_stat_uncertainty_hist(hist_pt_data_unfolded);
  auto hist_pt_mc_gen_syst = get_stat_uncertainty_hist(hist_pt_mc_gen, syst_uncertainty_mc);
  
  canvas->cd();
  pads[0]->Draw();
  pads[0]->cd();
  pads[0]->SetLogy();
//  canvas->cd();
  hist_pt_data_unfolded_syst->Draw("e2");
  hist_pt_data_unfolded->Draw("psameex0");
  hist_pt_mc_gen_syst->Draw("e2same");
  hist_pt_mc_gen->Draw("histsamex0");
  
  hist_pt_data_unfolded_syst->GetXaxis()->SetRangeUser(0, 0.3);
  
  canvas->cd();
  pads[1]->Draw();
  pads[1]->cd();
  TH1D *hist_pt_ratio = get_ratio(hist_pt_data_unfolded, hist_pt_mc_gen);
  auto hist_pt_ratio_syst = get_stat_uncertainty_hist(hist_pt_ratio);
  
  hist_pt_ratio->Draw("pex0");
  hist_pt_ratio_syst->Draw("e2same");
  
  hist_pt_ratio->GetXaxis()->SetRangeUser(0, 0.3);
  
  auto line = new TF1("line", "1", -100, 100);
  line->SetLineColor(kBlack);
  line->SetLineStyle(2);
  line->DrawCopy("same");
  
  
  // Rapidity
  x_title = "|y_{#gamma#gamma}|";
  y_title = "d#sigma_{#gamma#gamma}/dy_{#gamma#gamma} (nb)";
  
  hist_rapidity_data_unfolded->SetMaximum(100);
  hist_rapidity_data_unfolded->SetMinimum(0);
  
  make_hist(hist_rapidity_data_unfolded, x_title, y_title, 20, 1.0, data_unfold_color, 1, 2);
  make_hist(hist_rapidity_mc_gen, x_title, y_title, 20, 1.0, mc_gen_color, 1, 2);
  
  auto hist_rapidity_data_unfolded_syst = get_stat_uncertainty_hist(hist_rapidity_data_unfolded);
  auto hist_rapidity_mc_gen_syst = get_stat_uncertainty_hist(hist_rapidity_mc_gen, syst_uncertainty_mc);
  
  canvas->cd();
  pads[2]->Draw();
  pads[2]->cd();
//  canvas->cd();
  hist_rapidity_data_unfolded_syst->Draw("e2");
  hist_rapidity_data_unfolded->Draw("psameex0");
  hist_rapidity_mc_gen_syst->Draw("e2same");
  hist_rapidity_mc_gen->Draw("histsamex0");
  
  canvas->cd();
  pads[3]->Draw();
  pads[3]->cd();
  TH1D *hist_rapidity_ratio = get_ratio(hist_rapidity_data_unfolded, hist_rapidity_mc_gen);
  auto hist_rapidity_ratio_syst = get_stat_uncertainty_hist(hist_rapidity_ratio);
  
  hist_rapidity_ratio->Draw("pex0");
  hist_rapidity_ratio_syst->Draw("e2same");
  
  line->DrawCopy("same");
  
  
  //invmass
  x_title = "m_{#gamma#gamma} (GeV)";
  y_title = "d#sigma_{#gamma#gamma}/dm_{#gamma#gamma} (nb / 2 GeV)";
  
  hist_invmass_data_unfolded->SetMaximum(50);
  hist_invmass_data_unfolded->SetMinimum(1e-4);
  
  make_hist(hist_invmass_data_unfolded, x_title, y_title, 20, 1.0, data_unfold_color, 1, 2);
  make_hist(hist_invmass_mc_gen, x_title, y_title, 20, 1.0, mc_gen_color, 1, 2);
  auto hist_invmass_data_unfolded_syst = get_stat_uncertainty_hist(hist_invmass_data_unfolded);
  auto hist_invmass_mc_gen_syst = get_stat_uncertainty_hist(hist_invmass_mc_gen, syst_uncertainty_mc);
  
  canvas->cd();
  pads[4]->Draw();
  pads[4]->cd();
  pads[4]->SetLogy();
  hist_invmass_data_unfolded_syst->Draw("e2");
  hist_invmass_data_unfolded->Draw("psameex0");
  hist_invmass_mc_gen_syst->Draw("e2same");
  hist_invmass_mc_gen->Draw("histsamex0");
  
  legend->Draw();
  
  canvas->cd();
  pads[5]->Draw();
  pads[5]->cd();
  TH1D *hist_invmass_ratio = get_ratio(hist_invmass_data_unfolded, hist_invmass_mc_gen);
  auto hist_invmass_ratio_syst = get_stat_uncertainty_hist(hist_invmass_ratio);
  hist_invmass_ratio->Draw("pex0");
  hist_invmass_ratio_syst->Draw("e2same");
  line->DrawCopy("same");
  
  //CMS_lumi( canvas_mass, 1, 10 );
  
  canvas->SaveAs(("./fig/dielectron_unfolding_ratios_"+mc_name+".pdf").c_str());
}

