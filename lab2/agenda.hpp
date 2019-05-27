using std::string;
using std::vector;
using std::map;
using std::stack;

class Persoana
{
public:
    Persoana (size_t id, string nume, string nr_telefon, string email);
    Persoana (p_persoana_t p);

    size_t id;
    string nume;
    string nr_telefon;
    string email;
};

class Agenda
{
public:
    void adauga(Persoana p);
    void sterge(size_t id);
    void modifica(size_t id, string nume, string nr_telefon, string email);
    vector<Persoana> filtreaza(ssize_t id, string nume, string nr_telefon, string email);

private:
    
    vector<Persoana> _persoane;
    map<size_t, size_t> _cross_reference; 
    stack<size_t> _locuri_libere;

    const char *path_date = "./persoane.txt";

    void append_to_file(Persoana p);
    void rewrite_file();
};
