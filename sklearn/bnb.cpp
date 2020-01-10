// SWAMI KARUPPASWAMI THUNNAI

#include "bnb.h"
#include <sstream>
#include <bits/stdc++.h>
void bnb::print(std::string message)
{
	if (DEBUG) std::cout << message << "\n";
}

void bnb::get_unique_labels()
{
	print("Getting unqiue labels...");
	for (unsigned long int i : y)
	{
		unique_labels.insert(i);
	}
	if (DEBUG)
	{
		std::cout << unique_labels.size() << " unique lables found\n";
	}
}

void bnb::get_probabilities_of_y()
{
	print("Getting probabilities of y...");
	unsigned long int y_size = y.size();
	std::map<unsigned long int, unsigned long int> label_count;
	for (unsigned long int label : unique_labels)
	{
		label_count[label] = 0;
	}

	for (unsigned long int i : y)
	{
		label_count[i]++;
	}

	std::map<unsigned long int, unsigned long int>::iterator itr1 = label_count.begin();
	std::map<unsigned long int, unsigned long int>::iterator itr2 = label_count.end();
	for (std::map<unsigned long int, unsigned long int>::iterator itr = itr1; itr != itr2; ++itr)
	{
		y_prob[itr->first] = itr->second / double(y.size());
		std::stringstream stream;
		stream << "p(" << itr->first << ") = " << y_prob[itr->first];
		print(stream.str());
	}
}

void bnb::update_icl_count(unsigned long int X_val, unsigned long int y_val, std::vector<__individual_column_label_count>& icl)
{
	for (unsigned long int i = 0; i < icl.size(); i++)
	{
		__individual_column_label_count icl_count = icl[i];
		if ((icl_count.get_column_value() == X_val) && (icl_count.get_label_value() == y_val))
		{
			icl_count.increment_count();
			icl[i] = icl_count;
		}
	}
}

/*void bnb::calculate_X_prob()
{
	for (unsigned long int label : unique_labels)
	{
		double p = y_prob[label];
		if (p == 0) p = 1;
		std::cout << "p = " << p << "\n";
		std::map<unsigned long int, std::vector<__Xi_probability>>::iterator itr1 = individual_probability.begin();
		std::map<unsigned long int, std::vector<__Xi_probability>>::iterator itr2 = individual_probability.end();
		for (std::map<unsigned long int, std::vector<__Xi_probability>>::iterator itr = itr1; itr != itr2; ++itr)
		{
			std::vector<__Xi_probability> Xp = itr->second;
			for (__Xi_probability probability : Xp)
			{
				if (probability.get_y() == label)
				{
					if (probability.get_p() != 0)
					{
						p *= probability.get_p();
						std::cout << "p = " << p << "\n";
					}
				}
			}
		}
		X_prob[label] = p;
	}
	if (DEBUG)
	{
		for (auto i : X_prob)
		{
			std::cout << "P(X|" << i.first << ")*P(" << i.first << ") = " << i.second << "\n";
		}
	}
}*/

void bnb::get_column_probability(unsigned long int column_index)
{
	// Contains the column itself
	std::vector<unsigned long int> column_vector;
	// Contains only the unique values of the column
	std::set<unsigned long int> unique_column_values;
	
	for (std::vector<unsigned long int> i : X)
	{
		column_vector.push_back(i[column_index]);
		unique_column_values.insert(i[column_index]);
	}

	std::vector<__individual_column_label_count> icl_count;

	for (unsigned long int i : unique_column_values)
	{
		for (unsigned long int j : unique_labels)
		{
			__individual_column_label_count count(i, j, 0);
			icl_count.push_back(count);
		}
	}

	for (unsigned long int j = 0; j < column_vector.size(); j++)
	{
		unsigned long int X_val = column_vector[j];
		unsigned long int y_val = y[j];
		//std::cout << "Updating for X " << X_val << " and y " << y_val << "\n";
		update_icl_count(X_val, y_val, icl_count);
	}

	std::vector<__Xi_probability> xi_prob;

	// After individual col value count is found
	for (__individual_column_label_count i : icl_count)
	{
		unsigned long int X_val = i.get_column_value();
		unsigned long int y_val = i.get_label_value();
		unsigned long int count = i.get_count();
		double total_count = std::count(y.begin(), y.end(), y_val);
		//std::cout << X_val << " - " << y_val << " - " << count << " - " << total_count <<  "\n";
		double p = count / total_count;
		__Xi_probability x(X_val, y_val, p);
		xi_prob.push_back(x);
		std::stringstream stream;
		stream << "Col: " << column_index << " for " << i.get_column_value() << " and " << i.get_label_value() << " p(" << X_val << "/" << y_val << ")= " << count << "/" << total_count << " which is " << p;
		print(stream.str());
	}

	individual_probability[column_index] = xi_prob;
}

void bnb::get_indiviudual_probabilities()
{
	// Get the probabilities for each features in the dataset
	for (unsigned long int column_index = 0; column_index < X[0].size(); column_index++)
	{
		get_column_probability(column_index);
	}
}

void bnb::fit()
{
	// Get the unique lables of y
	get_unique_labels();
	// Then find the probabilities of each unique variables
	get_probabilities_of_y();
	// Getting the individual probabilities
	get_indiviudual_probabilities();
}

std::map<unsigned long int, double> bnb::predict(std::vector<unsigned long int> test)
{
	std::map<unsigned long int, double> prediction;
	for (unsigned long int label : unique_labels)
	{
		prediction[label] = y_prob[label];
	}
	// Check the below method
	for (unsigned long int i=0; i<test.size(); i++)
	{
		unsigned long int X_val = test[i];
		std::vector<__Xi_probability> p = individual_probability[i];
		for (__Xi_probability j : p)
		{
			if (j.get_X() == X_val)
			{
				std::cout << X_val << " matches " << j.get_X() << " and y " << j.get_y() << " and p " << j.get_p() << "\n";
				prediction[j.get_y()] *= j.get_p();
			}
		}
	}
	double total = 0.0;
	for (auto i: prediction)
	{
		total += i.second;
	}
	for (auto i : prediction)
	{
		// std::cout << i.first << " -- " << i.second << "\n";
		prediction[i.first] = i.second / total;
	}
	return prediction;
}
