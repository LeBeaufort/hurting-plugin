#ifndef SENTENCES_HPP
#define SENTENCES_HPP

#include <string>

const char* GetSelfFlashSentence();
const char* GetTeamFlashSentence();
const char* GetFallDamamageSentence();
const char* GetTeamKillSentence();
const char* GetAssistOnMateSentence();
const char* GetAssistSentence();
const char* GetDeathSentence(int team);
const char* GetKillSentence();
const char* GetChatSentence(bool teamonly);
const char* GetDecoyStartSetence();
const char* GetDecoyStopSetence();
const char* GetFakeFailedSentence();
const char* GetRoundEndSentence();

#endif