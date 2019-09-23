/**********************************************************************
 * Cours : INF1010
 * Travail pratique 2
 * Nom: membre.cpp
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/

#ifndef GESTIONNAIRE_H
#define	GESTIONNAIRE_H

#include <vector>

#include "membre.h"

class Gestionnaire {
public:
	// Constructeurs
	Gestionnaire();

	~Gestionnaire();

	// Getters
	vector<Membre*> getMembres() const;
	vector<Coupon*> getCoupons() const;

	void ajouterMembre(const string& nomMembre);
	void ajouterCoupon(const string& code, double rabais, int cout);

	Membre* trouverMembre(const string& nomMembre) const;
	void assignerBillet(const string& nomMembre, const string& pnr, double prixBase, const string& od, TarifBillet tarif, const string& dateVol, bool utiliserCoupon);
	double appliquerCoupon(Membre* membre, double prix);
	void acheterCoupon(const string& nomMembre);

	// TODO: Remplacer cette methode par l'operateur <<
	friend ostream& operator<<(ostream& o, const Gestionnaire& gestionnaire);
private:
	// TODO: Convertir membres_ en vecteur
	vector<Membre*> membres_;
	// TODO: Convertir coupons_ en vecteur
	vector<Coupon*> coupons_;
};
#endif // !GESTIONNAIRE_H



