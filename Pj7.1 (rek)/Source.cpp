#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void Print(int** a, const int rowCount, const int colCount, int i = 0, int j = 0);
void Sort(int** a, const int rowCount, const int colCount, int col1 = 0, bool swapped = false);
void ChangeColumns(int** a, const int col1, const int col2, const int rowCount, int i = 0);
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

int main()
{
    srand((unsigned)time(NULL));
    int Low = -34;
    int High = 26;
    int rowCount = 8;
    int colCount = 6;
    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);
    Print(a, rowCount, colCount);

    Sort(a, rowCount, colCount);
    Print(a, rowCount, colCount);

    int S = 0, k = 0;
    Calc(a, rowCount, colCount, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;

    Print(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
    if (i < rowCount) {
        if (j < colCount) {
            a[i][j] = Low + rand() % (High - Low + 1);
            Create(a, rowCount, colCount, Low, High, i, j + 1);
        }
        else {
            Create(a, rowCount, colCount, Low, High, i + 1, 0);
        }
    }
}

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
    if (i < rowCount) {
        if (j < colCount) {
            cout << setw(4) << a[i][j];
            Print(a, rowCount, colCount, i, j + 1);
        }
        else {
            cout << endl;
            Print(a, rowCount, colCount, i + 1, 0);
        }
    }
    else {
        cout << endl;
    }
}

void Sort(int** a, const int rowCount, const int colCount, int col1, bool swapped)
{
    if (col1 < colCount - 1) {
        for (int col2 = 0; col2 < colCount - col1 - 1; col2++) {
            if (a[0][col2] < a[0][col2 + 1] ||
                (a[0][col2] == a[0][col2 + 1] && a[1][col2] < a[1][col2 + 1]) ||
                (a[0][col2] == a[0][col2 + 1] && a[1][col2] == a[1][col2 + 1] && a[2][col2] < a[2][col2 + 1])) {
                ChangeColumns(a, col2, col2 + 1, rowCount);
                swapped = true;
            }
        }
        if (swapped)
            Sort(a, rowCount, colCount, col1 + 1, false);
    }
}

void ChangeColumns(int** a, const int col1, const int col2, const int rowCount, int i)
{
    if (i < rowCount) {
        int temp = a[i][col1];
        a[i][col1] = a[i][col2];
        a[i][col2] = temp;
        ChangeColumns(a, col1, col2, rowCount, i + 1);
    }
}

void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
    if (i < rowCount) {
        if (j < colCount) {
            if (a[i][j] > 0 || a[i][j] % 2 != 0) {
                S += a[i][j];
                k++;
                a[i][j] = 0;
            }
            Calc(a, rowCount, colCount, S, k, i, j + 1);
        }
        else {
            Calc(a, rowCount, colCount, S, k, i + 1, 0);
        }
    }
}
