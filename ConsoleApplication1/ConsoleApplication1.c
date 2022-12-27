#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <windows.h>
#pragma warning(disable:4996)
#define SIZE   10
#define LEN_NAME 40
#define LEN_SCORE 7
#define LEN_FILENAME 40
#define KICK_RANGE 8 
#define RESULTS_DEL1 3
#define RESULTS_DEL2 7
#define LAST_RESULT 6
#define PLACES 3
int file_read(char filename[LEN_FILENAME], char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE]);
float local_maximum(float scores[], int diap);
void sort(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE]);
void results(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE]);
int found_max(float maxes[], int number);
void winners(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE],int places[PLACES]);
float average(int size, float scores[SIZE][LEN_SCORE]);
int reduct(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE], char original_names[SIZE][LEN_NAME], float original_scores[SIZE][LEN_SCORE], char name[LEN_NAME]);
int minimum(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE]);
float local_minimum(float scores[]);
int main()
{

	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char  extension[6] = { ".txt" };
	char file_name[LEN_FILENAME];
	puts("Введите название файла в пределах 30 символов (без указания расширения файла)");

	scanf("%s", file_name);//Чтобы имена спортсменов корректно считались необходимо сменить кодировку с UTF-8 на ANCII
	strcat(file_name, extension);
	printf("Имя файла: %s\n", file_name);
	int what_do = 0;

	float scores[SIZE][LEN_SCORE];
	char names[SIZE][LEN_NAME];
	float original_scores[SIZE][LEN_SCORE];
	char original_names[SIZE][LEN_NAME];
	file_read(file_name, names, scores);
	file_read(file_name, original_names, original_scores);


	int is_sorted = 0;

	while (what_do != 9) {
		if (is_sorted == 0) {
			sort(SIZE, names, scores);
			is_sorted += 1;
		}
		printf("Толкание ядра\n");
		printf("\nВот что может программа:\n1)Вывести изначальную таблицу\n2)Вывести таблицу результатов,отсортированную по первым 3-м попыткам;\n3)Вывести список победителей;\n4)Вывести выбывших игроков\n5)Показать средний арифметический результат\n6)Изменить значения у одного из спортсменов\n7)Очистить консоль\n8)Показать наихудший среди всех результат\n9)Выйти из программы\n");

		scanf_s("%d", &what_do);
		switch (what_do)
		{
		case 1: {
			printf("Результаты спортсменов,Каждая строка - это результаты спортсмена за 6 попыток\n\n");

			results(SIZE, original_names, original_scores);
			break;
		}
		case 2: {
			printf("Результаты спортсменов,Каждая строка - это результаты спортсмена за 6 попыток\n\n");

			results(SIZE, names, scores);
			break;
		}
		
		case 3: {
			int places[PLACES];
			winners(SIZE, names, scores  ,places);
			printf("Победители, при поиске в изначальном массиве:\n\n");
			for (int i = 0; i < PLACES; i++) {
				printf("%d место: %s с индексом %d и наибольшим значением %5.2f\n\n", i+1, names[places[i]],places[i], local_maximum(scores[places[i]],6));
			}
			break;
		}
		case 4: { 
			puts("Проигравшие(Набравшие наихудшие результаты за первые 3 попытки)\n");
			printf("Номер      Имя         Попытка 1    Попытка 2   Попытка 3   Попытка 4   Попытка 5   Попытка 6");
			for (int i = KICK_RANGE; i < SIZE; i++) {
				printf("\n\n");
				for (int j = 0; j < LAST_RESULT; j++) {
					if (j == 0) {
						printf("%2d %15s  ", i + 1, names[i]);
					}
					printf(" %10.2f ", scores[i][j]);
				}

			}
			printf("\n\n");
			
		}
			  break;
		case 5: {

			printf("\nСреднее арифметическое из всех рузультатов спортсменов %5.2f\n\n", average(SIZE, scores));
			break;
		}
		case 6: {
			int flag;
			char name[LEN_NAME];
			printf("Введите имя нужного спортсмена : \n");
			scanf_s("%s", name,LEN_NAME);
			flag = reduct(SIZE, names, scores, original_names, original_scores, name);
			if (flag == 0) {
				printf("По запросу %s ничего не найдено\n\n", name);
			}
			break;
		}
		case 7: system("cls"); puts("Очистка прошла успешно!"); break;
		case 8: {
			int lowest;
			lowest = minimum(SIZE, names, scores);
			printf("Наихудший результат принадлежит игроку %s под индексом %d\nОн равен: %5.2f\n\n",names[lowest],lowest,local_minimum(scores[lowest]));
			break;
		}
		case 9:puts("Выход совершен успешно!"); return 0;
		default:
			printf("Неизвестная программа\n\n");
			break;
		}
	}
}

int file_read(char filename[LEN_FILENAME], char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE]) {
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
	fclose(table);
	return 1;
}
float local_maximum(float scores[], int diap)
{
	float max = scores[0];
	
	for (int i = 0; i < diap; i++) {
		if (scores[i] > max) {
			max = scores[i];
		}
	}
	return max;
}
void sort(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE]) {
	setlocale(LC_ALL, "rus");

	for (int i = 0; i < size; i++) {
		scores[i][LAST_RESULT] = local_maximum(scores[i], RESULTS_DEL1);
	}
	int max_index = 0;
	for (int i = 0; i < size; i++) {
		max_index = i;
		for (int j = i + 1; j < size; j++) {
			if (scores[max_index][LAST_RESULT] < scores[j][LAST_RESULT]) {
				max_index = j;
			}
		}
		float buffer[LEN_SCORE];
		for (int buff = 0; buff < LEN_SCORE; buff++) {
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
void results(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE]) {
	setlocale(LC_ALL, "rus");
	printf("Номер      Имя         Попытка 1    Попытка 2   Попытка 3   Попытка 4   Попытка 5   Попытка 6");
	for (int i = 0; i < size; i++) {
		printf("\n\n");
		for (int j = 0; j < LAST_RESULT; j++) {
			if (j == 0) {
				printf("%2d %15s  ", i + 1, names[i]);
			}
			printf(" %10.2f ", scores[i][j]);
		}
	}

	printf("\n\n");
}
int found_max(float maxes[],int number) {
	float max = 0.0;
	int max_index = maxes[0];
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
		
		
		for (int j = 0; j < SIZE; j++) {

			if ((max < maxes[j])&&(maxes[j]<past_max)) {
				past_max = max;
				max = maxes[j];
				max_index = j;
				
			}
		}
	if (i == number-1 ) {
		return max_index;
	}
	}
}
void winners(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE],int places[PLACES]) {
	float* maximums;
	maximums = (float*)malloc(size * sizeof(float));
	float winners_score[3];
	int winner_index[3];
	for (int i = 0; i < SIZE; i++) {
		maximums[i] = local_maximum(scores[i], LAST_RESULT);
	}
	
	for (int place = 0; place < PLACES;place++) {
		places[place] = found_max(maximums, place + 1);
	}
	free(maximums);
}
float average(int size, float scores[SIZE][LEN_SCORE]) {
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
int reduct(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE], char original_names[SIZE][LEN_NAME], float original_scores[SIZE][LEN_SCORE],char name[LEN_NAME]) {
	setlocale(LC_ALL, "rus");
	for (int i = 0; i < size; i++) {
		strcpy(names[i],original_names[i]);
		for (int j = 0; j<LAST_RESULT; j++) {
			scores[i][j] = original_scores[i][j];
		}
	}
	for (int i = 0; i < size; i++) {
		if (strcmp(names[i], name) == 0) {
			printf("%s найден\n\n", name);
			
			for (int value = 0; value < LAST_RESULT; value++) {
				printf("Введите значение %d  ", value + 1);
				float new_value;
				scanf_s("%f", &new_value);
				printf("\n");
				scores[i][value] = new_value;
			}
			sort(SIZE, names, scores);
			return 1;
		}
			
	}
	return 0;
}
int minimum(int size, char names[SIZE][LEN_NAME], float scores[SIZE][LEN_SCORE]) {
	int min_index;
	float minimum = scores[0][0];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < LEN_SCORE; j++) {
			if (scores[i][j] < minimum) {
				minimum = scores[i][j];
				min_index = i;
			}
		}
	}
	return min_index;
}
float local_minimum(float scores[]) {
	float min = scores[0];

	for (int i = 0; i < LAST_RESULT; i++) {
		if ((scores[i] < min)&&(scores[i]!=0)) {
			min = scores[i];
		}
	}
	return min;
}
