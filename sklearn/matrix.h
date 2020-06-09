// SWAMI KARUPPASWAMI THUNNAI

#pragma once
#include <iostream>
#include <vector>
#include <typeinfo>

template <typename T>
class matrix
{
public:
	std::vector<std::vector<T>> add(std::vector<std::vector<T>> mat1, std::vector<std::vector<T>> mat2)
	{
		std::vector<std::vector<T>> added_matrix;
		for (unsigned long int i = 0; i < mat1.size(); i++)
		{
			std::vector<T> row_mat1 = mat1[i];
			std::vector<T> row_mat2 = mat2[i];
			std::vector<T> result;
			if (row_mat1.size() != row_mat2.size()) throw "Matix size mismatch. Matrix additions can be performed only on matrices of same dimensions.";
			for (unsigned long int j = 0; j < row_mat1.size(); j++)
			{
				result.push_back(row_mat1[j] + row_mat2[j]);
			}
			added_matrix.push_back(result);
		}
		return added_matrix;
	}


	std::vector<std::vector<T>> transpose(std::vector<std::vector<T>> matrix)
	{
		std::vector<std::vector<T>> inverse_matrix(matrix[0].size(), std::vector<T>());
		for (unsigned long int i = 0; i < matrix.size(); i++)
		{
			for (unsigned long int j = 0; j < matrix[i].size(); j++)
			{
				inverse_matrix[j].push_back(matrix[i][j]);
			}
		}
		return inverse_matrix;
	}

	std::vector<std::vector<T>> mul(std::vector<std::vector<T>> mat1, std::vector<std::vector<T>> mat2)
	{
		std::vector<std::vector<T>> mat_mul;
		unsigned long int r1 = mat1.size();
		if (r1 == 0) throw "Matrix - 1 Trying to multiply empty matrices!";
		unsigned long int c1 = mat1[0].size();
		unsigned long int r2 = mat2.size();
		if (r2 == 0) throw "Matrix - 2 Trying to multiply empty matrices!";
		unsigned long int c2 = mat2[0].size();
		// Initialize with empty matrix
		//std::cout << "C1 " << c1 << " r2 " << r2 << "\n";
		for (unsigned long int i = 0; i < mat1.size(); i++)
		{
			std::vector<T> row;
			for (unsigned long int j = 0; j < mat2[0].size(); j++)
			{
				row.push_back(0);
			}
			mat_mul.push_back(row);
		}
		for (unsigned long int i = 0; i < r1; i++)
		{
			for (unsigned long int j = 0; j < c2; j++)
			{
				for (unsigned long int k = 0; k < r2; k++)
				{
					mat_mul[i][j] += mat1[i][k] * mat2[k][j];
				}
			}
		}
		return mat_mul;
	}

	void scalar_multiply(T scalar_value, std::vector<std::vector<T>> &mat)
	{
		for (unsigned long int row = 0; row < mat.size(); row++)
		{
			for(unsigned long int column = 0; column < mat[row].size(); column++)
			{
				mat[row][column] = mat[row][column] * scalar_value;
			}
		}
	}

	void  getCofactor(std::vector<std::vector<T>> matrix, std::vector<std::vector<T>> &temp, int p, int q, int n)
	{
		int i = 0, j = 0;
		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < n; col++)
			{
				if (row != p && col != q)
				{
					temp[i][j++] = matrix[row][col];
					if (j == n - 1)
					{
						j = 0;
						i++;
					}
				}
			}
		}
	}

	void adjoint(std::vector<std::vector<T>> matrix, std::vector<std::vector<T>> &adj)
	{
		int matrixSize = matrix.size();

		if (matrixSize == 1)
		{
			adj[0][0] = 1;
		}

		// temp is used to store cofactors of matrix[][] 
		int sign = 1;

		int number_of_elements = matrixSize;
		//cout << number_of_elements;
		int default_value = 1;
		int number_of_rows = 0;

		if (matrix.size() > 0)
		{
			number_of_rows = matrix[0].size();
		}

		std::vector<T> defaultValues(number_of_rows, default_value);
		std::vector<std::vector<T>> temp(number_of_elements, defaultValues);


		for (int i = 0; i<matrixSize; i++)
		{
			for (int j = 0; j<matrixSize; j++)
			{
				// Get cofactor of matrix[i][j] 
				getCofactor(matrix, temp, i, j, matrixSize);

				// sign of adj[j][i] positive if sum of row 
				// and column indexes is even. 
				sign = ((i + j) % 2 == 0) ? 1 : -1;

				// Interchanging rows and columns to get the 
				// transpose of the cofactor matrix 
				adj[j][i] = (sign)*(determinantOfMatrix(temp, matrixSize - 1));
			}
		}

	}

	bool slowInverse(std::vector<std::vector<T>> matrix, std::vector<std::vector<T>> &inverse)
	{

		//std::vector<std::vector<T>> inverse;
		int matrixSize = matrix.size();
		// Find determinant of matrix[][] 
		double det = determinantOfMatrix(matrix, matrixSize);
		if (det == 0)
		{
			return false;
		}

		// Find adjoint 
		int number_of_elements = matrix.size();
		//cout << number_of_elements;
		int default_value = 1;
		int number_of_rows = 0;

		if (matrix.size() > 0)
		{
			number_of_rows = matrix[0].size();
		}

		std::vector<T> defaultValues(number_of_rows, default_value);
		std::vector<std::vector<T>> adj(number_of_elements, defaultValues);

		adjoint(matrix, adj);

		// Find Inverse using formula "inverse(matrix) = adj(matrix)/det(matrix)" 
		for (int i = 0; i<matrixSize; i++)
			for (int j = 0; j<matrixSize; j++)
				inverse[i][j] = adj[i][j] / det;

		return true;

	}

	bool inverse(std::vector<std::vector<T>> matrix, std::vector<std::vector<T>> &inverse)
	{		
		int matrixSize = matrix.size();
		// Find determinant of matrix[][] 
		double det = determinantOfMatrix(matrix, matrixSize);
		if (det == 0)
		{
			return false;
		}

		std::vector<std::vector<T>> augmented;
		for (int i = 0; i < matrixSize; i++)
		{
			std::vector<T> row;
			for (int j = 0; j < 2 * matrixSize; j++)
				row.push_back(T());
			augmented.push_back(row);
		}
		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
				augmented[i][j] = matrix[i][j];

			augmented[i][i + matrixSize] = T(1);
		}
		
		for (int i = matrixSize - 1; i > 0; i--) 
		{
			if (augmented[i - 1][0] < augmented[i][0])
			{
				for (int j = 0; j < 2 * matrixSize; j++)
				{
					T temp = augmented[i][j];
					augmented[i][j] = augmented[i - 1][j];
					augmented[i - 1][j] = temp;
				}
			}
		}

		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				if (j != i) 
				{
					T temp = augmented[j][i] / augmented[i][i];
					for (int k = 0; k < 2 * matrixSize; k++) 
					{
						augmented[j][k] -= augmented[i][k] * temp;
					}
				}
			}
		}

		for (int i = 0; i < matrixSize; i++)
		{
			T temp = augmented[i][i];
			for (int j = 0; j < 2 * matrixSize; j++) 
			{
				augmented[i][j] = augmented[i][j] / temp;
			}
		}

		for (int i = 0; i < matrixSize; i++)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				inverse[i][j] = augmented[i][matrixSize + j];
			}
		}
	
		return true;

	}

	double determinantOfMatrix(std::vector<std::vector<T>> matrix, unsigned long int n)
	{
		double D = 0.0; 
		if (n == 1)
		{
			D = matrix[0][0];
			return D;
		}

		// Make L and U
		std::vector<std::vector<T>> L = matrix;
		std::vector<std::vector<T>> U = matrix;

		int i = 0, j = 0, k = 0;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (j < i)
					L[j][i] = 0;
				else {
					L[j][i] = matrix[j][i];
					for (k = 0; k < i; k++) {
						L[j][i] = L[j][i] - L[j][k] * U[k][i];
					}
				}
			}
			for (j = 0; j < n; j++) {
				if (j < i)
					U[i][j] = 0;
				else if (j == i)
					U[i][j] = 1;
				else {
					U[i][j] = matrix[i][j] / (L[i][i] == 0)? 1: L[i][i];
					for (k = 0; k < i; k++) {
						U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / (L[i][i] == 0)? 1: L[i][i]);
					}
				}
			}
		}
		
		D = 1.0;
		for (i = 0; i < n; i++) {
			D = D * U[i][i] * L[i][i];
		}
		
		return D;
	}

	double slowDeterminantOfMatrix(std::vector<std::vector<T>> matrix, unsigned long int n)
	{
		double D = 0.0;
		if (n == 1)
		{
			D = matrix[0][0];
			return D;
		}

		//int temp[matrixSize][matrixSize]; // To store cofactors 

		int sign = 1; // To store sign multiplier 

		int number_of_elements = matrix.size();
		//cout << number_of_elements;
		int default_value = 1;
		int number_of_rows = 0;

		if (matrix.size() > 0)
		{
			number_of_rows = matrix[0].size();
		}

		std::vector<T> defaultValues(number_of_rows, default_value);
		std::vector<std::vector<T>> temp(number_of_elements, defaultValues);

		for (int f = 0; f < n; f++)
		{
			getCofactor(matrix, temp, 0, f, n);

			D += sign * matrix[0][f] * slowDeterminantOfMatrix(temp, n - 1);
			sign = -sign;
		}
		return D;
	}
};

