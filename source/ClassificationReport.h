#ifndef CLASSIFICATIONREPORT_H
#define CLASSIFICATIONREPORT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class ClassificationReport {
    vector<vector<int>> _confusion;
    bool _ok;
    bool _nok;
    int _nbTags;
public:
    ClassificationReport(int nbTags) : _nbTags(nbTags) {};
    string toString() const;
};

#endif