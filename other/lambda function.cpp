#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <functional>
#include <ctime>
#include <iterator>
#include <iomanip>
using namespace std;


class Pair
{
private:
	int x, y;
public:
	Pair(int, int);
	Pair() {x = rand() % 10 - 5; y = rand() % 10 - 5;};
	friend ostream& operator<<(ostream&, const Pair&);
	friend istream& operator>>(istream&, Pair&);
	Pair& operator=(Pair other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	int get_sum() {return x + y;}
	bool operator>(const Pair& other)
	{
		if ((x + y) > (other.x + other.y)) return 1;
		return 0;
	}
	bool operator<(const Pair& other)
	{
		return !(operator>(other));
	}
	bool operator>=(const Pair& other)
	{
		if (operator==(other) || operator>(other)) return 1;
		return 0;
	}
	bool operator<=(const Pair& other)
	{
		if (operator==(other) || operator<(other)) return 1;
		return 0;
	}
	bool operator==(const Pair& other)
	{
		if ((x + y) == (other.x + other.y)) return 1;
		return 0;
	}
	Pair& operator/(const Pair& other)
	{
		if (other.x == 0 && other.y == 0)
		{
		}
		else if (other.x == 0 && other.y != 0)
		{
			y /= other.y;
		}
		else if (other.x != 0 && other.y == 0)
		{
			x /= other.x;
		}
		else
		{
			x /= other.x;
			y /= other.y;
		}
		return *this;
	}
};

Pair::Pair(int x, int y)
{
	this->x = x;
	this->y = y;
}
ostream& operator<<(ostream& out, const Pair& pair)
{
	out << "(" << pair.x << ";" << pair.y << ")";
	return out;
}
istream& operator>>(istream& in, Pair& pair)
{
	in >> pair.x >> pair.y;
	return in;
}
ostream& operator<<(ostream& out, vector<Pair>& vect)
{
	for_each(vect.begin(), vect.end(), [&](Pair& pair) {out << pair; });
	return out;
}
vector<Pair> fill_container()
{
	int count = 0;
	do { cout << "Введите количество элементов: "; cin >> count; } while (count <= 0);
	vector<Pair> vector;
	for (int i = 0; i < count; i++)
	{
		Pair temp;
		vector.push_back(temp);
	}
	return vector;
}

void task_5()
{
	cout << "\n\n\nВыполнение задания 5:\n";
	std::vector<Pair> vector = fill_container();
	cout << vector;
	Pair max = vector[0];
	int vector_size = vector.size();
	int index_of_max = 0;
	int current_index = 0;
	for (auto i : vector)
	{
		if (i.get_sum() > max.get_sum())
		{
			max = i;
			index_of_max = current_index;
		}
		current_index++;
	}
	cout << "\nМаксимальная пара: " << max;
	for_each(vector.begin(), vector.end(), [&max, &vector](Pair& pair)->void 
		{
			pair / max;
		});
	cout << "\nПосле деления каждой пары на максимальную: " << vector;
}


void task_4()
{
	cout << "\n\n\nВыполнение задания 4:\n";
	std::vector<Pair> vector = fill_container();
	for (auto i : vector)
	{
		cout << i << "->" << i.get_sum() << " ";
	}
	int size = vector.size();
	int sum = 0;
	for_each(vector.begin(), vector.end(), [&sum](Pair& pair)->void {sum += pair.get_sum(); });
	double average = sum / size;
	if (average != 0)
	{
		if ((abs(average) - abs(static_cast<int>(average)) > 0.4))
		{
			if (average > 0)
			{
				average = static_cast<int>(average + 1);
			}
			else
			{
				average = static_cast<int>(average - 1);
			}
		}
		else
		{
			if (average > 0)
			{
				average = static_cast<int>(average);
			}
			else
			{
				average = static_cast<int>(average);
			}
		}
	}
	cout << "\nСреднее арифметическое последовательности: " << average;
	std::vector<Pair> new_vector;
	for_each(vector.begin(), vector.end(), [&average, &vector, &new_vector](Pair& pair)->void
		{
			if (average <= pair.get_sum())
			{
				new_vector.push_back(pair);
			}
		});
	cout << "\nПосле удаления: ";
	for (auto i : new_vector)
	{
		cout << i << "->" << i.get_sum() << " ";
	}
}


void task_3()
{
	cout << "Выполнение задания 3:\n";
	std::vector<Pair> vector = fill_container();
	cout << vector;
	Pair min = vector[0];
	int vector_size = vector.size();
	int index_of_min = 0;
	int current_index = 0;
	for (auto i : vector)
	{
		if (i.get_sum() < min.get_sum())
		{
			min = i;
			index_of_min = current_index;
		}
		current_index++;
	}
	cout << "\nПервой вхождение минимальной пары: " << min;
	cout << "\nЕе индекс: " << index_of_min;
	std::vector<Pair>::iterator it = vector.begin();
	for (int i = 0; i < index_of_min; i++)
	{
		it++;
	}
	vector.erase(it);
	cout << "\nПроизводится удаление пары: " << vector;
	cout << "\nВведите индекс, на который нужно переставить минимальную пару (кроме " << index_of_min
		<< ", а также не меньше 0 и не больше " << vector_size - 1 << "): ";
	int index;
	cin >> index;
	if (index == vector_size - 1)
	{
		vector.push_back(min);
	}
	else
	{
		if (index < 0 || index >= vector_size || index == index_of_min)
		{
			do
			{
				cout << "Введите индекс, на который нужно переставить минимальную пару (кроме " << index_of_min
					<< ", а также не меньше 0 и не больше " << vector_size - 1 << "): ";
				cin >> index;
			} while (index < 0 || index >= vector_size || index == index_of_min);
		}
		it = vector.begin();
		current_index = 0;
		while (current_index != index)
		{
			it++;
		}
		vector.insert(it, min);
	}
	vector_size++;
	cout << "Результат задания после добавления на новое место: " << vector;
}



int main()
{
	setlocale(0, "");
	srand(time(0));
	task_3();
	task_4();
	task_5();
	cout << "\n\n\n\n\n\n";
	return 0;
}
