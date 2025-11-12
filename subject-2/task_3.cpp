#include <iostream>
#include <vector>
#include <mdspan>
#include <array>

void rotate90(std::mdspan<int, std::extents<size_t, 3, 3>>& mat) {
    std::array<int, 9> tmp;

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            tmp[j * 3 + (2 - i)] = mat[i, j];
        }
    }

    for (size_t i = 0; i < 9; ++i) {
        mat.data_handle()[i] = tmp[i];
    }
}

int main() {
    std::vector<int> data = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    std::mdspan<int, std::extents<size_t, 3, 3>> mat(data.data());

    rotate90(mat);

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            std::cout << mat[i, j] << ' ';
        }
        std::cout << '\n';
    }
    // Output:
    // 7 4 1
    // 8 5 2
    // 9 6 3
}

// Godbolt: https://godbolt.org/z/E865v1qWb
