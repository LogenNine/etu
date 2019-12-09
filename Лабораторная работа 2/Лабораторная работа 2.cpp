#include <iostream>
#include <chrono>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::fixed;
//namespace chrono = chrono;
//using clock_type = chrono::high_resolution_clock;

const int size = 200;
int arr[size] = {};

void addElements() {
	cout << "array contains these elements:" << endl;
	for (int i = 0; i < size; ++i) {
		arr[i] = rand() % 100;
		cout << arr[i] << " ";
	}
	cout << endl;
}//addElements

int partition(int* arr, int start, int end) {
	int pivot = arr[end];
	int p_index = start;
	int i, t;
	//Here we will check if array value is 
	//less than pivot
	//then we will place it at left side
	//by swapping 
	for (i = start; i < end; i++) {
		if (arr[i] < pivot)
		{
			t = arr[i];
			arr[i] = arr[p_index];
			arr[p_index] = t;
			p_index++;
		}//if
	}//for
	//Now exchanging value of
	//pivot and P-index
	t = arr[end];
	arr[end] = arr[p_index];
	arr[p_index] = t;
	//at last returning the pivot value index
	return p_index;

}//partition

void quicksort(int* arr, int start, int end) {
	if (start < end) {
		int p_index = partition(arr, start, end);
		quicksort(arr, start, p_index - 1);
		quicksort(arr, p_index + 1, end);
	}
}//quicksort

int averageMatch(int* arr, int start, int end)
{
	int a = 0;
	int b = 0;
	a = (arr[start] + arr[end]) / 2;
	for (int i = 0; i < end; ++i) {
		if (a == arr[i]) ++b;
	}
	cout << "The average between min and max value of the elements is " << a << endl;
	cout << "There are " << b << " elements in the array that are equal to the average between min and max value of the elements" << endl;
	return 0;
}//averageMatch

int smallerMatch(int a, int* arr, int start, int end)
{
	int b = 0;
	for (int i = start; i < end; ++i)
	{
		if (arr[i] < a) ++b;
	}
	cout << "There are " << b << " elements in the array that are smaller than " << a << endl;
	return 0;
}//smallerMatch

int biggerMatch(int a, int* arr, int start, int end)
{
	int b = 0;
	for (int i = start; i < end; ++i)
	{
		if (a < arr[i]) ++b;
	}
	cout << "There are " << b << " elements in the array that are bigger than " << a << endl;
	return 0;
}

int replaceElement(int a, int b, int* arr, int start, int end) {
	for (int i = start; i < end; ++i) {
		if (a == i) arr[i] = b;
	}
	return 0;
}//replaceElement

void deleteElement(unsigned index)
{
	if (index >= size) return;
	for (unsigned u = index + 1; u < size; ++u) {
		arr[u - 1] = arr[u];
	}
}//deleteElement

int searchElement(int a, int* arr, int start, int end)
{
	for (int i = start; i < end; ++i) {
		if (a == i) cout << arr[i] << " lies at that index\n";
	}
	return 0;
}//deleteElement

int swapElement(int a, int b, int* arr) {
	int temp1 = arr[a];
	arr[a] = arr[b];
	arr[b] = temp1;
	return 0;
}

int symArray(int* arr, int size) {
	for (int i = 0; i < size / 2; ++i) {
		arr[size - i] = arr[size];
	}
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}

int main()
{
	int inputNum = 0;
	int inputForDel = 0;
	int inputSpotRepl = 0;
	int inputForRepl = 0;
	int inputForSearch = 0;
	int indForSwap1 = 0;
	int indForSwap2 = 0;
	char inputSpec;
	srand((unsigned int)time(0));
	addElements();
	quicksort(arr, 0, size - 1);
	cout << "after the quicksort array looks like this:" << endl;
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "smallest element is: " << arr[0] << " and biggest element is: " << arr[size - 1] << endl << endl;
	averageMatch(arr, 0, size - 1);
	for (;;) {
		cout << "In this step you will find how many elements in the array are bigger or smaller than the number you did input:" << endl;
		cout << "Now enter any number from " << 0 << " to " << INT_MAX << endl;
		cin >> inputNum;
		if (0 < inputNum && INT_MAX > inputNum) break;
		cout << "Error, wrong input, try to input any number from " << 0 << " to " << INT_MAX << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	for (;;) {
		cout << "do you want to find how many numbers are bigger than yours or how many numbers are smaller?" << endl;
		cout << "Input either 'b' for 'bigger' or 's' for 'smaller' to specify what you want:" << endl;
		cin >> inputSpec;
		switch (inputSpec) {

		case 'b': {
			biggerMatch(inputNum, arr, 0, size - 1);
			break;
		}
		case 's': {
			smallerMatch(inputNum, arr, 0, size - 1);
			break;
		}
		default:
		{
			cout << "error wrong input, try inputting 'b' or 's'" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		}
		break;
	}
	for (;;) {
		cout << "In this step you will replace element at the selected index:" << endl;
		cout << "chose where to insert the element, input number from 0 to " << size - 1 << endl;
		cin >> inputSpotRepl;
		if (0 < inputSpotRepl && size - 1 > inputSpotRepl) break;
		cout << "Error, wrong input, try to input any number from " << 0 << " to " << size - 1 << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	for (;;) {
		cout << "input the number with which to replace the element from the selected spot, it must be bigger than " << INT_MIN << " and smaller than " << INT_MAX << endl;
		cin >> inputForRepl;
		if (INT_MIN < inputForRepl && INT_MAX > inputForRepl) break;
		cout << "Error, wrong input, try to input any number from " << INT_MIN << " to " << INT_MAX << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	replaceElement(inputSpotRepl, inputForRepl, arr, 0, size - 1);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "speed of replacing element " << time_span.count() * pow(10.0, 9.0) << " nanoseconds" << endl;
	for (;;) {
		cout << "chose which element to delete, input number from 0 to " << size - 1 << endl;
		cin >> inputForDel;
		if (0 < inputForDel && size - 1 > inputForDel) break;
		cout << "Error, wrong input, try to input any number from " << 0 << " to " << size - 1 << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	deleteElement(inputForDel);
	high_resolution_clock::time_point t4 = high_resolution_clock::now();
	duration<double> time_span2 = duration_cast<duration<double>>(t4 - t3);
	cout << "speed of deleting element is " << time_span2.count() * pow(10.0, 9.0) << " nanoseconds" << endl;
	for (;;) {
		cout << "input the index of the element you want to retrieve, it must be smaller than " << size - 1 << endl;
		cin >> inputForSearch;
		if (0 < inputForSearch && size - 1 > inputForSearch) break;
		cout << "Error, wrong input, try to input any number from " << 0 << " to " << size - 1 << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	high_resolution_clock::time_point t5 = high_resolution_clock::now();
	searchElement(inputForSearch, arr, 0, size - 1);
	high_resolution_clock::time_point t6 = high_resolution_clock::now();
	duration<double> time_span3 = duration_cast<duration<double>>(t6 - t5);
	cout << "speed of searching for element " << time_span3.count() * pow(10.0, 8.0) << " nanoseconds" << endl;
	for (;;) {
		cout << "Input two indexes to swap elements that lie at those indexes, inputs must be bigger than 0 and smaller that " << size - 1 << endl;
		cin >> indForSwap1 >> indForSwap2;
		if (0 < indForSwap1 && 0 < indForSwap2 && size - 1 > indForSwap1 && size - 1 > indForSwap2) break;
		cout << "Error, wrong input, try to input numbers from " << 0 << " to " << size - 1 << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	cout << "At index " << indForSwap1 << " there is number " << arr[indForSwap1] << " and at index " << indForSwap2 << " there is number " << arr[indForSwap2] << endl;
	swapElement(indForSwap1, indForSwap2, arr);
	cout << "We changed those elements and now at index " << indForSwap1 << " there is number " << arr[indForSwap1] << " and at index " << indForSwap2 << " there is number " << arr[indForSwap2] << endl;
	//making symmetrical array
	symArray(arr, size);
	cout << "We made the array symmetrical:" << endl;
	cout << "You can now replace any element and the array and it will remain symmetrical" << endl;
	for (;;) {
		cout << "chose where to insert the element, input number from 0 to " << size - 1 << endl;
		cin >> inputSpotRepl;
		if (0 < inputSpotRepl && size - 1 > inputSpotRepl) break;
		cout << "Error, wrong input, try to input any number from " << 0 << " to " << size - 1 << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	for (;;) {
		cout << "input the number with which to replace the element from the selected spot, it must be bigger than " << INT_MIN << " and smaller than " << INT_MAX << endl;
		cin >> inputForRepl;
		if (INT_MIN < inputForRepl && INT_MAX > inputForRepl) break;
		cout << "Error, wrong input, try to input any number from " << INT_MIN << " to " << INT_MAX << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	cout << "As you can see the array is still symmetrical:" << endl;
	symArray(arr, size);
	return 0;
}