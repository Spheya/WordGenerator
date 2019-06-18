#pragma once
#include <string>
#include <unordered_map>

#include "WeightedVector.h"

class MarkovChain
{
public:
	MarkovChain(unsigned order);

	void train(const std::vector<std::string>& trainingData);
	void train(std::string data);

	std::string next();

private:
	unsigned m_order;

	std::unordered_map<std::string, WeightedVector<char>> m_connections;

	void countConnection(const std::string& from, char to);
};

