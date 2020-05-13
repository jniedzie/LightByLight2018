#!/bin/bash

# Calculates limits in the asymptotic approximation, for each mass point separately

## uncomment for limits without systematic uncertainties
statonly="--freezeParameters all"
## uncomment for limits including systematic uncertainties
# statonly=""

alpMasses=( 5 6 9 11 14 16 22 30 50 90 )

for i in "${alpMasses[@]}"
do
  echo "processing mass: ${i} GeV"
  combine -M AsymptoticLimits datacard_ged_hinvmass_axion${i}.txt ${statonly}
done
