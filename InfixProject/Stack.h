	class Stack {
	private:
#include "List.h"
		List* topOfStack;
		size_t num_items;

	public:

		void push(const int& item) {
			topOfStack = new List(item, topOfStack);
			++num_items;
		}


		int& top() {
			return topOfStack->data;
		}

		const int& top() const {
			return topOfStack->data;
		}

		void pop() {
			if (!empty()) {
				List* old_top = topOfStack;
				topOfStack = topOfStack->next;
				delete old_top;

				--num_items;
			}
		}

		bool empty() const {
			return topOfStack == nullptr;
		}

		size_t size() {
			return num_items;
		}

	};