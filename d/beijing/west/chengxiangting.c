//Cracked by Roath
// Room: /d/beijing/west/chengxiangting.c

inherit ROOM;

void create()
{
	set("short", "澄祥亭");
	set("long", @LONG
这是一间什麽也没有的空房间。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"zixiangting",
  "southwest" : __DIR__"longzheting",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
