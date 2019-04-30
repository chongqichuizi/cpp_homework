#ifndef _MATRIX_H_//����
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
	Matrix():m_nRow(0), m_nCol(0), m_pData(nullptr){}//nullptr:��ָ�루�淶����������Ҫд0
	Matrix(int nRow, int nCol, double* pData=nullptr);
	Matrix(const std::string& strMatrixFile);//Create a matrix from a file
	Matrix(const Matrix& src);//src-source �������캯��

	virtual ~Matrix();

	const Matrix& operator=(const Matrix& r);//��ֵ��������rΪ�Ҳ���

	long Size()const { return m_nRow * m_nCol; }
	int  GetRows()const { return m_nRow; }//��ȡ����
	int  GetCols()const { return m_nCol; }//��ȡ����

	bool Empty()const { return (Size() == 0); }//���Ծ����Ƿ�Ϊ��

protected:
	void Load(std::istream& ism);//���ؾ���
	void Save(std::ostream& osm)const;
	//��Ϊʹ�ò�Ƶ�����ʲ���дuse namespace std;
	void Copy(void* pSource, int nRow, int nCol);
private:
	//ǰ׺��ʾ�������ͣ�i��ʾ�仯������n��ʾ�յ㣬d-double, f-float���������򣺱�ǩ_ǰ׺_����
	int     m_nRow;//m������ǩ��member��,n��ʾnumber
	int     m_nCol;

	double* m_pData;//�洢���������
};


#endif //_MATRIX_H_
