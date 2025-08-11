#include "utility/logger/logger.hpp"

#include <iostream>
#include <cmath>

ConsoleLogger logger;

bool is_divisible(int number, int divisor) {
    logger.start_section("is_divisible");

    logger.debug("Checking if {} is divisible by {}", number, divisor);

    bool result = (number % divisor == 0);

    logger.debug("Result of divisibility check: {}", result ? "true" : "false");

    logger.end_section("is_divisible");
    return result;
}

bool has_any_divisors(int number) {
    logger.start_section("has_any_divisors");

    logger.debug("Checking number: {}", number);

    if (number <= 3) {
        logger.debug("Number <= 3, automatically considered no divisors");
        logger.end_section("has_any_divisors");
        return false;
    }

    int limit = static_cast<int>(std::sqrt(number));
    logger.debug("Limit for divisor search: {}", limit);

    for (int i = 2; i <= limit; ++i) {
        logger.debug("Testing divisor: {}", i);
        if (is_divisible(number, i)) {
            logger.debug("Found a divisor: {}", i);
            logger.end_section("has_any_divisors");
            return true; // found a divisor
        }
    }

    logger.debug("No divisors found");
    logger.end_section("has_any_divisors");
    return false;
}

bool is_prime(int number) {
    logger.start_section("is_prime");

    logger.debug("Checking if {} is prime", number);

    if (number <= 1) {
        logger.debug("Number <= 1, not prime");
        logger.end_section("is_prime");
        return false;
    }

    bool result = !has_any_divisors(number);
    logger.debug("Prime check result: {}", result ? "true" : "false");

    logger.end_section("is_prime");
    return result;
}

int main() {
    logger.start_section("main");

    int num = 29;
    logger.debug("Number to check: {}", num);

    bool prime_status = is_prime(num);
    logger.debug("{} is {}", num, prime_status ? "prime" : "not prime");

    logger.end_section("main");
    return 0;
}
