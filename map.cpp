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
    31,0 ,0 ,0 ,44,  42,43,46,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,46,44,45,  42,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    31,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  23,23,23,23,23,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,29,
    38,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,0 ,  42,43,44,41,45,  0 ,0 ,0 ,0 ,0 ,  0 ,0 ,0 ,0 ,36,

    0 ,0 ,2 ,3 ,0 ,  0 ,1 ,0 ,0 ,12,  0 ,0 ,0 ,47,0 ,  0 ,0 ,0 ,9 ,12,  0 ,0 ,10,0 ,40,
    23,23,23,23,23,  23,23,23,23,23,  23,23,23,23,23,  23,23,23,23,23,  23,23,23,23,23,
    30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,
    30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,
    30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,  30,30,30,30,30,
};


void InitMap(Map& map)
{
    //マップチップをロード
    LoadDivGraph("img/platforms.png", MapChipXnum * MapChipYnum, MapChipXnum, MapChipYnum, MapChipSize, MapChipSize, map.mapChipImg);

    map.BacScreenImg[0] = LoadGraph("img/3. NEW CLOUDS/1.png", TRUE);
    map.BacScreenImg[1] = LoadGraph("img/3. NEW CLOUDS/2.png", TRUE);
    map.BacScreenImg[2] = LoadGraph("img/3. NEW CLOUDS/3.png", TRUE);
    map.BacScreenImg[3] = LoadGraph("img/3. NEW CLOUDS/4.png", TRUE);
    map.BacScreenImg[4] = LoadGraph("img/3. NEW CLOUDS/5.png", TRUE);
    map.BacScreenImg[5] = LoadGraph("img/3. NEW CLOUDS/6.png", TRUE);

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
    //DrawBox(0, 0, ScreenWidth, ScreenHeight, GetColor(150, 150, 150), TRUE);

    DrawExtendGraph(0, 0, 800, GameScreenHeight, map.BacScreenImg[0], TRUE);
    DrawExtendGraph(0, 0, 800, GameScreenHeight, map.BacScreenImg[1], TRUE);
    DrawExtendGraph(0, 0, 800, GameScreenHeight, map.BacScreenImg[2], TRUE);
    DrawExtendGraph(0, 0, 800, GameScreenHeight, map.BacScreenImg[3], TRUE);
    DrawExtendGraph(0, 0, 800, GameScreenHeight, map.BacScreenImg[4], TRUE);
    DrawExtendGraph(0, 0, 800, GameScreenHeight, map.BacScreenImg[5], TRUE);

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