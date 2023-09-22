#include <iostream>
#include <math.h>
typedef struct list {
	int data;
	list* next;
}list, *plist;
// максимальна довжина числа із списку
int max_nombers(plist list) {
	int max_nombers = 0;
	plist head = list;
	while (head) {
		int step = lenght_nomber(head->data);
		if (step > max_nombers)
			max_nombers = step;
		head = head->next;
	}
	return max_nombers;
}
//довжина числа
int lenght_nomber(int nomber) {
	int step = 0;
	while (nomber) {
		nomber /= 10;
		step++;
	}
	return step;
}
//видалення списку
void delete_list(plist start) {
	plist step = start;
	while (start) {
		start = start->next;
		delete step;
		step = start;
	}
}
//злиття масиву списків
plist merge_arr(plist arr[11]){
	plist step = arr[0],head = arr[0];
	for (int i = 1; i < 11; i++) {
		while (step->next) {
			step = step->next;
		}
		step->next = arr[i];
	}
	return head;
}

plist sort(plist sorting_list) {
	int max_nomber = max_nombers(sorting_list);
	for (int i = max_nomber; i > 0; i--) {
		plist arr[11];
		for (int i = 0; i < 11; i++)
			arr[i] = NULL;
		plist head = sorting_list;
		while (head) {
			int length = lenght_nomber(head->data);
			if (length >= i) {
				int checking_nomber;
				float degree1 = powf(10, i), degree2 = powf(10, i - 1);
				checking_nomber = head->data % (int)degree1;
				checking_nomber /= (int)degree2;
				plist node = new list;
				node->data = head->data;
				node->next = arr[checking_nomber + 1];
				arr[checking_nomber + 1] = node;
			}
			else {
				plist node = new list;
				node->data = head->data;
				node->next = arr[0];
				arr[0] = node;
			}
		}
		delete_list(sorting_list);
		sorting_list = merge_arr(arr);
	}
	return sorting_list;
}