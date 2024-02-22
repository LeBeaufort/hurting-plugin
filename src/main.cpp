#include "sentences.hpp"

#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/database.h>
#include <swiftly/commands.h>
#include <swiftly/configuration.h>
#include <swiftly/logger.h>
#include <swiftly/timers.h>
#include <swiftly/gameevents.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Database *db = nullptr;
Commands *commands = nullptr;
Configuration *config = nullptr;
Logger *logger = nullptr;
Timers *timers = nullptr;


void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    commands = new Commands(pluginName);
    config = new Configuration();
    logger = new Logger(mainFilePath, pluginName);
    timers = new Timers();
}

void OnPluginStart()
{

    print("[Hurting-Plugin] started \n");

}

void OnPluginStop()
{
    print("Hurting-plugin stoped");
}

const char *GetPluginAuthor()
{
    return "LeBeaufort";
}

const char *GetPluginVersion()
{
    return "0.0.0";
}

const char *GetPluginName()
{
    return "hurting-plugin";
}

const char *GetPluginWebsite()
{
    return "";
}


//real code start here
void OnPlayerBlind(Player* player, Player* attacker, short entityid, float duration)
{
    //first, we check if the player self-flashed
    if (player == attacker && duration > 0.5)
    {
        const char *message = GetSelfFlashSentence();
        player->SendMsg(HudDestination(4), message);
        //print("[Hurting-Plugin] showing `" + message + "` to the player " + player->GetName() + "\n");
    }
    else if (player->team == attacker->team)
    {
        const char *message = GetTeamFlashSentence();
        player->SendMsg(HudDestination(4), message);
        //print("[Hurting-Plugin] showing `" + message + "` to the player " + player->GetName() + "\n");
    }
}

void OnPlayerFallDamage(Player* player, float damage)
{
    const char *message = GetFallDamamageSentence();
    player->SendMsg(HudDestination(4), message);
}