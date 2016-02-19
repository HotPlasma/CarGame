#include "Matrix.h"

Matrix::Matrix()
{
	m_vMatrix.push_back(myVector(0, 0));
}

Matrix::Matrix(myVector Vector)
{
	m_vMatrix.push_back(Vector);
}
//
//Matrix::Matrix(vector<myVector> Vectors)
//{
//	m_vMatrix.resize(Vectors.size());
//
//	for (int i = 0; i < Vectors.size; i++)
//	{
//		//m_vMatrix.at(i).set(Vectors.at(i).x(), Vectors.at(i).y(), Vectors.at(i).h));
//	}
//
//}