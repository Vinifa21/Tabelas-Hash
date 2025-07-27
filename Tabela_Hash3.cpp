//Utiliza Double Hashing (sondagem não linear) para tratar colisõe
//É uma tabela_hash dinamica!, ao atingir 70% de sua capacidade, seu tamanho é dobrado e é feito o rehashing


#include <cmath>

int acha_primo(int n) {
    // retorna o maior número primo que é menor do que n
    for(int numero = (n - 1); numero> 1; numero--) { // testa todos os números menores do que n
        bool sentinela =false; // nenhum divisor encontrado

        int i= 2;
        while(sentinela == false && i <= sqrt(numero)){
            if(numero % i == 0) {
                sentinela = true; // encontrei um divisor, sai do while e altero sentinela
            }
            i++;
        }
        if(sentinela == false) { // se não tem divisor, é primo
            return numero;
        }

    }
}



class Tabela_Hash3 {
public:
    int* vetor;
    int capacidade; // guarda o tamanho atual do vetor
    int n_colisoes = 0;
    int n_keys = 0; // numero de chaves inseridas
    int indice_hash2; // começa com tamanho, muda se eu fizer um rehash

    Tabela_Hash3(){
        this->capacidade = 17; // tamanho inicial da tabela
        this->vetor = new int[capacidade];
        this->indice_hash2 = acha_primo(capacidade);
        for(int i = 0; i < this->capacidade; i++){
            vetor[i] = -1;
        }
    }

    ~Tabela_Hash3() {
        delete[] vetor; // Libera a memória quando o objeto deixa de existir
    }

    void print() {
        cout << "~~~~~~TABELA HASH~~~~~~" << endl;
        for (int i = 0; i < capacidade; i++) {
            if (vetor[i] == -1) {
                cout << i << ":  "<< "~~" << endl;
            }
            else{
                cout << i << ":  " <<  vetor[i] << endl;
            }
        }
        cout << "~~~~~~~~~~~~~~" << endl;

    };

    // retorna o valor do indice que a key será inserida
    int hash(int key, int t) {
        int index = (hash1(key) + t * hash2(key)) % capacidade;
        return (index < 0) ? index + capacidade : index;
    }

    int hash1(int key) {
        return key % capacidade;
    };

    int hash2(int key) { // calcula o tamanho do passo em caso de colisão
        return  (1 + (key % this->indice_hash2)); // 1 é importante, para o passo ser =! de 0
    };

    bool add(int key) {
        verifica_ocupacao();

        int indice = hash(key, 0);
        if (vetor[indice] == -1) {
            vetor[indice] = key;
            n_keys++;
            return true; // deu tudo certo de primeira!
        }
        else { // (deu colisão!) sondagem por double hashing
            for (int i = 1; i < capacidade; i++) {
                indice = hash(key, i); // recalculo o indice
                if (vetor[(indice) % capacidade] == -1) {
                    vetor[(indice) % capacidade] = key;
                    n_keys++; n_colisoes++;
                    return true;
                }
            }
        }
        return false;
    };

    int* search(int key) {
        int indice = hash(key, 0);

        if (vetor[indice] == key) { // de primeira
            return &vetor[indice]; // retorna o endereço da chave
        }
        else {
            for (int i = 1; i < capacidade; i++) { //
                indice = hash(key, i); // recalculo o indice
                if (vetor[(indice) % capacidade] == key) {
                    return &vetor[(indice) % capacidade];
                }
            }
            return nullptr;
        }
    }

    bool verifica_ocupacao() {
        // retorna true se mais de 70% dos slots estão ocupados
        if (this->n_keys > capacidade * 0.7){
            redimensiona_hash();
            cout << "Redimensionando a tabela hash!!" << endl;
            return true;
        }
        return false;
    }

    void redimensiona_hash() {
        // salvo dados antigos
        int old_capacidade = this->capacidade;
        int* old_vetor = this->vetor;

        // atualizo dados novos
        this->capacidade = old_capacidade* 2;
        this->indice_hash2 = acha_primo(capacidade);
        this->vetor = new int[capacidade]; // declaro novo vetor!

        //RECRIANDO A TABELA
        this->n_keys = 0;
        this->n_colisoes = 0;

        for(int i = 0; i < this->capacidade; i++) {
            this->vetor[i] = -1;
        }

        for (int i = 0; i < old_capacidade; i++) {
            if(old_vetor[i] != -1) {
                add(old_vetor[i]); // readiciono os elementos antigos

            }
        }
        delete[] old_vetor;
    }

};