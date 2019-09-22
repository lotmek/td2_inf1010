
#include "membre.h"

// TODO: Implementer toutes les methodes
Membre::Membre() 
{
	nom_ = "Bill Gates";
	points_ = 0;
	capaciteCoupons_ = capaciteBillets_ = CAPACITE_INITIALE;
	billets_ = new Billet*[capaciteBillets_];
	nbBillets_ = 0;
	coupons_ = new Coupon * [capaciteCoupons_];
	nbCoupons_ = 0;
}
Membre::Membre(const string& nom)
{
	nom_ = nom;
	points_ = 0;
	capaciteCoupons_ = capaciteBillets_ = CAPACITE_INITIALE;
	billets_ = new Billet * [capaciteBillets_];
	nbBillets_ = 0;
	coupons_ = new Coupon * [capaciteCoupons_];
	nbCoupons_ = 0;
}

// TODO: Implementer si necessaire
Membre::~Membre(){}

// Méthodes d'accès
string Membre::getNom()
{
	return nom_;
}
int Membre::getPoints()
{
	return points_;
}
Billet** Membre::getBillets()
{
	return billets_;
}
int Membre::getNbBillets()
{
	return nbBillets_;
}
int Membre::getCapaciteBillets()
{
	return capaciteBillets_;
}
Coupon** Membre::getCoupons()
{
	return coupons_;
}
int Membre::getNbCoupons()
{
	return nbCoupons_;
}
int Membre::getCapaciteCoupons()
{
	return capaciteCoupons_;
}

// Méthodes de modification
void Membre::setNom(const string& nom)
{
	nom_ = nom;
}
void Membre::modifierPoints(int points)
{
	points_ += points;
}
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, const string& dateVol)
{
	//On vérifie si on a de la place dans le tableau, si ce n'est pas le cas, on multiplie la capacité par 2
	if (capaciteBillets_ <= nbBillets_) {
		capaciteBillets_ *= 2;
		Billet** nouveauTableau = new Billet * [capaciteBillets_];
		for (int i = 0; i < nbBillets_; i++) {
			nouveauTableau[i] = billets_[i];
		}
		delete[] billets_;
		billets_ = nouveauTableau;
	}
	//On crée un billet avec les paramètres reçus
	Billet* nouveauBillet = new Billet(pnr, nom_, prix, od, tarif, dateVol);
	billets_[nbBillets_++] = nouveauBillet;

	modifierPoints(calculerPoints(nouveauBillet));
}
void Membre::ajouterCoupon(Coupon* coupon)
{
	if (capaciteCoupons_ <= nbCoupons_) {
		capaciteCoupons_ *= 2;
		Coupon** nouveauTableau = new Coupon* [capaciteCoupons_];
		for (int i = 0; i < nbBillets_; i++) {
			nouveauTableau[i] = coupons_[i];
		}
		delete[] coupons_;
		coupons_ = nouveauTableau;
	}

	coupons_[nbCoupons_++] = coupon;

}
void Membre::retirerCoupon(Coupon* coupon)
{
	for (int i = 0; i < nbCoupons_; i++)
	{
		if (coupons_[i]->getCode() == coupon->getCode())
			coupons_[i] = coupons_[--nbCoupons_];
	}
}
void Membre::acheterCoupon(Coupon* coupon)
{
	if (points_ >= coupon->getCout()) 
	{
		ajouterCoupon(coupon);
		modifierPoints(-coupon->getCout());
		
	}
	
}
double Membre::calculerPoints(Billet* billet)
{
	double pointsBonus = 0.0;
	switch (billet->getTarif()) {
		case TarifBillet::Economie: pointsBonus = 0.0 ; break;
		case TarifBillet::PremiumEconomie: pointsBonus = 50.0; break;
		case TarifBillet::Affaire: pointsBonus = 150.0; break;
		case TarifBillet::Premiere: pointsBonus = 300.0; 

	}

	return ((billet->getPrix() / 10.0) + pointsBonus);
}
void Membre::afficherMembre()
{
	cout << "- Membre " << nom_ << ": \n"
		<< "\t- Points  : " << points_ << "\n"
		<< "\t- Billets : " << endl;
	for (int i = 0; i < nbBillets_; i++)
		billets_[i]->afficherBillet();
	cout << "\t- Coupons :" << endl;
	for (int i = 0; i < nbCoupons_; i++)
		coupons_[i]->afficherCoupon();
}
