#include <iostream>
#include <windows.h>
#include <conio.h> //_getch
#include <fstream> //work with files
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
using namespace std;

int registration() {
	system("chcp 1251");
	system("cls");
	string name, password;
	cout << "Введите имя пользователя:" << endl;
	cin >> name;
	cout << "Введите пароль пользователя:" << endl;
	cin >> password;
	ofstream fout;
	fout.open("data.txt");
	fout << "имя_пользователя:" << endl << name << endl << "пароль_пользователя:" << endl << password;
	fout.close();
	return 0;
}

int login() {
	system("chcp 1251");
	system("cls");
	int crutch = 0;
	string name, password, nameInFile, passwordInFile;
	ifstream fin("data.txt");
	for (int i = 0; i < 2; i++) fin >> nameInFile;
	for (int i = 0; i < 4; i++) fin >> passwordInFile;
	fin.close();
	cout << "Введите имя пользователя: " << endl;
	for (;;) {
		cin >> name;
		if (name != nameInFile) cout << "Пользователь не найден, попробуйте ввести имя еще раз" << endl;
		else break;
	}
	cout << "Введите пароль пользователя: " << endl;
	for (;;) {
		auto code = _getch();
		if (code == 13) {
			system("cls");
			if (password != passwordInFile) {
				cout << "Пароль не совпадает, попробуйте ввести пароль еще раз: " << endl;
				//cout << "Пароль в файле - " << passwordInFile << endl << "Введеный пароль - " << password << endl; //Отладка
				while (!password.empty()) password.pop_back();
				crutch++;
			}
			else if (password == passwordInFile) break;			
		}
		if (code == 8) {
			if (!password.empty()) {
				cout << "\b \b";
				password.pop_back();
			}
		}
		else {			
			const auto ch = static_cast<char>(code);
			password += ch;
			cout << "*";
			if (!password.empty() && crutch != 0) { //стираем непонятный символ который все портит
				cout << "\b \b";
				password.pop_back();
				crutch = 0;
			}
		}
	}
	//cout << "Поздравляем! Вы вошли в систему!" << endl << "Нажмите enter для того чтобы продолжить...";
	return 1;
}

int binaryRep(int target) {
	//system("chcp 1251");
	int group = 9894, bits[8];
	string familyName = ("Романовский");
	int bitSize = sizeof(group) * 8;
	int stringSize = familyName.length();
	if (target == 0) {
		for (int i = bitSize - 2; i >= 0; --i) {
			int b = group & (1LL << i);
			cout << (b == 0 ? 0 : 1);
			if ((i & 7) == 0) cout << " ";
		}
	} else {
		//cout << stringSize << " <- Размер familyName" << endl;
		for (int i = 0; i < stringSize; i++) {
			char val = char(familyName[i]);
			for (int i = 0; i < 8; i++) bits[i] = ((1 << i) & val) != 0 ? 1 : 0;
			for (int i = 7; i >= 0; i--) cout << bits[i];	
			cout << " ";
		}
	}
	return 0;
}

int welcome(int logCheck) {
	int key = 0, code = 0;
	string name;

	while (code != 13) {
		system("cls");
		key = (key + 2) % 2;
		ifstream fin("data.txt");
		if (!fin.is_open()) {
			cout << "Для того чтобы увидеть полное приветствие нужно зарегестрироватся и войти в систему" << endl << "Для этого выйдите в главное меню и выберите первый пункт" << endl;
			if (key == 0) cout << "-> Выйти в главное меню" << endl;
			else cout << "   Выйти в главное меню" << endl;
			if (key == 1) cout << "-> Увидеть неполное приветствие" << endl;
			else cout << "   Увидеть неполное приветствие" << endl;
		} 
		else if (logCheck == 0) {
			cout << "Для того чтобы увидеть полное приветствие нужно войти в систему" << endl << "Для этого выйдите в главное меню и выберите первый пункт" << endl;
			if (key == 0) cout << "-> Выйти в главное меню" << endl;
			else cout << "   Выйти в главное меню" << endl;
			if (key == 1) cout << "-> Увидеть неполное приветствие" << endl;
			else cout << "   Увидеть неполное приветствие" << endl;
		}
		else {
			for (int i = 0; i < 2; i++) fin >> name;
			cout << "Уважаемый " << name << " вы можете увидеть полное приветствие!" << endl << "Просто выберите второй пункт меню" << endl;
			if (key == 0) cout << "-> Выйти в главное меню" << endl;
			else cout << "   Выйти в главное меню" << endl;
			if (key == 1) cout << "-> Увидеть полное приветствие" << endl;
			else cout << "   Увидеть полное приветствие" << endl;
		}
		fin.close();
		code = _getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;
	}
	system("cls");
	if (key == 0) return 0;
	ifstream fin("data.txt");
	if (key == 1 && !fin.is_open() || logCheck == 0) {
		fin.close();
		cout << "Приветствую, тебя Пользователь N" << endl;
		cout << "Эту программу написал студент группы 9894, Романовский Максим Алексеевич" << endl;
		cout << "Кстати, в памяти моего компьютера номер мой группы выглядит как:" << endl << endl;
		binaryRep(0);
		cout << endl << endl << "А моя фамилия как:" << endl << endl;
		binaryRep(1);
		cout << endl << endl << "Для того чтобы выйти в главное меню нажмите enter...";
		if (_getch() == 13) return 0;
	}
	if (key == 1 && logCheck == 1) {
		fin.close();
		cout << "Приветствую, тебя " << name << endl;
		cout << "Эту программу написал студент группы 9894, Романовский Максим Алексеевич" << endl;
		cout << "Кстати, в памяти моего компьютера номер мой группы выглядит как:" << endl << endl;
		binaryRep(0);
		cout << endl << endl << "А моя фамилия как:" << endl << endl;
		binaryRep(1);
		cout << endl << endl << "Для того чтобы выйти в главное меню нажмите enter...";
		if (_getch() == 13) return 0;
	}
	fin.close();
	return 0;
}

void arrayFill(int arr[], const int size, int darr[], int sizeD, int choice1, int choice2) {
	if (choice1 == 0) {
		if (choice2 == 0) {
			cout << "Введите " << sizeD << " чисел, для ввода числа нажмите enter" << endl;
			for (int i = 0; i < sizeD; i++) cin >> darr[i];
		}
		if (choice2 == 1) {
			for (int i = 0; i < sizeD; i++) darr[i] = rand()%100;
		}
		if (choice2 == 2) {
			ofstream fout;
			fout.open("array.txt");
			for (int i = 0; i < sizeD; i++) {
				fout << rand()%100 << " ";
			}
			fout.close();
			int num = 0;
			ifstream fin("array.txt");
			for (int i = 0; i < sizeD; i++) {
				fin >> num;
				darr[i] = num;
			}
			fin.close();
		}
	}
	if (choice1 == 1) {
		if (choice2 == 0) {
			cout << "Введите " << size << " чисел, для ввода числа нажмите enter" << endl;
			for (int i = 0; i < size; i++) cin >> arr[i];
		}
		if (choice2 == 1) {
			for (int i = 0; i < size; i++) arr[i] = rand()%100;
		}
		if (choice2 == 2) {
			ofstream fout;
			fout.open("array.txt");
			for (int i = 0; i < size; i++) {
				fout << rand()%100 << " ";
			}
			fout.close();
			int num = 0;
			ifstream fin("array.txt");
			for (int i = 0; i < size; i++) {
				fin >> num;
				arr[i] = num;
			}
			fin.close();
		}
	}
}

int partition(int arr[],int start, int end) {
	int pivot = arr[end];
	int p_index = start;
	int t;
	for (int i = start; i < end; i++) {
		if (arr[i] < pivot) {
			t = arr[i];
			arr[i] = arr[p_index];
			arr[p_index] = t;
			p_index++;
		}
	}
	t = arr[end];
	arr[end] = arr[p_index];
	arr[p_index] = t;
	return p_index;
}

void quicksort(int arr[], int start, int end) {
	if (start < end) {
		int p_index = partition(arr, start, end);
		quicksort(arr, start, p_index - 1);
		quicksort(arr, p_index + 1, end);
	}
}

void arraySort(int choice1, int arr[], const int size, int darr[], int sizeD, int choice3) {
	int tempSize = 0;
	if (choice1 == 0) {
		if (choice3 == 0) { //bubble
			for (int i = 0; i < sizeD; i++) {
				for (int j = i + 1; j < sizeD; j++) {
					if (darr[j] < darr[i]) swap(darr[i], darr[j]);
				}
			}
		} // choice3 == 0 
		if (choice3 == 1) { //shaker
			tempSize = sizeD;
			for (int i = 0; i < tempSize;) {
				for (int j = i + 1; j < tempSize; j++) {
					if (darr[j] < darr[j-1]) swap(darr[j], darr[j - 1]);
				}
				tempSize--;
				for (int k = tempSize - 1; k > i; k--) {
					if (darr[k] < darr[k - 1]) swap(darr[k], darr[k - 1]);
				}
				i++;
			}
		}//choice3 == 1
		if (choice3 == 2) {//Comb sort
			int gap = sizeD;
			bool flag = true;
			while (gap != 1 || flag == true) {
				gap = (gap * 10) / 13;
				if (gap < 1) gap = 1;
				flag = false;
				for (int i = 0; i < sizeD - gap; i++) {
					if (darr[i] > darr[i + gap]) {
						swap(darr[i], darr[i + gap]);
						flag = true;
					}
				}
			}
		}//choice3 == 2
		if (choice3 == 3) {//insert sort
			int key, j;
			for (int i = 1; i < sizeD; i++) {
				key = darr[i];
				j = i;
				while (j > 0 && darr[j - 1] > key) {
					darr[j] = darr[j - 1];
					j--;
				}
				darr[j] = key;
			}
		}//choice3 == 3
		if (choice3 == 4) {//quick sort
			quicksort(darr, 0, sizeD - 1);			
		}//choice3 == 4
	}
	if (choice1 == 1) {
		if (choice3 == 0) { //bubble
			for (int i = 0; i < size; i++) {
				for (int j = i + 1; j < size; j++) {
					if (arr[j] < arr[i]) swap(arr[i], arr[j]);
				}
			}
		} // choice3 == 0 
		if (choice3 == 1) { //shaker
			tempSize = size;
			for (int i = 0; i < tempSize;) {
				for (int j = i + 1; j < tempSize; j++) {
					if (arr[j] < arr[j - 1]) swap(arr[j], arr[j - 1]);
				}
				tempSize--;
				for (int k = tempSize - 1; k > i; k--) {
					if (arr[k] < arr[k - 1]) swap(arr[k], arr[k - 1]);
				}
				i++;
			}
		}//choice3 == 1
		if (choice3 == 2) {//Comb sort
			int gap = size;
			bool flag = true;
			while (gap != 1 || flag == true) {
				gap = (gap * 10) / 13;
				if (gap < 1) gap = 1;
				flag = false;
				for (int i = 0; i < size - gap; i++) {
					if (arr[i] > arr[i + gap]) {
						swap(arr[i], arr[i + gap]);
						flag = true;
					}
				}
			}
		}//choice3 == 2
		if (choice3 == 3) {//insert sort
			int key, j;
			for (int i = 1; i < size; i++) {
				key = arr[i];
				j = i;
				while (j > 0 && arr[j - 1] > key) {
					arr[j] = arr[j - 1];
					j--;
				}
				arr[j] = key;
			}
		}//choice3 == 3
		if (choice3 == 4) {//quick sort
			quicksort(arr, 0, size - 1);
		}//choice3 == 4
	}
}

int fib(int fibArr[], int arr[], int fib) {
	int a = 0, b = 1;
	fibArr[0] = a;
	fibArr[1] = b;
	for (int i = 2; i < 30; i++) {
		fibArr[i] = fibArr[i - 1] + fibArr[i - 2];
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 30; j++) {
			if (fibArr[j] == arr[i]) {
				fib++;
				break;
			}
		}
	}
	cout << "Из первых 15 чисел отсортированного массива " << fib << " являются числами Фибоначчи, а ";
	cout << 15 - fib << " не являются числами Фибоначчи" << endl;
	return 0;
}

int averageAndMedian(int arr[], int size, int median, int average, int moda) {
	int temp = 0;
	int count = 0;
	median = arr[size / 2];
	for (int i = 0; i < size; i++) {
		temp += arr[i];
		count++;
	}
	average = temp / count;
	count = 0;
	int z = 0;
	for (int n = 0; n < size; n++) {
		for (int p = 0; p < size; p++) {
			if (arr[n] == arr[p]) count++;
		}
		if (count > 1) {
			if (count > z) {
				z = count;
				moda = arr[n];
			}
			count = 0;
		}
	}

	cout << "Среднее значение массива = " << average << " медиана = " << median << " а мода = " << moda << endl;
	return 0;
}

int arraysMenu() {
	const int size = 100;
	int arr[size], code = 0, key = 0, fibC = 0, sizeD = 0, fibArr[30], median = 0, average = 0, moda = 0;
	int choice1, choice2, choice3;
	while (code != 13) {
		system("cls");
		key = (key + 2) % 2;
		cout << "Динамический или статический массив?" << endl;
		if (key == 0) cout << "-> Динамический" << endl;
		else cout << "   Динамический" << endl;
		if (key == 1) cout << "-> Статический размером 100 элементов" << endl;
		else cout << "   Статический размером 100 элементов" << endl;
		code = _getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;
	}
	choice1 = key;
	if (choice1 == 0) {
		cout << "Введите размер динамического массива:" << endl;
		cin >> sizeD;
	}
	int* darr = new int[sizeD];
	code = 0;
	key = 0;
	while (code != 13) {
		system("cls");
		key = (key + 3) % 3;
		cout << "Заполнить массив вручную, случайными числами или считать его с файла?" << endl;
		if (key == 0) cout << "-> Вручную" << endl;
		else cout << "   Вручную" << endl;
		if (key == 1) cout << "-> Случайными числами" << endl;
		else cout << "   Случайными числами" << endl;
		if (key == 2) cout << "-> Считать с файла" << endl;
		else cout << "   Считать с файла" << endl;
		code = _getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;
	}
	choice2 = key;
	arrayFill(arr, size, darr, sizeD, choice1, choice2);
	code = 0;
	key = 0;
	while (code != 13) {
		system("cls");
		key = (key + 5) % 5;
		if (choice1 == 0) {
			cout << "Содержание динамического массива: " << endl;
			for (int i = 0; i < sizeD; i++) cout << darr[i] << " ";
			cout << endl;
		}
		if (choice1 == 1) {
			cout << "Содержание статического массива: " << endl;
			for (int i = 0; i < size; i++) cout << arr[i] << " ";
			cout << endl;
		}
		cout << "Выберите метод сортировки" << endl;
		if (key == 0) cout << "-> Bubble sort" << endl;
		else cout << "   Bubble sort" << endl;
		if (key == 1) cout << "-> Shaker sort" << endl;
		else cout << "   Shaker sort" << endl;
		if (key == 2) cout << "-> Comb sort" << endl;
		else cout << "   Comb sort" << endl;
		if (key == 3) cout << "-> Insert sort" << endl;
		else cout << "   Insert sort" << endl;
		if (key == 4) cout << "-> Quick sort" << endl;
		else cout << "   Quick sort" << endl;
		code = _getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;
	}
	choice3 = key;
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	arraySort(choice1, arr, size, darr, sizeD, choice3);
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	code = 0;
	key = 0;
	cout << "Так выглядит массив после сортировки: " << endl;
	if (choice1 == 0) {
		for (int i = 0; i < sizeD; i++) cout << darr[i] << " ";
		cout << endl;
	}
	if (choice1 == 1) {
		for (int i = 0; i < size; i++) cout << arr[i] << " ";
		cout << endl;
	}
	cout << "На сортировку массива было потрачено " << time_span.count() << " секунд" << endl;
	if(choice1 == 0) fib(fibArr, darr, fibC);
	if (choice1 == 1) fib(fibArr, arr, fibC);
	//for (int i = 0; i < 30; i++) cout << fibArr[i] << " ";
	if (choice1 == 0) averageAndMedian(darr, sizeD, median, average, moda);
	if (choice1 == 1) averageAndMedian(arr, size, median, average, moda);	
	cout << endl;
	while (code != 13) {
		cout << "Нажмите enter чтобы вернутся в главное меню..." << endl;
		code = _getch();
	}
	return 0;
}

int menu(int logCheck) {
	int key = 0, code = 0;
	string name;
	while (code != 13) {
		system("cls");
		key = (key + 5) % 5;
		ifstream fin("data.txt");
		if (!fin.is_open()) {
			cout << "Пожалуйста зарегистрируйтесь" << endl;
		}
		else if (logCheck == 0) cout << "Пожалуйста войдите в систему" << endl;
		else {
			for (int i = 0; i < 2; i++) fin >> name;
			cout << "Добро пожаловать " << name << endl;
		}
		if (!fin.is_open()) {
			if (key == 0) cout << "-> Регистрация нового пользователя" << endl;
			else cout << "   Регистрация нового пользователя" << endl;
		}
		else {
			if (key == 0) cout << "-> Вход в систему" << endl;
			else cout << "   Вход в систему" << endl;

		}
		fin.close();
		if (key == 1) cout << "-> Приветствие" << endl;
		else cout << "   Приветствие" << endl;

		if (key == 2) cout << "-> Массивы" << endl;
		else cout << "   Массивы" << endl;

		if (key == 3) cout << "-> Флаги" << endl;
		else cout << "   Флаги" << endl;

		if (key == 4) cout << "-> Выход" << endl;
		else cout << "   Выход" << endl;

			code = _getch();
			if (code == 80 || code == 115) key++;
			if (code == 72 || code == 119) key--;
	}
	system("cls");
	return key;
}

int main()
{
	srand((unsigned int)time(NULL));
	setlocale(0, "");
	int logCheck = 0;
	for (;;) {
		int answer = menu(logCheck);
		switch (answer) {
			case 0: {
				ifstream fin("data.txt");
				if (!fin.is_open()) registration();
				else logCheck = login();
				fin.close();
				break;
			}
			case 1: {
				welcome(logCheck);
				break;
			}
			case 2: {
				arraysMenu();
				break;
			}
			case 3: {
				cout << "Work in progress. Нажмите enter чтобы продолжить..." << endl;
				if (_getch() == 13) break;
			}
			case 4: {
				return 0;
			}
		}
	}
	system("pause");
	return 0;
}