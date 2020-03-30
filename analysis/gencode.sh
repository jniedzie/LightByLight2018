#!/bin/bash

for var in `cat varlist.txt`; do
   # # histo declaration
   # echo "TH1F *h_"$var" = new TH1F(\"h_"$var"\",\""$var"\",1,0,1);"

   # # minmax declaration
   # echo "double min_"$var"(1e99), max_"$var"(-1e99), mean_"$var"(0);"

   # # what goes inside the loop
   # echo "if ("$var"->at(i) < min_"$var") min_$var = "$var"->at(i);"
   # echo "if ("$var"->at(i) > max_"$var") max_$var = "$var"->at(i);"
   # echo "mean_$var += "$var"->at(i);"
   # echo "h_"$var"->Fill("$var"->at(i));"

   # compute mean
   echo "if (h_"$var"->GetEntries() > 0) mean_"$var" = mean_"$var" / h_"$var"->GetEntries();"
   echo "cout << \"TH1F *h_"$var" = new TH1F(\\\"h_"$var"\\\",\\\""$var"\\\",10,\" << min_"$var" << \",\" << max_"$var" << \"); // mean = \" << mean_"$var" << endl;"
done
