#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void atualizar(const std::string& mensagem) = 0;
};

#endif