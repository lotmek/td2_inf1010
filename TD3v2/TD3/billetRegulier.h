/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: billetRegulier.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#ifndef BILLET_REGULIER_H
#define BILLET_REGULIER_H
#include "billet.h"

class BilletRegulier : public Billet {

public:
	
	//� faire 
	BilletRegulier(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, const string& dateVol, TypeBillet typeBillet);
	//� faire 
	string getDateVol() const;
	//� faire 
	void setDateVol(const string& dateVol);

	//� faire 
	virtual void afficherBillet(ostream& o) const;
private:
	string dateVol_;
};

#endif