#include "Matrix3.h"

#include <cstring>
#include <cmath>

IMPGEARS_BEGIN

Matrix3::Matrix3()
{
    for(Uint32 i=0; i<9; ++i)
        m_values[i] = 0.f;
}

Matrix3::Matrix3(const Matrix3& other)
{
    memcpy(m_values, other.m_values, sizeof(float)*9);
}

Matrix3::Matrix3(const float values[9])
{
    memcpy(m_values, values, sizeof(float)*9);
}

Matrix3::~Matrix3()
{
}

void Matrix3::setValue(Uint32 l, Uint32 c, float value)
{
    m_values[c*3+l] = value;
}

float Matrix3::getValue(Uint32 l, Uint32 c) const
{
    return m_values[c*3+l];
}

Matrix3& Matrix3::operator=(const Matrix3& other)
{
    memcpy(m_values, other.m_values, sizeof(float)*9);

    return *this;
}

Matrix3& Matrix3::operator+=(const Matrix3& other)
{
    for(Uint32 i=0; i<9; ++i)
        m_values[i] += other.m_values[i];

    return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& other)
{
    for(Uint32 i=0; i<9; ++i)
        m_values[i] -= other.m_values[i];

    return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& other)
{
    const Matrix3 before(*this);

    for(Uint32 l=0;l<3;l++)
    for(Uint32 c=0;c<3;c++){

        m_values[c*3+l] = 0.f;
        for(Uint32 k=0; k<3;k++)
            m_values[c*3+l] += ( before.m_values[c*3+k] * other.m_values[k*3+l] );
    }

    return *this;
}

Matrix3& Matrix3::operator*=(float scalar)
{
    for(Uint32 i=0; i<9; ++i)
        m_values[i] *= scalar;

    return *this;
}

Matrix3 Matrix3::operator+(const Matrix3& other) const
{
    return Matrix3(*this) += other;
}

Matrix3 Matrix3::operator-(const Matrix3& other) const
{
    return Matrix3(*this) -= other;
}

Matrix3 Matrix3::operator*(const Matrix3& other) const
{
    return Matrix3(*this) *= other;
}

Matrix3 Matrix3::operator*(float scalar) const
{
    return Matrix3(*this) *= scalar;
}

imp::Vector3 Matrix3::operator*(const imp::Vector3& vector) const
{
    imp::Vector3 result;

    imp::Vector3 line1(m_values[0], m_values[1], m_values[2]);
    imp::Vector3 line2(m_values[3], m_values[4], m_values[5]);
    imp::Vector3 line3(m_values[6], m_values[7], m_values[8]);

    result.setX(line1.dotProduct(vector));
    result.setY(line2.dotProduct(vector));
    result.setZ(line3.dotProduct(vector));

    return result;
}

float Matrix3::getDet() const
{
    /// not implemented
    return 0;
}

Matrix3 Matrix3::getTranspose() const
{
    Matrix3 transpose(*this);

    for(Uint32 i=0;i<3;i++){
    for(Uint32 j=0;j<3;j++){
        transpose.setValue(i,j, getValue(j,i));
    }}

    return transpose;
}

Matrix3 Matrix3::getInverse() const
{
    /// not implemented
    return Matrix3();
}

const Matrix3 Matrix3::getRotationMatrixX(float rad)
{
    ///     1           0           0
    ///     0           cos(a)      -sin(a)
    ///     0           sin(a)      cos(a)

    const float values[9] = {
        1.f,        0.f,            0.f,
        0.f,        cosf(rad),      -sinf(rad),
        0.f,        sinf(rad),      cosf(rad)
    };

    return Matrix3(values);
}

const Matrix3 Matrix3::getRotationMatrixY(float rad)
{
    ///     cos(a)      0           sin(a)
    ///     0           1           0
    ///     -sin(a)     0           cos(a)

    const float values[9] = {
        cosf(rad),      0.f,        sinf(rad),
        0.f,            1.f,        0.f,
        -sinf(rad),     0.f,        cosf(rad)
    };

    return Matrix3(values);
}

const Matrix3 Matrix3::getRotationMatrixZ(float rad)
{
    ///     cos(a)      -sin(a)     0
    ///     sin(a)      cos(a)      0
    ///     0           0           1

    const float values[9] = {
        cosf(rad),      -sinf(rad),         0.f,
        sinf(rad),      cosf(rad),          0.f,
        0.f,            0.f,                1.f
    };

    return Matrix3(values);
}

const Matrix3 Matrix3::getIdentity()
{
    const float values[9] = { 1.f, 0.f, 0.f,
                        0.f, 1.f, 0.f,
                        0.f, 0.f, 1.f};

    return Matrix3(values);
}
IMPGEARS_END
