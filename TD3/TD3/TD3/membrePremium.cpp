#include "membrePremium.h"

MembrePremium::MembrePremium(const string& nom)
	:MembreRegulier(nom, TypeMembre::Membre_Premium),
	pointsCumules_(0),
	joursRestants_(JOUR_RESTANT_INITIALE)
{
}

void MembrePremium::setJourRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;
}

void MembrePremium::modifierPointsCumules(unsigned int pointCumulee)
{
	pointsCumules_ += pointCumulee;
}

unsigned int MembrePremium::getJourRestants() const
{
	return joursRestants_;
}

unsigned int MembrePremium::getpointsCumulee() const
{
	return pointsCumules_;
}

void MembrePremium::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	MembreRegulier::ajouterBillet(pnr, prix, od, tarif, typeBillet, dateVol);
	modifierPointsCumules(calculerPoints(billets_[billets_.size() - 1]));
}

void MembrePremium::acheterCoupon(Coupon* coupon)
{
	double rabais = pointsCumules_/1000.0 /100.0 >= 0.2 ? 0.2 : pointsCumules_ / 1000.0 /100.0;		// A CHANGER ,, c'est pas les points cumules qui ont un maximum, mais le rabais.
	double rabaisTemp = coupon->getRabais();
	coupon->setRabais(rabais);		// de coupon, c'est le Gestionnaire qui s'en occupe !!!!!!!!!!!!!!!
	MembreRegulier::acheterCoupon(coupon);
	coupon->setRabais(rabaisTemp);
}

ostream& operator<<(ostream& os, const MembrePremium& membrePremium)
{
	MembreRegulier membreO = MembreRegulier(membrePremium);
	os << membreO;
	os << "\t-Points cumules : " << membrePremium.pointsCumules_ << endl;
	os << "\t-Jours premium restant : " << membrePremium.joursRestants_ << endl;

	return os;
}