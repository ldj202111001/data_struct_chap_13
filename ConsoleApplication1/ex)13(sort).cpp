/*
* 프로그램 내용: 정렬 함수들과 전체 선택 정렬 프로그램 (완료: 선택, 삽입, 버블, 셸, 병합, 퀵)
* 실습날짜: 2024 - 06- 05
* 학번: 202111001
* 이름: 이동재
*/
// 13.1 (시간 측정 까지)
// 11.3 11.4 11.5 11.6 11.7 11.8 11.9 11.10
// 연습문제: 1, 2, 3, 5, 6
#include <stdio.h>
#include <time.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define MAX_SIZE 100000
#define DATA_SIZE 100000

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

// 선택정렬
void selection_sort(int list[], int n)
{
    int i, j, least, tmp;
    for (i = 0; i < n - 1; i++) 
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least])
                least = j;
        SWAP(list[i], list[least], tmp);
        printStep(list, n, i + 1);
    }
}

// 삽입정렬
void insertion_sort(int list[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++) 
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--)
            list[j + 1] = list[j]; // 레코드의 오른쪽 이동list[j+1] = key;
        printStep(list, n, i); // 중간 과정 출력용 문장}
    }
}

// 버블정렬
void bubble_sort(int list[], int n)
{
    int i, j, bChanged, tmp;
    for (i = n - 1; i > 0; i--) 
    {
        bChanged = 0;
        for (j = 0; j < i; j++)
            if (list[j] > list[j + 1]) 
            {
                SWAP(list[j], list[j + 1], tmp);
                bChanged = 1;
            }
        if (!bChanged) break;
        printStep(list, n, n - i);
    }
}

// 셸정렬
static void sortGapInsertion(int list[], int first, int last, int gap)
{
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap) 
    {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j = j - gap)
            list[j + gap] = list[j];
        list[j + gap] = key;
    }
}
void shell_sort(int list[], int n)
{
    int i, gap, count = 0;
    for (gap = n / 2; gap > 0; gap = gap / 2) 
    {
        if ((gap % 2) == 0)
            gap++;
        for (i = 0; i < gap; i++)
            sortGapInsertion(list, i, n-1, gap);
        printStep(list, n, ++count);
    }
}

// 병합정렬
static void merge(int list[], int left, int mid, int right) 
{
    int i, j, k = left, l;
    static int sorted[MAX_SIZE];
    for (i = left, j = mid + 1; i <= mid && j <= right; )
        sorted[k++] = (list[i] <= list[j]) ? list[i++] : list[j++];
    if (i > mid)
        for (l = j; l <= right; l++, k++)
            sorted[k] = list[l];
    else
        for (l = i; l <= mid; l++, k++)
            sorted[k] = list[l];
    for (l = left; l <= right; l++)
        list[l] = sorted[l];
}
void merge_sort(int list[], int left, int right)
{
    if (left < right) 
    {
        int mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

// 퀵 정렬
int partition(int list[], int left, int right)
{
    int tmp;
    int low = left + 1;
    int high = right;
    int pivot = list[left];

    while (low < high)
    {
        for (; low <= right && list[low] < pivot; low++);
        for (; high >= left && list[high] > pivot; high--);
        if (low < high)
            SWAP(list[low], list[high], tmp);
    }
    SWAP(list[left], list[high], tmp);
    return high;
}

int partition(int list[], int left, int right)
{
    int pivot, tmp;
    int low, high;
    
    low = left;
    high = right + 1;
    pivot = list[left];
    do
    {
        do
            low++;
        while (low <= right && list[low] < pivot);
        do
            high--;
        while (high >= left && list[high] > pivot);
        if (low < high) SWAP(list[low], list[high], tmp);
    } while (low < high);

    SWAP(list[left], list[high], tmp);
    return high;
}

// 퀵 라이브러리도 하기 !!!!!!!!!!!!!!!!!!!!!!!!!

void quick_sort(int list[], int left, int right) // 매개변수: 전체배열, 분할한 배열의 맨 왼쪽, 분할한 배열의 맨 오른쪽
{
    int q; // 

    if (left < right) 
    {
        q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

// 메인함수
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

// 선택
// 삽입
// 버블정렬: 이동연산 과다 (이동연산은 비교연산보다 더 많은 시간 소요)
// 셸
// 병합
// 퀵
// 기수 정렬은 x
// 같은 데이터에서 7개의 정렬 알고리즘을 적용해서 비교
