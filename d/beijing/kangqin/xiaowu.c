//Cracked by Roath
// Room: /d/beijing/kangqin/xiaowu.c

inherit ROOM;

void create()
{
	set("short", "小屋");
	set("long", @LONG
这是一间什麽也没有的空房间。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"shiwu",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
