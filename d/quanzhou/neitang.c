//Cracked by Roath

inherit ROOM;

void create()
{
	set("short", "内堂");
	set("long", @LONG
这里是药铺的内堂，东首摆了一个书架，上面放了不少医书。此
外还有几张桌椅(chair)。看来大概是药铺接待客人的地方。
LONG
	);
	set("exits", ([ 
 	"out" : __DIR__"yaopu",
]));
	set("no_clean_up", 0);

	set("item_desc", ([
	"chair" : "一张椅子，抹拭得很干净，椅背刻着双龙抢珠的图案，
两条龙刻得甚是生动，张牙舞爪地抢夺一个镶在椅背上青光发亮的铁球(Iron Ball)。\n",
]));
	setup();
}


void init()
{
	add_action("do_push","zhuan");
	add_action("do_push","turn");
}

int do_push(string arg)
{
	object me;
	me = this_player();
	if( !arg || arg == "" ) return 0;
	if( arg == "ball" || arg == "qiu") 
	{
	message_vision("$N走向西首一张椅子，伸手在椅背铁球上一按……\n\n"+
	"椅子缓缓向一边移去，露出一个黑黝黝的大洞。\n",me);
        set("exits/down", __DIR__"yaopu_mishi");
        remove_call_out("close_door");
        call_out("close_door",15,me);	
		return 1;
	}
	else
		return notify_fail("你要干什么？\n");
}

void close_door()
{
	tell_room(this_object(),"椅子缓缓移回原位，遮住了地洞。\n");
	delete("exits/down");
}
