#include <unistd.h>

#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>

#include "font.h"

// for (;;) {
//     for(unsigned int i = 0; i < 60; i++){
//         usleep(10000);
//         std::cout << font.paint_text("~", font.PURPLE) << std::flush;
//     }

//     // std::cout << "\b\b\b\b\b\b      " << std::flush;

//     for(unsigned int i = 0; i < 60; i++){
//         usleep(10000);
//         std::cout << "\b \b" << std::flush;
//     }
// }

// TODO:
//        [] bootstrapping build pipeline
//        [] clang-tidy
//        [] adding unit test suite
//        [] handle the IDX files
//        [] neural network
//        [] teaching
//        [] testing
//        [] summary of the nn results
//        [] error logging
//        [] documentation

void LeakyReLU(float &x) {
  /// Implementation of the Leaky ReLU activation function.
  /// https://en.wikipedia.org/wiki/Rectifier_(neural_networks)#Leaky_ReLU

  if (x < 0) {
    x *= 0.01;
  }
}

void usage() {
  std::cout << "Usage:\n"
            << "\tsomething something";  // TODO
}

// int main(int argc, char **argv) {
int main() {
  // using Matrix = Eigen::MatrixXd;

  // Eigen::MatrixXd m(2,2);
  // m(0,0) = 3;
  // m(1,0) = 2.5;
  // m(0,1) = -1;
  // m(1,1) = m(1,0) + m(0,1);
  // std::cout << m << std::endl;

  Eigen::MatrixXd m1(2, 2);

  m1 << 3, 2.5, -1, 4;

  std::cout << m1 << std::endl;

  // ------------------------------------------------------------
  // // Init font colorization
  // Font font;

  // std::cout << std::endl
  //           << Font::paint_text("Initializing application",
  //                               Font::BOLD + Font::CYAN)
  //           << std::endl
  //           << std::endl;
  // ------------------------------------------------------------

  // Matrix m1;

  // m1 <<  3, 2.5,
  //      -1, 4;

  // Matrix m2;

  // m2 <<  1, 2,
  //        3, 4;

  // Matrix m3;

  // m3 = m1*m2;

  // // std::vector<int> t {3,2,1};

  // // for(auto i : t) {
  // //     std::cout << i << std::endl;
  // // }

  // // m(0,0) = 3;
  // // m(1,0) = 2.5;
  // // m(0,1) = -1;
  // // m(1,1) = m(1,0) + m(0,1);

  // std::cout << m1 << std::endl;
  // std::cout << std::endl;
  // std::cout << m2 << std::endl;
  // std::cout << std::endl;
  // std::cout << m3 << std::endl;

  return 0;
}