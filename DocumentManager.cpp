#include "DocumentManager.h"
using namespace std;

void DocumentManager::addDocument(string name, int id, int license_limit){
    documents[id] = {name, id, license_limit, 0};
    documentID[name] = id;
}

void DocumentManager::addPatron(int patronID){
    patrons.insert(patronID);
}

int DocumentManager::search(string name){
    if(documentID.find(name) != documentID.end()){
         return documentID[name];
     }
    return 0;
}

bool DocumentManager::borrowDocument(int docid, int patronID){
    if(patrons.find(patronID) == patrons.end()){
        return false;
    }
    if(documents.find(docid) != documents.end() && documents[docid].borrow_number < documents[docid].license_limit){
        documents[docid].borrow_number++;
        return true;
    }
    return false;
}

void DocumentManager::returnDocument(int docid, int patronID){
    if(patrons.find(patronID) != patrons.end() && documents.find(docid) != documents.end() && documents[docid].borrow_number > 0){
        documents[docid].borrow_number--;
    }
}