#include <iostream>
#include <chrono>
#include <ctime>

using namespace std::literals;
namespace chrono = std::chrono;
using clock_type = chrono::high_resolution_clock;

const int size = 200;
int arr[size] = {};

void addElements() {
	std::cout << "array contains these elements:" << std::endl;
	for (int i = 0; i < size; ++i) {
		arr[i] = rand() % 100;
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
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
	std::cout << "The average between min and max value of the elements is " << a << std::endl;
	std::cout << "There are " << b << " elements in the array that are equal to the average between min and max value of the elements" << std::endl;
	return 0;
}//averageMatch

int smallerMatch(int a, int* arr, int start, int end)
{
	int b = 0;
	for (int i = start; i < end; ++i)
	{
		if (arr[i] < a) ++b;
	}
	std::cout << "There are " << b << " elements in the array that are smaller than " << a << std::endl;
	return 0;
}//smallerMatch

int biggerMatch(int a, int* arr, int start, int end)
{
	int b = 0;
	for (int i = start; i < end; ++i)
	{
		if (a < arr[i]) ++b;
	}
	std::cout << "There are " << b << " elements in the array that are bigger than " << a << std::endl;
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
		if (a == i) std::cout << arr[i] << " lies at that index\n";
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
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
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
	std::cout << "after the quicksort array looks like this:" << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "smallest element is: " << arr[0] << " and biggest element is: " << arr[size - 1] << std::endl << std::endl;
	averageMatch(arr, 0, size - 1);
	for (;;) {
		std::cout << "In this step you will find how many elements in the array are bigger or smaller than the number you did input:" << std::endl;
		std::cout << "Now enter any number from " << 0 << " to " << INT_MAX << std::endl;
		std::cin >> inputNum;
		if (0 < inputNum && INT_MAX > inputNum) break;
		std::cout << "Error, wrong input, try to input any number from " << 0 << " to " << INT_MAX << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	for (;;) {
		std::cout << "do you want to find how many numbers are bigger than yours or how many numbers are smaller?" << std::endl;
		std::cout << "Input either 'b' for 'bigger' or 's' for 'smaller' to specify what you want:" << std::endl;
		std::cin >> inputSpec;
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
			std::cout << "error wrong input, try inputting 'b' or 's'" << std::endl;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}
		}
		break;
	}
	for (;;) {
		std::cout << "In this step you will replace element at the selected index:" << std::endl;
		std::cout << "chose where to insert the element, input number from 0 to " << size - 1 << std::endl;
		std::cin >> inputSpotRepl;
		if (0 < inputSpotRepl && size - 1 > inputSpotRepl) break;
		std::cout << "Error, wrong input, try to input any number from " << 0 << " to " << size - 1 << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	for (;;) {
		std::cout << "input the number with which to replace the element from the selected spot, it must be bigger than " << INT_MIN << " and smaller than " << INT_MAX << std::endl;
		std::cin >> inputForRepl;
		if (INT_MIN < inputForRepl && INT_MAX > inputForRepl) break;
		std::cout << "Error, wrong input, try to input any number from " << INT_MIN << " to " << INT_MAX << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	auto t1 = clock_type::now();
	replaceElement(inputSpotRepl, inputForRepl, arr, 0, size - 1);
	auto t2 = clock_type::now();
	auto interval = t2 - t1;
	std::cout << "speed of replacing element " << chrono::duration_cast<chrono::nanoseconds>(interval).count() << "ns\n";
	for (;;) {
		std::cout << "chose which element to delete, input number from 0 to " << size - 1 << std::endl;
		std::cin >> inputForDel;
		if (0 < inputForDel && size - 1 > inputForDel) break;
		std::cout << "Error, wrong input, try to input any number from " << 0 << " to " << size - 1 << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	auto t3 = clock_type::now();
	deleteElement(inputForDel);
	auto t4 = clock_type::now();
	auto interval2 = t4 - t3;
	std::cout << "speed of deleting element " << chrono::duration_cast<chrono::nanoseconds>(interval2).count() << "ns\n";
	for (;;) {
		std::cout << "input the index of the element you want to retrieve, it must be smaller than " << size - 1 << std::endl;
		std::cin >> inputForSearch;
		if (0 < inputForSearch && size - 1 > inputForSearch) break;
		std::cout << "Error, wrong input, try to input any number from " << 0 << " to " << size - 1 << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	auto t5 = clock_type::now();
	searchElement(inputForSearch, arr, 0, size - 1);
	auto t6 = clock_type::now();
	auto interval3 = t6 - t5;
	std::cout << "speed of searching for element " << chrono::duration_cast<chrono::nanoseconds>(interval3).count() << "ns\n";
	for (;;) {
		std::cout << "Input two indexes to swap elements that lie at those indexes, inputs must be bigger than 0 and smaller that " << size - 1 << std::endl;
		std::cin >> indForSwap1 >> indForSwap2;
		if (0 < indForSwap1 && 0 < indForSwap2 && size - 1 > indForSwap1 && size - 1 > indForSwap2) break;
		std::cout << "Error, wrong input, try to input numbers from " << 0 << " to " << size - 1 << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "At index " << indForSwap1 << " there is number " << arr[indForSwap1] << " and at index " << indForSwap2 << " there is number " << arr[indForSwap2] << std::endl;
	swapElement(indForSwap1, indForSwap2, arr);
	std::cout << "We changed those elements and now at index " << indForSwap1 << " there is number " << arr[indForSwap1] << " and at index " << indForSwap2 << " there is number " << arr[indForSwap2] << std::endl;
	//making symmetrical array
	symArray(arr, size);
	std::cout << "We made the array symmetrical:" << std::endl;
	std::cout << "You can now replace any element and the array and it will remain symmetrical" << std::endl;
	for (;;) {
		std::cout << "chose where to insert the element, input number from 0 to " << size - 1 << std::endl;
		std::cin >> inputSpotRepl;
		if (0 < inputSpotRepl && size - 1 > inputSpotRepl) break;
		std::cout << "Error, wrong input, try to input any number from " << 0 << " to " << size - 1 << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	for (;;) {
		std::cout << "input the number with which to replace the element from the selected spot, it must be bigger than " << INT_MIN << " and smaller than " << INT_MAX << std::endl;
		std::cin >> inputForRepl;
		if (INT_MIN < inputForRepl && INT_MAX > inputForRepl) break;
		std::cout << "Error, wrong input, try to input any number from " << INT_MIN << " to " << INT_MAX << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "As you can see the array is still symmetrical:" << std::endl;
	symArray(arr, size);
	return 0;
}

//TODO: fix the timer, it always grows