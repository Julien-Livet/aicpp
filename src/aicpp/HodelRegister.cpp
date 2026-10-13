// Automatically generated file. Do not modify.

#include <cstddef>

#include "aicpp/Hodel.h"
#include "aicpp/Neuron.h"
#include "aicpp/HodelRegister.h"
#include "aicpp/FunctionAdapterNeuron.h"
#include "aicpp/HodelPolymorphicNeuronRegister.h"

namespace aicpp
{
    using namespace hodel;

    // Original declaration: line 198
    aicpp::Neuron<hodel::Boolean> neuron_F_0{
        "F", [] () -> hodel::Boolean { return hodel::F; }};
    // Original declaration: line 199
    aicpp::Neuron<hodel::Boolean> neuron_T_1{
        "T", [] () -> hodel::Boolean { return hodel::T; }};
    // Original declaration: line 201
    aicpp::Neuron<hodel::Integer> neuron_ZERO_2{
        "ZERO", [] () -> hodel::Integer { return hodel::ZERO; }};
    // Original declaration: line 202
    aicpp::Neuron<hodel::Integer> neuron_ONE_3{
        "ONE", [] () -> hodel::Integer { return hodel::ONE; }};
    // Original declaration: line 203
    aicpp::Neuron<hodel::Integer> neuron_TWO_4{
        "TWO", [] () -> hodel::Integer { return hodel::TWO; }};
    // Original declaration: line 204
    aicpp::Neuron<hodel::Integer> neuron_THREE_5{
        "THREE", [] () -> hodel::Integer { return hodel::THREE; }};
    // Original declaration: line 205
    aicpp::Neuron<hodel::Integer> neuron_FOUR_6{
        "FOUR", [] () -> hodel::Integer { return hodel::FOUR; }};
    // Original declaration: line 206
    aicpp::Neuron<hodel::Integer> neuron_FIVE_7{
        "FIVE", [] () -> hodel::Integer { return hodel::FIVE; }};
    // Original declaration: line 207
    aicpp::Neuron<hodel::Integer> neuron_SIX_8{
        "SIX", [] () -> hodel::Integer { return hodel::SIX; }};
    // Original declaration: line 208
    aicpp::Neuron<hodel::Integer> neuron_SEVEN_9{
        "SEVEN", [] () -> hodel::Integer { return hodel::SEVEN; }};
    // Original declaration: line 209
    aicpp::Neuron<hodel::Integer> neuron_EIGHT_10{
        "EIGHT", [] () -> hodel::Integer { return hodel::EIGHT; }};
    // Original declaration: line 210
    aicpp::Neuron<hodel::Integer> neuron_NINE_11{
        "NINE", [] () -> hodel::Integer { return hodel::NINE; }};
    // Original declaration: line 211
    aicpp::Neuron<hodel::Integer> neuron_TEN_12{
        "TEN", [] () -> hodel::Integer { return hodel::TEN; }};
    // Original declaration: line 213
    aicpp::Neuron<hodel::Integer> neuron_NEG_ONE_13{
        "NEG_ONE", [] () -> hodel::Integer { return hodel::NEG_ONE; }};
    // Original declaration: line 214
    aicpp::Neuron<hodel::Integer> neuron_NEG_TWO_14{
        "NEG_TWO", [] () -> hodel::Integer { return hodel::NEG_TWO; }};
    // Original declaration: line 216
    aicpp::Neuron<IntegerTuple> neuron_DOWN_15{
        "DOWN", [] () -> IntegerTuple { return hodel::DOWN; }};
    // Original declaration: line 217
    aicpp::Neuron<IntegerTuple> neuron_RIGHT_16{
        "RIGHT", [] () -> IntegerTuple { return hodel::RIGHT; }};
    // Original declaration: line 218
    aicpp::Neuron<IntegerTuple> neuron_UP_17{
        "UP", [] () -> IntegerTuple { return hodel::UP; }};
    // Original declaration: line 219
    aicpp::Neuron<IntegerTuple> neuron_LEFT_18{
        "LEFT", [] () -> IntegerTuple { return hodel::LEFT; }};
    // Original declaration: line 221
    aicpp::Neuron<IntegerTuple> neuron_ORIGIN_19{
        "ORIGIN", [] () -> IntegerTuple { return hodel::ORIGIN; }};
    // Original declaration: line 222
    aicpp::Neuron<IntegerTuple> neuron_UNITY_20{
        "UNITY", [] () -> IntegerTuple { return hodel::UNITY; }};
    // Original declaration: line 223
    aicpp::Neuron<IntegerTuple> neuron_NEG_UNITY_21{
        "NEG_UNITY", [] () -> IntegerTuple { return hodel::NEG_UNITY; }};
    // Original declaration: line 224
    aicpp::Neuron<IntegerTuple> neuron_UP_RIGHT_22{
        "UP_RIGHT", [] () -> IntegerTuple { return hodel::UP_RIGHT; }};
    // Original declaration: line 225
    aicpp::Neuron<IntegerTuple> neuron_DOWN_LEFT_23{
        "DOWN_LEFT", [] () -> IntegerTuple { return hodel::DOWN_LEFT; }};
    // Original declaration: line 227
    aicpp::Neuron<IntegerTuple> neuron_ZERO_BY_TWO_24{
        "ZERO_BY_TWO", [] () -> IntegerTuple { return hodel::ZERO_BY_TWO; }};
    // Original declaration: line 228
    aicpp::Neuron<IntegerTuple> neuron_TWO_BY_ZERO_25{
        "TWO_BY_ZERO", [] () -> IntegerTuple { return hodel::TWO_BY_ZERO; }};
    // Original declaration: line 229
    aicpp::Neuron<IntegerTuple> neuron_TWO_BY_TWO_26{
        "TWO_BY_TWO", [] () -> IntegerTuple { return hodel::TWO_BY_TWO; }};
    // Original declaration: line 230
    aicpp::Neuron<IntegerTuple> neuron_THREE_BY_THREE_27{
        "THREE_BY_THREE", [] () -> IntegerTuple { return hodel::THREE_BY_THREE; }};
    // Original declaration: line 232
    aicpp::Neuron<hodel::Integer, hodel::Integer const&, hodel::Integer const&> neuron_add_28{
        "add", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::add)};
    // Original declaration: line 233
    aicpp::Neuron<IntegerTuple, IntegerTuple const&, hodel::Integer const&> neuron_add_29{
        "add", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&, hodel::Integer const&>::PointerFunction>(&hodel::add)};
    // Original declaration: line 234
    aicpp::Neuron<IntegerTuple, hodel::Integer const&, IntegerTuple const&> neuron_add_30{
        "add", static_cast<aicpp::Neuron<IntegerTuple, hodel::Integer const&, IntegerTuple const&>::PointerFunction>(&hodel::add)};
    // Original declaration: line 235
    aicpp::Neuron<IntegerTuple, IntegerTuple const&, IntegerTuple const&> neuron_add_31{
        "add", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::add)};
    // Original declaration: line 236
    aicpp::Neuron<hodel::Integer, hodel::Integer const&, hodel::Integer const&> neuron_subtract_32{
        "subtract", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::subtract)};
    // Original declaration: line 237
    aicpp::Neuron<IntegerTuple, IntegerTuple const&, hodel::Integer const&> neuron_subtract_33{
        "subtract", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&, hodel::Integer const&>::PointerFunction>(&hodel::subtract)};
    // Original declaration: line 238
    aicpp::Neuron<IntegerTuple, hodel::Integer const&, IntegerTuple const&> neuron_subtract_34{
        "subtract", static_cast<aicpp::Neuron<IntegerTuple, hodel::Integer const&, IntegerTuple const&>::PointerFunction>(&hodel::subtract)};
    // Original declaration: line 239
    aicpp::Neuron<IntegerTuple, IntegerTuple const&, IntegerTuple const&> neuron_subtract_35{
        "subtract", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::subtract)};
    // Original declaration: line 240
    aicpp::Neuron<hodel::Integer, hodel::Integer const&, hodel::Integer const&> neuron_multiply_36{
        "multiply", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::multiply)};
    // Original declaration: line 241
    aicpp::Neuron<IntegerTuple, IntegerTuple const&, hodel::Integer const&> neuron_multiply_37{
        "multiply", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&, hodel::Integer const&>::PointerFunction>(&hodel::multiply)};
    // Original declaration: line 242
    aicpp::Neuron<IntegerTuple, hodel::Integer const&, IntegerTuple const&> neuron_multiply_38{
        "multiply", static_cast<aicpp::Neuron<IntegerTuple, hodel::Integer const&, IntegerTuple const&>::PointerFunction>(&hodel::multiply)};
    // Original declaration: line 243
    aicpp::Neuron<IntegerTuple, IntegerTuple const&, IntegerTuple const&> neuron_multiply_39{
        "multiply", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::multiply)};
    // Original declaration: line 244
    aicpp::Neuron<hodel::Integer, hodel::Integer const&, hodel::Integer const&> neuron_divide_40{
        "divide", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::divide)};
    // Original declaration: line 245
    aicpp::Neuron<IntegerTuple, IntegerTuple const&, hodel::Integer const&> neuron_divide_41{
        "divide", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&, hodel::Integer const&>::PointerFunction>(&hodel::divide)};
    // Original declaration: line 246
    aicpp::Neuron<IntegerTuple, IntegerTuple const&, IntegerTuple const&> neuron_divide_42{
        "divide", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::divide)};
    // Original declaration: line 247
    aicpp::Neuron<hodel::Integer, hodel::Integer const&> neuron_invert_43{
        "invert", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&>::PointerFunction>(&hodel::invert)};
    // Original declaration: line 248
    aicpp::Neuron<IntegerTuple, IntegerTuple const&> neuron_invert_44{
        "invert", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&>::PointerFunction>(&hodel::invert)};
    // Original declaration: line 249
    aicpp::Neuron<hodel::Boolean, hodel::Integer const&> neuron_even_45{
        "even", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Integer const&>::PointerFunction>(&hodel::even)};
    // Original declaration: line 250
    aicpp::Neuron<hodel::Integer, hodel::Integer const&> neuron_double__46{
        "double", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&>::PointerFunction>(&hodel::double_)};
    // Original declaration: line 251
    aicpp::Neuron<IntegerTuple, IntegerTuple const&> neuron_double__47{
        "double", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&>::PointerFunction>(&hodel::double_)};
    // Original declaration: line 252
    aicpp::Neuron<hodel::Integer, hodel::Integer const&> neuron_halve_48{
        "halve", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&>::PointerFunction>(&hodel::halve)};
    // Original declaration: line 253
    aicpp::Neuron<IntegerTuple, IntegerTuple const&> neuron_halve_49{
        "halve", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&>::PointerFunction>(&hodel::halve)};
    // Original declaration: line 254
    aicpp::Neuron<hodel::Boolean, hodel::Boolean const&> neuron_flip_50{
        "flip", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Boolean const&>::PointerFunction>(&hodel::flip)};
    // Original declaration: line 255
    aicpp::Neuron<hodel::Boolean, hodel::Integer const&, hodel::Integer const&> neuron_greater_51{
        "greater", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::greater)};
    // Original declaration: line 256
    aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&> neuron_maximum_52{
        "maximum", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&>::PointerFunction>(&hodel::maximum)};
    // Original declaration: line 257
    aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&> neuron_maximum_53{
        "maximum", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&>::PointerFunction>(&hodel::maximum)};
    // Original declaration: line 258
    aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&> neuron_minimum_54{
        "minimum", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&>::PointerFunction>(&hodel::minimum)};
    // Original declaration: line 259
    aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&> neuron_minimum_55{
        "minimum", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&>::PointerFunction>(&hodel::minimum)};
    // Original declaration: line 260
    aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::Boolean const&> neuron_both_56{
        "both", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::Boolean const&>::PointerFunction>(&hodel::both)};
    // Original declaration: line 261
    aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::Boolean const&> neuron_either_57{
        "either", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::Boolean const&>::PointerFunction>(&hodel::either)};
    // Original declaration: line 262
    aicpp::Neuron<hodel::Integer, hodel::Integer const&> neuron_increment_58{
        "increment", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&>::PointerFunction>(&hodel::increment)};
    // Original declaration: line 263
    aicpp::Neuron<IntegerTuple, IntegerTuple const&> neuron_increment_59{
        "increment", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&>::PointerFunction>(&hodel::increment)};
    // Original declaration: line 264
    aicpp::Neuron<hodel::Integer, hodel::Integer const&> neuron_decrement_60{
        "decrement", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&>::PointerFunction>(&hodel::decrement)};
    // Original declaration: line 265
    aicpp::Neuron<IntegerTuple, IntegerTuple const&> neuron_decrement_61{
        "decrement", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&>::PointerFunction>(&hodel::decrement)};
    // Original declaration: line 266
    aicpp::Neuron<hodel::Integer, hodel::Integer const&> neuron_crement_62{
        "crement", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&>::PointerFunction>(&hodel::crement)};
    // Original declaration: line 267
    aicpp::Neuron<IntegerTuple, IntegerTuple const&> neuron_crement_63{
        "crement", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&>::PointerFunction>(&hodel::crement)};
    // Original declaration: line 268
    aicpp::Neuron<hodel::Integer, hodel::Integer const&> neuron_sign_64{
        "sign", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&>::PointerFunction>(&hodel::sign)};
    // Original declaration: line 269
    aicpp::Neuron<IntegerTuple, IntegerTuple const&> neuron_sign_65{
        "sign", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&>::PointerFunction>(&hodel::sign)};
    // Original declaration: line 270
    aicpp::Neuron<hodel::Boolean, hodel::Integer const&> neuron_positive_66{
        "positive", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Integer const&>::PointerFunction>(&hodel::positive)};
    // Original declaration: line 271
    aicpp::Neuron<IntegerTuple, hodel::Integer const&> neuron_toivec_67{
        "toivec", static_cast<aicpp::Neuron<IntegerTuple, hodel::Integer const&>::PointerFunction>(&hodel::toivec)};
    // Original declaration: line 272
    aicpp::Neuron<IntegerTuple, hodel::Integer const&> neuron_tojvec_68{
        "tojvec", static_cast<aicpp::Neuron<IntegerTuple, hodel::Integer const&>::PointerFunction>(&hodel::tojvec)};
    // Original declaration: line 273
    aicpp::Neuron<hodel::IntegerSet, hodel::Integer, hodel::Integer const&, hodel::Integer const&> neuron_interval_69{
        "interval", static_cast<aicpp::Neuron<hodel::IntegerSet, hodel::Integer, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::interval)};
    // Original declaration: line 274
    aicpp::Neuron<IntegerTuple, hodel::Integer const&, hodel::Integer const&> neuron_astuple_70{
        "astuple", static_cast<aicpp::Neuron<IntegerTuple, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::astuple)};
    // Original declaration: line 275
    aicpp::Neuron<hodel::FunctionIntegerPair, aicpp::FunctionValue const&, hodel::Integer const&> neuron_astuple_71{
        "astuple", static_cast<aicpp::Neuron<hodel::FunctionIntegerPair, aicpp::FunctionValue const&, hodel::Integer const&>::PointerFunction>(&hodel::astuple)};
    // Original declaration: line 276
    aicpp::Neuron<hodel::Cell, hodel::Integer const&, IntegerTuple const&> neuron_astuple_72{
        "astuple", static_cast<aicpp::Neuron<hodel::Cell, hodel::Integer const&, IntegerTuple const&>::PointerFunction>(&hodel::astuple)};
    // Original declaration: line 277
    aicpp::Neuron<IntegerTuple, hodel::Object const&> neuron_ulcorner_73{
        "ulcorner", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&>::PointerFunction>(&hodel::ulcorner)};
    // Original declaration: line 278
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_ulcorner_74{
        "ulcorner", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::ulcorner)};
    // Original declaration: line 279
    aicpp::Neuron<IntegerTuple, hodel::Object const&> neuron_urcorner_75{
        "urcorner", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&>::PointerFunction>(&hodel::urcorner)};
    // Original declaration: line 280
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_urcorner_76{
        "urcorner", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::urcorner)};
    // Original declaration: line 281
    aicpp::Neuron<IntegerTuple, hodel::Object const&> neuron_llcorner_77{
        "llcorner", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&>::PointerFunction>(&hodel::llcorner)};
    // Original declaration: line 282
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_llcorner_78{
        "llcorner", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::llcorner)};
    // Original declaration: line 283
    aicpp::Neuron<IntegerTuple, hodel::Object const&> neuron_lrcorner_79{
        "lrcorner", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&>::PointerFunction>(&hodel::lrcorner)};
    // Original declaration: line 284
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_lrcorner_80{
        "lrcorner", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::lrcorner)};
    // Original declaration: line 285
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, IntegerTuple const&, IntegerTuple const&> neuron_crop_81{
        "crop", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::crop)};
    // Original declaration: line 286
    aicpp::Neuron<hodel::Indices, hodel::Object const&> neuron_toindices_82{
        "toindices", static_cast<aicpp::Neuron<hodel::Indices, hodel::Object const&>::PointerFunction>(&hodel::toindices)};
    // Original declaration: line 287
    aicpp::Neuron<hodel::Object, hodel::Object const&, IntegerTuple const&> neuron_shift_83{
        "shift", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&, IntegerTuple const&>::PointerFunction>(&hodel::shift)};
    // Original declaration: line 288
    aicpp::Neuron<hodel::Indices, hodel::Indices const&, IntegerTuple const&> neuron_shift_84{
        "shift", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&, IntegerTuple const&>::PointerFunction>(&hodel::shift)};
    // Original declaration: line 289
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_uppermost_85{
        "uppermost", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::uppermost)};
    // Original declaration: line 290
    aicpp::Neuron<hodel::Integer, hodel::Indices const&> neuron_uppermost_86{
        "uppermost", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&>::PointerFunction>(&hodel::uppermost)};
    // Original declaration: line 291
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_lowermost_87{
        "lowermost", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::lowermost)};
    // Original declaration: line 292
    aicpp::Neuron<hodel::Integer, hodel::Indices const&> neuron_lowermost_88{
        "lowermost", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&>::PointerFunction>(&hodel::lowermost)};
    // Original declaration: line 293
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_leftmost_89{
        "leftmost", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::leftmost)};
    // Original declaration: line 294
    aicpp::Neuron<hodel::Integer, hodel::Indices const&> neuron_leftmost_90{
        "leftmost", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&>::PointerFunction>(&hodel::leftmost)};
    // Original declaration: line 295
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_rightmost_91{
        "rightmost", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::rightmost)};
    // Original declaration: line 296
    aicpp::Neuron<hodel::Integer, hodel::Indices const&> neuron_rightmost_92{
        "rightmost", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&>::PointerFunction>(&hodel::rightmost)};
    // Original declaration: line 297
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_rot90_93{
        "rot90", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::rot90)};
    // Original declaration: line 298
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_rot180_94{
        "rot180", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::rot180)};
    // Original declaration: line 299
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_rot270_95{
        "rot270", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::rot270)};
    // Original declaration: line 300
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_hmirror_96{
        "hmirror", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::hmirror)};
    // Original declaration: line 301
    aicpp::Neuron<hodel::Object, hodel::Object const&> neuron_hmirror_97{
        "hmirror", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&>::PointerFunction>(&hodel::hmirror)};
    // Original declaration: line 302
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_hmirror_98{
        "hmirror", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::hmirror)};
    // Original declaration: line 303
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_vmirror_99{
        "vmirror", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::vmirror)};
    // Original declaration: line 304
    aicpp::Neuron<hodel::Object, hodel::Object const&> neuron_vmirror_100{
        "vmirror", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&>::PointerFunction>(&hodel::vmirror)};
    // Original declaration: line 305
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_vmirror_101{
        "vmirror", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::vmirror)};
    // Original declaration: line 306
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_dmirror_102{
        "dmirror", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::dmirror)};
    // Original declaration: line 307
    aicpp::Neuron<hodel::Object, hodel::Object const&> neuron_dmirror_103{
        "dmirror", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&>::PointerFunction>(&hodel::dmirror)};
    // Original declaration: line 308
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_dmirror_104{
        "dmirror", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::dmirror)};
    // Original declaration: line 309
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_cmirror_105{
        "cmirror", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::cmirror)};
    // Original declaration: line 310
    aicpp::Neuron<hodel::Object, hodel::Object const&> neuron_cmirror_106{
        "cmirror", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&>::PointerFunction>(&hodel::cmirror)};
    // Original declaration: line 311
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_cmirror_107{
        "cmirror", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::cmirror)};
    // Original declaration: line 312
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&> neuron_hupscale_108{
        "hupscale", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::hupscale)};
    // Original declaration: line 313
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&> neuron_vupscale_109{
        "vupscale", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::vupscale)};
    // Original declaration: line 314
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&> neuron_upscale_110{
        "upscale", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::upscale)};
    // Original declaration: line 315
    aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Integer const&> neuron_upscale_111{
        "upscale", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Integer const&>::PointerFunction>(&hodel::upscale)};
    // Original declaration: line 316
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&> neuron_downscale_112{
        "downscale", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::downscale)};
    // Original declaration: line 317
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&> neuron_hconcat_113{
        "hconcat", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&>::PointerFunction>(&hodel::hconcat)};
    // Original declaration: line 318
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&> neuron_vconcat_114{
        "vconcat", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&>::PointerFunction>(&hodel::vconcat)};
    // Original declaration: line 319
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Integer const&> neuron_replace_115{
        "replace", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::replace)};
    // Original declaration: line 320
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Integer const&> neuron_switch__116{
        "switch", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::switch_)};
    // Original declaration: line 321
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_tophalf_117{
        "tophalf", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::tophalf)};
    // Original declaration: line 322
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_bottomhalf_118{
        "bottomhalf", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::bottomhalf)};
    // Original declaration: line 323
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_lefthalf_119{
        "lefthalf", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::lefthalf)};
    // Original declaration: line 324
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_righthalf_120{
        "righthalf", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::righthalf)};
    // Original declaration: line 325
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_trim_121{
        "trim", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::trim)};
    // Original declaration: line 326
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_compress_122{
        "compress", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::compress)};
    // Original declaration: line 327
    aicpp::Neuron<hodel::Object, hodel::Object const&> neuron_normalize_123{
        "normalize", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&>::PointerFunction>(&hodel::normalize)};
    // Original declaration: line 328
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_normalize_124{
        "normalize", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::normalize)};
    // Original declaration: line 329
    aicpp::Neuron<hodel::Indices, IntegerTuple const&> neuron_dneighbors_125{
        "dneighbors", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&>::PointerFunction>(&hodel::dneighbors)};
    // Original declaration: line 330
    aicpp::Neuron<hodel::Indices, IntegerTuple const&> neuron_ineighbors_126{
        "ineighbors", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&>::PointerFunction>(&hodel::ineighbors)};
    // Original declaration: line 331
    aicpp::Neuron<hodel::Indices, IntegerTuple const&> neuron_neighbors_127{
        "neighbors", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&>::PointerFunction>(&hodel::neighbors)};
    // Original declaration: line 332
    aicpp::Neuron<hodel::Object, hodel::Integer const&, hodel::Object const&> neuron_recolor_128{
        "recolor", static_cast<aicpp::Neuron<hodel::Object, hodel::Integer const&, hodel::Object const&>::PointerFunction>(&hodel::recolor)};
    // Original declaration: line 333
    aicpp::Neuron<hodel::Object, hodel::Integer const&, hodel::Indices const&> neuron_recolor_129{
        "recolor", static_cast<aicpp::Neuron<hodel::Object, hodel::Integer const&, hodel::Indices const&>::PointerFunction>(&hodel::recolor)};
    // Original declaration: line 334
    aicpp::Neuron<hodel::Boolean, hodel::Grid const&> neuron_square_130{
        "square", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Grid const&>::PointerFunction>(&hodel::square)};
    // Original declaration: line 335
    aicpp::Neuron<hodel::Boolean, hodel::Object const&> neuron_square_131{
        "square", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&>::PointerFunction>(&hodel::square)};
    // Original declaration: line 336
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&> neuron_square_132{
        "square", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&>::PointerFunction>(&hodel::square)};
    // Original declaration: line 337
    aicpp::Neuron<hodel::Boolean, hodel::Object const&> neuron_vline_133{
        "vline", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&>::PointerFunction>(&hodel::vline)};
    // Original declaration: line 338
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&> neuron_vline_134{
        "vline", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&>::PointerFunction>(&hodel::vline)};
    // Original declaration: line 339
    aicpp::Neuron<hodel::Boolean, hodel::Object const&> neuron_hline_135{
        "hline", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&>::PointerFunction>(&hodel::hline)};
    // Original declaration: line 340
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&> neuron_hline_136{
        "hline", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&>::PointerFunction>(&hodel::hline)};
    // Original declaration: line 341
    aicpp::Neuron<hodel::Integer, hodel::Grid const&> neuron_height_137{
        "height", static_cast<aicpp::Neuron<hodel::Integer, hodel::Grid const&>::PointerFunction>(&hodel::height)};
    // Original declaration: line 342
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_height_138{
        "height", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::height)};
    // Original declaration: line 343
    aicpp::Neuron<hodel::Integer, hodel::Indices const&> neuron_height_139{
        "height", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&>::PointerFunction>(&hodel::height)};
    // Original declaration: line 344
    aicpp::Neuron<hodel::Integer, hodel::Grid const&> neuron_width_140{
        "width", static_cast<aicpp::Neuron<hodel::Integer, hodel::Grid const&>::PointerFunction>(&hodel::width)};
    // Original declaration: line 345
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_width_141{
        "width", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::width)};
    // Original declaration: line 346
    aicpp::Neuron<hodel::Integer, hodel::Indices const&> neuron_width_142{
        "width", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&>::PointerFunction>(&hodel::width)};
    // Original declaration: line 347
    aicpp::Neuron<IntegerTuple, hodel::Grid const&> neuron_shape_143{
        "shape", static_cast<aicpp::Neuron<IntegerTuple, hodel::Grid const&>::PointerFunction>(&hodel::shape)};
    // Original declaration: line 348
    aicpp::Neuron<IntegerTuple, hodel::Object const&> neuron_shape_144{
        "shape", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&>::PointerFunction>(&hodel::shape)};
    // Original declaration: line 349
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_shape_145{
        "shape", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::shape)};
    // Original declaration: line 350
    aicpp::Neuron<hodel::Boolean, hodel::Grid const&> neuron_portrait_146{
        "portrait", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Grid const&>::PointerFunction>(&hodel::portrait)};
    // Original declaration: line 351
    aicpp::Neuron<hodel::Boolean, hodel::Object const&> neuron_portrait_147{
        "portrait", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&>::PointerFunction>(&hodel::portrait)};
    // Original declaration: line 352
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&> neuron_portrait_148{
        "portrait", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&>::PointerFunction>(&hodel::portrait)};
    // Original declaration: line 353
    aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::Boolean const&, hodel::Boolean const&> neuron_branch_149{
        "branch", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::Boolean const&, hodel::Boolean const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 354
    aicpp::Neuron<hodel::Integer, hodel::Boolean const&, hodel::Integer const&, hodel::Integer const&> neuron_branch_150{
        "branch", static_cast<aicpp::Neuron<hodel::Integer, hodel::Boolean const&, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 355
    aicpp::Neuron<IntegerTuple, hodel::Boolean const&, IntegerTuple const&, IntegerTuple const&> neuron_branch_151{
        "branch", static_cast<aicpp::Neuron<IntegerTuple, hodel::Boolean const&, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 356
    aicpp::Neuron<hodel::Indices, hodel::Boolean const&, hodel::Indices const&, hodel::Indices const&> neuron_branch_152{
        "branch", static_cast<aicpp::Neuron<hodel::Indices, hodel::Boolean const&, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 357
    aicpp::Neuron<hodel::Object, hodel::Boolean const&, hodel::Object const&, hodel::Object const&> neuron_branch_153{
        "branch", static_cast<aicpp::Neuron<hodel::Object, hodel::Boolean const&, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 358
    aicpp::Neuron<hodel::Grid, hodel::Boolean const&, hodel::Grid const&, hodel::Grid const&> neuron_branch_154{
        "branch", static_cast<aicpp::Neuron<hodel::Grid, hodel::Boolean const&, hodel::Grid const&, hodel::Grid const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 359
    aicpp::Neuron<hodel::GridVector, hodel::Boolean const&, hodel::GridVector const&, hodel::GridVector const&> neuron_branch_155{
        "branch", static_cast<aicpp::Neuron<hodel::GridVector, hodel::Boolean const&, hodel::GridVector const&, hodel::GridVector const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 360
    aicpp::Neuron<hodel::IntegerVector, hodel::Boolean const&, hodel::IntegerVector const&, hodel::IntegerVector const&> neuron_branch_156{
        "branch", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::Boolean const&, hodel::IntegerVector const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 361
    aicpp::Neuron<hodel::IndicesSet, hodel::Boolean const&, hodel::IndicesSet const&, hodel::IndicesSet const&> neuron_branch_157{
        "branch", static_cast<aicpp::Neuron<hodel::IndicesSet, hodel::Boolean const&, hodel::IndicesSet const&, hodel::IndicesSet const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 362
    aicpp::Neuron<hodel::IntegerSet, hodel::Boolean const&, hodel::IntegerSet const&, hodel::IntegerSet const&> neuron_branch_158{
        "branch", static_cast<aicpp::Neuron<hodel::IntegerSet, hodel::Boolean const&, hodel::IntegerSet const&, hodel::IntegerSet const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 363
    aicpp::Neuron<hodel::Objects, hodel::Boolean const&, hodel::Objects const&, hodel::Objects const&> neuron_branch_159{
        "branch", static_cast<aicpp::Neuron<hodel::Objects, hodel::Boolean const&, hodel::Objects const&, hodel::Objects const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 364
    aicpp::Neuron<hodel::ObjectVector, hodel::Boolean const&, hodel::ObjectVector const&, hodel::ObjectVector const&> neuron_branch_160{
        "branch", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::Boolean const&, hodel::ObjectVector const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 365
    aicpp::Neuron<hodel::ObjectsVector, hodel::Boolean const&, hodel::ObjectsVector const&, hodel::ObjectsVector const&> neuron_branch_161{
        "branch", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::Boolean const&, hodel::ObjectsVector const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 366
    aicpp::Neuron<hodel::IndicesVector, hodel::Boolean const&, hodel::IndicesVector const&, hodel::IndicesVector const&> neuron_branch_162{
        "branch", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::Boolean const&, hodel::IndicesVector const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 367
    aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&, hodel::BooleanVector const&, hodel::BooleanVector const&> neuron_branch_163{
        "branch", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&, hodel::BooleanVector const&, hodel::BooleanVector const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 368
    aicpp::Neuron<aicpp::FunctionValue, hodel::Boolean const&, aicpp::FunctionValue const&, aicpp::FunctionValue const&> neuron_branch_164{
        "branch", static_cast<aicpp::Neuron<aicpp::FunctionValue, hodel::Boolean const&, aicpp::FunctionValue const&, aicpp::FunctionValue const&>::PointerFunction>(&hodel::branch)};
    // Original declaration: line 369
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_color_165{
        "color", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::color)};
    // Original declaration: line 370
    aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Grid const&> neuron_toobject_166{
        "toobject", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Grid const&>::PointerFunction>(&hodel::toobject)};
    // Original declaration: line 371
    aicpp::Neuron<hodel::Object, hodel::Indices const&, hodel::Grid const&> neuron_toobject_167{
        "toobject", static_cast<aicpp::Neuron<hodel::Object, hodel::Indices const&, hodel::Grid const&>::PointerFunction>(&hodel::toobject)};
    // Original declaration: line 372
    aicpp::Neuron<hodel::Object, hodel::Grid const&> neuron_asobject_168{
        "asobject", static_cast<aicpp::Neuron<hodel::Object, hodel::Grid const&>::PointerFunction>(&hodel::asobject)};
    // Original declaration: line 373
    aicpp::Neuron<hodel::Integer, hodel::Grid const&> neuron_mostcolor_169{
        "mostcolor", static_cast<aicpp::Neuron<hodel::Integer, hodel::Grid const&>::PointerFunction>(&hodel::mostcolor)};
    // Original declaration: line 374
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_mostcolor_170{
        "mostcolor", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::mostcolor)};
    // Original declaration: line 375
    aicpp::Neuron<hodel::Integer, hodel::Grid const&> neuron_leastcolor_171{
        "leastcolor", static_cast<aicpp::Neuron<hodel::Integer, hodel::Grid const&>::PointerFunction>(&hodel::leastcolor)};
    // Original declaration: line 376
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_leastcolor_172{
        "leastcolor", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::leastcolor)};
    // Original declaration: line 377
    aicpp::Neuron<hodel::Indices, hodel::Grid const&, hodel::Integer const&> neuron_ofcolor_173{
        "ofcolor", static_cast<aicpp::Neuron<hodel::Indices, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::ofcolor)};
    // Original declaration: line 378
    aicpp::Neuron<hodel::Integer, hodel::Grid const&, hodel::Integer const&> neuron_colorcount_174{
        "colorcount", static_cast<aicpp::Neuron<hodel::Integer, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::colorcount)};
    // Original declaration: line 379
    aicpp::Neuron<hodel::Integer, hodel::Object const&, hodel::Integer const&> neuron_colorcount_175{
        "colorcount", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&, hodel::Integer const&>::PointerFunction>(&hodel::colorcount)};
    // Original declaration: line 380
    aicpp::Neuron<hodel::Objects, hodel::Objects const&, hodel::Integer const&> neuron_colorfilter_176{
        "colorfilter", static_cast<aicpp::Neuron<hodel::Objects, hodel::Objects const&, hodel::Integer const&>::PointerFunction>(&hodel::colorfilter)};
    // Original declaration: line 381
    aicpp::Neuron<hodel::Objects, hodel::Grid const&, hodel::Boolean const&, hodel::Boolean const&, hodel::Boolean const&> neuron_objects_177{
        "objects", static_cast<aicpp::Neuron<hodel::Objects, hodel::Grid const&, hodel::Boolean const&, hodel::Boolean const&, hodel::Boolean const&>::PointerFunction>(&hodel::objects)};
    // Original declaration: line 382
    aicpp::Neuron<hodel::Objects, hodel::Grid const&> neuron_partition_178{
        "partition", static_cast<aicpp::Neuron<hodel::Objects, hodel::Grid const&>::PointerFunction>(&hodel::partition)};
    // Original declaration: line 383
    aicpp::Neuron<hodel::Objects, hodel::Grid const&> neuron_fgpartition_179{
        "fgpartition", static_cast<aicpp::Neuron<hodel::Objects, hodel::Grid const&>::PointerFunction>(&hodel::fgpartition)};
    // Original declaration: line 384
    aicpp::Neuron<hodel::Indices, hodel::Grid const&> neuron_asindices_180{
        "asindices", static_cast<aicpp::Neuron<hodel::Indices, hodel::Grid const&>::PointerFunction>(&hodel::asindices)};
    // Original declaration: line 385
    aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::Boolean const&> neuron_equality_181{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::Boolean const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 386
    aicpp::Neuron<hodel::Boolean, hodel::Integer const&, hodel::Integer const&> neuron_equality_182{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 387
    aicpp::Neuron<hodel::Boolean, IntegerTuple const&, IntegerTuple const&> neuron_equality_183{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 388
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Indices const&> neuron_equality_184{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 389
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Object const&> neuron_equality_185{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 390
    aicpp::Neuron<hodel::Boolean, hodel::Grid const&, hodel::Grid const&> neuron_equality_186{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Grid const&, hodel::Grid const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 391
    aicpp::Neuron<hodel::Boolean, hodel::GridVector const&, hodel::GridVector const&> neuron_equality_187{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::GridVector const&, hodel::GridVector const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 392
    aicpp::Neuron<hodel::Boolean, hodel::IntegerVector const&, hodel::IntegerVector const&> neuron_equality_188{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::IntegerVector const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 393
    aicpp::Neuron<hodel::Boolean, hodel::IndicesSet const&, hodel::IndicesSet const&> neuron_equality_189{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::IndicesSet const&, hodel::IndicesSet const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 394
    aicpp::Neuron<hodel::Boolean, hodel::IntegerSet const&, hodel::IntegerSet const&> neuron_equality_190{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::IntegerSet const&, hodel::IntegerSet const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 395
    aicpp::Neuron<hodel::Boolean, hodel::Objects const&, hodel::Objects const&> neuron_equality_191{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Objects const&, hodel::Objects const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 396
    aicpp::Neuron<hodel::Boolean, hodel::ObjectVector const&, hodel::ObjectVector const&> neuron_equality_192{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::ObjectVector const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 397
    aicpp::Neuron<hodel::Boolean, hodel::ObjectsVector const&, hodel::ObjectsVector const&> neuron_equality_193{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::ObjectsVector const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 398
    aicpp::Neuron<hodel::Boolean, hodel::IndicesVector const&, hodel::IndicesVector const&> neuron_equality_194{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::IndicesVector const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 399
    aicpp::Neuron<hodel::Boolean, hodel::BooleanVector const&, hodel::BooleanVector const&> neuron_equality_195{
        "equality", static_cast<aicpp::Neuron<hodel::Boolean, hodel::BooleanVector const&, hodel::BooleanVector const&>::PointerFunction>(&hodel::equality)};
    // Original declaration: line 400
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Indices const&> neuron_hmatching_196{
        "hmatching", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::hmatching)};
    // Original declaration: line 401
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Indices const&> neuron_hmatching_197{
        "hmatching", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Indices const&>::PointerFunction>(&hodel::hmatching)};
    // Original declaration: line 402
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Object const&> neuron_hmatching_198{
        "hmatching", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Object const&>::PointerFunction>(&hodel::hmatching)};
    // Original declaration: line 403
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Object const&> neuron_hmatching_199{
        "hmatching", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::hmatching)};
    // Original declaration: line 404
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Indices const&> neuron_vmatching_200{
        "vmatching", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::vmatching)};
    // Original declaration: line 405
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Indices const&> neuron_vmatching_201{
        "vmatching", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Indices const&>::PointerFunction>(&hodel::vmatching)};
    // Original declaration: line 406
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Object const&> neuron_vmatching_202{
        "vmatching", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Object const&>::PointerFunction>(&hodel::vmatching)};
    // Original declaration: line 407
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Object const&> neuron_vmatching_203{
        "vmatching", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::vmatching)};
    // Original declaration: line 408
    aicpp::Neuron<hodel::Integer, hodel::Indices const&, hodel::Indices const&> neuron_manhattan_204{
        "manhattan", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::manhattan)};
    // Original declaration: line 409
    aicpp::Neuron<hodel::Integer, hodel::Object const&, hodel::Indices const&> neuron_manhattan_205{
        "manhattan", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&, hodel::Indices const&>::PointerFunction>(&hodel::manhattan)};
    // Original declaration: line 410
    aicpp::Neuron<hodel::Integer, hodel::Indices const&, hodel::Object const&> neuron_manhattan_206{
        "manhattan", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&, hodel::Object const&>::PointerFunction>(&hodel::manhattan)};
    // Original declaration: line 411
    aicpp::Neuron<hodel::Integer, hodel::Object const&, hodel::Object const&> neuron_manhattan_207{
        "manhattan", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::manhattan)};
    // Original declaration: line 412
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Indices const&> neuron_adjacent_208{
        "adjacent", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::adjacent)};
    // Original declaration: line 413
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Indices const&> neuron_adjacent_209{
        "adjacent", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Indices const&>::PointerFunction>(&hodel::adjacent)};
    // Original declaration: line 414
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Object const&> neuron_adjacent_210{
        "adjacent", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Object const&>::PointerFunction>(&hodel::adjacent)};
    // Original declaration: line 415
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Object const&> neuron_adjacent_211{
        "adjacent", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::adjacent)};
    // Original declaration: line 416
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Grid const> neuron_bordering_212{
        "bordering", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::Grid const>::PointerFunction>(&hodel::bordering)};
    // Original declaration: line 417
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Grid const> neuron_bordering_213{
        "bordering", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Grid const>::PointerFunction>(&hodel::bordering)};
    // Original declaration: line 418
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_centerofmass_214{
        "centerofmass", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::centerofmass)};
    // Original declaration: line 419
    aicpp::Neuron<IntegerTuple, hodel::Object const&> neuron_centerofmass_215{
        "centerofmass", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&>::PointerFunction>(&hodel::centerofmass)};
    // Original declaration: line 420
    aicpp::Neuron<hodel::IntegerSet, hodel::Grid const&> neuron_palette_216{
        "palette", static_cast<aicpp::Neuron<hodel::IntegerSet, hodel::Grid const&>::PointerFunction>(&hodel::palette)};
    // Original declaration: line 421
    aicpp::Neuron<hodel::IntegerSet, hodel::Object const&> neuron_palette_217{
        "palette", static_cast<aicpp::Neuron<hodel::IntegerSet, hodel::Object const&>::PointerFunction>(&hodel::palette)};
    // Original declaration: line 422
    aicpp::Neuron<hodel::Integer, hodel::Grid const&> neuron_numcolors_218{
        "numcolors", static_cast<aicpp::Neuron<hodel::Integer, hodel::Grid const&>::PointerFunction>(&hodel::numcolors)};
    // Original declaration: line 423
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_numcolors_219{
        "numcolors", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::numcolors)};
    // Original declaration: line 424
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Indices const&> neuron_fill_220{
        "fill", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Indices const&>::PointerFunction>(&hodel::fill)};
    // Original declaration: line 425
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Object const&> neuron_fill_221{
        "fill", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Object const&>::PointerFunction>(&hodel::fill)};
    // Original declaration: line 426
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Object const&> neuron_paint_222{
        "paint", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Object const&>::PointerFunction>(&hodel::paint)};
    // Original declaration: line 427
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Indices const&> neuron_underfill_223{
        "underfill", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Indices const&>::PointerFunction>(&hodel::underfill)};
    // Original declaration: line 428
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Object const&> neuron_underfill_224{
        "underfill", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Integer const&, hodel::Object const&>::PointerFunction>(&hodel::underfill)};
    // Original declaration: line 429
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Object const&> neuron_underpaint_225{
        "underpaint", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Object const&>::PointerFunction>(&hodel::underpaint)};
    // Original declaration: line 430
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_center_226{
        "center", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::center)};
    // Original declaration: line 431
    aicpp::Neuron<IntegerTuple, hodel::Object const&> neuron_center_227{
        "center", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&>::PointerFunction>(&hodel::center)};
    // Original declaration: line 432
    aicpp::Neuron<IntegerTuple, hodel::Indices const&, hodel::Indices const&> neuron_position_228{
        "position", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::position)};
    // Original declaration: line 433
    aicpp::Neuron<IntegerTuple, hodel::Object const&, hodel::Indices const&> neuron_position_229{
        "position", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&, hodel::Indices const&>::PointerFunction>(&hodel::position)};
    // Original declaration: line 434
    aicpp::Neuron<IntegerTuple, hodel::Indices const&, hodel::Object const&> neuron_position_230{
        "position", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&, hodel::Object const&>::PointerFunction>(&hodel::position)};
    // Original declaration: line 435
    aicpp::Neuron<IntegerTuple, hodel::Object const&, hodel::Object const&> neuron_position_231{
        "position", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::position)};
    // Original declaration: line 436
    aicpp::Neuron<hodel::Integer, hodel::Grid const&, IntegerTuple const&> neuron_index_232{
        "index", static_cast<aicpp::Neuron<hodel::Integer, hodel::Grid const&, IntegerTuple const&>::PointerFunction>(&hodel::index)};
    // Original declaration: line 437
    aicpp::Neuron<hodel::Grid, hodel::Integer const&, IntegerTuple const&> neuron_canvas_233{
        "canvas", static_cast<aicpp::Neuron<hodel::Grid, hodel::Integer const&, IntegerTuple const&>::PointerFunction>(&hodel::canvas)};
    // Original declaration: line 438
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_corners_234{
        "corners", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::corners)};
    // Original declaration: line 439
    aicpp::Neuron<hodel::Indices, hodel::Object const&> neuron_corners_235{
        "corners", static_cast<aicpp::Neuron<hodel::Indices, hodel::Object const&>::PointerFunction>(&hodel::corners)};
    // Original declaration: line 440
    aicpp::Neuron<hodel::Indices, IntegerTuple const&, IntegerTuple const&> neuron_connect_236{
        "connect", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::connect)};
    // Original declaration: line 441
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Indices const&> neuron_cover_237{
        "cover", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Indices const&>::PointerFunction>(&hodel::cover)};
    // Original declaration: line 442
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Object const&> neuron_cover_238{
        "cover", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Object const&>::PointerFunction>(&hodel::cover)};
    // Original declaration: line 443
    aicpp::Neuron<hodel::Indices, IntegerTuple const&> neuron_vfrontier_239{
        "vfrontier", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&>::PointerFunction>(&hodel::vfrontier)};
    // Original declaration: line 444
    aicpp::Neuron<hodel::Indices, IntegerTuple const&> neuron_hfrontier_240{
        "hfrontier", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&>::PointerFunction>(&hodel::hfrontier)};
    // Original declaration: line 445
    aicpp::Neuron<hodel::Indices, hodel::Object const&> neuron_backdrop_241{
        "backdrop", static_cast<aicpp::Neuron<hodel::Indices, hodel::Object const&>::PointerFunction>(&hodel::backdrop)};
    // Original declaration: line 446
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_backdrop_242{
        "backdrop", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::backdrop)};
    // Original declaration: line 447
    aicpp::Neuron<hodel::Indices, hodel::Object const&> neuron_delta_243{
        "delta", static_cast<aicpp::Neuron<hodel::Indices, hodel::Object const&>::PointerFunction>(&hodel::delta)};
    // Original declaration: line 448
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_delta_244{
        "delta", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::delta)};
    // Original declaration: line 449
    aicpp::Neuron<IntegerTuple, hodel::Indices const&, hodel::Indices const&> neuron_gravitate_245{
        "gravitate", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::gravitate)};
    // Original declaration: line 450
    aicpp::Neuron<IntegerTuple, hodel::Object const&, hodel::Indices const&> neuron_gravitate_246{
        "gravitate", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&, hodel::Indices const&>::PointerFunction>(&hodel::gravitate)};
    // Original declaration: line 451
    aicpp::Neuron<IntegerTuple, hodel::Indices const&, hodel::Object const&> neuron_gravitate_247{
        "gravitate", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&, hodel::Object const&>::PointerFunction>(&hodel::gravitate)};
    // Original declaration: line 452
    aicpp::Neuron<IntegerTuple, hodel::Object const&, hodel::Object const&> neuron_gravitate_248{
        "gravitate", static_cast<aicpp::Neuron<IntegerTuple, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::gravitate)};
    // Original declaration: line 453
    aicpp::Neuron<hodel::Indices, hodel::Object const&> neuron_inbox_249{
        "inbox", static_cast<aicpp::Neuron<hodel::Indices, hodel::Object const&>::PointerFunction>(&hodel::inbox)};
    // Original declaration: line 454
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_inbox_250{
        "inbox", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::inbox)};
    // Original declaration: line 455
    aicpp::Neuron<hodel::Indices, hodel::Object const&> neuron_outbox_251{
        "outbox", static_cast<aicpp::Neuron<hodel::Indices, hodel::Object const&>::PointerFunction>(&hodel::outbox)};
    // Original declaration: line 456
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_outbox_252{
        "outbox", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::outbox)};
    // Original declaration: line 457
    aicpp::Neuron<hodel::Indices, hodel::Object const&> neuron_box_253{
        "box", static_cast<aicpp::Neuron<hodel::Indices, hodel::Object const&>::PointerFunction>(&hodel::box)};
    // Original declaration: line 458
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_box_254{
        "box", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::box)};
    // Original declaration: line 459
    aicpp::Neuron<hodel::Indices, IntegerTuple const&, IntegerTuple const&> neuron_shoot_255{
        "shoot", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&, IntegerTuple const&>::PointerFunction>(&hodel::shoot)};
    // Original declaration: line 460
    aicpp::Neuron<hodel::Indices, hodel::Grid const&, hodel::Object const&> neuron_occurrences_256{
        "occurrences", static_cast<aicpp::Neuron<hodel::Indices, hodel::Grid const&, hodel::Object const&>::PointerFunction>(&hodel::occurrences)};
    // Original declaration: line 461
    aicpp::Neuron<hodel::Objects, hodel::Grid const&> neuron_frontiers_257{
        "frontiers", static_cast<aicpp::Neuron<hodel::Objects, hodel::Grid const&>::PointerFunction>(&hodel::frontiers)};
    // Original declaration: line 462
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_hperiod_258{
        "hperiod", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::hperiod)};
    // Original declaration: line 463
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_vperiod_259{
        "vperiod", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::vperiod)};
    // Original declaration: line 464
    aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&, hodel::IntegerVector const&> neuron_pair_260{
        "pair", static_cast<aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::pair)};
    // Original declaration: line 465
    aicpp::Neuron<hodel::Integer, hodel::Object const&> neuron_size_261{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::Object const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 466
    aicpp::Neuron<hodel::Integer, hodel::Objects const&> neuron_size_262{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::Objects const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 467
    aicpp::Neuron<hodel::Integer, hodel::ObjectVector const&> neuron_size_263{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::ObjectVector const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 468
    aicpp::Neuron<hodel::Integer, hodel::ObjectsVector const&> neuron_size_264{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::ObjectsVector const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 469
    aicpp::Neuron<hodel::Integer, hodel::Indices const&> neuron_size_265{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::Indices const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 470
    aicpp::Neuron<hodel::Integer, hodel::IndicesSet const&> neuron_size_266{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::IndicesSet const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 471
    aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&> neuron_size_267{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 472
    aicpp::Neuron<hodel::Integer, hodel::Grid const&> neuron_size_268{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::Grid const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 473
    aicpp::Neuron<hodel::Integer, hodel::GridVector const&> neuron_size_269{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::GridVector const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 474
    aicpp::Neuron<hodel::Integer, IntegerTuple const&> neuron_size_270{
        "size", static_cast<aicpp::Neuron<hodel::Integer, IntegerTuple const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 475
    aicpp::Neuron<hodel::Integer, hodel::IndicesVector const&> neuron_size_271{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::IndicesVector const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 476
    aicpp::Neuron<hodel::Integer, hodel::BooleanVector const&> neuron_size_272{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::BooleanVector const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 477
    aicpp::Neuron<hodel::Integer, hodel::FunctionIntegerPair const&> neuron_size_273{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::FunctionIntegerPair const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 478
    aicpp::Neuron<hodel::Integer, hodel::FunctionIntegerPairVector const&> neuron_size_274{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::FunctionIntegerPairVector const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 479
    aicpp::Neuron<hodel::Integer, hodel::Cell const&> neuron_size_275{
        "size", static_cast<aicpp::Neuron<hodel::Integer, hodel::Cell const&>::PointerFunction>(&hodel::size)};
    // Original declaration: line 480
    aicpp::Neuron<hodel::Boolean, hodel::Boolean const&> neuron_identity_276{
        "identity", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Boolean const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 481
    aicpp::Neuron<hodel::Integer, hodel::Integer const&> neuron_identity_277{
        "identity", static_cast<aicpp::Neuron<hodel::Integer, hodel::Integer const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 482
    aicpp::Neuron<IntegerTuple, IntegerTuple const&> neuron_identity_278{
        "identity", static_cast<aicpp::Neuron<IntegerTuple, IntegerTuple const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 483
    aicpp::Neuron<hodel::Indices, hodel::Indices const&> neuron_identity_279{
        "identity", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 484
    aicpp::Neuron<hodel::Object, hodel::Object const&> neuron_identity_280{
        "identity", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 485
    aicpp::Neuron<hodel::Grid, hodel::Grid const&> neuron_identity_281{
        "identity", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 486
    aicpp::Neuron<hodel::GridVector, hodel::GridVector const&> neuron_identity_282{
        "identity", static_cast<aicpp::Neuron<hodel::GridVector, hodel::GridVector const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 487
    aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&> neuron_identity_283{
        "identity", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 488
    aicpp::Neuron<hodel::IndicesSet, hodel::IndicesSet const&> neuron_identity_284{
        "identity", static_cast<aicpp::Neuron<hodel::IndicesSet, hodel::IndicesSet const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 489
    aicpp::Neuron<hodel::IntegerSet, hodel::IntegerSet const&> neuron_identity_285{
        "identity", static_cast<aicpp::Neuron<hodel::IntegerSet, hodel::IntegerSet const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 490
    aicpp::Neuron<hodel::Objects, hodel::Objects const&> neuron_identity_286{
        "identity", static_cast<aicpp::Neuron<hodel::Objects, hodel::Objects const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 491
    aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&> neuron_identity_287{
        "identity", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 492
    aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&> neuron_identity_288{
        "identity", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 493
    aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&> neuron_identity_289{
        "identity", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 494
    aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&> neuron_identity_290{
        "identity", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&>::PointerFunction>(&hodel::identity)};
    // Original declaration: line 495
    aicpp::Neuron<hodel::Integer, IntegerTuple const&> neuron_first_291{
        "first", static_cast<aicpp::Neuron<hodel::Integer, IntegerTuple const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 496
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_first_292{
        "first", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 497
    aicpp::Neuron<hodel::Cell, hodel::Object const&> neuron_first_293{
        "first", static_cast<aicpp::Neuron<hodel::Cell, hodel::Object const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 498
    aicpp::Neuron<hodel::IntegerVector, hodel::Grid const&> neuron_first_294{
        "first", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::Grid const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 499
    aicpp::Neuron<hodel::Grid, hodel::GridVector const&> neuron_first_295{
        "first", static_cast<aicpp::Neuron<hodel::Grid, hodel::GridVector const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 500
    aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&> neuron_first_296{
        "first", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 501
    aicpp::Neuron<hodel::Indices, hodel::IndicesSet const&> neuron_first_297{
        "first", static_cast<aicpp::Neuron<hodel::Indices, hodel::IndicesSet const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 502
    aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&> neuron_first_298{
        "first", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 503
    aicpp::Neuron<hodel::Object, hodel::Objects const&> neuron_first_299{
        "first", static_cast<aicpp::Neuron<hodel::Object, hodel::Objects const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 504
    aicpp::Neuron<hodel::Object, hodel::ObjectVector const&> neuron_first_300{
        "first", static_cast<aicpp::Neuron<hodel::Object, hodel::ObjectVector const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 505
    aicpp::Neuron<hodel::Objects, hodel::ObjectsVector const&> neuron_first_301{
        "first", static_cast<aicpp::Neuron<hodel::Objects, hodel::ObjectsVector const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 506
    aicpp::Neuron<hodel::Indices, hodel::IndicesVector const&> neuron_first_302{
        "first", static_cast<aicpp::Neuron<hodel::Indices, hodel::IndicesVector const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 507
    aicpp::Neuron<hodel::Boolean, hodel::BooleanVector const&> neuron_first_303{
        "first", static_cast<aicpp::Neuron<hodel::Boolean, hodel::BooleanVector const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 508
    aicpp::Neuron<hodel::Integer, hodel::Cell const&> neuron_first_304{
        "first", static_cast<aicpp::Neuron<hodel::Integer, hodel::Cell const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 509
    aicpp::Neuron<aicpp::FunctionValue, hodel::FunctionSet const&> neuron_first_305{
        "first", static_cast<aicpp::Neuron<aicpp::FunctionValue, hodel::FunctionSet const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 510
    aicpp::Neuron<hodel::FunctionIntegerPair, hodel::FunctionIntegerPairVector const&> neuron_first_306{
        "first", static_cast<aicpp::Neuron<hodel::FunctionIntegerPair, hodel::FunctionIntegerPairVector const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 511
    aicpp::Neuron<aicpp::FunctionValue, hodel::FunctionIntegerPair const&> neuron_first_307{
        "first", static_cast<aicpp::Neuron<aicpp::FunctionValue, hodel::FunctionIntegerPair const&>::PointerFunction>(&hodel::first)};
    // Original declaration: line 512
    aicpp::Neuron<hodel::Integer, IntegerTuple const&> neuron_last_308{
        "last", static_cast<aicpp::Neuron<hodel::Integer, IntegerTuple const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 513
    aicpp::Neuron<IntegerTuple, hodel::Indices const&> neuron_last_309{
        "last", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 514
    aicpp::Neuron<hodel::Cell, hodel::Object const&> neuron_last_310{
        "last", static_cast<aicpp::Neuron<hodel::Cell, hodel::Object const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 515
    aicpp::Neuron<hodel::IntegerVector, hodel::Grid const&> neuron_last_311{
        "last", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::Grid const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 516
    aicpp::Neuron<hodel::Grid, hodel::GridVector const&> neuron_last_312{
        "last", static_cast<aicpp::Neuron<hodel::Grid, hodel::GridVector const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 517
    aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&> neuron_last_313{
        "last", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 518
    aicpp::Neuron<hodel::Indices, hodel::IndicesSet const&> neuron_last_314{
        "last", static_cast<aicpp::Neuron<hodel::Indices, hodel::IndicesSet const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 519
    aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&> neuron_last_315{
        "last", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 520
    aicpp::Neuron<hodel::Object, hodel::Objects const&> neuron_last_316{
        "last", static_cast<aicpp::Neuron<hodel::Object, hodel::Objects const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 521
    aicpp::Neuron<hodel::Object, hodel::ObjectVector const&> neuron_last_317{
        "last", static_cast<aicpp::Neuron<hodel::Object, hodel::ObjectVector const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 522
    aicpp::Neuron<hodel::Objects, hodel::ObjectsVector const&> neuron_last_318{
        "last", static_cast<aicpp::Neuron<hodel::Objects, hodel::ObjectsVector const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 523
    aicpp::Neuron<hodel::Indices, hodel::IndicesVector const&> neuron_last_319{
        "last", static_cast<aicpp::Neuron<hodel::Indices, hodel::IndicesVector const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 524
    aicpp::Neuron<hodel::Boolean, hodel::BooleanVector const&> neuron_last_320{
        "last", static_cast<aicpp::Neuron<hodel::Boolean, hodel::BooleanVector const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 525
    aicpp::Neuron<IntegerTuple, hodel::Cell const&> neuron_last_321{
        "last", static_cast<aicpp::Neuron<IntegerTuple, hodel::Cell const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 526
    aicpp::Neuron<hodel::FunctionIntegerPair, hodel::FunctionIntegerPairVector const&> neuron_last_322{
        "last", static_cast<aicpp::Neuron<hodel::FunctionIntegerPair, hodel::FunctionIntegerPairVector const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 527
    aicpp::Neuron<hodel::Integer, hodel::FunctionIntegerPair const&> neuron_last_323{
        "last", static_cast<aicpp::Neuron<hodel::Integer, hodel::FunctionIntegerPair const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 528
    aicpp::Neuron<aicpp::FunctionValue, hodel::FunctionSet const&> neuron_last_324{
        "last", static_cast<aicpp::Neuron<aicpp::FunctionValue, hodel::FunctionSet const&>::PointerFunction>(&hodel::last)};
    // Original declaration: line 529
    aicpp::Neuron<hodel::Indices, IntegerTuple const&, hodel::Indices const&> neuron_insert_325{
        "insert", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&, hodel::Indices const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 530
    aicpp::Neuron<hodel::Object, hodel::Cell const&, hodel::Object const&> neuron_insert_326{
        "insert", static_cast<aicpp::Neuron<hodel::Object, hodel::Cell const&, hodel::Object const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 531
    aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&, hodel::Grid const&> neuron_insert_327{
        "insert", static_cast<aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&, hodel::Grid const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 532
    aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::GridVector const&> neuron_insert_328{
        "insert", static_cast<aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::GridVector const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 533
    aicpp::Neuron<hodel::IntegerVector, hodel::Integer const&, hodel::IntegerVector const&> neuron_insert_329{
        "insert", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::Integer const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 534
    aicpp::Neuron<hodel::IndicesSet, hodel::Indices const&, hodel::IndicesSet const&> neuron_insert_330{
        "insert", static_cast<aicpp::Neuron<hodel::IndicesSet, hodel::Indices const&, hodel::IndicesSet const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 535
    aicpp::Neuron<hodel::IntegerSet, hodel::Integer const&, hodel::IntegerSet const&> neuron_insert_331{
        "insert", static_cast<aicpp::Neuron<hodel::IntegerSet, hodel::Integer const&, hodel::IntegerSet const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 536
    aicpp::Neuron<hodel::Objects, hodel::Object const&, hodel::Objects const&> neuron_insert_332{
        "insert", static_cast<aicpp::Neuron<hodel::Objects, hodel::Object const&, hodel::Objects const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 537
    aicpp::Neuron<hodel::ObjectVector, hodel::Object const&, hodel::ObjectVector const&> neuron_insert_333{
        "insert", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::Object const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 538
    aicpp::Neuron<hodel::ObjectsVector, hodel::Objects const&, hodel::ObjectsVector const&> neuron_insert_334{
        "insert", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::Objects const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 539
    aicpp::Neuron<hodel::IndicesVector, hodel::Indices const&, hodel::IndicesVector const&> neuron_insert_335{
        "insert", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::Indices const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 540
    aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&, hodel::BooleanVector const&> neuron_insert_336{
        "insert", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&, hodel::BooleanVector const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 541
    aicpp::Neuron<hodel::FunctionSet, aicpp::FunctionValue const&, hodel::FunctionSet const&> neuron_insert_337{
        "insert", static_cast<aicpp::Neuron<hodel::FunctionSet, aicpp::FunctionValue const&, hodel::FunctionSet const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 542
    aicpp::Neuron<hodel::FunctionIntegerPairVector, hodel::FunctionIntegerPair const&, hodel::FunctionIntegerPairVector const&> neuron_insert_338{
        "insert", static_cast<aicpp::Neuron<hodel::FunctionIntegerPairVector, hodel::FunctionIntegerPair const&, hodel::FunctionIntegerPairVector const&>::PointerFunction>(&hodel::insert)};
    // Original declaration: line 543
    aicpp::Neuron<hodel::Indices, IntegerTuple const&, hodel::Indices const&> neuron_remove_339{
        "remove", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&, hodel::Indices const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 544
    aicpp::Neuron<hodel::Object, hodel::Cell const&, hodel::Object const&> neuron_remove_340{
        "remove", static_cast<aicpp::Neuron<hodel::Object, hodel::Cell const&, hodel::Object const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 545
    aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&, hodel::Grid const&> neuron_remove_341{
        "remove", static_cast<aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&, hodel::Grid const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 546
    aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::GridVector const&> neuron_remove_342{
        "remove", static_cast<aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::GridVector const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 547
    aicpp::Neuron<hodel::IntegerVector, hodel::Integer const&, hodel::IntegerVector const&> neuron_remove_343{
        "remove", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::Integer const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 548
    aicpp::Neuron<hodel::IndicesSet, hodel::Indices const&, hodel::IndicesSet const&> neuron_remove_344{
        "remove", static_cast<aicpp::Neuron<hodel::IndicesSet, hodel::Indices const&, hodel::IndicesSet const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 549
    aicpp::Neuron<hodel::IntegerSet, hodel::Integer const&, hodel::IntegerSet const&> neuron_remove_345{
        "remove", static_cast<aicpp::Neuron<hodel::IntegerSet, hodel::Integer const&, hodel::IntegerSet const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 550
    aicpp::Neuron<hodel::Objects, hodel::Object const&, hodel::Objects const&> neuron_remove_346{
        "remove", static_cast<aicpp::Neuron<hodel::Objects, hodel::Object const&, hodel::Objects const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 551
    aicpp::Neuron<hodel::ObjectVector, hodel::Object const&, hodel::ObjectVector const&> neuron_remove_347{
        "remove", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::Object const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 552
    aicpp::Neuron<hodel::ObjectsVector, hodel::Objects const&, hodel::ObjectsVector const&> neuron_remove_348{
        "remove", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::Objects const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 553
    aicpp::Neuron<hodel::IndicesVector, hodel::Indices const&, hodel::IndicesVector const&> neuron_remove_349{
        "remove", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::Indices const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 554
    aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&, hodel::BooleanVector const&> neuron_remove_350{
        "remove", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&, hodel::BooleanVector const&>::PointerFunction>(&hodel::remove)};
    // Original declaration: line 555
    aicpp::Neuron<IntegerTuple, hodel::Indices const&, IntegerTuple const&> neuron_other_351{
        "other", static_cast<aicpp::Neuron<IntegerTuple, hodel::Indices const&, IntegerTuple const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 556
    aicpp::Neuron<hodel::Cell, hodel::Object const&, hodel::Cell const&> neuron_other_352{
        "other", static_cast<aicpp::Neuron<hodel::Cell, hodel::Object const&, hodel::Cell const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 557
    aicpp::Neuron<hodel::IntegerVector, hodel::Grid const&, hodel::IntegerVector const&> neuron_other_353{
        "other", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::Grid const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 558
    aicpp::Neuron<hodel::Grid, hodel::GridVector const&, hodel::Grid const&> neuron_other_354{
        "other", static_cast<aicpp::Neuron<hodel::Grid, hodel::GridVector const&, hodel::Grid const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 559
    aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&, hodel::Integer const&> neuron_other_355{
        "other", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerVector const&, hodel::Integer const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 560
    aicpp::Neuron<hodel::Indices, hodel::IndicesSet const&, hodel::Indices const&> neuron_other_356{
        "other", static_cast<aicpp::Neuron<hodel::Indices, hodel::IndicesSet const&, hodel::Indices const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 561
    aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&, hodel::Integer const&> neuron_other_357{
        "other", static_cast<aicpp::Neuron<hodel::Integer, hodel::IntegerSet const&, hodel::Integer const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 562
    aicpp::Neuron<hodel::Object, hodel::Objects const&, hodel::Object const&> neuron_other_358{
        "other", static_cast<aicpp::Neuron<hodel::Object, hodel::Objects const&, hodel::Object const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 563
    aicpp::Neuron<hodel::Object, hodel::ObjectVector const&, hodel::Object const&> neuron_other_359{
        "other", static_cast<aicpp::Neuron<hodel::Object, hodel::ObjectVector const&, hodel::Object const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 564
    aicpp::Neuron<hodel::Objects, hodel::ObjectsVector const&, hodel::Objects const&> neuron_other_360{
        "other", static_cast<aicpp::Neuron<hodel::Objects, hodel::ObjectsVector const&, hodel::Objects const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 565
    aicpp::Neuron<hodel::Indices, hodel::IndicesVector const&, hodel::Indices const&> neuron_other_361{
        "other", static_cast<aicpp::Neuron<hodel::Indices, hodel::IndicesVector const&, hodel::Indices const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 566
    aicpp::Neuron<hodel::Boolean, hodel::BooleanVector const&, hodel::Boolean const&> neuron_other_362{
        "other", static_cast<aicpp::Neuron<hodel::Boolean, hodel::BooleanVector const&, hodel::Boolean const&>::PointerFunction>(&hodel::other)};
    // Original declaration: line 567
    aicpp::Neuron<hodel::Indices, IntegerTuple const&> neuron_initset_363{
        "initset", static_cast<aicpp::Neuron<hodel::Indices, IntegerTuple const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 568
    aicpp::Neuron<hodel::Object, hodel::Cell const&> neuron_initset_364{
        "initset", static_cast<aicpp::Neuron<hodel::Object, hodel::Cell const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 569
    aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&> neuron_initset_365{
        "initset", static_cast<aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 570
    aicpp::Neuron<hodel::GridVector, hodel::Grid const&> neuron_initset_366{
        "initset", static_cast<aicpp::Neuron<hodel::GridVector, hodel::Grid const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 571
    aicpp::Neuron<hodel::IndicesSet, hodel::Indices const&> neuron_initset_367{
        "initset", static_cast<aicpp::Neuron<hodel::IndicesSet, hodel::Indices const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 572
    aicpp::Neuron<hodel::IntegerSet, hodel::Integer const&> neuron_initset_368{
        "initset", static_cast<aicpp::Neuron<hodel::IntegerSet, hodel::Integer const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 573
    aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&> neuron_initset_369{
        "initset", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 574
    aicpp::Neuron<hodel::Objects, hodel::Object const&> neuron_initset_370{
        "initset", static_cast<aicpp::Neuron<hodel::Objects, hodel::Object const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 575
    aicpp::Neuron<hodel::ObjectsVector, hodel::Objects const&> neuron_initset_371{
        "initset", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::Objects const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 576
    aicpp::Neuron<hodel::FunctionSet, aicpp::FunctionValue const&> neuron_initset_372{
        "initset", static_cast<aicpp::Neuron<hodel::FunctionSet, aicpp::FunctionValue const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 577
    aicpp::Neuron<hodel::FunctionIntegerPairVector, hodel::FunctionIntegerPair const&> neuron_initset_373{
        "initset", static_cast<aicpp::Neuron<hodel::FunctionIntegerPairVector, hodel::FunctionIntegerPair const&>::PointerFunction>(&hodel::initset)};
    // Original declaration: line 578
    aicpp::Neuron<hodel::IntegerVector, IntegerTuple const&> neuron_totuple_374{
        "totuple", static_cast<aicpp::Neuron<hodel::IntegerVector, IntegerTuple const&>::PointerFunction>(&hodel::totuple)};
    // Original declaration: line 579
    aicpp::Neuron<hodel::IntegerVector, hodel::IntegerSet const&> neuron_totuple_375{
        "totuple", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::IntegerSet const&>::PointerFunction>(&hodel::totuple)};
    // Original declaration: line 580
    aicpp::Neuron<hodel::IndicesVector, hodel::IndicesSet const&> neuron_totuple_376{
        "totuple", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::IndicesSet const&>::PointerFunction>(&hodel::totuple)};
    // Original declaration: line 581
    aicpp::Neuron<hodel::ObjectVector, hodel::Objects const&> neuron_totuple_377{
        "totuple", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::Objects const&>::PointerFunction>(&hodel::totuple)};
    // Original declaration: line 582
    aicpp::Neuron<hodel::Grid, hodel::Object const&, hodel::Grid const&> neuron_subgrid_378{
        "subgrid", static_cast<aicpp::Neuron<hodel::Grid, hodel::Object const&, hodel::Grid const&>::PointerFunction>(&hodel::subgrid)};
    // Original declaration: line 583
    aicpp::Neuron<hodel::Grid, hodel::Indices const&, hodel::Grid const&> neuron_subgrid_379{
        "subgrid", static_cast<aicpp::Neuron<hodel::Grid, hodel::Indices const&, hodel::Grid const&>::PointerFunction>(&hodel::subgrid)};
    // Original declaration: line 584
    aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::Integer const&> neuron_hsplit_380{
        "hsplit", static_cast<aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::hsplit)};
    // Original declaration: line 585
    aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::Integer const&> neuron_vsplit_381{
        "vsplit", static_cast<aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::vsplit)};
    // Original declaration: line 586
    aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&, hodel::Integer const&> neuron_repeat_382{
        "repeat", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::Boolean const&, hodel::Integer const&>::PointerFunction>(&hodel::repeat)};
    // Original declaration: line 587
    aicpp::Neuron<hodel::IntegerVector, hodel::Integer const&, hodel::Integer const&> neuron_repeat_383{
        "repeat", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::Integer const&, hodel::Integer const&>::PointerFunction>(&hodel::repeat)};
    // Original declaration: line 588
    aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&, hodel::Integer const&> neuron_repeat_384{
        "repeat", static_cast<aicpp::Neuron<hodel::Grid, hodel::IntegerVector const&, hodel::Integer const&>::PointerFunction>(&hodel::repeat)};
    // Original declaration: line 589
    aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::Integer const&> neuron_repeat_385{
        "repeat", static_cast<aicpp::Neuron<hodel::GridVector, hodel::Grid const&, hodel::Integer const&>::PointerFunction>(&hodel::repeat)};
    // Original declaration: line 590
    aicpp::Neuron<hodel::ObjectVector, hodel::Object const&, hodel::Integer const&> neuron_repeat_386{
        "repeat", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::Object const&, hodel::Integer const&>::PointerFunction>(&hodel::repeat)};
    // Original declaration: line 591
    aicpp::Neuron<hodel::ObjectsVector, hodel::Objects const&, hodel::Integer const&> neuron_repeat_387{
        "repeat", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::Objects const&, hodel::Integer const&>::PointerFunction>(&hodel::repeat)};
    // Original declaration: line 592
    aicpp::Neuron<hodel::IndicesVector, hodel::Indices const&, hodel::Integer const&> neuron_repeat_388{
        "repeat", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::Indices const&, hodel::Integer const&>::PointerFunction>(&hodel::repeat)};
    // Original declaration: line 593
    aicpp::Neuron<hodel::GridVector, hodel::GridVector const&> neuron_dedupe_389{
        "dedupe", static_cast<aicpp::Neuron<hodel::GridVector, hodel::GridVector const&>::PointerFunction>(&hodel::dedupe)};
    // Original declaration: line 594
    aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&> neuron_dedupe_390{
        "dedupe", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&>::PointerFunction>(&hodel::dedupe)};
    // Original declaration: line 595
    aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&> neuron_dedupe_391{
        "dedupe", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&>::PointerFunction>(&hodel::dedupe)};
    // Original declaration: line 596
    aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&> neuron_dedupe_392{
        "dedupe", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&>::PointerFunction>(&hodel::dedupe)};
    // Original declaration: line 597
    aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&> neuron_dedupe_393{
        "dedupe", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&>::PointerFunction>(&hodel::dedupe)};
    // Original declaration: line 598
    aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&> neuron_dedupe_394{
        "dedupe", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&>::PointerFunction>(&hodel::dedupe)};
    // Original declaration: line 599
    aicpp::Neuron<hodel::Object, hodel::Objects const&> neuron_merge_395{
        "merge", static_cast<aicpp::Neuron<hodel::Object, hodel::Objects const&>::PointerFunction>(&hodel::merge)};
    // Original declaration: line 600
    aicpp::Neuron<hodel::Object, hodel::ObjectVector const&> neuron_merge_396{
        "merge", static_cast<aicpp::Neuron<hodel::Object, hodel::ObjectVector const&>::PointerFunction>(&hodel::merge)};
    // Original declaration: line 601
    aicpp::Neuron<hodel::Indices, hodel::IndicesSet const&> neuron_merge_397{
        "merge", static_cast<aicpp::Neuron<hodel::Indices, hodel::IndicesSet const&>::PointerFunction>(&hodel::merge)};
    // Original declaration: line 602
    aicpp::Neuron<hodel::Indices, hodel::IndicesVector const&> neuron_merge_398{
        "merge", static_cast<aicpp::Neuron<hodel::Indices, hodel::IndicesVector const&>::PointerFunction>(&hodel::merge)};
    // Original declaration: line 603
    aicpp::Neuron<hodel::IntegerVector, hodel::Grid const&> neuron_merge_399{
        "merge", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::Grid const&>::PointerFunction>(&hodel::merge)};
    // Original declaration: line 604
    aicpp::Neuron<hodel::Grid, hodel::GridVector const&> neuron_merge_400{
        "merge", static_cast<aicpp::Neuron<hodel::Grid, hodel::GridVector const&>::PointerFunction>(&hodel::merge)};
    // Original declaration: line 605
    aicpp::Neuron<hodel::Objects, hodel::ObjectsVector const&> neuron_merge_401{
        "merge", static_cast<aicpp::Neuron<hodel::Objects, hodel::ObjectsVector const&>::PointerFunction>(&hodel::merge)};
    // Original declaration: line 606
    aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::BooleanVector const&> neuron_contained_402{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Boolean const&, hodel::BooleanVector const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 607
    aicpp::Neuron<hodel::Boolean, hodel::Integer const&, hodel::IntegerVector const&> neuron_contained_403{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Integer const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 608
    aicpp::Neuron<hodel::Boolean, hodel::Integer const&, hodel::IntegerSet const&> neuron_contained_404{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Integer const&, hodel::IntegerSet const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 609
    aicpp::Neuron<hodel::Boolean, IntegerTuple const&, hodel::Indices const&> neuron_contained_405{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, IntegerTuple const&, hodel::Indices const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 610
    aicpp::Neuron<hodel::Boolean, hodel::IntegerVector const&, hodel::Grid const&> neuron_contained_406{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::IntegerVector const&, hodel::Grid const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 611
    aicpp::Neuron<hodel::Boolean, hodel::Grid const&, hodel::GridVector const&> neuron_contained_407{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Grid const&, hodel::GridVector const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 612
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Objects const&> neuron_contained_408{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::Objects const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 613
    aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::ObjectVector const&> neuron_contained_409{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Object const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 614
    aicpp::Neuron<hodel::Boolean, hodel::Objects const&, hodel::ObjectsVector const&> neuron_contained_410{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Objects const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 615
    aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::IndicesVector const&> neuron_contained_411{
        "contained", static_cast<aicpp::Neuron<hodel::Boolean, hodel::Indices const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::contained)};
    // Original declaration: line 616
    aicpp::Neuron<hodel::Object, hodel::IntegerSet const&, hodel::Indices const&> neuron_product_412{
        "product", static_cast<aicpp::Neuron<hodel::Object, hodel::IntegerSet const&, hodel::Indices const&>::PointerFunction>(&hodel::product)};
    // Original declaration: line 617
    aicpp::Neuron<hodel::Indices, hodel::IntegerSet const&, hodel::IntegerSet const&> neuron_product_413{
        "product", static_cast<aicpp::Neuron<hodel::Indices, hodel::IntegerSet const&, hodel::IntegerSet const&>::PointerFunction>(&hodel::product)};
    // Original declaration: line 618
    aicpp::Neuron<hodel::FunctionIntegerPairVector, hodel::FunctionSet const&, hodel::IntegerSet const&> neuron_product_414{
        "product", static_cast<aicpp::Neuron<hodel::FunctionIntegerPairVector, hodel::FunctionSet const&, hodel::IntegerSet const&>::PointerFunction>(&hodel::product)};
    // Original declaration: line 619
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Object const&, IntegerTuple const&> neuron_move_415{
        "move", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Object const&, IntegerTuple const&>::PointerFunction>(&hodel::move)};
    // Original declaration: line 620
    aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&, hodel::BooleanVector const&> neuron_intersection_416{
        "intersection", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&, hodel::BooleanVector const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 621
    aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&, hodel::IntegerVector const&> neuron_intersection_417{
        "intersection", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 622
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&> neuron_intersection_418{
        "intersection", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 623
    aicpp::Neuron<hodel::GridVector, hodel::GridVector const&, hodel::GridVector const&> neuron_intersection_419{
        "intersection", static_cast<aicpp::Neuron<hodel::GridVector, hodel::GridVector const&, hodel::GridVector const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 624
    aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&, hodel::ObjectVector const&> neuron_intersection_420{
        "intersection", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 625
    aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&, hodel::ObjectsVector const&> neuron_intersection_421{
        "intersection", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 626
    aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&, hodel::IndicesVector const&> neuron_intersection_422{
        "intersection", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 627
    aicpp::Neuron<hodel::Indices, hodel::Indices const&, hodel::Indices const&> neuron_intersection_423{
        "intersection", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 628
    aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Object const&> neuron_intersection_424{
        "intersection", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 629
    aicpp::Neuron<hodel::Objects, hodel::Objects const&, hodel::Objects const&> neuron_intersection_425{
        "intersection", static_cast<aicpp::Neuron<hodel::Objects, hodel::Objects const&, hodel::Objects const&>::PointerFunction>(&hodel::intersection)};
    // Original declaration: line 630
    aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&, hodel::BooleanVector const&> neuron_difference_426{
        "difference", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&, hodel::BooleanVector const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 631
    aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&, hodel::IntegerVector const&> neuron_difference_427{
        "difference", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 632
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&> neuron_difference_428{
        "difference", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 633
    aicpp::Neuron<hodel::GridVector, hodel::GridVector const&, hodel::GridVector const&> neuron_difference_429{
        "difference", static_cast<aicpp::Neuron<hodel::GridVector, hodel::GridVector const&, hodel::GridVector const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 634
    aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&, hodel::ObjectVector const&> neuron_difference_430{
        "difference", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 635
    aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&, hodel::ObjectsVector const&> neuron_difference_431{
        "difference", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 636
    aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&, hodel::IndicesVector const&> neuron_difference_432{
        "difference", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 637
    aicpp::Neuron<hodel::Indices, hodel::Indices const&, hodel::Indices const&> neuron_difference_433{
        "difference", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 638
    aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Object const&> neuron_difference_434{
        "difference", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 639
    aicpp::Neuron<hodel::Objects, hodel::Objects const&, hodel::Objects const&> neuron_difference_435{
        "difference", static_cast<aicpp::Neuron<hodel::Objects, hodel::Objects const&, hodel::Objects const&>::PointerFunction>(&hodel::difference)};
    // Original declaration: line 640
    aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&, hodel::BooleanVector const&> neuron_combine_436{
        "combine", static_cast<aicpp::Neuron<hodel::BooleanVector, hodel::BooleanVector const&, hodel::BooleanVector const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 641
    aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&, hodel::IntegerVector const&> neuron_combine_437{
        "combine", static_cast<aicpp::Neuron<hodel::IntegerVector, hodel::IntegerVector const&, hodel::IntegerVector const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 642
    aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&> neuron_combine_438{
        "combine", static_cast<aicpp::Neuron<hodel::Grid, hodel::Grid const&, hodel::Grid const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 643
    aicpp::Neuron<hodel::GridVector, hodel::GridVector const&, hodel::GridVector const&> neuron_combine_439{
        "combine", static_cast<aicpp::Neuron<hodel::GridVector, hodel::GridVector const&, hodel::GridVector const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 644
    aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&, hodel::ObjectVector const&> neuron_combine_440{
        "combine", static_cast<aicpp::Neuron<hodel::ObjectVector, hodel::ObjectVector const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 645
    aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&, hodel::ObjectsVector const&> neuron_combine_441{
        "combine", static_cast<aicpp::Neuron<hodel::ObjectsVector, hodel::ObjectsVector const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 646
    aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&, hodel::IndicesVector const&> neuron_combine_442{
        "combine", static_cast<aicpp::Neuron<hodel::IndicesVector, hodel::IndicesVector const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 647
    aicpp::Neuron<hodel::Indices, hodel::Indices const&, hodel::Indices const&> neuron_combine_443{
        "combine", static_cast<aicpp::Neuron<hodel::Indices, hodel::Indices const&, hodel::Indices const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 648
    aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Object const&> neuron_combine_444{
        "combine", static_cast<aicpp::Neuron<hodel::Object, hodel::Object const&, hodel::Object const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 649
    aicpp::Neuron<hodel::Objects, hodel::Objects const&, hodel::Objects const&> neuron_combine_445{
        "combine", static_cast<aicpp::Neuron<hodel::Objects, hodel::Objects const&, hodel::Objects const&>::PointerFunction>(&hodel::combine)};
    // Original declaration: line 650
    aicpp::Neuron<hodel::Grid, aicpp::FunctionValue const&, hodel::GridVector const&> neuron_mapply_446{
        "mapply", static_cast<aicpp::Neuron<hodel::Grid, aicpp::FunctionValue const&, hodel::GridVector const&>::PointerFunction>(&hodel::mapply)};
    // Original declaration: line 651
    aicpp::Neuron<hodel::IntegerVector, aicpp::FunctionValue const&, hodel::Grid const&> neuron_mapply_447{
        "mapply", static_cast<aicpp::Neuron<hodel::IntegerVector, aicpp::FunctionValue const&, hodel::Grid const&>::PointerFunction>(&hodel::mapply)};
    // Original declaration: line 652
    aicpp::Neuron<hodel::Indices, aicpp::FunctionValue const&, hodel::Objects const&> neuron_mapply_448{
        "mapply", static_cast<aicpp::Neuron<hodel::Indices, aicpp::FunctionValue const&, hodel::Objects const&>::PointerFunction>(&hodel::mapply)};
    // Original declaration: line 653
    aicpp::Neuron<hodel::Object, aicpp::FunctionValue const&, hodel::ObjectVector const&> neuron_mapply_449{
        "mapply", static_cast<aicpp::Neuron<hodel::Object, aicpp::FunctionValue const&, hodel::ObjectVector const&>::PointerFunction>(&hodel::mapply)};
    // Original declaration: line 654
    aicpp::Neuron<hodel::Objects, aicpp::FunctionValue const&, hodel::ObjectsVector const&> neuron_mapply_450{
        "mapply", static_cast<aicpp::Neuron<hodel::Objects, aicpp::FunctionValue const&, hodel::ObjectsVector const&>::PointerFunction>(&hodel::mapply)};
    // Original declaration: line 655
    aicpp::Neuron<hodel::Indices, aicpp::FunctionValue const&, hodel::IndicesVector const&> neuron_mapply_451{
        "mapply", static_cast<aicpp::Neuron<hodel::Indices, aicpp::FunctionValue const&, hodel::IndicesVector const&>::PointerFunction>(&hodel::mapply)};
    static FunctionAdapterNeuron adapter_add_28{&neuron_add_28};
    static FunctionAdapterNeuron adapter_add_29{&neuron_add_29};
    static FunctionAdapterNeuron adapter_add_30{&neuron_add_30};
    static FunctionAdapterNeuron adapter_add_31{&neuron_add_31};
    static FunctionAdapterNeuron adapter_subtract_32{&neuron_subtract_32};
    static FunctionAdapterNeuron adapter_subtract_33{&neuron_subtract_33};
    static FunctionAdapterNeuron adapter_subtract_34{&neuron_subtract_34};
    static FunctionAdapterNeuron adapter_subtract_35{&neuron_subtract_35};
    static FunctionAdapterNeuron adapter_multiply_36{&neuron_multiply_36};
    static FunctionAdapterNeuron adapter_multiply_37{&neuron_multiply_37};
    static FunctionAdapterNeuron adapter_multiply_38{&neuron_multiply_38};
    static FunctionAdapterNeuron adapter_multiply_39{&neuron_multiply_39};
    static FunctionAdapterNeuron adapter_divide_40{&neuron_divide_40};
    static FunctionAdapterNeuron adapter_divide_41{&neuron_divide_41};
    static FunctionAdapterNeuron adapter_divide_42{&neuron_divide_42};
    static FunctionAdapterNeuron adapter_invert_43{&neuron_invert_43};
    static FunctionAdapterNeuron adapter_invert_44{&neuron_invert_44};
    static FunctionAdapterNeuron adapter_even_45{&neuron_even_45};
    static FunctionAdapterNeuron adapter_double__46{&neuron_double__46};
    static FunctionAdapterNeuron adapter_double__47{&neuron_double__47};
    static FunctionAdapterNeuron adapter_halve_48{&neuron_halve_48};
    static FunctionAdapterNeuron adapter_halve_49{&neuron_halve_49};
    static FunctionAdapterNeuron adapter_flip_50{&neuron_flip_50};
    static FunctionAdapterNeuron adapter_greater_51{&neuron_greater_51};
    static FunctionAdapterNeuron adapter_maximum_52{&neuron_maximum_52};
    static FunctionAdapterNeuron adapter_maximum_53{&neuron_maximum_53};
    static FunctionAdapterNeuron adapter_minimum_54{&neuron_minimum_54};
    static FunctionAdapterNeuron adapter_minimum_55{&neuron_minimum_55};
    static FunctionAdapterNeuron adapter_both_56{&neuron_both_56};
    static FunctionAdapterNeuron adapter_either_57{&neuron_either_57};
    static FunctionAdapterNeuron adapter_increment_58{&neuron_increment_58};
    static FunctionAdapterNeuron adapter_increment_59{&neuron_increment_59};
    static FunctionAdapterNeuron adapter_decrement_60{&neuron_decrement_60};
    static FunctionAdapterNeuron adapter_decrement_61{&neuron_decrement_61};
    static FunctionAdapterNeuron adapter_crement_62{&neuron_crement_62};
    static FunctionAdapterNeuron adapter_crement_63{&neuron_crement_63};
    static FunctionAdapterNeuron adapter_sign_64{&neuron_sign_64};
    static FunctionAdapterNeuron adapter_sign_65{&neuron_sign_65};
    static FunctionAdapterNeuron adapter_positive_66{&neuron_positive_66};
    static FunctionAdapterNeuron adapter_toivec_67{&neuron_toivec_67};
    static FunctionAdapterNeuron adapter_tojvec_68{&neuron_tojvec_68};
    static FunctionAdapterNeuron adapter_interval_69{&neuron_interval_69};
    static FunctionAdapterNeuron adapter_astuple_70{&neuron_astuple_70};
    static FunctionAdapterNeuron adapter_astuple_71{&neuron_astuple_71};
    static FunctionAdapterNeuron adapter_astuple_72{&neuron_astuple_72};
    static FunctionAdapterNeuron adapter_ulcorner_73{&neuron_ulcorner_73};
    static FunctionAdapterNeuron adapter_ulcorner_74{&neuron_ulcorner_74};
    static FunctionAdapterNeuron adapter_urcorner_75{&neuron_urcorner_75};
    static FunctionAdapterNeuron adapter_urcorner_76{&neuron_urcorner_76};
    static FunctionAdapterNeuron adapter_llcorner_77{&neuron_llcorner_77};
    static FunctionAdapterNeuron adapter_llcorner_78{&neuron_llcorner_78};
    static FunctionAdapterNeuron adapter_lrcorner_79{&neuron_lrcorner_79};
    static FunctionAdapterNeuron adapter_lrcorner_80{&neuron_lrcorner_80};
    static FunctionAdapterNeuron adapter_crop_81{&neuron_crop_81};
    static FunctionAdapterNeuron adapter_toindices_82{&neuron_toindices_82};
    static FunctionAdapterNeuron adapter_shift_83{&neuron_shift_83};
    static FunctionAdapterNeuron adapter_shift_84{&neuron_shift_84};
    static FunctionAdapterNeuron adapter_uppermost_85{&neuron_uppermost_85};
    static FunctionAdapterNeuron adapter_uppermost_86{&neuron_uppermost_86};
    static FunctionAdapterNeuron adapter_lowermost_87{&neuron_lowermost_87};
    static FunctionAdapterNeuron adapter_lowermost_88{&neuron_lowermost_88};
    static FunctionAdapterNeuron adapter_leftmost_89{&neuron_leftmost_89};
    static FunctionAdapterNeuron adapter_leftmost_90{&neuron_leftmost_90};
    static FunctionAdapterNeuron adapter_rightmost_91{&neuron_rightmost_91};
    static FunctionAdapterNeuron adapter_rightmost_92{&neuron_rightmost_92};
    static FunctionAdapterNeuron adapter_rot90_93{&neuron_rot90_93};
    static FunctionAdapterNeuron adapter_rot180_94{&neuron_rot180_94};
    static FunctionAdapterNeuron adapter_rot270_95{&neuron_rot270_95};
    static FunctionAdapterNeuron adapter_hmirror_96{&neuron_hmirror_96};
    static FunctionAdapterNeuron adapter_hmirror_97{&neuron_hmirror_97};
    static FunctionAdapterNeuron adapter_hmirror_98{&neuron_hmirror_98};
    static FunctionAdapterNeuron adapter_vmirror_99{&neuron_vmirror_99};
    static FunctionAdapterNeuron adapter_vmirror_100{&neuron_vmirror_100};
    static FunctionAdapterNeuron adapter_vmirror_101{&neuron_vmirror_101};
    static FunctionAdapterNeuron adapter_dmirror_102{&neuron_dmirror_102};
    static FunctionAdapterNeuron adapter_dmirror_103{&neuron_dmirror_103};
    static FunctionAdapterNeuron adapter_dmirror_104{&neuron_dmirror_104};
    static FunctionAdapterNeuron adapter_cmirror_105{&neuron_cmirror_105};
    static FunctionAdapterNeuron adapter_cmirror_106{&neuron_cmirror_106};
    static FunctionAdapterNeuron adapter_cmirror_107{&neuron_cmirror_107};
    static FunctionAdapterNeuron adapter_hupscale_108{&neuron_hupscale_108};
    static FunctionAdapterNeuron adapter_vupscale_109{&neuron_vupscale_109};
    static FunctionAdapterNeuron adapter_upscale_110{&neuron_upscale_110};
    static FunctionAdapterNeuron adapter_upscale_111{&neuron_upscale_111};
    static FunctionAdapterNeuron adapter_downscale_112{&neuron_downscale_112};
    static FunctionAdapterNeuron adapter_hconcat_113{&neuron_hconcat_113};
    static FunctionAdapterNeuron adapter_vconcat_114{&neuron_vconcat_114};
    static FunctionAdapterNeuron adapter_replace_115{&neuron_replace_115};
    static FunctionAdapterNeuron adapter_switch__116{&neuron_switch__116};
    static FunctionAdapterNeuron adapter_tophalf_117{&neuron_tophalf_117};
    static FunctionAdapterNeuron adapter_bottomhalf_118{&neuron_bottomhalf_118};
    static FunctionAdapterNeuron adapter_lefthalf_119{&neuron_lefthalf_119};
    static FunctionAdapterNeuron adapter_righthalf_120{&neuron_righthalf_120};
    static FunctionAdapterNeuron adapter_trim_121{&neuron_trim_121};
    static FunctionAdapterNeuron adapter_compress_122{&neuron_compress_122};
    static FunctionAdapterNeuron adapter_normalize_123{&neuron_normalize_123};
    static FunctionAdapterNeuron adapter_normalize_124{&neuron_normalize_124};
    static FunctionAdapterNeuron adapter_dneighbors_125{&neuron_dneighbors_125};
    static FunctionAdapterNeuron adapter_ineighbors_126{&neuron_ineighbors_126};
    static FunctionAdapterNeuron adapter_neighbors_127{&neuron_neighbors_127};
    static FunctionAdapterNeuron adapter_recolor_128{&neuron_recolor_128};
    static FunctionAdapterNeuron adapter_recolor_129{&neuron_recolor_129};
    static FunctionAdapterNeuron adapter_square_130{&neuron_square_130};
    static FunctionAdapterNeuron adapter_square_131{&neuron_square_131};
    static FunctionAdapterNeuron adapter_square_132{&neuron_square_132};
    static FunctionAdapterNeuron adapter_vline_133{&neuron_vline_133};
    static FunctionAdapterNeuron adapter_vline_134{&neuron_vline_134};
    static FunctionAdapterNeuron adapter_hline_135{&neuron_hline_135};
    static FunctionAdapterNeuron adapter_hline_136{&neuron_hline_136};
    static FunctionAdapterNeuron adapter_height_137{&neuron_height_137};
    static FunctionAdapterNeuron adapter_height_138{&neuron_height_138};
    static FunctionAdapterNeuron adapter_height_139{&neuron_height_139};
    static FunctionAdapterNeuron adapter_width_140{&neuron_width_140};
    static FunctionAdapterNeuron adapter_width_141{&neuron_width_141};
    static FunctionAdapterNeuron adapter_width_142{&neuron_width_142};
    static FunctionAdapterNeuron adapter_shape_143{&neuron_shape_143};
    static FunctionAdapterNeuron adapter_shape_144{&neuron_shape_144};
    static FunctionAdapterNeuron adapter_shape_145{&neuron_shape_145};
    static FunctionAdapterNeuron adapter_portrait_146{&neuron_portrait_146};
    static FunctionAdapterNeuron adapter_portrait_147{&neuron_portrait_147};
    static FunctionAdapterNeuron adapter_portrait_148{&neuron_portrait_148};
    static FunctionAdapterNeuron adapter_branch_149{&neuron_branch_149};
    static FunctionAdapterNeuron adapter_branch_150{&neuron_branch_150};
    static FunctionAdapterNeuron adapter_branch_151{&neuron_branch_151};
    static FunctionAdapterNeuron adapter_branch_152{&neuron_branch_152};
    static FunctionAdapterNeuron adapter_branch_153{&neuron_branch_153};
    static FunctionAdapterNeuron adapter_branch_154{&neuron_branch_154};
    static FunctionAdapterNeuron adapter_branch_155{&neuron_branch_155};
    static FunctionAdapterNeuron adapter_branch_156{&neuron_branch_156};
    static FunctionAdapterNeuron adapter_branch_157{&neuron_branch_157};
    static FunctionAdapterNeuron adapter_branch_158{&neuron_branch_158};
    static FunctionAdapterNeuron adapter_branch_159{&neuron_branch_159};
    static FunctionAdapterNeuron adapter_branch_160{&neuron_branch_160};
    static FunctionAdapterNeuron adapter_branch_161{&neuron_branch_161};
    static FunctionAdapterNeuron adapter_branch_162{&neuron_branch_162};
    static FunctionAdapterNeuron adapter_branch_163{&neuron_branch_163};
    static FunctionAdapterNeuron adapter_branch_164{&neuron_branch_164};
    static FunctionAdapterNeuron adapter_color_165{&neuron_color_165};
    static FunctionAdapterNeuron adapter_toobject_166{&neuron_toobject_166};
    static FunctionAdapterNeuron adapter_toobject_167{&neuron_toobject_167};
    static FunctionAdapterNeuron adapter_asobject_168{&neuron_asobject_168};
    static FunctionAdapterNeuron adapter_mostcolor_169{&neuron_mostcolor_169};
    static FunctionAdapterNeuron adapter_mostcolor_170{&neuron_mostcolor_170};
    static FunctionAdapterNeuron adapter_leastcolor_171{&neuron_leastcolor_171};
    static FunctionAdapterNeuron adapter_leastcolor_172{&neuron_leastcolor_172};
    static FunctionAdapterNeuron adapter_ofcolor_173{&neuron_ofcolor_173};
    static FunctionAdapterNeuron adapter_colorcount_174{&neuron_colorcount_174};
    static FunctionAdapterNeuron adapter_colorcount_175{&neuron_colorcount_175};
    static FunctionAdapterNeuron adapter_colorfilter_176{&neuron_colorfilter_176};
    static FunctionAdapterNeuron adapter_objects_177{&neuron_objects_177};
    static FunctionAdapterNeuron adapter_partition_178{&neuron_partition_178};
    static FunctionAdapterNeuron adapter_fgpartition_179{&neuron_fgpartition_179};
    static FunctionAdapterNeuron adapter_asindices_180{&neuron_asindices_180};
    static FunctionAdapterNeuron adapter_equality_181{&neuron_equality_181};
    static FunctionAdapterNeuron adapter_equality_182{&neuron_equality_182};
    static FunctionAdapterNeuron adapter_equality_183{&neuron_equality_183};
    static FunctionAdapterNeuron adapter_equality_184{&neuron_equality_184};
    static FunctionAdapterNeuron adapter_equality_185{&neuron_equality_185};
    static FunctionAdapterNeuron adapter_equality_186{&neuron_equality_186};
    static FunctionAdapterNeuron adapter_equality_187{&neuron_equality_187};
    static FunctionAdapterNeuron adapter_equality_188{&neuron_equality_188};
    static FunctionAdapterNeuron adapter_equality_189{&neuron_equality_189};
    static FunctionAdapterNeuron adapter_equality_190{&neuron_equality_190};
    static FunctionAdapterNeuron adapter_equality_191{&neuron_equality_191};
    static FunctionAdapterNeuron adapter_equality_192{&neuron_equality_192};
    static FunctionAdapterNeuron adapter_equality_193{&neuron_equality_193};
    static FunctionAdapterNeuron adapter_equality_194{&neuron_equality_194};
    static FunctionAdapterNeuron adapter_equality_195{&neuron_equality_195};
    static FunctionAdapterNeuron adapter_hmatching_196{&neuron_hmatching_196};
    static FunctionAdapterNeuron adapter_hmatching_197{&neuron_hmatching_197};
    static FunctionAdapterNeuron adapter_hmatching_198{&neuron_hmatching_198};
    static FunctionAdapterNeuron adapter_hmatching_199{&neuron_hmatching_199};
    static FunctionAdapterNeuron adapter_vmatching_200{&neuron_vmatching_200};
    static FunctionAdapterNeuron adapter_vmatching_201{&neuron_vmatching_201};
    static FunctionAdapterNeuron adapter_vmatching_202{&neuron_vmatching_202};
    static FunctionAdapterNeuron adapter_vmatching_203{&neuron_vmatching_203};
    static FunctionAdapterNeuron adapter_manhattan_204{&neuron_manhattan_204};
    static FunctionAdapterNeuron adapter_manhattan_205{&neuron_manhattan_205};
    static FunctionAdapterNeuron adapter_manhattan_206{&neuron_manhattan_206};
    static FunctionAdapterNeuron adapter_manhattan_207{&neuron_manhattan_207};
    static FunctionAdapterNeuron adapter_adjacent_208{&neuron_adjacent_208};
    static FunctionAdapterNeuron adapter_adjacent_209{&neuron_adjacent_209};
    static FunctionAdapterNeuron adapter_adjacent_210{&neuron_adjacent_210};
    static FunctionAdapterNeuron adapter_adjacent_211{&neuron_adjacent_211};
    static FunctionAdapterNeuron adapter_bordering_212{&neuron_bordering_212};
    static FunctionAdapterNeuron adapter_bordering_213{&neuron_bordering_213};
    static FunctionAdapterNeuron adapter_centerofmass_214{&neuron_centerofmass_214};
    static FunctionAdapterNeuron adapter_centerofmass_215{&neuron_centerofmass_215};
    static FunctionAdapterNeuron adapter_palette_216{&neuron_palette_216};
    static FunctionAdapterNeuron adapter_palette_217{&neuron_palette_217};
    static FunctionAdapterNeuron adapter_numcolors_218{&neuron_numcolors_218};
    static FunctionAdapterNeuron adapter_numcolors_219{&neuron_numcolors_219};
    static FunctionAdapterNeuron adapter_fill_220{&neuron_fill_220};
    static FunctionAdapterNeuron adapter_fill_221{&neuron_fill_221};
    static FunctionAdapterNeuron adapter_paint_222{&neuron_paint_222};
    static FunctionAdapterNeuron adapter_underfill_223{&neuron_underfill_223};
    static FunctionAdapterNeuron adapter_underfill_224{&neuron_underfill_224};
    static FunctionAdapterNeuron adapter_underpaint_225{&neuron_underpaint_225};
    static FunctionAdapterNeuron adapter_center_226{&neuron_center_226};
    static FunctionAdapterNeuron adapter_center_227{&neuron_center_227};
    static FunctionAdapterNeuron adapter_position_228{&neuron_position_228};
    static FunctionAdapterNeuron adapter_position_229{&neuron_position_229};
    static FunctionAdapterNeuron adapter_position_230{&neuron_position_230};
    static FunctionAdapterNeuron adapter_position_231{&neuron_position_231};
    static FunctionAdapterNeuron adapter_index_232{&neuron_index_232};
    static FunctionAdapterNeuron adapter_canvas_233{&neuron_canvas_233};
    static FunctionAdapterNeuron adapter_corners_234{&neuron_corners_234};
    static FunctionAdapterNeuron adapter_corners_235{&neuron_corners_235};
    static FunctionAdapterNeuron adapter_connect_236{&neuron_connect_236};
    static FunctionAdapterNeuron adapter_cover_237{&neuron_cover_237};
    static FunctionAdapterNeuron adapter_cover_238{&neuron_cover_238};
    static FunctionAdapterNeuron adapter_vfrontier_239{&neuron_vfrontier_239};
    static FunctionAdapterNeuron adapter_hfrontier_240{&neuron_hfrontier_240};
    static FunctionAdapterNeuron adapter_backdrop_241{&neuron_backdrop_241};
    static FunctionAdapterNeuron adapter_backdrop_242{&neuron_backdrop_242};
    static FunctionAdapterNeuron adapter_delta_243{&neuron_delta_243};
    static FunctionAdapterNeuron adapter_delta_244{&neuron_delta_244};
    static FunctionAdapterNeuron adapter_gravitate_245{&neuron_gravitate_245};
    static FunctionAdapterNeuron adapter_gravitate_246{&neuron_gravitate_246};
    static FunctionAdapterNeuron adapter_gravitate_247{&neuron_gravitate_247};
    static FunctionAdapterNeuron adapter_gravitate_248{&neuron_gravitate_248};
    static FunctionAdapterNeuron adapter_inbox_249{&neuron_inbox_249};
    static FunctionAdapterNeuron adapter_inbox_250{&neuron_inbox_250};
    static FunctionAdapterNeuron adapter_outbox_251{&neuron_outbox_251};
    static FunctionAdapterNeuron adapter_outbox_252{&neuron_outbox_252};
    static FunctionAdapterNeuron adapter_box_253{&neuron_box_253};
    static FunctionAdapterNeuron adapter_box_254{&neuron_box_254};
    static FunctionAdapterNeuron adapter_shoot_255{&neuron_shoot_255};
    static FunctionAdapterNeuron adapter_occurrences_256{&neuron_occurrences_256};
    static FunctionAdapterNeuron adapter_frontiers_257{&neuron_frontiers_257};
    static FunctionAdapterNeuron adapter_hperiod_258{&neuron_hperiod_258};
    static FunctionAdapterNeuron adapter_vperiod_259{&neuron_vperiod_259};
    static FunctionAdapterNeuron adapter_pair_260{&neuron_pair_260};
    static FunctionAdapterNeuron adapter_size_261{&neuron_size_261};
    static FunctionAdapterNeuron adapter_size_262{&neuron_size_262};
    static FunctionAdapterNeuron adapter_size_263{&neuron_size_263};
    static FunctionAdapterNeuron adapter_size_264{&neuron_size_264};
    static FunctionAdapterNeuron adapter_size_265{&neuron_size_265};
    static FunctionAdapterNeuron adapter_size_266{&neuron_size_266};
    static FunctionAdapterNeuron adapter_size_267{&neuron_size_267};
    static FunctionAdapterNeuron adapter_size_268{&neuron_size_268};
    static FunctionAdapterNeuron adapter_size_269{&neuron_size_269};
    static FunctionAdapterNeuron adapter_size_270{&neuron_size_270};
    static FunctionAdapterNeuron adapter_size_271{&neuron_size_271};
    static FunctionAdapterNeuron adapter_size_272{&neuron_size_272};
    static FunctionAdapterNeuron adapter_size_273{&neuron_size_273};
    static FunctionAdapterNeuron adapter_size_274{&neuron_size_274};
    static FunctionAdapterNeuron adapter_size_275{&neuron_size_275};
    static FunctionAdapterNeuron adapter_identity_276{&neuron_identity_276};
    static FunctionAdapterNeuron adapter_identity_277{&neuron_identity_277};
    static FunctionAdapterNeuron adapter_identity_278{&neuron_identity_278};
    static FunctionAdapterNeuron adapter_identity_279{&neuron_identity_279};
    static FunctionAdapterNeuron adapter_identity_280{&neuron_identity_280};
    static FunctionAdapterNeuron adapter_identity_281{&neuron_identity_281};
    static FunctionAdapterNeuron adapter_identity_282{&neuron_identity_282};
    static FunctionAdapterNeuron adapter_identity_283{&neuron_identity_283};
    static FunctionAdapterNeuron adapter_identity_284{&neuron_identity_284};
    static FunctionAdapterNeuron adapter_identity_285{&neuron_identity_285};
    static FunctionAdapterNeuron adapter_identity_286{&neuron_identity_286};
    static FunctionAdapterNeuron adapter_identity_287{&neuron_identity_287};
    static FunctionAdapterNeuron adapter_identity_288{&neuron_identity_288};
    static FunctionAdapterNeuron adapter_identity_289{&neuron_identity_289};
    static FunctionAdapterNeuron adapter_identity_290{&neuron_identity_290};
    static FunctionAdapterNeuron adapter_first_291{&neuron_first_291};
    static FunctionAdapterNeuron adapter_first_292{&neuron_first_292};
    static FunctionAdapterNeuron adapter_first_293{&neuron_first_293};
    static FunctionAdapterNeuron adapter_first_294{&neuron_first_294};
    static FunctionAdapterNeuron adapter_first_295{&neuron_first_295};
    static FunctionAdapterNeuron adapter_first_296{&neuron_first_296};
    static FunctionAdapterNeuron adapter_first_297{&neuron_first_297};
    static FunctionAdapterNeuron adapter_first_298{&neuron_first_298};
    static FunctionAdapterNeuron adapter_first_299{&neuron_first_299};
    static FunctionAdapterNeuron adapter_first_300{&neuron_first_300};
    static FunctionAdapterNeuron adapter_first_301{&neuron_first_301};
    static FunctionAdapterNeuron adapter_first_302{&neuron_first_302};
    static FunctionAdapterNeuron adapter_first_303{&neuron_first_303};
    static FunctionAdapterNeuron adapter_first_304{&neuron_first_304};
    static FunctionAdapterNeuron adapter_first_305{&neuron_first_305};
    static FunctionAdapterNeuron adapter_first_306{&neuron_first_306};
    static FunctionAdapterNeuron adapter_first_307{&neuron_first_307};
    static FunctionAdapterNeuron adapter_last_308{&neuron_last_308};
    static FunctionAdapterNeuron adapter_last_309{&neuron_last_309};
    static FunctionAdapterNeuron adapter_last_310{&neuron_last_310};
    static FunctionAdapterNeuron adapter_last_311{&neuron_last_311};
    static FunctionAdapterNeuron adapter_last_312{&neuron_last_312};
    static FunctionAdapterNeuron adapter_last_313{&neuron_last_313};
    static FunctionAdapterNeuron adapter_last_314{&neuron_last_314};
    static FunctionAdapterNeuron adapter_last_315{&neuron_last_315};
    static FunctionAdapterNeuron adapter_last_316{&neuron_last_316};
    static FunctionAdapterNeuron adapter_last_317{&neuron_last_317};
    static FunctionAdapterNeuron adapter_last_318{&neuron_last_318};
    static FunctionAdapterNeuron adapter_last_319{&neuron_last_319};
    static FunctionAdapterNeuron adapter_last_320{&neuron_last_320};
    static FunctionAdapterNeuron adapter_last_321{&neuron_last_321};
    static FunctionAdapterNeuron adapter_last_322{&neuron_last_322};
    static FunctionAdapterNeuron adapter_last_323{&neuron_last_323};
    static FunctionAdapterNeuron adapter_last_324{&neuron_last_324};
    static FunctionAdapterNeuron adapter_insert_325{&neuron_insert_325};
    static FunctionAdapterNeuron adapter_insert_326{&neuron_insert_326};
    static FunctionAdapterNeuron adapter_insert_327{&neuron_insert_327};
    static FunctionAdapterNeuron adapter_insert_328{&neuron_insert_328};
    static FunctionAdapterNeuron adapter_insert_329{&neuron_insert_329};
    static FunctionAdapterNeuron adapter_insert_330{&neuron_insert_330};
    static FunctionAdapterNeuron adapter_insert_331{&neuron_insert_331};
    static FunctionAdapterNeuron adapter_insert_332{&neuron_insert_332};
    static FunctionAdapterNeuron adapter_insert_333{&neuron_insert_333};
    static FunctionAdapterNeuron adapter_insert_334{&neuron_insert_334};
    static FunctionAdapterNeuron adapter_insert_335{&neuron_insert_335};
    static FunctionAdapterNeuron adapter_insert_336{&neuron_insert_336};
    static FunctionAdapterNeuron adapter_insert_337{&neuron_insert_337};
    static FunctionAdapterNeuron adapter_insert_338{&neuron_insert_338};
    static FunctionAdapterNeuron adapter_remove_339{&neuron_remove_339};
    static FunctionAdapterNeuron adapter_remove_340{&neuron_remove_340};
    static FunctionAdapterNeuron adapter_remove_341{&neuron_remove_341};
    static FunctionAdapterNeuron adapter_remove_342{&neuron_remove_342};
    static FunctionAdapterNeuron adapter_remove_343{&neuron_remove_343};
    static FunctionAdapterNeuron adapter_remove_344{&neuron_remove_344};
    static FunctionAdapterNeuron adapter_remove_345{&neuron_remove_345};
    static FunctionAdapterNeuron adapter_remove_346{&neuron_remove_346};
    static FunctionAdapterNeuron adapter_remove_347{&neuron_remove_347};
    static FunctionAdapterNeuron adapter_remove_348{&neuron_remove_348};
    static FunctionAdapterNeuron adapter_remove_349{&neuron_remove_349};
    static FunctionAdapterNeuron adapter_remove_350{&neuron_remove_350};
    static FunctionAdapterNeuron adapter_other_351{&neuron_other_351};
    static FunctionAdapterNeuron adapter_other_352{&neuron_other_352};
    static FunctionAdapterNeuron adapter_other_353{&neuron_other_353};
    static FunctionAdapterNeuron adapter_other_354{&neuron_other_354};
    static FunctionAdapterNeuron adapter_other_355{&neuron_other_355};
    static FunctionAdapterNeuron adapter_other_356{&neuron_other_356};
    static FunctionAdapterNeuron adapter_other_357{&neuron_other_357};
    static FunctionAdapterNeuron adapter_other_358{&neuron_other_358};
    static FunctionAdapterNeuron adapter_other_359{&neuron_other_359};
    static FunctionAdapterNeuron adapter_other_360{&neuron_other_360};
    static FunctionAdapterNeuron adapter_other_361{&neuron_other_361};
    static FunctionAdapterNeuron adapter_other_362{&neuron_other_362};
    static FunctionAdapterNeuron adapter_initset_363{&neuron_initset_363};
    static FunctionAdapterNeuron adapter_initset_364{&neuron_initset_364};
    static FunctionAdapterNeuron adapter_initset_365{&neuron_initset_365};
    static FunctionAdapterNeuron adapter_initset_366{&neuron_initset_366};
    static FunctionAdapterNeuron adapter_initset_367{&neuron_initset_367};
    static FunctionAdapterNeuron adapter_initset_368{&neuron_initset_368};
    static FunctionAdapterNeuron adapter_initset_369{&neuron_initset_369};
    static FunctionAdapterNeuron adapter_initset_370{&neuron_initset_370};
    static FunctionAdapterNeuron adapter_initset_371{&neuron_initset_371};
    static FunctionAdapterNeuron adapter_initset_372{&neuron_initset_372};
    static FunctionAdapterNeuron adapter_initset_373{&neuron_initset_373};
    static FunctionAdapterNeuron adapter_totuple_374{&neuron_totuple_374};
    static FunctionAdapterNeuron adapter_totuple_375{&neuron_totuple_375};
    static FunctionAdapterNeuron adapter_totuple_376{&neuron_totuple_376};
    static FunctionAdapterNeuron adapter_totuple_377{&neuron_totuple_377};
    static FunctionAdapterNeuron adapter_subgrid_378{&neuron_subgrid_378};
    static FunctionAdapterNeuron adapter_subgrid_379{&neuron_subgrid_379};
    static FunctionAdapterNeuron adapter_hsplit_380{&neuron_hsplit_380};
    static FunctionAdapterNeuron adapter_vsplit_381{&neuron_vsplit_381};
    static FunctionAdapterNeuron adapter_repeat_382{&neuron_repeat_382};
    static FunctionAdapterNeuron adapter_repeat_383{&neuron_repeat_383};
    static FunctionAdapterNeuron adapter_repeat_384{&neuron_repeat_384};
    static FunctionAdapterNeuron adapter_repeat_385{&neuron_repeat_385};
    static FunctionAdapterNeuron adapter_repeat_386{&neuron_repeat_386};
    static FunctionAdapterNeuron adapter_repeat_387{&neuron_repeat_387};
    static FunctionAdapterNeuron adapter_repeat_388{&neuron_repeat_388};
    static FunctionAdapterNeuron adapter_dedupe_389{&neuron_dedupe_389};
    static FunctionAdapterNeuron adapter_dedupe_390{&neuron_dedupe_390};
    static FunctionAdapterNeuron adapter_dedupe_391{&neuron_dedupe_391};
    static FunctionAdapterNeuron adapter_dedupe_392{&neuron_dedupe_392};
    static FunctionAdapterNeuron adapter_dedupe_393{&neuron_dedupe_393};
    static FunctionAdapterNeuron adapter_dedupe_394{&neuron_dedupe_394};
    static FunctionAdapterNeuron adapter_merge_395{&neuron_merge_395};
    static FunctionAdapterNeuron adapter_merge_396{&neuron_merge_396};
    static FunctionAdapterNeuron adapter_merge_397{&neuron_merge_397};
    static FunctionAdapterNeuron adapter_merge_398{&neuron_merge_398};
    static FunctionAdapterNeuron adapter_merge_399{&neuron_merge_399};
    static FunctionAdapterNeuron adapter_merge_400{&neuron_merge_400};
    static FunctionAdapterNeuron adapter_merge_401{&neuron_merge_401};
    static FunctionAdapterNeuron adapter_contained_402{&neuron_contained_402};
    static FunctionAdapterNeuron adapter_contained_403{&neuron_contained_403};
    static FunctionAdapterNeuron adapter_contained_404{&neuron_contained_404};
    static FunctionAdapterNeuron adapter_contained_405{&neuron_contained_405};
    static FunctionAdapterNeuron adapter_contained_406{&neuron_contained_406};
    static FunctionAdapterNeuron adapter_contained_407{&neuron_contained_407};
    static FunctionAdapterNeuron adapter_contained_408{&neuron_contained_408};
    static FunctionAdapterNeuron adapter_contained_409{&neuron_contained_409};
    static FunctionAdapterNeuron adapter_contained_410{&neuron_contained_410};
    static FunctionAdapterNeuron adapter_contained_411{&neuron_contained_411};
    static FunctionAdapterNeuron adapter_product_412{&neuron_product_412};
    static FunctionAdapterNeuron adapter_product_413{&neuron_product_413};
    static FunctionAdapterNeuron adapter_product_414{&neuron_product_414};
    static FunctionAdapterNeuron adapter_move_415{&neuron_move_415};
    static FunctionAdapterNeuron adapter_intersection_416{&neuron_intersection_416};
    static FunctionAdapterNeuron adapter_intersection_417{&neuron_intersection_417};
    static FunctionAdapterNeuron adapter_intersection_418{&neuron_intersection_418};
    static FunctionAdapterNeuron adapter_intersection_419{&neuron_intersection_419};
    static FunctionAdapterNeuron adapter_intersection_420{&neuron_intersection_420};
    static FunctionAdapterNeuron adapter_intersection_421{&neuron_intersection_421};
    static FunctionAdapterNeuron adapter_intersection_422{&neuron_intersection_422};
    static FunctionAdapterNeuron adapter_intersection_423{&neuron_intersection_423};
    static FunctionAdapterNeuron adapter_intersection_424{&neuron_intersection_424};
    static FunctionAdapterNeuron adapter_intersection_425{&neuron_intersection_425};
    static FunctionAdapterNeuron adapter_difference_426{&neuron_difference_426};
    static FunctionAdapterNeuron adapter_difference_427{&neuron_difference_427};
    static FunctionAdapterNeuron adapter_difference_428{&neuron_difference_428};
    static FunctionAdapterNeuron adapter_difference_429{&neuron_difference_429};
    static FunctionAdapterNeuron adapter_difference_430{&neuron_difference_430};
    static FunctionAdapterNeuron adapter_difference_431{&neuron_difference_431};
    static FunctionAdapterNeuron adapter_difference_432{&neuron_difference_432};
    static FunctionAdapterNeuron adapter_difference_433{&neuron_difference_433};
    static FunctionAdapterNeuron adapter_difference_434{&neuron_difference_434};
    static FunctionAdapterNeuron adapter_difference_435{&neuron_difference_435};
    static FunctionAdapterNeuron adapter_combine_436{&neuron_combine_436};
    static FunctionAdapterNeuron adapter_combine_437{&neuron_combine_437};
    static FunctionAdapterNeuron adapter_combine_438{&neuron_combine_438};
    static FunctionAdapterNeuron adapter_combine_439{&neuron_combine_439};
    static FunctionAdapterNeuron adapter_combine_440{&neuron_combine_440};
    static FunctionAdapterNeuron adapter_combine_441{&neuron_combine_441};
    static FunctionAdapterNeuron adapter_combine_442{&neuron_combine_442};
    static FunctionAdapterNeuron adapter_combine_443{&neuron_combine_443};
    static FunctionAdapterNeuron adapter_combine_444{&neuron_combine_444};
    static FunctionAdapterNeuron adapter_combine_445{&neuron_combine_445};
    static FunctionAdapterNeuron adapter_mapply_446{&neuron_mapply_446};
    static FunctionAdapterNeuron adapter_mapply_447{&neuron_mapply_447};
    static FunctionAdapterNeuron adapter_mapply_448{&neuron_mapply_448};
    static FunctionAdapterNeuron adapter_mapply_449{&neuron_mapply_449};
    static FunctionAdapterNeuron adapter_mapply_450{&neuron_mapply_450};
    static FunctionAdapterNeuron adapter_mapply_451{&neuron_mapply_451};

    NeuronRegistry makeNeuronRegistry()
    {
        NeuronRegistry registry;
        registry.emplace("neuron_F_0", &neuron_F_0);
        registry.emplace("neuron_T_1", &neuron_T_1);
        registry.emplace("neuron_ZERO_2", &neuron_ZERO_2);
        registry.emplace("neuron_ONE_3", &neuron_ONE_3);
        registry.emplace("neuron_TWO_4", &neuron_TWO_4);
        registry.emplace("neuron_THREE_5", &neuron_THREE_5);
        registry.emplace("neuron_FOUR_6", &neuron_FOUR_6);
        registry.emplace("neuron_FIVE_7", &neuron_FIVE_7);
        registry.emplace("neuron_SIX_8", &neuron_SIX_8);
        registry.emplace("neuron_SEVEN_9", &neuron_SEVEN_9);
        registry.emplace("neuron_EIGHT_10", &neuron_EIGHT_10);
        registry.emplace("neuron_NINE_11", &neuron_NINE_11);
        registry.emplace("neuron_TEN_12", &neuron_TEN_12);
        registry.emplace("neuron_NEG_ONE_13", &neuron_NEG_ONE_13);
        registry.emplace("neuron_NEG_TWO_14", &neuron_NEG_TWO_14);
        registry.emplace("neuron_DOWN_15", &neuron_DOWN_15);
        registry.emplace("neuron_RIGHT_16", &neuron_RIGHT_16);
        registry.emplace("neuron_UP_17", &neuron_UP_17);
        registry.emplace("neuron_LEFT_18", &neuron_LEFT_18);
        registry.emplace("neuron_ORIGIN_19", &neuron_ORIGIN_19);
        registry.emplace("neuron_UNITY_20", &neuron_UNITY_20);
        registry.emplace("neuron_NEG_UNITY_21", &neuron_NEG_UNITY_21);
        registry.emplace("neuron_UP_RIGHT_22", &neuron_UP_RIGHT_22);
        registry.emplace("neuron_DOWN_LEFT_23", &neuron_DOWN_LEFT_23);
        registry.emplace("neuron_ZERO_BY_TWO_24", &neuron_ZERO_BY_TWO_24);
        registry.emplace("neuron_TWO_BY_ZERO_25", &neuron_TWO_BY_ZERO_25);
        registry.emplace("neuron_TWO_BY_TWO_26", &neuron_TWO_BY_TWO_26);
        registry.emplace("neuron_THREE_BY_THREE_27", &neuron_THREE_BY_THREE_27);
        registry.emplace("neuron_add_28", &neuron_add_28);
        registry.emplace("adapter_add_28", &adapter_add_28);
        registry.emplace("neuron_add_29", &neuron_add_29);
        registry.emplace("adapter_add_29", &adapter_add_29);
        registry.emplace("neuron_add_30", &neuron_add_30);
        registry.emplace("adapter_add_30", &adapter_add_30);
        registry.emplace("neuron_add_31", &neuron_add_31);
        registry.emplace("adapter_add_31", &adapter_add_31);
        registry.emplace("neuron_subtract_32", &neuron_subtract_32);
        registry.emplace("adapter_subtract_32", &adapter_subtract_32);
        registry.emplace("neuron_subtract_33", &neuron_subtract_33);
        registry.emplace("adapter_subtract_33", &adapter_subtract_33);
        registry.emplace("neuron_subtract_34", &neuron_subtract_34);
        registry.emplace("adapter_subtract_34", &adapter_subtract_34);
        registry.emplace("neuron_subtract_35", &neuron_subtract_35);
        registry.emplace("adapter_subtract_35", &adapter_subtract_35);
        registry.emplace("neuron_multiply_36", &neuron_multiply_36);
        registry.emplace("adapter_multiply_36", &adapter_multiply_36);
        registry.emplace("neuron_multiply_37", &neuron_multiply_37);
        registry.emplace("adapter_multiply_37", &adapter_multiply_37);
        registry.emplace("neuron_multiply_38", &neuron_multiply_38);
        registry.emplace("adapter_multiply_38", &adapter_multiply_38);
        registry.emplace("neuron_multiply_39", &neuron_multiply_39);
        registry.emplace("adapter_multiply_39", &adapter_multiply_39);
        registry.emplace("neuron_divide_40", &neuron_divide_40);
        registry.emplace("adapter_divide_40", &adapter_divide_40);
        registry.emplace("neuron_divide_41", &neuron_divide_41);
        registry.emplace("adapter_divide_41", &adapter_divide_41);
        registry.emplace("neuron_divide_42", &neuron_divide_42);
        registry.emplace("adapter_divide_42", &adapter_divide_42);
        registry.emplace("neuron_invert_43", &neuron_invert_43);
        registry.emplace("adapter_invert_43", &adapter_invert_43);
        registry.emplace("neuron_invert_44", &neuron_invert_44);
        registry.emplace("adapter_invert_44", &adapter_invert_44);
        registry.emplace("neuron_even_45", &neuron_even_45);
        registry.emplace("adapter_even_45", &adapter_even_45);
        registry.emplace("neuron_double__46", &neuron_double__46);
        registry.emplace("adapter_double__46", &adapter_double__46);
        registry.emplace("neuron_double__47", &neuron_double__47);
        registry.emplace("adapter_double__47", &adapter_double__47);
        registry.emplace("neuron_halve_48", &neuron_halve_48);
        registry.emplace("adapter_halve_48", &adapter_halve_48);
        registry.emplace("neuron_halve_49", &neuron_halve_49);
        registry.emplace("adapter_halve_49", &adapter_halve_49);
        registry.emplace("neuron_flip_50", &neuron_flip_50);
        registry.emplace("adapter_flip_50", &adapter_flip_50);
        registry.emplace("neuron_greater_51", &neuron_greater_51);
        registry.emplace("adapter_greater_51", &adapter_greater_51);
        registry.emplace("neuron_maximum_52", &neuron_maximum_52);
        registry.emplace("adapter_maximum_52", &adapter_maximum_52);
        registry.emplace("neuron_maximum_53", &neuron_maximum_53);
        registry.emplace("adapter_maximum_53", &adapter_maximum_53);
        registry.emplace("neuron_minimum_54", &neuron_minimum_54);
        registry.emplace("adapter_minimum_54", &adapter_minimum_54);
        registry.emplace("neuron_minimum_55", &neuron_minimum_55);
        registry.emplace("adapter_minimum_55", &adapter_minimum_55);
        registry.emplace("neuron_both_56", &neuron_both_56);
        registry.emplace("adapter_both_56", &adapter_both_56);
        registry.emplace("neuron_either_57", &neuron_either_57);
        registry.emplace("adapter_either_57", &adapter_either_57);
        registry.emplace("neuron_increment_58", &neuron_increment_58);
        registry.emplace("adapter_increment_58", &adapter_increment_58);
        registry.emplace("neuron_increment_59", &neuron_increment_59);
        registry.emplace("adapter_increment_59", &adapter_increment_59);
        registry.emplace("neuron_decrement_60", &neuron_decrement_60);
        registry.emplace("adapter_decrement_60", &adapter_decrement_60);
        registry.emplace("neuron_decrement_61", &neuron_decrement_61);
        registry.emplace("adapter_decrement_61", &adapter_decrement_61);
        registry.emplace("neuron_crement_62", &neuron_crement_62);
        registry.emplace("adapter_crement_62", &adapter_crement_62);
        registry.emplace("neuron_crement_63", &neuron_crement_63);
        registry.emplace("adapter_crement_63", &adapter_crement_63);
        registry.emplace("neuron_sign_64", &neuron_sign_64);
        registry.emplace("adapter_sign_64", &adapter_sign_64);
        registry.emplace("neuron_sign_65", &neuron_sign_65);
        registry.emplace("adapter_sign_65", &adapter_sign_65);
        registry.emplace("neuron_positive_66", &neuron_positive_66);
        registry.emplace("adapter_positive_66", &adapter_positive_66);
        registry.emplace("neuron_toivec_67", &neuron_toivec_67);
        registry.emplace("adapter_toivec_67", &adapter_toivec_67);
        registry.emplace("neuron_tojvec_68", &neuron_tojvec_68);
        registry.emplace("adapter_tojvec_68", &adapter_tojvec_68);
        registry.emplace("neuron_interval_69", &neuron_interval_69);
        registry.emplace("adapter_interval_69", &adapter_interval_69);
        registry.emplace("neuron_astuple_70", &neuron_astuple_70);
        registry.emplace("adapter_astuple_70", &adapter_astuple_70);
        registry.emplace("neuron_astuple_71", &neuron_astuple_71);
        registry.emplace("adapter_astuple_71", &adapter_astuple_71);
        registry.emplace("neuron_astuple_72", &neuron_astuple_72);
        registry.emplace("adapter_astuple_72", &adapter_astuple_72);
        registry.emplace("neuron_ulcorner_73", &neuron_ulcorner_73);
        registry.emplace("adapter_ulcorner_73", &adapter_ulcorner_73);
        registry.emplace("neuron_ulcorner_74", &neuron_ulcorner_74);
        registry.emplace("adapter_ulcorner_74", &adapter_ulcorner_74);
        registry.emplace("neuron_urcorner_75", &neuron_urcorner_75);
        registry.emplace("adapter_urcorner_75", &adapter_urcorner_75);
        registry.emplace("neuron_urcorner_76", &neuron_urcorner_76);
        registry.emplace("adapter_urcorner_76", &adapter_urcorner_76);
        registry.emplace("neuron_llcorner_77", &neuron_llcorner_77);
        registry.emplace("adapter_llcorner_77", &adapter_llcorner_77);
        registry.emplace("neuron_llcorner_78", &neuron_llcorner_78);
        registry.emplace("adapter_llcorner_78", &adapter_llcorner_78);
        registry.emplace("neuron_lrcorner_79", &neuron_lrcorner_79);
        registry.emplace("adapter_lrcorner_79", &adapter_lrcorner_79);
        registry.emplace("neuron_lrcorner_80", &neuron_lrcorner_80);
        registry.emplace("adapter_lrcorner_80", &adapter_lrcorner_80);
        registry.emplace("neuron_crop_81", &neuron_crop_81);
        registry.emplace("adapter_crop_81", &adapter_crop_81);
        registry.emplace("neuron_toindices_82", &neuron_toindices_82);
        registry.emplace("adapter_toindices_82", &adapter_toindices_82);
        registry.emplace("neuron_shift_83", &neuron_shift_83);
        registry.emplace("adapter_shift_83", &adapter_shift_83);
        registry.emplace("neuron_shift_84", &neuron_shift_84);
        registry.emplace("adapter_shift_84", &adapter_shift_84);
        registry.emplace("neuron_uppermost_85", &neuron_uppermost_85);
        registry.emplace("adapter_uppermost_85", &adapter_uppermost_85);
        registry.emplace("neuron_uppermost_86", &neuron_uppermost_86);
        registry.emplace("adapter_uppermost_86", &adapter_uppermost_86);
        registry.emplace("neuron_lowermost_87", &neuron_lowermost_87);
        registry.emplace("adapter_lowermost_87", &adapter_lowermost_87);
        registry.emplace("neuron_lowermost_88", &neuron_lowermost_88);
        registry.emplace("adapter_lowermost_88", &adapter_lowermost_88);
        registry.emplace("neuron_leftmost_89", &neuron_leftmost_89);
        registry.emplace("adapter_leftmost_89", &adapter_leftmost_89);
        registry.emplace("neuron_leftmost_90", &neuron_leftmost_90);
        registry.emplace("adapter_leftmost_90", &adapter_leftmost_90);
        registry.emplace("neuron_rightmost_91", &neuron_rightmost_91);
        registry.emplace("adapter_rightmost_91", &adapter_rightmost_91);
        registry.emplace("neuron_rightmost_92", &neuron_rightmost_92);
        registry.emplace("adapter_rightmost_92", &adapter_rightmost_92);
        registry.emplace("neuron_rot90_93", &neuron_rot90_93);
        registry.emplace("adapter_rot90_93", &adapter_rot90_93);
        registry.emplace("neuron_rot180_94", &neuron_rot180_94);
        registry.emplace("adapter_rot180_94", &adapter_rot180_94);
        registry.emplace("neuron_rot270_95", &neuron_rot270_95);
        registry.emplace("adapter_rot270_95", &adapter_rot270_95);
        registry.emplace("neuron_hmirror_96", &neuron_hmirror_96);
        registry.emplace("adapter_hmirror_96", &adapter_hmirror_96);
        registry.emplace("neuron_hmirror_97", &neuron_hmirror_97);
        registry.emplace("adapter_hmirror_97", &adapter_hmirror_97);
        registry.emplace("neuron_hmirror_98", &neuron_hmirror_98);
        registry.emplace("adapter_hmirror_98", &adapter_hmirror_98);
        registry.emplace("neuron_vmirror_99", &neuron_vmirror_99);
        registry.emplace("adapter_vmirror_99", &adapter_vmirror_99);
        registry.emplace("neuron_vmirror_100", &neuron_vmirror_100);
        registry.emplace("adapter_vmirror_100", &adapter_vmirror_100);
        registry.emplace("neuron_vmirror_101", &neuron_vmirror_101);
        registry.emplace("adapter_vmirror_101", &adapter_vmirror_101);
        registry.emplace("neuron_dmirror_102", &neuron_dmirror_102);
        registry.emplace("adapter_dmirror_102", &adapter_dmirror_102);
        registry.emplace("neuron_dmirror_103", &neuron_dmirror_103);
        registry.emplace("adapter_dmirror_103", &adapter_dmirror_103);
        registry.emplace("neuron_dmirror_104", &neuron_dmirror_104);
        registry.emplace("adapter_dmirror_104", &adapter_dmirror_104);
        registry.emplace("neuron_cmirror_105", &neuron_cmirror_105);
        registry.emplace("adapter_cmirror_105", &adapter_cmirror_105);
        registry.emplace("neuron_cmirror_106", &neuron_cmirror_106);
        registry.emplace("adapter_cmirror_106", &adapter_cmirror_106);
        registry.emplace("neuron_cmirror_107", &neuron_cmirror_107);
        registry.emplace("adapter_cmirror_107", &adapter_cmirror_107);
        registry.emplace("neuron_hupscale_108", &neuron_hupscale_108);
        registry.emplace("adapter_hupscale_108", &adapter_hupscale_108);
        registry.emplace("neuron_vupscale_109", &neuron_vupscale_109);
        registry.emplace("adapter_vupscale_109", &adapter_vupscale_109);
        registry.emplace("neuron_upscale_110", &neuron_upscale_110);
        registry.emplace("adapter_upscale_110", &adapter_upscale_110);
        registry.emplace("neuron_upscale_111", &neuron_upscale_111);
        registry.emplace("adapter_upscale_111", &adapter_upscale_111);
        registry.emplace("neuron_downscale_112", &neuron_downscale_112);
        registry.emplace("adapter_downscale_112", &adapter_downscale_112);
        registry.emplace("neuron_hconcat_113", &neuron_hconcat_113);
        registry.emplace("adapter_hconcat_113", &adapter_hconcat_113);
        registry.emplace("neuron_vconcat_114", &neuron_vconcat_114);
        registry.emplace("adapter_vconcat_114", &adapter_vconcat_114);
        registry.emplace("neuron_replace_115", &neuron_replace_115);
        registry.emplace("adapter_replace_115", &adapter_replace_115);
        registry.emplace("neuron_switch__116", &neuron_switch__116);
        registry.emplace("adapter_switch__116", &adapter_switch__116);
        registry.emplace("neuron_tophalf_117", &neuron_tophalf_117);
        registry.emplace("adapter_tophalf_117", &adapter_tophalf_117);
        registry.emplace("neuron_bottomhalf_118", &neuron_bottomhalf_118);
        registry.emplace("adapter_bottomhalf_118", &adapter_bottomhalf_118);
        registry.emplace("neuron_lefthalf_119", &neuron_lefthalf_119);
        registry.emplace("adapter_lefthalf_119", &adapter_lefthalf_119);
        registry.emplace("neuron_righthalf_120", &neuron_righthalf_120);
        registry.emplace("adapter_righthalf_120", &adapter_righthalf_120);
        registry.emplace("neuron_trim_121", &neuron_trim_121);
        registry.emplace("adapter_trim_121", &adapter_trim_121);
        registry.emplace("neuron_compress_122", &neuron_compress_122);
        registry.emplace("adapter_compress_122", &adapter_compress_122);
        registry.emplace("neuron_normalize_123", &neuron_normalize_123);
        registry.emplace("adapter_normalize_123", &adapter_normalize_123);
        registry.emplace("neuron_normalize_124", &neuron_normalize_124);
        registry.emplace("adapter_normalize_124", &adapter_normalize_124);
        registry.emplace("neuron_dneighbors_125", &neuron_dneighbors_125);
        registry.emplace("adapter_dneighbors_125", &adapter_dneighbors_125);
        registry.emplace("neuron_ineighbors_126", &neuron_ineighbors_126);
        registry.emplace("adapter_ineighbors_126", &adapter_ineighbors_126);
        registry.emplace("neuron_neighbors_127", &neuron_neighbors_127);
        registry.emplace("adapter_neighbors_127", &adapter_neighbors_127);
        registry.emplace("neuron_recolor_128", &neuron_recolor_128);
        registry.emplace("adapter_recolor_128", &adapter_recolor_128);
        registry.emplace("neuron_recolor_129", &neuron_recolor_129);
        registry.emplace("adapter_recolor_129", &adapter_recolor_129);
        registry.emplace("neuron_square_130", &neuron_square_130);
        registry.emplace("adapter_square_130", &adapter_square_130);
        registry.emplace("neuron_square_131", &neuron_square_131);
        registry.emplace("adapter_square_131", &adapter_square_131);
        registry.emplace("neuron_square_132", &neuron_square_132);
        registry.emplace("adapter_square_132", &adapter_square_132);
        registry.emplace("neuron_vline_133", &neuron_vline_133);
        registry.emplace("adapter_vline_133", &adapter_vline_133);
        registry.emplace("neuron_vline_134", &neuron_vline_134);
        registry.emplace("adapter_vline_134", &adapter_vline_134);
        registry.emplace("neuron_hline_135", &neuron_hline_135);
        registry.emplace("adapter_hline_135", &adapter_hline_135);
        registry.emplace("neuron_hline_136", &neuron_hline_136);
        registry.emplace("adapter_hline_136", &adapter_hline_136);
        registry.emplace("neuron_height_137", &neuron_height_137);
        registry.emplace("adapter_height_137", &adapter_height_137);
        registry.emplace("neuron_height_138", &neuron_height_138);
        registry.emplace("adapter_height_138", &adapter_height_138);
        registry.emplace("neuron_height_139", &neuron_height_139);
        registry.emplace("adapter_height_139", &adapter_height_139);
        registry.emplace("neuron_width_140", &neuron_width_140);
        registry.emplace("adapter_width_140", &adapter_width_140);
        registry.emplace("neuron_width_141", &neuron_width_141);
        registry.emplace("adapter_width_141", &adapter_width_141);
        registry.emplace("neuron_width_142", &neuron_width_142);
        registry.emplace("adapter_width_142", &adapter_width_142);
        registry.emplace("neuron_shape_143", &neuron_shape_143);
        registry.emplace("adapter_shape_143", &adapter_shape_143);
        registry.emplace("neuron_shape_144", &neuron_shape_144);
        registry.emplace("adapter_shape_144", &adapter_shape_144);
        registry.emplace("neuron_shape_145", &neuron_shape_145);
        registry.emplace("adapter_shape_145", &adapter_shape_145);
        registry.emplace("neuron_portrait_146", &neuron_portrait_146);
        registry.emplace("adapter_portrait_146", &adapter_portrait_146);
        registry.emplace("neuron_portrait_147", &neuron_portrait_147);
        registry.emplace("adapter_portrait_147", &adapter_portrait_147);
        registry.emplace("neuron_portrait_148", &neuron_portrait_148);
        registry.emplace("adapter_portrait_148", &adapter_portrait_148);
        registry.emplace("neuron_branch_149", &neuron_branch_149);
        registry.emplace("adapter_branch_149", &adapter_branch_149);
        registry.emplace("neuron_branch_150", &neuron_branch_150);
        registry.emplace("adapter_branch_150", &adapter_branch_150);
        registry.emplace("neuron_branch_151", &neuron_branch_151);
        registry.emplace("adapter_branch_151", &adapter_branch_151);
        registry.emplace("neuron_branch_152", &neuron_branch_152);
        registry.emplace("adapter_branch_152", &adapter_branch_152);
        registry.emplace("neuron_branch_153", &neuron_branch_153);
        registry.emplace("adapter_branch_153", &adapter_branch_153);
        registry.emplace("neuron_branch_154", &neuron_branch_154);
        registry.emplace("adapter_branch_154", &adapter_branch_154);
        registry.emplace("neuron_branch_155", &neuron_branch_155);
        registry.emplace("adapter_branch_155", &adapter_branch_155);
        registry.emplace("neuron_branch_156", &neuron_branch_156);
        registry.emplace("adapter_branch_156", &adapter_branch_156);
        registry.emplace("neuron_branch_157", &neuron_branch_157);
        registry.emplace("adapter_branch_157", &adapter_branch_157);
        registry.emplace("neuron_branch_158", &neuron_branch_158);
        registry.emplace("adapter_branch_158", &adapter_branch_158);
        registry.emplace("neuron_branch_159", &neuron_branch_159);
        registry.emplace("adapter_branch_159", &adapter_branch_159);
        registry.emplace("neuron_branch_160", &neuron_branch_160);
        registry.emplace("adapter_branch_160", &adapter_branch_160);
        registry.emplace("neuron_branch_161", &neuron_branch_161);
        registry.emplace("adapter_branch_161", &adapter_branch_161);
        registry.emplace("neuron_branch_162", &neuron_branch_162);
        registry.emplace("adapter_branch_162", &adapter_branch_162);
        registry.emplace("neuron_branch_163", &neuron_branch_163);
        registry.emplace("adapter_branch_163", &adapter_branch_163);
        registry.emplace("neuron_branch_164", &neuron_branch_164);
        registry.emplace("adapter_branch_164", &adapter_branch_164);
        registry.emplace("neuron_color_165", &neuron_color_165);
        registry.emplace("adapter_color_165", &adapter_color_165);
        registry.emplace("neuron_toobject_166", &neuron_toobject_166);
        registry.emplace("adapter_toobject_166", &adapter_toobject_166);
        registry.emplace("neuron_toobject_167", &neuron_toobject_167);
        registry.emplace("adapter_toobject_167", &adapter_toobject_167);
        registry.emplace("neuron_asobject_168", &neuron_asobject_168);
        registry.emplace("adapter_asobject_168", &adapter_asobject_168);
        registry.emplace("neuron_mostcolor_169", &neuron_mostcolor_169);
        registry.emplace("adapter_mostcolor_169", &adapter_mostcolor_169);
        registry.emplace("neuron_mostcolor_170", &neuron_mostcolor_170);
        registry.emplace("adapter_mostcolor_170", &adapter_mostcolor_170);
        registry.emplace("neuron_leastcolor_171", &neuron_leastcolor_171);
        registry.emplace("adapter_leastcolor_171", &adapter_leastcolor_171);
        registry.emplace("neuron_leastcolor_172", &neuron_leastcolor_172);
        registry.emplace("adapter_leastcolor_172", &adapter_leastcolor_172);
        registry.emplace("neuron_ofcolor_173", &neuron_ofcolor_173);
        registry.emplace("adapter_ofcolor_173", &adapter_ofcolor_173);
        registry.emplace("neuron_colorcount_174", &neuron_colorcount_174);
        registry.emplace("adapter_colorcount_174", &adapter_colorcount_174);
        registry.emplace("neuron_colorcount_175", &neuron_colorcount_175);
        registry.emplace("adapter_colorcount_175", &adapter_colorcount_175);
        registry.emplace("neuron_colorfilter_176", &neuron_colorfilter_176);
        registry.emplace("adapter_colorfilter_176", &adapter_colorfilter_176);
        registry.emplace("neuron_objects_177", &neuron_objects_177);
        registry.emplace("adapter_objects_177", &adapter_objects_177);
        registry.emplace("neuron_partition_178", &neuron_partition_178);
        registry.emplace("adapter_partition_178", &adapter_partition_178);
        registry.emplace("neuron_fgpartition_179", &neuron_fgpartition_179);
        registry.emplace("adapter_fgpartition_179", &adapter_fgpartition_179);
        registry.emplace("neuron_asindices_180", &neuron_asindices_180);
        registry.emplace("adapter_asindices_180", &adapter_asindices_180);
        registry.emplace("neuron_equality_181", &neuron_equality_181);
        registry.emplace("adapter_equality_181", &adapter_equality_181);
        registry.emplace("neuron_equality_182", &neuron_equality_182);
        registry.emplace("adapter_equality_182", &adapter_equality_182);
        registry.emplace("neuron_equality_183", &neuron_equality_183);
        registry.emplace("adapter_equality_183", &adapter_equality_183);
        registry.emplace("neuron_equality_184", &neuron_equality_184);
        registry.emplace("adapter_equality_184", &adapter_equality_184);
        registry.emplace("neuron_equality_185", &neuron_equality_185);
        registry.emplace("adapter_equality_185", &adapter_equality_185);
        registry.emplace("neuron_equality_186", &neuron_equality_186);
        registry.emplace("adapter_equality_186", &adapter_equality_186);
        registry.emplace("neuron_equality_187", &neuron_equality_187);
        registry.emplace("adapter_equality_187", &adapter_equality_187);
        registry.emplace("neuron_equality_188", &neuron_equality_188);
        registry.emplace("adapter_equality_188", &adapter_equality_188);
        registry.emplace("neuron_equality_189", &neuron_equality_189);
        registry.emplace("adapter_equality_189", &adapter_equality_189);
        registry.emplace("neuron_equality_190", &neuron_equality_190);
        registry.emplace("adapter_equality_190", &adapter_equality_190);
        registry.emplace("neuron_equality_191", &neuron_equality_191);
        registry.emplace("adapter_equality_191", &adapter_equality_191);
        registry.emplace("neuron_equality_192", &neuron_equality_192);
        registry.emplace("adapter_equality_192", &adapter_equality_192);
        registry.emplace("neuron_equality_193", &neuron_equality_193);
        registry.emplace("adapter_equality_193", &adapter_equality_193);
        registry.emplace("neuron_equality_194", &neuron_equality_194);
        registry.emplace("adapter_equality_194", &adapter_equality_194);
        registry.emplace("neuron_equality_195", &neuron_equality_195);
        registry.emplace("adapter_equality_195", &adapter_equality_195);
        registry.emplace("neuron_hmatching_196", &neuron_hmatching_196);
        registry.emplace("adapter_hmatching_196", &adapter_hmatching_196);
        registry.emplace("neuron_hmatching_197", &neuron_hmatching_197);
        registry.emplace("adapter_hmatching_197", &adapter_hmatching_197);
        registry.emplace("neuron_hmatching_198", &neuron_hmatching_198);
        registry.emplace("adapter_hmatching_198", &adapter_hmatching_198);
        registry.emplace("neuron_hmatching_199", &neuron_hmatching_199);
        registry.emplace("adapter_hmatching_199", &adapter_hmatching_199);
        registry.emplace("neuron_vmatching_200", &neuron_vmatching_200);
        registry.emplace("adapter_vmatching_200", &adapter_vmatching_200);
        registry.emplace("neuron_vmatching_201", &neuron_vmatching_201);
        registry.emplace("adapter_vmatching_201", &adapter_vmatching_201);
        registry.emplace("neuron_vmatching_202", &neuron_vmatching_202);
        registry.emplace("adapter_vmatching_202", &adapter_vmatching_202);
        registry.emplace("neuron_vmatching_203", &neuron_vmatching_203);
        registry.emplace("adapter_vmatching_203", &adapter_vmatching_203);
        registry.emplace("neuron_manhattan_204", &neuron_manhattan_204);
        registry.emplace("adapter_manhattan_204", &adapter_manhattan_204);
        registry.emplace("neuron_manhattan_205", &neuron_manhattan_205);
        registry.emplace("adapter_manhattan_205", &adapter_manhattan_205);
        registry.emplace("neuron_manhattan_206", &neuron_manhattan_206);
        registry.emplace("adapter_manhattan_206", &adapter_manhattan_206);
        registry.emplace("neuron_manhattan_207", &neuron_manhattan_207);
        registry.emplace("adapter_manhattan_207", &adapter_manhattan_207);
        registry.emplace("neuron_adjacent_208", &neuron_adjacent_208);
        registry.emplace("adapter_adjacent_208", &adapter_adjacent_208);
        registry.emplace("neuron_adjacent_209", &neuron_adjacent_209);
        registry.emplace("adapter_adjacent_209", &adapter_adjacent_209);
        registry.emplace("neuron_adjacent_210", &neuron_adjacent_210);
        registry.emplace("adapter_adjacent_210", &adapter_adjacent_210);
        registry.emplace("neuron_adjacent_211", &neuron_adjacent_211);
        registry.emplace("adapter_adjacent_211", &adapter_adjacent_211);
        registry.emplace("neuron_bordering_212", &neuron_bordering_212);
        registry.emplace("adapter_bordering_212", &adapter_bordering_212);
        registry.emplace("neuron_bordering_213", &neuron_bordering_213);
        registry.emplace("adapter_bordering_213", &adapter_bordering_213);
        registry.emplace("neuron_centerofmass_214", &neuron_centerofmass_214);
        registry.emplace("adapter_centerofmass_214", &adapter_centerofmass_214);
        registry.emplace("neuron_centerofmass_215", &neuron_centerofmass_215);
        registry.emplace("adapter_centerofmass_215", &adapter_centerofmass_215);
        registry.emplace("neuron_palette_216", &neuron_palette_216);
        registry.emplace("adapter_palette_216", &adapter_palette_216);
        registry.emplace("neuron_palette_217", &neuron_palette_217);
        registry.emplace("adapter_palette_217", &adapter_palette_217);
        registry.emplace("neuron_numcolors_218", &neuron_numcolors_218);
        registry.emplace("adapter_numcolors_218", &adapter_numcolors_218);
        registry.emplace("neuron_numcolors_219", &neuron_numcolors_219);
        registry.emplace("adapter_numcolors_219", &adapter_numcolors_219);
        registry.emplace("neuron_fill_220", &neuron_fill_220);
        registry.emplace("adapter_fill_220", &adapter_fill_220);
        registry.emplace("neuron_fill_221", &neuron_fill_221);
        registry.emplace("adapter_fill_221", &adapter_fill_221);
        registry.emplace("neuron_paint_222", &neuron_paint_222);
        registry.emplace("adapter_paint_222", &adapter_paint_222);
        registry.emplace("neuron_underfill_223", &neuron_underfill_223);
        registry.emplace("adapter_underfill_223", &adapter_underfill_223);
        registry.emplace("neuron_underfill_224", &neuron_underfill_224);
        registry.emplace("adapter_underfill_224", &adapter_underfill_224);
        registry.emplace("neuron_underpaint_225", &neuron_underpaint_225);
        registry.emplace("adapter_underpaint_225", &adapter_underpaint_225);
        registry.emplace("neuron_center_226", &neuron_center_226);
        registry.emplace("adapter_center_226", &adapter_center_226);
        registry.emplace("neuron_center_227", &neuron_center_227);
        registry.emplace("adapter_center_227", &adapter_center_227);
        registry.emplace("neuron_position_228", &neuron_position_228);
        registry.emplace("adapter_position_228", &adapter_position_228);
        registry.emplace("neuron_position_229", &neuron_position_229);
        registry.emplace("adapter_position_229", &adapter_position_229);
        registry.emplace("neuron_position_230", &neuron_position_230);
        registry.emplace("adapter_position_230", &adapter_position_230);
        registry.emplace("neuron_position_231", &neuron_position_231);
        registry.emplace("adapter_position_231", &adapter_position_231);
        registry.emplace("neuron_index_232", &neuron_index_232);
        registry.emplace("adapter_index_232", &adapter_index_232);
        registry.emplace("neuron_canvas_233", &neuron_canvas_233);
        registry.emplace("adapter_canvas_233", &adapter_canvas_233);
        registry.emplace("neuron_corners_234", &neuron_corners_234);
        registry.emplace("adapter_corners_234", &adapter_corners_234);
        registry.emplace("neuron_corners_235", &neuron_corners_235);
        registry.emplace("adapter_corners_235", &adapter_corners_235);
        registry.emplace("neuron_connect_236", &neuron_connect_236);
        registry.emplace("adapter_connect_236", &adapter_connect_236);
        registry.emplace("neuron_cover_237", &neuron_cover_237);
        registry.emplace("adapter_cover_237", &adapter_cover_237);
        registry.emplace("neuron_cover_238", &neuron_cover_238);
        registry.emplace("adapter_cover_238", &adapter_cover_238);
        registry.emplace("neuron_vfrontier_239", &neuron_vfrontier_239);
        registry.emplace("adapter_vfrontier_239", &adapter_vfrontier_239);
        registry.emplace("neuron_hfrontier_240", &neuron_hfrontier_240);
        registry.emplace("adapter_hfrontier_240", &adapter_hfrontier_240);
        registry.emplace("neuron_backdrop_241", &neuron_backdrop_241);
        registry.emplace("adapter_backdrop_241", &adapter_backdrop_241);
        registry.emplace("neuron_backdrop_242", &neuron_backdrop_242);
        registry.emplace("adapter_backdrop_242", &adapter_backdrop_242);
        registry.emplace("neuron_delta_243", &neuron_delta_243);
        registry.emplace("adapter_delta_243", &adapter_delta_243);
        registry.emplace("neuron_delta_244", &neuron_delta_244);
        registry.emplace("adapter_delta_244", &adapter_delta_244);
        registry.emplace("neuron_gravitate_245", &neuron_gravitate_245);
        registry.emplace("adapter_gravitate_245", &adapter_gravitate_245);
        registry.emplace("neuron_gravitate_246", &neuron_gravitate_246);
        registry.emplace("adapter_gravitate_246", &adapter_gravitate_246);
        registry.emplace("neuron_gravitate_247", &neuron_gravitate_247);
        registry.emplace("adapter_gravitate_247", &adapter_gravitate_247);
        registry.emplace("neuron_gravitate_248", &neuron_gravitate_248);
        registry.emplace("adapter_gravitate_248", &adapter_gravitate_248);
        registry.emplace("neuron_inbox_249", &neuron_inbox_249);
        registry.emplace("adapter_inbox_249", &adapter_inbox_249);
        registry.emplace("neuron_inbox_250", &neuron_inbox_250);
        registry.emplace("adapter_inbox_250", &adapter_inbox_250);
        registry.emplace("neuron_outbox_251", &neuron_outbox_251);
        registry.emplace("adapter_outbox_251", &adapter_outbox_251);
        registry.emplace("neuron_outbox_252", &neuron_outbox_252);
        registry.emplace("adapter_outbox_252", &adapter_outbox_252);
        registry.emplace("neuron_box_253", &neuron_box_253);
        registry.emplace("adapter_box_253", &adapter_box_253);
        registry.emplace("neuron_box_254", &neuron_box_254);
        registry.emplace("adapter_box_254", &adapter_box_254);
        registry.emplace("neuron_shoot_255", &neuron_shoot_255);
        registry.emplace("adapter_shoot_255", &adapter_shoot_255);
        registry.emplace("neuron_occurrences_256", &neuron_occurrences_256);
        registry.emplace("adapter_occurrences_256", &adapter_occurrences_256);
        registry.emplace("neuron_frontiers_257", &neuron_frontiers_257);
        registry.emplace("adapter_frontiers_257", &adapter_frontiers_257);
        registry.emplace("neuron_hperiod_258", &neuron_hperiod_258);
        registry.emplace("adapter_hperiod_258", &adapter_hperiod_258);
        registry.emplace("neuron_vperiod_259", &neuron_vperiod_259);
        registry.emplace("adapter_vperiod_259", &adapter_vperiod_259);
        registry.emplace("neuron_pair_260", &neuron_pair_260);
        registry.emplace("adapter_pair_260", &adapter_pair_260);
        registry.emplace("neuron_size_261", &neuron_size_261);
        registry.emplace("adapter_size_261", &adapter_size_261);
        registry.emplace("neuron_size_262", &neuron_size_262);
        registry.emplace("adapter_size_262", &adapter_size_262);
        registry.emplace("neuron_size_263", &neuron_size_263);
        registry.emplace("adapter_size_263", &adapter_size_263);
        registry.emplace("neuron_size_264", &neuron_size_264);
        registry.emplace("adapter_size_264", &adapter_size_264);
        registry.emplace("neuron_size_265", &neuron_size_265);
        registry.emplace("adapter_size_265", &adapter_size_265);
        registry.emplace("neuron_size_266", &neuron_size_266);
        registry.emplace("adapter_size_266", &adapter_size_266);
        registry.emplace("neuron_size_267", &neuron_size_267);
        registry.emplace("adapter_size_267", &adapter_size_267);
        registry.emplace("neuron_size_268", &neuron_size_268);
        registry.emplace("adapter_size_268", &adapter_size_268);
        registry.emplace("neuron_size_269", &neuron_size_269);
        registry.emplace("adapter_size_269", &adapter_size_269);
        registry.emplace("neuron_size_270", &neuron_size_270);
        registry.emplace("adapter_size_270", &adapter_size_270);
        registry.emplace("neuron_size_271", &neuron_size_271);
        registry.emplace("adapter_size_271", &adapter_size_271);
        registry.emplace("neuron_size_272", &neuron_size_272);
        registry.emplace("adapter_size_272", &adapter_size_272);
        registry.emplace("neuron_size_273", &neuron_size_273);
        registry.emplace("adapter_size_273", &adapter_size_273);
        registry.emplace("neuron_size_274", &neuron_size_274);
        registry.emplace("adapter_size_274", &adapter_size_274);
        registry.emplace("neuron_size_275", &neuron_size_275);
        registry.emplace("adapter_size_275", &adapter_size_275);
        registry.emplace("neuron_identity_276", &neuron_identity_276);
        registry.emplace("adapter_identity_276", &adapter_identity_276);
        registry.emplace("neuron_identity_277", &neuron_identity_277);
        registry.emplace("adapter_identity_277", &adapter_identity_277);
        registry.emplace("neuron_identity_278", &neuron_identity_278);
        registry.emplace("adapter_identity_278", &adapter_identity_278);
        registry.emplace("neuron_identity_279", &neuron_identity_279);
        registry.emplace("adapter_identity_279", &adapter_identity_279);
        registry.emplace("neuron_identity_280", &neuron_identity_280);
        registry.emplace("adapter_identity_280", &adapter_identity_280);
        registry.emplace("neuron_identity_281", &neuron_identity_281);
        registry.emplace("adapter_identity_281", &adapter_identity_281);
        registry.emplace("neuron_identity_282", &neuron_identity_282);
        registry.emplace("adapter_identity_282", &adapter_identity_282);
        registry.emplace("neuron_identity_283", &neuron_identity_283);
        registry.emplace("adapter_identity_283", &adapter_identity_283);
        registry.emplace("neuron_identity_284", &neuron_identity_284);
        registry.emplace("adapter_identity_284", &adapter_identity_284);
        registry.emplace("neuron_identity_285", &neuron_identity_285);
        registry.emplace("adapter_identity_285", &adapter_identity_285);
        registry.emplace("neuron_identity_286", &neuron_identity_286);
        registry.emplace("adapter_identity_286", &adapter_identity_286);
        registry.emplace("neuron_identity_287", &neuron_identity_287);
        registry.emplace("adapter_identity_287", &adapter_identity_287);
        registry.emplace("neuron_identity_288", &neuron_identity_288);
        registry.emplace("adapter_identity_288", &adapter_identity_288);
        registry.emplace("neuron_identity_289", &neuron_identity_289);
        registry.emplace("adapter_identity_289", &adapter_identity_289);
        registry.emplace("neuron_identity_290", &neuron_identity_290);
        registry.emplace("adapter_identity_290", &adapter_identity_290);
        registry.emplace("neuron_first_291", &neuron_first_291);
        registry.emplace("adapter_first_291", &adapter_first_291);
        registry.emplace("neuron_first_292", &neuron_first_292);
        registry.emplace("adapter_first_292", &adapter_first_292);
        registry.emplace("neuron_first_293", &neuron_first_293);
        registry.emplace("adapter_first_293", &adapter_first_293);
        registry.emplace("neuron_first_294", &neuron_first_294);
        registry.emplace("adapter_first_294", &adapter_first_294);
        registry.emplace("neuron_first_295", &neuron_first_295);
        registry.emplace("adapter_first_295", &adapter_first_295);
        registry.emplace("neuron_first_296", &neuron_first_296);
        registry.emplace("adapter_first_296", &adapter_first_296);
        registry.emplace("neuron_first_297", &neuron_first_297);
        registry.emplace("adapter_first_297", &adapter_first_297);
        registry.emplace("neuron_first_298", &neuron_first_298);
        registry.emplace("adapter_first_298", &adapter_first_298);
        registry.emplace("neuron_first_299", &neuron_first_299);
        registry.emplace("adapter_first_299", &adapter_first_299);
        registry.emplace("neuron_first_300", &neuron_first_300);
        registry.emplace("adapter_first_300", &adapter_first_300);
        registry.emplace("neuron_first_301", &neuron_first_301);
        registry.emplace("adapter_first_301", &adapter_first_301);
        registry.emplace("neuron_first_302", &neuron_first_302);
        registry.emplace("adapter_first_302", &adapter_first_302);
        registry.emplace("neuron_first_303", &neuron_first_303);
        registry.emplace("adapter_first_303", &adapter_first_303);
        registry.emplace("neuron_first_304", &neuron_first_304);
        registry.emplace("adapter_first_304", &adapter_first_304);
        registry.emplace("neuron_first_305", &neuron_first_305);
        registry.emplace("adapter_first_305", &adapter_first_305);
        registry.emplace("neuron_first_306", &neuron_first_306);
        registry.emplace("adapter_first_306", &adapter_first_306);
        registry.emplace("neuron_first_307", &neuron_first_307);
        registry.emplace("adapter_first_307", &adapter_first_307);
        registry.emplace("neuron_last_308", &neuron_last_308);
        registry.emplace("adapter_last_308", &adapter_last_308);
        registry.emplace("neuron_last_309", &neuron_last_309);
        registry.emplace("adapter_last_309", &adapter_last_309);
        registry.emplace("neuron_last_310", &neuron_last_310);
        registry.emplace("adapter_last_310", &adapter_last_310);
        registry.emplace("neuron_last_311", &neuron_last_311);
        registry.emplace("adapter_last_311", &adapter_last_311);
        registry.emplace("neuron_last_312", &neuron_last_312);
        registry.emplace("adapter_last_312", &adapter_last_312);
        registry.emplace("neuron_last_313", &neuron_last_313);
        registry.emplace("adapter_last_313", &adapter_last_313);
        registry.emplace("neuron_last_314", &neuron_last_314);
        registry.emplace("adapter_last_314", &adapter_last_314);
        registry.emplace("neuron_last_315", &neuron_last_315);
        registry.emplace("adapter_last_315", &adapter_last_315);
        registry.emplace("neuron_last_316", &neuron_last_316);
        registry.emplace("adapter_last_316", &adapter_last_316);
        registry.emplace("neuron_last_317", &neuron_last_317);
        registry.emplace("adapter_last_317", &adapter_last_317);
        registry.emplace("neuron_last_318", &neuron_last_318);
        registry.emplace("adapter_last_318", &adapter_last_318);
        registry.emplace("neuron_last_319", &neuron_last_319);
        registry.emplace("adapter_last_319", &adapter_last_319);
        registry.emplace("neuron_last_320", &neuron_last_320);
        registry.emplace("adapter_last_320", &adapter_last_320);
        registry.emplace("neuron_last_321", &neuron_last_321);
        registry.emplace("adapter_last_321", &adapter_last_321);
        registry.emplace("neuron_last_322", &neuron_last_322);
        registry.emplace("adapter_last_322", &adapter_last_322);
        registry.emplace("neuron_last_323", &neuron_last_323);
        registry.emplace("adapter_last_323", &adapter_last_323);
        registry.emplace("neuron_last_324", &neuron_last_324);
        registry.emplace("adapter_last_324", &adapter_last_324);
        registry.emplace("neuron_insert_325", &neuron_insert_325);
        registry.emplace("adapter_insert_325", &adapter_insert_325);
        registry.emplace("neuron_insert_326", &neuron_insert_326);
        registry.emplace("adapter_insert_326", &adapter_insert_326);
        registry.emplace("neuron_insert_327", &neuron_insert_327);
        registry.emplace("adapter_insert_327", &adapter_insert_327);
        registry.emplace("neuron_insert_328", &neuron_insert_328);
        registry.emplace("adapter_insert_328", &adapter_insert_328);
        registry.emplace("neuron_insert_329", &neuron_insert_329);
        registry.emplace("adapter_insert_329", &adapter_insert_329);
        registry.emplace("neuron_insert_330", &neuron_insert_330);
        registry.emplace("adapter_insert_330", &adapter_insert_330);
        registry.emplace("neuron_insert_331", &neuron_insert_331);
        registry.emplace("adapter_insert_331", &adapter_insert_331);
        registry.emplace("neuron_insert_332", &neuron_insert_332);
        registry.emplace("adapter_insert_332", &adapter_insert_332);
        registry.emplace("neuron_insert_333", &neuron_insert_333);
        registry.emplace("adapter_insert_333", &adapter_insert_333);
        registry.emplace("neuron_insert_334", &neuron_insert_334);
        registry.emplace("adapter_insert_334", &adapter_insert_334);
        registry.emplace("neuron_insert_335", &neuron_insert_335);
        registry.emplace("adapter_insert_335", &adapter_insert_335);
        registry.emplace("neuron_insert_336", &neuron_insert_336);
        registry.emplace("adapter_insert_336", &adapter_insert_336);
        registry.emplace("neuron_insert_337", &neuron_insert_337);
        registry.emplace("adapter_insert_337", &adapter_insert_337);
        registry.emplace("neuron_insert_338", &neuron_insert_338);
        registry.emplace("adapter_insert_338", &adapter_insert_338);
        registry.emplace("neuron_remove_339", &neuron_remove_339);
        registry.emplace("adapter_remove_339", &adapter_remove_339);
        registry.emplace("neuron_remove_340", &neuron_remove_340);
        registry.emplace("adapter_remove_340", &adapter_remove_340);
        registry.emplace("neuron_remove_341", &neuron_remove_341);
        registry.emplace("adapter_remove_341", &adapter_remove_341);
        registry.emplace("neuron_remove_342", &neuron_remove_342);
        registry.emplace("adapter_remove_342", &adapter_remove_342);
        registry.emplace("neuron_remove_343", &neuron_remove_343);
        registry.emplace("adapter_remove_343", &adapter_remove_343);
        registry.emplace("neuron_remove_344", &neuron_remove_344);
        registry.emplace("adapter_remove_344", &adapter_remove_344);
        registry.emplace("neuron_remove_345", &neuron_remove_345);
        registry.emplace("adapter_remove_345", &adapter_remove_345);
        registry.emplace("neuron_remove_346", &neuron_remove_346);
        registry.emplace("adapter_remove_346", &adapter_remove_346);
        registry.emplace("neuron_remove_347", &neuron_remove_347);
        registry.emplace("adapter_remove_347", &adapter_remove_347);
        registry.emplace("neuron_remove_348", &neuron_remove_348);
        registry.emplace("adapter_remove_348", &adapter_remove_348);
        registry.emplace("neuron_remove_349", &neuron_remove_349);
        registry.emplace("adapter_remove_349", &adapter_remove_349);
        registry.emplace("neuron_remove_350", &neuron_remove_350);
        registry.emplace("adapter_remove_350", &adapter_remove_350);
        registry.emplace("neuron_other_351", &neuron_other_351);
        registry.emplace("adapter_other_351", &adapter_other_351);
        registry.emplace("neuron_other_352", &neuron_other_352);
        registry.emplace("adapter_other_352", &adapter_other_352);
        registry.emplace("neuron_other_353", &neuron_other_353);
        registry.emplace("adapter_other_353", &adapter_other_353);
        registry.emplace("neuron_other_354", &neuron_other_354);
        registry.emplace("adapter_other_354", &adapter_other_354);
        registry.emplace("neuron_other_355", &neuron_other_355);
        registry.emplace("adapter_other_355", &adapter_other_355);
        registry.emplace("neuron_other_356", &neuron_other_356);
        registry.emplace("adapter_other_356", &adapter_other_356);
        registry.emplace("neuron_other_357", &neuron_other_357);
        registry.emplace("adapter_other_357", &adapter_other_357);
        registry.emplace("neuron_other_358", &neuron_other_358);
        registry.emplace("adapter_other_358", &adapter_other_358);
        registry.emplace("neuron_other_359", &neuron_other_359);
        registry.emplace("adapter_other_359", &adapter_other_359);
        registry.emplace("neuron_other_360", &neuron_other_360);
        registry.emplace("adapter_other_360", &adapter_other_360);
        registry.emplace("neuron_other_361", &neuron_other_361);
        registry.emplace("adapter_other_361", &adapter_other_361);
        registry.emplace("neuron_other_362", &neuron_other_362);
        registry.emplace("adapter_other_362", &adapter_other_362);
        registry.emplace("neuron_initset_363", &neuron_initset_363);
        registry.emplace("adapter_initset_363", &adapter_initset_363);
        registry.emplace("neuron_initset_364", &neuron_initset_364);
        registry.emplace("adapter_initset_364", &adapter_initset_364);
        registry.emplace("neuron_initset_365", &neuron_initset_365);
        registry.emplace("adapter_initset_365", &adapter_initset_365);
        registry.emplace("neuron_initset_366", &neuron_initset_366);
        registry.emplace("adapter_initset_366", &adapter_initset_366);
        registry.emplace("neuron_initset_367", &neuron_initset_367);
        registry.emplace("adapter_initset_367", &adapter_initset_367);
        registry.emplace("neuron_initset_368", &neuron_initset_368);
        registry.emplace("adapter_initset_368", &adapter_initset_368);
        registry.emplace("neuron_initset_369", &neuron_initset_369);
        registry.emplace("adapter_initset_369", &adapter_initset_369);
        registry.emplace("neuron_initset_370", &neuron_initset_370);
        registry.emplace("adapter_initset_370", &adapter_initset_370);
        registry.emplace("neuron_initset_371", &neuron_initset_371);
        registry.emplace("adapter_initset_371", &adapter_initset_371);
        registry.emplace("neuron_initset_372", &neuron_initset_372);
        registry.emplace("adapter_initset_372", &adapter_initset_372);
        registry.emplace("neuron_initset_373", &neuron_initset_373);
        registry.emplace("adapter_initset_373", &adapter_initset_373);
        registry.emplace("neuron_totuple_374", &neuron_totuple_374);
        registry.emplace("adapter_totuple_374", &adapter_totuple_374);
        registry.emplace("neuron_totuple_375", &neuron_totuple_375);
        registry.emplace("adapter_totuple_375", &adapter_totuple_375);
        registry.emplace("neuron_totuple_376", &neuron_totuple_376);
        registry.emplace("adapter_totuple_376", &adapter_totuple_376);
        registry.emplace("neuron_totuple_377", &neuron_totuple_377);
        registry.emplace("adapter_totuple_377", &adapter_totuple_377);
        registry.emplace("neuron_subgrid_378", &neuron_subgrid_378);
        registry.emplace("adapter_subgrid_378", &adapter_subgrid_378);
        registry.emplace("neuron_subgrid_379", &neuron_subgrid_379);
        registry.emplace("adapter_subgrid_379", &adapter_subgrid_379);
        registry.emplace("neuron_hsplit_380", &neuron_hsplit_380);
        registry.emplace("adapter_hsplit_380", &adapter_hsplit_380);
        registry.emplace("neuron_vsplit_381", &neuron_vsplit_381);
        registry.emplace("adapter_vsplit_381", &adapter_vsplit_381);
        registry.emplace("neuron_repeat_382", &neuron_repeat_382);
        registry.emplace("adapter_repeat_382", &adapter_repeat_382);
        registry.emplace("neuron_repeat_383", &neuron_repeat_383);
        registry.emplace("adapter_repeat_383", &adapter_repeat_383);
        registry.emplace("neuron_repeat_384", &neuron_repeat_384);
        registry.emplace("adapter_repeat_384", &adapter_repeat_384);
        registry.emplace("neuron_repeat_385", &neuron_repeat_385);
        registry.emplace("adapter_repeat_385", &adapter_repeat_385);
        registry.emplace("neuron_repeat_386", &neuron_repeat_386);
        registry.emplace("adapter_repeat_386", &adapter_repeat_386);
        registry.emplace("neuron_repeat_387", &neuron_repeat_387);
        registry.emplace("adapter_repeat_387", &adapter_repeat_387);
        registry.emplace("neuron_repeat_388", &neuron_repeat_388);
        registry.emplace("adapter_repeat_388", &adapter_repeat_388);
        registry.emplace("neuron_dedupe_389", &neuron_dedupe_389);
        registry.emplace("adapter_dedupe_389", &adapter_dedupe_389);
        registry.emplace("neuron_dedupe_390", &neuron_dedupe_390);
        registry.emplace("adapter_dedupe_390", &adapter_dedupe_390);
        registry.emplace("neuron_dedupe_391", &neuron_dedupe_391);
        registry.emplace("adapter_dedupe_391", &adapter_dedupe_391);
        registry.emplace("neuron_dedupe_392", &neuron_dedupe_392);
        registry.emplace("adapter_dedupe_392", &adapter_dedupe_392);
        registry.emplace("neuron_dedupe_393", &neuron_dedupe_393);
        registry.emplace("adapter_dedupe_393", &adapter_dedupe_393);
        registry.emplace("neuron_dedupe_394", &neuron_dedupe_394);
        registry.emplace("adapter_dedupe_394", &adapter_dedupe_394);
        registry.emplace("neuron_merge_395", &neuron_merge_395);
        registry.emplace("adapter_merge_395", &adapter_merge_395);
        registry.emplace("neuron_merge_396", &neuron_merge_396);
        registry.emplace("adapter_merge_396", &adapter_merge_396);
        registry.emplace("neuron_merge_397", &neuron_merge_397);
        registry.emplace("adapter_merge_397", &adapter_merge_397);
        registry.emplace("neuron_merge_398", &neuron_merge_398);
        registry.emplace("adapter_merge_398", &adapter_merge_398);
        registry.emplace("neuron_merge_399", &neuron_merge_399);
        registry.emplace("adapter_merge_399", &adapter_merge_399);
        registry.emplace("neuron_merge_400", &neuron_merge_400);
        registry.emplace("adapter_merge_400", &adapter_merge_400);
        registry.emplace("neuron_merge_401", &neuron_merge_401);
        registry.emplace("adapter_merge_401", &adapter_merge_401);
        registry.emplace("neuron_contained_402", &neuron_contained_402);
        registry.emplace("adapter_contained_402", &adapter_contained_402);
        registry.emplace("neuron_contained_403", &neuron_contained_403);
        registry.emplace("adapter_contained_403", &adapter_contained_403);
        registry.emplace("neuron_contained_404", &neuron_contained_404);
        registry.emplace("adapter_contained_404", &adapter_contained_404);
        registry.emplace("neuron_contained_405", &neuron_contained_405);
        registry.emplace("adapter_contained_405", &adapter_contained_405);
        registry.emplace("neuron_contained_406", &neuron_contained_406);
        registry.emplace("adapter_contained_406", &adapter_contained_406);
        registry.emplace("neuron_contained_407", &neuron_contained_407);
        registry.emplace("adapter_contained_407", &adapter_contained_407);
        registry.emplace("neuron_contained_408", &neuron_contained_408);
        registry.emplace("adapter_contained_408", &adapter_contained_408);
        registry.emplace("neuron_contained_409", &neuron_contained_409);
        registry.emplace("adapter_contained_409", &adapter_contained_409);
        registry.emplace("neuron_contained_410", &neuron_contained_410);
        registry.emplace("adapter_contained_410", &adapter_contained_410);
        registry.emplace("neuron_contained_411", &neuron_contained_411);
        registry.emplace("adapter_contained_411", &adapter_contained_411);
        registry.emplace("neuron_product_412", &neuron_product_412);
        registry.emplace("adapter_product_412", &adapter_product_412);
        registry.emplace("neuron_product_413", &neuron_product_413);
        registry.emplace("adapter_product_413", &adapter_product_413);
        registry.emplace("neuron_product_414", &neuron_product_414);
        registry.emplace("adapter_product_414", &adapter_product_414);
        registry.emplace("neuron_move_415", &neuron_move_415);
        registry.emplace("adapter_move_415", &adapter_move_415);
        registry.emplace("neuron_intersection_416", &neuron_intersection_416);
        registry.emplace("adapter_intersection_416", &adapter_intersection_416);
        registry.emplace("neuron_intersection_417", &neuron_intersection_417);
        registry.emplace("adapter_intersection_417", &adapter_intersection_417);
        registry.emplace("neuron_intersection_418", &neuron_intersection_418);
        registry.emplace("adapter_intersection_418", &adapter_intersection_418);
        registry.emplace("neuron_intersection_419", &neuron_intersection_419);
        registry.emplace("adapter_intersection_419", &adapter_intersection_419);
        registry.emplace("neuron_intersection_420", &neuron_intersection_420);
        registry.emplace("adapter_intersection_420", &adapter_intersection_420);
        registry.emplace("neuron_intersection_421", &neuron_intersection_421);
        registry.emplace("adapter_intersection_421", &adapter_intersection_421);
        registry.emplace("neuron_intersection_422", &neuron_intersection_422);
        registry.emplace("adapter_intersection_422", &adapter_intersection_422);
        registry.emplace("neuron_intersection_423", &neuron_intersection_423);
        registry.emplace("adapter_intersection_423", &adapter_intersection_423);
        registry.emplace("neuron_intersection_424", &neuron_intersection_424);
        registry.emplace("adapter_intersection_424", &adapter_intersection_424);
        registry.emplace("neuron_intersection_425", &neuron_intersection_425);
        registry.emplace("adapter_intersection_425", &adapter_intersection_425);
        registry.emplace("neuron_difference_426", &neuron_difference_426);
        registry.emplace("adapter_difference_426", &adapter_difference_426);
        registry.emplace("neuron_difference_427", &neuron_difference_427);
        registry.emplace("adapter_difference_427", &adapter_difference_427);
        registry.emplace("neuron_difference_428", &neuron_difference_428);
        registry.emplace("adapter_difference_428", &adapter_difference_428);
        registry.emplace("neuron_difference_429", &neuron_difference_429);
        registry.emplace("adapter_difference_429", &adapter_difference_429);
        registry.emplace("neuron_difference_430", &neuron_difference_430);
        registry.emplace("adapter_difference_430", &adapter_difference_430);
        registry.emplace("neuron_difference_431", &neuron_difference_431);
        registry.emplace("adapter_difference_431", &adapter_difference_431);
        registry.emplace("neuron_difference_432", &neuron_difference_432);
        registry.emplace("adapter_difference_432", &adapter_difference_432);
        registry.emplace("neuron_difference_433", &neuron_difference_433);
        registry.emplace("adapter_difference_433", &adapter_difference_433);
        registry.emplace("neuron_difference_434", &neuron_difference_434);
        registry.emplace("adapter_difference_434", &adapter_difference_434);
        registry.emplace("neuron_difference_435", &neuron_difference_435);
        registry.emplace("adapter_difference_435", &adapter_difference_435);
        registry.emplace("neuron_combine_436", &neuron_combine_436);
        registry.emplace("adapter_combine_436", &adapter_combine_436);
        registry.emplace("neuron_combine_437", &neuron_combine_437);
        registry.emplace("adapter_combine_437", &adapter_combine_437);
        registry.emplace("neuron_combine_438", &neuron_combine_438);
        registry.emplace("adapter_combine_438", &adapter_combine_438);
        registry.emplace("neuron_combine_439", &neuron_combine_439);
        registry.emplace("adapter_combine_439", &adapter_combine_439);
        registry.emplace("neuron_combine_440", &neuron_combine_440);
        registry.emplace("adapter_combine_440", &adapter_combine_440);
        registry.emplace("neuron_combine_441", &neuron_combine_441);
        registry.emplace("adapter_combine_441", &adapter_combine_441);
        registry.emplace("neuron_combine_442", &neuron_combine_442);
        registry.emplace("adapter_combine_442", &adapter_combine_442);
        registry.emplace("neuron_combine_443", &neuron_combine_443);
        registry.emplace("adapter_combine_443", &adapter_combine_443);
        registry.emplace("neuron_combine_444", &neuron_combine_444);
        registry.emplace("adapter_combine_444", &adapter_combine_444);
        registry.emplace("neuron_combine_445", &neuron_combine_445);
        registry.emplace("adapter_combine_445", &adapter_combine_445);
        registry.emplace("neuron_mapply_446", &neuron_mapply_446);
        registry.emplace("adapter_mapply_446", &adapter_mapply_446);
        registry.emplace("neuron_mapply_447", &neuron_mapply_447);
        registry.emplace("adapter_mapply_447", &adapter_mapply_447);
        registry.emplace("neuron_mapply_448", &neuron_mapply_448);
        registry.emplace("adapter_mapply_448", &adapter_mapply_448);
        registry.emplace("neuron_mapply_449", &neuron_mapply_449);
        registry.emplace("adapter_mapply_449", &adapter_mapply_449);
        registry.emplace("neuron_mapply_450", &neuron_mapply_450);
        registry.emplace("adapter_mapply_450", &adapter_mapply_450);
        registry.emplace("neuron_mapply_451", &neuron_mapply_451);
        registry.emplace("adapter_mapply_451", &adapter_mapply_451);

        auto polymorphicRegistry = makePolymorphicNeuronRegistry();
        registry.insert(
            polymorphicRegistry.begin(),
            polymorphicRegistry.end());

        return registry;
    }
} // namespace aicpp
