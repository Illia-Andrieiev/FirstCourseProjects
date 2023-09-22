#include<iostream>
#define N 10
typedef struct graf {
	int nomer = 0;
	graf* next = NULL;
}node, *pnode;
typedef struct turn {
	int vertex = 0;
	int nomer = 0;
	turn* next = NULL;
}turn, * pturn;

int find_min_length(pnode graff[N], int nomer1, int nomer2) {
	int length = -1;
	bool flags[N];
	for (int i = 0; i < N; i++)
		flags[i] = 1;
	flags[nomer1] = 0;
	pturn head_turn = new turn;
	head_turn->vertex = nomer1;
	pturn end_turn = head_turn;
	while (head_turn) {
		pnode step_graf = graff[head_turn->vertex];
		while (step_graf) {
			if (step_graf->nomer == nomer2) {
				length = head_turn->nomer + 1;
				while (head_turn) {
					pturn step = head_turn->next;
					delete head_turn;
					head_turn = step;
				}
				break;
			}
			else {
				if (flags[step_graf->nomer]) {
					pturn new_elem = new turn;
					new_elem->vertex = step_graf->nomer;
					new_elem->nomer = head_turn->nomer + 1;
					end_turn->next = new_elem;
					end_turn = end_turn->next;
					flags[step_graf->nomer] = 0;
				}
			}
			step_graf = step_graf->next;
		}
		pturn step = head_turn->next;
		delete head_turn;
		head_turn = step;
	}
	return length;
}