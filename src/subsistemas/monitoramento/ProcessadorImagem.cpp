#include "../../../include/subsistemas/monitoramento/ProcessadorImagem.hpp"
#include <iostream>

ProcessadorImagem::ProcessadorImagem(const std::string& caminho)
    : caminhoImagem(caminho) {
}

double ProcessadorImagem::processar() {
    carregarImagem();
    preprocessar();
    detectarDigitos();
    double valor = interpretarValor();

    return valor;
}