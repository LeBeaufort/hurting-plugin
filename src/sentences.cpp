#include <ctime>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>

const char* GetSelfFlashSentence()
{
    //this function return a sentence if someone flash himself

    const char* sentences[] = {"ha, you so good, you flashed yourself", "you are not supposed to look at it...", "you finaly flashed someone, but that the wrong person..."};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    
    return sentences[rand() % len];      
}

const char* GetTeamFlashSentence()
{
    //this function return a sentence if someone flash a team mate
    const char* sentences[] = {"bro that not an enemy, that a teammate", "you are not supposed to flash this person..."};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);


    return sentences[rand() % len];
}

const char* GetFallDamamageSentence()
{
    const char* sentences[] = {"the ground is better than you at this game", "maybe you should try to shoot at the ground for get a kill"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}

const char* GetTeamKillSentence()
{
    const char* sentences[] = {"I'm not doctor but i think you have vision trouble", "wrong person...", "are you doing this on purpose?"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}

const char* GetAssistOnMateSentence()
{
    const char* sentences[] = {"GG, you helped your team mate to die !", "Are you sure what is your team ?", "enemies are thanking you"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}

const char* GetAssistSentence()
{
    const char* sentences[] = {"Maybe next time you could kill him ?", "Nice start, try again"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}

const char* GetDeathSentence(int team)
{
    std::vector<const char*> sentences = {"Please stop dieing and help your team", "Yeah, you are feeding the enemy"};


    if (team == 3)
    {
        sentences.push_back("Maybe you could help your mates to stop T pushes instead of dieing");
    }
    else if (team == 4)
    {
        sentences.push_back("Stop feeding and help your mates to plant");
        sentences.push_back("your role is to have extra smokes and flashes for your team");
    }

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}

const char* GetKillSentence()
{
    std::vector<const char*> sentences = {"It was luck", "yeah ! first time you helped your team !", "finally !"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
    
}

const char* GetChatSentence(bool teamonly)
{
    std::vector<const char*> team = {"Maybe you should use voice chat ?", "do you know what VC stand for ? It doesn't mean \"Very Convenient\" even if it is"};
    std::vector<const char*> general = {"Do you really talk in the general chat ?", "<img src=\"https://media.tenor.com/vi0bP5tmmIwAAAAM/who-cares.gif\" width=\"262.5\" height=\"262.5\" alt=\"Who Cares GIF - Who Cares GIFs\" loading=\"lazy\">"};

    std::vector<const char*> & sentences = { general };

    if (teamonly)
    {
        // this is a team message
        std::vector<const char*> & sentences = { team };
    }
    // if it is a general message, we have nothing to do because it is already on the general vector

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}


const char* GetDecoyStartSetence()
{
    std::vector<const char*> sentences = {"This decoy is useful as you", "We could say it is your clone, you only make diversion too", "This is actually a decoy and not a flashbang"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}

const char* GetDecoyStopSetence()
{
    std::vector<const char*> sentences = {"Your clone just die !", "OK", "This decoy help us, we'll remember"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}

const char* GetFakeFailedSentence()
{
    std::vector<const char*> sentences = {"Nice fake", "maybe next time you will got it ?"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}

std::string GetRoundEndSentence()
{
    std::vector<std::string> sentences = {"EZ", "worst round I ever seen", "I want to say, nobody here is good at this game"};

    srand(time(NULL));
    unsigned long long len = sizeof(sentences) / sizeof(sentences[0]);

    return sentences[rand() % len];
}
