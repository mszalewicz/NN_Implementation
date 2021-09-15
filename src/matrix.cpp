#include <cmath>
#include <iostream>
#include <vector>

#include "matrix.h"

Matrix::Matrix()
{
	const int default_number_of_rows = 1;
	const int default_number_of_columns = 1;

	this->values = std::vector<std::vector<double>>(default_number_of_rows, std::vector<double>(default_number_of_columns, 0));
}

Matrix::Matrix(int rows, int columns)
{
	this->number_of_rows = rows;
	this->number_of_columns = columns;
	this->values = std::vector<std::vector<double>>(number_of_rows, std::vector<double>(number_of_columns, 0));
}

Matrix::Matrix(std::vector<std::vector<double>> values_to_insert)
{
	this->number_of_rows = values_to_insert.size();
	this->number_of_columns = values_to_insert[0].size();
	this->values = values_to_insert;
}

void Matrix::print_me()
{
	std::cout << "\n";

	for(auto row : this->values)
	{
		for(auto cell : row)
		{
			std::cout << cell << " ";
		}		
		std::cout << "\n";
	}

	std::cout << "\n";
}

void Matrix::round()
{
	for (auto i = 0; i < this->number_of_rows; ++i)
		for(auto j = 0; j < this->number_of_columns; ++j)
		{
			this->values[i][j] = std::round(this->values[i][j]);
		}
}

void Matrix::choose_most_probable()
{
	int best_position = 0;
	double best_value = 0;

	for (auto i = 0; i < this->number_of_rows; ++i)
	{
		for(auto j = 0; j < this->number_of_columns; ++j)
		{
			if(this->values[i][j] > best_value)
			{
				best_value = this->values[i][j];
				best_position = j;
			}
			this->values[i][j] = 0;
		}

		this->values[i][best_position] = 1;
		best_value = 0;	
	}
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

Matrix operator*(const Matrix m1, double scalar)
{
	Matrix result_of_operation = Matrix(m1.number_of_rows, m1.number_of_columns);

	for (auto i = 0; i < m1.values.size(); ++i)
		for (auto j = 0; j < m1.values[0].size(); ++j)
		{
			result_of_operation.values[i][j] = m1.values[i][j] * scalar; 
		}

	return result_of_operation;
}

Matrix operator*(double scalar, const Matrix m1)
{
	Matrix result_of_operation = Matrix(m1.number_of_rows, m1.number_of_columns);

	for (auto i = 0; i < m1.values.size(); ++i)
		for (auto j = 0; j < m1.values[0].size(); ++j)
		{
			result_of_operation.values[i][j] = m1.values[i][j] * scalar; 
		}

	return result_of_operation;
}

Matrix operator-(const Matrix &m1, const Matrix &m2)
{
	int number_of_rows_m1 = m1.values.size();
	int number_of_columns_m1 = m1.values[0].size();

	Matrix result_of_operation = Matrix(number_of_rows_m1, number_of_columns_m1);

	for (auto i = 0; i < number_of_rows_m1; ++i)
		for (auto j = 0; j < number_of_columns_m1; ++j)
		{
			result_of_operation.values[i][j] = m1.values[i][j] - m2.values[i][j]; 
		}

	return result_of_operation;
}
