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
		for (unsigned long int i = 0; i < c1; i++)
		{
			std::vector<T> row;
			for (unsigned long int j = 0; j < r2; j++)
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
};

