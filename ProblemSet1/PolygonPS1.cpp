#include "Polygon.h"  // Nhúng file định nghĩa cho lớp Polygon
#include <iostream>   // Thêm thư viện cho cout

using namespace std;

// Mở rộng bài tập Problem Set 1
float Polygon::getSignedArea() const
{
    float area = 0.0f; // Khởi tạo biến lưu diện tích có dấu

    // Kiểm tra xem đa giác có ít nhất ba đỉnh hay không
    if (fNumberOfVertices > 2) // Đa giác phải có ít nhất 3 đỉnh
    {
        // Duyệt qua các đỉnh của đa giác từ đỉnh thứ 1 đến đỉnh cuối
        for (size_t i = 1; i < fNumberOfVertices; i++) // Bắt đầu từ đỉnh thứ 1
        {
            Vector2D v0 = fVertices[i - 1]; // Lấy đỉnh trước đó
            Vector2D v1 = fVertices[i]; // Lấy đỉnh hiện tại

            // Tính tích chéo và cộng vào diện tích
            area += v0.getX() * v1.getY() - v0.getY() * v1.getX(); // Tích chéo
            // Có thể thay thế bằng: area += v0.cross(v1); nếu Vector2D có phương thức cross
        }

        // Tính tích chéo giữa đỉnh cuối cùng và đỉnh đầu tiên
        Vector2D v0 = fVertices[fNumberOfVertices - 1]; // Đỉnh cuối
        Vector2D v1 = fVertices[0]; // Đỉnh đầu tiên

        // Cộng diện tích của hình tứ giác được tạo ra từ đỉnh cuối và đỉnh đầu tiên
        area += v0.getX() * v1.getY() - v0.getY() * v1.getX(); // Tích chéo
        // Có thể thay thế bằng: area += v0.cross(v1); nếu Vector2D có phương thức cross
    }

    return area / 2.0f; // Chia cho 2 để có diện tích thực tế
} // Kết thúc hàm
