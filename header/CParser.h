#ifndef CPARSER 
#define CPARSER

#include <fstream>
#include <iostream>
#include "header/CException.h"

#define ERR_FICHIER 11

class CParser {

	private :

		std::ifstream fichier;

	public :

		// Constructeurs & Destructeur
		CParser(const char * pcChemin);
		~CParser();
		
		// Accesseurs
		void PAROuvrirFichier(const char * pcChemin);
		void PARLireLigne(char * pcBalise, char * pcResultat);
		
		// Methodes
		static void PARSeparateString(char cToken, char* pcStr1, char* pcStr2); 
		static bool PARIsStringEqual(const char* pccStr1, const char* pccStr2);
		static bool PARIsStringANumericalValue(const char * pcStr);
};

#endif