#include <string>
#include <unistd.h>
#include <vector>
#include <map>
#include <stack>
#include <sys/stat.h>
#include <fcntl.h>

extern "C" {
    #include "cpersoana.h"
}

#include "agenda.hpp"

Persoana::Persoana (size_t id, string nume, string nr_telefon, string email) {
    this->id = id;
    this->nume = nume;
    this->nr_telefon = nr_telefon;
    this->email = email;
}

Persoana::Persoana (p_persoana_t p) {
    this->id = p->id;
    this->nume = p->nume;
    this->nr_telefon = p->nr_telefon;
    this->email = p->email;
}

// agenda


void Agenda::adauga(Persoana p) {
    if (_cross_reference.find(p.id) != _cross_reference.end()) {
        throw "mai exista persoana cu acest id";
    }

    if (!_locuri_libere.empty()) {
        size_t loc_liber = _locuri_libere.top();
        _locuri_libere.pop();
        _persoane[loc_liber] = p;
        _cross_reference[p.id] = loc_liber;
    } else {
        _persoane.push_back(p);
        _cross_reference[p.id] = _persoane.size() - 1;
    }

    append_to_file(p);
}
void Agenda::sterge(size_t id) {
    if (_cross_reference.find(id) == _cross_reference.end()) {
        throw "nu extsta aceasta persoana";
    }

    _locuri_libere.push(_cross_reference[id]);
    _cross_reference.erase(id);    

    rewrite_file();
}
void Agenda::modifica(size_t id, string nume = "", string nr_telefon = "", string email = "") {
    if (_cross_reference.find(id) == _cross_reference.end()) {
        throw "nu extsta aceasta persoana";
    }

    auto persoana = _persoane[_cross_reference[id]];
    if (nume.size() > 0) persoana.nume = nume;
    if (nr_telefon.size() > 0) persoana.nr_telefon = nr_telefon;
    if (email.size() > 0) persoana.email = email;

    rewrite_file();
}
vector<Persoana> Agenda::filtreaza(ssize_t id = -1, string nume = "", string nr_telefon = "", string email = "") {
    vector<Persoana> persoane;
    if (id != -1) {
        if (_cross_reference.find(id) == _cross_reference.end()) return persoane;
        persoane.push_back(_persoane[_cross_reference[id]]);
        return persoane;
    }

    for (auto p : _persoane) {
        if (p.nume.find(nume) != string::npos &&
            p.nr_telefon.find(nr_telefon) != string::npos &&
            p.email.find(email) != string::npos)
            persoane.push_back(p);
    }
    return persoane;
}

void Agenda::append_to_file(Persoana p) {
    int fd = open(path_date, O_WRONLY | O_APPEND);
    if (!fd)
        throw "Some file error";

    auto _p = new_persoana(p.id, p.nume.c_str(), p.nr_telefon.c_str(), p.email.c_str());
    write_persoana(fd, _p);
    delete_persoana(_p);

    close(fd);
}
void Agenda::rewrite_file() {
    int fd = open(path_date, O_WRONLY | O_TRUNC);
    if (!fd)
        throw "Some file error";

    for(auto p : _persoane) {
        auto _p = new_persoana(p.id, p.nume.c_str(), p.nr_telefon.c_str(), p.email.c_str());
        write_persoana(fd, _p);
        delete_persoana(_p);
    }

    close(fd);
}
