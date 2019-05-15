#include <cstdlib>
#include <iostream>
#include "header/CGraphe.h"

using namespace std;

/********* CONSTRUCTEURS *********/
/** Constructeur par défaut **/
CGraphe::CGraphe()
{
	pSOMGRPTabSommet = nullptr;
	uiNombreSommet = 0;
}

/** Constructeur depuis un fichier **/
CGraphe::CGraphe(const char * pcChemin)
{
	unsigned int uiNbSommets;
	unsigned int uiNbArcs;
	unsigned int * puiTabSommets;
	unsigned int ** puiTabArcs;
	
	CParserGraphe::PAGParserGraphe(pcChemin, uiNbSommets, uiNbArcs, puiTabSommets, puiTabArcs);
}
/********************************/

/********** DESTRUCTEUR *********/ 
CGraphe::~CGraphe()
{
	unsigned int uiBoucle = 0;
	
	for (uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		delete pSOMGRPTabSommet[uiBoucle];
	}
	free(pSOMGRPTabSommet);
}
/********************************/

/********** ACCESSEURS **********/ 

/***********************************************************************************
**** Nom: GRPLireSommet		                                                    ****
************************************************************************************
**** Permet de renvoyer un sommet en fonction de son numéro                     ****
************************************************************************************
**** Précondition: uiNumero représente bien un sommet					        ****
**** Entrée: uiNumero : unsigned int					                        ****
**** Entraîne: -								    							****
**** Sortie: *CGraphe, le sommet associé à uiNumero								****
***********************************************************************************/
CSommet * CGraphe::GRPLireSommet(unsigned int uiNumero)
{
	unsigned int uiBoucle = 0;
	bool bTrouve = false;
	
	/***** Gestion exception *****/
	for (uiBoucle = 0; uiBoucle < uiNombreSommet && !bTrouve; uiBoucle++)
	{
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiNumero)
		{
			bTrouve = true;
		}
	}
	if(!bTrouve)
	{	// Erreur sommet non trouvé
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
	/*****************************/
	
	return pSOMGRPTabSommet[uiNumero];
}

/***********************************************************************************
**** Nom: GRPAjouterSommet		                                                ****
************************************************************************************
**** Permet d'ajouter un nouveau sommet au graphe			                    ****
************************************************************************************
**** Précondition: -					        								****
**** Entrée: uiNumero : unsigned int					                        ****
**** Entraîne: l'ajout d'un nouveau sommet au graphe							****
**** Sortie: Rien																****
***********************************************************************************/
void CGraphe::GRPAjouterSommet(unsigned int uiNumero)
{
	CSommet **pSOMTemp;
	
	// Réallocation du tableau
	pSOMTemp = (CSommet **)realloc(pSOMGRPTabSommet, (uiNombreSommet + 1) * sizeof(CSommet *));
	
	if (pSOMTemp != nullptr)
	{
		pSOMGRPTabSommet = pSOMTemp;
		pSOMGRPTabSommet[uiNombreSommet] = new CSommet(uiNumero);
		uiNombreSommet++;
	}
	/***** Gestion exception *****/
	else
	{	// Erreur realloc
		CException ErrRealloc(ERR_REALLOC);
		throw ErrRealloc;
	}
	/*****************************/
}

/***********************************************************************************
**** Nom: GRPEnleverSommet		                                                ****
************************************************************************************
**** Permet d'enlever un sommet en fonction de son numéro			            ****
************************************************************************************
**** Précondition: uiNumero représente bien un sommet					        ****
**** Entrée: uiNumero : unsigned int					                        ****
**** Entraîne: la suppression d'un sommet et de tous ses arcs liés				****
**** Sortie: Rien																****
***********************************************************************************/
void CGraphe::GRPEnleverSommet(unsigned int uiNumero)
{
	cout << "# Suppression du sommet " << uiNumero << "..." << endl;
 	
	CSommet ** pSOMTemp;
	bool bSommetDel = true;
	bool bTrouve = false;
	
	unsigned int uiBoucle = 0;
	unsigned int uiBoucleSom = 0;
	
	/***** Gestion exception *****/
	for (uiBoucle = 0; uiBoucle < uiNombreSommet && !bTrouve; uiBoucle++)
	{
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiNumero)
		{
			bTrouve = true;
		}
	}
	if(!bTrouve)
	{	// Erreur sommet non trouvé
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
	/*****************************/
	
	// On parcours la liste des sommets
	for (uiBoucle = 0; uiBoucle < uiNombreSommet && bSommetDel; uiBoucle++)
	{
		// Quand on trouve celui associé à uiNumero...
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiNumero)
		{
			// On supprime tous les arcs liés à ce sommet
			unsigned int uiArcsPartants = pSOMGRPTabSommet[uiBoucle]->SOMLireCompteurArcPartant();
			unsigned int uiArcsArrivants = pSOMGRPTabSommet[uiBoucle]->SOMLireCompteurArcArrivant();
			
			cout << "[GRPEnleverSommet] Sommet : " << uiNumero << endl;
			cout << "[GRPEnleverSommet] Arcs partants : " << uiArcsPartants << endl;
			cout << "[GRPEnleverSommet] Arcs arrivants : " << uiArcsArrivants << endl;
			
			// Arcs partants
			for(uiBoucleSom = 0; uiBoucleSom < uiArcsPartants; uiBoucleSom++)
			{
				GRPEnleverArc(uiNumero, pSOMGRPTabSommet[uiBoucle]->SOMLireArcPartant()[0]->ARCLireDestination());
			}
			
			// Arcs arrivants
			for(uiBoucleSom = 0; uiBoucleSom < uiArcsArrivants; uiBoucleSom++)
			{
				GRPEnleverArc(pSOMGRPTabSommet[uiBoucle]->SOMLireArcArrivant()[0]->ARCLireDestination(), uiNumero);
			}
			
			// On supprime le sommet et on réarrange le tableau
			delete pSOMGRPTabSommet[uiBoucle];
			for (unsigned int uiBoucleDel = uiBoucle; uiBoucleDel < uiNombreSommet - 1; uiBoucleDel++)
			{
				pSOMGRPTabSommet[uiBoucleDel] = pSOMGRPTabSommet[uiBoucleDel + 1];
			}
			
			// On réalloue le tableau
			pSOMTemp = (CSommet **)realloc(pSOMGRPTabSommet, (uiNombreSommet - 1) * sizeof(CSommet *));
			
			if (pSOMTemp != nullptr || uiNombreSommet == 1)
			{
				pSOMGRPTabSommet = pSOMTemp;
				uiNombreSommet--;
				bSommetDel = false;
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
/*******************************/ 

/*********** METHODES **********/

/***********************************************************************************
**** Nom: GRPAjouterArc		                                                	****
************************************************************************************
**** Permet d'ajouter un nouvel arc au graphe			                    	****
************************************************************************************
**** Précondition: uiFrom et uiTo représentent bien des sommets					****
**** Entrée: uiFrom : unsigned int, uiTo : unsigned int					        ****
**** Entraîne: l'ajout d'un nouvel arc au graphe								****
**** Sortie: Rien																****
***********************************************************************************/
void CGraphe::GRPAjouterArc(unsigned int uiFrom, unsigned int uiTo)
{
	bool bTrouveFrom = false, bTrouveTo = false;
	unsigned int uiIndiceFrom = 0, uiIndiceTo = 0;
	unsigned int uiBoucle = 0;
	
	/***** Gestion exception *****/
	for (uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiFrom)
		{
			uiIndiceFrom = uiBoucle;
			bTrouveFrom = true;
		}
		
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiTo)
		{
			uiIndiceTo = uiBoucle;
			bTrouveTo = true;
		}
	}
	if(!(bTrouveFrom && bTrouveTo))
	{	// Erreur sommet non trouvé
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
	/*****************************/
	
	// Ajout des arcs partants et arrivants
	pSOMGRPTabSommet[uiIndiceFrom]->SOMAjouterArcPartant(new CArc(uiTo));
	pSOMGRPTabSommet[uiIndiceTo]->SOMAjouterArcArrivant(new CArc(uiFrom));
}

/***********************************************************************************
**** Nom: GRPEnleverArc		                                                	****
************************************************************************************
**** Permet d'enlever un arc en fonction de ses sommets de départ et d'arrivée	****
************************************************************************************
**** Précondition: uiFrom et uiTo représentent bien des sommets					****
**** Entrée: uiFrom : unsigned int, uiTo : unsigned int					        ****
**** Entraîne: la suppresion d'un arc											****
**** Sortie: Rien																****
***********************************************************************************/
void CGraphe::GRPEnleverArc(unsigned int uiFrom, unsigned int uiTo)
{
	cout << "[GRPEnleverArc] Suppression de l'arc (from " << uiFrom << " to " << uiTo << ")" << endl;
	
	bool bTrouveFrom = false, bTrouveTo = false;
	unsigned int uiIndiceFrom = 0, uiIndiceTo = 0;
	unsigned int uiBoucle = 0;
	
	/***** Gestion exception *****/
	for (uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiFrom)
		{
			uiIndiceFrom = uiBoucle;
			bTrouveFrom = true;
		}
		
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiTo)
		{	
			uiIndiceTo = uiBoucle;
			bTrouveTo = true;
		}
	}
	if(!(bTrouveFrom && bTrouveTo))
	{	// Erreur sommet non trouvé
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
	/*****************************/
	
	// Suppression des arcs partants et arrivants
	pSOMGRPTabSommet[uiIndiceFrom]->SOMEnleverArcPartant(uiTo);
	pSOMGRPTabSommet[uiIndiceTo]->SOMEnleverArcArrivant(uiFrom);
}

/***********************************************************************************
**** Nom: GRPAfficherGraphe		                                                ****
************************************************************************************
**** Permet d'afficher un graphe							                    ****
************************************************************************************
**** Précondition: -					        								****
**** Entrée: Rien										                        ****
**** Entraîne: l'affichage du graphe											****
**** Sortie: Rien																****
***********************************************************************************/
void CGraphe::GRPAfficherGraphe()
{
	unsigned int uiBoucle = 0;
	
	for(uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		pSOMGRPTabSommet[uiBoucle]->SOMAfficherSommet();
	}
}
/*******************************/ 