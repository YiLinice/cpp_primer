#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <memory>
#include <set>

class queryResult {
private:
    typedef std::shared_ptr<std::vector<std::string>> share_file;
    typedef std::shared_ptr<std::set<int>> share_lines;
    share_file vec_file_ptr;
    share_lines line_set;

public:
    queryResult(share_file vec_f, share_lines lines) : vec_file_ptr(vec_f), line_set(lines){};
    void print();
};

class textQuery {
private:
    /* data */
    std::shared_ptr<std::vector<std::string>> vec_file;
    std::map<std::string, std::shared_ptr<std::set<int>>> word_map;

    void parse();
public:
    textQuery(std::ifstream &in);
    ~textQuery();

    queryResult query(std::string word);
};

