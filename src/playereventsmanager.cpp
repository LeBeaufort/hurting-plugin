#include <string>
#include <ctime>
#include <vector>

#include <swiftly/swiftly.h>

#include "playereventsmanager.hpp"




        
PlayerEvent::PlayerEvent(std::string type, Player* player)
{
        this->time = std::time(0);
        this->type = type;
        this->player = player;
}



PlayerEventsManager::PlayerEventsManager(){}

void PlayerEventsManager::add_event(std::string type, Player* player)
{
    //before adding anything, we check if it exist.
    int index = this->getIndexOf(type, player);

    if (index != -1)
    {
        //we change the time
        this->events[index].time = std::time(0);
        print("Event alerady exist. It has been updated \n");
    }
    else
    {
        // if it does exist yet, we create it
        this->events.push_back(PlayerEvent(type, player));
        print("Event created");
    }
}

int PlayerEventsManager::getTimeithappen(std::string type, Player* player)
{
    print("getTimeitHappen called \n");
    int index = this->getIndexOf(type, player);
    if (index != -1)
    {
        return this->events[index].time;
    }
    else {
        return 0;
    }
}

void PlayerEventsManager::clear()
{
    this->events.clear();
}


int PlayerEventsManager::getIndexOf(std::string type, Player* player)
{
    /*this function search for an PlayerEvent that match with the type and the player. It returns the index of this PlayerEvent*/
    for (int i = 0; i < this->events.size(); i++)
    {
        if (type == this->events[i].type && player == events[i].player)
        {
            return i;
        }
    }
    // if nothing is found -1 is returned
    return -1;
}

