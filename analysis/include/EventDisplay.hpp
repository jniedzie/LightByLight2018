//  EventDisplay.hpp
//  Created by Jeremi Niedziela on 18/11/2019.

#ifndef EventDisplay_h
#define EventDisplay_h

const double trackerRadius = 1080;
const double B = 3.8;
const int nPoints = 2000;

pair<vector<double>, vector<double>> getTrackPoints(double pt, double phi, int charge)
{
  while(phi < 0)              phi += 2*TMath::Pi();
  while(phi > 2*TMath::Pi())  phi -= 2*TMath::Pi();
  
  double radius = pt/(B*3)*10;
  double vx = charge *  radius*sin(phi);
  double vy = charge * -radius*cos(phi);
  double tShift = charge * TMath::Pi()/2. + phi;
  
  vector<double> pointsR, pointsPhi;
  
  auto fillRphi = [&](double t)->bool{
    double xp =  radius * cos(t) + vx;
    double yp =  radius * sin(t) + vy;
          
    double tp = atan2(yp, xp);
    double rp = sqrt(xp*xp + yp*yp);
    
    if(rp > trackerRadius) return true;
    
    pointsPhi.push_back(tp);
    pointsR.push_back(rp);
    
    return false;
  };
  
  if(charge > 0) for(double t = tShift; t > -(2*TMath::Pi()+tShift); t -= 0.01){ if(fillRphi(t)) break; }
  else           for(double t = tShift; t <  (2*TMath::Pi()+tShift); t += 0.01){ if(fillRphi(t)) break; }

  return make_pair(pointsPhi, pointsR);
}

TGraphPolar* getTrackGraph(double pt, double phi, int charge)
{
  auto phiR = getTrackPoints(pt, phi, charge);
  vector<double> phiVec = phiR.first;
  vector<double> rVec = phiR.second;
  
  if(phiVec.size()==0) return nullptr;
  
  double phiPoints[nPoints];
  double rPoints[nPoints];
  
  for(int i=0; i<nPoints; i++){
    phiPoints[i] = phiVec[i];
    rPoints[i] = rVec[i];
  }
  
  auto grP1 = new TGraphPolar((int)phiVec.size(), phiPoints, rPoints);
  grP1->SetTitle("");
  grP1->SetMarkerStyle(20);
  grP1->SetMarkerSize(0.5);
  grP1->SetMarkerColor(4);
  return grP1;
}

TGraphPolar* getPhotonGraph(double phi)
{
  double phiPoints[2] = {phi, phi};
  double rPoints[2] = {trackerRadius, trackerRadius};

  auto grP1 = new TGraphPolar(2, phiPoints, rPoints);
  grP1->SetTitle("");
  grP1->SetMarkerStyle(21);
  grP1->SetMarkerSize(2.0);
  grP1->SetMarkerColor(kGreen);

  return grP1;
}

void saveEventDisplay(PhysObjects &matchingTracks,
                      PhysObjects &bremTracks,
                      PhysObjects &electrons,
                      PhysObjects &goodPhotons,
                      PhysObjects &allPhotons,
                      string basePath, int maxEvents=-1)
{
  static int iCanvas=0;
  if(maxEvents > 0 && iCanvas > maxEvents) return;
  
  TLegend *leg = new TLegend(0.8, 0.8, 1.0, 1.0);
  TCanvas *canvas = new TCanvas("c1","c1",800,600);
  canvas->cd();
  
  bool first = true;
  
  for(auto matchingTrack : matchingTracks){
    auto matchedTrackGraph  = getTrackGraph(1000*matchingTrack->GetPt(), matchingTrack->GetPhi(), matchingTrack->GetCharge());
    matchedTrackGraph->SetMarkerColor(kRed);
    matchedTrackGraph->SetMarkerStyle(20);
//    matchedTrackGraph->SetMarkerSize(1.0);
    matchedTrackGraph->Draw(first ? "P" : "Psame");
    if(first){
      leg->AddEntry(matchedTrackGraph , "Matched tracks" , "p");
      canvas->Update();
      matchedTrackGraph->SetMinRadial(0);
      matchedTrackGraph->SetMaxRadial(trackerRadius);
      matchedTrackGraph->GetPolargram()->SetToRadian();
    }
    first = false;
  }
  first = true;
  for(auto bremTrack : bremTracks){
    auto bremTrackGraph = getTrackGraph(1000*bremTrack->GetPt(), bremTrack->GetPhi(), bremTrack->GetCharge());
    bremTrackGraph->SetMarkerColor(kViolet);
    bremTrackGraph->SetMarkerStyle(21);
    if(first) leg->AddEntry(bremTrackGraph, "Brem tracks", "p");
    bremTrackGraph->Draw("Psame");
    first = false;
  }
  first = true;
  for(auto electron : electrons){
    auto electronGraph = getTrackGraph(1000*electron->GetPt(), electron->GetPhi(), electron->GetCharge());
    electronGraph->SetMarkerColor(kBlue);
    electronGraph->SetMarkerStyle(20);
    electronGraph->Draw("Psame");
    if(first) leg->AddEntry(electronGraph, "Good matched electrons", "p");
    first = false;
  }
    
  first = true;
  for(auto photon : allPhotons){
    auto photonGraph = getPhotonGraph(photon->GetPhi());
    photonGraph->SetMarkerColor(kCyan);
    photonGraph->Draw("Psame");
    if(first) leg->AddEntry(photonGraph, "All photons", "p");
    first = false;
  }
  
  first = true;
  for(auto photon : goodPhotons){
    auto photonGraph = getPhotonGraph(photon->GetPhi());
    photonGraph->Draw("Psame");
    if(first){
      leg->AddEntry(photonGraph, "Good photons", "p");
      canvas->Update();
      photonGraph->SetMinRadial(0);
      photonGraph->SetMaxRadial(trackerRadius);
      photonGraph->GetPolargram()->SetToRadian();
    }
    first = false;
  }
  
  leg->Draw();
    
  canvas->Update();
  int randInt = static_cast<int>(rand())/(static_cast<int>(RAND_MAX/(1000000)));
  canvas->SaveAs((basePath+"/event_"+to_string(randInt)+".pdf").c_str());
  
  iCanvas++;
}

#endif /* EventDisplay_h */
