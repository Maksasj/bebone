#ifndef _BEBONE_CORE_META_FUNCTION_TRAITS_TPP_
#define _BEBONE_CORE_META_FUNCTION_TRAITS_TPP_

#include <tuple>
#include <type_traits>

namespace bebone::core {
    /// Meta function that is used for accessing function traits such as argument types
    template<typename> struct FunctionTraits;

    /// Meta function that is used for accessing function traits such as argument types
    template <typename Function>
    struct FunctionTraits : public FunctionTraits<decltype(&std::remove_reference<Function>::type::operator())> {

    };

    /// Meta function that is used for accessing function traits such as argument types
    template <typename ClassType, typename ReturnType, typename... Arguments>
    struct FunctionTraits<ReturnType(ClassType::*)(Arguments...) const> : FunctionTraits<ReturnType(*)(Arguments...)> {

    };

    /// Meta function that is used for accessing function traits such as argument types
    template <typename ClassType, typename ReturnType, typename... Arguments>
    struct FunctionTraits<ReturnType(ClassType::*)(Arguments...)> : FunctionTraits<ReturnType(*)(Arguments...)> {

    };

    /// Meta function that is used for accessing function traits such as argument types
    template <typename    ReturnType, typename... Arguments>
    struct FunctionTraits<ReturnType(*)(Arguments...)> {
        typedef ReturnType result_type;

        template <std::size_t Index>
        using Argument = typename std::tuple_element<Index, std::tuple<Arguments...>>::type;

        static const std::size_t arity = sizeof...(Arguments);
    };
}

#endif