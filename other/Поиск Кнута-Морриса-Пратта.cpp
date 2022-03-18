#include <iostream>
#include <string>
using namespace std;

int search(string str, string to_find);

int main()
{
	setlocale(0, "");
	string to_find;
	string str;
	do
	{
		cout << "������� ������, � ������� ����� ����� ���������: ";
		cin >> str;
	} while (str == "");
	cout << endl;
	do
	{
		cout << "������� ������, ������� ����� �����: ";
		cin >> to_find;
	} while (to_find == "");
	cout << "\n�����...\n\n";
	int index = search(str, to_find);
	cout << "������ ���������, ������� � ������� " << index << ". ������ ��� ���������: ";
	str.erase(index, to_find.length());
	cout << str << endl << endl;
	return 0;
}


int search(string str, string to_find)
{
	int str_length = str.length();
	int to_find_length = to_find.length();
	int* arr = new int[to_find_length];
	int i = 1, j = 0;
	arr[0] = 0; // � ������ ������� ������ 0
	while (i <= to_find_length) // �� ��� ���, ���� �� ���������� ����
	{
		if (to_find[i] == to_find[j]) // ���� ������� ���������
		{
			arr[i] = j + 1; // �� ���������� ����� ��������
			i++; // ����� ����������
			j++;
		}
		else if (j == 0) // ����� ���� ������� �� ����� � ��������� � ������
		{
			arr[i] = 0; // �� ����� �������� = 0
			i++; // � ����� ���������
		}
		else // ����� (������� �� ����� � ��������� ��� ������)
		{
			j = arr[j - 1]; // ����� ��������� �� ��������� ������ ����� ���������������� ���������� � �������� �������
		}
	}

	i = 0; // ������ ��� ����������� �� ������
	j = 0; // ������ ��� ����������� �� �����
	while (i <= str_length) // ���� �� ����������� ������
	{
		if (str[i] == to_find[j]) // ���� ������� ���������
		{
			i++; j++; // ����� ����������
			if (j == to_find_length) // � ���� ��������� ����� ��������� � ��� ������
			{
				return i - to_find_length; // �� ��������� ������� �� ������� i - to_find_length
			}
		}
		else if (j == 0) // ����� ���� ������ ������ ����� �� ��������� � �������� �� ������
		{
			i++; // �� ����� ��������� �� ������
			if (i == str_length) // � ���� ������ �����������
			{
				return -1; // �� ��������� ���
			}
		}
		else 
		{
			j = arr[j - 1]; // ����� ����� ��������� ����� �� �������
		}
	}
}
