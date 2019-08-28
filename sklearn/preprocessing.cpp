// SWAMI KARUPPASWAMI THUNNAI

#include "preprocessing.h"

template<typename T>
inline void LabelEncoder<T>::fit()
{
	unsigned long int index = 0;
	std::set<T> unique_labels;
	for (T i : label_vector)
	{
		unique_labels.insert(i);
	}

	for (T i : unique_labels)
	{
		headers[i] = index;
		index++;
	}
}


template<typename T>
void LabelEncoder<T>::transform()
{
	for (T i : label_vector)
	{
		if (headers.find(i) == headers.end()) throw "Transform Error: feature value not found!";
		encoded_vector.push_back(headers[i]);
	}
}


template<typename T>
std::vector<unsigned long int> LabelEncoder<T>::fit_transorm()
{
	fit();
	transform();
	return encoded_vector;
}

template class LabelEncoder<std::string>;
template class LabelEncoder<std::wstring>;