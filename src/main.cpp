#include <string>
#include <vector>
#include <iostream>
#include <Eigen/Dense>

// TODO:
// [] handle the IDX files 
// [] neural network
// [] teaching
// [] testing
// [] summary of the nn results
// [] error logging
// [] documentation

class FONT {
    public:
        std::string PURPLE = "\033[95m";
        std::string BLUE = "\033[94m";
        std::string CYAN = "\033[96m";
        std::string GREEN = "\033[92m";
        std::string YELLOW = "\033[93m";
        std::string RED = "\033[91m";
        std::string ENDC = "\033[0m";
        std::string BOLD = "\033[1m";
        std::string UNDERLINE = "\033[4m";

        std::string paint_text(std::string original_string, std::string color_name) {
            original_string.insert(0, color_name);
            original_string.append(this->ENDC);
            return original_string;
        }
} font;

void LeakyReLU(float& x) {
    /// Implementation of the Leaky ReLU activation function.
    /// https://en.wikipedia.org/wiki/Rectifier_(neural_networks)#Leaky_ReLU

    if(x < 0) x *= 0.01; 
}

int main() {

    using Matrix = Eigen::MatrixXd;
    
    std::string a = "test";

    std::cout << font.paint_text("test", font.YELLOW) << std::endl;




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