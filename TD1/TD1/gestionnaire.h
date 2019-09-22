/**********************************************************************
 * Cours : INF1010
 * Travail pratique 1
 * Nom: gestionnaire.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#ifndef GESTIONNAIRE_H
#define	GESTIONNAIRE_H

#include "membre.h";

class Gestionnaire {

public:
	// TODO: Implementer toutes les methodes
	Gestionnaire();

	// TODO: Implementer si necessaire
	~Gestionnaire();

	// Getters
	Membre** getMembres() const;
	int getNbMembres() const;
	int getCapaciteMembres() const;
	Coupon** getCoupons() const;
	int getNbCoupons() const;
	int getCapaciteCoupons() const;

	void ajouterMembre(const string& nomMembre);
	void ajouterCoupon(const string& code, double rabais, int cout);

	Membre* trouverMembre(const string& nomMembre);
	void assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon);
	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(const string& nomMembre);

	void afficherInfos() const;
private:
	Membre** membres_;
	int nbMembres_;
	int capaciteMembres_;
	Coupon** coupons_;
	int nbCoupons_;
	int capaciteCoupons_;
};

#endif // !GESTIONNAIRE_H



