#ifndef NOTIFICADOR_HPP
#define NOTIFICADOR_HPP

#include "Observer.hpp"
#include <string>

class Notificador : public Observer {
public:
    explicit Notificador(const std::string& nome);
    void atualizar(const std::string& mensagem) override;

private:
    std::string nome;
};

#endif