#include <iostream> // бібліотека для вводу і виводу даних
#include <cstdlib>  // бібліотека для роботи генератора випадкових значень

using namespace std; // Підключення простору імен

// Розроблена функція Radix sort
void radixSort(int arr[], int n)
{
    // Знайти максимальний елемент в масиві
    int m = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > m)
        {
            m = arr[i];
        }
    }

    // Виконати сортування за розрядами
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        int output[n];
        int i, count[10] = {0};

        // Розрахувати кількість елементів залежно від розряду
        for (i = 0; i < n; i++)
        {
            count[(arr[i] / exp) % 10]++;
        }

        // Змінити count[i] так, щоб він містив позицію цифри в output[]
        for (i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        // Скласти вихідний масив
        for (i = n - 1; i >= 0; i--)
        {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // Копіювати вихідний масив у arr[]
        for (i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }
    }
}

int main()
{
    int matrix[2][12]; // Оголошення масиву matrix, який представляє матрицю розміром 2 на 12.
    // Заповнення матриці випадковими числами
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }
    // Виведення початкової матриці
    cout << "Початкова матриця:" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    // Сортування матриці за допомогою Radix sort
    for (int i = 0; i < 2; i++)
    {
        radixSort(matrix[i], 12);
    }
    // Виведення відсортованої матриці
    cout << "Відсортована матриця:" << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}