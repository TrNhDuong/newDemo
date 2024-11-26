#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

long long comparision;
void insertionSort(int*, int);

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

void quickSort(int* arr, int left, int right) {
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
        quickSort(arr, left, j);
    ++comparision;
    if (i < right)
        quickSort(arr, i, right);
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

void selectionSort(int* arr, int n) {
    for (int i = 0;i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1;j < n; j++) {
            if (++comparision && arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

void heapify(int* arr, int n, int i) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child

    // Check if left child exists and is greater than the root
    if (left < n) 
    {
        if (++comparision && arr[left] > arr[largest]) {
            largest = left;
        }
    }

    // Check if right child exists and is greater than the root
    if (right < n)
    {
        if (++comparision && arr[right] > arr[largest]) {
            largest = right;
        }
    }

    // If the largest is not the root, swap and recursively heapify the affected subtree
    if (++comparision && largest != i) 
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);  // Recursively heapify the affected subtree
    }
}

void heapSort(int* arr, int n) {
    // Build a max heap
    for (int i = n / 2 - 1;i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements one by one from the heap
    for (int i = n - 1;i > 0; i--) {
        // Swap the root (maximum element) with the last element
        swap(arr[0], arr[i]);

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays to hold the values
    int* left_arr = new int[n1];
    int* right_arr = new int[n2];

    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        right_arr[i] = arr[mid + 1 + i];
    }

    int i = 0;  // Initial index for left subarray
    int j = 0;  // Initial index for right subarray
    int k = left;  // Initial index for merged subarray

    // Merge the temporary arrays back into the original array
    while (i < n1 && j < n2) 
    {
        if (++comparision && left_arr[i] <= right_arr[j]) 
        {
            arr[k] = left_arr[i];
            i++;
        }
        else 
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    // Copy the remaining elements of left_arr[], if any
    while (i < n1) 
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    // Copy the remaining elements of right_arr[], if any
    while (j < n2) 
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
    delete[] left_arr;
    delete[] right_arr;
}

void mergeSort(int* arr, int left, int right) {
    if (left < right) 
    {
        int mid = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void bubbleSort(int* arr, int sizeArr){
	int tmp;
	for (int i = sizeArr; i > 1 && ++comparision; i--)
    {
		for (int j = 0; j < i-1 && ++comparision; j++)
        {
			if (arr[j] > arr[j+1] && ++comparision)
            {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void shakerSort(int* a, int sizeArr)
{
    int Left = 0;
    int Right = sizeArr - 1;
    int k = 0;
    int i;
    while (++comparision && Left < Right)
    {
        for (i = Left;++comparision && i < Right; i++)
        {
            if (++comparision && a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                k = i;
            }
         }
        Right = k;
        for (i = Right;++comparision && i > Left; i--)
        {
            if (++comparision && a[i] < a[i - 1])
            {
                swap(a[i], a[i - 1]);
                k = i;
            }
        }
        Left = k;
    }
}

void flashSort(int* arr, int sizeArr) {
    int n = sizeArr;
    if (n <= 1 && ++comparision) return;

    int minVal = arr[0], maxVal = arr[0];
    int maxIndex = 0;
    for (int i = 1; i < n && ++comparision; ++i) {
        if (arr[i] < minVal && ++comparision) minVal = arr[i];
        if (arr[i] > maxVal && ++comparision) {
            maxVal = arr[i];
            maxIndex = i;
        }
    }

    if (minVal == maxVal) return;

    int numClasses = static_cast<int>(0.45 * n);

    int* classCount = new int[numClasses];
    for (int i = 0; ++comparision && i < numClasses; i++)
        classCount[i] = 0;

    double classWidth = static_cast<double>(numClasses - 1) / (maxVal - minVal);

    for (int i = 0; i < n && ++comparision; ++i) {
        int k = static_cast<int>(classWidth * (arr[i] - minVal));
        classCount[k]++;
    }

    for (int i = 1; i < numClasses && ++comparision; ++i) {
        classCount[i] += classCount[i - 1];
    }

    int nmove = 0;
    int j = 0, k = numClasses - 1;
    while (nmove < n && ++comparision) {
        while (j > classCount[k] - 1 && ++comparision) {
            j++;
            k = static_cast<int>(classWidth * (arr[j] - minVal));
        }

        int flash = arr[j];
        while (j != classCount[k] && ++comparision) {
            k = static_cast<int>(classWidth * (flash - minVal));
            int t = --classCount[k];
            swap(arr[t], flash);
            nmove++;
        }
    }

    int start = 0;
    for (int i = 0; i < numClasses && ++comparision; ++i) {
        int end = (i == numClasses - 1 && ++comparision) ? n : classCount[i];
        insertionSort(arr, end - start);
        start = end;
    }
}

void insertionSort(int* arr, int sizeArr) {
    for (int i = 1; i < sizeArr; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && (++comparision, arr[j] > key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shellSort(int* arr, int sizeArr) {
    for (int gap = sizeArr / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < sizeArr; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && (++comparision, arr[j - gap] > temp); j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void binaryInsertionSort(int* arr, int sizeArr) {
    for (int i = 1; i < sizeArr; i++) {
        int key = arr[i];
        int left = 0, right = i - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (++comparision, arr[mid] <= key)
                left = mid + 1;
            else
                right = mid - 1;
        }

        for (int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }
        arr[left] = key;
    }
}

void sortDependOnAlgorithm(string algo, int* a, int sizeArr){ 
    if (algo == "Quick Sort")
    {
        quickSort(a, 0, sizeArr - 1);
    } 
    else if (algo == "Radix Sort")
    {
        radixSort(a, sizeArr);
    } 
    else if (algo == "Counting Sort")
    {
        countingSort(a, sizeArr);
    }
    else if (algo == "Merge Sort")
    {
        mergeSort(a, 0, sizeArr - 1);
    }
    else if (algo == "Heap Sort")
    {
        heapSort(a, sizeArr);
    }
    else if (algo == "Selection Sort")
    {
        selectionSort(a, sizeArr);
    }
    else if (algo == "Bubble Sort")
    {
        bubbleSort(a, sizeArr);
    }
    else if (algo == "Shaker Sort")
    {
        shakerSort(a, sizeArr);
    }
    else if (algo == "Flash Sort")
    {
        flashSort(a, sizeArr);
    }
    else if (algo == "Insertion Sort")
    {
        insertionSort(a, sizeArr);
    }
    else if (algo == "Binary Insertion Sort")
    {
        binaryInsertionSort(a, sizeArr);
    }
    else if (algo == "Shell Sort")
    {
        shellSort(a, sizeArr);
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
    for (int i = 0; i < 12; i++){
        int* newArr = new int[sizeArr];
        for (int j = 0; j < sizeArr; j++)
            newArr[j] = arr[j];
        comparision = 0;
        chrono::duration<double> duration = countime(typeSort[i], newArr, sizeArr);
        cout << "Type of sort: " << typeSort[i] << "| Time: " << 1000*duration.count() << "ms | Comparisions: " << comparision << "\n";
        comparision = 0;
        delete[] newArr;
        newArr = nullptr;
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
    string typeSort[12] = {"Quick Sort", "Counting Sort", "Radix Sort", "Merge Sort", "Heap Sort", "Binary Insertion Sort", "Shell Sort", "Bubble Sort", 
    "Flash Sort", "Insertion Sort", "Shaker Sort", "Selection Sort"};

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
