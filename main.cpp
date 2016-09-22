#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>
#include <string>
#include <stack>
#include <cstdlib>
#include "main.h"

using namespace std;

enum TYPES {CHAR, INT, FLOAT, DOUBLE, STRING};
enum COMMANDS {HALT, PRTCR, PRTC, PRTI, PRTF, PRTD, PRTS, PRTAC, PRTAI, PRTAF, PRTAD, PRTAS, PUSHC, PUSHI, PUSHF, PUSHD, PUSHS, PUSHAC, PUSHAI, PUSHAF, PUSHAD, PUSHAS, PUSHKC, PUSHKI, PUSHKF, PUSHKD, PUSHKS, POPC, POPI, POPF, POPD, POPS, POPX, POPAC, POPAI, POPAF, POPAD, POPAS, RDC, RDI, RDF, RDD, RDS, RDAC, RDAI, RDAF, RDAD, RDAS, JMP, JMPEQ, JMPNE, JMPGT, JMPGE, JMPLT, JMPLE, STX, STKX, INC, DEC, ADD, SUB, MUL, DIV, MOD, CMP};

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

//function variables
int tempAddress;
StackBlock tempBlock = {};
int tempInteger;
char* tempPointer;
string tempString;
bool errorFlag = false;
float tempFloat;
double tempDouble;

int cmpeval, arrindex;

int main(int argc, char *argv[])
{
	if(argc > 1)
		fileOpen(argv[1]);
	else
		fileOpen((char*)"CK.chop");

	copyrightCheck();

	if(mainSwitch())
		return 1;

	outfile.close();
	if(errorFlag)
		return 1;
	return 0;
}  //int main(int argc, char *argv[])

int mainSwitch()
{
	/*
	while(true && !errorFlag)
	{
		tempBlock = {};
      switch(youAreHere[evindex++]){
        case PRTCR:
          cout << "\n";
        break;
        case PRTC: prtcFunc();
        break;
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
        break;
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
        break;
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
        case HALT: system("pause");
          return 0;
        break;
        default: cout << "ERROR: Unrecognized Command.";
        break;
      }
  	}*/
      return 0;
}  //void mainSwitch()

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
}
