#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <string>

using namespace std;

class Page{

public:
	Page(string& html);
	~Page();
	string getString();
	string getTitle();
private:
	void makeText(string& html);
	bool endOfString(int index, int length);
	string text;
	string title;
	bool haseTable;
};

#endif