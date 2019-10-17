/**********************************************************************
 * Cours : INF1010
 * Travail pratique 4
 * Nom: membrePremium.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "membrePremium.h"

 /****************************************************************************
  * Fonction:	MembrePremium::MembrePremium
  * Description: Constructeur par param�tres.
  * Param�tres:	(const string& nom)
  * Retour:		aucun
  ****************************************************************************/
MembrePremium::MembrePremium(const string& nom) : 
	MembreRegulier(nom), joursRestants_(JOUR_RESTANT_INITIALE), pointsCumulee_(0)
{
}

/****************************************************************************
 * Fonction:	MembrePremium::setJourRestants
 * Description: Modifie les jours restants.
 * Param�tres:	(unsigned int joursRestants)
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::setJourRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;
}

/****************************************************************************
 * Fonction:	MembrePremium::modifierPointsCumules
 * Description: Incr�mente les points cumul�s.
 * Param�tres:	(unsigned int pointCumulee)
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::modifierPointsCumulee(unsigned int pointCumulee)
{
	pointsCumulee_ += pointCumulee;
}

/****************************************************************************
 * Fonction:	MembrePremium::getJourRestants
 * Description: Fournit le nombre de jours restants.
 * Param�tres:	aucun
 * Retour:		unsigned int jours restants
 ****************************************************************************/
unsigned int MembrePremium::getJourRestants() const
{
	return joursRestants_;
}

/****************************************************************************
 * Fonction:	MembrePremium::getpointsCumulee
 * Description: Fournit le nombre de points cumul�s.
 * Param�tres:	aucun
 * Retour:		unsigned int points cumul�s
 ****************************************************************************/
unsigned int MembrePremium::getpointsCumulee() const
{
	return pointsCumulee_;
}

/****************************************************************************
 * Fonction:	MembrePremium::ajouterBillet
 * Description:	Ajoute un pointeur billet dans le vecteur. 
 *				Modifie les points et les points cumul�s.
 * Param�tres:	(Billet* billet)
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::ajouterBillet(Billet* billet)
{
	MembreRegulier::ajouterBillet(billet);
	modifierPointsCumulee(calculerPoints(billets_.back()));
}

/****************************************************************************
 * Fonction:	MembrePremium::calculerCoutCoupon
 * Description:	Calcul un rabais selon le nombre de points cumulees. Puis,
 *				le soustrait au prix du coupon au moment de le retourner.
 * Param�tres:	(Coupon* coupon)
 * Retour:		double cout du coupon avec le rabais
 ****************************************************************************/
double MembrePremium::calculerCoutCoupon(Coupon* coupon)
{
	double rabais = 0.01 * pointsCumulee_ / 1000;

	if (rabais > 0.2)
		rabais = 0.2;

	return coupon->getCout() * (1 - rabais);
}

/****************************************************************************
 * Fonction:	MembrePremium::peutAcheterCoupon
 * Description:	Verifie si le membreRegulier possede suffisamment de points pour
 *				acheter le coupon en parametre.
 * Param�tres:	(Coupon* coupon)
 * Retour:		bool vrai ou faux
 ****************************************************************************/
bool MembrePremium::peutAcheterCoupon(Coupon* coupon)
{
	if (points_ >= calculerCoutCoupon(coupon))
		return true;
	return false;
}

/****************************************************************************
 * Fonction:	MembrePremium::acheterCoupon
 * Description:	Ajoute le coupon(ach�te) si le membre poss�de assez de points. 
 *				Applique un rabais aux membres premiums.
 * Param�tres:	(Coupon* coupon)
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::acheterCoupon(Coupon* coupon)
{
	if (peutAcheterCoupon(coupon)) {
		*this += coupon;
		modifierPoints(-calculerCoutCoupon(coupon));
	}
}

/****************************************************************************
 * Fonction:	MembrePremium::afficher
 * Description:	Affiche les informations du membre premium
 * Param�tres:	ostream& o
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::afficher(ostream& o) const
{
	//o << static_cast<MembreRegulier>(membrePremium) << endl;		// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	MembreRegulier::afficher(o);
	o << "\t- Points cumulee: " << pointsCumulee_ << endl;
	o << "\t- Jours premium restant: " << joursRestants_ << endl;
	o << endl;
}