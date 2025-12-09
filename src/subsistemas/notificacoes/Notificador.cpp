#include "../../../include/subsistemas/notificacoes/Notificador.hpp"
#include <iostream>

Notificador::Notificador(const std::string& nome) : nome(nome) {}

void Notificador::atualizar(const std::string& mensagem) {
    std::cout << "[NOTIFICADOR: " << nome << "] " << mensagem << std::endl;
}