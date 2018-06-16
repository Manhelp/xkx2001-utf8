//Cracked by Roath
// tyroad7.c 崎岖山路
// by Marz 
// xQin 04/01

inherit ROOM;

#include "/d/wudang/feng.h"

void create()
{
	set("short", "崎岖山路");
	set("long", @LONG
你走在一条崎岖狭隘的山路上，一边是峭壁，一边是悬崖。高高的天柱
峰(feng)笼罩在云雾中，隐约可见。可是身旁的进香客和游人都仔细地町着
自己的脚下，不敢抬头望一眼，惟恐一不小心摔下去。更有强人趁机打劫，
行人无不噤声闭气，只求快点敢路。
LONG
	);
	set("outdoors", "wudang");

	set("exits", ([
		"northup" : __DIR__"tyroad6",
		"eastdown" : __DIR__"tyroad8",
	]));

    set("item_desc", ([
        "feng" : (:look_feng:),
    ]));

	set("cost", 2);
	setup();
}

void init()
{
        add_action("look_feng", "look");
}
