#include <iostream>
#include <map>
#include <string>
#include <boost/asio.hpp>

std::map<std::string, std::map<std::string, double>> exchangeRates = {
    {"USD", {{"EUR", 0.85}, {"GBP", 0.75}}},
    {"EUR", {{"USD", 1.18}, {"GBP", 0.88}}},
    {"GBP", {{"USD", 1.33}, {"EUR", 1.14}}},
};

void handleRequest(boost::asio::ip::tcp::iostream& stream) {
    std::string fromCurrency, toCurrency;
    double amount;

    stream >> fromCurrency >> toCurrency >> amount;

    if (exchangeRates.find(fromCurrency) != exchangeRates.end() &&
        exchangeRates[fromCurrency].find(toCurrency) != exchangeRates[fromCurrency].end()) {
        double exchangeRate = exchangeRates[fromCurrency][toCurrency];
        double convertedAmount = amount * exchangeRate;
        stream << "HTTP/1.1 200 OK\r\n"
               << "Content-Type: text/plain\r\n\r\n"
               << convertedAmount;
    } else {
        stream << "HTTP/1.1 400 Bad Request\r\n\r\nInvalid currency or currency pair.";
    }
}

int main() {
    boost::asio::ip::tcp::acceptor acceptor(
        boost::asio::io_context(),
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)
    );

    while (true) {
        boost::asio::ip::tcp::iostream stream;
        acceptor.accept(*stream.rdbuf());
        handleRequest(stream);
    }

    return 0;
}
