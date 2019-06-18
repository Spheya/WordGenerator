#pragma once
#include <unordered_map>
#include "MarkovChain.h"

class Generator
{
public:
	explicit Generator(unsigned order);

	void train(std::vector<std::string> trainingData);
	void train(const std::string& data);

	// Generates a new name and returns it
	std::string next();

	// Generates a name which is not in the training data
	std::string nextNew();

private:
	std::unordered_map<std::string, bool> m_trainingData;

	MarkovChain m_chain;
};

