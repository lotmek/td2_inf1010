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
	//int coutAvecRabais = coupon->getCout() - coupon->getRabais()*coupon->getCout();  //On avait pas appliqué le rabais.   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (points_ > coupon->getCout()) {
		*this += coupon;
		modifierPoints(-coupon->getCout());
	}
}


Membre& MembreRegulier::operator+=(Coupon* coupon)
{
	coupons_.push_back(coupon);

	return *this;
}

Membre& MembreRegulier::operator-=(Coupon* coupon)
{
	for (int i = 0; i < coupons_.size(); i++) {
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
	modifierPoints(calculerPoints(billets_[billets_.size() -1] ));
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

ostream& operator<<(ostream& os, const MembreRegulier& membreRegulier)
{
	Membre membreO = Membre(membreRegulier);
	os << membreO;
	os << "\t- Points : " << membreRegulier.points_ << endl;
	os << "\t- Coupons : " << endl;
	for (int i = 0; i < membreRegulier.coupons_.size(); i++)
		os << *membreRegulier.coupons_[i];

	return os;
}


