// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int kStackSize>
class TStack {
 private:
    T arr[kStackSize];
    int top;
 public:
    TStack() :top(-1) {}
    T get() const {
        return arr[top];
    }
    bool isEmpty() const {
        return top == -1;
    }
    bool isFull() const {
        return top == kStackSize - 1;
    }
    void pop() {
        if (top >= 0)
            top--;
    }
    void push(T item) {
        if (top < kStackSize - 1)
            arr[++top] = item;
    }
};

#endif  // INCLUDE_TSTACK_H_
