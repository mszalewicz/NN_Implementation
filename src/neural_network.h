#pragma once

class NeuralNetwork
{
	private:
		Matrix input;
		Matrix layer_1;
		Matrix y;
		Matrix weights_1;
		Matrix weights_2;
		Matrix output_layer;

	public:
		NeuralNetwork(Matrix x_input, Matrix y_input, int height_of_hidden_layer);

		void static LeakyReLU(double &x);
		void static LeakyReLU_derivative(double &x);
		void static sigmoid(double &x);
		void static sigmoid_derivative(double &x);

		void feed_forward();
		void back_propagation();

		void apply_piecewise(Matrix &m, void (*func)(double&));

		Matrix transpose(Matrix &m);
		Matrix matrix_piecewise_multiplication(Matrix &m1, Matrix &m2);
		Matrix seed_normal_random_values_into_matrix(int rows, int columns);
};