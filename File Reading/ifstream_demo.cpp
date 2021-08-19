#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int main(int argc, char *argv[])
 {
 	//Check to make sure all files are included
	if(argc != 3)
	{
		std::cout << "2 text files are required. Quitting." << std::endl;
		return 0;
	}

	std::ifstream f1(argv[1]);
	std::ifstream f2(argv[2]);
	int counter = 1;

	while (!(f1.eof() && f2.eof())) {
		std::string reader1;
		std::string reader2;

		//Checks for empty string else read line from file
		if (f1.eof()) reader1 = "";
		else getline(f1, reader1);

		if (f2.eof()) reader2 = "";
		else getline(f2, reader2);

		//Run if lines are different
		if (reader1 != reader2) {
			std::cout << argv[1] << ": " << counter << ": " << reader1 << std::endl;
			std::cout << argv[2] << ": " << counter << ": " << reader2 << std::endl;

			int num = 0;
			//search each char in each line and incremement number
			while (reader1[num] == reader2[num]) {
				num++; 
			}

			//Find length to first different in 
			std::string space(strlen(argv[1]) + 2 + std::to_string(counter).length() + 2 + num, ' ');
			//output
			std::cout << space << "^" << std::endl;
		}

		counter++;
	}

	f1.close(); 
	f2.close();


}