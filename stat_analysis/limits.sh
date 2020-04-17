#!/bin/bash

## uncomment for limits without systematic uncertainties
statonly="--freezeParameters all"
## uncomment for limits including systematic uncertainties
# statonly=""


############################################
## limits in the asymptotic approximation ##
############################################

# the limits are computed for each mass point separately

echo "##################"
echo "#  mass = 5 GeV  #"
echo "##################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion0.txt $statonly

echo "##################"
echo "#  mass = 6 GeV  #"
echo "##################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion1.txt $statonly

echo "##################"
echo "#  mass = 9 GeV  #"
echo "##################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion2.txt $statonly

echo "###################"
echo "#  mass = 11 GeV  #"
echo "###################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion3.txt $statonly

echo "###################"
echo "#  mass = 14 GeV  #"
echo "###################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion4.txt $statonly

echo "###################"
echo "#  mass = 16 GeV  #"
echo "###################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion5.txt $statonly

echo "###################"
echo "#  mass = 22 GeV  #"
echo "###################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion6.txt $statonly

echo "###################"
echo "#  mass = 30 GeV  #"
echo "###################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion7.txt $statonly

echo "###################"
echo "#  mass = 90 GeV  #"
echo "###################"

combine -M AsymptoticLimits datacard_ged_hinvmass_axion8.txt $statonly

# echo ""
# echo ""
# echo ""
# echo "################################"
# echo "# high mass with counting only #"
# echo "################################"
# echo ""
# echo ""
# echo ""

# echo "###################"
# echo "#  mass = 30 GeV  #"
# echo "###################"

# combine -M AsymptoticLimits datacard_ged_counting_axion_5.txt

# echo "###################"
# echo "#  mass = 90 GeV  #"
# echo "###################"

# combine -M AsymptoticLimits datacard_ged_counting_axion_6.txt
