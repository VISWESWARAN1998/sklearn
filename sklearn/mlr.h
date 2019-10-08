// SWAMI KARUPPASWAMI THUNNAI

#pragma once
#define DEBUG 1
#define NODEBUG 0


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class LinearRegression
{
private:
	// Independent variable X
	std::vector<std::vector<double>> X;

	std::vector<double> y;

	std::vector<double> bias;

	unsigned short int verbose;
private:
	void print(std::string message);
	
public:
	LinearRegression(std::string model_name);
	LinearRegression(std::vector<std::vector<double>> X, std::vector<double> y, unsigned short int verbose) : X(X), y(y), verbose(verbose) {}
	void fit();
	double predict(std::vector<double> test);
	void save_model(std::string model_name);

	std::vector<double> get_bias();
};