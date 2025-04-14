// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(const char a) {
	switch (a) {
	case '(':
		return 0;
	case ')':
		return 1;
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	default:
		return -1;
	}
}

int calculate(double a, double b, char op) {
	switch (op) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return -1;
	}
}

std::string infx2pstfx(const std::string& inf) {
	string post;
	TStack<char> stack;
	bool needSpace = false;
	for (int i = 0; i < inf.size(); i++){
		char current = inf[i];
		int currentPrior = prior(current);
		if (currentPrior == -1) {
			if (needSpace){
				post += ' ';
			}
			post += current;
			needSpace = false;
		}
		else if (current == '(') {
			stack.push(current);
			needSpace = false;
		}
		else if (current == ')') {
			while (!stack.isEmpty() && stack.get() != '(') {
				post += ' ';
				post += stack.get();
				stack.pop();
			}
			stack.pop();
			needSpace = true;
		} else {
            while (!stack.empty() &&
                  prior(stack.top()) >= currentPrior &&
                  stack.top() != '(') {
                post += ' ';
                post += stack.top();
                stack.pop();
            }
            post += ' ';
            stack.push(current);
            needSpace = false;
        }
    }

    while (!stack.empty()) {
        post += ' ';
        post += stack.top();
        stack.pop();
    }

    return post;
}

int eval(const std::string& pref) {
	TStack<int> stack;
	int num = 0;
	bool readingNum = false;
	bool negative = false;

	for (char c : pref) {
		if (c == ' ') {
			if (readingNum) {
				stack.push(negative ? -num : num);
				num = 0;
				readingNum = false;
				negative = false;
			}
			continue;
		}

		if (isdigit(c)) {
			num = num * 10 + (c - '0');
			readingNum = true;
		}
		else if (c == '-' && !readingNum) {
			negative = true;
		}
		else {
			int b = stack.get();
			stack.pop();
			int a = stack.get();
			stack.pop();
			stack.push(calculate(a, b, c));
		}
	}

	if (readingNum) {
		stack.push(negative ? -num : num);
	}

	return stack.get();
}
