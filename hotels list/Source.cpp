#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX 30

int menu() {
	printf("\n");
	printf("\tMENU\n");
	printf("-----------------------\n");
	printf("1. Display the hotel list\n");
	printf("2. Add new hotel\n");
	printf("3. EXIT\n");

	printf("\n");
	int choice;
	do {
		printf("Enter choice: ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 3);
	return (choice);
	printf("\n");
}

int readFromFile(FILE* inp, char arr[][MAX]) {
	int i = 0;
	while (fscanf(inp, " %[^\n]", arr[i]) != EOF)
		i++;
	return i;
}

void display(char arr[][MAX], int size) {
	int i;
	printf("Hotel List\n");
	printf("-------------------\n");
	for (i = 0; i < size; i++)
		printf("%d) %s\n", i + 1, arr[i]);
}

void sort(char* str1, char* str2) {
	char temp[MAX];
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
}

void bubbleSort(char arr[][MAX], int size) {
	int k, pass = 1, sorted;
	do {
		sorted = 1;
		for (k = 0; k < size - pass; k++)
			if (strcmp(arr[k], arr[k + 1]) > 0)
			{
				sort(arr[k], arr[k + 1]);
				sorted = 0;
			}
		pass++;
	} while (!sorted);
}

int binarySearch(char arr[][MAX], int top, int bottom, char key[MAX], int* mid) {
	while (top <= bottom)
	{
		*mid = (top + bottom) / 2;

		if (strcmp(arr[*mid], key) == 0)
			return (*mid + 1);
		else if (strcmp(arr[*mid], key) > 0)
			bottom = *mid - 1;
		else
			top = *mid + 1;
	}
	return (-1);
}

void shiftDown(char arr[][MAX], int* size, int newPos) {
	int k;
	char temp[MAX];
	for (k = (*size); k > newPos; k--)
		strcpy(arr[k], arr[k - 1]);
	(*size)++;
}

void addToList(char arr[][MAX], int* size, int newPos, char temp[]) {
	shiftDown(arr, size, newPos);
	strcpy(arr[newPos], temp);
}

int main(void)
{
	FILE* inp;
	inp = fopen("hotels.txt", "r");
	if (inp == NULL)
		printf("Error");
	else
	{
		char arr[MAX][MAX];
		int size = readFromFile(inp, arr);
		bubbleSort(arr, size);
		display(arr, size);
		int choice;
		do {
			choice = menu();

			char temp[MAX];
			int findHotel, mid;
			switch (choice)
			{
			case 1:
				display(arr, size);  break;
			case 2:
				printf("Enter a hotel name: ");
				scanf(" %[^\n]", temp);
				findHotel = binarySearch(arr, 0, size - 1, temp, &mid);
				if (findHotel != (-1))
					printf("\"%s\" already exists on the list!\n", arr[findHotel]);
				else
				{
					addToList(arr, &size, mid, temp);
					printf("\"%s\" added to the list!\n", temp);
				}
				break;
			}
		} while (choice != 3);
	}
	return 0;
}