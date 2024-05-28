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
  vect(int d) : dim(d), num(++count) {
    b = new double[dim];
    for (int i = 0; i < dim; ++i) {
      b[i] = 0;
    }
    cout << "Конструктор вектора: объект №" << num << endl;
  }

  vect(int d, const double *arr) : dim(d), num(++count) {
    b = new double[dim];
    for (int i = 0; i < dim; ++i) {
      b[i] = arr[i];
    }
    cout << "Конструктор вектора с массивом: объект №" << num << endl;
  }

  ~vect() {
    delete[] b;
    cout << "Деструктор вектора: объект №" << num << endl;
    --count;
  }

  vect(const vect &v) : dim(v.dim), num(++count) {
    b = new double[dim];
    for (int i = 0; i < dim; ++i) {
      b[i] = v.b[i];
    }
    cout << "Конструктор копирования вектора: объект №" << num << endl;
  }

  void print() const {
    cout << "Вектор объект №" << num << ": [ ";
    for (int i = 0; i < dim; ++i) {
      cout << b[i] << " ";
    }
    cout << "]" << endl;
  }

  // Операторы
  friend vect operator+(const vect &v1, const vect &v2);
  friend vect operator-(const vect &v1, const vect &v2);
  vect operator-() const;
  friend double operator*(const vect &v1, const vect &v2);
  friend vect operator*(double k, const vect &v);
  vect &operator=(const vect &v);

  friend vect operator*(const matr &m, const vect &v);

  static int getCount() { return count; }
};

vect operator+(const vect &v1, const vect &v2) {
  if (v1.dim != v2.dim) {
    cout << "Размерности векторов не совпадают!" << endl;
    exit(1);
  }
  vect sum(v1.dim);
  for (int i = 0; i < v1.dim; ++i) {
    sum.b[i] = v1.b[i] + v2.b[i];
  }
  return sum;
}

vect operator-(const vect &v1, const vect &v2) {
  if (v1.dim != v2.dim) {
    cout << "Размерности векторов не совпадают!" << endl;
    exit(1);
  }
  vect diff(v1.dim);
  for (int i = 0; i < v1.dim; ++i) {
    diff.b[i] = v1.b[i] - v2.b[i];
  }
  return diff;
}

vect vect::operator-() const {
  vect neg(dim);
  for (int i = 0; i < dim; ++i) {
    neg.b[i] = -b[i];
  }
  return neg;
}

double operator*(const vect &v1, const vect &v2) {
  if (v1.dim != v2.dim) {
    cout << "Размерности векторов не совпадают!" << endl;
    exit(1);
  }
  double product = 0.0;
  for (int i = 0; i < v1.dim; ++i) {
    product += v1.b[i] * v2.b[i];
  }
  return product;
}

vect operator*(double k, const vect &v) {
  vect scaled(v.dim);
  for (int i = 0; i < v.dim; ++i) {
    scaled.b[i] = k * v.b[i];
  }
  return scaled;
}

vect &vect::operator=(const vect &v) {
  if (this == &v) {
    return *this;
  }
  if (dim != v.dim) {
    cout << "Размерности векторов не совпадают!" << endl;
    exit(1);
  }
  for (int i = 0; i < dim; ++i) {
    b[i] = v.b[i];
  }
  return *this;
}

int vect::count = 0;

class matr {
private:
  int dim1, dim2;
  double **b;
  int num;
  static int count;

public:
  matr(int d1, int d2) : dim1(d1), dim2(d2), num(++count) {
    b = new double *[dim1];
    for (int i = 0; i < dim1; ++i) {
      b[i] = new double[dim2];
      for (int j = 0; j < dim2; ++j) {
        b[i][j] = 0;
      }
    }
    cout << "Конструктор матрицы: объект №" << num << endl;
  }

  matr(int d1, int d2, double **array) : dim1(d1), dim2(d2), num(++count) {
    b = new double *[dim1];
    for (int i = 0; i < dim1; ++i) {
      b[i] = new double[dim2];
      for (int j = 0; j < dim2; ++j) {
        b[i][j] = array[i][j];
      }
    }
    cout << "Конструктор матрицы с массивом: объект №" << num << endl;
  }

  ~matr() {
    for (int i = 0; i < dim1; ++i) {
      delete[] b[i];
    }
    delete[] b;
    cout << "Деструктор матрицы: объект №" << num << endl;
    --count;
  }

  void print() const {
    cout << "Матрица объект №" << num << ":" << endl;
    for (int i = 0; i < dim1; ++i) {
      for (int j = 0; j < dim2; ++j) {
        cout << b[i][j] << " ";
      }
      cout << endl;
    }
  }

  // Операторы
  friend matr operator+(const matr &m1, const matr &m2);
  friend matr operator-(const matr &m1, const matr &m2);
  matr operator-() const;
  friend matr operator*(const matr &m1, const matr &m2);
  friend matr operator*(double k, const matr &m);
  matr &operator=(const matr &m);
  friend vect operator*(const matr &m, const vect &v);

  static int getCount() { return count; }
};

int matr::count = 0;

matr operator+(const matr &m1, const matr &m2) {
  if (m1.dim1 != m2.dim1 || m1.dim2 != m2.dim2) {
    cout << "Размерности матриц не совпадают для сложения." << endl;
    exit(1);
  }

  matr result(m1.dim1, m1.dim2);
  for (int i = 0; i < m1.dim1; ++i) {
    for (int j = 0; j < m1.dim2; ++j) {
      result.b[i][j] = m1.b[i][j] + m2.b[i][j];
    }
  }

  return result;
}

matr operator-(const matr &m1, const matr &m2) {
  if (m1.dim1 != m2.dim1 || m1.dim2 != m2.dim2) {
    cout << "Размерности матриц не совпадают для вычитания." << endl;
    exit(1);
  }

  matr result(m1.dim1, m1.dim2);
  for (int i = 0; i < m1.dim1; ++i) {
    for (int j = 0; j < m1.dim2; ++j) {
      result.b[i][j] = m1.b[i][j] - m2.b[i][j];
    }
  }

  return result;
}

matr matr::operator-() const {
  matr result(dim1, dim2);
  for (int i = 0; i < dim1; ++i) {
    for (int j = 0; j < dim2; ++j) {
      result.b[i][j] = -b[i][j];
    }
  }

  return result;
}

matr operator*(const matr &m1, const matr &m2) {
  if (m1.dim2 != m2.dim1) {
    cout << "Размерности матриц не совпадают для умножения." << endl;
    exit(1);
  }

  matr result(m1.dim1, m2.dim2);
  for (int i = 0; i < result.dim1; ++i) {
    for (int j = 0; j < result.dim2; ++j) {
      for (int k = 0; k < m1.dim2; ++k) {
        result.b[i][j] += m1.b[i][k] * m2.b[k][j];
      }
    }
  }

  return result;
}

matr operator*(double k, const matr &m) {
  matr result(m.dim1, m.dim2);
  for (int i = 0; i < m.dim1; ++i) {
    for (int j = 0; j < m.dim2; ++j) {
      result.b[i][j] = k * m.b[i][j];
    }
  }

  return result;
}

matr &matr::operator=(const matr &m) {
  if (this != &m) {
    for (int i = 0; i < dim1; ++i) {
      delete[] b[i];
    }
    delete[] b;

    dim1 = m.dim1;
    dim2 = m.dim2;
    b = new double *[dim1];
    for (int i = 0; i < dim1; ++i) {
      b[i] = new double[dim2];
      for (int j = 0; j < dim2; ++j) {
        b[i][j] = m.b[i][j];
      }
    }
  }

  return *this;
}

vect operator*(const matr &m, const vect &v) {
  if (m.dim2 != v.dim) {
    cout << "Размерность матрицы и вектора не совпадают для умножения." << endl;
    exit(1);
  }

  vect result(m.dim1);
  for (int i = 0; i < m.dim1; ++i) {
    for (int j = 0; j < m.dim2; ++j) {
      result.b[i] += m.b[i][j] * v.b[j];
    }
  }

  return result;
}

int main() {
  vect v1(3);
  v1.print();
  cout << endl;

  double arr[] = {1.0, 2.0, 3.0};
  vect v2(3, arr);
  v2.print();
  cout << endl;

  vect v3 = v2;
  v3.print();
  cout << endl;

  vect v4 = v1 + v2;
  cout << "Сложение v1 и v2: " << endl;
  v4.print();
  cout << endl;

  vect v5 = v2 - v1;
  cout << "Вычитание v2 и v1: " << endl;
  v5.print();
  cout << endl;

  cout << "Умножение v2 на скаляр: " << endl;
  vect v6 = 2.0 * v2;
  v6.print();
  cout << endl;

  cout << "Унарный минус v2: " << endl;
  vect v7 = -v2;
  v7.print();
  cout << endl;

  double dotProduct = v2 * v3;
  cout << "Скалярное произведение v2 и v3: " << dotProduct << endl;
  cout << endl;

  cout << "Количество существующих векторов: " << vect::getCount() << endl;

  matr m1(3, 3);
  m1.print();
  cout << endl;

  double arr2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double *pArr[3] = {arr2[0], arr2[1], arr2[2]};
  matr m2(3, 3, pArr);
  m2.print();
  cout << endl;

  cout << "Сложение m1 и m2: " << endl;
  matr m3 = m1 + m2;
  m3.print();
  cout << endl;

  cout << "Вычитание m1 и m2: " << endl;
  matr m4 = m1 - m2;
  m4.print();
  cout << endl;

  cout << "Умножение m2 на скаляр: " << endl;
  matr m5 = 2.0 * m2;
  m5.print();
  cout << endl;

  cout << "Умножение m2 на m5: " << endl;
  matr m6 = m2 * m5;
  m6.print();
  cout << endl;

  cout << "Унарный минус m2: " << endl;
  matr m7 = -m2;
  m7.print();
  cout << endl;
  
  cout << "Умножение m6 на v2: " << endl;
  vect vm = m6 * v2;
  vm.print();
  
  cout << "Количество созданных матриц: " << matr::getCount() << endl;

  return 0;
}