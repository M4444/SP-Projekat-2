#pragma once

#include <string>

using namespace std;

enum SHT	// Section Header Type
{
	SHT_NULL	 = 0,			// - neaktivno zaglavlje; ne postoji odgovarajuca sekcija
	SHT_PROGBITS = 1,			// - sekcije ciji je sadrzaj nastao kao posledica prevodjenog koda
	SHT_SYMTAB	 = 2,			// - tabela simbola
	SHT_STRTAB	 = 3,			// - tabela stringova
	SHT_RELA	 = 4,			// - skecija sa relokacijama
	SHT_HASH	 = 5,			// - hash tabela simbola
	SHT_DYNAMIC	 = 6,			// - informacije potrebne za dinamicko vezivanje
	SHT_NOTE	 = 7,			// - informacije koje dodatno oznacavaju fajl
	SHT_NOBITS	 = 8,			// - sekcija ne zauzima protor u fajlu
	SHT_REL		 = 9,			// - sekcija sa relokacijama
	SHT_SHLIB	 = 10,			// - rezervisano za buduce koriscenje
	SHT_DYNSYM	 = 11,			//
	SHT_LOPROC	 = 0X70000000,	// - ulazi definisu opsege rezervisane za konkretan procesor,
	SHT_HIPROC	 = 0X7fffffff,	//   odnosno, za korisnika
	SHT_LOUSER	 = 0X80000000,	//
	SHT_HIUSER	 = 0Xffffffff	//
};

enum SHF	// Section Header Flags
{
	SHF_WRITE	  = 0x1,		// - upis u ovu sekciju je dozvoljen u toku izvrsavanja procese
	SHF_ALLOC	  = 0x2,		// - sekcija zauzima prostor u memoriji u toku izvrsavanja
	SHF_EXECINSTR = 0x4,		// - dozvoljeno je izvrsavanje sadrzaja ove sekcije
	SHF_MASKPROC  = 0Xf0000000	// - flegovi rezervisani za specificnosti pojedinih procesora
};

class Section
{
	//friend class SectionTab;
private:
	string name;
	SHT	type;
	int	flags;
	int	addr;
	///int /**/sh_offset;	ima tabelu?
	int	size;
	///int		sh_link;	tabela relokacija ima pokazivac kod sebe
	///int		sh_info;
	///int		sh_addralign;	poravnjanje - 0 i stebeni 2
	///int		sh_entsize;		velicina ulaza ako su fiksne
public:
	Section(string secName, SHT	secType, int attributes, int address = 0, int secSize = 0) 
	{ 
		name = secName;
		type = secType;
		flags = attributes;
		addr = address;
		size = secSize;
	}
	~Section() {}

	void setAddress(int address) { addr = address; }
	void setSize(int secSize) { size = secSize - addr; }

	string getName() { return name; }
	int getAddress() { return addr; }
	int getSize() { return size; }
};