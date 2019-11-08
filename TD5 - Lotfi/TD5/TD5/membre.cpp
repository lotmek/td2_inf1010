/********************************************
* Titre: Travail pratique #5 - membre.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "membre.h"

Membre::Membre() :
	nom_("")
{
}

Membre::Membre(const string& nom) :
	nom_(nom)
{
}

//todo
Membre::Membre(const Membre& membre) :
	nom_(membre.nom_)
{
	billets_.clear();
	copy(membre.getBillets().begin(), membre.getBillets().end(), back_inserter(billets_));
}

//todo
Membre::~Membre()
{
	for (vector<Billet*>::iterator it = billets_.begin(); it != billets_.end(); it++)
		delete *it;
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

//todo implemente trouverBillet() signature dans le .h
vector<Billet*>::iterator Membre::trouverBillet(const string& pnr)
{
	for (vector<Billet*>::iterator it = billets_.begin(); it != billets_.end(); it++) {
		if ((*it)->getPnr() == pnr) return it;
	}

}

//todo
void Membre::utiliserBillet(const string& pnr)
{
	vector<Billet*>::iterator it = trouverBillet(pnr);

	if (auto flightPass = dynamic_cast<FlightPass*>(*it)) {
		flightPass->decrementeNbUtilisations();
		if (flightPass->getNbUtilisationsRestante() > 0) {
			return;
		}
	}

	delete *it;
	billets_.erase(it);
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


//todo
Membre& Membre::operator=(const Membre& membre)
{
	if (this != &membre) {
		nom_ = membre.nom_;

		for (vector<Billet*>::iterator it = billets_.begin(); it != billets_.end(); it++)
			delete *it;

		billets_.clear();

		copy(membre.getBillets().begin(), membre.getBillets().end(), back_inserter(billets_));
	}

	return *this;
}


//todo
void Membre::afficher(ostream& o) const
{
	o << setfill(' ');
	o << "- Membre " << nom_ << ":" << endl;
	o << "\t" << "- Billets :" << endl;

	copy(billets_.begin(), billets_.end(), ostream_iterator<Billet*>(cout, "\n"));
}