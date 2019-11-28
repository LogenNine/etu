#include <windows.h>
#include <iostream>

using namespace std;

//This function converts numbers into binary code
void bitRep(long long int* ap, int aByteSize, char prefix)
{
	long long int a = *ap;
	int aBitSize = aByteSize * 8;
	long long int b = a & (1LL << (aBitSize - 1));
	cout << (b == 0 ? 0 : 1) << " ";
	//color code starts
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	/* Save current attributes */
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	//color code ends
	if (prefix == 'f' || prefix == 'F')
	{
		for (int i = aBitSize - 2; i >= aBitSize-2-7; --i) {
			long long int b = a & (1LL << i);
			cout << (b == 0 ? 0 : 1);
			//	if ((i & 3) == 0) cout << " ";
		} // for
		cout << " ";
		for (int i = aBitSize - 2-7-1; i >= 0; --i) {
			long long int b = a & (1LL << i);
			cout << (b == 0 ? 0 : 1);
			//	if ((i & 3) == 0) cout << " ";
		} // for
	}
	else if (prefix == 'd' || prefix == 'D')
	{
		for (int i = aBitSize - 2; i >= aBitSize - 2 - 10; --i) {
			long long int b = a & (1LL << i);
			cout << (b == 0 ? 0 : 1);
			//	if ((i & 3) == 0) cout << " ";
		} // for
		cout << " ";
		for (int i = aBitSize - 2 - 10 - 1; i >= 0; --i) {
			long long int b = a & (1LL << i);
			cout << (b == 0 ? 0 : 1);
			//	if ((i & 3) == 0) cout << " ";
		} // for
	}
	else
	{
		for (int i = aBitSize - 2; i >= 0; --i) {
			long long int b = a & (1LL << i);
			cout << (b == 0 ? 0 : 1);
			//	if ((i & 3) == 0) cout << " ";
		} // for
	} // else
	SetConsoleTextAttribute(hConsole, saved_attributes); //return color to normal
    cout << endl; 
}//bitRep

//This function handles wrong number inputs from user
template<typename Type>
bool Fail(Type min, Type max)
{
	char next = cin.peek();
	if (cin.fail() || next != '\n') {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << endl << "Try to enter correct number from  " << min << " to " << max << endl;
		return true;
	}
	return false;
}//Fail

//This function randomly changes selected bit
bool bitRep2(long long int* ap, int aByteSize, char prefix) //todo return numbers back to decimals
{
	long long int a = *ap;
	int bitNumber = 0;
	int bitNumberMax = aByteSize * 8 - 1;
	cout << "Now enter bit number in range from 0 to " << bitNumberMax << endl;
	cin >> bitNumber;
	if (Fail<int>(0, bitNumberMax)) return false;
	if (bitNumber < 0 || bitNumber>bitNumberMax) {
		cout << "Wrong input, bit number should be in range 0 to " << bitNumberMax << endl;
		return false;
	}
	int bitValue = rand() > RAND_MAX / 2 ? 1 : 0;
	long long int bit = 1LL << bitNumber;
	if ((a & bit) != 0 && bitValue == 0) a = a & ~bit;
	if ((a & bit) == 0 && bitValue == 1) a = a | bit;
	cout << bitValue << " This is random value for selected bit" << endl;
	//int b = ~bit;
	//bitRep((long long int*) & b, sizeof(b), prefix);
	bitRep((long long int*) & a, aByteSize, prefix);
	return true;
}//bitRep2


void help() {
	cout << "Prefix i or I means int, after it you can type arabic number no smaller than " << INT_MIN << " and no bigger than " << INT_MAX << endl;
	cout << "Prefix s or S means short int, after it you can type arabic number no smaller than " << SHRT_MIN << " and no bigger than " << SHRT_MAX << endl;
	cout << "Prefix u or U means unsigned int, after it you can type arabic number no smaller than " << 0 << " and no bigger than " << UINT_MAX << endl;
	cout << "Prefix f or F means float, after it you can type arabic number no smaller than " << FLT_MIN << " and no bigger than " << FLT_MAX << endl;
	cout << "Prefix d or D means double, after it you can type arabic number no smaller than " << DBL_MIN << " and no bigger than " << DBL_MAX << endl;
	cout << "Correct inputs: i34, U499999, f3.1415, d0.9999999, D1.23e-269"<< endl;
	cout << "Wrong inputs: int thirty two, CHETIRE, asdasdasd, S4e+2, u-99, d9.9e-9999, s 3, help, /;%$&* "<<endl;
}


//In main we get inputs from user and relay it to functions
int main() {
	for (;;)
	{
		help();
		cout << endl << "Enter prefix followed by number:" << endl; //TODO: more info
		char prefix = 0;
		cin >> prefix;
		switch (prefix)
		{
		case 'i': case 'I': {
			int a = 0;
			cin >> a;
			if (Fail<int>(INT_MIN, INT_MAX)) continue;
			bitRep((long long int*)& a, sizeof(a), prefix);
			if (!bitRep2((long long int*) & a, sizeof(a), prefix)) continue;
			break;
		}
		case 's': case 'S':{
			short int si = 0;
			cin >> si;
			if (Fail<short>(SHRT_MIN, SHRT_MAX)) continue;
			bitRep((long long int*) & si, sizeof(si), prefix);
			if (!bitRep2((long long int*) & si, sizeof(si), prefix)) continue;
			break;
		}
		case 'u': case 'U': {
			unsigned int ui = 0;
			cin >> ui;
			if (Fail<unsigned>(0, UINT_MAX)) continue;
			bitRep((long long int*) & ui, sizeof(ui), prefix);
			if (!bitRep2((long long int*) & ui, sizeof(ui), prefix)) continue;
			break;
		}
		case 'f': case 'F': {
			float f = 0.0F;
			cin >> f;
			if (Fail<float>(FLT_MIN, FLT_MAX)) continue;
			bitRep((long long int*) & f, sizeof(f), prefix);
			if (!bitRep2((long long int*) & f, sizeof(f), prefix)) continue;
			break;
		}
		case 'd': case 'D': {
			double d = 0;
			cin >> d;
			if (Fail<double>(DBL_MIN, DBL_MAX)) continue;
			bitRep((long long int*) & d, sizeof(d), prefix);
			if (!bitRep2((long long int*) & d, sizeof(d), prefix)) continue;
			break;
		}
		default : 
		{
			cout << endl << "error: wrong prefix" << endl << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
		} //switch
	} // for
	return 0;
}
