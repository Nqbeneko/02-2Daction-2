#include"DxLib.h"
#include "screen.h"
#include "map.h"

const int MapData[MapHeight][MapWidth] =
{
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,

    31,0 ,0 ,0 ,23,  23,23,23,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,23,23,23,  23,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  23,23,23,23,23,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    38,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,36,

    41,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,41,
    23,23,23,23,23,  23,23,23,23,23,  23,23,23,23,23,  23,23,23,23,23,  23,23,23,23,23,
    30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,
    30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,
    30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,
};


void InitMap(Map& map)
{
    //マップチップをロード
    LoadDivGraph("img/platforms.png", MapChipXnum * MapChipYnum, MapChipXnum, MapChipYnum, MapChipSize, MapChipSize, map.mapChipImg);

    map.BacScreenImg[0] = LoadGraph("img/Clouds 3/1.png", TRUE);
    map.BacScreenImg[1] = LoadGraph("img/Clouds 3/2.png", TRUE);
    map.BacScreenImg[2] = LoadGraph("img/Clouds 3/3.png", TRUE);
    map.BacScreenImg[3] = LoadGraph("img/Clouds 3/4.png", TRUE);

    //マップチップの大きさと中心座標を取得
    for (int iy = 0; iy < MapHeight; iy++)
    {
        for (int ix = 0; ix < MapWidth; ix++)
        {
            MapChip& mapChip = map.MapChips[iy][ix];
            mapChip.w = MapChipSize;
            mapChip.h = MapChipSize;
            mapChip.chipKind = MapData[iy][ix];

            mapChip.pos = VGet(ix * mapChip.w + mapChip.w * 0.5f, iy * mapChip.h + mapChip.h * 0.5f, 0);
        }
    }
    
}

void DrawMap(Map& map)
{
    DrawBox(0, 0, ScreenWidth, ScreenHeight, GetColor(150, 150, 150), TRUE);

    /*DrawExtendGraph(0, 0, 800, 480, map.BacScreenImg[0], TRUE);
    DrawExtendGraph(0, 0, 800, 480, map.BacScreenImg[1], TRUE);
    DrawExtendGraph(0, 0, 800, 480, map.BacScreenImg[2], TRUE);
    DrawExtendGraph(0, 0, 800, 480, map.BacScreenImg[3], TRUE);*/

    for (int iy = 0; iy < MapHeight; iy++)
    {
        for (int ix = 0; ix < MapWidth; ix++)
        {
            MapChip& mapChip = map.MapChips[iy][ix];
            //int imgIndex = MapData[iy][ix];
            if (mapChip.chipKind != 0)
            {
                DrawGraph(static_cast<int>(mapChip.pos.x - mapChip.w * 0.5f),
                    static_cast<int>(mapChip.pos.y - mapChip.h * 0.5f),
                    map.mapChipImg[mapChip.chipKind], TRUE);
            }
        }
    }
}