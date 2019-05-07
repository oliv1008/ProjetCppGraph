#ifndef CSOMMET 
#define CSOMMET

#include <header/CArc.h>

class CSommet
{
	private:
	
		unsigned int uiSOMNumero;
		CArc ** pARCSOMArrivant;
		CArc ** pARCSOMPartant;
		unsigned int uiCompteurArcArrivant;
		unsigned int uiCompteurArcPartant;
		
	public:
		//Constructeurs & Destructeur
		CSommet();
		CSommet(unsigned int uiNumero);
		~CSommet();
		//Setter & Getter
		unsigned int SOMLireNumero();
		void SOMModifierNumero(unsigned int uiNumero);
		void SOMAjouterArcArrivant(CArc * pARCArc);
		void SOMEnleverArcArrivant(unsigned int uiDestination);
		void SOMAjouterArcPartant(CArc * pARCArc);
		void SOMEnleverArcPartant(unsigned int uiDestination);
		//Methodes
			//Affiche toute les infos du sommet (numéro & liste d'arc arrivant + partant)
		void SOMAfficherSommet();
};

#endif