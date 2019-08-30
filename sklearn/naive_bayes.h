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


class __feature_row
{
private:
	double feature_value;
	unsigned long int neg_feature_count;
	unsigned long int y_value;
	unsigned long int rows_matched;
	double p;
public:
	__feature_row(double feature_value, unsigned long int neg_feature_count, unsigned long int y_value, unsigned long int rows_matched=0): feature_value(feature_value), neg_feature_count(neg_feature_count), y_value(y_value),rows_matched(rows_matched){}

	double get_feature_value();
	unsigned long int get_neg_feature_count();
	unsigned long int get_rows_matched();
	unsigned long int get_y_value();
	void increment_rows_matched();
	double get_p();
	void set_p(double _p);
};

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

	// Labels of y
	std::set<unsigned long int> labels;

	// Column probabilities
	std::map<unsigned long int, std::vector<__feature_row>> X_probabilities;

private:
	void print(std::string message);

	void calculate_y_probabilities();
	void calculate_x_probabilities();
	void display_x_probabilities();

public:
	naive_bayes(std::vector<std::vector<double>> X, std::vector<unsigned long int> y, unsigned short verbose): X(X), y(y), verbose(verbose){}

	void fit();
};

