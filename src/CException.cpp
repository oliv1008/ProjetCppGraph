#include "header/CException.h"

/* Liste exceptions (definies dans CGraphe.h)
 * #define ERR_FORMAT     1
 * #define ERR_NUMERIQUE  2
 * #define ERR_FICHIER    3
 * #define ERR_REALLOC    4
 * #define ERR_NUMSOM     5
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
