/*
* Titre : flightPassSolde.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "flightPassSolde.h"

// TODO
FlightPassSolde::FlightPassSolde(const string& pnr, double prix, const string& od, TarifBillet tarif, double pourcentageSolde):
	FlightPass(pnr, prix, od, tarif), Solde(pourcentageSolde)
{
}

// TODO
double FlightPassSolde::getPrix() const
{
	return prix_ - prix_ * pourcentageSolde_;
}

// TODO
double FlightPassSolde::getPrixBase() const
{
	return prix_;
}

// TODO
FlightPassSolde* FlightPassSolde::clone()
{
	return new FlightPassSolde(pnr_, prix_, od_, tarif_, pourcentageSolde_);
}

// TODO
void FlightPassSolde::afficher(ostream& o)
{
	FlightPass::afficher(o);
}