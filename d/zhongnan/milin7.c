//Cracked by Roath
// road: /zhongnan/milin7.c

inherit ROOM;

void create()
{
        set("short","树林");

        set("long",@LONG
走在林中，你只闻铮铮琴声，一股淡淡白烟，带着极甜的花香，自密
林深处传出。一群乳白色的蜜蜂在你身旁飞来飞去。不论往哪ㄦ走尽是茂
密的树林。
LONG);


        set("exits",([ "south" : __DIR__"milin8",
                        "east" : __DIR__"milin5",

                      ])
           );
	  set("cost",2);
	  set("outdoors", "zhongnan");
        setup();
        replace_program(ROOM);
}
