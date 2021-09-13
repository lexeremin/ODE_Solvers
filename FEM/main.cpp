#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#define _e 2.71828182845904523536

using namespace std;

double A = 13.0, B = -7.0, C = 0.0, D = 7.0, L;
double x_left = 3.0, x_right = 22.0;
int n_elements = 0;
double left_value = 5, right_value = 5;
int LB_type = 1, RB_type = 1;

class solver {
public:
    double A;
    double B;
    double C;
    double D;
    double E;
    solver() {
        A = 0, B = 0, C = 0, D = 0, E = 0;
    }

    solver(int i) {
        A = i, B = i, C = i, D = i, E = i;
    }

    solver(double a, double b, double c, double d, double e) {
        A = a, B = b, C = c, D = d, E = e;
    }

    double value(double x) {
        return (A)*x*x*x*x + (B)*x*x*x + (C)*x*x + (D)*x + E;
    }

    friend ostream& operator<<(ostream& out, solver& f) {
        out << f.A << "x^4 + " << f.B << "x^3 + " << f.C << "x^2 + " << f.D << "x + " << f.E;
        return out;
    }

    solver derivative() { // returns solver's derivative value in x
         return solver(0, 4 * this->A, 3 * this->B, 2 * this->C, this->D);
    }

    double derivative(double x) {
        return this->derivative().value(x);
    }

    double psiFunc(double a, double b, int i, double x[]) { // psi function (look at integral func)
        return (b + a) / 2 + (b - a) / 2 * x[i];
    }

    solver operator*(solver f1) {
        solver result;
        result.A = A*f1.E + B*f1.D + C*f1.C + D*f1.B + E*f1.A;
        result.B = B*f1.E + C*f1.D + D*f1.C + E*f1.B;
        result.C = C*f1.E + D*f1.D + E*f1.C;
        result.D = D*f1.E + E*f1.D;
        result.E = E*f1.E;
        return result;
    }

    solver operator*(double c) {
        return solver(A*c, B*c, C*c, D*c, E*c);
    }

    solver operator+(solver f1) {
        solver result;
        result.A = A + f1.A;
        result.B = B + f1.B;
        result.C = C + f1.C;
        result.D = D + f1.D;
        result.E = E + f1.E;
        return result;
    }

    solver operator-(solver f1) {
        solver result;
        result.A = A - f1.A;
        result.B = B - f1.B;
        result.C = C - f1.C;
        result.D = D - f1.D;
        result.E = E - f1.E;
        return result;
    }

    double integral(double a, double b) { // returns solver's defined integral from a to b
        double w[] = { 0.555555556, 0.888888889, 0.555555556 }; //Gauss-Legendre method
        double x[] = { -0.774596669, 0.0, 0.774596669 };
        double temp = 0.0;
        for (int i = 0; i<3; i++) {
            temp += w[i] * this->value(psiFunc(a, b, i, x));
        }
        return (b - a) / 2 * temp;
    }
};


template <class X> class matrix {
public:
    X **M;
    int h; // horizontal size
    int v; // vertical size
    matrix() : M(nullptr), h(0), v(0) {};
    matrix(int _h, int _v) {
        M = new X*[_v];
        for (int i = 0; i < _v; ++i) {
            M[i] = new X[_h];
            for (int j = 0; j < _h; ++j) {
                M[i][j] = X();
            }
        }
        h = _h;
        v = _v;
    }

    matrix<X>(const matrix<X> &m)
    {
        v = m.v;
        h = m.h;
        M = new X*[v];
        for (int i = 0; i < v; ++i) {
            M[i] = new X[h];
            for (int j = 0; j < h; ++j) {
                M[i][j] = m.M[i][j];
            }
        }
    }

    matrix<X>& operator=(matrix<X> m) {
        v = m.v;
        h = m.h;
        M = new X*[v];
        for (int i = 0; i < v; ++i) {
            M[i] = new X[h];
            for (int j = 0; j < h; ++j) {
                M[i][j] = m.M[i][j];
            }
        }
        return *this;
    }

    X get(int x, int y) {
        return M[x][y];
    }

    void set(int x, int y, X value) {
        M[x][y] = value;
    }

    ~matrix() {
        if (M != nullptr) {
            for (int i = 0; i < v; ++i) {
                delete M[i];
            }
            delete M;
        }
    }

    void derivative() {
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < h; ++j) {
                M[i][j] = M[i][j].derivative();
            }
        }
    }

    void print() {
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < h; ++j) {
                cout << M[i][j] << " ";
            }
            cout << endl;
        }
    }

    matrix operator*(double _c) {
        for (int i = 0; i < this->v; i++) {
            for (int j = 0; j < this->h; j++) {
                this->M[i][j] = this->M[i][j] * _c;
            }
        }
        return *this;
    }

    matrix<X> operator*(matrix<X> temp) {
        matrix <X> result(temp.h, v);
        X tempsum = 0;
        if (h == temp.v) {
            for (int i = 0; i != v; ++i) {
                for (int j = 0; j != temp.h; ++j) {
                    for (int k = 0; k != h; ++k) {
                        tempsum = tempsum + M[i][k] * temp.M[k][j];
                    }
                    result.M[i][j] = tempsum;
//result.set(j, i, tempsum);
                    tempsum = 0;
                }
            }
        }
        else
            cerr << "Error matrix multiple" << endl;
        return result;
    }

    matrix<double> integral(double a, double b) {
        matrix<double> temp(h, v);
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < h; j++) {
                temp.M[i][j] = M[i][j].integral(a, b);
            }
        }
        return temp;
    }
};


class SLAE {
public:
    matrix<double>* A; // SLAE
    matrix<double>* X; // solution
    int h; //vertical size (amount of equations)

    SLAE(int _h) {A = new matrix<double>(_h + 1, _h);
        X = new matrix<double>(1, _h);
        h = _h;
    }

    ~SLAE() {
        delete A;
        delete X;
    }

    void Gauss() {
        double tmp = 0.0;
        for (int i = 0; i < h; i++) {
            tmp = A->get(i, i);
            for (int j = h; j >= i; j--)
                A->set(i, j, A->get(i, j) / tmp);
            for (int j = i + 1; j < h; j++)
            {
                tmp = A->get(j, i);
                for (int k = h; k >= i; k--)
                    A->set(j, k, A->get(j, k) - tmp * A->get(i, k));
            }
        }
        X->set(h - 1, 0, A->get(h - 1, h));
        for (int i = h - 2; i >= 0; i--)
        {
            X->set(i, 0, A->get(i, h));
            for (int j = i + 1; j < h; j++) X->set(i, 0, X->get(i, 0) - A->get(i, j)*X->get(j, 0));
        }
    }

    void ensemble(matrix<double> local, int elem_no, int form_func) {
        for (int i = 0; i < local.v; i++) {
            for (int j = 0; j < local.h; j++) {
                A->set(i + elem_no*form_func, j + elem_no*form_func, A->get(i + elem_no*form_func, j + elem_no*form_func) + local.M[i][j]);
            }
        }
    }

    void ensemble_discrepancy(matrix<double> local, int elem_no, int form_func) {
        for (int i = 0; i < local.v; i++) {
            for (int j = 0; j < local.h; j++) {
                A->set(i + elem_no*form_func, h, A->get(i + elem_no*form_func, h) + local.M[i][j]);
            }
        }
    }
};


void countU(double _C, int no, SLAE &globalSLAE, double L, int form_type) {
    matrix<solver> m1(1, form_type + 1);
    matrix<solver> m2(form_type + 1, 1);
    if (form_type == 1) {
        solver form1(0, 0, 0, -1. / L, 1);
        solver form2(0, 0, 0, 1. / L, 0);
        m1.set(0, 0, form1);
        m1.set(1, 0, form2);
        m2.set(0, 0, form1);
        m2.set(0, 1, form2);
    }
    if (form_type == 2) {
        solver form1(0, 0, -2. / (L*L), 1. / L, 1);
        solver form2(0, 0, -4. / (L*L), 4. / L, 0);
        solver form3(0, 0, 2. / (L*L), -1. / L, 0);
        m1.set(0, 0, form1);
        m1.set(1, 0, form2);
        m1.set(2, 0, form3);
        m2.set(0, 0, form1);
        m2.set(0, 1, form2);
        m2.set(0, 2, form3);
    }
    matrix<solver> result;
    result = m1*m2*_C;
    matrix<double> i;
    i = result.integral(0, L);
    globalSLAE.ensemble(i, no, form_type);
}

void countd_dx(double _B, int no, SLAE &globalSLAE, double L, int form_type) {
    matrix<solver> m1(1, form_type + 1);
    matrix<solver> m2(form_type + 1, 1);
    if (form_type == 1) {
        solver form1(0, 0, 0, -1. / L, 1);
        solver form2(0, 0, 0, 1. / L, 0);
        m1.set(0, 0, form1);
        m1.set(1, 0, form2);
        m2.set(0, 0, form1);
        m2.set(0, 1, form2);
    }
    if (form_type == 2) {
        solver form1(0, 0, -2. / (L*L), 1. / L, 1);
        solver form2(0, 0, -4. / (L*L), 4. / L, 0);
        solver form3(0, 0, 2. / (L*L), -1. / L, 0);
        m1.set(0, 0, form1);
        m1.set(1, 0, form2);
        m1.set(2, 0, form3);
        m2.set(0, 0, form1);
        m2.set(0, 1, form2);
        m2.set(0, 2, form3);
    }
    m2.derivative();
    matrix<solver> result;
    result = m1*m2*_B;
    matrix<double> i;
    i = result.integral(0, L);
    globalSLAE.ensemble(i, no, form_type);
}

void countd2_dx(double _A, int no, SLAE &globalSLAE, double L, int form_type) {
    matrix<solver> m1(1, form_type + 1);
    matrix<solver> m2(form_type + 1, 1);
    if (form_type == 1) {
        solver form1(0, 0, 0, -1. / L, 1);
        solver form2(0, 0, 0, 1. / L, 0);
        m1.set(0, 0, form1);
        m1.set(1, 0, form2);
        m2.set(0, 0, form1);
        m2.set(0, 1, form2);
    }

    if (form_type == 2) {
        solver form1(0, 0, -2. / (L*L), 1. / L, 1);
        solver form2(0, 0, -4. / (L*L), 4. / L, 0);
        solver form3(0, 0, 2. / (L*L), -1. / L, 0);
        m1.set(0, 0, form1);
        m1.set(1, 0, form2);
        m1.set(2, 0, form3);
        m2.set(0, 0, form1);
        m2.set(0, 1, form2);
        m2.set(0, 2, form3);
    }
    m1.derivative();
    m2.derivative();
    matrix<solver> result;
    result = m1*m2*(_A*(-1.0));
    matrix<double> i;
    i = result.integral(0, L);
    globalSLAE.ensemble(i, no, form_type);
}

void count_const(double _D, int no, SLAE &globalSLAE, double L, int form_type) {
    matrix<solver> m1(1, form_type + 1);
    matrix<solver> m2(form_type + 1, 1);
    if (form_type == 1) {
        solver form1(0, 0, 0, -1. / L, 1);
        solver form2(0, 0, 0, 1. / L, 0);
        m1.set(0, 0, form1);
        m1.set(1, 0, form2);
        m2.set(0, 0, form1);
        m2.set(0, 1, form2);
    }
    if (form_type == 2) {
        solver form1(0, 0, -2. / (L*L), 1. / L, 1);
        solver form2(0, 0, -4. / (L*L), 4. / L, 0);
        solver form3(0, 0, 2. / (L*L), -1. / L, 0);
        m1.set(0, 0, form1);
        m1.set(1, 0, form2);
        m1.set(2, 0, form3);
        m2.set(0, 0, form1);
        m2.set(0, 1, form2);
        m2.set(0, 2, form3);
    }
    matrix<solver> result;
    result = m1*_D*(-1.0);
    matrix<double> i;
    i = result.integral(0, L);
    globalSLAE.ensemble_discrepancy(i, no, form_type);
}

void mesh(int &n_elements, double &x_left, double &x_right, double &L) {
    cout << "Quantity of elements: \n> ";
    cin >> n_elements;
    L = (x_right - x_left) / n_elements;
    cout << "Meshing complete!" << endl;
    cout << "Element size: " << L << endl;
}

double real_value(double x) {
    //return ((pow(_e,21./13.)*(x-17.)-19.*pow(_e, 7.*x/13.)+pow(_e, 154./13.)*(x+2.))/(pow(_e, 21./13.)*(pow(_e,133./13.)-1)));
    //return (pow(_e,21./13.)*(x-17.))/(pow(_e, 21./13.)*pow(_e,133./13.))-(19.*pow(_e, 7.*x/13.))/(pow(_e, 21./13.)*pow(_e,133./13.))+(pow(_e, 154./13.)*(x+2.))/((pow(_e, 21./13.)*pow(_e,133./13.));
    //return (pow(_e,21./13.)*(x-17.))/(pow(_e, 21./13.)*pow(_e,133./13.))-(19.*pow(_e, 7.*x/13.))/(pow(_e, 21./13.)*pow(_e,133./13.))+(pow(_e, 154./13.)*(x+2.))/(pow(_e, 21./13.)*pow(_e,133./13.));
    //return ((pow(_e,21./13.)*(x-17.))-(19.*pow(_e, 7.*x/13.))+(pow(_e, 154./13.)*(x+2.)))/(pow(_e, 21./13.)*pow(_e,133./13.));
    return ((-pow(_e,21./13.)*(x-17.)-19.*pow(_e, 7.*x/13.)+pow(_e, 154./13.)*(x+2.))/(pow(_e, 21./13.)*(pow(_e,133./13.)-1)));
}

void print_result_to(const char* path, SLAE &globalSLAE_linear, SLAE &globalSLAE_square) {
    ofstream output(path);
    double x = x_left;
    double xx = x_left;
    int k = 0;
    double fieldwidth = 23;
    double max_linear_error = 0, max_square_error = 0;
    output.setf(ios_base::right);
    output << setw(fieldwidth) << "X";
    output << setw(fieldwidth) << "Linear";
    output << setw(fieldwidth) << "Square";
    output << setw(fieldwidth) << "Real";
    output << setw(fieldwidth) << "Linear error";
    output << setw(fieldwidth) << "Square error" << endl;
    cout << setw(fieldwidth) << "X";
    cout << setw(fieldwidth) << "Linear";
    cout << setw(fieldwidth) << "Square";
    cout << setw(fieldwidth) << "Real";
    cout << setw(fieldwidth) << "Linear error";
    cout << setw(fieldwidth) << "Square error" << endl;
    for (int i = 0; i <= n_elements; i++, x+=L) {
        cout << setw(fieldwidth) << x << setw(fieldwidth) << globalSLAE_linear.X->get(i, 0) << setw(fieldwidth) <<
               globalSLAE_square.X->get(2 * i, 0) << setw(fieldwidth) << real_value(x) << setw(fieldwidth) <<
               fabs(real_value(x) - globalSLAE_linear.X->get(i, 0)) << setw(fieldwidth) << fabs(real_value(x) - globalSLAE_square.X->get(2 * i, 0)) << endl;
        output << setw(fieldwidth) << x << setw(fieldwidth) << globalSLAE_linear.X->get(i, 0) << setw(fieldwidth) <<
        globalSLAE_square.X->get(2 * i, 0) << setw(fieldwidth) << real_value(x) << setw(fieldwidth) <<
        fabs(real_value(x) - globalSLAE_linear.X->get(i, 0)) << setw(fieldwidth) << fabs(real_value(x) - globalSLAE_square.X->get(2 * i, 0)) << endl;
        if (fabs(real_value(x) - globalSLAE_linear.X->get(i, 0)) > max_linear_error) {
            max_linear_error = fabs(real_value(x) - globalSLAE_linear.X->get(i, 0));
        }
        if (fabs(real_value(x) - globalSLAE_square.X->get(2 * i, 0)) > max_square_error) {
            max_square_error = fabs(real_value(x) - globalSLAE_square.X->get(2 * i, 0));
        }
    }
    output << endl << "Max linear error: " << max_linear_error << endl;
    output << "Max square error: " << max_square_error << endl;
    cout << endl << "Max linear error: " << max_linear_error << endl;
    cout << "Max square error: " << max_square_error << endl;
    output.close();
}

void count(int i, SLAE &globalSLAE, double L, int form_type) {
    countd2_dx(A, i, globalSLAE, L, form_type);
    countd_dx(B, i, globalSLAE, L, form_type);
    countU(C, i, globalSLAE, L, form_type);
    count_const(D, i, globalSLAE, L, form_type);
}

void set_border_conditions(SLAE &globalSLAE) {
    if (LB_type == 1) {
        globalSLAE.A->set(0, 0, 1);
        for (int i = 1; i < globalSLAE.h; i++) {
            globalSLAE.A->set(0, i, 0);
        }
        globalSLAE.A->set(0, globalSLAE.h, left_value);
    }
    if (LB_type == 2) {
        globalSLAE.A->set(0, globalSLAE.h, globalSLAE.A->get(0, globalSLAE.h) + A*left_value);
    }
    if (RB_type == 1) {
        for (int i = 0; i < globalSLAE.h - 1; i++) {
            globalSLAE.A->set(globalSLAE.h - 1, i, 0);
        }
        globalSLAE.A->set(globalSLAE.h - 1, globalSLAE.h - 1, 1);
        globalSLAE.A->set(globalSLAE.h - 1, globalSLAE.h, right_value);
    }
    if (RB_type == 2) {
        globalSLAE.A->set(globalSLAE.h - 1, globalSLAE.h, globalSLAE.A->get(globalSLAE.h - 1, globalSLAE.h) - A*right_value);
    }
}

void gnuplot(SLAE& linear, SLAE& square, double x_left, int n_elements) {
    string linearfilename = "./linear.dat";
    string squarefilename = "./square.dat";
    string realfilename = "./real.dat";
    ofstream gnuscript("./script.plt");
    ofstream linearf(linearfilename);
    ofstream squaref(squarefilename);
    ofstream realf(realfilename);
    double x = x_left;
    int fieldwidth = 20;
    for (int i = 0; i <= n_elements; i++, x += L) {
        linearf << setw(fieldwidth) << x << setw(fieldwidth) << linear.X->get(i, 0) << endl;
        squaref << setw(fieldwidth) << x << setw(fieldwidth) << square.X->get(2 * i, 0) << endl;
    }

    x = x_left;
    for (int i = 0; i < 100; i++, x += (x_right - x_left) / 100.0) {
        realf << setw(fieldwidth) << x << setw(fieldwidth) << real_value(x) << endl;
    }

    linearf.close();
    squaref.close();
    realf.close();
    gnuscript << "set term wxt title 'FEM plotting'" << endl;
    gnuscript << "set style line 1 lt 1 lw 1 pt 1 linecolor rgb \"red\"" << endl;
    gnuscript << "set style line 2 lt 1 lw 1 pt 1 linecolor rgb \"green\"" << endl;
    gnuscript << "set style line 3 lt 1 lw 1 pt 1 linecolor rgb \"blue\"" << endl;
    gnuscript << "set xzeroaxis lt -1" << endl;
    gnuscript << "set yzeroaxis lt -1" << endl;
    gnuscript << "set grid xtics lc rgb '#555555' lw 1 lt 0" << endl;
    gnuscript << "set grid ytics lc rgb '#555555' lw 1 lt 0" << endl;
    gnuscript << "set xrange[" << x_left << ':' << x_right << ']' << endl;
    gnuscript << "plot "
              << "\"" << linearfilename
              << "\" using 1:2 title 'linear' w l ls 1, "
              << "\"" << squarefilename
              << "\" using 1:2 title 'square' w l ls 2, ";
    gnuscript << "\"" << realfilename << "\" using 1:2 title 'real' w l ls 3" << endl;
    gnuscript << "pause -1" << endl;
    gnuscript.close();
}


int main(int argc, char** argv) {
    mesh(n_elements, x_left, x_right, L); //div for finite elements
    SLAE globalSLAE_linear(n_elements + 1);//linear СЛАУ
    SLAE globalSLAE_square(2 * n_elements + 1);//СЛАУ squared
    for (int i = 0; i < n_elements; i++) {
        count(i, globalSLAE_linear, L, 1);
        count(i, globalSLAE_square, L, 2);
    }

    set_border_conditions(globalSLAE_linear);
    globalSLAE_linear.Gauss();
    set_border_conditions(globalSLAE_square);
    globalSLAE_square.Gauss();
    print_result_to("./table.plt", globalSLAE_linear, globalSLAE_square);
    gnuplot(globalSLAE_linear, globalSLAE_square, x_left, n_elements);
    system("gnuplot ./script.plt");
    return 0;
}
