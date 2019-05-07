#ifndef CPARSER 
#define CPARSER

#include <iostream>
#include <fstream>

using namespace std;

class CParser {

	public :

		static void PARSeparateString(char cToken, char* pcStr1, char* pcStr2); 
		static bool PARIsStringEqual(const char* pccStr1, const char* pccStr2);
		static bool PARIsStringANumericalValue(const char * pcStr);

};

#endif