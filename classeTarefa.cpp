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