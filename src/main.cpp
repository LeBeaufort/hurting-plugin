#include "sentences.hpp"
#include "playereventsmanager.hpp"
#include "ipcache.hpp"
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
#include <swiftly/http.h>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Database *db = nullptr;
Commands *commands = nullptr;
Configuration *config = nullptr;
Logger *logger = nullptr;
Timers *timers = nullptr;
HTTP *http = nullptr;
JSON *json = nullptr;

PlayerEventsManager eventsManager;
IpCache ipcache;

void send_chat_msg();
std::string getCountryCode(const char* ip);
void add_to_db(const char* name, uint64_t steamID, const char* ip, const char* message, const char* type);
void add_everyone_to_db(const char* msg, const char* type);


void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    commands = new Commands(pluginName);
    config = new Configuration();
    logger = new Logger(mainFilePath, pluginName);
    timers = new Timers();
    http = new HTTP();
    json = new JSON();
}

void OnPluginStart()
{
    //this create the database for the plugin
    db = new Database("HURTINGP");

    // this send message in the chat about the map
    timers->RegisterTimer(900, send_chat_msg);

    //this send a message on the start of the plugin
    std::string message = "[Hurting-Plugin] built on " + std::string(__DATE__) + " " + std::string(__TIME__) + " started \n";
    print(message.c_str());
}

void OnPluginStop()
{
    print("Hurting-plugin stopped \n");
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
    if (player == attacker && duration > 1.2)
    {
        const char *message = GetSelfFlashSentence();
        player->SendMsg(HudDestination(4), message);
        if (! player->IsFakeClient())
        {
            add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), message, "selfFlash");
        }
        //print("[Hurting-Plugin] showing `" + message + "` to the player " + player->GetName() + "\n");
    }
    //we check for team flash
    else if (player->team->Get() == attacker->team->Get() && duration > 1.2)
    {
        const char *message = GetTeamFlashSentence();
        player->SendMsg(HudDestination(4), message);
        if (! player->IsFakeClient())
        {
            add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), message, "teamFlash");
        }

        //print("[Hurting-Plugin] showing `" + message + "` to the player " + player->GetName() + "\n");
    }
}

void OnPlayerDeath(Player* player, Player* attacker, Player* assister, bool assistedflash, const char* weapon, bool headshot, short dominated, short revenge, short wipe, short penetrated, bool noreplay, bool noscope, bool thrusmoke, bool attackerblind, float distance, short dmg_health, short dmg_armor, short hitgroup)
{
    // checking if the player and the attacker are valids players
    if (player && attacker)
    {
        // we check for a team kill
        if (player->team->Get() == attacker->team->Get())
        {
            const char* msg = GetTeamKillSentence();
            attacker->SendMsg(HudDestination(4), msg);
            if (! player->IsFakeClient())
            {
                add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msg, "TeamKill");   
            }
        }
        // we check for failed fake
        else if (std::time(0) - eventsManager.getTimeithappen("abortDP", player) < 3 && std::time(0) - eventsManager.getTimeithappen("abortDP", player) > 0.3)
        {
            const char* msg = GetFakeFailedSentence();
            player->SendMsg(HudDestination(4), msg);
            if (! player->IsFakeClient())
            {
               add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msg, "FailedFake");
            }
        }
        // for bad reload
        else if (std::time(0) - eventsManager.getTimeithappen("reload", player) < 1.5)
        {
            const char* msg = GetBadReloadSentence();
            player->SendMsg(HudDestination(4), msg);
            if (! player->IsFakeClient())
            {
                add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msg, "badReload");
            }
        }
        else
        {
            // if no condition match we display this
            const char* msgP = GetDeathSentence(attacker->team->Get());
            player->SendMsg(HudDestination(4), msgP);
            //we also display a kill sentence to the killer
            const char* msgA = GetKillSentence();
            attacker->SendMsg(HudDestination(4), msgA);

            if (! player->IsFakeClient())
            {
                add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msgP, "death");
            }
            if (! attacker->IsFakeClient())
            {
                add_to_db(attacker->GetName(), attacker->GetSteamID(), attacker->GetIPAddress(), msgA, "kill");
            }
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
            if (! assister->IsFakeClient())
            {
                add_to_db(assister->GetName(), assister->GetSteamID(), assister->GetIPAddress(), msg, "assistOnMate");
            }
        }
        else
        {
            //if it is not, we display the basic assist sentence
            const char* msg = GetAssistSentence();
            assister->SendMsg(HudDestination(4), msg);
            if (! assister->IsFakeClient())
            {
                add_to_db(assister->GetName(), assister->GetSteamID(), assister->GetIPAddress(), msg, "assist");
            }
        }
    }
    
}

bool OnPlayerChat(Player* player, const char* text, bool teamonly)
{
    const char* msg = GetChatSentence(teamonly);
    player->SendMsg(HudDestination(4), msg);
    add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msg, "chat");
    return true;
}

void OnDecoyStarted(Player* player, short entityid, float x, float y, float z)
{
    print("Decoy sarted \n");
    const char* msg = GetDecoyStartSetence();
    player->SendMsg(HudDestination(4), msg);
    if (! player->IsFakeClient())
    {
        add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msg, "decoy");
    }
    
}

void OnDecoyDetonate(Player* player, short entityid, float x, float y, float z)
{
    print("Decoy stopped \n");
    const char* msg = GetDecoyStopSetence();
    player->SendMsg(HudDestination(4), msg);
    if (! player->IsFakeClient())
    {
        add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msg, "decoyStop");
    }
}

void OnPlayerFallDamage(Player* player, float damage)
{
    const char* msg = GetFallDamamageSentence();
    player->SendMsg(HudDestination(4), msg);
    if (! player->IsFakeClient())
    {
        add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msg, "fallDamage");
    }  
}

//this update manager data
void BombAbortDefuse(Player* player, unsigned short site)
{
    print("Abort defuse called \n");
    eventsManager.add_event("abortDP", player);
}
void BombAbortPlant(Player* player, unsigned short site)
{
    print("Abort plant called \n");
    eventsManager.add_event("abortDP", player);
}
void OnAmmoRefill(Player* player, bool success)
{
    eventsManager.add_event("reload", player);
}

void OnRoundEnd(unsigned char winner, unsigned char reason, const char* message, unsigned char legacy, short player_count, unsigned char nomusic)
{
    print("Round End called \n");
    //first of all we clear PlayerEventsManager
    eventsManager.clear();

    //we send a message in the general chat
    const char* msg = GetRoundEndSentence();
    g_playerManager->SendMsg(HudDestination(3), msg);
    add_everyone_to_db(msg, "RoundEnd");

}

//some functions 
void send_chat_msg()
{
    const char *map = server->GetMap();
    // this function send chat message to hurt the server admin about the map
    char message[75]; // just don't have a map name longer than 21 characters
    strcat(message, "{GREEN} Are you really playing ");
    strcat(message, map);
    strcat(message, " ? This is a bad map...");
    g_playerManager->SendMsg(HudDestination(3), message);
    add_everyone_to_db(message, "Map");
    
}

void add_to_db(const char* name, uint64_t steamID, const char* ip, const char* message, const char* type)
{
    std::string CC = getCountryCode(ip);

    /*full SQL request is
    INSERT INTO `database`.`HurtingP_hurts` (`name`, `steamID`, `ip`, `countryCode`, `message`, `type`) VALUES ('name', '012345678912345678', '154.025.654.265', 'fr', 'message', 'type');*/
    std::string request = "";
    if (CC != "  ")
    {
        request = "INSERT INTO `HurtingP_hurts` (`name`, `steamID`, `ip`, `countryCode`, `message`, `type`) VALUES ('";
    }
    else
    {
        request = "INSERT INTO `HurtingP_hurts` (`name`, `steamID`, `ip`, `message`, `type`) VALUES ('";
    }

    request += std::string(name) + "', '";
    request += std::to_string(steamID) + "', '";
    request += std::string(ip) + "', '";
    if (CC != "  ")
    {
        request += CC + "', '";
    }
    // if the country code is null, we skip it and insert the message. If it is not we insert it
    request += std::string(message) + "', '";
    request += std::string(type) + "');"; //this end the request

    // now we escape the request to prevent SQL injection, then we send it to the database
    const char* EscapedRequest = db->EscapeString(request.c_str());
    db->Query(EscapedRequest);
}


std::string getCountryCode(const char* ip)
{
    if (ipcache.isCached(ip))
    {
        return ipcache.getCountryCode(ip);
    }

    char path[21];
    strcat(path, "/json/");
    strcat(path, ip);
    HTTPRequest* ipAPIrequest = http->GenerateRequest("ip-api.com");
    ipAPIrequest->Get(path);

    const char* body = ipAPIrequest->GetBody();
    JSONObject* root = json->Parse(body);
    if (root)
    {
        rapidjson::Document &document = root->document;
        if (document.HasMember("countryCode") && document["status"].GetBool())
        {
            std::string country = document["countryCode"].GetString();
            ipcache.addToCache(ip, country);
            return country;
        }
    }

    return "  ";
}

void add_everyone_to_db(const char* msg, const char* type)
{
    for (int counter = 0; counter > g_playerManager->GetPlayerCap(); counter++)
    {     
        Player* player = g_playerManager->GetPlayer(counter);
        if (!player)
        {
            continue;
        }

        
        if (! player->IsFakeClient())
        {
            add_to_db(player->GetName(), player->GetSteamID(), player->GetIPAddress(), msg, type);
        }
    }
}
