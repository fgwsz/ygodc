#include "main.h"
#include "fraction.hpp"
#include <cstddef>//::std::size_t
#include <unordered_map>//::std::unordered_map
#include <string>//::std::stoull

// 使用递推公式计算组合数,避免大阶乘
Fraction C_r_n_optimized(::std::size_t r,::std::size_t n){
    if(r > n){
        return Fraction(0);
    }
    if(r > n - r){
        r = n - r;//利用对称性
    }
    auto result = Fraction(1);
    for(::std::size_t i = 1; i <= r; ++i){
        result = result * Fraction(n - i + 1, i);
    }
    return result;
}
// 计算超几何分布概率
Fraction hypergeometric_probability(::std::size_t deck_size, 
                                   ::std::size_t target_cards, 
                                   ::std::size_t hand_cards, 
                                   ::std::size_t n) {
    // 参数验证
    if(n > target_cards || hand_cards - n > deck_size - target_cards) {
        return Fraction(0);
    }
    return C_r_n_optimized(n, target_cards)
           * C_r_n_optimized(hand_cards - n, deck_size - target_cards)
           / C_r_n_optimized(hand_cards, deck_size);
}
int main(int argc, char* argv[]){
    // 参数检查
    if(argc != 5) {
        ::std::cerr << "用法: " << argv[0] 
                   << " <牌库总数> <目标牌数量> <抽牌数量> <期望抽到的目标牌数量>\n";
        return 1;
    }
    try {
        ::std::size_t deck_size = ::std::stoull(argv[1]);
        ::std::size_t target_cards = ::std::stoull(argv[2]);
        ::std::size_t hand_cards = ::std::stoull(argv[3]);
        ::std::size_t n = ::std::stoull(argv[4]);
        // 验证参数合理性
        if(target_cards > deck_size || hand_cards > deck_size) {
            ::std::cerr << "错误: 目标牌数量或抽牌数量不能大于牌库总数\n";
            return 1;
        }
        Fraction probability = hypergeometric_probability(
            deck_size, target_cards, hand_cards, n);
        ::std::cout << "概率: " << probability 
                   << " (约 " << static_cast<double>(probability)*100
                   << " %)\n";
    } catch(const ::std::exception& e) {
        ::std::cerr << "错误: 参数解析失败 - " << e.what() << '\n';
        return 1;
    }
    return 0;
}
