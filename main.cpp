#include <iostream>
#include <string>
#include <vector>
#include <valarray>

#include "io.h"


int main()
{
    std::string filename = "alpha_quartz_18.xyz";
    double rc = 1.8;
    double rc2 = rc * rc;

    std::vector<std::valarray<double> > particles;
    std::vector<std::string> species;
    read_xyz(filename, particles, species);
    std::size_t npar = particles.size();


    std::vector<int> topology1;
    std::vector<int> topology2;

    for (std::size_t i=0; i<npar; i++) {
        for (std::size_t j=0; j<npar; j++) {
            std::valarray<double> rij = particles[i] - particles[j];
            if (species[i] != species[j] && rij[0]*rij[0]+rij[1]*rij[1]+rij[2]*rij[2] < rc2) {
                topology1.push_back(i);
                topology2.push_back(j);
                std::cout << i << " " << j << std::endl;
            }
        }
    }

    write_ngph("topology.ngph", topology1, topology2);

    return 0;
}
