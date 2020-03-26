#include <string>
#include <iostream>

using namespace std;

class HasPtr {
public:
    int value;
    int *use;
    string *strPtr;

    HasPtr(const string &s = string()) : value(0), use(new int(1)), strPtr(new string(s)){}
    HasPtr(const HasPtr &hasPtr);
    HasPtr& operator=(const HasPtr &hasPtr);

    ~HasPtr();
};

HasPtr::HasPtr(const HasPtr &hasPtr) : value(hasPtr.value), use(hasPtr.use), strPtr(hasPtr.strPtr) {
    (*use)++;
}

HasPtr& HasPtr::operator=(const HasPtr &hasPtr) {
    value = hasPtr.value;
    auto old_use = use;
    auto old_strPtr = strPtr;

    use = hasPtr.use;
    strPtr = hasPtr.strPtr;
    (*use)++;

    if (--*old_use == 0) {
        cout << "delete in operator=" << endl;
        delete old_use;
        delete old_strPtr;
    }

    return *this;
}

HasPtr::~HasPtr() {
    if (--*use == 0) {
        delete use;
        delete strPtr;
    }
}

int main() {
    HasPtr p1("linyi");
    p1 = p1;

    cout << *p1.use << endl;
    cout << *p1.strPtr << endl;
    return 0;
}