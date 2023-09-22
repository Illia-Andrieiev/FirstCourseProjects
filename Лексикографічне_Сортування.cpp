#include <iostream>
#include <stdio.h>
#include <cstdlib>
#define LENGTH_MAX_WORD 25
using namespace std;
typedef struct node {
	char word[LENGTH_MAX_WORD];
	int size;
	struct node* next = NULL;
}List,*plist;
FILE* pivot;
//*****************************************
void out_sort();
void rand_fill_file(int amount);
void  print_file(FILE* name);
plist create_list(char arr[][LENGTH_MAX_WORD], int size);
void delete_list(plist start);
void merge_list_arr(plist list_sort_arr[], int size);
//*****************************************
int main() {
	rand_fill_file(15);
	print_file(pivot);
	out_sort();
	print_file(pivot);
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	
	return 0;
}
//Заповнення файлу випадковими числами
void rand_fill_file(int amount) {
	errno_t err;
	err = fopen_s(&pivot, "sourse.docx", "w");
	if (!err) {
		int rnom;
		for (int i = 0; i < amount; i++) {
			rnom = rand()%20;
			fwrite(&rnom, 1, sizeof(rnom), pivot);
		}
		fclose(pivot);
	}
}
//Виведення файлу
void  print_file(FILE* name) {
	errno_t err;
	err = fopen_s(&name, "sourse.docx", "r");
	if (!err) {
		int nom;
		fread(&nom, 1, sizeof(nom), name);
		while (!feof(name)) {		
			cout << nom<< " ";
			fread(&nom, 1, sizeof(nom), name);
		}
		cout << endl;
		fclose(name);
	}
}
//зовнішнє сортування	
void out_sort() {
	FILE* first;
	FILE* second;
	bool flag = true, flag1 = 1;
	int e=0, nomfirst = 0,nomsec = 0;
	errno_t err, errf, errs;
	char ch ='s';
	//cout << "iteretion"<<endl;
	err = fopen_s(&pivot, "sourse.docx", "r");
	errf = fopen_s(&first, "first.docx", "w");
	errs = fopen_s(&second, "second.docx", "w");
	//Зчитування в два допоміжні файли 
	if (!err && !errf && !errs) {
		//Запис у 1
		while (!feof(pivot)) {
			static int i = 0;
			fread(&nomfirst, 1, sizeof(nomfirst), pivot);
			if (feof(pivot))
				break;
			if (i % 2 == 0) {
				fwrite(&nomfirst, 1, sizeof(nomfirst), first);
				i++;
			}
			else {
				fwrite(&nomfirst, 1, sizeof(nomfirst), second);
				i++;
			}

		}
		fclose(pivot);
		fclose(first);
		fclose(second);
	}
	
	//Вивід допоміжних файлів
	/*
	err = fopen_s(&first, "first.docx", "r");
	if (!err) {
		int nom;
		fread(&nom, 1, sizeof(nom), first);
		while (!feof(first)) {			
			cout << nom << " ";
			fread(&nom, 1, sizeof(nom), first);
		}
		cout << endl;
		fclose(first);
	}
	err = fopen_s(&second, "second.docx", "r");
	if (!err) {
		int nom;
		fread(&nom, 1, sizeof(nom), second);
		while (!feof(second)) {
			cout << nom << " ";
			fread(&nom, 1, sizeof(nom), second);
		
		}
		cout << endl;
		fclose(second);
	}
	*/
	err = fopen_s(&pivot, "sourse.docx", "w");
	errf = fopen_s(&first, "first.docx", "r");
	errs = fopen_s(&second, "second.docx", "r");
	//Запис впорядкування в початковий файл
	if (!err && !errf && !errs) {
		fread(&nomfirst, 1, sizeof(nomfirst), first);
		fread(&nomsec, 1, sizeof(nomsec), second);
		while (!feof(first) && !feof(second)) {
			if (nomfirst >= nomsec) {
				fwrite(&nomsec, 1, sizeof(nomsec), pivot);
				fread(&nomsec, 1, sizeof(nomsec), second);
				if (feof(second)) {
					//Дописування в кінець початкового файлу
					while (!feof(first)) {
						fwrite(&nomfirst, 1, sizeof(nomfirst), pivot);
						fread(&nomfirst, 1, sizeof(nomsec), first);
					}

				}
			}
			else {
				fwrite(&nomfirst, 1, sizeof(nomfirst), pivot);
				fread(&nomfirst, 1, sizeof(nomfirst), first);
				if (feof(first)) {
					//Дописування в кінець початкового файлу
					while (!feof(second)) {
						fwrite(&nomsec, 1, sizeof(nomsec), pivot);
						fread(&nomsec, 1, sizeof(nomsec), second);
					}

				}

			}
		}

		fclose(second);
		fclose(first);
		fclose(pivot);
	}
	err = fopen_s(&pivot, "sourse.docx", "r");
	//Перевірка на впорядкованість
	if (!err) {
		fread(&nomfirst, 1, sizeof(nomfirst), pivot);
		fread(&nomsec, 1, sizeof(nomsec), pivot);
		flag = 1;
		while (!feof(pivot)) {
			if (nomfirst <= nomsec) {
				nomfirst = nomsec;
				fread(&nomsec, 1, sizeof(nomsec), pivot);
			}
			else {
				flag = 0;
				break;
			}
		}
		if (nomfirst > nomsec)
			flag = 0;
		if (!flag) {
			fclose(pivot);
			out_sort();
		}
		fclose(pivot);
	}
}
//Запис двумірного масиву чарів у сисок
plist create_list(char arr[][LENGTH_MAX_WORD], int size_arr, char alph[]) {
	plist last = new List;
	const int SIZE_ALPHABET = sizeof(alph);
	for (int k = 0; k < LENGTH_MAX_WORD; k++) {
		bool flag = 0;
		for (int j = 0; j < SIZE_ALPHABET; j++) {
			if (arr[0][k] == alph[j]) {
				flag = 1;
				break;
			}
		}
		if (flag) {
			last->word[k] = arr[0][k];
		}
		else {
			last->size = k + 1;
			break;
		}
	}
	for (int i = 1; i < size_arr; i++) {
		plist step = new List;
		for (int k = 0; k < LENGTH_MAX_WORD; k++) {
			bool flag = 0;
			for (int j = 0; j < SIZE_ALPHABET; j++) {
				if (arr[i][k] == alph[j]) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				step->word[k] = arr[i][k];
			}
			else {
				step->size = k + 1;
				break;
			}
		}
		step->next = last;
		last = step;
	}

	return last;
}
//Видалення списку
void delete_list(plist start) {
	plist step = start;
	while (start) {
		start = start->next;
		delete step;
		step = start;
	}
}
//******************************************************************
//Сортування вичерпуваням слів різної довжини
plist language_bucket_sort(plist words, char alphabet[]){
	const int SIZE_ALPHABET = sizeof(alphabet);
	plist step = words;
	for (int current_min_length = LENGTH_MAX_WORD; current_min_length > 0; current_min_length--) {
		plist list_sort_arr[SIZE_ALPHABET + 1];
		for (int i = 0; i - 1 < SIZE_ALPHABET; i++) {
			list_sort_arr[i] = NULL;
		}
		while (step) {
			//Запис усіх слів менших за current_min_length в початок нового списку
			if (step->size < current_min_length) {
				plist last = new List;
				last = step;
				last->next = list_sort_arr[0];
				list_sort_arr[0] = last;
				step = step->next;
			}
			//Запис усіх слів більших-рівних за current_min_length в початок нового списку
			else {
				plist last = new List;
				char ch = step->word[current_min_length-1];
				int position = 0;
				//Знаходження позиції літери в алфавіті
				while (position < SIZE_ALPHABET) {
					if (ch == alphabet[position])
						break;
					else
						position++;
				}
				//Вставка слова у відповідний список
				last = step;
				last->next = list_sort_arr[position + 1];
				list_sort_arr[position + 1] = last;
				step = step->next;
			}
		}
		//Злиття в єдиний масив, видалення старого списку
		merge_list_arr(list_sort_arr, SIZE_ALPHABET + 1);
		step = words;
		delete_list(step);
		step = list_sort_arr[0];
		words = list_sort_arr[0];
	}
	return step;
}
//Злиття масиву списків
void merge_list_arr(plist list_sort_arr[], int size) {
	plist step = list_sort_arr[0];
	for (int i = 1; i < size; i++) {
		while (step->next)
			step = step->next;
		step->next = list_sort_arr[i];
		step = step -> next;
	}
}