#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "WordAnalyzer.h"

//using namespace std;

int main(int argc, char *argv[])
{
	ifstream input;
	ofstream output;
	string line;
	string word;

	WordAnalyzer *WA;

	//if(strlen(argv[1]) == 1 && argv[1][0] == '0') WA = new WordAnalyzer('0', argv[3]);
	//else if(strlen(argv[1]) == 1 && argv[1][0] == '1') WA = new WordAnalyzer('1', argv[3]);
	if(strlen(argv[1]) == 1 && (argv[1][0] == '0' || argv[1][0] == '1'))
	{
		WA = new WordAnalyzer(argv[1][0], argv[3]);
	}
	else
	{
		std::cout << "*Invalid arguments*";
		return -1;
	}


	input.open(argv[2]);
	output.open("outEx.txt");	///////////////////

	if (input.is_open())
	{
		bool fileEnd = false;
		bool firstLine = true;	///////////////////
		bool newLine;
		while (getline(input, line) && !fileEnd)
		{
			newLine = true;
			if (!firstLine) output << endl;		///////////////////
			if(!firstLine) std::cout << endl;	///////////////////
			else firstLine = false;				///////////////////

			istringstream inLine(line);
			bool firstWord = true;		///////////////////
			while (inLine >> word)
			{
				try 
				{
					WA->pass(word, newLine);
				}
				catch (BadSyntax)
				{
					std::cout << "*Syntax error*" << endl;
					return -2;
				}
				catch (OutOfRange)
				{
					std::cout << "*Number out of range*" << endl;
					return -3;
				}
				catch (SectionRedefinition)
				{
					std::cout << "*Section already defined*" << endl;
					return -4;
				}
				catch (SymbolRedefinition)
				{
					std::cout << "*Symbol already defined*" << endl;
					return -5;
				}
				catch (BSSwrite)
				{
					std::cout << "*Can't write to BSS*" << endl;
					return -6;
				}
				catch(UnknownBinding)
				{
					std::cout << "*Unknown binding*" << endl;
					return -7;
				}
				catch(NoSection)
				{
					std::cout << "*Outside of section*" << endl;
					return -8;
				}
				catch (EndOfFile)
				{
					fileEnd = true;
					output << ".end" << endl;		///////////////////
					std::cout << ".end" << endl;	///////////////////
					break;
				}

				if (!firstWord) output << ' ';		///////////////////
				if(!firstWord) std::cout << ' ';	///////////////////
				else firstWord = false;				///////////////////
				output << word;						///////////////////
				std::cout << word;					///////////////////

				newLine = false;
			}
		}
		input.close();
		output.close();
	}
	else
	{
		std::cout << "*Unable to open input file*" << endl;
		return -1;
	}

	return 0;
}