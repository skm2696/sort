#include <iostream>
#include "SortFile.h"
#include <stdexcept>
#ifndef SORT_CPP
#define SORT_CPP
auto new_file(std::string file_name, uint_fast64_t file_size) -> void
{
	std::string names[] = { "Ivan", "Ann", "Ksusha", "Dima", "Kolya", "Anton", "Viktor", "Olga" };
	std::string surnames[] = { "Ivanov", "Petrov", "Sidorov",	"Tarasenko", "Sudarev", "Dmitriev",
	"Serebryakova", "Bushuev", "Fedorov", "Ionov", "Zinin" };
	std::ofstream file;
	file.open(file_name);
	if (file.good()) {
		while (file.tellp() < file_size) {
			file << names[rand() % 11].data() << " "
				<< surnames[rand() % 8].data() << " "
				<< 1950 + rand() % 2016 << std::endl;
		}
		file.close();
	}
	else {
		throw std::bad_exception();
	}
}

SortFile::SortFile(string name_main_file) :file(name_main_file), buffer(100), count_of_files(0), closed_files(0)
{
	if (file.is_open())
	{
		out = true;
		sort();
	}
};
auto SortFile::sort()->void
{
	string line_of_file;
	size_t temp_size_files = 0;
	while (!file.eof())
	{
		getline(file, line_of_file);
		temp_size_files += line_of_file.size();
		if (temp_size_files <= buffer)
		{
			lines.push_back(line_of_file);
		}
		else
		{
			count_of_files++;
			make_file(to_string(count_of_files) + ".txt");
			lines.push_back(line_of_file);
			temp_size_files = line_of_file.size();
		}
	}
	file.close();
	if (lines.size())
	{
		count_of_files++;
		make_file(to_string(count_of_files) + ".txt");
	}
	ifstream *files_streams = new ifstream[count_of_files];
	for (size_t i = 0; i < count_of_files; ++i)
	{
		files_streams[i].open(file_names[i]);
	}
	string *top_line = new string[count_of_files];
	for (size_t i = 0; i < count_of_files; ++i)
	{
		getline(files_streams[i], top_line[i]);
		map.insert(pair<string, size_t>(top_line[i], i));
	}
	while (out)
	{
		auto it = map.begin();
		out_file(it->first);
		if (!files_streams[it->second].eof())
		{
			getline(files_streams[it->second], top_line[it->second]);
		}
		else
		{
			closed_files++;
			if (closed_files == count_of_files) { out = false; };
		}
	}
	for (int i = 0; i<count_of_files; ++i) files_streams[i].close();
	remove_temp_files();
};
auto SortFile::make_file(string name_file)->void
{
	file_names.push_back(name_file);
	std::sort(lines.begin(), lines.end());
	ofstream temp(name_file);
	if (!temp.is_open())
		throw;
	for (auto i : lines)
	{
		temp << i;
		if (i != *(--lines.end()))
			temp << endl;
	}
	temp.close();
	lines.clear();
}
auto SortFile::file_size(string name_file)->size_t
{
	long fsize;
	ifstream temp(name_file);
	temp.seekg(0, ios::end);
	fsize = temp.tellg();
	temp.close();
	return fsize;
}
auto SortFile::out_file(string line)->void
{
	ofstream file("out.txt", ios::app);
	file << line << endl;
	file.close();
}
SortFile::~SortFile() {
	file_names.clear();
}

auto SortFile::remove_temp_files()->void
{
	for (int i = 0; i < file_names.size(); ++i)
	{
		if (remove(file_names[i].c_str()) == -1)
		{
			throw;
		}
		else
		{
			cout << "It's work";
		}
	}
}
/*int main()
{
	new_file("names.txt", 64);
	SortFile obj("names.txt");
	system("pause");
	return 0;
}*/
#endif
