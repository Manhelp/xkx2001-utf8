//Cracked by Roath
// huashan-jianfa.c ��ɽ���� 
// qfy July 9, 1996

inherit SKILL;

mapping *action = ({
([	"action":"$Nһ�С����Ƴ�ᶡ��������鶯��ӯ������$w����$n��$l",
	"force" : 150,
        "dodge" : 5,
	"parry" : 5,
	"damage": 15,
	"lvl" : 0,
	"skill_name" : "���Ƴ��",
	"damage_type":	"����"
]),
([	"action":"$Nʹ�����з����ǡ������Ʒ���������ڲ�������ţ�����$n��$l",
	"force" : 180,
        "dodge" : 5,
	"parry" : 5,
	"damage": 25,
	"lvl" : 9,
	"skill_name" : "�з�����",
	"damage_type":	"����"
]),
([	"action":"$N��������һ�С�����������$w���϶��»���һ���󻡣���$n������ȥ",
	"force" : 220,
        "dodge" : 8,
	"parry" : 8,
	"damage": 30,
	"lvl" : 18,
	"skill_name" : "������",
	"damage_type":	"����"
]),
([	"action":"$N��ǰ����һ���������ھ�������$wʹ�����׺���ա��������޳��ֱ��$n",
	"force" : 250,
        "dodge" : 10,
	"parry" : 10,
	"damage": 35,
	"lvl" : 25,
	"skill_name" : "�׺����",
	"damage_type":	"����"
]),
([	"action":"$N���е�$w������ҵ�һ�Σ�ʹ��������ӭ�͡����ź�������ֱ��$n��$l",
	"force" : 280,
        "dodge" : 15,
	"parry" : 15,
	"damage": 40,
	"lvl" : 32,
	"skill_name" : "����ӭ��",
	"damage_type":	"����"
]),
([	"action":"$N����Ծ��һʽ�������ա����������콣Ӱ��$w��$n�����ȥ",
	"force" : 310,
        "dodge" : 15,
	"parry" : 15,
	"damage": 45,
	"lvl" : 40,
	"skill_name" : "������",
	"damage_type":	"����"
]),
([	"action":"$N�������У�$w�Ƴ�ѩ����â���ӳ����ޱ���ľ����һ������һ���׵ع���$n",
	"force" : 350,
        "dodge" : 10,
	"parry" : 10,
	"damage": 55,
	"lvl" : 48,
	"skill_name" : "�ޱ���ľ",
	"damage_type":	"����"
]),
([      "action":"$N�����й�ֱ���������������;��Ȼת�����ϣ�����ɽ�������˵��Ǳ���޷�",
	"force" : 390,
        "dodge" : 5,
	"parry" : 5,
        "damage": 65,
        "lvl" : 55,
        "skill_name" : "��ɽ����",
        "damage_type":  "����"
]),
([      "action":"$N����б��һ����һ�С��Ű�ɭɭ��������ɭȻ��������$n��Χ����",
        "force" : 410,
        "dodge" : 8,
	"parry" : 8,
        "damage": 75,
        "lvl" : 62,
        "skill_name" : "�Ű�ɭɭ",
        "damage_type":  "����"
]),
([	"action":"$N˫������$w����â������һʽ����˫�޶ԡ���Ԧ�����Ҿ��׵���$n���",
	"force" : 450,
        "dodge" : 10,
	"parry" : 10,
	"damage": 85,
	"lvl" : 70,
	"skill_name" : "��˫�޶�",
	"damage_type":	"����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("zixia-gong", 1) < 25)
		return notify_fail("�����ϼ�񹦻��̫ǳ��\n");
	return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
	level   = (int) me->query_skill("huashan-jianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("��ľ�����������ɽ������\n");
	me->receive_damage("jingli", 25, "����͸֧��������");
	return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huashan-jianfa/" + action;
}
