//  EventDisplay.hpp
//  Created by Jeremi Niedziela on 18/11/2019.

#ifndef EventDisplay_h
#define EventDisplay_h

const double trackerRadius = 1080;
const double B = 3.8;
const int nPoints = 2000;

pair<vector<double>, vector<double>> getTrackPoints(double pt, double phi, int charge)
{
  double radius = pt/(B*3)*10;
  double vx = charge *  radius*sin(phi);
  double vy = charge * -radius*cos(phi);
  
  double tShift=0;
  if(charge > 0) tShift = TMath::Pi() - atan2(-vx, vy);
  if(charge < 0) tShift = TMath::Pi() - atan2(-vy, vx);
  
  vector<double> pointsPhi;
  vector<double> pointsR;
  
  for(int iPoint=0; iPoint<nPoints; iPoint++){
    double t;
    if(charge > 0) t = -2*TMath::Pi() + iPoint*0.01 - tShift;
    else           t =  2*TMath::Pi() + iPoint*0.01 + tShift;
    
    double xp = radius*cos(t) + vx;
    double yp = radius*sin(t) + vy;
    
    double tp = atan2(yp, xp);
    double rp = sqrt(xp*xp + yp*yp);
    
    if(charge<0 && rp > trackerRadius) break;
    if(charge>0 && tp > 0) break;
    
    pointsPhi.push_back(tp);
    pointsR.push_back(rp);
  }

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
  double rPoints[2] = {trackerRadius, trackerRadius-20};

  auto grP1 = new TGraphPolar(2, phiPoints, rPoints);
  grP1->SetTitle("");
  grP1->SetMarkerStyle(21);
  grP1->SetMarkerSize(2.0);
  grP1->SetMarkerColor(kGreen);

  return grP1;
}

void saveEventDisplay(const shared_ptr<PhysObject> &matchingTrack,
                      const shared_ptr<PhysObject> &bremTrack,
                      const shared_ptr<PhysObject> &electron,
                      vector<shared_ptr<PhysObject>> &photons)
{
  static int iCanvas=0;
     
     auto matchedTrackGraph  = getTrackGraph(1000*matchingTrack->GetPt(), matchingTrack->GetPhi(), matchingTrack->GetCharge());
     auto bremTrackGraph     = getTrackGraph(1000*bremTrack->GetPt(), bremTrack->GetPhi(), bremTrack->GetCharge());
     auto electronGraph      = getTrackGraph(1000*electron->GetPt(), electron->GetPhi(), electron->GetCharge());
     
     if(matchedTrackGraph && bremTrackGraph && electronGraph){
       
       matchedTrackGraph->SetMarkerColor(kRed);
       matchedTrackGraph->SetMarkerStyle(20);
       bremTrackGraph->SetMarkerColor(kRed);
       bremTrackGraph->SetMarkerStyle(21);
       electronGraph->SetMarkerColor(kBlue);
       electronGraph->SetMarkerStyle(20);
       
       TCanvas *canvas = new TCanvas("c1","c1",800,600);
       canvas->cd();
       matchedTrackGraph->Draw("P");
       bremTrackGraph->Draw("Psame");
       electronGraph->Draw("Psame");
       
       for(auto photon : photons){
         auto photonGraph = getPhotonGraph(photon->GetPhi());
         photonGraph->Draw("Psame");
       }

       canvas->Update();
       matchedTrackGraph->SetMinRadial(0);
       matchedTrackGraph->SetMaxRadial(trackerRadius);
       matchedTrackGraph->GetPolargram()->SetToRadian();
       
       canvas->SaveAs(("~/Desktop/canv_"+to_string(iCanvas++)+".pdf").c_str());
     }
}

#endif /* EventDisplay_h */
