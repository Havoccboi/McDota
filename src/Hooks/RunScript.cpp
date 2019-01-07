#include "hooks.h"
#include "../settings.h"
typedef int (* RunScriptFn)( panorama::UIEngine*, panorama::IUIPanel *,char const*,char const*,int,int,bool );

int Hooks::RunScript( panorama::UIEngine *thisptr, panorama::IUIPanel *panel, const char *entireJSCode, const char *pathToXMLContext, int int1, int int2, bool alreadyCompiled ) {
    if ( mc_log_runscript->GetBool() ){
        Util::Log( "--RunScript--\n Panel: %s Str1: %s, Str2: (%s), int1: %d, int2: %d, bool1(%s)\n", panel->GetID(), entireJSCode, pathToXMLContext, int1, int2, alreadyCompiled? "yes" : "no" );
    }

    /* AutoAccept */
    if( mc_autoaccept_on->GetBool() ){

        if( strstr( pathToXMLContext, "popup_accept_match.xml" ) ){
            if( OnAcceptMatch ){
                cvar->ConsoleColorPrintf(ColorRGBA(5, 5, 225), "Match Found! Attempting to AutoAccept...\n");
                OnAcceptMatch( gDBPlayPanel );
            } else {
                cvar->ConsoleColorPrintf(ColorRGBA( 225, 5, 5 ), "[%s]ERROR: Tried to Accept Match but OnMatchAccept() is NULL!\n", __func__);
            }
        }
    }

    return uiEngineVMT->GetOriginalMethod<RunScriptFn>(110)( thisptr, panel, entireJSCode, pathToXMLContext, int1, int2, alreadyCompiled );
}