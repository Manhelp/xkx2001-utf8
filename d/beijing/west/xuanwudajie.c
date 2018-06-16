//Cracked by Roath
// Room: /d/beijing/west/xuanwudajie.c

inherit ROOM;

void create()
{
	set("short", "宣武门大街");
	set("long", @LONG
这是繁华热闹的宣武门大街，大街街面宽阔，车水马龙，
川流不息，人群熙熙攘攘，来来往往。街边上耍枪买艺、百货
小吃，应有尽有，帝都风貌可见一斑。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
  "northeast" : __DIR__"lingjing",
  "south" : __DIR__"xuanwudajie2",
  "north" : __DIR__"fuchengmenjie2",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}
