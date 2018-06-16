//Cracked by Roath
// Room: /city/majiu.c
// Cleansword 1996/12/01

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", YEL"马厩"NOR);
        set("long", @LONG
这是草棚边的马厩，常年供应新鲜草料。据说此地民风淳朴，马夫们会把
马牵到马厩好生照看，将它们喂饱饮足，再洗刷得干乾净净，一直伺候到客人
上路。马厩中堆放著几堆草料，正中有一口泔槽。
LONG
        );

        set("objects", ([
		"/d/shaolin/npc/ma-fu" : 1,
		"/clone/horse/liuma" : 2,
		"/clone/horse/hongma" : 1,
		"/d/shaolin/obj/caoliao" : 2,
        ]));

        set("exits", ([
		"east" : __DIR__"shack",
        ]));

//	set("no_fight", 1);
        set("resource/water",1);
        set("cost",1);
	set("outdoors", "emei");

        setup();
        replace_program(ROOM);
}
