#ifndef CGRAPHE 
#define CGRAPHE

#include "header/CSommet.h"
#include "header/CParser.h"

// Codes d'exceptions
#define ERR_FORMAT    	21
#define ERR_NUMERIQUE 	22
#define ERR_REALLOC		23
#define ERR_NUMSOM		24
#define ERR_DOUBLON		25
#define ERR_NUMARC		26

class CGraphe
{
	private:

		CSommet ** pSOMGRPTabSommet;
		unsigned int uiNombreSommet;
		
	public:
	
		// Constructeurs & Destructeur
		CGraphe();
		CGraphe(const char * pcChemin);
		~CGraphe();
		
		// Accesseurs
		CSommet * GRPLireSommet(unsigned int uiNumero);
		
		// Methodes
		int GRPContientSommet(unsigned int uiNumero);
		void GRPAjouterSommet(unsigned int uiNumero);
		void GRPEnleverSommet(unsigned int uiNumero);
		bool GRPContientArc(unsigned int uiFrom, unsigned int uiTo);
		void GRPAjouterArc(unsigned int uiFrom, unsigned int uiTo);
		void GRPEnleverArc(unsigned int uiFrom, unsigned int uiTo);
		void GRInverserGraphe();
		void GRPAfficherGraphe();
};

#endif