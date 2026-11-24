#include "function.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

static string SpecToStr(Spec spec)
{
    switch (spec)
    {
    case KN:  return "Комп'ютерні науки";
    case INF: return "Інформатика";
    case ME:  return "Мат. та економіка";
    case FI:  return "Фіз. та інформатика";
    case TN:  return "Трудове навчання";
    default:  return "";
    }
}

int GetThirdGrade(const Student& s)
{
    switch (s.spec)
    {
    case KN:  return s.third.programuvannya;
    case INF: return s.third.chyselniMetody;
    default:  return s.third.pedagogika;
    }
}

static int ReadIntInRange(const string& prompt, int minVal, int maxVal)
{
    int val;
    while (true)
    {
        cout << prompt;
        if (cin >> val && val >= minVal && val <= maxVal)
        {
            return val;
        }
        cout << "Помилка! Введіть ціле число в межах [" << minVal << "; " << maxVal << "]." << endl;
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
}

static string ReadNonEmptyLine(const string& prompt)
{
    string line;
    while (true)
    {
        cout << prompt;
        getline(cin, line);
        if (!line.empty())
        {
            return line;
        }
        cout << "Помилка! Рядок не може бути порожнім." << endl;
    }
}

void Create(Student* p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        p[i].prizv = ReadNonEmptyLine("  Прізвище: ");
        p[i].kurs = ReadIntInRange("  Курс (1-6): ", 1, 6);

        int specCode = ReadIntInRange(
            "  Спеціальність (0 - КН, 1 - ІНФ, 2 - МЕ, 3 - ФІ, 4 - ТН): ", 0, 4);
        p[i].spec = static_cast<Spec>(specCode);

        p[i].fizyka = ReadIntInRange("  Оцінка з фізики (2-5): ", 2, 5);
        p[i].matematyka = ReadIntInRange("  Оцінка з математики (2-5): ", 2, 5);

        switch (p[i].spec)
        {
        case KN:
            p[i].third.programuvannya = ReadIntInRange("  Оцінка з програмування (2-5): ", 2, 5);
            break;
        case INF:
            p[i].third.chyselniMetody = ReadIntInRange("  Оцінка з чисельних методів (2-5): ", 2, 5);
            break;
        case ME:
        case FI:
        case TN:
            p[i].third.pedagogika = ReadIntInRange("  Оцінка з педагогіки (2-5): ", 2, 5);
            break;
        }
        cout << endl;
    }
}

static int Utf8Len(const string& text)
{
    int len = 0;
    for (unsigned char c : text)
    {
        if ((c & 0xC0) != 0x80)
            len++;
    }
    return len;
}

static string PadCol(const string& text, int width, bool rightAlign)
{
    int len = Utf8Len(text);
    if (len >= width)
        return text;

    string sp(width - len, ' ');
    return rightAlign ? (sp + text) : (text + sp);
}

static void PrintTableRows(const Student* p, const int* indexMap, const int N)
{
    const int w1 = 2;
    const int w2 = 16;
    const int w3 = 6;
    const int w4 = 22;
    const int w5 = 8;
    const int w6 = 10;
    const int w7 = 13;
    const int w8 = 11;
    const int w9 = 11;

    string header =
        "| " + PadCol("№", w1, false) +
        " | " + PadCol("Прізвище", w2, false) +
        " | " + PadCol("Курс", w3, false) +
        " | " + PadCol("Спеціальність", w4, false) +
        " | " + PadCol("Фізика", w5, false) +
        " | " + PadCol("Математика", w6, false) +
        " | " + PadCol("Програмування", w7, false) +
        " | " + PadCol("Чис. методи", w8, false) +
        " | " + PadCol("Педагогіка", w9, false) +
        " |";

    int lineLen = Utf8Len(header);
    string line(lineLen, '-');
    string title = "Успішність студентів";
    int titleLen = Utf8Len(title);

    int leftPad = (lineLen - 2 - titleLen) / 2;
    if (leftPad < 0) leftPad = 0;
    int rightPad = (lineLen - 2 - titleLen) - leftPad;
    if (rightPad < 0) rightPad = 0;

    cout << endl << line << endl;
    cout << "|" << string(leftPad, ' ') << title << string(rightPad, ' ') << "|" << endl;
    cout << line << endl;
    cout << header << endl;
    cout << line << endl;

    for (int i = 0; i < N; i++)
    {
        int idx = (indexMap != nullptr) ? indexMap[i] : i;
        const Student& st = p[idx];

        string sProg = (st.spec == KN) ? to_string(st.third.programuvannya) : "-";
        string sChys = (st.spec == INF) ? to_string(st.third.chyselniMetody) : "-";
        string sPed = (st.spec != KN && st.spec != INF) ? to_string(st.third.pedagogika) : "-";

        cout << "| " << PadCol(to_string(i + 1), w1, true)
            << " | " << PadCol(st.prizv, w2, false)
            << " | " << PadCol(to_string(st.kurs), w3, true)
            << " | " << PadCol(SpecToStr(st.spec), w4, false)
            << " | " << PadCol(to_string(st.fizyka), w5, true)
            << " | " << PadCol(to_string(st.matematyka), w6, true)
            << " | " << PadCol(sProg, w7, true)
            << " | " << PadCol(sChys, w8, true)
            << " | " << PadCol(sPed, w9, true)
            << " |" << endl;
    }

    cout << line << endl << endl;
}

void Print(const Student* p, const int N)
{
    PrintTableRows(p, nullptr, N);
}

// Варіант 14:
// 1) оцінка з 3-го предмету (зростання)
// 2) курс (зростання)
// 3) прізвище (спадання — у зворотному до алфавітного порядку)
static bool ShouldSwapPhysical(const Student& a, const Student& b)
{
    int gA = GetThirdGrade(a);
    int gB = GetThirdGrade(b);

    if (gA != gB)
        return gA > gB;
    if (a.kurs != b.kurs)
        return a.kurs > b.kurs;
    return a.prizv < b.prizv;
}

void Sort(Student* p, const int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (ShouldSwapPhysical(p[j], p[j + 1]))
            {
                Student tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }
}

// Варіант 14 (індексне впорядкування):
// 1) оцінка з 3-го предмету, 2) курс, 3) прізвище
static bool ShouldShiftIndex(const Student& leftSt, const Student& valSt)
{
    int gL = GetThirdGrade(leftSt);
    int gV = GetThirdGrade(valSt);

    if (gL != gV)
        return gL > gV;
    if (leftSt.kurs != valSt.kurs)
        return leftSt.kurs > valSt.kurs;
    return leftSt.prizv < valSt.prizv;
}

int* IndexSort(const Student* p, const int N)
{
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    for (int i = 1; i < N; i++)
    {
        int value = I[i];
        int j = i - 1;
        while (j >= 0 && ShouldShiftIndex(p[I[j]], p[value]))
        {
            I[j + 1] = I[j];
            j--;
        }
        I[j + 1] = value;
    }

    return I;
}

void PrintIndexSorted(const Student* p, const int* I, const int N)
{
    PrintTableRows(p, I, N);
}

// Бінарний пошук у масиві, впорядкованому за ключами (оцінка з 3-го предмету, курс, прізвище за спаданням)
int BinSearch(const Student* p, const int N, const string& prizv, const int kurs, const int thirdGrade)
{
    int L = 0;
    int R = N - 1;

    while (L <= R)
    {
        int m = L + (R - L) / 2;
        int gM = GetThirdGrade(p[m]);

        if (gM == thirdGrade && p[m].kurs == kurs && p[m].prizv == prizv)
            return m;

        bool isBeforeTarget =
            (gM < thirdGrade) ||
            (gM == thirdGrade && p[m].kurs < kurs) ||
            (gM == thirdGrade && p[m].kurs == kurs && p[m].prizv > prizv);

        if (isBeforeTarget)
            L = m + 1;
        else
            R = m - 1;
    }

    return -1;
}