#ifndef CEXCEPTION
#define CEXCEPTION

/* Liste exceptions :
 * 
 * définies dans CGraphe.h
 * #define ERR_FORMAT    	 1
 * #define ERR_NUMERIQUE 	 2
 * #define ERR_FICHIER 		 3
 * #define ERR_REALLOC		 4
 * #define ERR_NUMSOM		 5
 * #define ERR_DOUBLON		 6
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