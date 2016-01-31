#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Section.h"
#include "Elf_Sym.h"
#include "Table.h"

using namespace std;

class SymbolRedefinition {};

class SymTab : public Section, public Table<Elf_Sym>
{
public:
	///SymTab();
	SymTab(int address = 0, int secSize = 0):
		Section(".symtab", SHT_SYMTAB, 0, address, secSize){}

	void addSym(string sym, bool defined, Section *section, STT type, STB binding, int val = 0);
	Elf_Sym *addUndSym(string sym, int off);
	Elf_Sym *getSymRef(string name);
	Elf_Sym *getUnpSym();
	void setSymSize(string name, int size);
	void setSymVal(string name, int size);

	void checkUndefGlobal();

	///ostream& operator<<(ostream &os, const SymTab &st);
	void outTab(ofstream *output);
};