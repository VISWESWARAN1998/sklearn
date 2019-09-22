// SWAMI KARUPPASWAMI THUNNAI

#pragma once
#include <vector>
#include <set>
#include <map>

/*
Label Encoder: Encodes the label A,B,C to 0,1,2
i.e converts the categorical data into numerical values.
Written By: Visweswaran N, 2019-08-28
*/
template <typename T>
class LabelEncoder
{
private:
	std::vector<T> label_vector;
	std::vector<unsigned long int> encoded_vector;
	std::map<T, unsigned long int> headers;

	void fit();
	void transform();

public:
	LabelEncoder(std::vector<T> label_vector) : label_vector(label_vector) {}

	std::vector<unsigned long int> fit_transorm();
};

/*
For standardization
-------------------

Formula:
	z = (x - u) / s

Varaible names:
~~~~~~~~~~~~~~~~~~~~~~
u = mean
s = standard deviation

Written By: Visweswaran N, 2019-08-29
*/
class StandardScaler
{
private:
	std::vector<double> array;
	double u, s;
public:
	StandardScaler(std::vector<double> array): array(array){}

	std::vector<double> scale();

	double inverse_scale(double z);
};

namespace preprocessing
{
	std::vector<double> normalize(std::vector<double> array);
}


template <typename T>
class LabelBinarizer
{
private:
	std::set<T> headers;
	std::vector<T> data;

	std::vector<std::vector<unsigned long int>> encoded_vector;

public:
	LabelBinarizer(std::vector<T> data): data(data){}
	std::vector<std::vector<unsigned long int>> fit();
	std::vector<unsigned long int> predict(T value);
};