#include "iostream"
#include <string>
#include <sstream>

using namespace std;

struct Node {
	int value;
	Node* next;
	Node* prev;
};

Node* createNode(int value) {
	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = nullptr;
	newNode->prev = nullptr;
	return newNode;
}

void addToFront(Node*& head, Node*& tail, int value) {
	Node* newNode = createNode(value);
	if (head == nullptr) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void addToBack(Node*& head, Node*& tail, int value) {
	Node* newNode = createNode(value);
	if (tail == nullptr) {
		head = tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
}

void printList(Node* head) {
	Node* current = head;
	while (current != nullptr) {
		cout << current->value << " ";
		current = current->next;
	}
	cout << endl;
}

void deleteList(Node*& head, Node*& tail) {
	Node* current = head;
	while (current != nullptr) {
		Node* temp = current;
		current = current->next;
		delete temp;
	}
	head = tail = nullptr;
}

int* createArray(int size) {
	return new int[size];
}

void deleteArray(int* arr) {
	delete[] arr;
}

void printArray(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

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


