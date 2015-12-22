//
//  AQL.h
//  compiler
//
//  Created by 牛仁鹏 on 15/12/21.
//  Copyright © 2015年 牛仁鹏. All rights reserved.
//
#ifndef AQL_h
#define AQL_h

#include <iostream>
#include <vector>
#include "Tokenizer.h"
using namespace std;

struct Span {
    int from, to;
    string value;
    Span(string x, int f, int t) {
        value = x;
        from = f;
        to = t;
    }
};
struct Column {
    string name;
    vector<Span> spans;
    Column(string n = "") {
        name = n;
    }
    Column& operator=(const Column& c)//重载运算符
    {
        name = c.name;
        spans = c.spans;
        return *this;
    }
};
typedef enum{
    REG, COLUMN
} Type_Atom;
struct Atom {
    Column column;
    int interval_from;
    int interval_to;
    Type_Atom type;
    string regex;
    Atom(Type_Atom t, int from, int to, string r, Column c) {
        type = t;
        interval_from = from;
        interval_to = to;
        regex = r;
        column = c;
    }
};
class View {
private:
    string name;
public:
    vector<Column> columns;
    View(string name);
    void output(string);
    void extract_regex(string regex,
                       vector<int> groups,
                       vector<string> column_names,
                       string text);
    void extract_pattern(vector<Atom> atoms,
                         vector<int> groups,
                         vector<string> columns_names);
    void select(vector<Column> columns,
                vector<string> column_names);
};


#endif /* AQL_h */
