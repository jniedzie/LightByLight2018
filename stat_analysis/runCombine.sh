#!/bin/bash

# Calculates limits in the asymptotic approximation, for each mass point separately

## uncomment for limits without systematic uncertainties
statonly="--freezeParameters all"
## uncomment for limits including systematic uncertainties
# statonly=""

#suffix=""
#suffix="_3p0"
#suffix="_4p0"
#suffix="_4p5"
suffix="_old"

#alpMasses=( 5 6 9 11 14 16 22 30 50 90 )
alpMasses=( 0 1 2 3 4 5 6 7 8 9 )

for i in "${alpMasses[@]}"
do
  echo "processing mass: ${i} GeV"
  echo "combine -M AsymptoticLimits datacards/datacard_axion_${i}GeV${suffix}.txt ${statonly}"
  combine -M AsymptoticLimits datacards/datacard_axion_${i}GeV${suffix}.txt ${statonly}
done
