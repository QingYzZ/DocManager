#include <iostream>
#include <fstream>
#include <string.h>
#include "Document.h"
#include "Macro.h"

using namespace std;

/* default constructor */
Document::Document() {
	name = "Untitled"; /* default name is Untitled */
}

/* constructor that pass in name */
Document::Document(const string &name) {
	this->name = name; /* initialize name with name from parameter */
}


int Document::reset() {
	name = "Untitled";
    paragraphs.clear();
	return SUCCESS;
}

int Document::print(bool print_paragraphs) const {
	/* print basic info about doc */
	cout << "Document name: " << name << endl;
	cout << "Number of Paragraphs: " << paragraphs.size() << endl;

	if (print_paragraphs) {
		this->printParagraph();
	}
	

	return SUCCESS;
}

void Document::printParagraph () const {
	/* for each paragraph */
	for (size_t i = 0; i < paragraphs.size(); i++) {
		const Paragraph &currentParagraph = paragraphs[i];

		/* for each line in each paragraph */
		for (size_t k = 0; k < currentParagraph.getNumberOfLines(); k++) {
			cout << currentParagraph.getLine(k) << endl;
		}

		/* use empty lines to seperate paragraphs when printed */
		if (i < (paragraphs.size() - 1)) {
			cout << endl;
		}
	}
}

/* for the context, we will assume paragaphNumber is always valid */
int Document::addParagraphAfter(int paragraphNumber) {
	Paragraph newParagraph;

	/* insert to the right position */
	paragraphs.insert(paragraphs.begin() + paragraphNumber, newParagraph);
	return SUCCESS;
}

/* we will also assume the parameters are valid here */
int Document::addLineAfter(int paragraphNumber, int lineNumber, const string &newLine) {
	Paragraph &paragraph = paragraphs[paragraphNumber - 1]; /* reference pointer */
	paragraph.addLine(newLine); /* add that line */
	return SUCCESS;
}

int Document::getNumberLinesParagraph(int paragraphNumber, int *&numberOfLines) const {
	*numberOfLines = paragraphs[paragraphNumber - 1].getNumberOfLines();
	return SUCCESS;
}

int Document::appendLine(int paragraphNumber, const std::string &newLine) {
	Paragraph& target = paragraphs[paragraphNumber - 1];

    if (target.addLine(newLine)) {
        return SUCCESS;
    }

	return FAILURE;
}

int Document::removeLine(int paragraphNumber, int lineNumber) {
	Paragraph &target = paragraphs[paragraphNumber - 1];
	if (target.removeLine(lineNumber)) {
            return SUCCESS;
    }
    return FAILURE;
}

int Document::loadDocument(const vector<string> &data) {
	return SUCCESS;
}

int Document::replaceText(const string &target, const string &replacement) {
	if (target.empty()) {
        return FAILURE;
    }

    for (int i = 0; i < paragraphs.size(); i++) {
        for (int k = 0; k < paragraphs[i].getNumberOfLines(); k++) {
            string line = paragraphs[i].getLine(k);
            replaceInLine(line, target, replacement);
            paragraphs[i].addLine(line);
        }
    }

	return SUCCESS;
}

int Document::removeText(const string &target) {
	if (target.empty()) {
		return FAILURE;
	}

	for (int i = 0; i < paragraphs.size(); i++) {
		for (int k = 0; k < paragraphs[k].getNumberOfLines(); k++) {
			string line = paragraphs[i].getLine(k);
			removeInLine(line, target);
			paragraphs[i].addLine(line);
		}
	}

	return SUCCESS;
}

int Document::saveDocument(const string& filename) const {
	ofstream output(filename);

	if (!output.is_open()) {
		return FAILURE;
	}

	for (int i = 0; i < paragraphs.size(); i++) {
		for (int k = 0; k < paragraphs[i].getNumberOfLines(); k++){
			output << paragraphs[i].getLine(k) << endl;
		}

		if (i < paragraphs.size() - 1) {
			output << endl; 
		}
	}

	output.close();
	return SUCCESS;
}

void Document::replaceInLine (string &line, const string &target, const string &replacement){
	size_t pos = 0;
    while ((pos = line.find(target, pos)) != string::npos) {
        line.replace(pos, target.length(), replacement);
        pos += replacement.length();
    }
}

void Document::removeInLine (string &line, const string &target){
	size_t pos = 0;
    while ((pos = line.find(target, pos)) != string::npos) {
        line.erase(pos, target.length());
    }
}

bool trim_helper(const char* line) {
	for (int i = 0; line[i] != '\0'; i++) {
        if (!isspace(static_cast <unsigned char> (line[i]))) {
            return false;
        }
    }
    return true;
}