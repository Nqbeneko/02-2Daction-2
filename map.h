#pragma once

//-------------------------------------
//�@�萔
//-------------------------------------
const int MapChipSize = 32;                 // 1�̃}�b�v�`�b�v�̃T�C�Y
const int MapWidth = 800 / MapChipSize;     // �}�b�v�̉���
const int MapHeight = 480 / MapChipSize;   // �}�b�v�̏c��

const int MapChipXnum = 7;
const int MapChipYnum = 7;

struct MapChip
{
	VECTOR pos;		//���W
	float w, h;		//���A����
	int chipKind;	//�}�b�v�`�b�v�̔ԍ�
};

struct Map
{
	MapChip MapChips[MapHeight][MapWidth];
	int mapChipImg[49];
	int BacScreenImg[4];
};

struct sMapLayer
{
	int** mapData;      //�}�b�v�`�b�v�̂Q�����z��
	int mapXNum;        //�}�b�v�`�b�v���������ɕ���ł��鐔
	int mapYNum;        //�}�b�v�`�b�v���c�����ɕ���ł��鐔
};

void InitMap(Map &map);

void DrawMap(Map& map);

bool LoadMapLayer(sMapLayer& dst,const char*mapCSVFileName);

void DrawMapLayer(sMapLayer& layer);
