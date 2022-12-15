#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#pragma warning(disable:4996)
#define SIZE   10
#define LEN_NAME 40
#define lEN_SCORE 7
#define LEN_FILENAME 40
#define KICK_RANGE 8 
#define RESULTS_DEL1 3
#define RESULTS_DEL2 7
#define LAST_RESULT 6
int file_read(char name[LEN_FILENAME], char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]);
float local_maximum(float scores[], int diap);
void sort(int size, char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]);
void results(int size, char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]);
int found_max(float maxes[], int number);
void winners(int size, char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]);
float kicked(int size, char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]);
float average(int size, float scores[SIZE][lEN_SCORE]);



int main()
{



	setlocale(LC_ALL, "rus");



	char  extension[6] = { ".txt\0" };
	char file_name[LEN_FILENAME];
	puts("Введите название файла в пределах 30 символов (без указания расширения файла)");

	scanf("%s", file_name);//Чтобы имена спортсменов корректно считались необходимо сменить кодировку с UTF-8 на ANCII
	strcat(file_name, extension);
	printf("Имя файла: %s\n", file_name);
	int what_do = 0;

	float scores[SIZE][lEN_SCORE];
	char names[SIZE][LEN_NAME];
	file_read(file_name, names, scores);



	int is_sorted = 0;

	while (what_do != 5) {
		if (is_sorted == 0) {
			sort(SIZE, names, scores);
			is_sorted += 1;
		}
		puts("Толкание ядра");
		printf("\nВот что может программа:\n1)Вывести таблицу результатов;\n2)Вывести список победителей;\n3)Вывести выбывших игроков\n4)Показать средний арифметический результат\n5)Выйти из программы\n6)Очистить консоль\n");

		scanf_s("%d", &what_do);
		switch (what_do)
		{
		case 1: {
			puts("Результаты спортсменов,Каждая строка - это результаты спортсмена за 6 попыток");

			results(SIZE, names, scores);
			break;
		}
		case 2:  winners(SIZE, names, scores); break;
		case 3:  kicked(SIZE, names, scores); break;
		case 4: {

			printf("Среднее арифметическое из всех рузультатов спортсменов %5.2f\n", average(SIZE, scores));
			break;
		}
		case 5: puts("Выход совершен успешно!"); return 0;
		case 6: system("cls"); puts("Очистка прошла успешно!"); break;
		default:
			printf("Неизвестная программа");
			break;
		}
	}
}

int file_read(char filename[LEN_FILENAME], char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]) {
	FILE* table;
	table = fopen(filename, "rt");
	if (table == NULL) {
		puts("Не удалось открыть файл");
		fclose(table);
		exit(0);
	}
	int test_for_errs = 0;
		while (!feof(table)) {
			if (fgetc(table) == '\n') {
				test_for_errs += 1;
			}
		}
		if (test_for_errs != SIZE) {
			printf("Несоответствие масивов, в файле находится %d столбцов,а требуется %d\nЕсли количество элементов правильно, нажмите этер после последнего элемета.", test_for_errs, SIZE);
			exit(0);
		}
	fseek(table, 0, SEEK_SET);
	for (int i = 0; i < SIZE; i++) {

		fscanf(table, "%s ", &names[i]);
		fscanf(table, " %5f ", &scores[i][0]);
		fscanf(table, " %5f ", &scores[i][1]);
		fscanf(table, " %5f ", &scores[i][2]);
		fscanf(table, " %5f ", &scores[i][3]);
		fscanf(table, " %5f ", &scores[i][4]);
		fscanf(table, " %5f\n", &scores[i][5]);

	}
	return 1;
}
float local_maximum(float scores[], int diap)
{
	float max = 0.0;
	
	for (int i = 0; i < diap; i++) {
		if (scores[i] > max) {
			max = scores[i];
		}
	}
	return max;
}
void sort(int size, char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]) {
	setlocale(LC_ALL, "rus");

	for (int i = 0; i < size; i++) {
		scores[i][LAST_RESULT] = local_maximum(scores[i], 3);
	}
	int max_index = 0;
	for (int i = 0; i < size; i++) {
		max_index = i;
		for (int j = i + 1; j < size; j++) {
			if (scores[max_index][LAST_RESULT] < scores[j][LAST_RESULT]) {
				max_index = j;
			}
		}
		float buffer[lEN_SCORE];
		for (int buff = 0; buff < lEN_SCORE; buff++) {
			buffer[buff] = scores[max_index][buff];
			scores[max_index][buff] = scores[i][buff];
			scores[i][buff] = buffer[buff];
		}
		char name_buff[LEN_NAME];
		strcpy(name_buff, names[max_index]);
		strcpy(names[max_index], names[i]);
		strcpy(names[i], name_buff);

	}
	for (int i = KICK_RANGE; i < size; i++) {
		for (int j = RESULTS_DEL1; j < RESULTS_DEL2; j++) {
			scores[i][j] = 0.0;
		}
	}

}
void results(int size, char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]) {
	setlocale(LC_ALL, "rus");

	for (int i = 0; i < size; i++) {
		printf("\n");
		for (int j = 0; j < LAST_RESULT; j++) {
			if (j == 0) {
				printf("%2d %1s ", i + 1, names[i]);
			}
			printf(" %5.2f ", scores[i][j]);
		}
	}

	printf("\n\n");
}
int found_max(float maxes[],int number) {
	float max = 0.0;
	int max_index = 0;
	float past_max = 0 ;
	int past_max_index = 0;
	for (int past = 0; past < SIZE; past++) {
		if (past_max < maxes[past]) {
			past_max = maxes[past];
			past_max_index = past;
		}
	}
	if (number == 1) {
		return past_max_index;
	}
	for (int i = 0; i < number-1; i++) {
		max = maxes[max_index];
		
		for (int j = 0; j < SIZE; j++) {

			if ((max < maxes[j])&&(maxes[j]<past_max)) {
				past_max = max;
				max = maxes[j];
				max_index = j;
				
			}
		}
	if (i == number - 1) {
		return max_index;
	}
	}
}
void winners(int size, char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]) {
	float* maximums;
	maximums = (float*)malloc(size * sizeof(float));
	float winners_score[3];
	int winner_index[3];
	for (int i = 0; i < SIZE; i++) {
		maximums[i] = local_maximum(scores[i], 7);
	}
	int max_1 = found_max(maximums,1);
	int max_2 = found_max(maximums, 2);
	int max_3 = found_max(maximums, 3);
	int max_indexes[3] = { max_1,max_2,max_3 };
	
	printf("Победители:\n");
	for (int i = 1; i < 4; i++) {
		printf("%d место: %s с результатом %5.2f\n", i, names[max_indexes[i-1]], maximums[max_indexes[i - 1]]);
	}
	free(maximums);
}

float kicked(int size, char names[SIZE][LEN_NAME], float scores[SIZE][lEN_SCORE]) {
	puts("Проигравшие(Набравшие наихудшие результаты за первые 3 попытки)");
	for (int i = KICK_RANGE; i < size; i++) {
		printf("\n\n");
		for (int j = 0; j < 6; j++) {
			if (j == 0) {
				printf("%d %s ", i + 1, names[i]);
			}
			printf(" %5.2f", scores[i][j]);
		}

	}
	printf("\n");
	return 0.0;

}
float average(int size, float scores[SIZE][lEN_SCORE]) {
	float summ = 0.0;
	float average = 0.0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 6; j++) {
			summ += scores[i][j];
		}
	}
	average = summ / ((float)size * LAST_RESULT);
	return average;
}


