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

void MembrePremium::afficherMembre() const
{
	cout << setfill(' ');
	cout << "- Membre " << nom_ << ":" << endl;
	cout << "\t- Billets :" << endl;
	for (int i = 0; i < billets_.size(); i++) {
		if (billets_[i]->getTypeBillet() == Billet_Regulier) {
			BilletRegulier * billetReg = static_cast<BilletRegulier*>(billets_[i]);
			cout << *billetReg;
		}

		else if (billets_[i]->getTypeBillet() == Flight_Pass) {
			FlightPass * fp = static_cast<FlightPass*>(billets_[i]);
			cout << *fp;
		}

		else
			cout << billets_[i];
	}
	cout << "\t-Points cumules : " << pointsCumules_ << endl;
	cout << "\t-Jours premium restant : " << joursRestants_ << endl;

}