//Cracked by Roath
// room: /mingjiao/shulin1.c
// Zhangchi 3/00

inherit ROOM;

void create()
{
        set("short", "树林");
        set("long", @LONG
树林里光线暗淡，只能听见头顶上传来一些鸟儿的啼鸣。偶而从茂密
的叶间透过的一线光伴着落叶在飞舞。朽木腐烂的气味和身後传来野兽的
啸声使人不觉犹豫了前进的脚步。树上有个牌子(paizi)。
LONG );

        set("item_desc", ([
                "paizi"  : "逢林莫入。\n",
        ]));
        set("exits", ([
                "west" : __DIR__"shulin2",
                "east" : __DIR__"shanlu3",
        ]));

        set("outdoors", "mingjiao" );
	set("resource/grass", 1);
	set("cost", 1);

        setup();
        replace_program(ROOM);
}
