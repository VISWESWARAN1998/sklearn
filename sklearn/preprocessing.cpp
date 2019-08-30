// SWAMI KARUPPASWAMI THUNNAI

#include "preprocessing.h"
#include "statx.h"

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

std::vector<double> StandardScaler::scale()
{
	mean<double> mean_object;
	u = mean_object.get_mean(array);
	standard_deviation<double> sd;
	s = sd.get_standard_deviation(array);
	std::vector<double> standardized_array;
	for (double x : array)
	{
		double z = (x - u) / s;
		standardized_array.push_back(z);
	}
	return standardized_array;
}

double StandardScaler::inverse_scale(double z)
{
	return (z * s) + u;
}

std::vector<double> preprocessing::normalize(std::vector<double> array)
{
	double min = *std::min_element(array.begin(), array.end());
	double max = *std::max_element(array.begin(), array.end());
	std::vector<double> normalized_array;
	for (double i : array)
	{
		normalized_array.push_back((i - min) / (max - min));
	}
	return normalized_array;
}
