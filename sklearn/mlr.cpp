// SWAMI KARUPPASWAMI THUNNAI

#include "mlr.h"
#include "matrix.h"


void LinearRegression::print(std::string message)
{
	if (verbose) std::cout << message << "\n";
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
