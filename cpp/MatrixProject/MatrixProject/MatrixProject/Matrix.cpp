#include "pch.h"
#include "Matrix.h"
#include <cassert>
#include <fstream>
#include <iomanip>//对输入输出进行格式化定义
#include <string>

using namespace std;

#define SAFE_DELETE(p) {if(p) {delete[]p; p=nullptr;}}//宏定义

Matrix::Matrix(int nRow, int nCol, double* pData)
{
	assert(pData && nRow && nCol);
	Copy(pData, nRow, nCol);
	/*m_nRow = nRow;
	m_nCol = nCol;

	if (pData &&nRow && nCol)
	{
		pData = new double[ Size() ];
		if (m_pData)
		{
			size_t size = Size() * sizeof(double);
			memcpy_s(m_pData, size, pData, size);
		}
	}*/

	
}

Matrix::Matrix(const std::string & strMatrixFile)
{
	std::ifstream ifs(strMatrixFile);
	if (ifs)
	{
		Load(ifs);
	}
	else
	{
		cerr << "Open the file\"" << strMatrixFile << "\"failed!" << endl;
	}
}

Matrix::Matrix(const Matrix & src)
{
	//进行深拷贝
	m_nCol = src.m_nCol;
	m_nRow = src.m_nRow;
	
	if (m_pData &&m_nRow && m_nCol)
	{
		m_pData = new double[Size()];
		//if (m_pData)
		//{
			//size_t size = Size() * sizeof(double);
			//memcpy_s(m_pData, size, m_pData, size);
		//}
		Copy(m_pData, m_nRow, m_nCol);
	}
}

Matrix::~Matrix()
{
	//在使用指针之前要先判断是否为空
	//if (m_pData != nullptr)
	//{
		//delete[] m_pData;
		//m_pData = nullptr;//安全的写法
	//}
	SAFE_DELETE(m_pData);//使用宏定义后这样写
}

const Matrix & Matrix::operator=(const Matrix & r)
{
	if (this != &r)
	{
		SAFE_DELETE(m_pData);
		Copy(r.m_pData, r.m_nRow, r.m_nCol);
	}

	return *this;
}

void Matrix::Load(std::istream & ism)
{
	ism >> m_nRow >> m_nCol;
	if (Size() != 0)
	{
		SAFE_DELETE(m_pData);
		m_pData = new double[Size()];
		if (m_pData)
			for (size_t i = 0; i < Size(); ++i)
				ism >> m_pData[i];
	}
}

void Matrix::Save(std::ostream & osm)const
{
	osm << setw(6) << right << m_nRow 
		<< setw(6) << right << m_nCol << endl;//setw(6)表示输出6个字符，right表示右对齐
	for (size_t i = 0; i < Size(); ++i)
	{
		osm << setw(12) << right << fixed << m_pData[i];
		if ((i + 1) % m_nCol == 0)
			osm << endl;
	}
}

void Matrix::Copy(void * pSource, int nRow, int nCol)
{
	m_nCol = nCol;
	m_nRow = nRow;

	if (Size()!=0)
	{
		m_pData = new double[Size()];
		if (m_pData)
		{
			size_t size = Size() * sizeof(double);
			memset(m_pData, 0, size);
			
			if (pSource)
			{				
				memcpy_s(m_pData, size, pSource, size);
			}
			
			/*else
			{
				memset(m_pData, 0, size);
			}*/
		}
	}
}



std::ostream & operator<<(std::ostream & osm, const Matrix & mat)
{
	mat.Save(osm);
	return osm;
}

std::istream & operator>>(std::istream & ism, Matrix & mat)
{
	mat.Load(ism);
	return ism;
}

Matrix operator+(const Matrix & l, const Matrix & r)
{
	bool bCanop = l.m_nRow == r.m_nRow  &&
		l.m_nCol == r.m_nCol;
	
	assert(bCanop);

	Matrix ret(l);//ret-result,使用了拷贝构造函数
	if (bCanop)
	{
		for (size_t i = 0; i < l.Size(); ++i)
			ret.m_pData[i] += r.m_pData[i];
	}

	return ret;
}

Matrix operator-(const Matrix & l, const Matrix & r)
{
	bool bCanop = l.m_nRow == r.m_nRow  &&
		          l.m_nCol == r.m_nCol;
	/*assert(l.m_nRow == r.m_nRow  &&
		   l.m_nCol == r.m_nCol);*/
	assert(bCanop);

	Matrix ret(l);//ret-result,使用了拷贝构造函数
	if (bCanop)
	{
		for (size_t i = 0; i < l.Size(); ++i)
			ret.m_pData[i] -= r.m_pData[i];
	}

	return ret;
}

Matrix operator*(const Matrix & l, const Matrix & r)
{
	bool bCanop = l.m_nCol == r.m_nRow;

	assert(bCanop);
	
	Matrix ret(l.m_nRow, r.m_nCol);
	
	if (bCanop)
	{
		for (size_t i = 0; i < l.Size(); ++i)
		{
			for (size_t j = 0; j < r.m_nCol; ++j)
			{
				int idx = ret.m_nCol*i + j;
				for (size_t k = 0; k < r.m_nRow; ++k)
				{
					int idxL = i * l.m_nCol + k;
					int idxR = k * r.m_nCol + j;
						ret.m_pData[idx] += l.m_pData[idxL] * r.m_pData[idxR];
				}
			}
		}
	}

	return ret;
}
