#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

template<typename T>
class WeightedVector {

public:
	void add(T element, float weight);

	T& getRandom();

	float size();

	T& operator [](float value);

private:
	std::vector<T> m_elements;
	std::vector<float> m_cummulativeWeights;
};

template <typename T>
void WeightedVector<T>::add(T element, float weight) {
	// Check if the vector already contains the element
	auto it = std::find(m_elements.begin(), m_elements.end(), element);
	if (it != m_elements.end()) {
		for (size_t i = it - m_elements.begin(); i < m_cummulativeWeights.size(); i++)
			m_cummulativeWeights[i] += weight;
		return;
	}

	// Add element to the vector
	m_elements.push_back(element);
	m_cummulativeWeights.push_back(weight + size());
}

template <typename T>
T& WeightedVector<T>::operator[](float value) {
	assert(value < size());
	assert(value >= 0.0f);

	return m_elements[std::upper_bound(m_cummulativeWeights.begin(), m_cummulativeWeights.end(), value, std::less<float>()) - m_cummulativeWeights.begin()];
}

template <typename T>
T& WeightedVector<T>::getRandom() {
	return (*this)[(float(rand()) / float((RAND_MAX-1)+ 1)) * size()];
}

template <typename T>
float WeightedVector<T>::size() {
	if (m_cummulativeWeights.empty())
		return 0.0f;

	return m_cummulativeWeights.back();
}
