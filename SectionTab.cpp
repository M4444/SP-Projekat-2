#include "SectionTab.h"
#include "SymTab.h"
#include "ByteSection.h"
#include "WordAnalyzer.h"

bool SectionTab::sectionExists(string name)
{
	Section *sec;

	for (resetIterator(); getBoolIt(); iteratorNext())
	{
		sec = getItEnt();
		if (name.compare(sec->getName()) == 0) return true;
	}
	return false;
}

void SectionTab::createSection(string secTypeName, string name)
{
	///Section sec = Section();

	if (secTypeName.compare(".text") == 0)
	{
		current = new ByteSection(name, SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR);
	}
	else if (secTypeName.compare(".bss") == 0)
	{
		current = new ByteSection(name, SHT_NOBITS, SHF_ALLOC | SHF_WRITE);
	}
	else if (secTypeName.compare(".data") == 0)
	{
		current = new ByteSection(name, SHT_PROGBITS, SHF_ALLOC | SHF_WRITE);
	}

	symTab->addSym(name, true, current, STT_SECTION, STB_LOCAL, 0);

	endInsert(current);

	if(secTypeName.compare(".bss") != 0)
	{
		RelTab *relTab = new RelTab(symTab, current);
		endInsert(relTab);
	}
}

int SectionTab::addSymRel(string name, RT type, int off)
{
	Section *sec;
	for (resetIterator(); getBoolIt(); iteratorNext())
	{
		sec = getItEnt();
		if ((sec->getName()).compare(".rel") == 0)
		{
			RelTab *relTab = (RelTab*) sec;
			if (relTab->getBSPointer() == current)
			{
				return relTab->addRel(name, type, off);
			}
		}
	}
}

void SectionTab::backpatching()
{
	Elf_Sym *sym;
	FRef fr;

	Section *sec;
	int val;
	int offset;
	RT rt;
	while (true)
	{
		sym = symTab->getUnpSym();
		if (sym == NULL) break;

		///cout << 1;
		while (true)
		{
			fr = sym->removeFRTE();
			if (fr.getPatch() < 0) break;

			sec = sym->getSection();	//get section from symbol
			val = sym->getValue();		//value from symbol
			rt = fr.getRelType();		//get rel type from patch
			offset = fr.getPatch();		//get offset from patch

			if (sec == NULL) continue;
			string name = sec->getName();
			name = name.substr(0, 4);
			if (name.compare(".bss") == 0) continue;

			Section *tekSec;
			for (resetIterator(); getBoolIt(); iteratorNext())
			{
				tekSec = getItEnt();
				if ((tekSec->getName()).compare(sec->getName()) == 0)
				{
					ByteSection *byteSec = (ByteSection*)sec;		
					dword insMem = WordAnalyzer::creteMemRep(rt, val);
					byteSec->replace(insMem, offset);	//replace entry in ByteTable
					break;
				}
			}
		}
	}
}

void SectionTab::outSecs(ofstream *output)
{
	Section *sec;
	for (resetIterator(); getBoolIt(); iteratorNext())
	{
		sec = getItEnt();
		if ((sec->getName()).compare(".rel") == 0)
		{
			RelTab *relTab = (RelTab*)sec;
			
			relTab->outTab(output);
		}
	}
	for (resetIterator(); getBoolIt(); iteratorNext())
	{
		sec = getItEnt();
		if ((sec->getName()).compare(".rel") != 0)
		{
			string name = sec->getName();
			name = name.substr(0, 4);
			if (name.compare(".bss") != 0)
			{
				ByteSection *byteSec = (ByteSection*)sec;

				byteSec->outTab(output);
			}
		}
	}
}