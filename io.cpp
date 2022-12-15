#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <valarray>
#include <iterator>
#include <cassert>

#include "io.h"

/* ----------------------------------------------------------------------------
   Split string 's' by whitespace.
---------------------------------------------------------------------------- */

std::vector<std::string> split(const std::string &s)
{
    std::stringstream ss(s);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    return vstrings;
}


/* ----------------------------------------------------------------------------
   Read xyz-file 'filename' consisting of one time frame into vector of
   particle objects.
---------------------------------------------------------------------------- */

void read_xyz(const std::string &filename, std::vector<std::valarray<double> > &particles, std::vector<std::string> &species, const std::size_t dim)
{
    std::size_t i, line_num;  //npar;
    std::string line;
    std::ifstream f(filename);

    line_num = 0;  //npar = 0;
    if (f.is_open()) {
        while (std::getline(f, line))
        {
            if (line_num == 0) {
                // line containing number of particles
                //npar = std::stoi(line);
            }
            else if (line_num == 1) {
                // ignore info line
                line_num ++;
                continue;
            }
            else { 
                // coordinate line
                std::vector<std::string> splitted = split(line);
                if (line_num == 2) {
                    // count number of dimensions
                    std::size_t ndim = splitted.size() - 1;
                }
                std::valarray<double> tmp_r(dim);
                for (i=0; i<dim; i++) {
                    tmp_r[i] = std::stod(splitted[i+1]);
                }
                species.push_back(splitted[0]);
                particles.push_back(tmp_r);
            }
            line_num ++;
        }
    }
    else {
        std::cout << "Could not open file '" + filename + "'! Aborting." << std::endl;
        exit(0);
    }
    //return particles;
}


void write_ngph(const std::string &filename, const std::vector<int> &topology1, const std::vector<int> &topology2)
{
    assert (topology1.size() == topology2.size());
    std::size_t ntop = topology1.size();

    std::ofstream f(filename);
    
    f << "@NGPH" << std::endl;
    f << std::to_string(ntop) << std::endl;
    for (std::size_t i=0; i<ntop; i++)
    {
        f << std::to_string(topology1[i]) << " " << std::to_string(topology2[i]) << std::endl;
    }
    f << std::to_string(-1) << " " << std::to_string(-1) << std::endl;

    f.close();
}
