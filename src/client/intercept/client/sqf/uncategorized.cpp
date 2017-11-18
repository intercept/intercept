#include "uncategorized.hpp"
#include "client/pointers.hpp"
#include "common_helpers.hpp"
#include "position.hpp"  //for uses of get_pos_obj. Should be removed once they are sorted

using namespace intercept::types;

namespace intercept {
    namespace sqf {

        /////////////////////// DO NOT IMPLEMENT THESE FUNCTIONS /////////////////////////
        ///////// They are haram. Discuss on slack prior to removing from list. //////////
        // unary__abs__scalar_nan__ret__scalar_nan
        // unary__acos__scalar_nan__ret__scalar_nan
        // unary__asin__scalar_nan__ret__scalar_nan
        // unary__atan__scalar_nan__ret__scalar_nan
        // unary__atg__scalar_nan__ret__scalar_nan
        // unary__assert__bool__ret__bool
        // unary__breakout__string__ret__nothing
        // unary__breakto__string__ret__nothing
        // unary__case__any__ret__switch
        // unary__comment__string__ret__nothing
        // unary__count__array__ret__scalar
        // unary__count__string__ret__scalar
        // unary__ceil__scalar_nan__ret__scalar_nan
        // unary__cos__scalar_nan__ret__scalar_nan
        // unary__debuglog__any__ret__nothing
        // unary__default__code__ret__nothing
        // unary__deg__scalar_nan__ret__scalar_nan
        // unary__exp__scalar_nan__ret__scalar_nan
        // unary__floor__scalar_nan__ret__scalar_nan
        // unary__for__string__ret__for
        // unary__for__array__ret__for
        // unary__goto__string__ret__nothing
        // unary__if__bool__ret__if
        // unary__ln__scalar_nan__ret__scalar_nan
        // unary__log__scalar_nan__ret__scalar_nan
        // unary__not__bool__ret__bool
        // unary__oneachframe__code_string__ret__nothing
        // unary__ongroupiconclick__code_string__ret__nothing
        // unary__ongroupiconoverenter__code_string__ret__nothing
        // unary__ongroupiconoverleave__code_string__ret__nothing
        // unary__onhcgroupselectionchanged__code_string__ret__nothing
        // unary__onmapsingleclick__code_string__ret__nothing
        // unary__onplayerconnected__code_string__ret__nothing
        // unary__onplayerdisconnected__code_string__ret__nothing
        // unary__onpreloadfinished__code_string__ret__nothing
        // unary__onpreloadstarted__code_string__ret__nothing
        // unary__onteamswitch__code_string__ret__nothing
        // unary__param__array__ret__any
        // unary__params__array__ret__bool
        // unary__private__string_array__ret__nothing
        // unary__rad__scalar_nan__ret__scalar_nan
        // unary__random__array__ret__scalar_nan
        // unary__random__scalar_nan__ret__scalar_nan
        // unary__reverse__array__ret__nothing
        // unary__round__scalar_nan__ret__scalar_nan
        // unary__selectrandom__array__ret__any
        //  unary__selectrandomweighted__array__ret__any
        // unary__sin__scalar_nan__ret__scalar_nan
        // unary__sqrt__scalar_nan__ret__scalar_nan
        // unary__switch__any__ret__switch
        // unary__tan__scalar_nan__ret__scalar_nan
        // unary__tg__scalar_nan__ret__scalar_nan
        // unary__throw__any__ret__nothing
        // unary__toarray__string__ret__array
        // unary__tostring__array__ret__string
        // unary__try__code__ret__exception
        // unary__typename__any__ret__string
        // unary__vectormagnitude__array__ret__scalar
        // unary__vectormagnitudesqr__array__ret__scalar
        // unary__vectornormalized__array__ret__array
        // unary__waituntil__code__ret__nothing
        // unary__while__code__ret__while
        // unary__with__namespace__ret__with

        // binary__and__bool__bool__ret__bool
        // binary__and__bool__code__ret__bool
        // binary__atan2__scalar_nan__scalar_nan__ret__scalar_nan
        // binary__breakout__any__string__ret__any
        // binary__camsetdir__object__array__ret__nothing
        // binary__catch__exception__code__ret__any
        // binary__count__code__array__ret__scalar
        // binary__deleteat__array__scalar__ret__any
        // binary__deleterange__array__array__ret__nothing
        // binary__do__while__code__ret__nothing
        // binary__do__with__code__ret__nothing
        // binary__do__for__code__ret__any
        // binary__do__switch__code__ret__any
        // binary__else__code__code__ret__array
        // binary__exitwith__if__code__ret__any
        // binary__find__array__any__ret__scalar
        // binary__find__string__string__ret__scalar
        // binary__foreach__code__array__ret__nothing
        // binary__foreachmember__code__team_member__ret__nothing
        // binary__foreachmemberagent__code__team_member__ret__nothing
        // binary__foreachmemberteam__code__team_member__ret__nothing
        // binary__from__for__scalar__ret__for
        // binary__in__any__array__ret__bool
        // binary__joinstring__array__string__ret__string
        // binary__max__scalar_nan__scalar_nan__ret__scalar_nan
        // binary__min__scalar_nan__scalar_nan__ret__scalar_nan
        // binary__mod__scalar_nan__scalar_nan__ret__scalar_nan
        // binary__lbsetselected__control__array__ret__nothing (Depreciated in favor of lbSetCurSel)
        // binary__or__bool__bool__ret__bool
        // binary__or__bool__code__ret__bool
        // binary__param__any__array__ret__any
        // binary__params__any__array__ret__bool
        // binary__resize__array__scalar__ret__nothing
        // binary__select__array__scalar__ret__any
        // binary__select__array__bool__ret__any
        // binary__select__array__array__ret__array
        // binary__select__string__array__ret__string
        // binary__splitstring__string__string__ret__array
        // binary__step__for__scalar__ret__for
        // binary__then__if__code__ret__any
        // binary__then__if__array__ret__any
        // binary__throw__if__any__ret__nothing
        // binary__to__for__scalar__ret__for
        // binary__try__any__code__ret__exception
        // binary__vectoradd__array__array__ret__array
        // binary__vectorcos__array__array__ret__scalar
        // binary__vectorcrossproduct__array__array__ret__array
        // binary__vectordiff__array__array__ret__array
        // binary__vectordistance__array__array__ret__scalar
        // binary__vectordistancesqr__array__array__ret__scalar
        // binary__vectordotproduct__array__array__ret__scalar
        // binary__vectorfromto__array__array__ret__array
        // binary__vectormultiply__array__scalar__ret__array
        // unary__tofixed__scalar__ret__nothing
        // binary__call__any__code__ret__any
        // binary__append__array__array__ret__nothing
        // binary__arrayintersect__array__array__ret__array
        // binary__pushback__array__any__ret__scalar
        // binary__selectrandomweighted__array__array__ret__any
        // binary__set__array__array__ret__nothing
        // binary__sort__array__bool__ret__nothing

        // nular__allsites__ret__array (deprecated - source: BI Wiki)
        // nular__false__ret__bool
        // nular__netobjnull__ret__netobject ----------------------------------------------------------------------------------
        // nular__nil__ret__any
        // nular__true__ret__bool
        // unary__isnull__netobject__ret__bool

        /// INVESTIGATE
        /* No documentation. */
        // binary_dynamicsimulationdistancecoef__string__scalar__ret__nothing

        /* No documentation.*/
        // unary__addforcegeneratorrtd__array__ret__scalar

        /* No documentation.*/
        // nular__airdensitycurvertd__ret__array

        /* No documentation.*/
        // unary__ctrlangle__control__ret__array

        /* No documentation for return array elements. */
        // unary__ctrlmapmouseover__control__ret__array
        // unary__curatorcameraarea__object__ret__array
        // unary__curatoreditingarea__object__ret__array

        /* No documentation.*/
        // unary__enableaudiofeature__array__ret__bool

        /* No documentation.*/
        // nular__getdlcassetsusage__ret__array

        /* No documentation.*/
        // unary__getpersonuseddlcs__object__ret__array
        // unary__getplayerscores__object__ret__array

        /* Last parameter can be position (x, y, z) or target, unknown what target is.*/
        // nular__hudmovementlevels__ret__array

        /* No documentation for type Team.*/
        // nular__teams__ret__array

        /* No documentation.*/
        // nular__windrtd__ret__array

        /* No documentation.*/
        // unary__resources__team_member__ret__array

        /* These functions apparently send arbatary messages across the network. They are apparently inactive.*/
        // unary__sendaumessage__array__ret__nothing
        // unary__sendudpmessage__array__ret__bool

        /* This function is apparently depreciated but the functionality is different to the command which replaces it.*/
        // unary__lbselection__control__ret__array

        /* No documentation.*/
        // binary__ctrlsettextcolorsecondary__control__array__ret__nothing

        /* No documentation.*/
        // unary__enginespowerrtd__object__ret__array
        // unary__forceatpositionrtd__array__ret__array
        // unary__forcegeneratorrtd__scalar__ret__array
        // unary__gettrimoffsetrtd__object__ret__array
        // unary__isautostartupenabledrtd__object__ret__array
        // binary__setforcegeneratorrtd__scalar__array__ret__nothing
        // binary__setwingforcescalertd__object__array__ret__nothing

        /* No documentation.*/
        // unary__setwinddir__array__ret__nothing

        /* No documentation.*/
        // unary__call__code__ret__any
        // unary__clear3deninventory__array__ret__nothing
        // unary__tvpictureright__array__ret__string
        // unary__createobject__array__ret__object
        // unary__getdlcassetsusagebyname__string__ret__array
        // unary__getenginetargetrpmrtd__object__ret__array
        // unary__getfieldmanualstartpage__display__ret__array
        // binary__lnbcolorright__control__array__ret__array
        // unary__lnbcolorright__array__ret__array
        // unary__lnbpictureright__array__ret__string
        // binary__lnbpictureright__control__array__ret__string
        // unary__lnbsetcolorright__array__ret__nothing
        // binary__lnbsetcolorright__control__array__ret__nothing
        // unary__lnbsetpicturecolor__array__ret__nothing
        // binary__lnbsetpicturecolor__control__array__ret__nothing
        // unary__lnbsetpicturecolorright__array__ret__nothing
        // binary__lnbsetpicturecolorright__control__array__ret__nothing
        // unary__lnbsetpicturecolorselected__array__ret__nothing
        // binary__lnbsetpicturecolorselected__control__array__ret__nothing
        // unary__lnbsetpicturecolorselectedright__array__ret__nothing
        // binary__lnbsetpicturecolorselectedright__control__array__ret__nothing
        // unary__lnbsetpictureright__array__ret__nothing
        // binary__lnbsetpictureright__control__array__ret__nothing
        // unary__lnbsettextright__array__ret__nothing
        // binary__lnbsettextright__control__array__ret__nothing

        // unary__lnbtextright__array__ret__string
        // binary__lnbtextright__control__array__ret__string

        /* No documentation for return types. */
        // unary__getgroupicons__group__ret__array
        // unary__taskresult__task__ret__array
        // unary__waypointstatements__array__ret__array

        /* Wrong documentation - seems to take Array instead of String. */
        // unary__lognetwork__array__ret__scalar

        /* Team Member things - apparently useless. */
        // unary__teammember__object__ret__team_member
        // binary__sendtask__team_member__array__ret__task
        // binary__sendtaskresult__task__array__ret__nothing

        /* deprecated?*/
        // binary__seteditorobjectscope__control__array__ret__nothing
        // nular__benchmark__ret__scalar
        // unary__textlog__any__ret__nothing
        // unary__textlogformat__array__ret__nothing
        /////////////////////// DO NOT IMPLEMENT ABOVE FUNCTIONS /////////////////////////

    }  // namespace sqf
}  // namespace intercept
