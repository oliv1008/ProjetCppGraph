#include <cstdlib>
#include <iostream>
#include "header/CSommet.h"

using namespace std;

/********* CONSTRUCTEURS *********/
/** Constructeur par défaut **/
CSommet::CSommet()
{
	uiSOMNumero = 0;
	pARCSOMArrivant = nullptr;
	pARCSOMPartant = nullptr;
	uiCompteurArcArrivant = 0;
	uiCompteurArcPartant = 0;
}

/** Constructeur de confort **/
CSommet::CSommet(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
	pARCSOMArrivant = nullptr;
	pARCSOMPartant = nullptr;
	uiCompteurArcArrivant = 0;
	uiCompteurArcPartant = 0;
}
/********************************/

/********** DESTRUCTEUR *********/ 
CSommet::~CSommet()
{
	// Suppression des arcs arrivants
	for (unsigned int uiBoucle = 0; uiBoucle < uiCompteurArcArrivant; uiBoucle++)
	{
		delete pARCSOMArrivant[uiBoucle];
	}
	free(pARCSOMArrivant);
	
	// Suppression des arcs partants
	for (unsigned int uiBoucle = 0; uiBoucle < uiCompteurArcPartant; uiBoucle++)
	{
		delete pARCSOMPartant[uiBoucle];
	}
	
	// Suppression du sommet
	free(pARCSOMPartant);
}
/********************************/

/********** ACCESSEURS **********/ 
unsigned int CSommet::SOMLireNumero()
{
	return uiSOMNumero;
}

void CSommet::SOMModifierNumero(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
}

/***********************************************************************************
**** Nom: SOMAjouterArcArrivant		                                            ****
************************************************************************************
**** Permet d'ajouter un arc arrivant	                  						****
************************************************************************************
**** Précondition: pARCArc est un pointeur sur un arc valide					****
**** Entrée: pARCArc : *CArc							                        ****
**** Entraîne: l'ajout d'un arc arrivant au sommet								****
**** Sortie: Rien																****
***********************************************************************************/
void CSommet::SOMAjouterArcArrivant(CArc *pARCArc)
{
	CArc ** pARCTemp;
	
	pARCTemp = (CArc**)realloc(pARCSOMArrivant, sizeof(CArc*) * (uiCompteurArcArrivant + 1));
	
	if (pARCTemp != nullptr)
	{
		pARCSOMArrivant = pARCTemp;
		pARCSOMArrivant[uiCompteurArcArrivant] = pARCArc;
		uiCompteurArcArrivant++;
	}
	/***** Gestion exception *****/
	else
	{	// Erreur réallocation
		CException ErrRealloc(ERR_REALLOC);
		throw ErrRealloc;
	}
	/*****************************/
}

/***********************************************************************************
**** Nom: SOMEnleverArcArrivant		                                            ****
************************************************************************************
**** Permet d'enlever un arc arrivant en fonction de sa destination             ****
************************************************************************************
**** Précondition: uiDestination représente bien un sommet					    ****
**** Entrée: uiDestination : unsigned int					                    ****
**** Entraîne: la suppression d'un arc arrivant								    ****
**** Sortie: Rien																****
***********************************************************************************/
void CSommet::SOMEnleverArcArrivant(unsigned int uiDestination)
{
	CArc ** pARCTemp;
	bool bArcDel = true;
	unsigned int uiBoucle = 0;
	unsigned int uiBoucleDel = 0;
	
	// On parcourt la liste des arcs arrivants
	for (uiBoucle = 0; uiBoucle < uiCompteurArcArrivant && bArcDel; uiBoucle++)
	{
		// Quand on trouve celui associé à uiDestination...
		if (pARCSOMArrivant[uiBoucle]->ARCLireDestination() == uiDestination)
		{
			// On supprime l'arc et on réarrange le tableau
			delete pARCSOMArrivant[uiBoucle];
			for (uiBoucleDel = uiBoucle; uiBoucleDel < uiCompteurArcArrivant - 1; uiBoucleDel++)
			{
				pARCSOMArrivant[uiBoucleDel] = pARCSOMArrivant[uiBoucleDel + 1];
			}
			
			// On réalloue le tableau
			pARCTemp = (CArc**)realloc(pARCSOMArrivant, sizeof(CArc*) * (uiCompteurArcArrivant - 1));
			
			if (pARCTemp != nullptr || uiCompteurArcArrivant == 1)
			{
				pARCSOMArrivant = pARCTemp;
				uiCompteurArcArrivant--;
				bArcDel = false;
			}
			/***** Gestion exception *****/
			else
			{	// Erreur réallocation
				CException ErrRealloc(ERR_REALLOC);
				throw ErrRealloc;
			}
			/*****************************/
		}
	}
}

/***********************************************************************************
**** Nom: SOMAjouterArcPartant		                                            ****
************************************************************************************
**** Permet d'ajouter un arc partant                    						****
************************************************************************************
**** Précondition: pARCArc est un pointeur sur un arc valide					****
**** Entrée: pARCArc : *CArc							                        ****
**** Entraîne: l'ajout d'un arc partant au sommet								****
**** Sortie: Rien																****
***********************************************************************************/
void CSommet::SOMAjouterArcPartant(CArc *pARCArc)
{
	CArc ** pARCTemp;
	
	pARCTemp = (CArc**)realloc(pARCSOMPartant, (uiCompteurArcPartant + 1) * sizeof(CArc *));
	
	if (pARCTemp != nullptr)
	{
		pARCSOMPartant = pARCTemp;
		pARCSOMPartant[uiCompteurArcPartant] = pARCArc;
		uiCompteurArcPartant++;
	}
	/***** Gestion exception *****/
	else
	{	// Erreur réallocation
		CException ErrRealloc(ERR_REALLOC);
		throw ErrRealloc;
	}
	/*****************************/
}

/***********************************************************************************
**** Nom: SOMEnleverArcPartant		                                            ****
************************************************************************************
**** Permet d'enlever un arc partant en fonction de sa destination              ****
************************************************************************************
**** Précondition: uiDestination représente bien un sommet					    ****
**** Entrée: uiDestination : unsigned int					                    ****
**** Entraîne: la suppression d'un arc partant								    ****
**** Sortie: Rien																****
***********************************************************************************/
void CSommet::SOMEnleverArcPartant(unsigned int uiDestination)
{
	CArc ** pARCTemp;
	bool bArcDel = true;
	unsigned int uiBoucle = 0;
	unsigned int uiBoucleDel = 0;
	
	// On parcourt la liste des arcs partants
	for (uiBoucle = 0; uiBoucle < uiCompteurArcPartant && bArcDel; uiBoucle++)
	{
		// Quand on trouve celui associé à uiDestination...
		if (pARCSOMPartant[uiBoucle]->ARCLireDestination() == uiDestination)
		{
			// On supprime l'arc et on réarrange le tableau
			delete pARCSOMPartant[uiBoucle];
			for (uiBoucleDel = uiBoucle; uiBoucleDel < uiCompteurArcPartant - 1; uiBoucleDel++)
			{
				pARCSOMPartant[uiBoucleDel] = pARCSOMPartant[uiBoucleDel + 1];
			}
			
			// On réalloue le tableau
			pARCTemp = (CArc**)realloc(pARCSOMPartant, (uiCompteurArcPartant - 1) * sizeof(CArc *));
			
			if (pARCTemp != nullptr || uiCompteurArcPartant == 1)
			{
				pARCSOMPartant = pARCTemp;
				uiCompteurArcPartant--;
				bArcDel = false;
			}
			/***** Gestion exception *****/
			else
			{	// Erreur réallocation
				CException ErrRealloc(ERR_REALLOC);
				throw ErrRealloc;
			}
			/*****************************/
		}
	}
}

unsigned int CSommet::SOMLireCompteurArcArrivant()
{
	return uiCompteurArcArrivant;
}

unsigned int CSommet::SOMLireCompteurArcPartant()
{
	return uiCompteurArcPartant;
}

CArc ** CSommet::SOMLireArcArrivant()
{
	return pARCSOMArrivant;
}

CArc ** CSommet::SOMLireArcPartant()
{
	return pARCSOMPartant;
}
/*******************************/ 

/*********** METHODES **********/

/***********************************************************************************
**** Nom: SOMAfficherSommet		                                                ****
************************************************************************************
**** Permet de renvoyer un sommet en fonction de son numéro                     ****
************************************************************************************
**** Précondition: -					        								****
**** Entrée: Rien					                       						****
**** Entraîne: l'affichage d'un sommet								    		****
**** Sortie: Rien																****
***********************************************************************************/
void CSommet::SOMAfficherSommet()
{
	cout << "S" << uiSOMNumero << endl;
	cout << "Arc arrivant :" << endl;
	for (unsigned int uiBoucleA = 0; uiBoucleA < uiCompteurArcArrivant; uiBoucleA++)
	{
		cout << "\tArc arrivant de " << pARCSOMArrivant[uiBoucleA]->ARCLireDestination() << endl;
	}
	cout << "Arc partant :" << endl;
	for (unsigned int uiBoucleP = 0; uiBoucleP < uiCompteurArcPartant; uiBoucleP++)
	{
		cout << "\tArc partant vers " << pARCSOMPartant[uiBoucleP]->ARCLireDestination() << endl;
	}
}
/*******************************/ 