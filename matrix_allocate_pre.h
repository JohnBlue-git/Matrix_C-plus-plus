/*
Auther: John Blue
legacy of template Matrix: ..., inverse with trim
*/

#include <iostream>// basic i/o
#include <string>// std::string operation
#include <typeinfo>// determine data type
#include <iomanip>// fixed and setprecision
#include <cmath>// pow(...)
#include <stdexcept>// determine exception

// template prototypes
// a friend operator or function will need these
// but not really work well
/*
https://en.cppreference.com/w/cpp/language/friend?fbclid=IwAR2EFWdGtqcSYLfm1rXL9O12M7hfyr92Pt83asgepRZuvaKQsUGTwAdLsTEtemplate%3Cclass
*/
/*
template<class T> class Matrix;
template<class T> Matrix<T> operator+(const Matrix<T>& X, const Matrix<T>& Y);
template<class T> Matrix<T> operator-(const Matrix<T>& X, const Matrix<T>& Y);
template<class T> Matrix<T> operator*(const Matrix<T>& X, const Matrix<T>& Y);
template<class T>template<class U> Matrix<T> operator*(const U n, const Matrix<T>& X);
template<class T> std::ostream& operator<<(std::ostream&, const Matrix<T>& X);
*/


// different between template class and template typename
/*
https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates#:~:targetText=For%20naming%20template%20parameters%2C%20typename%20and%20class%20are%20equivalent.&targetText=There%20is%20no%20semantic%20difference,referring%20to%20a%20dependent%20type.
*/
template<class T>
class Matrix {
private:
	// var
	unsigned int M, N;// col number and row number
	T** ad;// storage data
public:
	// constructor
	Matrix() : M(0), N(0), ad(0) {};// default constructor
	Matrix(unsigned int a, unsigned int b, T* c = 0);
	Matrix(const Matrix& copy);// copy constructor !!! return will used it
	~Matrix();
	//operator
// (i,j) address operator
	T& operator()(const unsigned int i, const unsigned int j);
	T operator()(const unsigned int i, const unsigned int j) const;
	// =
	Matrix& operator=(const Matrix& X);
	// +
	template<class T> friend Matrix<T> operator+ (const Matrix<T>& X, const Matrix<T>& Y);
	Matrix& operator+=(const Matrix& X);
	// -
	template<class T> friend Matrix<T> operator-(const Matrix<T>& X, const Matrix<T>& Y);
	Matrix& operator-=(const Matrix& X);
	Matrix operator-() const;// - *this
// *
	template<class T> friend Matrix<T> operator*(const Matrix<T>& X, const Matrix<T>& Y);
	Matrix operator*(const T n) const;// *this * n
	// n * *this
	// why not operator* <> because it's not work, but i don't know @@
	template<class T> friend Matrix<T> operator*(const T n, const Matrix<T>& X);
	// <<
	template<class T> friend std::ostream& operator<< (std::ostream& os, const Matrix<T>& X);
	// function
	Matrix trim(const unsigned int c, const unsigned int r) const;// will be used in det() and inv()
	Matrix tran() const;
	T det() const;
	Matrix inv() const;
	// exception class
// empty
	class bad_empty : public std::logic_error
	{
	public:
		explicit bad_empty(const std::string & s = " ") :std::logic_error(s + ", Empty error in Matrix object\n") {};
		virtual ~bad_empty() throw() {}
	};
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
	// type
	// when to use
	// (typeid(T) != typeid(double)
	class bad_type : public std::logic_error
	{
	public:
		explicit bad_type(const std::string & s = " ") :std::logic_error(s + ", Type error in Matrix object\n") {};
		virtual ~bad_type() throw() {}
	};
};


template<class T>
Matrix<T>::Matrix(unsigned int a, unsigned int b, T* c) : M(a), N(b) {
	// assign size :M(a)...
	// assign ad
	ad = new T*[M];
	for (unsigned int i = 0; i < M; i++) {
		ad[i] = new T[N];
		for (unsigned int j = 0; j < N; j++) {
			// if the user don't give c, default is NULL
			if (c == 0) {
				ad[i][j] = 0;
			}
			// if the user give c
			else {
				ad[i][j] = *c++;//ad[i][j] = c[N * i + j];
			}
		}
	}
}

template<class T>
Matrix<T>::Matrix(const Matrix& copy) {
	// assign size
	M = copy.M;
	N = copy.N;
	// assign ad
	ad = new T*[M];
	for (unsigned int i = 0; i < M; i++) {
		ad[i] = new T[N];
		for (unsigned int j = 0; j < N; j++) {
			ad[i][j] = copy.ad[i][j];
		}
	}
}

template<class T>
Matrix<T>::~Matrix() {
	// if not empty
	if (ad != 0) {
		for (unsigned int i = 0; i < M; i++) {
			delete[] ad[i];
		}
		delete[] ad;
		ad = 0;
	}
}

template<class T>
T& Matrix<T>::operator()(const unsigned int i, const unsigned int j) {
	// empty ?
	if (ad == 0) {
		throw bad_empty("() operation");
	}
	// bad index ?
	if ((i < 0 && i >= M) || (j < 0 && j >= N)) {
		throw bad_index(i, j, "() operation");
	}
	// return
	return ad[i][j];
}

template<class T>
T Matrix<T>::operator()(const unsigned int i, const unsigned int j) const {
	// empty ?
	if (ad == 0) {
		throw bad_empty("() operation");
	}
	// bad index ?
	if ((i < 0 && i >= M) || (j < 0 && j >= N)) {
		throw bad_index(i, j, "() operation");
	}
	// return
	return ad[i][j];
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& copy) {
	// assign to itself ?
	if (&copy == this) {
		return *this;
	}
	// empty ?
	if (ad != 0) {
		this->~Matrix();
	}
	// using copy
	this->Matrix<T>::Matrix(copy);
	// return
	return *this;
}

template<class T>
Matrix<T> operator+(const Matrix<T>& X, const Matrix<T>& Y) {
	// empty ?
	if (X.ad == 0 || Y.ad == 0) {
		throw Matrix<T>::bad_empty("+ operation");
	}
	// size unmatch ?
	if (X.M != Y.M || X.N != Y.N) {
		throw Matrix<T>::bad_unmatch("+ operation");
	}
	// create new matrix for return
	Matrix<T> Z(X.M, X.N);
	// addition
	for (unsigned int i = 0; i < X.M; i++) {
		for (unsigned int j = 0; j < X.N; j++) {
			Z.ad[i][j] = X.ad[i][j] + Y.ad[i][j];
		}
	}
	// return
	return Z;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& X) {
	// empty ?
	if (X.ad == 0) {
		throw bad_empty("+= operation");
	}
	// size unmatch ?
	if (X.M != M || X.N != N) {
		throw bad_unmatch("+= operation");
	}
	// addition
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			ad[i][j] += X.ad[i][j];
		}
	}
	// return
	return *this;
}

template<class T>
Matrix<T> operator-(const Matrix<T>& X, const Matrix<T>& Y) {
	// empty ?
	if (X.ad == 0 || Y.ad == 0) {
		throw Matrix<T>::bad_empty("- operation");
	}
	// size unmatch ?
	if (X.M != Y.M || X.N != Y.N) {
		throw Matrix<T>::bad_unmatch("- operation");
	}
	// create new matrix for return
	Matrix<T> Z(X.M, X.N);
	// dedection
	for (unsigned int i = 0; i < X.M; i++) {
		for (unsigned int j = 0; j < X.N; j++) {
			Z.ad[i][j] = X.ad[i][j] - Y.ad[i][j];
		}
	}
	// return
	return Z;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& X) {
	// empty ?
	if (X.ad == 0) {
		throw bad_empty("-= operation");
	}
	// size unmatch ?
	if (X.M != M || X.N != N) {
		throw bad_unmatch("- operation");
	}
	// deduction
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			ad[i][j] -= X.ad[i][j];
		}
	}
	// return
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const {
	// empty ?
	if (ad == 0) {
		throw bad_empty("-() operation");
	}
	// create new matrix for return
	Matrix<T> Y(M, N);
	// multiplied by minus
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			Y.ad[i][j] -= ad[i][j];
		}
	}
	// return
	return Y;
}

template<class T>
Matrix<T> operator*(const Matrix<T>& X, const Matrix<T>& Y) {
	// empty ?
	if (X.ad == 0 || Y.ad == 0) {
		throw Matrix<T>::bad_empty("* operation");
	}
	// size unmatch
	if (X.N != Y.M) {
		throw Matrix<T>::bad_unmatch("* operation");
	}
	// create new matrix for return
	Matrix<T> Z(X.M, Y.N);
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

template<class T>
Matrix<T> Matrix<T>::operator*(const T n) const {
	// empty ?
	if (ad == 0) {
		throw bad_empty(" * n operation");
	}
	// create new matrix for return
	Matrix<T> Y(M, N);
	// multiplication
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			Y.ad[i][j] = n * ad[i][j];
		}
	}
	// return
	return Y;
}

template<class T>
Matrix<T> operator*(const T n, const Matrix<T>& X) {
	// empty ?
	if (X.ad == 0) {
		throw Matrix<T>::bad_empty(" n * operation");
	}
	// using Matrix * n
	return X.Matrix<T>::operator*(n);
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& X) {
	// empty ?
	if (X.ad == 0) {
		throw Matrix<T>::bad_empty("<< operation");
	}
	// if double
	if (typeid(T) == typeid(double)) {
		for (unsigned int i = 0; i < X.M; i++) {
			for (unsigned int j = 0; j < X.N; j++) {
				os << std::fixed << std::setprecision(3) << X.ad[i][j] << " ";//<< std::fixed << std::setprecision(3)
			}
			os << "" << std::endl;
		}
	}
	// not double
	else {
		for (unsigned int i = 0; i < X.M; i++) {
			for (unsigned int j = 0; j < X.N; j++) {
				os << X.ad[i][j] << " ";
			}
			os << "" << std::endl;
		}
	}
	// return
	return os;
}

template<class T>
Matrix<T> Matrix<T>::trim(const unsigned int c, const unsigned int r) const {
	// empty ?
	if (ad == 0) {
		throw bad_empty("trim() function");
	}
	// create new matrix for return
	// size will be one dim less than *this on both col and row
	Matrix<T> Y(M - 1, N - 1);
	// index for assign value to new matrix
	unsigned int yi, yj;
	// assign value to new matrix
	// set col index
	yi = 0;
	for (unsigned int i = 0; i < M; i++) {
		// reset row index
		yj = 0;
		// if col match the col that want to trim, skip this round
		if (i == c) {
			continue;
		}
		for (unsigned int j = 0; j < N; j++) {
			// if row match the row that want to trim, skip this round
			if (j == r) {
				continue;
			}
			// assign value
			Y.ad[yi][yj] = ad[i][j];
			// update row index
			yj++;
		}
		// update col index
		yi++;
	}
	// return
	return Y;
}

template<class T>
Matrix<T> Matrix<T>::tran() const {
	// empty ?
	if (ad == 0) {
		throw bad_empty("tran() function");
	}
	// create new traspose matrix for return
	Matrix<T> Y(N, M);
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

template<class T>
T Matrix<T>::det() const {
	// empty ?
	if (ad == 0) {
		throw bad_empty("det() function");
	}
	// size unmatch ?
	if (M != N) {
		throw bad_unmatch("not square for det() function");
	}
	// initial return value
	T value = 0;
	// if *this dimension is 1
	if (M == 1) {
		value = ad[0][0];
	}
	// if *this dimension is 2
	else if (M == 2) {
		value = ad[0][0] * ad[1][1] - ad[0][1] * ad[1][0];
	}
	// if *this dimension is more than 2, than use minor and �Դ��Դ��i�}
	else {
		for (int i = 0; i < N; i++) {
			value += ad[0][i] * (*this).Matrix<T>::trim(0, i).Matrix<T>::det() * pow(-1, i);
		}
	}
	// return
	return value;
}

template<class T>
Matrix<T> Matrix<T>::inv() const {
	// empty ?
	if (ad == 0) {
		throw bad_empty("inv() function");
	}
	// size unmatch ?
	if (M != N) {
		throw bad_unmatch("not square for inv() function");
	}
	// det
	T Det = this->Matrix<T>::det();
	// invertible ?
	if (Det == 0) {
		throw Matrix<T>::bad_invertible(" ");
	}
	// create new traspose matrix for return
	Matrix<T> Y(M, N);
	// if *this dimension is 1
	if (M == 1) {
		Y.ad[0][0] = 1;
	}
	// if *this dimension is 2
	else if (M == 2) {
		Y.ad[0][0] = ad[1][1];
		Y.ad[0][1] = -ad[0][1];
		Y.ad[1][0] = -ad[1][0];
		Y.ad[1][1] = ad[0][0];
	}
	// if *this dimension is more than 2, then use adjacent method
	else {
		for (unsigned int i = 0; i < M; i++) {
			for (unsigned int j = 0; j < N; j++) {
				Y.ad[i][j] = (*this).Matrix<T>::trim(i, j).Matrix<T>::det() * pow(-1, i + j);
			}
		}
		Y = Y.Matrix<T>::tran();
	}
	// division by det
	Y = Y.Matrix<T>::operator*(1 / Det);
	// return
	return Y;
}
