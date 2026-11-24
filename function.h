#pragma once
#include <string>

enum Spec { KN, INF, ME, FI, TN };

union ThirdGrade
{
    int programuvannya;
    int chyselniMetody;
    int pedagogika;
};

struct Student
{
    std::string prizv;
    int kurs;
    Spec spec;
    int fizyka;
    int matematyka;
    ThirdGrade third;
};

int GetThirdGrade(const Student& s);
void Create(Student* p, const int N);
void Print(const Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(const Student* p, const int N);
void PrintIndexSorted(const Student* p, const int* I, const int N);
int BinSearch(const Student* p, const int N, const std::string& prizv, const int kurs, const int thirdGrade);