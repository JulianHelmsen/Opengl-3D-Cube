#include "file_utils.h"
#include <stdio.h>



#include <string>
#include <fstream>

namespace utils {


	std::string read_file(const char* filepath) {
		FILE* file = NULL;
		fopen_s(&file, filepath, "r");

		if (!file)
			return "";

		char buffer[1024];
		
		
		std::string result;
		while(!feof(file)) {
			memset(buffer, 0, sizeof(buffer));
			fgets(buffer, sizeof(buffer) - 1, file);
			result += buffer;
		}

		
		return result;

	}

}