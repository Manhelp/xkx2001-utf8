//Cracked by Roath
// Room: /d/xiangyang/liangcang.c

inherit ROOM;

void create()
{
	set("short", "粮仓");
	set("long", @LONG
这是一间什麽也没有的空房间。
LONG
	);
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"jicang",
]));

	setup();
	replace_program(ROOM);
}
