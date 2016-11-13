#include <clocale>
#include "SortFile.h"

int main(int argc, char* argv[]) {
	if (argc == 3) {
		setlocale(LC_ALL, "");
		// You can change 512 to other number in Mb
		external_sort(argv[1], argv[2], 512 * 1024 * 1024);
		std::cout << "File succesfully sorted" << std::endl;
	}
	else if (argc == 4 && static_cast<std::string>(argv[1]) == "gen") {
		gen_file(static_cast<std::string>(argv[2]), std::stoul(static_cast<std::string>(argv[3])));
		std::cout << "File succesfully generated" << std::endl;
	}
	else {
		std::cout << "Input: external_sort.exe %input filename% %output_filename%" << std::endl;
		std::cout << "Or to generate random filled file: external_sort.exe gen %filename% %size in bytes%" << std::endl;
	}
	return 0;
}


