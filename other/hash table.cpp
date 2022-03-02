#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

string names[30] = { "Андрей", "Иван", "Петр","Дмитрий", "Евгений", "Александр", "Марк", "Анатолий", "Максим", "Георгий", "Михаил", "Илья", "Владимир", "Савелий", "Ибрагим", "Богдан", "Клим", "Аркадий", "Николай", "Мстислав", "Игорь", "Леонид", "Ярослав", "Артем", "Яков", "Семен", "Константин", "Люцифер", "Роман", "Прокоп" };
string patronymic[30] = { "Андреевич", "Иванович", "Петрович","Дмитриевич", "Евгеньевич", "Александрович", "Маркович", "Анатольевич", "Максимович", "Георгиевич", "Михайлович", "Ильич", "Владимирович", "Савельевич", "Ибрагимович", "Богдаонвич", "Климентьевич", "Аркадьевич", "Николаевич", "Мстиславич", "Игоревич", "Леонидович", "Ярославович", "Артемьевич", "Яковлевич", "Семенович", "Константинович", "Люциферович", "Романович", "Прокопьевич" };
string surnames[30] = { "Смирнов", "Маслов", "Сафонов", "Кузнецов", "Горбачёв", "Костин", "Брагин", "Лаврентьев", "Евсеев", "Шаров", "Быков", "Зуев", "Рябов", "Петров", "Горшков", "Мухин", "Белов", "Киселёв", "Лихачёв", "Шашков", "Фомин", "Савин", "Мельников", "Ефимов", "Сергеев", "Гуляев", "Носов", "Мамонтов", "Колесников", "Блинов" };
string phones[30] = { "88422352177", "84959631102", "84953245489", "84953584156", "84959524920", "84953244105", "84991935577", "89585380329", "89033788272", "89050609891", "89697657977", "89061689884", "89061665057", "89033755608", "89061663935", "89585779300", "89062604822", "89014992059", "89093869743", "89697659060", "89014990856", "89062604591", "89033769156", "89062406784", "89064106293", "84996775624", "84996720056", "89064559359", "89052026204", "89062297167" };
string ID[30] = { "4759 969117", "4481 920688", "4340 356756", "4340 356756", "4793 464759", "4130 787768", "4266 463923", "4213 639031", "4848 499985", "4723 403863", "4551 404070", "4268 662048", "4027 668070", "4288 507733", "4640 341686", "4388 842676", "4951 448545", "4192 774735", "4061 412534", "4955 510694", "4299 865860", "4618 523942", "4864 617354", "4475 423620", "4926 157427", "4475 423620", "4539 871633", "4875 189971", "4044 794668", "4295 943154" };
string dates[30] = { "15.11.1969", "27.01.1996", "23.10.1972", "13.04.1993", "20.07.1985", "10.12.1986", "05.01.1986", "16.08.1983", "18.06.1988", "18.12.1995", "18.08.1965", "12.01.1980", "25.09.1989", "12.05.1972", "28.12.1971", "11.11.1996", "07.07.1986", "22.08.1976", "09.06.1987", "12.06.1968", "26.11.1995", "27.11.1990", "23.09.1981", "22.05.1976", "26.09.1987", "04.09.1983", "18.10.1972", "21.07.1994", "17.10.1961", "07.06.1968" };

struct Human
{
	Human()																																			// конструктор по умолчанию создает объект с пустыми полями
	{
		full_name = "NULL";
		ID_number = "NULL";
		phone_number = "NULL";
		date_of_birth = "NULL";
	}
	string full_name;
	string ID_number;
	string phone_number;
	string date_of_birth;
	friend ostream& operator<<(ostream& out, const Human& object);																												// дружественные методы, для решения задачи не понадобились
	friend istream& operator>>(istream& in, Human& object);
};

ostream& operator<<(ostream& out, const Human& object)
{
	out << "ФИО:           " << object.full_name << endl
		<< "Дата рождения: " << object.date_of_birth << endl
		<< "#Телефона:     " << object.phone_number << endl
		<< "#Паспорта:     " << object.ID_number << endl << endl;
	return out;
}																																				// это, соответственно, тоже
istream& operator>>(istream& in, Human& object)
{
	in >> object.full_name >> object.ID_number >> object.phone_number >> object.date_of_birth;
	return in;
}

int collisions_count = 0;					

struct hash_table
{
	Human* array;
	hash_table(int size)																																	// конструктор по умолчанию требует передачи размера 
	{																																			// массива-поля
		array = new Human[size];
	}
	~hash_table()
	{
		delete[] array;																																	// освобождение памяти в деструкторе структуры
	}
	void add(Human temp, const int size);																															// прототипы методов
	void pop(string date_to_delete, const int size);
	void find_index(string date_of_birth, const int size);
};

void show_info(const Human temp);																																// прототипы функций
void show_hash_table(hash_table* object, const int size);
Human create_random_human();
string get_random_name(); string get_random_ID(); string get_random_phone(); string get_random_date();
void print_array_humans(const Human* const array, const int size);
void fill_array_random_humans(Human* array, const int count);
int get_sum_of_date(string str); int get_random_number();
int hash_function(string str, const int size);



void hash_table::find_index(string date_of_birth, const int size)
{
	int hash = hash_function(date_of_birth, size);																														// получение хеша данных, запись о которых нужно найти
	int index = hash;																																	// копия значения хеша для итераций
	while (array[index].date_of_birth != date_of_birth && index < size)																											// пока поле "дата рождения" не соответсвует поисковому
	{																																			// запросу, а также не закончился массив
		index++;
	}
	if (index >= size)																																	// если ничего не найдено, а index выходит за предел
	{																																			// массива, перенос индекса в начало массива и 
		index = 0;																																	// аналогичные итерации до начального значения hash
		while (array[index].date_of_birth != date_of_birth && index < hash)
		{
			index++;
		}
		if (index >= hash)																																// если снова ничего не найдено, то в массиве просто нет 
		{																																		// объекта с такими данными
			cout << "Человека с датой рождения \"" << date_of_birth << "\" нет.\n\n";
		}
		else
		{																																		// иначе вывод индекса
			cout << "Человек с датой рождения \"" << date_of_birth << "\" содержится по индексу " << index << endl << endl;							
		}
	}
	else																																			// сработает, если нашелся объект с нужным полем
	{																																			// в диапазоне от hash до size массива
		cout << "Человек с датой рождения \"" << date_of_birth << "\" содержится по индексу " << index << endl << endl;
	}
}
void hash_table::add(Human temp, const int size)
{
	int index = hash_function(temp.date_of_birth, size);																													// аналогичная логика поиска нужных данных
	int hash = index;																																	// только другое условие на итерации
	if (array[index].full_name == "NULL")																															// и увеличение счетчика коллизий в каждый возникающий
	{																																			// случай, если ячейка свободная, то запись переданных
		array[index] = temp;																																// данных об объекте
		return;
	}
	else
	{
		while (index < size)
		{
			if (array[index].full_name == "NULL")
			{
				array[index] = temp;
				return;
			}
			index++;
			collisions_count++;
		}
		if (index >= size)
		{
			index = 0;
			collisions_count++;
			while (index < hash)
			{
				if (array[index].full_name == "NULL")
				{
					array[index] = temp;
					return;
				}
				index++;
				collisions_count++;
			}
		}
	}
}
void hash_table::pop(string date_to_delete, const int size)
{
	int index = hash_function(date_to_delete, size);																													// аналогичная логика поиска нужного поля
	if (array[index].date_of_birth == date_to_delete)																													// если нужный объект найден - перезапись 
	{																																			// этой ячейки пустым объектом через
		array[index] = Human();																																// применение конструктора по умолчанию
		return;
	}
	else
	{
		while (index < size)
		{
			if (array[index].date_of_birth == date_to_delete)
			{
				array[index] = Human();
				return;
			}
			index++;
		}
		if (index >= size)
		{
			index = 0;
			while (index < size)
			{
				if (array[index].date_of_birth == date_to_delete)
				{
					array[index] = Human();
					return;
				}
				index++;
			}
		}
	}
}
																																					
int main()
{
	srand(time(0));
	setlocale(0, "");
	int size;
	do
	{
		cout << "Введите количество элементов в массиве (не меньше 100): ";
		cin >> size;
	} while (size < 100);
	cout << endl;
	Human* array = new Human[size];
	hash_table table(size);
	fill_array_random_humans(array, size);
	for (int i = 0; i < size; i++)
	{
		table.add(array[i], size);
	}
	show_hash_table(&table, size);																																// передача по ссылке, так как функция принимает параметром
	table.find_index("23.10.1972", size);																															// указатель на объект типа hash_table	
	table.pop("23.10.1972", size);
	cout << endl << endl << "==================" << endl << endl;
	show_hash_table(&table, size);
	cout << endl << "Количество коллизий для " << size << " записей: " << collisions_count << endl << endl;
	delete[] array; 
	return 0;
}

Human create_random_human()																																	// создание локального объекта со случайными данными,
{																																				// возврат копии этого объекта
	Human temp;
	temp.full_name = get_random_name();
	temp.ID_number = get_random_ID();
	temp.phone_number = get_random_phone();
	temp.date_of_birth = get_random_date();
	return temp;
}
string get_random_name()																																	// получение случайных данных из массивов с именами, телефонами, 
{																																				// паспортами и т.д.
	return (surnames[get_random_number()] + " " + names[get_random_number()] + " " + patronymic[get_random_number()]);
}
string get_random_ID()
{
	return ID[get_random_number()];
}
string get_random_phone()
{
	return phones[get_random_number()];
}
string get_random_date()
{
	return dates[get_random_number()];
}
void show_info(const Human temp)																																// вывод информации о конкретном объекте
{
	cout << "ФИО:           "   << temp.full_name
		 << "\nДата рождения: " << temp.date_of_birth
		 << "\n#Телефона:     " << temp.phone_number
		 << "\n#Паспорта:     " << temp.ID_number << endl << endl;
}
void print_array_humans(const Human* const array, const int size)
{
	for (int i = 0; i < size; i++)
	{
		show_info(array[i]);																																// вывод массива, переданного в функцию
	}
}
void fill_array_random_humans(Human* array, const int count)
{
	for (int i = 0; i < count; i++)
	{
		array[i] = create_random_human();																														// заполнение массва рандомными объектами
	}
}
void show_hash_table(hash_table* table, const int size)
{
	for (int i = 0; i < size; i++)
	{
		show_info(table->array[i]);																															// вывод данных хеш-таблицы через обращение к данным поля-массива 
	}																																			// array структуры hash_table
}
int get_random_number()
{
	return rand() % 30;																																	// генерация случайного числа от 0 до 30
}
int get_sum_of_date(string str)
{
	return stoi(str.substr(0, 2)) + stoi(str.substr(3, 2)) + stoi(str.substr(6, 4));																									// дата формата "дд.мм.гггг" форматируется с помощью суммирования блоков,
}																																				// отеделенных точками. Строка приводится к int с помощью функции stoi()
int hash_function(string str, const int size)
{
	double a = ((sqrt(5) - 1) / 2) * get_sum_of_date(str);																													// хеш-функция умножает преобразованную дату на A ≈ 0.68
	double c = size * (a - static_cast<int>(a));																														// приведением типов отделяется дробная часть, которая умножается на размер
	return static_cast<int>(c);																																// таким образом hash никогда не получится больше размера массива
}

																																					
