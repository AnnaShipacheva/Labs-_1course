#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define ASIZE 100


void f22();
void f27();
void f32();
void f36();
void f45();
void f50();
int main() {
	f22();
	f27();
	f32();
	f36();
	f45();
	f50();
	return 0;
}

void f22() {
	int i, a, v, s, n;											// \(-_-)/
	int* A = NULL;												// \(-_-)/
	int Acapacity = 0;											// \(-_-)/

	/* находим все простые числа меньше v
	* а - число, которое проверяем на простоту
	* i - счетчик индексов в массиве
	* n - перебор чисел меньших a
	* s - флаг, что число не простое
	*/
	printf("Prime numbers\nEnter v to find prime numbers less then v: ");					// \(-_-)/
	scanf("%d", &v);											// \(-_-)/
	for (i = 0, a = 2; a < v; a++) {
		for (s = 0, n = 2; n < a; n++) /*проверяем есть ли у а делители, кроме 1 и а*/
			if (a % n == 0) { //число имеет делитель - не простое
				s = 1;
				break;
			}
		if (s == 0)
		{
			if (i >= Acapacity) {									// \(-_-)/
				if ((A = (int*)realloc(A, (Acapacity + ASIZE) * sizeof(int))) == NULL) {	// \(-_-)/
					printf("Some problems");						// \(-_-)/
					return;									// \(-_-)/
				}										// \(-_-)/
				Acapacity += ASIZE;								// \(-_-)/
			}											// \(-_-)/
			A[i++] = a; /*если а простое число, записываем его в массив*/
		}
	}
	if (i < Acapacity)											// \(-_-)/
		A[i] = 0;
	printf("Prime numbers < %d:\n", v);									// \(-_-)/
	for (i = 0; i < Acapacity && A[i] != 0; i++)								// \(-_-)/
		printf("%d ", A[i]);										// \(-_-)/
	free(A);												// \(-_-)/
	printf("\n\n");												// \(-_-)/
	return;													// \(-_-)/
}

void f27() {
	int val, m, i;												// \(-_-)/
	int* A = NULL;												// \(-_-)/
	int n; //размер A;											// \(-_-)/
	printf("Multipliers\nEnter val: ");									// \(-_-)/
	scanf("%d", &val);											// \(-_-)/
	printf("Enter n to find n-1 prime multipliers in val: ");						// \(-_-)/
	scanf("%d", &n);											// \(-_-)/
	if ((A = (int*)malloc(n * sizeof(int))) == NULL) {							// \(-_-)/
		printf("Some problems\n");									// \(-_-)/
		return;												// \(-_-)/
	}
	/*находим n-1 или меньше простых множителей в val
	* val- число, которое раскладывается на простые множители
	* n - размер массива, в который записыввется n-1 или меньше простых множителей val
	*/
	printf("Multipliers of %d: ", val);
	for (i = 0; i < n - 1 && val != 1; i++) {
		for (m = 2; val % m != 0; m++); /*находим m - наименьший делитель val*/
		val /= m;
		A[i] = m; /*записываем val в массив*/
	}
	A[i] = 0;
	for (i = 0; A[i] != 0; i++) {										// \(-_-)/
		printf("%d ", A[i]);										// \(-_-)/
	}													// \(-_-)/
	free(A);												// \(-_-)/
	printf("\n\n");												// \(-_-)/
	return;													// \(-_-)/
}

void f32() {
	int s, i, n, k, j, b;											// \(-_-)/
	int* c;
	/*находим число, которое чаще всех встречается в массиве
	* Из двух чисел с одинаковой частотой выбирается с более ранним вхождением 
	* n - размер массива
	* b - хранит последний индекс самого частого элемента
	* s - хранит количество вхождений самого частого элемента
	*/
	printf("Frequency\nEnter n - array size: ");								// \(-_-)/
	scanf("%d", &n);											// \(-_-)/
	if (n <= 0)												// \(-_-)/
		return;												// \(-_-)/
	if ((c = (int*)malloc(n * sizeof(int))) == NULL) {							// \(-_-)/
		printf("Some problems\n");									// \(-_-)/
		return;												// \(-_-)/
	}													// \(-_-)/
	printf("Enter %d elements: ", n);									// \(-_-)/
	for (i = 0; i < n; i++) {										// \(-_-)/
		scanf("%d", &c[i]);										// \(-_-)/
	}
	for (s = 0, i = 0; i < n; i++) {
		for (k = 0, j = 0; j < n; j++) /*находим количество вхождений в массив числа равного i-ому элементу*/
			if (c[i] == c[j]) 
				k++;
		if (k > s) //сохраняем наибольшее количество и индекс этого элемента
			s = k, b = i;
	}
	if (n>0)												// \(-_-)/
		printf("Most frequent element is %d, it meets %d times\n\n", c[b], s);				// \(-_-)/
	free(c);												// \(-_-)/
	return;													// \(-_-)/
}

int findMedian(int* c, int n) {											// \(-_-)/
	int k1, k2, i, j;											// \(-_-)/
	for (i = 0; i < n; i++) {
		for (j = k1 = k2 = 0; j < n; j++)
			if (c[i] != c[j])
			{
				if (c[i] < c[j])
					k1++; //кол-во эл. больше текущего (i-ого)
				else
					k2++; //кол-во эл. меньше текущего (i-ого)
			}
		if (k1 == k2) return i;
	}
	return -1;
}
void f36() {
	int i, n;												// \(-_-)/
	int* c;													// \(-_-)/
	int res;												// \(-_-)/
	/*находит индекс медианного элемента массива
	* Если такого нет возвращает -1
	* с - массив
	* n - размер массива
	* k1 - счетчик больших элементов
	* k2 - счетчик меньших элементов
	*/
	printf("Median\nEnter n - array size: ");								// \(-_-)/
	scanf("%d", &n);											// \(-_-)/
	if (n <= 0) return;											// \(-_-)/
	if ((c = (int*)malloc(n * sizeof(int))) == NULL) {							// \(-_-)/
		printf("Some problems\n");									// \(-_-)/
		return;												// \(-_-)/
	}													// \(-_-)/
	printf("Enter %d elements: ", n);									// \(-_-)/
	for (i = 0; i < n; i++) {										// \(-_-)/
		scanf("%d", &c[i]);										// \(-_-)/
	}													// \(-_-)/
	if ((res = findMedian(c, n)) == -1) {									// \(-_-)/
		printf("Cann't find median\n");									// \(-_-)/
	}													// \(-_-)/
	else {													// \(-_-)/
		printf("Median is %d, with index %d\n\n", c[res], res);						// \(-_-)/
	}													// \(-_-)/
	return;													// \(-_-)/
}

void f45() {
	int j, k, i, max, n;											// \(-_-)/
	int* A=NULL;												// \(-_-)/
	int* B = NULL;												// \(-_-)/
	printf("Sort\nEnter n - array size: ");									// \(-_-)/
	scanf("%d", &n);											// \(-_-)/
	if ((A = (int*)malloc(n * sizeof(int))) == NULL) {							// \(-_-)/
		printf("Some problems\n");									// \(-_-)/
		return;												// \(-_-)/
	}													// \(-_-)/
	if ((B = (int*)malloc(n * sizeof(int))) == NULL) {							// \(-_-)/
		printf("Some problems\n");									// \(-_-)/
		return;												// \(-_-)/
	}													// \(-_-)/
	printf("Enter %d elements: ", n);									// \(-_-)/
	for (i = 0; i < n; i++) {										// \(-_-)/
		scanf("%d", &A[i]);										// \(-_-)/
	}													// \(-_-)/
		
	for (j = 0, max = A[0]; j < n; j++) //находим максимальный элемент в А
		if (A[j] > max) max = A[j];
	for (j = 0; j < n; j++) { //сортировка по возрастанию
		for (k = 0, i = 1; i < n; i++) //находим меньший из индексов наименьшего элемента в А
			if (A[i] < A[k]) k = i;
		B[j] = A[k]; //записываем в В найденый наименьший элемент
		A[k] = max + 1; //перенесенный в В делаем больше максимального. Он больше не используется в переносе
	}
	printf("Sorted array:\n");										// \(-_-)/
	for (i = 0; i < n; i++) {										// \(-_-)/
		printf("%d ", B[i]);										// \(-_-)/
	}													// \(-_-)/
	printf("\n\n");												// \(-_-)/
	return;													// \(-_-)/
}

void f50() {
	int i, s, k;												// \(-_-)/
	int A[10] = {0};											// \(-_-)/
	printf("Pairs\nEnter 10 elements: ");									// \(-_-)/
	for (i = 0; i < 10; i++) {										// \(-_-)/
		scanf("%d", &A[i]);										// \(-_-)/
	}													// \(-_-)/
	/*посчитать количество пар вида "меньше 0 - больше 0"*/
	for (i = 0, s = 0, k = 0; i < 10; i++)						
		if (A[i] < 0)											
			k = 1;												
		else {													
			if (k == 1) s++;
			k = 0;
		}
	printf("Number of pairs \"less 0 - more 0\": %d\n\n", s);						// \(-_-)/
}