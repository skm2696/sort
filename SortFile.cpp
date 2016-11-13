#include "stdafx.h"
#include "SortFile.h"
extern void sortF(std::string const file_name, const std::string output_name, uint_fast64_t const memory_size) 
{
	auto size_of_file = file_size(file_name);
	data tmp;
	std::vector<data> data_to_sort;

	std::ifstream input(file_name);
	if (input.bad()) {
		throw std::bad_exception();
	}

	float_t pieces = size_of_file / memory_size;

	uint_fast64_t start_pos = input.tellg();
	uint_fast64_t current_pos = input.tellg();

	for (size_t i = 0; i < pieces; ++i) {
		std::ofstream temp_file;
		temp_file.open(to_string(i));
		if (input.good() && temp_file.good()) {
			while (current_pos - start_pos < memory_size) {
				input >> tmp.last_name >> tmp.first_name >> tmp.year;
				if (!input)
					break;
				data_to_sort.push_back(tmp);
				current_pos = input.tellg();
			}
			start_pos = input.tellg();
			auto by_last_name = [](const auto& a, const auto& b) { return a.last_name < b.last_name; };
			std::sort(data_to_sort.begin(), data_to_sort.end(), by_last_name);
			for (auto j : data_to_sort) {
				temp_file << j.last_name << " " << j.first_name << " " << j.year << std::endl;
			}
			data_to_sort.clear();
			temp_file.close();
		}
	}

	{
		std::ofstream _extra_file("extra.txt");
		_extra_file.close();
	}
	std::ifstream extra_file("extra.txt");

	while (pieces > 1) {
		size_t i;
		for (i = 1; i < pieces; i += 2) {
			std::cout << "Merging " << to_string(i - 1) << " and " << to_string(i) << " into " << to_string((i / 2) + 100) << std::endl;
			std::ifstream first_temp_file, second_temp_file;
			std::ofstream sorted;
			first_temp_file.open(to_string(i - 1));
			second_temp_file.open(to_string(i));
			sorted.open(to_string((i / 2) + 100));

			mergeF(first_temp_file, second_temp_file, sorted);

			first_temp_file.close();
			second_temp_file.close();
			sorted.close();

			std::remove(to_string(i - 1).c_str());
			std::remove(to_string(i).c_str());
			std::rename(to_string((i / 2) + 100).c_str(), to_string(i / 2).c_str());
			std::cout << "Renaming " << to_string((i / 2) + 100) << " into " << to_string(i / 2) << std::endl;
		}
		std::ifstream temp_file(to_string(i - 1));
		if (temp_file.is_open()) {
			std::cout << "Merging into extra file: " << to_string(i - 1) << std::endl;
			std::ofstream extra_temp_file("extra_temp.txt");
			mergeF(temp_file, extra_file, extra_temp_file);
			temp_file.close();
			extra_file.close();
			extra_temp_file.close();
			std::remove(to_string(i - 1).c_str());
			std::remove("extra.txt");
			std::rename("extra_temp.txt", "extra.txt");
			temp_file.open("extra.txt");
		}
		pieces = i / 2;
	}
	std::cout << "Final merging" << std::endl;
	std::ifstream result_file(to_string(0));
	std::ofstream sorted_file(output_name);
	mergeF(result_file, extra_file, sorted_file);
	result_file.close();
	extra_file.close();
	sorted_file.close();
	std::remove(to_string(0).c_str());
	std::remove("extra.txt");
}

extern uint_fast64_t file_size(const std::string filename)  
{
	std::ifstream file(filename.c_str(), std::ifstream::in | std::ifstream::binary);

	if (!file.is_open()) {
		throw std::bad_exception();
	}

	file.seekg(0, std::ios::end);
	uint_fast64_t size = file.tellg();
	file.close();

	return size;
}

extern void c_file(std::string file_name, uint_fast64_t file_size)
{
	std::string first_names[] = { "Dima", "Ann", "HGBI", "Jb", "NBLk", "KJnlk", "Jns", "Hnk" };
	std::string last_names[] = { "Jnkl", "Jpoijpo", "Llj",	"Nkns", "Nkhj;lk", "Jjkhbki",
		"Kkjh", "Ihakh", "IOoij[o", "Jjcsakn", "IKklhpoi" };
	std::ofstream file;
	file.open(file_name);
	if (file.good()) {
		while (file.tellp() < file_size) {
			file << last_names[rand() % 11].data() << " "
				<< first_names[rand() % 8].data() << " "
				<< 1950 + rand() % 2016 << std::endl;
		}
		file.close();
	}
	else {
		throw std::bad_exception();
	}
}

extern inline auto mergeF(std::ifstream & first_file, std::ifstream & second_file, std::ofstream & sorted) -> void {
	data temp1, temp2;
	if (sorted.good() && first_file.good() && second_file.good()) {
		first_file >> temp1.last_name >> temp1.first_name >> temp1.year;
		second_file >> temp2.last_name >> temp2.first_name >> temp2.year;
		while (first_file && second_file) {
			if (temp1.last_name < temp2.last_name) {
				sorted << temp1.last_name << " " << temp1.first_name << " " << temp1.year << std::endl;
				first_file >> temp1.last_name >> temp1.first_name >> temp1.year;
			}
			else {
				sorted << temp2.last_name << " " << temp2.first_name << " " << temp2.year << std::endl;
				second_file >> temp2.last_name >> temp2.first_name >> temp2.year;
			}
		}
		while (first_file) {
			first_file >> temp1.last_name >> temp1.first_name >> temp1.year;
			sorted << temp1.last_name << " " << temp1.first_name << " " << temp1.year << std::endl;
		}
		while (second_file) {
			second_file >> temp2.last_name >> temp2.first_name >> temp2.year;
			sorted << temp2.last_name << " " << temp2.first_name << " " << temp2.year << std::endl;
		}
	}
	else {
		throw std::bad_exception();
	}
}

extern inline auto to_string(size_t sz) -> std::string {
	std::stringstream ss;
	ss << sz << ".txt";

	return ss.str();
}
