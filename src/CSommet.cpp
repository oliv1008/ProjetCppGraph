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
	uiSOMCompteurArcArrivant = 0;
	uiSOMCompteurArcPartant = 0;
}

/** Constructeur de confort **/
CSommet::CSommet(unsigned int uiNumero)
{
	uiSOMNumero = uiNumero;
	pARCSOMArrivant = nullptr;
	pARCSOMPartant = nullptr;
	uiSOMCompteurArcArrivant = 0;
	uiSOMCompteurArcPartant = 0;
}
/********************************/

/** Constructeur de recopie **/
CSommet::CSommet(CSommet &SOMSommet)
{
	unsigned int uiBoucle = 0;
	uiSOMNumero = SOMSommet.SOMLireNumero();
	uiCompteurArcArrivant = SOMSommet.SOMLireCompteurArcArrivant();
	uiCompteurArcPartant = SOMSommet.SOMLireCompteurArcPartant();
	
	pARCSOMArrivant = (CArc**)malloc(sizeof(CArc*) * uiCompteurArcArrivant);
	for (uiBoucle = 0; uiBoucle < uiCompteurArcArrivant; uiBoucle++)
	{
		pARCSOMArrivant[uiBoucle] = new CArc(*(SOMSommet.SOMLireArcArrivantIndice(uiBoucle)));
	}
	
	pARCSOMPartant = (CArc**)malloc(sizeof(CArc*) * uiCompteurArcPartant);
	for (uiBoucle = 0; uiBoucle < uiCompteurArcPartant; uiBoucle++)
	{
		pARCSOMPartant[uiBoucle] = new CArc(*(SOMSommet.SOMLireArcPartantIndice(uiBoucle)));
	}
}
/********************************/

/********** DESTRUCTEUR *********/ 
CSommet::~CSommet()
{
	unsigned int uiBoucle = 0;
	
	// Suppression des arcs arrivants
	for (uiBoucle = 0; uiBoucle < uiSOMCompteurArcArrivant; uiBoucle++)
	{
		delete pARCSOMArrivant[uiBoucle];
	}
	free(pARCSOMArrivant);
	
	// Suppression des arcs partants
	for (uiBoucle = 0; uiBoucle < uiSOMCompteurArcPartant; uiBoucle++)
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
	
	pARCTemp = (CArc**)realloc(pARCSOMArrivant, sizeof(CArc*) * (uiSOMCompteurArcArrivant + 1));
	
	if (pARCTemp != nullptr)
	{
		pARCSOMArrivant = pARCTemp;
		pARCSOMArrivant[uiSOMCompteurArcArrivant] = pARCArc;
		uiSOMCompteurArcArrivant++;
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
	for (uiBoucle = 0; uiBoucle < uiSOMCompteurArcArrivant && bArcDel; uiBoucle++)
	{
		// Quand on trouve celui associé à uiDestination...
		if (pARCSOMArrivant[uiBoucle]->ARCLireDestination() == uiDestination)
		{
			// On supprime l'arc et on réarrange le tableau
			delete pARCSOMArrivant[uiBoucle];
			for (uiBoucleDel = uiBoucle; uiBoucleDel < uiSOMCompteurArcArrivant - 1; uiBoucleDel++)
			{
				pARCSOMArrivant[uiBoucleDel] = pARCSOMArrivant[uiBoucleDel + 1];
			}
			
			// On réalloue le tableau
			pARCTemp = (CArc**)realloc(pARCSOMArrivant, sizeof(CArc*) * (uiSOMCompteurArcArrivant - 1));
			
			if (pARCTemp != nullptr || uiSOMCompteurArcArrivant == 1)
			{
				pARCSOMArrivant = pARCTemp;
				uiSOMCompteurArcArrivant--;
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
	
	pARCTemp = (CArc**)realloc(pARCSOMPartant, (uiSOMCompteurArcPartant + 1) * sizeof(CArc *));
	
	if (pARCTemp != nullptr)
	{
		pARCSOMPartant = pARCTemp;
		pARCSOMPartant[uiSOMCompteurArcPartant] = pARCArc;
		uiSOMCompteurArcPartant++;
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
	for (uiBoucle = 0; uiBoucle < uiSOMCompteurArcPartant && bArcDel; uiBoucle++)
	{
		// Quand on trouve celui associé à uiDestination...
		if (pARCSOMPartant[uiBoucle]->ARCLireDestination() == uiDestination)
		{
			// On supprime l'arc et on réarrange le tableau
			delete pARCSOMPartant[uiBoucle];
			for (uiBoucleDel = uiBoucle; uiBoucleDel < uiSOMCompteurArcPartant - 1; uiBoucleDel++)
			{
				pARCSOMPartant[uiBoucleDel] = pARCSOMPartant[uiBoucleDel + 1];
			}
			
			// On réalloue le tableau
			pARCTemp = (CArc**)realloc(pARCSOMPartant, (uiSOMCompteurArcPartant - 1) * sizeof(CArc *));
			
			if (pARCTemp != nullptr || uiSOMCompteurArcPartant == 1)
			{
				pARCSOMPartant = pARCTemp;
				uiSOMCompteurArcPartant--;
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
	return uiSOMCompteurArcArrivant;
}

unsigned int CSommet::SOMLireCompteurArcPartant()
{
	return uiSOMCompteurArcPartant;
}

CArc ** CSommet::SOMLireArcArrivant()
{
	return pARCSOMArrivant;
}

CArc * CSommet::SOMLireArcArrivantIndice(unsigned int uiIndice)
{
	if (uiIndice < uiCompteurArcArrivant)
	{
		return pARCSOMArrivant[uiIndice];
	}
	else
	{
		//Erreur, l'arc n'existe pas
		CException ErrNumSom(ERR_NUMARC);
		throw ErrNumSom;
	}
}

CArc ** CSommet::SOMLireArcPartant()
{
	return pARCSOMPartant;
}

CArc * CSommet::SOMLireArcPartantIndice(unsigned int uiIndice)
{
	if (uiIndice < uiCompteurArcPartant)
	{
		return pARCSOMPartant[uiIndice];
	}
	else
	{
		//Erreur, l'arc n'existe pas
		CException ErrNumSom(ERR_NUMARC);
		throw ErrNumSom;
	}
}

void CSommet::SOMModifierArcArrivant(CArc ** pARCParam)
{
	pARCSOMArrivant = pARCParam;
}

void CSommet::SOMModifierArcPartant(CArc ** pARCParam)
{
	pARCSOMPartant = pARCParam;
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
	unsigned int uiBoucleA = 0;
	unsigned int uiBoucleP = 0;
	
	cout << "S" << uiSOMNumero << endl;
	cout << "Arc arrivant :" << endl;
	for (uiBoucleA = 0; uiBoucleA < uiSOMCompteurArcArrivant; uiBoucleA++)
	{
		cout << "\tArc arrivant de " << pARCSOMArrivant[uiBoucleA]->ARCLireDestination() << endl;
	}
	cout << "Arc partant :" << endl;
	for (uiBoucleP = 0; uiBoucleP < uiSOMCompteurArcPartant; uiBoucleP++)
	{
		cout << "\tArc partant vers " << pARCSOMPartant[uiBoucleP]->ARCLireDestination() << endl;
	}
}
/*******************************/ 

/********************************************************************************
**** Nom: SOMContientArc                                                     ****
*********************************************************************************
****                                                                         ****
*********************************************************************************
**** Précondition: Rien                                                      ****
**** Entrée: unsigned int uiTo : destination de l'arc partant                ****
**** Entraîne: Rien                                                          ****
**** Sortie: Vrai si le sommet contient un arc partant vers uiTo, faux sinon ****
********************************************************************************/
int CSommet::SOMContientArc(unsigned int uiTo)
{
	unsigned int uiBoucle = 0;
	
	for (uiBoucle = 0; uiBoucle < uiSOMCompteurArcPartant; uiBoucle++)
	{
		if (pARCSOMPartant[uiBoucle]->ARCLireDestination() == uiTo)
		{
			return uiBoucle;
		}
	}
	
	return -1;
}