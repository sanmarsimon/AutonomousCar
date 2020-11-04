
#include <iostream>
#include "Graphe.h"

//Fonction permettant de vérifier la nature des entrées de l'utilisateur
bool estUnNombre(string input) {
	for (size_t i = 0; i < input.length(); i++)
		if (!isdigit(input[i])) {
			return false;
		}
	return true;
}

int main() {
	//Initialisation des conditions de la boucle principale
	string reponse;
	bool aChoisie = false;
	bool quitter = false;

	//Initialisation de la voiture
	string typeCarburant = "null";
	string autoMax = "null";
	string coeffPerte = "null";
	Voiture voiture;

	//Initialisation de la carte
	string nomCarte = "null";
	Graphe carte;

	//Initialisation du chemin
	string idPointDepart = "null";
	string idPointArrivee = "null";
	vector<Sommet*> chemin;
	
	while (!quitter) {

		//Affichage du menu principal
		cout
			<< "################# MENU PRINCIPAL #################" << '\n' << '\n'
			<< "Choisissez une option parmi les suivantes:" << '\n' << '\n'
			<< '\t' << "(a) Demander les charactéristiques du véhicule." << '\n'
			<< '\t' << "(b) Mettre à jour la carte." << '\n'
			<< '\t' << "(c) Extraire un sous-graphe." << '\n'
			<< '\t' << "(d) Déterminer le plus court chemin." << '\n'
			<< '\t' << "(e) Quitter." << '\n' << '\n'
			<< "##################################################" << '\n' << '\n'
			<< "Votre réponse: ";

		cin 
			>> reponse;
		
		cout
			<< endl;

		if (reponse == "a") {
			aChoisie = true;
			//Affichage du menu du type de carburant
			bool valide = false;
			while (!valide)
			{
				cout
					<< "Entrez le type de carburant; les options possibles sont les suivantes:" << '\n' << '\n'
					<< '\t' << "essence" << '\n'
					<< '\t' << "electrique" << '\n'
					<< '\t' << "hybrid" << '\n' << '\n'
					<< "Votre réponse: ";
				cin
					>> typeCarburant;
				cout
					<< endl;

				if (typeCarburant == "essence" || typeCarburant == "electrique" || typeCarburant == "hybrid") {
					valide = true;
					voiture.setType(typeCarburant);
				}
				else
					cout << "Cette réponse n'est pas valide. Veuillez réesssayer." << '\n' << endl;
			}
			//Affichage du menu de l'autonomie maximale
			valide = false;
			while (!valide)
			{
				cout
					<< "Entrez l'autonomie maximale sous forme d'entier naturel: ";
				cin
					>> autoMax;
				cout
					<< endl;

				if (estUnNombre(autoMax)) {
					valide = true;
					voiture.setAutoMax(stoi(autoMax));
				}
				else 
					cout << "Cette réponse n'est pas valide. Veuillez réesssayer." << '\n' << endl;
			}
			//Affichage du menu du coefficient de perte d'autonomie
			valide = false;
			while (!valide)
			{
				cout
					<< "Entrez le coefficient de perte d'autonomie par kilomètre sous forme d'entier naturel: ";
				cin
					>> coeffPerte;
				cout
					<< endl;

				if (estUnNombre(coeffPerte)) {
					valide = true;
					voiture.setCoeffPerte(stoi(coeffPerte));
				}
				else
					cout << "Cette réponse n'est pas valide. Veuillez réesssayer." << '\n' << endl;
			}

			//Confirmation de l'opération
			cout
				<< "##################################################" << '\n' 
				<< "######## VÉHICULE CONFIGURÉ AVEC SUCCÈS ##########" << '\n'
				<< "##################################################" << '\n' << endl;
		}
		else if (reponse == "b") {
			cout 
				<< "Entrez le nom du fichier contenant la carte : ";
			cin
				>> nomCarte;
			cout
				<< endl;

			carte.creerGraphe(nomCarte);

			//Confirmation de l'opération
			cout
				<< "##################################################" << '\n'
				<< "############# GÉNÉRATION DE LA CARTE #############" << '\n'
				<< "##################################################" << '\n' << endl;

			carte.lireGraphe();

			//Confirmation de l'opération
			cout
				<< "##################################################" << '\n' << endl;

		}
		else if (reponse == "c" && aChoisie) {
			bool valide = false;
			while (!valide) {
				cout
					<< "Veuillez entrer l'ID de la station de départ: ";
				cin
					>> idPointDepart;
				cout
					<< endl;
				if (idPointDepart == "C" || idPointDepart == "V"
					|| idPointDepart == "G" || idPointDepart == "S"
					|| idPointDepart == "X" || idPointDepart == "E"
					|| idPointDepart == "P" || idPointDepart == "B"
					|| idPointDepart == "D" || idPointDepart == "J"
					|| idPointDepart == "K" || idPointDepart == "A"
					|| idPointDepart == "U") {
					valide = true;
				}
				else
					cout << "Cette réponse n'est pas valide. Veuillez réesssayer." << '\n' << endl;
			}

			chemin = carte.extractionGraphe(idPointDepart, &voiture);

			//Confirmation de l'opération
			cout
				<< "##################################################" << '\n'
				<< "############## GÉNÉRATION DU CHEMIN ##############" << '\n'
				<< "##################################################" << '\n' << endl;

			carte.lireChemin(chemin);

			//Confirmation de l'opération
			cout
				<< "##################################################" << '\n' << endl;
		}
		else if (reponse == "c" && !aChoisie) {
			cout << "Erreur : l'option (a) n'a pas été choisie avant l'option (c). Veuillez recommencer." << endl << endl;
		}
		else if (reponse == "d") {
		bool valide = false;
		while (!valide) {
			cout
				<< "Veuillez entrer l'ID de la station de départ: ";
			cin
				>> idPointDepart;
			cout
				<< endl;
			if (idPointDepart == "C" || idPointDepart == "V"
				|| idPointDepart == "G" || idPointDepart == "S"
				|| idPointDepart == "X" || idPointDepart == "E"
				|| idPointDepart == "P" || idPointDepart == "B"
				|| idPointDepart == "D" || idPointDepart == "J"
				|| idPointDepart == "K" || idPointDepart == "A"
				|| idPointDepart == "U") {
				valide = true;
			}
			else
				cout << "Cette réponse n'est pas valide. Veuillez réesssayer." << '\n' << endl;
		}
		valide = false;
		while (!valide) {
			cout
				<< "Veuillez entrer l'ID de la station d'arrivée: ";
			cin
				>> idPointArrivee;
			cout
				<< endl;
			if (idPointDepart == "C" || idPointDepart == "V"
				|| idPointDepart == "G" || idPointDepart == "S"
				|| idPointDepart == "X" || idPointDepart == "E"
				|| idPointDepart == "P" || idPointDepart == "B"
				|| idPointDepart == "D" || idPointDepart == "J"
				|| idPointDepart == "K" || idPointDepart == "A"
				|| idPointDepart == "U") {
				valide = true;
			}
			else
				cout << "Cette réponse n'est pas valide. Veuillez réesssayer." << '\n' << endl;
		}

		chemin = carte.plusCourtChemin(idPointDepart, idPointArrivee, &voiture);

		//Confirmation de l'opération
		cout
			<< "##################################################" << '\n'
			<< "############## GÉNÉRATION DU CHEMIN ##############" << '\n'
			<< "##################################################" << '\n' << endl;
		if (chemin.size() > 1) {
			carte.lireChemin(chemin);
			cout
				<< "Le chemin est de " << carte.calculerDistanceChemin(chemin) << endl
				<< "L'autonomie restante est de " << voiture.getAutoRestante() << "km" << '\n' << endl;
		}
		else
			cout << "Impossible d'atteindre la destination. Vérifier l'autonomie restante ou la destination" << '\n' << endl;

		//Confirmation de l'opération
		cout
			<< "##################################################" << '\n' << endl;
		}
		else if (reponse == "e") {
			quitter = true;

			//Confirmation de l'opération
			cout
				<< "##################################################" << '\n'
				<< "############## FERMETURE DU SYSTÈME ##############" << '\n'
				<< "##################################################" << '\n' << endl;
		}
		else {
			cout << "Entrée invalide. Veuillez recommencer." << endl << endl;
		}
	}

	//Désallocation de la mémoire
	for (auto& sommet : chemin) {
		delete sommet;
		sommet = nullptr;
	}
	chemin.clear();
}
