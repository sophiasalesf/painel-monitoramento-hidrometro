#ifndef HIDROMETRO_HPP
#define HIDROMETRO_HPP

#include <string>
#include <ctime>

class Hidrometro 
{
public:
    // Construtores
    Hidrometro();
    Hidrometro(const std::string& numeroHidrometro, const std::string& numeroConta);

    // Getters
    std::string getNumeroHidrometro() const;
    std::string getNumeroConta() const;
    double getLeituraAtual() const;
    std::string getDataCriacao() const;

    // Setters
    void setLeituraAtual(double novaLeitura);

    // Exibição
    std::string toString() const;

private:
    std::string numeroHidrometro;
    std::string numeroConta;
    double leituraAtual;
    std::string dataCriacao;
};

#endif