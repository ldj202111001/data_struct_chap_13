﻿/*
* 프로그램 내용: 선택 정렬 함수와 전체 선택 정렬 프로그램
* 실습날짜: 2024 - 06- 05
* 학번: 202111001
* 이름: 이동재
*/
// 13.1 (시간 측정 까지)
// 11.3 11.4 11.5 11.6 11.7 11.8 11.9 11.10
#include <stdio.h>
#include <time.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void printArray(int arr[], int n, const char* str)
{
    int i;
    printf("%s = ", str);
    for (i = 0; i < n; i++) printf("%3d", arr[i]);
    printf("/n");
}

void printStep(int arr[], int n, int val)
{
    int i;
    printf(" Step %2d = ", val);
    for (i = 0; i < n; i++) printf("%3d", arr[i]);
    printf("/n");
}

void selection_sort(int list[], int n)
{
    int i, j, least, tmp;
    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least])
                least = j;
        SWAP(list[i], list[least], tmp);
        printStep(list, n, i + 1);
    }
}

void main()
{
    int list[9] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
    printArray(list, 9, "Original "); // 정렬 전 배열 출력

    clock_t start = clock(); // 정렬 시작 시간 저장
    selection_sort( list, 9 ); // 선택 정렬 실행
    clock_t end = clock(); // 정렬이 끝난 시간 저장

    printArray( list, 9, "Selection" ); // 정렬 후 배열 출력
    printf("\nTime: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}