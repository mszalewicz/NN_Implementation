#pragma once

class Matrix
{
	// private:
	// 	unsigned int number_of_rows, number_of_columns;
	// 	std::vector<std::vector<unsigned int>> values;

	public:
		unsigned int number_of_rows, number_of_columns;
		std::vector<std::vector<double>> values;

		Matrix();
		Matrix(int rows, int columns);
		Matrix(std::vector<std::vector<double>> values_to_insert);
		// ~Matrix();
		friend Matrix operator*(const Matrix &m1, const Matrix &m2);
		friend Matrix operator*(const Matrix &m1, double scalar);
};