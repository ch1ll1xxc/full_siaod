#include <iostream>
#include <random>
#include <chrono>
using namespace std;

void RandomFilling(int value, int array[]) {
	for (int i = 0; i < value; i++) {
		int tmp = rand();
		array[i] = tmp;
	}
}

void IncreasingFilling(int value, int array[]) {
	for (int i = 0; i < value; i++) {
		array[i] = i;
	}
}

void DecreasingFilling(int value, int array[]) {
	for (int i = 0; i < value; i++) {
		array[i] = value - i;
	}
}

void equaling(int value, int array_1[], int array_2[], int array_3[]) {
	for (int i = 0; i < value; i++) {
		array_2[i] = array_1[i];
		array_3[i] = array_1[i];
	}
}

void print(int value, int array[]) {
	for (int i = 0; i < value; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

void BubbleSortwAi(int value, int array[]) {
	long long unsigned compare = 0;
	long long unsigned move = 0;
	for (int i = 0; i < value; i++) {
		bool flag = true;
		for (int j = 0; j < value - i - 1; j++) {
			compare++;
			if (array[j] > array[j + 1]) {
				move++;
				swap(array[j], array[j + 1]);
				flag = false;
			}
		}
		if (flag) break; // условие Айверсона
	}
	cout << "C+M: " << compare << '+' << move << endl;
}

void ShakerSort(int value, int array[]) {
	long long unsigned compare = 0;
	long long unsigned move = 0;
	int left = 0;
	int right = value - 1;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = left; i < right; i++) {
			compare++;
			if (array[i] > array[i + 1]) {
				swap(array[i], array[i + 1]);
				move++;
				flag = true;
			}
		}
		flag = false;
		right--;
		for (int i = right - 1; i >= left; i--) {
			compare++;
			if (array[i] > array[i + 1]) {
				swap(array[i], array[i + 1]);
				move++;
				flag = true;
			}
		}
		left++;
	}
	cout << "C+M: " << compare << '+' << move << endl;
}

long long unsigned moves = 0;
long long unsigned comp = 0;

void Merge(int array[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	int* LeftArray = new int[n1];
	int* RightArray = new int[n2];
	for (int i = 0; i < n1; i++)
		LeftArray[i] = array[left + i];
	for (int j = 0; j < n2; j++)
		RightArray[j] = array[mid + 1 + j];

	int i = 0;
	int j = 0;
	int k = left;
	while (i < n1 && j < n2) {
		if (LeftArray[i] <= RightArray[j]) {
			array[k] = LeftArray[i];
			i++;
			moves++;
		}
		else {
			array[k] = RightArray[j];
			j++;
			moves++;
		}
		comp++;
		k++;
	}

	while (i < n1) {
		array[k] = LeftArray[i];
		i++;
		k++;
		moves++;
	}

	while (j < n2) {
		array[k] = RightArray[j];
		j++;
		k++;
		moves++;
	}
}

// Функция для сортировки массива слиянием
void MergeSort(int array[], int left, int right) {
	if (left >= right) {
		return;
	}

	int mid = left + (right - left) / 2;

	MergeSort(array, left, mid);
	MergeSort(array, mid + 1, right);

	Merge(array, left, mid, right);
}

void TakeTimeBubbleSort(int value, int array[]) {
	cout << "BubbleSort" << endl;
	auto start = chrono::steady_clock::now();
	BubbleSortwAi(value, array);
	auto end = chrono::steady_clock::now();
	chrono::duration<double>elapsed_seconds = end - start;
	cout << "Time: " << elapsed_seconds.count() << "s" << endl;
	cout << endl;
}

void TakeTimeShakerSort(int value, int array[]) {
	cout << "ShakerSort" << endl;
	auto start = chrono::steady_clock::now();
	ShakerSort(value, array);
	auto end = chrono::steady_clock::now();
	chrono::duration<double>elapsed_seconds = end - start;
	cout << "Time: " << elapsed_seconds.count() << "s" << endl;
	cout << endl;
}

void TakeTimeMergeSort(int value, int array[]) {
	cout << "MergeSort" << endl;
	auto start = chrono::steady_clock::now();
	MergeSort(array, 0, value - 1);
	auto end = chrono::steady_clock::now();
	chrono::duration<double>elapsed_seconds = end - start;
	cout << "Time: " << elapsed_seconds.count() << "s" << endl;
	cout << "C+M: " << comp << "+" << moves << endl;
}

void func(int value) {
	cout << "Number of elements: " << value << endl;
	int* array_1 = new int[value];
	int* array_2 = new int[value];
	int* array_3 = new int[value];
	IncreasingFilling(value, array_1);
	equaling(value, array_1, array_2, array_3);
	//TakeTimeBubbleSort(value, array_1);
	TakeTimeShakerSort(value, array_2);
	//TakeTimeMergeSort(value, array_3);
	cout << "_________________________________________________" << endl;
}

int main() {
	func(100);
	func(1000);
	func(10000);
	func(100000);
}