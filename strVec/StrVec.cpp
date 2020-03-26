#include <memory>
#include <string>
#include <iostream>

using namespace std;

class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &strVec);
    StrVec& operator=(StrVec &strVec);
    ~StrVec();
    void push_back(const string &s);
    void print();
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    string* begin() const {return elements;}
    string* end() const {return first_free;}

private:
    static allocator<string> alloc;
    string *elements;   /* begin point */
    string *first_free; /* end point */
    string *cap;        /* end of capacity */

    pair<string*, string*> alloc_n_copy(const string *begin, const string *end);
    void free();
    void chk_n_alloc() {if (size() == capacity()) reallocate();}
    void reallocate();
};

allocator<string> StrVec::alloc;
void StrVec::push_back(const string &s) {
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

void StrVec::free() {
    if (elements) {
        for (auto p = first_free; p != elements; ) {
            alloc.destroy(--p);
        }

        alloc.deallocate(elements, cap - elements);
    }
}

pair<string*, string*> StrVec::alloc_n_copy(const string *begin, const string *end) {
    auto new_data = alloc.allocate(end - begin);
    return {new_data, uninitialized_copy(begin, end, new_data)};
}

StrVec::StrVec(const StrVec &strVec) {
    auto new_data = alloc_n_copy(strVec.begin(), strVec.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

StrVec::~StrVec() {
    free();
}

StrVec& StrVec::operator=(StrVec &strVec) {
    auto new_data = alloc_n_copy(strVec.begin(), strVec.end());
    free();

    elements = new_data.first;
    first_free = cap = new_data.second;
    
    return *this;
}

void StrVec::reallocate() {
    size_t n_cap = capacity() ? capacity() * 2 : 1;
    auto new_data = alloc.allocate(n_cap);

    auto dest = new_data;
    auto src = elements;
    for ( ; dest != new_data + size(); ) {
        alloc.construct(dest++, std::move(*src++));
    }

    free();

    first_free = dest;
    elements = new_data;
    cap = elements + n_cap;

    return;
}

void StrVec::print() {
    auto ele = elements;
    for (int i = 0; i < size(); i++) {
        cout << *ele++ << endl;
    }
}

int main() {
    StrVec vec;

    string strs[] = {"linyi", "ly", "xq"};

    for(int i = 0; i < sizeof(strs)/sizeof(string); i++) {
        vec.push_back(strs[i]);
    }

    vec.print();
    vec = vec;
    StrVec vec2 = vec;
    vec.print();
    vec2.print();

    return 0;
}