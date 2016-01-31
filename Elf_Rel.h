#pragma once

#include "Elf_Sym.h"
#include "EnumRelType.h"

class Elf_Rel
{
private:
	int		offest;			// Beginning of instruction location offset
	RT		info;			// Relocation type
	Elf_Sym	*sym;			// Pointer to the symbol to be relocated
public:
	Elf_Rel() {}
	Elf_Rel(int off, RT inf, Elf_Sym *s) :offest(off), info(inf), sym(s) {}

	///string getName() { return name; }
	void outRel(ofstream *output)
	{
		ofstream &out = *output;
		string i;
		switch (info)
		{
		case RT_IMM32:		i = "RT_IMM32"; break;
		case RT_IMM2x16:	i = "RT_IMM2x16"; break;
		case RT_IMM16:		i = "RT_IMM16"; break;
		case RT_IMM18:		i = "RT_IMM18"; break;
		case RT_IMM21:		i = "RT_IMM21"; break;
		case RT_IMM21_PC:	i = "RT_IMM21_PC"; break;
		case RT_IMM24:		i = "RT_IMM24"; break;
		case RT_IMM24_PC:	i = "RT_IMM24_PC"; break;
		case RT_IMM5:		i = "RT_IMM5"; break;
		}
		out << setfill('0') << setw(8) << offest << '\t' << i << '\t' << sym->getNum() << endl;
	}
};