/*
* Titre : membre.cpp - Travail Pratique #4
* Date : 5 Octobre 2019
* Auteur : Philippe CÔTÉ-MORNEAULT
*/

#include "membre.h"

Membre::Membre() :
	nom_("")
{
}

Membre::Membre(const string& nom) :
	nom_(nom)
{
}

// TODO
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	Billet* billet = nullptr;
	for (size_t i = 0; i < membre.billets_.size(); ++i) {
		billet = membre.getBillets()[i];
		if (BilletRegulier* billetRegulier = dynamic_cast<BilletRegulier*>(billet))
			billets_.push_back(billetRegulier->clone());
		else if (FlightPass* flightPass = dynamic_cast<FlightPass*>(billet))
			billets_.push_back(flightPass->clone());
	}
}

Membre::~Membre()
{
	for (size_t i = 0; i < billets_.size(); ++i) {
		delete billets_[i];
	}
}

string Membre::getNom() const
{
	return nom_;
}

vector<Billet*> Membre::getBillets() const
{
	return billets_;
}

void Membre::setNom(const string& nom)
{
	nom_ = nom;
}

// TODO
void Membre::utiliserBillet(const string& pnr)
{
	int indexTrouve = -1;
	for (size_t i = 0; i < billets_.size(); ++i) {
		if (billets_[i]->getPnr() == pnr) {
			indexTrouve = i;
			break;
		}
	}

	if (indexTrouve == -1) {
		cout << "Le billet n'est pas trouve" << endl;
		return;
	}
	if (FlightPass* flightPass = dynamic_cast<FlightPass*>(billets_[indexTrouve])) {
		flightPass->decrementeNbUtilisations();
		if (flightPass->getNbUtilisationsRestante() > 0) {
			return;
		}
	}
		
	delete billets_[indexTrouve];
	billets_[indexTrouve] = billets_[billets_.size() - 1];
	billets_.pop_back();
}

void Membre::ajouterBillet(Billet* billet)
{
	billet->setNomPassager(nom_);
	billets_.push_back(billet);
}

bool Membre::operator==(const string& nomMembre) const
{
	return nom_ == nomMembre;
}

bool operator==(const string& nomMembre, const Membre& membre)
{
	return nomMembre == membre.nom_;
}

// TODO
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;

		for (size_t i = 0; i < billets_.size(); ++i) {
			delete billets_[i];
		}

		billets_.clear();

		string nomTemp = nom_;										
		this->Membre::Membre(membre);
		nom_ = nomTemp;
	}

	return *this;
}


// TODO
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;
	for (size_t i = 0; i < billets_.size(); i++) {
		
		if (BilletRegulier* billetRegulier = dynamic_cast<BilletRegulier*>(billets_[i]))
			billetRegulier->afficher(o);
		else if (FlightPass* flightPass = dynamic_cast<FlightPass*>(billets_[i]))
			flightPass->afficher(o);
		else if (Billet* billet = dynamic_cast<Billet*>(billets_[i]))
			billet->afficher(o);
	}
	o << endl;
}