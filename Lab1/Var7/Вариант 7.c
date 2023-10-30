#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAXNUM 50 //любое число >2

void findPrimeNumbers(); //решето Эратосфена, найти простые числа до MAXNUM
void countDegrees(int* deg, int num); //посчитать степени множителей, которые входят в НОК
int checkMuls(int* deg, int num); //проверить, делит ли новое число уже имеющийся НОК
int findLcm(int a, int b);//найти НОК двух чисел

int primeNumbers[MAXNUM];
int sizeArrPrime = 0;
int main() {
	findPrimeNumbers(); //найти простые числа до MAXNUM

	int i;
	int numbers[2][MAXNUM] = { 0 }; //хранятся флаги, что данное число делит искомое и "добавочные" множители
	for (i = 0; i < MAXNUM / 2; i++) { //проставить флаг, что первая половина чисел делит искомое
		numbers[0][i] = 1;
		numbers[1][i] = 1;
	}

	int degrees[MAXNUM] = { 0 }; //хранятся степени множителей для НОК
	degrees[1 - 1] = 1;
	for (i = 2; i <= MAXNUM / 2; i++) {
		//посчитать какие множители и в какой степени есть в первой половине чисел
		countDegrees(degrees, i);
	}

	for (i = MAXNUM / 2; i < MAXNUM; i++) {		//какой множитель нужно добавить к уже имеющемуся "набору" 
		int check = checkMuls(degrees, i + 1);	//множителей, чтобы на это число делилось искомое
		if (check == 1) {//это число уже делит искомое
			numbers[0][i] = numbers[1][i] = 1;
		}
		else { //чтобы это число делило искомое, нужно добавить множитель check
			numbers[0][i] = 0;
			numbers[1][i] = check;
		}
	}

	int flag = 0;
	int pair[2] = { 0 }; //первый элемент-стартовый элемент пары; второй элемент - НОК "добавочных" множителей пары
	for (i = MAXNUM / 2; i < MAXNUM; i++) {
		if (numbers[0][i] == 0) { //ищем два числа подряд, не делители искомого
			if (flag == 0)
				flag = 1;
			else { //нашли пару
				int Lcm = findLcm(numbers[1][i], numbers[1][i - 1]);
				if (pair[0] == 0 || Lcm > pair[1]) { //сравниваем новую пару с предыдущей
					pair[0] = i-1;					//если она была
					pair[1] = Lcm;
				}
			}
		}
		else
			flag = 0;
	}
	if (pair[0] == 0) {
		printf("No pair found");
		return 0;
	}
	//пометить, что эту пару не используем
	numbers[0][pair[0]] = -1;
	numbers[1][pair[0]] = 1;
	numbers[0][pair[0] + 1] = -1;
	numbers[1][pair[0] + 1] = 1;

	//дополнить информацию по степеням множителей в НОК (искомом числе)
	for (i = MAXNUM / 2; i < MAXNUM; i++) {
		if (numbers[0][i] >= 0) {
			countDegrees(degrees, i + 1);
		}
	}

	//подсчитать НОК
	double res = 1.0;
	printf("%d statements\n", MAXNUM);
	printf("Result: 1 ");
	for (i = 1; i < MAXNUM; i++) {
		for (int j = 0; j < degrees[i]; j++) {
			res *= (i + 1) * 1.0;
		}
		printf("* %d^%d ", i + 1, degrees[i]);
	}
	printf("\n= %.0lf", res);
}

void findPrimeNumbers() { //найти простые числа меньше или равные MAXNUM, решето Эратосфена
	int arr[MAXNUM] = { 0 };
	int i;
	for (i = 1; i < MAXNUM; i++) {
		arr[i] = 1;
	}
	for (i = 1; i < MAXNUM / 2; i++) {
		if (arr[i] == 1) {
			for (int j = i + (i + 1); j < MAXNUM; j += i + 1) {
				arr[j] = 0;
			}
		}
	}
	for (i = 1; i < MAXNUM; i++) {
		if (arr[i] == 1) {
			primeNumbers[sizeArrPrime] = i + 1;
			sizeArrPrime++;
		}
	}
}

void factorize(int* muls, int* degs, int* size, int num) { //разложение числа на простые множители
	int i = 0, j = 1;
	int count = 0;
	int mul = 0;
	*size = 0;
	while (i < sizeArrPrime) {
		if (num % primeNumbers[i] == 0) {
			mul = primeNumbers[i];
			count++;
			num = num / mul;
		}
		else {
			if (mul != 0) {
				muls[*size] = mul;
				degs[*size] = count;
				*size = *size + 1;
				mul = 0;
				count = 0;
			}
			i++;
		}
	}

}
void countDegrees(int* deg, int num) { //дополнить таблицу по уже имеющимся множителям для НОК
	int muls[MAXNUM] = { 0 };
	int degs[MAXNUM] = { 0 };
	int size = 0;
	factorize(muls, degs, &size, num);
	for (int i = 0; i < size; i++) {
		if (degs[i] > deg[muls[i] - 1]) {
			deg[muls[i] - 1] = degs[i];
		}
	}
	return;
}

int checkMuls(int* deg, int num) { //проверить, что все множители данного числа есть в НОК (возвращает 1)
	int muls[MAXNUM] = { 0 };		//иначе возвращает множитель. которого не хватает
	int degs[MAXNUM] = { 0 };
	int size = 0;
	int res = 1;
	factorize(muls, degs, &size, num);
	for (int i = 0; i < size; i++) {
		if (deg[muls[i] - 1] < degs[i]) {//если такого множителя не было в первой половине чисел
			for (int j = 0; j < degs[i] - deg[muls[i] - 1]; j++) {
				res *= muls[i];
			}
		}
	}
	return res;
}

int findLcm(int a, int b) {
	int res = a * b;
	while (a % b != 0 && b % a != 0) {
		if (a > b) {
			a = a % b;
		}
		else {
			b = b % a;
		}
	}
	if (a < b)
		res = res / a;
	else
		res = res / b;
	return res;
}