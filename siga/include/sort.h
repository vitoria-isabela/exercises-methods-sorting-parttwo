#ifndef SORT_H
#define SORT_H

#include <chrono>
#include <iostream>
#include <vector>
using namespace std;

#include "metrics.h"


// Use essa função para movimentar dados 
template <typename T>
void troca(T& a, T& b)
{
    T tmp = a;
    a     = b;
    b     = tmp;
}

template <typename T>
void bubble_sort_internal(T* array, int size, bool (*compare)(T&, T&), PerformanceMetrics *p)  
{
    // bubble sort
    for (int i = size-2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            p->n_comp++;   // incrementa o número de comparações
            if (compare(array[j+1], array[j]))
            {
                p->n_mov+=3; // troca realiza tres movimentacoes de dados
                troca<T>(array[j], array[j + 1]);
            }
        }
    }
}

template <typename T>
void insertion_sort_internal(T* array, int size,  bool (*compare)(T&, T&), PerformanceMetrics *p)
{
    // Implementação do Insert Sort
    // TODO: Insira as métricas de performance
    for (int i = 1; i < size; i++)
    {
        T key = array[i];
        int j = i - 1;

        p->n_comp++; 
        while (j >= 0 && compare(key, array[j]))
        {
            p->n_mov++;
            array[j + 1] = array[j]; //insertion
            j = j - 1;
        }
        array[j + 1] = key;
    }

}

template <typename T>
void selection_sort_internal(T* array, int size, bool (*compare)(T&, T&), PerformanceMetrics *p)
{
    // TODO: Insira as métricas de performance
    
    for (int i = 0; i < size; i++)
    {
        //minimo assume sempre a posição atual
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            p->n_comp++;
            p->n_mov++;
            if (compare(array[j], array[min]))// compara sempre o mínimo com o seu próximo
                min = j;
        }
        troca(array[i], array[min]);// função troca() é chamada inutilmente quando o minimo não sofre atualizações no if.
        p->n_mov+=3;
    }
}

template <typename T>
void merge (T* array, int start, int end, bool (*compare)(T&, T&), PerformanceMetrics *p )
{
    int mid = (start + end) / 2;
	
	int StarMid = mid - start + 1; 
    int MidP1End = end - mid;


    // Criar arrays temporários
    T *arrayEsq = new T[StarMid];
    T *arrayDir = new T[MidP1End];

    // Copiar dados do vetor para os temporários
    for (int i = 0; i < StarMid; i++){
         arrayEsq[i] = array[start + i];
         p->n_mov++;
    }
       
    for (int j = 0; j < MidP1End; j++){
        arrayDir[j] = array[mid + 1 + j];
        p->n_mov++;
    }

    int indexOfArrayEsq = 0, // Índice inicial do primeiro subarray
    indexOfArrayDir = 0; // Índice inicial do segundo subarray
    int indexOfMergedArray = start; // Índice inicial do array mesclado

    // Mesclar arrays temporarios de volta ao principal esquerda->direita
    while (indexOfArrayEsq < StarMid && indexOfArrayDir < MidP1End) {
        p->n_comp++;
        if (compare(arrayEsq[indexOfArrayEsq],arrayDir[indexOfArrayDir])) 
        {
            p->n_mov++;
            array[indexOfMergedArray] = arrayEsq[indexOfArrayEsq];
            indexOfArrayEsq++;
        }
        else {
            p->n_mov++;
            array[indexOfMergedArray] = arrayDir[indexOfArrayDir];
            indexOfArrayDir++;
        }
        indexOfMergedArray++;
    }  

    // Copia os elementos restantes de
    // arrayEsq[], se houver algum
    while (indexOfArrayEsq < StarMid) 
    {
        p->n_mov++;
        array[indexOfMergedArray] = arrayEsq[indexOfArrayEsq];
        indexOfArrayEsq++;
        indexOfMergedArray++;
    }

	// Copia os elementos restantes de
    // arrayDir[], se houver algum
    while (indexOfArrayDir < MidP1End) 
    {
        p->n_mov++;
        array[indexOfMergedArray] = arrayDir[indexOfArrayDir];
        indexOfArrayDir++;
        indexOfMergedArray++;
    }  

}

// função de template para realizar merge sort em array, arr
template<typename T>
void mergesort_internal(T* array, int start, int end, bool (*compare)(T&, T&), PerformanceMetrics *p)
{
    if (start >= end)
        return;

        int mid = start + (end - start) / 2;
        mergesort_internal(array, start, mid, compare, p); // merge classifica os elementos no intervalo [start, mid]
        mergesort_internal(array, mid + 1, end, compare, p); // merge classifica os elementos no intervalo [mid+1, end]
        merge(array, start, end, compare, p);   // mescla os 2 componentes acima
}

template <typename T>
void quicksort_internal(T* array, int low, int high, bool (*compare)(T&, T&), PerformanceMetrics *p)
{
    // TODO: Implementação do quicksort

    if (low < high)
    {
        int pi = partition(array, low, high, compare, p);

        quicksort_internal(array, low, pi - 1, compare, p);
        quicksort_internal(array, pi + 1, high, compare, p);
    }

}

template <typename T>
int partition(T* arr, int start, int end, bool (*compare)(T&, T&), PerformanceMetrics *p)
{
    T pivot = arr[end];
    int i = (start - 1);
    for (int j = start; j <= end - 1; j++)
    {
        if (compare(arr[j], pivot)) // arr[j] < pivot
        {
            i++;
            T t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            p->n_mov+=1;
            p->n_comp+=1;

        }else {
            p->n_comp+=1;
        }
    }
    T t = arr[i + 1];
    arr[i + 1] = arr[end];
    arr[end] = t;
    p->n_mov+=3;
    return (i + 1);
}

template <typename T>
void bubble_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    bubble_sort_internal<T>(array, size, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Bubble Sort:" << endl; 
    PerformanceMetricsPrint(&p);
}

template <typename T>
void insertion_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    insertion_sort_internal(array, size, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Insertion Sort:" << endl; 
    PerformanceMetricsPrint(&p);
}

template <typename T>
void selection_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    selection_sort_internal(array, size, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Selection Sort:" << endl; 
    PerformanceMetricsPrint(&p);
}

template <typename T>
void merge_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    mergesort_internal(array, 0, size-1, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Merge Sort:" << endl; 
    PerformanceMetricsPrint(&p);
}

template <typename T>
void quick_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p);
    auto t1 = Clock::now();
    quicksort_internal(array, 0, size-1, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    cout << "Quick Sort:" << endl; 
    PerformanceMetricsPrint(&p);
}

#endif /* SORT_H */