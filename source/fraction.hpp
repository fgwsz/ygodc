#ifndef FRACTION_HPP
#define FRACTION_HPP

#include<cstddef>//::std::size_t
#include<numeric>//::std::gcd
#include<stdexcept>//::std::invalid_argument
#include<string>//::std::string

struct Fraction{
    ::std::size_t numerator;//分子
    ::std::size_t denominator;//分母
    //构造函数
    Fraction(Fraction const&)=default;
    Fraction& operator=(Fraction const&)=default;
    Fraction(::std::size_t num=0,::std::size_t den=1)
        :numerator(num)
        ,denominator(den){
        if(denominator==0){
            throw ::std::invalid_argument("分母不能为零");
        }
        this->simplify();//自动简化
    }
    //算术运算符重载
    Fraction operator*(Fraction const& other)const{
        return Fraction(
            this->numerator*other.numerator
            ,this->denominator*other.denominator
        );
    }
    Fraction operator/(Fraction const& other)const{
        if(other.numerator==0){
            throw ::std::invalid_argument("除法错误:除数为零");
        }
        return Fraction(
            this->numerator*other.denominator
            ,this->denominator*other.numerator
        );
    }
    //类型转换
    explicit operator double(void)const{
        return static_cast<double>(numerator)/denominator;
    }
    ::std::string to_string(void)const{
        if(this->denominator==1){
            return ::std::to_string(this->numerator);
        }else{
            return ::std::to_string(this->numerator)
                +"/"+::std::to_string(this->denominator);
        }
    }
private:
    //简化分数
    void simplify(void){
        ::std::size_t gcd=::std::gcd(numerator,denominator);
        numerator/=gcd;
        denominator/=gcd;
    }
};

#endif//!FRACTION_HPP
