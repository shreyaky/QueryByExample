#include<bits/stdc++.h>

using namespace std;
typedef long long int i64;

//struct Json {
//    Json *parent;
//
//    Json() {
//        parent = NULL;
//    }
//};

int main() {
    int n, q;
    cin >> n >> q;
    string s, temp;
    vector<string> categories;
    vector<string> contents;

    vector<string> store;
    unordered_map<string, int> lookup;
    vector<unordered_map<string, vector<int>>> search;
    cin.ignore();
//    Json *Obj = NULL, *currentObj = NULL;
//    Json *rootObj;
    string key, value;
    bool ifKey;
    size_t end_quote;
    int entryID = 0;
    while (n--) {
        getline(cin, s);
        int i = 0;
        while (i < s.length()) {
            switch (s[i]) {
                case '{':
//                    Obj = new Json;
//                    if (key.compare("")) {
//                        Obj->parent = currentObj;
//                    } else {
//                        Obj->parent = Obj;
//                        rootObj = Obj;
//                    }
//                    currentObj = Obj;
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
//                    currentObj = currentObj->parent;
                    break;
                case '\"':
                    end_quote = s.find('\"', i + 1);
                    temp = s.substr(i + 1, end_quote - i - 1);
                    if (ifKey) key = temp;
                    else value = '\"' + temp + '\"';
                    i = end_quote;
                    break;
                case ':':
                    ifKey = false;
                    break;
                case ' ':
                    break;
                default:
                    if (!ifKey)value.push_back(s[i]);
                    break;
            }
            i++;
        }
    }

    while (q--) {
//        getline(cin, s);
//        size_t dot1, dot2;
//        dot1 = -1;
//        currentObj = rootObj;
//        bool exist = true;
//        while ((dot2 = s.find('.', dot1 + 1)) != string::npos) {
//            key = s.substr(dot1 + 1, dot2 - dot1 - 1);
//            if (currentObj->objects.count(key))currentObj = currentObj->objects[key];
//            else {
//                exist = false;
//                break;
//            }
//            dot1 = dot2;
//        }
//        if (exist) {
//            key = s.substr(dot1 + 1);
//            if (currentObj->elements.count(key))cout << currentObj->elements[key] << endl;
//            else exist = false;
//        }
//        if (!exist)cout << "null\n";
    }

    if (lookup.empty()) {
        search.resize(categories.size());
        for (int j = 0; j != (int) categories.size(); ++j) {
            lookup[categories[j]] = j;
        }
    }

    for (int j = 0; j != (int) categories.size(); ++j) {
        search[lookup[categories[j]]][contents[j]].push_back(entryID);
    }

    cout << "hello";
}