AVRAM Marius 334CB 

Tema 2 - Cubul Rubik 

Am realizat un cub rubic de dimensiune 3x3 precum a fost cerut in enuntul temei.
Ca schelet de cod am folosit laboratorul 3, cel in care se foloseste doar GLUT
si nu se mai foloseste frameworkul in care trebuie date topologii de vertecsi.

Cuburile sunt desenate dintr-o structura mai complexa, fiecare fata continand 
un contur si patratul cu culoare. Am reusit astfel sa adaug un plus de realism
jocului. Conturul patratelor este in mod normal negru. In cazul in care se 
selecteaza un anumit layer(sau strat) conturul isi schimba culoarea pentru 
patratele care fac parte din layerul respectiv. In acest mod mutarea fetelor 
este mult mai facila, iar utilizatorul aplicatiei stie dinainte ce va muta. 

De fiecare data cand apasa o tasta o fata se roteste cu +90 sau cu -90 de grade, 
iar culorile fetelor cuburilor mici care fac parte din fata cubului mare 
isi schimba culoarea conform mutarii.

Ca bonus am realizat rezolvarea automata a cubului rubik la o apasare a unei taste
si afisarea de text pentru scor (care consta in numarul de mutarii facute de jucator.
Mutarile nu se contorizeaza de la inceput ci numai dupa ce s-a apasat tasta de 
incepere a jocului(ENTER).

De asemenea camera este sferica(se invarte in jurul cubului).

Controalele sunt urmatoarele: 

SPATIU - selectarea urmatoarei fete pentru care se poate efectua o mutare
	selectarea are loc in ordinea: SUS, JOS, STANGA, DREAPTA, FATA, SPATE
<- rotire in sens invers trigonometric a fetei selectate
-> rotire in sens trigonometric a fetei selectate
ENTER - inceperea propriu-zisa a jocului. Se contorizeaza scorul.
's'   - rezolvarea automata a cubului.
'+' - zoom in
'-' - zoom out
CLICK STANGA MOUSE + DRAG - mutarea camerei 
 