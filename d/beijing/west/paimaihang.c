//Cracked by Roath
// Room: /d/beijing/west/paimaihang.c

inherit ROOM;

void create()
{
	set("short", "拍卖行");
	set("long", @LONG
这是一间什麽也没有的空房间。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"tianqiao2",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
