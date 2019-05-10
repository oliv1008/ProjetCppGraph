#ifndef CPARSERGRAPHE
#define CPARSERGRAPHE

#include <fstream>
#include <iostream>
#include "header/CParser.h"
#include "header/CException.h"

using namespace std;

#define ERR_FORMAT    	1
#define ERR_NUMERIQUE 	2
#define ERR_FICHIER 	3

class CParserGraphe : private CParser {

	private :


	public :
	
		static void PAGParserGraphe(const char * pcChemin, unsigned int &uiNbSommets, unsigned int &uiNbArcs, unsigned int * &puiNumeroSommets, \
									unsigned int ** &puiTabArc)
		{
			ifstream fichier(pcChemin, ios::in);  // On ouvre le fichier en lecture
 
			if(fichier)  // Si l'ouverture a réussi
			{       
				// Instructions
				char ligne[256];
				char resultat[256];
				
				// On récupère le nombre de sommets
				fichier >> ligne;
				cout << ligne << endl;
				CParser::PARSeparateString('=', ligne, resultat);
				
				if (!CParser::PARIsStringEqual(ligne, "NBSommets"))
				{
					CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;
				}
				else if (!CParser::PARIsStringANumericalValue(resultat))
				{
					CException ErrNumerique(ERR_NUMERIQUE);
					throw ErrNumerique;
				}
				
				uiNbSommets = atoi(resultat);
				
				// On récupère le nombre d'arcs
				fichier >> ligne;
				cout << ligne << endl;
				CParser::PARSeparateString('=', ligne, resultat);
				
				if (!CParser::PARIsStringEqual(ligne, "NBArcs"))
				{
					CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;
				}
				else if (!CParser::PARIsStringANumericalValue(resultat))
				{
					CException ErrNumerique(ERR_NUMERIQUE);
					throw ErrNumerique;
				}

				uiNbArcs = atoi(resultat);
				
				// On récupère la ligne "Sommets=["
				fichier >> ligne;
				cout << ligne << endl;
				if (!CParser::PARIsStringEqual(ligne, "Sommets=["))
				{
					CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;
				}
				
				// On remplit le tableau
				puiNumeroSommets = (unsigned int *)malloc(uiNbSommets * sizeof(unsigned int));
				for (unsigned int uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
				{
					// On récupère l'élement
					fichier >> ligne;
					cout << ligne << endl;
					if (CParser::PARIsStringEqual(ligne, "]"))
					{
						CException ErrFormat(ERR_FORMAT);
						throw ErrFormat;
					}
					else if (!CParser::PARIsStringANumericalValue(ligne))
					{
						CException ErrNumerique(ERR_NUMERIQUE);
						throw ErrNumerique;
					}
					
					puiNumeroSommets[uiBoucle] = atoi(ligne);
				}
				
				fichier >> ligne;
				cout << ligne << endl;
				if (!CParser::PARIsStringEqual(ligne, "]"))
				{
					CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;
				}
				
				// On récupère la ligne "Arcs=["
				fichier >> ligne;
				cout << ligne << endl;
				if (!CParser::PARIsStringEqual(ligne, "Arcs=["))
				{
					CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;
				}
				
				// On remplit le tableau
				puiTabArc = (unsigned int **)malloc(uiNbSommets * sizeof(unsigned int *));
				for (unsigned int uiBoucle = 0; uiBoucle < uiNbArcs; uiBoucle++)
				{
					puiTabArc[uiBoucle] = (unsigned int *)malloc(2 * sizeof(unsigned int));
				}
				
				for (unsigned int uiBoucle = 0; uiBoucle < uiNbSommets; uiBoucle++)
				{
					// On récupère l'élement
					fichier >> ligne;
					cout << ligne << endl;
					if (CParser::PARIsStringEqual(ligne, "]"))
					{
						CException ErrFormat(ERR_FORMAT);
						throw ErrFormat;
					}
					CParser::PARSeparateString('=', ligne, resultat);
					puiTabArc[uiBoucle][0] = atoi(resultat);
					
					fichier >> ligne;
					cout << ligne << endl;
					if (CParser::PARIsStringEqual(ligne, "]"))
					{
						CException ErrFormat(ERR_FORMAT);
						throw ErrFormat;
					}
					CParser::PARSeparateString('=', ligne, resultat);
					puiTabArc[uiBoucle][1] = atoi(resultat);
				}
				
				fichier >> ligne;
				cout << ligne << endl;
				if (!CParser::PARIsStringEqual(ligne, "]"))
				{
					CException ErrFormat(ERR_FORMAT);
					throw ErrFormat;
				}

				fichier.close();  // Impossible d'ouvrir le fichier
			}
			else  // sinon
			{
				CException ErrFichier(ERR_FICHIER);
				throw ErrFichier;
			}
		}

};

#endif