//Cracked by Roath
// Room: /d/heimuya/heimulin4.c
// Date: fear 99/12/08

inherit ROOM;




void create()
{
        set("short", "黑木林");
        set("long", @LONG
这是一个幽秘的树林，周围长满黑漆漆的参天巨树。
树林里极是阴暗，你挣大了眼睛也看不清树林里弯曲的
道路。一阵阵风吹过树梢，树叶发出沙沙的响声，令你
不寒而栗。 
LONG
        );

        set("exits", ([
                "north" : __DIR__"heimulin5",
                "east" : __DIR__"heimulin3",
                "south" : __DIR__"heimulin6",
                "west" : __DIR__"heimulin5",
        ]));

        set("outdoors", "heimuya");
        set("cost", 2);
        setup();
        replace_program(ROOM);
}

