#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include "../headers/disk.h"
#include "../headers/shared.h"

using namespace std;

class Analysis
{
public:
    Analysis();
    void start();
    void execute(string token, string body);
    string token(string s);
    vector<string> split(string s, string source);
};

#endif // END OF DECLARATION