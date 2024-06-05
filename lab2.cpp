#include <iostream>

class vect {
private:
    int dim;
    double *b;
    int pit;
    static int count;

public:
    vect() : dim(0), pit(0), b(nullptr) {
        count++;
        pit = count;
        std::cout << "Creating vector " << pit << ", total count: " << count << std::endl;
    }

    vect(int d) : dim(d), pit(0) {
        b = new double[dim];
        count++;
        pit = count;
        std::cout << "Creating vector " << pit << ", total count: " << count << std::endl;
    }

    vect(int d, double *x) : dim(d), pit(0) {
        b = new double[dim];
        for (int i = 0; i < dim; ++i) {
            b[i] = x[i];
        }
        count++;
        pit = count;
        std::cout << "Creating vector " << pit << ", total count: " << count << std::endl;
    }

    vect(const vect &other) : dim(other.dim), pit(0) {
        b = new double[dim];
        for (int i = 0; i < dim; ++i) {
            b[i] = other.b[i];
        }
        count++;
        pit = count;
        std::cout << "Copying vector " << pit << ", total count: " << count << std::endl;
    }

    ~vect() {
        delete[] b;
        count--;
        std::cout << "Deleting vector " << pit << ", total count: " << count << std::endl;
    }

    vect operator+(const vect &other) const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = b[i] + other.b[i];
        }
        std::cout << "Vector addition performed with vectors " << pit << " and " << other.pit << std::endl;
        return result;
    }

    vect operator-(const vect &other) const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = b[i] - other.b[i];
        }
        std::cout << "Vector subtraction performed with vectors " << pit << " and " << other.pit << std::endl;
        return result;
    }

    vect operator-() const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = -b[i];
        }
        std::cout << "Unary minus performed on vector " << pit << std::endl;
        return result;
    }

    double operator*(const vect &other) const {
        double dotProduct = 0.0;
        for (int i = 0; i < dim; ++i) {
            dotProduct += b[i] * other.b[i];
        }
        std::cout << "Dot product performed with vectors " << pit << " and " << other.pit << std::endl;
        return dotProduct;
    }

    vect operator*(double k) const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = b[i] * k;
        }
        std::cout << "Scalar multiplication performed on vector " << pit << std::endl;
        return result;
    }

    vect &operator=(const vect &other) {
        if (this != &other) {
            delete[] b;
            dim = other.dim;
            b = new double[dim];
            for (int i = 0; i < dim; ++i) {
                b[i] = other.b[i];
            }
            std::cout << "Vector assignment performed from " << other.pit << " to " << pit << std::endl;
        }
        return *this;
    }

    friend class matrix;
};

class matrix {
private:
    int dim;
    double *a;

public:
    matrix() : dim(0), a(nullptr) {}

    matrix(matrix &x) : dim(x.dim), a(new double[dim * dim]) {
        for (int i = 0; i < dim * dim; ++i) {
            a[i] = x.a[i];
        }
    }

    matrix(int n) : dim(n), a(new double[dim * dim]) {
        for (int i = 0; i < dim * dim; ++i) {
            if (i / dim == i % dim) a[i] = 1.0;
            else a[i] = 0.0;
        }
    }

    matrix(int n, double *x) : dim(n), a(new double[dim * dim]) {
        for (int i = 0; i < dim * dim; ++i) {
            a[i] = x[i];
        }
    }

    ~matrix() {
        delete[] a;
    }

    matrix operator+(matrix &r) {
        matrix result(dim);
        for (int i = 0; i < dim * dim; ++i) {
            result.a[i] = a[i] + r.a[i];
        }
        return result;
    }

    matrix operator-(matrix &r) {
        matrix result(dim);
        for (int i = 0; i < dim * dim; ++i) {
            result.a[i] = a[i] - r.a[i];
        }
        return result;
    }

    matrix operator-() {
        matrix result(dim);
        for (int i = 0; i < dim * dim; ++i) {
            result.a[i] = -a[i];
        }
        return result;
    }

    matrix operator*(matrix &r) {
        matrix result(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                double sum = 0.0;
                for (int k = 0; k < dim; ++k) {
                    sum += a[i * dim + k] * r.a[k * dim + j];
                }
                result.a[i * dim + j] = sum;
            }
        }
        return result;
    }

    friend matrix operator*(double k, matrix &r);

    vect operator*(vect &r);
};

matrix operator*(double k, matrix &r) {
    matrix result(r.dim);
    for (int i = 0; i < r.dim * r.dim; ++i) {
        result.a[i] = k * r.a[i];
    }
    return result;
}

vect matrix::operator*(vect &r) {
    double *result = new double[dim];
    for (int i = 0; i < dim; ++i) {
        result[i] = 0;
        for (int j = 0; j < dim; ++j) {
            result[i] += a[i * dim + j] * r.b[j];
        }
    }
    vect v(dim, result);
    delete[] result;
    return v;
}

int vect::count = 0;

int main() {
    double arr1[] = {1, 2, 3};
    double arr2[] = {4, 5, 6};

    vect v1(3, arr1);
    vect v2(3, arr2);
    vect v3;

    v3 = v1 + v2;
    v3 = v1 - v2;
    v3 = -v1;
    double dotProduct = v1 * v2;
    v3 = v1 * 2;

    matrix m1(2, arr1);
    matrix m2(2, arr2);
    matrix m3;

    m3 = m1 + m2;
    m3 = m1 - m2;
    m3 = -m1;
    matrix m4 = m1 * m2;
    matrix m5 = 2 * m1;

    vect result = m1 * v1;

    std::cout << "Press Enter to exit"; 
    getchar();
    return 0;
}
