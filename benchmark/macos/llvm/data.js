window.BENCHMARK_DATA = {
  "lastUpdate": 1729024629830,
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
      },
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
          "id": "8beccc8c11a9a796eb1598992658de96efeb40b1",
          "message": "Link to the website from the README (#2)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T15:05:20-04:00",
          "tree_id": "e93a092a42372d9d96622e6b593b64d812f8903f",
          "url": "https://github.com/sourcemeta/blaze/commit/8beccc8c11a9a796eb1598992658de96efeb40b1"
        },
        "date": 1729020188208,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2743149167.0000696,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2742867999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 736.245972623849,
            "unit": "ns/iter",
            "extra": "iterations: 951488\ncpu: 736.2058165736199 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 933.3988811590391,
            "unit": "ns/iter",
            "extra": "iterations: 751492\ncpu: 933.2727427570743 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 150.9247368382772,
            "unit": "ns/iter",
            "extra": "iterations: 4669562\ncpu: 150.89016914220196 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.28591357838374,
            "unit": "ns/iter",
            "extra": "iterations: 6835604\ncpu: 102.28518211411914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2592.7297511892507,
            "unit": "ns/iter",
            "extra": "iterations: 269522\ncpu: 2592.578713425993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.38276848150369,
            "unit": "ns/iter",
            "extra": "iterations: 30622780\ncpu: 23.124680384994512 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1257.7279598621353,
            "unit": "ns/iter",
            "extra": "iterations: 551698\ncpu: 1254.7661945484633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 993.8030907717068,
            "unit": "ns/iter",
            "extra": "iterations: 725644\ncpu: 972.4892647083146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1359.771069525597,
            "unit": "ns/iter",
            "extra": "iterations: 527907\ncpu: 1320.1813955867217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 228.40501796093955,
            "unit": "ns/iter",
            "extra": "iterations: 3243429\ncpu: 218.2730067468724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1421.4447791243256,
            "unit": "ns/iter",
            "extra": "iterations: 513592\ncpu: 1382.6870356236104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 113.86918634638319,
            "unit": "ns/iter",
            "extra": "iterations: 6591896\ncpu: 112.19670334604801 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 410.28651394297077,
            "unit": "ns/iter",
            "extra": "iterations: 1675182\ncpu: 406.7337160977144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 365.304529472791,
            "unit": "ns/iter",
            "extra": "iterations: 1902164\ncpu: 365.12361710136577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 758.2504161294779,
            "unit": "ns/iter",
            "extra": "iterations: 916782\ncpu: 758.163881926131 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 168.579710967086,
            "unit": "ns/iter",
            "extra": "iterations: 4160080\ncpu: 168.40926136035864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1391.5955858186023,
            "unit": "ns/iter",
            "extra": "iterations: 505054\ncpu: 1391.1304533772623 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "8963cd8de155de7581bf4679a1beb680c3f4bb68",
          "message": "Simplify interface member names (#4)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T15:39:31-04:00",
          "tree_id": "fdf4abe919a1322e9776ac6a7fc3eeccdfc9af83",
          "url": "https://github.com/sourcemeta/blaze/commit/8963cd8de155de7581bf4679a1beb680c3f4bb68"
        },
        "date": 1729021401156,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3250516542.000014,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3248612000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 802.7597832738912,
            "unit": "ns/iter",
            "extra": "iterations: 877237\ncpu: 802.5288491023521 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1041.7279214717737,
            "unit": "ns/iter",
            "extra": "iterations: 695189\ncpu: 1041.4649829039292 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 165.8791073040457,
            "unit": "ns/iter",
            "extra": "iterations: 4185927\ncpu: 165.85740745120495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 113.65401652230801,
            "unit": "ns/iter",
            "extra": "iterations: 6366067\ncpu: 113.63986587008903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2804.727929163468,
            "unit": "ns/iter",
            "extra": "iterations: 243602\ncpu: 2803.9835469331147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.137024492327033,
            "unit": "ns/iter",
            "extra": "iterations: 28693228\ncpu: 25.131191234391675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1384.6903507444524,
            "unit": "ns/iter",
            "extra": "iterations: 515874\ncpu: 1382.45579346895 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1040.5580011319216,
            "unit": "ns/iter",
            "extra": "iterations: 690771\ncpu: 1040.473615713456 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1382.1270513802576,
            "unit": "ns/iter",
            "extra": "iterations: 504843\ncpu: 1381.7543275830335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 227.1656453416917,
            "unit": "ns/iter",
            "extra": "iterations: 3057303\ncpu: 227.15085812560991 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1439.5013317745766,
            "unit": "ns/iter",
            "extra": "iterations: 482439\ncpu: 1439.42342969785 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.23318631186618,
            "unit": "ns/iter",
            "extra": "iterations: 6207710\ncpu: 117.56557571149426 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 441.8648937622255,
            "unit": "ns/iter",
            "extra": "iterations: 1612420\ncpu: 441.82595105493556 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 401.8081781526711,
            "unit": "ns/iter",
            "extra": "iterations: 1762354\ncpu: 401.7904461873146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 849.8403985152685,
            "unit": "ns/iter",
            "extra": "iterations: 716259\ncpu: 849.8057266994261 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 187.18995123957833,
            "unit": "ns/iter",
            "extra": "iterations: 3768425\ncpu: 187.19066984217477 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1520.0479935044532,
            "unit": "ns/iter",
            "extra": "iterations: 461875\ncpu: 1519.4479025710432 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "aa62a0844fb95a702554956958477bb116102c44",
          "message": "Fix WebAssembly setup (#3)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T15:51:38-04:00",
          "tree_id": "dbb59de567f9564c904a8673550008ecd22eef41",
          "url": "https://github.com/sourcemeta/blaze/commit/aa62a0844fb95a702554956958477bb116102c44"
        },
        "date": 1729022102085,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2805363124.999985,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2804808000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 740.4579920514761,
            "unit": "ns/iter",
            "extra": "iterations: 945333\ncpu: 740.2174683418436 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 934.1125049153409,
            "unit": "ns/iter",
            "extra": "iterations: 742572\ncpu: 934.0494928437914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 150.73411344970202,
            "unit": "ns/iter",
            "extra": "iterations: 4641017\ncpu: 150.7331259506268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.37912677290176,
            "unit": "ns/iter",
            "extra": "iterations: 6841817\ncpu: 102.36213567243908 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2783.612407972784,
            "unit": "ns/iter",
            "extra": "iterations: 267312\ncpu: 2760.7926318309705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.939205707436674,
            "unit": "ns/iter",
            "extra": "iterations: 29908778\ncpu: 24.910446023572092 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1393.2675290338777,
            "unit": "ns/iter",
            "extra": "iterations: 510610\ncpu: 1393.1356612678958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 964.4656131153803,
            "unit": "ns/iter",
            "extra": "iterations: 732823\ncpu: 964.432066133294 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1285.2057829093585,
            "unit": "ns/iter",
            "extra": "iterations: 544501\ncpu: 1284.5596243165758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.80456953817495,
            "unit": "ns/iter",
            "extra": "iterations: 3296088\ncpu: 211.78591105577323 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1335.1850308971132,
            "unit": "ns/iter",
            "extra": "iterations: 519951\ncpu: 1335.0546493804218 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.47389096835649,
            "unit": "ns/iter",
            "extra": "iterations: 6646474\ncpu: 104.46411134685836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 403.5983736046989,
            "unit": "ns/iter",
            "extra": "iterations: 1733158\ncpu: 403.5939019985489 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 364.0917004363088,
            "unit": "ns/iter",
            "extra": "iterations: 1923077\ncpu: 364.0701854371942 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 766.1319482316414,
            "unit": "ns/iter",
            "extra": "iterations: 922339\ncpu: 764.5811355694608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 170.02339671956085,
            "unit": "ns/iter",
            "extra": "iterations: 4018854\ncpu: 170.02011021052243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1389.5561953774363,
            "unit": "ns/iter",
            "extra": "iterations: 504828\ncpu: 1389.3524130991168 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "d9bdcbbf93d8cd96f6c31f23d9769dab6bedbc7f",
          "message": "Move benchmark validate helper into `contrib/` (#5)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T16:15:51-04:00",
          "tree_id": "bb95dee17a27294badae7557697d4422b3c04c3b",
          "url": "https://github.com/sourcemeta/blaze/commit/d9bdcbbf93d8cd96f6c31f23d9769dab6bedbc7f"
        },
        "date": 1729023540546,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2750456167.0000386,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2750072000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 742.3085831434876,
            "unit": "ns/iter",
            "extra": "iterations: 951656\ncpu: 742.2240809704349 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 931.8611685320811,
            "unit": "ns/iter",
            "extra": "iterations: 752243\ncpu: 931.7295076192145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.18707391652714,
            "unit": "ns/iter",
            "extra": "iterations: 4643603\ncpu: 151.15504060101603 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.3347545029653,
            "unit": "ns/iter",
            "extra": "iterations: 6842486\ncpu: 102.32728280335532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2612.056942227598,
            "unit": "ns/iter",
            "extra": "iterations: 265023\ncpu: 2611.686532866965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.66938813503674,
            "unit": "ns/iter",
            "extra": "iterations: 30789261\ncpu: 22.665565113758383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1250.8398337583235,
            "unit": "ns/iter",
            "extra": "iterations: 557502\ncpu: 1250.686096193377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 960.4698424308191,
            "unit": "ns/iter",
            "extra": "iterations: 735487\ncpu: 960.3731949035121 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1277.8945334410262,
            "unit": "ns/iter",
            "extra": "iterations: 550895\ncpu: 1277.8224525544767 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.35978919775718,
            "unit": "ns/iter",
            "extra": "iterations: 3308504\ncpu: 211.35534368403316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1343.971561345312,
            "unit": "ns/iter",
            "extra": "iterations: 525060\ncpu: 1343.9111720565265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 106.96271493371455,
            "unit": "ns/iter",
            "extra": "iterations: 6680664\ncpu: 106.93981915570055 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 408.5777321624906,
            "unit": "ns/iter",
            "extra": "iterations: 1631519\ncpu: 408.57139880074925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 366.76789040901394,
            "unit": "ns/iter",
            "extra": "iterations: 1907237\ncpu: 366.75095963428026 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 764.9943602485355,
            "unit": "ns/iter",
            "extra": "iterations: 911565\ncpu: 763.767805916196 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 169.97121415974667,
            "unit": "ns/iter",
            "extra": "iterations: 4153292\ncpu: 169.95963683747703 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1416.5096311104853,
            "unit": "ns/iter",
            "extra": "iterations: 500150\ncpu: 1413.849845046485 ns\nthreads: 1"
          }
        ]
      },
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
          "id": "4f77ec3bb8fb7002152d0cfa3d289d04b7cf9f62",
          "message": "Remove performance `unordered_map` related TODO (#7)\n\nWe tried and it didn't work better.\r\n\r\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T16:33:20-04:00",
          "tree_id": "c606c45d7d5e2b26d4df62077c8dd5c137e14752",
          "url": "https://github.com/sourcemeta/blaze/commit/4f77ec3bb8fb7002152d0cfa3d289d04b7cf9f62"
        },
        "date": 1729024628059,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3163738666.9999614,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3163043000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 801.2428906241029,
            "unit": "ns/iter",
            "extra": "iterations: 836290\ncpu: 801.1096629159737 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 999.8623581654874,
            "unit": "ns/iter",
            "extra": "iterations: 701698\ncpu: 999.7862328238073 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 169.96388180672056,
            "unit": "ns/iter",
            "extra": "iterations: 4248939\ncpu: 169.9365418049069 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 110.31964797964181,
            "unit": "ns/iter",
            "extra": "iterations: 6085898\ncpu: 110.30007404001836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2787.8820072063754,
            "unit": "ns/iter",
            "extra": "iterations: 250617\ncpu: 2787.0216306156417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.71761868545152,
            "unit": "ns/iter",
            "extra": "iterations: 28596407\ncpu: 24.709922473826907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1482.7700051550128,
            "unit": "ns/iter",
            "extra": "iterations: 506307\ncpu: 1482.2410118761916 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1023.2408921488066,
            "unit": "ns/iter",
            "extra": "iterations: 684684\ncpu: 1023.1566678935114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1475.0326236666197,
            "unit": "ns/iter",
            "extra": "iterations: 511132\ncpu: 1468.258688557947 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 249.66653487845633,
            "unit": "ns/iter",
            "extra": "iterations: 2951706\ncpu: 249.55872976509207 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1496.442711171967,
            "unit": "ns/iter",
            "extra": "iterations: 451362\ncpu: 1496.3111648743104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 114.96406160220926,
            "unit": "ns/iter",
            "extra": "iterations: 5821545\ncpu: 114.4833545046888 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 460.86080873905536,
            "unit": "ns/iter",
            "extra": "iterations: 1379555\ncpu: 460.72247935022455 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 393.12391660572314,
            "unit": "ns/iter",
            "extra": "iterations: 1789284\ncpu: 393.0717538411984 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 814.28435694081,
            "unit": "ns/iter",
            "extra": "iterations: 850505\ncpu: 814.2480055966753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 179.68353135398718,
            "unit": "ns/iter",
            "extra": "iterations: 3859109\ncpu: 179.50697946080234 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1494.565802651331,
            "unit": "ns/iter",
            "extra": "iterations: 464305\ncpu: 1494.2634690559019 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}