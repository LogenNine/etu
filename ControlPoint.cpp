#include <iostream>
#include <windows.h>
#include <conio.h> //_getch
#include <fstream> //work with files
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
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
	//if (_getch() == 13)	return 1;
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

void arrayFill(int arr[], const int size, int darr[],int sizeD, int choice1, int choice2) {
	if (choice1 == 0) {
		if (choice2 == 0) {
			cout << "Введите " << sizeD << " чисел, для ввода числа нажмите enter" << endl;
			for (int i = 0; i < sizeD; i++) cin >> darr[i];
		}
		if (choice2 == 1) {
			for (int i = 0; i < sizeD; i++) darr[i] = rand();
		}
		if (choice2 == 2) {
			ofstream fout;
			fout.open("array.txt");
			for (int i = 0; i < sizeD; i++) {
				fout << rand() << " ";
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
			for (int i = 0; i < size; i++) arr[i] = rand();
		}
		if (choice2 == 2) {
			ofstream fout;
			fout.open("array.txt");
			for (int i = 0; i < size; i++) {
				fout << rand() << " ";
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

int arraysMenu() {
	const int size = 100;
	int arr[size], code = 0, key = 0, fib = 0, noFib = 0, sizeD = 0;
	int choice1, choice2, choice3;
	int* darr = new int[sizeD];
	double time = 0;
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
	code = 0;
	key = 0;
	cout << "На сортировку массива было потрачено " << time << " секунд" << endl;
	cout << "Из первых 15 чисел отсортированного массива " << fib << " являются числами Фибоначчи, а";
	cout << noFib << "не являются числами Фибоначчи" << endl;

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

		//code = _getch();
		//if (code == 224) {
			code = _getch();
			if (code == 80 || code == 115) key++;
			if (code == 72 || code == 119) key--;
		//}
	}
	system("cls");
	return key;
}

int main()
{
	srand(time(NULL));
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