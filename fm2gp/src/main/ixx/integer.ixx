module;

#include <concepts>
#include <utility>

export module br.dev.pedrolamarao.number.integer;

export namespace br::dev::pedrolamarao::number
{
    template <typename Set>
    requires std::integral<Set>
    auto is_even (Set x) -> bool
    {
        return (x & 1) == 0;
    }

    template <typename Set>
    requires std::integral<Set>
    auto is_odd (Set x) -> bool
    {
        return (x & 1) == 1;
    }

    template <typename Set>
    requires std::integral<Set>
    auto sum (Set x, Set y) -> Set
    {
        return x + y;
    }

    template <typename Set>
    requires std::integral<Set>
    auto product (Set x, Set y) -> Set
    {
        return x * y;
    }

    template <typename Set>
    requires std::integral<Set>
    auto remainder (Set x, Set y) -> Set
    {
        return x % y;
    }

    template <typename Set>
    requires std::integral<Set>
    auto half (Set x) -> Set
    {
        return x >> 1;
    }

    template <typename Set>
    requires std::integral<Set>
    auto twice (Set x) -> Set
    {
        return x << 1;
    }

    template <typename Set>
    concept IntegerLike = requires (Set x, bool b)
    {
        std::regular<Set>;
        { b = is_even(x) };
        { b = is_odd(x) };
        { x = sum(x,x) };
        { x = product(x,x) };
        { x = remainder(x,x) };
        { x = half(x) };
        { x = twice(x) };
    };
}
