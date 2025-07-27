//Utiliza Double Hashing (sondagem não linear) para tratar colisões
// o tamanho do passo para achar a chave é determinado por uma segunda função hash
// ou seja, tamanho do passo é único de acordo com cada key e tentativa (t),
#define tamanho 17 // servirá tb para a função hash

class Tabela_Hash2 {
public:
    int vetor[tamanho];
    int n_colisoes = 0;
    int n_keys = 0; // numero de chaves inseridas
    Tabela_Hash2(){
        for (int i = 0; i < tamanho; i++) {
            vetor[i] = NULL;
        }
    };
    void print() {
        cout << "~~~~~~TABELA HASH~~~~~~" << endl;
        for (int i = 0; i < tamanho; i++) {
            if (vetor[i] == NULL) {
                cout << i << ":  "<< "~~" << endl;
            }
            else{
                cout << i << ":  " <<  vetor[i] << endl;
            }
        }
        cout << "~~~~~~~~~~~~~~" << endl;

    };

    // retorna o valor do indice que a key será inserida
    int hash(int key, int t) {// t = n° da tentativa
        return (hash1(key) + (t *  hash2(key))) % tamanho;
    }

    int hash1(int key) {
        return key % tamanho;
    };

    int hash2(int key) { // calcula o tamanho do passo em caso de colisão
        return  (1 + (key % 13)); // 1 é importante, para o passo ser =! de 0
    };

    bool add(int key) {
        if (this->n_keys == tamanho) {
            return false; // se deu overflow, retorno false
        }

        int indice = hash(key, 0);
        if (vetor[indice] == NULL) {
            vetor[indice] = key;
            n_keys++;
            return true; // deu tudo certo de primeira!
        }
        else { // (deu colisão!) sondagem por double hashing
            for (int i = 1; i < tamanho; i++) {
                indice = hash(key, i); // recalculo o indice
                if (vetor[(indice) % tamanho] == NULL) {
                    vetor[(indice) % tamanho] = key;
                    n_keys++; n_colisoes++;
                    return true;
                }
            }
        }
    };

    int* search(int key) {
        int indice = hash(key, 0);

        if (vetor[indice] == key) { // de primeira
            return &vetor[indice]; // retorna o endereço da chave
        }
        else {
            for (int i = 1; i < tamanho; i++) { //
                indice = hash(key, i); // recalculo o indice
                if (vetor[(indice) % tamanho] == key) {
                    return &vetor[(indice) % tamanho];
                }
            }
            return nullptr;
        }
    }


};