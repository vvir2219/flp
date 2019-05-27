#include <iostream>
#include <vector>
#include <map>
#include <stack>

#include "agenda.hpp"

using namespace std;

void test_agenda()
{
    Agenda agenda;
    agenda.adauga(Persoana(1, "Ana", "4620429294", "ana@ana.ana"));
    agenda.adauga(Persoana(2, "Ana", "4620429294", "ana@ana.ana"));
    agenda.adauga(Persoana(3, "Ana", "4620429294", "ana@ana.ana"));
    agenda.sterge(2);
    agenda.adauga(Persoana(4, "Ana", "4620429294", "ana@ana.ana"));
    agenda.adauga(Persoana(5, "Ana", "4620429294", "ana@ana.ana"));
    
    for(auto p : agenda.filtreaza()) {
        cout << "Id: " << p.id << "\n"
             << "Nume: " << p.nume << "\n"
             << "Nr telefon: " << p.nr_telefon << "\n"
             << "Email: " << p.email << "\n"
    }
}

int main(int argc, char *argv[])
{
    test_agenda();   
    return 0;
}
