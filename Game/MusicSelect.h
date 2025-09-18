#pragma once
#include <Scene.h>
#include"Sprite2D.h"
#include<unordered_map>
#include"FrameTimer.h"
class MusicSelect :
    public MelLib::Scene
{
private:
	MelLib::FrameTimer addTimer;

	std::unordered_map<unsigned short, std::wstring>musicNames;
	short selectMusicNum = 0;
	short musicCount = 0;
	// [曲名][bpm]
	std::unordered_map<std::wstring, float>bpms;
	std::unordered_map<std::wstring, std::wstring>artistNames;
	MelLib::Sprite2D arrow;
	MelLib::Sprite2D arrow2;

	bool easy = false;
private:
	void LoadMusicData();
	// この辺曲選択でも読み込むから別クラス(曲選択シーン)とかに書いたほうがいいかも
	void LoadBPM(const std::wstring& musicFolderPath,float& bpm);
	/// <summary>
	/// 曲名、アーティスト名などの日本語を読み込むための関数
	/// </summary>
	/// <param name="musicFolderPath"></param>
	/// <param name="format"></param>
	/// <param name="refStr"></param>
	void LoadName(const std::wstring& musicFolderPath, const std::wstring& format, std::wstring& refStr,bool file);

public:
	MusicSelect();
	~MusicSelect();
	void Initialize()override;//初期化
	void Update()override;
	void Draw()override;
	void Finalize()override;//終了処理
	Scene* GetNextScene()override;//次のシーンの指定

};

