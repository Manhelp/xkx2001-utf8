//Cracked by Roath
// dianban.c 店伴

inherit NPC;
inherit F_DEALER;

string ask_me(string);

void create()
{
        set_name("店伴", ({ "dian ban", "waiter" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long",
                "这位店伴正伏在桌上打盹。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "小哥");
        set("vendor_goods", ({
                "/clone/food/jiudai",
                "/d/heimuya/obj/peanut",
                "/d/heimuya/obj/candou",
                "/d/heimuya/obj/niurou",
        }));

        setup();
}

void init()
{       
        object ob; 
        mapping myfam; 

        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() ) {
                if ( (myfam = ob->query("family")) 
                && myfam["family_name"] == "丐帮" 
                && ob->query_skill("begging",1) > 10 )
                {
                        remove_call_out("saying");
                        call_out("saying", 0, ob);
                }
                else
                { 
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "店伴笑咪咪地说道：这位" + RANK_D->query_respect(ob)
                                + "，进来喝杯茶，歇歇腿吧。\n");
                        break;
                case 1:
                        say( "店伴用脖子上的毛巾抹了抹手，说道：这位" + RANK_D->query_respect(ob)
                                + "，请进请进。\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        say("\n店伴大喝一声：你这臭要饭的进来干什麽？ 给我滚出去！\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);
        
}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        ob->move("/d/heimuya/northstreet1");
        message("vision","只听“乒”地一声，" +  ob->query("name") +
                "被人从醉仙楼里一脚踢了出来，狼狈万状的逃开了。\n", environment(ob), ob);
}
int accept_kill(object obj)
{
        command("chat 各位客官救命啊！ " + obj->name() + "这个" 
        + RANK_D->query_rude(obj) + "要杀了我！");
}


