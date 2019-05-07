#ifndef CEXCEPTION
#define CEXCEPTION

#include <iostream>

class CException 
{
	private :
	
		unsigned int uiEXCErreur;
		
	public :
	
		// Constructeurs
		CException(unsigned int uiEXCErreur);
		
		// Accesseurs
		unsigned int EXCLireErreur();
		void EXCModifierErreur(unsigned int uiEXCErreur);
		
		// Méthodes
		void EXCAfficherErreur();
};

#endif