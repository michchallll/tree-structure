#ifndef TREE_H
#define TREE_H

#include "Node.h"

#include <string>
#include <unordered_map>
#include <memory>

// Trida reprezentujici cely strom
class Tree {
private:
    // Mapa vsech vytvorenych uzlu
    // Klic je ID uzlu
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes;

    // Ukazatel na koren stromu
    std::shared_ptr<Node> root;

    // Rekurzivne vypise cely podstrom, depth urcuje odsazeni
    void printTree(const std::shared_ptr<Node>& node, int depth) const;

    // Overi, zda identifikator obsahuje pouze pismena a cisla
    bool isValidIdentifier(const std::string& id) const;

    // Vrati true, pokud potentialAncestor lezi nad uzlem node
    // Funkce se pouziva pro detekci cyklu
    bool isAncestor(
        const std::shared_ptr<Node>& node,
        const std::shared_ptr<Node>& ancestor) const;

public:
    // Vytvori novy uzel
    void createNode(const std::string& id);

    // Pripoji uzel pod jineho rodice
    void attachNode(const std::string& id, const std::string& parentId);

    // Vypise informace o jednom uzlu
    void printNode(const std::string& id) const;

    // Vypise koren stromu
    void printRootNode() const;

    // Vypise podstrom od zadaneho uzlu
    void printTree(const std::string& id) const;

    // Vypise cely strom od korene
    void printTree() const;
};

#endif