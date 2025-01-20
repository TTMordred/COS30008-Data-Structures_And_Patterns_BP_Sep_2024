#include "KeyProvider.h"
#include <cctype>  // Thư viện để sử dụng hàm toupper()

using namespace std;

// Khởi tạo đối tượng KeyProvider, thiết lập ban đầu cho từ khóa
KeyProvider::KeyProvider(const string& aKeyword) :
    fKeyword(nullptr),      // Đặt con trỏ fKeyword thành nullptr
    fSize(0),               // Đặt kích thước từ khóa ban đầu là 0
    fIndex(0)               // Đặt chỉ mục từ khóa là 0
{
    initialize(aKeyword);   // Gọi hàm khởi tạo từ khóa với aKeyword
}

// Destructor giải phóng bộ nhớ đã cấp phát cho từ khóa
KeyProvider::~KeyProvider()
{
    delete[] fKeyword;      // Giải phóng bộ nhớ đã cấp phát
}

// Hàm khởi tạo lại từ khóa với chuỗi mới
void KeyProvider::initialize(const string& aKeyword)
{
    delete[] fKeyword;      // Xóa từ khóa cũ nếu tồn tại

    fSize = aKeyword.length();    // Cập nhật độ dài từ khóa mới
    fKeyword = new char[fSize];   // Cấp phát bộ nhớ cho từ khóa mới
    fIndex = 0;                   // Đặt lại chỉ mục về 0

    for (size_t i = 0; i < fSize; ++i)  // Duyệt qua từng ký tự của từ khóa mới
    {
        fKeyword[i] = toupper(aKeyword[i]);  // Chuyển mỗi ký tự thành chữ in hoa
    }
}

// Toán tử dereference trả về ký tự hiện tại của từ khóa
char KeyProvider::operator*() const
{
    return fKeyword[fIndex];  // Trả về ký tự tại vị trí fIndex hiện tại
}

// Toán tử dịch trái, thêm một ký tự mới và di chuyển chỉ mục
KeyProvider& KeyProvider::operator<<(char aKeyCharacter)
{
    fKeyword[fIndex] = toupper(aKeyCharacter);  // Thay thế ký tự hiện tại bằng ký tự mới

    ++fIndex;  // Tăng chỉ mục lên 1

    if (fIndex == fSize)  // Nếu chỉ mục vượt quá độ dài từ khóa
    {
        fIndex = 0;  // Đặt lại chỉ mục về 0 (vòng lặp tuần hoàn)
    }

    return *this;  // Trả về chính đối tượng để hỗ trợ xâu chuỗi
}
