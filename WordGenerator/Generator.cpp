#include "Generator.h"

Generator::Generator(unsigned order) :
	m_chain(order)
{}

void Generator::train(std::vector<std::string> trainingData) {
	for (const std::string& s : trainingData)
		m_trainingData[s] = false;

	m_chain.train(trainingData);
}

void Generator::train(const std::string& data) {
	m_trainingData[data] = false;
	m_chain.train(data);
}

std::string Generator::next() {
	return m_chain.next();
}

std::string Generator::nextNew() {
	std::string generated;

	do {
		generated = next();
	} while (m_trainingData.find(generated) != m_trainingData.end());

	return generated;
}