#ifndef CPARSER 
#define CPARSER

#include <fstream>
#include <iostream>
#include <header/CException.h>

<<<<<<< HEAD
#define ERR_ACCES_FICHIER 7
=======
#define ERR_FICHIER 3
>>>>>>> 44bc005fb5a9b50cb6d28d432f17666d13c78dc9

class CParser {

	private :

	std::ifstream fichier;

	public :

		//Constructeurs & Destructeur
		CParser();
		CParser(const char * pcChemin);
		~CParser();
		//Getter & Setter
		void PAROuvrirFichier(const char * pcChemin);
		void PARLireLigne(char * pcBalise, char * pcResultat);
		//Methodes
		static void PARSeparateString(char cToken, char* pcStr1, char* pcStr2); 
		static bool PARIsStringEqual(const char* pccStr1, const char* pccStr2);
		static bool PARIsStringANumericalValue(const char * pcStr);
};

#endif