#ifndef ADAPTERSHA1_HPP
#define ADAPTERSHA1_HPP

#include "ISHAAdapter.hpp"
#include <string>

/**
    Adapter para o SHA1 (Sistema de Hidrômetro Analógico).
    Responsável por localizar e fornecer o caminho da imagem mais recente gerada pelo SHA na pasta de saída configurada.
 */
class AdapterSHA1 : public ISHAAdapter {
public:
    explicit AdapterSHA1(const std::string& pastaSaida);
    std::string obterImagemMaisRecente() override;
    bool verificarDisponibilidade() override;
    std::string obterInformacoes() const override;
    
    double lerValorDoArquivo(const std::string& caminhoImagem);

private:
    std::string pastaSaida;
    bool ehArquivoImagem(const std::string& nomeArquivo) const;
};

#endif