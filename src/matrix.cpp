#include <vector>

#include "matrix.h"

Matrix::Matrix(unsigned int rows, unsigned int columns)
{
	number_of_rows = rows;
	number_of_columns = columns;
	values = std::vector<std::vector<unsigned int>>(number_of_rows, std::vector<unsigned int>(number_of_columns, 0));
}

Matrix::Matrix(std::vector<std::vector<unsigned int>> values_to_insert)
{
	number_of_rows = values_to_insert.size();
	number_of_columns = values_to_insert[0].size();
	values = values_to_insert;
}

// Matrix multiplication
Matrix operator*(const Matrix &m1, const Matrix &m2)
{
	int number_of_rows_m1 = m1.values.size();
	int number_of_columns_m1 = m1.values[0].size();
	int number_of_columns_m2 = m2.values[0].size();

	Matrix result_of_operation = Matrix(number_of_rows_m1, number_of_columns_m2);

	for (auto i = 0; i < number_of_rows_m1; ++i)
		for(auto j = 0; j < number_of_columns_m2; ++j)
			for(auto k = 0; k < number_of_columns_m1; ++k)
			{
				result_of_operation.values[i][j] += m1.values[i][k] * m2.values[k][j];
			}

	return result_of_operation;
}

Matrix operator*(const Matrix &m1, unsigned int scalar)
{
	Matrix result_of_operation = Matrix(m1.number_of_rows, m1.number_of_columns);

	for (auto i = 0; i < m1.values.size(); ++i)
		for (auto j = 0; j < m1.values[0].size(); ++j)
		{
			result_of_operation.values[i][j] = m1.values[i][j] * scalar; 
		}

	return result_of_operation;
}