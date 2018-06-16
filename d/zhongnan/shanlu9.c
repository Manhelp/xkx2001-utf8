//Cracked by Roath
// road: /zhongnan/shanlu9.c

inherit ROOM;

void create()
{
        set("short","山路");

        set("long",@LONG
这条山路盘终南山主峰而上，山路贴着石璧凿出，只容一人可过，形
势极为险峻。往远处望去。群山环绕，列於脚下，百里美景尽收眼底，顿
时令人豪气陡声，想要长啸一声。往东下和西上各是一条山路。
LONG);

        set("exits",([ "westup" : __DIR__"shanlu10",
                        "eastdown" : __DIR__"shanlu8",
                      ])
           );
	  set("cost",2);
	  set("outdoors", "zhongnan");

        setup();

        replace_program(ROOM);
}
