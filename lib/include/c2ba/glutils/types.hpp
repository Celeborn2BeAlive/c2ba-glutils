#pragma once

#include <array>

namespace c2ba {

using GLfloat2 = std::array<GLfloat, 2>;
using GLfloat3 = std::array<GLfloat, 3>;
using GLfloat4 = std::array<GLfloat, 4>;
using GLint2 = std::array<GLint, 2>;
using GLint3 = std::array<GLint, 3>;
using GLint4 = std::array<GLint, 4>;
using GLuint2 = std::array<GLuint, 2>;
using GLuint3 = std::array<GLuint, 3>;
using GLuint4 = std::array<GLuint, 4>;
using GLboolean2 = std::array<GLboolean, 2>;
using GLboolean3 = std::array<GLboolean, 3>;
using GLboolean4 = std::array<GLboolean, 4>;

template<typename T, size_t num_rows, size_t num_cols>
struct GLMatrixArray : public std::array<T, num_rows * num_cols> {
};

using GLfloat2x2 = GLMatrixArray<GLfloat, 2, 2>;
using GLfloat3x3 = GLMatrixArray<GLfloat, 3, 3>;
using GLfloat4x4 = GLMatrixArray<GLfloat, 4, 4>;

using GLfloat2x3 = GLMatrixArray<GLfloat, 2, 3>;
using GLfloat3x2 = GLMatrixArray<GLfloat, 3, 2>;
using GLfloat2x4 = GLMatrixArray<GLfloat, 2, 4>;
using GLfloat4x2 = GLMatrixArray<GLfloat, 4, 2>;
using GLfloat3x4 = GLMatrixArray<GLfloat, 3, 4>;
using GLfloat4x3 = GLMatrixArray<GLfloat, 4, 3>;

}