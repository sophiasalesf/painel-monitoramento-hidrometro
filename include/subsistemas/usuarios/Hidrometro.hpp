#ifndef HIDROMETRO_HPP
#define HIDROMETRO_HPP

#include <string>
#include "../notificacoes/Subject.hpp"

class Hidrometro : public Subject {
public:
    // construtor padrão
    Hidrometro();
    Hidrometro(const std::string& numero, double leituraInicial);

    std::string getNumero() const;
    double getLeituraAtual() const;
    void setLeituraAtual(double novaLeitura);

private:
    std::string numero;
    double leituraAtual;
};

#endif
