//Cracked by Roath
// road: /zhongnan/haoshanxiaojing4.c

inherit ROOM;

void create()
{
        set("short","後山小径");

        set("long",@LONG
这後山小路蜿蜒於终南山区中，也不知通往何处。只见浓荫蔽天，越
走越是阴森，越行越是荒凉，不时还有野兽吼声传来，令人心中发毛。往
西北和东南各是一条阴森森的小径。
LONG);

		  set("exits",([ "northwest" : __DIR__"haoshanxiaojing3",
								"southeast" : __DIR__"haoshanxiaojing5",
							 ])
			  );
	  set("cost",2);
	  set("outdoors", "zhongnan");

		setup();

}
