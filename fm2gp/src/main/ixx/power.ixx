export module br.dev.pedrolamarao.number.power;

import br.dev.pedrolamarao.number.integer;

export namespace br::dev::pedrolamarao::number
{
    // Operator

    template <typename Operator, typename Set>
    concept SemigroupOperator = requires (Operator o, Set e)
    {
        { e = o(e,e) };
    };

    template <typename Operator, typename Set>
    struct identity_type;

    template <typename Operator, typename Set>
    constexpr auto identity = identity_type<Operator,Set>::value;

    template <typename Operator, typename Set>
    concept MonoidOperator = SemigroupOperator<Operator,Set> && requires (Operator o, Set e)
    {
        { e = identity<Operator,Set> };
    };

    template <typename Operator, typename Set>
    struct inverse_type;

    template <typename Operator, typename Set>
    constexpr auto inverse = typename inverse_type<Operator,Set>::type();

    template <typename Operator, typename Set>
    concept GroupOperator = MonoidOperator<Operator,Set> && requires (Operator o, Set e)
    {
        { e = inverse<Operator,Set>(e) };
    };

    // power

    template <typename Set, SemigroupOperator<Set> Operator, Integer I>
    // requires { n >= Integer(0) }
    auto power_accumulate_semigroup (Operator o, Set a, Set x, I n) -> Set
    {
        if (n == I{0})
            return a;
        while (true) {
            if (is_odd(n)) {
                a = o(a,x);
                if (n == I(1))
                    return a;
            }
            n = half(n);
            x = o(x,x);
        }
    }

    template <typename Set, SemigroupOperator<Set> Operator, Integer I>
    // requires { n > Integer(0) }
    auto power_semigroup (Operator o, Set x, I n) -> Set
    {
        while (! is_odd(n)) {
            x = o(x,x);
            n = half(n);
        }
        if (n == I{1})
            return x;
        return power_accumulate_semigroup(o,x,o(x,x),half(n-I{1}));
    }

    template <typename Set, MonoidOperator<Set> Operator, Integer I>
    // requires { n >= Integer(0) }
    auto power_monoid (Operator o, Set x, I n) -> Set
    {
        if (n == I{0})
            return identity<Operator,Set>;
        return power_semigroup(o,x,n);
    }

    template <typename Set, GroupOperator<Set> Operator, Integer I>
    auto power_group (Operator o, Set x, I n) -> Set
    {
        if (n < I{0}) {
            n = -n;
            x = inverse<Operator,Set>(x);
        }
        return power_monoid(o,x,n);
    }
}
