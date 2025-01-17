﻿#include <iostream>
#include <stdexcept>
#include <iterator>
#include <queue>

class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Ошибка: операция с пустым деревом или некорректным элементом!";
    }
};

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insertNode(Node*& current, const T& value) {
        if (!current) {
            current = new Node(value);
        }
        else if (value < current->data) {
            insertNode(current->left, value);
        }
        else if (value > current->data) {
            insertNode(current->right, value);
        }
    }

    bool searchNode(const Node* current, const T& value) const {
        if (!current) return false;
        if (current->data == value) return true;
        if (value < current->data) {
            return searchNode(current->left, value);
        }
        else {
            return searchNode(current->right, value);
        }
    }

    void inorderTraversal(const Node* current) const {
        if (!current) return;
        inorderTraversal(current->left);
        std::cout << current->data << " ";
        inorderTraversal(current->right);
    }

    void preorderTraversal(const Node* current) const {
        if (!current) return;
        std::cout << current->data << " ";
        preorderTraversal(current->left);
        preorderTraversal(current->right);
    }

    void postorderTraversal(const Node* current) const {
        if (!current) return;
        postorderTraversal(current->left);
        postorderTraversal(current->right);
        std::cout << current->data << " ";
    }

    void deleteTree(Node* current) {
        if (!current) return;
        deleteTree(current->left);
        deleteTree(current->right);
        delete current;
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        deleteTree(root);
    }

    void insert(const T& value) {
        insertNode(root, value);
    }

    bool search(const T& value) const {
        return searchNode(root, value);
    }

    void inorder() const {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void preorder() const {
        preorderTraversal(root);
        std::cout << std::endl;
    }

    void postorder() const {
        postorderTraversal(root);
        std::cout << std::endl;
    }

    class PositiveIterator : public std::iterator<std::input_iterator_tag, T> {
    private:
        std::queue<Node*> nodes;
    public:
        PositiveIterator(Node* start) {
            if (start) {
                std::queue<Node*> q;
                q.push(start);
                while (!q.empty()) {
                    Node* current = q.front();
                    q.pop();
                    if (current->data > 0) {
                        nodes.push(current);
                    }
                    if (current->left) q.push(current->left);
                    if (current->right) q.push(current->right);
                }
            }
        }

        PositiveIterator& operator++() {
            nodes.pop();
            return *this;
        }

        T& operator*() {
            if (nodes.empty()) throw CustomException();
            return nodes.front()->data;
        }

        bool operator!=(const PositiveIterator& other) const {
            return !nodes.empty();
        }
    };

    class NegativeIterator : public std::iterator<std::input_iterator_tag, T> {
    private:
        std::queue<Node*> nodes;
    public:
        NegativeIterator(Node* start) {
            if (start) {
                std::queue<Node*> q;
                q.push(start);
                while (!q.empty()) {
                    Node* current = q.front();
                    q.pop();
                    if (current->data < 0) {
                        nodes.push(current);
                    }
                    if (current->left) q.push(current->left);
                    if (current->right) q.push(current->right);
                }
            }
        }

        NegativeIterator& operator++() {
            nodes.pop();
            return *this;
        }

        T& operator*() {
            if (nodes.empty()) throw CustomException();
            return nodes.front()->data;
        }

        bool operator!=(const NegativeIterator& other) const {
            return !nodes.empty();
        }
    };

    PositiveIterator beginPositive() {
        return PositiveIterator(root);
    }

    PositiveIterator endPositive() {
        return PositiveIterator(nullptr);
    }

    NegativeIterator beginNegative() {
        return NegativeIterator(root);
    }

    NegativeIterator endNegative() {
        return NegativeIterator(nullptr);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    BinaryTree<int> tree;

    tree.insert(10);
    tree.insert(-5);
    tree.insert(15);
    tree.insert(-3);
    tree.insert(7);

    std::cout << "Положительные элементы: ";
    for (auto it = tree.beginPositive(); it != tree.endPositive(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Отрицательные элементы: ";
    for (auto it = tree.beginNegative(); it != tree.endNegative(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Поиск числа 7: " << (tree.search(7) ? "Найдено" : "Не найдено") << std::endl;
    std::cout << "Поиск числа 12: " << (tree.search(12) ? "Найдено" : "Не найдено") << std::endl;

    return 0;
}
