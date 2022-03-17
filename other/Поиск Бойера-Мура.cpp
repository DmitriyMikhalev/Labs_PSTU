#include <iostream>
#include <string>
using namespace std;


int search(string to_find, string str);

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
	int index = search(to_find, str);
	cout << "������ ���������, ������� � ������� " << index << ". ������ ��� ���������: ";
	str.erase(index, to_find.length());
	cout << str << "\n\n� ����������� � ������ ������: ";
	str.insert(0, to_find);
	cout << str << endl << endl;
	return 0;
}

int search(string to_find, string str)
{
	int to_find_length = to_find.length();
	int str_length = str.length();
	if (str_length < to_find_length) return -1;
	int arr[256];
	for (int i = 0; i < 256; i++)
	{
		arr[i] = to_find_length; // ���������� ������� ������ �����
	}
	for (int i = to_find_length - 2; i >= 0; i--) // � �������������� �� �������
	{
		if (arr[(int)to_find[i]] == to_find_length) // ���� ��� �� ��������� ��� ��������
		{
			arr[(int)to_find[i]] = to_find_length - i - 1; // �� ���������� �������� �� ����� �����, ������� � 1 (������������� �������)
		}
	}
	int index = to_find_length - 1; // ������ �������� ������, ������� ��������� � ������ �����
	while (index < str_length) // ���� ���� ��������� ����� ������������
	{
		if (to_find[to_find_length - 1] != str[index]) // ���� ��������� �������� �� ����� 
		{
			index += arr[str[index]]; // �� �������� �� �� �������
		}
		else // �����
		{
			for (int i = to_find_length - 1; i >= 0; i--) // � ���������� �� ������
			{
				if (to_find[i] != str[index - to_find_length + i + 1]) // ���� ��������� ������������
				{
					index += arr[str[index - to_find_length + i + 1]]; // �� ����� �� �������
					break;
				}
				else if (i == 0) // ����� ���� ������ ���������
				{
					return index - to_find_length + 1; // ���� ����������, ����������� ������� ������� �������� ���������
				}
			}
		}
	}
	return -1; // ���� �� ������� - ������� -1
}
