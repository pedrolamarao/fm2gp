module;

#include <concepts>
#include <utility>

export module br.dev.pedrolamarao.number.gcd;

import br.dev.pedrolamarao.number.integer;

export namespace br::dev::pedrolamarao::number
{
    // gcd

    template <Integer I>
    auto gcd (I x, I y) -> I
    {
        using std::swap;
        while (y != I{0}) {
            x = remainder(x,y);
            swap(x,y);
        }
        return x;
    }
}
