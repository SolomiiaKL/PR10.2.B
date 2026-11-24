#define NOMINMAX 
#include <windows.h>
#include "function.h"
#include <iostream>

using namespace std;

static int ReadMenuItem()
{
    int item;
    while (true)
    {
        cout << "Введіть значення: ";
        if (cin >> item)
        {
            return item;
        }
        cout << "Помилка! Введіть ціле число — номер пункту меню." << endl;
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
}

static int ReadPositiveCount()
{
    int n;
    while (true)
    {
        cout << "Введіть кількість студентів: ";
        if (cin >> n && n > 0)
        {
            return n;
        }
        cout << "Помилка! Кількість студентів має бути додатним цілим числом." << endl;
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
}

static int ReadSearchInt(const string& prompt, int minVal, int maxVal)
{
    int val;
    while (true)
    {
        cout << prompt;
        if (cin >> val && val >= minVal && val <= maxVal)
        {
            return val;
        }
        cout << "Помилка! Введіть число в межах [" << minVal << "; " << maxVal << "]." << endl;
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int N = ReadPositiveCount();
    Student* p = new Student[N];

    int menuItem;
    do
    {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних (Варіант 14)" << endl;
        cout << " [4] - бінарний пошук (прізвище, курс, оцінка з 3-го предмету)" << endl;
        cout << " [5] - індексне впорядкування та вивід даних (Варіант 14)" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;

        menuItem = ReadMenuItem();
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "Масив фізично впорядковано." << endl;
            break;
        case 4:
        {
            string prizv;
            int kurs = ReadSearchInt("Введіть курс (1-6): ", 1, 6);
            int thirdGrade = ReadSearchInt("Введіть оцінку з 3-го предмету (2-5): ", 2, 5);
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Введіть прізвище: ";
            getline(cin, prizv);

            int found = BinSearch(p, N, prizv, kurs, thirdGrade);
            if (found != -1)
                cout << "Студента знайдено на позиції " << found + 1 << "." << endl;
            else
                cout << "Шуканого студента не знайдено (переконайтеся, що масив фізично впорядковано)." << endl;
            break;
        }
        case 5:
        {
            int* idxArr = IndexSort(p, N);
            PrintIndexSorted(p, idxArr, N);
            delete[] idxArr;
            break;
        }
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! Слід ввести номер вибраного пункту меню." << endl;
            break;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}