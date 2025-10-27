#pragma once
#include <iostream>
#include <numeric> // std::gcd
#include <stdexcept> // std::invalid_argument
#include <cmath>    // std::abs

struct Fraction {
    long long numerator;   // 分子
    long long denominator; // 分母
    // 构造函数
    Fraction(long long num = 0, long long den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw std::invalid_argument("分母不能为零");
        }
        simplify(); // 自动简化
        // 确保分母为正,符号由分子携带
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
    // 复制构造函数
    Fraction(const Fraction& other) = default;
    // 赋值运算符
    Fraction& operator=(const Fraction& other) = default;
private:
    // 简化分数(私有方法)
    void simplify() {
        long long gcd = std::gcd(std::abs(numerator), std::abs(denominator));
        numerator /= gcd;
        denominator /= gcd;
    }
public:
    // 算术运算符重载
    Fraction operator+(const Fraction& other) const {
        long long new_num = numerator * other.denominator + other.numerator * denominator;
        long long new_den = denominator * other.denominator;
        return Fraction(new_num, new_den);
    }
    Fraction operator-(const Fraction& other) const {
        long long new_num = numerator * other.denominator - other.numerator * denominator;
        long long new_den = denominator * other.denominator;
        return Fraction(new_num, new_den);
    }
    Fraction operator*(const Fraction& other) const {
        long long new_num = numerator * other.numerator;
        long long new_den = denominator * other.denominator;
        return Fraction(new_num, new_den);
    }
    // 明确的除法运算符重载
    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("除法错误:除数为零");
        }
        long long new_num = numerator * other.denominator;
        long long new_den = denominator * other.numerator;
        return Fraction(new_num, new_den);
    }
    // 复合赋值运算符
    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }
    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }
    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }
    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }
    // 比较运算符重载
    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }
    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }
    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }
    bool operator>(const Fraction& other) const {
        return other < *this;
    }
    bool operator<=(const Fraction& other) const {
        return !(other < *this);
    }
    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }
    // 一元运算符
    Fraction operator-() const {
        return Fraction(-numerator, denominator);
    }
    Fraction operator+() const {
        return *this;
    }
    // 类型转换
    explicit operator double() const {
        return static_cast<double>(numerator) / denominator;
    }
    explicit operator float() const {
        return static_cast<float>(numerator) / denominator;
    }
    // 友元函数:输出流
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        if (frac.denominator == 1) {
            os << frac.numerator;
        } else {
            os << frac.numerator << "/" << frac.denominator;
        }
        return os;
    }
    // 实用方法
    Fraction reciprocal() const {
        if (numerator == 0) {
            throw std::invalid_argument("倒数错误:分子为零");
        }
        return Fraction(denominator, numerator);
    }
    Fraction abs() const {
        return Fraction(std::abs(numerator), std::abs(denominator));
    }
    bool is_zero() const {
        return numerator == 0;
    }
    bool is_positive() const {
        return numerator > 0;
    }
    bool is_negative() const {
        return numerator < 0;
    }
};
// 全局运算符重载,支持与整数的混合运算
Fraction operator+(long long num, const Fraction& frac) {
    return Fraction(num) + frac;
}
Fraction operator-(long long num, const Fraction& frac) {
    return Fraction(num) - frac;
}
Fraction operator*(long long num, const Fraction& frac) {
    return Fraction(num) * frac;
}
Fraction operator/(long long num, const Fraction& frac) {
    return Fraction(num) / frac;
}
