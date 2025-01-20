#include "iVigenereStream.h"

using namespace std;

// Constructor cho lớp iVigenereStream, khởi tạo cipher provider và mở tệp
iVigenereStream::iVigenereStream(Cipher aCipher,
    const std::string& aKeyword,
    const char* aFileName) :
    fCipherProvider(aKeyword),
    fCipher(aCipher)
{
    open(aFileName);
}

// Destructor cho lớp iVigenereStream, đảm bảo tệp được đóng
iVigenereStream::~iVigenereStream()
{
    close();
}

// Phương thức mở tệp với tên tệp được cung cấp
void iVigenereStream::open(const char* aFileName)
{
    if (aFileName)                                                    
        fIStream.open(aFileName, ifstream::binary);                 
}

// Phương thức đóng tệp hiện tại
void iVigenereStream::close()
{
    if (is_open())
    {
        fIStream.close();
    }
}

// Phương thức đặt lại trạng thái của cipher provider
void iVigenereStream::reset()
{
    fCipherProvider.reset();

    if (is_open())
    {
        seekstart();
    }
}

// Kiểm tra trạng thái tốt của luồng tệp
bool iVigenereStream::good() const
{
    return fIStream.good();
}

// Kiểm tra xem tệp có đang mở hay không
bool iVigenereStream::is_open() const
{
    return fIStream.is_open();
}

// Kiểm tra xem đã đến cuối tệp chưa
bool iVigenereStream::eof() const
{
    return fIStream.eof();
}

// Toán tử nhập liệu để lấy ký tự từ tệp và mã hóa nó
iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
    char lCharacter = 0;

    if (fIStream.get(lCharacter))
    {
        aCharacter = fCipher(fCipherProvider, lCharacter);
    }

    return *this;
}
