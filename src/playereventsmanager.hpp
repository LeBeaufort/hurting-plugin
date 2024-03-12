
#ifndef PLAYEREVENTSMANAGER_HPP
#define PLAYEREVENTSMANAGER_HPP

#include <string>
#include <vector>
#include <ctime>
#include <swiftly/swiftly.h>

class PlayerEvent
{
    public:
        int time;
        std::string type;
        Player* player;
    
        PlayerEvent(std::string type, Player* player);
};

class PlayerEventsManager
{
public:
    PlayerEventsManager();

    void add_event(std::string type, Player* player);

    int getTimeithappen(std::string type, Player* player);

    void clear();

private:

    int getIndexOf(std::string type, Player* player);

    std::vector<PlayerEvent> events;
};

#endif // PLAYEREVENTSMANAGER_HPP