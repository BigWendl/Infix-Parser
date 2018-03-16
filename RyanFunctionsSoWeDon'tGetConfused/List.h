#ifndef NODE_H_
#define NODE_H_

struct List {
	int data;
	List* next;

	List(const int& data_item, List* next_ptr = NULL) :
		data(data_item), next(next_ptr) {}
};
#endif
