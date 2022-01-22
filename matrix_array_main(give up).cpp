/*
Auther: John Blue
Time: 2022/1
Platform: ATOM with MinGw and g++compiler
Object: Test Template Size Matrix
Version:
matrix_allocate.h(Dynamic Allocate Matrix)
matrix_array.h(Template Size Matrix)
*/

#include <iostream>
#include "matrix_array.h"// template matrix class

int main()
{
	// normal 2D array
	const int M = 3;
	const int N = 3;
	float MA[M][N] = { 1.0,1.0,1.0 ,2.0,2.0,2.0 ,3.0,3.0,33.0 };
	// object
	Matrix<M, N> MT = Matrix<M, N>(MA);
	std::cout << "MT =\n" << MT << std::endl;
	// mutate
	std::cout << "Mutate MT ..." << std::endl;
	MT(2, 2) = 3;
	std::cout << "MT =\n" << MT << std::endl;
	// mutiplication
	//float MAR[N][1] = {1, 1, 1};
	//Matrix MTR(N, 1, &MAR[0][0]);
	// MT + MT
	//std::cout << "MT + MT =\n" << MT + MT << "\n";
	// MT - MT
	//std::cout << "MT - MT =\n" << MT - MT << "\n";
	// MT * 3
	//std::cout << "MT * 3 =\n" << MT * 3 << "\n";
	// 3 * MT
	//std::cout << "3 * MT =\n" << (float)3 * MT << "\n";
	// MT * MTR
	//std::cout << "MT * MTR =\n" << MT * MTR << "\n";
	//
	// det and inverse
	//     2,1,2
	// M = 3,2,2
	//     1,2,3
	// det(M) = 5
	//                  2,   1, - 2
	// inv(M) = 0.2 * - 7,   4,   2
	//                  4, - 3,   1
	//float MAI[M][N] = { 2,1,2 ,3,2,2 ,1,2,3 };
	//Matrix MTI(M, N, &MAI[0][0]);
	//std::cout << "tran(MTI) =\n" << MTI.tran() << "\n";
	//std::cout << "det(MTI) =\n" << MTI.det() << "\n\n";
	//std::cout << "inv(MTI) =\n" << MTI.inv() << "\n";
	//
	// LU
	//std::cout << "LU(MTI) =\n" << MTI.LU() << "\n";
}
