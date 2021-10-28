#include <iostream>
using namespace std;
int main()
{
    setlocale(0, "");
    int input_number, last, middle, start;
    cout << "Введите целое трехзначное число: \n\n";
    cin >> input_number;
    while (input_number<100 || input_number>999)
    {
        cout << "\nВы вводите некорректное число, оно должно быть целым и трехзначным! Повторите ввод: \n\n";
        cin >> input_number;
    }
    last = input_number % 10;
    input_number /= 10;
    middle = input_number % 10;
    start = input_number / 10;
    while ((start == middle) || (middle == last) || (start == last))
    {
        cout << "\nЧисло имеет повторения, такого быть не должно! Повторите ввод: \n\n";
        cin >> input_number;
        last = input_number % 10;
        input_number /= 10;
        middle = input_number % 10;
        start = input_number / 10;
    } 
    cout << "\nВсе комбинации из цифр введенного числа: \n\n" <<
        start << middle << last << "\n" <<
        start << last << middle << "\n" <<
        last << middle << start << "\n" <<
        last << start << middle << "\n" <<
        middle << start << last << "\n" <<
        middle << last << start << "\n";
    int max_number, middle_number, min_number;
    if ((start > middle) && (start > last))
    {
        if (middle > last)  
        {
            max_number = start; 
            middle_number = middle; // 321
            min_number = last; 
        }
        else 
        {
            max_number = start; 
            middle_number = last; // 312
            min_number = middle; 
        }
    }
    else if ((middle > last) && (middle > start))
    {
        if (start > last)
        {
            max_number = middle;
            middle_number = start; // 231
            min_number = last;
        }
        else
        {
            max_number = middle;
            middle_number = last; // 132
            min_number = start;
        }
    }
    else
    {
        if (middle > start)
        {
            max_number = last;
            middle_number = middle; // 123
            min_number = start;
        }
        else
        {
            max_number = last;
            middle_number = start; // 213
            min_number = middle;
        }
    }
    cout << "\nМаксимальное число:  " << max_number << middle_number << min_number << "\n\n";
    return 0;
}