#include "BernsteinBasisPolynomial.h"  // Nhúng file định nghĩa cho lớp BernsteinBasisPolynomial

#include <cmath>                       // Thư viện toán học để sử dụng các hàm toán học

using namespace std;

// Hàm khởi tạo cho lớp BernsteinBasisPolynomial với tham số aV và aN
BernsteinBasisPolynomial::BernsteinBasisPolynomial(unsigned int aV, unsigned int aN) :
    fFactor(aN, aV)                                                    // Khởi tạo biến fFactor với các tham số aN và aV
{}

// Hàm toán tử để tính giá trị của đa thức Bernstein tại một giá trị x cho trước
double BernsteinBasisPolynomial::operator()(double aX) const
{
    // Tính giá trị của đa thức Bernstein với công thức C(n, k) * x^k * (1 - x)^(n - k)
    double Result = fFactor() * pow(aX, fFactor.getK());              // Tính C(n, k) * x^k

    // Nhân kết quả với (1 - x)^(n - k) và trả về giá trị cuối cùng
    return Result * pow(1 - aX, fFactor.getN() - fFactor.getK());     // Trả về giá trị của đa thức Bernstein
}
