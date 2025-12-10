#ifndef ARMAZENAMENTO_STRATEGY_HPP
#define ARMAZENAMENTO_STRATEGY_HPP

#include <vector>
#include <string>

class Usuario;
class Conta;
class Hidrometro;

// Interface Strategy para armazenamento
class ArmazenamentoStrategy {
public:
    virtual ~ArmazenamentoStrategy() = default;

    virtual void salvar(
        const std::vector<Usuario>& usuarios,
        const std::vector<Conta>& contas,
        const std::vector<Hidrometro>& hidrometros
    ) = 0;

    virtual void carregar(
        std::vector<Usuario>& usuarios,
        std::vector<Conta>& contas,
        std::vector<Hidrometro>& hidrometros
    ) = 0;
};

#endif