//Cracked by Roath

#include <ansi.h>
#include <armor.h>

inherit NECK;

void create()
{
	set_name( YEL "围脖" NOR, ({ "wei bo", "bo" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "条");
                set("long", "这是一皮围脖，用以保护颈部。\n");
		set("value", 150);
		set("material", "leather");
		set("armor_prop/armor", 3);
		set("shaolin",1);
	}
	setup();
}
