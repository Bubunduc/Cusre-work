#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#pragma warning(disable:4996)

void results(int size, struct sportsmen sport[]);
void winners(int size, struct sportsmen sport[]);
float kicked(int size, struct sportsmen sport[]);
float average(int size, struct sportsmen sport[]);
float local_maximum(struct  sportsmen sportsmen);
void sort(int size, struct sportsmen sport[]);
struct sportsmen {
	char full_name[60];
	float results[6];
	float maximum;
};

int main()
{

	struct sportsmen* sportsmens;

	setlocale(LC_ALL, "rus");

	puts("Толкание ядра");

	char  extension[6] = { ".txt\0" };
	char file_name[40];
	puts("Введите название файла в пределах 30 символов (без указания расширения файла)");

	gets(file_name);//Чтобы имена спортсменов корректно считались необходимо сменить кодировку с UTF-8 на ANCII
	strcat(file_name, extension);
	printf("Имя файла: %s\n", file_name);
	int what_do = 0; int size = 0;

	FILE* table;
	table = fopen(file_name, "rt");
	if (table == NULL) {
		puts("Не удалось открыть файл");
		fclose(table);
		exit(0);
	}
	while (!feof(table)) {
		if (fgetc(table) == '\n')
			size += 1;
	}
	fclose(table);
	table = fopen(file_name, "rt");

	sportsmens = (struct sportsmen*)malloc(size * sizeof(struct sportsmen));


	for (int i = 0; i < size + 1; i++) {
		fscanf(table, "%s", &sportsmens[i].full_name);
		fscanf(table, " %5f ", &sportsmens[i].results[0]);
		fscanf(table, " %5f ", &sportsmens[i].results[1]);
		fscanf(table, " %5f ", &sportsmens[i].results[2]);
		fscanf(table, " %5f ", &sportsmens[i].results[3]);
		fscanf(table, " %5f ", &sportsmens[i].results[4]);
		fscanf(table, " %5f\n", &sportsmens[i].results[5]);
	}
	
	
	int is_sorted = 0;

	while (what_do != 5) {
		if (is_sorted == 0) {
			sort(size, sportsmens);
			is_sorted += 1;
		}
		printf("\nВот что может программа:\n1)Вывести таблицу результатов;\n2)Вывести список победителей;\n3)Вывести выбывших игроков\n4)Показать средний арифметический результат\n5)Выйти из программы\n6)Очистить консоль\n");

		scanf_s("%d", &what_do);
		switch (what_do)
		{
		case 1: {
			puts("Результаты спортсменов,Каждая строка - это результаты спортсмена за 6 попыток");
			
			results(size, sportsmens);
			break;
		}
		case 2:  winners(size, sportsmens); break;
		case 3:  kicked(size, sportsmens); break;
		case 4: {
			float averag = average(size, sportsmens);
			printf("Среднее арифметическое из всех рузультатов спортсменов %5.2f\n", averag);
			break;
		}
		case 5: puts("Выход совершен успешно!"); free(sportsmens); break;
		case 6: system("cls"); puts("Очистка прошла успешно!"); break;
		default:
			printf("Неизвестная программа");
			break;
		}
	}
}


float local_maximum(struct  sportsmen sportsmen)
{
	float max = 0.0;
	for (int i = 0; i < 4; i++) {
		if (sportsmen.results[i] > max) {
			max = sportsmen.results[i];
		}
	}
	return max;
}
void sort(int size, struct sportsmen sport[]) {
	setlocale(LC_ALL, "rus");
	for (int i = 0; i < size + 1; i++) {
		sport[i].maximum = local_maximum(sport[i]);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i; j++) {
			if (sport[j + 1].maximum > sport[j].maximum) {
				struct sportsmen buffer = sport[j + 1];
				sport[j + 1] = sport[j];
				sport[j] = buffer;
			}
		}
	}

}
void results(int size, struct sportsmen sport[]) {
	setlocale(LC_ALL, "rus");

	for (int i = 1; i < size + 2; i++) {
		printf("\n\n");
		for (int j = 0; j < 7; j++) {
			if (j == 0) {
				printf("%1d %5s ", i, sport[i - 1].full_name);
			}
			else
			{
				printf("%5.2f ", sport[i - 1].results[j - 1]);
			}
		}
	}
	printf("\n\n");
}
void winners(int size, struct sportsmen sport[]) {
	float* maximums;
	maximums = (float*)malloc(size * sizeof(float));
	float winners_score[3];
	int winner_index[3];
	for (int i = 0; i < 8; i++) {
		maximums[i] = local_maximum(sport[i]);
	}
	float max_1 = 0.0;
	float max_2 = 0.0;
	float max_3 = 0.0;

	for (int i = 0; i < 8; i++) {
		if (maximums[i] > max_1) {
			max_1 = maximums[i];
			winner_index[0] = i;
		}
	}
	winners_score[0] = max_1;
	for (int i = 0; i < 8; i++) {
		if ((maximums[i] > max_2) && (maximums[i] != max_1)) {
			max_2 = maximums[i];
			winner_index[1] = i;
		}
	}
	winners_score[1] = max_2;
	for (int i = 0; i < 8; i++) {
		if ((maximums[i] > max_3) && (maximums[i] != max_1) && (maximums[i] != max_2)) {
			max_3 = maximums[i];
			winner_index[2] = i;
		}
	}
	winners_score[2] = max_3;
	printf("Победители:\n");
	for (int i = 1; i < 4; i++) {
		printf("%d место: %s с результатом %5.2f\n", i, sport[winner_index[i - 1]].full_name, winners_score[i - 1]);
	}
	free(maximums);
}

float kicked(int size, struct sportsmen sport[]) {
	puts("Проигравшие(Набравшие наихудшие результаты за первые 3 попытки)");
	for (int i = 8; i < size + 1; i++) {
		printf("\n\n");
		for (int j = 0; j < 7; j++) {
			if (j == 0) {
				printf("%1d %5s ", i+1, sport[i].full_name);
			}
			else
			{
				printf("%5.2f ", sport[i].results[j]);
			}
		}
		
	}
	printf("\n");
	
}
float average(int size, struct sportsmen sport[]) {
	float summ = 0.0;
	float average = 0.0;
	for (int i = 0; i < size + 1; i++) {
		for (int j = 0; j < 6; j++) {
			summ += sport[i].results[j];
		}
	}
	average = summ / ((float)size * 6.0);
	return average;
}

