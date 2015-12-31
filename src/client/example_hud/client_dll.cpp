#include <Windows.h>
#include <stdio.h>
#include <cstdint>
#include <atomic>
#include <memory>

#include "intercept.hpp"
#include "logging.hpp"
#include "client\client.hpp"
#include "client\pointers.hpp"
#include "client\sqf\uncategorized.hpp"

#define PI 3.14159265f

#define DEG(x) (x * 180.0f / PI)
#define RAD(x) (x / 180.0f * PI)

using namespace intercept;

INITIALIZE_EASYLOGGINGPP

int __cdecl intercept::api_version() {
    return 1;
}

vector2 ace_hud_pos;
vector3 ace_hud_size;
sqf::rv_color ace_hud_color;
std::string ace_hud_color_string;

class line_base {
public:
    int type;
    line_base(int type_) : type(type_) {}
};

class line_straight : public line_base {
public:
    vector2 pos1;
    vector2 pos2;
    line_straight(int type_, vector2 pos1_, vector2 pos2_) : line_base(type_), pos1(pos1_), pos2(pos2_) {};
};

class line_text : public line_base {
public:
    vector2 pos;
    std::string text;
    float text_size;
    std::string text_align;
};

class line_circle : public line_base {
public:
    vector2 pos;
    float size;
    line_circle(int type_, vector2 pos_, float size_) : line_base(type_), pos(pos_), size(size_) {}
};

class line_dashed : public line_straight {
public:
    float spacing;
};

std::vector<std::shared_ptr<line_base>> lines_to_render;

void draw_hud() {
    //_ctrlMap = nil;
    //with uiNamespace do {
    //    _ctrlMap = GVAR(ctrlMap);
    //};
    control ctrl_map(sqf::get_variable(sqf::ui_namespace(), "ace_airhud_ctrlMap"));
    object vehicle = sqf::vehicle(sqf::player());
    //_mUl = (GVAR(vehicle) selectionPosition "HUD_top_left");
    //_mLl = (GVAR(vehicle) selectionPosition "HUD_bottom_left");
    //_mUr = (GVAR(vehicle) selectionPosition "HUD_top_right");

    vector3 m_ul, m_ll, m_ur;
    m_ul = sqf::selection_positon(vehicle, "HUD_top_left");
    m_ll = sqf::selection_positon(vehicle, "HUD_bottom_left");
    m_ur = sqf::selection_positon(vehicle, "HUD_top_right");

    //_center = _mLl vectorAdd((_mUr vectorDiff _mLl) vectorMultiply 0.5);
    vector3 center = m_ll + ((m_ur - m_ll) * 0.5f);


    //_wUl = (GVAR(vehicle) modelToWorldVisual _mUl);
    //_wLl = (GVAR(vehicle) modelToWorldVisual _mLl);
    //_wUr = (GVAR(vehicle) modelToWorldVisual _mUr);
    vector3 w_ul, w_ll, w_ur;
    w_ul = sqf::model_to_world_visual(vehicle, m_ul);
    w_ll = sqf::model_to_world_visual(vehicle, m_ll);
    w_ur = sqf::model_to_world_visual(vehicle, m_ur);

    //_ul = worldToScreen _wUl;
    //_ll = worldToScreen _wLl;
    //_ur = worldToScreen _wUr;
    //if (count _ul == 0 || count _ll == 0 || count _ur == 0) exitWith{};
    vector2 ul, ll, ur;
    bool is_ok;
    ul = sqf::world_to_screen(w_ul, is_ok);
    if (!is_ok)
        return;
    ll = sqf::world_to_screen(w_ll, is_ok);
    if (!is_ok)
        return;
    ur = sqf::world_to_screen(w_ur, is_ok);
    if (!is_ok)
        return;

    //_width = (_ur select 0) - (_ul select 0);
    //_height = (_ll select 1) - (_ul select 1);
    //_coef = _height;

    float width = ur.x - ul.x;
    float height = ll.y - ul.y;
    float coef = height;

    //_ctrlMap ctrlSetPosition[_ul select 0, _ul select 1, _width, _height];
    sqf::ctrl_set_position(ctrl_map, ul.x, ul.y, width, height);

    //_ctrlMap ctrlCommit 0;
    sqf::ctrl_commit(ctrl_map, 0.0f);

    //_ctrlMap ctrlMapAnimAdd[0, 0.001, [21, 21]];
    sqf::ctrl_map_anim_add(ctrl_map, 0, 0.001f, vector2(21, 21));

    //ctrlMapAnimCommit _ctrlMap;
    sqf::ctrl_map_anim_commit(ctrl_map);


    //_infiniteDir = (_mUl vectorFromTo _mUr) vectorCrossProduct(_mUl vectorFromTo _mLl);
    vector3 infinite_dir = (m_ur - m_ul).cross(m_ll - m_ul);

    //_infinitePos = _center vectorAdd(_infiniteDir vectorMultiply 5000);
    vector3 infinite_pos = center + (infinite_dir * 5000.0f);

    //_infinitePosWorld = GVAR(vehicle) modelToWorldVisual _infinitePos;
    vector3 infinite_pos_world = sqf::model_to_world_visual(vehicle, infinite_pos);

    //_infinitePosScreen = worldToScreen _infinitePosWorld;
    //if (count _infinitePosScreen == 0) exitWith{};
    vector2 infinite_pos_screen = sqf::world_to_screen(infinite_pos_world, is_ok);
    if (!is_ok)
        return;

    
    //_infinitePosHudCanvas = _ctrlMap ctrlMapScreenToWorld _infinitePosScreen;
    vector2 infinite_pos_hud_canvas = sqf::ctrl_map_screen_to_world(ctrl_map, infinite_pos_screen);



    //_ul = _ctrlMap ctrlMapScreenToWorld _ul;
    //_ll = _ctrlMap ctrlMapScreenToWorld _ll;
    //_ur = _ctrlMap ctrlMapScreenToWorld _ur;
    ul = sqf::ctrl_map_screen_to_world(ctrl_map, ul);
    ll = sqf::ctrl_map_screen_to_world(ctrl_map, ll);
    ur = sqf::ctrl_map_screen_to_world(ctrl_map, ur);

    //_width = (_ur select 0) - (_ul select 0);
    //_height = (_ul select 1) - (_ll select 1);
    width = ur.x - ul.x;
    height = ul.y - ll.y;

    //GVAR(hudPos) = _ll;
    ace_hud_pos = ll;
    //_wh = [_width, _height, 0];
    //if (_width <= 0 || _height <= 0) exitWith{};
    if (width <= 0 || height <= 0)
        return;
    //GVAR(hudSize) = _wh;
    ace_hud_size = vector3(width, height, 0.0f);

    //_negHalfWidth = _width*-0.5;
    //_negHalfHeight = _height*-0.5;
    float neg_half_width = width * -0.5f;
    float neg_half_height = height * -0.5f;
    

    //_offset = _infinitePosHudCanvas;
    vector2 offset = infinite_pos_hud_canvas;
    //_nhw = _negHalfWidth;
    //_nhh = _negHalfHeight;

    float nhw = neg_half_width;
    float nhh = neg_half_height;
    for (auto line : lines_to_render) {
        int type = line->type;
        //    if (_type < 0) then{
        if (type < 0) {
            //        _offset = _ll;
            offset = ll;
            //    _nhw = 0;
            //    _nhh = 0;
            nhw = 0;
            nhh = 0;
            //    _type = abs _type;
            type = std::abs(type);
        }

        //    }
        //    else {
        //        _offset = _infinitePosHudCanvas;
        //        _nhw = _negHalfWidth;
        //        _nhh = _negHalfHeight;
        //    };
        else {
            offset = infinite_pos_hud_canvas;
            nhw = neg_half_width;
            nhh = neg_half_height;
        }
        switch (type) {
        case 1: {

            //        _pos1 = _x select 1;
            //        _pos2 = _x select 2;
            //        _pos1offset = [_nhw + (_pos1 select 0) * _width, _nhh + (_pos1 select 1) * _height, 0];
            //        _pos2offset = [_nhw + (_pos2 select 0) * _width, _nhh + (_pos2 select 1) * _height, 0];
            vector2 pos1_offset(nhw + ((line_straight *)line.get())->pos1.x * width, nhh + ((line_straight *)line.get())->pos1.y * height);
            vector2 pos2_offset(nhw + ((line_straight *)line.get())->pos2.x * width, nhh + ((line_straight *)line.get())->pos2.y * height);

            //        _size = (_pos1offset vectorDistance _pos2offset)*0.5;
            float size = pos1_offset.distance(pos2_offset) * 0.5f;
            //        _vectorDir = _pos1offset vectorFromTo _pos2offset;
            vector2 vector_dir = (pos2_offset - pos1_offset).normalize();
            //        _centerPos = _pos1offset vectorAdd(_vectorDir vectorMultiply _size);
            vector2 center_pos = pos1_offset + (vector_dir * size);

            //        _ctrlMap drawRectangle[
            //            _offset vectorAdd _centerPos,
            //                0.0025*_height,
            //                _size,
            //                (_vectorDir select 0) atan2(_vectorDir select 1),
            //                [1, 1, 1, 1],
            //                _hudColorString
            //        ];
            sqf::draw_rectangle(ctrl_map, offset + center_pos, 0.0025f*height, size, DEG(std::atan2(vector_dir.x, vector_dir.y)), sqf::rv_color{ 1, 1, 1, 1 }, ace_hud_color_string);
            break;
        }
        case 2: {
            //        _pos1offset = [_nhw + (_pos1 select 0) * _width, _nhh + (_pos1 select 1) * _height, 0];
            vector2 pos_offset(nhw + ((line_text *)line.get())->pos.x * width, nhh + ((line_text *)line.get())->pos.y * height);

            //        _ctrlMap drawIcon[
            //            '\a3\ui_f\data\IGUI\Cfg\Actions\clear_empty_ca.paa',
            //                _hudColor,
            //                _offset vectorAdd _pos1offset,
            //                5 * _height,
            //                5 * _height,
            //                0,
            //                _x select 2,
            //                0,
            //                (_x select 3)*_height,
            //                'EtelkaNarrowMediumPro',
            //                _x select 4
            //        ];
            sqf::draw_icon(ctrl_map, "\\a3\\ui_f\\data\\IGUI\\Cfg\\Actions\\clear_empty_ca.paa",
                ace_hud_color,
                offset + pos_offset,
                5.0f * height,
                5.0f * height,
                0.0f,
                ((line_text *)line.get())->text,
                0,
                ((line_text *)line.get())->text_size,
                "EtelkaNarrowMediumPro",
                ((line_text *)line.get())->text_align
                );
            break;
        }
        case 3: {
            //        _pos1 = _x select 1;
            //        _pos1offset = [_nhw + (_pos1 select 0) * _width, _nhh + (_pos1 select 1) * _height, 0];
            vector2 pos_offset = vector2(nhw + ((line_circle *)line.get())->pos.x * width, nhh + ((line_circle *)line.get())->pos.y * height);
            //        _a = (_x select 2) * _height;
            float a = ((line_circle *)line.get())->size * height;
            //        _circ = 2 * pi*_a;
            float circ = 2.0f * PI * a;
            //        _segLength = (_circ / 16) / 1.9;
            float seg_length = (circ / 16.0f) / 1.9f;
            //        for "_i" from 0 to 15 do {
            for (uint32_t i = 0; i <= 15; ++i) {
                //            _dir = (360 / 16)*_i;
                float dir = (360.0f / 16.0f) * (float)i;
                //            _add = [_a*sin _dir, _a*cos _dir, 0];
                vector2 add(a * std::sin(RAD(dir)), a * std::cos(RAD(dir)));
                //            _segPos = _pos1offset vectorAdd _add;
                vector2 seg_pos = pos_offset + add;
                //            _ctrlMap drawRectangle[
                //                _offset vectorAdd _segPos,
                //                    _segLength,
                //                    0.0025*_height,

                //                    _dir,
                //                    [1, 1, 1, 1],
                //                    _hudColorString
                //            ];
                sqf::draw_rectangle(ctrl_map, offset + seg_pos, seg_length, 0.0025f*height, dir, sqf::rv_color{ 1,1,1,1 }, ace_hud_color_string);
            }
            break;
        }
        case 4: {
            //        _pos1 = _x select 1;
            //        _pos2 = _x select 2;
            //        _pos1offset = [_nhw + (_pos1 select 0) * _width, _nhh + (_pos1 select 1) * _height, 0];
            //        _pos2offset = [_nhw + (_pos2 select 0) * _width, _nhh + (_pos2 select 1) * _height, 0];
            vector2 pos1_offset(nhw + ((line_dashed *)line.get())->pos1.x * width, nhh + ((line_dashed *)line.get())->pos1.y * height);
            vector2 pos2_offset(nhw + ((line_dashed *)line.get())->pos2.x * width, nhh + ((line_dashed *)line.get())->pos2.y * height);
            //        _size = (_pos1offset vectorDistance _pos2offset);
            float size = pos1_offset.distance(pos2_offset);
            //        _vectorDir = _pos1offset vectorFromTo _pos2offset;
            vector2 vector_dir = (pos2_offset - pos1_offset).normalize();

            //        _dashSpacing = (_x select 3) * _width;
            float dash_spacing = ((line_dashed *)line.get())->spacing * width;
            //        _chunks = floor(_size / (_dashSpacing * 2));
            uint32_t chunks = (uint32_t)std::floor(size / (dash_spacing * 2.0f));
            //        _dir = (_vectorDir select 0) atan2(_vectorDir select 1);
            float dir = DEG(std::atan2(vector_dir.x, vector_dir.y));
            //        for "_i" from 0 to _chunks do {
            for (uint32_t i = 0; i <= chunks; ++i) {
                //            _centerPos = _pos1offset vectorAdd(_vectorDir vectorMultiply(((_dashSpacing * 2)*_i) - (_dashSpacing / 4)));
                vector2 center_pos = pos1_offset + (vector_dir * ((dash_spacing * 2.0f * (float)i) - (dash_spacing / 4.0f)));
                //            _ctrlMap drawRectangle[
                //                _offset vectorAdd _centerPos,
                //                    0.0025*_height,
                //                    _dashSpacing / 2,
                //                    _dir,
                //                    [1, 1, 1, 1],
                //                    _hudColorString
                //            ];
                sqf::draw_rectangle(ctrl_map,
                    offset + center_pos,
                    0.0025f * height,
                    dash_spacing / 2.0f,
                    dir,
                    sqf::rv_color{ 1,1,1,1 },
                    ace_hud_color_string);
            }
            break;
        }
        }
    }
}

inline float clamp(float x, float a, float b) {
    return x < a ? a : (x > b ? b : x);
}

vector2 world_to_hud_constrained(const control &map_, const vector3 &world_pos_) {
    //_wp = worldToScreen(ASLtoATL _this);
    bool is_ok;
    vector2 wp = sqf::world_to_screen(world_pos_, is_ok);
    if (is_ok) {
        //    _hp = _ctrlMap ctrlMapScreenToWorld _wp;
        vector2 hp = sqf::ctrl_map_screen_to_world(map_, wp);
        //_diff = _hp vectorDiff GVAR(hudPos);
        vector2 diff = hp - ace_hud_pos;
        
        //[((_diff select 0) / (GVAR(hudSize) select 0)) max 0 min 1, ((_diff select 1) / (GVAR(hudSize) select 1)) max 0 min 1];
        return vector2(clamp(diff.x / ace_hud_size.x, 0.0f, 1.0f), clamp(diff.y / ace_hud_size.y, 0.0f, 1.0f));
    }
    return vector2(-1000, -1000);
}

void calculate_hud() {
    control ctrl_map(sqf::get_variable(sqf::ui_namespace(), "ace_airhud_ctrlMap"));
    //// if(diag_tickTime < GVAR(delta)) exitWith {};
    //// GVAR(delta) = diag_tickTime + 1/5;
    //_vehicle = GVAR(vehicle);
    object vehicle = sqf::vehicle(sqf::player());

    //_vehicleVector = vectorDir _vehicle;
    vector3 vehicle_vector = sqf::vector_dir(vehicle);

    //_vehicleVector2d = +_vehicleVector;
    //_vehicleVector2d set[2, 0];
    //_vehicleVector2d = vectorNormalized _vehicleVector2d;
    vector3 vehicle_vector_2d = vehicle_vector;
    vehicle_vector_2d.z = 0.0f;
    vehicle_vector_2d = vehicle_vector_2d.normalize();

    //_mUl = (GVAR(vehicle) selectionPosition "HUD_top_left");
    //_mLl = (GVAR(vehicle) selectionPosition "HUD_bottom_left");
    //_mUr = (GVAR(vehicle) selectionPosition "HUD_top_right");
    vector3 m_ul, m_ll, m_ur;
    m_ul = sqf::selection_positon(vehicle, "HUD_top_left");
    m_ll = sqf::selection_positon(vehicle, "HUD_bottom_left");
    m_ur = sqf::selection_positon(vehicle, "HUD_top_right");

    //_center = _mLl vectorAdd((_mUr vectorDiff _mLl) vectorMultiply 0.5);
    vector3 center = m_ll + ((m_ur - m_ll) * 0.5f);
    
    //_vehiclePos = getPosASL _vehicle; //ATLtoASL (_vehicle modelToWorldVisual _center);
    vector3 vehicle_pos = sqf::get_pos_asl(vehicle);

    //_vehiclePos2d = +_vehiclePos;
    vector2 vehicle_pos_2d = vector2(vehicle_pos.x, vehicle_pos.y);


    //GVAR(lines) = [];
    lines_to_render.clear();
    //std::vector

    //_velocityVectorPos = _vehiclePos vectorAdd((vectorNormalized(velocity _vehicle)) vectorMultiply 5000);
    vector3 velocity_vector_pos = vehicle_pos + (sqf::velocity(vehicle).normalize() * 5000.0f);

    //_fpmHud = _velocityVectorPos call FUNC(worldToHudConstrained);
    vector2 fpm_hud = world_to_hud_constrained(ctrl_map, velocity_vector_pos);

    //_wpPos = (getPosASL trucky);
    vector3 wp_pos = sqf::get_pos_asl(object(sqf::get_variable(sqf::mission_namespace(), "trucky")));
    //_wpPos2d = +_wpPos;
    vector2 wp_pos_2d = vector2(wp_pos.x, wp_pos.y);
    //_wpPos2d set[2, 0];
    //drawIcon3D["\a3\ui_f\data\IGUI\Cfg\Cursors\selectover_ca.paa", [1, 1, 1, 1], ASLtoATL _wpPos, 0.75, 0.75, 0, "UR", 0.5, 0.025, "TahomaB"];
    sqf::draw_icon_3d("\\a3\\ui_f\\data\\IGUI\\Cfg\\Cursors\\selectover_ca.paa", sqf::rv_color{ 1,1,1,1 }, sqf::asl_to_atl(wp_pos), 0.75f, 0.75f, 0.0f, "UR", 0.5f, 0.025f, "TahomaB");
    //_wpVector = _vehiclePos2d vectorFromTo _wpPos2d;
    vector2 wp_vector = (vehicle_pos_2d - wp_pos_2d).normalize();
    //_wpDir = (_wpVector select 0) atan2(_wpVector select 1);
    float wp_dir = DEG(std::atan2(wp_vector.x, wp_vector.y));
    //_vDir = (_vehicleVector select 0) atan2(_vehicleVector select 1);
    float v_dir = DEG(std::atan2(vehicle_vector.x, vehicle_vector.y));
    //_wpRDir = _vDir - _wpDir;
    float wp_r_dir = v_dir - wp_dir;
    //if (_wpRDir > 180) then{
    //    _wpRDir = _wpRDir - 360;
    //};
    //if (_wpRDir < -180) then{
    //    _wpRDir = _wpRDir + 360;
    //};
    //_wpRDir = _wpRDir * -1;
    if (wp_r_dir > 180.0f)
        wp_r_dir -= 360.0f;
    if (wp_r_dir < -180.0f)
        wp_r_dir += 360.0f;
    wp_r_dir *= -1.0f;


    //_tadPolePos = +_fpmHud;
    vector2 tad_pole_pos = fpm_hud;

    //_tadPolePos set[0, (_tadPolePos select 0) + (0.5*(_wpRDir / 180))];
    tad_pole_pos.x += 0.5f*(wp_r_dir / 180.0f);

    //GVAR(lines) pushBack[-3, _tadPolePos, 0.016, 0.016];
    lines_to_render.push_back(std::make_shared<line_circle>(-3, tad_pole_pos, 0.016f));

    //_vec = [sin _wpRDir, cos _wpRDir, 0];
    vector2 vec(std::sin(RAD(wp_r_dir)), std::cos(RAD(wp_r_dir)));

    //_tailPos1 = _tadPolePos vectorAdd(_vec vectorMultiply 0.016);
    vector2 tail_pos1 = tad_pole_pos + (vec * 0.016f);

    //_tailPos2 = _tadPolePos vectorAdd(_vec vectorMultiply 0.05);
    vector2 tail_pos2 = tad_pole_pos + (vec * 0.05f);

    //GVAR(lines) pushBack[-1, _tailPos1, _tailPos2];
    lines_to_render.push_back(std::make_shared<line_straight>(-1, tail_pos1, tail_pos2));

    //GVAR(lines) pushBack[-3, _fpmHud, 0.02, 0.02];
    //GVAR(lines) pushBack[-1, _fpmHud vectorAdd[0.02, 0, 0], _fpmHud vectorAdd[0.05, 0, 0]];
    //GVAR(lines) pushBack[-1, _fpmHud vectorAdd[-0.02, 0, 0], _fpmHud vectorAdd[-0.05, 0, 0]];
    //GVAR(lines) pushBack[-1, _fpmHud vectorAdd[0, 0.02, 0], _fpmHud vectorAdd[0, 0.04, 0]];

    //_pb = _vehicle call BIS_fnc_getPitchBank;
    //_bank = _pb select 1;

    //_centerPos = [0.5, 0.2, 0];

    //for "_i" from 135 to 225 step 5 do {
    //    if ((_i == 135 || _i == 225 || _i % 10 == 0) && (_i != 140 && _i != 220)) then{
    //        _vec = [(sin _i), (cos _i), 0];
    //    _notchStart = _centerPos vectorAdd(_vec vectorMultiply 0.15);
    //    _notchEnd = nil;
    //    if (_i >= 160 && _i <= 200 && _i != 180) then{
    //        _notchEnd = _centerPos vectorAdd(_vec vectorMultiply 0.18);
    //    }
    //    else {
    //        _notchEnd = _centerPos vectorAdd(_vec vectorMultiply 0.192);
    //    };
    //    GVAR(lines) pushBack[1, _notchStart, _notchEnd];
    //    };
    //};
    //_bankDraw = (_bank + 180) max 135 min 225;

    //_vec1 = [(sin _bankDraw), (cos _bankDraw), 0];
    //_vec2 = [(sin(_bankDraw + 2.5)), (cos(_bankDraw + 2.5)), 0];
    //_vec3 = [(sin(_bankDraw - 2.5)), (cos(_bankDraw - 2.5)), 0];

    //_t1 = _centerPos vectorAdd(_vec1 vectorMultiply 0.192);
    //_t2 = _centerPos vectorAdd(_vec2 vectorMultiply 0.21);
    //_t3 = _centerPos vectorAdd(_vec3 vectorMultiply 0.21);

    //GVAR(lines) pushBack[1, _t1, _t2];
    //GVAR(lines) pushBack[1, _t1, _t3];
    //GVAR(lines) pushBack[1, _t3, _t2];



    //// player sideChat format["b: %1", _bankDraw];




    //_pitch = _pb select 0;
    //_bank = (90 - _bank);
    //_bank2 = (270 + _bank);
    //_vec = [sin _bank, cos _bank, 0];
    //_vec2 = [sin _bank2, cos _bank2, 0];
    //_dir = getDir _vehicle;
    //_pitch0pos = _vehiclePos vectorAdd([5000, _dir, 0] call cba_fnc_polar2vect);

    //_pitch0HudPos = _pitch0pos call FUNC(worldToHud);
    //_pitch0HudPos set[2, 0];


    //_pitchBase = _pitch - (_pitch % 5) - 10;
    //for "_i" from _pitchBase to _pitchBase + 20 step 5 do {
    //    _drawPitch = _i;
    //    if (_drawPitch > 90) then{
    //        _drawPitch = _drawPitch - 180;
    //    }
    //    else {
    //        if (_drawPitch < -90) then{
    //            _drawPitch = _drawPitch + 180;
    //        };
    //    };
    //    if (_i != -90 && _i != 90) then{
    //        if (_drawPitch < 0) then{
    //            _pitchpos = _vehiclePos vectorAdd([5000, _dir, _drawPitch] call cba_fnc_polar2vect);
    //    _vbank1 = _bank + (0 + (_drawPitch*0.41));
    //    _vbank2 = _bank - (0 + (_drawPitch*0.41));
    //    _vec3 = [sin _vbank1, cos _vbank1, 0];
    //    _vec4 = [sin _vbank2, cos _vbank2, 0];
    //    _pitchposhud = _pitchpos call FUNC(worldToHud);
    //    _pitchposhud set[2, 0];
    //    // _pitch0HudPos set[1, _fpmHud select 1];
    //    // player sideChat format["f: %1", _pitchposhud];
    //    _rbank1 = _pitchposhud vectorAdd(_vec vectorMultiply 0.05);
    //    _rbank2 = _pitchposhud vectorAdd(_vec4 vectorMultiply 0.15);
    //    _lbank1 = _pitchposhud vectorAdd(_vec vectorMultiply - 0.05);
    //    _lbank2 = _pitchposhud vectorAdd(_vec3 vectorMultiply - 0.15);

    //    _rbank3 = _rbank1 vectorAdd(_vec2 vectorMultiply 0.03);
    //    _lbank3 = _lbank1 vectorAdd(_vec2 vectorMultiply 0.03);

    //    _llabel = _lbank2 vectorAdd(_vec2 vectorMultiply 0.03);
    //    _llabel = _llabel vectorAdd(_vec vectorMultiply 0.018);

    //    _rlabel = _rbank2 vectorAdd(_vec2 vectorMultiply 0.03);
    //    _rlabel = _rlabel vectorAdd(_vec vectorMultiply - 0.018);


    //    GVAR(lines) pushBack[-4, _rbank2, _rbank1, 0.01];
    //    GVAR(lines) pushBack[-1, _rbank1, _rbank3, 0.01];
    //    GVAR(lines) pushBack[-2, _rlabel, (str abs _drawPitch), 0.01, "center"];

    //    GVAR(lines) pushBack[-4, _lbank2, _lbank1, 0.01];
    //    GVAR(lines) pushBack[-1, _lbank1, _lbank3, 0.01];
    //    GVAR(lines) pushBack[-2, _llabel, (str abs _drawPitch), 0.01, "center"];
    //        }
    //        else {
    //            if (_drawPitch > 0) then{
    //                _pitchpos = _vehiclePos vectorAdd([5000, _dir, _drawPitch] call cba_fnc_polar2vect);
    //            _pitchposhud = _pitchpos call FUNC(worldToHud);
    //            _pitchposhud set[2, 0];
    //            _rbank1 = _pitchposhud vectorAdd(_vec vectorMultiply 0.05);
    //            _rbank2 = _pitchposhud vectorAdd(_vec vectorMultiply 0.15);
    //            _lbank1 = _pitchposhud vectorAdd(_vec vectorMultiply - 0.05);
    //            _lbank2 = _pitchposhud vectorAdd(_vec vectorMultiply - 0.15);

    //            _rbank3 = _rbank1 vectorAdd(_vec2 vectorMultiply - 0.03);
    //            _lbank3 = _lbank1 vectorAdd(_vec2 vectorMultiply - 0.03);

    //            _llabel = _lbank2 vectorAdd(_vec2 vectorMultiply - 0.03);
    //            _llabel = _llabel vectorAdd(_vec vectorMultiply 0.018);

    //            _rlabel = _rbank2 vectorAdd(_vec2 vectorMultiply - 0.03);
    //            _rlabel = _rlabel vectorAdd(_vec vectorMultiply - 0.018);


    //            GVAR(lines) pushBack[-1, _rbank1, _rbank2];
    //            GVAR(lines) pushBack[-1, _rbank1, _rbank3];
    //            GVAR(lines) pushBack[-2, _rlabel, (str _drawPitch), 0.01, "center"];

    //            GVAR(lines) pushBack[-1, _lbank1, _lbank2];
    //            GVAR(lines) pushBack[-1, _lbank1, _lbank3];
    //            GVAR(lines) pushBack[-2, _llabel, (str _drawPitch), 0.01, "center"];
    //            }
    //            else {
    //                _rbank1 = _pitch0HudPos vectorAdd(_vec vectorMultiply 0.05);
    //                _rbank2 = _pitch0HudPos vectorAdd(_vec vectorMultiply 0.55);
    //                _lbank1 = _pitch0HudPos vectorAdd(_vec vectorMultiply - 0.05);
    //                _lbank2 = _pitch0HudPos vectorAdd(_vec vectorMultiply - 0.55);



    //                GVAR(lines) pushBack[-1, _rbank1, _rbank2];
    //                GVAR(lines) pushBack[-1, _lbank1, _lbank2];
    //            };
    //        };
    //    };
    //};

    //_gForce = (velocityModelSpace GVAR(vehicle)) select 2;
    //_gForce = _gForce * -1;
    //_gForce = (_gForce + 9.80665) / 9.80665;
    //_gForceExp = _gForce - (floor _gForce);
    //_gForceStr = (str(floor _gForce)) + "." + (str((floor(_gForceExp * 10))));
    //_gForce = parseNumber _gForceStr;
    //GVAR(maxGForce) = _gForce max GVAR(maxGForce);
    //GVAR(lines) pushBack[2, [0.25, 0.63], _gForceStr, 0.0065, "left"];

    //_gForceExp = GVAR(maxGForce) - (floor GVAR(maxGForce));
    //_gForceStr = (str(floor GVAR(maxGForce))) + "." + (str((floor(_gForceExp * 10))));
    //GVAR(lines) pushBack[2, [0.22, 0.08], _gForceStr, 0.0065, "left"];
    //GVAR(lines) pushBack[2, [0.118, 0.05], "NAV", 0.0065, "right"];


    //GVAR(lines) pushBack[2, [0.085, 0.02], "180  090", 0.0065, "right"];



    //_speedKnots = (speed GVAR(vehicle))*0.539957;
    //_speedMach = _speedKnots / 661.470842333;

    //_speedMachExp = _speedMach - (floor _speedMach);
    //_machStr = (str(floor _speedMach)) + "." + (str((floor(_speedMachExp * 100))));
    //// player sideChat format["m: %1", _machStr];
    //GVAR(lines) pushBack[2, [0.3, 0.12], _machStr, 0.0065, "left"];
    //GVAR(lines) pushBack[2, [0.3, 0.15], "ARM", 0.0065, "left"];



    //GVAR(lines) pushBack[1, [0.0575, 0.4], [0.15, 0.4], 0.01];
    //GVAR(lines) pushBack[1, [0.0575, 0.365], [0.15, 0.365], 0.01];
    //GVAR(lines) pushBack[1, [0.06, 0.4], [0.06, 0.365], 0.01];
    //GVAR(lines) pushBack[1, [0.1475, 0.365], [0.17, 0.365 + (0.4 - 0.365) / 2], 0.01];
    //GVAR(lines) pushBack[1, [0.1475, 0.4], [0.17, 0.4 - (0.4 - 0.365) / 2 - 0.001], 0.01];
    //GVAR(lines) pushBack[1, [0.2025, 0.4 - (0.4 - 0.365) / 2 - 0.001], [0.25, 0.4 - (0.4 - 0.365) / 2 - 0.001], 0.01];




    //GVAR(lines) pushBack[2, [0.18, 0.382], (str(floor _speedKnots)), 0.0065, "left"];

    //_range = 160;
    //_top = 0.4 - (0.4 - 0.365) / 2 - 0.001 + 0.2;
    //_bottom = 0.4 - (0.4 - 0.365) / 2 - 0.001 - 0.2;

    //_steps = _range / 10 * 2;

    //_spacing = (_top - _bottom) / _steps;
    //// player sideChat format["_steps: %1", _steps];
    //_speedOffset = (_speedKnots % 10) / 10;
    //_stepSpeed = ((round(_speedKnots)) - (_range / 2)) - (round(_speedKnots % 10));
    //_speedOffset = _speedOffset * _spacing * 2;
    //_speedOffset = _speedOffset * -1;
    //// player sideChat format["_stepSpeed: %1", _stepSpeed];
    //for "_i" from 0 to _steps step 2 do {
    //    _offset = _speedOffset + _bottom + _spacing*_i;
    //    if (_stepSpeed % 50 == 0) then{

    //        GVAR(lines) pushBack[1,[0.17, _offset],[0.2, _offset], 0.01];
    //    if (_offset > 0.415 || _offset < 0.35) then{
    //        GVAR(lines) pushBack[2,[0.2, _offset], (str(floor(_stepSpeed / 10))), 0.0065, "left"];
    //    };
    //    }
    //    else {
    //        GVAR(lines) pushBack[1, [0.185, _offset], [0.2, _offset], 0.01];
    //    };
    //    _stepSpeed = _stepSpeed + 10;
    //};



    //GVAR(lines) pushBack[1, [1 - 0.0375, 0.4], [1 - 0.15, 0.4], 0.01];
    //GVAR(lines) pushBack[1, [1 - 0.0375, 0.365], [1 - 0.15, 0.365], 0.01];
    //GVAR(lines) pushBack[1, [1 - 0.04, 0.4], [1 - 0.04, 0.365], 0.01];
    //GVAR(lines) pushBack[1, [1 - 0.1475, 0.365], [1 - 0.17, 0.365 + (0.4 - 0.365) / 2], 0.01];
    //GVAR(lines) pushBack[1, [1 - 0.1475, 0.4], [1 - 0.17, 0.4 - (0.4 - 0.365) / 2 - 0.001], 0.01];
    //GVAR(lines) pushBack[1, [1 - 0.2025, 0.4 - (0.4 - 0.365) / 2 - 0.001], [1 - 0.25, 0.4 - (0.4 - 0.365) / 2 - 0.001], 0.01];

    //_altitude = _vehiclePos select 2;
    //// player sideChat format["alt: %1", _altitude];
    //_altitude = floor(_altitude * 3.28084);

    //// _altitude = 2000;
    //_altStr = str _altitude;
    //// _altStr = "10,000";
    //if (count _altStr > 3) then{
    //    _altStr = (_altStr select[0, (count _altStr) - 3]) + "," + (_altStr select[(count _altStr) - 3, 3]);
    //};
    //GVAR(lines) pushBack[2, [1 - 0.175, 0.382], _altStr, 0.0065, "right"];


    //_range = 1600;
    //_top = 0.4 - (0.4 - 0.365) / 2 - 0.001 + 0.2 - 0.012;
    //_bottom = 0.4 - (0.4 - 0.365) / 2 - 0.001 - 0.1 - 0.012;

    //_steps = _range / 100 * 2;

    //_spacing = (_top - _bottom) / _steps;
    //// player sideChat format["_steps: %1", _steps];
    //_altOffset = (_altitude % 100) / 100;
    //_stepAlt = ((round(_altitude)) - (_range * 0.5)) - (round(_altitude % 100));

    //_altOffset = _altOffset * _spacing * 2;
    //_altOffset = _altOffset * -1;
    //// player    format["_stepAlt: %1", _stepAlt];

    //for "_i" from - 4 to _steps + 4 step 2 do {
    //    if (_i >= 0) then{
    //        if (_stepAlt >= 0) then{
    //            _offset = _altOffset + _bottom + _spacing*_i;
    //    if (_stepAlt % 500 == 0) then{

    //        GVAR(lines) pushBack[1,[1 - 0.17, _offset],[1 - 0.2, _offset], 0.01];
    //    if (_offset > 0.415 || _offset < 0.35) then{
    //        _stepAltStr = str _stepAlt;
    //    _stepAltStr = (_stepAltStr select[0, (count _stepAltStr) - 3]) + "," + (_stepAltStr select[(count _stepAltStr) - 3, 1]);

    //    GVAR(lines) pushBack[2,[0.81, _offset], _stepAltStr, 0.0065, "right"];
    //    };
    //    }
    //    else {
    //        GVAR(lines) pushBack[1,[1 - 0.185, _offset],[1 - 0.2, _offset], 0.01];
    //    };
    //        };
    //    };
    //    _stepAlt = _stepAlt + 100;
    //};

    //_radarAlt = (getPos _vehicle) select 2;
    //GVAR(lines) pushBack[1, [0.72, 0.2], [0.835, 0.2], 0.01];
    //GVAR(lines) pushBack[1, [0.72, 0.165], [0.835, 0.165], 0.01];
    //GVAR(lines) pushBack[1, [0.7225, 0.2], [0.7225, 0.165], 0.01];
    //GVAR(lines) pushBack[1, [0.8325, 0.2], [0.8325, 0.165], 0.01];

    //_altStr = str(floor(_radarAlt*3.28084));
    //// _altStr = "10,000";
    //if (count _altStr > 3) then{
    //    _altStr = (_altStr select[0, (count _altStr) - 3]) + "," + (_altStr select[(count _altStr) - 3, 3]);
    //};
    //GVAR(lines) pushBack[2, [0.695, 0.182], _altStr, 0.0065, "right"];
    //GVAR(lines) pushBack[2, [0.75, 0.182], "R", 0.0075, "left"];
    //_dir = (getDir _vehicle);
    //GVAR(lines) pushBack[1, [0.467, 0.18], [0.533, 0.18], 0.01];
    //GVAR(lines) pushBack[1, [0.467, 0.145], [0.533, 0.145], 0.01];
    //GVAR(lines) pushBack[1, [0.4695, 0.18], [0.4695, 0.145], 0.01];
    //GVAR(lines) pushBack[1, [0.5315, 0.18], [0.5315, 0.145], 0.01];
    //_dirStr = str(round _dir);
    //if ((count _dirStr) == 1) then{
    //    _dirStr = "0" + _dirStr;
    //};
    //if ((count _dirStr) == 2) then{
    //    _dirStr = "0" + _dirStr;
    //};
    //if (_dirStr == "000") then{
    //    _dirStr = "360";
    //};
    //GVAR(lines) pushBack[2, [0.5, 0.162], _dirStr, 0.0065, "center"];
    //GVAR(lines) pushBack[1, [0.5, 0.215], [0.5, 0.25], 0.01];

    //_range = 30;
    //_top = 0.62;
    //_bottom = 0.37;

    //// GVAR(lines) pushBack [1, [_bottom, 0.22], [_top, 0.22], 0.01];

    //_steps = _range / 5 * 2;

    //_spacing = (_top - _bottom) / _steps;
    //// player sideChat format["_steps: %1", _steps];
    //_dirOffset = (_dir % 5) / 5;
    //_stepDir = ((round(_dir)) - (_range / 2)) - (round(_dir % 5)) + 5;
    //_dirOffset = _dirOffset * _spacing * 2;
    //_dirOffset = _dirOffset * -1;




    //_wpDirFull = _wpDir;
    //if (_wpDirFull < 0) then{
    //    _wpDirFull = _wpDirFull + 360;
    //}
    //else {
    //    if (_wpDirFull > 360) then{
    //        _wpDirFull = _wpDirFull - 360;
    //    };
    //};
    //// player sideChat format["_wpDirFull: %1", _wpDir];
    //// player sideChat format["_stepDir: %1", _stepDir];
    //_caretRendered = false;
    //for "_i" from 2 to _steps step 2 do {
    //    _offset = _dirOffset + (_bottom)+_spacing*_i;
    //    _tStepDir = _stepDir;
    //    if (_tStepDir >= 360) then{
    //        _tStepDir = _tStepDir % 360;
    //    };
    //    if (_wpDirFull >= _tStepDir && _wpDirFull < (_tStepDir + 5)) then{
    //        if (_stepDir > 360) then{
    //            _wpDirFull = _wpDirFull + 360;
    //        };
    //    _caretOffset = _offset + (1 - (((_tStepDir + 5) - _wpDirFull) / 5))*(_spacing * 2);
    //    // player sideChat format["sd: %1 %2", _wpDirFull, 1-(((_tStepDir + 5) - _wpDirFull)/5)];
    //    GVAR(lines) pushBack[1,[_caretOffset, 0.21],[_caretOffset - 0.008, 0.23], 0.01];
    //    GVAR(lines) pushBack[1,[_caretOffset, 0.21],[_caretOffset + 0.008, 0.23], 0.01];
    //    _caretRendered = true;
    //    };
    //    if (_stepDir % 10 == 0) then{
    //        GVAR(lines) pushBack[1,[_offset, 0.21],[_offset, 0.18], 0.01];
    //    if (_offset > 0.56 || _offset < 0.43) then{
    //        _stepDirStr = _stepDir;
    //    if (_stepDir < 0) then{
    //        _stepDirStr = _stepDir + 360;
    //    };
    //    if (_stepDir > 360) then{
    //        _stepDirStr = _stepDir - 360;
    //    };
    //    _az = floor(_stepDirStr / 10);
    //    _azString = str _az;
    //    if (_az < 10) then{
    //        _azString = "0" + _azString;
    //    };
    //    GVAR(lines) pushBack[2,[_offset, 0.162], _azString, 0.0065, "center"];
    //    };
    //    }
    //    else {
    //        GVAR(lines) pushBack[1, [_offset, 0.21], [_offset, 0.19], 0.01];
    //    };
    //    // GVAR(lines) pushBack [2, [0.3, _dirOffset+_bottom+_spacing*_i], (str _stepDir), 0.0065, "left"];
    //    _stepDir = _stepDir + 5;
    //};
    //// player sideChat format["_wpRDir: %1", _wpRDir];
    //if (!_caretRendered) then{
    //    if (_wpRDir < 0) then{
    //        GVAR(lines) pushBack[1,[_bottom, 0.21],[_bottom - 0.008, 0.23], 0.01];
    //GVAR(lines) pushBack[1,[_bottom, 0.21],[_bottom + 0.008, 0.23], 0.01];
    //    }
    //    else {
    //        GVAR(lines) pushBack[1,[_top, 0.21],[_top - 0.008, 0.23], 0.01];
    //        GVAR(lines) pushBack[1,[_top, 0.21],[_top + 0.008, 0.23], 0.01];
    //    };
    //};
    //_slantRange = ((_wpPos vectorDistance _vehiclePos) / 1000)*0.539957;
    //_eta = floor((_slantRange / _speedKnots) * 60 * 60);
    //_slantRangeExp = _slantRange - (floor _slantRange);
    //_slantRangeStr = (str(floor _slantRange)) + "." + (str((floor(_slantRangeExp * 10))));
    //_slantRange = parseNumber _slantRangeStr;
    //if (_slantRange < 10) then{
    //    _slantRangeStr = "00" + _slantRangeStr;
    //}
    //else {
    //    if (_slantRange < 100) then{
    //        _slantRangeStr = "0" + _slantRangeStr;
    //    };
    //};
    //_rangeType = "B";
    //_slantRangeStr = _rangeType + _slantRangeStr;
    //GVAR(lines) pushBack[2, [0.665, 0.11], _slantRangeStr, 0.0065, "right"];
    //// player sideChat format["(_speedKnots/60/60): %1", (_speedKnots/60/60)];

    //_etaStr = str _eta;
    //if (_eta < 10) then{
    //    _etaStr = "000" + _etaStr;
    //}
    //else {
    //    if (_eta < 100) then{
    //        _etaStr = "00" + _etaStr;
    //    }
    //    else {
    //        _etaStr = "0" + _etaStr;
    //    };
    //};

    //GVAR(lines) pushBack[2, [0.665, 0.08], _etaStr, 0.0065, "right"];

    //_slantRange = floor _slantRange;
    //_slantRangeStr = str _slantRange;
    //if (_slantRange < 10) then{
    //    _slantRangeStr = "00" + _slantRangeStr;
    //}
    //else {
    //    if (_slantRange < 100) then{
    //        _slantRangeStr = "0" + _slantRangeStr;
    //    };
    //};
    //_currentWaypointStr = str GVAR(currentWaypointIndex);
    //if (GVAR(currentWaypointIndex) < 10) then{
    //    _currentWaypointStr = "0" + _currentWaypointStr;
    //};
    //GVAR(lines) pushBack[2, [0.665, 0.05], format["%1>%2", _slantRangeStr, _currentWaypointStr], 0.0065, "right"];

}

void __cdecl intercept::on_frame() {
    draw_hud();
}


void __cdecl intercept::post_init() {
    //_hudColor = [0 / 255, 230 / 255, 65 / 255, 1];
    ace_hud_color = { 0 / 255, 230 / 255, 65 / 255, 1 };
    //_hudColorString = format(["#(rgb,8,8,3)color(%1,%2,%3,%4)"] + _hudColor);
    std::stringstream ss;
    ss << "#(rgb,8,8,3)color(" << ace_hud_color.red << "," << ace_hud_color.green << "," << ace_hud_color.blue << "," << ace_hud_color.alpha << ")";
    ace_hud_color_string = ss.str();
}

void __cdecl intercept::mission_stopped() {

}

void __cdecl intercept::fired(
    object &unit_,
    std::string &weapon_,
    std::string &muzzle_,
    std::string &mode_,
    std::string &ammo_,
    std::string &magazine,
    object &projectile_) 
{
}


void Init(void) {
    el::Configurations conf;

    conf.setGlobally(el::ConfigurationType::Filename, "logs/intercept_example_dll.log");
    conf.setGlobally(el::ConfigurationType::MaxLogFileSize, "10240");
#ifdef _DEBUG
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "[%datetime] - %level - {%loc}t:%thread- %msg");
    conf.setGlobally(el::ConfigurationType::PerformanceTracking, "true");
#else
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime-{%level}- %msg");
#endif
    el::Loggers::setDefaultConfigurations(conf, true);

    LOG(INFO) << "Intercept Example DLL Loaded";
}

void Cleanup(void) {

}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Init();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        Cleanup();
        break;
    }
    return TRUE;
}
