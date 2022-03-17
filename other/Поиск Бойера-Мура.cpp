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
		cout << "Введите строку, в которой нужно найти подстроку: ";
		cin >> str;
	} while (str == "");
	cout << endl;
	do
	{
		cout << "Введите строку, которую нужно найти: ";
		cin >> to_find;
	} while (to_find == "");
	cout << "\nПоиск...\n\n";
	int index = search(to_find, str);
	cout << "Строка находится, начиная с индекса " << index << ". Теперь она удаляется: ";
	str.erase(index, to_find.length());
	cout << str << "\n\nИ добавляется в начало строки: ";
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
		arr[i] = to_find_length; // заполнение массива длиной ключа
	}
	for (int i = to_find_length - 2; i >= 0; i--) // с предпоследнего до первого
	{
		if (arr[(int)to_find[i]] == to_find_length) // если еще не поменялся вес элемента
		{
			arr[(int)to_find[i]] = to_find_length - i - 1; // то присвоение удаления от конца слова, начиная с 1 (предпоследний элемент)
		}
	}
	int index = to_find_length - 1; // индекс элемента строки, который совпадает с концом ключа
	while (index < str_length) // пока ключ физически может существовать
	{
		if (to_find[to_find_length - 1] != str[index]) // если последние элементы не равны 
		{
			index += arr[str[index]]; // то смещение на по таблице
		}
		else // иначе
		{
			for (int i = to_find_length - 1; i >= 0; i--) // с последнего до начала
			{
				if (to_find[i] != str[index - to_find_length + i + 1]) // если встречаем несовпадение
				{
					index += arr[str[index - to_find_length + i + 1]]; // то сдвиг по таблице
					break;
				}
				else if (i == 0) // иначе если строка кончилась
				{
					return index - to_find_length + 1; // есть совпадение, возвращение индекса первого элемента вхождения
				}
			}
		}
	}
	return -1; // если не найдено - возврат -1
}
