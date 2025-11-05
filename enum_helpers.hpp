//
// Created by neko on 11/2/25.
//

#ifndef RV64_ENUM_HELPERS_HPP
#define RV64_ENUM_HELPERS_HPP

#include <type_traits>

template <typename Enum>
struct is_flag_enum : std::true_type {};

template <typename Enum>
inline constexpr typename std::enable_if<is_flag_enum<Enum>::value, Enum>::type
operator~(Enum a) {
    using T = std::underlying_type_t<Enum>;
    return static_cast<Enum>(~static_cast<T>(a));
}

template <typename Enum>
inline constexpr typename std::enable_if<is_flag_enum<Enum>::value, Enum>::type
operator|(Enum a, Enum b) {
    using T = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<T>(a) | static_cast<T>(b));
}

template <typename Enum>
inline constexpr typename std::enable_if<is_flag_enum<Enum>::value, Enum>::type
operator&(Enum a, Enum b) {
    using T = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<T>(a) & static_cast<T>(b));
}

template <typename Enum>
inline constexpr typename std::enable_if<is_flag_enum<Enum>::value, Enum>::type
operator^(Enum a, Enum b) {
    using T = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<T>(a) ^ static_cast<T>(b));
}

template <typename Enum>
inline typename std::enable_if<is_flag_enum<Enum>::value, Enum&>::type
operator|=(Enum& a, Enum b) {
    a = a | b;
    return a;
}

template <typename Enum>
inline typename std::enable_if<is_flag_enum<Enum>::value, Enum&>::type
operator&=(Enum& a, Enum b) {
    a = a & b;
    return a;
}

template <typename Enum>
inline typename std::enable_if<is_flag_enum<Enum>::value, Enum&>::type
operator^=(Enum& a, Enum b) {
    a = a ^ b;
    return a;
}

// Optional: check if a flag is set
template <typename Enum>
inline constexpr typename std::enable_if<is_flag_enum<Enum>::value, bool>::type
has_flag(Enum value, Enum flag) {
    using T = std::underlying_type_t<Enum>;
    return (static_cast<T>(value) & static_cast<T>(flag)) != 0;
}


#endif //RV64_ENUM_HELPERS_HPP
