
#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cmath>

struct data {
	std::string last_name;
	std::string first_name;
	size_t year;
};

void sortF(std::string const file_name, const std::string output_name, uint_fast64_t const memory_size);

uint_fast64_t file_size(const std::string filename);

void c_file(std::string file_name, uint_fast64_t file_size);

std::string to_string(size_t sz);

void mergeF(std::ifstream & first_file, std::ifstream & second_file, std::ofstream & sorted); 
