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
    auto sort()->void;
    auto out_file(string line)->void;
    auto remove_temp_files()->void;
    ~SortFile();
private:
    fstream file;
    size_t buffer, count_of_files, closed_files;
    bool out;
    vector<string> lines;
    vector<string> file_names;
};

