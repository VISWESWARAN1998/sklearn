// SWAMI KARUPPASWAMI THUNNAI

#include "naive_bayes.h"

void gaussian_naive_bayes::print(std::string message)
{
	if (verbose == DEBUG)
	{
		std::cout << message << "\n";
	}
}

void gaussian_naive_bayes::calculate_y_probabilities()
{
	print("Calculating probabilities for the all the labels of y");
	std::set<unsigned long int> unique_labels;
	for (unsigned long int i : y)
	{
		unique_labels.insert(i);
	}

	labels = unique_labels;
	
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

void gaussian_naive_bayes::calculate_x_probabilities()
{
	print("Calculating independent variable proabilities");
	unsigned long int total_features = X[0].size();
	for (unsigned long int column = 0; column < total_features; column++)
	{
		// Get the seperate column
		std::stringstream stream;
		stream << "Computing probabilities for feature vector number: " << column + 1;
		print(stream.str());
		// Our feature vector
		std::vector<double> feature_vector;
		for (std::vector<double> row : X)
		{
			feature_vector.push_back(row[column]);
		}
		
		print("Creating label map(s)");
		std::map<unsigned long int, std::vector<double>> label_map;

		for (unsigned long int label=0; label<y.size(); label++)
		{
			if (label_map.find(y[label]) == label_map.end())
			{
				std::vector<double> vec;
				vec.push_back(feature_vector[label]);
				label_map[y[label]] = vec;
			}
			else
			{
				std::vector<double> vec = label_map[y[label]];
				vec.push_back(feature_vector[label]);
				label_map[y[label]] = vec;
			}
		}

		print("Calculating mean and variance!");
		std::map<unsigned long int, std::vector<double>>::iterator itr1 = label_map.begin();
		std::map<unsigned long int, std::vector<double>>::iterator itr2 = label_map.end();
		for (std::map<unsigned long int, std::vector<double>>::iterator itr = itr1; itr != itr2; ++itr)
		{
			std::vector<double> vec = itr->second;
			double mean = 0.0;
			for (double value : vec) { mean += value; }
			mean = mean / double(vec.size());
			std::vector<double> variance_vector;
			for (double value : vec)
			{
				double Xi_mean = value - mean;
				variance_vector.push_back(Xi_mean*Xi_mean);
			}
			double variance = 0.0;
			for (double value : variance_vector) { variance += value; }
			variance = variance / double(variance_vector.size() - 1);
			if (mean_variance_map.find(itr->first) == mean_variance_map.end())
			{
				std::vector<mean_variance> vec;
				mean_variance mv(column, mean, variance);
				vec.push_back(mv);
				mean_variance_map[itr->first] = vec;
			}
			else
			{
				std::vector<mean_variance> vec = mean_variance_map[itr->first];
				mean_variance mv(column, mean, variance);
				vec.push_back(mv);
				mean_variance_map[itr->first] = vec;
			}
		}
	}
	print("Computed! Model has been trained!");
}


void gaussian_naive_bayes::fit()
{
	calculate_y_probabilities();
	calculate_x_probabilities();
	if (DEBUG)
	{
		std::map<unsigned long int, std::vector<mean_variance>>::iterator itr1 = mean_variance_map.begin();
		std::map<unsigned long int, std::vector<mean_variance>>::iterator itr2 = mean_variance_map.end();
		for (std::map<unsigned long int, std::vector<mean_variance>>::iterator itr = itr1; itr != itr2; ++itr)
		{
			std::cout << "LABEL: " << itr->first << "\n-------------------------------\n";
			std::vector<mean_variance> mv = itr->second;
			for (mean_variance i : mv)
			{
				std::cout << "COLUMN: " << i.get_column() << " MEAN: " << i.get_mean() << " VARIANCE: " << i.get_variance() << "\n";
			}
		}
	}
}

std::map<unsigned long int, double> gaussian_naive_bayes::predict(std::vector<double> X_test)
{
	std::map<unsigned long int, double> probability;
	std::map<unsigned long int, std::vector<mean_variance>>::iterator itr1 = mean_variance_map.begin();
	std::map<unsigned long int, std::vector<mean_variance>>::iterator itr2 = mean_variance_map.end();
	for (std::map<unsigned long int, std::vector<mean_variance>>::iterator itr = itr1; itr != itr2; ++itr)
	{
		std::vector<mean_variance> mv_vec = itr->second;
		std::vector<double> posterior_numerator;
		for (unsigned long int column = 0; column < X_test.size(); column++)
		{
			mean_variance mv = mv_vec[column];
			double column_value = X_test[column];
			// Calculate Gaussian Normal distribution
			double mean = mv.get_mean();
			double mean_square_by_two_sigma = std::pow((column_value - mean), 2) / (2 * mv.get_variance());
			double exp_neg_mean_square_by_sigma = std::exp(-1 * mean_square_by_two_sigma);
			double gnb = (1 / (sqrt(2 * PI * mv.get_variance()))) * exp_neg_mean_square_by_sigma;
			// std::cout << "COLUMN VALUE: " << column_value << " MEAN: " << mean << "  VARIANCE: " << mv.get_variance() << " GNB: " << gnb << "\n";
			posterior_numerator.push_back(gnb);
		}
		double p = 1;
		for (double numerator : posterior_numerator)
		{
			p = p * numerator;
		}
		probability[itr->first] = p;
	}
	return probability;
}

void gaussian_naive_bayes::save_model(std::string model_name)
{
	json j;
	j["labels"] = labels;
	std::map<unsigned long int, std::vector<mean_variance>>::iterator itr1 = mean_variance_map.begin();
	std::map<unsigned long int, std::vector<mean_variance>>::iterator itr2 = mean_variance_map.end();
	for (std::map<unsigned long int, std::vector<mean_variance>>::iterator itr = itr1; itr != itr2; ++itr)
	{
		std::string label_name = std::to_string(itr->first);
		j["mean_variance"][label_name] = json::array();
	}
	for (std::map<unsigned long int, std::vector<mean_variance>>::iterator itr = itr1; itr != itr2; ++itr)
	{
		std::string label_name = std::to_string(itr->first);
		std::vector<mean_variance> mv_vec = itr->second;
		for (mean_variance mv : mv_vec)
		{
			j["mean_variance"][label_name].push_back({ 
				{"column", mv.get_column()},
				{"mean", mv.get_mean()},
				{"variance", mv.get_variance()}
				});
		}
	}
	std::ofstream file(model_name);
	file << std::setw(4) << j << std::endl;
	file.close();
}

void gaussian_naive_bayes::load_model(std::string model_name)
{
	std::ifstream file;
	file.open(model_name);
	if (!file.is_open()) throw "Model cannot be loaded because it cannot be opened!";
	json j;
	file >> j;
	file.close();
	std::vector<unsigned long int> label_vector = j["labels"];
	for (unsigned long int label : label_vector)
	{
		std::vector<mean_variance> mv_vector;
		std::string label_name = std::to_string(label);
		for (json::iterator itr = j["mean_variance"][label_name].begin(); itr != j["mean_variance"][label_name].end(); ++itr)
		{
			json array =  *itr;
			mean_variance mv(array["column"], array["mean"], array["variance"]);
			mv_vector.push_back(mv);
		}
		mean_variance_map[label] = mv_vector;
	}
}
