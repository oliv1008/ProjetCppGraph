#ifndef CEXCEPTION
#define CEXCEPTION

/* Liste exceptions :
 * 
 * définies dans CGraphe.h :
 * ERR_FORMAT    	 21
 * ERR_NUMERIQUE 	 22
 * ERR_REALLOC		 23
 * ERR_NUMSOM		 24
 * ERR_DOUBLON		 25
 * ERR_NUMARC		 26
 * 
 * définie dans CParser.h :
 * ERR_FICHIER 		 11
 * 
 */

class CException 
{
	private :
	
		unsigned int uiEXCErreur;
		
	public :
	
		// Constructeur
		CException(unsigned int uiErreur);
		
		// Accesseurs
		unsigned int EXCLireErreur();
		void EXCModifierErreur(unsigned int uiErreur);
};

#endif