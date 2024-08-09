#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>
#include <string>
#include "Paragraph.h"

using namespace std;

class Document {
public:
    Document();
	Document(const string &name);
    int reset();
    int print(bool print_paragraphs) const;
    int addParagraphAfter(int paragraphNumber);
    int addLineAfter(int paragraphNumber, int lineNumber, const string &newLine);
    int getNumberLinesParagraph(int paragraphNumber, int *&numberOfLines) const;
    int appendLine(int paragraphNumber, const string &newLine);
    int removeLine(int paragraphNumber, int lineNumber);
    int loadDocument(const vector<string> &data);
    int replaceText(const string &target, const string &replacement);
    int removeText(const string &target);
    int loadFile(const string &filename);
    int saveDocument(const string &filename) const;

private:
    vector<Paragraph> paragraphs;
    string name;

    void replaceInLine(string &line, const string &target, const string &replacement);
    void removeInLine(string &line, const string &target);
	void printParagraph() const;
    bool trimHelper(const string &line) const;
};

#endif
