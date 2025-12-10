#ifndef ARMAZENAMENTO_CONSOLE_STRATEGY_HPP
#define ARMAZENAMENTO_CONSOLE_STRATEGY_HPP

#include "subsistemas/armazenamento/ArmazenamentoStrategy.hpp"

class ArmazenamentoConsoleStrategy : public ArmazenamentoStrategy {
public:
    ArmazenamentoConsoleStrategy() = default;
    virtual ~ArmazenamentoConsoleStrategy() = default;

    void salvar(
        const std::vector<Usuario>& usuarios,
        const std::vector<Conta>& contas,
        const std::vector<Hidrometro>& hidrometros
    ) override;

    void carregar(
        std::vector<Usuario>& usuarios,
        std::vector<Conta>& contas,
        std::vector<Hidrometro>& hidrometros
    ) override;
};

#endif