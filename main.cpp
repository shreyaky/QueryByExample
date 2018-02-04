#include<bits/stdc++.h>

using namespace std;

void decode_JSON(string input, vector<string> &categories, vector<string> &contents);

void add_JSON(string input, int entryID, vector<string> &storage, unordered_map<string, int> &lookup,
              vector<unordered_map<string, vector<int>>> &search);

//void get_JSON(string input);

//void delete_JSON(string input);

int main() {
    vector<string> storage;
    unordered_map<string, int> lookup;
    vector<unordered_map<string, vector<int>>> search;
    int n = 5;
    int entryID = 0;

    while (n--) {
        string input;
        getline(cin, input);
        add_JSON(input, entryID, storage, lookup, search);
        entryID++;
    }

    cout << "hello";
}

void decode_JSON(string input, vector<string> &categories, vector<string> &contents) {
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

void add_JSON(string input, int entryID, vector<string> &storage, unordered_map<string, int> &lookup,
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