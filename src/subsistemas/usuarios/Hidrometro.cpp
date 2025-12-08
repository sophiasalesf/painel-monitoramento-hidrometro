#include "../../../include/subsistemas/usuarios/Hidrometro.hpp"
#include <iostream>
#include <sstream>
#include <ctime>

// Construtor padrão
Hidrometro::Hidrometro()
    : numeroHidrometro(""), numeroConta(""), leituraAtual(0.0), dataCriacao("") 
{}

// Construtor com parâmetros
Hidrometro::Hidrometro(const std::string& numeroHidrometro, const std::string& numeroConta)
    : numeroHidrometro(numeroHidrometro), numeroConta(numeroConta), leituraAtual(0.0) {
    // Gerar timestamp (simplificado)
    time_t agora = time(nullptr);
    dataCriacao = std::to_string(agora);
}

// Getters
std::string Hidrometro::getNumeroHidrometro() const {
    return numeroHidrometro;
}

std::string Hidrometro::getNumeroConta() const {
    return numeroConta;
}

double Hidrometro::getLeituraAtual() const {
    return leituraAtual;
}

std::string Hidrometro::getDataCriacao() const {
    return dataCriacao;
}

// Setters
void Hidrometro::setLeituraAtual(double novaLeitura) {
    leituraAtual = novaLeitura;
}

// Exibição
std::string Hidrometro::toString() const {
    std::stringstream ss;
    ss << "Hidrometro(" << numeroHidrometro << ", Leitura: " << leituraAtual << " m3)";
    return ss.str();
}