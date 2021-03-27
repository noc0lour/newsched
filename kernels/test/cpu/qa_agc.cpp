#include <gnuradio/kernels/cpu/agc_cc.hpp>
#include <gnuradio/kernels/cpu/agc_ff.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <thread>

using namespace gr;
namespace analog = gr::kernels::analog::cpu;

TEST(AnalogKernel, agc_float_identity_test)
{
    auto agc_kernel = analog::agc_ff(.001f, 1.0f, 1.0f, 65536.0f);
    float input[1000];
    float output[1000];
    float expected_output[1000];

    for (unsigned int idx = 0; idx < 1000; idx++) {
        input[idx] = 1.0f;
        output[idx] = 1.0f;
        expected_output[idx] = 1.0f;
    }

    agc_kernel(input, output, 1000);

    for (unsigned int idx = 0; idx < 1000; idx++)
        EXPECT_NEAR(output[idx], expected_output[idx], .0001f);
}

TEST(AnalogKernel, agc_float_ramp_test)
{
    auto agc_kernel = analog::agc_ff(.001f, 1.0f, 1.0f, 65536.0f);
    float input[1000];
    float output[1000];
    float expected_output[1000] = {
        0.5,      0.50025,  0.5005,   0.50075,  0.500999, 0.501249, 0.501498, 0.501747,
        0.501997, 0.502246, 0.502494, 0.502743, 0.502992, 0.50324,  0.503489, 0.503737,
        0.503985, 0.504233, 0.504481, 0.504729, 0.504976, 0.505224, 0.505471, 0.505718,
        0.505966, 0.506213, 0.506459, 0.506706, 0.506953, 0.507199, 0.507446, 0.507692,
        0.507938, 0.508184, 0.50843,  0.508676, 0.508922, 0.509167, 0.509413, 0.509658,
        0.509903, 0.510148, 0.510393, 0.510638, 0.510882, 0.511127, 0.511371, 0.511616,
        0.51186,  0.512104, 0.512348, 0.512592, 0.512836, 0.513079, 0.513323, 0.513566,
        0.513809, 0.514052, 0.514295, 0.514538, 0.514781, 0.515023, 0.515266, 0.515508,
        0.515751, 0.515993, 0.516235, 0.516477, 0.516718, 0.51696,  0.517201, 0.517443,
        0.517684, 0.517925, 0.518166, 0.518407, 0.518648, 0.518889, 0.519129, 0.51937,
        0.51961,  0.51985,  0.52009,  0.52033,  0.52057,  0.52081,  0.521049, 0.521289,
        0.521528, 0.521768, 0.522007, 0.522246, 0.522485, 0.522723, 0.522962, 0.523201,
        0.523439, 0.523677, 0.523916, 0.524154, 0.524392, 0.524629, 0.524867, 0.525105,
        0.525342, 0.525579, 0.525817, 0.526054, 0.526291, 0.526528, 0.526764, 0.527001,
        0.527238, 0.527474, 0.52771,  0.527946, 0.528182, 0.528418, 0.528654, 0.52889,
        0.529125, 0.529361, 0.529596, 0.529831, 0.530066, 0.530301, 0.530536, 0.530771,
        0.531006, 0.53124,  0.531474, 0.531709, 0.531943, 0.532177, 0.532411, 0.532644,
        0.532878, 0.533112, 0.533345, 0.533578, 0.533812, 0.534045, 0.534278, 0.534511,
        0.534743, 0.534976, 0.535209, 0.535441, 0.535673, 0.535905, 0.536137, 0.536369,
        0.536601, 0.536833, 0.537064, 0.537296, 0.537527, 0.537758, 0.53799,  0.538221,
        0.538452, 0.538682, 0.538913, 0.539144, 0.539374, 0.539604, 0.539834, 0.540065,
        0.540295, 0.540524, 0.540754, 0.540984, 0.541213, 0.541443, 0.541672, 0.541901,
        0.54213,  0.542359, 0.542588, 0.542817, 0.543045, 0.543274, 0.543502, 0.54373,
        0.543958, 0.544186, 0.544414, 0.544642, 0.54487,  0.545097, 0.545325, 0.545552,
        0.545779, 0.546007, 0.546233, 0.54646,  0.546687, 0.546914, 0.54714,  0.547367,
        0.547593, 0.547819, 0.548045, 0.548271, 0.548497, 0.548723, 0.548949, 0.549174,
        0.5494,   0.549625, 0.54985,  0.550075, 0.5503,   0.550525, 0.55075,  0.550974,
        0.551199, 0.551423, 0.551647, 0.551872, 0.552096, 0.55232,  0.552543, 0.552767,
        0.552991, 0.553214, 0.553438, 0.553661, 0.553884, 0.554107, 0.55433,  0.554553,
        0.554776, 0.554998, 0.555221, 0.555443, 0.555666, 0.555888, 0.55611,  0.556332,
        0.556554, 0.556775, 0.556997, 0.557218, 0.55744,  0.557661, 0.557882, 0.558103,
        0.558324, 0.558545, 0.558766, 0.558986, 0.559207, 0.559427, 0.559648, 0.559868,
        0.560088, 0.560308, 0.560528, 0.560747, 0.560967, 0.561186, 0.561406, 0.561625,
        0.561844, 0.562063, 0.562282, 0.562501, 0.56272,  0.562939, 0.563157, 0.563376,
        0.563594, 0.563812, 0.56403,  0.564248, 0.564466, 0.564684, 0.564902, 0.565119,
        0.565337, 0.565554, 0.565771, 0.565988, 0.566205, 0.566422, 0.566639, 0.566856,
        0.567072, 0.567289, 0.567505, 0.567721, 0.567937, 0.568153, 0.568369, 0.568585,
        0.568801, 0.569016, 0.569232, 0.569447, 0.569663, 0.569878, 0.570093, 0.570308,
        0.570523, 0.570737, 0.570952, 0.571167, 0.571381, 0.571595, 0.57181,  0.572024,
        0.572238, 0.572451, 0.572665, 0.572879, 0.573093, 0.573306, 0.573519, 0.573733,
        0.573946, 0.574159, 0.574372, 0.574584, 0.574797, 0.57501,  0.575222, 0.575435,
        0.575647, 0.575859, 0.576071, 0.576283, 0.576495, 0.576707, 0.576918, 0.57713,
        0.577341, 0.577553, 0.577764, 0.577975, 0.578186, 0.578397, 0.578608, 0.578819,
        0.579029, 0.57924,  0.57945,  0.57966,  0.57987,  0.58008,  0.58029,  0.5805,
        0.58071,  0.58092,  0.581129, 0.581339, 0.581548, 0.581757, 0.581966, 0.582175,
        0.582384, 0.582593, 0.582802, 0.58301,  0.583219, 0.583427, 0.583636, 0.583844,
        0.584052, 0.58426,  0.584468, 0.584675, 0.584883, 0.585091, 0.585298, 0.585505,
        0.585713, 0.58592,  0.586127, 0.586334, 0.586541, 0.586747, 0.586954, 0.587161,
        0.587367, 0.587573, 0.587779, 0.587986, 0.588192, 0.588397, 0.588603, 0.588809,
        0.589015, 0.58922,  0.589425, 0.589631, 0.589836, 0.590041, 0.590246, 0.590451,
        0.590656, 0.59086,  0.591065, 0.591269, 0.591474, 0.591678, 0.591882, 0.592086,
        0.59229,  0.592494, 0.592698, 0.592901, 0.593105, 0.593308, 0.593512, 0.593715,
        0.593918, 0.594121, 0.594324, 0.594527, 0.59473,  0.594932, 0.595135, 0.595337,
        0.59554,  0.595742, 0.595944, 0.596146, 0.596348, 0.59655,  0.596751, 0.596953,
        0.597155, 0.597356, 0.597557, 0.597759, 0.59796,  0.598161, 0.598362, 0.598562,
        0.598763, 0.598964, 0.599164, 0.599365, 0.599565, 0.599765, 0.599965, 0.600165,
        0.600365, 0.600565, 0.600765, 0.600964, 0.601164, 0.601363, 0.601563, 0.601762,
        0.601961, 0.60216,  0.602359, 0.602558, 0.602757, 0.602955, 0.603154, 0.603352,
        0.60355,  0.603749, 0.603947, 0.604145, 0.604343, 0.604541, 0.604738, 0.604936,
        0.605133, 0.605331, 0.605528, 0.605725, 0.605923, 0.60612,  0.606317, 0.606513,
        0.60671,  0.606907, 0.607103, 0.6073,   0.607496, 0.607692, 0.607889, 0.608085,
        0.608281, 0.608476, 0.608672, 0.608868, 0.609063, 0.609259, 0.609454, 0.60965,
        0.609845, 0.61004,  0.610235, 0.61043,  0.610624, 0.610819, 0.611014, 0.611208,
        0.611403, 0.611597, 0.611791, 0.611985, 0.612179, 0.612373, 0.612567, 0.612761,
        0.612954, 0.613148, 0.613341, 0.613535, 0.613728, 0.613921, 0.614114, 0.614307,
        0.6145,   0.614693, 0.614885, 0.615078, 0.61527,  0.615463, 0.615655, 0.615847,
        0.616039, 0.616231, 0.616423, 0.616615, 0.616806, 0.616998, 0.61719,  0.617381,
        0.617572, 0.617763, 0.617955, 0.618146, 0.618336, 0.618527, 0.618718, 0.618909,
        0.619099, 0.61929,  0.61948,  0.61967,  0.61986,  0.620051, 0.620241, 0.62043,
        0.62062,  0.62081,  0.620999, 0.621189, 0.621378, 0.621568, 0.621757, 0.621946,
        0.622135, 0.622324, 0.622513, 0.622702, 0.62289,  0.623079, 0.623267, 0.623456,
        0.623644, 0.623832, 0.62402,  0.624208, 0.624396, 0.624584, 0.624772, 0.624959,
        0.625147, 0.625334, 0.625521, 0.625709, 0.625896, 0.626083, 0.62627,  0.626457,
        0.626643, 0.62683,  0.627017, 0.627203, 0.62739,  0.627576, 0.627762, 0.627948,
        0.628134, 0.62832,  0.628506, 0.628692, 0.628877, 0.629063, 0.629248, 0.629434,
        0.629619, 0.629804, 0.629989, 0.630174, 0.630359, 0.630544, 0.630729, 0.630914,
        0.631098, 0.631283, 0.631467, 0.631651, 0.631835, 0.632019, 0.632203, 0.632387,
        0.632571, 0.632755, 0.632938, 0.633122, 0.633305, 0.633489, 0.633672, 0.633855,
        0.634038, 0.634221, 0.634404, 0.634587, 0.63477,  0.634952, 0.635135, 0.635317,
        0.6355,   0.635682, 0.635864, 0.636046, 0.636228, 0.63641,  0.636592, 0.636773,
        0.636955, 0.637137, 0.637318, 0.637499, 0.637681, 0.637862, 0.638043, 0.638224,
        0.638405, 0.638585, 0.638766, 0.638947, 0.639127, 0.639308, 0.639488, 0.639668,
        0.639848, 0.640029, 0.640209, 0.640388, 0.640568, 0.640748, 0.640928, 0.641107,
        0.641287, 0.641466, 0.641645, 0.641824, 0.642004, 0.642183, 0.642361, 0.64254,
        0.642719, 0.642898, 0.643076, 0.643255, 0.643433, 0.643611, 0.64379,  0.643968,
        0.644146, 0.644324, 0.644502, 0.644679, 0.644857, 0.645034, 0.645212, 0.645389,
        0.645567, 0.645744, 0.645921, 0.646098, 0.646275, 0.646452, 0.646629, 0.646805,
        0.646982, 0.647158, 0.647335, 0.647511, 0.647687, 0.647864, 0.64804,  0.648216,
        0.648391, 0.648567, 0.648743, 0.648919, 0.649094, 0.64927,  0.649445, 0.64962,
        0.649796, 0.649971, 0.650146, 0.650321, 0.650495, 0.65067,  0.650845, 0.651019,
        0.651194, 0.651368, 0.651543, 0.651717, 0.651891, 0.652065, 0.652239, 0.652413,
        0.652587, 0.65276,  0.652934, 0.653108, 0.653281, 0.653454, 0.653628, 0.653801,
        0.653974, 0.654147, 0.65432,  0.654493, 0.654665, 0.654838, 0.655011, 0.655183,
        0.655356, 0.655528, 0.6557,   0.655872, 0.656044, 0.656216, 0.656388, 0.65656,
        0.656732, 0.656903, 0.657075, 0.657246, 0.657418, 0.657589, 0.65776,  0.657931,
        0.658102, 0.658273, 0.658444, 0.658615, 0.658786, 0.658956, 0.659127, 0.659297,
        0.659468, 0.659638, 0.659808, 0.659978, 0.660148, 0.660318, 0.660488, 0.660658,
        0.660827, 0.660997, 0.661166, 0.661336, 0.661505, 0.661674, 0.661844, 0.662013,
        0.662182, 0.662351, 0.662519, 0.662688, 0.662857, 0.663025, 0.663194, 0.663362,
        0.663531, 0.663699, 0.663867, 0.664035, 0.664203, 0.664371, 0.664539, 0.664706,
        0.664874, 0.665042, 0.665209, 0.665377, 0.665544, 0.665711, 0.665878, 0.666045,
        0.666212, 0.666379, 0.666546, 0.666713, 0.666879, 0.667046, 0.667212, 0.667379,
        0.667545, 0.667711, 0.667877, 0.668043, 0.668209, 0.668375, 0.668541, 0.668707,
        0.668873, 0.669038, 0.669204, 0.669369, 0.669534, 0.6697,   0.669865, 0.67003,
        0.670195, 0.67036,  0.670524, 0.670689, 0.670854, 0.671018, 0.671183, 0.671347,
        0.671512, 0.671676, 0.67184,  0.672004, 0.672168, 0.672332, 0.672496, 0.67266,
        0.672823, 0.672987, 0.67315,  0.673314, 0.673477, 0.67364,  0.673804, 0.673967,
        0.67413,  0.674293, 0.674456, 0.674618, 0.674781, 0.674944, 0.675106, 0.675269,
        0.675431, 0.675593, 0.675755, 0.675918, 0.67608,  0.676242, 0.676403, 0.676565,
        0.676727, 0.676889, 0.67705,  0.677212, 0.677373, 0.677534, 0.677696, 0.677857,
        0.678018, 0.678179, 0.67834,  0.6785,   0.678661, 0.678822, 0.678982, 0.679143,
        0.679303, 0.679464, 0.679624, 0.679784, 0.679944, 0.680104, 0.680264, 0.680424,
        0.680584, 0.680744, 0.680903, 0.681063, 0.681222, 0.681382, 0.681541, 0.6817,
        0.681859, 0.682018, 0.682177, 0.682336, 0.682495, 0.682654, 0.682813, 0.682971,
        0.68313,  0.683288, 0.683446, 0.683605, 0.683763, 0.683921, 0.684079, 0.684237,
        0.684395, 0.684553, 0.68471,  0.684868, 0.685026, 0.685183, 0.685341, 0.685498,
        0.685655, 0.685812, 0.685969, 0.686126, 0.686283, 0.68644,  0.686597, 0.686754,
        0.68691,  0.687067, 0.687223, 0.68738,  0.687536, 0.687692, 0.687848, 0.688004,
        0.68816,  0.688316, 0.688472, 0.688628, 0.688784, 0.688939, 0.689095, 0.68925,
        0.689406, 0.689561, 0.689716, 0.689871, 0.690026, 0.690181, 0.690336, 0.690491,
        0.690646, 0.690801, 0.690955, 0.69111,  0.691264, 0.691418, 0.691573, 0.691727,
        0.691881, 0.692035, 0.692189, 0.692343, 0.692497, 0.692651, 0.692804, 0.692958,
        0.693111, 0.693265, 0.693418, 0.693572, 0.693725, 0.693878, 0.694031, 0.694184,
        0.694337, 0.69449,  0.694642, 0.694795, 0.694948, 0.6951,   0.695253, 0.695405,
        0.695557, 0.69571,  0.695862, 0.696014, 0.696166, 0.696318, 0.69647,  0.696621
    };

    for (unsigned int idx = 0; idx < 1000; idx++)
        input[idx] = .5f;

    agc_kernel(input, output, 1000);

    for (unsigned int idx = 0; idx < 1000; idx++)
        EXPECT_NEAR(output[idx], expected_output[idx], .0001f);
}

TEST(AnalogKernel, agc_complex_identity_test)
{
    auto agc_kernel = analog::agc_cc(.001f, 1.0f, 1.0f, 65536.0f);
    std::complex<float> input[1000];
    std::complex<float> output[1000];
    std::complex<float> expected_output[1000];

    for (unsigned int idx = 0; idx < 1000; idx++) {
        input[idx] = 1.0f;
        output[idx] = 1.0f;
        expected_output[idx] = 1.0f;
    }

    agc_kernel(input, output, 1000);

    for (unsigned int idx = 0; idx < 1000; idx++) {
        EXPECT_NEAR(output[idx].real(), expected_output[idx].real(), .0001f);
        EXPECT_NEAR(output[idx].imag(), expected_output[idx].imag(), .0001f);
    }
}

TEST(AnalogKernel, agc_complex_ramp_test)
{
    auto agc_kernel = analog::agc_cc(.001f, 1.0f, 1.0f, 65536.0f);
    std::complex<float> input[1000];
    std::complex<float> output[1000];
    std::complex<float> expected_output[1000] = {
        { 0.5, 0.5 },           { 0.500146, 0.500146 }, { 0.500293, 0.500293 },
        { 0.500439, 0.500439 }, { 0.500585, 0.500585 }, { 0.500731, 0.500731 },
        { 0.500877, 0.500877 }, { 0.501023, 0.501023 }, { 0.501169, 0.501169 },
        { 0.501314, 0.501314 }, { 0.50146, 0.50146 },   { 0.501605, 0.501605 },
        { 0.501751, 0.501751 }, { 0.501896, 0.501896 }, { 0.502041, 0.502041 },
        { 0.502186, 0.502186 }, { 0.502331, 0.502331 }, { 0.502476, 0.502476 },
        { 0.50262, 0.50262 },   { 0.502765, 0.502765 }, { 0.502909, 0.502909 },
        { 0.503054, 0.503054 }, { 0.503198, 0.503198 }, { 0.503342, 0.503342 },
        { 0.503486, 0.503486 }, { 0.50363, 0.50363 },   { 0.503774, 0.503774 },
        { 0.503918, 0.503918 }, { 0.504062, 0.504062 }, { 0.504205, 0.504205 },
        { 0.504349, 0.504349 }, { 0.504492, 0.504492 }, { 0.504635, 0.504635 },
        { 0.504778, 0.504778 }, { 0.504921, 0.504921 }, { 0.505064, 0.505064 },
        { 0.505207, 0.505207 }, { 0.50535, 0.50535 },   { 0.505493, 0.505493 },
        { 0.505635, 0.505635 }, { 0.505778, 0.505778 }, { 0.50592, 0.50592 },
        { 0.506062, 0.506062 }, { 0.506204, 0.506204 }, { 0.506347, 0.506347 },
        { 0.506489, 0.506489 }, { 0.50663, 0.50663 },   { 0.506772, 0.506772 },
        { 0.506914, 0.506914 }, { 0.507055, 0.507055 }, { 0.507197, 0.507197 },
        { 0.507338, 0.507338 }, { 0.507479, 0.507479 }, { 0.507621, 0.507621 },
        { 0.507762, 0.507762 }, { 0.507903, 0.507903 }, { 0.508043, 0.508043 },
        { 0.508184, 0.508184 }, { 0.508325, 0.508325 }, { 0.508465, 0.508465 },
        { 0.508606, 0.508606 }, { 0.508746, 0.508746 }, { 0.508887, 0.508887 },
        { 0.509027, 0.509027 }, { 0.509167, 0.509167 }, { 0.509307, 0.509307 },
        { 0.509447, 0.509447 }, { 0.509586, 0.509586 }, { 0.509726, 0.509726 },
        { 0.509866, 0.509866 }, { 0.510005, 0.510005 }, { 0.510145, 0.510145 },
        { 0.510284, 0.510284 }, { 0.510423, 0.510423 }, { 0.510562, 0.510562 },
        { 0.510701, 0.510701 }, { 0.51084, 0.51084 },   { 0.510979, 0.510979 },
        { 0.511117, 0.511117 }, { 0.511256, 0.511256 }, { 0.511394, 0.511394 },
        { 0.511533, 0.511533 }, { 0.511671, 0.511671 }, { 0.511809, 0.511809 },
        { 0.511947, 0.511947 }, { 0.512085, 0.512085 }, { 0.512223, 0.512223 },
        { 0.512361, 0.512361 }, { 0.512499, 0.512499 }, { 0.512636, 0.512636 },
        { 0.512774, 0.512774 }, { 0.512911, 0.512911 }, { 0.513049, 0.513049 },
        { 0.513186, 0.513186 }, { 0.513323, 0.513323 }, { 0.51346, 0.51346 },
        { 0.513597, 0.513597 }, { 0.513734, 0.513734 }, { 0.513871, 0.513871 },
        { 0.514007, 0.514007 }, { 0.514144, 0.514144 }, { 0.51428, 0.51428 },
        { 0.514417, 0.514417 }, { 0.514553, 0.514553 }, { 0.514689, 0.514689 },
        { 0.514825, 0.514825 }, { 0.514961, 0.514961 }, { 0.515097, 0.515097 },
        { 0.515233, 0.515233 }, { 0.515368, 0.515368 }, { 0.515504, 0.515504 },
        { 0.515639, 0.515639 }, { 0.515775, 0.515775 }, { 0.51591, 0.51591 },
        { 0.516045, 0.516045 }, { 0.51618, 0.51618 },   { 0.516315, 0.516315 },
        { 0.51645, 0.51645 },   { 0.516585, 0.516585 }, { 0.51672, 0.51672 },
        { 0.516854, 0.516854 }, { 0.516989, 0.516989 }, { 0.517123, 0.517123 },
        { 0.517258, 0.517258 }, { 0.517392, 0.517392 }, { 0.517526, 0.517526 },
        { 0.51766, 0.51766 },   { 0.517794, 0.517794 }, { 0.517928, 0.517928 },
        { 0.518062, 0.518062 }, { 0.518195, 0.518195 }, { 0.518329, 0.518329 },
        { 0.518462, 0.518462 }, { 0.518596, 0.518596 }, { 0.518729, 0.518729 },
        { 0.518862, 0.518862 }, { 0.518995, 0.518995 }, { 0.519129, 0.519129 },
        { 0.519261, 0.519261 }, { 0.519394, 0.519394 }, { 0.519527, 0.519527 },
        { 0.51966, 0.51966 },   { 0.519792, 0.519792 }, { 0.519925, 0.519925 },
        { 0.520057, 0.520057 }, { 0.520189, 0.520189 }, { 0.520321, 0.520321 },
        { 0.520453, 0.520453 }, { 0.520585, 0.520585 }, { 0.520717, 0.520717 },
        { 0.520849, 0.520849 }, { 0.520981, 0.520981 }, { 0.521112, 0.521112 },
        { 0.521244, 0.521244 }, { 0.521375, 0.521375 }, { 0.521507, 0.521507 },
        { 0.521638, 0.521638 }, { 0.521769, 0.521769 }, { 0.5219, 0.5219 },
        { 0.522031, 0.522031 }, { 0.522162, 0.522162 }, { 0.522293, 0.522293 },
        { 0.522424, 0.522424 }, { 0.522554, 0.522554 }, { 0.522685, 0.522685 },
        { 0.522815, 0.522815 }, { 0.522945, 0.522945 }, { 0.523076, 0.523076 },
        { 0.523206, 0.523206 }, { 0.523336, 0.523336 }, { 0.523466, 0.523466 },
        { 0.523596, 0.523596 }, { 0.523725, 0.523725 }, { 0.523855, 0.523855 },
        { 0.523985, 0.523985 }, { 0.524114, 0.524114 }, { 0.524243, 0.524243 },
        { 0.524373, 0.524373 }, { 0.524502, 0.524502 }, { 0.524631, 0.524631 },
        { 0.52476, 0.52476 },   { 0.524889, 0.524889 }, { 0.525018, 0.525018 },
        { 0.525147, 0.525147 }, { 0.525275, 0.525275 }, { 0.525404, 0.525404 },
        { 0.525532, 0.525532 }, { 0.525661, 0.525661 }, { 0.525789, 0.525789 },
        { 0.525917, 0.525917 }, { 0.526045, 0.526045 }, { 0.526173, 0.526173 },
        { 0.526301, 0.526301 }, { 0.526429, 0.526429 }, { 0.526557, 0.526557 },
        { 0.526685, 0.526685 }, { 0.526812, 0.526812 }, { 0.52694, 0.52694 },
        { 0.527067, 0.527067 }, { 0.527194, 0.527194 }, { 0.527322, 0.527322 },
        { 0.527449, 0.527449 }, { 0.527576, 0.527576 }, { 0.527703, 0.527703 },
        { 0.52783, 0.52783 },   { 0.527956, 0.527956 }, { 0.528083, 0.528083 },
        { 0.52821, 0.52821 },   { 0.528336, 0.528336 }, { 0.528462, 0.528462 },
        { 0.528589, 0.528589 }, { 0.528715, 0.528715 }, { 0.528841, 0.528841 },
        { 0.528967, 0.528967 }, { 0.529093, 0.529093 }, { 0.529219, 0.529219 },
        { 0.529345, 0.529345 }, { 0.529471, 0.529471 }, { 0.529596, 0.529596 },
        { 0.529722, 0.529722 }, { 0.529847, 0.529847 }, { 0.529972, 0.529972 },
        { 0.530098, 0.530098 }, { 0.530223, 0.530223 }, { 0.530348, 0.530348 },
        { 0.530473, 0.530473 }, { 0.530598, 0.530598 }, { 0.530722, 0.530722 },
        { 0.530847, 0.530847 }, { 0.530972, 0.530972 }, { 0.531096, 0.531096 },
        { 0.531221, 0.531221 }, { 0.531345, 0.531345 }, { 0.53147, 0.53147 },
        { 0.531594, 0.531594 }, { 0.531718, 0.531718 }, { 0.531842, 0.531842 },
        { 0.531966, 0.531966 }, { 0.53209, 0.53209 },   { 0.532213, 0.532213 },
        { 0.532337, 0.532337 }, { 0.532461, 0.532461 }, { 0.532584, 0.532584 },
        { 0.532708, 0.532708 }, { 0.532831, 0.532831 }, { 0.532954, 0.532954 },
        { 0.533077, 0.533077 }, { 0.5332, 0.5332 },     { 0.533323, 0.533323 },
        { 0.533446, 0.533446 }, { 0.533569, 0.533569 }, { 0.533692, 0.533692 },
        { 0.533814, 0.533814 }, { 0.533937, 0.533937 }, { 0.534059, 0.534059 },
        { 0.534182, 0.534182 }, { 0.534304, 0.534304 }, { 0.534426, 0.534426 },
        { 0.534548, 0.534548 }, { 0.53467, 0.53467 },   { 0.534792, 0.534792 },
        { 0.534914, 0.534914 }, { 0.535036, 0.535036 }, { 0.535157, 0.535157 },
        { 0.535279, 0.535279 }, { 0.5354, 0.5354 },     { 0.535522, 0.535522 },
        { 0.535643, 0.535643 }, { 0.535764, 0.535764 }, { 0.535886, 0.535886 },
        { 0.536007, 0.536007 }, { 0.536128, 0.536128 }, { 0.536249, 0.536249 },
        { 0.536369, 0.536369 }, { 0.53649, 0.53649 },   { 0.536611, 0.536611 },
        { 0.536731, 0.536731 }, { 0.536852, 0.536852 }, { 0.536972, 0.536972 },
        { 0.537093, 0.537093 }, { 0.537213, 0.537213 }, { 0.537333, 0.537333 },
        { 0.537453, 0.537453 }, { 0.537573, 0.537573 }, { 0.537693, 0.537693 },
        { 0.537813, 0.537813 }, { 0.537932, 0.537932 }, { 0.538052, 0.538052 },
        { 0.538171, 0.538171 }, { 0.538291, 0.538291 }, { 0.53841, 0.53841 },
        { 0.53853, 0.53853 },   { 0.538649, 0.538649 }, { 0.538768, 0.538768 },
        { 0.538887, 0.538887 }, { 0.539006, 0.539006 }, { 0.539125, 0.539125 },
        { 0.539244, 0.539244 }, { 0.539362, 0.539362 }, { 0.539481, 0.539481 },
        { 0.539599, 0.539599 }, { 0.539718, 0.539718 }, { 0.539836, 0.539836 },
        { 0.539954, 0.539954 }, { 0.540073, 0.540073 }, { 0.540191, 0.540191 },
        { 0.540309, 0.540309 }, { 0.540427, 0.540427 }, { 0.540545, 0.540545 },
        { 0.540662, 0.540662 }, { 0.54078, 0.54078 },   { 0.540898, 0.540898 },
        { 0.541015, 0.541015 }, { 0.541133, 0.541133 }, { 0.54125, 0.54125 },
        { 0.541367, 0.541367 }, { 0.541484, 0.541484 }, { 0.541602, 0.541602 },
        { 0.541719, 0.541719 }, { 0.541836, 0.541836 }, { 0.541952, 0.541952 },
        { 0.542069, 0.542069 }, { 0.542186, 0.542186 }, { 0.542303, 0.542303 },
        { 0.542419, 0.542419 }, { 0.542536, 0.542536 }, { 0.542652, 0.542652 },
        { 0.542768, 0.542768 }, { 0.542884, 0.542884 }, { 0.543001, 0.543001 },
        { 0.543117, 0.543117 }, { 0.543233, 0.543233 }, { 0.543348, 0.543348 },
        { 0.543464, 0.543464 }, { 0.54358, 0.54358 },   { 0.543696, 0.543696 },
        { 0.543811, 0.543811 }, { 0.543927, 0.543927 }, { 0.544042, 0.544042 },
        { 0.544157, 0.544157 }, { 0.544272, 0.544272 }, { 0.544388, 0.544388 },
        { 0.544503, 0.544503 }, { 0.544618, 0.544618 }, { 0.544733, 0.544733 },
        { 0.544847, 0.544847 }, { 0.544962, 0.544962 }, { 0.545077, 0.545077 },
        { 0.545191, 0.545191 }, { 0.545306, 0.545306 }, { 0.54542, 0.54542 },
        { 0.545534, 0.545534 }, { 0.545649, 0.545649 }, { 0.545763, 0.545763 },
        { 0.545877, 0.545877 }, { 0.545991, 0.545991 }, { 0.546105, 0.546105 },
        { 0.546219, 0.546219 }, { 0.546333, 0.546333 }, { 0.546446, 0.546446 },
        { 0.54656, 0.54656 },   { 0.546673, 0.546673 }, { 0.546787, 0.546787 },
        { 0.5469, 0.5469 },     { 0.547013, 0.547013 }, { 0.547127, 0.547127 },
        { 0.54724, 0.54724 },   { 0.547353, 0.547353 }, { 0.547466, 0.547466 },
        { 0.547579, 0.547579 }, { 0.547692, 0.547692 }, { 0.547804, 0.547804 },
        { 0.547917, 0.547917 }, { 0.548029, 0.548029 }, { 0.548142, 0.548142 },
        { 0.548254, 0.548254 }, { 0.548367, 0.548367 }, { 0.548479, 0.548479 },
        { 0.548591, 0.548591 }, { 0.548703, 0.548703 }, { 0.548815, 0.548815 },
        { 0.548927, 0.548927 }, { 0.549039, 0.549039 }, { 0.549151, 0.549151 },
        { 0.549263, 0.549263 }, { 0.549374, 0.549374 }, { 0.549486, 0.549486 },
        { 0.549597, 0.549597 }, { 0.549709, 0.549709 }, { 0.54982, 0.54982 },
        { 0.549931, 0.549931 }, { 0.550042, 0.550042 }, { 0.550153, 0.550153 },
        { 0.550264, 0.550264 }, { 0.550375, 0.550375 }, { 0.550486, 0.550486 },
        { 0.550597, 0.550597 }, { 0.550707, 0.550707 }, { 0.550818, 0.550818 },
        { 0.550928, 0.550928 }, { 0.551039, 0.551039 }, { 0.551149, 0.551149 },
        { 0.55126, 0.55126 },   { 0.55137, 0.55137 },   { 0.55148, 0.55148 },
        { 0.55159, 0.55159 },   { 0.5517, 0.5517 },     { 0.55181, 0.55181 },
        { 0.55192, 0.55192 },   { 0.552029, 0.552029 }, { 0.552139, 0.552139 },
        { 0.552249, 0.552249 }, { 0.552358, 0.552358 }, { 0.552467, 0.552467 },
        { 0.552577, 0.552577 }, { 0.552686, 0.552686 }, { 0.552795, 0.552795 },
        { 0.552904, 0.552904 }, { 0.553013, 0.553013 }, { 0.553122, 0.553122 },
        { 0.553231, 0.553231 }, { 0.55334, 0.55334 },   { 0.553449, 0.553449 },
        { 0.553557, 0.553557 }, { 0.553666, 0.553666 }, { 0.553775, 0.553775 },
        { 0.553883, 0.553883 }, { 0.553991, 0.553991 }, { 0.5541, 0.5541 },
        { 0.554208, 0.554208 }, { 0.554316, 0.554316 }, { 0.554424, 0.554424 },
        { 0.554532, 0.554532 }, { 0.55464, 0.55464 },   { 0.554748, 0.554748 },
        { 0.554855, 0.554855 }, { 0.554963, 0.554963 }, { 0.555071, 0.555071 },
        { 0.555178, 0.555178 }, { 0.555285, 0.555285 }, { 0.555393, 0.555393 },
        { 0.5555, 0.5555 },     { 0.555607, 0.555607 }, { 0.555714, 0.555714 },
        { 0.555821, 0.555821 }, { 0.555928, 0.555928 }, { 0.556035, 0.556035 },
        { 0.556142, 0.556142 }, { 0.556249, 0.556249 }, { 0.556356, 0.556356 },
        { 0.556462, 0.556462 }, { 0.556569, 0.556569 }, { 0.556675, 0.556675 },
        { 0.556782, 0.556782 }, { 0.556888, 0.556888 }, { 0.556994, 0.556994 },
        { 0.5571, 0.5571 },     { 0.557206, 0.557206 }, { 0.557312, 0.557312 },
        { 0.557418, 0.557418 }, { 0.557524, 0.557524 }, { 0.55763, 0.55763 },
        { 0.557736, 0.557736 }, { 0.557841, 0.557841 }, { 0.557947, 0.557947 },
        { 0.558052, 0.558052 }, { 0.558158, 0.558158 }, { 0.558263, 0.558263 },
        { 0.558368, 0.558368 }, { 0.558473, 0.558473 }, { 0.558578, 0.558578 },
        { 0.558683, 0.558683 }, { 0.558788, 0.558788 }, { 0.558893, 0.558893 },
        { 0.558998, 0.558998 }, { 0.559103, 0.559103 }, { 0.559207, 0.559207 },
        { 0.559312, 0.559312 }, { 0.559417, 0.559417 }, { 0.559521, 0.559521 },
        { 0.559625, 0.559625 }, { 0.55973, 0.55973 },   { 0.559834, 0.559834 },
        { 0.559938, 0.559938 }, { 0.560042, 0.560042 }, { 0.560146, 0.560146 },
        { 0.56025, 0.56025 },   { 0.560354, 0.560354 }, { 0.560458, 0.560458 },
        { 0.560561, 0.560561 }, { 0.560665, 0.560665 }, { 0.560768, 0.560768 },
        { 0.560872, 0.560872 }, { 0.560975, 0.560975 }, { 0.561079, 0.561079 },
        { 0.561182, 0.561182 }, { 0.561285, 0.561285 }, { 0.561388, 0.561388 },
        { 0.561491, 0.561491 }, { 0.561594, 0.561594 }, { 0.561697, 0.561697 },
        { 0.5618, 0.5618 },     { 0.561903, 0.561903 }, { 0.562005, 0.562005 },
        { 0.562108, 0.562108 }, { 0.562211, 0.562211 }, { 0.562313, 0.562313 },
        { 0.562415, 0.562415 }, { 0.562518, 0.562518 }, { 0.56262, 0.56262 },
        { 0.562722, 0.562722 }, { 0.562824, 0.562824 }, { 0.562926, 0.562926 },
        { 0.563028, 0.563028 }, { 0.56313, 0.56313 },   { 0.563232, 0.563232 },
        { 0.563334, 0.563334 }, { 0.563435, 0.563435 }, { 0.563537, 0.563537 },
        { 0.563638, 0.563638 }, { 0.56374, 0.56374 },   { 0.563841, 0.563841 },
        { 0.563942, 0.563942 }, { 0.564044, 0.564044 }, { 0.564145, 0.564145 },
        { 0.564246, 0.564246 }, { 0.564347, 0.564347 }, { 0.564448, 0.564448 },
        { 0.564549, 0.564549 }, { 0.56465, 0.56465 },   { 0.56475, 0.56475 },
        { 0.564851, 0.564851 }, { 0.564952, 0.564952 }, { 0.565052, 0.565052 },
        { 0.565153, 0.565153 }, { 0.565253, 0.565253 }, { 0.565353, 0.565353 },
        { 0.565453, 0.565453 }, { 0.565554, 0.565554 }, { 0.565654, 0.565654 },
        { 0.565754, 0.565754 }, { 0.565854, 0.565854 }, { 0.565954, 0.565954 },
        { 0.566053, 0.566053 }, { 0.566153, 0.566153 }, { 0.566253, 0.566253 },
        { 0.566352, 0.566352 }, { 0.566452, 0.566452 }, { 0.566551, 0.566551 },
        { 0.566651, 0.566651 }, { 0.56675, 0.56675 },   { 0.566849, 0.566849 },
        { 0.566948, 0.566948 }, { 0.567048, 0.567048 }, { 0.567147, 0.567147 },
        { 0.567246, 0.567246 }, { 0.567344, 0.567344 }, { 0.567443, 0.567443 },
        { 0.567542, 0.567542 }, { 0.567641, 0.567641 }, { 0.567739, 0.567739 },
        { 0.567838, 0.567838 }, { 0.567936, 0.567936 }, { 0.568035, 0.568035 },
        { 0.568133, 0.568133 }, { 0.568231, 0.568231 }, { 0.56833, 0.56833 },
        { 0.568428, 0.568428 }, { 0.568526, 0.568526 }, { 0.568624, 0.568624 },
        { 0.568722, 0.568722 }, { 0.56882, 0.56882 },   { 0.568917, 0.568917 },
        { 0.569015, 0.569015 }, { 0.569113, 0.569113 }, { 0.56921, 0.56921 },
        { 0.569308, 0.569308 }, { 0.569405, 0.569405 }, { 0.569503, 0.569503 },
        { 0.5696, 0.5696 },     { 0.569697, 0.569697 }, { 0.569794, 0.569794 },
        { 0.569891, 0.569891 }, { 0.569988, 0.569988 }, { 0.570085, 0.570085 },
        { 0.570182, 0.570182 }, { 0.570279, 0.570279 }, { 0.570376, 0.570376 },
        { 0.570473, 0.570473 }, { 0.570569, 0.570569 }, { 0.570666, 0.570666 },
        { 0.570762, 0.570762 }, { 0.570859, 0.570859 }, { 0.570955, 0.570955 },
        { 0.571051, 0.571051 }, { 0.571147, 0.571147 }, { 0.571244, 0.571244 },
        { 0.57134, 0.57134 },   { 0.571436, 0.571436 }, { 0.571532, 0.571532 },
        { 0.571627, 0.571627 }, { 0.571723, 0.571723 }, { 0.571819, 0.571819 },
        { 0.571915, 0.571915 }, { 0.57201, 0.57201 },   { 0.572106, 0.572106 },
        { 0.572201, 0.572201 }, { 0.572297, 0.572297 }, { 0.572392, 0.572392 },
        { 0.572487, 0.572487 }, { 0.572582, 0.572582 }, { 0.572678, 0.572678 },
        { 0.572773, 0.572773 }, { 0.572868, 0.572868 }, { 0.572963, 0.572963 },
        { 0.573057, 0.573057 }, { 0.573152, 0.573152 }, { 0.573247, 0.573247 },
        { 0.573342, 0.573342 }, { 0.573436, 0.573436 }, { 0.573531, 0.573531 },
        { 0.573625, 0.573625 }, { 0.57372, 0.57372 },   { 0.573814, 0.573814 },
        { 0.573908, 0.573908 }, { 0.574002, 0.574002 }, { 0.574096, 0.574096 },
        { 0.57419, 0.57419 },   { 0.574284, 0.574284 }, { 0.574378, 0.574378 },
        { 0.574472, 0.574472 }, { 0.574566, 0.574566 }, { 0.57466, 0.57466 },
        { 0.574753, 0.574753 }, { 0.574847, 0.574847 }, { 0.57494, 0.57494 },
        { 0.575034, 0.575034 }, { 0.575127, 0.575127 }, { 0.575221, 0.575221 },
        { 0.575314, 0.575314 }, { 0.575407, 0.575407 }, { 0.5755, 0.5755 },
        { 0.575593, 0.575593 }, { 0.575686, 0.575686 }, { 0.575779, 0.575779 },
        { 0.575872, 0.575872 }, { 0.575965, 0.575965 }, { 0.576058, 0.576058 },
        { 0.57615, 0.57615 },   { 0.576243, 0.576243 }, { 0.576335, 0.576335 },
        { 0.576428, 0.576428 }, { 0.57652, 0.57652 },   { 0.576613, 0.576613 },
        { 0.576705, 0.576705 }, { 0.576797, 0.576797 }, { 0.576889, 0.576889 },
        { 0.576981, 0.576981 }, { 0.577073, 0.577073 }, { 0.577165, 0.577165 },
        { 0.577257, 0.577257 }, { 0.577349, 0.577349 }, { 0.577441, 0.577441 },
        { 0.577532, 0.577532 }, { 0.577624, 0.577624 }, { 0.577716, 0.577716 },
        { 0.577807, 0.577807 }, { 0.577898, 0.577898 }, { 0.57799, 0.57799 },
        { 0.578081, 0.578081 }, { 0.578172, 0.578172 }, { 0.578264, 0.578264 },
        { 0.578355, 0.578355 }, { 0.578446, 0.578446 }, { 0.578537, 0.578537 },
        { 0.578628, 0.578628 }, { 0.578718, 0.578718 }, { 0.578809, 0.578809 },
        { 0.5789, 0.5789 },     { 0.578991, 0.578991 }, { 0.579081, 0.579081 },
        { 0.579172, 0.579172 }, { 0.579262, 0.579262 }, { 0.579353, 0.579353 },
        { 0.579443, 0.579443 }, { 0.579533, 0.579533 }, { 0.579623, 0.579623 },
        { 0.579714, 0.579714 }, { 0.579804, 0.579804 }, { 0.579894, 0.579894 },
        { 0.579984, 0.579984 }, { 0.580073, 0.580073 }, { 0.580163, 0.580163 },
        { 0.580253, 0.580253 }, { 0.580343, 0.580343 }, { 0.580432, 0.580432 },
        { 0.580522, 0.580522 }, { 0.580612, 0.580612 }, { 0.580701, 0.580701 },
        { 0.58079, 0.58079 },   { 0.58088, 0.58088 },   { 0.580969, 0.580969 },
        { 0.581058, 0.581058 }, { 0.581147, 0.581147 }, { 0.581236, 0.581236 },
        { 0.581325, 0.581325 }, { 0.581414, 0.581414 }, { 0.581503, 0.581503 },
        { 0.581592, 0.581592 }, { 0.581681, 0.581681 }, { 0.581769, 0.581769 },
        { 0.581858, 0.581858 }, { 0.581947, 0.581947 }, { 0.582035, 0.582035 },
        { 0.582124, 0.582124 }, { 0.582212, 0.582212 }, { 0.5823, 0.5823 },
        { 0.582389, 0.582389 }, { 0.582477, 0.582477 }, { 0.582565, 0.582565 },
        { 0.582653, 0.582653 }, { 0.582741, 0.582741 }, { 0.582829, 0.582829 },
        { 0.582917, 0.582917 }, { 0.583004, 0.583004 }, { 0.583092, 0.583092 },
        { 0.58318, 0.58318 },   { 0.583268, 0.583268 }, { 0.583355, 0.583355 },
        { 0.583443, 0.583443 }, { 0.58353, 0.58353 },   { 0.583617, 0.583617 },
        { 0.583705, 0.583705 }, { 0.583792, 0.583792 }, { 0.583879, 0.583879 },
        { 0.583966, 0.583966 }, { 0.584053, 0.584053 }, { 0.58414, 0.58414 },
        { 0.584227, 0.584227 }, { 0.584314, 0.584314 }, { 0.584401, 0.584401 },
        { 0.584488, 0.584488 }, { 0.584575, 0.584575 }, { 0.584661, 0.584661 },
        { 0.584748, 0.584748 }, { 0.584834, 0.584834 }, { 0.584921, 0.584921 },
        { 0.585007, 0.585007 }, { 0.585094, 0.585094 }, { 0.58518, 0.58518 },
        { 0.585266, 0.585266 }, { 0.585352, 0.585352 }, { 0.585438, 0.585438 },
        { 0.585524, 0.585524 }, { 0.58561, 0.58561 },   { 0.585696, 0.585696 },
        { 0.585782, 0.585782 }, { 0.585868, 0.585868 }, { 0.585954, 0.585954 },
        { 0.586039, 0.586039 }, { 0.586125, 0.586125 }, { 0.58621, 0.58621 },
        { 0.586296, 0.586296 }, { 0.586381, 0.586381 }, { 0.586467, 0.586467 },
        { 0.586552, 0.586552 }, { 0.586637, 0.586637 }, { 0.586722, 0.586722 },
        { 0.586807, 0.586807 }, { 0.586892, 0.586892 }, { 0.586977, 0.586977 },
        { 0.587062, 0.587062 }, { 0.587147, 0.587147 }, { 0.587232, 0.587232 },
        { 0.587317, 0.587317 }, { 0.587402, 0.587402 }, { 0.587486, 0.587486 },
        { 0.587571, 0.587571 }, { 0.587655, 0.587655 }, { 0.58774, 0.58774 },
        { 0.587824, 0.587824 }, { 0.587908, 0.587908 }, { 0.587993, 0.587993 },
        { 0.588077, 0.588077 }, { 0.588161, 0.588161 }, { 0.588245, 0.588245 },
        { 0.588329, 0.588329 }, { 0.588413, 0.588413 }, { 0.588497, 0.588497 },
        { 0.588581, 0.588581 }, { 0.588665, 0.588665 }, { 0.588749, 0.588749 },
        { 0.588832, 0.588832 }, { 0.588916, 0.588916 }, { 0.588999, 0.588999 },
        { 0.589083, 0.589083 }, { 0.589166, 0.589166 }, { 0.58925, 0.58925 },
        { 0.589333, 0.589333 }, { 0.589416, 0.589416 }, { 0.5895, 0.5895 },
        { 0.589583, 0.589583 }, { 0.589666, 0.589666 }, { 0.589749, 0.589749 },
        { 0.589832, 0.589832 }, { 0.589915, 0.589915 }, { 0.589998, 0.589998 },
        { 0.59008, 0.59008 },   { 0.590163, 0.590163 }, { 0.590246, 0.590246 },
        { 0.590328, 0.590328 }, { 0.590411, 0.590411 }, { 0.590493, 0.590493 },
        { 0.590576, 0.590576 }, { 0.590658, 0.590658 }, { 0.590741, 0.590741 },
        { 0.590823, 0.590823 }, { 0.590905, 0.590905 }, { 0.590987, 0.590987 },
        { 0.591069, 0.591069 }, { 0.591151, 0.591151 }, { 0.591233, 0.591233 },
        { 0.591315, 0.591315 }, { 0.591397, 0.591397 }, { 0.591479, 0.591479 },
        { 0.591561, 0.591561 }, { 0.591643, 0.591643 }, { 0.591724, 0.591724 },
        { 0.591806, 0.591806 }, { 0.591887, 0.591887 }, { 0.591969, 0.591969 },
        { 0.59205, 0.59205 },   { 0.592132, 0.592132 }, { 0.592213, 0.592213 },
        { 0.592294, 0.592294 }, { 0.592375, 0.592375 }, { 0.592457, 0.592457 },
        { 0.592538, 0.592538 }, { 0.592619, 0.592619 }, { 0.5927, 0.5927 },
        { 0.59278, 0.59278 },   { 0.592861, 0.592861 }, { 0.592942, 0.592942 },
        { 0.593023, 0.593023 }, { 0.593103, 0.593103 }, { 0.593184, 0.593184 },
        { 0.593265, 0.593265 }, { 0.593345, 0.593345 }, { 0.593426, 0.593426 },
        { 0.593506, 0.593506 }, { 0.593586, 0.593586 }, { 0.593667, 0.593667 },
        { 0.593747, 0.593747 }, { 0.593827, 0.593827 }, { 0.593907, 0.593907 },
        { 0.593987, 0.593987 }, { 0.594067, 0.594067 }, { 0.594147, 0.594147 },
        { 0.594227, 0.594227 }, { 0.594307, 0.594307 }, { 0.594386, 0.594386 },
        { 0.594466, 0.594466 }, { 0.594546, 0.594546 }, { 0.594625, 0.594625 },
        { 0.594705, 0.594705 }, { 0.594784, 0.594784 }, { 0.594864, 0.594864 },
        { 0.594943, 0.594943 }, { 0.595022, 0.595022 }, { 0.595102, 0.595102 },
        { 0.595181, 0.595181 }, { 0.59526, 0.59526 },   { 0.595339, 0.595339 },
        { 0.595418, 0.595418 }, { 0.595497, 0.595497 }, { 0.595576, 0.595576 },
        { 0.595655, 0.595655 }, { 0.595734, 0.595734 }, { 0.595813, 0.595813 },
        { 0.595891, 0.595891 }, { 0.59597, 0.59597 },   { 0.596048, 0.596048 },
        { 0.596127, 0.596127 }, { 0.596205, 0.596205 }, { 0.596284, 0.596284 },
        { 0.596362, 0.596362 }, { 0.596441, 0.596441 }, { 0.596519, 0.596519 },
        { 0.596597, 0.596597 }, { 0.596675, 0.596675 }, { 0.596753, 0.596753 },
        { 0.596831, 0.596831 }, { 0.596909, 0.596909 }, { 0.596987, 0.596987 },
        { 0.597065, 0.597065 }, { 0.597143, 0.597143 }, { 0.597221, 0.597221 },
        { 0.597298, 0.597298 }, { 0.597376, 0.597376 }, { 0.597454, 0.597454 },
        { 0.597531, 0.597531 }, { 0.597609, 0.597609 }, { 0.597686, 0.597686 },
        { 0.597763, 0.597763 }, { 0.597841, 0.597841 }, { 0.597918, 0.597918 },
        { 0.597995, 0.597995 }, { 0.598072, 0.598072 }, { 0.598149, 0.598149 },
        { 0.598226, 0.598226 }, { 0.598303, 0.598303 }, { 0.59838, 0.59838 },
        { 0.598457, 0.598457 }, { 0.598534, 0.598534 }, { 0.598611, 0.598611 },
        { 0.598688, 0.598688 }, { 0.598764, 0.598764 }, { 0.598841, 0.598841 },
        { 0.598917, 0.598917 }, { 0.598994, 0.598994 }, { 0.59907, 0.59907 },
        { 0.599147, 0.599147 }, { 0.599223, 0.599223 }, { 0.599299, 0.599299 },
        { 0.599376, 0.599376 }, { 0.599452, 0.599452 }, { 0.599528, 0.599528 },
        { 0.599604, 0.599604 }, { 0.59968, 0.59968 },   { 0.599756, 0.599756 },
        { 0.599832, 0.599832 }, { 0.599908, 0.599908 }, { 0.599984, 0.599984 },
        { 0.600059, 0.600059 }, { 0.600135, 0.600135 }, { 0.600211, 0.600211 },
        { 0.600286, 0.600286 }, { 0.600362, 0.600362 }, { 0.600437, 0.600437 },
        { 0.600513, 0.600513 }, { 0.600588, 0.600588 }, { 0.600663, 0.600663 },
        { 0.600739, 0.600739 }, { 0.600814, 0.600814 }, { 0.600889, 0.600889 },
        { 0.600964, 0.600964 }, { 0.601039, 0.601039 }, { 0.601114, 0.601114 },
        { 0.601189, 0.601189 }, { 0.601264, 0.601264 }, { 0.601339, 0.601339 },
        { 0.601414, 0.601414 }, { 0.601488, 0.601488 }, { 0.601563, 0.601563 },
        { 0.601638, 0.601638 }, { 0.601712, 0.601712 }, { 0.601787, 0.601787 },
        { 0.601861, 0.601861 }, { 0.601936, 0.601936 }, { 0.60201, 0.60201 },
        { 0.602084, 0.602084 }, { 0.602159, 0.602159 }, { 0.602233, 0.602233 },
        { 0.602307, 0.602307 }, { 0.602381, 0.602381 }, { 0.602455, 0.602455 },
        { 0.602529, 0.602529 }, { 0.602603, 0.602603 }, { 0.602677, 0.602677 },
        { 0.602751, 0.602751 }, { 0.602825, 0.602825 }, { 0.602898, 0.602898 },
        { 0.602972, 0.602972 }, { 0.603046, 0.603046 }, { 0.603119, 0.603119 },
        { 0.603193, 0.603193 }, { 0.603266, 0.603266 }, { 0.60334, 0.60334 },
        { 0.603413, 0.603413 }, { 0.603486, 0.603486 }, { 0.60356, 0.60356 },
        { 0.603633, 0.603633 }, { 0.603706, 0.603706 }, { 0.603779, 0.603779 },
        { 0.603852, 0.603852 }, { 0.603925, 0.603925 }, { 0.603998, 0.603998 },
        { 0.604071, 0.604071 }, { 0.604144, 0.604144 }, { 0.604217, 0.604217 },
        { 0.60429, 0.60429 },   { 0.604362, 0.604362 }, { 0.604435, 0.604435 },
        { 0.604508, 0.604508 }, { 0.60458, 0.60458 },   { 0.604653, 0.604653 },
        { 0.604725, 0.604725 }, { 0.604797, 0.604797 }, { 0.60487, 0.60487 },
        { 0.604942, 0.604942 }
    };

    for (unsigned int idx = 0; idx < 1000; idx++)
        input[idx] = std::complex<float>(.5f, .5f);

    agc_kernel(input, output, 1000);

    for (unsigned int idx = 0; idx < 1000; idx++) {
        EXPECT_NEAR(output[idx].real(), expected_output[idx].real(), .0001f);
        EXPECT_NEAR(output[idx].imag(), expected_output[idx].imag(), .0001f);
    }
}