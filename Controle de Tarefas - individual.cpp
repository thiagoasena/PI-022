#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

class Tarefa {
public:
    Tarefa(const string& descricao) : descricao(descricao), concluida(false) {}

    void marcarConcluida() {
        concluida = true;
    }

    bool estaConcluida() const {
        return concluida;
    }

    const string& getDescricao() const {
        return descricao;
    }

private:
    string descricao;
    bool concluida;
};

class GerenciadorTarefas {
public:
    void adicionarTarefa(const string& descricao) {
        Tarefa tarefa(descricao);
        tarefas.push_back(tarefa);
    }

    void listarTarefasPendentes() {
        bool temTarefasPendentes = false;
        for (size_t i = 0; i < tarefas.size(); ++i) {
            if (!tarefas[i].estaConcluida()) {
                cout << i << ". " << tarefas[i].getDescricao() << endl;
                temTarefasPendentes = true;
            }
        }

        if (!temTarefasPendentes) {
            cout << "Não há tarefas pendentes." << endl;
        }
    }

    void marcarTarefaConcluida(int indice) {
        if (indice >= 0 && static_cast<size_t>(indice) < tarefas.size()) {
            tarefas[indice].marcarConcluida();
            cout << "Tarefa marcada como concluída. ";
        } else {
            cout << "Índice de tarefa inválido." << endl;
        }
    }

    void salvarTarefasNoArquivo(const string& nomeArquivo) {
        ofstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            for (const Tarefa& tarefa : tarefas) {
                arquivo << tarefa.getDescricao() << " " << tarefa.estaConcluida() << endl;
            }
            arquivo.close();
        } else {
            cout << "Erro ao abrir o arquivo para salvar as tarefas." << endl;
        }
    }

    void carregarTarefasDoArquivo(const string& nomeArquivo) {
        ifstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            string descricao;
            bool concluida;
            while (arquivo >> descricao >> concluida) {
                Tarefa tarefa(descricao);
                if (concluida) {
                    tarefa.marcarConcluida();
                }
                tarefas.push_back(tarefa);
            }
            arquivo.close();
        }
    }

private:
    vector<Tarefa> tarefas;
};

int main() {
    GerenciadorTarefas gerenciador;

    // Verifica se o arquivo "tarefas.txt" existe antes de carregar as tarefas
    ifstream arquivoExistencia("tarefas.txt");
    if (arquivoExistencia) {
        gerenciador.carregarTarefasDoArquivo("tarefas.txt");
    }

    int escolha;
    do {
        cout << "\nEscolha uma opção:" << endl;
        cout << "1. Adicionar nova tarefa" << endl;
        cout << "2. Marcar tarefa como concluída" << endl;
        cout << "3. Listar tarefas pendentes" << endl;
        cout << "4. Salvar tarefas" << endl;
        cout << "5. Sair" << endl;

        cin >> escolha;

        switch (escolha) {
            case 1: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar o buffer
                cout << "Digite a descrição da nova tarefa: ";
                string descricao;
                getline(cin, descricao);
                gerenciador.adicionarTarefa(descricao);
                cout << "Tarefa adicionada com sucesso. ";
                break;
            }
            case 2: {
                cout << "Digite o índice da tarefa a ser marcada como concluída: ";
                int indice;
                cin >> indice;
                gerenciador.marcarTarefaConcluida(indice);
                break;
            }
            case 3:
                cout << "Tarefas pendentes:" << endl;
                gerenciador.listarTarefasPendentes();
                break;
            case 4:
                gerenciador.salvarTarefasNoArquivo("tarefas.txt");
                cout << "Tarefas salvas no arquivo." << endl;
                break;
            case 5:
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while (escolha != 5);

    return 0;
}
