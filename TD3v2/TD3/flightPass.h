/**********************************************************************
 * Cours : INF1010
 * Travail pratique 3
 * Nom: flightPass.h
 * Auteurs:		 Lotfi		Meklati      1953909
 *			     Mathieu	Bussières    1882012
 * Equipe : 17
 * Groupe : 03
 **********************************************************************/
#ifndef FLIGHT_PASS_H
#define FLIGHT_PASS_H

#include "billet.h"

class FlightPass : public Billet {
public:
	//à faire 
	FlightPass(const string& pnr, const string& nomPassager, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet);

	//à faire 
	void decrementeNbUtilisations();

	//à faire 
	 int getNbUtilisationsRestante() const;

	 //à faire 
	 virtual void afficherBillet(ostream& o) const;

private:
	 int nbUtilisationsRestante_;
};

#endif