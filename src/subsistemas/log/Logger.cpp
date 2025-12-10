#include "../../../include/subsistemas/log/Logger.hpp"

#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Logger(const std::string& caminhoArquivo)
    : arquivoLog(caminhoArquivo) {}

void Logger::info(const std::string& mensagem) {
    registrar("INFO", mensagem);
}

void Logger::aviso(const std::string& mensagem) {
    registrar("AVISO", mensagem);
}

void Logger::erro(const std::string& mensagem) {
    registrar("ERRO", mensagem);
}

void Logger::registrar(const std::string& nivel, const std::string& mensagem) {
    std::string timestamp = obterTimestamp();
    std::string linha = "[" + timestamp + "] [" + nivel + "] " + mensagem;

    // Console
    std::cout << linha << std::endl;

    // Arquivo
    std::ofstream arquivo(arquivoLog, std::ios::app);
    if (arquivo.is_open()) {
        arquivo << linha << std::endl;
    }
}

std::string Logger::obterTimestamp() const {
    auto agora = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(agora);

    std::tm tmLocal{};
#ifdef _WIN32
    localtime_s(&tmLocal, &t);
#else
    localtime_r(&t, &tmLocal);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tmLocal, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}