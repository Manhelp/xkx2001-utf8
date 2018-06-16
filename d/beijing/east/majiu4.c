//Cracked by Roath
// Room: /d/beijing/east/majiu4.c

inherit ROOM;

void create()
{
	set("short", "马厩");
	set("long", @LONG
这是京城跑马场边上的一间马厩，马厩中堆放著几堆草料，
正中有一口泔槽，边上有一块沙地。此处是为即将上跑马场的
马匹歇养脚力之用。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"majiu5",
  "east" : __DIR__"majiu3",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
