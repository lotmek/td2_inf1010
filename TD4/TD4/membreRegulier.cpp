/**********************************************************************
 * Cours : INF1010
 * Travail pratique 4
 * Nom: membreRegulier.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "membreRegulier.h"

 /****************************************************************************
  * Fonction:	MembreRegulier::MembreRegulier
  * Description: Constructeur par param�tres.
  * Param�tres:	(const string& nom)
  * Retour:		aucun
  ****************************************************************************/
MembreRegulier::MembreRegulier(const string& nom) : 
	Membre(nom), points_(0)
{
}

/****************************************************************************
 * Fonction:	MembreRegulier::getPoints
 * Description: Fournit les points.
 * Param�tres:	aucun
 * Retour:		(int) Les points du membre
 ****************************************************************************/
int MembreRegulier::getPoints() const
{
	return points_;
}

/****************************************************************************
 * Fonction:	MembreRegulier::getCoupons
 * Description: Fournit le tableau de coupons.
 * Param�tres:	aucun
 * Retour:		vector<Coupon*> vecteur de coupons
 ****************************************************************************/
vector<Coupon*> MembreRegulier::getCoupons() const
{
	return coupons_;
}

/****************************************************************************
 * Fonction:	MembreRegulier::ajouterBillet
 * Description: Ajoute le billet en parametre a la fin du vecteur billet du 
 *				membre. En plus, le nombre de points est modifier.
 * Param�tres:	Billet* billet
 * Retour:		aucun
 ****************************************************************************/
void MembreRegulier::ajouterBillet(Billet* billet)
{
	Membre::ajouterBillet(billet);
	modifierPoints(calculerPoints(billets_.back()));
}

/****************************************************************************
 * Fonction:	MembreRegulier::operator+=
 * Description:	Surcharge l'op�rateur += pour ajouter un pointeur coupon dans le vecteur coupons_
 * Param�tres:	(Coupon* coupon)
 * Retour:		Membre& membre
 ****************************************************************************/
Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

/****************************************************************************
 * Fonction:	MembreRegulier::operator-=
 * Description:	Surcharge l'op�rateur -= pour retirer un pointeur coupon du vecteur coupons_
 * Param�tres:	(Coupon* coupon)
 * Retour:		Membre& membre
 ****************************************************************************/
Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	for (size_t i = 0; i < coupons_.size(); ++i) {
		if (coupons_[i] == coupon) {
			coupons_[i] = coupons_[coupons_.size() - 1];
			coupons_.pop_back();
			return *this;
		}
	}

	return *this;
}

/****************************************************************************
 * Fonction:	MembreRegulier::modifierPoints
 * Description: Modificateur de points.
 * Param�tres:	(int) points
 * Retour:		aucun
 ****************************************************************************/
void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}

/****************************************************************************
 * Fonction:	MembreRegulier::calculerPoints
 * Description:	Calcule le nombre de points incluant les points bonus selon la classe du billet.
 * Param�tres:	(Billet* billet)
 * Retour:		(double) nombre de points
 ****************************************************************************/
double MembreRegulier::calculerPoints(Billet* billet) const
{
	double bonus = 0;
	switch (billet->getTarif()) {
	case TarifBillet::PremiumEconomie:
		bonus = 50;
		break;
	case TarifBillet::Affaire:
		bonus = 150;
		break;
	case TarifBillet::Premiere:
		bonus = 300;
		break;
	default:
		break;
	}

	return billet->getPrix() * 0.10 + bonus;
}

/****************************************************************************
 * Fonction:	MembreRegulier::peutAcheterCoupon
 * Description:	Verifie si le membreRegulier possede suffisamment de points pour
 *				acheter le coupon en parametre.
 * Param�tres:	(Coupon* coupon)
 * Retour:		bool vrai ou faux
 ****************************************************************************/
bool MembreRegulier::peutAcheterCoupon(Coupon* coupon)
{
	if (points_ >= coupon->getCout())
		return true;
	return false;
}

/****************************************************************************
 * Fonction:	MembreRegulier::acheterCoupon
 * Description:	Ajoute le coupon(ach�te) si le membre poss�de assez de points. 
 *				Applique un rabais aux membres premiums.
 * Param�tres:	(Coupon* coupon)
 * Retour:		aucun
 ****************************************************************************/
void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	if (peutAcheterCoupon(coupon)) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}

/****************************************************************************
 * Fonction:	MembreRegulier::afficher
 * Description:	Affiche les informations du membre regulier
 * Param�tres:	ostream& o
 * Retour:		aucun
 ****************************************************************************/
void MembreRegulier::afficher(ostream& o) const
{
	Membre::afficher(o);
	o << "\t" << "- Points : " << points_ << endl;
	o << "\t" << "- Coupons :" << endl;
	for (size_t i = 0; i < coupons_.size(); ++i) {
		o << coupons_[i];
	}
	o << endl;
}
