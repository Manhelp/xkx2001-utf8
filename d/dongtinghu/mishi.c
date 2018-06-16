//Cracked by Roath

inherit ROOM;

void create()
{
	set("short", "密室");
	set("long", @LONG
这里象是一个地窖，可能是药铺收藏珍贵药物的地方。东首一个
大架子，放着药材和无数小瓷瓶。地上有一只炼药炉，空气中尽是药
味。
LONG
	);
	set("no_clean_up", 0);

    set("objects", ([
         __DIR__"obj/yaolu" : 1,
]));
	setup();
}


void init()
{
	add_action("do_turn","zhuan");
	add_action("do_turn","turn");
	add_action("do_search","search");
}

int do_turn(string arg)
{
	object me;
	me = this_player();
	if( !arg || arg == "" ) return 0;
	if( arg == "ball" || arg == "qiu")
	{
		message_vision("$N坐在椅上，把椅背铁球像右一转，头上开出一洞。\n椅子带着$N升了上去。\n",me);
		me->move(__DIR__"neitang");
		return 1;
	}
	else
		return notify_fail("你要干什么？\n");
}

int do_search(string arg)
{
	object ob,me;
	me = this_player();
	if (!arg || arg == "") return 0;
	
	if (arg == "jia" || arg == "shelf")
	{
		if (query("searched"))
			return notify_fail("你在架子上翻寻了一阵，但什么都没找到。\n");

		switch (random(7))
		{
			case 0:
			ob = new("/d/dongtinghu/obj/yangxin");
			break;
			case 1:
			ob = new("/d/dongtinghu/obj/jinchuang");
			break;
			case 2:
			ob = new("/d/dongtinghu/obj/baicao-dan");
			break;
			case 3:
			ob = new("/d/dongtinghu/obj/yulu-wan");
			break;
			case 4:
			ob = new("/d/dongtinghu/obj/xxqingxin-san");
			break;
			case 5:
			ob = new("/d/dongtinghu/obj/heishi-dan");
			break;
			case 6:
			ob = new("/d/dongtinghu/obj/dali-dan");
			break;
		}

		set("searched",1);		
		message_vision("你从一个小瓶子里找到一颗"+ob->query("name")+"。\n",me);
		ob->move(me);
		return 1;
	}
}	

