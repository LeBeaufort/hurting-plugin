#include "sentences.hpp"
#include "playereventsmanager.hpp"
#include <string>
#include <ctime>

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

PlayerEventsManager manager;


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
    std::string message = "[Hurting-Plugin] built on " + std::string(__DATE__) + " started \n";
    
    print(message.c_str());
}

void OnPluginStop()
{
    print("Hurting-plugin stopped");
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
    return "https://github.com/LeBeaufort/hurting-plugin";
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
    //we check for team flash
    else if (player->team == attacker->team && duration > 1.1)
    {
        const char *message = GetTeamFlashSentence();
        player->SendMsg(HudDestination(4), message);
        //print("[Hurting-Plugin] showing `" + message + "` to the player " + player->GetName() + "\n");
    }
}

void OnPlayerDeath(Player* player, Player* attacker, Player* assister, bool assistedflash, const char* weapon, bool headshot, short dominated, short revenge, short wipe, short penetrated, bool noreplay, bool noscope, bool thrusmoke, bool attackerblind, float distance, short dmg_health, short dmg_armor, short hitgroup)
{
    // checking if the player and the attacker are valids players
    if (player && attacker)
    {
        // we check for a team kill
        if (player->team == attacker->team)
        {
            const char* msg = GetTeamKillSentence();
            attacker->SendMsg(HudDestination(4), msg);
        }
        // we check for failed fake
        else if (std::time(0) - manager.getTimeithappen("abortDP", player) < 3 && std::time(0) - manager.getTimeithappen("abortDP", player) > 0.3)
        {
            const char* msg = GetFakeFailedSentence();
            player->SendMsg(HudDestination(4), msg);
        }
        else
        {
            // if no condition match we display this
            player->SendMsg(HudDestination(4), GetDeathSentence(attacker->team->Get()));
        }
         
        if (player->team == attacker->team)
        {
            //we send a kill message to the player
            const char* message = GetKillSentence();
            attacker->SendMsg(HudDestination(4), message);
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

bool OnPlayerChat(Player* player, const char* text, bool teamonly)
{
    const char* msg = GetChatSentence(teamonly);
    player->SendMsg(HudDestination(4), msg);
    return true;
}

void OnDecoyStarted(Player* player, short entityid, float x, float y, float z)
{
    const char* msg = GetDecoyStartSetence();
    player->SendMsg(HudDestination(4), msg);
}

void OnDecoyDetonate(Player* player, short entityid, float x, float y, float z)
{
    const char* msg = GetDecoyStopSetence();
    player->SendMsg(HudDestination(4), msg);
}



//this update manager data
void BombAbortDefuse(Player* player, unsigned short site)
{
    manager.add_event("abortDP", player);
}
void BombAbortPlant(Player* player, unsigned short site)
{
    manager.add_event("abortDP", player);
}
