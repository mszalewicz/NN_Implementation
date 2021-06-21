#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include <Eigen/Dense>

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

  if (x < 0)
    x *= 0.01;
}

// void usage() {

// }

int main() {

  Font font;

  using Matrix = Eigen::MatrixXd;

  std::string a = "test";

  std::cout << std::endl
            << font.paint_text("Initializing application",
                               font.BOLD + font.CYAN)
            << std::endl
            << std::endl;

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