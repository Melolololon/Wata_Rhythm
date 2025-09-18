#pragma once
#include<string>
#include<array>
#include<vector>

#include"Block.h"

#include<Sound.h>
#include<Values.h>
#include<FrameTimer.h>

class MusicalScoreManager 
{
private:
	MusicalScoreManager() {}
	~MusicalScoreManager() {}

	void LoadHumen(const std::wstring& musicFolderPath);
	void CheckBlockMoveStart();

	/// <summary>
	/// 曲と譜面のズレを読み込み。
	/// </summary>
	void LoadDelayTime();

	/// <summary>
	/// 曲の再生
	/// </summary>
	void PlayMusic();

	/// <summary>
	/// 譜面の再生
	/// </summary>
	void PlayHumen();

private:
	const std::string SOUND_KEY = "Music";


	// テンポ
	float bpm = 0;
	// 16分の時間
	DWORD haku16Time = 0;
	// 最後に譜面を確認(ノーツがあるか確認)した時間
	DWORD humenCheckTime = 0;
	// 現在の時間
	DWORD nowTime = 0;
	// 前フレームの時間
	DWORD preTime = 0;
	// 最後に確認した譜面の縦列の添え字
	unsigned int currentHumenIndex = 0;

	// これがMaxになったら曲を再生
	MelLib::FrameTimer musicDelayTimer;
	MelLib::FrameTimer humenDelayTimer;

	// 曲名
	std::wstring musicName;
	// 作曲者名
	std::wstring artistName;

	// 譜面データ
	std::vector<std::array<std::unique_ptr<Block>, 2>> humen;
	// ブロックの配列番号(次に反応するブロックの指定用)
	std::vector<MelLib::Value2<unsigned int>>blockIndex;
	unsigned int nextBlockIndex = 0;
	
	// 次にキーを押した時に反応するブロック
	// 同時押し実装するならこれ配列にすること
	Block* pNextBlock = nullptr;

	// 譜面を最後まで読み込み終わったかどうか
	bool changeNextBlockEnd = false;
	bool lastBlockPush = false;

	// 移動を終えたブロックを格納する配列。プレイヤーを歩かせるのに使用
	std::vector<Block*>moveEndBlock;

	// キーを押さずにミスになったかどうか
	bool notPushMiss = false;

	bool easy = false;

	// デリーと番号
	int dPos = 0;
public:
	MusicalScoreManager(MusicalScoreManager& m) = delete;
	MusicalScoreManager operator=(MusicalScoreManager & m) = delete;
	static MusicalScoreManager* GetInstance();

	void SetMusicData( const std::wstring& musicName, const std::wstring& artistName, const float& bpm,const bool easy);

	/// <summary>
	/// 曲と譜面のロードをします。リトライ時もこれ呼び出してください。
	/// </summary>
	/// <param name="musicFolderPath"></param>
	void Load();

	
	
	void BlockMoveStart();

	/// <summary>
	/// 停止。終了、ポーズ中に止める用
	/// </summary>
	void Stop();

	void Update();
	void Draw();

	/// <summary>
	/// 読み込んだ譜面情報を削除します
	/// </summary>
	void Finalize();

	void Play();

	// 左側のノーツの現在の位置とジャストタイミングとの差分を取得します。(これの戻り値を判定確認に使う)
	short GetLeftTimingDifferenceFrame();
	// 上の関数の右側版
	short GetRigthTimingDifferenceFrame();

	// キーを押したときに反応するブロックの切り替え
	void  ChangeNextBlock();

	bool GetHumenEnd() const { return changeNextBlockEnd;}
	bool GetLastBlockPush() const { return lastBlockPush;}

	const std::vector<Block*>& GetMoveEndBlock() { return moveEndBlock; }

	void TrueBlockMissFlag()const { pNextBlock->TrueMiss(); }

	/// <summary>
	/// ブロックの数を取得します
	/// </summary>
	/// <returns></returns>
	size_t GetBlockIndexNum()const { return blockIndex.size(); }

	bool GetNotPushMiss()const { return notPushMiss; }

	std::wstring GetMusicName() { return musicName; }
};

