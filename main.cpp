#include<bits/stdc++.h>

using namespace std;
typedef long long int i64;

struct Json {
    map<string, string> elements;
    map<string, Json *> objects;
    Json *parent;

    Json() {
        parent = nullptr;
    }
};

class query {
private:
    vector<string> store;

public:
    vector<unordered_map<string, int>> search;

    void add_JSON(string input);

    void get_JSON(string input);

    void delete_JSON(string input);

    void decode_JSON(string input);
};

int main() {
    while (q--) {
        getline(cin, s);
        size_t dot1, dot2;
        dot1 = -1;
        currentObj = rootObj;
        bool exist = true;
        while ((dot2 = s.find('.', dot1 + 1)) != string::npos) {
            key = s.substr(dot1 + 1, dot2 - dot1 - 1);
            if (currentObj->objects.count(key))currentObj = currentObj->objects[key];
            else {
                exist = false;
                break;
            }
            dot1 = dot2;
        }
        if (exist) {
            key = s.substr(dot1 + 1);
            if (currentObj->elements.count(key))cout << currentObj->elements[key] << endl;
            else exist = false;
        }
        if (!exist)cout << "null\n";
    }
}

void query::decode_JSON(string input) {
    string key, value;
    string temp;
    Json *Obj = nullptr, *currentObj = nullptr;
    Json *rootObj;
    size_t end_quote;
    bool key_time;
    int i = 0;
    while (i < input.length()) {
        switch (input[i]) {
            case '{':
                Obj = new Json;
                if (key.compare("")) {
                    Obj->parent = currentObj;
                    currentObj->objects[key] = Obj;
                } else {
                    Obj->parent = Obj;
                    rootObj = Obj;
                }
                currentObj = Obj;
                key_time = true;
                break;
            case ',':
                if (value.compare(""))currentObj->elements[key] = value;
                value = "";
                key_time = true;
                break;
            case '}':
                if (value.compare(""))currentObj->elements[key] = value;
                value = "";
                key_time = true;
                currentObj = currentObj->parent;
                break;
            case '\"':
                end_quote = input.find('\"', i + 1);
                temp = input.substr(i + 1, end_quote - i - 1);
                if (key_time) key = temp;
                else value = '\"' + temp + '\"';
                i = end_quote;
                break;
            case ':':
                key_time = false;
                break;
            case ' ':
                break;
            default:
                if (!key_time)value.push_back(input[i]);
                break;
        }
        i++;
    }
}