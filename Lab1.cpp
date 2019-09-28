//#include <windows.h>
#include <iostream>
using namespace std;
void bitRep(int* ap)
{
	int a = *ap;
	int aByteSize = sizeof(a);
	int aBitSize = aByteSize * 8;
	int aBitSizeCopy = aBitSize;
	for (int i = aBitSizeCopy; i > 0; --i) {
		int b = a & (1 << i);
		if (b == 0) std::cout << 0;
		else std::cout << 1;

	}
	int b = a & (1 << (aBitSize - 1));
	std::cout << " " << (b == 0 ? 0: 1 );
    std::cout << "\n"; 
}

int main() {
	int a = 63;
	bitRep(&a);
	float f = 3.14;
	bitRep((int*)&f);
	return 0;
}

/* color
const WORD colors[] =
{
0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
};

HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
WORD   index = 0;


SetConsoleTextAttribute(hstdout, colors[index]);
FlushConsoleInputBuffer(hstdin);
color end*/
