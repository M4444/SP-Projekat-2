#include "RelTab.h"

RelTab::~RelTab()
{
}

int RelTab::addRel(string name, RT type, int off)
{
	Elf_Sym *sym = symTab->getSymRef(name);

	if (sym != NULL)
	{
		Elf_Rel rel;

		if(sym->getDef() == false && sym->getBinding() != STB_EXTERN)
		{
			sym->addFRef(off, type);
			cout << "Obracanje u napred, simbol: " << name << endl;
		}

		if(sym->getBinding() == STB_GLOBAL || sym->getBinding() == STB_EXTERN)
		{
			rel = Elf_Rel(off, type, sym);
			endInsert(rel);
			return (-1)*INS_SIZE;
		}
		else if (sym->getBinding() == STB_LOCAL)
		{
			if (sym->getSection() == NULL) rel = Elf_Rel(off, type, NULL);	// dodati fref na mesto
			else
			{
				string sec = sym->getSection()->getName();
				rel = Elf_Rel(off, type, symTab->getSymRef(sec));
			}
			///rel = Elf_Rel(off, type, );
			endInsert(rel);
			return (-1)*INS_SIZE + sym->getValue();
		}
		else throw UnknownBinding();
	}
	else
	{
		sym = symTab->addUndSym(name, off);
		sym->addFRef(off, type);
		//if(type != STB_GLOBAL && type != STT_SECTION)
		//{
		cout << "Obracanje u napred, simbol: " << name << endl;
		//}
		return 0;
	}
}

void RelTab::outTab(ofstream *output)
{
	ofstream &out = *output;

	/*string name = bTab->getName();
	name = name.substr(0, 4);
	if(name.compare(".bss") == 0)
	{
		cout << "ISPISIVANJE BSS SEKCIJE " << name << endl;
		//return;
	}*/
	if(isEmpty()) return;

	out << "#.rel" << bTab->getName() << endl;
	out << "offset\t\tType\t\tVal[" << bTab->getName() << "]:" << endl;

	Elf_Rel *tek;
	for (resetIterator(); getBoolIt(); iteratorNext())
	{
		tek = getItEntPointer();

		tek->outRel(output);
	}
}