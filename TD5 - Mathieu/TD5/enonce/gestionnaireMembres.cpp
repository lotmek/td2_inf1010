/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "GestionnaireMembres.h"
#include <numeric>

void GestionnaireMembres::assignerBillet(Billet* billet, const string& nomMembre, int rabaisCoupon)
{
	Membre* membre = conteneur_[nomMembre];

	if (membre == nullptr) {
		delete billet;
		return;
	}

	double prix = billet->getPrix();

	if (auto solde = dynamic_cast<Solde*>(billet)) {
		prix = solde->getPrixBase();
	}

	
	prix -= rabaisCoupon;
	

	if (auto membrePremium = dynamic_cast<MembrePremium*>(membre)) {
		double rabais = 0.005 * membrePremium->getpointsCumulee() / 1000;
		if (rabais > 0.1)
			rabais = 0.1;

		prix *= (1 - rabais);
	}

	billet->setPrix(prix);
	membre->ajouterBillet(billet);
}



double GestionnaireMembres::calculerRevenu() const
{
	//TODO
	double revenu = 0;
	for (pair<string, Membre*> membre: conteneur_) {
		for_each(membre.second->getBillets().begin(), membre.second->getBillets().end(), [&revenu](Billet* billet) {
			revenu += billet->getPrix(); 
		});
	}
	return revenu;
}

int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{
	//TODO
	int nbBilletsSolde = 0;
	for (pair<string, Membre*> membre : conteneur_) {
		for_each(membre.second->getBillets().begin(), membre.second->getBillets().end(), [&nbBilletsSolde](Billet* billet) {
			//Si le billet est en solde, on incremente la somme
			if (auto val = dynamic_cast<Solde*>(billet) )	++nbBilletsSolde;
			
		}); 
	}
	return nbBilletsSolde;
}

Billet* GestionnaireMembres::getBilletMin(string nomMembre) const {
	Membre* membreATrouver = nullptr;
	//Recherche du membre
	for_each(conteneur_.begin(), conteneur_.end(), [&membreATrouver, &nomMembre](pair<string, Membre*> membre) {
		//Vérification si le membre est celui qu'on recherche
		if (membre.second->getNom() == nomMembre) {
			membreATrouver = membre.second;
		}			
	});

	//Recherche du bon billet, s'il existe
	if (membreATrouver != nullptr) {
		vector<Billet*>::iterator it = min_element(membreATrouver->getBillets().begin(), membreATrouver->getBillets().end(), 
			[](Billet* billet1, Billet* billet2) {
				if (billet1->getPrix() < billet2->getPrix())
					return true;
				return false;
		});
		return *it;
	}	
	return nullptr;
}

Billet* GestionnaireMembres::getBilletMax(string nomMembre) const {
	Membre* membreATrouver = nullptr;
	//Recherche du membre
	for_each(conteneur_.begin(), conteneur_.end(), [&membreATrouver, &nomMembre](pair<string, Membre*> membre) {
		//Vérification si le membre est celui qu'on recherche
		if (membre.second->getNom() == nomMembre) {
			membreATrouver = membre.second;
		}
	});

	//Recherche du bon billet, s'il existe
	if (membreATrouver != nullptr) {
		vector<Billet*>::iterator it = min_element(membreATrouver->getBillets().begin(), membreATrouver->getBillets().end(),
			[](Billet* billet1, Billet* billet2) {
			if (billet1->getPrix() > billet2->getPrix())
				return true;
			return false;
		});
		//Retour du billet pointé par l'itérateur
		return *it;	
	}
	//Retour nulle si on n'a rien trouvé
	return nullptr;
}

vector<Billet*> GestionnaireMembres::trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const {
	IntervallePrixBillet intervalle(prixInf, prixSup);

	vector<Billet*> billets = membre->getBillets(), billetsRetour;
	copy_if(billets.begin(), billets.end(), back_inserter(billetsRetour), intervalle);
	
	return billetsRetour;
}


void GestionnaireMembres::afficher(ostream& o) const
{
	//TODO
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for_each(conteneur_.begin(), conteneur_.end(), [&o](const pair<string, Membre*>& membre){
		membre.second->afficher(o);
	});
}
