/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#include "membreRegulier.h"

/****************************************************************************
 * Fonction:	MembreRegulier::MembreRegulier
 * Description: Constructeur par paramètres.
 * Paramètres:	(const string& nom, TypeMembre typeMembre)
 * Retour:		aucun
 ****************************************************************************/
MembreRegulier::MembreRegulier(const string& nom, TypeMembre typeMembre)
	:Membre(nom, typeMembre), points_(0)    
{
}

/****************************************************************************
 * Fonction:	MembreRegulier::getPoints
 * Description: Fournit les points.
 * Paramètres:	aucun
 * Retour:		(int) Les points du membre
 ****************************************************************************/
int MembreRegulier::getPoints() const
{
	return points_;
}

/****************************************************************************
 * Fonction:	MembreRegulier::getCoupons
 * Description: Fournit le tableau de coupons.
 * Paramètres:	aucun
 * Retour:		vector<Coupon*> vecteur de coupons
 ****************************************************************************/
vector<Coupon*> MembreRegulier::getCoupons() const
{
	return coupons_;
}

/****************************************************************************
 * Fonction:	MembreRegulier::acheterCoupon
 * Description:	Ajoute le coupon(achète) si le membre possède assez de points. Applique un rabais aux membres premiums
 * Paramètres:	(Coupon* coupon)
 * Retour:		aucun
 ****************************************************************************/
void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	int cout = coupon->getCout();
	if (typeMembre_ == Membre_Premium)
		cout -= int(ceil(coupon->getRabais()*cout));
	if (points_ > cout) {
		*this += coupon;
		modifierPoints(-cout);
	}
}

/****************************************************************************
 * Fonction:	MembreRegulier::operator+=
 * Description:	Surcharge l'opérateur += pour ajouter un pointeur coupon dans le vecteur coupons_
 * Paramètres:	(Coupon* coupon)
 * Retour:		MembreRegulier& membre
 ****************************************************************************/
Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

/****************************************************************************
 * Fonction:	MembreRegulier::operator-=
 * Description:	Surcharge l'opérateur -= pour retirer un pointeur coupon du vecteur coupons_
 * Paramètres:	(Coupon* coupon)
 * Retour:		Membre& membre
 ****************************************************************************/
Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	for (unsigned i = 0; i < coupons_.size(); i++) {
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
 * Paramètres:	(int) points
 * Retour:		aucun
 ****************************************************************************/
void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}

/****************************************************************************
 * Fonction:	MembreRegulier::ajouterBillet
 * Description:	Ajoute un pointeur billet dans le vecteur. Modifie les points.
 * Paramètres:	(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
 * Retour:		aucun
 ****************************************************************************/
void MembreRegulier::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	Membre::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	modifierPoints(int(calculerPoints(billets_[billets_.size() -1] )));
}

/****************************************************************************
 * Fonction:	MembreRegulier::calculerPoints
 * Description:	Calcule le nombre de points incluant les points bonus selon la classe du billet.
 * Paramètres:	(Billet* billet)
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
 * Fonction:	MembreRegulier::afficherMembre
 * Description:	Affiche les informations du membre regulier
 * Paramètres:	aucun
 * Retour:		aucun
 ****************************************************************************/
void MembreRegulier::afficherMembre(ostream& o) const
{
	Membre::afficherMembre(o);
	cout << "\t- Points : " << points_<< endl;
	cout << "\t- Coupons : " << endl;
	for (unsigned i = 0; i < coupons_.size(); i++)
		cout << *coupons_[i];

}


