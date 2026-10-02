#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class big_integer {
private:
    std::vector<int> digits;

    void normalize() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

public:
    big_integer() : digits(1, 0) {}

    big_integer(const std::string& s) {
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
            digits.push_back(s[i] - '0');
        }
        normalize();
    }

    big_integer(const big_integer& other) : digits(other.digits) {}

    big_integer(big_integer&& other) noexcept : digits(std::move(other.digits)) {}

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            digits = std::move(other.digits);
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        big_integer result;
        result.digits.clear();

        size_t n = std::max(digits.size(), other.digits.size());
        int carry = 0;

        for (size_t i = 0; i < n || carry; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            carry = sum / 10;
            result.digits.push_back(sum % 10);
        }

        result.normalize();
        return result;
    }

    big_integer operator*(int num) const {
        big_integer result;
        result.digits.clear();

        int carry = 0;
        for (size_t i = 0; i < digits.size() || carry; ++i) {
            long long product = carry;
            if (i < digits.size()) product += static_cast<long long>(digits[i]) * num;
            carry = static_cast<int>(product / 10);
            result.digits.push_back(static_cast<int>(product % 10));
        }

        result.normalize();
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num) {
        for (int i = static_cast<int>(num.digits.size()) - 1; i >= 0; --i) {
            os << num.digits[i];
        }
        return os;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << "\n";  // 193099

    auto product = number1 * 3;
    std::cout << product << "\n"; // 343725

    return 0;
}