#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>

// Trida reprezentujici jeden uzel stromu
class Node {
public:
    // Jedinecny identifikator uzlu
    std::string id;

    // Seznam vsech primych potomku
    std::vector<std::shared_ptr<Node>> children;

    // Odkaz na rodice, weak_ptr na zabraneni cyklickym referencim
    std::weak_ptr<Node> parent;

    // Konstruktor vytvori uzel s danym ID
    explicit Node(const std::string& id) : id(id) {}
};

#endif