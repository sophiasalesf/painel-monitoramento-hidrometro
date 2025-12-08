#include "../../../include/subsistemas/monitoramento/LeitorImagem.hpp"

LeitorImagem::LeitorImagem(const std::string& caminho)
    : caminhoImagem(caminho) {
}

double LeitorImagem::lerValorHidrometro() {
    return 123.45;
}

std::string LeitorImagem::getCaminhoImagem() const {
    return caminhoImagem;
}