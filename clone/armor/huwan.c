//Cracked by Roath
// huwan.c

#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
	set_name( WHT"铁护腕"NOR, ({ "hu wan", "huwan" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "双");
                set("long", "这是一件皮质的护腕，上面满布铁钉，用以保护腕部。\n");
		set("value", 500);
		set("material", "iron");
		set("armor_prop/armor", 5);
		set("shaolin",1);
	}
	setup();
}
