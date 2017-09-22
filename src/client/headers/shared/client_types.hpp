#pragma once
#include "shared.hpp"
#include "types.hpp"
#include <variant>
namespace intercept {
    namespace types {

        class internal_object : public game_value {
        public:
            internal_object();
            //internal_object(const rv_game_value &value_);  //deprecated
            internal_object(const game_value &value_);
            internal_object(const internal_object &copy_);
            internal_object(internal_object &&move_) noexcept;
            internal_object & operator = (internal_object &&move_) noexcept;

            internal_object & operator = (const internal_object &copy_);

            bool operator<(const internal_object& compare_) const;
            bool operator>(const internal_object& compare_) const;

            bool is_null() const;

        };

            //type(const rv_game_value &value_);\ deprecated
#define RV_GENERIC_OBJECT_DEC(type) class type : public internal_object {\
            public:\
                type();\
                type(const game_value &value_);\
                type(const type &copy_);\
                type(const internal_object &copy_) = delete;/*prevents code(object()) You can't convert object to code!*/\
                type(type &&move_);\
                type & operator = (type &&move_);\
                type & operator = (const type &copy_);\
            }

        RV_GENERIC_OBJECT_DEC(object);
        RV_GENERIC_OBJECT_DEC(group);
        RV_GENERIC_OBJECT_DEC(code);
        RV_GENERIC_OBJECT_DEC(config);
        RV_GENERIC_OBJECT_DEC(control);
        RV_GENERIC_OBJECT_DEC(display);
        RV_GENERIC_OBJECT_DEC(location);
        RV_GENERIC_OBJECT_DEC(script);
        RV_GENERIC_OBJECT_DEC(side);
        RV_GENERIC_OBJECT_DEC(rv_text);
        RV_GENERIC_OBJECT_DEC(team_member);
        RV_GENERIC_OBJECT_DEC(rv_namespace);
        RV_GENERIC_OBJECT_DEC(task);

        typedef std::string marker;

        struct hit_part_ammo {
            float hit;
            float indirect_hit;
            float indirect_hit_range;
            float explosive;
        };

        struct hit_part_impulse {

        };

        struct hit_part_data {
            object target;
            object shooter;
            object bullet;
            vector3 position;
            vector3 velocity;
            std::vector<std::string> selections;
            r_string ammo_type;
            hit_part_ammo ammo_data;
            hit_part_impulse impulse_data;
            vector3 direction;
            float radius;
            r_string surface;
            bool direct;
        };

        struct rv_color {
            float red{ 0.f };
            float green{ 0.f };
            float blue{ 0.f };
            float alpha{ 0.f };

            operator game_value() const {
                return game_value({
                    red,
                    green,
                    blue,
                    alpha
                });
            }

            rv_color(const game_value &ret_game_value_) :
                red(ret_game_value_[0]),
                green(ret_game_value_[1]),
                blue(ret_game_value_[2]),
                alpha(ret_game_value_[3]) {}

            rv_color(float red_, float green_, float blue_, float alpha_) :
                red(red_),
                green(green_),
                blue(blue_),
                alpha(alpha_) {}
        };

        using sqf_string = std::string;
        using sqf_return_string = std::string;   //Special return type so we can have that be different than argument type
        using sqf_return_string_list = std::vector<std::string>;
        using sqf_string_list_const_ref = const std::vector<std::string>&;

        class sqf_string_const_ref {
        public:
            sqf_string_const_ref(const std::string& ref) : _var(std::string_view(ref)) {}
            sqf_string_const_ref(r_string ref) : _var(std::move(ref)) {}
            sqf_string_const_ref(const game_value& ref) : _var(r_string(ref)) {}
            sqf_string_const_ref(std::string_view ref) : _var(std::move(ref)) {}
            sqf_string_const_ref(const char* ref) : _var(std::string_view(ref)) {}
            operator std::string_view() const {
                if (std::holds_alternative<std::string_view>(_var))
                    return std::get<std::string_view>(_var);
                return std::string_view(std::get<r_string>(_var));
            }
            operator r_string() const {
                if (std::holds_alternative<r_string>(_var))
                    return std::get<r_string>(_var);
                return r_string(std::get<std::string_view>(_var));
            }
            operator game_value() const {
                if (std::holds_alternative<r_string>(_var))
                    return std::get<r_string>(_var);
                return r_string(std::get<std::string_view>(_var));
            }
            std::variant<r_string, std::string_view> _var;
        };

        //using sqf_string_const_ref = const std::string_view; //const sqf_string&;
        using sqf_string_const_ref_wrapper = std::reference_wrapper<const std::string>;



        using t_sqf_in_area_position = std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3> >;

        struct rv_particle_shape {
            std::string file;
            int ntieth = 16; //this param is a const internally
            int row;
            int column;
            int loop;

            operator game_value() {
                return game_value(std::vector<game_value>({
                    file,
                    16.0f,
                    static_cast<float>(row),
                    static_cast<float>(column),
                    static_cast<float>(loop)
                }));
            }

            operator game_value() const {
                return game_value(std::vector<game_value>({
                    file,
                    16.0f,
                    static_cast<float>(row),
                    static_cast<float>(column),
                    static_cast<float>(loop)
                }));
            }
        };
        struct rv_particle_array {
            rv_particle_shape shape;
            std::string animation_name;
            std::string type;
            float timer_period;
            float lifetime;
            vector3 position;
            vector3 move_velocity;
            float rotation_velocity;
            float weight;
            float volume;
            float rubbing;
            float size;
            std::vector<rv_color> color;
            float animation_phase;
            float rand_dir_period;
            float rand_dir_intensity;
            std::string on_timer;
            std::string before_destroy;
            object follow;
            float angle;
            bool on_surface;
            float bounce_on_surface;
            std::vector<rv_color> emissive_color;

            operator game_value() {
                std::vector<game_value> color_gv, emissive_color_gv;
                for (rv_color c : color) {
                    color_gv.push_back(c);
                }
                for (rv_color ec : emissive_color) {
                    emissive_color_gv.push_back(ec);
                }
                return game_value(std::vector<game_value>({
                    shape,
                    animation_name,
                    type,
                    timer_period,
                    lifetime,
                    position,
                    move_velocity,
                    rotation_velocity,
                    weight,
                    volume,
                    rubbing,
                    size,
                    color_gv,
                    animation_phase,
                    rand_dir_period,
                    rand_dir_intensity,
                    on_timer,
                    before_destroy,
                    follow,
                    angle,
                    on_surface,
                    bounce_on_surface,
                    emissive_color_gv
                }));
            }

            operator game_value() const {
                std::vector<game_value> color_gv, emissive_color_gv;
                for (rv_color c : color) {
                    color_gv.push_back(c);
                }
                for (rv_color ec : emissive_color) {
                    emissive_color_gv.push_back(ec);
                }
                return game_value(std::vector<game_value>({
                    shape,
                    animation_name,
                    type,
                    timer_period,
                    lifetime,
                    position,
                    move_velocity,
                    rotation_velocity,
                    weight,
                    volume,
                    rubbing,
                    size,
                    color_gv,
                    animation_phase,
                    rand_dir_period,
                    rand_dir_intensity,
                    on_timer,
                    before_destroy,
                    follow,
                    angle,
                    on_surface,
                    bounce_on_surface,
                    emissive_color_gv
                }));
            }
        };
        struct rv_particle_random {
            float lifetime;
            vector3 position;
            vector3 move_velocity;
            float rotation_velocity;
            float size;
            rv_color color;
            float random_direction_period;
            float random_direction_intensity;
            float angle;
            float bounce_on_surface;

            operator game_value() {
                return game_value(std::vector<game_value>({
                    lifetime,
                    position,
                    move_velocity,
                    rotation_velocity,
                    size,
                    color,
                    random_direction_period,
                    random_direction_intensity,
                    angle,
                    bounce_on_surface
                }));
            }

            operator game_value() const {
                return game_value(std::vector<game_value>({
                    lifetime,
                    position,
                    move_velocity,
                    rotation_velocity,
                    size,
                    color,
                    random_direction_period,
                    random_direction_intensity,
                    angle,
                    bounce_on_surface
                }));
            }
        };







        struct rv_vehicle_role {
            std::string role;
            std::vector<int> turret_path;
        };

        struct rv_hit_points_damage {
            sqf_return_string_list hit_points;
            sqf_return_string_list hit_selections;
            std::vector<float> damages;

            rv_hit_points_damage(const game_value &_gv) {
                auto _arr = _gv.to_array();
                if (_arr.count() == 3) {
                    auto _hp = _arr[0].to_array();
                    auto _hs = _arr[1].to_array();
                    auto _dmgs = _arr[2].to_array();

                    //iterator conversion didnt work
                    hit_points.reserve(_hp.count());
                    hit_selections.reserve(_hs.count());
                    damages.reserve(_dmgs.count());
                    for (auto &_x : _hp) hit_points.emplace_back(_x);
                    for (auto &_x : _hs) hit_selections.emplace_back(_x);
                    for (auto &_x : _dmgs) damages.emplace_back(_x);
                }
            }

            operator game_value() const {
                return game_value({ hit_points, hit_selections, damages });
            }
        };







        struct rv_best_place {
            vector2 pos;
            float result;

            rv_best_place(const game_value& gv) {
                if (gv.size() == 2) {
                    pos = gv[0];
                    result = gv[1];
                }
            }

            operator game_value() const {
                return game_value({ pos, result });
            }
        };
        struct rv_uav_control {
            object unit;
            std::string position;

            rv_uav_control(const game_value &ret_game_value_) :
                unit(ret_game_value_[0]),
                position(ret_game_value_[1]) {}
        };

        struct rv_model_info {
            std::string name;
            std::string path;
            bool skeleton;

            rv_model_info(const game_value &ret_game_value_) :
                name(ret_game_value_[0]),
                path(ret_game_value_[1]),
                skeleton(ret_game_value_[2]) {}
        };

        struct rv_shot_parents {
            object vehicle;
            object instigator;
        };
        struct rv_action_params {
            std::string title;
            std::string script;
            game_value arguments;
            float priority;
            bool show_window;
            bool hide_on_use;
            std::string shortcut;
            std::string condition;
            float radius;
            bool unconscious;
            std::string text_window_background;
            std::string text_window_foreground;
            std::string selection;
        };
        struct rv_target {
            vector3 position;
            std::string type;
            side side_;
            float subjective_cost;
            object object_;
            float position_accuracy;
            rv_target(vector3&& pos, const game_value& from)
            {
                position = std::move(pos);
                type = std::string(from[1]);
                side_ = from[2];
                subjective_cost = from[3];
                object_ = from[4];
                position_accuracy = from[5];
            }
        };

        struct rv_query_target {
            float accuracy;
            object target;
            side target_side;
            std::string target_type;
            vector2 target_position;
            float target_age;
        };


        struct rv_cursor_object_params
        {
            object cursor_object;
            std::string cursor_object_named_sel;
            float distance;
        };

    }
}

//custom conversion from std::string& to const std::string& inside reference_wrapper
namespace std {
    template<>
    class reference_wrapper<const std::string>
        : public reference_wrapper<std::string> {
    public:
        reference_wrapper(string& _Val) noexcept
            : reference_wrapper<std::string>(_Val) {};
    };
    
#define DEFINE_HASH_FUNCTION_FOR_CLASS(type) template <> struct hash<intercept::types::type> { \
        size_t operator()(const intercept::types::type& x) const { \
            return x.hash(); \
        } \
    }; 

    DEFINE_HASH_FUNCTION_FOR_CLASS(object)
    DEFINE_HASH_FUNCTION_FOR_CLASS(location)
    DEFINE_HASH_FUNCTION_FOR_CLASS(group)
    DEFINE_HASH_FUNCTION_FOR_CLASS(config)
    DEFINE_HASH_FUNCTION_FOR_CLASS(control)
    DEFINE_HASH_FUNCTION_FOR_CLASS(display)
    DEFINE_HASH_FUNCTION_FOR_CLASS(side)
    DEFINE_HASH_FUNCTION_FOR_CLASS(task)
}

