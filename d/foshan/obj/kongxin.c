//Cracked by Roath
// Jay 5/23/96

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("空心菜", ({"kongxin cai", "cai"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一棵绿油油的空心菜。\n");
                set("unit", "棵");
                set("food_remaining", 3);
                set("food_supply",20 );
        }
}

