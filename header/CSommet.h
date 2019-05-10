#ifndef CSOMMET 
#define CSOMMET

#include "header/CArc.h"

class CSommet
{
	private:
	
		unsigned int uiSOMNumero;
		CArc ** pARCSOMArrivant;
		CArc ** pARCSOMPartant;
		unsigned int uiCompteurArcArrivant;
		unsigned int uiCompteurArcPartant;
		
	public:
	
		// Constructeurs & Destructeur
		CSommet();
		CSommet(unsigned int uiNumero);
		~CSommet();
		
		// Accesseurs
		unsigned int SOMLireNumero();
		void SOMModifierNumero(unsigned int uiNumero);
		
		void SOMAjouterArcArrivant(CArc * pARCArc);
		void SOMEnleverArcArrivant(unsigned int uiDestination);
		void SOMAjouterArcPartant(CArc * pARCArc);
		void SOMEnleverArcPartant(unsigned int uiDestination);
		
		CArc ** SOMLireArcArrivant();
		CArc ** SOMLireArcPartant();
		
		unsigned int SOMLireCompteurArcArrivant();
		unsigned int SOMLireCompteurArcPartant();
		
		// Methodes
		void SOMAfficherSommet();
};

#endif