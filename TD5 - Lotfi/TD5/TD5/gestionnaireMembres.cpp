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
	for_each(conteneur_.begin(), conteneur_.end(), [&revenu]( const pair<string, Membre*>& membre)
	{
		for_each(membre.second->getBillets().begin(), membre.second->getBillets().end(), [&revenu](const Billet*& billet)
		{
			revenu += billet->getPrix(); 
		});
	});

	return revenu;
}

int GestionnaireMembres::calculerNombreBilletsEnSolde() const
{
	//TODO
	int nbBilletsSolde = 0;
	for_each(conteneur_.begin(), conteneur_.end(), [&nbBilletsSolde](const pair<string, Membre*>& membre)
	{
		nbBilletsSolde = count_if(membre.second->getBillets().begin(), membre.second->getBillets().end(), [&nbBilletsSolde](Billet* billet) 
		{
			if (dynamic_cast<Solde*>(billet)) return true;
		});
	});

	return nbBilletsSolde;
}



//TODO
Billet* GestionnaireMembres::getBilletMin(string nomMembre) const
{
	for_each(conteneur_.begin(), conteneur_.end(), [&nomMembre](const pair<string, Membre*>& membre) 
	{
		if (membre.second->getNom() == nomMembre) 
		{
			auto billetMin = min_element(membre.second->getBillets().begin(), membre.second->getBillets().end(), [](const Billet*& billet1, const Billet*& billet2)
			{
				if (billet2->getPrix() < billet1->getPrix())
					return true;
				else
					return false;
			});
			return billetMin;
		}
	});
	return nullptr;

}



//TODO
Billet* GestionnaireMembres::getBilletMax(string nomMembre) const
{
	for_each(conteneur_.begin(), conteneur_.end(), [&nomMembre](const pair<string, Membre*>& membre) 
	{
		if (membre.second->getNom() == nomMembre) 
		{
			auto billetMin = max_element(membre.second->getBillets().begin(), membre.second->getBillets().end(), [](const Billet*& billet1, const Billet*& billet2)
			{
				if (billet2->getPrix() > billet1->getPrix())
					return true;
				else
					return false;
			});
			return billetMin;
		}
	});

	return nullptr;
}

void GestionnaireMembres::afficher(ostream& o) const
{
	//TODO
	o << "=================== ETAT ACTUEL DU PROGRAMME ==================\n\n";

	for_each(conteneur_.begin(), conteneur_.end(), [&o](const pair<string, Membre*>& membre)
	{
		membre.second->afficher(o);
	});
}
