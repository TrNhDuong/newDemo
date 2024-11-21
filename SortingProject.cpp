#include <iostream>
#include <algorithm>
using namespace std;

int comparision;
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



void flashSort(int* arr, int sizeArr) {
    int n = sizeArr;
    if (n <= 1) return;

    // Tìm giá trị lớn nhất và nhỏ nhất
    int minVal = arr[0], maxVal = arr[0];
    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxIndex = i;
        }
    }

    // Nếu tất cả phần tử bằng nhau, không cần sắp xếp
    if (minVal == maxVal) return;

    // Số lớp (buckets)
    int numClasses = static_cast<int>(0.45 * n);
    int* classCount = new int[numClasses](); // Khởi tạo mảng đếm với giá trị 0
    double classWidth = static_cast<double>(numClasses - 1) / (maxVal - minVal);

    // Tính toán số phần tử trong mỗi lớp
    for (int i = 0; i < n; ++i) {
        int k = static_cast<int>(classWidth * (arr[i] - minVal));
        classCount[k]++;
    }

    // Tính vị trí bắt đầu của mỗi lớp
    for (int i = 1; i < numClasses; ++i) {
        classCount[i] += classCount[i - 1];
    }

    // Hoán đổi và phân phối phần tử vào đúng lớp
    int nmove = 0;
    int j = 0, k = numClasses - 1;
    while (nmove < n) {
        while (j >= classCount[k]) {
            j++;
            k = static_cast<int>(classWidth * (arr[j] - minVal));
        }

        int flash = arr[j];
        while (j != classCount[k]) {
            k = static_cast<int>(classWidth * (flash - minVal));
            int t = --classCount[k];
            swap(arr[t], flash);
            nmove++;
        }
    }

    // Sắp xếp từng lớp bằng quickSort
    int start = 0;
    for (int i = 0; i < numClasses; ++i) {
        int end = (i == numClasses - 1) ? n : classCount[i];
        if (end - start > 1) { // Chỉ gọi quickSort nếu có hơn một phần tử
            quickSort(arr, start, end - 1);
        }
        start = end;
    }
    delete[] classCount; // Giải phóng bộ nhớ
}

int main(){
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i <n; i++)
        a[i] = rand()%(100);
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << "\n";
    flashSort(a, n);
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << "\n";
    delete[] a;
    return 0;
}