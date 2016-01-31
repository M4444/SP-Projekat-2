#pragma once

template <typename T>
class Table
{
private:
	struct Elem {
		T entry;
		Elem* next;
		Elem(T ent, Elem* n = 0)
		{
			entry = ent;
			next = n;
		}
	};
	Elem *first;

	Elem *iterator;

protected:
	void resetIterator() 
	{
		iterator = first; 
	}
	T getItEnt() { return iterator->entry; }
	T *getItEntPointer() { return &(iterator->entry); }
	bool getBoolIt() { return iterator; }
	void iteratorNext() { iterator = iterator->next; }

	void replItEnt(T newEnt) { iterator->entry = newEnt; }
public:
	Table() { first = 0; iterator = (Elem *)4; }
	Table(T ent)
	{
		first = new Elem(ent);
	}
	~Table() { removeAll(); }
	int length() const
	{
		int n = 0;
		for (Elem* tek = first; tek; tek = tek->next)
			n++;
		return n;
	}
	bool isEmpty()
	{
		if(length() == 0) return true;
		else return false;
	}
	void endInsert(T ent)
	{
		Elem* newE = new Elem(ent);
		if (!first) first = newE;
		else {
			Elem* cur = first;
			while (cur->next) cur = cur->next;
			cur->next = newE;
		}
		iterator = newE;
	}
	void removeAll()
	{
		while (first) {
			Elem* stari = first;
			first = first->next;
			delete stari;
		}
	}

	void removeFirst()
	{
		if (first) {
			Elem* stari = first;
			first = first->next;
			delete stari;
		}
	}
};
