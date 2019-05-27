      FACILITATI DE COMPILARE SEPARATA IN CADRUL LIMBAJELOR DE PROGRAMARE DE NIVEL INALT
      
posibilitatea oferita de un limbaj de programare sa ofere mecanisme \
ca module diferite ca fisiere separate sa poata fi compilate la momente diferite de timp urmand ca linkeditarea sa aiba loc
la un moment ulterior
pt a fi posibila e nevoie ca limbajul sa puna la dispozitie mecanisme de import export

analiza facilitatilor make si build
care ar fi criteriile utile/necesare de impartire in module(ex. dupa frecventa modificarilor acelui modul)


- Care este motivatia si justificarea introducerii unei astfel de facilitati ?
(de ex. TP justifica aceasta si prin legatura cu definirea de TAD-uri). Alte justificari in alte limbaje ?

 - incapsularea datelor
 - separarea interfetei de implementare(ofera posibilitatea de a schimba implementarea si a pastra interfata, deci abstractizare)
 - posibilitatea de a lucra separat la acelasi program (stiind interfata) urmand ca apoi sa fie legate fisierele obiect
 - avantajul da a recompila doar bucati de cod(nu tot de fiecare data)
 - posibilitatea de a grupa functionalitatile asemanatoare
 - ajuta sa nu fie cod duplicat(abstractizare din nou)

- Rolul programarii bazate obiect si a OOP in promovarea acestor facilitati 
(accent pe incapsulare - data driven computations, in care datele controleaza accesul la cod);

 Programarea bazata obiect (si OOP) se poate folosi foarte bine de compilarea separata deoarece aceasta se bazeaza in principal pe incapsulare
 si pe faptul ca o clasa e o unitate de sine statatoare, care probabil ar trebui sa poata fi compilata separat.

- Legarea de module dezvoltate in limbaje de programare diferite (probleme de compatibilitate ?)

Pentru exemple:

i).  Sa se elaboreze un program C(++) format din minimum 3 module compilate separat pentru 
     rezolvarea unei probleme adecvate punerii in valoare a utilitatii unei astfel de facilitati. 
     
     --> modul cu date(si mai ales tipuri de date), modul cu functii(incerc ceva functional) si modulul program care face restul
     
ii). Sa se elaboreze o varianta echivalenta in MINIM 2 alte limbaje de programare diferite, 
     folosind capacitatea de compilare separata a acelor limbaje. Se cere o scurta analiza 
     a acestor mecanisme (prezentarea modului de functionare si exemplificarea mecanismului de export-import).
