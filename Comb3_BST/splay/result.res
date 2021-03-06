data:
in_e3.txt
in_e5.txt
in_e7.txt

splay_v1.0:
splay_v1+++:	hard_splay, hard_insert, hard_remove
splay_v1---:	simple_splay, simple_insert, simple_remove

splay_v1.1:
splay_v1*++:	hard_splay, hard_insert, hard_remove
splay_v1*++:	hard_splay, hard_insert, hard_remove
splay_v1*++:	hard_splay, hard_insert, hard_remove
splay_v1*++:	hard_splay, hard_insert, hard_remove

splay_v2.0;
splay_v2+:		hard_splay, simple_insert, simple_remove, hard_top_down_access
splay_v2-:		hard_splay, simple_insert, simple_remove, simple_top_down_access

splay_v2.1:		hard_splay, simple_insert, simple_remove
splay_v2*++: 	undef-linkd, hard_top_down_access
splay_v2*+-: 	undef-linkd, simple_top_down_access
splay_v2*-+: 	def-linkd, hard_top_down_access
splay_v2*--: 	def-linkd, simple_top_down_access


------------------------------------------
global
(ms)			e3		e5		e7
treap			15		1194	23894
set				48		1173	22213
splay_v1+++		26		1663	33498
splay_v1++-		12		1548	33611
splay_v1+-+		8		1563	31804
splay_v1+--		7		1515	31038
splay_v2+		0		1404	29701
splay_v2-		15		1388	27128
splay_v1*+-		8		1552	30047
splay_v1*++		3		1423	32268
splay_v1*--		3		1444	30916
splay_v1*-+		3		1474	29600
splay_v2*++				1483	38139
splay_v2*+-				1465	39185
splay_v2*-+				1611	31532
splay_v2*--				1529	32327


--------------------------------------
splay v1.0
	e5 		e7
set	2218  	34082
+++ 7083	115662
-++	9064
++- 9402
-+- 8096
+-- 8660
--- 9473
--+ 8981
+-+ 8015  	100588


---------------------------------------
splay v2.0 lite
configuration: hard_splay, simple_insert, simple_remove
++: undef-linkd, hard_top_down_access
+-: undef-linkd, simple_top_down_access
-+: def-linkd, hard_top_down_access
--: def-linkd, simple_top_down_access

		e5		e7
v2+		1404	29701
v2-		1388	27128
lite++	1483	38139
lite+-	1465	39185
lite-+	1611	31532
lite--	1529	32327
