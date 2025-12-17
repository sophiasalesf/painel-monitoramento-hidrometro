#ifndef HIDROMETRO_HPP
#define HIDROMETRO_HPP

#include <string>
#include <vector>
#include "../notificacoes/Subject.hpp"

class Hidrometro : public Subject {
public:
    // construtor padrão
    Hidrometro();
    Hidrometro(const std::string& numero, double leituraInicial);

    // getters
    std::string getNumero() const;
    double getLeituraAtual() const;
    std::string getNumeroConta() const;
    const std::vector<double>& getHistoricoLeituras() const;

    // setters
    void setLeituraAtual(double novaLeitura);
    void setNumeroConta(const std::string& conta);

private:
    std::string numero;
    double leituraAtual;
    std::vector<double> historicoLeituras;
    std::string numeroConta;
};

#endif