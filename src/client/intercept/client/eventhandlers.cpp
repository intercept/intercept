#include <random>
#include "eventhandlers.hpp"
#include "sqf.hpp"

namespace intercept::client {

    void client_eventhandler(intercept::types::game_value& retVal, int ehType, int32_t uid, float handle, game_value args) {
        switch (static_cast<eventhandler_type>(ehType)) {
            case eventhandler_type::mission: {
                auto found = funcMapMissionEH.find({uid, handle});
                if (found != funcMapMissionEH.end())
                    retVal = callEHHandler(found->second.first, args, found->second.second);
            } break;
            case eventhandler_type::object: {
                auto found = funcMapObjectEH.find({uid, handle});
                if (found != funcMapObjectEH.end())
                    retVal = callEHHandler(found->second.first, args, found->second.second);
            } break;
            case eventhandler_type::display: {
                auto found = funcMapCtrlEH.find({uid, handle});
                if (found != funcMapCtrlEH.end())
                    retVal = callEHHandler(found->second.first, args, found->second.second);
            } break;
            default:;
        }
        return;
    }

#pragma region Mission Eventhandlers
    std::unordered_map<EHIdentifier, std::pair<eventhandlers_mission, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapMissionEH;

    EHIdentifier addScriptEH(eventhandlers_mission type) {
        std::default_random_engine rng(std::random_device{}());
        std::uniform_int_distribution<int32_t> dist(-16777215, 16777215);

        r_string typeStr;
        //#TODO eachFrame is just redirector to InvokePeriod.
        switch (type) {
#define EHMISS_CASE(name, retVal, args) \
    case eventhandlers_mission::name: typeStr = #name##sv; break;
            EHDEF_MISSION(EHMISS_CASE)
            default:;
        }

        auto uid = dist(rng);
        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("[\""sv)
                              + intercept::client::host::module_name.data() + "\","
                              + std::to_string(static_cast<uint32_t>(eventhandler_type::mission)) + ","
                              + std::to_string(uid) + ","
                              + "_thisEventHandler] InterceptClientEvent _this";
        float ehid = intercept::sqf::add_mission_event_handler(static_cast<sqf_string>(typeStr), command);

        return {uid, ehid};
    }

    void delScriptEH(eventhandlers_mission type, EHIdentifier& handle) {
        r_string typeStr;
        switch (type) {
            EHDEF_MISSION(EHMISS_CASE)
            default:;
        }
        sqf::remove_mission_event_handler(static_cast<sqf_string>(typeStr), handle.second);
    }

//#define EH_Add_Mission_definition(name,retVal,fncArg)\
//template<> \
//[[nodiscard]] EHIdentifier addMissionEventHandler<eventhandlers_mission::name, std::function<retVal(fncArg)>>(std::function<retVal(fncArg)> function) {\
//    auto ident = addScriptEH(eventhandlers_mission::name);\
//    funcMapMissionEH[ident] = {eventhandlers_mission::name,std::make_shared < std::function<void()> >(*reinterpret_cast<std::function<void()>*>(&function))};\
//    return ident;\
//}
//
//EHDEF_MISSION(EH_Add_Mission_definition)

#pragma endregion

#pragma region Object Eventhandlers

    std::unordered_map<EHIdentifier, std::pair<eventhandlers_object, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapObjectEH;
    EHIdentifier addScriptEH(types::object obj, eventhandlers_object type) {
        std::default_random_engine rng(std::random_device{}());
        std::uniform_int_distribution<int32_t> dist(-16777215, 16777215);

        r_string typeStr;
        //#TODO eachFrame is just redirector to InvokePeriod.
        switch (type) {
#define EHOBJ_CASE(name, retVal, args) \
    case eventhandlers_object::name: typeStr = #name##sv; break;
            EHDEF_OBJECT(EHOBJ_CASE)
            default:;
        }

        auto uid = dist(rng);
        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("[\"")
                              + intercept::client::host::module_name.data() + "\","
                              + std::to_string(static_cast<uint32_t>(eventhandler_type::object)) + ","
                              + std::to_string(uid) + ","
                              + "_thisEventHandler] InterceptClientEvent _this";
        float ehid = intercept::sqf::add_event_handler(obj, static_cast<sqf_string>(typeStr), command);

        return {uid, ehid};
    }

    void delScriptEH(types::object obj, eventhandlers_object type, EHIdentifier& handle) {
        r_string typeStr;
        switch (type) {
            EHDEF_OBJECT(EHOBJ_CASE)
        default:;
        }
        sqf::remove_event_handler(obj, static_cast<sqf_string>(typeStr), static_cast<int>(handle.second));
    }
#pragma endregion

#pragma region Ctrl Eventhandlers
    std::unordered_map<EHIdentifier, std::pair<eventhandlers_ctrl, std::shared_ptr<std::function<void()>>>, EHIdentifier_hasher> funcMapCtrlEH;
    EHIdentifier addScriptEH(types::control ctrl, eventhandlers_ctrl type) {
        std::default_random_engine rng(std::random_device{}());
        std::uniform_int_distribution<int32_t> dist(-16777215, 16777215);

        r_string typeStr;
        //#TODO eachFrame is just redirector to InvokePeriod.
        switch (type) {
#define EHCTRL_CASE(name, retVal, args) \
    case eventhandlers_ctrl::name: typeStr = #name##sv; break;
            EHDEF_CTRL(EHCTRL_CASE)
            default:;
        }

        auto uid = dist(rng);
        //#TODO use hash of moduleName as identifier.. That's faster..
        std::string command = std::string("[\"")
                              + intercept::client::host::module_name.data() + "\","
                              + std::to_string(static_cast<uint32_t>(eventhandler_type::object)) + ","
                              + std::to_string(uid) + ","
                              + "_thisEventHandler] InterceptClientEvent _this";
        float ehid = intercept::sqf::ctrl_add_event_handler(ctrl, static_cast<sqf_string>(typeStr), command);

        return {uid, ehid};
    }

    void delScriptEH(types::control ctrl, eventhandlers_ctrl type, EHIdentifier& handle) {
        r_string typeStr;
        switch (type) {
            EHDEF_CTRL(EHCTRL_CASE)
        default:;
        }
        sqf::ctrl_remove_event_handler(ctrl,static_cast<sqf_string>(typeStr), handle.second);
    }

#pragma endregion
}  // namespace intercept::client
