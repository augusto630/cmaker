#include <tuple>
#include <functional>
#include <utility>

namespace std {
    template<typename... Args>
    struct hash<std::tuple<Args...> > {
        /**
         * hashes a tuple at compile time, if possible
         * @param tuple tuple to be hashed
         * @return a hashed value for the tuple
         */
        constexpr std::size_t operator()(const std::tuple<Args...> &tuple) const {
            std::size_t hash = 0;
            std::apply([&hash](const auto &... val) constexpr {
                // this hashing function will:
                // - get declared type of val
                // - reduces/decay the type of val to its original form, e.g. int[10] -> int, etc
                // - uses seed 0xEEFFDDCC to spread out hashed values
                // - shift << 5 and shift >> 3 also to spread hashed values
                // this procedure is executed for each value in the tuple
                ((hash ^= std::hash<std::decay_t<decltype(val)> >{}(val) + 0xEEFFDDCC + (hash << 5) + (hash >> 3))
                    , ...);
            }, tuple);
            return hash;
        }
    };
}
