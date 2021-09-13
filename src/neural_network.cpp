#include <chrono>
#include <cmath>
#include <random>

#include "matrix.h"
#include "neural_network.h"

NeuralNetwork::NeuralNetwork(Matrix x_input, Matrix y_input, int height_of_hidden_layer)
{
    // Height of the output layer (set specifically to this particular problem)
    constexpr auto number_of_output_classes = 10;

    this->input = x_input;
    this->y = y_input;
    this->weights_1 = seed_normal_random_values_into_matrix(this->input.number_of_columns, height_of_hidden_layer);
    this->weights_2 = seed_normal_random_values_into_matrix(height_of_hidden_layer, number_of_output_classes);
    this->output_layer = Matrix(this->y.number_of_rows, this->y.number_of_columns); // populated with zeros
}

void NeuralNetwork::feed_forward()
{
    this->layer_1 = this->input * this->weights_1;
    // apply_piecewise(this->layer_1, &NeuralNetwork::LeakyReLU); //TODO check which version is workin in:
    apply_piecewise(this->layer_1, &LeakyReLU);

    this->output_layer = this->layer_1 * this->weights_2;
    // apply_piecewise(this->output_layer, &NeuralNetwork::sigmoid); //TODO check which version is workin in:
    apply_piecewise(this->output_layer, &sigmoid);
}

void NeuralNetwork::back_propagation()
{
    constexpr auto learning_rate = 0.5;

    auto m = this->input.values.size();

    auto output_copy = this->output;
    sigmoid_derivative(output_copy);

    auto layer_1_copy = this->layer_1;
    LeakyReLU_derivative(layer_1_copy);

    //TODO Double check logic below

    auto derived_weights2 = -(1/m)*(transpose(this->layer_1)*matrix_piecewise_multiplication((this->y - this->output_layer), output_copy));
    auto derived_weights1 = -(1/m)*(transpose(this->input)*((matrix_piecewise_multiplication((this->y - this->output_layer), output_copy)*transpose(this->weights_2)), layer_1_copy));

    this->weights_2 = this->weights_2 - learning_rate * derived_weights2;
    this->weights_1 = this->weights_1 - learning_rate * derived_weights1; 
}

Matrix matrix_piecewise_multiplication(Matrix &m1, Matrix &m2)
{
    auto number_of_rows_m1 = m1.values.size();
    auto number_of_columns_m1 = m1.values[0].size();

    Matrix result_of_operation = Matrix(number_of_rows_m1, number_of_columns_m1);

    for (auto i = 0; i < number_of_rows_m1; ++i)
        for (auto j = 0; j < number_of_columns_m1.size(); ++j)
        {
            result_of_operation.values[i][j] = m1.values[i][j] * m2.values[i][j]; 
        }

    return result_of_operation;  
}

void NeuralNetwork::apply_piecewise(Matrix &m, void (*func)(double&))
{
    for(auto i = 0; i < m.values.size(); ++i)
        for(auto j = 0; j < m.values[0].size(); ++j)
        {
            func(m.values[i][j]);
        }
}

Matrix NeuralNetwork::transpose(Matrix &m)
{
    auto m_rows = m.values.size();
    auto m_columns = m.values[0].size();
    Matrix transposed_copy = Matrix(m_columns, m_rows);

    for(auto i = 0; i < m_rows; ++i)
        for(auto j = 0; j < m_columns; ++j)
        {
            transposed_copy.values[j][i] = m.values[i][j];
        }

    return transposed_copy;  
}

// One of the activation functions: https://en.wikipedia.org/wiki/Rectifier_(neural_networks)#Leaky_ReLU
void NeuralNetwork::LeakyReLU(double &x)
{
    constexpr auto kSlopeCoefficient = 0.01f;
    if (x < 0) { x *= kSlopeCoefficient; }
}

void NeuralNetwork::LeakyReLU_derivative(double &x)
{
    constexpr auto kSlopeCoefficient = 0.01f;
    if (x < 0) { x = kSlopeCoefficient; }
    else if(x > 0) { x = 1; }
}

// One of the activation functions: https://en.wikipedia.org/wiki/Sigmoid_function
void NeuralNetwork::sigmoid(double &x)
{
    x = 1 / (1 + std::exp(-x));
}

void NeuralNetwork::sigmoid_derivative(double &x)
{   
    auto x_copy = x;

    sigmoid(x_copy);

    x = x_copy * (1 - x_copy);
}

Matrix NeuralNetwork::seed_normal_random_values_into_matrix(int rows, int columns)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(0.0, 1.0);

    Matrix output_matrix = Matrix(rows, columns);

    for(auto i = 0; i < rows; ++i)
        for(auto j = 0; j < columns; ++j)
        {
            output_matrix.values[i][j] = distribution(generator);
        }

    return output_matrix;
}