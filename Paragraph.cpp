#include <iostream>

#include "Paragraph.h"
#include "Macro.h"

using namespace std;

int Paragraph::addLine(const string &line) {
	if (line.empty()) {
		return FAILURE;
	}
	lines.push_back(line);
	return SUCCESS;
}

const string& Paragraph::getLine(int lineNumber) const {
	return lines[lineNumber];
}

int Paragraph::getNumberOfLines() const {
	return static_cast<int> (lines.size());
}

void Paragraph::printLines() const {
	for (size_t i = 0; i < lines.size(); ++i) {
		const string &line = lines[i];  // Use explicit type instead of auto
		cout << line << endl;
	}
}
