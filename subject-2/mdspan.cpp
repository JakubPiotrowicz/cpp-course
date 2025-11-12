#include <iostream>
#include <mdspan>
#include <vector>

int main() {
    std::vector<int> data(3 * 4);
    // Fill with sample values
    for (int i = 0; i < 12; ++i)
        data[i] = i + 1;

    // Create a 3x4 mdspan (rows x cols)
    std::mdspan mat(data.data(), 3, 4);

    // Print the matrix
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j)
            std::cout << mat[i, j] << ' ';
        std::cout << '\n';
    }

    // Access like a 2D array
    std::cout << "Element (1,2): " << mat[1, 2] << '\n';
}

// Godbolt: https://godbolt.org/z/6qz7W7bPf
