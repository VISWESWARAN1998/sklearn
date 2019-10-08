// SWAMI KARUPPASWAMI THUNNAI

#pragma once

#include "mlr.h"
#include <set>
#include <map>

class logistic_regression
{
private:
	std::vector<std::vector<double>> X;
	std::vector<unsigned long int> y;
	unsigned short int verbose;

	// Unique labels
	std::set<unsigned long int> unique_lables;

	// Bias variables
	std::map<unsigned long int, std::vector<double>>  bias_map;
private:
	void get_unique_labels();
public:
	logistic_regression(std::vector<std::vector<double>> X, std::vector<unsigned long int> y, unsigned short int verbose): X(X), y(y), verbose(verbose) {}
	logistic_regression(std::string model_name);
	void fit();
	std::map<unsigned long int, double> predict(std::vector<double> test);
	void save_model(std::string model_name);
};

