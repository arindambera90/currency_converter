function convertCurrency() {
    const fromCurrency = document.getElementById("fromCurrency").value;
    const toCurrency = document.getElementById("toCurrency").value;
    const amount = parseFloat(document.getElementById("amount").value);
    
    // Replace with actual exchange rate API or your exchange rate logic
    const exchangeRate = getExchangeRate(fromCurrency, toCurrency);
    
    if (!isNaN(amount) && exchangeRate !== null) {
        const convertedAmount = amount * exchangeRate;
        document.getElementById("result").innerHTML = `${amount} ${fromCurrency} is equal to ${convertedAmount.toFixed(2)} ${toCurrency}`;
    } else {
        document.getElementById("result").innerHTML = "Invalid input or exchange rate data.";
    }
}

function getExchangeRate(fromCurrency, toCurrency) {
    // In a real app, you would fetch exchange rates from an API or database.
    // For simplicity, this function returns a hardcoded exchange rate.
    const exchangeRates = {
        "USD": {
            "EUR": 0.85,
            "GBP": 0.75,
            // Add more exchange rates here
        },
        "EUR": {
            "USD": 1.18,
            "GBP": 0.88,
        },
        "GBP": {
            "USD": 1.33,
            "EUR": 1.14,
        },
    };
    
    if (fromCurrency in exchangeRates && toCurrency in exchangeRates[fromCurrency]) {
        return exchangeRates[fromCurrency][toCurrency];
    } else {
        return null; // Invalid or unsupported currency pair
    }
}
