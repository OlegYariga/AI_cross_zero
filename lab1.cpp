// lab1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "iostream"
#include <stdlib.h>

using namespace std;

char strarea[] = "_________\n0 |1 |2 |\n__|__|__|\n3 |4 |5 |\n__|__|__|\n6 |7 |8 |\n__|__|__|\n";
//индексы символов, которые мы будем заменять
int massindex[] = { 10,13,16,30,33,36,50,53,56 };
// массив указателей на символы для замены
char *areapointer[8];
// прототип функции проверки выигрыш/проигрыш/ничья
int check_vin();
// функция МИНИМАКС
int minmax(int next_player);

//главный цикл
int main()
{
	// задаем русский язык в консоли
	setlocale(LC_ALL, "Russian");
	int step = 0;
	// заполняем массив указателей на элементы строки
	for (int i=0; i<9; i++) areapointer[i] = &strarea[massindex[i]];
	// выводим на экран начальную матрицу
	cout << strarea;
	while (true) {
		//проверяем победу компьютера, пользователя или ничью
		int res = check_vin();
		if (res == -1) { cout << "Вы выиграли!" << endl; break;}
		else if (res == 1) { cout << "Вы проиграли!" << endl; break;}
		else if (res == 0) { cout << "Ничья!" << endl; break;}
		//спрашиваем ход у пользователя и очищаем экран
		cout << "Выберите ход (0-8): "; cin >> step; system("cls");
		// преобразуем индекс в указатель на символ
		int radix = 10;	char buffer[20]; char *p;  //указатель на результат
		p = _itoa(step, buffer, radix);
		// проверяем, не занята ли клетка
		if (*areapointer[step] == *p) *areapointer[step] = 'O';
		else cout << "Нельзя ходить на занятую клетку. Теперь вы точно проиграете :)" << endl;

		int result = -10;
		int index = -1;
		for (int i = 0; i < 9; i++) {
			// преобразуем индекс в указатель на символ
			int radix = 10;	char buffer[20]; char *p;  //указатель на результат
			p = _itoa(i, buffer, radix);
			if (*areapointer[i] == *p) {
				*areapointer[i] = 'X';
				// вызываем функцию minmax(). 0 - человек, 1 - компьютер
				int new_result = minmax(0);
				*areapointer[i] = *p;
				//запоминаем наилучший результат
				if (new_result > result) {
					index = i;
					result = new_result;
				}
			}
		}
		if (index != -1) *areapointer[index] = 'X';
		cout << strarea;
	}
	system("pause");
	return 0;
}

int check_vin() {
	// проверяем победу пользователя по вертикали
	if (*areapointer[0] == *areapointer[1] && *areapointer[0] == *areapointer[2]) if (*areapointer[0] == 'O') return -1;
	if (*areapointer[3] == *areapointer[4] && *areapointer[3] == *areapointer[5]) if (*areapointer[3] == 'O') return -1;
	if (*areapointer[6] == *areapointer[7] && *areapointer[6] == *areapointer[8]) if (*areapointer[6] == 'O') return -1;
	// проверяем победу пользователя по горизонтали
	if (*areapointer[0] == *areapointer[3] && *areapointer[0] == *areapointer[6]) if (*areapointer[0] == 'O') return -1;
	if (*areapointer[1] == *areapointer[4] && *areapointer[1] == *areapointer[7]) if (*areapointer[1] == 'O') return -1;
	if (*areapointer[2] == *areapointer[5] && *areapointer[2] == *areapointer[8]) if (*areapointer[2] == 'O') return -1;
	// проверяем победу пользователя по диагонали
	if (*areapointer[0] == *areapointer[4] && *areapointer[0] == *areapointer[8]) if (*areapointer[0] == 'O') return -1;
	if (*areapointer[2] == *areapointer[4] && *areapointer[2] == *areapointer[6]) if (*areapointer[2] == 'O') return -1;

	// проверяем победу КОМПЬЮТЕРА по вертикали
	if (*areapointer[0] == *areapointer[1] && *areapointer[0] == *areapointer[2]) if (*areapointer[0] == 'X') return 1;
	if (*areapointer[3] == *areapointer[4] && *areapointer[3] == *areapointer[5]) if (*areapointer[3] == 'X') return 1;
	if (*areapointer[6] == *areapointer[7] && *areapointer[6] == *areapointer[8]) if (*areapointer[6] == 'X') return 1;
	// проверяем победу КОМПЬЮТЕРА по горизонтали
	if (*areapointer[0] == *areapointer[3] && *areapointer[0] == *areapointer[6]) if (*areapointer[0] == 'X') return 1;
	if (*areapointer[1] == *areapointer[4] && *areapointer[1] == *areapointer[7]) if (*areapointer[1] == 'X') return 1;
	if (*areapointer[2] == *areapointer[5] && *areapointer[2] == *areapointer[8]) if (*areapointer[2] == 'X') return 1;
	// проверяем победу КОМПЬЮТЕРА по диагонали
	if (*areapointer[0] == *areapointer[4] && *areapointer[0] == *areapointer[8]) if (*areapointer[0] == 'X') return 1;
	if (*areapointer[2] == *areapointer[4] && *areapointer[2] == *areapointer[6]) if (*areapointer[2] == 'X') return 1;

	// проверяем, остались ли еще свободные клетки
	for (int i = 0; i < 9; i++) {
		int radix = 10;  //система счисления
		char buffer[20]; //результат
		char *p;  //указатель на результат
		p = _itoa(i, buffer, radix);
		if (*areapointer[i] == *p) return -100;
	}
	// в противном случае, ничья
	return 0;
}

int minmax(int next_player) {
	//cout << "Зашел в minmax";
	int term = check_vin();
	if (term == -1) return -10;
	if (term == 1) return 10;
	if (term == 0) return 0;
	//если играет компьютер
	if (next_player == 1) {
		int result = -10;
		int index = 0;
		for (int i = 0; i < 9; i++) {
			int radix = 10;  //система счисления
			char buffer[20]; //результат
			char *p;  //указатель на результат
			p = _itoa(i, buffer, radix);
			if (*areapointer[i] == *p) {
				*areapointer[i] = 'X';
				// вызываем функцию minmax(). 0 - человек, 1 - компьютер
				int new_result = minmax(0);
				*areapointer[i] = *p;
				// запоминаем наилучший результат
				if (new_result > result) {
					//index = i;
					result = new_result;
				}
			}
		}
		return result;
	}
	//если играет человек
	if (next_player == 0) {
		int result = 10;
		int index = 0;
		for (int i = 0; i < 9; i++) {
			int radix = 10; char buffer[20]; char *p;  //указатель на результат
			p = _itoa(i, buffer, radix);
			if (*areapointer[i] == *p) {
				*areapointer[i] = 'O';
				// вызываем функцию minmax(). 0 - человек, 1 - компьютер
				int new_result = minmax(1);
				*areapointer[i] = *p;
				// запоминаем НАИХУДШИЙ результат
				if (new_result < result) {
					//index = i;
					result = new_result;
				}
			}
		}
		return result;
	}
}