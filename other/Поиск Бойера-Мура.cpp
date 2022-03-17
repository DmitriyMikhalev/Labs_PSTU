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
		cout << "Ââåäèòå ñòðîêó, â êîòîðîé íóæíî íàéòè ïîäñòðîêó: ";
		cin >> str;
	} while (str == "");
	cout << endl;
	do
	{
		cout << "Ââåäèòå ñòðîêó, êîòîðóþ íóæíî íàéòè: ";
		cin >> to_find;
	} while (to_find == "");
	cout << "\nÏîèñê...\n\n";
	int index = search(to_find, str);
	cout << "Ñòðîêà íàõîäèòñÿ, íà÷èíàÿ ñ èíäåêñà " << index << ". Òåïåðü îíà óäàëÿåòñÿ: ";
	str.erase(index, to_find.length());
	cout << str << "\n\nÈ äîáàâëÿåòñÿ â íà÷àëî ñòðîêè: ";
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
		arr[i] = to_find_length; // çàïîëíåíèå ìàññèâà äëèíîé êëþ÷à
	}
	for (int i = to_find_length - 2; i >= 0; i--) // ñ ïðåäïîñëåäíåãî äî ïåðâîãî
	{
		if (arr[(int)to_find[i]] == to_find_length) // åñëè åùå íå ïîìåíÿëñÿ âåñ ýëåìåíòà
		{
			arr[(int)to_find[i]] = to_find_length - i - 1; // òî ïðèñâîåíèå óäàëåíèÿ îò êîíöà ñëîâà, íà÷èíàÿ ñ 1 (ïðåäïîñëåäíèé ýëåìåíò)
		}
	}
	int index = to_find_length - 1; // èíäåêñ ýëåìåíòà ñòðîêè, êîòîðûé ñîâïàäàåò ñ êîíöîì êëþ÷à
	while (index < str_length) // ïîêà êëþ÷ ôèçè÷åñêè ìîæåò ñóùåñòâîâàòü
	{
		if (to_find[to_find_length - 1] != str[index]) // åñëè ïîñëåäíèå ýëåìåíòû íå ðàâíû 
		{
			index += arr[str[index]]; // òî ñìåùåíèå íà ïî òàáëèöå
		}
		else // èíà÷å
		{
			for (int i = to_find_length - 1; i >= 0; i--) // ñ ïîñëåäíåãî äî íà÷àëà
			{
				if (to_find[i] != str[index - to_find_length + i + 1]) // åñëè âñòðå÷àåì íåñîâïàäåíèå
				{
					index += arr[str[index - to_find_length + i + 1]]; // òî ñäâèã ïî òàáëèöå
					break;
				}
				else if (i == 0) // èíà÷å åñëè ñòðîêà êîí÷èëàñü
				{
					return index - to_find_length + 1; // åñòü ñîâïàäåíèå, âîçâðàùåíèå èíäåêñà ïåðâîãî ýëåìåíòà âõîæäåíèÿ
				}
			}
		}
	}
	return -1; // åñëè íå íàéäåíî - âîçâðàò -1
}
