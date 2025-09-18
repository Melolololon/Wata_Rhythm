#pragma once

#include<Input.h>

class CheckPushKey
{
public:
	enum class JudgmentType 
	{
		PERFECT,
		GREAT,
		GOOD,
		MISS,
		NONE// ŠÖŒW‚È‚¢‚Æ‚±‚ë‚Å‰Ÿ‚µ‚½
	};



private:
	CheckPushKey(){}
	~CheckPushKey(){}

	JudgmentType CheckJudgmentType(short frame);
	JudgmentType PushProcess(short frame);

	static const std::unordered_map<JudgmentType, short>TIMING_FRAME;
	
public:
	CheckPushKey(CheckPushKey& c) = delete;
	CheckPushKey operator=(CheckPushKey& c) = delete;
	static CheckPushKey* GetInstance();

	void CheckTiming(JudgmentType& timing,bool& keyTrrigerFrame);

	static short GetTimingFrame(JudgmentType type) { return TIMING_FRAME.at(type); }
};

