#ifndef CONV2_H
#define CONV2_H
#include <libmsp/mem.h>
#include <libfixed/fixed.h>

#define CONV2_WM_LEN 931

__ro_hifram _q15 conv2_wm[931] = {
    _Q15(0.3609372),      _Q15(-0.13929456),   _Q15(-0.06411328),
    _Q15(-0.14308593),    _Q15(-0.07196701),   _Q15(-0.0033705407),
    _Q15(-0.107480586),   _Q15(-0.2735574),    _Q15(-0.16289745),
    _Q15(-0.22797589),    _Q15(-0.25277436),   _Q15(0.24958108),
    _Q15(0.26707667),     _Q15(0.23151354),    _Q15(0.2172853),
    _Q15(0.115045585),    _Q15(-0.14800364),   _Q15(-0.14042354),
    _Q15(-0.095462374),   _Q15(-0.083515786),  _Q15(-0.13962139),
    _Q15(-0.14522715),    _Q15(-0.22158697),   _Q15(-0.09876421),
    _Q15(-0.16188627),    _Q15(-0.17538945),   _Q15(0.15698653),
    _Q15(0.19303845),     _Q15(0.21112143),    _Q15(0.23652866),
    _Q15(-0.1766927),     _Q15(0.20902605),    _Q15(0.17699932),
    _Q15(0.15415812),     _Q15(-0.0985282),    _Q15(-0.042117666),
    _Q15(-0.16297174),    _Q15(-0.32517922),   _Q15(-0.2753498),
    _Q15(0.22888698),     _Q15(0.27671197),    _Q15(0.24031554),
    _Q15(-0.040725734),   _Q15(-0.05759161),   _Q15(-0.2339043),
    _Q15(-0.3816181),     _Q15(-0.1709738),    _Q15(0.0064499252),
    _Q15(-0.06267423),    _Q15(-0.1509559),    _Q15(-0.09641537),
    _Q15(0.16305862),     _Q15(0.16267532),    _Q15(0.114959866),
    _Q15(0.1123951),      _Q15(0.19046764),    _Q15(0.24091792),
    _Q15(-0.18175228),    _Q15(-0.27907127),   _Q15(0.26430374),
    _Q15(0.25816596),     _Q15(0.15859005),    _Q15(-0.19444515),
    _Q15(0.11114047),     _Q15(0.18390478),    _Q15(-0.13913523),
    _Q15(-0.08807733),    _Q15(0.21759671),    _Q15(-0.056879543),
    _Q15(-0.16727133),    _Q15(0.217647),      _Q15(0.10796722),
    _Q15(0.14178887),     _Q15(-0.21224348),   _Q15(0.1366084),
    _Q15(0.21153629),     _Q15(-0.22805062),   _Q15(0.179414),
    _Q15(0.15644209),     _Q15(-0.13518319),   _Q15(-0.26165405),
    _Q15(-0.29142842),    _Q15(0.33904526),    _Q15(0.3045872),
    _Q15(0.14731996),     _Q15(-0.17054336),   _Q15(0.30300108),
    _Q15(-0.32187614),    _Q15(0.23766345),    _Q15(-0.12529898),
    _Q15(-0.18525255),    _Q15(0.019362196),   _Q15(0.14267227),
    _Q15(-0.066376194),   _Q15(-0.16312338),   _Q15(0.08112866),
    _Q15(-0.11497499),    _Q15(-0.114261165),  _Q15(-0.1689259),
    _Q15(-0.14982295),    _Q15(-0.19457501),   _Q15(0.1586672),
    _Q15(-0.15675522),    _Q15(-0.18494356),   _Q15(0.11020727),
    _Q15(0.2773906),      _Q15(-0.09160342),   _Q15(-0.15863352),
    _Q15(-0.08641966),    _Q15(-0.13328733),   _Q15(-0.100243755),
    _Q15(-0.0980888),     _Q15(-0.085418165),  _Q15(-0.12302333),
    _Q15(-0.080859534),   _Q15(-0.08678798),   _Q15(-0.09673444),
    _Q15(-0.092213556),   _Q15(-0.113264404),  _Q15(-0.06574896),
    _Q15(0.20803191),     _Q15(-0.059535686),  _Q15(-0.20031245),
    _Q15(0.21986046),     _Q15(-0.13716839),   _Q15(-0.06557447),
    _Q15(-0.09797433),    _Q15(-0.101940125),  _Q15(-0.12005001),
    _Q15(0.16335763),     _Q15(-0.20774013),   _Q15(0.2930879),
    _Q15(0.21451426),     _Q15(-0.33221337),   _Q15(0.20128575),
    _Q15(-0.09210249),    _Q15(-0.0828328),    _Q15(-0.07360573),
    _Q15(-0.055397853),   _Q15(-0.14062525),   _Q15(0.134806),
    _Q15(-0.13377507),    _Q15(-0.17868239),   _Q15(-0.15986684),
    _Q15(-0.14813046),    _Q15(0.009828783),   _Q15(-0.2903861),
    _Q15(0.24053517),     _Q15(0.12996808),    _Q15(0.23213819),
    _Q15(0.16037333),     _Q15(0.22550586),    _Q15(0.08038039),
    _Q15(0.17181098),     _Q15(0.2095191),     _Q15(0.2994371),
    _Q15(0.2346403),      _Q15(-0.052045558),  _Q15(-0.20150958),
    _Q15(0.24690664),     _Q15(0.31861648),    _Q15(-0.11781082),
    _Q15(-0.19564925),    _Q15(-0.16128547),   _Q15(-0.091589585),
    _Q15(-0.10853873),    _Q15(-0.06517664),   _Q15(-0.12352769),
    _Q15(-0.10310088),    _Q15(0.21637334),    _Q15(0.27449697),
    _Q15(0.2590351),      _Q15(0.19518654),    _Q15(0.22376932),
    _Q15(0.05735408),     _Q15(0.00083802914), _Q15(-0.1670655),
    _Q15(-0.14177682),    _Q15(-0.18917364),   _Q15(-0.22416501),
    _Q15(-0.08660479),    _Q15(-0.20965192),   _Q15(-0.14300439),
    _Q15(-0.1180437),     _Q15(0.090059586),   _Q15(0.13985397),
    _Q15(0.23499921),     _Q15(0.25684708),    _Q15(-0.19229473),
    _Q15(-0.15189227),    _Q15(0.000633089),   _Q15(0.31979463),
    _Q15(0.31759387),     _Q15(-0.11876637),   _Q15(-0.19490325),
    _Q15(-0.210979),      _Q15(-0.21452464),   _Q15(-0.2132381),
    _Q15(-0.115688555),   _Q15(-0.11504711),   _Q15(-0.11230408),
    _Q15(-0.14070489),    _Q15(0.28076756),    _Q15(0.24226594),
    _Q15(0.2524954),      _Q15(-0.18778172),   _Q15(-0.11733316),
    _Q15(-0.21297215),    _Q15(-0.0049772505), _Q15(-0.065803856),
    _Q15(-0.1837601),     _Q15(-0.11910885),   _Q15(-0.13883607),
    _Q15(-0.074483305),   _Q15(-0.1644493),    _Q15(-0.13658844),
    _Q15(-0.11986693),    _Q15(-0.1007273),    _Q15(-0.10516408),
    _Q15(-0.117352),      _Q15(-0.10779163),   _Q15(-0.13680543),
    _Q15(-0.15114696),    _Q15(-0.15629674),   _Q15(-0.19798023),
    _Q15(-0.17590353),    _Q15(-0.09754398),   _Q15(-0.106566094),
    _Q15(-0.18887123),    _Q15(-0.121250436),  _Q15(-0.19053362),
    _Q15(0.1920918),      _Q15(0.20366284),    _Q15(0.09898553),
    _Q15(0.13869797),     _Q15(0.06750669),    _Q15(0.16671205),
    _Q15(-0.029207718),   _Q15(0.17891459),    _Q15(0.10360963),
    _Q15(0.11715047),     _Q15(-0.10794133),   _Q15(0.12042143),
    _Q15(-0.049855914),   _Q15(-0.1646569),    _Q15(-0.18569434),
    _Q15(-0.16146585),    _Q15(0.15297948),    _Q15(0.20353837),
    _Q15(-0.11838823),    _Q15(0.21517058),    _Q15(0.17876023),
    _Q15(0.2893026),      _Q15(-0.28953087),   _Q15(0.1831816),
    _Q15(-0.09238038),    _Q15(-0.09710218),   _Q15(-0.10888995),
    _Q15(-0.18856001),    _Q15(-0.04857404),   _Q15(-0.09452506),
    _Q15(0.22832344),     _Q15(0.21212195),    _Q15(0.258496),
    _Q15(0.24995556),     _Q15(0.1918491),     _Q15(0.1908925),
    _Q15(0.15071803),     _Q15(0.124239765),   _Q15(-0.23745088),
    _Q15(0.12811458),     _Q15(0.19935733),    _Q15(-0.3270073),
    _Q15(0.12909728),     _Q15(0.18021038),    _Q15(0.11352672),
    _Q15(-0.2142028),     _Q15(0.17392692),    _Q15(0.022139752),
    _Q15(-0.1077402),     _Q15(-0.23496243),   _Q15(-0.19659473),
    _Q15(-0.23847356),    _Q15(0.26912686),    _Q15(0.2006939),
    _Q15(-0.1211255),     _Q15(-0.0665028),    _Q15(0.044924006),
    _Q15(0.000103153754), _Q15(-0.041018095),  _Q15(0.21924198),
    _Q15(0.24546112),     _Q15(0.23772173),    _Q15(-0.100158945),
    _Q15(-0.0075261397),  _Q15(0.002293015),   _Q15(0.21545161),
    _Q15(0.002007858),    _Q15(-0.07043856),   _Q15(0.28850076),
    _Q15(-0.22164354),    _Q15(0.26678225),    _Q15(-0.3897417),
    _Q15(-0.32172164),    _Q15(-0.26463434),   _Q15(-0.22436391),
    _Q15(-0.26250747),    _Q15(-0.42949244),   _Q15(0.31446487),
    _Q15(0.21229796),     _Q15(0.29294154),    _Q15(0.07438679),
    _Q15(0.012552242),    _Q15(0.016550511),   _Q15(0.16684845),
    _Q15(0.05582001),     _Q15(0.06829512),    _Q15(0.17231885),
    _Q15(0.095474415),    _Q15(0.15231751),    _Q15(-0.048278496),
    _Q15(0.015778136),    _Q15(-0.08306435),   _Q15(0.15313838),
    _Q15(0.25429973),     _Q15(0.25311548),    _Q15(0.1985296),
    _Q15(0.23958313),     _Q15(0.21723023),    _Q15(0.19670793),
    _Q15(0.18572447),     _Q15(0.14518651),    _Q15(0.17521746),
    _Q15(-0.119564965),   _Q15(0.34822312),    _Q15(-0.06512244),
    _Q15(0.039122093),    _Q15(-0.1095716),    _Q15(-0.06285296),
    _Q15(-0.15004161),    _Q15(-0.12685855),   _Q15(-0.1003501),
    _Q15(-0.19628981),    _Q15(-0.10276548),   _Q15(-0.17231107),
    _Q15(0.25308597),     _Q15(-0.17054379),   _Q15(-0.15636091),
    _Q15(-0.04803731),    _Q15(0.18901284),    _Q15(0.24176955),
    _Q15(0.23903608),     _Q15(0.072959274),   _Q15(0.35712868),
    _Q15(0.24387857),     _Q15(-0.108851865),  _Q15(0.261908),
    _Q15(0.26616204),     _Q15(0.21004906),    _Q15(0.15750854),
    _Q15(0.057480298),    _Q15(0.16466837),    _Q15(0.092472196),
    _Q15(-0.19601434),    _Q15(-0.042317946),  _Q15(-0.021690736),
    _Q15(0.008183056),    _Q15(-0.0528704),    _Q15(-0.071703285),
    _Q15(-0.10727592),    _Q15(-0.048622824),  _Q15(-0.12070469),
    _Q15(-0.1965082),     _Q15(-0.13961099),   _Q15(-0.16628413),
    _Q15(0.17848666),     _Q15(0.16176373),    _Q15(0.18479626),
    _Q15(0.1539367),      _Q15(-0.14538375),   _Q15(-0.2987538),
    _Q15(-0.3339671),     _Q15(-0.18503433),   _Q15(-0.117555775),
    _Q15(0.08165695),     _Q15(-0.30004737),   _Q15(0.01375495),
    _Q15(0.07371402),     _Q15(0.10919031),    _Q15(0.11943796),
    _Q15(0.034280583),    _Q15(0.26621863),    _Q15(0.0973491),
    _Q15(-0.04236187),    _Q15(0.15143847),    _Q15(0.10789103),
    _Q15(0.1295023),      _Q15(-0.30876866),   _Q15(-0.01687879),
    _Q15(-0.3087047),     _Q15(-0.08950986),   _Q15(0.20117103),
    _Q15(-0.058297683),   _Q15(-0.12805395),   _Q15(-0.030029206),
    _Q15(-0.1263784),     _Q15(-0.24088499),   _Q15(-0.10628603),
    _Q15(-0.3526143),     _Q15(-0.13513698),   _Q15(-0.33552366),
    _Q15(0.042460997),    _Q15(0.26322916),    _Q15(0.25610715),
    _Q15(-0.24908142),    _Q15(0.17312008),    _Q15(0.22877158),
    _Q15(0.2809726),      _Q15(-0.24325593),   _Q15(-0.2536631),
    _Q15(0.057123985),    _Q15(0.1402639),     _Q15(0.21278456),
    _Q15(-0.102013044),   _Q15(-0.16778366),   _Q15(-0.07225509),
    _Q15(-0.083316326),   _Q15(-0.19162944),   _Q15(0.37322176),
    _Q15(0.35627857),     _Q15(0.39580697),    _Q15(0.36475915),
    _Q15(-0.1330928),     _Q15(-0.13518465),   _Q15(-0.098797224),
    _Q15(-0.15205795),    _Q15(-0.16772737),   _Q15(-0.18210779),
    _Q15(-0.17219463),    _Q15(-0.07145281),   _Q15(-0.010535231),
    _Q15(-0.010235855),   _Q15(0.005632981),   _Q15(0.21222138),
    _Q15(0.24464747),     _Q15(0.26817203),    _Q15(-0.14133011),
    _Q15(-0.1130225),     _Q15(0.22537626),    _Q15(-0.24173637),
    _Q15(-0.097768776),   _Q15(-0.25162718),   _Q15(-0.2460939),
    _Q15(-0.0031260476),  _Q15(-0.09868135),   _Q15(0.059743736),
    _Q15(-0.11924223),    _Q15(-0.18599999),   _Q15(-0.25308827),
    _Q15(-0.08022718),    _Q15(-0.080544844),  _Q15(-0.17700517),
    _Q15(0.23586205),     _Q15(-0.071702324),  _Q15(0.25683475),
    _Q15(0.24758649),     _Q15(0.21687962),    _Q15(-0.24250644),
    _Q15(-0.05323036),    _Q15(-0.13965562),   _Q15(-0.036013793),
    _Q15(0.018389072),    _Q15(0.22290613),    _Q15(0.13545637),
    _Q15(0.2077471),      _Q15(0.13773757),    _Q15(0.1856966),
    _Q15(-0.034103185),   _Q15(-0.029724386),  _Q15(0.27857235),
    _Q15(0.13772146),     _Q15(-0.30659184),   _Q15(0.31284314),
    _Q15(0.30074814),     _Q15(0.25728655),    _Q15(0.2852359),
    _Q15(0.036419276),    _Q15(-0.10134807),   _Q15(-0.1412919),
    _Q15(-0.24192289),    _Q15(-0.23383264),   _Q15(-0.2820977),
    _Q15(-0.007006676),   _Q15(-0.012090355),  _Q15(0.31705174),
    _Q15(-0.3322192),     _Q15(-0.30774918),   _Q15(-0.16728625),
    _Q15(-0.11213621),    _Q15(-0.12555277),   _Q15(0.20272276),
    _Q15(0.21773617),     _Q15(-0.08194873),   _Q15(0.0065191253),
    _Q15(-0.10664795),    _Q15(0.2696068),     _Q15(-0.25125885),
    _Q15(-0.14023472),    _Q15(0.2695609),     _Q15(0.30614233),
    _Q15(-0.03421077),    _Q15(-0.11942889),   _Q15(0.13550083),
    _Q15(-0.3687053),     _Q15(-0.21482548),   _Q15(-0.19958164),
    _Q15(-0.119764194),   _Q15(-0.07946061),   _Q15(-0.15701167),
    _Q15(-0.24402474),    _Q15(-0.092683576),  _Q15(-0.049001426),
    _Q15(-0.11840297),    _Q15(0.2847794),     _Q15(-0.04195437),
    _Q15(0.2825308),      _Q15(0.15043299),    _Q15(-0.101299085),
    _Q15(0.18600558),     _Q15(-0.13361087),   _Q15(0.25408953),
    _Q15(-0.022013877),   _Q15(-0.100756176),  _Q15(0.20273148),
    _Q15(0.23114823),     _Q15(0.28480932),    _Q15(-0.080262855),
    _Q15(-0.061364714),   _Q15(0.19596325),    _Q15(0.23723282),
    _Q15(0.12598678),     _Q15(0.13975687),    _Q15(0.17410089),
    _Q15(0.25548363),     _Q15(0.2931972),     _Q15(0.2142407),
    _Q15(0.26100168),     _Q15(0.23314238),    _Q15(-0.23792288),
    _Q15(-0.3040619),     _Q15(-0.23295285),   _Q15(0.03250874),
    _Q15(-0.0719725),     _Q15(-0.12291464),   _Q15(-0.06003021),
    _Q15(0.10907556),     _Q15(0.23167075),    _Q15(0.2694332),
    _Q15(-0.061701704),   _Q15(0.037059773),   _Q15(-0.24010853),
    _Q15(-0.038000412),   _Q15(-0.075293586),  _Q15(-0.093292534),
    _Q15(0.022806913),    _Q15(-0.25196403),   _Q15(0.14282925),
    _Q15(0.08759279),     _Q15(0.2994996),     _Q15(0.33892456),
    _Q15(-0.21341994),    _Q15(-0.10207071),   _Q15(-0.20651239),
    _Q15(-0.040548764),   _Q15(-0.0049930788), _Q15(0.2979177),
    _Q15(-0.12088557),    _Q15(0.02054977),    _Q15(-0.06818683),
    _Q15(-0.12445984),    _Q15(-0.24935207),   _Q15(-0.25726202),
    _Q15(0.19817065),     _Q15(0.19295435),    _Q15(0.24076745),
    _Q15(0.19972084),     _Q15(0.19616354),    _Q15(0.18994433),
    _Q15(-0.24158716),    _Q15(-0.16524757),   _Q15(0.12510557),
    _Q15(0.24498798),     _Q15(-0.07442344),   _Q15(-0.045469042),
    _Q15(0.010690128),    _Q15(-0.051708017),  _Q15(0.17378396),
    _Q15(0.17641677),     _Q15(-0.12965196),   _Q15(0.18274015),
    _Q15(0.20693778),     _Q15(0.0201887),     _Q15(0.15039164),
    _Q15(-0.2528756),     _Q15(0.18912917),    _Q15(0.19213837),
    _Q15(0.27148274),     _Q15(-0.36620387),   _Q15(-0.27360696),
    _Q15(-0.17346369),    _Q15(-0.3612972),    _Q15(-0.111024305),
    _Q15(-0.21399303),    _Q15(-0.07646594),   _Q15(-0.10434217),
    _Q15(-0.16321403),    _Q15(-0.13653542),   _Q15(-0.037983634),
    _Q15(0.23323792),     _Q15(-0.12158854),   _Q15(-0.25841933),
    _Q15(-0.17788702),    _Q15(-0.19192109),   _Q15(-0.18160161),
    _Q15(-0.0944385),     _Q15(-0.24604245),   _Q15(0.18940926),
    _Q15(-0.23565127),    _Q15(0.19218369),    _Q15(0.26911122),
    _Q15(-0.23422767),    _Q15(0.22350441),    _Q15(-0.058448702),
    _Q15(-0.008082486),   _Q15(-0.16631189),   _Q15(0.2047339),
    _Q15(0.34688002),     _Q15(0.31009105),    _Q15(-0.027986556),
    _Q15(-0.11812682),    _Q15(0.33631453),    _Q15(-0.024630144),
    _Q15(-0.071995296),   _Q15(-0.118665114),  _Q15(-0.10524024),
    _Q15(-0.19507155),    _Q15(0.21200584),    _Q15(-0.19739373),
    _Q15(-0.32119074),    _Q15(0.16469471),    _Q15(-0.112004936),
    _Q15(0.036235448),    _Q15(0.18133786),    _Q15(0.21182477),
    _Q15(-0.1185598),     _Q15(0.16556755),    _Q15(0.16171125),
    _Q15(-0.07051824),    _Q15(0.2175852),     _Q15(0.16079265),
    _Q15(-0.3137674),     _Q15(0.1390646),     _Q15(-0.4210839),
    _Q15(0.07542157),     _Q15(-0.18684016),   _Q15(0.200549),
    _Q15(-0.060315154),   _Q15(-0.18667081),   _Q15(0.07670053),
    _Q15(-0.00081276684), _Q15(-0.18634902),   _Q15(0.26419967),
    _Q15(-0.2896311),     _Q15(0.2366617),     _Q15(0.3882595),
    _Q15(0.23376329),     _Q15(-0.09267196),   _Q15(-0.21139464),
    _Q15(-0.026746351),   _Q15(-0.25614572),   _Q15(-0.132871),
    _Q15(-0.14489676),    _Q15(0.18854325),    _Q15(-0.15894662),
    _Q15(0.22607598),     _Q15(-0.07922863),   _Q15(0.2205214),
    _Q15(-0.20254901),    _Q15(-0.13630731),   _Q15(-0.0075893733),
    _Q15(-0.25806764),    _Q15(-0.06238157),   _Q15(-0.11021933),
    _Q15(-0.1107669),     _Q15(0.23891957),    _Q15(0.26219478),
    _Q15(0.21083407),     _Q15(0.26969692),    _Q15(0.23281711),
    _Q15(0.3229297),      _Q15(-0.13333432),   _Q15(0.2643428),
    _Q15(-0.23222043),    _Q15(-0.22729436),   _Q15(0.19752157),
    _Q15(-0.31652418),    _Q15(-0.36793813),   _Q15(-0.1252839),
    _Q15(-0.12043723),    _Q15(-0.100551024),  _Q15(0.20005117),
    _Q15(0.15447734),     _Q15(-0.093151696),  _Q15(0.25746572),
    _Q15(-0.15151447),    _Q15(-0.30041167),   _Q15(-0.17373021),
    _Q15(-0.15862982),    _Q15(-0.33855543),   _Q15(0.004024961),
    _Q15(-0.3165777),     _Q15(-0.15337688),   _Q15(-0.034926046),
    _Q15(0.22555067),     _Q15(0.1981758),     _Q15(0.20457922),
    _Q15(0.08988285),     _Q15(0.17049871),    _Q15(0.081163734),
    _Q15(0.35597888),     _Q15(0.14730768),    _Q15(-0.09064257),
    _Q15(0.10712228),     _Q15(0.2083279),     _Q15(-0.22633646),
    _Q15(0.0023257246),   _Q15(-0.18742968),   _Q15(-0.15074928),
    _Q15(0.31791496),     _Q15(-0.10327911),   _Q15(0.34420076),
    _Q15(-0.07917052),    _Q15(-0.07608422),   _Q15(-0.1492675),
    _Q15(-0.17018616),    _Q15(-0.26031053),   _Q15(-0.12957229),
    _Q15(0.022016535),    _Q15(-0.24978425),   _Q15(-0.22982271),
    _Q15(0.21509929),     _Q15(0.23130691),    _Q15(0.18776688),
    _Q15(0.16042754),     _Q15(0.2102719),     _Q15(0.23791605),
    _Q15(0.25508478),     _Q15(0.044309266),   _Q15(-0.124940835),
    _Q15(-0.13080841),    _Q15(-0.15241696),   _Q15(-0.23753451),
    _Q15(-0.24052778),    _Q15(-0.2122956),    _Q15(-0.23136254),
    _Q15(0.004051651),    _Q15(0.11379551),    _Q15(0.1239495),
    _Q15(-0.20016001),    _Q15(-0.091062814),  _Q15(-0.027277593),
    _Q15(0.07186187),     _Q15(-0.058974188),  _Q15(0.13526453),
    _Q15(0.121295206),    _Q15(0.18106128),    _Q15(0.18962412),
    _Q15(0.12579072),     _Q15(-0.19548889),   _Q15(0.12429857),
    _Q15(-0.1187803),     _Q15(-0.04153825),   _Q15(0.16946931),
    _Q15(0.23955876),     _Q15(-0.11878852),   _Q15(-0.14346664),
    _Q15(-0.05196101),    _Q15(-0.16392718),   _Q15(-0.081342265),
    _Q15(-0.15707693),    _Q15(-0.18620162),   _Q15(0.27152172),
    _Q15(0.24660654),     _Q15(-0.27671915),   _Q15(-0.07395512),
    _Q15(0.046735488),    _Q15(-0.009542682),  _Q15(-0.20726793),
    _Q15(-0.067029245),   _Q15(-0.12478929),   _Q15(-0.021819223),
    _Q15(-0.109480046),   _Q15(-0.11219791),   _Q15(-0.110515915),
    _Q15(-0.11156705),    _Q15(-0.10389635),   _Q15(-0.1220331),
    _Q15(-0.10932424),    _Q15(-0.103579484),  _Q15(-0.20694546),
    _Q15(-0.10832633),    _Q15(-0.16721842),   _Q15(-0.102789566),
    _Q15(-0.21531814),    _Q15(0.18707773),    _Q15(0.20451197),
    _Q15(0.09619575),     _Q15(0.13717863),    _Q15(0.30072948),
    _Q15(0.0949544),      _Q15(0.114806525),   _Q15(-0.16195892),
    _Q15(0.31939697),     _Q15(-0.093441084),  _Q15(0.32717213),
    _Q15(-0.05402712),    _Q15(-0.13526337),   _Q15(-0.097628266),
    _Q15(-0.08673083),    _Q15(-0.20274498),   _Q15(-0.26819104),
    _Q15(-0.25022534),    _Q15(-0.043445986),  _Q15(-0.1075437),
    _Q15(-0.16993901),    _Q15(0.15759678),    _Q15(-0.15245098),
    _Q15(0.29145312),     _Q15(0.22987896),    _Q15(-0.34557506),
    _Q15(0.23433234),     _Q15(-0.14127676),   _Q15(-0.08125515),
    _Q15(-0.03993988),    _Q15(-0.12008733),   _Q15(-0.13470785),
    _Q15(-0.19436777),    _Q15(-0.16946839),   _Q15(-0.0070354035),
    _Q15(0.12013766),     _Q15(-0.14075753),   _Q15(0.0026784248),
    _Q15(0.39758214),     _Q15(-0.1608587),    _Q15(-0.13184227),
    _Q15(-0.149637),      _Q15(-0.1725033),    _Q15(-0.111354314),
    _Q15(-0.07780752),    _Q15(-0.045371734),  _Q15(-0.27329108),
    _Q15(0.12089162),     _Q15(0.19847897),    _Q15(-0.23283829),
    _Q15(0.30545264),     _Q15(-0.034061242),  _Q15(-0.1277116),
    _Q15(-0.11161997),    _Q15(-0.011874343),  _Q15(0.26404062),
    _Q15(-0.13043737),    _Q15(-0.124179505),  _Q15(-0.07547392),
    _Q15(0.27170002),     _Q15(-0.0018186626), _Q15(-0.118723),
    _Q15(-0.072386146),   _Q15(-0.10749106),   _Q15(-0.17378432),
    _Q15(-0.12027356),    _Q15(0.18812732),    _Q15(-0.18742359),
    _Q15(-0.13658154),    _Q15(0.25499582),    _Q15(0.26032612),
    _Q15(0.21415582),     _Q15(0.16448966),    _Q15(-0.108300775),
    _Q15(-0.00415785),    _Q15(-0.10951461),   _Q15(-0.17802893),
    _Q15(-0.14228874),    _Q15(-0.12856196),   _Q15(-0.21432708),
    _Q15(0.19758496),     _Q15(-0.062034234),  _Q15(0.022464985),
    _Q15(-0.053630155),   _Q15(-0.24587859),   _Q15(-0.1392108),
    _Q15(-0.1100247),     _Q15(0.04310842),    _Q15(-0.18370023),
    _Q15(-0.11749912),    _Q15(-0.10281257),   _Q15(0.20360118),
    _Q15(0.2397297),      _Q15(0.2542895),     _Q15(0.24459587),
    _Q15(-0.005063416),   _Q15(-0.07046577),   _Q15(0.19284323),
    _Q15(0.1704036),      _Q15(0.21844372),    _Q15(-0.01450775),
    _Q15(0.2752233),      _Q15(0.21644926),    _Q15(0.17945303),
    _Q15(0.18265693),     _Q15(-0.041132342),  _Q15(0.01798889),
    _Q15(-0.124736175),   _Q15(-0.20694187),   _Q15(-0.18749066),
    _Q15(-0.17434916),    _Q15(0.042662524),   _Q15(-0.11916516),
    _Q15(-0.04046091),    _Q15(-0.15802337),   _Q15(0.19168457),
    _Q15(0.19619259)};

__ro_hifram fixed conv2_wm_offsets[931] = {
    120, 42,  45,  5,   101, 75,  95,  4,   17, 11,  1,   7,   1,   1,   1,
    61,  4,   2,   3,   1,   8,   199, 27,  5,  5,   1,   69,  1,   4,   1,
    9,   84,  5,   5,   2,   5,   1,   216, 5,  41,  1,   1,   68,  1,   4,
    1,   91,  5,   6,   12,  1,   14,  1,   1,  3,   1,   1,   2,   1,   2,
    1,   1,   2,   2,   1,   10,  1,   2,   3,  1,   2,   12,  1,   3,   2,
    1,   3,   3,   6,   5,   9,   5,   7,   1,  1,   8,   3,   3,   3,   14,
    1,   1,   2,   2,   1,   2,   23,  1,   12, 5,   1,   3,   2,   1,   2,
    7,   11,  6,   18,  1,   24,  1,   5,   1,  19,  5,   1,   19,  24,  1,
    2,   3,   1,   2,   22,  1,   18,  6,   1,  16,  3,   3,   1,   2,   3,
    15,  1,   5,   20,  39,  65,  96,  109, 7,  22,  5,   3,   67,  2,   3,
    4,   1,   3,   1,   4,   36,  4,   2,   41, 2,   1,   2,   279, 8,   23,
    1,   4,   1,   50,  14,  4,   1,   5,   97, 2,   5,   168, 74,  25,  28,
    1,   4,   5,   6,   59,  5,   5,   5,   27, 25,  4,   43,  5,   2,   96,
    125, 25,  25,  174, 45,  4,   1,   104, 4,  1,   1,   5,   4,   3,   1,
    1,   90,  5,   178, 95,  106, 1,   52,  45, 5,   5,   45,  1,   1,   8,
    4,   14,  10,  5,   45,  5,   15,  1,   2,  2,   1,   2,   4,   1,   4,
    32,  6,   44,  6,   101, 71,  4,   111, 1,  2,   3,   3,   85,  7,   3,
    27,  5,   5,   1,   44,  5,   14,  1,   4,  1,   3,   2,   47,  1,   2,
    42,  1,   2,   1,   1,   1,   2,   1,   2,  2,   91,  75,  95,  31,  7,
    3,   70,  103, 1,   5,   42,  1,   1,   3,  64,  1,   49,  61,  8,   102,
    3,   2,   105, 275, 27,  5,   5,   1,   70, 4,   1,   5,   36,  5,   2,
    43,  5,   2,   3,   2,   31,  1,   5,   69, 1,   1,   3,   1,   3,   1,
    4,   89,  4,   16,  22,  2,   1,   49,  1,  100, 199, 1,   95,  41,  1,
    66,  53,  50,  32,  76,  4,   1,   2,   1,  1,   2,   1,   1,   35,  5,
    3,   47,  3,   278, 31,  1,   68,  5,   5,  1,   5,   336, 25,  27,  1,
    6,   3,   1,   1,   69,  5,   5,   7,   26, 1,   3,   1,   6,   62,  4,
    1,   3,   1,   2,   1,   2,   2,   33,  9,  41,  9,   2,   8,   158, 45,
    67,  32,  5,   1,   6,   14,  46,  9,   5,  15,  21,  50,  12,  67,  125,
    100, 8,   5,   8,   9,   25,  4,   1,   54, 1,   4,   1,   201, 4,   25,
    129, 16,  5,   4,   28,  1,   4,   5,   70, 5,   4,   7,   35,  52,  2,
    11,  265, 4,   34,  4,   1,   61,  1,   1,  1,   2,   3,   1,   1,   4,
    5,   3,   88,  7,   22,  4,   1,   75,  4,  1,   3,   5,   88,  14,  17,
    12,  10,  3,   1,   1,   4,   63,  4,   1,  1,   1,   4,   96,  1,   218,
    58,  1,   1,   111, 28,  15,  1,   62,  6,  4,   23,  70,  15,  15,  1,
    9,   60,  111, 133, 50,  91,  29,  5,   5,  62,  1,   3,   1,   3,   1,
    4,   4,   2,   2,   88,  2,   12,  275, 43, 1,   59,  32,  5,   10,  1,
    53,  1,   4,   1,   1,   3,   1,   1,   8,  1,   1,   80,  21,  101, 5,
    7,   1,   41,  70,  1,   4,   6,   5,   17, 5,   5,   65,  4,   1,   5,
    8,   1,   18,  23,  11,  37,  2,   5,   1,  5,   96,  75,  12,  1,   24,
    1,   1,   3,   6,   1,   52,  1,   66,  45, 1,   4,   95,  75,  80,  15,
    1,   15,  122, 7,   6,   1,   3,   20,  71, 3,   1,   1,   3,   8,   44,
    1,   4,   1,   34,  6,   4,   1,   3,   1,  1,   83,  6,   69,  6,   4,
    64,  6,   7,   5,   7,   3,   3,   1,   6,  115, 47,  127, 50,  121, 101,
    12,  107, 193, 174, 44,  66,  33,  70,  5,  2,   2,   1,   2,   2,   5,
    41,  48,  2,   3,   6,   6,   17,  3,   1,  67,  7,   2,   2,   2,   4,
    4,   2,   1,   27,  62,  11,  82,  6,   69, 6,   110, 27,  2,   4,   1,
    3,   63,  1,   1,   7,   4,   1,   3,   1,  4,   2,   38,  6,   151, 168,
    2,   4,   27,  1,   11,  39,  5,   5,   54, 2,   5,   22,  3,   1,   1,
    3,   1,   43,  20,  1,   4,   1,   3,   1,  3,   1,   1,   4,   2,   29,
    13,  37,  4,   3,   2,   2,   2,   10,  3,  75,  9,   66,  50,  29,  25,
    13,  23,  2,   1,   3,   1,   1,   64,  1,  3,   1,   1,   4,   1,   4,
    91,  219, 5,   29,  4,   77,  3,   2,   2,  1,   4,   90,  4,   2,   3,
    105, 1,   7,   1,   173, 1,   32,  13,  3,  1,   1,   37,  6,   3,   60,
    1,   4,   1,   47,  50,  5,   112, 60,  1,  45,  1,   3,   1,   1,   491,
    7,   26,  1,   4,   63,  5,   1,   4,   3,  6,   2,   34,  48,  2,   2,
    16,  83,  75,  45,  29,  25,  29,  5,   5,  5,   65,  1,   4,   5,   96,
    3,   13,  1,   25,  2,   1,   20,  29,  28, 2,   66,  21,  13,  16,  25,
    25,  26,  75,  1,   73,  103, 11,  5,   42, 57,  13,  30,  20,  99,  60,
    16,  25,  50,  41,  69,  1,   102, 1,   4,  250, 12,  6,   10,  8,   1,
    1,   62,  10,  9,   74,  124, 1,   75,  95, 113, 111, 5,   5,   17,  1,
    4,   1,   4,   1,   50,  19,  1,   4,   1,  6,   5,   37,  5,   40,  3,
    1,   1,   5,   5,   2,   82,  130, 5,   5,  43,  100, 112, 34,  5,   70,
    5};

__ro_hifram fixed conv2_wm_sizes[100] = {
    8, 14, 17, 10, 90, 4,  0, 20, 16, 19, 4,  0,  13, 6,  0,  3, 0,
    0, 0,  23, 0,  8,  28, 0, 4,  3,  6,  3,  5,  16, 13, 10, 5, 16,
    0, 9,  9,  0,  24, 14, 0, 3,  16, 14, 0,  15, 11, 19, 1,  8, 0,
    9, 0,  17, 3,  17, 4,  4, 21, 20, 1,  0,  36, 0,  1,  3,  2, 4,
    2, 13, 22, 21, 3,  0,  0, 4,  0,  36, 16, 2,  0,  12, 4,  7, 10,
    8, 0,  1,  21, 10, 19, 5, 8,  7,  14, 2,  29, 0,  2,  4};

__ro_hifram fixed conv2_b[100] = {
    _Q15(0.196523740888),     _Q15(0.0270340051502),
    _Q15(-0.0171628054231),   _Q15(0.0640425086021),
    _Q15(0.103266447783),     _Q15(0.151402235031),
    _Q15(-0.0226933471859),   _Q15(-0.0038078201469),
    _Q15(0.0224395468831),    _Q15(0.10781507194),
    _Q15(0.0633652433753),    _Q15(-0.011569284834),
    _Q15(0.13311457634),      _Q15(0.003920705989),
    _Q15(-0.0061055268161),   _Q15(0.0913253948092),
    _Q15(-0.00120702187996),  _Q15(-0.0184175614268),
    _Q15(-0.0103748915717),   _Q15(0.0579093173146),
    _Q15(0.00916726607829),   _Q15(0.0040731979534),
    _Q15(0.0131594901904),    _Q15(-0.0174309816211),
    _Q15(0.0516680218279),    _Q15(-0.0123871369287),
    _Q15(0.0480610579252),    _Q15(0.0299753230065),
    _Q15(0.127385020256),     _Q15(-0.000249430275289),
    _Q15(-0.00449963985011),  _Q15(0.15353423357),
    _Q15(0.150118470192),     _Q15(-0.0266412887722),
    _Q15(-0.014088015072),    _Q15(0.181392028928),
    _Q15(0.0168920364231),    _Q15(-0.0185732506216),
    _Q15(0.0298650357872),    _Q15(0.130665183067),
    _Q15(0.0365493074059),    _Q15(0.0110251847655),
    _Q15(0.199030205607),     _Q15(0.0383041799068),
    _Q15(-0.0132253859192),   _Q15(0.011047734879),
    _Q15(0.0210250187665),    _Q15(0.0942302197218),
    _Q15(-0.00253081764095),  _Q15(0.0314549580216),
    _Q15(-0.017454713583),    _Q15(0.141579091549),
    _Q15(-0.00191018707119),  _Q15(0.0290157105774),
    _Q15(0.0390226431191),    _Q15(0.0300275366753),
    _Q15(-0.0290858503431),   _Q15(0.0369864329696),
    _Q15(0.0528944991529),    _Q15(0.0739212036133),
    _Q15(0.00975369755179),   _Q15(-0.0218778699636),
    _Q15(0.0722374841571),    _Q15(-0.0139426458627),
    _Q15(-0.00192885939032),  _Q15(0.0385927893221),
    _Q15(-0.00646644365042),  _Q15(0.151078909636),
    _Q15(0.0306956898421),    _Q15(-0.0549622029066),
    _Q15(0.0273936204612),    _Q15(-0.0165219344199),
    _Q15(-0.0146550824866),   _Q15(-0.0169187374413),
    _Q15(-0.00944347400218),  _Q15(0.0531173124909),
    _Q15(-0.0112824384123),   _Q15(0.118561193347),
    _Q15(0.0831662267447),    _Q15(0.0743100419641),
    _Q15(-0.00194427464157),  _Q15(-0.0241687279195),
    _Q15(-0.000622548046522), _Q15(0.131776228547),
    _Q15(0.0394919700921),    _Q15(-0.00454293983057),
    _Q15(-0.0109727596864),   _Q15(0.0896088182926),
    _Q15(0.0740780234337),    _Q15(-0.0136159881949),
    _Q15(0.192574903369),     _Q15(-0.0199599247426),
    _Q15(0.128755152225),     _Q15(0.106993891299),
    _Q15(0.0709483474493),    _Q15(0.0319215543568),
    _Q15(0.00435964530334),   _Q15(-0.0221845600754),
    _Q15(0.0488187856972),    _Q15(0.0283885765821)};

#endif
