// SWAMI KARUPPASWAMI THUNNAI

#pragma once

#define NODEBUG 0
#define DEBUG 1

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

/*
Implementation of simple linear regression or Least Squares Regression
Written By: Visweswaran N @ 2019-08-26
*/
class simple_linear_regression
{
private:
	// ~~~~~~~~~~~~~ PRIVATE VARIABLES ~~~~~~~~~~~~
	unsigned int N=0;

	// Independent and dependent variable
	std::vector<double> X;
	std::vector<double> y;

	// XX and Xy
	std::vector<double> XX;
	std::vector<double> Xy;

	// To print into console
	bool verbose;

	// Summation
	double sigma_X = 0.0;
	double sigma_y = 0.0;
	double sigma_XX = 0.0;
	double sigma_Xy = 0.0;

	// Slope
	double m = 0.0;

	// Bias (or) Intercept
	double b = 0.0;

	// ~~~~~~~~~~ Methods ~~~~~~~~~~~~~
	void print(std::string message);

	void calculate_N();

	void x_square();
	void x_cross_y();

	void calculate_sigma();

	void calculate_slope();

	void calculate_bias();
public:
	simple_linear_regression(std::string model_name);
	simple_linear_regression(std::vector<double> X, std::vector<double> y, unsigned short verbose);
	void fit();
	double predict(double _X);
	void save_model(std::string file_name);
};
