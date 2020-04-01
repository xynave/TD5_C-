#ifndef GRAPHE_H
#define TGRAPHE_H

#include <iostream>
#include <vector>
#include <string>
#include "Sommet.h"
#include <map>

class Graphe {
private:
    bool m_estOriente;
    std::vector<Sommet*> m_sommets;
    std::map<int,std::vector<int>> m_arrete;
    int taille;
public:
    Graphe(std::string cheminFichierGraphe);
    ~Graphe();
    void afficher() const;
    void Kruskal()const;


};


#endif
