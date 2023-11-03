#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

// Custom Exception Classes
class InvalidKeyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid key. Key must be a non-negative integer.";
    }
};

class KeyNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Key not found in the tree.";
    }
};

template <typename T>
class QuartenarySearchTree {
private:
    struct Node {
        T data;
        int key;
        Node* children[4];
        Node(T _data, int _key) : data(_data), key(_key) {
            for (int i = 0; i < 4; ++i) {
                children[i] = nullptr;
            }
        }
    };

    Node* root;

    // Helper function for inserting a new element
    void insertHelper(Node* &node, const T& data, int key) {
        if (node == nullptr) {
            node = new Node(data, key);
        } else if (key < node->key) {
            insertHelper(node->children[0], data, key);
        } else if (key < 2 * node->key) {
            insertHelper(node->children[1], data, key);
        } else if (key < 3 * node->key) {
            insertHelper(node->children[2], data, key);
        } else {
            insertHelper(node->children[3], data, key);
        }
    }

    // Helper function to print elements in preorder
    void preorderHelper(Node* node) {
        if (node != nullptr) {
            std::cout << node->data << " ";
            for (int i = 0; i < 4; ++i) {
                preorderHelper(node->children[i]);
            }
        }
    }

    // Helper function for deleting a specific key
    Node* deleteHelper(Node* node, int key) {
        if (node == nullptr) {
            throw KeyNotFoundException();
        }
        if (key < node->key) {
            node->children[0] = deleteHelper(node->children[0], key);
        } else if (key < 2 * node->key) {
            node->children[1] = deleteHelper(node->children[1], key);
        } else if (key < 3 * node->key) {
            node->children[2] = deleteHelper(node->children[2], key);
        } else if (key == node->key) {
            // Found the node to delete
            if (node->children[0] == nullptr && node->children[1] == nullptr &&
                node->children[2] == nullptr && node->children[3] == nullptr) {
                // Node has no children
                delete node;
                return nullptr;
            } else {
                throw std::runtime_error("Cannot delete a node with children.");
            }
        } else {
            node->children[3] = deleteHelper(node->children[3], key);
        }
        return node;
    }

public:
    QuartenarySearchTree() : root(nullptr) {}

    // Function to insert an element
    void insert(const T& data) {
        int key = data.getKey();
        if (key < 0) {
            throw InvalidKeyException();
        }
        insertHelper(root, data, key);
    }

    // Function to delete an element with a specific key
    void deleteKey(int key) {
        root = deleteHelper(root, key);
    }

    // Function to print elements in preorder
    void printPreorder() {
        preorderHelper(root);
        std::cout << std::endl;
    }
};

class Book {
public:
    Book(std::string _title, int _key) : title(_title), key(_key) {}

    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << "Book: " << book.title;
        return os;
    }

    int getKey() const {
        return key;
    }

private:
    std::string title;
    int key;
};

class Person {
public:
    Person(std::string _name, int _key) : name(_name), key(_key) {}

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "Person: " << person.name;
        return os;
    }

    int getKey() const {
        return key;
    }

private:
    std::string name;
    int key;
};

int main() {
    try {
        QuartenarySearchTree<Book> bookTree;
        QuartenarySearchTree<Person> personTree;

        int choice;
        while (true) {
            std::cout << "Menu:\n";
            std::cout << "1. Insert Book\n";
            std::cout << "2. Insert Person\n";
            std::cout << "3. Delete Book\n";
            std::cout << "4. Delete Person\n";
            std::cout << "5. Print Book Tree (Preorder)\n";
            std::cout << "6. Print Person Tree (Preorder)\n";
            std::cout << "7. Quit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    try {
                        std::string title;
                        int key;
                        std::cout << "Enter Book title: ";
                        std::cin.ignore();
                        std::getline(std::cin, title);
                        std::cout << "Enter key: ";
                        std::cin >> key;
                        assert(key >= 0);
                        bookTree.insert(Book(title, key));
                    } catch (const InvalidKeyException& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    break;
                case 2:
                    try {
                        std::string name;
                        int key;
                        std::cout << "Enter Person name: ";
                        std::cin.ignore();
                        std::getline(std::cin, name);
                        std::cout << "Enter key: ";
                        std::cin >> key;
                        assert(key >= 0);
                        personTree.insert(Person(name, key));
                    } catch (const InvalidKeyException& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    break;
                case 3:
                    try {
                        int key;
                        std::cout << "Enter key to delete Book: ";
                        std::cin >> key;
                        bookTree.deleteKey(key);
                    } catch (const KeyNotFoundException& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    break;
                case 4:
                    try {
                        int key;
                        std::cout << "Enter key to delete Person: ";
                        std::cin >> key;
                        personTree.deleteKey(key);
                    } catch (const KeyNotFoundException& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                    break;
                case 5:
                    std::cout << "Book Tree (Preorder): ";
                    bookTree.printPreorder();
                    break;
                case 6:
                    std::cout << "Person Tree (Preorder): ";
                    personTree.printPreorder();
                    break;
                case 7:
                    return 0;
                default:
                    std::cout << "Invalid choice. Try again.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
