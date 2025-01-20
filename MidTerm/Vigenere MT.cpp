#include "Vigenere.h"
#include <cctype>                                                   // Thư viện để sử dụng các hàm kiểm tra ký tự

using namespace std;

// Hàm khởi tạo Vigenere, thiết lập từ khóa và chuẩn bị bảng mã hóa
Vigenere::Vigenere(const string& aKeyword) :
    fKeyword(aKeyword),                                             // Gán từ khóa ban đầu
    fKeywordProvider(aKeyword)                                      // Khởi tạo KeyProvider với từ khóa
{
    initializeTable();                                              // Gọi hàm khởi tạo bảng mã hóa
}

// Trả về từ khóa hiện tại, được cung cấp bởi KeyProvider
string Vigenere::getCurrentKeyword()
{
    string currentKeyword;                                          // Chuỗi chứa kết quả

    for (size_t i = 0; i < fKeyword.size(); ++i)                    // Lặp qua từng ký tự của từ khóa
    {
        char keyCharacter = *fKeywordProvider;                      // Lấy ký tự hiện tại từ KeyProvider

        currentKeyword += keyCharacter;                             // Thêm ký tự vào chuỗi kết quả
        fKeywordProvider << keyCharacter;                           // Đẩy ký tự và cập nhật KeyProvider
    }

    return currentKeyword;                                          // Trả về từ khóa hiện tại
}

// Đặt lại KeyProvider về trạng thái ban đầu
void Vigenere::reset()
{
    fKeywordProvider.initialize(fKeyword);                          // Khởi tạo lại từ khóa trong KeyProvider
}

// Mã hóa ký tự dựa trên từ khóa và bảng mã hóa
char Vigenere::encode(char aCharacter)
{
    if (isalpha(aCharacter))                                        // Kiểm tra nếu ký tự là chữ cái
    {
        bool isLower = islower(aCharacter);                         // Kiểm tra ký tự có phải là chữ thường không
        aCharacter = toupper(aCharacter);                           // Chuyển ký tự thành chữ in hoa

        // Tính toán chỉ số hàng và cột 
        char rowIndex = *fKeywordProvider - 'A';                    // Lấy hàng tương ứng trong bảng mã hóa
        char columnIndex = aCharacter - 'A';                        // Lấy cột tương ứng trong bảng mã hóa

        fKeywordProvider << aCharacter;                             // Cập nhật KeyProvider với ký tự hiện tại

        aCharacter = fMappingTable[rowIndex][columnIndex];          // Mã hóa ký tự dựa trên bảng

        if (isLower)                                                // Nếu ký tự ban đầu là chữ thường
        {
            aCharacter = tolower(aCharacter);                       // Chuyển ký tự đã mã hóa thành chữ thường
        }
    }

    return aCharacter;                                              // Trả về ký tự đã mã hóa
}

// Giải mã ký tự dựa trên từ khóa và bảng mã hóa
char Vigenere::decode(char aCharacter)
{
    if (isalpha(aCharacter))                                        // Kiểm tra nếu ký tự là chữ cái
    {
        bool isLower = islower(aCharacter);                         // Kiểm tra ký tự có phải là chữ thường không
        aCharacter = toupper(aCharacter);                           // Chuyển ký tự thành chữ in hoa

        char rowIndex = *fKeywordProvider - 'A';                    // Lấy hàng tương ứng trong bảng mã hóa

        for (char columnIndex = 0; columnIndex < CHARACTERS; ++columnIndex)  // Duyệt qua cột để tìm ký tự đã mã hóa
        {
            if (aCharacter == fMappingTable[rowIndex][columnIndex])  // Kiểm tra nếu ký tự khớp với cột hiện tại
            {
                aCharacter = 'A' + columnIndex;                      // Khôi phục ký tự ban đầu
                break;                                               // Thoát khỏi vòng lặp khi tìm thấy
            }
        }

        fKeywordProvider << aCharacter;                             // Cập nhật KeyProvider với ký tự hiện tại

        if (isLower)                                                // Nếu ký tự ban đầu là chữ thường
        {
            aCharacter = tolower(aCharacter);                       // Chuyển ký tự đã giải mã thành chữ thường
        }
    }

    return aCharacter;                                              // Trả về ký tự đã giải mã
}