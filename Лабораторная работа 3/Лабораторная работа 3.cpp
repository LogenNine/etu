#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>

using namespace std;

void matrFill(int** darr, int n, int m) {
	int code = 0, key = 0;
	while (code != 13) {
		system("cls");
		key = (key + 2) % 2;
		cout << "Выберите способ заполнения матрицы: " << endl;
		if (key == 0) cout << "-> Случайными числами от 0 до 9" << endl;
		else cout << "   Случайными числами от 0 до 9" << endl;
		if (key == 1) cout << "-> Вручную" << endl;
		else cout << "   Вручную" << endl;

		code = _getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;
	}
	system("cls");
	if (key == 0) {
		cout << "Так выглядит матрица заполненная случайными числами: " << endl;
		for (int i = 0; i < m; i++) { // строки
			for (int p = 0; p < n; p++) {//столбцы
				darr[p][i] = rand() % 10;
				cout << darr[p][i] << " ";
			}
			cout << endl;
		}
	}
	else {
		for (int i = 0; i < m; i++) {
			for (int p = 0; p < n; p++) {
				cout << "Введите элемент с индексом [" << p << "," << i << "]:" << endl;
				cin >> darr[p][i];
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Допустим ввод только целых арабских чисел, повторите попытку ввода." << endl;
				}
			}
		}
	}
	system("pause");
}

void matrShow(int** darr, int n, int m) {
	cout << "Так выглядит ваша матрица: " << endl;
	for (int i = 0; i < m; i++) { // строки
		for (int p = 0; p < n; p++) {//столбцы
			cout << darr[p][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}



int determinant(int** matrix, int size) {
	int det, coeff = 1, i, j, sub_j, temp;
	int** newMatr; //набор ссылок на исходную матрицу
	if (size == 1) {
		return matrix[0][0];
	}
	else if (size == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {
		newMatr = new int* [(long long int)size - 1]; //массив ссылок на столбцы новой матрицы
		det = 0;
		for (i = 0; i < size; i++) {
			sub_j = 0;
			for (j = 0; j < size; j++) { // Заполняем новую матрицу ссылками на исходные столбцы
				if (i != j)	// исключаем i-тую строку
					newMatr[sub_j++] = matrix[j] + 1; // +1 исключает первый столбец		
			}
			temp = determinant(newMatr, size - 1); //рекурсивно вызывая функцию мы все сводим к вычислению миноров второго порядка
			//cout << "Определитель: " << det << " + Индекс: " << coeff << " * значение ячейки [" << i << "][0]: " << matrix[i][0] << " * Минор: " << temp << endl;;
			det = det + coeff * matrix[i][0] * temp;
			coeff = -coeff; //меняем знак минора
		}
		delete[] newMatr;
		return det;
	}
}

int rankOfMatrix(int** matrix, int n, int m) {
	int rank = 0;
	int q = 1;
	int minDim = n <= m ? n : m; //минимальный размер матрицы
	while (q <= minDim) // проверка: порядок матрицы меньше или равен минимальному из размеров матрицы?
	{ // если да
		int** newMatrix = new int* [q]; // создаем новую матрицу размера q
		for (int i = 0; i < q; i++) newMatrix[i] = new int[q];
		for (int a = 0; a < (n - (q - 1)); a++) { //перебор матриц q-го порядка
			for (int b = 0; b < (m - (q - 1)); b++) {
				for (int c = 0; c < q; c++) {
					for (int d = 0; d < q; d++) {
						newMatrix[c][d] = matrix[a + c][b + d];
					}
				}
				if (determinant(newMatrix, q) != 0) // если определитель отличен от нуля
				{
					rank = q; //присваиваем рангу значение q
				}
			}
		}
		q++;
	}
	return rank;
}
void saddlePoints(int** matrix, int n, int m) {
	int column = 0;
	int counter = 0;
	int saddlePointsAmount = 0;
	for (int row = 0; row < m; row++) {//наибольший элемент в своей строке и наименьший в столбце
		int temp = matrix[0][row];
		for (int i = 1; i < n; i++) {
			if (matrix[i][row] > temp) {
				temp = matrix[i][row];
				column = i;
			}
		}
		for (int j = 0; j < m; j++) {
			if (temp < matrix[column][j]) counter++;
		}
		if (counter == m - 1) {
			cout << "Элемент " << matrix[column][row] << " с индексом [" << column << "][" << row << "] является седловой точкой." << endl;
			saddlePointsAmount++;
		}
		counter = 0;
	}
	counter = 0;
	column = 0;
	for (int row = 0; row < m; row++) {//наименьший элемент в своей строке и наибольший в столбце
		int temp = matrix[0][row];
		for (int i = 1; i < n; i++) {
			if (matrix[i][row] < temp) {
				temp = matrix[i][row];
				column = i;
			}
		}
		for (int j = 0; j < m; j++) {
			if (temp > matrix[column][j]) counter++;
		}
		if (counter == m - 1) {
			cout << "Элемент " << matrix[column][row] << " с индексом [" << column << "][" << row << "] является седловой точкой." << endl;
			saddlePointsAmount++;
		}
		counter = 0;
	}
	if (saddlePointsAmount == 0) cout << endl << "В данной матрице нет седловых точек!" << endl;
}

int menu() {
	int code = 0, key = 0;
	while (code != 13) {
		system("cls");
		key = (key + 7) % 7;
		if (key == 0) cout << "-> Заполнение матрицы" << endl;
		else cout << "   Заполнение матрицы" << endl;
		if (key == 1) cout << "-> Определитель матрицы" << endl;
		else cout << "   Определитель матрицы" << endl;
		if (key == 2) cout << "-> Ранг матрицы" << endl;
		else cout << "   Ранг матрицы" << endl;
		if (key == 3) cout << "-> Индексы седловых точек матрицы" << endl;
		else cout << "   Индексы седловых точек матрицы" << endl;
		if (key == 4) cout << "-> Вывести матрицу в консоль" << endl;
		else cout << "   Вывести матрицу в консоль" << endl;
		if (key == 5) cout << "-> Создать новую матрицу с другими размерами" << endl;
		else cout << "   Создать новую матрицу с другими размерами" << endl;
		if (key == 6) cout << "-> Выйти из программы" << endl;
		else cout << "   Выйти из программы" << endl;

		code = _getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;
	}
	system("cls");
	return key;
}

int main() {
	setlocale(0, "");
	srand((unsigned int)time(NULL));
	int m, n;
	for (;;) {
		cout << "Введите количество столбцов, а затем количество строк в матрице: " << endl;
		cin >> n >> m;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Допустим ввод только целых, положительных, арабских чисел больше нуля, повторите попытку ввода." << endl;
		}
		else if (n < 1 || m < 1) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Допустим ввод только целых, положительных, арабских чисел больше нуля, повторите попытку ввода." << endl;
		}
		else break;
	}
	int** darr = new int* [n];
	for (int i = 0; i < n; i++) {
		darr[i] = new int[m];
	}
	for (;;) {
		int answer = menu();
		switch (answer) {
		case 0: {//заполнение матрицы
			matrFill(darr, n, m);
			break;
		}
		case 1: { //определитель матрицы
			if (n == m) {
				matrShow(darr, n, m);
				cout << "Определитель матрицы равен " << determinant(darr, n) << endl;
				system("pause");
			}
			else {
				cout << "Матрица должна быть квадратной!" << endl;
				system("pause");
			}
			break;
		}
		case 2: {// ранг матрицы
			matrShow(darr, n, m);
			cout << "Ранг матрицы равен: " << rankOfMatrix(darr, n, m) << endl;
			system("pause");
			break;
		}
		case 3: {// индексы седловых точек
			matrShow(darr, n, m);
			saddlePoints(darr, n, m);
			system("pause");
			break;
		}
		case 4: {//вывод матрицы в консоль
			matrShow(darr, n, m);
			system("pause");
			break;
		}
		case 5: {
			delete[] darr;
			main();
		}
		case 6: {
			return 0;
		}
		}//switch

	}
	return 0;
}
//https://prog-cpp.ru/matrix-determinant/ определитель
//http://liloisproj.narod.ru/mat_rang.htm ранг
