/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#ifndef MEMBRE_PREMIUM_H
#define MEMBRE_PREMIUM_H


#include "membreRegulier.h"

class MembrePremium : public MembreRegulier {
public:
	//à faire
	MembrePremium(const string& nom);

	//setters
	//à faire
	void setJourRestants(unsigned int joursRestants);
	//à faire
	void modifierPointsCumules(unsigned int pointCumulee);


	//getters
	//à faire
	unsigned int getJourRestants() const;
	//à faire
	unsigned int getpointsCumulee() const;

	//à faire
	void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol) override;
	//à faire
	void acheterCoupon(Coupon* coupon);

	//à faire
	virtual void afficherMembre(ostream& o) const;

private:
	unsigned int joursRestants_;
	unsigned int pointsCumules_;

};

#endif