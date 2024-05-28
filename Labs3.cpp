#include <iostream>
using namespace std;

class matr;

class vect {
private:
  int dim;
  double *b;
  int num;
  static int count;

public:
  vect(int dimension);
  vect(double *array, int dimension);
  vect(const vect &v);
  ~vect();

  void print() const;

  vect &operator=(const vect &v);
  friend vect operator+(const vect &v1, const vect &v2);
  vect operator-(const vect &v) const;
  friend double operator*(const vect &v1, const vect &v2);
  friend vect operator*(double k, const vect &v);

  friend vect operator*(const matr &m, const vect &v);
};

class matr {
private:
  int dim1, dim2;
  double **b;
  int num;
  static int count;

public:
  matr(int dimension1, int dimension2);
  matr(double **array, int dimension1, int dimension2);
  matr(const matr &m);
  ~matr();

  void print() const;

  matr &operator=(const matr &m);
  friend matr operator+(const matr &m1, const matr &m2);
  matr operator-(const matr &m) const;

  friend matr operator*(const matr &m1, const matr &m2);
  friend matr operator*(double k, const matr &m);
  friend vect operator*(const matr &m, const vect &v);
};

int vect::count = 0;
int matr::count = 0;

vect::vect(int dimension) : dim(dimension), num(count++) {
  b = new double[dim]();
  cout << "Vector " << num << " constructed with zeros." << endl;
}

vect::vect(double *array, int dimension) : dim(dimension), num(count++) {
  b = new double[dim];
  for (int i = 0; i < dim; i++) {
    b[i] = array[i];
  }
  cout << "Vector " << num << " constructed from array." << endl;
}

vect::vect(const vect &v) : dim(v.dim), num(count++) {
  b = new double[dim];
  for (int i = 0; i < dim; i++) {
    b[i] = v.b[i];
  }
  cout << "Vector " << num << " copied from vector " << v.num << "." << endl;
}

vect::~vect() {
  delete[] b;
  cout << "Vector " << num << " destructed." << endl;
}

// Реализация методов класса vect
void vect::print() const {
  for (int i = 0; i < dim; i++) {
    cout << b[i] << " ";
  }
  cout << endl;
}

vect &vect::operator=(const vect &v) {
  if (this != &v) {
    if (dim != v.dim) {
      cerr << "Vector dimensions do not match." << endl;
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < dim; i++) {
      b[i] = v.b[i];
    }
  }
  return *this;
}

vect operator+(const vect &v1, const vect &v2) {
  if (v1.dim != v2.dim) {
    cerr << "Vector dimensions do not match." << endl;
    exit(EXIT_FAILURE);
  }
  vect result(v1.dim);
  for (int i = 0; i < v1.dim; i++) {
    result.b[i] = v1.b[i] + v2.b[i];
  }
  return result;
}

vect vect::operator-(const vect &v) const {
  if (dim != v.dim) {
    cerr << "Vector dimensions do not match." << endl;
    exit(EXIT_FAILURE);
  }
  vect result(dim);
  for (int i = 0; i < dim; i++) {
    result.b[i] = b[i] - v.b[i];
  }
  return result;
}

double operator*(const vect &v1, const vect &v2) {
  if (v1.dim != v2.dim) {
    cerr << "Vector dimensions do not match." << endl;
    exit(EXIT_FAILURE);
  }
  double result = 0.0;
  for (int i = 0; i < v1.dim; i++) {
    result += v1.b[i] * v2.b[i];
  }
  return result;
}

vect operator*(double k, const vect &v) {
  vect result(v.dim);
  for (int i = 0; i < v.dim; i++) {
    result.b[i] = k * v.b[i];
  }
  return result;
}

/////

matr::matr(int dimension1, int dimension2)
    : dim1(dimension1), dim2(dimension2), num(count++) {
  b = new double *[dim1];
  for (int i = 0; i < dim1; i++) {
    b[i] = new double[dim2]();
  }
  cout << "Matrix " << num << " constructed with zeros." << endl;
}

matr::matr(double **array, int dimension1, int dimension2)
    : dim1(dimension1), dim2(dimension2), num(count++) {
  b = new double *[dim1];
  for (int i = 0; i < dim1; i++) {
    b[i] = new double[dim2];
    for (int j = 0; j < dim2; j++) {
      b[i][j] = array[i][j];
    }
  }
  cout << "Matrix " << num << " constructed from array." << endl;
}

matr::matr(const matr &m) : dim1(m.dim1), dim2(m.dim2), num(count++) {
  b = new double *[dim1];
  for (int i = 0; i < dim1; i++) {
    b[i] = new double[dim2];
    for (int j = 0; j < dim2; ++j) {
      b[i][j] = m.b[i][j];
    }
  }
  cout << "Matrix " << num << " copied from matrix " << m.num << "." << endl;
}

matr::~matr() {
  for (int i = 0; i < dim1; i++) {
    delete[] b[i];
  }
  delete[] b;
  cout << "Matrix " << num << " destructed." << endl;
}

void matr::print() const {
  for (int i = 0; i < dim1; i++) {
    for (int j = 0; j < dim2; j++) {
      cout << b[i][j] << " ";
    }
    cout << endl;
  }
}

matr &matr::operator=(const matr &m) {
  if (this != &m) {
    if (dim1 != m.dim1 || dim2 != m.dim2) {
      cerr << "Matrix dimensions mismatch" << endl;
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dim1; i++) {
      for (int j = 0; j < dim2; j++) {
        b[i][j] = m.b[i][j];
      }
    }
  }
  return *this;
}

matr operator+(const matr &m1, const matr &m2) {
  if (m1.dim1 != m2.dim1 || m1.dim2 != m2.dim2) {
    cerr << "Matrix dimensions mismatch" << endl;
    exit(EXIT_FAILURE);
  }

  matr result(m1.dim1, m1.dim2);
  for (int i = 0; i < m1.dim1; i++) {
    for (int j = 0; j < m1.dim2; j++) {
      result.b[i][j] = m1.b[i][j] + m2.b[i][j];
    }
  }
  return result;
}

matr matr::operator-(const matr &m) const {
  if (dim1 != m.dim1 || dim2 != m.dim2) {
    cerr << "Matrix dimensions mismatch" << endl;
    exit(EXIT_FAILURE);
  }

  matr result(dim1, dim2);
  for (int i = 0; i < dim1; i++) {
    for (int j = 0; j < dim2; j++) {
      result.b[i][j] = b[i][j] - m.b[i][j];
    }
  }
  return result;
}

matr operator*(const matr &m1, const matr &m2) {
  if (m1.dim2 != m2.dim1) {
    cerr << "Matrix dimensions mismatch" << endl;
    exit(EXIT_FAILURE);
  }

  matr result(m1.dim1, m2.dim2);
  for (int i = 0; i < result.dim1; i++) {
    for (int j = 0; j < result.dim2; j++) {
      result.b[i][j] = 0;
      for (int k = 0; k < m1.dim2; k++) {
        result.b[i][j] += m1.b[i][k] * m2.b[k][j];
      }
    }
  }
  return result;
}

matr operator*(double k, const matr &m) {
  matr result(m.dim1, m.dim2);
  for (int i = 0; i < m.dim1; i++) {
    for (int j = 0; j < m.dim2; j++) {
      result.b[i][j] = k * m.b[i][j];
    }
  }
  return result;
}

vect operator*(const matr &m, const vect &v) {
  if (m.dim2 != v.dim) {
    cerr << "Matrix and Vector dimensions mismatch" << endl;
    exit(EXIT_FAILURE);
  }

  vect result(m.dim1);

  for (int i = 0; i < m.dim1; i++) {
    for (int j = 0; j < m.dim2; j++) {
      result.b[i] += m.b[i][j] * v.b[j];
    }
  }

  return result;
}

int main() {
  double *vectorData = new double[4];
  vectorData[0] = 1.0;
  vectorData[1] = 2.0;
  vectorData[2] = 3.0;
  vectorData[3] = 4.0;

  double **matrixData = new double *[4];
  for (int i = 0; i < 4; i++) {
    matrixData[i] = new double[4];
  }

  double initValue = 1.0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrixData[i][j] = initValue++;
    }
  }

  vect v1(4);
  vect v2(vectorData, 4);

  matr m1(4, 4);
  matr m2(matrixData, 4, 4);

  cout << "Vector v1: ";
  v1.print();
  cout << "Vector v2: ";
  v2.print();
  cout << "Matrix m1: " << endl;
  m1.print();
  cout << "Matrix m2: " << endl;
  m2.print();

  vect v3 = v1 + v2;
  vect v4 = v2 - v1;
  double dotProduct = v4 * v2;
  vect v5 = 2.0 * v1;

  matr m3 = m1 + m2;
  matr m4 = m2 - m1;
  matr m5 = m3 * m2;
  matr m6 = 2.0 * m2;

  vect v6 = m2 * v2;

  cout << "Vector v3 (v1 + v2): ";
  v3.print();
  cout << "Vector v4 (v2 - v1): ";
  v4.print();
  cout << "Dot product (v4 * v2): " << dotProduct << endl;
  cout << "Vector v5 (2.0 * v1): ";
  v5.print();
  cout << "Matrix m3 (m1 + m2): ";
  m3.print();
  cout << "Matrix m4 (m2 - m1): " << endl;
  m4.print();
  cout << "Matrix m5 (m3 * m2): " << endl;
  m5.print();
  cout << "Matrix m6 (2.0 * m2): " << endl;
  m6.print();
  cout << "Vector v6 (m2 * v2): ";
  v6.print();

  return 0;
}