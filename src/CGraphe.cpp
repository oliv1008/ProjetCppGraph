#include <cstdlib>
#include <iostream>
#include "header/CGraphe.h"
#include "header/CParser.h"

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
	unsigned int uiBoucle = 0;
	unsigned int uiNbSommets;
	unsigned int uiNbArcs;
	unsigned int * puiTabSommets;
	unsigned int ** puiTabArcs;
	char pcBalise[256];
	char pcResultat[256];
	CParser PARParserGraphe(pcChemin);
	
	// Récupération du nombre de sommets
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "NBSommets"))
	{
		CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;
	}
	else if (!CParser::PARIsStringANumericalValue(pcResultat))
	{
		CException ErrFormat(ERR_NUMERIQUE);
		throw ErrFormat;
	}
	else if (atoi(pcResultat) <= 0)
	{
		CException ErrFormat(ERR_NUMERIQUE);
		throw ErrFormat;
	}
	uiNbSommets = atoi(pcResultat);
	
	// Récupération du nombre d'arcs
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "NBArcs"))
	{
		CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;
	}
	else if (!CParser::PARIsStringANumericalValue(pcResultat))
	{
		CException ErrNumerique(ERR_NUMERIQUE);
		throw ErrNumerique;
	}
	else if (atoi(pcResultat) <= 0)
	{
		CException ErrFormat(ERR_NUMERIQUE);
		throw ErrFormat;
	}
	uiNbArcs = atoi(pcResultat);
	
	// Récupération des sommets
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "Sommets") || !CParser::PARIsStringEqual(pcResultat, "["))
	{
		CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;
	}
	
	// On remplit le tableau de sommets
	puiTabSommets = (unsigned int *)malloc(uiNbSommets * sizeof(unsigned int));
	for (uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
	{
		// On récupère l'élement
		PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
		if (CParser::PARIsStringEqual(pcBalise, "]") || !CParser::PARIsStringEqual(pcBalise, "Numero"))
		{
			CException ErrDimension(ERR_FORMAT);
			throw ErrDimension;
		}
		else if (!CParser::PARIsStringANumericalValue(pcResultat))
		{
			CException ErrNumerique(ERR_NUMERIQUE);
			throw ErrNumerique;
		}
		else if (atoi(pcResultat) <= 0)
		{
			CException ErrFormat(ERR_NUMERIQUE);
			throw ErrFormat;
		}
					
		puiTabSommets[uiBoucle] = atoi(pcResultat);
	}
	// On vérifie que les sommets s'arretent bien
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "]"))
	{
		CException ErrDimension(ERR_FORMAT);
		throw ErrDimension;
	}
	
	// Récupération des arcs
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "Arcs") || !CParser::PARIsStringEqual(pcResultat, "["))
	{
		CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;
	}
	
	// On remplit le tableau d'arcs
	puiTabArcs = (unsigned int **)malloc(uiNbArcs * sizeof(unsigned int *));
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++)
	{
		puiTabArcs[uiBoucle] = (unsigned int *)malloc(2 * sizeof(unsigned int));
	}
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++)
	{
		// On récupère l'élement
		PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
		if (CParser::PARIsStringEqual(pcBalise, "]") || !CParser::PARIsStringEqual(pcBalise, "Debut"))
		{
			CException ErrDimension(ERR_FORMAT);
			throw ErrDimension;
		}
		else if (atoi(pcResultat) <= 0)
		{
			CException ErrFormat(ERR_NUMERIQUE);
			throw ErrFormat;
		}
		puiTabArcs[uiBoucle][0] = atoi(pcResultat);
			
		PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
		if (CParser::PARIsStringEqual(pcBalise, "]") || !CParser::PARIsStringEqual(pcBalise, "Fin"))
		{
			CException ErrDimension(ERR_FORMAT);
			throw ErrDimension;
		}
		else if (atoi(pcResultat) <= 0)
		{
			CException ErrFormat(ERR_NUMERIQUE);
			throw ErrFormat;
		}
		puiTabArcs[uiBoucle][1] = atoi(pcResultat);
	}
	// On vérifie que les arcs ne s'arretent pas
	PARParserGraphe.PARLireLigne(pcBalise, pcResultat);
	if (!CParser::PARIsStringEqual(pcBalise, "]"))
	{
		CException ErrDimension(ERR_FORMAT);
		throw ErrDimension;
	}
	
	// Les données du fichier ont été récupérées sans problèmes, on peut créer le graphe
	
	pSOMGRPTabSommet = nullptr;
	uiNombreSommet = 0;
	
	try {
		for (uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
		{
			GRPAjouterSommet(puiTabSommets[uiBoucle]);
		}
	} catch(CException EXCErreur){
		switch(EXCErreur.EXCLireErreur()){
			case ERR_DOUBLON : cerr << "Erreur doublon : sommet deja existant" << endl; break;
			default : cerr << "Erreur inconnue (creation des sommets)" << endl; break;
		}
		CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;
	}
	
	try 
	{
		for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++)
		{
			//### cout << "Ajout de l'arc " << puiTabArcs[uiBoucle][0] << "->" << puiTabArcs[uiBoucle][1] << endl;
			GRPAjouterArc(puiTabArcs[uiBoucle][0], puiTabArcs[uiBoucle][1]);
		}
	} 
	catch(CException EXCErreur)
	{
		switch(EXCErreur.EXCLireErreur())
		{
			case ERR_NUMSOM : cerr << "Erreur numero arc : sommets introuvables" << endl; break;
			case ERR_DOUBLON : cerr << "Erreur doublon : arc déjà existant" << endl; break;
			default : cerr << "Erreur inconnue (creation des arcs)" << endl; break;
		}
		CException ErrFormat(ERR_FORMAT);
		throw ErrFormat;
		
	}
	
	// Libération mémoire
	for (uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++)
	{
		free(puiTabArcs[uiBoucle]);
	}
	free(puiTabArcs);
	free(puiTabSommets);
	
	
}
/********************************/

CGraphe::CGraphe(CGraphe &GRPGraphe)
{
	unsigned int uiBoucle = 0;
	
	uiNombreSommet = GRPGraphe.GRPLireNombreSommet();
	pSOMGRPTabSommet = (CSommet**)malloc(sizeof(CSommet*) * uiNombreSommet);
	
	for (uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		pSOMGRPTabSommet[uiBoucle] = new CSommet(*(GRPGraphe.GRPLireSommetIndice(uiBoucle)));
	}
}

/********** DESTRUCTEUR *********/ 
CGraphe::~CGraphe()
{
	unsigned int uiBoucle = 0;
	
	for (uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		try 
		{
			GRPEnleverSommet(pSOMGRPTabSommet[uiBoucle]->SOMLireNumero());
		}
		catch(CException EXCErreur)
		{
			switch(EXCErreur.EXCLireErreur())
			{
				case ERR_NUMSOM : cerr << "Erreur numero sommet : sommets introuvables" << endl; break;
				case ERR_NUMARC : cerr << "Erreur arc : cet arc n'existe pas" << endl; break;
				case ERR_REALLOC : cerr << "Erreur realloc" << endl; break;
				default : cerr << "Erreur inconnue (creation des arcs)" << endl; break;
			}
		}	
	}
	free(pSOMGRPTabSommet);
}
/********************************/

/********** ACCESSEURS **********/ 

/***********************************************************************************
**** Nom: GRPLireSommetNumero                                                   ****
************************************************************************************
**** Permet de renvoyer un sommet en fonction de son numéro                     ****
************************************************************************************
**** Précondition: uiNumero représente bien un sommet					        ****
**** Entrée: uiNumero : unsigned int					                        ****
**** Entraîne: -								    							****
**** Sortie: *CGraphe, le sommet associé à uiNumero								****
***********************************************************************************/
CSommet * CGraphe::GRPLireSommetNumero(unsigned int uiNumero)
{
	unsigned int uiNumeroReturn = GRPContientSommet(uiNumero);
	
	if(!uiNumeroReturn)
	{
		//Erreur, le sommet n'existe pas
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
	/*****************************/
	
	return pSOMGRPTabSommet[uiNumeroReturn];
}

/***********************************************************************************
**** Nom: GRPLireSommetIndice	                                                ****
************************************************************************************
**** Permet de renvoyer un sommet en fonction de son indice                     ****
************************************************************************************
**** Précondition: uiIndice est inférieur au nombre de sommet dans le tableau	****
**** Entrée: uiIndice : unsigned int					                        ****
**** Entraîne: -								    							****
**** Sortie: *CGraphe, le sommet associé à l'indice uiIndice dans le tableau	****
***********************************************************************************/
CSommet * CGraphe::GRPLireSommetIndice(unsigned int uiIndice)
{
	if (uiIndice < uiNombreSommet)
	{
		return pSOMGRPTabSommet[uiIndice];
	}
	else
	{
		//Erreur, le sommet n'existe pas
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
}

unsigned int CGraphe::GRPLireNombreSommet()
{
	return uiNombreSommet;
}

/***********************************************************************************
**** Nom: GRPContientSommet		                                                ****
************************************************************************************
**** Permet de vérifier si un graphe contient un sommet ou non                  ****
************************************************************************************
**** Précondition: -					        								****
**** Entrée: uiNumero : unsigned int					                        ****
**** Entraîne: -																****
**** Sortie: bool																****
***********************************************************************************/
int CGraphe::GRPContientSommet(unsigned int uiNumero)
{
	unsigned int uiBoucle = 0;
	
	for (uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		if (pSOMGRPTabSommet[uiBoucle]->SOMLireNumero() == uiNumero)
		{
			return uiBoucle;
		}
	}
	
	return -1;
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
	if(GRPContientSommet(uiNumero) != -1)
	{
		//Erreur, sommet existe deja
		CException ErrDoublon(ERR_DOUBLON);
		throw ErrDoublon;
	}
	
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
	CSommet ** pSOMTemp;
	bool bSommetDel = true;
	
	unsigned int uiBoucle = 0;
	unsigned int uiBoucleSom = 0;
	
	/***** Gestion exception *****/
	if(GRPContientSommet(uiNumero) == -1)
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
	int uiIndiceFrom = 0, uiIndiceTo = 0;
	
	/***** Gestion exception *****/
	uiIndiceFrom = GRPContientSommet(uiFrom);
	uiIndiceTo = GRPContientSommet(uiTo);
	if(uiIndiceFrom == -1 || uiIndiceTo == -1)
	{	// Erreur sommet non trouvé
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
	if (pSOMGRPTabSommet[uiIndiceFrom]->SOMContientArc(uiTo) != -1)
	{
		//Erreur, arc existe deja
		CException ErrDoublon(ERR_DOUBLON);
		throw ErrDoublon;
	}
	/*****************************/
	
	// Ajout des arcs partants et arrivants
	pSOMGRPTabSommet[uiIndiceFrom]->SOMAjouterArcPartant(new CArc(uiTo));
	pSOMGRPTabSommet[uiIndiceTo]->SOMAjouterArcArrivant(new CArc(uiFrom));
}
/*******************************/ 

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
	//### cout << "[GRPEnleverArc] Suppression de l'arc (from " << uiFrom << " to " << uiTo << ")" << endl;
	
	int uiIndiceFrom = 0, uiIndiceTo = 0;
	
	/***** Gestion exception *****/
	uiIndiceFrom = GRPContientSommet(uiFrom);
	uiIndiceTo = GRPContientSommet(uiTo);
	if(uiIndiceFrom == -1 || uiIndiceTo == -1)
	{	// Erreur sommet non trouvé
		CException ErrNumSom(ERR_NUMSOM);
		throw ErrNumSom;
	}
	if (pSOMGRPTabSommet[uiIndiceFrom]->SOMContientArc(uiTo) == -1)
	{
		//Erreur, arc n'existe pas
		CException ErrNumArc(ERR_NUMARC);
		throw ErrNumArc;
	}
	/*****************************/
	
	// Suppression des arcs partants et arrivants
	pSOMGRPTabSommet[uiIndiceFrom]->SOMEnleverArcPartant(uiTo);
	pSOMGRPTabSommet[uiIndiceTo]->SOMEnleverArcArrivant(uiFrom);
}
/*******************************/ 

/***********************************************************************************
**** Nom: GRInverserGraphe		                                                ****
************************************************************************************
**** Permet d'inverser un graphe							                    ****
************************************************************************************
**** Précondition: -					        								****
**** Entrée: Rien										                        ****
**** Entraîne: l'inversion des arcs du graphe									****
**** Sortie: Rien																****
***********************************************************************************/
void CGraphe::GRInverserGraphe(){
	unsigned int uiBoucleSom = 0;
	
	for(uiBoucleSom = 0; uiBoucleSom < uiNombreSommet; uiBoucleSom++)
	{
		CArc ** pARCTemp;
		// Temp = Arcs arrivants
		pARCTemp = pSOMGRPTabSommet[uiBoucleSom]->SOMLireArcArrivant();
		// Arcs arrivants = Arcs partants
		pSOMGRPTabSommet[uiBoucleSom]->SOMModifierArcArrivant(pSOMGRPTabSommet[uiBoucleSom]->SOMLireArcPartant());
		// Arcs partants = Temp
		pSOMGRPTabSommet[uiBoucleSom]->SOMModifierArcPartant(pARCTemp);
	}
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

CGraphe& CGraphe::operator=(CGraphe &GRPGraphe)
{
	unsigned int uiBoucle = 0;
	
	uiNombreSommet = GRPGraphe.GRPLireNombreSommet();
	pSOMGRPTabSommet = (CSommet**)realloc(pSOMGRPTabSommet, sizeof(CSommet*) * uiNombreSommet);
	
	for (uiBoucle = 0; uiBoucle < uiNombreSommet; uiBoucle++)
	{
		pSOMGRPTabSommet[uiBoucle] = new CSommet(*(GRPGraphe.GRPLireSommetIndice(uiBoucle)));
	}
	
	return *this;
}