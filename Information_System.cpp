#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <conio.h>
#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define STD_OUTPUT_HANDLE  ((DWORD)-11)
using namespace std;

struct Music {
	short int nomer;
	char track[40];
	char genre[15];
	char autor[30];
	char album[20];
	int year;
	bool vision;
};

HANDLE my_consol = GetStdHandle(STD_OUTPUT_HANDLE);
FILE* music_lib;
//********************************************************************************************
Music entering_music(short int& nom);
bool checking_arrs(char arr1[], char arr2[], const int SIZE);
void add_music(short int& nom, int& k);
void print_music_all(int option, short int& nom);
void print_music_chunk(short command[]);
int edit_music_nomer(short& nom);
int edit_music_name(short& nom);
void ConsoleCursorVisible(bool show, short size);
void change_colour_print(int active_menu, short x, short y, string Menu[], short menu[]);
void change_colour(int active_menu, short x, short y, string Menu[], int size);
int menu_print(short& nom);
int menu_edit(short& nom, int& zvit_change);
int menu_delete(short& nom, int& zvit_deleted);
int delete_music_nomer(short& nom);
int delete_music_name(short& nom);
void search_year(short& nom);
void search_else(short& nom, int option);
int menu_search(short& nom);
int menu(short& nom);
//*****************************************************************************************************
int main() {

	setlocale(LC_CTYPE, "ukr");
	short int nom;
	print_music_all(1, nom);
	menu(nom);
	return 0;
}
// Введення параметрів музики
Music entering_music(short int& nom) {
	short x = 50, y = 12;
	Music element;
	for (int i = 0; i < 40; i++) {
		element.track[i] = NULL;
	}
	for (int i = 0; i < 15; i++) {
		element.genre[i] = NULL;
	}
	for (int i = 0; i < 30; i++) {
		element.autor[i] = NULL;
	}
	for (int i = 0; i < 20; i++) {
		element.album[i] = NULL;
	}
	element.nomer = nom;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cout << "Введіть назву треку: " << endl;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cin >> element.track;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cout << "Введіть жанр треку: " << endl;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cin >> element.genre;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cout << "Введіть автора треку: " << endl;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cin >> element.autor;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cout << "Введіть альбом, до якого входить трек: " << endl;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cin >> element.album;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cout << "Введіть рік виходу треку: " << endl;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	cin >> element.year;
	SetConsoleCursorPosition(my_consol, { x, y++ });
	element.vision = 1;
	nom++;
	return element;
}
//Додавання музики у файл
void add_music(short int& nom, int& k) {
	Music elem = entering_music(nom);
	errno_t err = fopen_s(&music_lib, "music_lib.docx", "a");
	if (err == 0) {
		fwrite(&elem, 1, sizeof(elem), music_lib);
		int errr = fclose(music_lib);
		k++;
		SetConsoleCursorPosition(my_consol, { 50, 23 });
		cout << "Композицію додано! ";
		system("pause");
	}
	else {
		SetConsoleCursorPosition(my_consol, { 50, 1 });
		SetConsoleTextAttribute(my_consol, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Не вдалось відкрити файл" << endl;
		system("pause");
	}

}
//Виведення всієї музики
void print_music_all(int option, short int& nom) {
	short x = 50, y = 12;
	errno_t err;
	err = fopen_s(&music_lib, "music_lib.docx", "r");
	Music tracks;
	if (err == 0 && option == 0) {
		SetConsoleCursorPosition(my_consol, { 50, 11 });
		cout << " Номер треку в списку: ";
		cout << " Назва треку: ";
		cout << " Жанр треку: ";
		cout << " Автор треку: ";
		cout << " Альбом, до якого входить трек: ";
		cout << " Рік виходу треку: ";
		while (!feof(music_lib)) {
			fread(&tracks, 1, sizeof(tracks), music_lib);
			if (tracks.vision == 1) {
				cout << tracks.nomer;
				cout << "              " << tracks.track;
				cout << "             " << tracks.genre;
				cout << "             " << tracks.autor;
				cout << "                         " << tracks.album;
				cout << "                        " << tracks.year << endl;

			}
		}
		int errr = fclose(music_lib);
	}
	else {
		if (option == 0 && err != 0) {
			SetConsoleCursorPosition(my_consol, { 50, 13 });
			SetConsoleTextAttribute(my_consol, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Не вдалось відкрити файл" << endl;
		}

	}
	if (err == 0 && option == 1) {
		nom = 0;
		while (!feof(music_lib)) {
			fread(&tracks, 1, sizeof(tracks), music_lib);
			nom++;
			int errr = fclose(music_lib);
		}
	}
	else {
		if (option == 1 && err != 0) {
			SetConsoleCursorPosition(my_consol, { 50, 13 });
			SetConsoleTextAttribute(my_consol, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Не вдалось відкрити файл" << endl;
			nom = 1;
		}
	}
}
// Виведення параметрів музики
void print_music_chunk(short command[]) {
	errno_t err;
	err = fopen_s(&music_lib, "music_lib.docx", "r");
	Music tracks;
	if (err == 0) {
		SetConsoleCursorPosition(my_consol, { 0, 12 });
		cout << " Номерa треків в списку: ";
		while (!feof(music_lib)) {
			short y = 12;
			SetConsoleCursorPosition(my_consol, { 10, ++y });
			fread(&tracks, 1, sizeof(tracks), music_lib);
			cout << tracks.nomer << endl;
			if (1 == command[0]) {
				short y = 12;
				SetConsoleCursorPosition(my_consol, { 20, ++y });
				cout << " Назви треків: ";
				while (!feof(music_lib)) {
					SetConsoleCursorPosition(my_consol, { 20, ++y });
					fread(&tracks, 1, sizeof(tracks), music_lib);
					cout << tracks.track;
				}
			}
			if (1 == command[3]) {
				SetConsoleCursorPosition(my_consol, { 60, 12 });
				cout << " Жанри треків: ";
				short y = 12;
				while (!feof(music_lib)) {

					SetConsoleCursorPosition(my_consol, { 60, ++y });
					fread(&tracks, 1, sizeof(tracks), music_lib);
					cout << tracks.genre << endl;
				}
			}
			if (1 == command[1]) {
				SetConsoleCursorPosition(my_consol, { 78, 12 });
				cout << " Автори треків: ";
				short y = 12;
				while (!feof(music_lib)) {
					SetConsoleCursorPosition(my_consol, { 78, ++y });
					fread(&tracks, 1, sizeof(tracks), music_lib);
					cout << tracks.autor << endl;
				}
			}
			if (1 == command[2]) {
				short y = 12;
				SetConsoleCursorPosition(my_consol, { 100, 12 });
				cout << " Альбоми, до яких входять треки: ";
				while (!feof(music_lib)) {
					SetConsoleCursorPosition(my_consol, { 100, ++y });
					fread(&tracks, 1, sizeof(tracks), music_lib);
					cout << tracks.album << endl;
				}
			}
			if (1 == command[4]) {
				short y = 12;
				SetConsoleCursorPosition(my_consol, { 135, 12 });
				cout << " Роки виходу треків: ";
				while (!feof(music_lib)) {
					SetConsoleCursorPosition(my_consol, { 135, ++y });
					fread(&tracks, 1, sizeof(tracks), music_lib);
					cout << tracks.album << endl;
				}
			}
		}
	}
}
// Редагування музики за номером
int edit_music_nomer(short& nom) {
	short int nomer, y = 12, check = nom;
	errno_t err;
	SetConsoleCursorPosition(my_consol, { 50, y });
	cout << "Введіть номер музики, яку бажаєте відредагувати: ";
	cin >> nomer;
	Music tracks;
	for (int i = 1; i < nom; i++) {
		err = fopen_s(&music_lib, "music_lib.docx", "r");
		if (err == 0) {
			bool checking = 0;
			fread(&tracks, 1, sizeof(tracks), music_lib);
			int errr = fclose(music_lib);
			if (tracks.nomer == nomer) {
				checking = 1;
				system("CLS");
				tracks = entering_music(nomer);
				nomer--;
				short vis;
				cout << "Бажаєте приховати композицію? 0 - так 1 - ні ";
				cin >> vis;
				if (vis == 0) {
					tracks.vision = 0;
				}
				err = fopen_s(&music_lib, "music_lib2.docx", "a");
				if (err == 0) {
					fwrite(&tracks, 1, sizeof(tracks), music_lib);
					int errr = fclose(music_lib);
				}
			}
			else {
				err = fopen_s(&music_lib, "music_lib2.docx", "a");
				if (err == 0) {
					fwrite(&tracks, 1, sizeof(tracks), music_lib);
					int errr = fclose(music_lib);
				}
				if ((!checking && (i == (check - 1))) || (!checking && check == 1)) {
					SetConsoleCursorPosition(my_consol, { 50, y++ });
					cout << "Композиції з введеним номером не існує!";
					return 0;
				}
			}
		}

	}
	int asas;
	asas = rename("music_lib.docx", "music_litter.docx");
	asas = rename("music_lib2.docx", "music_lib.docx");
	asas = rename("music_litter.docx", "music_lib2.docx");
	err = fopen_s(&music_lib, "music_lib2.docx", "w");
	if (err == 0) {
		int errr = fclose(music_lib);
	}
	return 1;
}
// Редагування музики за іменем
int edit_music_name(short& nom) {
	short int y = 12, check = nom;
	bool flag;

	errno_t err;
	SetConsoleCursorPosition(my_consol, { 50, y });
	char edit_name[40];
	for (int i = 0; i < 40; i++) {
		edit_name[i] = NULL;
	}
	Music tracks;
	cout << "Введіть назву редагованої композиції: ";
	cin >> edit_name;
	for (int i = 1; i < nom; i++) {
		short nomer = i;
		err = fopen_s(&music_lib, "music_lib.docx", "r");
		if (err == 0) {
			bool checking = 0;
			fread(&tracks, 1, sizeof(tracks), music_lib);
			int errr = fclose(music_lib);
			flag = checking_arrs(tracks.track, edit_name, 40);
			if (flag) {
				system("CLS");
				tracks = entering_music(nomer);
				short vis;
				cout << "Бажаєте приховати композицію? 0 - так 1 - ні ";
				cin >> vis;
				if (vis == 0) {
					tracks.vision = 0;
				}
				err = fopen_s(&music_lib, "music_lib2.docx", "a");
				if (err == 0) {
					fwrite(&tracks, 1, sizeof(tracks), music_lib);
					int errr = fclose(music_lib);
				}
				checking = 1;
			}
			else {
				err = fopen_s(&music_lib, "music_lib2.docx", "a");
				if (err == 0) {
					fwrite(&tracks, 1, sizeof(tracks), music_lib);
					int errr = fclose(music_lib);
				}
				if ((!checking && (i == (check - 1))) || (!checking && check == 1)) {
					SetConsoleCursorPosition(my_consol, { 50, y++ });
					cout << "Композиції з введеним іменем не існує!";
					return 0;
				}
			}
		}

	}
	int asas;
	asas = rename("music_lib.docx", "music_litter.docx");
	asas = rename("music_lib2.docx", "music_lib.docx");
	asas = rename("music_litter.docx", "music_lib2.docx");
	err = fopen_s(&music_lib, "music_lib2.docx", "w");
	if (err == 0) {
		int errr = fclose(music_lib);
	}
	return 1;
}
// Перевірка 2 масивів чарів на рівність
bool checking_arrs(char arr1[], char arr2[], const int SIZE) {
	for (int i = 0; i < SIZE; i++) {
		if (arr1[i] != arr2[i]) {
			return 0;
		}
	}
	return 1;
}
//Видалення музики за номером
int delete_music_nomer(short& nom) {
	short int nomer, y = 12, check = nom;
	bool checking = 0;
	int counter = 1;
	errno_t err;
	SetConsoleCursorPosition(my_consol, { 50, y });
	cout << "Введіть номер музики, яку бажаєте видалити: ";
	cin >> nomer;
	Music tracks;
	for (int i = 1; i < nom; i++) {

		err = fopen_s(&music_lib, "music_lib.docx", "r");
		if (err == 0) {
			fread(&tracks, 1, sizeof(tracks), music_lib);
			int errr = fclose(music_lib);
			if (tracks.nomer == nomer) {
				checking = 1;
			}
			else {
				tracks.nomer = counter;
				counter++;
				err = fopen_s(&music_lib, "music_lib2.docx", "a");
				if (err == 0) {
					fwrite(&tracks, 1, sizeof(tracks), music_lib);
					int errr = fclose(music_lib);
				}
				if ((!checking && (i == (check - 1))) || (!checking && check == 1)) {
					SetConsoleCursorPosition(my_consol, { 50, y++ });
					cout << "Композиції з введеним номером не існує!";
					return 0;
				}
			}
		}

	}
	int asas;
	asas = rename("music_lib.docx", "music_litter.docx");
	asas = rename("music_lib2.docx", "music_lib.docx");
	asas = rename("music_litter.docx", "music_lib2.docx");
	err = fopen_s(&music_lib, "music_lib2.docx", "w");
	if (err == 0) {
		int errr = fclose(music_lib);
	}
	return 1;
}
//видалення музики за іменем
int delete_music_name(short& nom) {
	short int y = 12, check = nom;
	bool flag;
	int counter = 1;
	errno_t err;
	SetConsoleCursorPosition(my_consol, { 50, y });
	char delete_name[40];
	for (int i = 0; i < 40; i++) {
		delete_name[i] = NULL;
	}
	Music tracks;
	cout << "Введіть назву редагованої композиції: ";
	cin >> delete_name;
	for (int i = 1; i < nom; i++) {
		err = fopen_s(&music_lib, "music_lib.docx", "r");
		if (err == 0) {
			bool checking = 0;
			fread(&tracks, 1, sizeof(tracks), music_lib);
			int errr = fclose(music_lib);
			flag = checking_arrs(tracks.track, delete_name, 40);
			if (flag) {
				checking = 1;
			}
			else {
				tracks.nomer = counter;
				counter++;
				err = fopen_s(&music_lib, "music_lib2.docx", "a");
				if (err == 0) {
					fwrite(&tracks, 1, sizeof(tracks), music_lib);
					int errr = fclose(music_lib);
				}
				if ((!checking && (i == (check - 1))) || (!checking && check == 1)) {
					SetConsoleCursorPosition(my_consol, { 50, y++ });
					cout << "Композиції з введеним іменем не існує!";
					return 0;
				}
			}
		}

	}
	int asas;
	asas = rename("music_lib.docx", "music_litter.docx");
	asas = rename("music_lib2.docx", "music_lib.docx");
	asas = rename("music_litter.docx", "music_lib2.docx");
	err = fopen_s(&music_lib, "music_lib2.docx", "w");
	if (err == 0) {
		int errr = fclose(music_lib);
	}
	
	return 1;
}
// пошук за роком виходу
void search_year(short& nom) {
	short int year, y = 12, check = nom;
	errno_t err;
	SetConsoleCursorPosition(my_consol, { 50, y });
	cout << "Введіть рік виходу музики, яку бажаєте шукати: ";
	cin >> year;
	Music tracks;
	cout << endl << " Номер треку в списку: ";
	cout << " Назва треку: ";
	cout << " Жанр треку: ";
	cout << " Автор треку: ";
	cout << " Альбом, до якого входить трек: ";
	cout << " Рік виходу треку: ";
	for (int i = 1; i < nom; i++) {
		err = fopen_s(&music_lib, "music_lib.docx", "r");
		if (err == 0) {
			bool checking = 0;
			fread(&tracks, 1, sizeof(tracks), music_lib);
			int errr = fclose(music_lib);
			if (tracks.year == year) {
				checking = 1;
				cout << tracks.nomer;
				cout << "              " << tracks.track;
				cout << "             " << tracks.genre;
				cout << "             " << tracks.autor;
				cout << "                         " << tracks.album;
				cout << "                        " << tracks.year << endl;
			}
			if ((!checking && (i == (check - 1))) || (!checking && check ==1 )){
				SetConsoleCursorPosition(my_consol, { 50, y++ });
				cout << "Композиції з введеним роком виходу не знайдено!";
			}
		}
	}
}
//опційний пошук за іншими параметрами
void search_else(short& nom, int option) {
	short int y = 12, check = nom;
	errno_t err;
	SetConsoleCursorPosition(my_consol, { 50, y });
	Music tracks;
	if (option == 0) {
		bool flag;
		char search_name[40];
		for (int i = 0; i < 40; i++) {
			search_name[i] = NULL;
		}
		cout << "Введіть ім'я композиції для пошуку: ";
		cin >> search_name;
		cout << endl << " Номер треку в списку: ";
		cout << " Назва треку: ";
		cout << " Жанр треку: ";
		cout << " Автор треку: ";
		cout << " Альбом, до якого входить трек: ";
		cout << " Рік виходу треку: ";
		for (int i = 1; i < nom; i++) {
			err = fopen_s(&music_lib, "music_lib.docx", "r");
			if (err == 0) {
				bool checking = 0;
				fread(&tracks, 1, sizeof(tracks), music_lib);
				int errr = fclose(music_lib);
				flag = checking_arrs(tracks.track, search_name, 40);
				if (flag) {
					checking = 1;
					cout << tracks.nomer;
					cout << "              " << tracks.track;
					cout << "             " << tracks.genre;
					cout << "             " << tracks.autor;
					cout << "                         " << tracks.album;
					cout << "                        " << tracks.year << endl;
				}

				if ((!checking && (i == (check - 1))) || (!checking && check == 1)) {
					SetConsoleCursorPosition(my_consol, { 50, y++ });
					cout << "Композиції з введеним іменем не знайдено!";
				}

			}

		}
	}
	if (option == 1) {
		bool flag;
		char search_genre[15];
		for (int i = 0; i < 15; i++) {
			search_genre[i] = NULL;
		}
		cout << "Введіть жанр композиції для пошуку: ";
		cin >> search_genre;
		cout << endl << " Номер треку в списку: ";
		cout << " Назва треку: ";
		cout << " Жанр треку: ";
		cout << " Автор треку: ";
		cout << " Альбом, до якого входить трек: ";
		cout << " Рік виходу треку: ";
		for (int i = 1; i < nom; i++) {
			err = fopen_s(&music_lib, "music_lib.docx", "r");
			if (err == 0) {
				bool checking = 0;
				fread(&tracks, 1, sizeof(tracks), music_lib);
				int errr = fclose(music_lib);
				flag = checking_arrs(tracks.genre, search_genre, 15);
				if (flag) {
					checking = 1;
					cout << tracks.nomer;
					cout << "              " << tracks.track;
					cout << "             " << tracks.genre;
					cout << "             " << tracks.autor;
					cout << "                         " << tracks.album;
					cout << "                        " << tracks.year << endl;
				}

				if ((!checking && (i == (check - 1))) || (!checking && check == 1)) {
					SetConsoleCursorPosition(my_consol, { 50, y++ });
					cout << "Композиції з введеним іменем не знайдено!";
				}
			}
		}
	}
	if (option == 2) {
		bool flag;
		char search_autor[30];
		for (int i = 0; i < 30; i++) {
			search_autor[i] = NULL;
		}
		cout << "Введіть автора композиції для пошуку: ";
		cin >> search_autor;
		cout << endl << " Номер треку в списку: ";
		cout << " Назва треку: ";
		cout << " Жанр треку: ";
		cout << " Автор треку: ";
		cout << " Альбом, до якого входить трек: ";
		cout << " Рік виходу треку: ";
		for (int i = 1; i < nom; i++) {
			err = fopen_s(&music_lib, "music_lib.docx", "r");
			if (err == 0) {
				bool checking = 0;
				fread(&tracks, 1, sizeof(tracks), music_lib);
				int errr = fclose(music_lib);
				flag = checking_arrs(tracks.autor, search_autor, 30);
				if (flag) {
					checking = 1;
					cout << tracks.nomer;
					cout << "              " << tracks.track;
					cout << "             " << tracks.genre;
					cout << "             " << tracks.autor;
					cout << "                         " << tracks.album;
					cout << "                        " << tracks.year << endl;
				}

				if ((!checking && (i == (check - 1))) || (!checking && check == 1)) {
					SetConsoleCursorPosition(my_consol, { 50, y++ });
					cout << "Композиції з введеним автором не знайдено!";
				}
			}
		}
	}
	if (option == 3) {
		bool flag;
		char search_album[20];
		for (int i = 0; i < 20; i++) {
			search_album[i] = NULL;
		}
		cout << "Введіть альбом для пошуку: ";
		cin >> search_album;
		cout << endl << " Номер треку в списку: ";
		cout << " Назва треку: ";
		cout << " Жанр треку: ";
		cout << " Автор треку: ";
		cout << " Альбом, до якого входить трек: ";
		cout << " Рік виходу треку: ";
		for (int i = 1; i < nom; i++) {
			err = fopen_s(&music_lib, "music_lib.docx", "r");
			if (err == 0) {
				bool checking = 0;
				fread(&tracks, 1, sizeof(tracks), music_lib);
				int errr = fclose(music_lib);
				flag = checking_arrs(tracks.album, search_album, 20);
				if (flag) {
					checking = 1;
					cout << tracks.nomer;
					cout << "              " << tracks.track;
					cout << "             " << tracks.genre;
					cout << "             " << tracks.autor;
					cout << "                         " << tracks.album;
					cout << "                        " << tracks.year << endl;
				}

				if ((!checking && (i == (check - 1))) || (!checking && check == 1)) {
					SetConsoleCursorPosition(my_consol, { 50, y++ });
					cout << "Композицій з введеним альбомом не знайдено!";
				}
			}
		}
	}
}
// Видимість курсору
void ConsoleCursorVisible(bool show, short size) {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(my_consol, &structCursorInfo);
	structCursorInfo.bVisible = show; // Зміна видимості курсора
	structCursorInfo.dwSize = size; // Зміна розмірів курсора
}

//Зміна кольору елеиентів меню виводу
void change_colour_print(int active_menu, short x, short y, string Menu[], short menu[]) {
	for (int i = 0; i < 8; i++) {
		if (i == active_menu) {
			if (i > 0 && i < 6) {
				if (menu[i - 1] == 1)
					SetConsoleTextAttribute(my_consol, FOREGROUND_RED | FOREGROUND_INTENSITY);
				else
					SetConsoleTextAttribute(my_consol, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
				SetConsoleTextAttribute(my_consol, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else {
			SetConsoleTextAttribute(my_consol, FOREGROUND_GREEN);
		}
		SetConsoleCursorPosition(my_consol, { x, y++ });
		cout << Menu[i] << endl;
	}
}
void change_colour(int active_menu, short x, short y, string Menu[], int size) {
	for (int i = 0; i < size; i++) {
		if (i == active_menu) {
			SetConsoleTextAttribute(my_consol, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else {
			SetConsoleTextAttribute(my_consol, FOREGROUND_GREEN);
		}
		SetConsoleCursorPosition(my_consol, { x, y++ });
		cout << Menu[i] << endl;
	}
}
/*


	МЕНЮ


*/
//Меню виводу
int menu_print(short& nom) {
	int active_menu = 0;
	char ch;
	SetConsoleCursorPosition(my_consol, { 50, 13 });
	string Menu[] = { "Вивести одразу всі композиції", "Вивести назви композицій", "Вивести всіх виконавців","Вивести всі альбоми", "Вивести жанри музики","Вивести роки виходу композицій","Пошук","Розпочати вивід"};
	short menu_op[] = { 0,0,0,0,0 };
	while (true) {

		ConsoleCursorVisible(false, 100);
		short int x = 50, y = 12;
		SetConsoleCursorPosition(my_consol, { x, y });
		//Зміна кольору елеиентів иеню
		change_colour_print(active_menu, x, y, Menu, menu_op);
		ch = _getch();
		SetConsoleCursorPosition(my_consol, { x, y });
		if (ch == -32)
			ch = _getch();
		switch (ch) {
		case ESC:
			system("CLS");
			menu(nom);
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(Menu) - 1)
				++active_menu;
			break;
		case ENTER:
			switch (active_menu) {
			case 0:
				system("CLS");
				print_music_all(0, nom);
				system("pause");
				system("CLS");
				break;
			case 1:
				if (menu_op[0] == 1)
					menu_op[0] = 0;
				else
					menu_op[0] = 1;
				break;
			case 2:
				if (menu_op[1] == 1)
					menu_op[1] = 0;
				else
					menu_op[1] = 1;
				break;
			case 3:
				if (menu_op[2] == 1)
					menu_op[2] = 0;
				else
					menu_op[2] = 1;
				break;
			case 4:
				if (menu_op[3] == 1)
					menu_op[3] = 0;
				else
					menu_op[3] = 1;
				break;
			case 5:
				if (menu_op[4] == 1)
					menu_op[4] = 0;
				else
					menu_op[4] = 1;
				break;
			case 6:
				system("CLS");
				menu_search(nom);
				system("CLS");
				break;
				
			case 7:
				system("CLS");
				print_music_chunk(menu_op);
				system("pause");
				system("CLS");
				break;
			}
		}
	}
	return 0;
}
//меню редагування
int menu_edit(short& nom, int& zvit_change) {
	int active_menu = 0;
	char ch;
	SetConsoleCursorPosition(my_consol, { 50, 13 });
	string Menu[] = { "Редагувати композицію за номером","Редагувати композицію за назвою" };
	while (true) {

		ConsoleCursorVisible(false, 100);
		short int x = 50, y = 12;
		SetConsoleCursorPosition(my_consol, { x, y });
		//Зміна кольору елеиентів mеню
		change_colour(active_menu, x, y, Menu, 2);
		//*********************************************************
		ch = _getch();
		SetConsoleCursorPosition(my_consol, { x, y });
		if (ch == -32)
			ch = _getch();
		switch (ch) {
		case ESC:
			menu(nom);
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(Menu) - 1)
				++active_menu;
			break;
		case ENTER:
			switch (active_menu) {
			case 0:
				system("CLS");
				zvit_change += edit_music_nomer(nom);
				system("CLS");
				break;
			case 1:
				system("CLS");
				zvit_change += edit_music_name(nom);
				system("CLS");
				break;
			}
		}
	}
}
//меню видалення
int menu_delete(short& nom, int& zvit_deleted) {
	int active_menu = 0;
	char ch;
	SetConsoleCursorPosition(my_consol, { 50, 13 });
	string Menu[] = { "Видалити композицію за номером","Видалити композицію за назвою" };
	while (true) {

		ConsoleCursorVisible(false, 100);
		short int x = 50, y = 12;
		SetConsoleCursorPosition(my_consol, { x, y });
		//Зміна кольору елеиентів mеню
		change_colour(active_menu, x, y, Menu, 2);
		//*********************************************************
		ch = _getch();
		SetConsoleCursorPosition(my_consol, { x, y });
		if (ch == -32)
			ch = _getch();
		switch (ch) {
		case ESC:
			menu(nom);
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(Menu) - 1)
				++active_menu;
			break;
		case ENTER:
			switch (active_menu) {
			case 0:
				system("CLS");
				zvit_deleted += delete_music_nomer(nom);
				system("CLS");
				break;
			case 1:
				system("CLS");
				zvit_deleted += delete_music_name(nom);
				system("CLS");
				break;
			}
		}
	}
}
//меню пошуку
int menu_search(short& nom) {
	int active_menu = 0;
	char ch;
	SetConsoleCursorPosition(my_consol, { 50, 13 });
	string Menu[] = { "Пошук композиції за назвою","Пошук композиції за жанром", "Пошук композиції за автором", "Пошук композиції за альбомом", "Пошук композиції за роком випуску"};
	while (true) {

		ConsoleCursorVisible(false, 100);
		short int x = 50, y = 12;
		SetConsoleCursorPosition(my_consol, { x, y });
		//Зміна кольору елеиентів mеню
		change_colour(active_menu, x, y, Menu, 5);
		//*********************************************************
		ch = _getch();
		SetConsoleCursorPosition(my_consol, { x, y });
		if (ch == -32)
			ch = _getch();
		switch (ch) {
		case ESC:
			system("CLS");
			menu_print(nom);
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(Menu) - 1)
				++active_menu;
			break;
		case ENTER:
			switch (active_menu) {
			case 0:
				system("CLS");
				search_else(nom, 0);
				system("pause");
				system("CLS");
				break;
			case 1:
				system("CLS");
				search_else(nom, 1);
				system("pause");
				system("CLS");
				break; 
			case 2:
				system("CLS");
				search_else(nom, 2);
				system("pause");
				system("CLS");
				break;
			case 3:
				system("CLS");
				search_else(nom, 3);
				system("pause");
				system("CLS");
				break;
			case 4:
				system("CLS");
				search_year(nom);
				system("pause");
				system("CLS");
				break;
			}
		}
	}
}
// Основне меню
int menu(short& nom) {
	int active_menu = 0, zvit_add = 0, zvit_change = 0, zvit_deleted = 0;
	char ch;
	SetConsoleCursorPosition(my_consol, { 50, 13 });
	string Menu[] = { "Додати композицію", "Редагувати записану композицію","Вилучити записану композицію", "Вивести записані композиції","Надати підсумковий звіт та вийти" };
	while (true) {
		ConsoleCursorVisible(false, 100);
		short int x = 50, y = 12;
		SetConsoleCursorPosition(my_consol, { x, y });
		//Зміна кольору елеиентів иеню
		for (int i = 0; i < 5; i++) {
			if (i == active_menu) {
				SetConsoleTextAttribute(my_consol, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			}
			else {
				SetConsoleTextAttribute(my_consol, FOREGROUND_BLUE);
			}
			SetConsoleCursorPosition(my_consol, { x, y++ });
			cout << Menu[i] << endl;
		}
		//***************************************************
		ch = _getch();
		SetConsoleCursorPosition(my_consol, { x, y });
		if (ch == -32)
			ch = _getch();
		switch (ch) {
		case ESC:
			system("CLS");
			exit(0);
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(Menu) - 1)
				++active_menu;
			break;
		case ENTER:
			switch (active_menu) {
			case 0:
				system("CLS");
				add_music(nom, zvit_add);
				system("CLS");
				break;
			case 1:
				system("CLS");
				menu_edit(nom, zvit_change);
				system("CLS");
				break;
			case 2:
				system("CLS");
				menu_delete(nom, zvit_deleted);
				system("CLS");
				break;
			case 3:
				system("CLS");
				menu_print(nom);
				system("CLS");
				break;
			case 4:
				system("CLS");
				SetConsoleCursorPosition(my_consol, { 0, y });
				cout << "Додано " << zvit_add << " музикальних композицій, відредаговано " << zvit_change
					<< " музикальних композицій, видалено " << zvit_deleted << " музикальних композицій." << endl;
				system("pause");
				exit(0);
			}
		}
	}

	return 0;
}

