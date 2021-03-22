#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;
typedef struct
{
	int code;
	int month;
	int quantity;
	int codeStr;
	string monthStr, quantityStr;
}Details;



vector <Details> arraydFull;



void WriteFile(vector <Details> array)										//запись в файл
{
	ofstream fout;
	fout.open("example.txt", ios_base::app);								//открытие файла для записи в конец
	for (int i = 0; i < array.size(); i++)
	{
		fout << "Code " << array[i].code << " Month " << array[i].month << " Quantity " << array[i].quantity << endl;
	}
	fout.close();
}


vector <Details> Sort(vector <Details> array)
{
	int j = 0;
	Details tmp;
	for (int i = 0; i < array.size() - 1; i++) {
		j = i;
		for (int k = i; k < array.size(); k++) {
			if (array[j].code > array[k].code) {
				j = k;
			}
		}
		tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}

	cout << " SORT  " << endl;
	for (int i = 0; i < array.size(); i++)
		if (array[i].code != 0)
		{
			cout << "Code: " << array[i].code << " Month " << array[i].month << " Quantity: " << array[i].quantity << endl;
		}
	return array;
}


vector <Details> Qsort(vector <Details> array, int left, int right)
{
	Details mid, count;

	int l = left, r = right;
	mid = array[(l + r) / 2];						//вычисление опорного элемента
	do
	{
		while (array[l].code < mid.code) l++;
		while (array[r].code > mid.code) r--;
		if (l <= r)									//перестановка элементов
		{
			count = array[l];
			array[l] = array[r];
			array[r] = count;
			l++;
			r--;
		}
	} while (l <= r);
	if (left < r) array = Qsort(array, left, r);
	if (l < right) array = Qsort(array, l, right);


	return array;
}

int Cut(string code, char pos1, char pos2)   //функция вырезает из строки нужные числа
{
	int intcode;
	string codeBuff;			//буфер для обмена
	pos1 = code.find(':');
	pos2 = code.find('/');

	codeBuff = code.substr(pos1 + 1, pos2 - pos1 - 1);			//вырезать подстроку в бафф с символа : до /

	intcode = stoi(codeBuff);
	return intcode;
}

string CutToString(string code, char pos1, char pos2)
{
	string codeBuff;
	int pos3, pos4, codeBuff2;

	pos3 = code.find(pos1);
	pos4 = code.find(pos2);

	codeBuff = code.substr(pos3, pos4 - pos3);


	return codeBuff;
}


vector <Details> OutFile(string month_now)
{

	string line, month, codeBuff, quantity, code;
	Details detail;
	int intcode, pos1, pos2;

	vector <Details> arrayd;			//вектор для сортировок

	vector <int> arr;

	int i = 0;    //счётчик для циклов
	int k = 0;

	string month_now_here;    //строка с нынешним месяцем для сравнения данных с файлом

	month_now_here = " Month of production:" + month_now; //месяц в этой функции

	ifstream fout;
	fout.open("last_month.txt", ios_base::app);

	while (!fout.eof())
	{
		//считывание полной строки

		getline(fout, code, ';');
		getline(fout, month, ',');
		getline(fout, quantity, '.');

		arrayd.push_back({});
		arraydFull.push_back({});
		if (code != "")			//чтобы вайл не считывал 1 лишнюю строчку
		{
			arraydFull[k].codeStr = Cut(code, ' ', ';');
			arraydFull[k].monthStr = Cut(month, ':', ' ');
			arraydFull[k].quantityStr = Cut(quantity, ',', '.');
		}
		if (month == month_now_here && code != "")   //код не равен пустоте из-за того, что EOF работает по дебильному и лишний раз выводит последнюю строчку
		{

			arrayd[i].code = Cut(code, ' ', ';');
			arrayd[i].month = Cut(month, ';', ',');
			arrayd[i].quantity = Cut(quantity, ',', '.');
		
			arr.push_back(intcode);			//пуш_бэк добавляет элемент в конец вектора
			i++;
		}
		k++;
	}
	cout << " UNSORTED VECTOR " << endl;
	for (int i = 0; i < arr.size(); i++)
	{
		if (arrayd[i].code != 0) 
		{
			cout << "Code: " << arrayd[i].code << " Month " << arrayd[i].month << " Quantity: " << arrayd[i].quantity << endl;
		}
	}

	return arrayd;
}

void OutQsort(vector <Details> array)
{
	cout << " QSORT " << endl;
	for (int i = 0; i < array.size(); i++)
		if (array[i].code != 0)
		{
			cout << "Code: " << array[i].code << " Month " << array[i].month << " Quantity: " << array[i].quantity << endl;
		}

}

void LineSearch(vector <Details> array)
{
	string key_str;
		int key, codeBuff;
	cout << "\nEnter key-search ";
		cin >> key;
	for (int i = 0; i < array.size(); i++)
	{
	//	codeBuff = CutToString(array[i].codeStr, ' ', ';');
		if (arraydFull[i].codeStr == key)
		{
			cout << "Code = " << arraydFull[i].codeStr << " " << arraydFull[i].monthStr << " " << arraydFull[i].quantityStr << endl;
		}
		}
}

int main()
{
	setlocale(LC_ALL, "rus");
	string month1;
	cout << "Which mounth now? ";
	cin >> month1;
	vector <Details> arrayd;

	arrayd = OutFile(month1);

	Sort(arrayd);

	arrayd = Qsort(arrayd, 0, arrayd.size() - 1);

	OutQsort(arrayd);

	WriteFile(arrayd);

	LineSearch(arraydFull);

	return 0;
}