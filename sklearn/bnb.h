// SWAMI KARUPPASWAMI THUNNAI

#pragma once
#define NODEBUG 0
#define DEBUG 1

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

class __individual_column_label_count
{
private:
	unsigned long int column_value;
	unsigned long int label_value;
	unsigned long int count;
public:
	__individual_column_label_count(unsigned long int column_value, unsigned long int label_value, unsigned long int count) : column_value(column_value), label_value(label_value), count(count) {}
	unsigned long int get_column_value()
	{
		return column_value;
	}

	unsigned long int get_label_value()
	{
		return label_value;
	}

	unsigned long int get_count()
	{
		return count;
	}

	void increment_count()
	{
		count++;
	}
};

class __Xi_probability
{
private:
	unsigned long int X_val;
	unsigned long int y_val;
	double p;
public:
	__Xi_probability(unsigned long int X_val, unsigned long int y_val, double p): X_val(X_val), y_val(y_val), p(p) {}

	unsigned long int get_X()
	{
		return X_val;
	}

	unsigned long int get_y()
	{
		return y_val;
	}

	double get_p()
	{
		return p;
	}
};

class bnb
{
private:
	// Independent variable
	std::vector<std::vector<unsigned long int>> X;
	
	// Dependent variable
	std::vector<unsigned long int> y;

	// print verbose message
	unsigned short int verbose;

	// Unique labels of y
	std::set<unsigned long int> unique_labels;

	// Probabilties of y
	std::map<unsigned long int, double> y_prob;

	// Individual probability
	std::map<unsigned long int, std::vector<__Xi_probability>> individual_probability;

	// X probability for labels/classes
	std::map<unsigned long int, double> X_prob;
private:
	void print(std::string message);

	void get_unique_labels();

	void get_probabilities_of_y();

	void get_indiviudual_probabilities();

	void get_column_probability(unsigned long int column_index);

	void update_icl_count(unsigned long int X_val, unsigned long int y_val, std::vector<__individual_column_label_count>& icl);

	/*void calculate_X_prob();*/
public:
	bnb(std::vector<std::vector<unsigned long int>> X, std::vector<unsigned long int> y, unsigned short int verbose) : X(X), y(y), verbose(verbose) {}
	void fit();
	std::map<unsigned long int, double> predict(std::vector<unsigned long int> test);
};

