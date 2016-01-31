#pragma once

#include <string>
#include "SectionTab.h"
#include "SymTab.h"

using namespace std;

enum DP		// Directive Process
{
	NONE = 0,
	GLOBAL,
	EXTERN,
	CHAR,
	WORD,
	LONG,
	ALIGN,
	SKIP,
	SECTION,
	INSTR
};

class BadSyntax {};
class EndOfFile {};
class OutOfRange{};

class WordAnalyzer
{
private:
	bool outputSep;
	char *outName;
	SectionTab *secTab;
	SymTab *symtab;
	bool expectNewLine, expectSameLine;
	bool sectionDefinition, stringDefinition, skipNextWord;
	string section;
	string instr, instrOp[4];
	int instrOpNum;
	int val;
	bool inSection;

	int loCnt;

	bool trySection(string sym, string dotSecton);
	int checkNum(string numS, bool isLong = false);
	//int checkNum(string numS);
	//int checkLongNum(string numS);
	dword creteMemRep(string type, int instr, int op0, int op1 = 0, int op2 = 0, int op3 = 0);
	dword creteMemRep(int instr); 
	char* creteMemWordRep(int word);
	string determineSec(string sym);
	bool isValidSection(string sym);
	bool determineIns(string sym);
	void creteInstEntry(string instr, string *instrOp, int instrOpNum);
	void creteEntry(string word, char type);
	//void creteCharEntry(string word);
	//void creteWordEntry(string word);
	//void creteLongEntry(string word);

	DP cdp;
	void process(string word, bool newLine);

	void writeOutTabs();
public:
	WordAnalyzer() {}
	WordAnalyzer(char outSep, char* name = "output.txt");
	~WordAnalyzer();

	static dword creteMemRep(RT type, int val);

	void pass(string word, bool newLine);
};

