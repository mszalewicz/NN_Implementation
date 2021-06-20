#include <cmath>
#include <vector>
#include <iostream>
#include <Eigen/Dense>

int main() {

    // using Matrix = Eigen::MatrixXd;

    // Matrix m2 = Matrix::Random(3,3);

    Eigen::Matrix2d m1;
    
    m1 <<  3, 2.5,
         -1, 4;

    Eigen::Matrix2d m2;

    m2 <<  1, 2,
           3, 4;

    Eigen::Matrix2d m3;

    m3 = m1*m2;

    // std::vector<int> t {3,2,1};

    // for(auto i : t) {
    //     std::cout << i << std::endl;
    // }

    // m(0,0) = 3;
    // m(1,0) = 2.5;
    // m(0,1) = -1;
    // m(1,1) = m(1,0) + m(0,1);

    std::cout << m1 << std::endl;
    std::cout << std::endl;
    std::cout << m2 << std::endl;
    std::cout << std::endl;
    std::cout << m3 << std::endl;
    
    return 0;
}