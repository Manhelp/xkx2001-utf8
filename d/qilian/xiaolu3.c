//Cracked by Roath
// Summer 9/12/96
#include "room.h"

inherit ROOM;

void create()
{
        set("short", "��С·");
        set("long", @LONG
��ǰ��һ��һ����С·���ش�Խ��ԽƫƧ��·��Խ��Խ���ء�
LONG
        );
        set("exits", ([
                "north" : __DIR__"xiaolu"+(random(5)+1),
                "south" : __DIR__"xiaolu"+(random(5)+1),
                "west" : __DIR__"xiaolu"+(random(5)+1),
		"east" :__DIR__"xiaolu4",
        ]));


	set("cost", 1);
        setup();
        set("outdoors","qilian-shan");
        replace_program(ROOM);
}