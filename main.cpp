// Trabalho INF101 - Etapa 1
// Sistema de Registro e Gestao de Contas Bancarias
// Obs: o enunciado pede variaveis individuais, mas para resolver o
// desafio das 5 contas usei vetores (um para cada variavel obrigatoria).

#include <iostream>
#include <string>
using namespace std;

const int MAX_CONTAS = 5;

// procura uma conta pelo numero; retorna a posicao ou -1 se nao achar
int buscarConta(int numeros[], int total, int numero) {
    for (int i = 0; i < total; i++) {
        if (numeros[i] == numero) {
            return i;
        }
    }
    return -1;
}

int main() {
    // variaveis obrigatorias (agora em vetores, 1 posicao por conta)
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    int totalContas = 0; // quantas contas ja foram cadastradas
    int opcao;

    do {
        cout << "\n********************************\n";
        cout << "**         BANCO INF101       **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar/Desativar conta\n";
        cout << "6 - Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        // se digitou letra no lugar de numero
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcao = 0;
        }

        switch (opcao) {

        case 1: { // ---------- CADASTRO ----------
            if (totalContas >= MAX_CONTAS) {
                cout << "Limite de " << MAX_CONTAS << " contas atingido!\n";
                break;
            }

            int numero, tipo;
            double saldoInicial;
            string nome, cpfDigitado;

            cout << "Numero da conta: ";
            cin >> numero;
            if (cin.fail() || numero <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Numero invalido! Deve ser maior que zero.\n";
                break;
            }
            // nao deixa repetir numero de conta
            if (buscarConta(numeroConta, totalContas, numero) != -1) {
                cout << "Ja existe uma conta com esse numero!\n";
                break;
            }

            cin.ignore(1000, '\n'); // limpa o enter que sobrou
            cout << "Nome do titular: ";
            getline(cin, nome);
            if (nome.empty()) {
                cout << "O nome nao pode ficar vazio!\n";
                break;
            }

            cout << "CPF (somente numeros): ";
            getline(cin, cpfDigitado);
            bool cpfOk = (cpfDigitado.size() == 11);
            for (int i = 0; i < (int)cpfDigitado.size(); i++) {
                if (cpfDigitado[i] < '0' || cpfDigitado[i] > '9') {
                    cpfOk = false;
                }
            }
            if (!cpfOk) {
                cout << "CPF invalido! Digite 11 numeros.\n";
                break;
            }

            cout << "Tipo da conta (1 = Corrente, 2 = Poupanca): ";
            cin >> tipo;
            if (cin.fail() || (tipo != 1 && tipo != 2)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Tipo invalido! Use 1 ou 2.\n";
                break;
            }

            cout << "Saldo inicial: ";
            cin >> saldoInicial;
            if (cin.fail() || saldoInicial < 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Saldo invalido! Nao pode ser negativo.\n";
                break;
            }

            // tudo certo, guarda na proxima posicao livre
            numeroConta[totalContas] = numero;
            nomeCliente[totalContas] = nome;
            cpf[totalContas] = cpfDigitado;
            tipoConta[totalContas] = tipo;
            saldo[totalContas] = saldoInicial;
            contaAtiva[totalContas] = true; // conta nova ja nasce ativa
            totalContas++;

            cout << "Conta cadastrada com sucesso!\n";
            break;
        }

        case 2: { // ---------- CONSULTAR ----------
            if (totalContas == 0) {
                cout << "Nenhuma conta cadastrada.\n";
                break;
            }
            int numero;
            cout << "Numero da conta: ";
            cin >> numero;
            int pos = buscarConta(numeroConta, totalContas, numero);
            if (pos == -1) {
                cout << "Conta nao encontrada!\n";
                break;
            }
            cout << "\n--- Dados da conta ---\n";
            cout << "Numero: " << numeroConta[pos] << endl;
            cout << "Titular: " << nomeCliente[pos] << endl;
            cout << "CPF: " << cpf[pos] << endl;
            cout << "Tipo: " << (tipoConta[pos] == 1 ? "Corrente" : "Poupanca") << endl;
            cout << "Saldo: R$ " << saldo[pos] << endl;
            cout << "Situacao: " << (contaAtiva[pos] ? "Ativa" : "Inativa") << endl;
            break;
        }

        case 3: { // ---------- VERIFICAR SALDO ----------
            if (totalContas == 0) {
                cout << "Nenhuma conta cadastrada.\n";
                break;
            }
            int numero;
            cout << "Numero da conta: ";
            cin >> numero;
            int pos = buscarConta(numeroConta, totalContas, numero);
            if (pos == -1) {
                cout << "Conta nao encontrada!\n";
            } else if (!contaAtiva[pos]) {
                cout << "Conta inativa! Ative a conta para ver o saldo.\n";
            } else {
                cout << "Saldo atual: R$ " << saldo[pos] << endl;
            }
            break;
        }

        case 4: { // ---------- ALTERAR TIPO ----------
            if (totalContas == 0) {
                cout << "Nenhuma conta cadastrada.\n";
                break;
            }
            int numero, novoTipo;
            cout << "Numero da conta: ";
            cin >> numero;
            int pos = buscarConta(numeroConta, totalContas, numero);
            if (pos == -1) {
                cout << "Conta nao encontrada!\n";
                break;
            }
            if (!contaAtiva[pos]) {
                cout << "Conta inativa! Nao e possivel alterar o tipo.\n";
                break;
            }
            cout << "Novo tipo (1 = Corrente, 2 = Poupanca): ";
            cin >> novoTipo;
            if (cin.fail() || (novoTipo != 1 && novoTipo != 2)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Tipo invalido! Use 1 ou 2.\n";
                break;
            }
            tipoConta[pos] = novoTipo;
            cout << "Tipo alterado com sucesso!\n";
            break;
        }

        case 5: { // ---------- ATIVAR / DESATIVAR ----------
            if (totalContas == 0) {
                cout << "Nenhuma conta cadastrada.\n";
                break;
            }
            int numero;
            cout << "Numero da conta: ";
            cin >> numero;
            int pos = buscarConta(numeroConta, totalContas, numero);
            if (pos == -1) {
                cout << "Conta nao encontrada!\n";
                break;
            }
            contaAtiva[pos] = !contaAtiva[pos]; // inverte o estado
            cout << "Conta agora esta " << (contaAtiva[pos] ? "ATIVA" : "INATIVA") << ".\n";
            break;
        }

        case 6:
            cout << "Encerrando o sistema. Ate logo!\n";
            break;

        default:
            cout << "Opcao invalida! Tente novamente.\n";
        }

    } while (opcao != 6);

    return 0;
}
