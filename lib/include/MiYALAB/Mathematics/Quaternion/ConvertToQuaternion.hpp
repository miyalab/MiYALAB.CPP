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

#ifndef __MIYALAB_CPP_MATHEMATICS_QUATERNION_QUATERNION_CONVERTER_HPP__
#define __MIYALAB_CPP_MATHEMATICS_QUATERNION_QUATERNION_CONVERTER_HPP__

//-----------------------------
// include
//-----------------------------
#include <string>
#include <cmath>
#include "../EulerAngles/EulerAngles.hpp"
#include "Quaternion.hpp"

//-----------------------------
// Namespace & using
//-----------------------------

//-----------------------------
// Class
//-----------------------------
namespace MiYALAB {
namespace Mathematics{

template<typename Numeric> void ConvertToQuaternion(const EulerAngles<Numeric> &euler, Quaternion<Numeric> &quaternion);
template<typename Numeric> Quaternion<Numeric> ConvertToQuaternion(const EulerAngles<Numeric> &euler);

}
}

#endif // __MIYALAB_CPP_MATHEMATICS_QUATERNION_QUATERNION_CONVERTER_HPP__

//-----------------------------------------------------------------------------------
// end of file
//-----------------------------------------------------------------------------------