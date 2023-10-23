#include <iostream>
#include <unordered_map>
#include <set>

class Document {
public:
    std::string name;
    int id;
    int license_limit;
    int borrowed_copies;
    
    Document(std::string n, int identifier, int limit) 
        : name(n), id(identifier), license_limit(limit), borrowed_copies(0) {}
};

class DocumentManager {
private:
    std::unordered_map<int, Document> docsByID;
    std::unordered_map<std::string, int> docNameToID;
    std::set<int> patrons;

public:
    void addDocument(std::string name, int id, int license_limit) {
        Document doc(name, id, license_limit);
        docsByID[id] = doc;
        docNameToID[name] = id;
    }

    void addPatron(int patronID) {
        patrons.insert(patronID);
    }

    int search(std::string name) {
        if (docNameToID.find(name) != docNameToID.end()) {
            return docNameToID[name];
        }
        return 0;
    }

    bool borrowDocument(int docid, int patronID) {
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

    void returnDocument(int docid, int patronID) {
        if (docsByID.find(docid) == docsByID.end() || patrons.find(patronID) == patrons.end()) {
            return;
        }
        Document &doc = docsByID[docid];
        if (doc.borrowed_copies > 0) {
            doc.borrowed_copies--;
        }
    }
};

int main() {
    DocumentManager dm;
    
    // 添加文档
    dm.addDocument("Book1", 1, 2);
    dm.addDocument("Book2", 2, 1);
    
    // 搜索文档
    int id = dm.search("Book1");
    std::cout << "ID of Book1: " << id << std::endl;  // 应该输出 1
    
    // 添加顾客
    dm.addPatron(101);
    dm.addPatron(102);
    
    // 借出文档
    std::cout << dm.borrowDocument(1, 101) << std::endl; // 应该输出 true
    std::cout << dm.borrowDocument(1, 102) << std::endl; // 应该输出 true
    std::cout << dm.borrowDocument(1, 103) << std::endl; // 应该输出 false (因为顾客 103 不存在)
    std::cout << dm.borrowDocument(1, 101) << std::endl; // 应该输出 false (因为所有的副本都被借出)

    // 归还文档
    dm.returnDocument(1, 101);
    std::cout << dm.borrowDocument(1, 101) << std::endl; // 应该输出 true (因为文档已经归还)

    return 0;
}
