//Cracked by Roath
// Room: /d/beijing/east/xiaojing3.c

inherit ROOM;

void create()
{
	set("short", "小径");
	set("long", @LONG
你正走在一条石板路上，路旁古树参天，花草丛中蝴蝶纷飞，
不时还可以看到几只小兽从旁边跑过。向南走就进紫禁城了。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"xiaojing2",
  "northup" : __DIR__"guanmiaoting",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
