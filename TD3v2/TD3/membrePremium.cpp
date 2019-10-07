/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#include "membrePremium.h"

 /****************************************************************************
  * Fonction:	MembrePremium::MembrePremium
  * Description: Constructeur par paramètres.
  * Paramètres:	(const string& nom)
  * Retour:		aucun
  ****************************************************************************/
MembrePremium::MembrePremium(const string& nom)
	:MembreRegulier(nom, TypeMembre::Membre_Premium),
	pointsCumules_(0),
	joursRestants_(JOUR_RESTANT_INITIALE)
{
}

/****************************************************************************
 * Fonction:	MembrePremium::setJourRestants
 * Description: Modifie les jours restants.
 * Paramètres:	(unsigned int joursRestants)
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::setJourRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;
}

/****************************************************************************
 * Fonction:	MembrePremium::modifierPointsCumules
 * Description: Incrémente les points cumulés.
 * Paramètres:	(unsigned int pointCumulee)
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::modifierPointsCumules(unsigned int pointCumulee)
{
	pointsCumules_ += pointCumulee;
}

/****************************************************************************
 * Fonction:	MembrePremium::getJourRestants
 * Description: Fournit le nombre de jours restants.
 * Paramètres:	aucun
 * Retour:		unsigned int jours restants
 ****************************************************************************/
unsigned int MembrePremium::getJourRestants() const
{
	return joursRestants_;
}

/****************************************************************************
 * Fonction:	MembrePremium::getpointsCumulee
 * Description: Fournit le nombre de points cumulés.
 * Paramètres:	aucun
 * Retour:		unsigned int points cumulés
 ****************************************************************************/
unsigned int MembrePremium::getpointsCumulee() const
{
	return pointsCumules_;
}

/****************************************************************************
 * Fonction:	MembrePremium::ajouterBillet
 * Description:	Ajoute un pointeur billet dans le vecteur. Modifie les points et les points cumulés.
 * Paramètres:	(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	MembreRegulier::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	modifierPointsCumules(unsigned(calculerPoints(billets_[billets_.size() - 1])));
}

/****************************************************************************
 * Fonction:	MembrePremium::acheterCoupon
 * Description:	Ajoute le coupon(achète) si le membre possède assez de points. Applique un rabais aux membres premiums
 * Paramètres:	(Coupon* coupon)
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::acheterCoupon(Coupon* coupon)
{
	double rabais = pointsCumules_/1000.0 /100.0 >= 0.2 ? 0.2 : pointsCumules_ / 1000.0 /100.0;		// A CHANGER ,, c'est pas les points cumules qui ont un maximum, mais le rabais.
	double rabaisTemp = coupon->getRabais();
	coupon->setRabais(rabais);
	MembreRegulier::acheterCoupon(coupon);
	coupon->setRabais(rabaisTemp);
}

/****************************************************************************
 * Fonction:	MembrePremium::afficherMembre
 * Description:	Affiche les informations du membre premium
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
void MembrePremium::afficherMembre(ostream& o) const
{
	MembreRegulier::afficherMembre(o);
	cout << "\t-Points cumules : " << pointsCumules_ << endl;
	cout << "\t-Jours premium restant : " << joursRestants_ << endl;

}