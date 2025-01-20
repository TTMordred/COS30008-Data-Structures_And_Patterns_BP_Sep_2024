#include "VigenereForwardIterator.h"

using namespace std;

// Constructor cho lớp VigenereForwardIterator, khởi tạo iterator với luồng iVigenereStream
VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream) :
    fIStream(aIStream),                                                     // Gán luồng tệp cho iterator
    fEOF(false)                                                             // Đặt cờ EOF về false
{
    ++(*this);                                                              // Tăng iterator để chuẩn bị cho ký tự đầu tiên
}

// Toán tử dereference, trả về ký tự hiện tại
char VigenereForwardIterator::operator*() const
{
    return fCurrentChar;                                                    // Trả về ký tự hiện tại
}

// Toán tử tiền tố tăng, cập nhật ký tự hiện tại từ luồng
VigenereForwardIterator& VigenereForwardIterator::operator++()
{
    fIStream >> fCurrentChar;                                               // Đọc ký tự mới từ luồng tệp

    fEOF = fIStream.eof();                                                  // Cập nhật cờ EOF dựa trên trạng thái luồng

    return *this;                                                           // Trả về đối tượng hiện tại
}

// Toán tử hậu tố tăng, trả về giá trị trước khi tăng
VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
    VigenereForwardIterator temp = *this;                                   // Lưu trữ bản sao hiện tại

    ++(*this);                                                              // Tăng iterator để cập nhật ký tự

    return temp;                                                            // Trả về bản sao trước khi tăng
}

// So sánh hai iterator để kiểm tra tính tương đương
bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
    return &fIStream == &aOther.fIStream && fEOF == aOther.fEOF;            // So sánh địa chỉ luồng và cờ EOF
}

// So sánh hai iterator để kiểm tra tính không tương đương
bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
    return !(*this == aOther);                                              // Sử dụng toán tử == để kiểm tra không tương đương
}

// Phương thức bắt đầu iterator, đặt lại trạng thái
VigenereForwardIterator VigenereForwardIterator::begin() const
{
    VigenereForwardIterator Result = *this;                                 // Tạo bản sao của iterator

    Result.fIStream.reset();                                                // Đặt lại luồng để bắt đầu từ đầu
    Result.fEOF = false;                                                    // Đặt cờ EOF về false

    return ++Result;                                                        // Tăng và trả về iterator bắt đầu
}

// Phương thức kết thúc iterator, đánh dấu vị trí kết thúc
VigenereForwardIterator VigenereForwardIterator::end() const
{
    VigenereForwardIterator Result = *this;                                 // Tạo bản sao của iterator

    Result.fEOF = true;                                                     // Đặt cờ EOF về true

    return Result;                                                          // Trả về iterator kết thúc
}                                                                          
