#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector< vector<string> > hashtable;
    vector<string> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        hashtable.resize(bucket_count,vector<string>());
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery_naive(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }

    void processQuery_fast(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            vector<string>* array = &hashtable[query.ind];
            for (int i = static_cast<int>(array->size()) - 1; i >= 0; --i)
                //if (hash_func(array[i]) == query.ind)
                    std::cout << (*array)[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>* array = &hashtable[hash_func(query.s)];
            vector<string>::iterator it = std::find(array->begin(), array->end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != array->end());
            else if (query.type == "add") {
                if (it == array->end())
                    array->push_back(query.s);
            } else if (query.type == "del") {
                if (it != array->end())
                    array->erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            Query query = readQuery();
            //processQuery_naive(query);
            processQuery_fast(query);
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
