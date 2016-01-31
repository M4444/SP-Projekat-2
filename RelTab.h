#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Section.h"
#include "Table.h"
#include "Elf_Rel.h"
#include "SymTab.h"
#include "ByteSection.h" 

class UnknownBinding {};

class RelTab : public Section, public Table<Elf_Rel>
{
private:
	SymTab *symTab;
	ByteSection *bTab;
public:
	///RelTab();
	RelTab(SymTab *st, ByteSection *bt, int address = 0, int secSize = 0) :
		Section(".rel", SHT_REL, 0, address, secSize), symTab(st), bTab(bt) {}
	~RelTab();

	ByteSection *getBSPointer() { return bTab; }

	int addRel(string name, RT type, int off);
	void outTab(ofstream *output);
};