#include "header/CException.h"

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
