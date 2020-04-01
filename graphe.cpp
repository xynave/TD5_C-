#include "Graphe.h"
#include <fstream>
#include<map>
#include <algorithm>

Graphe::Graphe(std::string cheminFichierGraphe) {

    std::ifstream ifs{cheminFichierGraphe};
    if(!ifs) {
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    ifs >> m_estOriente;
    if(ifs.fail()) {
        throw std::runtime_error("Probleme de lecture de l'orientation du graphe.");
    }
    int ordre;
    ifs >> ordre;
    if(ifs.fail()) {
        throw std::runtime_error("Probleme de lecture de l'ordre du graphe.");
    }

    ifs >> taille;
    if(ifs.fail()) {
        throw std::runtime_error("Probleme de lecture de la taille du graphe.");
    }
    for(int i=0; i<ordre; ++i) {
        m_sommets.push_back(new Sommet(i));
    }
    int num1, num2 ,poids;
    for(int i=0; i<taille; ++i) {
        ifs >> num1 >> num2 >>poids;
        if(ifs.fail()) {
            throw std::runtime_error("Probleme de lecture d'un.e arc/arete.");
        }
        m_arrete[i].push_back(num1);
        m_arrete[i].push_back(num2);
        m_arrete[i].push_back(poids);
        m_sommets[num1]->addSuccesseur(m_sommets[num2]);
        if(!m_estOriente && num1 < num2) {
            m_sommets[num2]->addSuccesseur(m_sommets[num1]);
        }
    }
}

Graphe::~Graphe() {
    for(auto addrSommet : m_sommets) {
        delete addrSommet;
    }
}




void Graphe::afficher() const {
    std::map<int,std::vector<int>> arrete=m_arrete;
    std::cout << std::endl << "Graphe ";
    std::cout << (m_estOriente ? "orienté" : "non oriente") << std::endl;
    std::cout << "Ordre : " << m_sommets.size() << std::endl;
    std::cout << "Liste d'adjacences : " << std::endl;
    for(auto addrSommet : m_sommets)
        {
        addrSommet->afficher();
        std::cout << std::endl;
        }
  std::cout << std::endl;
  //on affiche les arrètes avec leur poid
 std::cout << "Liste des arretes : " << std::endl;
 for(int i=0;i<taille;i++)
     {
                std::cout << " arrete numero " <<i+1 <<" : ";
                for(int j=0;j<arrete[i].size();j++)
                {
                        if(j==1)
                        std::cout<<arrete[i][j]<<" poids-> ";

                        else
                        std::cout<<arrete[i][j]<<" ";
                }
        std::cout<<std::endl;
     }






}


void Graphe::Kruskal() const {
     std::map<int,std::vector<int>> arrete=m_arrete;
     std::map<int,std::vector<int>> trier;
     std::vector<int> compte;
     std::vector<Sommet*>Sommet= m_sommets;
     int tab [m_sommets.size()][1];
     int addition=0;
    std::vector<int>deuxtriage;
     int compteur=0;
     int success=0;
     int antesuccess;
    //on initialise le tbleau ou on va colorier les sommets
     for (int i=0;i<=m_sommets.size();i++){
        tab[i][1]=0;
     }


     //on intialise le fait que les sommet ne sont pas trier
        for(int i=0;i<taille;i++)
             {
                       arrete[i].push_back(0);
             }

             std::cout<<std::endl;

    //on envoie le poids de chaque arrète dans un vecteur
            for(int i=0;i<arrete.size();i++)
            {
               compte.push_back(arrete[i][2]);
            }
            //on trie ce poids
            std::sort (compte.begin(), compte.end());
            //on compare le poids trier et on envois dans l'ordre croissant de poid les arrètes dans un autres vecteurs
          for(int i=0;i<arrete.size();i++)
            {

                for(int j=0;j<arrete.size();j++)
                {
                    if(compte[i]==arrete[j][2] && arrete[j][3]==0)
                    {
                        arrete[j][3]=1;
                        trier[i]=arrete[j];

                        break;

                    }
                }

            }


            for(int i=0;i<arrete.size();i++)
            {
                //on colorie chaque sommet de l'arrete que l'on rajjoute et on rajoute celle qui on aucun lien avec un autre sommet celon le plus petit sommet
                       if(tab[trier[i][0]][1]==0 || tab[trier[i][1]][1]==0)
                       {
                            addition=addition+trier[i][2];
                           trier[i][3]++;
                           tab[trier[i][0]][1]++;
                            tab[trier[i][1]][1]++;
                       }
            }

//on va faire une grande boucle tant que l'on n'aura pas le nombre de sommet -1 == au nombre d'arrètes
              while(success<m_sommets.size()-1)
               {    antesuccess=success;
               //on a réalisé des chaines connexes mantenant on va les relier entre elle
//on initialise la première
                    if(success==0)
                    {
                        for(int i=0;i<taille;i++)
                    {
                          if(success==0 && trier[i][3]==2 )
                          {
                              deuxtriage.push_back(trier[i][0]);
                              deuxtriage.push_back(trier[i][1]);
                              success++;
                              trier[i][3]=3;
                              break;
                          }
                    }
                    }


               //on réalise la chaine connexe
                    for(int k=0;k<deuxtriage.size();k++)
                    {
                        for(int i=0;i<taille;i++)
                        {
                              if(trier[i][3]==2 && deuxtriage[k]==trier[i][0]  )
                              {
                                  deuxtriage.push_back(trier[i][1]);
                                  success++;
                                 trier[i][3]++;
                              }
                              else if(trier[i][3]==2 && deuxtriage[k]==trier[i][1])
                              {
                                  deuxtriage.push_back(trier[i][0]);
                                  success++;
                                   trier[i][3]++;
                              }



                        }
                        //on rajoute l'arrete pour relier les chaines connexes entre elles
                        }

                    if(antesuccess==success)
                        {
                            for(int k=0;k<deuxtriage.size();k++)
                    {
                        for(int i=0;i<taille;i++)
                        {
                            //on  vérifie que l'on forme pas de cycle
                            for(int l=0;l<deuxtriage.size();l++){
                                 if(trier[i][3]==1 && deuxtriage[k]==trier[i][0]  )
                              {
                               compteur=1;
                              }
                               if(trier[i][3]==1 && deuxtriage[k]==trier[i][1])
                              {
                                  compteur=2;
                              }
                              if(trier[i][3]==1 && deuxtriage[k]==trier[i][0] && deuxtriage[l]==trier[i][1] )
                              {
                               compteur=0;
                              }
                              if(trier[i][3]==1 && deuxtriage[k]==trier[i][1] && deuxtriage[l]==trier[i][0])
                              {
                                  compteur=0;
                              }

                            }

//on valide l'arrète
                    if(compteur==1)
                    {
                        deuxtriage.push_back(trier[i][1]);
                        addition=addition+trier[i][2];
                              success++;
                              trier[i][3]=3;
                              break;
                    }
                    else if (compteur==2)
                    {
                         deuxtriage.push_back(trier[i][0]);
                         addition=addition+trier[i][2];
                              success++;
                              trier[i][3]=3;
                              break;
                    }

                        }
                        if(antesuccess!=success)
                        {
                            break;
                            compteur=0;

                        }
                        }

                compteur=0;

               }
               }


        std::cout<<"La nouvelle liste trie: "<<std::endl;

 //on affiche les arrètes avec leur poid et trié
    for(int i=0;i<taille;i++)
     {
                std::cout << " arrete numero " <<i+1 <<" : ";
                for(int j=0;j<trier[i].size()-1;j++)
                {

                        if(j==1)
                        std::cout<<trier[i][j]<<" poids-> ";

                        else
                        std::cout<<trier[i][j]<<" ";
                }
        std::cout<<std::endl;
     }

      std::cout<<std::endl;
      //on affiche les arrètes et le poid de Kruskal
      std::cout<<"les arretes du algorithme de Kruskal: ";
      for(int i=0;i<taille;i++)
     {
         if(trier[i][3]!=1 && i!=0){
             std::cout << " / ";
         }

                for(int j=0;j<trier[i].size();j++)
                {
                    if(trier[i][3]!=1)
                    {
                        if(j==0 || j==1)
                        {
                          std::cout<<trier[i][j]<<" ";
                        }
                    }

                }

     }
      std::cout<<std::endl<<"le poids total est : "<<addition;


}
