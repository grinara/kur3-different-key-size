#include <iostream>  
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
//Для текста и ключа можно использовать символы, аски-код которых лежит
//в пределах промежутка [32,127]. Каждому символу ставится в соответствие
//число равное аски-код минус 30. Переходу на следущую строку (подряд 
//стоящие аски-коды 10 и 13) соответствует число 0. Число 1 указывает окончание текста. 
using namespace std;
void main() {
	setlocale(LC_ALL, "Russian");
	cout << "Алфавит" << endl;
	for (int i = 32; i < 127; i++) { cout << char(i) << " "; }
	cout << endl;
	//string key = "abcd";
	//string text = "exp(A+2)*C=?";
	int* K1{ new int[256] };
	cdelatK1(K1);
	ifstream file1;
	ofstream file_cip;
	string key_tr;
	int key_str[100] = { 0 };
	//int key_mtr[10][10] = { 0 };
	int file_str[100] = { 0 };
	int p;// размерность строки-ключа
	int n = 4;//размерность матрицы ключа
	int k = 0;
	int m = 97;//количество символов в алфавите
	char buff;
	bool fl = true;
	file1.open("12.txt", ios::in | ios::binary);
	file_cip.open("112.txt", ios::in | ios::trunc);
	if (!file1.is_open()) { cout << "Файл не открыт" << endl; return; }
	else if (file1.peek() == EOF) { cout << "Файл пуст" << endl; return; }
	else { cout << "Файл успешно открыт" << endl; }


	while (true) {
		cout << "Введите ключ(без пробелов)" << endl;
		cin >> key_tr;
		if (!cheak_key(key_tr)) { cout << "недопустимый ключ" << endl; }
		else { break; }
	}
	p = key_tr.size();//количество символов в строке
	for (int i = 0; i < p ; i++) { key_str[i] = key_tr[i]; }//по правилу 30
	//for (int i = 0; i < p; i++) { cout << key_str[i] << " "; }cout << endl << endl;
	while (fl) {
		key_str[k] = K1[key_str[k]];
		n = key_str[k] % 4 + 2;// не меньше мин не больше макс = 6
		k++;
		if (k == p) { k = 0; }
		//cout << n << " ";
		//cout << endl;
		for (int i = 0; i < n; i++) {//формируем блок символов
			buff = file1.get(); // считываем очередной символ
			//cout << (char)buff << " ";
			if (buff > 126 || (buff < 32 && buff != 13 && buff != 10 && buff != -1)) {//проверка на допустимость
				cout << "Файл содержит недопустимые символы" << endl;
				file1.close(); file_cip.close(); return;
			}
			if (buff == 13) { buff = file1.get(); buff = 30; }//если в ключе есть перенос строки
			if (file1.eof()) {// если текст  закончился
				fl = false; n = i;
			}
			//cout << (char)buff << " ";
			file_str[i] = buff - 30;// если текст не закончился
			
		}
		int** key_mtr = new int* [n];
		for (int i = 0; i < n; i++) {
			key_mtr[i] = new int[n];
			for (int j = 0; j < n; j++) {
				key_mtr[i][j] = 0;
			}
		}
		//cout << endl;
		for (int i = 0; i < n; i++) {//формируем матрицу ключ размерности n
			for (int j = 0; j < n; j++) {
				key_str[k] = K1[key_str[k]];
				key_mtr[i][j] = key_str[k] % m;
				//cout << key_mtr[i][j] << " ";
				k++;
				if (k == p) { k = 0; };
			}
			//cout << endl;
		}
		//cout << "*****" << " ";
		//cout << endl;
		//for (int i = 0; i < n; i++) { cout << file_str[i] << " "; }cout << endl << endl;
		
		if (n != 0) {
			key_mtr = degenerate_matrix(key_mtr, n);//проверяем на вырожденность
		}
		for (int i = 0; i < n; i++) { // кодируем i-элемент полученного вектора
			int S = 0;
			for (int j = 0; j < n; j++) {
				S = S + key_mtr[i][j] * file_str[j];
			}
			S = (S % 97) + 30; // получаем аски - код  шифрованного символа
			cout << (char)S << " "; // выводим этот символ на экран
			file_cip.write((char*)&S, sizeof(char)); //записываем его  в  файл
		}

		//for (int i = 0; i < n; i++) { cout << (char)V[i] << " "; }cout << endl<<endl;
		//for (int i = 0; i < n; i++) { cout << file_str[i] << " "; }cout << endl<<endl;
	}
	cout << endl;
	file1.close();
	file_cip.close();
	decode();
}
