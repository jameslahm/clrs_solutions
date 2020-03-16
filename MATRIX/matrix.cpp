/**
 * @file matrix.cpp
 * @author wango
 * @brief matrix multiplication
 * @version 0.1
 * @date 2020-03-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <string>
#include <iomanip>
#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

/**
 * @brief print matrix
 * 
 * @param a matrix
 * @param n size 
 */
void print(int **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(4) << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * @brief generate random matrix (size n)
 * 
 * @param n size
 * @return int** matrix pointer 
 */
int **randomMatrix(int n)
{
    srand((unsigned)time(NULL));
    int **a = new int *[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % 10;
        }
    }
    return a;
}

/**
 * @brief traditional matrix multiplication
 * 
 * @param a OP Left
 * @param b OP Right
 * @param n size
 * @return int** result 
 */
int **tradMatrixMulti(int **a, int **b, int n)
{
    int **c = new int *[n];
    for (int i = 0; i < n; i++)
    {
        c[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

/**
 * @brief matrix add
 * 
 * @param a OP Left
 * @param b OP Right
 * @param n size
 * @return int** result 
 */
int **Add(int **a, int **b, int n)
{
    int **c = new int *[n];
    for (int i = 0; i < n; i++)
    {
        c[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

/**
 * @brief matrix sub
 * 
 * @param a OP Left
 * @param b OP Right
 * @param n size
 * @return int** result 
 */
int **Sub(int **a, int **b, int n)
{
    int **c = new int *[n];
    for (int i = 0; i < n; i++)
    {
        c[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

/**
 * @brief slice of Matrix
 * 
 * @param a original matrix
 * @param n size
 * @param startX slice start point X 
 * @param startY slice start point Y
 * @return int** result
 */
int **slice(int **a, int n, int startX, int startY)
{
    int **c = new int *[n];
    for (int i = 0; i < n; i++)
    {
        c[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[startX + i][startY + j];
        }
    }
    return c;
}

/**
 * @brief free the malloc space
 * 
 * @param a matrix
 * @param n size
 * @return true Success
 * @return false Error
 */
bool clearMatrix(int **a, int n)
{
    try
    {
        for (int i = 0; i < n; i++)
        {
            delete[] a[i];
        }
        delete[] a;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

/**
 * @brief StrassenMatrix multiplication
 * 
 * @param OP Left
 * @param OP Right
 * @param n size
 * @param flag for distinguish testing and compute, default 0 for compute
 * @return int** result
 */
int **strassenMatrixMulti(int **op1, int **op2, int n, int flag = 0)
{
    if (n < 500 && !flag)
    {
        return tradMatrixMulti(op1, op2, n);
    }

    if (n == 1)
    {
        int **c = new int *[1];
        c[0] = new int[1];
        c[0][0] = op1[0][0] * op2[0][0];
        return c;
    }

    // Judge n even or odd
    bool isEven = true;
    int **oldOP1 = op1;
    int **oldOP2 = op2;
    // odd condition
    if (n % 2 == 1)
    {
        isEven = false;
        int **newOP1 = new int *[n + 1];
        int **newOP2 = new int *[n + 1];
        for (int i = 0; i < n; i++)
        {
            newOP1[i] = new int[n + 1];
            newOP2[i] = new int[n + 1];
            newOP1[i][n] = 0;
            newOP2[i][n] = 0;
            for (int j = 0; j < n; j++)
            {
                newOP1[i][j] = op1[i][j];
                newOP2[i][j] = op2[i][j];
            }
        }
        newOP1[n] = new int[n + 1]{0};
        newOP2[n] = new int[n + 1]{0};
        op1 = newOP1;
        op2 = newOP2;
        n += 1;
    }

    // create a,b,c,d,e,f,g,h
    int **a = slice(op1, n / 2, 0, 0);
    int **b = slice(op1, n / 2, 0, n / 2);
    int **c = slice(op1, n / 2, n / 2, 0);
    int **d = slice(op1, n / 2, n / 2, n / 2);
    int **e = slice(op2, n / 2, 0, 0);
    int **f = slice(op2, n / 2, 0, n / 2);
    int **g = slice(op2, n / 2, n / 2, 0);
    int **h = slice(op2, n / 2, n / 2, n / 2);

    if (!isEven)
    {
        clearMatrix(op1, n);
        clearMatrix(op2, n);
        op1 = oldOP1;
        op2 = oldOP2;
    }

    // P1
    int **temp = Sub(f, h, n / 2);
    int **P1 = strassenMatrixMulti(a, temp, n / 2, flag);
    clearMatrix(temp, n / 2);

    // P2
    temp = Add(a, b, n / 2);
    int **P2 = strassenMatrixMulti(temp, h, n / 2, flag);
    clearMatrix(temp, n / 2);

    // P3
    temp = Add(c, d, n / 2);
    int **P3 = strassenMatrixMulti(temp, e, n / 2, flag);
    clearMatrix(temp, n / 2);

    // P4
    temp = Sub(g, e, n / 2);
    int **P4 = strassenMatrixMulti(d, temp, n / 2, flag);
    clearMatrix(temp, n / 2);

    // P5
    temp = Add(a, d, n / 2);
    int **temp1 = Add(e, h, n / 2);
    int **P5 = strassenMatrixMulti(temp, temp1, n / 2, flag);
    clearMatrix(temp, n / 2);
    clearMatrix(temp1, n / 2);

    // P6
    temp = Sub(b, d, n / 2);
    temp1 = Add(g, h, n / 2);
    int **P6 = strassenMatrixMulti(temp, temp1, n / 2, flag);
    clearMatrix(temp, n / 2);
    clearMatrix(temp1, n / 2);

    // P7
    temp = Sub(a, c, n / 2);
    temp1 = Add(e, f, n / 2);
    int **P7 = strassenMatrixMulti(temp, temp1, n / 2, flag);
    clearMatrix(temp, n / 2);
    clearMatrix(temp1, n / 2);

    // r
    int **r = Add(Sub(Add(P5, P4, n / 2), P2, n / 2), P6, n / 2);
    int **s = Add(P1, P2, n / 2);
    int **t = Add(P3, P4, n / 2);
    int **u = Sub(Sub(Add(P5, P1, n / 2), P3, n / 2), P7, n / 2);

    int m = isEven ? n : n - 1;
    int **Res = new int *[m];
    for (int i = 0; i < m; i++)
    {
        Res[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            if (i < n / 2 && j < n / 2)
            {
                Res[i][j] = r[i][j];
            }
            else if (i < n / 2 && j >= n / 2)
            {
                Res[i][j] = s[i][j - n / 2];
            }
            else if (i >= n / 2 && j < n / 2)
            {
                Res[i][j] = t[i - n / 2][j];
            }
            else
            {
                Res[i][j] = u[i - n / 2][j - n / 2];
            }
        }
    }

    clearMatrix(r, n / 2);
    clearMatrix(s, n / 2);
    clearMatrix(t, n / 2);
    clearMatrix(u, n / 2);
    return Res;
}

int main()
{
    cout << "===================Begin Test(s)====================" << endl;
    cout << setw(16) << "N" << setw(16) << "Traditional" << setw(16) << "Strassen" << endl;

    // compute    average 3
    for (int i = 2; i < 1024 * 8; i = 2 * i)
    {
        int **a = randomMatrix(i);
        sleep(1);
        int **b = randomMatrix(i);

        clock_t start = clock();
        for (int j = 0; j < 3; j++)
        {
            tradMatrixMulti(a, b, i);
        }
        clock_t end = clock();
        double trad = double(end - start) / 3 / CLOCKS_PER_SEC;

        start = clock();
        for (int j = 0; j < 3; j++)
        {
            strassenMatrixMulti(a, b, i);
        }
        end = clock();
        double stra = double((end - start)) / 3 / CLOCKS_PER_SEC;

        cout << setw(16) << i << setw(16) << setprecision(4) << fixed << trad << setw(16) << setprecision(4) << fixed << stra << endl;
    }

    // evaluate the correctness of strassen
    cout << "===================Evaluate Correctness====================" << endl;
    for (int i = 5; i < 9; i = i + 1)
    {
        int **a = randomMatrix(i);
        // for generate different matrix
        sleep(1);
        int **b = randomMatrix(i);
        int **c = tradMatrixMulti(a, b, i);
        print(a, i);
        print(b, i);
        print(c, i);
        int **d = strassenMatrixMulti(a, b, i, 1);
        print(d, i);
    }

    return 0;
}