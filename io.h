#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <valarray>


std::vector<std::string> split(const std::string &);
void read_xyz(const std::string &, std::vector<std::valarray<double> > &, std::vector<std::string> &, const std::size_t = 3);
void write_ngph(const std::string &, const std::vector<int> &, const std::vector<int> &);
