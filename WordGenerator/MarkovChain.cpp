#include "MarkovChain.h"

namespace {

	std::string getKey(const std::string& str, size_t index, unsigned order) {
		assert(order > 0);

		std::string key;
		size_t start;
		size_t size;

		if (index < order - 1) {
			key = std::string(order - index - 1, '\2');
			start = 0;
			size = index + 1;
		}
		else {
			start = index - order + 1;
			size = order;
		}

		key += str.substr(start, size);

		return key;
	}

}

MarkovChain::MarkovChain(unsigned order) :
	m_order(order)
{}

void MarkovChain::train(const std::vector<std::string>& trainingData) {
	for(const std::string& str : trainingData)
		train(str);
}

void MarkovChain::train(std::string data) {
	// Add starting character
	m_connections[std::string(1, '\2')].add(data[0], 1.0f);

	// Add characters
	for(size_t i = 0; i < data.size() - 1; i++)
		m_connections[getKey(data, i, m_order)].add(data[i+1], 1.0f);

	// Add ending character
	m_connections[getKey(data, data.size()-1, m_order)].add('\0', 1.0f);
}


std::string MarkovChain::next() {
	std::string generated;
	char nextChar = m_connections["\2"].getRandom();

	do {
		generated += nextChar;
		nextChar = m_connections[getKey(generated, generated.size()-1, m_order)].getRandom();
	} while (nextChar != '\0');

	return generated;
}
