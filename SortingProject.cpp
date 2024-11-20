#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // Để đo thời gian
#include <cmath>
#include <ctime>
using namespace std;

int comparision;
void quickSort(int*, int, int);

void swap(int &a, int &b)
{
	int x = a;
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
void quicksort(int arr[], int left, int right) {
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

void shakerSort(int* a, int sizeArr){
	int left = 0, right = sizeArr - 1, temp;
	while (left < right && ++comparision){
		for (int i = left; i < right && ++comparision; i++){
			if (a[i] > a[i+1] && ++comparision){
				swap(a[i], a[i+1]);
			}
		}
		right --;

		for (int i = right; i > left && ++comparision; i--){
			if (a[i] < a[i-1]){
				swap(a[i], a[i-1]);
			}
		}
		left++;
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
        quickSort(arr, 0, n - 1);
        start = end;
    }
}

void sortDependOnAlgorithm(string algo, int* a, int sizeArr){ 
    if (algo == "quick-sort")
    {
        quicksort(a, 0, sizeArr - 1);
    } 
    else if (algo == "radix-sort")
    {
        radixSort(a, sizeArr);
    } 
    else if (algo == "counting-sort")
    {
        countingSort(a, sizeArr);
    }
    else if (algo == "merge-sort")
    {
        mergeSort(a, 0, sizeArr - 1);
    }
    else if (algo == "heap-sort")
    {
        heapSort(a, sizeArr);
    }
    else if (algo == "selection-sort")
    {
        selectionSort(a, sizeArr);
    }
    else if (algo == "bubble-sort")
    {
        bubbleSort(a, sizeArr);
    }
    else if (algo == "shaker-sort")
    {
        shakerSort(a, sizeArr);
    }
    else if (algo == "flash-sort")
    {
        flashSort(a, sizeArr);
    }

}

string nameDependOnSort(string algo){
    string name = algo;
    if (name == "radix-sort")
    {
        name = "Radix Sort";
    }
    else if (name == "quick-sort")
    {
        name = "Quick Sort";
    }
    else if (name == "counting-sort")
    {
        name = "Counting Sort";
    }
    else if (name == "merge-sort")
    {
        name = "Merge Sort";
    }
    else if (name == "heap-sort")
    {
        name = "Heap Sort";
    }
    else if (name == "selection-sort")
    {
        name = "Selection Sort";
    }
    else if (name == "bubble-sort")
    {
        name = "Bubble Sort";
    }
    else if (name == "shaker-sort")
    {
        name = "Shaker Sort";
    }
    else if (name == "flash-sort")
    {
        name = "Flash Sort";
    }
    return name;
}

int* readFile(string fileName, int &sizeArr){
    fstream file(fileName, ios::in);
    if (!file.is_open())
    {
        cout << "File not exist\n";
        return nullptr;
    }

    int* a = (int*)malloc(sizeof(int)*sizeArr);

    file >> sizeArr;
    for (int i = 0; i < sizeArr; i++)
        file >> a[i];

    file.close();
    return a;
}

void writeDownFile(string fileName, int* a, int sizeArr){
    fstream file(fileName, ios::out);
    if (!file.is_open())
    {
        cout << "Failed to open file/n";
        return;
    }

    file << sizeArr << '\n';
    for (int i = 0; i < sizeArr; i++)
        file << a[i];
    
    file.close();
}

void printCommad1(int sizeArr, int argc, char* argv[], chrono::duration<double> duration){
    string algo = argv[2];
    string fileName = argv[3];

    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << nameDependOnSort(algo) << "\n";
    cout << "Input file: " << fileName << "\n";
    cout << "Input size: " << sizeArr << "\n";
    cout << "-----------------------\n";

    string outPara = argv[argc-1];
    if (outPara == "-time")
    {
        cout << "Running time: " << duration.count() << " seconds\n";
    } 
    else if (outPara == "-comp")
    {
        cout << "Comparision: " << comparision << "\n";
        comparision = 0;
    }
    else if (outPara == "-both")
    {
        cout << "Running time: " << duration.count() << " seconds\n";
        cout << "Comparision: " << comparision << "\n";
        comparision = 0;
    }
}

chrono::duration<double> countime(string nameSort, int* &a, int size){
    auto start = chrono::high_resolution_clock::now();
    sortDependOnAlgorithm(nameSort, a, size);
    auto end = chrono::high_resolution_clock::now();
    return end - start;
}

void Command1(int* &a, int argc, char* argv[]){
    string fileName = argv[3];
    string algo = argv[2];
    int sizeArr;
    a = readFile(fileName, sizeArr);
    
    chrono::duration<double> duration = countime(algo, a, sizeArr);
    printCommad1(sizeArr, argc, argv, duration);
    free(a);
    a = nullptr;
}

void printCommand2(int argc, char* argv[], chrono::duration<double> duration){
    string algo = argv[2];
    string sizeArr = argv[3];
    string order = argv[4];

    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << nameDependOnSort(algo) << "\n";
    cout << "Input size: " << sizeArr << "\n";
    cout << "Input order: " << order << "\n";
    cout << "-----------------------\n";

    string outPara = argv[argc-1];
    if (outPara == "-time")
    {
        cout << "Running time: " << duration.count() << " seconds\n";
    } 
    else if (outPara == "-comp")
    {
        cout << "Comparision: " << comparision << "\n";
        comparision = 0;
    } 
    else if (outPara == "-both")
    {
        cout << "Running time: " << duration.count() << " seconds\n";
        cout << "Comparision: " << comparision << "\n";
        comparision = 0;
    }
}

void Command2(int* &a, int argc, char* argv[]){
    string algo = argv[2];
    string size = argv[3];
    int sizeArr = stoi(size);
    string order = argv[4];
    a = (int*)malloc(sizeof(int)*sizeArr);

    if (order == "-rand")
    {
        GenerateData(a, sizeArr, 0);
    } 
    else if (order == "-sorted")
    {
        GenerateData(a, sizeArr, 1);
    } 
    else if (order == "-nsorted")
    {
        GenerateData(a, sizeArr, 3);
    } 
    else if (order == "-rev")
    {
        GenerateData(a, sizeArr, 2);
    }

    chrono::duration<double> duration = countime(algo, a, sizeArr);

    printCommand2(argc, argv, duration);

    writeDownFile("output.txt", a, sizeArr);
    free(a);
    a = nullptr;
}

void Command3(int* &a, int argc, char* argv[]){
    string algo = argv[2];
    string size = argv[3];
    string order;
    int sizeArr = stoi(size);

    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << nameDependOnSort(algo) << "\n";
    cout << "Input size: " << sizeArr << "\n";

    a = (int*)malloc(sizeof(int)*sizeArr);
    for (int i = 0; i < 4; i++){
        GenerateData(a, sizeArr, i);
        chrono::duration<double> duration = countime(algo, a, sizeArr);
        if (i == 0)
        {
            order = "Randomize";
        } 
        else if (i == 1)
        {
            order = "Sorted";
        } 
        else if (i == 2)
        {
            order = "Reverse";
        } 
        else if (i == 3)
        {
            order = "Nearly Sorted";
        };

        cout << "Input order: " << order << "\n";
        cout << "-----------------------\n";
        string outPara = argv[argc-1];

        if (outPara == "-time")
        {
            cout << "Running time: " << duration.count() << " seconds\n";
        } 
        else if (outPara == "-comp")
        {
            cout << "Comparision: " << comparision << "\n";
            comparision = 0;
        } 
        else if (outPara == "-both")
        {
            cout << "Running time: " << duration.count() << " seconds\n";
            cout << "Comparision: " << comparision << "\n";
            comparision = 0;
        }
    }
    free(a);
    a = nullptr;
}

void algorithmMode(int* &a, int argc, char* argv[]){
    if (argc == 6)
    {
        Command2(a, argc, argv);
    } 
    else if (argc == 5)
    {
        if (argv[3][0] <= 'z' && argv[3][0] >= 'A')
        {
            Command1(a, argc, argv);
        } 
        else 
        {
            Command3(a, argc, argv);
        }
    }
}

void printCommand4(int argc, char* argv[], int sizeArr, chrono::duration<double> duration1, chrono::duration<double> duration2, int compare1, int compare2){
    string name1 = argv[2];
    string name2 = argv[3];
    string fileName = argv[4];

    cout << "COMPARE MODE\n";
    cout << "Algorithm: " << nameDependOnSort(name1) << " | " << nameDependOnSort(name2) << "\n";
    cout << "Input file: " << fileName << "\n";
    cout << "Input size: " << sizeArr << "\n";
    cout << "-----------------------\n";
    cout << "Running time: " << duration1.count() << " | " << duration2.count() << "\n";
    cout << "Comparisions: " << compare1 << " | " << compare2 << "\n";
}

void Command4(int* &a, int argc, char* argv[] ){
    string algo1 = argv[2];
    string algo2 = argv[3];
    string fileName = argv[4];
    int sizeArr;
    a = readFile(fileName, sizeArr);

    chrono::duration<double> duration1 = countime(algo1, a, sizeArr);
    int compare1 = comparision;
    comparision = 0;

    chrono::duration<double> duration2 = countime(algo2, a, sizeArr);
    int compare2 = comparision;
    comparision = 0;

    printCommand4(argc, argv, sizeArr, duration1, duration2, compare1, compare2);
    free(a);
    a = nullptr;
}

void printCommand5(int argc, char* argv[], int sizeArr, chrono::duration<double> duration1, chrono::duration<double> duration2, int compare1, int compare2){
    string name1 = argv[2];
    string name2 = argv[3];
    string fileName = argv[4];
    string order = argv[5];

    if (order == "-rand")
    {
        order = "Randomize";
    } 
    else if (order == "-sorted")
    {
        order = "Sorted";
    } 
    else if (order == "-rev")
    {
        order = "Reverse";
    }
    else if (order == "-nsorted")
    {
        order = "Nearly Sorted";
    };

    cout << "COMPARE MODE\n";
    cout << "Algorithm: " << nameDependOnSort(name1) << " | " << nameDependOnSort(name2) << "\n";
    cout << "Input size: " << fileName << "\n";
    cout << "Input order: " << order << "\n";
    cout << "-----------------------\n";
    cout << "Running time: " << duration1.count() << " | " << duration2.count() << "\n";
    cout << "Comparisions: " << compare1 << " | " << compare2 << "\n";
}

void Command5(int* &a, int argc, char* argv[]){
    string algo1 = argv[2];
    string algo2 = argv[3];
    string size = argv[4];
    string order = argv[5];
    int sizeArr = stoi(size);
    a = (int*)malloc(sizeof(int)*sizeArr);
    if (order == "-rand")
    {
        GenerateData(a, sizeArr, 0);
    } 
    else if (order == "-sorted")
    {
        GenerateData(a, sizeArr, 1);
    } 
    else if (order == "-nsorted")
    {
        GenerateData(a, sizeArr, 3);
    } 
    else if (order == "-rev")
    {
        GenerateData(a, sizeArr, 2);
    }

    chrono::duration<double> duration1 = countime(algo1, a, sizeArr);
    int compare1 = comparision;
    comparision = 0;

    chrono::duration<double> duration2 = countime(algo2, a, sizeArr);
    int compare2 = comparision;
    comparision = 0;
    printCommand5(argc, argv, sizeArr, duration1, duration2, compare1, compare2);
    free(a);
    a = nullptr;
}

void comparisionMode(int* a, int argc, char* argv[]){
    if (argc == 5)
    {
        Command4(a, argc, argv);
    } 
    else if (argc == 6) 
    {
        Command5(a, argc, argv);
    }
}

bool checkInput(int argc, char* argv[]){
    string mode = argv[1];
    string nameSort = argv[2];
    string outPara = argv[argc-1];
    string typeSort[12] = {"quick-sort", "radix-sort", "counting-sort", "merge-sort", "heap-sort", "selection-sort", "bubble-sort",
    "shaker-sort", "flash-sort", "insertion-sort", "binary-insertion-sort", "shell-sort" };

    if (mode == "-a" && outPara != "-both" && outPara != "-comp" && outPara != "-time")
    {
        return false;
    }

    for (int i = 0; i < 12; i++)
        if (nameSort == typeSort[i])
            return true;

    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 4 || !checkInput(argc, argv)){
        cout << "Invalid input";
        return 1;
    }
    int* a = nullptr;
    string mode = argv[1];
    comparision = 0;
    
    if (mode == "-a")
    {
        algorithmMode(a, argc, argv);
    } 
    else if (mode == "-c")
    {
        comparisionMode(a, argc, argv);
    } 
    else 
    {
        cout << "Invalid mode";
    }
    return 0;
}
