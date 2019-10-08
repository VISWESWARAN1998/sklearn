// SWAMI KARUPPASWAMI THUNNAI

#include <iomanip>
#include <sstream>
#include "mlr.h"
#include "matrix.h"
#include "json.h"

using json = nlohmann::json;


void LinearRegression::print(std::string message)
{
	if (verbose) std::cout << message << "\n";
}

LinearRegression::LinearRegression(std::string model_name)
{
	std::ifstream file;
	file.open(model_name);
	if (!file.is_open()) throw "Model cannot be loaded because it cannot be opened!";
	json j;
	file >> j;
	file.close();
	std::vector<double> b = j["bias"];
	bias = b;
}

void LinearRegression::fit()
{
	// Adding bias to X
	for (unsigned long int i = 0; i < X.size(); i++)
	{
		std::vector<double> row;
		row.push_back(1);
		for (double j : X[i])
		{
			row.push_back(j);
		}
		X[i] = row;
	}

	// X'
	std::vector<std::vector<double>> X_transpose;

	// X'X
	std::vector<std::vector<double>> X_transpose_X;

	matrix<double> mat;

	print("Finding the transpose");
	X_transpose = mat.transpose(X);
	print("Finding X'X");
	X_transpose_X = mat.mul(X_transpose, X);
	print("Found!");
	std::vector<double> rows(X_transpose_X[0].size(), 1);
	// (X'X)-1
	std::vector<std::vector<double>> inverse_of_X_transpose_X(X_transpose_X.size(), rows);
	// find the inverse
	print("Finding (X'X)^-1");
	// Print the matrix shapes for debug messages
	std::stringstream s1;
	s1 << "Shape of X transpose X: " << X_transpose_X.size() << "," << X_transpose_X[0].size();
	print(s1.str());
	std::stringstream s2;
	s2 << "Shape of inverse of X transpose X: " << inverse_of_X_transpose_X.size() << "," << inverse_of_X_transpose_X[0].size();
	print(s2.str());
	mat.inverse(X_transpose_X, inverse_of_X_transpose_X);
	// Reshape y
	print("Reshaping y");
	std::vector<std::vector<double>> y_reshaped;
	for (double i : y)
	{
		std::vector<double> row;
		row.push_back(i);
		y_reshaped.push_back(row);
	}
	std::vector<std::vector<double>> X_transpose_y = mat.mul(X_transpose, y_reshaped);
	std::vector<std::vector<double>> b = mat.mul(inverse_of_X_transpose_X, X_transpose_y);
	for (std::vector<double> i : b)
	{
		bias.push_back(i[0]);
	}
	print("Found");
}

double LinearRegression::predict(std::vector<double> test)
{
	double prediction = 0.0;
	prediction += bias[0];
	for (unsigned long int i = 0; i < test.size(); i++)
	{
		double value = bias[i + 1] * test[i];
		prediction += value;
	}
	return prediction;
}

void LinearRegression::save_model(std::string model_name)
{
	json j;
	j["bias"] = bias;
	std::ofstream file;
	file.open(model_name);
	if (file.is_open())
	{
		file << std::setw(4) << j << std::endl;
		file.close();
	}
	else
	{
		throw "File cannot be opened for saving the model. May be the file is opened in some other place or you might not have proper permissions.";
	}
}

std::vector<double> LinearRegression::get_bias()
{
	return bias;
}
