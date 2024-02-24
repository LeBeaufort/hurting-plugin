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
    if (player == attacker && duration > 1.1)
    {
        const char *message = GetSelfFlashSentence();
        player->SendMsg(HudDestination(4), message);
        //print("[Hurting-Plugin] showing `" + message + "` to the player " + player->GetName() + "\n");
    }
    else if (player->team == attacker->team && duration > 1.1)
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

void OnPlayerDeath(Player* player, Player* attacker, Player* assister, bool assistedflash, const char* weapon, bool headshot, short dominated, short revenge, short wipe, short penetrated, bool noreplay, bool noscope, bool thrusmoke, bool attackerblind, float distance, short dmg_health, short dmg_armor, short hitgroup)
{
    // checking if the player and the attacker are valids players
    if (player and attacker)
    {

        //we send a death message to the player
        player->SendMsg(HudDestination(4), GetDeathSentence(attacker->team->Get()));

        // we check for team kill
        if (player->team == attacker->team)
        {
            const char* msg = GetTeamKillSentence();
            attacker->SendMsg(HudDestination(4), msg);
        }

    }

    //we check if the assister is a valid player
    if (assister)
    {
        //we check if a teammate assist an enemy
        if (assister->team == player->team)
        {
            const char* msg = GetAssistOnMateSentence();
            assister->SendMsg(HudDestination(4), msg);
        }
    }
    
}