#include <iostream>
#include <fstream>
#include <vector>

class Tarefa {
public:
    Tarefa(const std::string& descricao) : descricao(descricao), concluida(false) {}

    void marcarConcluida() {
        concluida = true;
    }

    bool estaConcluida() const {
        return concluida;
    }

    const std::string& getDescricao() const {
        return descricao;
    }

private:
    std::string descricao;
    bool concluida;
};

class GerenciadorTarefas {
public:
    void adicionarTarefa(const std::string& descricao) {
        Tarefa tarefa(descricao);
        tarefas.push_back(tarefa);
    }

    void listarTarefasPendentes() {
        for (const Tarefa& tarefa : tarefas) {
            if (!tarefa.estaConcluida()) {
                std::cout << tarefa.getDescricao() << std::endl;
            }
        }
    }

    void marcarTarefaConcluida(int indice) {
        if (indice >= 0 && indice < tarefas.size()) {
            tarefas[indice].marcarConcluida();
        }
    }

    void salvarTarefasNoArquivo(const std::string& nomeArquivo) {
        std::ofstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            for (const Tarefa& tarefa : tarefas) {
                arquivo << tarefa.getDescricao() << " " << tarefa.estaConcluida() << std::endl;
            }
            arquivo.close();
        } else {
            std::cerr << "Erro ao abrir o arquivo para salvar as tarefas." << std::endl;
        }
    }

    void carregarTarefasDoArquivo(const std::string& nomeArquivo) {
        std::ifstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            std::string descricao;
            bool concluida;
            while (arquivo >> descricao >> concluida) {
                Tarefa tarefa(descricao);
                if (concluida) {
                    tarefa.marcarConcluida();
                }
                tarefas.push_back(tarefa);
            }
            arquivo.close();
        } else {
            std::cerr << "Erro ao abrir o arquivo para carregar as tarefas." << std::endl;
        }
    }

private:
    std::vector<Tarefa> tarefas;
};

int main() {
    GerenciadorTarefas gerenciador;
    gerenciador.carregarTarefasDoArquivo("tarefas.txt");

    int escolha;
    do {
        std::cout << "Escolha uma opção:" << std::endl;
        std::cout << "1. Adicionar nova tarefa" << std::endl;
        std::cout << "2. Marcar tarefa como concluída" << std::endl;
        std::cout << "3. Listar tarefas pendentes" << std::endl;
        std::cout << "4. Salvar tarefas" << std::endl;
        std::cout << "5. Sair" << std::endl;

        std::cin >> escolha;

        switch (escolha) {
            case 1: {
                std::cin.ignore();
                std::cout << "Digite a descrição da nova tarefa: ";
                std::string descricao;
                std::getline(std::cin, descricao);
                gerenciador.adicionarTarefa(descricao);
                std::cout << "Tarefa adicionada com sucesso. ";
                break;
            }
            case 2: {
                std::cout << "Digite o índice da tarefa a ser marcada como concluída: ";
                int indice;
                std::cin >> indice;
                gerenciador.marcarTarefaConcluida(indice);
                std::cout << "Concluida com sucesso. ";
                break;
            }
            case 3:
                std::cout << "Tarefas pendentes:" << std::endl;
                gerenciador.listarTarefasPendentes();
                break;
            case 4:
                gerenciador.salvarTarefasNoArquivo("tarefas.txt");
                std::cout << "Tarefas salvas no arquivo." << std::endl;
                break;
            case 5:
                break;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    } while (escolha != 5);

    return 0;
}
