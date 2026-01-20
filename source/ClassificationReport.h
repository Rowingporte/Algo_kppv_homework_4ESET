#ifndef CLASSIFICATIONREPORT_H
#define CLASSIFICATIONREPORT_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class ClassificationReport {
    vector<vector<int>> _confusion;
    double _ok;
    double _nok;
    int _nbTags;
public:
    ClassificationReport(int nbTags) : _nbTags(nbTags) { _confusion.resize(10, std::vector<int>(10, 0)); };
    void toString() const;
};

#endif