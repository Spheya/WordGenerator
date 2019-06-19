#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Generator.h"
#include <iterator>
#include <ctime>

int main(int argc, char **argv) {

	Generator gen(7);

	std::ifstream myfile("trainingData.txt");
	std::vector<std::string> names;
	std::copy(std::istream_iterator<std::string>(myfile),
		std::istream_iterator<std::string>(),
		std::back_inserter(names));

	srand(long(time(nullptr)));

	for (std::string& name : names)
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	gen.train(names);

	int word_count = (argc == 0) ? 29 : std::atoi(argv[0]);
	if (word_count < 1)
		word_count = 29;

	for (int i = 0; i < word_count; i++)
		std::cout << gen.nextNew() << std::endl;
	
	int pause;
	std::cin >> pause;
}
