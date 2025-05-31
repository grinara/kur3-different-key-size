#include <iostream>  
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
//��� ������ � ����� ����� ������������ �������, ����-��� ������� �����
//� �������� ���������� [32,127]. ������� ������� �������� � ������������
//����� ������ ����-��� ����� 30. �������� �� �������� ������ (������ 
//������� ����-���� 10 � 13) ������������� ����� 0. ����� 1 ��������� ��������� ������. 
using namespace std;
void main() {
	setlocale(LC_ALL, "Russian");
	cout << "�������" << endl;
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
	int p;// ����������� ������-�����
	int n = 4;//����������� ������� �����
	int k = 0;
	int m = 97;//���������� �������� � ��������
	char buff;
	bool fl = true;
	file1.open("12.txt", ios::in | ios::binary);
	file_cip.open("112.txt", ios::in | ios::trunc);
	if (!file1.is_open()) { cout << "���� �� ������" << endl; return; }
	else if (file1.peek() == EOF) { cout << "���� ����" << endl; return; }
	else { cout << "���� ������� ������" << endl; }


	while (true) {
		cout << "������� ����(��� ��������)" << endl;
		cin >> key_tr;
		if (!cheak_key(key_tr)) { cout << "������������ ����" << endl; }
		else { break; }
	}
	p = key_tr.size();//���������� �������� � ������
	for (int i = 0; i < p ; i++) { key_str[i] = key_tr[i]; }//�� ������� 30
	//for (int i = 0; i < p; i++) { cout << key_str[i] << " "; }cout << endl << endl;
	while (fl) {
		key_str[k] = K1[key_str[k]];
		n = key_str[k] % 4 + 2;// �� ������ ��� �� ������ ���� = 6
		k++;
		if (k == p) { k = 0; }
		//cout << n << " ";
		//cout << endl;
		for (int i = 0; i < n; i++) {//��������� ���� ��������
			buff = file1.get(); // ��������� ��������� ������
			//cout << (char)buff << " ";
			if (buff > 126 || (buff < 32 && buff != 13 && buff != 10 && buff != -1)) {//�������� �� ������������
				cout << "���� �������� ������������ �������" << endl;
				file1.close(); file_cip.close(); return;
			}
			if (buff == 13) { buff = file1.get(); buff = 30; }//���� � ����� ���� ������� ������
			if (file1.eof()) {// ���� �����  ����������
				fl = false; n = i;
			}
			//cout << (char)buff << " ";
			file_str[i] = buff - 30;// ���� ����� �� ����������
			
		}
		int** key_mtr = new int* [n];
		for (int i = 0; i < n; i++) {
			key_mtr[i] = new int[n];
			for (int j = 0; j < n; j++) {
				key_mtr[i][j] = 0;
			}
		}
		//cout << endl;
		for (int i = 0; i < n; i++) {//��������� ������� ���� ����������� n
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
			key_mtr = degenerate_matrix(key_mtr, n);//��������� �� �������������
		}
		for (int i = 0; i < n; i++) { // �������� i-������� ����������� �������
			int S = 0;
			for (int j = 0; j < n; j++) {
				S = S + key_mtr[i][j] * file_str[j];
			}
			S = (S % 97) + 30; // �������� ���� - ���  ������������ �������
			cout << (char)S << " "; // ������� ���� ������ �� �����
			file_cip.write((char*)&S, sizeof(char)); //���������� ���  �  ����
		}

		//for (int i = 0; i < n; i++) { cout << (char)V[i] << " "; }cout << endl<<endl;
		//for (int i = 0; i < n; i++) { cout << file_str[i] << " "; }cout << endl<<endl;
	}
	cout << endl;
	file1.close();
	file_cip.close();
	decode();
}
