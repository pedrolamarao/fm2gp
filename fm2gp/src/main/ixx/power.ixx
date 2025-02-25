module;

#include <concepts>

export module br.dev.pedrolamarao.number.power;

export namespace br::dev::pedrolamarao::number
{
    // Integer

    template <typename Integer>
    auto is_odd (Integer x) -> bool;

    template <typename Integer>
    auto half (Integer x) -> Integer;

    // power

    template <typename Operator, typename Set, typename Integer>
    requires requires (Operator o, Set x, Integer n) {
        // Operator domain is a Semigroup
        std::regular<Set>;
        std::invocable<Operator,Set,Set>;
        // Integer is integer-like
        std::integral<Integer>;
        { is_odd(n) };
        { n = half(n) };
    }
    // requires { n >= Integer(0) }
    auto power_accumulate_semigroup (Operator o, Set r, Set x, Integer n) -> Set
    {
        if (n == Integer(0))
            return r;
        while (true) {
            if (is_odd(n)) {
                r = o(r,x);
                if (n == Integer(1))
                    return r;
            }
            n = half(n);
            x = o(x,x);
        }
    }

    template <typename Operator, typename Set, typename Integer>
    requires requires (Operator o, Set x, Integer n) {
        // Operator domain is a Semigroup
        std::regular<Set>;
        std::invocable<Operator,Set,Set>;
        // Integer is integer-like
        std::integral<Integer>;
        { is_odd(n) };
        { n = half(n) };
    }
    // requires { n > Integer(0) }
    auto power_semigroup (Operator o, Set x, Integer n) -> Set
    {
        while (! is_odd(n)) {
            x = o(x,x);
            n = half(n);
        }
        if (n == Integer(1))
            return x;
        return power_accumulate_semigroup(o,x,o(x,x),half(n-Integer(1)));
    }

    template <typename Operator, typename Set>
    struct identity_type;

    template <typename Operator, typename Set>
    constexpr auto identity = identity_type<Operator,Set>::value;

    template <typename Operator, typename Set, typename Integer>
    requires requires (Operator o, Set x, Integer n) {
        // Operator domain is a Monoid
        std::regular<Set>;
        std::invocable<Operator,Set,Set>;
        { x = identity<Operator,Set> };
        // Integer is integer-like
        std::integral<Integer>;
        { is_odd(n) };
        { n = half(n) };
    }
    // requires { n >= Integer(0) }
    auto power_monoid (Operator o, Set x, Integer n) -> Set
    {
        if (n == Integer(0))
            return identity<Operator,Set>;
        return power_semigroup(o,x,n);
    }

    template <typename Operator, typename Set>
    struct inverse_type;

    template <typename Operator, typename Set>
    constexpr auto inverse = typename inverse_type<Operator,Set>::type();

    template <typename Operator, typename Set, typename Integer>
    requires requires (Operator o, Set x, Integer n) {
        // Operator domain is a Group
        std::regular<Set>;
        std::invocable<Operator,Set,Set>;
        { x = identity<Operator,Set> };
        { x = inverse<Operator,Set>(x) };
        // Integer is integer-like
        std::integral<Integer>;
        { is_odd(n) };
        { n = half(n) };
    }
    auto power_group (Operator o, Set x, Integer n) -> Set
    {
        if (n < Integer(0)) {
            n = -n;
            x = inverse<Operator,Set>(x);
        }
        return power_monoid(o,x,n);
    }
}
