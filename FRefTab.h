#pragma once

#include "Table.h"
#include "EnumRelType.h"

class FRef
{
private:
	int patch;
	RT type;
public:
	FRef(){}
	FRef(int p, RT t) : patch(p), type(t) {}
	~FRef(){}
	int getPatch() { return patch; }
	RT getRelType() { return type; }
};

class FRefTab : public Table<FRef>
{
public:
	FRefTab() {}
	FRefTab(int off, RT type) :Table(FRef(off, type)) {}
	~FRefTab() {}

	void addFRef(int off, RT type) { endInsert(FRef(off, type)); }
	bool boolFirst() { resetIterator(); return getBoolIt(); }
	FRef removeFRef()
	{
		resetIterator();
		if (getBoolIt() == false) return FRef(-1, RT_IMM32);
		FRef fr = getItEnt();
		removeFirst();
		return fr;
	}
};

