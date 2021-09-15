#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

#include "font.h"
#include "matrix.h"
#include "neural_network.h"

NeuralNetwork::NeuralNetwork(Matrix x_input, Matrix y_input, int height_of_hidden_layer)
{
    // Height of the output layer (set specifically to this particular problem)
    constexpr auto number_of_output_classes = 3;

    this->input = x_input;
    this->y = y_input;
    this->weights_1 = seed_normal_random_values(this->input.number_of_columns, height_of_hidden_layer);
    this->weights_2 = seed_normal_random_values(height_of_hidden_layer, number_of_output_classes);
    this->output_layer = Matrix(this->y.number_of_rows, this->y.number_of_columns); // populated with zeros
}

void NeuralNetwork::find_scales()
{
    std::vector<std::vector<double>> scales;

    auto number_of_rows_m = this->input.values.size();
    auto number_of_columns_m = this->input.values[0].size();


    // Calculating mean for each feature set
    double counter = 0;

    for(auto j = 0; j < number_of_columns_m; ++j)
    {
        for(auto i = 0; i < number_of_rows_m; ++i)
        {
            counter += this->input.values[i][j];
        }
        scales.push_back( {counter/number_of_rows_m, 0} );
        counter = 0;
    }

    // Calculating standard deviation for each feature set
    for(auto j = 0; j < number_of_columns_m; ++j)
    {
        for(auto i = 0; i < number_of_rows_m; ++i)
        {
            counter += std::pow((this->input.values[i][j] - scales[j][0]), 2);
        }
        scales[j][1] = std::sqrt(counter/(number_of_rows_m));
        counter = 0;
    }

    this->scaling_factors = scales;
}

void NeuralNetwork::scale_to_standard()
{   
    auto number_of_rows_m = this->input.values.size();
    auto number_of_columns_m = this->input.values[0].size();

    // Applying normalization per feature set
    for(auto i = 0; i < number_of_rows_m; ++i)
        for(auto j = 0; j < number_of_columns_m; ++j)
        {
            this->input.values[i][j] = (this->input.values[i][j] - this->scaling_factors[j][0]) / this->scaling_factors[j][0];    
        }
}

void NeuralNetwork::work(Matrix &x_test, Matrix &y_test, int number_of_epochs)
{
    auto train_number_of_entries = this->y.values.size();
    auto test_number_of_entries = y_test.values.size();
    double train_accuracy = 0;
    double test_accuracy = 0;
    double correct_predictions_train = 0;
    double correct_predictions_test = 0;

    for(auto i = 0; i < number_of_epochs; ++i)
    {
        // Starting epoch

        feed_forward();

        Matrix y_predict_train = this->output_layer;
        y_predict_train.choose_most_probable();

        Matrix y_predict_test = predict(x_test);
        y_predict_test.choose_most_probable();

        // Calculating the accuracies

        correct_predictions_train = 0;

        for(auto x = 0; x < train_number_of_entries; ++x)
        {
            if(y_predict_train.values[x] == this->y.values[x]) ++correct_predictions_train;
        }

        correct_predictions_test = 0;

        for(auto x = 0; x < test_number_of_entries; ++x)
        {
            if(y_predict_test.values[x] == y_test.values[x]) ++correct_predictions_test;
        }

        train_accuracy = correct_predictions_train/train_number_of_entries;
        test_accuracy = correct_predictions_test/test_number_of_entries;

        // Back propagation

        back_propagation();

        // Printing learning process data

        int width_of_print = (int) std::floor(std::log10(number_of_epochs));

        if(i > 0) Font::erase_n_lines(3);

        std::cout << std::setw(16) << "Epoch: " << std::setw(width_of_print) << i+1 << " / " << std::setw(width_of_print) << number_of_epochs << "\n"
                  << std::setw(16) << "Train Accuracy: " << std::round(train_accuracy * 100) << " %\n"
                  << std::setw(16) <<"Test Accuracy: " << std::round(test_accuracy * 100) << " %\n";
    }

    std::cout << "\n";
}

Matrix NeuralNetwork::predict(Matrix &x)
{
    Matrix prediction_layer_1 = x * this->weights_1;
    apply_piecewise(prediction_layer_1, &LeakyReLU);

    Matrix results = prediction_layer_1 * this->weights_2;
    apply_piecewise(results, &sigmoid);

    return results;
}

void NeuralNetwork::feed_forward()
{
    this->layer_1 = this->input * this->weights_1;
    apply_piecewise(this->layer_1, &LeakyReLU);

    this->output_layer = this->layer_1 * this->weights_2;
    apply_piecewise(this->output_layer, &sigmoid);
}

void NeuralNetwork::back_propagation()
{
    constexpr double learning_rate = 0.5;

    double m = this->input.values.size();

    auto output_copy = this->output_layer;
    apply_piecewise(output_copy, &sigmoid_derivative);


    auto layer_1_copy = this->layer_1;
    apply_piecewise(layer_1_copy, &LeakyReLU_derivative);

    auto derived_weights2 = -(1/m) 
                            
                            * 

                            (
                                transpose(this->layer_1) 

                                *

                                matrix_piecewise_multiplication(
                                                                    (this->y - this->output_layer), 
                                                                    output_copy
                                                               )
                             );

    auto derived_weights1 = -(1/m) 

                            * 

                            (
                                transpose(this->input) 

                                * 

                                matrix_piecewise_multiplication(
                                                                  (
                                                                      matrix_piecewise_multiplication((this->y - this->output_layer), output_copy)

                                                                      *

                                                                      transpose(this->weights_2)
                                                                  ), 
                                                                  layer_1_copy
                                                                )
                             );


    this->weights_2 = this->weights_2 - learning_rate * derived_weights2;
    this->weights_1 = this->weights_1 - learning_rate * derived_weights1;
}

Matrix NeuralNetwork::matrix_piecewise_multiplication(Matrix m1, Matrix m2)
{
    auto number_of_rows_m1 = m1.values.size();
    auto number_of_columns_m1 = m1.values[0].size();

    Matrix result_of_operation = Matrix(number_of_rows_m1, number_of_columns_m1);

    for (auto i = 0; i < number_of_rows_m1; ++i)
        for (auto j = 0; j < number_of_columns_m1; ++j)
        {
            result_of_operation.values[i][j] = m1.values[i][j] * m2.values[i][j]; 
        }

    return result_of_operation;  
}

void NeuralNetwork::apply_piecewise(Matrix &m, void (*func)(double&))
{
    auto number_of_rows_m = m.values.size();
    auto number_of_columns_m = m.values[0].size();

    for(auto i = 0; i < number_of_rows_m; ++i)
        for(auto j = 0; j < number_of_columns_m; ++j)
        {
            func(m.values[i][j]);
        }
}

Matrix NeuralNetwork::transpose(Matrix &m)
{
    auto number_of_rows_m = m.values.size();
    auto number_of_columns_m = m.values[0].size();
    Matrix transposed_copy = Matrix(number_of_columns_m, number_of_rows_m);

    for(auto i = 0; i < number_of_rows_m; ++i)
        for(auto j = 0; j < number_of_columns_m; ++j)
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

Matrix NeuralNetwork::seed_normal_random_values(int rows, int columns)
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