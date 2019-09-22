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

template<typename T>
std::vector<std::vector<unsigned long int>> LabelBinarizer<T>::fit()
{
	// prepare the headers
	for (T value : data)
	{
		headers.insert(value);
	}

	for (T value : data)
	{
		std::vector<unsigned long int> feature_vector;
		for (T header : headers)
		{
			if (header == value) feature_vector.push_back(1);
			else feature_vector.push_back(0);
		}
		encoded_vector.push_back(feature_vector);
	}
	return encoded_vector;
}
template<typename T>
std::vector<unsigned long int> LabelBinarizer<T>::predict(T value)
{
	std::vector<unsigned long int> prediction;
	for (T header : headers)
	{
		if (header == value) prediction.push_back(1);
		else prediction.push_back(0);
	}
	return prediction;
}
template class LabelBinarizer<std::string>;
template class LabelBinarizer<std::wstring>;
