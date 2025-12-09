#include "../../../include/subsistemas/usuarios/Hidrometro.hpp"

Hidrometro::Hidrometro() : numero(""), leituraAtual(0.0) {}

Hidrometro::Hidrometro(const std::string& numero, double leituraInicial)
    : numero(numero), leituraAtual(leituraInicial) {}

std::string Hidrometro::getNumero() const {
    return numero;
}

double Hidrometro::getLeituraAtual() const {
    return leituraAtual;
}

void Hidrometro::setLeituraAtual(double novaLeitura) {
    leituraAtual = novaLeitura;

    // Notifica observadores sobre a mudança
    std::string msg = "Hidrômetro " + numero + " atualizado para " + std::to_string(leituraAtual) + " m^3";
    notificarObservadores(msg);
}