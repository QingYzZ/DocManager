#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include <vector>
#include <string>

using namespace std;

class Paragraph {
public:
    Paragraph();

    int addLine(const string &line);
    int removeLine(int lineNumber);
    int getNumberOfLines() const;
    const string& getLine(int lineNumber) const;
	void printLines() const;

private:
    vector<string> lines;
};

#endif
