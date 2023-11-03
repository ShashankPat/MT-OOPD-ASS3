int main() {
    QuaternarySearchTree<std::string, Person> personTree;  // For persons
    QuaternarySearchTree<std::string, Book> bookTree;  // For books

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Insert a Person" << std::endl;
        std::cout << "2. Insert a Book" << std::endl;
        std::cout << "3. Delete a Person" << std::endl;
        std::cout << "4. Delete a Book" << std::endl;
        std::cout << "5. Preorder traversal for Persons" << std::endl;
        std::cout << "6. Preorder traversal for Books" << std::endl;
        std::cout << "7. Postorder traversal for Persons" << std::endl;
        std::cout << "8. Postorder traversal for Books" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        try {
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InvalidInputDataException("Invalid input. Please enter a number.");
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1: {
                    std::string name;
                    int age;
                    std::cout << "Enter the name of the person: ";
                    assert(std::cin >> std::ws);
                    std::getline(std::cin, name);
                    std::cout << "Enter the age of the person: ";
                    if (!(std::cin >> age)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw InvalidInputDataException("Invalid age. Please enter a number.");
                    }
                    assert(age >= 0);
                    personTree.insert(name, Person(name, age));
                    break;
                }

                case 2: {
                    std::string title, author;
                    std::cout << "Enter the title of the book: ";
                    assert(std::cin >> std::ws);
                    std::getline(std::cin, title);
                    std::cout << "Enter the author of the book: ";
                    assert(std::cin >> std::ws);
                    std::getline(std::cin, author);
                    bookTree.insert(title, Book(title, author));
                    break;
                }

                case 3: {
                    std::string name;
                    std::cout << "Enter the name of the person to delete: ";
                    assert(std::cin >> std::ws);
                    std::getline(std::cin, name);
                    personTree.deleteElement(name);
                    break;
                }

                case 4: {
                    std::string title;
                    std::cout << "Enter the title of the book to delete: ";
                    assert(std::cin >> std::ws);
                    std::getline(std::cin, title);
                    bookTree.deleteElement(title);
                    break;
                }

                case 5: {
                    std::cout << "Preorder traversal for Persons:" << std::endl;
                    personTree.preorder();
                    break;
                }

                case 6: {
                    std::cout << "Preorder traversal for Books:" << std::endl;
                    bookTree.preorder();
                    break;
                }

                case 7: {
                    std::cout << "Postorder traversal for Persons:" << std::endl;
                    personTree.postorder();
                    break;
                }

                case 8: {
                    std::cout << "Postorder traversal for Books:" << std::endl;
                    bookTree.postorder();
                    break;
                }

                case 9: {
                    std::cout << "Exiting the program." << std::endl;
                    return 0;
                }

                default:
                    throw InvalidMenuChoiceException();
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
