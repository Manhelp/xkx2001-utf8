//Cracked by Roath
// /d/emei/obj/coffin.c 石棺

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW"石棺"NOR, ({ "coffin", "guan cai", "guan" }) );
	set_weight(3000);
	set_max_encumbrance(50000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "口");
                set("long", "这是一具白玉石雕成的石棺。\n");
		set("value", 1000);
//		set("material", "stone");
		set("no_get",1);
		set("no_drop",1);
		set("arrow_count", 3);
	}
	set("opened", 0);
	setup();
}

void init()
{
	add_action("do_open", "open");
	add_action("do_put", "put");
}

int is_container() { return query("opened"); };

int do_open(string arg)
{
	object me = this_player();
	object ob = this_object();
	object rwj, book;

	if ( !arg && ( arg != "coffin" ) && ( arg != "guan" ) )
		return notify_fail("什么？\n");

	if ( query("opened") )
		return notify_fail("白玉石棺盖已经是开的了。\n");

	message_vision("$N运足气，双手用力去搬白玉石棺盖。\n", me);
	if (query("arrow_count") > 0) {
		remove_call_out("shoot_arrow");
		call_out("shoot_arrow", 1, me);	
		return 1;
	}

	me->add("jingli", -(20+random(20)));
	me->add("qi", -(20+random(20)));

	if ( (int)me->query_str() < 22 ) {
		return notify_fail("你没那么大力气搬动棺盖。\n");
	}

	message_vision("$N用力搬开白玉石棺盖。\n", me);
	ob->set("opened", 1);
        ob->set("long", "这是一具白玉石雕成的石棺，里面躺着一具骸骨。\n");
//	rwj = new(__DIR__"ruanwei-jia");
//	if (rwj) 
//	rwj->move(ob); 
	book = new(__DIR__"jiuyin-jing1");
	if (book) 
	book->move(ob);

	return 1;
}

int shoot_arrow(object me)
{
	if ((int)query("arrow_count") < 1 ) return 0;

	switch ((int)query("arrow_count")) {
	case 3:
		message_vision(HIY"忽然间几支短箭从棺后一个机关里射出来，直射向$N的面门！\n"NOR, me);
		break;
	case 2:
		message_vision(HIY"忽然间几支短箭从棺后一个机关里射出来，直射向$N的咽喉！\n"NOR, me);
		break;
	case 1:
		message_vision(HIY"忽然间几支短箭从棺后一个机关里射出来，直射向$N的前胸！\n"NOR, me);
		break;
	default:
		message_vision(HIY"忽然间几支短箭从棺后一个机关里射出来，直射向$N的面门！\n"NOR, me);
		break;
	}
	add("arrow_count", -1);

	if ( (int)me->query_dex() > (22+random(8))) {
		message_vision("$N头一低，避开短箭，跳到一旁。\n", me);
		return 1;
	}

	else if ( (int)me->query_dex() > (20+random(4))) {
		message_vision("$N欲闪身避开，却被其中一支短箭射中右肩，晕死过去。\n", me);
		me->add("qi", -50);
		me->unconcious();
		return 1;
	}

	else {
		message_vision("$N躲避不及，被短箭射个正好，倒在地上。\n", me);
		me->receive_damage("qi", 50, "被毒箭射死了");
		me->die();
		return 1;
	}
	return 0;
}

int do_put()
{
	write("什么？\n");
	return 1;
}

void reset()
{
	set("opened", 0);
}
