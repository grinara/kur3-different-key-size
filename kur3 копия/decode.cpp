#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
using namespace std;
void decode() {
	ifstream file1;
	file1.open("112.txt", ios::in | ios::binary);
	int* K1{ new int[256] };
	cdelatK1(K1);
	string key_tr;
	int file_str[100] = { 0 };
	int n = 4;
	int k = 0;
	int m = 97;
	char buff;
	bool fl = true;
	int i;
	int** key_mtr = new int* [n];
	for (int i = 0; i < n; ++i) {
		key_mtr[i] = new int[n];
	}
	int key_str[100] = { 0 };
	while (true) {
		cout << "������� ����" << endl;
		cin >> key_tr;
		if (!cheak_key(key_tr)) { cout << "������������ ����" << endl; }
		else { break; }
	}
	int p = key_tr.size();//���������� �������� � ������
	for (int i = 0; i < p; i++) { key_str[i] = key_tr[i]; }//�� ������� 30
	while (fl) {
		key_str[k] = K1[key_str[k]];
		n = key_str[k] % 4 + 2;// �� ������ ��� �� ������ ���� = 6
		k++;
		if (k == p) { k = 0; }
		//cout << n << " ";
		//cout << endl;
		for (i = 0; i < n; i++) {
			buff = file1.get(); // ��������� ��������� ������
			if (file1.eof()) {// ���� ���� �� ����������
				fl = false; n = i;
			}
			file_str[i] = buff - 30;
		}
		//for (int i = 0; i < n; i++) { cout << file_str[i] << " "; } cout << endl << endl;
		int** key_mtr = new int* [n];
		for (int i = 0; i < n; i++) {
			key_mtr[i] = new int[n];
			for (int j = 0; j < n; j++) {
				key_mtr[i][j] = 0;
			}
		}
		for (i = 0; i < n; i++) {//������ �������-����
			for (int j = 0; j < n; j++) {
				key_str[k] = K1[key_str[k]];
				key_mtr[i][j] = key_str[k] % m; //29;
				k++;
				if (k == p) { k = 0; };
			}
		}
		key_mtr = degenerate_matrix(key_mtr, n);
		//for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) { cout << key_mtr[i][j] << " "; }cout << endl; }cout << endl;
		key_mtr = invers(key_mtr, n);// ������ �������� ������� � ������� - �����
		//for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) { cout << key_mtr[i][j] << " "; }cout << endl; }cout << endl;
		//for (i = 0; i < n; i++) {
			//buff = file1.get(); // ��������� ��������� ������
			//if (file1.eof()) {// ���� ���� �� ����������
				//fl = false; n = i;
			//}
			//file_str[i] = buff - 30;
		//}
		//int k1 = i;
		int k1 = n;
		//for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) { cout << key_mtr[i][j] << " "; }cout << endl; }cout << endl;
		for (i = 0; i < k1; i++) { //���������  i ������� �������
			int S = 0;
			for (int j = 0; j < n; j++) {
				S = S + key_mtr[i][j] * file_str[j];
			}
			S = (S % 97) + 30;// �������� ���� - ���  ��������� �������
			//cout << S << " ";
			if (S == 30) {
				S = 13; cout << (char)S;  S = 10;// ���� ������� �� ������ ������

			}
			cout << (char)S;
		}
	}
}