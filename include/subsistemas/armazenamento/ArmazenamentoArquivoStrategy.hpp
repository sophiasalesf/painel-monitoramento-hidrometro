#ifndef ARMAZENAMENTO_ARQUIVO_STRATEGY_HPP
#define ARMAZENAMENTO_ARQUIVO_STRATEGY_HPP

#include <string>
#include "subsistemas/armazenamento/ArmazenamentoStrategy.hpp"

class ArmazenamentoArquivoStrategy : public ArmazenamentoStrategy {
public:
    explicit ArmazenamentoArquivoStrategy(const std::string& caminhoBase);
    virtual ~ArmazenamentoArquivoStrategy() = default;

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

private:
    std::string caminhoBase;
};

#endif