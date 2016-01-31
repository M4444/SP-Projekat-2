#pragma once

#include <string>
#include "FRefTab.h"

using namespace std;

enum STT	// Symbol Table Type
{
	STT_NOTYPE	= 0,
	STT_OBJECT	= 1,	// - simbol je vezan za neki podatak
	STT_FUNC	= 2,	// - simbol vezan za funkciju ili drugi izvrsni kod
	STT_SECTION = 3,	// - simbol vezan za sekciju, lokalni i obicno prisutan samo za potrebe relokacije
	STT_FILE	= 4,	// - apsolutni lokalni fajl simbol, koji prethodi ostalim lokalnim simbolima iz istog fajla, ukoliko postoji
	STT_LOPROC	= 13,
	STT_HIPROC	= 15
};

enum STB	// Symbol Table Binding
{
	STB_LOCAL	= 0,
	STB_GLOBAL  = 1,
	STB_WEAK	= 2,	// - globalno vidljivi, manjeg prioriteta (ako niko drugi ne definise isti simbol)
	STB_EXTERN	= 3,
	STB_LOPROC	= 13,
	STB_HIPROC	= 15
};

class Elf_Sym 
{
	//friend class SymTab;

private:
	string	name;			// Symbol name
	int		value;			// Section offset, or VM address
	int		size;			// Object size in bytes
	char	type : 4,		// Data, func, section, or src file name (4 bits)
			binding : 4;	// Local or global (4 bits)
	char	reserved;		// Unused
	Section	*section;		// Section pointer
	bool	defined;		// Defined
	FRefTab *fRefTab;		// Pointer to forward reference table
	int		num;

public:
	Elf_Sym() {}
	Elf_Sym(string n, bool def, Section *sec, STT t, STB b, int val=0, int s=0)
		:name(n), value(val), size(s), type(t), binding(b), reserved(0), 
		section(sec), defined(def), fRefTab(NULL), num(0) {}
	~Elf_Sym() { if(fRefTab!=NULL) delete fRefTab; }

	string getName() { return name; }
	void copyInfo(Elf_Sym s) { value = s.value; type = s.type;  binding = s.binding; section = s.section; defined = s.defined; }
	char getBinding() { return binding; }
	Section	*getSection() { return section; }
	int getValue() { return value; }
	bool getDef() { return defined; }
	char getType() { return type; }
	int getNum(){ return num; }
	FRefTab *getFRefTab() { return fRefTab; }
	FRef removeFRTE() { return fRefTab->removeFRef(); }
	void setSize(int s) { size = s; }
	void setAddress(int val) { value = val; }
	void setBinding(STB bind) { binding = bind; }
	void addFRef(int off, RT type) 
	{
		if (fRefTab == NULL) fRefTab = new FRefTab(off, type);
		else fRefTab->addFRef(off, type);
	}

	void outSym(ofstream *output, int n)
	{
		ofstream &out = *output;
		num = n;

		string sec;
		if (section == NULL) sec = "UND";
		else sec = section->getName();
		string bind;
		if (binding == STB_LOCAL) bind = "local";
		else if(binding == STB_GLOBAL || binding == STB_EXTERN) bind = "global";
		else bind = "other";

		out << num << ":\t" << name << '\t' << sec << '\t' << value << '\t' << size << '\t' << bind << endl;
	}
};

#define INS_SIZE 4

/// 11:34 ako treba da ima proveru za global i extern simbole, dodatna polja

// ~ add sym to simbol table
// label = sym;