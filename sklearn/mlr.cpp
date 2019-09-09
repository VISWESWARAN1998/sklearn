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
}
