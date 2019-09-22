// SWAMI KARUPPASWAMI THUNNAI

#include "mlr.h"
#include "matrix.h"


void LinearRegression::print(std::string message)
{
	if (verbose) std::cout << message << "\n";
}

void LinearRegression::fit()
{
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
	print("Found");
}
