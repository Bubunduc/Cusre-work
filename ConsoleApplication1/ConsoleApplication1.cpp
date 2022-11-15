// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <locale.h>
void results();
void winners();
void kicked();
int main()
{
	
	setlocale(LC_ALL, "rus");
	while (1 > 0) {
		
		printf("\nВот что может программа:\n1)Вывести таблицу результатов;\n2)Вывести список победителей;\n3)Вывести выбывших игроков\n4)Выход\n");
		int what_do;
		scanf_s("%d", &what_do);
		switch (what_do)
		{
		case 1: results(); break;
		case 2: winners(); break;
		case 3: kicked(); break;

		default:
			printf("Неизвестная программа");
			break;
		}
	}
}
void results() {
	setlocale(LC_ALL, "rus");
	puts("Результаты спортсменов,Каждая строка - это результаты нового спортсмена за 8 попыток");
	float sportsmens[9][6];
	sportsmens[0][0] = 11.12;
	sportsmens[0][1] = 15.0;
	sportsmens[0][2] = 12.13;
	sportsmens[0][3] = 10.9;
	sportsmens[0][4] = 17.6;
	sportsmens[0][5] = 18.32;
	sportsmens[1][0] = 19.60;
	sportsmens[1][1] = 10.20;
	sportsmens[1][2] = 11.60;
	sportsmens[1][3] = 18.20;
	sportsmens[1][4] = 15.60;
	sportsmens[1][5] = 19.50;
	sportsmens[2][0] = 17.00;
	sportsmens[2][1] = 15.10;
	sportsmens[2][2] = 18.10;
	sportsmens[2][3] = 14.20;
	sportsmens[2][4] = 11.30;
	sportsmens[2][5] = 12.85;
	sportsmens[3][0] = 15.20;
	sportsmens[3][1] = 22.12;
	sportsmens[3][2] = 14.20;
	sportsmens[3][3] = 15.70;
	sportsmens[3][4] = 17.30;
	sportsmens[3][5] = 14.50;
	sportsmens[4][0] = 17.03;
	sportsmens[4][1] = 12.30;
	sportsmens[4][2] = 11.56;
	sportsmens[4][3] = 12.89;
	sportsmens[4][4] = 15.21;
	sportsmens[4][5] = 19.20;
	sportsmens[5][0] = 10.20;
	sportsmens[5][1] = 9.30;
	sportsmens[5][2] = 11.20;
	sportsmens[5][3] = 0.00;
	sportsmens[5][4] = 0.00;
	sportsmens[5][5] = 0.00;
	sportsmens[6][0] = 15.18;
	sportsmens[6][1] = 21.30;
	sportsmens[6][2] = 12.60;
	sportsmens[6][3] = 15.20;
	sportsmens[6][4] = 16.45;
	sportsmens[6][5] = 13.35;
	sportsmens[7][0] = 11.20;
	sportsmens[7][1] = 18.23;
	sportsmens[7][2] = 11.24;
	sportsmens[7][3] = 16.22;
	sportsmens[7][4] = 16.31;
	sportsmens[7][5] = 11.00;
	sportsmens[8][0] = 12.30;
	sportsmens[8][1] = 15.49;
	sportsmens[8][2] = 13.61;
	sportsmens[8][3] = 18.21;
	sportsmens[8][4] = 15.02;
	sportsmens[8][5] = 14.23;
	for (int i = 0; i < 7; i++) {
		printf("%d     ", i);
	}
	for (int i = 1; i < 10; i++) {
		printf("\n\n");
		for (int j = 0; j < 6; j++) {
			if (j == 0) {
				printf("%1d %5.2f ", i, sportsmens[i - 1][j]);
			}
			else
			{
				printf("%5.2f ", sportsmens[i - 1][j]);
			}
		}
	}

}
void winners() {
	printf("Победители:\n");
}
void kicked() {
	printf("Выбывшие игроки\n");
}




