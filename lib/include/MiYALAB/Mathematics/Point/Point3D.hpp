/*
 * MIT License
 * 
 * Copyright (c) 2022-2023 MiYA LAB(K.Miyauchi)
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

#ifndef __MIYALAB_CPP_MATHEMATICS_POINT_3D_HPP__
#define __MIYALAB_CPP_MATHEMATICS_POINT_3D_HPP__

//-----------------------------
// include
//-----------------------------
#include <string>
#include <cmath>

//-----------------------------
// Namespace & using
//-----------------------------

//-----------------------------
// Class
//-----------------------------
namespace MiYALAB {
namespace Cpp{
namespace Mathematics{
/**
 * @brief x-y-z NumericType
 * 
 * @tparam NumericType 
 */
template<class NumericType>
struct Point3D{
    // フィールド
    NumericType x;
    NumericType y;
    NumericType z;

    // コンストラクタ
    Point3D(){this->x = 0; this->y = 0; this->z = 0;}
    Point3D(const NumericType &_x, const NumericType &_y, const NumericType &_z){this->x = _x; this->y = _y; this->z = _z;}

    // デストラクタ
    virtual ~Point3D(){}

    // 算術演算子
    Point3D &operator+=(const Point3D &point)  {this->x+=point.x; this->y+=point.y; this->z+=point.z; return *this;}
    Point3D &operator-=(const Point3D &point)  {this->x-=point.x; this->y-=point.y; this->z-=point.z; return *this;}
    Point3D &operator*=(const Point3D &point)  {*this=*this*point; return *this;}
    Point3D &operator*=(const NumericType &num){this->x*=num; this->y*=num; this->z*=num; return *this;}
    Point3D &operator/=(const NumericType &num){this->x/=num; this->y/=num; this->z/=num; return *this;}
    Point3D operator+ (const Point3D &point)   const {return (Point3D(*this)+=point);}
    Point3D operator- (const Point3D &point)   const {return (Point3D(*this)-=point);}
    Point3D operator* (const Point3D &point)   const {return (Point3D(this->y*point.z-point.y*this->z, this->z*point.x-point.z*this->x, this->x*point.y-point.x*this->y));}
    Point3D operator* (const NumericType &num) const {return (Point3D(*this)*=num);}
    Point3D operator/ (const NumericType &num) const {return (Point3D(*this)/=num);}    
    
    // 比較演算子
    bool operator==(const Point3D &point) const {return (this->x == point.x && this->y == point.y && this->z == point.z);}
    bool operator!=(const Point3D &point) const {return (this->x != point.x || this->y != point.y || this->z != point.z);}

    // 文字列化メソッド
    std::string toString() const {return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " << std::to_string(this->z) + ")";}

    // 3次元ベクトル計算メソッド
    NumericType Dot(const Point3D &point) const {return (this->x*point.x + this->y*point.y + this->z*point.z);}
    NumericType Magnitude()     const {return std::sqrt(this->x*this->x + this->y*this->y + this->z*this->z);}
    NumericType MagnitudePow2() const {return (this->x*this->x + this->y*this->y + this->z*this->z);}
};
}
}
}

#endif // __MIYALAB_CPP_MATHEMATICS_POINT_3D_HPP__

//-----------------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------------