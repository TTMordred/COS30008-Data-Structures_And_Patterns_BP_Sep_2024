#include "Polynomial.h"  // Nhúng file định nghĩa cho lớp Polynomial

#include <cmath>        // Thư viện toán học để sử dụng pow()

using namespace std;

// Hàm tính giá trị của đa thức tại một giá trị x cho trước
double Polynomial::operator()(double aX) const
{
    double Result = 0.0;  // Khởi tạo biến để lưu kết quả                                               

    // Vòng lặp qua từng hệ số của đa thức để tính giá trị
    for (size_t i = 0; i <= fDegree; i++)                                
    {
        Result += fCoeffs[i] * pow(aX, i);  // Tính giá trị của đa thức tại x                              
    }

    return Result;  // Trả về kết quả tính được                                          
}

// Hàm tính đạo hàm của đa thức
Polynomial Polynomial::getDerivative() const
{
    Polynomial Result;  // Khởi tạo đa thức kết quả                                                      

    if (fDegree)  // Nếu bậc của đa thức lớn hơn 0                                                    
    {
        Result.fDegree = fDegree - 1;  // Cập nhật bậc cho đạo hàm                                         

        // Vòng lặp để tính toán các hệ số của đạo hàm
        for (size_t i = 0; i < fDegree; i++)                           
        {
            Result.fCoeffs[i] = (i + 1) * fCoeffs[i + 1];  // Tính toán hệ số của đạo hàm                 
        }
    }

    return Result;  // Trả về đa thức đạo hàm                                             
}

// Hàm tính tích phân không xác định của đa thức
Polynomial Polynomial::getIndefiniteIntegral() const
{
    Polynomial Result;  // Khởi tạo đa thức cho tích phân không xác định                                  

    Result.fDegree = fDegree + 1;  // Cập nhật bậc cho đa thức tích phân không xác định                 

    // Vòng lặp để tính toán các hệ số của tích phân không xác định
    for (size_t i = 1; i <= fDegree + 1; i++)                         
    {
        Result.fCoeffs[i] = fCoeffs[i - 1] / i;  // Tính toán hệ số cho tích phân                      
    }

    return Result;  // Trả về đa thức tích phân không xác định                                  
}

// Hàm tính tích phân xác định của đa thức giữa hai giới hạn
double Polynomial::getDefiniteIntegral(double aXLow, double aXHigh) const
{
    Polynomial lIndefiniteIntegral = getIndefiniteIntegral();  // Gọi hàm tính tích phân không xác định             

    return lIndefiniteIntegral(aXHigh) - lIndefiniteIntegral(aXLow);  // Tính hiệu giữa hai giá trị tích phân     
}