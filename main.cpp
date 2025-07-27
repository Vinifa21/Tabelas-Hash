#include <iostream>
#include <vector>
using namespace std;
#include "Tabela_Hash3.cpp"

void preenche1(Tabela_Hash3 *T) {
    T->add(25);
    T->add(47);
    T->add(98);
    T->add(13);
    T->add(52);
    T->add(75);
    T->add(67);
    T->add(32);
    T->add(81);
    T->add(11);
    T->add(89);
    T->add(55);
    T->add(29);
    T->add(39);
    T->add(42);
}


void preenche2(Tabela_Hash3 *T) {
    T->add(12);
    T->add(23);
    T->add(66);
    T->add(91);
    T->add(44);
    T->add(56);
    T->add(78);
    T->add(99);
}

int main() {


    Tabela_Hash3 T;
    preenche1(&T);

    T.print();
    cout << "A tabela teve " << T.n_colisoes << " colisoes\n" << endl;


    cout << "Preenchendo ainda mais!!" << endl;

    preenche2(&T);

    T.print();
    cout << "A tabela teve " << T.n_colisoes << " colisoes" << endl;

    return 0;
}
