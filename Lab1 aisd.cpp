#include "iostream"
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
	Node* next;
	Node* prev;
	int value;
public:
	Node(int data) {
		next = prev = nullptr;
		this->value = data;
	}
	Node() {
		next = prev = nullptr;
		value = 0;
	}
};


class LinkedList {
public:
	Node* head;
	Node* tail;
	int size;
public:
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	~LinkedList() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void appendFirstInd(int value) {
		size++;
		Node* temp = new Node(value);
		if (head == nullptr) {
			head = tail = temp;
		}
		else {
			temp->next = head;
			head->prev = temp;
			head = temp;
		}
	}

	void appendLastInd(int value) {
		size++;
		Node* temp = new Node(value);
		if (tail == nullptr) {
			head = tail = temp;
		}
		else {
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
	}

	void append(int index, int value) {
		Node* temp = new Node(value);
		while (index > size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}

		if (index == size) {
			delete temp;
			appendLastInd(value);
			return;
		}
		if (!index) {
			delete temp;
			appendFirstInd(value);
			return;
		}
		if (size / 2 > index) {
			Node* curr = head;
			for (int i = 0; i < index - 1; i++) {
				curr = curr->next;
			}
			temp->prev = curr;
			temp->next = curr->next;
			curr->next->prev = temp;
			curr->next = temp;
		}
		else {
			Node* curr = tail;
			for (int i = 0; i < size - index - 1; i++) {
				curr = curr->prev;
			}
			curr->prev->next = temp;
			temp->next = curr;
			temp->prev = curr->prev;
			curr->prev = temp;
		}
		size++;
	}

	void showList() {
		Node* temp = head;
		while (temp) {
			cout << temp->value << " ";
			temp = temp->next;
		}
	}

	Node* findElement(int index) {
		while (index >= size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}
		Node* temp = head;
		while (index--) {
			temp = temp->next;
		}
		return temp;
	}

	void remove(int index) {
		while (index >= size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}
		if (!index) {
			Node* temp = head->next;
			if (temp == nullptr) {
				tail = nullptr;
			}
			else {
				temp->prev = nullptr;
			}
			delete head;
			head = temp;
		}
		else {
			Node* prev = findElement(index - 1);
			Node* temp = prev->next;
			prev->next = temp->next;
			if (temp->next != nullptr) {
				temp->next->prev = prev;
				delete temp;
			}
			else {
				tail = prev;
				delete temp;
			}
		}
		size--;
	}

};

class DynamicArray {
public:
	int* data;
	int size;
	int capacity;

public:
	DynamicArray(int capacity) {
		this->capacity = capacity;
		data = new int[capacity];
		this->size = 0;
	}
	~DynamicArray() {
		delete[] data;
	}
	void resize(int newSize) {
		int* temp = new int[newSize];
		for (int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		for (int i = size; i < newSize; i++) {
			temp[i] = 0;
		}
		this->size = newSize;
		this->capacity = newSize;
		delete[] data;
		this->data = temp;
	}

	void reverse() {
		int* temp = new int[capacity * 2];
		for (int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		this->capacity *= 2;
		this->data = temp;
	}

	void reverse(int capacity) {
		int* temp = new int[capacity];
		for (int i = 0; i < size; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		this->capacity = capacity;
		this->data = temp;
	}


	void remove(int index) {
		while (index >= size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}
		for (int i = index; i < size - 1; i++) {
			data[i] = data[i + 1];
		}
		size--;
	}

	void insert(int index, int value) {
		while (index > size || index < 0) {
			cout << "Индекс либо больше размера массива, либо меньше нуля, попробуйте снова: ";
			cin >> index;
		}
		if (size == capacity) {
			reverse();
		}
		for (int i = size; i > index; i--) {
			data[i] = data[i - 1];
		}
		data[index] = value;
		size++;

	}

	int& operator[](int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Индекс либо больше размера массива, либо меньше нуля");
		}
		return data[index];
	}
};

template <typename T>
class StackNode {
public:
	T value;
	StackNode<T>* next = nullptr;
public:
	StackNode(T value) {
		this->value = value;
	}
};

template <typename T>
class Stack {
public:
	StackNode<T>* top;

public:
	Stack<T>() {
		top = nullptr;
	}
	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}
	void push(T value) {
		StackNode<T>* temp = new StackNode<T>(value);
		temp->next = top;
		top = temp;
	}

	void pop() {
		if (!isEmpty()) {
			StackNode<T>* temp = top;
			temp = top->next;
			delete top;
			top = temp;
		}
		else {
			cout << "Стэк и так пуст";
			return;
		}
	}

	bool isEmpty() {
		return (top == nullptr);
	}

	T get() {
		if (!isEmpty()) {
			return top->value;
		}
		else {
			cout << "Стэк пуст";
			return T();
		}
	}

	int size() {
		StackNode<T>* cur = top;
		int count(0);
		while (cur) {
			cur = cur->next;
			count++;
		}
		return count;
	}

};

int getPriority(string operation) {
	if (operation == "+" || operation == "-")
		return 1;
	if (operation == "*" || operation == "/")
		return 2;
	if (operation == "^")
		return 3;
	if (operation == "sin" || operation == "cos")
		return 4;
	return 0;
}

bool isRightAssociative(string operation) {
	return operation == "^";
}

bool isOperation(string str) {
	return str == "+" || str == "-" || str == "*" || str == "/" || str == "^";
}

bool isFunction(string str) {
	return str == "sin" || str == "cos";
}

string marshallingYarD(string expression) {
	Stack<string> stack;
	string output = "";
	string receivedChar;

	stringstream ss(expression);
	while (ss >> receivedChar)
	{
		if (isdigit(receivedChar[0])) {
			output += receivedChar + " ";
		}
		else if (isFunction(receivedChar)) {
			stack.push(receivedChar);
		}
		else if (isOperation(receivedChar))
		{
			while (!stack.isEmpty() &&
				(isOperation(stack.get()) || isFunction(stack.get())) &&
				(getPriority(stack.get()) > getPriority(receivedChar) ||
					(getPriority(stack.get()) == getPriority(receivedChar) && !isRightAssociative(receivedChar)))) {
				output += (stack.get()) + " ";
				stack.pop();
			}
			stack.push(receivedChar);
		}
		else if (receivedChar == "(") {
			stack.push(receivedChar);
		}
		else if (receivedChar == ")") {
			while (!stack.isEmpty() && stack.get() != "(") {
				output += stack.get() + " ";
				stack.pop();
			}
			stack.pop();
			if (!stack.isEmpty() && isFunction(stack.get())) {
				output += stack.get() + " ";
				stack.pop();
			}
		}
	}
	while (!stack.isEmpty()) {
		output += stack.get() + " ";
		stack.pop();
	}
	return output;
}

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите выражение (через пробел)" << endl;
	string expression;
	getline(cin, expression);

	string reversePolNotation = marshallingYarD(expression);
	cout << "Обратная польская нотация: " << reversePolNotation << endl;
}

