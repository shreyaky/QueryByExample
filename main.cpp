#include<bits/stdc++.h>

using namespace std;

void decode_JSON(const string &input, vector<string> &categories, vector<string> &contents);

void add_JSON(const string &input, int entryID, vector<string> &storage, unordered_map<string, int> &lookup,
              vector<unordered_map<string, vector<int>>> &search);

void get_JSON(const string &input, vector<string> &storage, unordered_map<string, int> &lookup,
              vector<unordered_map<string, vector<int>>> &search);

//void delete_JSON(string input);

vector<int> getIntersection(vector<vector<int> > &sets);

int main() {
    vector<string> storage;
    unordered_map<string, int> lookup;
    vector<unordered_map<string, vector<int>>> search;
    int n = 5;
    int entryID = 0;

    while (n--) {
        string input;
        getline(cin, input);

        switch (input[0]) {
            case 'a':
                add_JSON(input.substr(3), entryID, storage, lookup, search);
                entryID++;
                break;
            case 'g':
                get_JSON(input.substr(3), storage, lookup, search);\
                break;

            default:
                cerr << "error." << endl;
        }
    }

    cout << "hello";
}

void decode_JSON(const string &input, vector<string> &categories, vector<string> &contents) {
    int i = 0;
    string key, value, temp;
    bool ifKey;
    size_t end_quote;
    while (i < input.length()) {
        switch (input[i]) {
            case '{':
                ifKey = true;
                break;
            case ',':
                if (value.compare("")) {
                    categories.push_back(key);
                    contents.push_back(value);
                }
                value = "";
                ifKey = true;
                break;
            case '}':
                if (value.compare("")) {
                    categories.push_back(key);
                    contents.push_back(value);
                }
                value = "";
                ifKey = true;
                break;
            case '\"':
                end_quote = input.find('\"', i + 1);
                temp = input.substr(i + 1, end_quote - i - 1);
                if (ifKey)
                    key = temp;
                else
                    value = '\"' + temp + '\"';
                i = end_quote;
                break;
            case ':':
                ifKey = false;
                break;
            case ' ':
                break;
            default:
                if (!ifKey)
                    value.push_back(input[i]);
                break;
        }
        i++;
    }
}

void add_JSON(const string &input, int entryID, vector<string> &storage, unordered_map<string, int> &lookup,
              vector<unordered_map<string, vector<int>>> &search) {
    vector<string> categories;
    vector<string> contents;

    storage.push_back(input);
    decode_JSON(input, categories, contents);

    if (lookup.empty()) {
        search.resize(categories.size());
        for (int j = 0; j != (int) categories.size(); ++j) {
            lookup[categories[j]] = j;
        }
    }

    for (int j = 0; j != (int) categories.size(); ++j) {
        search[lookup[categories[j]]][contents[j]].push_back(entryID);
    }
}

void get_JSON(const string &input, vector<string> &storage, unordered_map<string, int> &lookup,
              vector<unordered_map<string, vector<int>>> &search) {
    vector<string> categories;
    vector<string> contents;

    decode_JSON(input, categories, contents);
    vector<vector<int>> partial_results(categories.size());
    for (int j = 0; j != (int) categories.size(); ++j) {
        int lookup_number = lookup[categories[j]];
        if (search[lookup_number].find(contents[j]) != search[lookup_number].end()) {
            for (auto t: search[lookup[categories[j]]][contents[j]])
                partial_results[j].push_back(t);
        } else {
            cout << "0 entries found\n% ";
            return;
        }
    }
    vector<int> full_results = getIntersection(partial_results);
    for (auto c: full_results)
        cout << storage[c] << endl;
}

vector<int> getIntersection(vector<vector<int> > &sets) {
    vector<int> result;
    int smallest = 0;
    int minSize = (int) sets[0].size();

    if (sets.size() == 1) {
        vector<int>::iterator temp;
        temp = unique(sets[0].begin(), sets[0].end());
        sets[0].resize((unsigned) (temp - sets[0].begin()));
        return sets[0];
    }

    for (int i = 1; i != (int) sets.size(); ++i) {
        if (minSize > (int) sets[i].size()) {
            minSize = (int) sets[i].size();
            smallest = i;
        }
    }

    vector<int>::iterator temp;
    temp = unique(sets[smallest].begin(), sets[smallest].end());
    sets[smallest].resize((unsigned) (temp - sets[smallest].begin()));

    vector<int> elements;
    for (auto c: sets[smallest])
        elements.push_back(c);

    for (auto it = elements.begin(); it != elements.end(); ++it) {
        bool ifFound = true;

        for (int j = 0; j != (int) sets.size(); ++j) {
            if (j != smallest) {
                if (!binary_search(sets[j].begin(), sets[j].end(), *it)) {
                    ifFound = false;
                    break;
                }
            }
        }

        if (ifFound)
            result.push_back(*it);
    }
    return result;
}