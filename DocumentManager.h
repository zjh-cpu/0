#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <iostream>
#include <unordered_map>
#include <set>

class Document {
public:
    std::string name;
    int id;
    int license_limit;
    int borrowed_copies;
    
    Document(std::string n, int identifier, int limit);
};

class DocumentManager {
private:
    std::unordered_map<int, Document> docsByID;
    std::unordered_map<std::string, int> docNameToID;
    std::set<int> patrons;

public:
    void addDocument(std::string name, int id, int license_limit);
    void addPatron(int patronID);
    int search(std::string name);
    bool borrowDocument(int docid, int patronID);
    void returnDocument(int docid, int patronID);
};

#endif // DOCUMENTMANAGER_H
