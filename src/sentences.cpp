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

