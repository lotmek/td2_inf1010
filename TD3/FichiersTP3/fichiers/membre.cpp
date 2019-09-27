/*
 * Date : 12 Septembre 2019
 * Auteur : Philippe CÔTÉ-MORNEAULT
 */

#include "membre.h"

//a changer
Membre::Membre() :
	nom_(""),
	typeMembre_(TypeMembre::Membre_Regulier)
{
}

//a changer
Membre::Membre(const string& nom, TypeMembre typeMembre) :
	nom_(nom),
	typeMembre_(typeMembre)
{
}

//a changer
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_),
	typeMembre_(membre.typeMembre_)
{
	for (int i = 0; i < membre.billets_.size(); ++i) {
		BilletRegulier * billetReg = static_cast<BilletRegulier*>(membre.billets_[i]);
		ajouterBillet(membre.billets_[i]->getPnr(), membre.billets_[i]->getPrix(), membre.billets_[i]->getOd(), membre.billets_[i]->getTarif(), membre.billets_[i]->getTypeBillet(), billetReg->getDateVol());

	}
}

Membre::~Membre()
{
	for (int i = 0; i < billets_.size(); i++) {
		delete billets_[i];
	}
}

string Membre::getNom() const
{
	return nom_;
}

TypeMembre Membre::getTypeMembre() const
{
	return typeMembre_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}


void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

void Membre::utiliserBillet(const string& pnr)
{
	for (int i = 0; i < billets_.size(); ++i) {
		if (billets_[i]->getPnr() == pnr) {
			if(billets_[i]->getTypeBillet() == TypeBillet::Flight_Pass){
				FlightPass* flightpass = static_cast<FlightPass*>(billets_[i]);
				flightpass->decrementeNbUtilisations();
				if (flightpass->getNbUtilisationsRestante() == 0) {
					billets_[i] = billets_[billets_.size()-1];
					delete billets_[billets_.size() - 1];
					billets_.pop_back();
				}
			}

			else {
				billets_[i] = billets_[billets_.size() - 1];
				delete billets_[billets_.size() - 1];
				billets_.pop_back();
			}
		}
	}
}

// a changer
void Membre::ajouterBillet(const string& pnr, double prix, const string& od, TarifBillet tarif, TypeBillet typeBillet, const string& dateVol)
{
	Billet* billet = new Billet(pnr, nom_, prix, od, tarif, typeBillet);
	switch (typeBillet) {
		case TypeBillet::Billet_Base : 
			billets_.push_back(billet);
			break;
		case TypeBillet::Billet_Regulier :
			BilletRegulier* billetReg = static_cast<BilletRegulier*>(billet);
			billetReg->setDateVol(dateVol);
			billets_.push_back(billetReg);
			break;
		case TypeBillet::Flight_Pass:
			FlightPass* flightpass = static_cast<FlightPass*>(billet);
			billets_.push_back(flightpass);
			break;
	}

	//inutile, cette classe ne fait pas partie du programme de fidèlité.
	//modifierPoints(calculerPoints(billet));
}



bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}

Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;
		typeMembre_ = membre.typeMembre_;


		for (int i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		for (int i = 0; i < membre.billets_.size(); i++) {
			billets_.push_back(new Billet(*membre.billets_[i]));
		}
	}

	return *this;
}

// a changer
ostream& operator<<(ostream& o, const Membre& membre)
{
	o << setfill(' ');
	o << "- Membre " << membre.nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	for (int i = 0; i < membre.billets_.size(); i++) {
		switch (membre.billets_[i]->getTypeBillet()) {
		case TypeBillet::Billet_Base:
			o << *membre.billets_[i];
			break;
		case TypeBillet::Billet_Regulier:
			BilletRegulier* billetReg = static_cast<BilletRegulier*>(membre.billets_[i]);
			o << *billetReg;
			break;
		case TypeBillet::Flight_Pass:
			FlightPass* flightpass = static_cast<FlightPass*>(membre.billets_[i]);
			o << *flightpass;
			break;
		}
	}

	return o << endl;
}
