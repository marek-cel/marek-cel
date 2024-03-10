#include <iostream>
#include <armadillo>

////////////////////////////////////////////////////////////////////////////////

void PressEnterToContinue();

void InitiatingMatrix();
void AccessingMatrix();
void MatrixOperations();
void SolveLinearEquastionsSystem();

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    std::cout << "Hello Armadillo" << std::endl;

    PressEnterToContinue();

    InitiatingMatrix();
    AccessingMatrix();
    MatrixOperations();
    SolveLinearEquastionsSystem();

    PressEnterToContinue();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void PressEnterToContinue()
{
    std::cout << "Press enter to continue..." << std::endl; 
    std::cin.ignore();
}

////////////////////////////////////////////////////////////////////////////////

void InitiatingMatrix()
{
    std::cout << ">>> Initiating Matrix..." << std::endl;
    PressEnterToContinue();

    constexpr int num_rows = 3;
    constexpr int num_cols = 3;

    arma::mat a(num_rows, num_cols, arma::fill::randu);
    std::cout << a << std::endl;
    PressEnterToContinue();

    a = arma::zeros<arma::mat>(num_rows, num_cols);
    std::cout << a << std::endl;
    PressEnterToContinue();

    a = arma::ones<arma::mat>(num_rows, num_cols);
    std::cout << a << std::endl;
    PressEnterToContinue();

    a << 1 << 2 << arma::endr
      << 3 << 4 << arma::endr;
    std::cout << a << std::endl;
    PressEnterToContinue();

    a.fill(M_PI);
    std::cout << a << std::endl;
    PressEnterToContinue();

    a = "1 2 3; 4 5 6; 7 8 9";
    std::cout << a << std::endl;
    PressEnterToContinue();

    double x[] = { 11, 12, 13,
                   21, 22, 23,
                   31, 32, 33 };
    a = arma::mat(x, 3, 3);
    std::cout << a << std::endl;
    PressEnterToContinue();
}

////////////////////////////////////////////////////////////////////////////////

void AccessingMatrix()
{
    std::cout << ">>> Accessing Matrix..." << std::endl;
    PressEnterToContinue();

    constexpr int num_rows = 3;
    constexpr int num_cols = 3;

    arma::mat a(num_rows, num_cols, arma::fill::zeros);

    a << 1 << 2 << 3 << arma::endr
      << 4 << 5 << 6 << arma::endr
      << 7 << 8 << 9 << arma::endr;

    std::cout << a(0,0) << "\t" << a(0,1) << "\t" << a(0,2) << std::endl;
    std::cout << a(1,0) << "\t" << a(1,1) << "\t" << a(1,2) << std::endl;
    std::cout << a(2,0) << "\t" << a(2,1) << "\t" << a(2,2) << std::endl;
    PressEnterToContinue();

    std::cout << a.diag(0) << std::endl;
    std::cout << a.diag(1) << std::endl;
    std::cout << a.diag(-1) << std::endl;
    PressEnterToContinue();

    std::cout << "Rows= " << a.n_rows << std::endl;
    std::cout << "Columns= " << a.n_cols << std::endl;
    std::cout << "Element= " << a.n_elem << std::endl;
    PressEnterToContinue();
}

////////////////////////////////////////////////////////////////////////////////

void MatrixOperations()
{
    std::cout << ">>> Matrix Operations..." << std::endl;
    PressEnterToContinue();

    constexpr int num_rows = 3;
    constexpr int num_cols = 3;

    arma::mat a(num_rows, num_cols, arma::fill::zeros);
    arma::mat b(num_rows, num_cols, arma::fill::zeros);
    arma::mat c(num_rows, num_cols, arma::fill::zeros);

    a.fill(1.0);
    b << 1 << 2 << 3 << arma::endr
      << 4 << 5 << 6 << arma::endr
      << 7 << 8 << 9 << arma::endr;
    
    c = a + b;
    std::cout << c << std::endl;
    PressEnterToContinue();

    c = a - b;
    std::cout << c << std::endl;
    PressEnterToContinue();

    c = a * b;
    std::cout << c << std::endl;
    PressEnterToContinue();

    c = a * 2.0;
    std::cout << c << std::endl;
    PressEnterToContinue();

    c = a / 2.0;
    std::cout << c << std::endl;
    PressEnterToContinue();

    c = b.t();
    std::cout << c << std::endl;
    PressEnterToContinue();

    b << 1 << 1 << 1 << arma::endr
      << 2 << 1 << 1 << arma::endr
      << 2 << 2 << 1 << arma::endr;
    c = b.i();
    std::cout << c << std::endl;
    PressEnterToContinue();
}

////////////////////////////////////////////////////////////////////////////////

void SolveLinearEquastionsSystem()
{
    std::cout << ">>> Solve Linear Equastions System..." << std::endl;
    PressEnterToContinue();

    // x = 1
    // y = 1
    // z = 2
    //  x +  y + z = 4
    // 2x +  y + z = 5
    // 2x + 2y + z = 6
    arma::mat lhs;
    arma::mat rhs;
    lhs << 1 << 1 << 1 << arma::endr
        << 2 << 1 << 1 << arma::endr
        << 2 << 2 << 1 << arma::endr;
    rhs << 4 << arma::endr
        << 5 << arma::endr
        << 6 << arma::endr; 
    arma::mat sol = arma::solve(lhs, rhs);
    std::cout << sol << std::endl;
    PressEnterToContinue();

}