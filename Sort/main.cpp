#include <iostream>
#include <tuple>
#include <vector>
#include <math.h>
#include <memory.h>
#include <random>
#include <stdlib.h>
#include <time.h>
using namespace std;

pair<unsigned int, unsigned int> swap(unsigned int a, unsigned int b)
{
    return make_pair(b, a);
}

bool insertionSort(vector<unsigned> &A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (A[j] > A[j + 1])
                tie<unsigned int, unsigned int>(A[j], A[j + 1]) = swap(A[j], A[j + 1]);
            else
            {
                break;
            }
        }
    }
    return true;
}

bool shellSort(vector<unsigned> &A, int n)
{
    for (int gap = n / 2; gap != 0; gap = gap / 2)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i - gap; j >= 0; j -= gap)
            {
                if (A[j] > A[j + gap])
                    tie<unsigned int, unsigned int>(A[j], A[j + gap]) = swap(A[j], A[j + gap]);
                else
                {
                    break;
                }
            }
        }
    }
    return true;
}

bool quickSort(vector<unsigned> &A, int p, int r)
{
    if (r <= p)
        return true;
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (A[j] <= A[r])
        {
            i += 1;
            tie(A[i], A[j]) = swap(A[i], A[j]);
        }
    }
    tie(A[i + 1], A[r]) = swap(A[i + 1], A[r]);
    quickSort(A, p, i);
    quickSort(A, i + 2, r);
    return true;
}

bool mergeSort(vector<unsigned> &A, int p, int r)
{
    if (r == p)
        return true;
    int q = (p + r) / 2;
    mergeSort(A, p, q);
    mergeSort(A, q + 1, r);
    vector<unsigned int> temp;
    for (int i = p; i < q + 1; i++)
    {
        temp.push_back(A[i]);
    }
    for (int i = 0, j = 0, k = p; i <= q - p || j <= r - q - 1;)
    {
        if (j == r - q ||(i<=q-p && temp[i] <= A[j + q + 1]))
            {A[k++] = temp[i++];continue;}
        if (i == q - p + 1 || (j<=r-q-1 && temp[i] > A[j + q + 1]))
            {A[k++] = A[(j++) + q + 1];continue;}
    }
    return true;
}

class Number
{
public:
    unsigned int data;
    unsigned int getData(unsigned int r)
    {
        return (data >> (8 * r)) & 0x000000ff;
    }
    Number(int n)
    {
        data = n;
    }
};

// r=8
bool radixSort(vector<unsigned> &A, int n)
{
    int MAX = pow(2, 8);
    vector<Number *> nums;
    for (int i = 0; i < n; i++)
    {
        nums.push_back(new Number(A[i]));
    }
    for (int r = 0; r < 4; r++)
    {
        vector<Number *> temp = nums;
        int C[(int)pow(2, 8)];
        memset(C, 0, pow(2, 8) * 4);
        for (int i = 0; i < n; i++)
        {
            C[(*nums[i]).getData(r)] = C[(*nums[i]).getData(r)] + 1;
        }
        for (int i = 0; i < MAX; i++)
        {
            C[i] = C[i] + C[i - 1];
        }

        for (int j = n - 1; j >= 0; j--)
        {
            temp[C[nums[j]->getData(r)] - 1] = nums[j];
            C[nums[j]->getData(r)]--;
        }
        nums.clear();
        nums = temp;
    }
    for(int i=0;i<n;i++){
        A[i]=nums[i]->data;
    }
    return true;
}

int main(int argc, char *argv[])
{
    cout<<"InsertionTime"<<" "<<"ShellTime"<<" "<<"QuickTime"<<" "<<"MergeTime"<<" "<<"RadixTime"<<endl;
    vector<unsigned> res;
    for (int i = pow(10,1); i < pow(10, 9); i *= 10)
    {
        std::random_device rd;
        for (int k = 0; k < i; k++)
        {
            std::uniform_int_distribution<unsigned> dist;
            res.push_back(dist(rd));
        }
        vector<unsigned> temp = res;

        clock_t start = clock();
        insertionSort(res, i);
        clock_t end = clock();
        double insertionTime = double(end - start) / CLOCKS_PER_SEC;

        res.clear();

        res = temp;
        start = clock();
        shellSort(res, i);
        end = clock();
        double shellTime = double(end - start) / CLOCKS_PER_SEC;

        res.clear();

        res = temp;
        start = clock();
        quickSort(res, 0, i - 1);
        end = clock();
        double quickTime = double(end - start) / CLOCKS_PER_SEC;

        res.clear();

        res = temp;
        start = clock();
        mergeSort(res, 0, i - 1);
        end = clock();
        double mergeTime = double(end - start) / CLOCKS_PER_SEC;

        res.clear();

        res = temp;
        start = clock();
        radixSort(res, i);
        end = clock();
        double radixTime = double(end - start) / CLOCKS_PER_SEC;

        cout << insertionTime << " " << shellTime << " " << quickTime << " " << mergeTime << " " << radixTime << endl;
    }
}