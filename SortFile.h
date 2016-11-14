
#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <iterator>
#include <algorithm>
#include <cstdio>



using namespace std;

class SortFile 
{
public:
	SortFile(string name_main_file);
	auto division()->void; 
	auto file_size(string name_file)->size_t;
	auto make_file(string name_file)->void;
	auto file_sort()->void;
	auto write_to_out(string line)->void;
	auto remove_temp_files()->void;
	~SortFile();
private:
	fstream file;
	size_t buffer, count_of_files, closed_files;
	bool out;
	vector<string> lines;
	vector<string> file_names;//имена временных файлов
};
auto new_file(std::string file_name, uint_fast64_t file_size) -> void;
