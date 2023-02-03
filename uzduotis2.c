#include<stdio.h>
#include<stdbool.h>

bool InputValidationNonNegative(int *N);
bool InputValidationRegular(int *number);
bool Sorted(int array[], int sizeOfTheArray);
bool Increasing(int* index, int N, int vector[]);
void Extremities(int index, int N, int vector[], bool extremity[], bool increasing);
void DistanceBetweenExtremities(bool extremity[], int N, int* leftmostExtremity, int* rightmostExtremity, int* distance);

int main()
{
    int N;

    printf("Iveskite sveika skaiciu N: ");
    while (!InputValidationNonNegative(&N));

    int vector[N];

    printf("Iveskite N sveikuju skaiciu:\n");
    for (int i = 0; i < N; ++i) {
        printf("%d%s", i + 1, " -tasis narys: ");
        while (!InputValidationRegular(&vector[i]));
    }

    if (Sorted(vector, N)) {
        printf("Vektorius neturi jokiu ekstremumu\n");
        return 0;
    }

    int index = 1;
    bool increasing;
    bool extremity[N];
    for (int i = 0; i < N; ++i) {
        extremity[i] = 0;
    }

    increasing = Increasing(&index, N, vector);

    Extremities(index, N, vector, extremity, increasing);

    int leftmostExtremity = 0, rightmostExtremity = N - 1;
    int distance;

    DistanceBetweenExtremities(extremity, N, &leftmostExtremity, &rightmostExtremity, &distance);

    if (leftmostExtremity == rightmostExtremity) {
        printf("%s%d\n", "Vektorius turi tik viena ekstremuma indekse: ", leftmostExtremity + 1);
        printf("Kadangi yra tik vienas ekstremumas, tai atstumas tarp ju yra 0");
    }
    else {
        printf("%s%d%s%d\n", "Vektoriaus tolimiausiu ekstremumu indeksai: ", leftmostExtremity + 1, " ", rightmostExtremity + 1);
        printf("%s%d", "Atstumas tarp tolimiausiu ekstremumu: ", distance);
    }
}

bool InputValidationNonNegative(int *N)
{
    int temp;
    if (scanf("%d", &temp) == 1 && getchar() == '\n') {
        *N = temp;
        if (*N > 0) {
            return true;
        }
        else {
            printf("Netinkama N ivestis, veskite sveikaji, teigiama skaiciu: ");
            return false;
        }
    }
    else {
        printf("Netinkama N ivestis, veskite sveikaji, teigiama skaiciu: ");
        while (getchar() != '\n');
        return false;
    }
}

bool InputValidationRegular(int *number)
{
    int temp;
    if (scanf("%d", &temp) == 1 && getchar() == '\n') {
        *number = temp;
        return true;
    }
    else {
        printf("Netinkama ivestis, veskite sveikaji skaiciu: ");
        while (getchar() != '\n');
        return false;
    }
}

bool Sorted(int array[], int sizeOfTheArray)
{
    bool increasingOrEqual = true;
    bool decreasing = true;

    for (int i = 0; i < sizeOfTheArray - 1; ++i) {
        if (array[i] > array[i + 1]) {
            increasingOrEqual = false;
        }
    }
    for (int i = 0; i < sizeOfTheArray - 1; ++i) {
        if (array[i] <= array[i + 1]) {
            decreasing = false;
        }
    }

    if (increasingOrEqual || decreasing) {
        return true;
    }
    else {
        return false;
    }
}

bool Increasing(int* index, int N, int vector[])
{
    while (*index < N) {
        if (vector[*index - 1] < vector[*index]) {
            *index = *index + 1;
            return true;
        }
        else if (vector[*index - 1] > vector[*index]) {
            *index = *index + 1;
            return false;
        }
        else {
            *index = *index + 1;
        }
    }
}

void Extremities(int index, int N, int vector[], bool extremity[], bool increasing)
{
    for (; index < N; ++index) {
        if (vector[index] > vector[index - 1] && !increasing) {
            extremity[index] = 1;
            increasing = true;
        }
        else if (vector[index] < vector[index - 1] && increasing) {
            extremity[index] = 1;
            increasing = false;
        }
    }
}

void DistanceBetweenExtremities(bool extremity[], int N, int* leftmostExtremity, int* rightmostExtremity, int* distance)
{
    for (int i = 0; i < N; ++i) {
        if (extremity[i]) {
            *leftmostExtremity = i;
            break;
        }
    }
    for (int i = N - 1; i != -1; --i) {
        if (extremity[i]) {
            *rightmostExtremity = i;
            break;
        }
    }
    *distance = *rightmostExtremity - *leftmostExtremity - 1;
}