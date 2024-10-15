window.BENCHMARK_DATA = {
  "lastUpdate": 1729019194431,
  "repoUrl": "https://github.com/sourcemeta/blaze",
  "entries": {
    "Benchmark (macos/llvm)": [
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
            "name": "Juan Cruz Viotti",
            "username": "jviotti"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "a39bf1e160169cf337421e363393d6d35ff41660",
          "message": "Bump JSON Toolkit to the latest version (#1)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T14:49:22-04:00",
          "tree_id": "0e7667765467f6f3cd2728d8254450e70fb67c1f",
          "url": "https://github.com/sourcemeta/blaze/commit/a39bf1e160169cf337421e363393d6d35ff41660"
        },
        "date": 1729018356718,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3064438416.00003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2961190000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 842.8003111392679,
            "unit": "ns/iter",
            "extra": "iterations: 923702\ncpu: 815.5238377745198 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1077.8680337994178,
            "unit": "ns/iter",
            "extra": "iterations: 680841\ncpu: 1052.501244784025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 169.02422002970803,
            "unit": "ns/iter",
            "extra": "iterations: 4331415\ncpu: 165.6368646273793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 114.90699272685895,
            "unit": "ns/iter",
            "extra": "iterations: 5923569\ncpu: 112.44774898376298 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2674.1394183843036,
            "unit": "ns/iter",
            "extra": "iterations: 263301\ncpu: 2672.2382368468066 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.08613755926843,
            "unit": "ns/iter",
            "extra": "iterations: 28745544\ncpu: 23.076376637714738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1281.4765491170992,
            "unit": "ns/iter",
            "extra": "iterations: 553412\ncpu: 1280.9227121927252 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1031.696009017858,
            "unit": "ns/iter",
            "extra": "iterations: 735433\ncpu: 1019.6877213831854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1294.9775676872425,
            "unit": "ns/iter",
            "extra": "iterations: 544527\ncpu: 1294.789790037959 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.81333262767282,
            "unit": "ns/iter",
            "extra": "iterations: 3306550\ncpu: 211.79325883473714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1369.5478201253513,
            "unit": "ns/iter",
            "extra": "iterations: 517805\ncpu: 1368.9728758895735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.52482979277246,
            "unit": "ns/iter",
            "extra": "iterations: 6233137\ncpu: 104.49986900656907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 404.5722679811599,
            "unit": "ns/iter",
            "extra": "iterations: 1732510\ncpu: 404.53907913951525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 365.18062595834573,
            "unit": "ns/iter",
            "extra": "iterations: 1927796\ncpu: 365.1278454774259 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 768.2069354298047,
            "unit": "ns/iter",
            "extra": "iterations: 918876\ncpu: 768.0557550746779 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 169.38070631880555,
            "unit": "ns/iter",
            "extra": "iterations: 4151100\ncpu: 169.18045819180455 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1398.446081098158,
            "unit": "ns/iter",
            "extra": "iterations: 483439\ncpu: 1398.2943039349304 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "Juan Cruz Viotti",
            "username": "jviotti",
            "email": "jv@jviotti.com"
          },
          "committer": {
            "name": "GitHub",
            "username": "web-flow",
            "email": "noreply@github.com"
          },
          "id": "8beccc8c11a9a796eb1598992658de96efeb40b1",
          "message": "Link to the website from the README (#2)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T19:05:20Z",
          "url": "https://github.com/sourcemeta/blaze/commit/8beccc8c11a9a796eb1598992658de96efeb40b1"
        },
        "date": 1729019192550,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3954745707.999791,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3952039000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 992.7636017363963,
            "unit": "ns/iter",
            "extra": "iterations: 703072\ncpu: 969.3160871148339 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1087.7794894581666,
            "unit": "ns/iter",
            "extra": "iterations: 609862\ncpu: 1087.273842279073 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 194.42256599007507,
            "unit": "ns/iter",
            "extra": "iterations: 3542313\ncpu: 194.38090309918985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 130.6729335296102,
            "unit": "ns/iter",
            "extra": "iterations: 5560145\ncpu: 130.61583825601707 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3137.6806742822855,
            "unit": "ns/iter",
            "extra": "iterations: 183662\ncpu: 3137.5515893325824 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.39863495689716,
            "unit": "ns/iter",
            "extra": "iterations: 24246707\ncpu: 33.14359347848754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1778.3260993785545,
            "unit": "ns/iter",
            "extra": "iterations: 439271\ncpu: 1692.570190155962 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1347.2832576652384,
            "unit": "ns/iter",
            "extra": "iterations: 618271\ncpu: 1236.2992927049806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1481.1868744058083,
            "unit": "ns/iter",
            "extra": "iterations: 419501\ncpu: 1480.916612832864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 248.77706316031197,
            "unit": "ns/iter",
            "extra": "iterations: 2814093\ncpu: 248.71850361732868 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1743.4638351648764,
            "unit": "ns/iter",
            "extra": "iterations: 322067\ncpu: 1743.1621370708588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 153.8513516513382,
            "unit": "ns/iter",
            "extra": "iterations: 4730177\ncpu: 153.75323164439732 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 570.2668727244147,
            "unit": "ns/iter",
            "extra": "iterations: 1007484\ncpu: 553.0400482786838 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 437.2124166368394,
            "unit": "ns/iter",
            "extra": "iterations: 1665604\ncpu: 436.9802185873712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 927.008006157344,
            "unit": "ns/iter",
            "extra": "iterations: 784771\ncpu: 926.813044824538 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 192.16482457988755,
            "unit": "ns/iter",
            "extra": "iterations: 3855772\ncpu: 191.80854054648378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1575.6200037359845,
            "unit": "ns/iter",
            "extra": "iterations: 374730\ncpu: 1574.4989725935952 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}