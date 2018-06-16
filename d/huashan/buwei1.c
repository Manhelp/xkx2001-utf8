//Cracked by Roath
// square.c

#include <ansi.h>
inherit ROOM;
string day_event() {return NATURE_D->outdoor_room_event();}

void create()
{
	set("short", "客厅");
	set("long", @LONG
这是华山掌门岳不群的居所「有所不为轩」，此处是前厅，厅上挂着
「正气堂」三字匾额。厅中很宽敞，却没什么摆设，靠墙放着两把交椅，
这里是岳不群议事、授徒的地方，后面则是个花园。客厅东面有间偏厅。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
	    "north" : __DIR__"square",
	    "south" : __DIR__"huayuan",
	    "east" : __DIR__"pianting", 
	]));

	set("objects", ([ 
	    CLASS_D("huashan") + "/buqun" : 1,
	]));

	set("no_clean_up", 0);

	set("valid_startroom",1);

	set("cost", 1);
	setup();

//	"/clone/board/huashan_b"->foo();
}

void init()
{
	object ob, me = this_player();
	int level;

	//destruct duplicated Yue, Ryu.
	if( objectp( ob = present("yue buqun 2", this_object()) ) )
	destruct(ob);

/*
	if ( mapp(me->query("family")) && me->query("family/family_name") == "华山派" ) {
	   if ( me->query_skill("buddhism",1) > 0 && me->query_skill("ziyin-yin",1) < 1 ) {
		level = me->query_skill("buddhism", 1);
		me->delete_skill("buddhism");
		me->set_skill("ziyin-yin", level+1);
		tell_object(this_player(),HIR"\n禅宗心法已自动更改为紫氤吟。\n"NOR);
	   }

	   if ( me->query_skill("taoism",1) > 0 && me->query_skill("zhengqi-jue", 1) < 1 ) {
		level = me->query_skill("taoism",1);
		me->delete_skill("taoism");
		me->set_skill("zhengqi-jue", level+1);
		tell_object(this_player(),HIR"道学心法已自动更改为正气诀。\n\n"NOR);
	   }
	}
*/
	if ( me->query_temp("marks/帖") ) {
		me->delete_temp("marks/帖");
	}

	if ( me->query("yue") ) {
		me->set("huashan/yue", 1);
		me->delete("yue");
	}

	if ( me->query("ning") ) {
		me->set("huashan/ning", 1);
		me->delete("ning");
	}

	if ( me->query("feilong") ) {
		me->set("huashan/feilong", 1);
		me->delete("feilong");
	}

//      add_action("do_jump","jump");
	add_action("do_kill","kill");
	add_action("do_hit","hit");
	add_action("do_throw","throw");
}

int do_kill(string arg)
{
	object ob, ob1, me = this_player();

	if ( !arg || arg == "" ) return 0;

	if ( !ob=present(arg, environment(me)) ) return 0;

	if ( ob->query("family/family_name") == "华山派" && me->query("family/family_name") != "华山派" ) {
	   message_vision("$n对著$N喝道：「"+RANK_D->query_rude(ob)+"！今日不是你死就是我活！」\n", ob, me);    
	
	   if ( ob1=present("yue buqun", environment(me)) ) {
		message_vision("$N一声冷笑：大胆狂徒！竟敢在华山上行凶杀人，当我华山派好欺负么？\n", ob1);
		ob1->kill_ob(me);
		return 1;
	   }

	   return 0;
	}
	else if ( ob->query("family/family_name") == "华山派" && ob->query("id") != "yue buqun" 
	&& ob->query("id") != "ning zhongze" && me->query("family/family_name") == "华山派" ) {
	   message_vision("$n对著$N喝道：「"+RANK_D->query_rude(ob)+"！今日不是你死就是我活！」\n", ob, me);

	   if ( ob1=present("yue buqun", environment(me)) ) {
		message_vision("$N气得大骂：真是越来越有出息了！自己同门竟自相残杀！给我都到思过崖去面壁！\n", ob1);
		return 1;
	   }

	   return 0;
	}

	return 0;
}

int do_hit(string arg)
{
	object ob, ob1, me = this_player();

	if ( !arg || arg == "" ) return 0;

	if ( !ob=present(arg, environment(me)) ) return 0;

	if ( ob->query("family/family_name") == "华山派" && me->query("family/family_name") != "华山派" ) {
	   message_vision("$n对著$N大喝一声：看招！\n",ob, me);

	   if ( ob1=present("yue buqun", environment(me)) ) {
		message_vision("$N一声冷笑：大胆狂徒！竟敢在华山上偷袭伤人，当我华山派好欺负么？\n", ob1);
		ob1->kill_ob(me);
		return 1;
	   }

	   return 0;
	}
	else if ( ob->query("family/family_name") == "华山派" && ob->query("id") != "yue buqun"
	&& ob->query("id") != "ning zhongze" && me->query("family/family_name") == "华山派" ) {
	   message_vision("$n对著$N喝道：「"+RANK_D->query_rude(ob)+"！今日不是你死就是我活！」\n", ob, me);

	   if ( ob1=present("yue buqun", environment(me)) ) {
		message_vision("$N气得大骂：真是越来越有出息了！自己同门竟自相残杀！给我都到思过崖去面壁！\n", ob1);
		return 1;
	   }

	   return 0;
	}

	return 0;
}

int do_throw(string arg)
{
	object victim, ob1, ob, me = this_player();
	string what, who;

	if( !arg
        ||      sscanf(arg, "%s at %s", what, who)!=2)
                return notify_fail("命令格式: throw <物品> at <某人>。\n");

	ob = present(what, me);
        if( !ob ) ob = present(arg, environment(me));
	if( !ob ) return notify_fail("你要扔什么？\n");

        if (ob->query("no_drop"))
                return notify_fail("这个东西不能离开你。\n");

        if (!(victim = present(who, environment(me))))
                return notify_fail("这里没有你的目标。\n");

        if (!victim)
                return notify_fail("这里并无此人！\n");

        if (!living(victim))
                return notify_fail("这不是活物！\n");
	
	if ( victim->query("family/family_name") == "华山派" && me->query("family/family_name") != "华山派" ) {
	   message_vision("$n对著$N大喝一声：看招！\n",victim, me);

	   if ( ob1=present("yue buqun", environment(me)) ) {
		message_vision("$N一声冷笑：大胆狂徒！竟敢在华山上偷袭伤人，当我华山派好欺负么？\n", ob1);
		ob1->kill_ob(me);
		return 1;
	   }

	   return 0;
	}
	else if ( victim->query("family/family_name") == "华山派" && victim->query("id") != "yue buqun"
	&& victim->query("id") != "ning zhongze" && me->query("family/family_name") == "华山派" ) {
	   message_vision("$n对著$N喝道：「"+RANK_D->query_rude(ob)+"！今日不是你死就是我活！」\n", victim, me);

	   if ( ob1=present("yue buqun", environment(me)) ) {
		message_vision("$N气得大骂：真是越来越有出息了！自己同门竟自相残杀！给我都到思过崖去面壁！\n", ob1);
		return 1;
	   }

	   return 0;
	}

	return 0;
}

int do_jump(string arg)
{
	object me = this_player();

	if ( !arg || arg == "" ) return 0;

	if ( arg == "bian" || arg == "board" ) {
	   if ( me->query_skill("dodge") > 50 ) {
	      write("你乘着大家一个不留神，跳上了匾额。\n");
	      me->move(__DIR__"bian");
	   }
	   else {
	      write("你乘着大家一个不留神，纵身想跳上匾额，怎奈轻功不济，未能如愿。\n");
	   }

	   return 1;
	}
	
	return 0;
}

int valid_leave(object me, string dir)
{
	mapping myfam;
	myfam = (mapping)me->query("family");
/*
	if ( (!myfam || myfam["family_name"] != "华山派") && dir != "north" ) {
	   if ( present("yue buqun", environment(me)) )
		return notify_fail("岳不群拦身说：那是本派重地，外人不能随易出入！\n");

	   if ( present("ning zhongze", environment(me)) )
		return notify_fail("宁中则拦在你身前说：抱歉，外人不能随易出入本派重地！\n");
	}

	if ( dir == "north" && (day_event() == "event_night" || day_event() == "event_midnight") )
        	return notify_fail("华山总所此时已然关闭，天亮时才能通行！\n");
*/

	return ::valid_leave(me, dir);
}
