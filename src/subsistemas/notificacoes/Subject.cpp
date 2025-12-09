#include "../../../include/subsistemas/notificacoes/Subject.hpp"
#include <algorithm>

void Subject::adicionarObservador(std::shared_ptr<Observer> observador) {
    observadores.push_back(observador);
}

void Subject::removerObservador(std::shared_ptr<Observer> observador) {
    observadores.erase(
        std::remove(observadores.begin(), observadores.end(), observador),
        observadores.end()
    );
}

void Subject::notificarObservadores(const std::string& mensagem) {
    for (auto& observador : observadores) {
        observador->atualizar(mensagem);
    }
}