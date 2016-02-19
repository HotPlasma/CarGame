#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include <vector>

using namespace std;

class Matrix
{
private:
	vector<myVector> m_vMatrix;

public:
	Matrix();
	Matrix(myVector Vector);
	Matrix(vector<myVector> Vectors);
	void push(myVector PushVect);
	float size();
	myVector getVect(int index);
	Matrix operator - (const Matrix Matrix2);
	Matrix operator + (const Matrix Matrix2);
	Matrix operator + (float scalar);
	Matrix dotProduct(Matrix Matrix2);
	Matrix scale(const float scalar);
	Matrix rotate(float angle);
	Matrix translate(const float fX, const float fY);

};

#endif