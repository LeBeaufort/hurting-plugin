#include <string>
#include <ctime>
#include <vector>

#include <swiftly/swiftly.h>



class PlayerEvent
{
    public:
        int time;
        std::string type;
        Player* player;
        
        PlayerEvent(std::string type, Player* player)
        {
            this->time = std::time(0);
            this->type = type;
            this->player = player;
        }

        
};





class PlayerEventsManager
{

public:

    PlayerEventsManager(){}

    void add_event(std::string type, Player* player)
    {
        //before adding anything, we check if it exist.
        int index = this->getIndexOf(type, player);

        if (index != -1)
        {
            //we change the time
            this->events[index].time = std::time(0);
        }
        else
        {
            // if it does exist yet, we create it
            this->events.push_back(PlayerEvent(type, player));
        }
    }

    int getTimeithappen(std::string type, Player* player)
    {
        int index = this->getIndexOf(type, player);
        if (index != -1)
        {
            return this->events[index].time;
        }
    }

    void clear()
    {
        this->events.clear();
    }


private:

    std::vector<PlayerEvent> events;

    int getIndexOf(std::string type, Player* player)
    {
        /*this function search for an PlayerEvent that match with the type and the player. It returns the index of this PlayerEvent*/
        for (int i = 0; i++; i < this->events.size())
        {
            if (type == events[i].type && player == events[i].player)
            {
                return i;
            }
        }
        // if nothing is found -1 is returned
        return -1;
    }
};

