#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // Để đo thời gian
#include <cmath>
#include <ctime>
using namespace std;

int comparision;

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

void quicksort(int arr[], int left, int right) {
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
        quicksort(arr, left, j);
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
        if (array[i] > max)
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

void sortDependOnAlgorithm(string algo, int* a, int n){ 
    if (algo == "quick-sort")
    {
        quicksort(a, 0, n - 1);
    } 
    else if (algo == "radix-sort")
    {
        radixSort(a, n);
    } 
    else if (algo == "counting-sort")
    {
        countingSort(a, n);
    }
}

string nameDependOnSort(string algo){
    string name = algo;
    if (name == "radix-sort"){
        name = "Radix Sort";
    } else if (name == "quick-sort"){
        name = "Quick Sort";
    } else if (name == "counting-sort"){
        name = "Counting Sort";
    }
    return name;
}

int* readFile(string fileName, int &size){
    fstream file(fileName, ios::in);
    if (!file.is_open()){
        cout << "File not exist\n";
        return nullptr;
    }

    int* a = (int*)malloc(sizeof(int)*size);

    file >> size;
    for (int i = 0; i < size; i++)
        file >> a[i];

    file.close();
    return a;
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
    if (outPara == "-time"){
        cout << "Running time: " << duration.count() << " seconds\n";
    } else if (outPara == "-comp"){
        cout << "Comparision: " << comparision << "\n";
        comparision = 0;
    } else if (outPara == "-both"){
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
    
    // auto start = chrono::high_resolution_clock::now();
    // sortDependOnAlgorithm(algo, a, sizeArr);
    // auto end = chrono::high_resolution_clock::now();
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
    if (outPara == "-time"){
        cout << "Running time: " << duration.count() << " seconds\n";
    } else if (outPara == "-comp"){
        cout << "Comparision: " << comparision << "\n";
        comparision = 0;
    } else if (outPara == "-both"){
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

    // auto start = chrono::high_resolution_clock::now();
    // sortDependOnAlgorithm(algo, a, sizeArr);
    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration = end - start;
    chrono::duration<double> duration = countime(algo, a, sizeArr);

    printCommand2(argc, argv, duration);


    fstream fileout("output.txt", ios::out);
    fileout << sizeArr << "\n";
    for (int i = 0; i < sizeArr; i++)
        fileout << a[i] << ' ';
    fileout.close();
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
        // auto start = chrono::high_resolution_clock::now();
        // sortDependOnAlgorithm(algo, a, sizeArr);
        // auto end = chrono::high_resolution_clock::now();
        // chrono::duration<double> duration = end - start;
        chrono::duration<double> duration = countime(algo, a, sizeArr);
        if (i == 0){
            order = "Randomize";
        } else if (i == 1){
            order = "Sorted";
        } else if (i == 2){
            order = "Reverse";
        } else if (i == 3){
            order = "Nearly Sorted";
        };
        cout << "Input order: " << order << "\n";
        cout << "-----------------------\n";
        string outPara = argv[argc-1];
    if (outPara == "-time"){
        cout << "Running time: " << duration.count() << " seconds\n";
    } else if (outPara == "-comp"){
        cout << "Comparision: " << comparision << "\n";
        comparision = 0;
    } else if (outPara == "-both"){
        cout << "Running time: " << duration.count() << " seconds\n";
        cout << "Comparision: " << comparision << "\n";
        comparision = 0;
    }
    }
    free(a);
    a = nullptr;
}

void algorithmMode(int* &a, int argc, char* argv[]){
    if (argc == 6){
        Command2(a, argc, argv);
    } else if (argc == 5){
        if (argv[3][0] <= 'z' && argv[3][0] >= 'A'){
            Command1(a, argc, argv);
        } else {
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

    // auto start1 = chrono::high_resolution_clock::now();
    // sortDependOnAlgorithm(algo1, a, sizeArr);
    // auto end1 = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration1 = end1 - start1;
    chrono::duration<double> duration1 = countime(algo1, a, sizeArr);
    int compare1 = comparision;
    comparision = 0;

    // auto start2 = chrono::high_resolution_clock::now();
    // sortDependOnAlgorithm(algo2, a, sizeArr);
    // auto end2 = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration2 = end2 - start2;
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
    if (order == "-rand"){
        order = "Randomize";
    } else if (order == "-sorted"){
        order = "Sorted";
    } else if (order == "-rev"){
        order = "Reverse";
    } else if (order == "-nsorted"){
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

    // auto start1 = chrono::high_resolution_clock::now();
    // sortDependOnAlgorithm(algo1, a, sizeArr);
    // auto end1 = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration1 = end1 - start1;
    chrono::duration<double> duration1 = countime(algo1, a, sizeArr);
    int compare1 = comparision;
    comparision = 0;

    // auto start2 = chrono::high_resolution_clock::now();
    // sortDependOnAlgorithm(algo2, a, sizeArr);
    // auto end2 = chrono::high_resolution_clock::now();
    // chrono::duration<double> duration2 = end2 - start2;
    chrono::duration<double> duration2 = countime(algo2, a, sizeArr);
    int compare2 = comparision;
    comparision = 0;
    printCommand5(argc, argv, sizeArr, duration1, duration2, compare1, compare2);
    free(a);
    a = nullptr;
}

void comparisionMode(int* a, int argc, char* argv[]){
    if (argc == 5){
        Command4(a, argc, argv);
    } else if (argc == 6) {
        Command5(a, argc, argv);
    }
}

bool checkInput(int argc, char* argv[]){
    string mode = argv[1];
    string nameSort = argv[2];
    string outPara = argv[argc-1];
    if (nameSort != "quick-sort" && nameSort != "radix-sort" && nameSort != "counting-sort"){
        return false;
    }
    if (mode == "-a" && outPara != "-both" && outPara != "-comp" && outPara != "-time"){
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 4 || !checkInput(argc, argv)){
        cout << "Invalid input";
        return 1;
    }
    int* a = nullptr;
    string mode = argv[1];
    comparision = 0;
    
    if (mode == "-a"){
        algorithmMode(a, argc, argv);
    } else if (mode == "-c"){
        comparisionMode(a, argc, argv);
    } else {
        cout << "Invalid mode";
    }
    return 0;
}
