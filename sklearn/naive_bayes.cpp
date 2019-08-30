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
		// Our feature vector
		std::vector<double> feature_vector;
		// Our feature probabilities
		std::vector<__feature_row> feature_probabilities;
		for (std::vector<double> row : X)
		{
			feature_vector.push_back(row[column]);
		}
		// Get the unique labels
		print("Getting unique labels");
		std::set<double> unique_labels_col;
		for (double feature : feature_vector)
		{
			unique_labels_col.insert(feature);
		}

		print("Preparing feature rows");
		for (double feature_value : unique_labels_col)
		{
			unsigned long int neg_feature_count = feature_vector.size() - std::count(feature_vector.begin(), feature_vector.end(), feature_value);
			for (unsigned long int label : labels)
			{
				__feature_row row(feature_value, neg_feature_count, label, 0);
				feature_probabilities.push_back(row);
			}
		}

		for (unsigned long int i=0; i<y.size(); i++)
		{
			double feature_value = feature_vector[i];
			unsigned long int y_value = y[i];
			// std::cout << "X=" << feature_value << " y=" << y_value << "\n";
			for (unsigned long int row = 0; row< feature_probabilities.size(); row++)
			{
				__feature_row object = feature_probabilities[row];
				if ((object.get_feature_value() == feature_value) && (object.get_y_value() == y_value))
				{
					object.increment_rows_matched();
					feature_probabilities[row] = object;
				}
			}
		}

		// Compute probabilities
		for (unsigned long int row = 0; row < feature_probabilities.size(); row++)
		{
			__feature_row object = feature_probabilities[row];
			double p = object.get_rows_matched() / double(y.size());
			object.set_p(p);
			feature_probabilities[row] = object;
		}

		X_probabilities[column] = feature_probabilities;

		if (DEBUG)
		{
			for (__feature_row row : feature_probabilities)
			{
				std::cout << "X:" << row.get_feature_value() << " y:" << row.get_y_value() << " matched:" << row.get_rows_matched() << " neg:" << row.get_neg_feature_count() << "\n";
			}
		}
	}
	print("Calculated probabilities!");
}

void naive_bayes::display_x_probabilities()
{
	std::map<unsigned long int, std::vector<__feature_row>>::iterator itr1 = X_probabilities.begin();
	std::map<unsigned long int, std::vector<__feature_row>>::iterator itr2 = X_probabilities.end();
	for (std::map<unsigned long int, std::vector<__feature_row>>::iterator itr = itr1; itr != itr2; ++itr)
	{
		std::cout << "COLUMN: ";
		std::cout << itr->first + 1;
		std::cout << "\n~~~~~~~~~~~~~~~~~~~\n";
		std::vector<__feature_row> _row = itr->second;
		for (__feature_row row : _row)
		{
			std::cout << "X:" << row.get_feature_value() << " y:" << row.get_y_value() << " matched:" << row.get_rows_matched() << " neg:" << row.get_neg_feature_count() << " probability(p): " << row.get_p() << "\n";
		}
	}
}

void naive_bayes::fit()
{
	calculate_y_probabilities();
	calculate_x_probabilities();
	if (DEBUG)
	{
		display_x_probabilities();
	}
}

double __feature_row::get_feature_value()
{
	return feature_value;
}

unsigned long int __feature_row::get_neg_feature_count()
{
	return neg_feature_count;
}

unsigned long int __feature_row::get_rows_matched()
{
	return rows_matched;
}

unsigned long int __feature_row::get_y_value()
{
	return y_value;
}

void __feature_row::increment_rows_matched()
{
	rows_matched = rows_matched + 1;
}

double __feature_row::get_p()
{
	return p;
}

void __feature_row::set_p(double _p)
{
	p = _p;
}
