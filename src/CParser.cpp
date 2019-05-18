#include "header/CParser.h"

using namespace std;

CParser::CParser(const char * pcChemin)
{
	fichier.open(pcChemin, ios::in);
}

CParser::~CParser()
{
	if(fichier.is_open())
	{
		fichier.close();
	}
}

void CParser::PAROuvrirFichier(const char * pcChemin)
{
	if (!fichier.is_open())
	{
		fichier.open(pcChemin, ios::in);
	}
	else
	{
		CException ErrFichier(ERR_FICHIER);
		throw ErrFichier;
	}
}

/***********************************************************************************
**** Nom: PARLireLigne		                                            		****
************************************************************************************
**** Lis une ligne et la sépare en 2 parties : balise et résultat               ****
************************************************************************************
**** Précondition: -															****
**** Entrée: pcBalise : char*, pcResultat : char*								****
**** Entraîne: la modification de pcBalise et de pcResultat						****
**** Exemple: "NBSommets=3" ---> pcBalise = "NBSommets", pcResultat = "3"		**** 
**** Sortie: Rien																****
***********************************************************************************/
void CParser::PARLireLigne(char * pcBalise, char * pcResultat)
{
	if (fichier.is_open())
	{
		fichier >> pcBalise;
		//### cout << pcBalise << endl;
		PARSeparateString('=', pcBalise, pcResultat);
	}
	else
	{
		CException ErrFichier(ERR_FICHIER);
		throw ErrFichier;
	}
}


/***********************************************************************************
**** Nom: PARSeparateString		                                                ****
************************************************************************************
**** Permet de séparer une chaine de caractère et de conserver un pointeur      ****
**** qui pointe les chaines avant et après le token de séparation 				****
************************************************************************************
**** Précondition: cToken est un caractère ASCII, pcStr1 et pcStr2 sont 2       ****
****			   chaînes de caractères valides (finies par '\0')				****
**** Entrée: cToken : char, pcStr1 : char*, pcStr2 : char*	                    ****
**** Entraîne: Si pcStr1 conteint cToken :									    ****
****			-> pcStr1 se finit à l'indice de cToken							****
****			-> pcStr2 contient la suite de la chaine de caractère			****
****		   Sinon :															****
****			-> pcStr1 reste inchangée										****
****			-> pcStr2 = "\0" 												****
**** Sortie: Rien																****
***********************************************************************************/
void CParser::PARSeparateString(char cToken, char* pcStr1, char* pcStr2)
{
	bool bCopie = false;
	unsigned int uiBoucleDst = 0;
	unsigned int uiBoucleSrc = 0;
	int uiIndiceFinStr = -1;
	
	for (uiBoucleSrc = 0; pcStr1[uiBoucleSrc] != '\0'; uiBoucleSrc++)
	{
		if (bCopie == true)
		{
			pcStr2[uiBoucleDst] = pcStr1[uiBoucleSrc];
			uiBoucleDst++;
		}
		else if (pcStr1[uiBoucleSrc] == cToken)
		{
			bCopie = true;
			uiIndiceFinStr = uiBoucleSrc;
		}
	}
	
	if (uiIndiceFinStr != -1)
	{
		pcStr1[uiIndiceFinStr] = '\0';
	}
	pcStr2[uiBoucleDst] = '\0';
}

/***********************************************************************************
**** Nom: PARIsStringEqual		                                                ****
************************************************************************************
**** Permet de vérifier si deux chaines de caractères sont égales				****
************************************************************************************
**** Précondition: pccStr1 et pccStr2 sont 2 chaînes de caractères valides	    ****
**** Entrée: pcStr1 : const char*, pcStr2 : const char*	  	                    ****
**** Entraîne: Rien																****
**** Sortie: VRAI si la chaine pointée par pccStr1 = la chaine					****
****		 pointée par pccStr2, sinon FAUX									****
***********************************************************************************/
bool CParser::PARIsStringEqual(const char * pccStr1, const char * pccStr2)
{
	unsigned int uiBoucleStr = 0;
	bool bResultat = true;
	
	while (bResultat == true && pccStr1[uiBoucleStr] != '\0' && pccStr2[uiBoucleStr] != '\0')
	{
		if (pccStr1[uiBoucleStr] != pccStr2[uiBoucleStr])
		{
			bResultat = false;
		}
		
		uiBoucleStr++;
	}
	
	if (pccStr1[uiBoucleStr] != pccStr2[uiBoucleStr])
	{
		bResultat = false;
	}
	return bResultat;
}

/***********************************************************************************
**** Nom: PARIsStringANumericalValue		                                    ****
************************************************************************************
**** Permet de vérifier si une chaine de caractère représente un nombre valide	****
************************************************************************************
**** Précondition: pcStr1 est une chaîne de caractères valide				    ****
**** Entrée: pcStr1 : const char*						  	                    ****
**** Entraîne: Rien																****
**** Sortie: VRAI si la chaine pointée par pccStr1 est composée de chiffres		****
****		 et des points, sinon FAUX											****
***********************************************************************************/
bool CParser::PARIsStringANumericalValue(const char * pcStr)
{
	bool bIsNumericalValue = true;
	unsigned int uiBoucleStr = 0;
	
	if ((pcStr[0] < '0' || pcStr[0] > '9') && pcStr[uiBoucleStr] != '-')
	{
		return false;
	}
	
	for (uiBoucleStr = 0; pcStr[uiBoucleStr] != '\0' && bIsNumericalValue; uiBoucleStr++)
	{
		if ((pcStr[uiBoucleStr] < '0' || pcStr[uiBoucleStr] > '9') && pcStr[uiBoucleStr] != ',' && pcStr[uiBoucleStr] != '.' && pcStr[uiBoucleStr] != '-')
		{
			bIsNumericalValue = false;
		}
	}
	
	return bIsNumericalValue;
}