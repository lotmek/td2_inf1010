#include "membreRegulier.h"


MembreRegulier::MembreRegulier(const string& nom, TypeMembre typeMembre)
	:Membre(nom, typeMembre), points_(0)    //ICI J'AI AJOUTÉ points_(0) , CAR ON NE L'AVAIT PAS MIS ERREURS 10, 13, 15 à 18, 28 à 30, 42, 43 CORRIGÉES !!!!!!!!!!!!!!!!!!!1
{
}

int MembreRegulier::getPoints() const
{
	return points_;
}

vector<Coupon*> MembreRegulier::getCoupons() const
{
	return coupons_;
}

void MembreRegulier::acheterCoupon(Coupon* coupon)
{
	int cout = coupon->getCout();
	if (typeMembre_ == Membre_Premium)
		cout -= coupon->getRabais()*cout;
	if (points_ > cout) {
		*this += coupon;
		modifierPoints(-cout);
	}
}


Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

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

void MembreRegulier::modifierPoints(int points)
{
	points_ += points;
}


void MembreRegulier::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	Membre::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	modifierPoints(int(calculerPoints(billets_[billets_.size() -1] )));
}

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

void MembreRegulier::afficherMembre() const
{
	Membre::afficherMembre();
	cout << "\t- Points : " << points_<< endl;
	cout << "\t- Coupons : " << endl;
	for (unsigned i = 0; i < coupons_.size(); i++)
		cout << *coupons_[i];

}


