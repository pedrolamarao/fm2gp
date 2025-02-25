module;

#include <concepts>
#include <utility>

export module br.dev.pedrolamarao.number.gcd;

import br.dev.pedrolamarao.number.integer;

export namespace br::dev::pedrolamarao::number
{
    // gcd

    template <typename Set>
    auto gcd (Set x, Set y) -> Set
    {
        using std::swap;
        while (y != Set(0)) {
            x = remainder(x,y);
            swap(x,y);
        }
        return x;
    }
}
