#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int comparision;

// Hàm hoán đổi
template <class T>
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

// Các hàm tạo dữ liệu
void GenerateRandomData(int* a, int n)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % n;
    }
}

void GenerateSortedData(int* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
}

void GenerateReverseData(int* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = n - 1 - i;
    }
}

void GenerateNearlySortedData(int* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 10; i++)
    {
        int r1 = rand() % n;
        int r2 = rand() % n;
        swap(a[r1], a[r2]);
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

// Các thuật toán sắp xếp

void quicksort(int* arr, int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];
      /* partition */
    while (++comparision && i <= j) {
        ++comparision;
        while (arr[i] < pivot)
            i++;
        ++comparision;
        while (arr[j] > pivot)
            j--;
        if (++comparision && i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };
    ++comparision;
    if (left < j)
        quicksort(arr, left, j);
    ++comparision;
    if (i < right)
        quicksort(arr, i, right);
}

void countingSort(int* arr, int n) 
{ 
    // max_element() is a c++ stl function to find the 
    // maximum element from an array 
    int k = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > k)
            k = arr[i];
  
    // we declare a count array and initialize the array by 
    // 0 
    int* count = new int[k+1];
    for (int i = 0; i <= k; i++)
        count[i] = 0;
  
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
    int* ans = new int[n]; 
    for (int i = n - 1; i >= 0; i--) { 
        ans[--count[arr[i]]] = arr[i]; 
    } 
  
    // here we copy the contents on ans array to our 
    // original array 
    for (int i = 0; i < n; i++) { 
        arr[i] = ans[i]; 
    } 
    delete[] ans;
}

int getMax(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (++comparision && array[i] > max)
        max = array[i];
    return max;
}

// Using counting sort to sort the elements in the basis of significant places
void countsort_inRadix(int* array, int size, int place) {
    const int max = 10;
    int* output = new int[size];
    int count[max];

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    // Calculate count of elements
    for (int i = 0; i < size; i++)
        count[(array[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < max; i++)
        count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = size - 1; i >= 0; i--) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }

    for (int i = 0; i < size; i++)
        array[i] = output[i];

    delete[] output;
}

// Main function to implement radix sort
void radixSort(int array[], int size) {
  // Get maximum element
  int max = getMax(array, size);

  // Apply counting sort to sort elements based on place value.
  for (int place = 1; max / place > 0; place *= 10)
    countsort_inRadix(array, size, place);
}

void sortDependOnAlgorithm(string algo, int* arr, int sizeArr){ 
    if (algo == "Quick Sort")
    {
        quicksort(arr, 0, sizeArr - 1);
    } 
    else if (algo == "Radix Sort")
    {
        radixSort(arr, sizeArr);
    } 
    else if (algo == "Counting Sort")
    {
        countingSort(arr, sizeArr);
    }
}

chrono::duration<double> countime(string nameSort, int* &a, int size){
    auto start = chrono::high_resolution_clock::now();
    sortDependOnAlgorithm(nameSort, a, size);
    auto end = chrono::high_resolution_clock::now();
    return end - start;
}

// Hàm chính để thử nghiệm
void runExperiment(int sizeArr, int dataType, string typeSort[])
{
    int* arr = new int[sizeArr];
    GenerateData(arr, sizeArr, dataType);
    for (int i = 0; i < 3; i++){
        int* newArr = new int[sizeArr];
        for (int i = 0; i < sizeArr; i++)
            newArr[i] = arr[i];
        comparision = 0;
        chrono::duration<double> duration = countime(typeSort[i], arr, sizeArr);
        cout << "Type of sort: " << typeSort[i] << "| Time: " << 1000*duration.count() << "ms | Comparisions: " << comparision << "\n";
        delete[] newArr;
    }

    delete[] arr;
}

string nameOrder(int i){
    if (i == 0)
        return "Random";
    if (i == 1)
        return "Sorted";
    if (i == 2)
        return "Reverse";
    if (i == 3)
        return "Nearly Sorted";
    return "";
}

int main()
{
    int dataOrder[4] = {0, 1, 2, 3}; // Random, Sorted, Reverse, Nearly Sorted
    int dataSize[6] = {10000, 30000, 50000, 100000, 300000, 500000}; // Các kích thước dữ liệu
    string typeSort[3] = {"Quick Sort", "Counting Sort", "Radix Sort"};

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 6; j++)
        {
            cout << "Data order: " << nameOrder(i) << "\n";
            cout << "Data size: " << dataSize[j] << "\n";
            runExperiment(dataSize[j], dataOrder[i], typeSort);
            cout << "\n";
        }
    return 0;
}
