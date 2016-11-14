
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
	auto division()->void; // разделение файла на подфайлы
	auto file_size(string name_file)->size_t;//проверка размера файла
	auto make_file(string name_file)->void;//создание временных файлов
	auto file_sort()->void;//конечная сортировка временных файлов в выходной файл
	auto write_to_out(string line)->void;//запись в выходной файл
	auto remove_temp_files()->void;//удаление временных файлов
	~SortFile();
private:
	fstream file;
	size_t buffer, count_of_files, closed_files;
	bool out;
	vector<string> lines;
	vector<string> file_names;//имена временных файлов
};
