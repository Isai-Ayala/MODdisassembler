#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <string>
#include <stack>
#include <cstdlib>
#include "main.h"
#include "conversion.h"

using namespace std;

enum TYPES {CHAR, INT, FLOAT, DOUBLE, STRING};
enum COMMANDS {HALT, PRTCR, PRTC, PRTI, PRTF, PRTD, PRTS, PRTAC, PRTAI, PRTAF, PRTAD, PRTAS, PUSHC, PUSHI, PUSHF, PUSHD, PUSHS, PUSHAC, PUSHAI, PUSHAF, PUSHAD, PUSHAS, PUSHKC, PUSHKI, PUSHKF, PUSHKD, PUSHKS, POPC, POPI, POPF, POPD, POPS, POPX, POPAC, POPAI, POPAF, POPAD, POPAS, RDC, RDI, RDF, RDD, RDS, RDAC, RDAI, RDAF, RDAD, RDAS, JMP, JMPEQ, JMPNE, JMPGT, JMPGE, JMPLT, JMPLE, STX, STKX, INC, DEC, ADD, SUB, MUL, DIV, MOD, CMP, PRTM};

int evindex;
char* memoryMapper;

union Data {
  int i;
  float f;
  double d;
  char* s;
};

struct StackBlock {
  char typecode;
  union Data data;
};

stack<StackBlock> theStack;

char copyright[10] = {'(','C',')','C','H','U','N','K','U','N'};
int codeSegment = 0;
int dataSegment = 0;
int someIndex = 0;
ifstream inFile;
std::ofstream outfile("CK.rice");
size_t size = 0;
char* oData = 0;
char* youAreHere;
int **vararr = NULL; //variable array
size_t vars = 0;

//function variables
int tempAddress;
StackBlock tempBlock = {};
int tempInteger;
char* tempPointer;
string tempString;
bool errorFlag = false;
float tempFloat;
double tempDouble;
bool firstLoop = true;

int cmpeval, arrindex;

int main(int argc, char *argv[])
{
	if(argc > 1)
		fileOpen(argv[1]);
	else
		fileOpen((char*)"CK.chop");

	copyrightCheck();

	mainSwitch();
	firstLoop = false;
	evindex = 14;
	setVarName();

	std::cout << "firstLoop done!!!\n\n\n";

	if(mainSwitch())
		return 1;

	outfile.close();
	if(errorFlag)
		return 1;
	return 0;
}  //int main(int argc, char *argv[])

void prtcrFunc()
{
	outfile << "prtcr \n";
}  //void prtcrFunc()

void pushkiFunc()
{
	outfile << "pushki " << chartoint(&youAreHere[evindex]) << std::endl;
	evindex += 4;
}  //void pushkiFunc()

void pushkcFunc()
{
	outfile << "pushkc '" << (char)youAreHere[evindex] << "'" <<  std::endl;
	evindex++;
}  //void pushkcFunc()

void popiFunc()
{
	if(firstLoop)
	{
		arrResize(chartodir(&youAreHere[evindex]), 'i');
		return;
	}
	outfile << "popi var" << getVarName(chartodir(&youAreHere[evindex])) << std::endl;
	evindex += 2;
}  //void popiFunc()

void popcFunc()
{
	if(firstLoop)
	{
		arrResize(chartodir(&youAreHere[evindex]),'c');
		return;
	}
	outfile << "popc var" << getVarName(chartodir(&youAreHere[evindex])) << std::endl;
	evindex += 2;
}  //void popcFunc()

void pushkfFunc()
{
	outfile << "pushkf " << chartofloat(&youAreHere[evindex]) << std::endl;
	evindex += 4;
}  //void pushkfFunc()

void pushkdFunc()
{
	outfile << "pushkd " << chartodouble(&youAreHere[evindex]) << std::endl;
	evindex += 8;
}  //void pushkdFunc()

void pushksFunc()
{
	outfile << "pushks \"";
	int i = youAreHere[evindex++];
	while(i-- > 0)
		outfile << youAreHere[evindex++];
	outfile << "\"" << std::endl;
}  //void pushksFunc()

int mainSwitch()
{
	while(true && !errorFlag)
	{
		tempInteger = evindexjmp();
		if(tempInteger)
		{
			evindex += tempInteger;
			continue;
		}
		if(firstLoop && youAreHere[evindex] == PRTCR)
		{
			evindex++;
			continue;
		}
		if(firstLoop && youAreHere[evindex] == HALT)
			return 0;
		StackBlock reset = {};
		tempBlock = reset;

		printf("instruction: %x \n", youAreHere[evindex]);

      switch(youAreHere[evindex++]){ 
        case PRTCR: prtcrFunc();
        break;
        case PRTC: outfile << "prtc '" << youAreHere[evindex++] << "'\n";
        break;/*
        case PRTI: prtiFunc();
        break;
        case PRTF: prtfFunc();
        break;
        case PRTD:prtdFunc();
        break;
        case PRTS: prtsFunc();
        break;
        case PRTAC: prtacFunc();
        break;
        case PRTAI: prtaiFunc();
        break;
        case PRTAF: prtafFunc();
        break;
        case PRTAD: prtadFunc();
        break;
        case PRTAS: prtasFunc();
        break;
        case PUSHC: pushcFunc();
        break;
        case PUSHI: pushiFunc();
        break;
        case PUSHF: pushfFunc();
        break;
        case PUSHD: pushdFunc();
        break;
        case PUSHS: pushsFunc();
          break;
        case PUSHAC: pushacFunc();
        break;
        case PUSHAI: pushaiFunc();
        break;
        case PUSHAF: pushafFunc();
        break;
        case PUSHAD: pushadFunc();
        break;
        case PUSHAS: pushasFunc();
        break;*/
        case PUSHKC: pushkcFunc();
        break;
        case PUSHKI: pushkiFunc();
        break;
        case PUSHKF: pushkfFunc();
        break;
        case PUSHKD: pushkdFunc();
        break;
        case PUSHKS: pushksFunc();
        break;
        case POPC: popcFunc();
        break;
        case POPI: popiFunc();
        break;/*
        case POPF: popfFunc();
        break;
        case POPD: popdFunc();
        break;
        case POPS: popsFunc();
        break;
        case POPX: if(!popxFunc()) return 1;
        break;
        case POPAC: popacFunc();
        break;
        case POPAI: popaiFunc();
        break;
        case POPAF: popafFunc();
        break;
        case POPAD: popadFunc();
        break;
        case POPAS: popasFunc();
        break;
        case RDC: if(!rdcFunc()) return 1;
        break;
        case RDI: rdiFunc();
        break;
        case RDF: rdfFunc();
        break;
        case RDD: rddFunc();
        break;
        case RDS: rdsFunc();
        break;
        case RDAC: if(!rdacFunc()) return 1;
        break;
        case RDAI: rdaiFunc();
        break;
        case RDAF: rdafFunc();
        break;
        case RDAD: rdadFunc();
        break;
        case RDAS: rdasFunc();
        break;
        case JMP: jmpFunc();
        break;
        case JMPEQ: jmpeqFunc();
        break;
        case JMPNE: jmpneFunc();
        break;
        case JMPGT: jmpgtFunc();
        break;
        case JMPGE: jmpgeFunc();
        break;
        case JMPLT: jmpltFunc();
        break;
        case JMPLE: jmpleFunc();
        break;
        case STX: stxFunc();
        break;
        case STKX: stkxFunc();
        break;
        case INC: incFunc();
        break;
        case DEC: decFunc();
        break;
        case ADD: if(!addFunc()) return 1;
        break;
        case SUB: if(!subFunc()) return 1;
        break;
        case MUL: if(!mulFunc()) return 1;
        break;
        case DIV: if(!divFunc()) return 1;
        break;
        case MOD: if(!modFunc()) return 1;
        break;
        case CMP: cmpFunc();
        break;
        case PRTM:
        break;*/
        case HALT: outfile << "halt\n";
          return 0;
        break;
        default: cout << "ERROR: Unrecognized Command.";
        break;
      }
  	}
      return 0;
}  //void mainSwitch()

int evindexjmp()
{
	if(firstLoop)
	{
		if(youAreHere[evindex] > PRTCR && youAreHere[evindex] < ADD && youAreHere[evindex] != POPX)
		{
			if(youAreHere[evindex] < PUSHKC || youAreHere[evindex] > RDAS)
				return 3;
			else
				if(youAreHere[evindex] == PUSHKC)
					return 2;
				else
					if(youAreHere[evindex] == PUSHKI || youAreHere[evindex] == PUSHKF)
						return 5;
					else
						if(youAreHere[evindex] == PUSHKD)
							return 9;
						else
							if(youAreHere[evindex] == PUSHKS)
							{
								return (int)youAreHere[++evindex] + 1;
							}
		}
		else
			if(youAreHere[evindex] == PRTM)
			{
				return (int)youAreHere[++evindex] + 2;
			}
	}
	return 0;
}  //int evindexjmp()

int getVarName(int dir)
{
	int i;
	for(i = 0; vararr[i][0] != dir && i < vars;i++)
	{
	}
	return i;
}  //char* getVarName()

void setVarName()
{
	int i = 0;
	char *varN;
	while(i < vars)
	{
		std::cout << "var" << i << "  varindeeeex  " << vararr[i][1] << std::endl;
		switch(vararr[i][1])
		{
			case 'i': outfile << "defi var" << i << std::endl;
			break;
			case 'f': outfile << "deff var" << i << std::endl;
			break;
			case 'd': outfile << "defd var" << i << std::endl;
			break;
			case 'c': outfile << "defc var" << i << std::endl;
			break;
			case 's': outfile << "defs var" << i << std::endl;
			break;
			case 'I': outfile << "defai var" << i << std::endl;
			break;
			case 'F': outfile << "defaf var" << i << std::endl;
			break;
			case 'D': outfile << "defad var" << i << std::endl;
			break;
			case 'C': outfile << "defac var" << i << std::endl;
			break;
			case 'S': outfile << "defas var" << i << std::endl;
			break; 
		}
		i++;
	}
}  //void setVarName()

void arrResize(int dir, char type)
{
	if(vars == 0)
	{
		vars++;
		vararr = new int *[1];
		vararr[0] = new int[2];
		vararr[0][0] = dir;
		vararr[0][1] = (int)type;
		evindex += 2;
		return;
	}
	int ** temparr = new int*[++vars];
	bool sum = false;
	std::cout << "first check\n";
	for(int i = 0; i < vars; i++)
	{
		if(!sum && dir == vararr[i][0])
			return;
		std::cout << "r\n";
		temparr[i] = new int[2];
		if(sum)
		{
			temparr[i][0] = vararr[i-1][0];
			temparr[i][1] = vararr[i-1][1];
		}
		else
		{
			if(dir < vararr[i][0])
			{
				sum = true;
				temparr[i][0] = dir;
				temparr[i][1] = (int)type;
			}
			else
			{
			temparr[i][0] = vararr[i][0];
			temparr[i][1] = vararr[i][1];
			}
		}
		std::cout << temparr[i][0] << "typeee: " << temparr[i][1] << "   hey world! \n";
	}
	std::cout << "out of loop\n";
	vararr = temparr;
	evindex += 2;
}  //void arrResize(int dir, char type)


void fileOpen(char *fileName)
{
  inFile.open(fileName,ios::in|ios::binary|ios::ate);

  inFile.seekg(0, ios::end);
  size = inFile.tellg();
  cout << "Size of file: " << size << endl;
  inFile.seekg(0, ios::beg);

  oData = new char[size+1];
  inFile.read(oData, size);
  oData[size] = '\0';
  cout << "oData size: " << strlen(oData) <<  endl;
} // void fileOpen()

void copyrightCheck()
{
  youAreHere = oData;

  while(someIndex<10) {
    if(copyright[someIndex] != youAreHere[someIndex]) {
      cout << "FATAL ERROR: Key not present.\n";
      errorFlag = true;
      return ;
    }
    someIndex++;
  }
  std::cout << "successful copyright!\n";
  evindex = 14;
}
