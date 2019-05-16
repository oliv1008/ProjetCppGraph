#include "header/CException.h"

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
 * définie dans CParser.h
 * #define ERR_ACCES_FICHIER 7
 */

using namespace std;

/********* CONSTRUCTEURS *********/
/** Constructeur de confort **/
CException::CException(unsigned int uiErreur){
	EXCModifierErreur(uiErreur);
}
/*********************************/

/********** ACCESSEURS **********/ 
unsigned int CException::EXCLireErreur()
{
	return uiEXCErreur;
}

void CException::EXCModifierErreur(unsigned int uiErreur)
{
	uiEXCErreur = uiErreur;
}
/********************************/
