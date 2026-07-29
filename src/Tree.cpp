#include "Tree.h"

#include <iostream>
#include <regex>

// Rekurzivne vypise cely podstrom, depth urcuje odsazeni
void Tree::printTree(const std::shared_ptr<Node>& node, int depth) const {
    for (int i = 0; i < depth; i++) {
        std::cout << "    ";
    }

    // vypis aktualniho uzlu
    std::cout << "-[" << node->id << "]" << std::endl;

    // rekurzivne vypise vsechny potomky
    for (const auto& child : node->children) {
        printTree(child, depth + 1);
    }
}

// Overi, zda identifikator obsahuje pouze pismena a cisla
bool Tree::isValidIdentifier(const std::string& id) const {
    std::regex validIdRegex("^[a-zA-Z0-9]+$");

    return std::regex_match(id, validIdRegex);
}

// Vrati true, pokud potentialAncestor lezi nad uzlem node
// Funkce se pouziva pro detekci cyklu
bool Tree::isAncestor(
    const std::shared_ptr<Node>& node,
    const std::shared_ptr<Node>& potentialAncestor) const
{
    auto current = node;

    // postupujeme smerem ke koreni
    while (current) {
        if (current == potentialAncestor) {
            return true;
        }

        current = current->parent.lock();
    }

    return false;
}

// Vytvori novy uzel
void Tree::createNode(const std::string& id) {
    // kontrola formatu identifikatoru
    if (!isValidIdentifier(id)) {
        std::cout << "Invalid identifier '" << id << "'" << std::endl;
        return;
    }

    // kontrola duplicity
    if (nodes.find(id) != nodes.end()) {
        std::cout << "Duplicate node id " << id << std::endl;
        return;
    }

    // vytvoreni noveho uzlu
    nodes[id] = std::make_shared<Node>(id);
    std::cout << "New node " << id << std::endl;
}

// Pripoji uzel pod jineho rodice
void Tree::attachNode(const std::string& id, const std::string& parentId) {
    auto itNode = nodes.find(id);
    auto itParent = nodes.find(parentId);

    // uzel musi existovat
    if (itNode == nodes.end()) {
        std::cout << "No node with id " << id << std::endl;
        return;
    }

    // uzel nesmi byt nikam pripojen
    if (!itNode->second->parent.expired()) {
        std::cout << "Node " << id << " already attached" << std::endl;
        return;
    }

    // musi existovat rodic
    if (itParent == nodes.end()) {
        std::cout << "No node with id " << parentId << std::endl;
        return;
    }

    // uzel nesmi byt svym vlastnim rodicem
    if (id == parentId) {
        std::cout << "Can't attach node to itself" << std::endl;
        return;
    }

    // kontrola vytvoreni cyklu
    if (isAncestor(itParent->second, itNode->second)) {
        std::cout << "Cannot attach node " << id << " under " << parentId 
                  << " as it creates a cycle" << std::endl;
        return;
    }

    // pokud jeste neexistuje koren, prvni rodic se stane korenem
    if (!root) {
        root = itParent->second;
        std::cout << "New root node " << parentId << std::endl;
        
    // strom muze mit pouze jeden koren
    } else if (itParent->second->parent.expired() && itParent->second != root) {
        std::cout << "Another node is already a root node" << std::endl;
        return;
    }

    // propojeni rodice a ditete
    itNode->second->parent = itParent->second;
    itParent->second->children.push_back(itNode->second);

    std::cout << "Node " << id << " is child of node " << parentId << std::endl;
}

// Vypise informace o jednom uzlu
void Tree::printNode(const std::string& id) const {
    auto itNode = nodes.find(id);

    if (itNode == nodes.end()) {
        std::cout << "No node with id " << id << std::endl;
        return;
    }

    // uzel neni soucasti stromu
    const auto& node = itNode->second;
    if (node->parent.expired() && node != root) {
        std::cout << "Unattached node " << id << std::endl;
        return;
    }

    std::cout << "Node " << id << " with " << node->children.size() << " children";

    // vypis seznamu potomku
    if (!node->children.empty()) {
        std::cout << " ";
        for (size_t i = 0; i < node->children.size(); ++i) {
            std::cout << node->children[i]->id;
            if (i < node->children.size() - 1) {
                std::cout << ",";
            }
        }
    }

    std::cout << std::endl;
}

// Vypise koren stromu
void Tree::printRootNode() const {
    if (!root) {
        std::cout << "No root node" << std::endl;
    } else {
        printNode(root->id);
    }
}

// Vypise podstrom od zadaneho uzlu
void Tree::printTree(const std::string& id) const {
    auto itNode = nodes.find(id);

    if (itNode == nodes.end()) {
        std::cout << "No node with id " << id << std::endl;
        return;
    }

    const auto& node = itNode->second;

    // uzel neni soucasti stromu
    if (node->parent.expired() && node != root) {
        std::cout << "Node " << id << " not attached" << std::endl;
        return;
    }

    printTree(node, 0);
}

// Vypise cely strom od korene
void Tree::printTree() const {
    if (!root) {
        std::cout << "No root node" << std::endl;
    } else {
        printTree(root, 0);
    }
}
