#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	setlocale(0, "");
	srand(time(NULL));
	int random_number = rand()%100;
	int user_number;
	bool flag = false;
	cout << "Было загадано целое число от 0 до 100, у вас есть 6 попыток его угадать. Удачи!\n";
	for (int i = 1; i < 7; i++)
	{
		cout << "\n" << i << "-ая попытка ввода числа: ";
		cin >> user_number;
		if (random_number > user_number)
		{
			if (i < 6)
			{
				cout << "\nВведенное число меньше загаданного, попробуйте еще раз!\n";
			}
		}
		else if (user_number > random_number) 
		{
			if (i < 6)
			{
				cout << "\nВведенное число больше загаданного, попробуйте еще раз!\n";
			}
		}
		else
		{
			cout << "\nУра! Вы угадали число за отведенное число попыток!\n\n";
			flag = true;
			i = 7;
		}
	}
	if (flag == false)
	{
		cout << "\nУпс, вы не угадали число за отведенное число попыток :(\n" << "Ответ: " << random_number;
	}
	return 0;
}
