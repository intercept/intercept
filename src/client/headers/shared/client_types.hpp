#pragma once
#include "types.hpp"
#include <variant>

namespace intercept::types {

class internal_object : public game_value {
    public:
        internal_object();
        internal_object(const game_value &value_);
        internal_object(const internal_object &copy_);
        internal_object(internal_object &&move_) noexcept;
        internal_object & operator = (internal_object &&move_) noexcept;

        internal_object & operator = (const internal_object &copy_);

        bool operator<(const internal_object& compare_) const;
        bool operator>(const internal_object& compare_) const;
    };

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

        //#TODO make a typedef for std::vector and let it be replaced by auto_array for using engine types
#ifdef INTERCEPT_SQF_STRTYPE_RSTRING
    using sqf_string = r_string;
    using sqf_return_string = r_string;  //Special return type so we can have that be different than argument type
    using sqf_return_string_list = std::vector<r_string>;
    using sqf_string_list_const_ref = const std::vector<r_string> &;

    using sqf_string_const_ref_wrapper = std::reference_wrapper<const r_string>;
#else
    using sqf_string = std::string;
    using sqf_return_string = std::string;  //Special return type so we can have that be different than argument type
    using sqf_return_string_list = std::vector<std::string>;
    using sqf_string_list_const_ref = const std::vector<std::string> &;

    //using sqf_string_const_ref = const std::string_view; //const sqf_string&;
    using sqf_string_const_ref_wrapper = std::reference_wrapper<const std::string>;
#endif

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
        sqf_return_string_list selections;
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

          rv_color() = default;

          explicit rv_color(const game_value &ret_game_value_) :
              red(ret_game_value_[0]),
              green(ret_game_value_[1]),
              blue(ret_game_value_[2]),
              alpha(ret_game_value_[3]) {}

        rv_color(float red_, float green_, float blue_, float alpha_) noexcept :
            red(red_),
            green(green_),
            blue(blue_),
            alpha(alpha_) {}
    };


    class sqf_string_const_ref {
    public:
        sqf_string_const_ref(const std::string& ref) noexcept : _var(std::string_view(ref)) {}
        sqf_string_const_ref(r_string ref) noexcept : _var(std::move(ref)) {}
        sqf_string_const_ref(const game_value& ref) : _var(r_string(ref)) {}
        sqf_string_const_ref(std::string_view ref) noexcept : _var(ref) {}
        sqf_string_const_ref(const char* ref) noexcept : _var(std::string_view(ref)) {}
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

    using t_sqf_in_area_position = std::variant<std::reference_wrapper<const object>, std::reference_wrapper<const vector2>, std::reference_wrapper<const vector3> >;

    struct rv_particle_shape {
        std::string file;
        int ntieth;
        int index;
        int count;
        int loop;

        operator game_value() {
            return game_value(std::vector<game_value>({
                file,
                static_cast<float>(ntieth),
                static_cast<float>(index),
                static_cast<float>(count),
                static_cast<float>(loop)
            }));
        }

        operator game_value() const {
            return game_value(std::vector<game_value>({
                file,
                static_cast<float>(ntieth),
                static_cast<float>(index),
                static_cast<float>(count),
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
        std::vector<float> size;
        std::vector<rv_color> color;
        std::vector<float> animation_speed;
        float rand_dir_period;
        float rand_dir_intensity;
        std::string on_timer;
        std::string before_destroy;
        object follow;
        float angle;
        bool on_surface;
        float bounce_on_surface;
        std::vector<rv_color> emissive_color;

        operator game_value() const {
            std::vector<game_value> color_gv, emissive_color_gv,
                size_gv, animation_speed_gv;
            for (const auto& c : color) {
                color_gv.push_back(c);
            }
            for (const auto& ec : emissive_color) {
                emissive_color_gv.push_back(ec);
            }
            for (const auto& s : size)
                size_gv.push_back(s);
            for (const auto& a : animation_speed)
                animation_speed_gv.push_back(a);
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
                size_gv,
                color_gv,
                animation_speed_gv,
                rand_dir_period,
                rand_dir_intensity,
                on_timer,
                before_destroy,
                static_cast<game_value>(follow),
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


    struct rv_hit_points_damage {
        sqf_return_string_list hit_points;
        sqf_return_string_list hit_selections;
        std::vector<float> damages;

        explicit rv_hit_points_damage(const game_value& _gv);

        operator game_value() const {
            return game_value({ hit_points, hit_selections, damages });
        }
    };


    //#TODO replace by just returning a pair? Can game_value initialize from pair or tuple?
    struct rv_best_place {
        vector2 pos;
        float result = -1;

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
        sqf_string position;

        explicit rv_uav_control(const game_value &ret_game_value_) :
            unit(ret_game_value_[0]),
            position(ret_game_value_[1]) {}
    };

    struct rv_model_info {
        sqf_string name;
        sqf_string path;
        vector3 placing_point;
        bool skeleton;

        explicit rv_model_info(const game_value &ret_game_value_)
            : name(ret_game_value_[0]),
              path(ret_game_value_[1]),
              skeleton(ret_game_value_[2]),
              placing_point(ret_game_value_[3]) {}
    };

    struct rv_shot_parents {
        object vehicle;
        object instigator;
    };
    struct rv_action_params {
        sqf_string title;
        sqf_string script;
        game_value arguments;
        float priority;
        bool show_window;
        bool hide_on_use;
        sqf_string shortcut;
        sqf_string condition;
        float radius;
        bool unconscious;
        sqf_string text_window_background;
        sqf_string text_window_foreground;
        sqf_string selection;
    };
    struct rv_target {
        vector3 position;
        sqf_string type;
        side side_;
        float subjective_cost;
        object object_;
        float position_accuracy;
        rv_target(const game_value& from)
        {
            position = from[0];
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
        sqf_string target_type;
        vector2 target_position;
        float target_age;
    };


    struct rv_cursor_object_params
    {
        object cursor_object;
        sqf_string cursor_object_named_sel;
        float distance;
    };

    class rv_turret_path {
        game_value pathRaw;
    public:
        explicit rv_turret_path (game_value path) noexcept : pathRaw(std::move(path)) {}

        explicit operator std::vector<float>() const {
            if (pathRaw.type_enum() != game_data_type::ARRAY) return std::vector<float>();
            std::vector<float> ret(pathRaw.to_array().begin(), pathRaw.to_array().end());
            return ret;

        }
        operator game_value() const {return pathRaw;}

    };

    struct rv_vehicle_role {
        sqf_string role;
        rv_turret_path turret_path{ game_value() };
    };
    using marker = sqf_return_string;

    /**
     * \brief A Deallocation Threadsafe variant of game_value.
     * \description When going out of scope it doesn't deallocate the data immediately but instead stores it
     * till game_value_threadsafe::garbage_collect() is called.
     */
    class game_value_threadsafe : public game_value {
    public:

        static void garbage_collect();

        ~game_value_threadsafe();
        game_value_threadsafe(const game_value& copy) : game_value(copy) {}
        //Move constructor should never have data before it's assigned.
        game_value_threadsafe(game_value&& move_) noexcept : game_value(move_) {}

        //allocations


        game_value_threadsafe(float val_);
        game_value_threadsafe(int val_);
        game_value_threadsafe(size_t val_);
        game_value_threadsafe(bool val_);
        game_value_threadsafe(const std::string &val_);
        game_value_threadsafe(const r_string &val_);
        game_value_threadsafe(std::string_view val_);
        game_value_threadsafe(const char* str_) : game_value(std::string_view(str_)) {}
        game_value_threadsafe(const std::vector<game_value> &list_);
        game_value_threadsafe(const std::initializer_list<game_value> &list_);
        game_value_threadsafe(auto_array<game_value> &&array_);
        template<class Type>
        game_value_threadsafe(const auto_array<Type>& array_) {
            static_assert(std::is_convertible<Type, game_value>::value);
        }
        template<class Type>
        game_value_threadsafe(const std::vector<Type>& array_) : game_value(std::move(auto_array<game_value>(array_.begin(), array_.end()))) {
            static_assert(std::is_convertible<Type, game_value>::value);
        }
        game_value_threadsafe(const vector3 &vec_);
        game_value_threadsafe(const vector2 &vec_);
        game_value_threadsafe(const internal_object &internal_);

        game_value_threadsafe & operator = (const game_value &copy_);
        game_value_threadsafe & operator = (game_value &&move_) noexcept;
        game_value_threadsafe & operator = (float val_);
        game_value_threadsafe & operator = (bool val_);
        game_value_threadsafe & operator = (const std::string &val_);
        game_value_threadsafe & operator = (const r_string &val_);
        game_value_threadsafe & operator = (std::string_view val_);
        game_value_threadsafe & operator = (const char* str_) {
            return this->operator =(std::string_view(str_));
        }
        game_value_threadsafe & operator = (const std::vector<game_value> &list_);
        game_value_threadsafe & operator = (const vector3 &vec_);
        game_value_threadsafe & operator = (const vector2 &vec_);
        game_value_threadsafe & operator = (const internal_object &internal_);
    private:
        static void discard(ref<game_data> && data);
    };

}

namespace intercept {
    namespace sqf {
        enum class rv_selection_lods {
            Memory,
            Geometry,
            FireGeometry,
            LandContact,
            HitPoints,
            ViewGeometry
        };

        enum object_types {
            obj_type_primary = 1,
            obj_type_network = 2,
            obj_type_temporary = 4,
            obj_type_vehicle = 8,
            obj_type_temp_veh = 16,
            obj_type_land_decal = 32,
            obj_type_all = 63,
            obj_type_all_inc_null = -1
        };
#ifdef DEFINE_ENUM_FLAG_OPERATORS
        DEFINE_ENUM_FLAG_OPERATORS(object_types)
#endif

        enum class object_simulation_kind {
            Statics = 0,
            Slow = 0,
            Vehicles = 1,
            Normal = 1,
            Projectiles = 2,
            Fast = 2,
            Cloudlets = 3,
            Holders = 4,
            Out = 4,
            Animals = 5,
            Mines = 6,
            TriggersMap = 7,
            VehiclesMap = 8
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
            return x.get_hash(); \
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

