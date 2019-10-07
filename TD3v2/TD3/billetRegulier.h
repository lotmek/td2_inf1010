/*
* Titre : billetRegulier.h - Travail Pratique #3
* Date : 20 Septembre 2019
* Auteur : Jeffrey Lavallee
*/

#ifndef BILLET_REGULIER_H
#define BILLET_REGULIER_H
#include "billet.h"

class BilletRegulier : public Billet {

public:
	
	//à faire 
	BilletRegulier(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol, TypeBillet typeBillet);
	//à faire 
	string getDateVol() const;
	//à faire 
	void setDateVol(const string& dateVol);

	//à faire 
	virtual void afficherBillet() const;
private:
	string dateVol_;
};

#endif