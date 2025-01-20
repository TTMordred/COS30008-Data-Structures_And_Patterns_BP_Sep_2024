#include "Combination.h"

// Hàm khởi tạo cho lớp Combination với các tham số aN và aK
Combination::Combination(size_t aN, size_t aK) :
    fN(aN),                                                         // Gán giá trị aN cho biến thành viên fN
    fK(aK)                                                          // Gán giá trị aK cho biến thành viên fK
{}

// Hàm trả về giá trị của fN
size_t Combination::getN() const
{
    return fN;                                                      // Trả về giá trị của biến fN
}

// Hàm trả về giá trị của fK
size_t Combination::getK() const
{
    return fK;                                                      // Trả về giá trị của biến fK
}

// Hàm toán tử để tính giá trị tổ hợp C(n, k)
unsigned long long Combination::operator()() const
{
    // Kiểm tra xem k có lớn hơn n hay không
    if (fK > fN)                                                    // Nếu k lớn hơn n, không thể tính tổ hợp
    {
        return 0;                                                   // Trả về 0 nếu k > n
    }
    else
    {
        unsigned long long Result = 1;                              // Khởi tạo biến Result với giá trị 1

        // Vòng lặp để tính toán tổ hợp
        for (unsigned long long i = 0; i < fK; )                   // Lặp từ 0 đến k
        {
            Result *= (fN - i);                                     // Nhân Result với (n - i), thực hiện tính toán tổ hợp
            Result /= ++i;                                          // Tăng i lên 1 và chia cho giá trị mới của i
        }

        return Result;                                              // Trả về giá trị cuối cùng của tổ hợp C(n, k)
    }
}
