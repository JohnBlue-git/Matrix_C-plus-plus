/*
Auther: John Blue
Time: 2022/1
Platform: ATOM with MinGw and g++compiler
Object: Template Size Matrix
Version:
matrix_allocate.h(Dynamic Allocate Matrix)
matrix_array.h(Template Size Matrix)
*/

#include <iostream>// basic i/o
#include <string>// std::string operation
#include <typeinfo>// determine data type
#include <iomanip>// fixed and setprecision
#include <cmath>// pow(...)
#include <stdexcept>// determine exception

template<size_t m, size_t n>
class Matrix {
private:
	// var
	int M, N;// col number and row number
	float ad[m][n];// storage data

	// function
	//float det_loop(int n, int* r, int* c) const;
public:
	// constructor
	Matrix(float (&c)[m][n]);
	Matrix(const Matrix& copy);
	~Matrix();

	//operator
	// (i,j) address operator
	float& operator()(const int i, const int j);
	float operator()(const int i, const int j) const;
	// =
	Matrix& operator=(const Matrix& X);
	// +
	friend Matrix operator+(const Matrix& X, const Matrix& Y);
	Matrix& operator+=(const Matrix& X);
	// -
	friend Matrix operator-(const Matrix& X, const Matrix& Y);
	Matrix& operator-=(const Matrix& X);
	Matrix operator-() const;// - *this
// *
	friend Matrix operator*(const Matrix& X, const Matrix& Y);
	Matrix operator*(const float n) const;// *this * n
	// n * *this
	// why not operator* <> because it's not work, but i don't know @@
	friend Matrix operator*(const float n, const Matrix& X);
	// <<
	friend std::ostream& operator<<(std::ostream& os, const Matrix& X);
/*
	// function
	Matrix tran() const;
	float det() const;
	Matrix inv() const;

	// function
	Matrix LU() const;

	// exception class
	// index out of range
	class bad_index : public std::logic_error
	{
	private:
		int x; // bad index value
		int y; // bad index value
	public:
		explicit bad_index(int ix = 0, int iy = 0, const std::string & s = " ") :x(ix), y(iy), std::logic_error(s + ", Index error in Matrix object\n") {};
		int get_x() const { return x; }
		int get_y() const { return y; }
		virtual ~bad_index() throw() {}
	};
	// martix size unmatch for operation
	class bad_unmatch : public std::logic_error
	{
	public:
		explicit bad_unmatch(const std::string & s = " ") :std::logic_error(s + ", Size unmatch error in Matrix object\n") {};
		virtual ~bad_unmatch() throw() {}
	};
	// not invertible
	class bad_invertible : public std::logic_error
	{
	public:
		explicit bad_invertible(const std::string & s = " ") :std::logic_error(s + ", Not invertible error in Matrix object\n") {};
		virtual ~bad_invertible() throw() {}
	};
	*/
};

////// .cpp

template<size_t m, size_t n>
Matrix<m, n>::Matrix(float (&c)[m][n]): M(m), N(n) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			ad[i][j] = c[i][j];
		}
	}
}

template<size_t m, size_t n>
Matrix<m, n>::Matrix(const Matrix& copy): M(m), N(n) {
	// assign ad
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			ad[i][j] = copy.ad[i][j];
		}
	}
}

template<size_t m, size_t n>
Matrix<m, n>::~Matrix() {
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; i < N; j++) {
			ad[i][j] = 0;
		}
	}
	M = 0;
	N = 0;
}

template<size_t m, size_t n>
float& Matrix<m, n>::operator()(const int i, const int j) {
	// bad index ?
	//if ((i < 0 && i >= M) || (j < 0 && j >= N)) {
		//throw bad_index(i, j, "() operation");
	//}
	// return
	return ad[i][j];
}

template<size_t m, size_t n>
float Matrix<m, n>::operator()(const int i, const int j) const {
	// bad index ?
	//if ((i < 0 && i >= M) || (j < 0 && j >= N)) {
		//throw bad_index(i, j, "() operation");
	//}
	// return
	return ad[i][j];
}

template<size_t m, size_t n>
Matrix<m, n>& Matrix<m, n>::operator=(const Matrix<m, n>& copy) {
	// assign to itself ?
	if (&copy == this) {
		return *this;
	}
	// empty it
	this->~Matrix();
	// copy
	M = m;
	N = n;
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			ad[i][j] = copy.ad[i][j];
		}
	}
	// return
	return *this;
}

template<size_t m, size_t n>
Matrix<m, n> Matrix<m, n>::operator+(const Matrix<m, n>& X, const Matrix<m, n>& Y) {
	// create new matrix for return
	Matrix Z(X.M, X.N);
	// addition
	for (unsigned int i = 0; i < X.M; i++) {
		for (unsigned int j = 0; j < X.N; j++) {
			Z.ad[i][j] = X.ad[i][j] + Y.ad[i][j];
		}
	}
	// return
	return Z;
}

Matrix& Matrix::operator+=(const Matrix& X) {
	// empty ?
	//if (X.ad == 0) {
		//throw bad_empty("+= operation");
	//}
	// size unmatch ?
	//if (X.M != M || X.N != N) {
		//throw bad_unmatch("+= operation");
	//}
	// addition
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			ad[i][j] += X.ad[i][j];
		}
	}
	// return
	return *this;
}

Matrix operator-(const Matrix& X, const Matrix& Y) {
	// empty ?
	//if (X.ad == 0 || Y.ad == 0) {
		//throw Matrix<T>::bad_empty("- operation");
	//}
	// size unmatch ?
	//if (X.M != Y.M || X.N != Y.N) {
		//throw Matrix<T>::bad_unmatch("- operation");
	//}
	// create new matrix for return
	Matrix Z(X.M, X.N);
	// dedection
	for (unsigned int i = 0; i < X.M; i++) {
		for (unsigned int j = 0; j < X.N; j++) {
			Z.ad[i][j] = X.ad[i][j] - Y.ad[i][j];
		}
	}
	// return
	return Z;
}

Matrix& Matrix::operator-=(const Matrix& X) {
	// size unmatch ?
	//if (X.M != M || X.N != N) {
		//throw bad_unmatch("- operation");
	//}
	// deduction
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			ad[i][j] -= X.ad[i][j];
		}
	}
	// return
	return *this;
}

Matrix Matrix::operator-() const {
	// create new matrix for return
	Matrix Y(M, N);
	// multiplied by minus
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			Y.ad[i][j] -= ad[i][j];
		}
	}
	// return
	return Y;
}

Matrix operator*(const Matrix& X, const Matrix& Y) {
	// size unmatch
	//if (X.N != Y.M) {
		//throw Matrix<T>::bad_unmatch("* operation");
	//}
	// create new matrix for return
	Matrix Z(X.M, Y.N);
	// multiplication
	for (unsigned int i = 0; i < X.M; i++) {
		for (unsigned int j = 0; j < Y.N; j++) {
			for (unsigned int k = 0; k < X.N; k++) {
				Z.ad[i][j] += X.ad[i][k] * Y.ad[k][j];
			}
		}
	}
	// return
	return Z;
}

Matrix Matrix::operator*(const float n) const {
	// create new matrix for return
	Matrix Y(M, N);
	// multiplication
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			Y.ad[i][j] = n * ad[i][j];
		}
	}
	// return
	return Y;
}

Matrix operator*(const float n, const Matrix& X) {
	// using Matrix * n
	return X.operator*(n);
}

std::ostream& operator<<(std::ostream& os, const Matrix& X) {
	for (unsigned int i = 0; i < X.M; i++) {
		for (unsigned int j = 0; j < X.N; j++) {
			os << std::fixed << std::setprecision(3) << X.ad[i][j] << " ";//<< std::fixed << std::setprecision(3)
		}
		os << "\n";
	}
	// return
	return os;
}

Matrix Matrix::tran() const {
	// create new traspose matrix for return
	Matrix Y(N, M);
	// assign value to new matrix
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			// assign in traspose way
			Y.ad[j][i] = ad[i][j];
		}
	}
	// return
	return Y;
}

// det
//https://zh.wikipedia.org/wiki/%E8%A1%8C%E5%88%97%E5%BC%8F
// * can represent a matrice
// size, r[], c[]
// ex: 3 x 3
// *0*0 0*1 0*2
//  *10  11  12
//  *20  21  22
// ex: 2 x 2
// *1*1 1*2
//  *21  22
// ex: 2 x 2
// *1*0 1*2
//  *20  22
//
float Matrix::det_loop(int n, int* r, int* c) const {
	// if *this dimension is 1
	if (n == 1) {
		return ad[r[0]][c[0]];
	}
	// if *this dimension is 2
	else if (n == 2) {
		return ad[r[0]][c[0]] * ad[r[1]][c[1]] - ad[r[0]][c[1]] * ad[r[1]][c[0]];
	}
	// if *this dimension is more than 2, than use minor and ...
	else {
		// initial value
		float value = 0;
		int* r_next = new int[n - 1];
		int* c_next = new int[n - 1];
		// loop
		for (int j = 0; j < n; j++) {
			// next row col
			int kr = 0;
			int kc = 0;
			for (int k = 0; k < n; k++) {
				// r_next
				if (k != 0) {
					r_next[kr++] = r[k];
				}
				// c_next
				if (k != j) {
					c_next[kc++] = c[k];
				}
			}
			// add up
			value += ad[r[0]][c[j]] * det_loop(n - 1, r_next, c_next) * pow(- 1, j);
			}
		// delete
		delete r_next;
		delete c_next;
		// return
		return value;
	}
}

float Matrix::det() const {
	// size unmatch ?
	//if (M != N) {
		//throw bad_unmatch("not square for det() function");
	//}
	// initialize
	int* r = new int[M];
	int* c = new int[M];
	for (int i = 0; i < M; i++) {
		r[i] = i;
		c[i] = i;
	}
	// det
	float value = det_loop(M, r, c);
	// delete
	delete r;
	delete c;
	// return
	return value;
}

// inv
//https://en.wikipedia.org/wiki/Invertible_matrix
//
Matrix Matrix::inv() const {
	// size unmatch ?
	//if (M != N) {
		//throw bad_unmatch("not square for inv() function");
	//}
	// invertible ?
	//if (Det == 0) {
		//throw Matrix<T>::bad_invertible(" ");
	//}
	// det
	float dt = det();
	// create new matrix for return
	Matrix Y(M, M);
	// inv
	// if *this dimension is 1
	if (M == 1) {
		Y.ad[0][0] = 1;
	}
	// if *this dimension is more than 2, then use adjacent method
	else {
		// initial vlue
		int* r_next = new int[M - 1];
		int* c_next = new int[M - 1];
		// loop
		for (unsigned int i = 0; i < M; i++) {
			for (unsigned int j = 0; j < M; j++) {
				// next row col
				int kr = 0;
				int kc = 0;
				for (int k = 0; k < M; k++) {
					if (k != i) {
						r_next[kr++] = k;
					}
					if (k != j) {
						c_next[kc++] = k;
					}
				}
				// sub det and tran at the same time
				Y.ad[j][i] = det_loop(M - 1, r_next, c_next) * pow(- 1, i + j);
			}
		}
		// delete
		delete r_next;
		delete c_next;
	}
	// division by det
	Y = Y * (1 / dt);
	// return
	return Y;
}

// LU
//https://zh.wikipedia.org/wiki/LU%E5%88%86%E8%A7%A3
//
// LU == M
//
// I = invL LU invU
// L I invL = L invL LU invU invL
//   I      = LU invU invL
//     invM =    invU invL
//
// multiple to left (row operation)
// r1 = r1 * d1 + r2 * n1
// r2 = r1 * n2 + r2 * d2
//    c1 c2
// r1 d1 n1
// r2 n2 d2
//
// multiple to right (col operation)
// c1 = c1 * d1 + c2 * n1
// c2 = c1 * n2 + c2 * d2
//    c1 c2
// r1 d1 n2
// r2 n1 d2
//
// multiple to left is different from to right
//    c1 c2
// r1 d1 0
// r2 0  0
//
// method 1
// become Upper == row operation == multiple with left matrix  == invL * M
// become Lower == row operation == multiple with left matrix  == invU * invL * M
//
// method 2
// become Lower == column operation == multiple with right matrix == M * invU
// become Upper == column operation == multiple with right matrix == M * invU * invL
//
Matrix Matrix::LU() const {
	// size unmatch ?
	//if (M != N) {
		//throw bad_unmatch("not square for inv() function");
	//}
	// invertible ?
	//if (Det == 0) {
		//throw Matrix<T>::bad_invertible(" ");
	//}
	// LU
	// initialize
	Matrix Daul(*this);
	Matrix I(M, M);
	for (int i = 0; i < M; i++) {
		I.ad[i][i] = 1;
	}
	////// become Upper
	for (int i = 0; i < (M - 1); i++) {
		// unit
		if (Daul.ad[i][i] != 1) {
			float den = Daul.ad[i][i];
			for (int j = 0; j < M; j++) {
				Daul.ad[i][j] /= den;
				I.ad[i][j] /= den;
			}
		}
		// deduction
		for (int ii = i + 1; ii < M; ii++) {
			if (Daul.ad[ii][i] != 0) {
				float den = Daul.ad[ii][i] / Daul.ad[i][i];
				for (int j = 0; j < M; j++) {
					Daul.ad[ii][j] -= Daul.ad[i][j] * den;
					I.ad[ii][j] -= I.ad[i][j] * den;
				}
			}
		}
	}
	////// become Lower
	for (int i = M - 1; i > 0; i--) {
		// unit
		if (Daul.ad[i][i] != 1) {
			float den = Daul.ad[i][i];
			for (int j = 0; j < M; j++) {
				Daul.ad[i][j] /= den;
				I.ad[i][j] /= den;
			}
		}
		// deduction
		for (int ii = i - 1; ii > - 1; ii--) {
			if (Daul.ad[ii][i] != 0) {
				float den = Daul.ad[ii][i] / Daul.ad[i][i];
				for (int j = 0; j < M; j++) {
					Daul.ad[ii][j] -= Daul.ad[i][j] * den;
					I.ad[ii][j] -= I.ad[i][j] * den;
				}
			}
		}
	}
	////// return
	return I;
}
*/
