#include <iostream>
typedef struct graf_node {
	int nomer = 0;
	graf_node* next = 0;
}vertex, *pvertex;

// Топографічне сортування. Повертає 1 якщо граф не має циклу 0,якщо має і сортування неможливе
bool orgraf_topsort(pvertex* graf, int nomer_vertex) {
	int* index = new int[nomer_vertex]; // Відповідає за стан вершини з відповідним номером. 0-біла, 1-сіра, 2-чорна.
	int* stec = new int[nomer_vertex]; // Стек з нумерами вершин 
	int stec_position = 0;
	for (int i = 0; i < nomer_vertex; i++)
		index[i] = 0; // колір всіх вершин білий
	for (int i = 0; i < nomer_vertex; i++) {
		bool res = step_of_sort(graf, nomer_vertex, stec,i, index, stec_position); // застосовуємо алгоритм для всіх вершин
		if (!res) {
			delete[] index;
			delete[] stec;
			return 0;
		}
	} 
	// Нумерація відповідно до утвореного стеку. Для проведення нумерації необхідно у структурі суміжності
	// поміняти місцями рядки відповідно до стеку, і нумера всіх вершин у ньому.
	for (int i = 0; i < nomer_vertex; i++) {
		pvertex step = graf[i];
		while (step) {
			step->nomer = find_position_end_value_in_arr(stec, nomer_vertex, step->nomer);
			step = step->next;
		}
	}
	pvertex* copy_graf_raws;
	for (int i = 0; i < nomer_vertex; i++) // Копіювання рядків графа у необхідному порядку
		copy_graf_raws[i] = graf[stec[nomer_vertex -1 - i]];
	for (int i = 0; i < nomer_vertex; i++) // Присвоєння рядків графу у необхідному порядку
		graf[i] = copy_graf_raws[i];
	delete[] index;
	delete[] stec;
	return 1;
}
// повертає 0 якщо граф має цикл. проводить крок сортування для вершини
bool step_of_sort(pvertex* graf, int nomer_vertex, int* stec, int current_vertex, int* index, int& stec_position) {
	if (index[current_vertex] == 1) // Вершина сіра - існує цикл
		return 0;
	if(index[current_vertex] == 2) // Вершина чорна - нічого не робимо
		return 1; 
	else {
		index[current_vertex] = 1; // Фарбуємо вершину в сірий
		pvertex step = graf[current_vertex];
		while (step) { // Застосовуємо алгоритм для кожної з вершин, у які ведуть дуги
			bool res = step_of_sort(graf, nomer_vertex, stec, step->nomer, index, stec_position);
			if (!res)
				return 0; // існує цикл
			else
				step = step->next;
		}
		index[current_vertex] = 2; // Фарбуємо в чорний
		stec[stec_position] = current_vertex; // Покладаємо вершину в стек
		++stec_position;
		return 1;
	}
}
int find_position_end_value_in_arr(int* arr, int length, int value) {
	for (int i = length - 1; i >= 0; i--) {
		if (arr[i] == value)
			return length - i - 1;
	}
	return -1;
}