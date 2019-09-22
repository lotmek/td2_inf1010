/**********************************************************************
 * Cours : INF1010
 * Travail pratique 1
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#include "membre.h"

 /****************************************************************************
  * Fonction:	Membre::Membre
  * Description: Constructeur par d�faut.
  * Param�tres:	aucun
  * Retour:		aucun
  ****************************************************************************/
Membre::Membre()
{
	nom_ = "Bill Gates";
	points_ = 0;
	capaciteCoupons_ = capaciteBillets_ = CAPACITE_INITIALE;
	billets_ = new Billet*[capaciteBillets_];
	nbBillets_ = 0;
	coupons_ = new Coupon *[capaciteCoupons_];
	nbCoupons_ = 0;
}

/****************************************************************************
 * Fonction:	Membre::Membre
 * Description: Constructeur par param�tres.
 * Param�tres:	(const string&) nom
 * Retour:		aucun
 ****************************************************************************/
Membre::Membre(const string& nom)
{
	nom_ = nom;
	points_ = 0;
	capaciteCoupons_ = capaciteBillets_ = CAPACITE_INITIALE;
	billets_ = new Billet *[capaciteBillets_];
	nbBillets_ = 0;
	coupons_ = new Coupon *[capaciteCoupons_];
	nbCoupons_ = 0;
}

// TODO: Implementer si necessaire
/****************************************************************************
 * Fonction:	Membre::~Membre
 * Description: Destructeur, d�truit le membre du syst�me.
 * Param�tres:	aucun
 * Retour:		aucun
 ****************************************************************************/
Membre::~Membre() {}

		// M�thodes d'acc�s

/****************************************************************************
 * Fonction:	Membre::getNom
 * Description: Fournit le nom.
 * Param�tres:	aucun
 * Retour:		(string) Nom du membre
 ****************************************************************************/
string Membre::getNom() const
{
	return nom_;
}

/****************************************************************************
 * Fonction:	Membre::getPoints
 * Description: Fournit les points.
 * Param�tres:	aucun
 * Retour:		(int) Les points du membre
 ****************************************************************************/
int Membre::getPoints() const
{
	return points_;
}

/****************************************************************************
 * Fonction:	Membre::getBillets
 * Description: Fournit les billets.
 * Param�tres:	aucun
 * Retour:		(Billet**) tableau de billets
 ****************************************************************************/
Billet** Membre::getBillets() const
{
	return billets_;
}

/****************************************************************************
 * Fonction:	Membre::getNbBillets
 * Description: Fournit le nombre de billets du membre.
 * Param�tres:	aucun
 * Retour:		(int) nombre de billets du membre
 ****************************************************************************/
int Membre::getNbBillets() const
{
	return nbBillets_;
}

/****************************************************************************
 * Fonction:	Membre::getCapaciteBillets
 * Description: Fournit la capacit� du tableau de points.
 * Param�tres:	aucun
 * Retour:		(int) Capacite du tableau de billets
 ****************************************************************************/
int Membre::getCapaciteBillets() const
{
	return capaciteBillets_;
}

/****************************************************************************
 * Fonction:	Membre::getCoupons
 * Description: Fournit le tableau de coupons.
 * Param�tres:	aucun
 * Retour:		(Coupon**) tableau de coupons
 ****************************************************************************/
Coupon** Membre::getCoupons() const
{
	return coupons_;
}

/****************************************************************************
 * Fonction:	Membre::getNbCoupons
 * Description: Fournit le nombre de coupons.
 * Param�tres:	aucun
 * Retour:		(int) Nombre de coupons
 ****************************************************************************/
int Membre::getNbCoupons() const
{
	return nbCoupons_;
}

/****************************************************************************
 * Fonction:	Membre::getCapaciteCoupons
 * Description: Fournit la capacite en coupons.
 * Param�tres:	aucun
 * Retour:		(int) capacite de coupons
 ****************************************************************************/
int Membre::getCapaciteCoupons() const
{
	return capaciteCoupons_;
}

		// M�thodes de modification

/****************************************************************************
 * Fonction:	Membre::setNom
 * Description: Modificateur de nom.
 * Param�tres:	(const string& nom)
 * Retour:		aucun
 ****************************************************************************/
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

/****************************************************************************
 * Fonction:	Membre::modifierPoints
 * Description: Modificateur de points.
 * Param�tres:	(int) points
 * Retour:		aucun
 ****************************************************************************/
void Membre::modifierPoints(int points)	
{
	points_ += points;
}

/****************************************************************************
 * Fonction:	Membre::ajouterBillet
 * Description:	Ajoute un billet, double la capacite si elle �gale nbBillets_, modifie les points. Tient compte de la r�allocation dynamique.
 * Param�tres:	(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
 * Retour:		aucun
 ****************************************************************************/
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	//On v�rifie si on a de la place dans le tableau, si ce n'est pas le cas, on multiplie la capacit� par 2
	if (capaciteBillets_ <= nbBillets_) {
		capaciteBillets_ *= 2;
		Billet** nouveauTableau = new Billet *[capaciteBillets_] ;
		for (int i = 0; i < nbBillets_; i++) {
			nouveauTableau[i] = billets_[i];
		}
		delete[] billets_;
		billets_ = nouveauTableau;
	}
	//On cr�e un billet avec les param�tres re�us
	Billet* nouveauBillet = new Billet(pnr, nom_, prix, od, tarif, dateVol);
	billets_[nbBillets_++] = nouveauBillet;

	modifierPoints(int(calculerPoints(nouveauBillet)));
}

/****************************************************************************
 * Fonction:	Membre::ajouterCoupon
 * Description:	Ajoute un coupon, double la capacite si elle �gale nbCoupons_. Tient compte de la r�allocation dynamique.
 * Param�tres:	(Coupon* coupon)
 * Retour:		aucun
 ****************************************************************************/
void Membre::ajouterCoupon(Coupon* coupon)
{
	if (capaciteCoupons_ <= nbCoupons_) {
		capaciteCoupons_ *= 2;
		Coupon** nouveauTableau = new Coupon*[capaciteCoupons_];
		for (int i = 0; i < nbCoupons_; i++) {		
			nouveauTableau[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = nouveauTableau;
	}

	coupons_[nbCoupons_++] = coupon;

}

/****************************************************************************
 * Fonction:	Membre::retirerCoupon
 * Description:	Retire un coupon. Diminue nbCoupons_.
 * Param�tres:	(Coupon* coupon)
 * Retour:		aucun
 ****************************************************************************/
void Membre::retirerCoupon(Coupon* coupon)
{
	for (int i = 0; i < nbCoupons_; i++)
	{
		if (coupons_[i]->getCode() == coupon->getCode())
			coupons_[i] = coupons_[--nbCoupons_];
	}
}

/****************************************************************************
 * Fonction:	Membre::acheterCoupon
 * Description:	Ajoute le coupon(ach�te) si le membre poss�de assez de points.
 * Param�tres:	(Coupon* coupon)
 * Retour:		aucun
 ****************************************************************************/
void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_ >= coupon->getCout())
	{
		ajouterCoupon(coupon);
		modifierPoints(-coupon->getCout());

	}

}

/****************************************************************************
 * Fonction:	Membre::calculerPoints
 * Description:	Calcule le nombre de points incluant les points bonus selon la classe du billet.
 * Param�tres:	(Coupon* coupon)
 * Retour:		(double) nombre de points 
 ****************************************************************************/
double Membre::calculerPoints(Billet* billet)	
{
	double pointsBonus = 0.0;
	switch (billet->getTarif()) {
	case TarifBillet::Economie: pointsBonus = 0.0; break;
	case TarifBillet::PremiumEconomie: pointsBonus = 50.0; break;
	case TarifBillet::Affaire: pointsBonus = 150.0; break;
	case TarifBillet::Premiere: pointsBonus = 300.0;

	}

	return ((billet->getPrix() / 10.0) + pointsBonus);
}

/****************************************************************************
 * Fonction:	Membre::afficherMembre
 * Description:	Affiche les informations du membre, c-�-d le nombre de points, de billets et de coupons.
 * Param�tres:	aucun
 * Retour:		aucun
 ****************************************************************************/
void Membre::afficherMembre() const
{
	cout << "- Membre " << nom_ << ": \n"
		<< "\t- Points  : " << points_ << "\n"
		<< "\t- Billets : " << endl;
	for (int i = 0; i < nbBillets_; i++)
		billets_[i]->afficherBillet();
	cout << "\t- Coupons :" << endl;
	for (int i = 0; i < nbCoupons_; i++)
		coupons_[i]->afficherCoupon();
	cout << endl;
}

