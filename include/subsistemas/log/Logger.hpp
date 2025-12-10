#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger {
public:
    explicit Logger(const std::string& caminhoArquivo);

    void info(const std::string& mensagem);
    void aviso(const std::string& mensagem);
    void erro(const std::string& mensagem);

private:
    std::string arquivoLog;

    void registrar(const std::string& nivel, const std::string& mensagem);
    std::string obterTimestamp() const;
};

#endif