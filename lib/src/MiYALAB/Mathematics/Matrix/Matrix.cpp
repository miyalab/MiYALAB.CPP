/*
 * MIT License
 * 
 * Copyright (c) 2022 MiYA LAB(K.Miyauchi)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

//-----------------------------
// include
//-----------------------------
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "MiYALAB/Mathematics/Matrix/Matrix.hpp"

//-----------------------------
// Namespace & using
//-----------------------------

//-----------------------------
// template 
//-----------------------------
namespace MiYALAB {
namespace Cpp{
namespace Mathematics{
template struct Matrix<char>;
template struct Matrix<short>;
template struct Matrix<int>;
template struct Matrix<long>;
template struct Matrix<long long>;
template struct Matrix<float>;
template struct Matrix<double>;
template struct Matrix<long double>;
}
}
}

//-----------------------------
// Helper function
//-----------------------------
namespace MiYALAB {
namespace Cpp{
namespace Mathematics{

template<class Numeric>
struct LUP{
public:
    LUP(const Matrix<Numeric> &matrix): mat(matrix), perm(matrix.Height()){}
    Matrix<Numeric> mat;
    std::vector<Numeric> perm;
    int toggle;
};

template<class Numeric> 
void DecomposeLUP(LUP<Numeric> &ret)
{
    const size_t &n = ret.mat.Height();

    int pRow;
    Numeric colMax;
    ret.toggle = 1;
    for(size_t i=0; i<n; i++) ret.perm[i] = i;
    
    for(size_t j=0; j<n-1; j++){
        colMax = std::abs(ret.mat[j][j]);
        pRow = j;
        for(int i=j+1; i<n; i++){
            if(ret.mat[i][j] > colMax){
                colMax = ret.mat[i][j];
                pRow = i;
            }
        }
        if(pRow != j){
            std::swap(ret.mat[pRow], ret.mat[j]);
            std::swap(ret.perm[pRow],ret.perm[j]);
            ret.toggle = -ret.toggle;
        }
        if(std::abs(ret.mat[j][j]) < 1.0E-10){
            ret.toggle = 0;
            return;
        }
        for(size_t i=j+1; i<n; i++){
            ret.mat[i][j] /= ret.mat[j][j];
            for(size_t k=j+1; k<n; k++) ret.mat[i][k] -= ret.mat[i][j] * ret.mat[j][k];
        }
    }
}

/**
 * @brief 
 * 
 * @tparam Numeric 
 * @param luMat 
 * @param b 
 * @param x 
 */
template<class Numeric>
void HelperSolve(const Matrix<Numeric> &luMat, const std::vector<Numeric> &b, std::vector<Numeric> &x)
{
    const size_t &n = luMat.Height();
    Numeric sum;
    x.resize(n);
    for(size_t i=0; i<b.size(); i++) x[i] = b[i];
    
    for(size_t i=1; i<n; i++){
        sum = x[i];
        for(size_t j=0; j<i; j++) sum -= luMat[i][j] * x[j];
        x[i] = sum;
    }
    x[n-1] /= luMat[n-1][n-1];
    for(long i=n-2; 0<=i; i--){
        sum = x[i];
        for(size_t j=i+1; j<n; j++) sum-= luMat[i][j] * x[j];
        x[i] = sum / luMat[i][i];
    }
}
}
}
}

//-----------------------------
// Methods
//-----------------------------
namespace MiYALAB {
namespace Cpp{
namespace Mathematics{
/**
 * @brief 加算代入メソッド
 * 
 * @tparam Numeric 
 * @param matrix 
 * @return Matrix<Numeric>& 
 */
template<class Numeric> Matrix<Numeric> &Matrix<Numeric>::operator+=(const Matrix &matrix)
{
    if(this->Cols() != matrix.Cols() || this->Rows() != matrix.Rows()) throw "Input matrices have different sizes.";

    for(size_t i=0; i<this->Rows(); i++){
        for(size_t j=0; j<this->Cols(); j++){
            (*this)[i][j] += matrix[i][j];
        }
    }
    return *this;
}

/**
 * @brief 減算代入メソッド
 * 
 * @tparam Numeric 
 * @param matrix 
 * @return Matrix<Numeric>& 
 */
template<class Numeric> Matrix<Numeric> &Matrix<Numeric>::operator-=(const Matrix &matrix)
{
    if(this->Cols() != matrix.Cols() || this->Rows() != matrix.Rows()) throw "Input matrices have different sizes.";

    for(size_t i=0; i<this->Rows(); i++){
        for(size_t j=0; j<this->Cols(); j++){
            (*this)[i][j] -= matrix[i][j];
        }
    }
    return *this;
}

/**
 * @brief 乗算メソッド
 * 
 * @tparam Numeric 
 * @param matrix 
 * @return Matrix<Numeric> 
 * 
*/
template<class Numeric> Matrix<Numeric> Matrix<Numeric>::operator*(const Matrix &matrix) const 
{
    if(this->Cols() != matrix.Rows()) throw "Input matrices have different sizes.";

    Matrix<Numeric> ret(this->Rows(), matrix.Cols());
    for(size_t i=0; i<this->Rows(); i++){
        for(size_t k=0; k<this->Cols(); k++){
            for(size_t j=0; j<matrix.Cols(); j++){
                ret[i][j] += (*this)[i][k] * matrix[k][j];
            }
        }
    }
    return ret;
}

/**
 * @brief スカラ積メソッド
 * 
 * @tparam Numeric 
 * @param num 
 * @return Matrix<Numeric>& 
 */
template<class Numeric> Matrix<Numeric> &Matrix<Numeric>::operator*=(const Numeric &num)
{
    for(size_t i=0; i<this->Rows(); i++){
        for(size_t j=0; j<this->Cols(); j++){
            (*this)[i][j] *= num;
        }
    }
    return *this;
}

/**
 * @brief スカラ積メソッド（除算）
 * 
 * @tparam Numeric 
 * @param num 
 * @return Matrix<Numeric>& 
 */
template<class Numeric> Matrix<Numeric> &Matrix<Numeric>::operator/=(const Numeric &num)
{
    for(size_t i=0; i<this->Rows(); i++){
        for(size_t j=0; j<this->Cols(); j++){
            (*this)[i][j] /= num;
        }
    }
    return *this;
}

/**
 * @brief 等価判定メソッド
 * 
 * @tparam Numeric 
 * @param matrix 
 * @return true 
 * @return false 
 */
template<class Numeric> bool Matrix<Numeric>::operator==(const Matrix &matrix) const 
{
    if(this->Cols() != matrix.Cols() || this->Rows() != matrix.Rows()) return false;

    for(size_t i=0; i<this->Rows(); i++){
        for(size_t j=0; j<this->Cols(); j++){
            if((*this)[i][j] != matrix[i][j]) return false;
        }
    }
    return true;
}

/**
 * @brief 文字列化メソッド
 * 
 * @tparam Numeric 
 * @return std::string 
 */
template<class Numeric> std::string Matrix<Numeric>::ToString() const
{
    std::string ret = "[";

    for(size_t i=0; i<this->Rows(); i++){
        ret += "[";
        for(size_t j=0; j<this->Cols(); j++) ret += std::to_string((*this)[i][j]) + ", ";
        ret[ret.length() - 2] = ']';
        ret[ret.length() - 1] = '\n';
    }
    ret[ret.length() - 1] = ']';
    return ret;
}

/**
 * @brief 逆行列計算メソッド
 * 
 * @tparam Numeric 
 * @return Matrix<Numeric> 
 */
template<class Numeric> Matrix<Numeric> Matrix<Numeric>::Inverse() const
{
    LUP<Numeric> lum(*this);
    DecomposeLUP(lum);
    if(lum.toggle == 0) throw "Unable to compute inversed matrix.";

    Matrix ret(*this);
    
    std::vector<Numeric> b(this->Height());
    for(size_t i=0; i<this->Height(); i++){
        for(size_t j=0; j<this->Height(); j++){
            if(i == lum.perm[j]) b[j] = 1.0;
            else b[j] = 0.0;
        }
        std::vector<Numeric> x;
        HelperSolve(lum.mat, b, x);
        for(size_t j=0; j<this->Height(); j++) ret[j][i] = x[j];
    }
    return ret;
}

/**
 * @brief 行列式計算メソッド
 * 
 * @tparam Numeric 
 * @return double 
 */
template<class Numeric> Numeric Matrix<Numeric>::Determinant() const
{
    LUP<Numeric> lum(*this);
    DecomposeLUP(lum);
    if(lum.toggle == 0) throw "Unable to compute matrix determinate.";
    
    Numeric ret = lum.toggle;
    for(size_t i=0; i<lum.mat.Height(); i++) ret *= lum.mat[i][i];
    return ret; 
}

/**
 * @brief 転置行列計算メソッド
 * 
 * @tparam Numeric 
 * @return Matrix<Numeric> 
 */
template<class Numeric> Matrix<Numeric> Matrix<Numeric>::Transpose() const
{
    Matrix ret(this->Cols(), this->Rows());
    for(size_t i=0; i<this->Rows(); i++){
        for(size_t j=0; j<this->Cols(); j++){
            ret[j][i] = (*this)[i][j];
        }
    }
    return ret;
}

}
}
}

//-----------------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------------