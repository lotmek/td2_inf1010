/********************************************
* Titre: Travail pratique #5 - gestionnaireMembres.cpp
* Date: 30 octobre 2019
* Auteur: Allan BEDDOUK & Jeffrey LAVALLEE
*******************************************/

#include "GestionnaireMembres.h"
#include <numeric>

void GestionnaireMembres::assignerBillet(Billet* billet, const string& nomMembre, double rabaisCoupon)
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
		//vecteur créé car écrire directement membre.second->getBillets().begin() ou end() ne marche pas
		vector<Billet*> vec = membre.second->getBillets();
		for_each(vec.begin(), vec.end(), [&revenu](Billet* billet)
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
	vector<Billet*> billetsCopie;

	//On ajoute les billets de tous les membres au vecteur billetsCopie ...
	for_each(conteneur_.begin(), conteneur_.end(), [&billetsCopie](const pair<string, Membre*>& membre)
	{
		vector<Billet*> vec = membre.second->getBillets();
		billetsCopie.insert(billetsCopie.end(), vec.begin(), vec.end());
	});

	//... puis on compte les billets qui sont soldés
	for_each(billetsCopie.begin(), billetsCopie.end(), [&nbBilletsSolde](Billet* billet) 
	{
		if (auto d = dynamic_cast<Solde*>(billet)) ++nbBilletsSolde;
	});


	return nbBilletsSolde;
}



//TODO
Billet* GestionnaireMembres::getBilletMin(string nomMembre) const
{
	Membre* membreRecherche = nullptr;
	Billet* billet = nullptr;
	for_each(conteneur_.begin(), conteneur_.end(), [&nomMembre, &membreRecherche](const pair<string, Membre*>& membre)
	{
		//On vérifie si le membre a le même nom
		if (membre.second->getNom() == nomMembre) membreRecherche = membre.second;
	});

	if(membreRecherche != nullptr){
			//On copie son vecteur de billets
			vector<Billet*> vec = membreRecherche->getBillets();

			//On fait pointer l'itérateur vers l'élément le plus petit grâce à une comparaison des prix
			vector<Billet*>::iterator it = min_element(vec.begin(), vec.end(), [](Billet* billet1, Billet* billet2)
			{
				if (billet1->getPrix() < billet2->getPrix())
					return true;
				else
					return false;
			});

			//On retourne le billet pointé par l'itérateur
			return *it;

	}
	

	//Retourne nullptr si on a pas trouvé le membre
	return nullptr;

}



//TODO
Billet* GestionnaireMembres::getBilletMax(string nomMembre) const
{
	Membre* membreRecherche = nullptr;
	Billet* billet = nullptr;
	for_each(conteneur_.begin(), conteneur_.end(), [&nomMembre, &membreRecherche](const pair<string, Membre*>& membre)
	{
		//On vérifie si le membre a le même nom
		if (membre.second->getNom() == nomMembre) membreRecherche = membre.second;
	});

	if (membreRecherche != nullptr) {
		//On copie son vecteur de billets
		vector<Billet*> vec = membreRecherche->getBillets();

		//On fait pointer l'itérateur vers l'élément le plus petit grâce à une comparaison des prix
		vector<Billet*>::iterator it = max_element(vec.begin(), vec.end(), [](Billet* billet1, Billet* billet2)
		{
			if (billet2->getPrix() > billet1->getPrix())
				return true;
			else
				return false;
		});

		//On retourne le billet pointé par l'itérateur
		return *it;

	}


	//Retourne nullptr si on a pas trouvé le membre
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

vector<Billet*> GestionnaireMembres::trouverBilletParIntervallle(Membre* membre, double prixInf, double prixSup) const 
{
	IntervallePrixBillet intervalle(prixInf, prixSup);
	
	vector<Billet*> billets = membre->getBillets(), billetsIntervalle;

	//On copie les billets qui satisfont le foncteur "IntervallePrixBillet"
	copy_if(billets.begin(), billets.end(), back_inserter(billetsIntervalle), intervalle);
	return billetsIntervalle;
}