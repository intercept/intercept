#pragma once

namespace intercept {
    struct gamestate_partial {
        auto_array<void*> types;
        map_string_to_class<__internal::game_functions, auto_array<__internal::game_functions>> functions;
        map_string_to_class<__internal::game_operators, auto_array<__internal::game_operators>> operators;
        map_string_to_class<__internal::gsNular, auto_array<__internal::gsNular>> nulars;

        static bool is_valid(const auto_array<void*>& arr) {
            if (arr.size() != arr.capacity())
                return false;

            if (IsBadReadPtr(arr.data(), sizeof(void*) + 2 * sizeof(int)))
                return false;

            return true;
        }

        template <class Type>
        static bool is_valid(const map_string_to_class<Type, auto_array<Type>>& map) {
            if (IsBadReadPtr(map.GetTablePtrRaw(), sizeof(void*)))
                return false;

            // all arrays in map are compacted, could check that too. But if we get to here we're probably fine

            return true;
        }

        bool is_valid() const {
            if (!is_valid(types)) return false;
            if (!is_valid(functions)) return false;
            if (!is_valid(operators)) return false;
            if (!is_valid(nulars)) return false;
            return true;
        }

        void dump() const {
            std::cerr << '\t' << "size: " << sizeof(struct gamestate_partial) << " (game_state: " << sizeof(game_state) << ')' << std::endl;
        }
    };
}
