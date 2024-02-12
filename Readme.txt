                                
		Minesweeper

   Detalii joc:
-programul incepe cu un meniu unde se poate selecta optiunea dorita prin apasarea tastei corespunzatoare:
	1. Easy - 9x9 casute si 9 mine
	2. Normal - 9x18 casute si 18 mine
	3. Hard - 9x26 casute si 27 mine
	4. Custom - dimensiunea scenei si numarul de mine este la alegerea jucatorului
	5. Leaderboard - afiseaza top 3 jucatori pentru fiecare mod de joc (Easy, Normal, Hard) in functie de scor si timp
	6. How to play - afiseaza instructiunile
	0. Exit - opreste programul
-dupa fiecare runda arata scena cu minele si flagurile puse corect sau gresit (casuta verde pentru cele puse corect si rosie pentru cele puse gresit )
-scena este colorata in gri si am folosit pentru numere urmatoarele culori:
	1 - albastru
	2 - verde
	3 - rosu
	4 - violet
	5 - portocaliu
	6 - turcoaz
	7 - negru
	8 - gri inchis


   Instructiuni:
-pentru a selecta o casuta este necesar sa tastezi coloana si linia aferenta apoi apasa tasta ENTER
-pentru a pune sau lua un FLAG este necesar sa pui caracterul 'F' inaintea coordonatelor
-pentru a castiga trebuie sa pui FLAG pe toate minele, dar numarul de FLAG uri nu treebuie sa depaseasca numarul de mine
-numarul din casute afiseaza cate mine se afla in jurul acesteia
-pentru a fi in clasament este necesar sa faci cel putin un punct


  Mod implementare:
-am folosit doua scene, cea principala in care sunt casutele ascunse, si una secundara in care se genereaza minele si numerele din casuta
-am folosit functia gotoXY pentru a afisa casutele si textul, jocul fiind cursiv
-am folosit numeroase functii pentru a face programul eficient si pentru a da un aspect placut meniului


   Probleme intampinate:
-o problema mare a fost aceea a afisarii spatiului liber, am cautat o solutie timp de cateva zile, iar in final am folosit o coada in care am introdus pe rand coordonatele si le am verificat 
-o alta problema am intalnit-o la conditia generarii unei noi scene in cazul in care pe prima pozitie se afla mina: in cazul in care se punea FLAG pe cel putin o mina iar apoi se selecta o casuta cu mina si se genera o noua scena apareau probleme la numarul de mine ramase si numarul de mine setate , am rezolvat problema prin implementarea unei conditii la generarea minelor din noua scena
-o problema minora a fost cu colorarea casutelor si a textului, am experimentat folosirea culorilor intr-o noua sursa
-o alta problema a fost ordonarea clasamentului, am rezolvat facand matricea cu o dimensiune in plus, astfel 
-a fost dificil sa lucrez cu scena pe coloane deoarece valorile se afla din doua in doua casute si erau necesare cateva calcule mai complicate


