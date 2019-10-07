/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#ifndef MEMBRE_PREMIUM_H
#define MEMBRE_PREMIUM_H


#include "membreRegulier.h"

class MembrePremium : public MembreRegulier {
public:
	//� faire
	MembrePremium(const string& nom);

	//setters
	//� faire
	void setJourRestants(unsigned int joursRestants);
	//� faire
	void modifierPointsCumules(unsigned int pointCumulee);


	//getters
	//� faire
	unsigned int getJourRestants() const;
	//� faire
	unsigned int getpointsCumulee() const;

	//� faire
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol) override;
	//� faire
	void acheterCoupon(Coupon* coupon);

	//� faire
	virtual void afficherMembre(ostream& o) const;

private:
	unsigned int joursRestants_;
	unsigned int pointsCumules_;

};

#endif