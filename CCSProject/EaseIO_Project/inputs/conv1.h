#ifndef CONV1_H
#define CONV1_H
#include <libmsp/mem.h>
#include <libfixed/fixed.h>

#define CONV1_WMD_LEN 20

__ro_hifram _q15 conv1_wmd[20] = {
    _Q15(0.5514001),   _Q15(-0.6771312),  _Q15(0.5063913),
    _Q15(-0.43023926), _Q15(-0.57395524), _Q15(-0.5555001),
    _Q15(0.49755034),  _Q15(0.18338768),  _Q15(0.5493566),
    _Q15(0.2648332),   _Q15(0.1498827),   _Q15(0.18056822),
    _Q15(0.53418916),  _Q15(0.39554012),  _Q15(0.45877257),
    _Q15(0.55877864),  _Q15(0.17857419),  _Q15(-0.611645),
    _Q15(0.441671),    _Q15(-0.67354447)};

__ro_hifram _q15 conv1_wmd_offsets[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

__ro_hifram _q15 conv1_wmd_sizes[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

#define CONV1_WMH_LEN 100

__ro_hifram _q15 conv1_wmh[100] = {
    _Q15(0.42195162),  _Q15(0.607521),     _Q15(0.7214888),
    _Q15(0.7699961),   _Q15(0.5149403),    _Q15(0.73833525),
    _Q15(0.7471793),   _Q15(0.62391305),   _Q15(0.4999502),
    _Q15(0.30073732),  _Q15(0.19750598),   _Q15(0.57918626),
    _Q15(0.90448314),  _Q15(0.8415422),    _Q15(0.42951274),
    _Q15(0.87163675),  _Q15(0.7089953),    _Q15(0.5756348),
    _Q15(0.19598788),  _Q15(-0.052413143), _Q15(-0.6788556),
    _Q15(-0.38587645), _Q15(0.2693438),    _Q15(0.7289479),
    _Q15(-0.08480139), _Q15(-0.13926604),  _Q15(0.15005721),
    _Q15(0.4884112),   _Q15(0.9500218),    _Q15(1.0134408),
    _Q15(-0.64983284), _Q15(-0.13047867),  _Q15(0.412729),
    _Q15(0.7219357),   _Q15(0.70316505),   _Q15(0.05307127),
    _Q15(0.33146644),  _Q15(0.58162814),   _Q15(0.55370015),
    _Q15(0.35339627),  _Q15(-0.6754474),   _Q15(-0.37561938),
    _Q15(0.25562602),  _Q15(0.6788612),    _Q15(0.80467135),
    _Q15(0.18626766),  _Q15(0.40928575),   _Q15(0.63764215),
    _Q15(0.70523876),  _Q15(0.3291444),    _Q15(0.1928357),
    _Q15(0.2895186),   _Q15(0.6035212),    _Q15(0.4539167),
    _Q15(0.29035628),  _Q15(0.16905385),   _Q15(0.42260495),
    _Q15(0.6427114),   _Q15(0.58646584),   _Q15(0.21356678),
    _Q15(0.20895058),  _Q15(0.5637914),    _Q15(0.7099463),
    _Q15(0.8713418),   _Q15(0.6335595),    _Q15(0.34659886),
    _Q15(0.72370124),  _Q15(0.85134107),   _Q15(0.7317003),
    _Q15(0.24380337),  _Q15(0.17141198),   _Q15(0.55959535),
    _Q15(0.72837234),  _Q15(0.80555004),   _Q15(0.60339963),
    _Q15(0.26286945),  _Q15(0.57987726),   _Q15(0.8050496),
    _Q15(0.816413),    _Q15(0.58757913),   _Q15(0.09106697),
    _Q15(0.44904828),  _Q15(0.58086306),   _Q15(0.622108),
    _Q15(0.26553652),  _Q15(-0.24120075),  _Q15(0.06904729),
    _Q15(0.5035345),   _Q15(0.9026511),    _Q15(1.0589938),
    _Q15(-0.20708887), _Q15(0.19818985),   _Q15(0.75051904),
    _Q15(0.9180645),   _Q15(0.36436552),   _Q15(0.88785416),
    _Q15(0.93573177),  _Q15(0.7429203),    _Q15(0.49206775),
    _Q15(0.14983158)};

__ro_hifram _q15 conv1_wmh_offsets[100] = {
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1};

__ro_hifram _q15 conv1_wmh_sizes[20] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                                         5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

#define CONV1_WMV_LEN 100

__ro_hifram _q15 conv1_wmv[100] = {
    _Q15(0.09034854),   _Q15(0.7444282),    _Q15(0.73090804),
    _Q15(-0.027014952), _Q15(-0.72026634),  _Q15(-0.6302),
    _Q15(-0.59967935),  _Q15(-0.15395786),  _Q15(0.48952276),
    _Q15(0.6799719),    _Q15(0.22759485),   _Q15(0.75491345),
    _Q15(1.0511882),    _Q15(0.5158098),    _Q15(-0.10920517),
    _Q15(-0.57162786),  _Q15(-0.64726),     _Q15(-0.1756984),
    _Q15(0.36389232),   _Q15(0.45943275),   _Q15(0.42095637),
    _Q15(0.6834508),    _Q15(0.79231834),   _Q15(0.59661615),
    _Q15(0.39022866),   _Q15(0.52901095),   _Q15(0.106788844),
    _Q15(-0.56312805),  _Q15(-0.79748154),  _Q15(-0.6597942),
    _Q15(0.5566851),    _Q15(0.6371929),    _Q15(0.7193053),
    _Q15(0.64646775),   _Q15(0.37697202),   _Q15(0.12648186),
    _Q15(0.49046817),   _Q15(0.7193447),    _Q15(0.28532472),
    _Q15(-0.2185924),   _Q15(0.56034124),   _Q15(0.6019353),
    _Q15(0.72189325),   _Q15(0.7133785),    _Q15(0.5922777),
    _Q15(-0.122034095), _Q15(0.27822733),   _Q15(0.8400388),
    _Q15(0.54377395),   _Q15(-0.103865854), _Q15(-0.31242767),
    _Q15(0.23566066),   _Q15(0.6961476),    _Q15(0.39828768),
    _Q15(-0.19021952),  _Q15(0.011746993),  _Q15(0.5011174),
    _Q15(0.7344384),    _Q15(0.2606247),    _Q15(-0.24701619),
    _Q15(0.09965036),   _Q15(0.819571),     _Q15(0.78367484),
    _Q15(0.04327332),   _Q15(-0.50731283),  _Q15(0.064122945),
    _Q15(0.42805067),   _Q15(0.8728541),    _Q15(0.9093745),
    _Q15(0.23949121),   _Q15(0.13951026),   _Q15(0.701733),
    _Q15(0.9635506),    _Q15(0.59771603),   _Q15(-0.1617696),
    _Q15(0.36940092),   _Q15(0.8583519),    _Q15(0.710357),
    _Q15(-0.03765018),  _Q15(-0.5268749),   _Q15(0.2956454),
    _Q15(0.5652739),    _Q15(0.58474207),   _Q15(0.38414493),
    _Q15(-0.12687822),  _Q15(0.8061497),    _Q15(0.55174077),
    _Q15(-0.36154303),  _Q15(-0.7110712),   _Q15(-0.5647537),
    _Q15(0.16678001),   _Q15(0.55335397),   _Q15(0.8637919),
    _Q15(0.79079705),   _Q15(0.17070384),   _Q15(0.78301543),
    _Q15(0.2815614),    _Q15(-0.44108206),  _Q15(-0.767558),
    _Q15(-0.79296577)};

__ro_hifram _q15 conv1_wmv_offsets[100] = {
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1};

__ro_hifram _q15 conv1_wmv_sizes[20] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                                         5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

__ro_hifram _q15 conv1_b[20] = {
    _Q15(-5.98718688707e-05), _Q15(0.0763346850872),
    _Q15(-0.0136281428859),   _Q15(0.00148962275125),
    _Q15(0.0577480830252),    _Q15(-0.0010069408454),
    _Q15(-0.029848838225),    _Q15(-0.0112964976579),
    _Q15(-0.00544264679775),  _Q15(-0.00724812503904),
    _Q15(-0.00770109938458),  _Q15(-0.00349061563611),
    _Q15(-0.00143658765592),  _Q15(-0.00792094878852),
    _Q15(0.0015508076176),    _Q15(0.000811299367342),
    _Q15(-0.00796844158322),  _Q15(0.0223307348788),
    _Q15(-0.0237380620092),   _Q15(0.00162841996644)};

#endif