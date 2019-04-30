// MatrixProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "Matrix.h"

#include <iostream>
#include<fstream>
int main()
{
	Matrix mat1;
	//std::cin >> mat;
	std::ifstream ifs("D:\\作业\\C++\\Matrix\\Matrix.txt");
		if (ifs)
			ifs >> mat1;
	//Matrix mat2;

	std::cout << "\n\n" << mat1;

	return 0;
}

