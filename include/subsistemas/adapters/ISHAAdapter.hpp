#ifndef ISHAADAPTER_HPP
#define ISHAADAPTER_HPP

#include <string>

/**
    Interface abstrata para Adapters de SHA.
    Define o contrato para integração com o Painel.
 */
class ISHAAdapter {
public:
    virtual ~ISHAAdapter() = default;
    
    virtual std::string obterImagemMaisRecente() = 0;
    virtual bool verificarDisponibilidade() = 0;
    virtual std::string obterInformacoes() const = 0;
};

#endif