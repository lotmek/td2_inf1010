/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: flightPass.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussi�res    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#ifndef FLIGHT_PASS_H
#define FLIGHT_PASS_H

#include "billet.h"

class FlightPass : public Billet {
public:
	//� faire 
	FlightPass(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet);

	//� faire 
	void decrementeNbUtilisations();

	//� faire 
	 int getNbUtilisationsRestante() const;

	 //� faire 
	 virtual void afficherBillet(ostream& o) const;

private:
	 int nbUtilisationsRestante_;
};

#endif