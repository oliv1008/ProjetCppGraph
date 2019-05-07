#include <header/CArc.h>

CArc::CArc()
{
	uiARCDestination = 0;
}

CArc::CArc(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}

unsigned int CArc::ARCLireDestination()
{
	return uiARCDestination;
}

void CArc::ARCModifierDestination(unsigned int uiDestination)
{
	uiARCDestination = uiDestination;
}