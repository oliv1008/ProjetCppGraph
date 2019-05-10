#ifndef CGRAPHE 
#define CGRAPHE

#include "header/CSommet.h"
#include "header/CParserGraphe.h"

#define ERR_REALLOC		4
#define ERR_NUMSOM		5

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
		void GRPAjouterSommet(unsigned int uiNumero);
		void GRPEnleverSommet(unsigned int uiNumero);
		
		// Methodes
		void GRPAjouterArc(unsigned int uiFrom, unsigned int uiTo);
		void GRPEnleverArc(unsigned int uiFrom, unsigned int uiTo);
		void GRPAfficherGraphe();
};

#endif