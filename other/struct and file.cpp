#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <Windows.h>
#include <cstdio> 
using namespace std;

struct Car
{
	string brand;
	string VIN;
	string plate;
	string year_of_release;
	friend ostream& operator<<(ostream& out, const Car& object);
	friend istream& operator>>(istream& in, Car& object);
};
Car create_new_object();
Car set_info(string brand = "NULL", string VIN = "NULL", string plate = "NULL", string year_of_release = "NULL")
{
	Car temp;
	temp.brand = brand;
	temp.VIN = VIN;
	temp.plate = plate;
	temp.year_of_release = year_of_release;
	return temp;
}
Car create_new_object()
{
	SetConsoleCP(1251);
	Car temp;
	cout << "������� �������� ��������: "; cin >> temp.brand;
	cout << "������� VIN-�����: "; cin >> temp.VIN;
	cout << "������� �������� ����: "; cin >> temp.plate;
	cout << "������� ���� �������: "; cin >> temp.year_of_release; cout << endl;
	SetConsoleCP(866);
	return temp;
}

// ���������� ���������� ����� � ������
ostream& operator<<(ostream& out, const Car& object)
{
	out << object.brand << endl
		<< object.VIN << endl
		<< object.plate << endl
		<< object.year_of_release << endl;
	return out;
}
istream& operator>>(istream& in, Car& object)
{
	in >> object.brand >> object.VIN >> object.plate >> object.year_of_release;
	return in;
}

void print_info(const Car car);
void print_info(const Car* array, const int size);
void append(Car*& array, int& array_size, Car other);
void create_objects(Car*& array, const int size);
void delete_first_three_objects(Car*& array, int& size);
void add_after_plate(Car*& array, int& size, const string value);

int main()
{
	setlocale(0, "");
	int command, count_of_objects = 0;
	string plate, path = "file.txt";
	fstream file;
	Car* new_arr = new Car[count_of_objects];
	file.open(path, fstream::in | fstream::out | fstream::app);
	Car* array = new Car[count_of_objects];

	cout << "���� \"" << path << "\" ������ ��� ������ � ������.\n\n";
	cout << "1. �������� � ����\n2. ������� �� ����� (������ ������)\n" <<
		"3. �������� ������ ����� ���������� � ��������� ������� (������� ������ � ����)\n4. ������� ������ 3 ������� (�������� ����� ����� ������)\n\n";
	cout << "�������� ��������, ����� ��� �����: ";
	cin >> command;
	cout << endl;
	switch (command)
	{
	case 1:
		if (!file.is_open())
		{
			cout << "������ �������� �����.\n\n";
		}
		else
		{
			do
			{
				cout << "������� ���������� �������� ��� ������ � ����: ";
				cin >> count_of_objects;
			} while (count_of_objects < 1);
			cout << endl;
			create_objects(array, count_of_objects); // �������� �������� � ���������� count_of_objects
			for (int i = 0; i < count_of_objects; i++)
			{
				file << array[i] << endl; // ������ ���� �������� � ����
			}
			cout << "���������� ������:\n\n";
			print_info(array, count_of_objects); // ����� � ������� ���������� ������ ��� ��������
			file.close();
		}
		break;
	case 2:
		while (!file.eof())
		{
			Car temp;
			Car temp2;

			file >> temp;
			if (file.eof())
			{
				break;
			}

			temp2.brand = temp.brand;
			temp2.VIN = temp.VIN;
			temp2.plate = temp.plate;
			temp2.year_of_release = temp.year_of_release;

			append(array, count_of_objects, temp2);
		}
		file.close();
		break;
	case 3:
		while (!file.eof())
		{
			Car temp;
			Car temp2;

			file >> temp;
			if (file.eof())
			{
				break;
			}

			temp2.brand = temp.brand;
			temp2.VIN = temp.VIN;
			temp2.plate = temp.plate;
			temp2.year_of_release = temp.year_of_release;

			append(array, count_of_objects, temp2);
		}
		file.close();
		file.open(path, fstream::in | fstream::out | std::ios::trunc);
		cout << "������� ����� ����������, ����� �������� ����� �������� ����� ������: "; cin >> plate;
		cout << endl << endl;
		add_after_plate(array, count_of_objects, plate);
		for (int i = 0; i < count_of_objects; i++)
		{
			file << array[i] << endl;
		}
		file.close();
		break;

	case 4:
		cout << "�������� ������ 3-� �������� � ������ ����� ������ � ����.\n\n";
		while (!file.eof())
		{
			Car temp;
			Car temp2;

			file >> temp;
			if (file.eof())
			{
				break;
			}

			temp2.brand = temp.brand;
			temp2.VIN = temp.VIN;
			temp2.plate = temp.plate;
			temp2.year_of_release = temp.year_of_release;

			append(array, count_of_objects, temp2);
		}
		file.close();
		file.open(path, fstream::in | fstream::out | std::ios::trunc);
		delete_first_three_objects(array, count_of_objects);
		for (int i = 0; i < count_of_objects; i++)
		{
			file << array[i] << endl;
		}
		file.close();
		break;

	default:
		cout << "������� ��������, �� � �� ���� ����� �������. ����� :)\n\n";
		break;
	}
	print_info(array, count_of_objects);
	delete[] array;
	return 0;
}

void print_info(const Car car)
{
	cout << "Brand: " << car.brand << endl
		<< "VIN: " << car.VIN << endl
		<< "Plate: " << car.plate << endl
		<< "Year of release: " << car.year_of_release << endl << endl;
}
void print_info(const Car* array, const int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Brand: " << array[i].brand << endl
			<< "VIN: " << array[i].VIN << endl
			<< "Plate: " << array[i].plate << endl
			<< "Year of release: " << array[i].year_of_release << endl << endl;
	}
}
void append(Car*& array, int& array_size, Car other) // ���������� ������ ������� � ����� �������
{
	Car* temp = new Car[array_size + 1];
	for (int i = 0; i < array_size; i++)
	{
		temp[i] = array[i];
	}
	temp[array_size].brand = other.brand;
	temp[array_size].VIN = other.VIN;
	temp[array_size].plate = other.plate;
	temp[array_size].year_of_release = other.year_of_release;
	delete[] array;
	array = temp;
	array_size++;
}
void create_objects(Car*& array, const int size) // �������� size ��������
{
	Car* new_arr = new Car[size];
	for (int i = 0; i < size; i++)
	{
		new_arr[i] = create_new_object();
	}
	delete[] array;
	array = new_arr;
}
void delete_first_three_objects(Car*& array, int& size) // �������� ������ 3-� ��������� � �������
{
	Car* new_arr = new Car[size - 3];
	for (int i = 0; i < size - 3; i++)
	{
		new_arr[i] = array[i + 3];
	}
	size -= 3;
	delete[] array;
	array = new_arr;
}
void add_after_plate(Car*& array, int& size, const string value)
{
	Car* new_arr = new Car[size + 1];
	int i = 0, index = 0;
	bool is_found = false; // ������ �� ������ ����?
	while (i < size && !is_found)
	{
		if (array[i].plate == value)
		{
			index = i; // ���� �� - ������������ ������
			is_found = true; // � ����� �� ����� 
		}
		i++;
	}

	if (!is_found)
	{
		cout << "\n���������� � ����� ������� ���.\n\n";
	}
	else
	{
		for (int i = 0; i < index + 1; i++)
		{
			new_arr[i] = array[i];
		}
		size++;
		new_arr[index + 1] = create_new_object();
		for (int i = index + 2; i < size; i++)
		{
			new_arr[i] = array[i - 1]; // ����������� ������ � ����������� ������ ������� �� ���������� ������� 
		}
		delete[] array;
		array = new_arr;
	}
}
