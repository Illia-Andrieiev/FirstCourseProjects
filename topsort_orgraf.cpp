#include <iostream>
typedef struct graf_node {
	int nomer = 0;
	graf_node* next = 0;
}vertex, *pvertex;

// ������������ ����������. ������� 1 ���� ���� �� �� ����� 0,���� �� � ���������� ���������
bool orgraf_topsort(pvertex* graf, int nomer_vertex) {
	int* index = new int[nomer_vertex]; // ³������ �� ���� ������� � ��������� �������. 0-���, 1-���, 2-�����.
	int* stec = new int[nomer_vertex]; // ���� � �������� ������ 
	int stec_position = 0;
	for (int i = 0; i < nomer_vertex; i++)
		index[i] = 0; // ���� ��� ������ ����
	for (int i = 0; i < nomer_vertex; i++) {
		bool res = step_of_sort(graf, nomer_vertex, stec,i, index, stec_position); // ����������� �������� ��� ��� ������
		if (!res) {
			delete[] index;
			delete[] stec;
			return 0;
		}
	} 
	// ��������� �������� �� ���������� �����. ��� ���������� ��������� ��������� � �������� ��������
	// ������� ������ ����� �������� �� �����, � ������ ��� ������ � �����.
	for (int i = 0; i < nomer_vertex; i++) {
		pvertex step = graf[i];
		while (step) {
			step->nomer = find_position_end_value_in_arr(stec, nomer_vertex, step->nomer);
			step = step->next;
		}
	}
	pvertex* copy_graf_raws;
	for (int i = 0; i < nomer_vertex; i++) // ��������� ����� ����� � ����������� �������
		copy_graf_raws[i] = graf[stec[nomer_vertex -1 - i]];
	for (int i = 0; i < nomer_vertex; i++) // ��������� ����� ����� � ����������� �������
		graf[i] = copy_graf_raws[i];
	delete[] index;
	delete[] stec;
	return 1;
}
// ������� 0 ���� ���� �� ����. ��������� ���� ���������� ��� �������
bool step_of_sort(pvertex* graf, int nomer_vertex, int* stec, int current_vertex, int* index, int& stec_position) {
	if (index[current_vertex] == 1) // ������� ��� - ���� ����
		return 0;
	if(index[current_vertex] == 2) // ������� ����� - ����� �� ������
		return 1; 
	else {
		index[current_vertex] = 1; // ������� ������� � ����
		pvertex step = graf[current_vertex];
		while (step) { // ����������� �������� ��� ����� � ������, � �� ������ ����
			bool res = step_of_sort(graf, nomer_vertex, stec, step->nomer, index, stec_position);
			if (!res)
				return 0; // ���� ����
			else
				step = step->next;
		}
		index[current_vertex] = 2; // ������� � ������
		stec[stec_position] = current_vertex; // ��������� ������� � ����
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