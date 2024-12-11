#pragma once

//-------------------------------------
//　定数
//-------------------------------------
const int MapChipSize = 32;                 // 1つのマップチップのサイズ
const int MapWidth = 800 / MapChipSize;     // マップの横幅
const int MapHeight = 480 / MapChipSize;   // マップの縦幅

const int MapChipXnum = 7;
const int MapChipYnum = 7;

struct MapChip
{
	VECTOR pos;		//座標
	float w, h;		//幅、高さ
	int chipKind;	//マップチップの番号
};

struct Map
{
	MapChip MapChips[MapHeight][MapWidth];
	int mapChipImg[49];
	int BacScreenImg[4];
};

struct sMapLayer
{
	int** mapData;      //マップチップの２次元配列
	int mapXNum;        //マップチップが横方向に並んでいる数
	int mapYNum;        //マップチップが縦方向に並んでいる数
};

void InitMap(Map &map);

void DrawMap(Map& map);

bool LoadMapLayer(sMapLayer& dst,const char*mapCSVFileName);

void DrawMapLayer(sMapLayer& layer);
