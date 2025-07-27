//Tabela Hash de enderessamento Aberto (sem listas encadeadas) e
// colisões baseadas em sondagem linear(caso haja colisão, chave é inserida no slot posterior)
#define tamanho 17 // servirá tb para a função hash

class Tabela_Hash1 {
public:
    int vetor[tamanho];
    int n_colisoes = 0;
    int n_keys = 0; // numero de chaves inseridas
    Tabela_Hash1(){
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
    int hash(int key) {
        return key % tamanho;
    };

    bool add(int key) {
        if (this->n_keys == tamanho) {
            return false; // se deu overflow, retorno false
        }

        int indice = hash(key);
        if (vetor[indice] == NULL) {
            vetor[indice] = key;
            n_keys++;
            return true; // deu tudo certo de primeira!
        }
        else { // (deu colisão!) sondagem linear: tento colocar nos próximos slots
            for (int i = 1; i < tamanho; i++) {
                if (vetor[(indice + i) % tamanho] == NULL) {
                    vetor[(indice + i) % tamanho] = key;
                    n_keys++; n_colisoes++;
                    return true;
                }
            }
        }
    };

    int* search(int key) {
        int indice = hash(key);

        if (vetor[indice] == key) { // de primeira
            return &vetor[indice]; // retorna o endereço da chave
        }
        else {
            for (int i = 1; i < tamanho; i++) { // avanço linearmente
                if (vetor[(indice + i) % tamanho] == key) {
                    return &vetor[(indice + i) % tamanho];
                }
            }
            return nullptr;
        }
    }


};