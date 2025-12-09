#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.hpp"
#include <vector>
#include <memory>

class Subject {
public:
    void adicionarObservador(std::shared_ptr<Observer> observador);
    void removerObservador(std::shared_ptr<Observer> observador);
    void notificarObservadores(const std::string& mensagem);

private:
    std::vector<std::shared_ptr<Observer>> observadores;
};

#endif