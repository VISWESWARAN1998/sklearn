// SWAMI KARUPPASWAMI THUNNAI

#include "naive_bayes.h"

void naive_bayes::print(std::string message)
{
	if (verbose == DEBUG)
	{
		std::cout << message << "\n";
	}
}

void naive_bayes::calculate_y_probabilities()
{
	print("Calculating probabilities for the all the labels of y");
	std::set<unsigned long int> unique_labels;
	for (unsigned long int i : y)
	{
		unique_labels.insert(i);
	}
	
	unsigned long int toatal_labels = y.size();

	// Calculate the probabilities for all the unique labels
	print("Calculating probabilities of labels");
	for (unsigned long int i : unique_labels)
	{
		double p = std::count(y.begin(), y.end(), i) / double(toatal_labels);
		y_prob[i] = p;
	}
	print("Calculated probabilities of labels");
}

void naive_bayes::calculate_x_probabilities()
{
	print("Calculating independent variable proabilities");
	unsigned long int total_features = X[0].size();
	for (unsigned long int column = 0; column < total_features; column++)
	{
		// Get the seperate column
		std::stringstream stream;
		stream << "Computing probabilities for feature vector number: " << column + 1;
		print(stream.str());
		std::vector<double> feature_vector;
		for (std::vector<double> row : X)
		{
			feature_vector.push_back(row[column]);
		}
		// Get the unique labels
		print("Getting unique labels");
		std::set<double> unique_labels;
		for (double feature : feature_vector)
		{
			unique_labels.insert(feature);
		}
	}
	print("Calculated probabilities!");
}

void naive_bayes::fit()
{
	calculate_y_probabilities();
	calculate_x_probabilities();
}
