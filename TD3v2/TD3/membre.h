/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: membre.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#ifndef MEMBRE_H
#define MEMBRE_H

#include <string>
#include <vector>

#include "flightPass.h"
#include "billetRegulier.h"
#include "coupon.h"

using namespace std;

enum TypeMembre { Membre_Regulier, Membre_Premium, Membre_Occasionnel};

class Membre {
public:
	// Constructeurs

	//� modifer
	Membre();
	//� modifer
	Membre(const string& nom, TypeMembre typeMembre);
	//� modifer
	Membre(const Membre& membre);

	virtual ~Membre(); //virtual permet de bien delete les object deriv� 

	// Getters
	string getNom() const;
	TypeMembre getTypeMembre() const;

	vector<Billet*> getBillets() const;


	// Setters
	void setNom(const string& nom);

	//� faire
	void utiliserBillet(const string& pnr);

	//� modifer
	virtual void ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet , const string& dateVol);

	bool operator==(const string& nomMembre) const;
	friend bool operator==(const string& nomMembre, const Membre& membre);

	Membre& operator=(const Membre& membre);

	//� modifer
	virtual void afficherMembre(ostream& o) const;
	friend ostream& operator<<(ostream& o, const Membre& membre);
protected:
	string nom_;
	TypeMembre typeMembre_;
	vector<Billet*> billets_;
};


#endif
