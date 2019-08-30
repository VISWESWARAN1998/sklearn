// SWAMI KARUPPASWAMI THUNNAI

#pragma once
#define DEBUG 1
#define NODEBUG 0
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>


class naive_bayes
{

private:
	// Independent variable
	std::vector<std::vector<double>> X;
	// Dependent variable
	std::vector<unsigned long int> y;
	// Verbose to print debug messages
	unsigned short verbose;

	// Independent variable probabilities <features, probability>
	std::map<unsigned long int, std::map<double, double>> X_prob;

	// Dependent variable probabilities
	std::map<unsigned long int, double> y_prob;

private:
	void print(std::string message);

	void calculate_y_probabilities();
	void calculate_x_probabilities();

public:
	naive_bayes(std::vector<std::vector<double>> X, std::vector<unsigned long int> y, unsigned short verbose): X(X), y(y), verbose(verbose){}

	void fit();
};

