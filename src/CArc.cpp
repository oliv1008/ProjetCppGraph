#include "header/CArc.h"

/********* CONSTRUCTEURS *********/
/** Constructeur par défaut **/
CArc::CArc()
{
	uiARCDestination = 0;
}

/** Constructeur de confort **/
CArc::CArc(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}
/********************************/

/********** ACCESSEURS **********/ 
unsigned int CArc::ARCLireDestination()
{
	return uiARCDestination;
}

void CArc::ARCModifierDestination(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}
/********************************/