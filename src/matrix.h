#pragma once

class Matrix
{
	/// Implements martices and their functionality
	public:
		unsigned int number_of_rows, number_of_columns;
		std::vector<std::vector<double>> values;

		Matrix();
		Matrix(int rows, int columns);
		Matrix(std::vector<std::vector<double>> values_to_insert);

		void round();
		void print_me();
		void choose_most_probable();
		
		friend Matrix operator*(const Matrix &m1, const Matrix &m2);
		friend Matrix operator*(const Matrix m1, double scalar);
		friend Matrix operator*(double scalar, const Matrix m1);
		friend Matrix operator-(const Matrix &m1, const Matrix &m2);
};