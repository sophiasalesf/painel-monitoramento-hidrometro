#ifndef ADAPTERSHA2_HPP
#define ADAPTERSHA2_HPP

#include "ISHAAdapter.hpp"
#include <string>

/**
    Adapter para o SHA2 (Sistema de Hidrômetro Analógico da Ligia).
    Responsável por localizar a imagem PNG mais recente gerada pelo SHA2
    e extrair o valor de consumo a partir do nome do arquivo.
    Exemplo de arquivo: "hidrometro_final_0.02.png" -> valor 0.02.
*/
class AdapterSHA2 : public ISHAAdapter {
public:
    explicit AdapterSHA2(const std::string& pastaSaida);

    std::string obterImagemMaisRecente() override;
    bool verificarDisponibilidade() override;
    std::string obterInformacoes() const override;

    // Recebe caminho da imagem, extrai o nome e o valor entre o último "_" e ".png"
    double lerValorDoArquivo(const std::string& caminhoImagem);

private:
    std::string pastaSaida;

    bool ehArquivoImagem(const std::string& nomeArquivo) const;
};

#endif