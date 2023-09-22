#include <iostream>
typedef struct stec {
	short current = 0; // ³������ �� �-�� ����� �� ����, �� �����������
	bool checked = false;
	char a = '0';
	char b = '0';
	char c = '0';
	stec* previous = NULL;
}stec, *pstec;

long long int hanoi_iteratios(int n);
void hanoi_iterations_with_moves(int n);
void print_move(char first, char second, long long int &step);
pstec delete_from_stec(pstec step);
pstec create_turn_elem(char a, char b, char c, short curr);
void add_elem_to_stec(pstec elem, pstec previous);

int main() {
	int n;
	std::cout << "enter nomber of plates" << std::endl;
	std::cin >> n;
	long long int res = hanoi_iteratios(n);
	return 0;
}

// ������� �������� ������� � �����
pstec delete_from_stec(pstec head) {
	pstec step = head->previous;
	delete head;
	return step;
}
// ������� ������� �����
pstec create_turn_elem(char a, char b, char c, short curr) {
	pstec centre = new stec;
	centre->current = curr;
	centre->a = a;
	centre->b = b;
	centre->c = c;
	return centre;
}
// ���� ������� �� �����
void add_elem_to_stec(pstec elem, pstec previous) {
	elem->previous = previous;
}
// �������� ���� ������������ �����
void print_move(char first, char second, long long int &step) {
	std::cout << "step " << step << ":" << " from pivot " << first << " on pivot " << second << std::endl;
	step++;
}
// �-��������� �������, �-������, �- ��������. �������� �� ����� ��� ���������� ������ ����������
void hanoi_iterations_with_moves(int n) {
	char a = 'A', b = 'B', c = 'C';
	long long int step = 1;
	pstec centre = create_turn_elem(a, b, c, n);
	while (centre) {
		if (centre->current == 1) { // ���� ������ �� 1 ������ ������ ������������ �� ��������� �� � ����������� ������ �� �����
			print_move(centre->a, centre->b, step);
			centre = delete_from_stec(centre);
		}
		else {
			if (centre->checked == false) { // ���� ����� �� �����������, �� ������ �� ����� "����" ������, ������� ������ � ��������� �������� "����" 
				pstec tail = create_turn_elem(centre->a, centre->c, centre->b, centre->current - 1);
				add_elem_to_stec(tail, centre);
				centre->checked = true;
				centre = tail;
			}
			else { // ���� ����� �����������, �� ������ �� ����� "������" ������, ��������� �������� ����. � ��������� �������� "������" 
				print_move(centre->a, centre->b, step);
				pstec head = create_turn_elem(centre->c, centre->b, centre->a, centre->current - 1);
				add_elem_to_stec(head, centre->previous);
				centre->previous = head;
				centre = delete_from_stec(centre);
			}
		}
	}
}
// �������� �-�� ������������ � ������ ��� �������� ����� �� �������� �����
long long int hanoi_iteratios(int n) {
	long long int res = 0;
	for (int i = 0; i < n; i++) {
		res = res * 2 + 1;
		std::cout << res << " moves for " << i + 1 << " plates" << std::endl;
	}
	hanoi_iterations_with_moves(n);
	return res;
}