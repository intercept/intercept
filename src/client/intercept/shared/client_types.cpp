#include "shared/client_types.hpp"
#include "client/client.hpp"
#include "shared/functions.hpp"
#include "../client/sqf/common_helpers.hpp"

namespace intercept::types {
    internal_object::internal_object() : game_value() {}
    //internal_object::internal_object(const rv_game_value &value_) : game_value(value_) {}
    internal_object::internal_object(const game_value & value_) : game_value(value_) {
        set_vtable(game_value::__vptr_def);
    }
    internal_object::internal_object(const internal_object & copy_) : game_value(copy_) {
        set_vtable(game_value::__vptr_def);
    }
    internal_object::internal_object(internal_object && move_) noexcept : game_value(move_) { set_vtable(game_value::__vptr_def); }

    internal_object & internal_object::operator=(internal_object && move_) noexcept {
        if (this == &move_)
            return *this;
        game_value::operator=(std::move(move_));
        return *this;
    }

    internal_object & internal_object::operator=(const internal_object & copy_) {
        game_value::operator=(copy_);
        return *this;
    }

    bool internal_object::operator<(const internal_object& compare_) const {
        return static_cast<game_data_object *>(data.get())->object < static_cast<game_data_object *>(compare_.data.get())->object;
    }

    bool internal_object::operator>(const internal_object& compare_) const {
        return static_cast<game_data_object *>(data.get())->object > static_cast<game_data_object *>(compare_.data.get())->object;
    }

#define RV_GENERIC_OBJECT_DEF(type)         type::type() : internal_object() {}\
    type::type(const game_value & value_) : internal_object(value_) {}\
    type::type(const type &copy_) : internal_object(copy_) {}\
    type::type(type && move_) : internal_object(std::move(move_)) {}\
    type & type::operator=(type && move_) {\
        if (this == &move_)\
            return *this;\
        game_value::operator=(std::move(move_));\
        return *this;\
    }\
    type & type::operator=(const type & copy_) {\
        game_value::operator=(copy_);\
        return *this;\
    }

    RV_GENERIC_OBJECT_DEF(object)

    RV_GENERIC_OBJECT_DEF(group)

    RV_GENERIC_OBJECT_DEF(code)

    RV_GENERIC_OBJECT_DEF(config)

    RV_GENERIC_OBJECT_DEF(control)

    RV_GENERIC_OBJECT_DEF(display)

    RV_GENERIC_OBJECT_DEF(location)

    RV_GENERIC_OBJECT_DEF(script)

    RV_GENERIC_OBJECT_DEF(side)

    RV_GENERIC_OBJECT_DEF(rv_text)

    RV_GENERIC_OBJECT_DEF(team_member)

    RV_GENERIC_OBJECT_DEF(rv_namespace)

    RV_GENERIC_OBJECT_DEF(task)

    rv_hit_points_damage::rv_hit_points_damage(const game_value& _gv) {
        auto& _arr = _gv.to_array();
        if (_arr.count() != 3) return;
        hit_points = sqf::__helpers::__convert_to_vector<sqf_return_string>(_arr[0]);
        hit_selections = sqf::__helpers::__convert_to_vector<sqf_return_string>(_arr[1]);
        damages = sqf::__helpers::__convert_to_vector<float>(_arr[2]);
    }


    static std::vector<ref<game_data>> gv_threadsafe_garbage;
    static std::mutex gv_threadsafe_garbage_lock;

    void game_value_threadsafe::garbage_collect() {
        std::unique_lock<std::mutex> lock(gv_threadsafe_garbage_lock);
        client::invoker_lock invoke_lock;
        gv_threadsafe_garbage.clear();
    }

    game_value_threadsafe::~game_value_threadsafe() {
        discard(std::move(data));
    }

    game_value_threadsafe::game_value_threadsafe(float val_) {
        client::invoker_lock lock;
        data = new game_data_number(val_);
    }
    game_value_threadsafe::game_value_threadsafe(int val_) : game_value_threadsafe(static_cast<float>(val_)) {}
    game_value_threadsafe::game_value_threadsafe(size_t val_) : game_value_threadsafe(static_cast<float>(val_)) {}
    game_value_threadsafe::game_value_threadsafe(bool val_) {
        client::invoker_lock lock;
        data = new game_data_bool(val_);
    }
    game_value_threadsafe::game_value_threadsafe(const std::string& val_) {
        client::invoker_lock lock;
        data = new game_data_string(val_);
    }
    game_value_threadsafe::game_value_threadsafe(const r_string& val_) {
        client::invoker_lock lock;
        data = new game_data_string(val_);
    }
    game_value_threadsafe::game_value_threadsafe(std::string_view val_) {
        client::invoker_lock lock;
        data = new game_data_string(val_);
    }
    game_value_threadsafe::game_value_threadsafe(const std::vector<game_value>& list_) {
        client::invoker_lock lock;
        data = new game_data_array(list_);
    }
    game_value_threadsafe::game_value_threadsafe(const std::initializer_list<game_value>& list_) {
        client::invoker_lock lock;
        data = new game_data_array(list_);
    }
    game_value_threadsafe::game_value_threadsafe(auto_array<game_value>&& array_) {
        client::invoker_lock lock;
        data = new game_data_array(std::move(array_));
    }
    game_value_threadsafe::game_value_threadsafe(const vector3& vec_) {
        client::invoker_lock lock;
        data = new game_data_array({ vec_.x, vec_.y, vec_.z });
    }
    game_value_threadsafe::game_value_threadsafe(const vector2& vec_) {
        client::invoker_lock lock;
        data = new game_data_array({ vec_.x, vec_.y });
    }
    game_value_threadsafe::game_value_threadsafe(const internal_object& internal_){
        discard(std::move(data));
        data = internal_.data;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(game_value&& move_) noexcept {
        set_vtable(__vptr_def);
        discard(std::move(data));
        data = move_.data;
        move_.data = nullptr;
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(float val_) {
        client::invoker_lock lock;
        game_value::operator=(val_);
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(bool val_) {
        client::invoker_lock lock;
        game_value::operator=(val_);
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(const std::string& val_) {
        client::invoker_lock lock;
        game_value::operator=(val_);
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(const r_string& val_) {
        client::invoker_lock lock;
        game_value::operator=(val_);
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(std::string_view val_) {
        client::invoker_lock lock;
        game_value::operator=(val_);
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(const std::vector<game_value>& list_) {
        client::invoker_lock lock;
        game_value::operator=(list_);
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(const vector3& vec_) {
        client::invoker_lock lock;
        game_value::operator=(vec_);
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(const vector2& vec_) {
        client::invoker_lock lock;
        game_value::operator=(vec_);
        return *this;
    }
    game_value_threadsafe& game_value_threadsafe::operator=(const internal_object& internal_) {
        discard(std::move(data));
        data = internal_.data;
        return *this;
    }

    game_value_threadsafe & game_value_threadsafe::operator=(const game_value & copy_) {
        discard(std::move(data));
        data = copy_.data;
        return *this;
    }

    void game_value_threadsafe::discard(ref<game_data>&& data) {
        if (data.is_null()) return;
        //Don't need to store data that won't get deleted anyway.
        //But we also don't want to get into race-condition area. Number 5 was choosen by a fair dice roll.
        if (data.ref_count() < 5) {
            std::unique_lock<std::mutex> lock(gv_threadsafe_garbage_lock);
            gv_threadsafe_garbage.emplace_back(std::move(data));
        }
    }

}
