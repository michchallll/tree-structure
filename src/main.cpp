#include "Tree.h"

#include <iostream>
#include <sstream>
#include <string>

int main() {
    // Vytvoreni instance stromu
    Tree tree;

    // Promenna pro ulozeni jednoho prikazu ze vstupu
    std::string line;

    // Cteme vstup radek po radku az do konce souboru
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        // Prikaz: create node <id>
        if (command == "create") {
            std::string nodeCmd, id;
            iss >> nodeCmd >> id;

            // Kontrola spravne syntaxe prikazu
            if (nodeCmd == "node" && !id.empty()) {
                tree.createNode(id);
            } else {
                std::cout << "Unknown command '" << line << "'" << std::endl;
            }

        // Prikaz: attach node <id> under <parentId>
        } else if (command == "attach") {
            std::string nodeCmd, id, underCmd, parentId;
            iss >> nodeCmd >> id >> underCmd >> parentId;

            if (nodeCmd == "node" && underCmd == "under" && !id.empty() && !parentId.empty()) {
                tree.attachNode(id, parentId);
            } else {
                std::cout << "Unknown command '" << line << "'" << std::endl;
            }

        // Prikaz: print
        } else if (command == "print") {
            std::string nodeCmd, id;
            iss >> nodeCmd;

            // print node <id>
            if (nodeCmd == "node") {
                iss >> id;

                if (!id.empty()) {
                    tree.printNode(id);
                } else {
                    std::cout << "Unknown command '" << line << "'" << std::endl;
                }

            // print root
            } else if (nodeCmd == "root") {
                tree.printRootNode();

            // print tree
            } else if (nodeCmd == "tree") {
                std::string underCmd;
                iss >> underCmd >> id;

                // print tree under <id>
                if (underCmd == "under" && !id.empty()) {
                    tree.printTree(id);
                } else {
                    tree.printTree();
                }

            } else {
                std::cout << "Unknown command '" << line << "'" << std::endl;
            }

        } else if (!command.empty()) {
            std::cout << "Unknown command '" << line << "'" << std::endl;
        }
    }

    return 0;
}
