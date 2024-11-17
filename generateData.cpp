#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

template <class T>
void Swap(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// This function generates a random array
void GenerateRandomData(int* a, int n)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
    fstream fout("input.txt", ios::out);
	fout << n << "\n";
    for (int i = 0; i < n; i++)
        fout << a[i] << ' ';
    fout.close();
}

// This function generates a sorted array (ascending order)
void GenerateSortedData(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// This function generates a reverse-sorted array (descending order)
void GenerateReverseData(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// This function generates a nearly-sorted array
void GenerateNearlySortedData(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}

	srand((unsigned int) time(NULL));
	
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		Swap(a[r1], a[r2]);
	}
}

void GenerateData(int* a, int n, int dataType)
{
	switch (dataType)
	{
	case 0:	
		GenerateRandomData(a, n);
		break;
	case 1:	
		GenerateSortedData(a, n);
		break;
	case 2:	
		GenerateReverseData(a, n);
		break;
	case 3:	
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

void countingSort(int arr[], int n) 
{ 
    // max_element() is a c++ stl function to find the 
    // maximum element from an array 
    int k = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > k)
            k = arr[i];
  
    // we declare a count array and initialize the array by 
    // 0 
    int count[k + 1] = { 0 }; 
  
    // we count the frequency of each distinct element in 
    // the original array 
    for (int i = 0; i < n; i++) { 
        count[arr[i]]++; 
    } 
  
    // we perform prefix sum and update the count array 
    for (int i = 1; i <= k; i++) { 
        count[i] = count[i] + count[i - 1]; 
    } 
  
    // we store our answer in the ans array 
    int ans[n]; 
    for (int i = n - 1; i >= 0; i--) { 
        ans[--count[arr[i]]] = arr[i]; 
    } 
  
    // here we copy the contents on ans array to our 
    // original array 
    for (int i = 0; i < n; i++) { 
        arr[i] = ans[i]; 
    } 
}

void quickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];
      /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

int main(){
    int* a = new int[1000000];
    int n = 100;
    GenerateData(a, n, 0);
    delete[] a;
    return 0;
}