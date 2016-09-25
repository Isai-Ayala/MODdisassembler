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

void normalFunc(const char* msg)
{
	outfile << msg << getVarName(chartodir(&youAreHere[evindex])) << std::endl;
	evindex += 2;
}  //void normalFunc(const char* msg)

void defFunc(char t, const char* msg)
{
	if(firstLoop)
	{
		arrResize(chartodir(&youAreHere[evindex]), t);
		return;
	}
	outfile << msg;
	getVarName2(chartodir(&youAreHere[evindex]));
	outfile << std::endl;
	evindex += 2;
}  //void defFunc()

void pushksFunc()
{
	outfile << "pushks \"";
	int i = youAreHere[evindex++];
	while(i-- > 0)
		outfile << youAreHere[evindex++];
	outfile << "\"" << std::endl;
}  //void pushksFunc()

void prtmFunc()
{
	outfile << "prtm \"";
	int i = youAreHere[evindex++];
	while(i-- > 0)
		outfile << youAreHere[evindex++];
	outfile << "\"" << std::endl;
}  //void prtmFunc()

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
        case PRTCR: outfile << "prtcr\n";
        break;
        case PRTC: normalFunc((const char*)"prtc var");
        break;
        case PRTI: normalFunc((const char*)"prti var");
        break;
        case PRTF: normalFunc((const char*)"prtf var");
        break;
        case PRTD: normalFunc((const char*)"prtd var");
        break;
        case PRTS: normalFunc((const char*)"prts var");
        break;
        case PRTAC: normalFunc((const char*)"prtac var");
        break;
        case PRTAI: normalFunc((const char*)"prtai var");
        break;
        case PRTAF: normalFunc((const char*)"prtaf var");
        break;
        case PRTAD: normalFunc((const char*)"prtad var");
        break;
        case PRTAS: normalFunc((const char*)"prtas var");
        break;
        case PUSHC: normalFunc((const char*)"pushc var");
        break;
        case PUSHI: normalFunc((const char*)"pushi var");
        break;
        case PUSHF: normalFunc((const char*)"pushf var");
        break;
        case PUSHD: normalFunc((const char*)"pushd var");
        break;
        case PUSHS: normalFunc((const char*)"pushs var");
          break;
        case PUSHAC: normalFunc((const char*)"pushac var");
        break;
        case PUSHAI: normalFunc((const char*)"pushai var");
        break;
        case PUSHAF: normalFunc((const char*)"pushaf var");
        break;
        case PUSHAD: normalFunc((const char*)"pushad var");
        break;
        case PUSHAS: normalFunc((const char*)"pushas var");
        break;
        case PUSHKC: 
			outfile << "pushkc " << (char)youAreHere[evindex] << std::endl;
			evindex++;
        break;
        case PUSHKI: 
			outfile << "pushki " << chartoint(&youAreHere[evindex]) << std::endl;
			evindex += 4;
        break;
        case PUSHKF: 
			outfile << "pushkf " << chartofloat(&youAreHere[evindex]) << std::endl;
			evindex += 4;
        break;
        case PUSHKD: 
			outfile << "pushkd " << chartodouble(&youAreHere[evindex]) << std::endl;
			evindex += 8;
        break;
        case PUSHKS: pushksFunc();
        break;
        case POPC: defFunc('c', (const char*)"popc var");
        break;
        case POPI: defFunc('i', (const char*)"popi var");
        break;
        case POPF: defFunc('f', (const char*)"popf var");
        break;
        case POPD: defFunc('d', (const char*)"popd var");
        break;
        case POPS: defFunc('s', (const char*)"pops var");
        break;
        case POPX: outfile << "popx\n";
        break;
        case POPAC: defFunc('C', (const char*)"popac var");
        break;
        case POPAI: defFunc('I', (const char*)"popai var");
        break;
        case POPAF: defFunc('F', (const char*)"popaf var");
        break;
        case POPAD: defFunc('D', (const char*)"popad var");
        break;
        case POPAS: defFunc('S', (const char*)"popas var");
        break;
        case RDC: defFunc('c', (const char*)"rdc var");
        break;
        case RDI: defFunc('i', (const char*)"rdi var");
        break;
        case RDF: defFunc('f', (const char*)"rdf var");
        break;
        case RDD: defFunc('d', (const char*)"rdd var");
        break;
        case RDS: defFunc('s', (const char*)"rds var");
        break;
        case RDAC: defFunc('C', (const char*)"rdac var");
        break;
        case RDAI: defFunc('I', (const char*)"rdai var");
        break;
        case RDAF: defFunc('F', (const char*)"rdaf var");
        break;
        case RDAD: defFunc('D', (const char*)"rdad var");
        break;
        case RDAS: defFunc('S', (const char*)"rdas var");
        break;
        case JMP: normalFunc((const char*)"jmp var");
        break;
        case JMPEQ: normalFunc((const char*)"jmpeq var");
        break;
        case JMPNE: normalFunc((const char*)"jmpne var");
        break;
        case JMPGT: normalFunc((const char*)"jmpgt var");
        break;
        case JMPGE: normalFunc((const char*)"jmpge var");
        break;
        case JMPLT: normalFunc((const char*)"jmplt var");
        break;
        case JMPLE: normalFunc((const char*)"jmple var");
        break;
        case STX: normalFunc((const char*)"stx var");
        break;
        case STKX: 
        	outfile << "stkx " << chartoint(&youAreHere[evindex]) << std::endl;
        	evindex += 4;
        break;
        case INC: normalFunc((const char*)"inc var");
        break;
        case DEC: normalFunc((const char*)"dec var");
        break;
        case ADD: outfile << "add\n";
        break;
        case SUB: outfile << "sub\n";
        break;
        case MUL: outfile << "mul\n";
        break;
        case DIV: outfile << "div\n";
        break;
        case MOD: outfile << "mod\n";
        break;
        case CMP: outfile << "cmp\n";
        break;
        case PRTM: prtmFunc();
        break;
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

void getVarName2(int dir)
{
	int i;
	for(i = 0; vararr[i][0] != dir && i < vars;i++)
	{
	}
	outfile << i;
}  //char* getVarName()

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
