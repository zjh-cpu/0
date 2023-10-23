#include "DocumentManager.h"

Document::Document(std::string n, int identifier, int limit) 
    : name(n), id(identifier), license_limit(limit), borrowed_copies(0) {}

void DocumentManager::addDocument(std::string name, int id, int license_limit) {
    Document doc(name, id, license_limit);
    docsByID[id] = doc;
    docNameToID[name] = id;
}

void DocumentManager::addPatron(int patronID) {
    patrons.insert(patronID);
}

int DocumentManager::search(std::string name) {
    if (docNameToID.find(name) != docNameToID.end()) {
        return docNameToID[name];
    }
    return 0;
}

bool DocumentManager::borrowDocument(int docid, int patronID) {
    if (docsByID.find(docid) == docsByID.end() || patrons.find(patronID) == patrons.end()) {
        return false;
    }
    Document &doc = docsByID[docid];
    if (doc.borrowed_copies < doc.license_limit) {
        doc.borrowed_copies++;
        return true;
    }
    return false;
}

void DocumentManager::returnDocument(int docid, int patronID) {
    if (docsByID.find(docid) == docsByID.end() || patrons.find(patronID) == patrons.end()) {
        return;
    }
    Document &doc = docsByID[docid];
    if (doc.borrowed_copies > 0) {
        doc.borrowed_copies--;
    }
}
