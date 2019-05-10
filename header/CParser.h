#ifndef CPARSER 
#define CPARSER

#include "header/CException.h"

class CParser {

	private :

	public :

		static void PARSeparateString(char cToken, char* pcStr1, char* pcStr2); 
		static bool PARIsStringEqual(const char* pccStr1, const char* pccStr2);
		static bool PARIsStringANumericalValue(const char * pcStr);
};

#endif