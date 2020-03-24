#include "textQuery.h"
#include <iostream>
using namespace std;

void queryResult::print() {
    cout << "element occurs " << line_set->size() << " times" << endl;
    for (auto itb = line_set->cbegin(); itb != line_set->cend(); itb++) {
        cout << "   line (" << (*itb) + 1 << ") " << vec_file_ptr->at(*itb) << endl;
    }
}

textQuery::textQuery(std::ifstream &in) : vec_file(new std::vector<std::string>()){
    std::string line;
    while(std::getline(in, line)) {
        vec_file->push_back(line);
    }

    parse();
}

textQuery::~textQuery() {

}

void textQuery::parse() {
    std::string word;
    std::shared_ptr<std::set<int>> word_set;

    /* parse file to extract every word in which line */
    for (int line = 0; line < vec_file->size(); line++) {
        std::istringstream in(vec_file->at(line));
        while(in >> word) {
            std::shared_ptr<std::set<int>> &word_set = word_map[word];
            if (!word_set) {
                word_set.reset(new set<int>());
            }
            word_set->insert(line);
        }
    }
    return;
}

queryResult textQuery::query(std::string word) {
    auto it = word_map.find(word);
    if (it == word_map.end()) {
        throw std::runtime_error( word + " is not found");
    }

    return queryResult(vec_file, it->second);
}

int main(int argc , char** argv) {

/*
    if (argc < 2) {
        cerr << "please input file name" << endl;
        return 0;
    }
*/
    ifstream in("test.txt");
    textQuery tq(in);
    tq.query("hello").print();

    return 0;
}