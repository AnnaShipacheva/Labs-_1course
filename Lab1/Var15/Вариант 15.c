#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int checkNums(int * firstArr, int * secondArr, int * thirdArr);
//проверить что первое*второе=третье

int main() {
	int firstNum[3]={-1,-1,-1}; //первое число
	int secondNum[2]={-1,-1}; //второе число
	int thirdNum[5]={-1,-1,-1,-1,-1}; //третье число
	int digits[10] = { 0 };
	int a, b, c, d, e, f, g, h, i;
	secondNum[1] = 5; //вторая цифра второго числа
	thirdNum[4] = 0;
	digits[0] = 1;
	digits[5] = 1;

	//создание новых цифр
	for (a = 0; a < 10; a++) { //заполнение первой цифры первого числа
	if (digits[a] != 1) {
		firstNum[0] = a;
		digits [a] = 1;
		for (b = 0; b < 10; b++) { //заполнение второй цифры первого числа
		if (digits[b] != 1) {
			firstNum[1] = b;
			digits[b] = 1;
			for (c = 2; c < 10; c += 2) { //заполнение третьей цифры первого числа
			if (digits[c] != 1) {
				firstNum[2] = c;
				digits[c] = 1;
				for (d = 0; d < 10; d++) { //заполнение первой цифры второго числа
				if (digits[d] != 1) {
					secondNum[0] = d;
					digits[d] = 1;
					for (e = 0; e < 10; e++) {//заполнение первой цифры третьего числа
					if (digits[e] != 1) {
						thirdNum[0] = e;
						digits[e] = 1;
						for (f = 0; f < 10; f++) {//заполнение второй цифры третьего числа
						if (digits[f] != 1) {
							thirdNum[1] = f;
							digits[f] = 1;
							for (g = 0; g < 10; g++) { //заполнение третьей цифры третьего цисла
							if (digits[g] != 1) {
								thirdNum[2] = g;
								digits[g] = 1;
								for (h = 0; h < 10; h++) {
								if (digits[h] != 1) {
									thirdNum[3] = h;
									digits[h] = 1;
									//проверка чисел
									if (checkNums(firstNum, secondNum, thirdNum)) {
										printf("Solution: %d%d%d * %d%d = %d%d%d%d%d", firstNum[0], firstNum[1], firstNum[2],
											secondNum[0], secondNum[1],
											thirdNum[0], thirdNum[1], thirdNum[2], thirdNum[3], thirdNum[4]);
										return 0;
									}
									digits[h] = 0;
								}
								}
								digits[g] = 0;
							}
							}
							digits[f] = 0;
						}
						}
						digits[e] = 0;
					}
					}
					digits[d] = 0;
				}
				}
				digits[c] = 0;
			}
			}
			digits[b] = 0;
		}
		}
		digits[a] = 0;
	}
	}
	
	printf("No solution found");
	return 0;
}

int fromDigits(int* num, int count) {//перевод из массива в число
	int res = 0;
	for (int i = 0; i < count; i++) {
		res = res * 10;
		res = res + num[i];
	}
	return res;
}

int checkNums(int* firstArr, int* secondArr, int* thirdArr) {
	int first = fromDigits(firstArr, 3);
	int second = fromDigits(secondArr, 2);
	int third = fromDigits(thirdArr, 5);
	int res = first * second;
	return res == third;
}