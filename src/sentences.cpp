#include <ctime>
#include <cstring>
#include <cstdlib>

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
    const char* sentences[] = {"the ground is better at this game", "maybe you should try to shoot at the ground for get a kill"};

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

