#ifndef _MATRIX_H_//宏检测
#define _MATRIX_H_

#include <iostream>

class Matrix
{
	friend std::ostream& operator<<(std::ostream& osm, const Matrix& mat);
	friend std::istream& operator>>(std::istream& ism, Matrix& mat);

	friend Matrix operator+(const Matrix& l, const Matrix& r);
	friend Matrix operator-(const Matrix& l, const Matrix& r);
	friend Matrix operator*(const Matrix& l, const Matrix& r);

public:
	Matrix():m_nRow(0), m_nCol(0), m_pData(nullptr){}//nullptr:空指针（规范），尽量不要写0
	Matrix(int nRow, int nCol, double* pData=nullptr);
	Matrix(const std::string& strMatrixFile);//Create a matrix from a file
	Matrix(const Matrix& src);//src-source 拷贝构造函数

	virtual ~Matrix();

	const Matrix& operator=(const Matrix& r);//赋值操作数，r为右侧数

	long Size()const { return m_nRow * m_nCol; }
	int  GetRows()const { return m_nRow; }//获取行数
	int  GetCols()const { return m_nCol; }//获取列数

	bool Empty()const { return (Size() == 0); }//测试矩阵是否为空

protected:
	void Load(std::istream& ism);//加载矩阵
	void Save(std::ostream& osm)const;
	//因为使用不频繁，故不用写use namespace std;
	void Copy(void* pSource, int nRow, int nCol);
private:
	//前缀表示数据类型，i表示变化的量，n表示终点，d-double, f-float。命名规则：标签_前缀_名称
	int     m_nRow;//m变量标签（member）,n表示number
	int     m_nCol;

	double* m_pData;//存储矩阵的数据
};


#endif //_MATRIX_H_
