#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Table.h"
#include "Section.h"
#include "SymTab.h"
#include "RelTab.h"
#include "ByteSection.h"
#include "FRefTab.h"

using namespace std;

enum SecName	// Section names
{
	DOT_TEXT = 0,
	DOT_BSS = 1,
	DOT_DATA = 2
};

static string SECTION_STR[] = {".text", ".bss", ".data"};

class SectionRedefinition {};
class BSSwrite {};
class NoSection {};

class SectionTab : public Table<Section*>
{
private:
	///void trySection(string fullnSecName, string dotSecton);
	ByteSection *current;

	SymTab *symTab;
	FRefTab *freftab;
public:
	SectionTab() 
	{ 
		current = NULL; 
		symTab = new SymTab(); 
		freftab = new FRefTab();
	}
	~SectionTab()
	{
		delete symTab;
		delete freftab;
		delete current;
	}


	bool sectionExists(string name);

	///bool setSection(string sec);
	///Section *createSec(string name);

	void createSection(string secTypeName, string secName);
	void createSection(string secTypeName) { createSection(secTypeName, secTypeName); }

	void setCurrSecAddr(int addr) 
	{
		if (current)
		{
			current->setAddress(addr);
			symTab->setSymVal(current->getName(), current->getAddress());
		}
	}
	void setCurrSecSize(int size) 
	{
		if (current)
		{
			current->setSize(size);
			symTab->setSymSize(current->getName(), current->getSize());
		}
	}

	bool checkBssCur()
	{
		string name = current->getName();
		name = name.substr(0, 4);
		if (name.compare(".bss") == 0) return true;
		else return false;
	}
	///SymTab *getSymTab() { return symTab; }

	void addToSymTab(string sym, bool def, STT type, STB binding, int val = 0) 
	{
		if(current == NULL && binding == STB_LOCAL) throw NoSection();
		symTab->addSym(sym, def, def ? current : NULL, type, binding, val); 
	}
	void addMemToCurSec(dword insMem)
	{
		if (checkBssCur()) throw BSSwrite();
		else current->endInsert(insMem); 
	}
	void addWordToCurSec(char* w)
	{
		if(checkBssCur()) throw BSSwrite();
		else current->insertWord(w);
	}
	void addCharToCurSec(char c)
	{
		if (checkBssCur()) throw BSSwrite();
		else current->insert(c);
	}
	int addSymRel(string name, RT type, int off);

	void backpatching();

	void outSymTab(ofstream *output)
	{
		///*output << "nesto, test" << endl;
		///ofstream &out = *output;
		///out << "jos nesto \\o//" << endl;
		symTab->outTab(output);
	}
	void checkUndefGlobal()
	{
		symTab->checkUndefGlobal();
	}

	void outSecs(ofstream *output);
};