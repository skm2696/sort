#include <iostream>
#include "SortFile.h"
#include <stdexcept>
#include <map> 
#include <iterator>
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
			file << surnames[rand() % 11].data() << " "
				<< names[rand() % 8].data() << " "
				<< 1950 + rand() % 2016 << std::endl;
		}
		file.close();
	}
	else {
		throw std::bad_exception();
	}
}

SortFile::~SortFile() {
	file_names.clear();
}

SortFile::SortFile(string name_main_file, size_t buf, string name_out_file) :file(name_main_file), buffer(buf*1024*1024), count_of_files(0), closed_files(0), str(name_out_file) {
	if (file.is_open()) {
		out = true;
		division();
	}
};

auto SortFile::make_file(string name_file)->void {
	file_names.push_back(name_file);
	std::sort(lines.begin(), lines.end());
	ofstream temp(name_file);
	for (auto i : lines)
	{
		temp << i;
		if (i != *(--lines.end())) temp << endl;
        }
        	/*for (size_t i = 0; i < lines.size(); i++)
	{
		if (i == lines.size() - 1)
		{
			temp << lines[i];
			continue;
		}
		temp << lines[i] << endl;
	}*/
        temp.close();
	lines.clear();
}

auto SortFile::file_size(string name_file)->size_t {
	long fsize;
	ifstream temp(name_file);
	temp.seekg(0, ios::end);
	fsize = temp.tellg();
	temp.close();
	return fsize;

}

auto SortFile::out_file(string line)->void {
	ofstream file(str, ios::app);
	file << line << endl;
	file.close();

}

auto SortFile::remove_temp_files()->void {
	for (int i = 0; i < file_names.size(); ++i) {
		if (remove(file_names[i].c_str()) == -1) {
			throw;
		}
		else {
			cout << "Gj";
		}
	}

}




auto SortFile::sort()->void {

	//Spair *sort = new Spair[count_of_files];
	ifstream *streams = new ifstream[count_of_files];
	string *top_line = new string[count_of_files];
	for (int i = 0; i < count_of_files; ++i) {
		streams[i].open(file_names[i]);
		getline(streams[i], top_line[i]);
		//sort[i].index = i;
		map.insert(pair<string,size_t>(top_line[i], i));
	}

	while (out) {
		auto it = map.begin();
		//int n = queue.top().index;
		int n = (*it).second;
		//out_file(queue.top().str);
		out_file((*it).first);
		if (!streams[n].eof()) {
			getline(streams[n], top_line[n]);
			//queue.pop();
			map.erase(map.begin());
			//queue.push(sort[n]);
			map.insert(pair<string, size_t>(top_line[n], n));
		}
		else {
			closed_files++;
			streams[n].close();
			map.erase(map.begin());

			if (closed_files == count_of_files) { out = false; };

		}
	}
	
}


auto SortFile::division()->void { 
	string line_of_file;
	size_t temp_size_files = 0;
	while (!file.eof()) {
		getline(file, line_of_file);
		temp_size_files += line_of_file.size();


		if (temp_size_files <= buffer) {
			lines.push_back(line_of_file);
		}
		else {
			count_of_files++;

			make_file(to_string(count_of_files) + ".txt");
			lines.push_back(line_of_file);
			temp_size_files = line_of_file.size();
		}
	}
	file.close();

	if (lines.size()) {
		count_of_files++;
		make_file(to_string(count_of_files) + ".txt");
	}


	sort();
};
/*int main()
{
	new_file("names.txt", 120);
	SortFile obj("names.txt");
	const int N = 256;
	char S[N] = { "" };
	ifstream in1("abcd.txt"); 
	while (!in1.eof()) 
	{
		in1.getline(S, N); 
		cout << S << endl; 
	}
	in1.close();  
	system("pause");
	return 0;
}*/
#endif
