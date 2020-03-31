#!/bin/bash

for var in `cat varlist2.txt`; do
   # # histo declaration
   # echo "TH1F *h_"$var" = new TH1F(\"h_"$var"\",\""$var"\",1,0,1);"

   # # minmax declaration
   # echo "double min_"$var"(1e99), max_"$var"(-1e99), mean_"$var"(0);"

   # # what goes inside the loop
   # echo "if ("$var"->at(i) < min_"$var") min_$var = "$var"->at(i);"
   # echo "if ("$var"->at(i) > max_"$var") max_$var = "$var"->at(i);"
   # echo "mean_$var += "$var"->at(i);"
   # echo "h_"$var"->Fill("$var"->at(i));"

   # # compute mean
   # echo "if (h_"$var"->GetEntries() > 0) mean_"$var" = mean_"$var" / h_"$var"->GetEntries();"
   # echo "cout << \"TH1F *h_"$var" = new TH1F(\\\"h_"$var"\\\",\\\""$var"\\\",10,\" << min_"$var" << \",\" << max_"$var" << \"); // mean = \" << mean_"$var" << endl;"

   # draw histos
   echo "hlow = (TH1F*) tflow->Get(\"h_"$var"\");"
   echo "hlow->SetLineColor(kGreen+1);"
   echo "hlow->SetMarkerColor(kGreen+1);"
   echo "hlow->GetXaxis()->SetTitle(\""$var"\");"
   echo "hhigh = (TH1F*) tfhigh->Get(\"h_"$var"\");"
   echo "hhigh->SetLineColor(kRed+1);"
   echo "hhigh->SetMarkerColor(kRed+1);"
   echo "hhigh->GetXaxis()->SetTitle(\""$var"\");"
   echo "hlow->DrawNormalized(\"E\");"
   echo "hhigh->DrawNormalized(\"E same\");"
   echo "tleg->Draw();"
   echo "chi2 = hlow->Chi2TestX(hhigh,chi2,ndf,igood,\"UU\");"
   echo "prob = TMath::Prob(chi2,ndf);"
   echo "ksprob = hlow->KolmogorovTest(hhigh);"
   echo "pt = new TPaveText(0.3,0.8,0.7,0.9,\"NDC\");"
   echo "pt->SetBorderSize(0);"
   echo "pt->SetFillColor(0);"
   echo "pt->AddText(Form(\"#chi^{2}/ndf=%.2f/%d (%.1f%s), KS (%.1f%s)\",chi2,ndf,prob*100.,\"%\",ksprob*100,\"%\"));"
   echo "pt->Draw();"
   echo "c1->SaveAs(\"c_"$var".pdf\");"
   echo ""
done
