window.BENCHMARK_DATA = {
  "lastUpdate": 1731352004152,
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
          "id": "43cac42dc486be24addbc2cd0aa646d18e2000f5",
          "message": "Add a top-level `vendorpull` mask file (#10)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-16T09:38:36-04:00",
          "tree_id": "f25e688eff97c36df7d04edf295bb28830b442b8",
          "url": "https://github.com/sourcemeta/blaze/commit/43cac42dc486be24addbc2cd0aa646d18e2000f5"
        },
        "date": 1729086120566,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3194156332.99991,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3193181000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 782.385217059703,
            "unit": "ns/iter",
            "extra": "iterations: 883559\ncpu: 782.2759996785729 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 975.366137919458,
            "unit": "ns/iter",
            "extra": "iterations: 721769\ncpu: 975.1762683074506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 157.76939977231203,
            "unit": "ns/iter",
            "extra": "iterations: 4495594\ncpu: 157.74489422309938 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 107.32004159336641,
            "unit": "ns/iter",
            "extra": "iterations: 6218298\ncpu: 107.31376978073442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2756.414754979021,
            "unit": "ns/iter",
            "extra": "iterations: 255141\ncpu: 2756.2053923124827 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.948261807909642,
            "unit": "ns/iter",
            "extra": "iterations: 29578923\ncpu: 23.941845347107513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1330.2715660013303,
            "unit": "ns/iter",
            "extra": "iterations: 523799\ncpu: 1329.7028058472827 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 998.0105855490839,
            "unit": "ns/iter",
            "extra": "iterations: 689336\ncpu: 997.8776677846504 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1353.4665997730349,
            "unit": "ns/iter",
            "extra": "iterations: 507272\ncpu: 1353.2660978725428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 223.07678564528416,
            "unit": "ns/iter",
            "extra": "iterations: 3132187\ncpu: 223.04798532143872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1416.046299215055,
            "unit": "ns/iter",
            "extra": "iterations: 494868\ncpu: 1415.864432535545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 110.68154072720435,
            "unit": "ns/iter",
            "extra": "iterations: 6353701\ncpu: 110.67769792755462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 425.074544585951,
            "unit": "ns/iter",
            "extra": "iterations: 1672489\ncpu: 425.05630829260895 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 389.5722003569921,
            "unit": "ns/iter",
            "extra": "iterations: 1803980\ncpu: 389.5575338972709 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 807.9081884065042,
            "unit": "ns/iter",
            "extra": "iterations: 886424\ncpu: 807.8662130086718 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 179.77474529140244,
            "unit": "ns/iter",
            "extra": "iterations: 4012036\ncpu: 179.77356135388675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1560.9252374463588,
            "unit": "ns/iter",
            "extra": "iterations: 476950\ncpu: 1552.3367229269281 ns\nthreads: 1"
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
          "id": "43cac42dc486be24addbc2cd0aa646d18e2000f5",
          "message": "Add a top-level `vendorpull` mask file (#10)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-16T13:38:36Z",
          "url": "https://github.com/sourcemeta/blaze/commit/43cac42dc486be24addbc2cd0aa646d18e2000f5"
        },
        "date": 1729105484117,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2839266250.000037,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2829204000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 737.605867506464,
            "unit": "ns/iter",
            "extra": "iterations: 951307\ncpu: 737.5242692422108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 933.1028575471629,
            "unit": "ns/iter",
            "extra": "iterations: 749104\ncpu: 933.082722826203 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.82502265472615,
            "unit": "ns/iter",
            "extra": "iterations: 4646933\ncpu: 151.76375471735858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.49484971060625,
            "unit": "ns/iter",
            "extra": "iterations: 6844761\ncpu: 102.49152600068871 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2602.693786552985,
            "unit": "ns/iter",
            "extra": "iterations: 265537\ncpu: 2602.4923080399276 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.868245070601315,
            "unit": "ns/iter",
            "extra": "iterations: 30811758\ncpu: 22.866108451195792 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1258.7873256785897,
            "unit": "ns/iter",
            "extra": "iterations: 556085\ncpu: 1258.6151397718006 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 980.284582409077,
            "unit": "ns/iter",
            "extra": "iterations: 742509\ncpu: 979.5935133446189 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1285.6025587259812,
            "unit": "ns/iter",
            "extra": "iterations: 531749\ncpu: 1285.0724684014428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 212.02978192506535,
            "unit": "ns/iter",
            "extra": "iterations: 3263053\ncpu: 212.00421813559282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1349.9486149693623,
            "unit": "ns/iter",
            "extra": "iterations: 520891\ncpu: 1349.6451272915065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 105.18261477058257,
            "unit": "ns/iter",
            "extra": "iterations: 6687493\ncpu: 105.18141850765305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 403.46791459955523,
            "unit": "ns/iter",
            "extra": "iterations: 1726268\ncpu: 403.4611080087215 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 383.7527121673974,
            "unit": "ns/iter",
            "extra": "iterations: 1914797\ncpu: 383.687148037101 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 771.7129690663697,
            "unit": "ns/iter",
            "extra": "iterations: 854117\ncpu: 769.9483794374739 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 170.2876598559202,
            "unit": "ns/iter",
            "extra": "iterations: 4139587\ncpu: 170.27858093089935 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1436.0519579038819,
            "unit": "ns/iter",
            "extra": "iterations: 498288\ncpu: 1436.022942555309 ns\nthreads: 1"
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
          "id": "9de9e573e83ee8ba48407b12b97effdbcf4e8b6b",
          "message": "Add a simple `unevaluatedProperties` benchmark case (#12)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-16T17:52:47-04:00",
          "tree_id": "c6d76de3f03bd60b3362f6dc044e912601e87578",
          "url": "https://github.com/sourcemeta/blaze/commit/9de9e573e83ee8ba48407b12b97effdbcf4e8b6b"
        },
        "date": 1729115760805,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2752638791.9999704,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2752164000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 734.6277872759504,
            "unit": "ns/iter",
            "extra": "iterations: 937609\ncpu: 734.6047232908388 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 931.9126812900553,
            "unit": "ns/iter",
            "extra": "iterations: 737906\ncpu: 931.736562651612 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.48049640886651,
            "unit": "ns/iter",
            "extra": "iterations: 4606203\ncpu: 151.47465276714914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.55680045168975,
            "unit": "ns/iter",
            "extra": "iterations: 6630986\ncpu: 102.55186785193015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2620.9787623799725,
            "unit": "ns/iter",
            "extra": "iterations: 265849\ncpu: 2620.8373926552263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.89221331346582,
            "unit": "ns/iter",
            "extra": "iterations: 30696908\ncpu: 22.888950248669982 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1264.554715066305,
            "unit": "ns/iter",
            "extra": "iterations: 559727\ncpu: 1264.5235981112235 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 951.6507166669533,
            "unit": "ns/iter",
            "extra": "iterations: 724953\ncpu: 951.6299677358378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1282.6147786097583,
            "unit": "ns/iter",
            "extra": "iterations: 550769\ncpu: 1282.3815428972946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 268.7054056024623,
            "unit": "ns/iter",
            "extra": "iterations: 3304849\ncpu: 268.64949049109396 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1360.078486749053,
            "unit": "ns/iter",
            "extra": "iterations: 517667\ncpu: 1360.0654474787834 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.97332426758908,
            "unit": "ns/iter",
            "extra": "iterations: 6653613\ncpu: 104.9638745144932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 405.1810795473159,
            "unit": "ns/iter",
            "extra": "iterations: 1732189\ncpu: 405.17345393603193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 369.32735610041146,
            "unit": "ns/iter",
            "extra": "iterations: 1910360\ncpu: 369.2916518352569 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 768.6834160768362,
            "unit": "ns/iter",
            "extra": "iterations: 906818\ncpu: 768.5853170095883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 168.06001452781405,
            "unit": "ns/iter",
            "extra": "iterations: 4156177\ncpu: 168.041447705428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 827.3872172837451,
            "unit": "ns/iter",
            "extra": "iterations: 849350\ncpu: 827.2408312238771 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1400.7237727133736,
            "unit": "ns/iter",
            "extra": "iterations: 464154\ncpu: 1395.8276778827708 ns\nthreads: 1"
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
          "id": "6933f66b0aa0fbae21ecf57cdfdef69eda083588",
          "message": "Decouple `unevaluatedProperties` from annotations (#13)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T09:07:57-04:00",
          "tree_id": "b4b5102fb37f7b3b2e15e54809299bf0815b273a",
          "url": "https://github.com/sourcemeta/blaze/commit/6933f66b0aa0fbae21ecf57cdfdef69eda083588"
        },
        "date": 1729170733294,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2865123583.0000134,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2864832000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 739.5054679987828,
            "unit": "ns/iter",
            "extra": "iterations: 950622\ncpu: 739.416929126404 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 951.5282234955187,
            "unit": "ns/iter",
            "extra": "iterations: 755523\ncpu: 951.5037927369505 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 152.7109477674703,
            "unit": "ns/iter",
            "extra": "iterations: 4600390\ncpu: 152.65944843806702 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 105.17338072870635,
            "unit": "ns/iter",
            "extra": "iterations: 6685322\ncpu: 104.8458099699611 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2598.576459348807,
            "unit": "ns/iter",
            "extra": "iterations: 264827\ncpu: 2597.5032757234007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.826323435460836,
            "unit": "ns/iter",
            "extra": "iterations: 29252352\ncpu: 23.825571359185062 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1261.515686232746,
            "unit": "ns/iter",
            "extra": "iterations: 564954\ncpu: 1261.46907535835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 972.8168885337268,
            "unit": "ns/iter",
            "extra": "iterations: 748271\ncpu: 967.4061937453162 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1278.1140241821802,
            "unit": "ns/iter",
            "extra": "iterations: 545358\ncpu: 1278.0063737948274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 212.87257836837003,
            "unit": "ns/iter",
            "extra": "iterations: 3293389\ncpu: 212.84184771370795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1331.812284270092,
            "unit": "ns/iter",
            "extra": "iterations: 527569\ncpu: 1331.5319891805618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 105.33308913322281,
            "unit": "ns/iter",
            "extra": "iterations: 6631174\ncpu: 105.3267490794239 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 405.4706957181513,
            "unit": "ns/iter",
            "extra": "iterations: 1719015\ncpu: 405.42054606853293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 366.9002672500855,
            "unit": "ns/iter",
            "extra": "iterations: 1937137\ncpu: 365.9178468017502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 762.1229882559816,
            "unit": "ns/iter",
            "extra": "iterations: 869457\ncpu: 762.0790907428384 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 168.82261826172558,
            "unit": "ns/iter",
            "extra": "iterations: 4105090\ncpu: 168.79532482844488 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 621.51869356072,
            "unit": "ns/iter",
            "extra": "iterations: 1125655\ncpu: 621.5065894967839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1406.9172687854318,
            "unit": "ns/iter",
            "extra": "iterations: 502531\ncpu: 1406.5719328757805 ns\nthreads: 1"
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
          "id": "e2c5d132cee4e51da2fd309ed6725b31787e1c66",
          "message": "Update README Bowtie badges (#15)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T13:54:58-04:00",
          "tree_id": "6fcd1c4d30bb630dc2a2e5d4bab7afe05e87b20c",
          "url": "https://github.com/sourcemeta/blaze/commit/e2c5d132cee4e51da2fd309ed6725b31787e1c66"
        },
        "date": 1729187908291,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2782097958.0000086,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2781111000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 737.5245644693231,
            "unit": "ns/iter",
            "extra": "iterations: 949359\ncpu: 737.3870158707088 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 960.3912666288762,
            "unit": "ns/iter",
            "extra": "iterations: 727348\ncpu: 960.3119827097897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 159.0639706248393,
            "unit": "ns/iter",
            "extra": "iterations: 4520825\ncpu: 159.06123329259577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 105.20018918241901,
            "unit": "ns/iter",
            "extra": "iterations: 6441402\ncpu: 105.1977504276242 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2641.3446032389497,
            "unit": "ns/iter",
            "extra": "iterations: 264983\ncpu: 2641.3241604178365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.805220758641152,
            "unit": "ns/iter",
            "extra": "iterations: 29502877\ncpu: 23.80439033115315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1251.0334207381227,
            "unit": "ns/iter",
            "extra": "iterations: 563662\ncpu: 1250.916329289537 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 936.7980837233099,
            "unit": "ns/iter",
            "extra": "iterations: 750831\ncpu: 936.7154526118393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1280.7097371719533,
            "unit": "ns/iter",
            "extra": "iterations: 542560\ncpu: 1280.525656148627 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 212.75837550625485,
            "unit": "ns/iter",
            "extra": "iterations: 3292398\ncpu: 212.74949140413736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1337.0305798878787,
            "unit": "ns/iter",
            "extra": "iterations: 520342\ncpu: 1336.8880467077386 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 105.40482524585877,
            "unit": "ns/iter",
            "extra": "iterations: 6639413\ncpu: 105.35584998252101 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 406.2940950532586,
            "unit": "ns/iter",
            "extra": "iterations: 1731345\ncpu: 406.27777825909936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 360.7304924961144,
            "unit": "ns/iter",
            "extra": "iterations: 1944239\ncpu: 360.1763980662864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 761.9802532371893,
            "unit": "ns/iter",
            "extra": "iterations: 921113\ncpu: 761.9390889065722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 168.85581718232237,
            "unit": "ns/iter",
            "extra": "iterations: 4147214\ncpu: 168.85118539819797 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 638.0342869681496,
            "unit": "ns/iter",
            "extra": "iterations: 1121184\ncpu: 637.8569440876813 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1386.9484124289265,
            "unit": "ns/iter",
            "extra": "iterations: 500450\ncpu: 1386.9277650114839 ns\nthreads: 1"
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
          "id": "e3360d0630a5ba5689c52c14beaa5836fbb88c1e",
          "message": "Decouple `unevaluatedItems` from annotations (#14)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T14:05:42-04:00",
          "tree_id": "ba4ccf11d811ddbbadf8dd31dffc5ee74276ffef",
          "url": "https://github.com/sourcemeta/blaze/commit/e3360d0630a5ba5689c52c14beaa5836fbb88c1e"
        },
        "date": 1729188542158,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2815484832.999914,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2814896999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 756.4205350741106,
            "unit": "ns/iter",
            "extra": "iterations: 952653\ncpu: 754.072049319112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1009.1510170891206,
            "unit": "ns/iter",
            "extra": "iterations: 705887\ncpu: 992.5497990471576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.88938696399387,
            "unit": "ns/iter",
            "extra": "iterations: 4624247\ncpu: 151.88051157301942 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 103.1405234913577,
            "unit": "ns/iter",
            "extra": "iterations: 6768975\ncpu: 103.13762423409759 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2633.9392893587074,
            "unit": "ns/iter",
            "extra": "iterations: 266576\ncpu: 2633.586669467619 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.955717127314145,
            "unit": "ns/iter",
            "extra": "iterations: 29131466\ncpu: 24.952949501408522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1289.3210804520982,
            "unit": "ns/iter",
            "extra": "iterations: 515525\ncpu: 1288.9345812521233 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 978.6245835146709,
            "unit": "ns/iter",
            "extra": "iterations: 740122\ncpu: 978.5967718835537 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1318.4988215594003,
            "unit": "ns/iter",
            "extra": "iterations: 509996\ncpu: 1318.478968462497 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 212.5350745934184,
            "unit": "ns/iter",
            "extra": "iterations: 3236545\ncpu: 212.5028386751923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1364.8486765140055,
            "unit": "ns/iter",
            "extra": "iterations: 525695\ncpu: 1364.4775012126815 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 105.42014398324079,
            "unit": "ns/iter",
            "extra": "iterations: 6628411\ncpu: 105.41063310648666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 404.55919232212926,
            "unit": "ns/iter",
            "extra": "iterations: 1718804\ncpu: 404.4684559728742 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 366.26748914643633,
            "unit": "ns/iter",
            "extra": "iterations: 1906754\ncpu: 366.2465110863823 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 761.0244981216248,
            "unit": "ns/iter",
            "extra": "iterations: 920193\ncpu: 760.922980287829 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 171.6436774892693,
            "unit": "ns/iter",
            "extra": "iterations: 4158696\ncpu: 170.16223354628482 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 627.3365086005631,
            "unit": "ns/iter",
            "extra": "iterations: 1128304\ncpu: 627.274209787433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1394.0752259076903,
            "unit": "ns/iter",
            "extra": "iterations: 504188\ncpu: 1394.067292359205 ns\nthreads: 1"
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
          "id": "9e9f8ce5992b3a5fe1bc73ad1e5aaa8515b23c89",
          "message": "Don't store annotations in the `EvaluationContext` (#16)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T14:22:17-04:00",
          "tree_id": "ab47a6d0848c62be8fcb5718cdb1aa3c375bccc8",
          "url": "https://github.com/sourcemeta/blaze/commit/9e9f8ce5992b3a5fe1bc73ad1e5aaa8515b23c89"
        },
        "date": 1729189525225,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2758407874.999989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2748027000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 740.4889171131022,
            "unit": "ns/iter",
            "extra": "iterations: 954264\ncpu: 739.3802972762262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 938.6630234444265,
            "unit": "ns/iter",
            "extra": "iterations: 744396\ncpu: 938.6334692824787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.27442055012463,
            "unit": "ns/iter",
            "extra": "iterations: 4685910\ncpu: 149.22821821161745 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.18730094868049,
            "unit": "ns/iter",
            "extra": "iterations: 6855016\ncpu: 102.18604887282522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2619.252911002569,
            "unit": "ns/iter",
            "extra": "iterations: 268636\ncpu: 2619.183579267115 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.21912219293596,
            "unit": "ns/iter",
            "extra": "iterations: 33021516\ncpu: 21.217499523643944 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1251.4511608108955,
            "unit": "ns/iter",
            "extra": "iterations: 563830\ncpu: 1251.3151127112787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 944.1271918818093,
            "unit": "ns/iter",
            "extra": "iterations: 741258\ncpu: 944.1139252460017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1275.8614713892257,
            "unit": "ns/iter",
            "extra": "iterations: 550038\ncpu: 1275.5464167930181 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.82130574462815,
            "unit": "ns/iter",
            "extra": "iterations: 3320006\ncpu: 210.80624553088103 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1327.1941652100352,
            "unit": "ns/iter",
            "extra": "iterations: 525743\ncpu: 1327.1921832530325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.0283859862718,
            "unit": "ns/iter",
            "extra": "iterations: 6714757\ncpu: 104.01567770806892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 403.7975288265123,
            "unit": "ns/iter",
            "extra": "iterations: 1738850\ncpu: 403.7467291600769 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 367.331739095668,
            "unit": "ns/iter",
            "extra": "iterations: 1876550\ncpu: 367.2915723002313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 758.9316175645234,
            "unit": "ns/iter",
            "extra": "iterations: 926232\ncpu: 757.9807218925733 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 166.54794209817354,
            "unit": "ns/iter",
            "extra": "iterations: 4223355\ncpu: 166.53466260828245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 620.4224501391341,
            "unit": "ns/iter",
            "extra": "iterations: 1129944\ncpu: 620.2802970766693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1385.667870028998,
            "unit": "ns/iter",
            "extra": "iterations: 504697\ncpu: 1385.625434666743 ns\nthreads: 1"
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
          "id": "03841f2a611ba1e4ada437535b5130ffdfc55e38",
          "message": "Simplify non-pure-annotation instructions (#17)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T14:38:00-04:00",
          "tree_id": "169832bebb0f58b0892167c9107da003036403ac",
          "url": "https://github.com/sourcemeta/blaze/commit/03841f2a611ba1e4ada437535b5130ffdfc55e38"
        },
        "date": 1729190478652,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2839408292.00003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2835638000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 743.5469590861595,
            "unit": "ns/iter",
            "extra": "iterations: 952148\ncpu: 743.5188647143088 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 923.5978188797426,
            "unit": "ns/iter",
            "extra": "iterations: 745030\ncpu: 923.574889601761 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.4064550628632,
            "unit": "ns/iter",
            "extra": "iterations: 4611543\ncpu: 149.40378957758807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.3915693257818,
            "unit": "ns/iter",
            "extra": "iterations: 6916244\ncpu: 101.37785769270151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2610.7580294881486,
            "unit": "ns/iter",
            "extra": "iterations: 270752\ncpu: 2610.6621557735493 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.71149052074103,
            "unit": "ns/iter",
            "extra": "iterations: 33070033\ncpu: 21.707689254498177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1261.668232284767,
            "unit": "ns/iter",
            "extra": "iterations: 555904\ncpu: 1261.4606119042153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 959.7799140351937,
            "unit": "ns/iter",
            "extra": "iterations: 747049\ncpu: 959.6639577859008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1290.1197895142004,
            "unit": "ns/iter",
            "extra": "iterations: 551676\ncpu: 1289.958236356122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 214.04803281972937,
            "unit": "ns/iter",
            "extra": "iterations: 3089117\ncpu: 214.04045233638033 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1344.5487921371168,
            "unit": "ns/iter",
            "extra": "iterations: 521334\ncpu: 1344.5104290147967 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.69173028271494,
            "unit": "ns/iter",
            "extra": "iterations: 6700616\ncpu: 104.68171881510602 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 407.8956475719329,
            "unit": "ns/iter",
            "extra": "iterations: 1717593\ncpu: 407.8504046069122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 364.4388417480949,
            "unit": "ns/iter",
            "extra": "iterations: 1908704\ncpu: 363.6823729609212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 765.1850988491556,
            "unit": "ns/iter",
            "extra": "iterations: 925754\ncpu: 765.0704182752646 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 166.7528249871194,
            "unit": "ns/iter",
            "extra": "iterations: 4236391\ncpu: 166.74995296704182 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 626.7118433538344,
            "unit": "ns/iter",
            "extra": "iterations: 1125492\ncpu: 626.6379503363842 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1415.1006504835768,
            "unit": "ns/iter",
            "extra": "iterations: 492864\ncpu: 1415.073935203219 ns\nthreads: 1"
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
          "id": "e150395c7d0d31d8a46efd633ee3b92783c2475a",
          "message": "Simplify `EvaluationContext` with regards to evaluation tracking (#18)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T14:54:42-04:00",
          "tree_id": "7d129c585fe773a8cf162db9a2f3c400ce340e7b",
          "url": "https://github.com/sourcemeta/blaze/commit/e150395c7d0d31d8a46efd633ee3b92783c2475a"
        },
        "date": 1729191478715,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2761792708.00003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2761360000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 740.9561067533928,
            "unit": "ns/iter",
            "extra": "iterations: 948278\ncpu: 740.9346204383105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 926.1262599456501,
            "unit": "ns/iter",
            "extra": "iterations: 749834\ncpu: 926.071637189031 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 150.41457435938793,
            "unit": "ns/iter",
            "extra": "iterations: 4697167\ncpu: 150.40384980989583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.7385790992186,
            "unit": "ns/iter",
            "extra": "iterations: 6911123\ncpu: 101.71834591860113 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2640.7617240747763,
            "unit": "ns/iter",
            "extra": "iterations: 267761\ncpu: 2640.687030598187 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.533784532818405,
            "unit": "ns/iter",
            "extra": "iterations: 33123708\ncpu: 21.531949261236072 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1250.9752345528389,
            "unit": "ns/iter",
            "extra": "iterations: 564052\ncpu: 1250.9343110209652 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 957.011977457999,
            "unit": "ns/iter",
            "extra": "iterations: 734630\ncpu: 956.7755196493471 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1293.714190399202,
            "unit": "ns/iter",
            "extra": "iterations: 550055\ncpu: 1293.6688149366882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.10319011493766,
            "unit": "ns/iter",
            "extra": "iterations: 3299599\ncpu: 211.07928569501922 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1351.776881613349,
            "unit": "ns/iter",
            "extra": "iterations: 527061\ncpu: 1351.5911820453405 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.2151521758293,
            "unit": "ns/iter",
            "extra": "iterations: 6737831\ncpu: 104.21335886875156 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 402.42071611768597,
            "unit": "ns/iter",
            "extra": "iterations: 1739351\ncpu: 402.39549119182936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 365.9593077739796,
            "unit": "ns/iter",
            "extra": "iterations: 1920760\ncpu: 365.9525396197337 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 762.8348700130025,
            "unit": "ns/iter",
            "extra": "iterations: 927324\ncpu: 762.8078212145926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 167.82528240719566,
            "unit": "ns/iter",
            "extra": "iterations: 4214836\ncpu: 167.77782101130416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 653.6579577992724,
            "unit": "ns/iter",
            "extra": "iterations: 1057849\ncpu: 653.6386573130955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1407.458475751058,
            "unit": "ns/iter",
            "extra": "iterations: 497071\ncpu: 1407.4025642212148 ns\nthreads: 1"
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
          "id": "e150395c7d0d31d8a46efd633ee3b92783c2475a",
          "message": "Simplify `EvaluationContext` with regards to evaluation tracking (#18)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T18:54:42Z",
          "url": "https://github.com/sourcemeta/blaze/commit/e150395c7d0d31d8a46efd633ee3b92783c2475a"
        },
        "date": 1729191875567,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2797583374.999931,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2797138000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 739.9160002437139,
            "unit": "ns/iter",
            "extra": "iterations: 935967\ncpu: 739.8487339831423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 950.5409377316741,
            "unit": "ns/iter",
            "extra": "iterations: 758298\ncpu: 946.7188361303861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 155.0020715936181,
            "unit": "ns/iter",
            "extra": "iterations: 4352205\ncpu: 154.34658983205088 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.67821729673167,
            "unit": "ns/iter",
            "extra": "iterations: 6901788\ncpu: 101.65191976340043 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2626.6809721467516,
            "unit": "ns/iter",
            "extra": "iterations: 266215\ncpu: 2626.583776271059 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.498736260770173,
            "unit": "ns/iter",
            "extra": "iterations: 33095831\ncpu: 21.4972393350691 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1262.0675916063283,
            "unit": "ns/iter",
            "extra": "iterations: 554847\ncpu: 1261.7316124985805 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 957.4814075083616,
            "unit": "ns/iter",
            "extra": "iterations: 735001\ncpu: 957.3034594510776 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1289.8074813572575,
            "unit": "ns/iter",
            "extra": "iterations: 550622\ncpu: 1289.77955839033 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.0406381823207,
            "unit": "ns/iter",
            "extra": "iterations: 3307456\ncpu: 211.01112153872953 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1333.6844586762984,
            "unit": "ns/iter",
            "extra": "iterations: 525573\ncpu: 1333.666303253782 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.83666651744358,
            "unit": "ns/iter",
            "extra": "iterations: 6723851\ncpu: 104.83352471671354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 404.56023777660107,
            "unit": "ns/iter",
            "extra": "iterations: 1736925\ncpu: 404.36000403011013 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 365.88129633033884,
            "unit": "ns/iter",
            "extra": "iterations: 1919233\ncpu: 365.42358327519287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 759.1624615344009,
            "unit": "ns/iter",
            "extra": "iterations: 925179\ncpu: 758.893143921338 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 165.93666979724202,
            "unit": "ns/iter",
            "extra": "iterations: 4227130\ncpu: 165.92084937061225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 631.670020792663,
            "unit": "ns/iter",
            "extra": "iterations: 1113852\ncpu: 631.5650553215323 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1395.5049559438398,
            "unit": "ns/iter",
            "extra": "iterations: 501519\ncpu: 1395.3409541811977 ns\nthreads: 1"
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
          "id": "012b106a3a870e2f5be58e289abd52e108d24265",
          "message": "Report `ControlMark` during evaluation (#21)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T16:05:07-04:00",
          "tree_id": "a76c25e441019c76c09d7958c6e8cb6547e6d2f0",
          "url": "https://github.com/sourcemeta/blaze/commit/012b106a3a870e2f5be58e289abd52e108d24265"
        },
        "date": 1729195707736,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3063184999.9999757,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3047936000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 740.2954219862007,
            "unit": "ns/iter",
            "extra": "iterations: 949320\ncpu: 740.2646104580127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 925.9385475522297,
            "unit": "ns/iter",
            "extra": "iterations: 759986\ncpu: 925.9262670628144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 155.46500055327053,
            "unit": "ns/iter",
            "extra": "iterations: 4690117\ncpu: 155.44580231154157 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 107.7466426231151,
            "unit": "ns/iter",
            "extra": "iterations: 6637399\ncpu: 107.70649768079342 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2734.9825857317087,
            "unit": "ns/iter",
            "extra": "iterations: 257490\ncpu: 2733.849858246923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.431563943196686,
            "unit": "ns/iter",
            "extra": "iterations: 31467038\ncpu: 22.427468387714217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1312.6204262056372,
            "unit": "ns/iter",
            "extra": "iterations: 520547\ncpu: 1312.5020411221294 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1001.9050848562284,
            "unit": "ns/iter",
            "extra": "iterations: 705546\ncpu: 1001.6058485201548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1342.8019870719356,
            "unit": "ns/iter",
            "extra": "iterations: 528617\ncpu: 1341.9829479566506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 215.6203470884329,
            "unit": "ns/iter",
            "extra": "iterations: 3193941\ncpu: 215.53121989416854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1352.5478739080866,
            "unit": "ns/iter",
            "extra": "iterations: 515688\ncpu: 1352.3874901102986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.41017136727727,
            "unit": "ns/iter",
            "extra": "iterations: 6755257\ncpu: 104.40846292006363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 405.2340133925259,
            "unit": "ns/iter",
            "extra": "iterations: 1737986\ncpu: 404.70636702482074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 376.6261606741372,
            "unit": "ns/iter",
            "extra": "iterations: 1862926\ncpu: 376.6059414061546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 772.4640717464985,
            "unit": "ns/iter",
            "extra": "iterations: 899835\ncpu: 772.1004406363409 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 167.49189828860284,
            "unit": "ns/iter",
            "extra": "iterations: 4194731\ncpu: 167.4810613600722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 626.549382461172,
            "unit": "ns/iter",
            "extra": "iterations: 1114100\ncpu: 625.7562157795518 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1404.7558526691007,
            "unit": "ns/iter",
            "extra": "iterations: 500669\ncpu: 1404.7204839924227 ns\nthreads: 1"
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
          "id": "b4e3b8319ff13bafa2f21c10d6b65bf652f61ca9",
          "message": "Report all `dependentSchemas` steps (#22)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T16:20:47-04:00",
          "tree_id": "3e02f14df9fdb1114fcf5373ccbb318863144c71",
          "url": "https://github.com/sourcemeta/blaze/commit/b4e3b8319ff13bafa2f21c10d6b65bf652f61ca9"
        },
        "date": 1729196747897,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2808785749.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2808212000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 744.9736516930577,
            "unit": "ns/iter",
            "extra": "iterations: 931483\ncpu: 744.9057041298661 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 935.5888997356315,
            "unit": "ns/iter",
            "extra": "iterations: 759063\ncpu: 935.358461682364 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.97166668548425,
            "unit": "ns/iter",
            "extra": "iterations: 4608356\ncpu: 151.95549128582945 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 108.09689337012247,
            "unit": "ns/iter",
            "extra": "iterations: 6784458\ncpu: 104.876174338466 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2803.3180977835145,
            "unit": "ns/iter",
            "extra": "iterations: 263419\ncpu: 2779.6969846518273 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.64882106147408,
            "unit": "ns/iter",
            "extra": "iterations: 30991141\ncpu: 21.642959192757708 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1266.1272567265914,
            "unit": "ns/iter",
            "extra": "iterations: 540883\ncpu: 1266.0519927599885 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 983.8636478418749,
            "unit": "ns/iter",
            "extra": "iterations: 712816\ncpu: 983.7657965028855 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1301.2259062943758,
            "unit": "ns/iter",
            "extra": "iterations: 530512\ncpu: 1301.2259854630984 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 213.54416431842958,
            "unit": "ns/iter",
            "extra": "iterations: 3288639\ncpu: 213.38006391093688 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1350.4396154051124,
            "unit": "ns/iter",
            "extra": "iterations: 527204\ncpu: 1349.2120697111573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 105.46584656267741,
            "unit": "ns/iter",
            "extra": "iterations: 6722237\ncpu: 105.4568590783099 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 405.2042146074479,
            "unit": "ns/iter",
            "extra": "iterations: 1729651\ncpu: 405.16901964616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 366.0730614484105,
            "unit": "ns/iter",
            "extra": "iterations: 1891928\ncpu: 366.02978548866423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 766.2557948154323,
            "unit": "ns/iter",
            "extra": "iterations: 911375\ncpu: 766.2191743245123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 169.62556881845242,
            "unit": "ns/iter",
            "extra": "iterations: 4221470\ncpu: 169.58689745515196 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 637.8899338546828,
            "unit": "ns/iter",
            "extra": "iterations: 1084884\ncpu: 637.6967491455308 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1440.2846069931065,
            "unit": "ns/iter",
            "extra": "iterations: 495933\ncpu: 1439.6017203936822 ns\nthreads: 1"
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
          "id": "28802968317fb9426f7048ee645e50ff975287e7",
          "message": "Always mark `ControlEvaluate` with `report` true (#23)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T16:24:02-04:00",
          "tree_id": "70bc6b86448b578459b7714241158197e96c3512",
          "url": "https://github.com/sourcemeta/blaze/commit/28802968317fb9426f7048ee645e50ff975287e7"
        },
        "date": 1729196938904,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2846767083.0000315,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2815876000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 753.4217034867838,
            "unit": "ns/iter",
            "extra": "iterations: 932053\ncpu: 753.246864716921 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 948.3621101530201,
            "unit": "ns/iter",
            "extra": "iterations: 725028\ncpu: 948.1261413352314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.8978397006273,
            "unit": "ns/iter",
            "extra": "iterations: 4648939\ncpu: 151.87744988695258 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.00140137719124,
            "unit": "ns/iter",
            "extra": "iterations: 6871098\ncpu: 101.9922871133551 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2631.560485900597,
            "unit": "ns/iter",
            "extra": "iterations: 268203\ncpu: 2629.5194311771265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.916410809258366,
            "unit": "ns/iter",
            "extra": "iterations: 31999269\ncpu: 21.90928174015476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1283.342594434857,
            "unit": "ns/iter",
            "extra": "iterations: 557925\ncpu: 1281.3639826141537 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 965.9266743783999,
            "unit": "ns/iter",
            "extra": "iterations: 723567\ncpu: 965.8124264926413 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1307.7550127450397,
            "unit": "ns/iter",
            "extra": "iterations: 539824\ncpu: 1307.7484513471095 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 216.7447110573313,
            "unit": "ns/iter",
            "extra": "iterations: 3222525\ncpu: 216.70212023180528 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1367.0915167931953,
            "unit": "ns/iter",
            "extra": "iterations: 516102\ncpu: 1366.3636257949042 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 105.95072685056276,
            "unit": "ns/iter",
            "extra": "iterations: 6584641\ncpu: 105.93348976808291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 412.6005101517056,
            "unit": "ns/iter",
            "extra": "iterations: 1695182\ncpu: 412.4447994374653 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 369.4324584934335,
            "unit": "ns/iter",
            "extra": "iterations: 1888498\ncpu: 368.8873379797056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 763.2150666495031,
            "unit": "ns/iter",
            "extra": "iterations: 922886\ncpu: 763.1755168027212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 168.43739900023567,
            "unit": "ns/iter",
            "extra": "iterations: 4123153\ncpu: 168.4012211043347 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 634.8789917091026,
            "unit": "ns/iter",
            "extra": "iterations: 1090479\ncpu: 634.8467049801021 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1405.431661217816,
            "unit": "ns/iter",
            "extra": "iterations: 500404\ncpu: 1405.3504768147347 ns\nthreads: 1"
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
          "id": "4266c3ff8a1a51ec189a98f7678912eef8443da0",
          "message": "Mark evaluation on `Loop(Properties|Items)Unevaluated` out of the box (#24)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T16:35:10-04:00",
          "tree_id": "e195616788a9e0e0a5838cfd26cb6bd3c04aef43",
          "url": "https://github.com/sourcemeta/blaze/commit/4266c3ff8a1a51ec189a98f7678912eef8443da0"
        },
        "date": 1729197522081,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3110377999.999969,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3109426000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 790.4428536237523,
            "unit": "ns/iter",
            "extra": "iterations: 872785\ncpu: 790.0376381353942 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 991.5126363264258,
            "unit": "ns/iter",
            "extra": "iterations: 712628\ncpu: 990.1561544031383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 164.15721440565693,
            "unit": "ns/iter",
            "extra": "iterations: 4385635\ncpu: 164.14498698592124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 109.4771513090707,
            "unit": "ns/iter",
            "extra": "iterations: 6402927\ncpu: 109.37841396598775 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2876.643611423423,
            "unit": "ns/iter",
            "extra": "iterations: 249907\ncpu: 2876.1539292616862 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.369437142800717,
            "unit": "ns/iter",
            "extra": "iterations: 30251563\ncpu: 23.364809282746776 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1338.7209821768129,
            "unit": "ns/iter",
            "extra": "iterations: 525608\ncpu: 1338.0751434529154 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1027.6702340759211,
            "unit": "ns/iter",
            "extra": "iterations: 690417\ncpu: 1027.4153156715447 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1395.837367028783,
            "unit": "ns/iter",
            "extra": "iterations: 511483\ncpu: 1395.295640324313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 232.96738746108176,
            "unit": "ns/iter",
            "extra": "iterations: 3096907\ncpu: 232.8658884493458 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1461.1691417320426,
            "unit": "ns/iter",
            "extra": "iterations: 493657\ncpu: 1456.130471157098 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 134.38551335794526,
            "unit": "ns/iter",
            "extra": "iterations: 6237636\ncpu: 131.53685146103408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 513.6656249999305,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 501.23199999999815 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 405.95348611169646,
            "unit": "ns/iter",
            "extra": "iterations: 1707834\ncpu: 405.45568246094285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 938.5709350697272,
            "unit": "ns/iter",
            "extra": "iterations: 833403\ncpu: 933.9275236590154 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 192.98404979249332,
            "unit": "ns/iter",
            "extra": "iterations: 3573872\ncpu: 192.74221348722014 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 738.4528739986539,
            "unit": "ns/iter",
            "extra": "iterations: 939736\ncpu: 738.0360016004462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1637.6168385942956,
            "unit": "ns/iter",
            "extra": "iterations: 451546\ncpu: 1635.8156201139989 ns\nthreads: 1"
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
          "id": "41304832027085370a67b9dd5cdc50dedcfa4af8",
          "message": "Report evaluation of `ControlEvaluate` (#25)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T18:35:28-04:00",
          "tree_id": "851f22b2096627e30b867f1f94059fc429d4761e",
          "url": "https://github.com/sourcemeta/blaze/commit/41304832027085370a67b9dd5cdc50dedcfa4af8"
        },
        "date": 1729204740948,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2805417709.0000396,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2805177999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 749.1005884747228,
            "unit": "ns/iter",
            "extra": "iterations: 945665\ncpu: 747.857856640566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 990.6103976629031,
            "unit": "ns/iter",
            "extra": "iterations: 693502\ncpu: 979.7044565120223 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 150.76396117651484,
            "unit": "ns/iter",
            "extra": "iterations: 4623697\ncpu: 150.76333937972151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.22663620355534,
            "unit": "ns/iter",
            "extra": "iterations: 6915903\ncpu: 102.22063554101318 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2615.7874131388467,
            "unit": "ns/iter",
            "extra": "iterations: 266230\ncpu: 2615.591781542281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.73227522753381,
            "unit": "ns/iter",
            "extra": "iterations: 32482448\ncpu: 21.730505040753016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1251.9980386837494,
            "unit": "ns/iter",
            "extra": "iterations: 563907\ncpu: 1251.8695458648351 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 959.001977193343,
            "unit": "ns/iter",
            "extra": "iterations: 717684\ncpu: 958.7994158989189 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1271.0522469133198,
            "unit": "ns/iter",
            "extra": "iterations: 550444\ncpu: 1271.0539128412654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.3247044154892,
            "unit": "ns/iter",
            "extra": "iterations: 3315634\ncpu: 211.30046319949665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1359.7246727525342,
            "unit": "ns/iter",
            "extra": "iterations: 519026\ncpu: 1359.6621363862282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.74590524596434,
            "unit": "ns/iter",
            "extra": "iterations: 6724885\ncpu: 104.68684594606435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 406.89068089760246,
            "unit": "ns/iter",
            "extra": "iterations: 1724694\ncpu: 406.8634783909494 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 362.6658966714738,
            "unit": "ns/iter",
            "extra": "iterations: 1921657\ncpu: 361.90589683798913 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 767.111250139104,
            "unit": "ns/iter",
            "extra": "iterations: 925473\ncpu: 767.0434469725208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 166.90407196343156,
            "unit": "ns/iter",
            "extra": "iterations: 4232037\ncpu: 166.82155661682575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 664.3159576921948,
            "unit": "ns/iter",
            "extra": "iterations: 1062215\ncpu: 664.0708331175898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1412.757033315106,
            "unit": "ns/iter",
            "extra": "iterations: 496743\ncpu: 1410.570455950064 ns\nthreads: 1"
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
            "email": "jv@jviotti.com",
            "name": "Juan Cruz Viotti",
            "username": "jviotti"
          },
          "distinct": true,
          "id": "fbb15e15769b7a2c63eddc39c54fe6eb4b019d44",
          "message": "Add a simple logo\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T19:22:50-04:00",
          "tree_id": "dc8ed259de5bbcdfefc513ebcc2217f335e73b21",
          "url": "https://github.com/sourcemeta/blaze/commit/fbb15e15769b7a2c63eddc39c54fe6eb4b019d44"
        },
        "date": 1729207576176,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3008672459.000081,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3008103999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 853.6793051284876,
            "unit": "ns/iter",
            "extra": "iterations: 819720\ncpu: 849.4876299224131 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1051.4359011238107,
            "unit": "ns/iter",
            "extra": "iterations: 667461\ncpu: 1051.244941652022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 167.5213654139424,
            "unit": "ns/iter",
            "extra": "iterations: 4055620\ncpu: 167.46983198623164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 115.53668914418333,
            "unit": "ns/iter",
            "extra": "iterations: 6244313\ncpu: 115.51743162138087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2978.7994703380496,
            "unit": "ns/iter",
            "extra": "iterations: 234489\ncpu: 2977.103403571169 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.782916572023677,
            "unit": "ns/iter",
            "extra": "iterations: 26429157\ncpu: 25.774147847394445 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1501.30864763162,
            "unit": "ns/iter",
            "extra": "iterations: 471447\ncpu: 1500.7901206286165 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1107.9945687103523,
            "unit": "ns/iter",
            "extra": "iterations: 645703\ncpu: 1107.6222349903896 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1621.8802968292816,
            "unit": "ns/iter",
            "extra": "iterations: 483780\ncpu: 1621.4767042870758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 263.24889671708684,
            "unit": "ns/iter",
            "extra": "iterations: 2810929\ncpu: 263.241796573304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2083.4994644913227,
            "unit": "ns/iter",
            "extra": "iterations: 394018\ncpu: 2023.6029826048548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 151.60575452868522,
            "unit": "ns/iter",
            "extra": "iterations: 4575492\ncpu: 147.85054809406293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 513.6817486722961,
            "unit": "ns/iter",
            "extra": "iterations: 1097953\ncpu: 512.4645590476091 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 456.604828819147,
            "unit": "ns/iter",
            "extra": "iterations: 1617704\ncpu: 454.6789771181849 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 883.460597231977,
            "unit": "ns/iter",
            "extra": "iterations: 793561\ncpu: 883.2263682312993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 196.57296551843737,
            "unit": "ns/iter",
            "extra": "iterations: 3196318\ncpu: 196.56554823393753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 849.3709512875135,
            "unit": "ns/iter",
            "extra": "iterations: 921404\ncpu: 845.1428472201134 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1832.235536813345,
            "unit": "ns/iter",
            "extra": "iterations: 395072\ncpu: 1831.0409241859752 ns\nthreads: 1"
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
            "email": "jv@jviotti.com",
            "name": "Juan Cruz Viotti",
            "username": "jviotti"
          },
          "distinct": true,
          "id": "b1c2eafcb8fa57152b23e0b4a1801aba7654c296",
          "message": "Improve the README\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T19:39:59-04:00",
          "tree_id": "b3b303fcd5e32381ff9cfcf2f65cc7a0a66ed11a",
          "url": "https://github.com/sourcemeta/blaze/commit/b1c2eafcb8fa57152b23e0b4a1801aba7654c296"
        },
        "date": 1729208613404,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2769973291.000042,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2769145000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 738.6702899348411,
            "unit": "ns/iter",
            "extra": "iterations: 952731\ncpu: 738.5505457469098 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 923.4713565652391,
            "unit": "ns/iter",
            "extra": "iterations: 753506\ncpu: 923.4020697910839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.85726700057643,
            "unit": "ns/iter",
            "extra": "iterations: 4715742\ncpu: 149.8283833169839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.67961763688064,
            "unit": "ns/iter",
            "extra": "iterations: 6887798\ncpu: 101.67734303474052 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2719.313903502343,
            "unit": "ns/iter",
            "extra": "iterations: 264027\ncpu: 2662.3716513841405 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.84774076769716,
            "unit": "ns/iter",
            "extra": "iterations: 31481756\ncpu: 22.236847271162407 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1276.7706348912623,
            "unit": "ns/iter",
            "extra": "iterations: 545920\ncpu: 1275.7931565064484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 957.02812616576,
            "unit": "ns/iter",
            "extra": "iterations: 734654\ncpu: 956.8613251952636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1328.960494329128,
            "unit": "ns/iter",
            "extra": "iterations: 516255\ncpu: 1328.4113471055994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 221.00218992109959,
            "unit": "ns/iter",
            "extra": "iterations: 3079563\ncpu: 218.9771730599442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1371.2156695768813,
            "unit": "ns/iter",
            "extra": "iterations: 527251\ncpu: 1371.183743605987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.16903525213277,
            "unit": "ns/iter",
            "extra": "iterations: 6737636\ncpu: 104.13147875605021 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 402.5914671394686,
            "unit": "ns/iter",
            "extra": "iterations: 1740073\ncpu: 402.5003548701697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 377.7795966237861,
            "unit": "ns/iter",
            "extra": "iterations: 1863025\ncpu: 377.3846298358873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 763.7232325993858,
            "unit": "ns/iter",
            "extra": "iterations: 914125\ncpu: 763.5104608231912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 166.63518653452905,
            "unit": "ns/iter",
            "extra": "iterations: 4203699\ncpu: 166.62301463544378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 662.7134080335262,
            "unit": "ns/iter",
            "extra": "iterations: 1059611\ncpu: 662.6412900583313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1403.0123170149373,
            "unit": "ns/iter",
            "extra": "iterations: 501339\ncpu: 1402.9249669385422 ns\nthreads: 1"
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
          "id": "dbb3acf5c0b1ac7580ca3b807db3aaf4ac05254c",
          "message": "Fix `ErrorTraceOutput` crashing on `$dynamicAnchor` (#26)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T20:25:02-04:00",
          "tree_id": "a2431c3bc0c7e36e0a8b8072d74e31f6e2c4fa51",
          "url": "https://github.com/sourcemeta/blaze/commit/dbb3acf5c0b1ac7580ca3b807db3aaf4ac05254c"
        },
        "date": 1729211383058,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3265264791.0000496,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3263848999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 819.2909727514315,
            "unit": "ns/iter",
            "extra": "iterations: 827971\ncpu: 819.2581624235637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 993.0908137040619,
            "unit": "ns/iter",
            "extra": "iterations: 704310\ncpu: 993.092530277859 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 160.29234836094685,
            "unit": "ns/iter",
            "extra": "iterations: 4374945\ncpu: 160.23767155929949 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 110.56596901200439,
            "unit": "ns/iter",
            "extra": "iterations: 6343683\ncpu: 110.51482238314883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2900.446056736227,
            "unit": "ns/iter",
            "extra": "iterations: 232726\ncpu: 2896.6853724981406 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.516516837916985,
            "unit": "ns/iter",
            "extra": "iterations: 29207679\ncpu: 23.5084068131535 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1346.1071425045895,
            "unit": "ns/iter",
            "extra": "iterations: 506391\ncpu: 1346.0349808744602 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1039.510482267129,
            "unit": "ns/iter",
            "extra": "iterations: 699944\ncpu: 1039.1988501937315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1448.5421029092392,
            "unit": "ns/iter",
            "extra": "iterations: 503065\ncpu: 1448.0236152385849 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 236.29965579198745,
            "unit": "ns/iter",
            "extra": "iterations: 2941535\ncpu: 236.2820772147873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1446.960150570044,
            "unit": "ns/iter",
            "extra": "iterations: 488012\ncpu: 1446.4234486037217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 116.45842578759088,
            "unit": "ns/iter",
            "extra": "iterations: 6091300\ncpu: 116.43951209101502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 431.84103048420315,
            "unit": "ns/iter",
            "extra": "iterations: 1592494\ncpu: 431.690166493562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 406.7131885053562,
            "unit": "ns/iter",
            "extra": "iterations: 1692997\ncpu: 406.6037919736427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 820.4909267451662,
            "unit": "ns/iter",
            "extra": "iterations: 853773\ncpu: 820.4370482552151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 186.2179463331729,
            "unit": "ns/iter",
            "extra": "iterations: 3768547\ncpu: 186.01864325959045 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 713.9323817012839,
            "unit": "ns/iter",
            "extra": "iterations: 970403\ncpu: 713.9332833884494 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1554.7153307050155,
            "unit": "ns/iter",
            "extra": "iterations: 466443\ncpu: 1554.687282261716 ns\nthreads: 1"
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
          "id": "b438b45e453562d882786dee0b7658f81e6fb6a0",
          "message": "Revise export header includes (#27)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T20:31:47-04:00",
          "tree_id": "f3cd03ea64e16143382a53be434e01fe8b715097",
          "url": "https://github.com/sourcemeta/blaze/commit/b438b45e453562d882786dee0b7658f81e6fb6a0"
        },
        "date": 1729211788629,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2748210917.0000515,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2747928000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 737.3695876792443,
            "unit": "ns/iter",
            "extra": "iterations: 951371\ncpu: 737.1603717161863 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 919.1957131964836,
            "unit": "ns/iter",
            "extra": "iterations: 762013\ncpu: 919.1693580030789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 148.55796558760616,
            "unit": "ns/iter",
            "extra": "iterations: 4690809\ncpu: 148.55902254813603 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.44125388527875,
            "unit": "ns/iter",
            "extra": "iterations: 6918432\ncpu: 101.43382199897313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2602.0673462909563,
            "unit": "ns/iter",
            "extra": "iterations: 267795\ncpu: 2601.807352639142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.3826494106241,
            "unit": "ns/iter",
            "extra": "iterations: 32864313\ncpu: 21.382373031805038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1264.8969399899056,
            "unit": "ns/iter",
            "extra": "iterations: 559606\ncpu: 1264.6540601780512 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 939.3828624471812,
            "unit": "ns/iter",
            "extra": "iterations: 745474\ncpu: 939.3486560228772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1310.3177050058496,
            "unit": "ns/iter",
            "extra": "iterations: 538424\ncpu: 1306.1156263465252 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 215.3750325455793,
            "unit": "ns/iter",
            "extra": "iterations: 3126382\ncpu: 214.37591439561817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1329.384947041762,
            "unit": "ns/iter",
            "extra": "iterations: 528813\ncpu: 1329.3602842592777 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.22926351518947,
            "unit": "ns/iter",
            "extra": "iterations: 6768517\ncpu: 104.21248849637243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 404.00700147091476,
            "unit": "ns/iter",
            "extra": "iterations: 1738349\ncpu: 403.97929299582506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 362.275538045932,
            "unit": "ns/iter",
            "extra": "iterations: 1933664\ncpu: 362.2211511410455 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 756.9670108042945,
            "unit": "ns/iter",
            "extra": "iterations: 924727\ncpu: 756.4783984894983 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 165.93921134318794,
            "unit": "ns/iter",
            "extra": "iterations: 4211312\ncpu: 165.93593635427706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 658.9543635036252,
            "unit": "ns/iter",
            "extra": "iterations: 1061475\ncpu: 658.9246096234028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1391.2400272698596,
            "unit": "ns/iter",
            "extra": "iterations: 500189\ncpu: 1391.1921293750936 ns\nthreads: 1"
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
          "id": "4437626506357ef03b1454fa2702d8eac2fb3fb4",
          "message": "Implement a new `AssertionArrayPrefix` step (#28)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-18T11:53:11-04:00",
          "tree_id": "9a6e9d74466e9280c5456cc0a9ae4d6de6d886aa",
          "url": "https://github.com/sourcemeta/blaze/commit/4437626506357ef03b1454fa2702d8eac2fb3fb4"
        },
        "date": 1729267038938,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2927750458.000105,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2924791000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 763.0601815119771,
            "unit": "ns/iter",
            "extra": "iterations: 925118\ncpu: 762.9134877929082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 990.3223881990226,
            "unit": "ns/iter",
            "extra": "iterations: 728817\ncpu: 990.0743259281833 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 153.9344939333159,
            "unit": "ns/iter",
            "extra": "iterations: 4550922\ncpu: 153.89694659675553 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 105.2831335861691,
            "unit": "ns/iter",
            "extra": "iterations: 6674104\ncpu: 105.27016060882478 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2707.4842114636963,
            "unit": "ns/iter",
            "extra": "iterations: 258257\ncpu: 2707.0205260651196 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.25877404849978,
            "unit": "ns/iter",
            "extra": "iterations: 31310945\ncpu: 22.248897310509136 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1312.2750672947434,
            "unit": "ns/iter",
            "extra": "iterations: 540904\ncpu: 1312.2402496561292 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1001.1167484635721,
            "unit": "ns/iter",
            "extra": "iterations: 709277\ncpu: 1001.0870224186019 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1372.5049412886497,
            "unit": "ns/iter",
            "extra": "iterations: 520512\ncpu: 1372.2238872494813 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 227.9482495408226,
            "unit": "ns/iter",
            "extra": "iterations: 2979104\ncpu: 227.90778703932435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1423.960891602066,
            "unit": "ns/iter",
            "extra": "iterations: 483579\ncpu: 1423.777707468686 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 112.19484943056119,
            "unit": "ns/iter",
            "extra": "iterations: 6284509\ncpu: 111.98265449218073 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 433.144163556415,
            "unit": "ns/iter",
            "extra": "iterations: 1593676\ncpu: 433.1281891676849 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 387.82120442963037,
            "unit": "ns/iter",
            "extra": "iterations: 1803227\ncpu: 387.80530681938654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 818.2562958311132,
            "unit": "ns/iter",
            "extra": "iterations: 856678\ncpu: 818.1300325209734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 179.81390701128004,
            "unit": "ns/iter",
            "extra": "iterations: 3939423\ncpu: 179.7522124432946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 716.2997629645968,
            "unit": "ns/iter",
            "extra": "iterations: 985929\ncpu: 715.2989718326581 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1534.715621502709,
            "unit": "ns/iter",
            "extra": "iterations: 462862\ncpu: 1533.992853161418 ns\nthreads: 1"
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
          "id": "f3aee3d5514dcf53470ab6bfe4e332a4225e0032",
          "message": "Get rid of `AnnotationWhenArraySizeEqual` (#29)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-18T13:52:57-04:00",
          "tree_id": "09f148f7208bb4d705ca217f745be07ef52c9e04",
          "url": "https://github.com/sourcemeta/blaze/commit/f3aee3d5514dcf53470ab6bfe4e332a4225e0032"
        },
        "date": 1729274172172,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2841628541.9999666,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2841322000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 732.7286570160577,
            "unit": "ns/iter",
            "extra": "iterations: 958418\ncpu: 732.7105709617299 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 917.6125107353145,
            "unit": "ns/iter",
            "extra": "iterations: 766158\ncpu: 917.5848845799427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 148.80526011404208,
            "unit": "ns/iter",
            "extra": "iterations: 4675488\ncpu: 148.77270565126022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.78230427927173,
            "unit": "ns/iter",
            "extra": "iterations: 6905873\ncpu: 101.77337463344595 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2618.330287129322,
            "unit": "ns/iter",
            "extra": "iterations: 271376\ncpu: 2610.743028123341 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.768108733156563,
            "unit": "ns/iter",
            "extra": "iterations: 32968637\ncpu: 21.765382657463217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1296.0146767788844,
            "unit": "ns/iter",
            "extra": "iterations: 557343\ncpu: 1291.786207057413 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1002.2008760757134,
            "unit": "ns/iter",
            "extra": "iterations: 682361\ncpu: 994.6978212412528 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1276.1080836201604,
            "unit": "ns/iter",
            "extra": "iterations: 548529\ncpu: 1275.9690007273973 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 214.70916984739557,
            "unit": "ns/iter",
            "extra": "iterations: 3270218\ncpu: 214.70464660154144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1329.993860147739,
            "unit": "ns/iter",
            "extra": "iterations: 531446\ncpu: 1329.9827263729517 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.25998265005707,
            "unit": "ns/iter",
            "extra": "iterations: 6719333\ncpu: 104.24546603063153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 402.8161979296797,
            "unit": "ns/iter",
            "extra": "iterations: 1741346\ncpu: 402.7637241536139 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 358.6217520494003,
            "unit": "ns/iter",
            "extra": "iterations: 1937491\ncpu: 358.59779477685396 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 758.5056850029483,
            "unit": "ns/iter",
            "extra": "iterations: 922339\ncpu: 758.4402264243423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 165.45943605706245,
            "unit": "ns/iter",
            "extra": "iterations: 4223406\ncpu: 165.45792661183924 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 674.2946571755685,
            "unit": "ns/iter",
            "extra": "iterations: 1060076\ncpu: 674.1761911410152 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1396.1871960811948,
            "unit": "ns/iter",
            "extra": "iterations: 499722\ncpu: 1395.9001204669823 ns\nthreads: 1"
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
          "id": "f3aee3d5514dcf53470ab6bfe4e332a4225e0032",
          "message": "Get rid of `AnnotationWhenArraySizeEqual` (#29)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-18T17:52:57Z",
          "url": "https://github.com/sourcemeta/blaze/commit/f3aee3d5514dcf53470ab6bfe4e332a4225e0032"
        },
        "date": 1729278279910,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2942244583.9999228,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2941756000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 738.7390842876838,
            "unit": "ns/iter",
            "extra": "iterations: 950648\ncpu: 738.7487271839836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 927.7877343720089,
            "unit": "ns/iter",
            "extra": "iterations: 756863\ncpu: 927.7200761564505 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 150.0548253357259,
            "unit": "ns/iter",
            "extra": "iterations: 4673022\ncpu: 150.04872649861267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.64711828552706,
            "unit": "ns/iter",
            "extra": "iterations: 6914946\ncpu: 101.64417769856769 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2585.5196926136778,
            "unit": "ns/iter",
            "extra": "iterations: 268197\ncpu: 2585.416689970428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.68671883214418,
            "unit": "ns/iter",
            "extra": "iterations: 32156261\ncpu: 21.686476546511397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1237.8777695149536,
            "unit": "ns/iter",
            "extra": "iterations: 566119\ncpu: 1237.6638127319534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 944.2625865707752,
            "unit": "ns/iter",
            "extra": "iterations: 733937\ncpu: 944.0401560351917 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1282.989286819199,
            "unit": "ns/iter",
            "extra": "iterations: 546243\ncpu: 1282.961978460135 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 214.13702724084214,
            "unit": "ns/iter",
            "extra": "iterations: 3329338\ncpu: 214.11643996494197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1360.378127289237,
            "unit": "ns/iter",
            "extra": "iterations: 516022\ncpu: 1360.3470394673097 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.52228173107139,
            "unit": "ns/iter",
            "extra": "iterations: 6727664\ncpu: 104.51502928802648 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 402.5294984318633,
            "unit": "ns/iter",
            "extra": "iterations: 1739584\ncpu: 402.4588637283395 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 363.54745473870014,
            "unit": "ns/iter",
            "extra": "iterations: 1945812\ncpu: 362.82796076907994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 790.0495969710045,
            "unit": "ns/iter",
            "extra": "iterations: 920157\ncpu: 790.0380043840354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 175.3080717298412,
            "unit": "ns/iter",
            "extra": "iterations: 3913238\ncpu: 175.20069057900372 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 704.7847833036749,
            "unit": "ns/iter",
            "extra": "iterations: 1007078\ncpu: 704.7438232192566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1492.444072238672,
            "unit": "ns/iter",
            "extra": "iterations: 473155\ncpu: 1492.390442878127 ns\nthreads: 1"
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
          "id": "f4b310df1e2aa819d2e016a111abb70f7597386e",
          "message": "Remove unused annotation related evaluate macros (#30)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-18T15:27:51-04:00",
          "tree_id": "897b42d0a8b1d53957e7c09329042e3b95a10020",
          "url": "https://github.com/sourcemeta/blaze/commit/f4b310df1e2aa819d2e016a111abb70f7597386e"
        },
        "date": 1729279926890,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3140230125.000016,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3126499999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 804.4576725882145,
            "unit": "ns/iter",
            "extra": "iterations: 880824\ncpu: 804.3627330772088 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 991.3707879502325,
            "unit": "ns/iter",
            "extra": "iterations: 689866\ncpu: 991.2359791611689 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 158.27547628578904,
            "unit": "ns/iter",
            "extra": "iterations: 4303561\ncpu: 158.27148726368694 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 108.27386416779575,
            "unit": "ns/iter",
            "extra": "iterations: 6398128\ncpu: 108.2651050432252 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2703.015406783288,
            "unit": "ns/iter",
            "extra": "iterations: 263715\ncpu: 2702.5235576285045 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.22036007704813,
            "unit": "ns/iter",
            "extra": "iterations: 31645283\ncpu: 22.213926795977777 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1271.448292908972,
            "unit": "ns/iter",
            "extra": "iterations: 544142\ncpu: 1271.449364320342 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 971.1973042325523,
            "unit": "ns/iter",
            "extra": "iterations: 697983\ncpu: 970.920495198309 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1312.2212700869272,
            "unit": "ns/iter",
            "extra": "iterations: 542640\ncpu: 1311.9379330679667 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 229.14597243642666,
            "unit": "ns/iter",
            "extra": "iterations: 3292971\ncpu: 229.11802138555117 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2176.1126020686274,
            "unit": "ns/iter",
            "extra": "iterations: 272979\ncpu: 2171.1340432780567 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 109.27036593511261,
            "unit": "ns/iter",
            "extra": "iterations: 5757715\ncpu: 109.26713114490744 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 471.15715347799903,
            "unit": "ns/iter",
            "extra": "iterations: 1674605\ncpu: 471.0531737335076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 404.8545451600991,
            "unit": "ns/iter",
            "extra": "iterations: 1605928\ncpu: 404.7597401626971 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 809.1560086531965,
            "unit": "ns/iter",
            "extra": "iterations: 867657\ncpu: 809.144627427662 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 171.2888973055839,
            "unit": "ns/iter",
            "extra": "iterations: 4100329\ncpu: 171.27942660210914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 678.3461034649923,
            "unit": "ns/iter",
            "extra": "iterations: 1024500\ncpu: 678.159102000975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1405.8034722826937,
            "unit": "ns/iter",
            "extra": "iterations: 490801\ncpu: 1404.6079775713565 ns\nthreads: 1"
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
          "id": "0c62572d89bad784571127aba64405c1321a9ccc",
          "message": "Fix description for `items` emitting the `true` annotation (#31)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-18T15:37:31-04:00",
          "tree_id": "e6ca1370c441f1d0f12ceb5b4cd04848787e29b7",
          "url": "https://github.com/sourcemeta/blaze/commit/0c62572d89bad784571127aba64405c1321a9ccc"
        },
        "date": 1729280511057,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3183038791.000058,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3182415000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 769.9845561066066,
            "unit": "ns/iter",
            "extra": "iterations: 885269\ncpu: 769.5999746969574 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 988.117107824663,
            "unit": "ns/iter",
            "extra": "iterations: 757174\ncpu: 987.5127777763092 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 157.42710556957132,
            "unit": "ns/iter",
            "extra": "iterations: 4122400\ncpu: 157.34086939646798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.1009574915483,
            "unit": "ns/iter",
            "extra": "iterations: 6762044\ncpu: 102.07875015306016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2778.8919680100594,
            "unit": "ns/iter",
            "extra": "iterations: 254582\ncpu: 2778.89638701872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.000962743812043,
            "unit": "ns/iter",
            "extra": "iterations: 30094195\ncpu: 22.99360391597123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1304.5915252255588,
            "unit": "ns/iter",
            "extra": "iterations: 530138\ncpu: 1304.32642066783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1000.4298837559636,
            "unit": "ns/iter",
            "extra": "iterations: 697670\ncpu: 1000.240801525075 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1292.5513674722558,
            "unit": "ns/iter",
            "extra": "iterations: 552918\ncpu: 1292.4936428186436 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 214.56912692034842,
            "unit": "ns/iter",
            "extra": "iterations: 3234138\ncpu: 214.55794403330987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1350.9842726664658,
            "unit": "ns/iter",
            "extra": "iterations: 516998\ncpu: 1350.968475700101 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 105.14613790930606,
            "unit": "ns/iter",
            "extra": "iterations: 6626152\ncpu: 104.87142462171101 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 406.58486754049414,
            "unit": "ns/iter",
            "extra": "iterations: 1737814\ncpu: 406.54868702864485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 367.5487336265419,
            "unit": "ns/iter",
            "extra": "iterations: 1890635\ncpu: 367.5204362555453 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 759.9576473699144,
            "unit": "ns/iter",
            "extra": "iterations: 907665\ncpu: 759.850826020616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 170.69793825584998,
            "unit": "ns/iter",
            "extra": "iterations: 4150903\ncpu: 170.64985618791957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 675.0116705096488,
            "unit": "ns/iter",
            "extra": "iterations: 1060365\ncpu: 674.914769914136 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1406.5538113979783,
            "unit": "ns/iter",
            "extra": "iterations: 497980\ncpu: 1406.2251496044055 ns\nthreads: 1"
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
          "id": "a033accb3a7c3712a94c5b9124932e88e7f7b3ab",
          "message": "Implement `ControlGroup` as a more efficient `LogicalAnd` alternative (#32)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-18T15:54:44-04:00",
          "tree_id": "f86f4468f24d3f5f0dee414fdaac3dfcbad522d8",
          "url": "https://github.com/sourcemeta/blaze/commit/a033accb3a7c3712a94c5b9124932e88e7f7b3ab"
        },
        "date": 1729281475830,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2807597083.0000186,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2807298000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 724.0591729922598,
            "unit": "ns/iter",
            "extra": "iterations: 971575\ncpu: 724.0388029745502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 920.691639801543,
            "unit": "ns/iter",
            "extra": "iterations: 754384\ncpu: 920.5643279815056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.6905133545627,
            "unit": "ns/iter",
            "extra": "iterations: 4448738\ncpu: 149.6350200888432 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 103.09332669350603,
            "unit": "ns/iter",
            "extra": "iterations: 6867660\ncpu: 103.07688499430665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2612.3692125108305,
            "unit": "ns/iter",
            "extra": "iterations: 268791\ncpu: 2612.293566376845 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.929842782622288,
            "unit": "ns/iter",
            "extra": "iterations: 32097724\ncpu: 21.91563489049886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1265.285534421466,
            "unit": "ns/iter",
            "extra": "iterations: 555975\ncpu: 1265.2151625522708 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 946.9218506596945,
            "unit": "ns/iter",
            "extra": "iterations: 745291\ncpu: 946.8878599097515 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1292.467260528319,
            "unit": "ns/iter",
            "extra": "iterations: 544908\ncpu: 1292.27502624296 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.81619789631648,
            "unit": "ns/iter",
            "extra": "iterations: 3328531\ncpu: 210.78487777340806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1371.6768205214962,
            "unit": "ns/iter",
            "extra": "iterations: 523545\ncpu: 1371.6624167932093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 103.96278798263411,
            "unit": "ns/iter",
            "extra": "iterations: 6722237\ncpu: 103.95854832253009 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 402.0268306258552,
            "unit": "ns/iter",
            "extra": "iterations: 1737343\ncpu: 402.0098506742762 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 279.8523808303477,
            "unit": "ns/iter",
            "extra": "iterations: 2536195\ncpu: 279.54238534497597 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 759.1110232805942,
            "unit": "ns/iter",
            "extra": "iterations: 922230\ncpu: 758.9278162714313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 167.27997654745374,
            "unit": "ns/iter",
            "extra": "iterations: 4188883\ncpu: 167.27442614176562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 663.4562775041189,
            "unit": "ns/iter",
            "extra": "iterations: 1059386\ncpu: 663.4239078107519 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1400.0634467246582,
            "unit": "ns/iter",
            "extra": "iterations: 502390\ncpu: 1398.630545990166 ns\nthreads: 1"
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
          "id": "1e8709cf97ac769bc3c2dd0641fe806b2a69d10b",
          "message": "Fix `unevaluatedProperties` on object with many optional properties (#33)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-18T17:19:36-04:00",
          "tree_id": "e8c65c76e39a7acd68b87c31db6ddffc332aaa2d",
          "url": "https://github.com/sourcemeta/blaze/commit/1e8709cf97ac769bc3c2dd0641fe806b2a69d10b"
        },
        "date": 1729286567560,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2814675792.0001163,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2807519000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 722.6884128056693,
            "unit": "ns/iter",
            "extra": "iterations: 966731\ncpu: 722.6043232295233 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 931.5284012434242,
            "unit": "ns/iter",
            "extra": "iterations: 753717\ncpu: 931.4702998605579 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.21696836802667,
            "unit": "ns/iter",
            "extra": "iterations: 4668192\ncpu: 149.21258594333733 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.8233476173859,
            "unit": "ns/iter",
            "extra": "iterations: 6883666\ncpu: 101.82408617733626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2691.701350295706,
            "unit": "ns/iter",
            "extra": "iterations: 263794\ncpu: 2690.989939119161 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.779721904164667,
            "unit": "ns/iter",
            "extra": "iterations: 31985232\ncpu: 21.778238156909453 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1283.0493425682466,
            "unit": "ns/iter",
            "extra": "iterations: 554126\ncpu: 1282.7732320807932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 961.9012315117918,
            "unit": "ns/iter",
            "extra": "iterations: 739254\ncpu: 961.8439670262192 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1311.8496283320833,
            "unit": "ns/iter",
            "extra": "iterations: 531523\ncpu: 1311.8341068965965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 216.5701266331855,
            "unit": "ns/iter",
            "extra": "iterations: 3294319\ncpu: 216.55947708767744 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1378.3054132315303,
            "unit": "ns/iter",
            "extra": "iterations: 506278\ncpu: 1378.2329076120254 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.81251650762266,
            "unit": "ns/iter",
            "extra": "iterations: 6640862\ncpu: 104.80823122058543 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 402.4702763273034,
            "unit": "ns/iter",
            "extra": "iterations: 1734863\ncpu: 402.4340826912562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 277.4734663524226,
            "unit": "ns/iter",
            "extra": "iterations: 2519989\ncpu: 277.46867149023205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 759.372976707902,
            "unit": "ns/iter",
            "extra": "iterations: 918985\ncpu: 757.7860356806711 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 166.64689514764768,
            "unit": "ns/iter",
            "extra": "iterations: 4193726\ncpu: 166.63964217023275 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 691.1909389385719,
            "unit": "ns/iter",
            "extra": "iterations: 1060847\ncpu: 691.1383074090821 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1410.6461694134975,
            "unit": "ns/iter",
            "extra": "iterations: 463493\ncpu: 1410.1291713143448 ns\nthreads: 1"
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
          "id": "e803728a9e9573a7ed02607c55b49371cc8f7c44",
          "message": "Split utilities for compiler output handling into a separate header (#35)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T13:43:09-04:00",
          "tree_id": "2a007a69bcd8e25786d360ce35bd32e4875441e3",
          "url": "https://github.com/sourcemeta/blaze/commit/e803728a9e9573a7ed02607c55b49371cc8f7c44"
        },
        "date": 1729359973806,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3023689707.9998927,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3017617000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 785.4928582302938,
            "unit": "ns/iter",
            "extra": "iterations: 965517\ncpu: 770.1728711146457 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 955.6619617713161,
            "unit": "ns/iter",
            "extra": "iterations: 711245\ncpu: 951.6327004056268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 163.20866879574797,
            "unit": "ns/iter",
            "extra": "iterations: 4305996\ncpu: 162.5164073538387 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 110.78379232931829,
            "unit": "ns/iter",
            "extra": "iterations: 6394972\ncpu: 110.4103348693318 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2783.1177681421045,
            "unit": "ns/iter",
            "extra": "iterations: 251163\ncpu: 2781.329256299696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.62914882061052,
            "unit": "ns/iter",
            "extra": "iterations: 29981412\ncpu: 22.593098683944607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1297.9780667148661,
            "unit": "ns/iter",
            "extra": "iterations: 565214\ncpu: 1293.697608339499 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1008.6218142692491,
            "unit": "ns/iter",
            "extra": "iterations: 743550\ncpu: 1005.6526124672173 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1377.1623082310823,
            "unit": "ns/iter",
            "extra": "iterations: 512531\ncpu: 1376.2504121701897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 226.5203457199106,
            "unit": "ns/iter",
            "extra": "iterations: 3101586\ncpu: 226.40578078441132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1430.2762108909756,
            "unit": "ns/iter",
            "extra": "iterations: 496845\ncpu: 1429.2847870060095 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 112.05008291959531,
            "unit": "ns/iter",
            "extra": "iterations: 6217469\ncpu: 111.9989500550788 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 433.7933304040979,
            "unit": "ns/iter",
            "extra": "iterations: 1613561\ncpu: 433.57146088682185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 294.3021553947085,
            "unit": "ns/iter",
            "extra": "iterations: 2389168\ncpu: 293.9810009174735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 812.5249697448785,
            "unit": "ns/iter",
            "extra": "iterations: 859360\ncpu: 812.0031185998929 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 177.1094662126678,
            "unit": "ns/iter",
            "extra": "iterations: 3925065\ncpu: 176.98407542295456 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 713.0747454811853,
            "unit": "ns/iter",
            "extra": "iterations: 969771\ncpu: 712.7022771355279 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1499.7052069753393,
            "unit": "ns/iter",
            "extra": "iterations: 467277\ncpu: 1497.4972018738374 ns\nthreads: 1"
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
          "id": "7cd1451d81e7ff7e1200fdd158f84f799b76e680",
          "message": "Better report the execution of `if` (#36)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T14:03:54-04:00",
          "tree_id": "ad3b6a2594b42756156fe929412e073b492ed839",
          "url": "https://github.com/sourcemeta/blaze/commit/7cd1451d81e7ff7e1200fdd158f84f799b76e680"
        },
        "date": 1729361244121,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2772564750.0001287,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2772311000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 725.5170673175393,
            "unit": "ns/iter",
            "extra": "iterations: 979240\ncpu: 725.4237980474657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 918.6122878885644,
            "unit": "ns/iter",
            "extra": "iterations: 763809\ncpu: 918.5909042705707 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.23436268749572,
            "unit": "ns/iter",
            "extra": "iterations: 4599000\ncpu: 151.22048271363343 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 103.42780928162068,
            "unit": "ns/iter",
            "extra": "iterations: 6771660\ncpu: 103.42368045649076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2876.3248741491275,
            "unit": "ns/iter",
            "extra": "iterations: 269963\ncpu: 2876.201553546228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.646474118961603,
            "unit": "ns/iter",
            "extra": "iterations: 28894934\ncpu: 22.644350044198035 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1301.4061724714352,
            "unit": "ns/iter",
            "extra": "iterations: 556244\ncpu: 1301.2580809860428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 954.5761012740808,
            "unit": "ns/iter",
            "extra": "iterations: 740960\ncpu: 954.5265601381975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1278.5623536287324,
            "unit": "ns/iter",
            "extra": "iterations: 540153\ncpu: 1278.4340733088588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 218.51094779981392,
            "unit": "ns/iter",
            "extra": "iterations: 3176346\ncpu: 218.50705181362468 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1450.3095095399651,
            "unit": "ns/iter",
            "extra": "iterations: 490560\ncpu: 1450.0795009784708 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 108.53768500898018,
            "unit": "ns/iter",
            "extra": "iterations: 6274763\ncpu: 108.52425820704295 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 427.4624684349725,
            "unit": "ns/iter",
            "extra": "iterations: 1679866\ncpu: 426.6786755610281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 289.34131038698393,
            "unit": "ns/iter",
            "extra": "iterations: 2389813\ncpu: 289.25777874670587 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 802.5781526987973,
            "unit": "ns/iter",
            "extra": "iterations: 852920\ncpu: 802.516062467761 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 193.19617277683224,
            "unit": "ns/iter",
            "extra": "iterations: 3434605\ncpu: 193.19193910216825 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 681.1276161563621,
            "unit": "ns/iter",
            "extra": "iterations: 1057993\ncpu: 681.1028050280102 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1466.535734188472,
            "unit": "ns/iter",
            "extra": "iterations: 482689\ncpu: 1466.4183356156836 ns\nthreads: 1"
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
          "id": "5e631d57f77a8429b7d55a1bff6ff0b62415aeae",
          "message": "Fix failed `if` incorrectly showing up on error traces (#34)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T14:22:28-04:00",
          "tree_id": "fd4856558b2355016002438323f4b429e0a50ac0",
          "url": "https://github.com/sourcemeta/blaze/commit/5e631d57f77a8429b7d55a1bff6ff0b62415aeae"
        },
        "date": 1729362369541,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2975161332.99996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2974681000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 748.8703459669783,
            "unit": "ns/iter",
            "extra": "iterations: 944020\ncpu: 748.7637973771741 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 955.8971154485754,
            "unit": "ns/iter",
            "extra": "iterations: 691338\ncpu: 955.6917166422229 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 157.61974671593504,
            "unit": "ns/iter",
            "extra": "iterations: 4362295\ncpu: 157.61107398743118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 105.6334360610805,
            "unit": "ns/iter",
            "extra": "iterations: 6638910\ncpu: 105.61703653159921 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2761.672386670646,
            "unit": "ns/iter",
            "extra": "iterations: 244755\ncpu: 2759.8905027476458 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.045022856684106,
            "unit": "ns/iter",
            "extra": "iterations: 30323509\ncpu: 23.041660514948955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1386.237626234333,
            "unit": "ns/iter",
            "extra": "iterations: 512738\ncpu: 1386.107524700722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1015.1116470237197,
            "unit": "ns/iter",
            "extra": "iterations: 705339\ncpu: 1014.5405259031503 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1339.3865332295263,
            "unit": "ns/iter",
            "extra": "iterations: 492219\ncpu: 1339.1742293572577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 218.64334794035312,
            "unit": "ns/iter",
            "extra": "iterations: 3176317\ncpu: 218.57043865583975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1390.1396363425583,
            "unit": "ns/iter",
            "extra": "iterations: 497392\ncpu: 1389.7730562614597 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 107.73436929990653,
            "unit": "ns/iter",
            "extra": "iterations: 6436308\ncpu: 107.73319114001342 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 417.29179427204724,
            "unit": "ns/iter",
            "extra": "iterations: 1679656\ncpu: 417.27115552232146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 283.6313711995494,
            "unit": "ns/iter",
            "extra": "iterations: 2423739\ncpu: 281.87399715893446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 784.9077020690032,
            "unit": "ns/iter",
            "extra": "iterations: 885762\ncpu: 784.7740137869979 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 195.03407809096524,
            "unit": "ns/iter",
            "extra": "iterations: 3601082\ncpu: 194.99528197358424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 687.779892082296,
            "unit": "ns/iter",
            "extra": "iterations: 1020036\ncpu: 687.6316130018957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1491.3428049658419,
            "unit": "ns/iter",
            "extra": "iterations: 487350\ncpu: 1486.0634041243493 ns\nthreads: 1"
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
          "id": "bfb48266713d223adc8d9145274151a680a468d4",
          "message": "Reduce unnecessary instructions in array/object `items` (#37)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T14:41:21-04:00",
          "tree_id": "fc7db4361a4c3f6a0ad4652e809f8327533e191b",
          "url": "https://github.com/sourcemeta/blaze/commit/bfb48266713d223adc8d9145274151a680a468d4"
        },
        "date": 1729363471442,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2786271750.0001965,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2784674000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 720.8496763661456,
            "unit": "ns/iter",
            "extra": "iterations: 960654\ncpu: 720.8214403937315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 934.9765079061575,
            "unit": "ns/iter",
            "extra": "iterations: 739270\ncpu: 934.8330109432274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.69334380453685,
            "unit": "ns/iter",
            "extra": "iterations: 4689646\ncpu: 149.69402807802547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.5529391437375,
            "unit": "ns/iter",
            "extra": "iterations: 6904579\ncpu: 101.53450340708693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2674.792930676271,
            "unit": "ns/iter",
            "extra": "iterations: 270040\ncpu: 2673.9779291956756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.84831097607802,
            "unit": "ns/iter",
            "extra": "iterations: 32994589\ncpu: 21.847491417456396 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1281.249227044081,
            "unit": "ns/iter",
            "extra": "iterations: 553395\ncpu: 1280.8229203371902 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 949.3043284272933,
            "unit": "ns/iter",
            "extra": "iterations: 735140\ncpu: 949.2912914546897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1293.8138819507676,
            "unit": "ns/iter",
            "extra": "iterations: 553294\ncpu: 1293.7118421670957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.48424828450246,
            "unit": "ns/iter",
            "extra": "iterations: 3264819\ncpu: 211.475429418905 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1341.2691530158306,
            "unit": "ns/iter",
            "extra": "iterations: 519396\ncpu: 1341.2136404593 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.7256794213543,
            "unit": "ns/iter",
            "extra": "iterations: 6722044\ncpu: 104.72156980823078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 403.6352273576586,
            "unit": "ns/iter",
            "extra": "iterations: 1716768\ncpu: 403.57054651531297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 274.6834351714686,
            "unit": "ns/iter",
            "extra": "iterations: 2532287\ncpu: 274.6750269617938 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 760.5183627173933,
            "unit": "ns/iter",
            "extra": "iterations: 924019\ncpu: 760.0438952012923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 190.08177387398976,
            "unit": "ns/iter",
            "extra": "iterations: 3635929\ncpu: 190.07466867477243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 670.5218235630159,
            "unit": "ns/iter",
            "extra": "iterations: 1046369\ncpu: 670.3084667072548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1293.0725707819627,
            "unit": "ns/iter",
            "extra": "iterations: 542119\ncpu: 1292.9541299972907 ns\nthreads: 1"
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
          "id": "3acabcf5bd565c27aedd0d4894985269340611d1",
          "message": "Implement pass through evaluator helper macros (#38)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T14:41:40-04:00",
          "tree_id": "c8e84de9f379cc0d22d20074cfad7597d95f8cbf",
          "url": "https://github.com/sourcemeta/blaze/commit/3acabcf5bd565c27aedd0d4894985269340611d1"
        },
        "date": 1729363492510,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2794453166.0000396,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2793965999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 719.0303895564097,
            "unit": "ns/iter",
            "extra": "iterations: 976059\ncpu: 718.784417745238 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 939.1604178173649,
            "unit": "ns/iter",
            "extra": "iterations: 747791\ncpu: 939.1541219404896 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.5580739575027,
            "unit": "ns/iter",
            "extra": "iterations: 4673334\ncpu: 151.54833786756956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 102.11118077869007,
            "unit": "ns/iter",
            "extra": "iterations: 6913785\ncpu: 102.10514211824623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2582.6852319448467,
            "unit": "ns/iter",
            "extra": "iterations: 269697\ncpu: 2582.290496371852 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.295250398178542,
            "unit": "ns/iter",
            "extra": "iterations: 32285738\ncpu: 21.29488258871451 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1247.7174353522614,
            "unit": "ns/iter",
            "extra": "iterations: 565099\ncpu: 1247.7017301393223 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 965.5236498659837,
            "unit": "ns/iter",
            "extra": "iterations: 738186\ncpu: 965.4870181769934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1291.805040683859,
            "unit": "ns/iter",
            "extra": "iterations: 537189\ncpu: 1291.7390341202113 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 212.13621261258436,
            "unit": "ns/iter",
            "extra": "iterations: 3320368\ncpu: 212.12859538460796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1342.2152100669057,
            "unit": "ns/iter",
            "extra": "iterations: 520287\ncpu: 1342.138089170016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.39634829933412,
            "unit": "ns/iter",
            "extra": "iterations: 6610509\ncpu: 104.35777335754287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 405.52527695392325,
            "unit": "ns/iter",
            "extra": "iterations: 1731696\ncpu: 405.5122839112645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 273.82555836002547,
            "unit": "ns/iter",
            "extra": "iterations: 2549162\ncpu: 273.82292690696084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 763.9371373254503,
            "unit": "ns/iter",
            "extra": "iterations: 921453\ncpu: 762.6118749409869 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 187.59739670771006,
            "unit": "ns/iter",
            "extra": "iterations: 3728740\ncpu: 187.59715078015668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 666.1695851383728,
            "unit": "ns/iter",
            "extra": "iterations: 1057003\ncpu: 665.9905411810524 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1287.5551077728196,
            "unit": "ns/iter",
            "extra": "iterations: 536222\ncpu: 1287.4723528687725 ns\nthreads: 1"
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
          "id": "a32600c946ac616f2f8e678dd05fb827fbb38f91",
          "message": "Short-circuit `patternProperties` wrapper when possible (#39)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T15:30:18-04:00",
          "tree_id": "fe84e68665c79d1cc71b085299bcdf22f4d63744",
          "url": "https://github.com/sourcemeta/blaze/commit/a32600c946ac616f2f8e678dd05fb827fbb38f91"
        },
        "date": 1729366410813,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2766938207.999829,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2766419000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 714.9626877300701,
            "unit": "ns/iter",
            "extra": "iterations: 981795\ncpu: 714.8610453302379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 925.0956714204104,
            "unit": "ns/iter",
            "extra": "iterations: 758586\ncpu: 925.0038888141885 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.4913866670284,
            "unit": "ns/iter",
            "extra": "iterations: 4690809\ncpu: 149.47272421452246 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.69232443925047,
            "unit": "ns/iter",
            "extra": "iterations: 6926647\ncpu: 101.68787293476913 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2591.704940748565,
            "unit": "ns/iter",
            "extra": "iterations: 270627\ncpu: 2591.0348930446726 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.485737559313023,
            "unit": "ns/iter",
            "extra": "iterations: 32532265\ncpu: 21.484240338015198 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1238.5870103612262,
            "unit": "ns/iter",
            "extra": "iterations: 569731\ncpu: 1238.5353789770957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 907.4139276048943,
            "unit": "ns/iter",
            "extra": "iterations: 769637\ncpu: 907.4147942471584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1248.8982733183336,
            "unit": "ns/iter",
            "extra": "iterations: 564493\ncpu: 1248.8392238699134 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.72923360075757,
            "unit": "ns/iter",
            "extra": "iterations: 3324168\ncpu: 210.70204634663486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1342.7184937834404,
            "unit": "ns/iter",
            "extra": "iterations: 530070\ncpu: 1342.5396645726055 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 103.9089779803706,
            "unit": "ns/iter",
            "extra": "iterations: 6741984\ncpu: 103.90383602215618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 402.75210828886895,
            "unit": "ns/iter",
            "extra": "iterations: 1736835\ncpu: 402.5598286538456 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 272.3681291577287,
            "unit": "ns/iter",
            "extra": "iterations: 2546158\ncpu: 272.36919311370394 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 755.721496231894,
            "unit": "ns/iter",
            "extra": "iterations: 925632\ncpu: 755.6534346262866 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 189.00597342427957,
            "unit": "ns/iter",
            "extra": "iterations: 3723325\ncpu: 188.98645699744202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 671.5177846089889,
            "unit": "ns/iter",
            "extra": "iterations: 1063054\ncpu: 671.424969945081 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1290.3404483731754,
            "unit": "ns/iter",
            "extra": "iterations: 541201\ncpu: 1290.1251106335717 ns\nthreads: 1"
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
          "id": "e59009eb70e13d1a0e98f5c35648793dd45af8ee",
          "message": "Improve the instructions emitted for `dependencies` (#40)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T15:57:40-04:00",
          "tree_id": "2eec3e45487155a3e945e1dbda6a9af8c65b1a63",
          "url": "https://github.com/sourcemeta/blaze/commit/e59009eb70e13d1a0e98f5c35648793dd45af8ee"
        },
        "date": 1729368052177,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2807136792.000165,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2806775000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 679.4801392059135,
            "unit": "ns/iter",
            "extra": "iterations: 1036162\ncpu: 679.3638446497755 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 919.6230074390048,
            "unit": "ns/iter",
            "extra": "iterations: 764092\ncpu: 919.4246242599065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 148.84139758804773,
            "unit": "ns/iter",
            "extra": "iterations: 4699153\ncpu: 148.84022716434225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.42678128995205,
            "unit": "ns/iter",
            "extra": "iterations: 6887256\ncpu: 101.40206781917206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2583.9946782602983,
            "unit": "ns/iter",
            "extra": "iterations: 269085\ncpu: 2583.50335395878 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.438585644247944,
            "unit": "ns/iter",
            "extra": "iterations: 33111330\ncpu: 21.43767707307444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1222.4760005769026,
            "unit": "ns/iter",
            "extra": "iterations: 575743\ncpu: 1222.4204202222159 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 907.7779524631076,
            "unit": "ns/iter",
            "extra": "iterations: 769637\ncpu: 907.6642625029705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1244.7232962800747,
            "unit": "ns/iter",
            "extra": "iterations: 563957\ncpu: 1244.6338993930378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.6124990643534,
            "unit": "ns/iter",
            "extra": "iterations: 3326601\ncpu: 210.5882250381099 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1338.7188891353799,
            "unit": "ns/iter",
            "extra": "iterations: 531406\ncpu: 1338.6713736766237 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 103.78885394969475,
            "unit": "ns/iter",
            "extra": "iterations: 6746013\ncpu: 103.7855989900998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 401.95499265215614,
            "unit": "ns/iter",
            "extra": "iterations: 1739316\ncpu: 401.93213884078597 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 276.53650416882476,
            "unit": "ns/iter",
            "extra": "iterations: 2521123\ncpu: 276.51883704206375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 759.634431405188,
            "unit": "ns/iter",
            "extra": "iterations: 925167\ncpu: 758.3171470664179 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 189.42824440032462,
            "unit": "ns/iter",
            "extra": "iterations: 3709160\ncpu: 189.4256381498776 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 665.6902852172904,
            "unit": "ns/iter",
            "extra": "iterations: 1064347\ncpu: 665.6428777456975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1299.9187930372636,
            "unit": "ns/iter",
            "extra": "iterations: 537614\ncpu: 1299.8564025490386 ns\nthreads: 1"
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
          "id": "0dbc880eaf13f4213f99829907d4882428ba253b",
          "message": "Use an efficient `ControlGroup` variant for `properties` (#41)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T16:08:19-04:00",
          "tree_id": "50f16cee8cfa8fb759fb3c95a1518ca3a3bd9b92",
          "url": "https://github.com/sourcemeta/blaze/commit/0dbc880eaf13f4213f99829907d4882428ba253b"
        },
        "date": 1729368699710,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3169310582.9999695,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3168927000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 694.7297222385334,
            "unit": "ns/iter",
            "extra": "iterations: 1017383\ncpu: 694.6390887207668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 926.0748770534402,
            "unit": "ns/iter",
            "extra": "iterations: 759071\ncpu: 926.056982811885 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 151.86938881216537,
            "unit": "ns/iter",
            "extra": "iterations: 4699406\ncpu: 151.7902475334115 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.65468314156618,
            "unit": "ns/iter",
            "extra": "iterations: 6893631\ncpu: 101.65005930836745 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2684.928876997332,
            "unit": "ns/iter",
            "extra": "iterations: 262742\ncpu: 2684.386203956728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.310579007942223,
            "unit": "ns/iter",
            "extra": "iterations: 29805498\ncpu: 23.2925817914534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1400.1514074834975,
            "unit": "ns/iter",
            "extra": "iterations: 535033\ncpu: 1373.2124934349883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1076.4592844482938,
            "unit": "ns/iter",
            "extra": "iterations: 651078\ncpu: 1053.07658990167 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1322.1346717324775,
            "unit": "ns/iter",
            "extra": "iterations: 496912\ncpu: 1321.8215700164253 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 224.743173099719,
            "unit": "ns/iter",
            "extra": "iterations: 3174574\ncpu: 224.73188528602532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1351.217299574014,
            "unit": "ns/iter",
            "extra": "iterations: 516163\ncpu: 1350.8600965198955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 103.98017805424675,
            "unit": "ns/iter",
            "extra": "iterations: 6729410\ncpu: 103.97731747656913 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 404.0046788404347,
            "unit": "ns/iter",
            "extra": "iterations: 1730557\ncpu: 403.90001600640795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 277.81417454017765,
            "unit": "ns/iter",
            "extra": "iterations: 2515877\ncpu: 277.7667588677816 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 759.6736610018971,
            "unit": "ns/iter",
            "extra": "iterations: 921174\ncpu: 759.6729825201332 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 187.4926742975751,
            "unit": "ns/iter",
            "extra": "iterations: 3694185\ncpu: 187.39180631181193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 663.1370503416878,
            "unit": "ns/iter",
            "extra": "iterations: 1081515\ncpu: 661.6292885443124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1366.416569491287,
            "unit": "ns/iter",
            "extra": "iterations: 511965\ncpu: 1364.0873887863409 ns\nthreads: 1"
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
          "id": "f1e6d1276de57ed62bbd21d85fbb0658444b5ca0",
          "message": "Fix JSON Schema test suite GoogleTest test names (#42)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T16:09:56-04:00",
          "tree_id": "e9534fed9cb8a8680fda1bff5e2a769c029caab8",
          "url": "https://github.com/sourcemeta/blaze/commit/f1e6d1276de57ed62bbd21d85fbb0658444b5ca0"
        },
        "date": 1729369003945,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2747671208.9999185,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2747302000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 720.8655962164831,
            "unit": "ns/iter",
            "extra": "iterations: 1022062\ncpu: 720.7879756805362 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 944.9350864065466,
            "unit": "ns/iter",
            "extra": "iterations: 714935\ncpu: 944.6746907061466 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 150.33299851309937,
            "unit": "ns/iter",
            "extra": "iterations: 4423269\ncpu: 150.2902039193186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.47720140809169,
            "unit": "ns/iter",
            "extra": "iterations: 6839611\ncpu: 101.46044855474982 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2586.665151037225,
            "unit": "ns/iter",
            "extra": "iterations: 269635\ncpu: 2586.5633170767874 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.324793260776257,
            "unit": "ns/iter",
            "extra": "iterations: 33012483\ncpu: 21.323721696426215 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1225.3337248853702,
            "unit": "ns/iter",
            "extra": "iterations: 579744\ncpu: 1224.6836534746408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 905.6947992548261,
            "unit": "ns/iter",
            "extra": "iterations: 740067\ncpu: 905.558550779861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1242.1484406700233,
            "unit": "ns/iter",
            "extra": "iterations: 556970\ncpu: 1242.0651022496734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.88066728843089,
            "unit": "ns/iter",
            "extra": "iterations: 3323900\ncpu: 210.87577845302195 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1327.0696273483254,
            "unit": "ns/iter",
            "extra": "iterations: 529878\ncpu: 1327.0583039869564 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.14426013906936,
            "unit": "ns/iter",
            "extra": "iterations: 6776314\ncpu: 104.1393595397144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 410.59539643789543,
            "unit": "ns/iter",
            "extra": "iterations: 1618703\ncpu: 410.5496808247105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 272.94837314885507,
            "unit": "ns/iter",
            "extra": "iterations: 2571317\ncpu: 272.9395092087053 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 781.7307533648756,
            "unit": "ns/iter",
            "extra": "iterations: 909055\ncpu: 781.6886767027308 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 187.8797977136081,
            "unit": "ns/iter",
            "extra": "iterations: 3704056\ncpu: 187.86514026785753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 642.0925713445315,
            "unit": "ns/iter",
            "extra": "iterations: 1086805\ncpu: 642.0986285488186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1304.6162956690357,
            "unit": "ns/iter",
            "extra": "iterations: 535897\ncpu: 1304.4950802113103 ns\nthreads: 1"
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
          "id": "d06c3b1c53ce8dfedadbcd37c75e254200b89752",
          "message": "Remove the unused `LogicalWhenArraySizeEqual` step (#44)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T16:26:45-04:00",
          "tree_id": "736fffe9cc811998807dd53cd7fe3a3f92ebbb67",
          "url": "https://github.com/sourcemeta/blaze/commit/d06c3b1c53ce8dfedadbcd37c75e254200b89752"
        },
        "date": 1729369789557,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2735400040.9995933,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2735051999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 690.5861419666901,
            "unit": "ns/iter",
            "extra": "iterations: 1017013\ncpu: 690.535912520292 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 921.9505915496846,
            "unit": "ns/iter",
            "extra": "iterations: 757502\ncpu: 921.8681930872795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.6998193464242,
            "unit": "ns/iter",
            "extra": "iterations: 4686318\ncpu: 149.68147701457735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 101.71733644314834,
            "unit": "ns/iter",
            "extra": "iterations: 6895261\ncpu: 101.69259727804352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2581.2818768823704,
            "unit": "ns/iter",
            "extra": "iterations: 269788\ncpu: 2581.167435171325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.40057045524083,
            "unit": "ns/iter",
            "extra": "iterations: 32617458\ncpu: 21.40047210300687 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1219.3156814524696,
            "unit": "ns/iter",
            "extra": "iterations: 574934\ncpu: 1219.2529925174065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 921.2616485190579,
            "unit": "ns/iter",
            "extra": "iterations: 760440\ncpu: 921.2232391773165 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1255.0874389180694,
            "unit": "ns/iter",
            "extra": "iterations: 555199\ncpu: 1254.951828083263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.78547666009277,
            "unit": "ns/iter",
            "extra": "iterations: 3321550\ncpu: 210.77569207147243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1331.8238365611965,
            "unit": "ns/iter",
            "extra": "iterations: 517281\ncpu: 1331.6978586106977 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 104.18607300421768,
            "unit": "ns/iter",
            "extra": "iterations: 6746078\ncpu: 104.16719166306696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 402.92711144175826,
            "unit": "ns/iter",
            "extra": "iterations: 1728049\ncpu: 402.90582037893637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 277.4959221490551,
            "unit": "ns/iter",
            "extra": "iterations: 2509410\ncpu: 277.4823564104719 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 775.1593029286483,
            "unit": "ns/iter",
            "extra": "iterations: 926907\ncpu: 772.7743991576332 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 194.0761607153178,
            "unit": "ns/iter",
            "extra": "iterations: 3458686\ncpu: 193.18348066288797 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 647.517171071267,
            "unit": "ns/iter",
            "extra": "iterations: 1087818\ncpu: 647.5127273128442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1290.7435229126609,
            "unit": "ns/iter",
            "extra": "iterations: 539054\ncpu: 1290.6851632675073 ns\nthreads: 1"
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
          "id": "1bf10d4240debf93f3878535afdbe577e45873f4",
          "message": "Don't pass a noop callback when running the JSON Schema test suite (#46)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T17:06:32-04:00",
          "tree_id": "6b0f6dfa01c6159342066e3a4ec3657439f6b546",
          "url": "https://github.com/sourcemeta/blaze/commit/1bf10d4240debf93f3878535afdbe577e45873f4"
        },
        "date": 1729372183337,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2765745000.0001516,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2765380000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 689.0419350736806,
            "unit": "ns/iter",
            "extra": "iterations: 1022390\ncpu: 688.8789992077391 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 922.6259029608912,
            "unit": "ns/iter",
            "extra": "iterations: 762353\ncpu: 922.5647436292633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 148.9049788213788,
            "unit": "ns/iter",
            "extra": "iterations: 4700731\ncpu: 148.89896911778186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 106.08791622586969,
            "unit": "ns/iter",
            "extra": "iterations: 6915356\ncpu: 105.97256309002749 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2916.819505557383,
            "unit": "ns/iter",
            "extra": "iterations: 251354\ncpu: 2869.439117738332 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.469480996889573,
            "unit": "ns/iter",
            "extra": "iterations: 30034926\ncpu: 23.45569288234637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1277.2480603973138,
            "unit": "ns/iter",
            "extra": "iterations: 531810\ncpu: 1273.5206182659208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1016.2951598241332,
            "unit": "ns/iter",
            "extra": "iterations: 676525\ncpu: 1010.6278408041084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1326.4808925131501,
            "unit": "ns/iter",
            "extra": "iterations: 561874\ncpu: 1322.52426700648 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 230.32824427224955,
            "unit": "ns/iter",
            "extra": "iterations: 3030487\ncpu: 229.96270896393824 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1442.0291661915041,
            "unit": "ns/iter",
            "extra": "iterations: 473082\ncpu: 1421.0179207832914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 112.94328119929617,
            "unit": "ns/iter",
            "extra": "iterations: 6163600\ncpu: 112.85093127393078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 442.1838984103244,
            "unit": "ns/iter",
            "extra": "iterations: 1586539\ncpu: 441.72629856561963 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 296.8247727468767,
            "unit": "ns/iter",
            "extra": "iterations: 2341662\ncpu: 296.28272568799446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 792.5196443659048,
            "unit": "ns/iter",
            "extra": "iterations: 817919\ncpu: 788.5573021289435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 200.6213136621576,
            "unit": "ns/iter",
            "extra": "iterations: 3434201\ncpu: 200.04915262676815 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 677.9097218405446,
            "unit": "ns/iter",
            "extra": "iterations: 1000829\ncpu: 676.5621299942364 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1470.2813957934309,
            "unit": "ns/iter",
            "extra": "iterations: 486777\ncpu: 1454.152517477199 ns\nthreads: 1"
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
          "id": "cc6aae9499aa1e9c243011e3982f8559bfb1f0ad",
          "message": "Avoid keeping track of the evaluate path when possible (#45)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T17:21:19-04:00",
          "tree_id": "2f5b72d97f95b96bf3c27e2d0751b188bc6ce413",
          "url": "https://github.com/sourcemeta/blaze/commit/cc6aae9499aa1e9c243011e3982f8559bfb1f0ad"
        },
        "date": 1729373156654,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3274792332.999823,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3177734000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 605.4754387902924,
            "unit": "ns/iter",
            "extra": "iterations: 1132375\ncpu: 605.2906501821393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 865.0598222229936,
            "unit": "ns/iter",
            "extra": "iterations: 797630\ncpu: 864.9837644020416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 116.71644865367936,
            "unit": "ns/iter",
            "extra": "iterations: 5837955\ncpu: 116.71107434024395 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 82.1650582234913,
            "unit": "ns/iter",
            "extra": "iterations: 8429165\ncpu: 82.14633359294783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2376.7487083615856,
            "unit": "ns/iter",
            "extra": "iterations: 298458\ncpu: 2376.3913180414006 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.45992870124162,
            "unit": "ns/iter",
            "extra": "iterations: 33042091\ncpu: 21.448914961223302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1204.0011413513769,
            "unit": "ns/iter",
            "extra": "iterations: 601918\ncpu: 1201.907901076226 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 866.4402132052181,
            "unit": "ns/iter",
            "extra": "iterations: 811425\ncpu: 865.9925439812678 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1226.5972718275636,
            "unit": "ns/iter",
            "extra": "iterations: 582368\ncpu: 1226.444447497113 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 196.83681700498167,
            "unit": "ns/iter",
            "extra": "iterations: 3585202\ncpu: 196.79560593796361 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1306.5865583671798,
            "unit": "ns/iter",
            "extra": "iterations: 537152\ncpu: 1306.2708507089262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.50902730841865,
            "unit": "ns/iter",
            "extra": "iterations: 8328673\ncpu: 82.50594062223361 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 386.58788701960805,
            "unit": "ns/iter",
            "extra": "iterations: 1783921\ncpu: 386.5754144942515 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 195.5016393653217,
            "unit": "ns/iter",
            "extra": "iterations: 3578824\ncpu: 195.20602298408542 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 749.7344903257119,
            "unit": "ns/iter",
            "extra": "iterations: 908159\ncpu: 733.5840970578947 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.06529090083409,
            "unit": "ns/iter",
            "extra": "iterations: 5571297\ncpu: 124.0248006882423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 657.9973579277072,
            "unit": "ns/iter",
            "extra": "iterations: 1088918\ncpu: 657.8208827478281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1090.8706118068617,
            "unit": "ns/iter",
            "extra": "iterations: 639842\ncpu: 1088.3093013587759 ns\nthreads: 1"
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
          "id": "3beca89972339446bb6046864d4bde1ac3bdf8d6",
          "message": "Rename the `evaluate_path` step property to `track` (#47)\n\nSo we can use it for more than just the evaluate path.\r\n\r\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T18:05:08-04:00",
          "tree_id": "6c1ce82e3229c5d628016b76db00811374d9564e",
          "url": "https://github.com/sourcemeta/blaze/commit/3beca89972339446bb6046864d4bde1ac3bdf8d6"
        },
        "date": 1729375700181,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2765676584.0001755,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2764865000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 567.6584310644707,
            "unit": "ns/iter",
            "extra": "iterations: 1229904\ncpu: 567.6077157241546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 798.0995030542615,
            "unit": "ns/iter",
            "extra": "iterations: 877963\ncpu: 797.9277031036604 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 115.0878139737811,
            "unit": "ns/iter",
            "extra": "iterations: 6105805\ncpu: 115.08425178989506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 81.59449365002278,
            "unit": "ns/iter",
            "extra": "iterations: 8638136\ncpu: 81.5858884370425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2323.4603906101847,
            "unit": "ns/iter",
            "extra": "iterations: 301835\ncpu: 2323.395232494575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.408655414118005,
            "unit": "ns/iter",
            "extra": "iterations: 32535289\ncpu: 21.407032837483012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1160.5457221031188,
            "unit": "ns/iter",
            "extra": "iterations: 603100\ncpu: 1160.5007461449197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 864.365948750626,
            "unit": "ns/iter",
            "extra": "iterations: 816669\ncpu: 864.3379386263002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1195.279461097531,
            "unit": "ns/iter",
            "extra": "iterations: 591721\ncpu: 1195.0767337985312 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 194.87607496021522,
            "unit": "ns/iter",
            "extra": "iterations: 3588621\ncpu: 194.84615399620097 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1315.377245985652,
            "unit": "ns/iter",
            "extra": "iterations: 540520\ncpu: 1315.2538296455248 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.35819171213288,
            "unit": "ns/iter",
            "extra": "iterations: 8505261\ncpu: 82.35408648835134 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 389.68598702663536,
            "unit": "ns/iter",
            "extra": "iterations: 1801709\ncpu: 389.6839056695616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 192.1659485709149,
            "unit": "ns/iter",
            "extra": "iterations: 3645985\ncpu: 192.14999513163056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 685.4212105506878,
            "unit": "ns/iter",
            "extra": "iterations: 1022510\ncpu: 685.4182355184786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.38758000431498,
            "unit": "ns/iter",
            "extra": "iterations: 5689068\ncpu: 123.38154509666614 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 648.6279894103251,
            "unit": "ns/iter",
            "extra": "iterations: 1091227\ncpu: 648.6056521695326 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1075.2882489309666,
            "unit": "ns/iter",
            "extra": "iterations: 653515\ncpu: 1075.2668263161513 ns\nthreads: 1"
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
          "id": "65b0c728bd038b5225c1be855936fd85c63aca7e",
          "message": "Always report `LogicalWhenArraySizeGreater` (#48)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T18:44:11-04:00",
          "tree_id": "0d5b6c479e6c0129a19000e218ff4d5f9a77d1d6",
          "url": "https://github.com/sourcemeta/blaze/commit/65b0c728bd038b5225c1be855936fd85c63aca7e"
        },
        "date": 1729378127854,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4164301249.9998803,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4092540000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 611.9284010772183,
            "unit": "ns/iter",
            "extra": "iterations: 1150143\ncpu: 611.6248153490471 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 870.1655539243535,
            "unit": "ns/iter",
            "extra": "iterations: 803720\ncpu: 869.6660528542265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 124.10477993033778,
            "unit": "ns/iter",
            "extra": "iterations: 5622174\ncpu: 124.08509590773976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 88.48269479845804,
            "unit": "ns/iter",
            "extra": "iterations: 7033550\ncpu: 88.46969169196186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2512.2055005270677,
            "unit": "ns/iter",
            "extra": "iterations: 275610\ncpu: 2511.164326403252 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.26534209858036,
            "unit": "ns/iter",
            "extra": "iterations: 30423804\ncpu: 23.258728592913663 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1285.6631283123043,
            "unit": "ns/iter",
            "extra": "iterations: 557227\ncpu: 1285.2607644640366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 935.075735847769,
            "unit": "ns/iter",
            "extra": "iterations: 760076\ncpu: 934.29209710608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1331.944921568982,
            "unit": "ns/iter",
            "extra": "iterations: 542136\ncpu: 1325.554842327387 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.6796168713679,
            "unit": "ns/iter",
            "extra": "iterations: 3205921\ncpu: 210.59595666892577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1383.7805138077313,
            "unit": "ns/iter",
            "extra": "iterations: 511203\ncpu: 1383.505182872555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 89.98665311303012,
            "unit": "ns/iter",
            "extra": "iterations: 7768628\ncpu: 89.96260343525265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 419.4600480906271,
            "unit": "ns/iter",
            "extra": "iterations: 1645228\ncpu: 419.37166155694 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 209.02608821845482,
            "unit": "ns/iter",
            "extra": "iterations: 3369337\ncpu: 208.99334201357723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 751.620606160771,
            "unit": "ns/iter",
            "extra": "iterations: 934604\ncpu: 751.4861909428998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 134.22577326856128,
            "unit": "ns/iter",
            "extra": "iterations: 5303914\ncpu: 134.1918439854035 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 696.9587396667869,
            "unit": "ns/iter",
            "extra": "iterations: 988310\ncpu: 696.8896398903166 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1166.1319949017434,
            "unit": "ns/iter",
            "extra": "iterations: 604887\ncpu: 1165.9830679118572 ns\nthreads: 1"
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
          "id": "a9c388a5c80f8a448a54bff38bdfb3da83fb1ece",
          "message": "Isolate non-reported `LogicalWhenType` in schema `items` (#49)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T18:54:53-04:00",
          "tree_id": "bceb813a36fc2c7df1ac78289c94a7f9e6d26735",
          "url": "https://github.com/sourcemeta/blaze/commit/a9c388a5c80f8a448a54bff38bdfb3da83fb1ece"
        },
        "date": 1729378688819,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2758537290.999811,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2758234000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 567.9875050046433,
            "unit": "ns/iter",
            "extra": "iterations: 1241377\ncpu: 567.9684737191038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 797.1795401356342,
            "unit": "ns/iter",
            "extra": "iterations: 865255\ncpu: 797.1511288579671 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 115.06682299391312,
            "unit": "ns/iter",
            "extra": "iterations: 6070171\ncpu: 115.0577141896002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 81.46394596430858,
            "unit": "ns/iter",
            "extra": "iterations: 8633555\ncpu: 81.45798573125441 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2315.894141764901,
            "unit": "ns/iter",
            "extra": "iterations: 302924\ncpu: 2315.3035084707694 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.390260399053172,
            "unit": "ns/iter",
            "extra": "iterations: 33142056\ncpu: 21.38844373445022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1169.4873250062399,
            "unit": "ns/iter",
            "extra": "iterations: 601736\ncpu: 1169.4630203278525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 861.3031250384098,
            "unit": "ns/iter",
            "extra": "iterations: 820470\ncpu: 861.2100381488664 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1231.7001135990597,
            "unit": "ns/iter",
            "extra": "iterations: 588913\ncpu: 1228.7859157464698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 196.70240802164804,
            "unit": "ns/iter",
            "extra": "iterations: 3595275\ncpu: 196.64670991787827 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1279.5070857120459,
            "unit": "ns/iter",
            "extra": "iterations: 548357\ncpu: 1279.1210835277002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 86.02236020297003,
            "unit": "ns/iter",
            "extra": "iterations: 8502472\ncpu: 86.02004217126513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 386.39891910290953,
            "unit": "ns/iter",
            "extra": "iterations: 1721903\ncpu: 386.3196707363889 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 192.59221146001693,
            "unit": "ns/iter",
            "extra": "iterations: 3656937\ncpu: 192.58767651726018 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 699.1532585431324,
            "unit": "ns/iter",
            "extra": "iterations: 1023571\ncpu: 696.8016874256879 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 129.40038883879086,
            "unit": "ns/iter",
            "extra": "iterations: 5317371\ncpu: 128.5496159662359 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 653.4881396356594,
            "unit": "ns/iter",
            "extra": "iterations: 1086771\ncpu: 653.4798959486412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1075.3021869548775,
            "unit": "ns/iter",
            "extra": "iterations: 654426\ncpu: 1075.1605223508857 ns\nthreads: 1"
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
          "id": "a9c388a5c80f8a448a54bff38bdfb3da83fb1ece",
          "message": "Isolate non-reported `LogicalWhenType` in schema `items` (#49)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T22:54:53Z",
          "url": "https://github.com/sourcemeta/blaze/commit/a9c388a5c80f8a448a54bff38bdfb3da83fb1ece"
        },
        "date": 1729537495843,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2751898999.9999804,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2751654999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 573.4019542583083,
            "unit": "ns/iter",
            "extra": "iterations: 1231874\ncpu: 573.1243617447883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 818.3276738269186,
            "unit": "ns/iter",
            "extra": "iterations: 862855\ncpu: 812.2233747269249 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 121.59607139107328,
            "unit": "ns/iter",
            "extra": "iterations: 5964554\ncpu: 118.0894665384872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 84.946228694009,
            "unit": "ns/iter",
            "extra": "iterations: 8595179\ncpu: 83.81198343862302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2349.1606197666583,
            "unit": "ns/iter",
            "extra": "iterations: 298693\ncpu: 2348.3308949322586 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.679303008911482,
            "unit": "ns/iter",
            "extra": "iterations: 32923979\ncpu: 21.677300911897696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1183.9078595595292,
            "unit": "ns/iter",
            "extra": "iterations: 602960\ncpu: 1183.803237362344 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 852.788024172648,
            "unit": "ns/iter",
            "extra": "iterations: 819768\ncpu: 852.7485825257863 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1200.2829077972858,
            "unit": "ns/iter",
            "extra": "iterations: 567206\ncpu: 1199.9485195854784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 197.32006631225997,
            "unit": "ns/iter",
            "extra": "iterations: 3574000\ncpu: 197.19418019026304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1300.7765703639689,
            "unit": "ns/iter",
            "extra": "iterations: 539445\ncpu: 1300.566322794725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 83.21894390916484,
            "unit": "ns/iter",
            "extra": "iterations: 8514779\ncpu: 83.20204200249938 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 386.60847957839854,
            "unit": "ns/iter",
            "extra": "iterations: 1810774\ncpu: 386.58275411509084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 198.84765181142402,
            "unit": "ns/iter",
            "extra": "iterations: 3317834\ncpu: 198.80168808927667 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 689.5713296296451,
            "unit": "ns/iter",
            "extra": "iterations: 1017915\ncpu: 689.4947024063869 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.2015474121018,
            "unit": "ns/iter",
            "extra": "iterations: 5710696\ncpu: 122.94928674193125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 651.5426145035417,
            "unit": "ns/iter",
            "extra": "iterations: 1087564\ncpu: 651.0954757605031 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1081.3290001832222,
            "unit": "ns/iter",
            "extra": "iterations: 649489\ncpu: 1081.2346321492735 ns\nthreads: 1"
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
          "id": "8b8f23a28594e162925724818572c188e80ebe7f",
          "message": "Report every instance of `LogicalWhenType` (#50)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T14:45:51-04:00",
          "tree_id": "29dd94a1b9c8580dfff5b698341225f3f6aeb2be",
          "url": "https://github.com/sourcemeta/blaze/commit/8b8f23a28594e162925724818572c188e80ebe7f"
        },
        "date": 1729622967889,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3458489624.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3456105000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 658.7509210844993,
            "unit": "ns/iter",
            "extra": "iterations: 916854\ncpu: 658.6359442179444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 940.7348414410752,
            "unit": "ns/iter",
            "extra": "iterations: 804496\ncpu: 940.5329547940566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 130.1690923947072,
            "unit": "ns/iter",
            "extra": "iterations: 4899079\ncpu: 130.16017908672208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 89.82769395317312,
            "unit": "ns/iter",
            "extra": "iterations: 7995796\ncpu: 89.80844433749927 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2564.652295106404,
            "unit": "ns/iter",
            "extra": "iterations: 280902\ncpu: 2553.577404219264 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.369855165832636,
            "unit": "ns/iter",
            "extra": "iterations: 30541412\ncpu: 23.367649144708807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1283.0213357406878,
            "unit": "ns/iter",
            "extra": "iterations: 558312\ncpu: 1282.8812563584556 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 933.3455460849958,
            "unit": "ns/iter",
            "extra": "iterations: 758142\ncpu: 933.3277934740474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1298.2405345781708,
            "unit": "ns/iter",
            "extra": "iterations: 547572\ncpu: 1298.2438839093302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 212.08278284423338,
            "unit": "ns/iter",
            "extra": "iterations: 3327344\ncpu: 211.98739895844827 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1783.0982802180574,
            "unit": "ns/iter",
            "extra": "iterations: 492795\ncpu: 1677.5900729512273 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 89.67447811656811,
            "unit": "ns/iter",
            "extra": "iterations: 7816688\ncpu: 89.56491547315181 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 436.3158702615425,
            "unit": "ns/iter",
            "extra": "iterations: 1667786\ncpu: 436.02296697538026 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 206.11909345841576,
            "unit": "ns/iter",
            "extra": "iterations: 3431238\ncpu: 206.11569351936566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 752.9817534491123,
            "unit": "ns/iter",
            "extra": "iterations: 943740\ncpu: 752.8206921397857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 136.2591105789216,
            "unit": "ns/iter",
            "extra": "iterations: 5316402\ncpu: 136.23875696382686 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 699.8170789164969,
            "unit": "ns/iter",
            "extra": "iterations: 965717\ncpu: 699.1106090086454 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1192.4858964884959,
            "unit": "ns/iter",
            "extra": "iterations: 610309\ncpu: 1192.363212733225 ns\nthreads: 1"
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
          "id": "8b8f23a28594e162925724818572c188e80ebe7f",
          "message": "Report every instance of `LogicalWhenType` (#50)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T18:45:51Z",
          "url": "https://github.com/sourcemeta/blaze/commit/8b8f23a28594e162925724818572c188e80ebe7f"
        },
        "date": 1729623887302,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3218740500.000081,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3217914000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 606.3009682871663,
            "unit": "ns/iter",
            "extra": "iterations: 1133548\ncpu: 606.1587158197091 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 845.7148065474258,
            "unit": "ns/iter",
            "extra": "iterations: 845349\ncpu: 845.5714740302534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.39739451546956,
            "unit": "ns/iter",
            "extra": "iterations: 5780729\ncpu: 128.37083350560096 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 88.83708036975928,
            "unit": "ns/iter",
            "extra": "iterations: 7978572\ncpu: 88.8234135130948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2559.2321899167546,
            "unit": "ns/iter",
            "extra": "iterations: 278901\ncpu: 2558.7323100311573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.292309907853664,
            "unit": "ns/iter",
            "extra": "iterations: 30824104\ncpu: 23.21154249933758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1361.937625220761,
            "unit": "ns/iter",
            "extra": "iterations: 512595\ncpu: 1336.796106087653 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 942.4541743109462,
            "unit": "ns/iter",
            "extra": "iterations: 733115\ncpu: 941.5835169107164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1318.6033604592988,
            "unit": "ns/iter",
            "extra": "iterations: 533439\ncpu: 1318.3269314767033 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 209.7852547694144,
            "unit": "ns/iter",
            "extra": "iterations: 3260105\ncpu: 209.7374164329064 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1389.4668858619434,
            "unit": "ns/iter",
            "extra": "iterations: 510960\ncpu: 1389.4081728511007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 87.5366071230938,
            "unit": "ns/iter",
            "extra": "iterations: 7903175\ncpu: 87.47269293669947 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 422.6604401951285,
            "unit": "ns/iter",
            "extra": "iterations: 1667397\ncpu: 422.54484085073983 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 216.14728594392233,
            "unit": "ns/iter",
            "extra": "iterations: 3196931\ncpu: 216.1413555688247 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 781.0323302625113,
            "unit": "ns/iter",
            "extra": "iterations: 904323\ncpu: 775.8300961050462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 136.7019380600631,
            "unit": "ns/iter",
            "extra": "iterations: 5302106\ncpu: 136.67003262477206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 709.5633335792579,
            "unit": "ns/iter",
            "extra": "iterations: 1003354\ncpu: 709.4833927008823 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1203.6358001597416,
            "unit": "ns/iter",
            "extra": "iterations: 580003\ncpu: 1203.5023956772652 ns\nthreads: 1"
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
          "id": "8ef793e4b5a28f105d1e582291b146f9e96d3194",
          "message": "Remove the `report` flag from instruction steps (#51)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T15:05:15-04:00",
          "tree_id": "b21af10326b8011de576e1a3e9d42d54a0d94a04",
          "url": "https://github.com/sourcemeta/blaze/commit/8ef793e4b5a28f105d1e582291b146f9e96d3194"
        },
        "date": 1729624307371,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3297721249.999995,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3293293000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 628.2526829088602,
            "unit": "ns/iter",
            "extra": "iterations: 1145119\ncpu: 627.94347137721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 869.8110824360588,
            "unit": "ns/iter",
            "extra": "iterations: 791631\ncpu: 869.5730712920536 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 125.29226625281605,
            "unit": "ns/iter",
            "extra": "iterations: 5524644\ncpu: 125.16716009212557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 89.56337230831333,
            "unit": "ns/iter",
            "extra": "iterations: 7987858\ncpu: 89.55241818269668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2363.633183377807,
            "unit": "ns/iter",
            "extra": "iterations: 294087\ncpu: 2360.1315257049787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.134551967051287,
            "unit": "ns/iter",
            "extra": "iterations: 30830757\ncpu: 23.123824043632798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1238.1170888983995,
            "unit": "ns/iter",
            "extra": "iterations: 554869\ncpu: 1237.9768918429377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 908.5485982480845,
            "unit": "ns/iter",
            "extra": "iterations: 780666\ncpu: 908.3743880225347 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1290.919280330637,
            "unit": "ns/iter",
            "extra": "iterations: 551142\ncpu: 1289.8091598898282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 223.87978182429464,
            "unit": "ns/iter",
            "extra": "iterations: 3249858\ncpu: 223.862704155074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1374.9311964067008,
            "unit": "ns/iter",
            "extra": "iterations: 445718\ncpu: 1374.5215584741907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 120.51095402249308,
            "unit": "ns/iter",
            "extra": "iterations: 7923482\ncpu: 114.6610795607282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 430.0669129455182,
            "unit": "ns/iter",
            "extra": "iterations: 1405453\ncpu: 429.7817145077049 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 209.08744781381063,
            "unit": "ns/iter",
            "extra": "iterations: 3364155\ncpu: 209.02812147478295 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 737.4157579987938,
            "unit": "ns/iter",
            "extra": "iterations: 948458\ncpu: 737.4158897916426 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 133.4541002561588,
            "unit": "ns/iter",
            "extra": "iterations: 5312851\ncpu: 133.4473712889745 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 694.9185798981378,
            "unit": "ns/iter",
            "extra": "iterations: 1018434\ncpu: 693.1190435511768 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1176.777050355455,
            "unit": "ns/iter",
            "extra": "iterations: 608236\ncpu: 1176.4627545886854 ns\nthreads: 1"
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
          "id": "12a0fa822f668c7e081931671d65f5b9cc683469",
          "message": "Completely disable assertions on WebAssembly (#55)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T16:00:20-04:00",
          "tree_id": "25670356989a36af5c45bfcf19648cbb38d039d8",
          "url": "https://github.com/sourcemeta/blaze/commit/12a0fa822f668c7e081931671d65f5b9cc683469"
        },
        "date": 1729627444453,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2936948500.000085,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2935950000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 618.8952035068982,
            "unit": "ns/iter",
            "extra": "iterations: 1205193\ncpu: 618.7871983989282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 826.7968914873906,
            "unit": "ns/iter",
            "extra": "iterations: 848187\ncpu: 826.3767306030395 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 118.33478874616522,
            "unit": "ns/iter",
            "extra": "iterations: 5777055\ncpu: 118.28864360820513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 84.15455805530581,
            "unit": "ns/iter",
            "extra": "iterations: 8306141\ncpu: 84.14003566758628 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2291.643022072745,
            "unit": "ns/iter",
            "extra": "iterations: 306624\ncpu: 2291.095935086619 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.77820515035775,
            "unit": "ns/iter",
            "extra": "iterations: 32005121\ncpu: 23.26468317367085 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1282.3880484680333,
            "unit": "ns/iter",
            "extra": "iterations: 550055\ncpu: 1278.875748788758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 904.1016703043227,
            "unit": "ns/iter",
            "extra": "iterations: 789916\ncpu: 902.5554615933859 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1368.9143051416138,
            "unit": "ns/iter",
            "extra": "iterations: 550033\ncpu: 1364.043611928741 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 219.88899005080845,
            "unit": "ns/iter",
            "extra": "iterations: 3220360\ncpu: 218.84634016072707 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1362.2058236283888,
            "unit": "ns/iter",
            "extra": "iterations: 530391\ncpu: 1361.4295868519632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 86.6814606189876,
            "unit": "ns/iter",
            "extra": "iterations: 8043850\ncpu: 86.53045494383905 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 400.8092302440736,
            "unit": "ns/iter",
            "extra": "iterations: 1710659\ncpu: 400.7362075083334 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 197.55839858799143,
            "unit": "ns/iter",
            "extra": "iterations: 3448157\ncpu: 197.52145856467556 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 717.319904418811,
            "unit": "ns/iter",
            "extra": "iterations: 987223\ncpu: 716.161394132833 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.43329391061384,
            "unit": "ns/iter",
            "extra": "iterations: 5509512\ncpu: 126.43043521821917 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 672.8405117327408,
            "unit": "ns/iter",
            "extra": "iterations: 1048516\ncpu: 672.7937389605894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1108.3621837273881,
            "unit": "ns/iter",
            "extra": "iterations: 627386\ncpu: 1108.28740201407 ns\nthreads: 1"
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
          "id": "1fc8ae9f95d993709c0b272c1ebf4ac105de2a61",
          "message": "Assert that annotation steps are tracked (#54)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T16:00:38-04:00",
          "tree_id": "75bee31f1c3b052b51a5082f85c6b44223f49726",
          "url": "https://github.com/sourcemeta/blaze/commit/1fc8ae9f95d993709c0b272c1ebf4ac105de2a61"
        },
        "date": 1729627454911,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2792578249.999906,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2792134000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 572.3719424155998,
            "unit": "ns/iter",
            "extra": "iterations: 1252909\ncpu: 572.3296743817785 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 815.3939475155794,
            "unit": "ns/iter",
            "extra": "iterations: 876830\ncpu: 811.1412702576326 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 114.74802943064651,
            "unit": "ns/iter",
            "extra": "iterations: 6137820\ncpu: 114.71353021105213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 81.73001209202249,
            "unit": "ns/iter",
            "extra": "iterations: 8460953\ncpu: 81.72779118380633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2228.802154144927,
            "unit": "ns/iter",
            "extra": "iterations: 318920\ncpu: 2228.768970274676 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.119108702297915,
            "unit": "ns/iter",
            "extra": "iterations: 33140173\ncpu: 21.11633515009106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1173.1359005739582,
            "unit": "ns/iter",
            "extra": "iterations: 599762\ncpu: 1173.0669832366877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 851.8673220747595,
            "unit": "ns/iter",
            "extra": "iterations: 840901\ncpu: 851.715005690325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1185.4578210163925,
            "unit": "ns/iter",
            "extra": "iterations: 593708\ncpu: 1185.458171356963 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 194.94041784523546,
            "unit": "ns/iter",
            "extra": "iterations: 3570700\ncpu: 194.90884140364648 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1286.9177582590553,
            "unit": "ns/iter",
            "extra": "iterations: 553320\ncpu: 1286.67136557507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.51028105579134,
            "unit": "ns/iter",
            "extra": "iterations: 8515711\ncpu: 82.5047961350496 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 388.5987799329165,
            "unit": "ns/iter",
            "extra": "iterations: 1808753\ncpu: 388.58539557363525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 194.42453674751343,
            "unit": "ns/iter",
            "extra": "iterations: 3668302\ncpu: 194.41856204859866 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 696.0009542269639,
            "unit": "ns/iter",
            "extra": "iterations: 971467\ncpu: 695.863060711278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 122.35186184632506,
            "unit": "ns/iter",
            "extra": "iterations: 5766158\ncpu: 122.17771347923504 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 645.1686145251314,
            "unit": "ns/iter",
            "extra": "iterations: 1084011\ncpu: 645.1096898463207 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1069.5860512636507,
            "unit": "ns/iter",
            "extra": "iterations: 658712\ncpu: 1069.4977471186207 ns\nthreads: 1"
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
          "id": "707cec47b6d88afe79dd3e6aac2e2e24220cfe82",
          "message": "Avoid `enter`/`leave` on `LoopPropertiesType(Strict)` (#57)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T17:03:31-04:00",
          "tree_id": "83619087aea11372b51f7660f5ba7dc89cddd77f",
          "url": "https://github.com/sourcemeta/blaze/commit/707cec47b6d88afe79dd3e6aac2e2e24220cfe82"
        },
        "date": 1729631223512,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3435064042.000022,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3332593000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 666.1715423836811,
            "unit": "ns/iter",
            "extra": "iterations: 1114366\ncpu: 646.2356173824393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1013.3321390252544,
            "unit": "ns/iter",
            "extra": "iterations: 771716\ncpu: 962.4680581975769 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 152.86338574664762,
            "unit": "ns/iter",
            "extra": "iterations: 5164527\ncpu: 148.74798795707724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 92.22426238407415,
            "unit": "ns/iter",
            "extra": "iterations: 7537256\ncpu: 92.06506983443312 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2469.7949675161344,
            "unit": "ns/iter",
            "extra": "iterations: 276444\ncpu: 2467.150670660236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.383572738458103,
            "unit": "ns/iter",
            "extra": "iterations: 29076167\ncpu: 24.352281371887855 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1295.8941028751017,
            "unit": "ns/iter",
            "extra": "iterations: 534396\ncpu: 1294.3229365489244 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 973.8668533109358,
            "unit": "ns/iter",
            "extra": "iterations: 734731\ncpu: 972.6770750111262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1274.2520404651639,
            "unit": "ns/iter",
            "extra": "iterations: 549507\ncpu: 1273.7872310998785 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 57.14635989108726,
            "unit": "ns/iter",
            "extra": "iterations: 12667849\ncpu: 57.13061467657206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1435.287752878264,
            "unit": "ns/iter",
            "extra": "iterations: 451502\ncpu: 1434.4410434505314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 99.87814254062206,
            "unit": "ns/iter",
            "extra": "iterations: 7898983\ncpu: 95.79739569005262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 79.57392640182105,
            "unit": "ns/iter",
            "extra": "iterations: 10250553\ncpu: 74.25940824851114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 230.57278491308205,
            "unit": "ns/iter",
            "extra": "iterations: 3227695\ncpu: 220.26647499221582 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 895.9320271320993,
            "unit": "ns/iter",
            "extra": "iterations: 925840\ncpu: 833.8816642184373 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 152.37235665494552,
            "unit": "ns/iter",
            "extra": "iterations: 5015189\ncpu: 144.0386394211668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 772.7773560280193,
            "unit": "ns/iter",
            "extra": "iterations: 885728\ncpu: 743.0655912424578 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1179.436645792196,
            "unit": "ns/iter",
            "extra": "iterations: 596898\ncpu: 1173.4299662588962 ns\nthreads: 1"
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
          "id": "41886c525ba3c6bae83ce447ca845cfa57e851a8",
          "message": "Decouple `propertyNames` from the instance location pointer (#53)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T17:28:45-04:00",
          "tree_id": "b3198ac228694641b035921a7dbd3030b66e228f",
          "url": "https://github.com/sourcemeta/blaze/commit/41886c525ba3c6bae83ce447ca845cfa57e851a8"
        },
        "date": 1729632759700,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3351162791.999968,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3347216000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 630.8234745830692,
            "unit": "ns/iter",
            "extra": "iterations: 1127577\ncpu: 630.2035249033997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 871.3606223845936,
            "unit": "ns/iter",
            "extra": "iterations: 813452\ncpu: 871.3556546667771 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 127.154674825082,
            "unit": "ns/iter",
            "extra": "iterations: 5654372\ncpu: 127.04240187946606 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.3151082538447,
            "unit": "ns/iter",
            "extra": "iterations: 7266763\ncpu: 91.31067023927976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2434.5129391390733,
            "unit": "ns/iter",
            "extra": "iterations: 295692\ncpu: 2434.144312324985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.082342297325976,
            "unit": "ns/iter",
            "extra": "iterations: 28989949\ncpu: 24.08169120959818 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1300.1178976359433,
            "unit": "ns/iter",
            "extra": "iterations: 559884\ncpu: 1299.37808546056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1010.3786252544535,
            "unit": "ns/iter",
            "extra": "iterations: 746189\ncpu: 996.03719701041 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1283.8105883416217,
            "unit": "ns/iter",
            "extra": "iterations: 553250\ncpu: 1283.1685494803405 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 54.09531966115759,
            "unit": "ns/iter",
            "extra": "iterations: 12948336\ncpu: 54.07644657969956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1399.9199421747207,
            "unit": "ns/iter",
            "extra": "iterations: 503586\ncpu: 1399.6060255845114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 91.29860530902359,
            "unit": "ns/iter",
            "extra": "iterations: 7583472\ncpu: 90.83675656744032 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 69.43567579580544,
            "unit": "ns/iter",
            "extra": "iterations: 10205272\ncpu: 69.39070315813247 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 211.30763607984568,
            "unit": "ns/iter",
            "extra": "iterations: 3433830\ncpu: 211.17498536619522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 713.4465342054364,
            "unit": "ns/iter",
            "extra": "iterations: 978953\ncpu: 713.2885848452339 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.4816427412044,
            "unit": "ns/iter",
            "extra": "iterations: 5397320\ncpu: 131.42263197290532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 713.4998643405306,
            "unit": "ns/iter",
            "extra": "iterations: 1013567\ncpu: 713.1743634115924 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1166.868843457595,
            "unit": "ns/iter",
            "extra": "iterations: 602814\ncpu: 1166.8325553155737 ns\nthreads: 1"
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
          "id": "0f5b7543aa393037b49906ad1ef9cde7164966a3",
          "message": "Avoid keeping track of the instance location when possible (#56)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T17:40:19-04:00",
          "tree_id": "b1a6cd51e436087465b3bac65c0005231ddfc1aa",
          "url": "https://github.com/sourcemeta/blaze/commit/0f5b7543aa393037b49906ad1ef9cde7164966a3"
        },
        "date": 1729633456953,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4067633208.9999504,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4062411999.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 563.994222699851,
            "unit": "ns/iter",
            "extra": "iterations: 1223755\ncpu: 563.0783939595746 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 928.9215548835817,
            "unit": "ns/iter",
            "extra": "iterations: 843150\ncpu: 899.6275870248483 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 114.30439605797318,
            "unit": "ns/iter",
            "extra": "iterations: 4474759\ncpu: 113.48722914463082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.19130110394129,
            "unit": "ns/iter",
            "extra": "iterations: 8990842\ncpu: 76.67190681362206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2293.636448270798,
            "unit": "ns/iter",
            "extra": "iterations: 316871\ncpu: 2292.753202407288 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.92797128540297,
            "unit": "ns/iter",
            "extra": "iterations: 28114482\ncpu: 24.92231583708353 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1289.448835724696,
            "unit": "ns/iter",
            "extra": "iterations: 545146\ncpu: 1289.095031422775 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 947.3552864918444,
            "unit": "ns/iter",
            "extra": "iterations: 794525\ncpu: 946.5680752650957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1339.0236601981737,
            "unit": "ns/iter",
            "extra": "iterations: 518043\ncpu: 1337.0685445030606 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 56.670243000332945,
            "unit": "ns/iter",
            "extra": "iterations: 12870723\ncpu: 56.62712187963324 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1449.489893653304,
            "unit": "ns/iter",
            "extra": "iterations: 485487\ncpu: 1449.2540479971672 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 71.49199673179649,
            "unit": "ns/iter",
            "extra": "iterations: 9325003\ncpu: 71.48866332804415 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 71.14289574400722,
            "unit": "ns/iter",
            "extra": "iterations: 10288368\ncpu: 71.13985425093664 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 194.72781692986433,
            "unit": "ns/iter",
            "extra": "iterations: 3638518\ncpu: 194.72213687001158 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 662.0213688700379,
            "unit": "ns/iter",
            "extra": "iterations: 827091\ncpu: 651.6090732458705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 136.6333009565287,
            "unit": "ns/iter",
            "extra": "iterations: 5735589\ncpu: 136.44038999307642 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 815.697165393008,
            "unit": "ns/iter",
            "extra": "iterations: 869468\ncpu: 815.0156187461752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1101.3747538984637,
            "unit": "ns/iter",
            "extra": "iterations: 649122\ncpu: 1101.1258284267055 ns\nthreads: 1"
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
          "id": "94c8d875044914fdd0a9ce51891438e84f5e5e01",
          "message": "Make `EvaluationContext::unevaluate()` remove evaluation entries (#58)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T17:54:22-04:00",
          "tree_id": "dde193031bcfba37879025f151df5a19e33ea6d6",
          "url": "https://github.com/sourcemeta/blaze/commit/94c8d875044914fdd0a9ce51891438e84f5e5e01"
        },
        "date": 1729634260522,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2763122958.9999294,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2762682999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 492.4498797226183,
            "unit": "ns/iter",
            "extra": "iterations: 1418388\ncpu: 492.4315490542784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 748.6623221548524,
            "unit": "ns/iter",
            "extra": "iterations: 927914\ncpu: 748.5618279280178 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 98.93037601749332,
            "unit": "ns/iter",
            "extra": "iterations: 7080362\ncpu: 98.90963202163955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.09309054492086,
            "unit": "ns/iter",
            "extra": "iterations: 10750211\ncpu: 65.09109449107555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1896.946059857387,
            "unit": "ns/iter",
            "extra": "iterations: 366573\ncpu: 1895.9006800828215 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.68923777339189,
            "unit": "ns/iter",
            "extra": "iterations: 31759571\ncpu: 22.683744689120637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1160.5611579310419,
            "unit": "ns/iter",
            "extra": "iterations: 596374\ncpu: 1160.0824314943316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 823.8353938123283,
            "unit": "ns/iter",
            "extra": "iterations: 845758\ncpu: 823.8101206255226 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1163.9803320420085,
            "unit": "ns/iter",
            "extra": "iterations: 607333\ncpu: 1163.8178725674416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 49.112147081886974,
            "unit": "ns/iter",
            "extra": "iterations: 14284723\ncpu: 49.08138575735774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1284.7163115451933,
            "unit": "ns/iter",
            "extra": "iterations: 554552\ncpu: 1284.6640170804505 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 66.30970236742587,
            "unit": "ns/iter",
            "extra": "iterations: 10619738\ncpu: 66.29739829739674 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.51802964247918,
            "unit": "ns/iter",
            "extra": "iterations: 11129838\ncpu: 62.51789109598919 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 179.65784743369454,
            "unit": "ns/iter",
            "extra": "iterations: 3894254\ncpu: 179.65417766791842 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 602.9349108130591,
            "unit": "ns/iter",
            "extra": "iterations: 1170686\ncpu: 602.8807041341583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.91822159675336,
            "unit": "ns/iter",
            "extra": "iterations: 5987461\ncpu: 116.9123272786245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 654.1241101824796,
            "unit": "ns/iter",
            "extra": "iterations: 1082385\ncpu: 654.0159000725242 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 967.2856282266534,
            "unit": "ns/iter",
            "extra": "iterations: 722096\ncpu: 967.1650306884393 ns\nthreads: 1"
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
          "id": "7d828f7108b68ffe1780640aeee91baefc44fe5b",
          "message": "Simplify evaluation tracking in `EvaluationContext` (#59)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T08:34:36-04:00",
          "tree_id": "86670b7ced74943b8b61d7ef007ef1dd36ca8f54",
          "url": "https://github.com/sourcemeta/blaze/commit/7d828f7108b68ffe1780640aeee91baefc44fe5b"
        },
        "date": 1729687124315,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2978499082.9999743,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2977772000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 504.3066836031478,
            "unit": "ns/iter",
            "extra": "iterations: 1321802\ncpu: 504.1428292588449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 759.6649932579348,
            "unit": "ns/iter",
            "extra": "iterations: 937408\ncpu: 758.5853758448826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 103.10043895244351,
            "unit": "ns/iter",
            "extra": "iterations: 6835137\ncpu: 103.08630243987788 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 68.1413251707944,
            "unit": "ns/iter",
            "extra": "iterations: 10368988\ncpu: 68.14097962115497 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1986.2136883614883,
            "unit": "ns/iter",
            "extra": "iterations: 352986\ncpu: 1984.8889191072751 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.820976376434068,
            "unit": "ns/iter",
            "extra": "iterations: 30706333\ncpu: 22.82082982686341 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1159.9303035935272,
            "unit": "ns/iter",
            "extra": "iterations: 581106\ncpu: 1159.8658420322613 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 835.0137105305429,
            "unit": "ns/iter",
            "extra": "iterations: 846065\ncpu: 834.7372837784327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1204.1869546402322,
            "unit": "ns/iter",
            "extra": "iterations: 603157\ncpu: 1204.1359049136468 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.434388187875115,
            "unit": "ns/iter",
            "extra": "iterations: 13578523\ncpu: 50.421831593907534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1269.179373372911,
            "unit": "ns/iter",
            "extra": "iterations: 537800\ncpu: 1269.0275195239858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.13553789249698,
            "unit": "ns/iter",
            "extra": "iterations: 10414962\ncpu: 68.31009080974081 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.62273864631841,
            "unit": "ns/iter",
            "extra": "iterations: 10912435\ncpu: 63.60477748550171 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 183.9888361874534,
            "unit": "ns/iter",
            "extra": "iterations: 3837130\ncpu: 183.96275341205558 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 610.4565186355783,
            "unit": "ns/iter",
            "extra": "iterations: 1127759\ncpu: 609.8004981560752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 118.80362175826271,
            "unit": "ns/iter",
            "extra": "iterations: 5974888\ncpu: 118.71938017917648 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 631.5816922620945,
            "unit": "ns/iter",
            "extra": "iterations: 1127414\ncpu: 631.5594803683484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 988.4292090238407,
            "unit": "ns/iter",
            "extra": "iterations: 681803\ncpu: 987.7559940334628 ns\nthreads: 1"
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
          "id": "7f7c6c6825786e7e2a8209f3460fe0054a11b97f",
          "message": "Optimize `EvaluationContext::unevaluate` to not require moves/destructs (#60)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T10:49:56-04:00",
          "tree_id": "f3ac9b1d98efef4af3eea617814c4e046d2263dd",
          "url": "https://github.com/sourcemeta/blaze/commit/7f7c6c6825786e7e2a8209f3460fe0054a11b97f"
        },
        "date": 1729695213297,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2800488207.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2799431000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 503.9211250000335,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 503.8669999999996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 746.519477080998,
            "unit": "ns/iter",
            "extra": "iterations: 902702\ncpu: 746.4766888740693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.55605753146072,
            "unit": "ns/iter",
            "extra": "iterations: 7339219\ncpu: 95.54327238361479 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.976461344502724,
            "unit": "ns/iter",
            "extra": "iterations: 11202509\ncpu: 62.97473182123753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1898.2422303225887,
            "unit": "ns/iter",
            "extra": "iterations: 364880\ncpu: 1897.8403858802856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.159387085527836,
            "unit": "ns/iter",
            "extra": "iterations: 36776681\ncpu: 19.157166466435577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1137.4149501033764,
            "unit": "ns/iter",
            "extra": "iterations: 620183\ncpu: 1137.1869270844245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 814.9563865826233,
            "unit": "ns/iter",
            "extra": "iterations: 849257\ncpu: 814.9405892444796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1226.8683568003748,
            "unit": "ns/iter",
            "extra": "iterations: 607802\ncpu: 1215.662337405932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.122832326194946,
            "unit": "ns/iter",
            "extra": "iterations: 14532168\ncpu: 47.12063609504105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1431.341922365551,
            "unit": "ns/iter",
            "extra": "iterations: 555243\ncpu: 1334.006912288854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.15010402757918,
            "unit": "ns/iter",
            "extra": "iterations: 10449633\ncpu: 68.41943635723868 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 64.99918735418096,
            "unit": "ns/iter",
            "extra": "iterations: 10158177\ncpu: 64.73947047782285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 187.38341480866154,
            "unit": "ns/iter",
            "extra": "iterations: 3801765\ncpu: 187.12071892923385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 624.9587559071907,
            "unit": "ns/iter",
            "extra": "iterations: 1131459\ncpu: 623.1829876292475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 128.42572991382158,
            "unit": "ns/iter",
            "extra": "iterations: 5312408\ncpu: 128.00861680804553 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 674.8966139591215,
            "unit": "ns/iter",
            "extra": "iterations: 1016172\ncpu: 671.4650669374847 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 978.0121923669523,
            "unit": "ns/iter",
            "extra": "iterations: 703801\ncpu: 977.3302396558123 ns\nthreads: 1"
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
          "id": "2eb9fcb203275d748d184a2e5a5f9271e5068fa0",
          "message": "Add a meaningless `not` on the `unevaluatedProperties` benchmark case (#61)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T11:16:48-04:00",
          "tree_id": "d9c9ddfc810d9cb43d085242c671ad192a6029ab",
          "url": "https://github.com/sourcemeta/blaze/commit/2eb9fcb203275d748d184a2e5a5f9271e5068fa0"
        },
        "date": 1729696865731,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3209209625.000028,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3204244000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 532.1091493704117,
            "unit": "ns/iter",
            "extra": "iterations: 1333283\ncpu: 531.9268302378412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 810.3345691989293,
            "unit": "ns/iter",
            "extra": "iterations: 875230\ncpu: 810.2270260388697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 106.00110968612056,
            "unit": "ns/iter",
            "extra": "iterations: 6643320\ncpu: 105.97758349740785 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 67.03332690072264,
            "unit": "ns/iter",
            "extra": "iterations: 10353498\ncpu: 67.02903694963774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1993.0502023517006,
            "unit": "ns/iter",
            "extra": "iterations: 334566\ncpu: 1990.8448557235351 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.141509619162836,
            "unit": "ns/iter",
            "extra": "iterations: 35759350\ncpu: 20.13708302863446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1306.3316382573644,
            "unit": "ns/iter",
            "extra": "iterations: 604496\ncpu: 1303.174876260556 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 840.3721106258633,
            "unit": "ns/iter",
            "extra": "iterations: 838936\ncpu: 840.2023515500592 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1201.030589675622,
            "unit": "ns/iter",
            "extra": "iterations: 591376\ncpu: 1200.8096371851402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.631356455176494,
            "unit": "ns/iter",
            "extra": "iterations: 14227584\ncpu: 48.62828432430971 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1302.288458542062,
            "unit": "ns/iter",
            "extra": "iterations: 539100\ncpu: 1302.0571322574651 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.70372866427655,
            "unit": "ns/iter",
            "extra": "iterations: 10563327\ncpu: 67.41730138620173 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.46531113498601,
            "unit": "ns/iter",
            "extra": "iterations: 11088933\ncpu: 63.236291534992645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 188.54020362983456,
            "unit": "ns/iter",
            "extra": "iterations: 3761924\ncpu: 188.42592248009242 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 616.2970686458871,
            "unit": "ns/iter",
            "extra": "iterations: 1098332\ncpu: 616.2344354894503 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 119.24139110883095,
            "unit": "ns/iter",
            "extra": "iterations: 5851131\ncpu: 119.23558026644739 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 665.7510969281861,
            "unit": "ns/iter",
            "extra": "iterations: 1053852\ncpu: 665.6162345376754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1001.5662723071805,
            "unit": "ns/iter",
            "extra": "iterations: 708237\ncpu: 1001.5347969676849 ns\nthreads: 1"
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
          "id": "f27771ca2b1b4a4097b0694b58e053b5d504e329",
          "message": "Perform no pointer copying when checking evaluation (#62)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T11:31:18-04:00",
          "tree_id": "48d654ee321f9dff02e8302644cc7426443390a2",
          "url": "https://github.com/sourcemeta/blaze/commit/f27771ca2b1b4a4097b0694b58e053b5d504e329"
        },
        "date": 1729697758123,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2783642708.9999914,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2783309000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 565.8183001743013,
            "unit": "ns/iter",
            "extra": "iterations: 1336490\ncpu: 561.3076042469459 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 823.6275017660295,
            "unit": "ns/iter",
            "extra": "iterations: 832412\ncpu: 816.2832827974603 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 98.4059923600836,
            "unit": "ns/iter",
            "extra": "iterations: 7165524\ncpu: 97.16637610871163 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.83141784893019,
            "unit": "ns/iter",
            "extra": "iterations: 11063520\ncpu: 65.81838329934773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1921.4049969647242,
            "unit": "ns/iter",
            "extra": "iterations: 357457\ncpu: 1920.6897612859746 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.716162962632573,
            "unit": "ns/iter",
            "extra": "iterations: 35704995\ncpu: 19.714104427125715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1142.96337844243,
            "unit": "ns/iter",
            "extra": "iterations: 606528\ncpu: 1142.6364487707067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 827.5628670394912,
            "unit": "ns/iter",
            "extra": "iterations: 856856\ncpu: 826.9499192396368 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1201.7826903522027,
            "unit": "ns/iter",
            "extra": "iterations: 603802\ncpu: 1183.6810742594441 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 49.30002261129774,
            "unit": "ns/iter",
            "extra": "iterations: 14612162\ncpu: 48.04504631142186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1290.9934187885488,
            "unit": "ns/iter",
            "extra": "iterations: 540478\ncpu: 1285.3011593441404 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 65.06795800032752,
            "unit": "ns/iter",
            "extra": "iterations: 10378366\ncpu: 65.05783280335261 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.73969112965046,
            "unit": "ns/iter",
            "extra": "iterations: 10517617\ncpu: 62.72561550777127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 186.71539580211382,
            "unit": "ns/iter",
            "extra": "iterations: 3775763\ncpu: 186.20527824442345 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 622.0242531784211,
            "unit": "ns/iter",
            "extra": "iterations: 1113586\ncpu: 621.8415102201363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.91195617855043,
            "unit": "ns/iter",
            "extra": "iterations: 5938645\ncpu: 115.8995023275508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 621.9339708849371,
            "unit": "ns/iter",
            "extra": "iterations: 1121687\ncpu: 621.6083452870546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 990.2312897466339,
            "unit": "ns/iter",
            "extra": "iterations: 709651\ncpu: 990.1345872830476 ns\nthreads: 1"
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
          "id": "1e4aca6a1ab593bcd699fc6de00a23932535a10e",
          "message": "Heavily simplify `EvaluationContext` methods (#64)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T12:50:05-04:00",
          "tree_id": "aa9d5e1e2f98e56ff42b60715c962a36054f2d24",
          "url": "https://github.com/sourcemeta/blaze/commit/1e4aca6a1ab593bcd699fc6de00a23932535a10e"
        },
        "date": 1729702402553,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2865042416.999927,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2864084000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 502.47633300000416,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 502.44999999999965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 736.2067416261568,
            "unit": "ns/iter",
            "extra": "iterations: 930814\ncpu: 736.1707064999023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.73097245119664,
            "unit": "ns/iter",
            "extra": "iterations: 7299955\ncpu: 95.6904528863534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.95252992922005,
            "unit": "ns/iter",
            "extra": "iterations: 10924357\ncpu: 64.90999882189857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1893.0847353151762,
            "unit": "ns/iter",
            "extra": "iterations: 369893\ncpu: 1892.8717223629546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.413456388302095,
            "unit": "ns/iter",
            "extra": "iterations: 36315153\ncpu: 20.412388184072974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1201.04948537224,
            "unit": "ns/iter",
            "extra": "iterations: 515324\ncpu: 1200.9745325271085 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 851.3672760739079,
            "unit": "ns/iter",
            "extra": "iterations: 833433\ncpu: 851.272987750665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1215.357002026067,
            "unit": "ns/iter",
            "extra": "iterations: 588344\ncpu: 1215.2227268400768 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.86901875818072,
            "unit": "ns/iter",
            "extra": "iterations: 14234962\ncpu: 48.85885891370835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1314.1652484973401,
            "unit": "ns/iter",
            "extra": "iterations: 530026\ncpu: 1313.7695131936923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.50313790945401,
            "unit": "ns/iter",
            "extra": "iterations: 10847668\ncpu: 64.48482752237608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.06413591710161,
            "unit": "ns/iter",
            "extra": "iterations: 11453629\ncpu: 61.06361573262055 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 179.1096224629784,
            "unit": "ns/iter",
            "extra": "iterations: 3942130\ncpu: 179.02732786589922 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 595.1996335746632,
            "unit": "ns/iter",
            "extra": "iterations: 1171862\ncpu: 595.1938026832545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 114.25618774132107,
            "unit": "ns/iter",
            "extra": "iterations: 6150548\ncpu: 114.24819381947745 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 687.0006768443685,
            "unit": "ns/iter",
            "extra": "iterations: 1133200\ncpu: 664.0619484645274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1036.7530048405097,
            "unit": "ns/iter",
            "extra": "iterations: 676159\ncpu: 1032.5056680455339 ns\nthreads: 1"
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
          "id": "570f3fecc2977a79feccd618f4e9036b7e641634",
          "message": "Introduce a new `LoopPropertiesEvaluate` step (#65)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T13:05:02-04:00",
          "tree_id": "dfce1dc03c827f3c29186eae3af551fe22c01d9a",
          "url": "https://github.com/sourcemeta/blaze/commit/570f3fecc2977a79feccd618f4e9036b7e641634"
        },
        "date": 1729703289129,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2759977875.0000043,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2759473000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 492.51395839599684,
            "unit": "ns/iter",
            "extra": "iterations: 1424913\ncpu: 492.4258533678899 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 745.6822000223349,
            "unit": "ns/iter",
            "extra": "iterations: 931136\ncpu: 745.6687315279412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.67261654836696,
            "unit": "ns/iter",
            "extra": "iterations: 7168826\ncpu: 96.66143382472941 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.11458984644029,
            "unit": "ns/iter",
            "extra": "iterations: 11027443\ncpu: 63.10175441396525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1889.9205345509436,
            "unit": "ns/iter",
            "extra": "iterations: 372275\ncpu: 1889.7186219864354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.260603077942296,
            "unit": "ns/iter",
            "extra": "iterations: 36365714\ncpu: 19.256709767887408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1126.4219461638324,
            "unit": "ns/iter",
            "extra": "iterations: 626196\ncpu: 1126.3837520520763 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 827.4992276583207,
            "unit": "ns/iter",
            "extra": "iterations: 854544\ncpu: 826.7134284483882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1170.4745666736026,
            "unit": "ns/iter",
            "extra": "iterations: 602202\ncpu: 1170.4245419311121 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.825674338177166,
            "unit": "ns/iter",
            "extra": "iterations: 14582483\ncpu: 47.81970258425805 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1268.0740936322832,
            "unit": "ns/iter",
            "extra": "iterations: 549170\ncpu: 1267.955277964928 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.15087063751862,
            "unit": "ns/iter",
            "extra": "iterations: 10937158\ncpu: 64.14783438257005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.38672608837089,
            "unit": "ns/iter",
            "extra": "iterations: 11442957\ncpu: 61.37958920932756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.89429973228533,
            "unit": "ns/iter",
            "extra": "iterations: 3820189\ncpu: 182.8851923294894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 604.9743157209813,
            "unit": "ns/iter",
            "extra": "iterations: 1154792\ncpu: 604.9392444700018 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.84960219361723,
            "unit": "ns/iter",
            "extra": "iterations: 5986078\ncpu: 116.7950033394153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 631.7590774216848,
            "unit": "ns/iter",
            "extra": "iterations: 1146526\ncpu: 622.4847931926545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 988.0370721897787,
            "unit": "ns/iter",
            "extra": "iterations: 709076\ncpu: 987.4414026141026 ns\nthreads: 1"
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
          "id": "db7ae4bdaf054e2cec7246f92972bb46c3b93952",
          "message": "Implement `LoopPropertiesType(Strict)` evaluate variants (#66)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T13:39:27-04:00",
          "tree_id": "9769ee5bc8648c4678b021b8d9cb3646439eddb2",
          "url": "https://github.com/sourcemeta/blaze/commit/db7ae4bdaf054e2cec7246f92972bb46c3b93952"
        },
        "date": 1729705402121,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2777060582.9999795,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2776249000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 488.2946899008262,
            "unit": "ns/iter",
            "extra": "iterations: 1436734\ncpu: 488.2483465972132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 734.4425953709432,
            "unit": "ns/iter",
            "extra": "iterations: 961142\ncpu: 731.6442315495525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 98.77187803572815,
            "unit": "ns/iter",
            "extra": "iterations: 7300564\ncpu: 97.01935357323087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 66.14753632759806,
            "unit": "ns/iter",
            "extra": "iterations: 10622638\ncpu: 65.23963256584666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2080.1332256040932,
            "unit": "ns/iter",
            "extra": "iterations: 340978\ncpu: 2042.1258849544545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.388260720165608,
            "unit": "ns/iter",
            "extra": "iterations: 34750837\ncpu: 20.375710662738875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1134.6462559259326,
            "unit": "ns/iter",
            "extra": "iterations: 572705\ncpu: 1134.5003099326855 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 809.0990186049387,
            "unit": "ns/iter",
            "extra": "iterations: 869069\ncpu: 809.0588894552671 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1151.3905805569207,
            "unit": "ns/iter",
            "extra": "iterations: 611034\ncpu: 1151.1634377137773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.908073727621904,
            "unit": "ns/iter",
            "extra": "iterations: 14944683\ncpu: 46.90323642194371 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1273.6765919367565,
            "unit": "ns/iter",
            "extra": "iterations: 556492\ncpu: 1273.4882082761267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.01988601899103,
            "unit": "ns/iter",
            "extra": "iterations: 10946736\ncpu: 64.01332780839863 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.069493297096976,
            "unit": "ns/iter",
            "extra": "iterations: 11469581\ncpu: 61.06587503065719 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 185.63318495371138,
            "unit": "ns/iter",
            "extra": "iterations: 3849136\ncpu: 182.7937490387461 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 598.9068793433582,
            "unit": "ns/iter",
            "extra": "iterations: 1161826\ncpu: 596.8535735988027 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.79924575398475,
            "unit": "ns/iter",
            "extra": "iterations: 6148657\ncpu: 115.27818188589788 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 640.9496466235439,
            "unit": "ns/iter",
            "extra": "iterations: 1124155\ncpu: 628.3448456840921 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1016.20778937536,
            "unit": "ns/iter",
            "extra": "iterations: 701494\ncpu: 1000.0185318762518 ns\nthreads: 1"
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
          "id": "b6f3b13db1f56b195278a356bae139e0c2aa4069",
          "message": "Correctly format the `track` step JSON property (#67)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T13:55:03-04:00",
          "tree_id": "531905d819abac29061b456d7eec7582ff275c55",
          "url": "https://github.com/sourcemeta/blaze/commit/b6f3b13db1f56b195278a356bae139e0c2aa4069"
        },
        "date": 1729706313315,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3004599833.9999757,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3000863000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 556.3805873523098,
            "unit": "ns/iter",
            "extra": "iterations: 1347709\ncpu: 546.3434613852099 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1079.1503360234965,
            "unit": "ns/iter",
            "extra": "iterations: 811848\ncpu: 987.7279983445171 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 138.82942351275156,
            "unit": "ns/iter",
            "extra": "iterations: 5811733\ncpu: 129.02829500254066 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 88.81526502651211,
            "unit": "ns/iter",
            "extra": "iterations: 9282958\ncpu: 81.80905267480465 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2465.579099486857,
            "unit": "ns/iter",
            "extra": "iterations: 302050\ncpu: 2427.472272802513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.53772031984874,
            "unit": "ns/iter",
            "extra": "iterations: 27993506\ncpu: 25.829597764567236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1512.7340541379097,
            "unit": "ns/iter",
            "extra": "iterations: 490378\ncpu: 1500.01631394557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1187.5299673010197,
            "unit": "ns/iter",
            "extra": "iterations: 585338\ncpu: 1158.4486228469707 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1633.5310265857986,
            "unit": "ns/iter",
            "extra": "iterations: 408714\ncpu: 1605.6093013696634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 65.50492274320256,
            "unit": "ns/iter",
            "extra": "iterations: 12056286\ncpu: 64.435100494464 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1934.2392223924915,
            "unit": "ns/iter",
            "extra": "iterations: 376591\ncpu: 1907.9983324083669 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.70955832735129,
            "unit": "ns/iter",
            "extra": "iterations: 7676364\ncpu: 97.47700864628081 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 95.50804549816056,
            "unit": "ns/iter",
            "extra": "iterations: 9145425\ncpu: 94.09655647495892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 255.3778643137832,
            "unit": "ns/iter",
            "extra": "iterations: 2763140\ncpu: 248.50677128194693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 890.0643911944476,
            "unit": "ns/iter",
            "extra": "iterations: 1029442\ncpu: 817.9518612996183 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 188.265842514579,
            "unit": "ns/iter",
            "extra": "iterations: 4825323\ncpu: 164.41344962813852 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 786.363941695554,
            "unit": "ns/iter",
            "extra": "iterations: 971521\ncpu: 774.019295517025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1397.4666275217473,
            "unit": "ns/iter",
            "extra": "iterations: 575639\ncpu: 1359.8140501251683 ns\nthreads: 1"
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
          "id": "02cccba5474f08b88e73c161cf3ba04f02401d16",
          "message": "Never add a wrapper step for `patternProperties` (#68)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T14:20:42-04:00",
          "tree_id": "1a48a9f559c814be96575bf2dd2f242bcb8f63c6",
          "url": "https://github.com/sourcemeta/blaze/commit/02cccba5474f08b88e73c161cf3ba04f02401d16"
        },
        "date": 1729707882166,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3941803542.0000024,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3650323000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 674.447474174659,
            "unit": "ns/iter",
            "extra": "iterations: 1260875\ncpu: 619.0526420144737 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 904.5069139756831,
            "unit": "ns/iter",
            "extra": "iterations: 757379\ncpu: 851.9103381530251 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 109.93026557993316,
            "unit": "ns/iter",
            "extra": "iterations: 6672831\ncpu: 105.51893191960055 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.86201763821214,
            "unit": "ns/iter",
            "extra": "iterations: 8860647\ncpu: 75.3991215314186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2379.2447930964877,
            "unit": "ns/iter",
            "extra": "iterations: 269546\ncpu: 2335.961208847472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.38894021780525,
            "unit": "ns/iter",
            "extra": "iterations: 31316548\ncpu: 23.96595563470146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1452.1532544582587,
            "unit": "ns/iter",
            "extra": "iterations: 463856\ncpu: 1408.0382704977396 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 968.3968170960162,
            "unit": "ns/iter",
            "extra": "iterations: 717081\ncpu: 959.422994055065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1328.1037000027839,
            "unit": "ns/iter",
            "extra": "iterations: 550405\ncpu: 1320.6420726555912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 63.526727570031376,
            "unit": "ns/iter",
            "extra": "iterations: 12441348\ncpu: 62.21793651298878 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1691.8936624708658,
            "unit": "ns/iter",
            "extra": "iterations: 392298\ncpu: 1651.6959046439229 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.61376911347705,
            "unit": "ns/iter",
            "extra": "iterations: 8345156\ncpu: 78.02394586751893 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 69.1774781681678,
            "unit": "ns/iter",
            "extra": "iterations: 10207802\ncpu: 68.28845230344379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 239.13756462128833,
            "unit": "ns/iter",
            "extra": "iterations: 3339456\ncpu: 222.98811542957853 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 694.31336549081,
            "unit": "ns/iter",
            "extra": "iterations: 1059370\ncpu: 691.1655040259766 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 140.82232539029584,
            "unit": "ns/iter",
            "extra": "iterations: 5081891\ncpu: 138.7904620543799 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 749.0427358775863,
            "unit": "ns/iter",
            "extra": "iterations: 849731\ncpu: 738.9785708653665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1066.9770646657778,
            "unit": "ns/iter",
            "extra": "iterations: 627983\ncpu: 1060.2436690165155 ns\nthreads: 1"
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
          "id": "44ae00b3c224beaa0bf69837c717f2819c09fc79",
          "message": "Apply `PropertyType` object optimizations when marking evaluation (#69)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T14:48:47-04:00",
          "tree_id": "518c1e6c2e68ea9158bd2642c9e5fe5de4ccd5f7",
          "url": "https://github.com/sourcemeta/blaze/commit/44ae00b3c224beaa0bf69837c717f2819c09fc79"
        },
        "date": 1729709524002,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2753484542.000024,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2753262000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 488.89995509491393,
            "unit": "ns/iter",
            "extra": "iterations: 1423001\ncpu: 488.8921371102343 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 734.8182066077105,
            "unit": "ns/iter",
            "extra": "iterations: 957147\ncpu: 734.7418944007562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 98.90437693900748,
            "unit": "ns/iter",
            "extra": "iterations: 7305288\ncpu: 98.89534813685631 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.99614038960256,
            "unit": "ns/iter",
            "extra": "iterations: 11180144\ncpu: 64.99549558574564 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1908.3545282126702,
            "unit": "ns/iter",
            "extra": "iterations: 364868\ncpu: 1908.1366411962683 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.175295935602573,
            "unit": "ns/iter",
            "extra": "iterations: 36994366\ncpu: 19.172649154198226 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1131.2623542917888,
            "unit": "ns/iter",
            "extra": "iterations: 621019\ncpu: 1131.2343100613662 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 814.3367666992273,
            "unit": "ns/iter",
            "extra": "iterations: 862419\ncpu: 814.2561794209101 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1180.348395661513,
            "unit": "ns/iter",
            "extra": "iterations: 610906\ncpu: 1180.3174301774727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.412997467393396,
            "unit": "ns/iter",
            "extra": "iterations: 14712497\ncpu: 47.41064688067574 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1281.3444689736323,
            "unit": "ns/iter",
            "extra": "iterations: 557609\ncpu: 1281.0804703654358 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.44717628377909,
            "unit": "ns/iter",
            "extra": "iterations: 10951189\ncpu: 64.43848243327724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.06800747191584,
            "unit": "ns/iter",
            "extra": "iterations: 11398424\ncpu: 61.045720004800756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 179.57040199436437,
            "unit": "ns/iter",
            "extra": "iterations: 3968389\ncpu: 179.21705760196332 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 598.1552921872657,
            "unit": "ns/iter",
            "extra": "iterations: 1173768\ncpu: 597.9580291846434 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.53336704602182,
            "unit": "ns/iter",
            "extra": "iterations: 5979942\ncpu: 115.53239145128781 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 604.4186093078554,
            "unit": "ns/iter",
            "extra": "iterations: 1163622\ncpu: 604.4170701482109 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 968.2664936661406,
            "unit": "ns/iter",
            "extra": "iterations: 722156\ncpu: 968.1952375940925 ns\nthreads: 1"
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
          "id": "44ae00b3c224beaa0bf69837c717f2819c09fc79",
          "message": "Apply `PropertyType` object optimizations when marking evaluation (#69)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T18:48:47Z",
          "url": "https://github.com/sourcemeta/blaze/commit/44ae00b3c224beaa0bf69837c717f2819c09fc79"
        },
        "date": 1729710297352,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2788573375.0000553,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2788209000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 495.2936785668993,
            "unit": "ns/iter",
            "extra": "iterations: 1411373\ncpu: 495.29359000065875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 737.2917336269136,
            "unit": "ns/iter",
            "extra": "iterations: 942723\ncpu: 737.2918662215721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 97.2941336274421,
            "unit": "ns/iter",
            "extra": "iterations: 7141108\ncpu: 97.29092460161635 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.66207584450143,
            "unit": "ns/iter",
            "extra": "iterations: 11018070\ncpu: 63.65715592658245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1948.114473098375,
            "unit": "ns/iter",
            "extra": "iterations: 357097\ncpu: 1947.7928966079244 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.266501054934267,
            "unit": "ns/iter",
            "extra": "iterations: 36437837\ncpu: 19.265331254432056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1157.876537817698,
            "unit": "ns/iter",
            "extra": "iterations: 604428\ncpu: 1157.4066720932856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 829.6944160290703,
            "unit": "ns/iter",
            "extra": "iterations: 846566\ncpu: 829.671874372461 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1169.0044894764405,
            "unit": "ns/iter",
            "extra": "iterations: 606975\ncpu: 1168.954240289963 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.24050284695615,
            "unit": "ns/iter",
            "extra": "iterations: 14638808\ncpu: 48.223256975568056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1277.4912641371836,
            "unit": "ns/iter",
            "extra": "iterations: 550146\ncpu: 1277.1627895140568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 65.38492817691484,
            "unit": "ns/iter",
            "extra": "iterations: 10753019\ncpu: 65.37605857480597 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.08179841430329,
            "unit": "ns/iter",
            "extra": "iterations: 11289412\ncpu: 62.070371778441555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 179.15478695321025,
            "unit": "ns/iter",
            "extra": "iterations: 3898158\ncpu: 179.1548726347156 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 603.4859091492177,
            "unit": "ns/iter",
            "extra": "iterations: 1175621\ncpu: 603.4870081429318 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 117.82046414500296,
            "unit": "ns/iter",
            "extra": "iterations: 5979942\ncpu: 117.81719622029804 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 616.3719117051972,
            "unit": "ns/iter",
            "extra": "iterations: 1153954\ncpu: 616.3521249547197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 985.9722327854564,
            "unit": "ns/iter",
            "extra": "iterations: 723155\ncpu: 985.8301470639105 ns\nthreads: 1"
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
          "id": "4a27761d18983f969c7d98e68eb4b973f39cfce0",
          "message": "Don't unevaluate in `not` when no applicators are present (#70)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T16:57:33-04:00",
          "tree_id": "b518e4779047bd53837121647bddbedf0f3a0de3",
          "url": "https://github.com/sourcemeta/blaze/commit/4a27761d18983f969c7d98e68eb4b973f39cfce0"
        },
        "date": 1729717255037,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2858371999.9999175,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2848751000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 490.92487188014053,
            "unit": "ns/iter",
            "extra": "iterations: 1425618\ncpu: 490.87764043383316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 736.6231265198908,
            "unit": "ns/iter",
            "extra": "iterations: 943765\ncpu: 736.6176961425787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.62322432164201,
            "unit": "ns/iter",
            "extra": "iterations: 7332761\ncpu: 95.62005361963926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.796676796220694,
            "unit": "ns/iter",
            "extra": "iterations: 11163384\ncpu: 62.78732327043483 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1911.2626954032703,
            "unit": "ns/iter",
            "extra": "iterations: 365526\ncpu: 1910.873645103219 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.96380381525117,
            "unit": "ns/iter",
            "extra": "iterations: 36845596\ncpu: 19.958233271623588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1148.0209620686292,
            "unit": "ns/iter",
            "extra": "iterations: 622887\ncpu: 1148.0172166059017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 839.1467958218108,
            "unit": "ns/iter",
            "extra": "iterations: 838062\ncpu: 839.099016540543 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1419.659625128031,
            "unit": "ns/iter",
            "extra": "iterations: 574543\ncpu: 1419.4899250360709 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 53.647590722248225,
            "unit": "ns/iter",
            "extra": "iterations: 13649215\ncpu: 53.62777273271751 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1406.2987951900695,
            "unit": "ns/iter",
            "extra": "iterations: 514687\ncpu: 1405.5357916559005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.00290941787169,
            "unit": "ns/iter",
            "extra": "iterations: 10051839\ncpu: 66.98694636871919 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.71234898587062,
            "unit": "ns/iter",
            "extra": "iterations: 11368804\ncpu: 63.70098385019218 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.59466707625967,
            "unit": "ns/iter",
            "extra": "iterations: 3867147\ncpu: 180.58687709569884 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 642.3957277800037,
            "unit": "ns/iter",
            "extra": "iterations: 1130747\ncpu: 641.5971035076857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.41531091264886,
            "unit": "ns/iter",
            "extra": "iterations: 5940913\ncpu: 123.41470073707518 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 617.2801628686528,
            "unit": "ns/iter",
            "extra": "iterations: 1122622\ncpu: 617.2709959363004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1050.1181959565101,
            "unit": "ns/iter",
            "extra": "iterations: 702156\ncpu: 1048.0277886965248 ns\nthreads: 1"
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
          "id": "683867f18d10da58b040890f23b206339c5b8a67",
          "message": "Extract `LogicalNotEvaluate` out of `LogicalNot` (#71)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T17:36:13-04:00",
          "tree_id": "cc55c39f8fb08dd6a31ac656a8115298db64b8e7",
          "url": "https://github.com/sourcemeta/blaze/commit/683867f18d10da58b040890f23b206339c5b8a67"
        },
        "date": 1729719568873,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3121904250.0000567,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3121304000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 527.5790886289498,
            "unit": "ns/iter",
            "extra": "iterations: 1330874\ncpu: 527.5510679448244 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 779.9904912491963,
            "unit": "ns/iter",
            "extra": "iterations: 873406\ncpu: 779.9751776378912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 97.91198094979032,
            "unit": "ns/iter",
            "extra": "iterations: 7257872\ncpu: 97.8567822634514 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.42546553827245,
            "unit": "ns/iter",
            "extra": "iterations: 10943998\ncpu: 64.41740943300616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1968.901065759031,
            "unit": "ns/iter",
            "extra": "iterations: 358430\ncpu: 1968.579638981115 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.434692544837997,
            "unit": "ns/iter",
            "extra": "iterations: 33252735\ncpu: 20.43224414472974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1156.1657172122032,
            "unit": "ns/iter",
            "extra": "iterations: 583844\ncpu: 1156.0793636656338 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 884.7270798090897,
            "unit": "ns/iter",
            "extra": "iterations: 787428\ncpu: 872.6537537400236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1159.0668147938732,
            "unit": "ns/iter",
            "extra": "iterations: 590483\ncpu: 1158.7344597558265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 49.53370317910189,
            "unit": "ns/iter",
            "extra": "iterations: 14621410\ncpu: 49.52497741325899 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1255.3915036003527,
            "unit": "ns/iter",
            "extra": "iterations: 552281\ncpu: 1255.197987980757 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.96168894751996,
            "unit": "ns/iter",
            "extra": "iterations: 10782502\ncpu: 64.95857825947992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.75675934331563,
            "unit": "ns/iter",
            "extra": "iterations: 10668455\ncpu: 61.756177440876016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 177.89339063078637,
            "unit": "ns/iter",
            "extra": "iterations: 3959455\ncpu: 177.88357236033733 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 597.9382314833305,
            "unit": "ns/iter",
            "extra": "iterations: 1170823\ncpu: 597.475451028892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.86613356428663,
            "unit": "ns/iter",
            "extra": "iterations: 6082884\ncpu: 115.71599918722791 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 611.6317645558344,
            "unit": "ns/iter",
            "extra": "iterations: 1160054\ncpu: 611.4973958108845 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 968.8711312064956,
            "unit": "ns/iter",
            "extra": "iterations: 721672\ncpu: 968.8501147335631 ns\nthreads: 1"
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
          "id": "d3ddf2853da10213df4be8a01d5af46e6dc04236",
          "message": "Ignore `unevaluated*` when total evaluation is guaranteed (#72)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T17:53:19-04:00",
          "tree_id": "4e0ee81ba15d5cdc055dd96c130a722148d2d820",
          "url": "https://github.com/sourcemeta/blaze/commit/d3ddf2853da10213df4be8a01d5af46e6dc04236"
        },
        "date": 1729720597794,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2806026040.9999957,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2805626000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 484.6115252302377,
            "unit": "ns/iter",
            "extra": "iterations: 1435980\ncpu: 484.5875290742213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 732.1030063652207,
            "unit": "ns/iter",
            "extra": "iterations: 952213\ncpu: 732.0851532167698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 99.46856577018173,
            "unit": "ns/iter",
            "extra": "iterations: 7312538\ncpu: 98.95907549471877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.04943158851472,
            "unit": "ns/iter",
            "extra": "iterations: 10301692\ncpu: 64.67238585661458 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1903.7041070843418,
            "unit": "ns/iter",
            "extra": "iterations: 366440\ncpu: 1903.544918677001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 18.950983725015913,
            "unit": "ns/iter",
            "extra": "iterations: 36931713\ncpu: 18.94994689252568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1157.8062968990778,
            "unit": "ns/iter",
            "extra": "iterations: 628214\ncpu: 1157.7838125224862 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 813.5770311527816,
            "unit": "ns/iter",
            "extra": "iterations: 830969\ncpu: 813.550204640607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1153.5578901359363,
            "unit": "ns/iter",
            "extra": "iterations: 613196\ncpu: 1153.2625783599408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.85819991450228,
            "unit": "ns/iter",
            "extra": "iterations: 14923369\ncpu: 46.85349534679463 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1266.8919928703754,
            "unit": "ns/iter",
            "extra": "iterations: 554306\ncpu: 1266.6289017257611 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 63.98227004132594,
            "unit": "ns/iter",
            "extra": "iterations: 10945880\ncpu: 63.96799526397151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.101180828372556,
            "unit": "ns/iter",
            "extra": "iterations: 11452130\ncpu: 61.09719327321641 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 176.97026839676738,
            "unit": "ns/iter",
            "extra": "iterations: 3942707\ncpu: 176.97054333482026 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 606.3233580359175,
            "unit": "ns/iter",
            "extra": "iterations: 1146432\ncpu: 605.7411167866923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.77144283142432,
            "unit": "ns/iter",
            "extra": "iterations: 5970760\ncpu: 115.73602020513299 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 597.290354680982,
            "unit": "ns/iter",
            "extra": "iterations: 1185798\ncpu: 597.2577116844528 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 976.5558307813371,
            "unit": "ns/iter",
            "extra": "iterations: 717794\ncpu: 976.5044009841243 ns\nthreads: 1"
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
          "id": "4f8a369543fc4061ada3ec7da5fb63f44a2d6f5e",
          "message": "Implement a new `LoopPropertiesUnevaluatedExcept` step (#73)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-23T18:28:32-04:00",
          "tree_id": "3f85c2f2b8c211084c67953ee84c71e5c0600192",
          "url": "https://github.com/sourcemeta/blaze/commit/4f8a369543fc4061ada3ec7da5fb63f44a2d6f5e"
        },
        "date": 1729722703991,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2949839083.9999046,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2949714000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 491.6723654181681,
            "unit": "ns/iter",
            "extra": "iterations: 1279520\ncpu: 491.6070088783293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 731.1653630322212,
            "unit": "ns/iter",
            "extra": "iterations: 951954\ncpu: 730.2453689989227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.88572579381147,
            "unit": "ns/iter",
            "extra": "iterations: 7336450\ncpu: 95.85208104737316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.69808330004153,
            "unit": "ns/iter",
            "extra": "iterations: 11211301\ncpu: 62.6943295876188 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1922.6603798420756,
            "unit": "ns/iter",
            "extra": "iterations: 364625\ncpu: 1922.5999314364074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.01781732599204,
            "unit": "ns/iter",
            "extra": "iterations: 36400131\ncpu: 19.017651337573525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1128.34513279995,
            "unit": "ns/iter",
            "extra": "iterations: 625000\ncpu: 1128.2431999999972 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 804.450180231462,
            "unit": "ns/iter",
            "extra": "iterations: 858896\ncpu: 804.097352880909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1155.4992752922672,
            "unit": "ns/iter",
            "extra": "iterations: 610591\ncpu: 1155.3822444156585 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.145727486515625,
            "unit": "ns/iter",
            "extra": "iterations: 14905383\ncpu: 47.14357222487998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1276.710560735406,
            "unit": "ns/iter",
            "extra": "iterations: 558891\ncpu: 1276.6890144947772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.16288749457622,
            "unit": "ns/iter",
            "extra": "iterations: 10943314\ncpu: 64.15323548241442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 64.15955374637882,
            "unit": "ns/iter",
            "extra": "iterations: 11382854\ncpu: 64.15693287465508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.1371973206798,
            "unit": "ns/iter",
            "extra": "iterations: 3892197\ncpu: 180.11498390240791 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 597.1084391006026,
            "unit": "ns/iter",
            "extra": "iterations: 1169864\ncpu: 596.2949539433636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.26712362097241,
            "unit": "ns/iter",
            "extra": "iterations: 6082884\ncpu: 115.23990922726817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 597.0945244407172,
            "unit": "ns/iter",
            "extra": "iterations: 1172903\ncpu: 597.0868861278378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 983.7679064777427,
            "unit": "ns/iter",
            "extra": "iterations: 710162\ncpu: 983.7163914712474 ns\nthreads: 1"
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
          "id": "1b85992ae0198160a1a5c2c1d96ae3b00e41e45e",
          "message": "Remove `base_dialect` from `SchemaContext` (#74)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T09:44:45-04:00",
          "tree_id": "08d0d491c61f0fc2d7286aa15d5b0b6ba7b22019",
          "url": "https://github.com/sourcemeta/blaze/commit/1b85992ae0198160a1a5c2c1d96ae3b00e41e45e"
        },
        "date": 1729777698905,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2761118624.9999948,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2758888000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 492.67086120271216,
            "unit": "ns/iter",
            "extra": "iterations: 1408658\ncpu: 492.61992619926224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 752.938507422485,
            "unit": "ns/iter",
            "extra": "iterations: 949887\ncpu: 751.3441072464409 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.87685605883104,
            "unit": "ns/iter",
            "extra": "iterations: 7237311\ncpu: 95.8604653026519 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.9974276203601,
            "unit": "ns/iter",
            "extra": "iterations: 11221905\ncpu: 64.90422080742981 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1970.6990568298147,
            "unit": "ns/iter",
            "extra": "iterations: 362713\ncpu: 1970.60485838666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.06685713252715,
            "unit": "ns/iter",
            "extra": "iterations: 36453777\ncpu: 19.066666260673035 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1134.2421496206257,
            "unit": "ns/iter",
            "extra": "iterations: 617709\ncpu: 1133.9578992697222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 816.6256405977142,
            "unit": "ns/iter",
            "extra": "iterations: 862866\ncpu: 816.4141361462831 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1159.5054676963048,
            "unit": "ns/iter",
            "extra": "iterations: 605008\ncpu: 1159.0177319969314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.20312731798574,
            "unit": "ns/iter",
            "extra": "iterations: 14694892\ncpu: 48.197428058674994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1305.4624009861611,
            "unit": "ns/iter",
            "extra": "iterations: 533764\ncpu: 1305.4477259612877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.25299181200549,
            "unit": "ns/iter",
            "extra": "iterations: 10513194\ncpu: 67.24312326016236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.32190047629505,
            "unit": "ns/iter",
            "extra": "iterations: 10951360\ncpu: 61.31704190164507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 181.11490787287647,
            "unit": "ns/iter",
            "extra": "iterations: 3867916\ncpu: 181.10657004960711 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 605.1222587909115,
            "unit": "ns/iter",
            "extra": "iterations: 1152776\ncpu: 604.0297507928699 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.8120918229263,
            "unit": "ns/iter",
            "extra": "iterations: 6051908\ncpu: 115.80529644535285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 604.0385893100046,
            "unit": "ns/iter",
            "extra": "iterations: 1164338\ncpu: 603.9328785971069 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 996.4934632190262,
            "unit": "ns/iter",
            "extra": "iterations: 701951\ncpu: 996.4798112688743 ns\nthreads: 1"
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
          "id": "bf2f80f76968e4ce642fbf335efc8c50db7027b6",
          "message": "Keep track of all subschema requiring evaluation tracking (#75)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T12:47:49-04:00",
          "tree_id": "f6108823dfc5b4496ca951c12fe9e6ba735295cc",
          "url": "https://github.com/sourcemeta/blaze/commit/bf2f80f76968e4ce642fbf335efc8c50db7027b6"
        },
        "date": 1729788762631,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3221989374.999964,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3217552000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 538.1357211923587,
            "unit": "ns/iter",
            "extra": "iterations: 1302059\ncpu: 538.0846797264944 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 896.5863232812288,
            "unit": "ns/iter",
            "extra": "iterations: 885885\ncpu: 874.7365628721573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 150.444916091424,
            "unit": "ns/iter",
            "extra": "iterations: 6038179\ncpu: 134.2797224129992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 93.46129454620335,
            "unit": "ns/iter",
            "extra": "iterations: 7904067\ncpu: 86.07265095298405 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2512.5020958843497,
            "unit": "ns/iter",
            "extra": "iterations: 264089\ncpu: 2368.928656627121 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.793502445585936,
            "unit": "ns/iter",
            "extra": "iterations: 30996493\ncpu: 23.90938226463231 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1411.4488211536473,
            "unit": "ns/iter",
            "extra": "iterations: 502610\ncpu: 1397.5547641312382 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1054.412276488023,
            "unit": "ns/iter",
            "extra": "iterations: 616186\ncpu: 1039.1894655185274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1712.8521601352272,
            "unit": "ns/iter",
            "extra": "iterations: 515639\ncpu: 1685.9042857503016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 67.84310703366558,
            "unit": "ns/iter",
            "extra": "iterations: 11738270\ncpu: 64.51470276284327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1763.5626792952146,
            "unit": "ns/iter",
            "extra": "iterations: 454209\ncpu: 1691.1686029999396 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 86.6359179716454,
            "unit": "ns/iter",
            "extra": "iterations: 7719623\ncpu: 82.5061016580729 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 72.91021249001098,
            "unit": "ns/iter",
            "extra": "iterations: 9420631\ncpu: 72.25365264810807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 211.6504432705645,
            "unit": "ns/iter",
            "extra": "iterations: 2757458\ncpu: 210.43548079426745 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 738.3641438645998,
            "unit": "ns/iter",
            "extra": "iterations: 918225\ncpu: 730.6313811974161 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 142.63490822926326,
            "unit": "ns/iter",
            "extra": "iterations: 5394367\ncpu: 141.62773871336492 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 727.2488041586082,
            "unit": "ns/iter",
            "extra": "iterations: 983408\ncpu: 721.2377771992881 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1208.192951740145,
            "unit": "ns/iter",
            "extra": "iterations: 626566\ncpu: 1196.7869306665234 ns\nthreads: 1"
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
          "id": "bf2f80f76968e4ce642fbf335efc8c50db7027b6",
          "message": "Keep track of all subschema requiring evaluation tracking (#75)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T16:47:49Z",
          "url": "https://github.com/sourcemeta/blaze/commit/bf2f80f76968e4ce642fbf335efc8c50db7027b6"
        },
        "date": 1729796683021,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2801269207.999894,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2800919000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 522.6186659999712,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 522.4910000000004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 766.5187493202167,
            "unit": "ns/iter",
            "extra": "iterations: 937634\ncpu: 766.3768592009253 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.98657644863694,
            "unit": "ns/iter",
            "extra": "iterations: 7054318\ncpu: 95.98475713740143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.877372005196605,
            "unit": "ns/iter",
            "extra": "iterations: 11222625\ncpu: 62.85516980207394 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1937.2767737964598,
            "unit": "ns/iter",
            "extra": "iterations: 358849\ncpu: 1936.7003948736087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.175373554135145,
            "unit": "ns/iter",
            "extra": "iterations: 36317226\ncpu: 19.166386771941244 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1138.3384606536604,
            "unit": "ns/iter",
            "extra": "iterations: 625928\ncpu: 1138.0270574251374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 809.8920887299565,
            "unit": "ns/iter",
            "extra": "iterations: 863654\ncpu: 809.8497778045369 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1176.6819341675427,
            "unit": "ns/iter",
            "extra": "iterations: 602347\ncpu: 1176.6158045113534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.095550876896276,
            "unit": "ns/iter",
            "extra": "iterations: 14927346\ncpu: 47.092899166402326 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1256.5373777978052,
            "unit": "ns/iter",
            "extra": "iterations: 557684\ncpu: 1256.458854835354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.0138413121406,
            "unit": "ns/iter",
            "extra": "iterations: 10961822\ncpu: 64.0127161342339 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.12987147150036,
            "unit": "ns/iter",
            "extra": "iterations: 11373976\ncpu: 62.124713468711505 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 176.89483192974225,
            "unit": "ns/iter",
            "extra": "iterations: 3965871\ncpu: 176.8920370834047 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 596.521181357349,
            "unit": "ns/iter",
            "extra": "iterations: 1171195\ncpu: 596.5138170842588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.3430243924608,
            "unit": "ns/iter",
            "extra": "iterations: 6046054\ncpu: 116.34050903283357 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 612.6530067467711,
            "unit": "ns/iter",
            "extra": "iterations: 1161305\ncpu: 612.6452568446673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1016.1499832219952,
            "unit": "ns/iter",
            "extra": "iterations: 715220\ncpu: 1015.951735130443 ns\nthreads: 1"
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
          "id": "517cb182ae8921d69291c3aef727a0db572a9e28",
          "message": "Implement a `LoopPropertiesStartsWith` step (#76)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T15:05:00-04:00",
          "tree_id": "fee32c15031428f6a4e0612fbbca01fa4e57c023",
          "url": "https://github.com/sourcemeta/blaze/commit/517cb182ae8921d69291c3aef727a0db572a9e28"
        },
        "date": 1729797124695,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3000052707.9999986,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2998612000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 510.69605191426115,
            "unit": "ns/iter",
            "extra": "iterations: 1430820\ncpu: 510.1459303056988 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 736.3492217938827,
            "unit": "ns/iter",
            "extra": "iterations: 955788\ncpu: 736.2511351889755 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.49618043044514,
            "unit": "ns/iter",
            "extra": "iterations: 7329229\ncpu: 95.4809844255104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.173676719235196,
            "unit": "ns/iter",
            "extra": "iterations: 11231989\ncpu: 63.160051171702506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1912.8940551448152,
            "unit": "ns/iter",
            "extra": "iterations: 365728\ncpu: 1912.7958482806882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.229591858777987,
            "unit": "ns/iter",
            "extra": "iterations: 36799689\ncpu: 19.224917906235568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1133.640502480172,
            "unit": "ns/iter",
            "extra": "iterations: 626174\ncpu: 1133.5938572984544 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 808.0651193846942,
            "unit": "ns/iter",
            "extra": "iterations: 870171\ncpu: 808.0630129020622 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1157.3094668630308,
            "unit": "ns/iter",
            "extra": "iterations: 607086\ncpu: 1157.210016373299 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 51.28040284507012,
            "unit": "ns/iter",
            "extra": "iterations: 13713659\ncpu: 51.278218307746954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1330.4672853984662,
            "unit": "ns/iter",
            "extra": "iterations: 536366\ncpu: 1323.1599318375909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.96179377814819,
            "unit": "ns/iter",
            "extra": "iterations: 10236762\ncpu: 67.25495815962118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.69316024090449,
            "unit": "ns/iter",
            "extra": "iterations: 11082788\ncpu: 63.68397554839084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 179.10582600055636,
            "unit": "ns/iter",
            "extra": "iterations: 3699828\ncpu: 179.10156904591275 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 610.5074207095885,
            "unit": "ns/iter",
            "extra": "iterations: 1134595\ncpu: 610.3993054790474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 119.17091079918796,
            "unit": "ns/iter",
            "extra": "iterations: 6092254\ncpu: 119.15081019274636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 399.71596842052475,
            "unit": "ns/iter",
            "extra": "iterations: 1704652\ncpu: 399.6182211970538 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 975.2403452633686,
            "unit": "ns/iter",
            "extra": "iterations: 714701\ncpu: 975.1938223117063 ns\nthreads: 1"
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
          "id": "8cd6a9d96b35cd894aa665a947b55ce7c8009d69",
          "message": "Test `patternProperties` with `^/` (#77)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T15:19:29-04:00",
          "tree_id": "83fed75c432486b49924677f3a8b6ac07ef4c4a9",
          "url": "https://github.com/sourcemeta/blaze/commit/8cd6a9d96b35cd894aa665a947b55ce7c8009d69"
        },
        "date": 1729798037115,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3130664250.0001087,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3122583000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 517.9642499999773,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 517.9479999999996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 778.8966584229603,
            "unit": "ns/iter",
            "extra": "iterations: 883894\ncpu: 778.6125938178106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 101.02586776276188,
            "unit": "ns/iter",
            "extra": "iterations: 6908599\ncpu: 101.02352155625192 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 67.33200738271175,
            "unit": "ns/iter",
            "extra": "iterations: 10202743\ncpu: 67.29455010284975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2048.0879213614744,
            "unit": "ns/iter",
            "extra": "iterations: 340088\ncpu: 2048.031685916587 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.70773851884891,
            "unit": "ns/iter",
            "extra": "iterations: 31516199\ncpu: 20.69795916696682 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1221.7398190674103,
            "unit": "ns/iter",
            "extra": "iterations: 576568\ncpu: 1221.6911101552632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 872.235464474237,
            "unit": "ns/iter",
            "extra": "iterations: 805922\ncpu: 872.2370154928158 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1251.2098917518547,
            "unit": "ns/iter",
            "extra": "iterations: 556868\ncpu: 1251.1133697752423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 54.91228434038336,
            "unit": "ns/iter",
            "extra": "iterations: 12675878\ncpu: 54.88645441365087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1356.8536133649152,
            "unit": "ns/iter",
            "extra": "iterations: 522131\ncpu: 1356.7706188676807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 68.62805472588481,
            "unit": "ns/iter",
            "extra": "iterations: 9889799\ncpu: 68.5998775101497 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 66.44935864734093,
            "unit": "ns/iter",
            "extra": "iterations: 10287008\ncpu: 66.44118484208435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 184.90841841398392,
            "unit": "ns/iter",
            "extra": "iterations: 3773870\ncpu: 184.5678309003752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 623.5300968163954,
            "unit": "ns/iter",
            "extra": "iterations: 1132246\ncpu: 623.4625690883421 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.9226883746232,
            "unit": "ns/iter",
            "extra": "iterations: 5682095\ncpu: 124.92276176304692 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 420.6030425016738,
            "unit": "ns/iter",
            "extra": "iterations: 1691700\ncpu: 420.5491517408519 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1050.2781992848443,
            "unit": "ns/iter",
            "extra": "iterations: 665469\ncpu: 1049.0856824284874 ns\nthreads: 1"
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
          "id": "db832116e9eef39be8dbb202e84663f741a7d6a5",
          "message": "Turn `ValuePropertyFilter` into a tuple (#79)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T15:29:32-04:00",
          "tree_id": "94f54e1a7ef3611bb9a5e877c13624959fe18cc7",
          "url": "https://github.com/sourcemeta/blaze/commit/db832116e9eef39be8dbb202e84663f741a7d6a5"
        },
        "date": 1729798370695,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2845297583.0000467,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2845018999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 494.5931052724922,
            "unit": "ns/iter",
            "extra": "iterations: 1417750\ncpu: 494.54699347557766 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 736.5696203459888,
            "unit": "ns/iter",
            "extra": "iterations: 954211\ncpu: 736.5152990271547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.80388565910802,
            "unit": "ns/iter",
            "extra": "iterations: 7318501\ncpu: 95.79939935787392 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.627727910112505,
            "unit": "ns/iter",
            "extra": "iterations: 11221365\ncpu: 63.62603836520779 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1922.0023924550478,
            "unit": "ns/iter",
            "extra": "iterations: 368241\ncpu: 1921.594825128106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.000060170369377,
            "unit": "ns/iter",
            "extra": "iterations: 36994953\ncpu: 18.999294309145363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1128.0002424493994,
            "unit": "ns/iter",
            "extra": "iterations: 618686\ncpu: 1126.3532712878555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 821.0018546539897,
            "unit": "ns/iter",
            "extra": "iterations: 875635\ncpu: 818.8274794863173 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1234.5504791046153,
            "unit": "ns/iter",
            "extra": "iterations: 558855\ncpu: 1226.4612466561089 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.91989637376841,
            "unit": "ns/iter",
            "extra": "iterations: 14919774\ncpu: 46.919745567191704 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1261.3187557669023,
            "unit": "ns/iter",
            "extra": "iterations: 553819\ncpu: 1261.1809995684507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.24342998216333,
            "unit": "ns/iter",
            "extra": "iterations: 10887147\ncpu: 64.23298959773402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.08701981272915,
            "unit": "ns/iter",
            "extra": "iterations: 11468078\ncpu: 61.084429317624114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.14051637267525,
            "unit": "ns/iter",
            "extra": "iterations: 3893041\ncpu: 180.14169385834848 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 599.5178040911348,
            "unit": "ns/iter",
            "extra": "iterations: 1175404\ncpu: 599.4806891928223 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 117.87257262592163,
            "unit": "ns/iter",
            "extra": "iterations: 6055206\ncpu: 117.85891347049149 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 388.76381109765566,
            "unit": "ns/iter",
            "extra": "iterations: 1756124\ncpu: 388.68838419154883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 998.1823146874297,
            "unit": "ns/iter",
            "extra": "iterations: 705659\ncpu: 997.0311439377945 ns\nthreads: 1"
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
          "id": "9c0a08c6c5d63f30741de6d9c8867243c007d747",
          "message": "Extend `ValuePropertyFilter` to take string prefixes (#80)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T15:44:06-04:00",
          "tree_id": "6bec07457864ca3d9965fc242e8bdcae332751db",
          "url": "https://github.com/sourcemeta/blaze/commit/9c0a08c6c5d63f30741de6d9c8867243c007d747"
        },
        "date": 1729799277827,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2842587792.000131,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2841455000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 500.0375411724361,
            "unit": "ns/iter",
            "extra": "iterations: 1392924\ncpu: 499.9562072302573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 745.1385447474028,
            "unit": "ns/iter",
            "extra": "iterations: 938325\ncpu: 745.1149654970293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 98.03457964762312,
            "unit": "ns/iter",
            "extra": "iterations: 7235441\ncpu: 97.94385718852523 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.718872726946074,
            "unit": "ns/iter",
            "extra": "iterations: 11198387\ncpu: 62.71733598776327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1928.7774919274698,
            "unit": "ns/iter",
            "extra": "iterations: 361106\ncpu: 1928.3866787037605 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.691769188142395,
            "unit": "ns/iter",
            "extra": "iterations: 36428545\ncpu: 19.68881820561322 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1143.951606452475,
            "unit": "ns/iter",
            "extra": "iterations: 615082\ncpu: 1143.9450349709425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 824.8975184813097,
            "unit": "ns/iter",
            "extra": "iterations: 864390\ncpu: 824.8730318490506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1166.9212742297534,
            "unit": "ns/iter",
            "extra": "iterations: 602560\ncpu: 1166.809944237918 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.70218087426231,
            "unit": "ns/iter",
            "extra": "iterations: 14539261\ncpu: 47.69850407114911 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1281.810323091828,
            "unit": "ns/iter",
            "extra": "iterations: 555260\ncpu: 1281.4915535064647 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.40693277321908,
            "unit": "ns/iter",
            "extra": "iterations: 10917882\ncpu: 64.40507417097938 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.57143501453982,
            "unit": "ns/iter",
            "extra": "iterations: 11152535\ncpu: 61.56277474134807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 181.03672213513323,
            "unit": "ns/iter",
            "extra": "iterations: 3893864\ncpu: 181.02686688595173 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 605.6150495451067,
            "unit": "ns/iter",
            "extra": "iterations: 1155211\ncpu: 605.1587112657352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.65732780357988,
            "unit": "ns/iter",
            "extra": "iterations: 6057197\ncpu: 116.6516459675987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 390.1043531280637,
            "unit": "ns/iter",
            "extra": "iterations: 1787680\ncpu: 390.0625391568973 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 985.2986579354915,
            "unit": "ns/iter",
            "extra": "iterations: 709802\ncpu: 985.2747667659469 ns\nthreads: 1"
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
          "id": "3f98fc14cc6bd0b6e85e5374959f226d71f372f4",
          "message": "Don't track object applicators siblings of `unevaluatedProperties` (#81)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T16:10:03-04:00",
          "tree_id": "bceebb8f0faa30f2a7859558346d7f20516a2a43",
          "url": "https://github.com/sourcemeta/blaze/commit/3f98fc14cc6bd0b6e85e5374959f226d71f372f4"
        },
        "date": 1729800792564,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2770210042.0000305,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2767827999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 495.8598683696476,
            "unit": "ns/iter",
            "extra": "iterations: 1408490\ncpu: 495.8089869292642 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 770.4947756708563,
            "unit": "ns/iter",
            "extra": "iterations: 905188\ncpu: 770.3968678329813 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.84566721006263,
            "unit": "ns/iter",
            "extra": "iterations: 7317583\ncpu: 95.83492254204685 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.05091071241998,
            "unit": "ns/iter",
            "extra": "iterations: 11183717\ncpu: 63.0333367698772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1904.5123588615477,
            "unit": "ns/iter",
            "extra": "iterations: 361967\ncpu: 1904.2094997610234 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.217380827778143,
            "unit": "ns/iter",
            "extra": "iterations: 36603412\ncpu: 19.215093937144452 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1134.4376184280998,
            "unit": "ns/iter",
            "extra": "iterations: 599520\ncpu: 1134.1339738457427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 810.8444408650334,
            "unit": "ns/iter",
            "extra": "iterations: 869155\ncpu: 810.6057032405037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1155.6555605708488,
            "unit": "ns/iter",
            "extra": "iterations: 611466\ncpu: 1155.5605708248697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.00416574659597,
            "unit": "ns/iter",
            "extra": "iterations: 14912813\ncpu: 47.00286927758023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1257.823331888967,
            "unit": "ns/iter",
            "extra": "iterations: 553920\ncpu: 1257.7249422299276 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.92017081903766,
            "unit": "ns/iter",
            "extra": "iterations: 10944682\ncpu: 64.91316970196122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.05612614424398,
            "unit": "ns/iter",
            "extra": "iterations: 11468078\ncpu: 61.05460740675119 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.34992840645202,
            "unit": "ns/iter",
            "extra": "iterations: 3860684\ncpu: 180.34213626393668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 602.8910149572172,
            "unit": "ns/iter",
            "extra": "iterations: 1171803\ncpu: 602.0756048584966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.565186004028,
            "unit": "ns/iter",
            "extra": "iterations: 6004924\ncpu: 116.56200811200891 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 343.5106224105177,
            "unit": "ns/iter",
            "extra": "iterations: 2082484\ncpu: 341.54404067450184 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1025.029223157023,
            "unit": "ns/iter",
            "extra": "iterations: 639048\ncpu: 1023.7353062680763 ns\nthreads: 1"
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
          "id": "722304608286c8bf6461779e199f004e174e99b9",
          "message": "Introduce a new `AssertionPropertyTypeStrictEvaluate` step (#82)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T16:37:35-04:00",
          "tree_id": "6439befb89f06e07a9fdd6e713e4e750c0ffc7f6",
          "url": "https://github.com/sourcemeta/blaze/commit/722304608286c8bf6461779e199f004e174e99b9"
        },
        "date": 1729802465342,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2770331124.9999843,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2770105000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 494.9878299153229,
            "unit": "ns/iter",
            "extra": "iterations: 1423244\ncpu: 494.93481089679676 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 755.2708980170727,
            "unit": "ns/iter",
            "extra": "iterations: 965917\ncpu: 755.2098161643289 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 101.4491405248637,
            "unit": "ns/iter",
            "extra": "iterations: 6809272\ncpu: 101.44168128399035 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.69646731885404,
            "unit": "ns/iter",
            "extra": "iterations: 11206276\ncpu: 62.69388688981066 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1916.0469583484412,
            "unit": "ns/iter",
            "extra": "iterations: 364621\ncpu: 1916.0141626510836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.00538381341944,
            "unit": "ns/iter",
            "extra": "iterations: 37024500\ncpu: 19.003740766249386 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1132.5277385812738,
            "unit": "ns/iter",
            "extra": "iterations: 615136\ncpu: 1132.4568875825855 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 808.1866815342944,
            "unit": "ns/iter",
            "extra": "iterations: 869004\ncpu: 808.1757966591642 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1170.807661200297,
            "unit": "ns/iter",
            "extra": "iterations: 604605\ncpu: 1170.62710364618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.98432755619479,
            "unit": "ns/iter",
            "extra": "iterations: 14897230\ncpu: 46.979673402370736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1277.536976656864,
            "unit": "ns/iter",
            "extra": "iterations: 546845\ncpu: 1277.5082518812455 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.55376502530487,
            "unit": "ns/iter",
            "extra": "iterations: 10932888\ncpu: 64.54607419375385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.41536580559542,
            "unit": "ns/iter",
            "extra": "iterations: 11393415\ncpu: 61.284171602632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.0723694125846,
            "unit": "ns/iter",
            "extra": "iterations: 3881557\ncpu: 180.03857730287123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 599.4376993588373,
            "unit": "ns/iter",
            "extra": "iterations: 1171882\ncpu: 598.7343435601849 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.43954383689623,
            "unit": "ns/iter",
            "extra": "iterations: 5586949\ncpu: 125.26622312106312 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 340.36481020342853,
            "unit": "ns/iter",
            "extra": "iterations: 2025985\ncpu: 340.2483236549132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 980.3320723887,
            "unit": "ns/iter",
            "extra": "iterations: 718509\ncpu: 980.1909231477965 ns\nthreads: 1"
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
          "id": "b9098d4381ef01b1cfb1b9d747674affed015a87",
          "message": "Add TODO for optimizing `$dynamicRef` as `$ref` (#83)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T09:50:46-04:00",
          "tree_id": "d5daaed4141b7bbbf9378f1c66c9c80c5d91a487",
          "url": "https://github.com/sourcemeta/blaze/commit/b9098d4381ef01b1cfb1b9d747674affed015a87"
        },
        "date": 1729864530657,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3302551874.999949,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3293308000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 551.9129308606024,
            "unit": "ns/iter",
            "extra": "iterations: 1318814\ncpu: 551.4158933708621 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 790.1572567171922,
            "unit": "ns/iter",
            "extra": "iterations: 891822\ncpu: 789.5275066100637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 107.54072224932098,
            "unit": "ns/iter",
            "extra": "iterations: 6610072\ncpu: 107.30215949236268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 68.9763510623837,
            "unit": "ns/iter",
            "extra": "iterations: 10159357\ncpu: 68.89461606674512 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2066.647483873096,
            "unit": "ns/iter",
            "extra": "iterations: 340583\ncpu: 2065.3027309055365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.203845456493294,
            "unit": "ns/iter",
            "extra": "iterations: 34002205\ncpu: 21.18500844283483 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1239.2080255712092,
            "unit": "ns/iter",
            "extra": "iterations: 578775\ncpu: 1238.1115286596657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 879.6461991778324,
            "unit": "ns/iter",
            "extra": "iterations: 808062\ncpu: 879.1095237741669 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1264.589432967612,
            "unit": "ns/iter",
            "extra": "iterations: 550921\ncpu: 1264.0668988838718 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.94056107303153,
            "unit": "ns/iter",
            "extra": "iterations: 13894127\ncpu: 50.63132070118551 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1552.9439519705306,
            "unit": "ns/iter",
            "extra": "iterations: 407918\ncpu: 1549.8041273000968 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 70.6727252290949,
            "unit": "ns/iter",
            "extra": "iterations: 9715341\ncpu: 70.62953322997102 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 65.97810352659224,
            "unit": "ns/iter",
            "extra": "iterations: 10631027\ncpu: 65.94076000371378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 195.65165610007244,
            "unit": "ns/iter",
            "extra": "iterations: 3602862\ncpu: 195.54398697480005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 642.1003377652734,
            "unit": "ns/iter",
            "extra": "iterations: 1093955\ncpu: 642.0026417905661 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.1244759898959,
            "unit": "ns/iter",
            "extra": "iterations: 5637296\ncpu: 125.08213157513796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 345.7471359963003,
            "unit": "ns/iter",
            "extra": "iterations: 2016408\ncpu: 345.62201697275583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1205.659016418256,
            "unit": "ns/iter",
            "extra": "iterations: 659935\ncpu: 1204.9307886382771 ns\nthreads: 1"
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
          "id": "5e2242526fff8e036b56df31007e263f22aec09a",
          "message": "Introduce a generalizable helper to traverse adjacent subschemas (#84)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T10:19:43-04:00",
          "tree_id": "76a83aeffccd1a3768401e77e18e66fe158c71d8",
          "url": "https://github.com/sourcemeta/blaze/commit/5e2242526fff8e036b56df31007e263f22aec09a"
        },
        "date": 1729866205105,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2809624541.9999375,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2809105000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 490.0584780232041,
            "unit": "ns/iter",
            "extra": "iterations: 1426211\ncpu: 490.00954276751435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 733.0519091256849,
            "unit": "ns/iter",
            "extra": "iterations: 953185\ncpu: 732.993070600146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.8458680420832,
            "unit": "ns/iter",
            "extra": "iterations: 7356573\ncpu: 95.81689735152494 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.1567811857862,
            "unit": "ns/iter",
            "extra": "iterations: 11207531\ncpu: 63.15342781563573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1925.5325691311796,
            "unit": "ns/iter",
            "extra": "iterations: 362644\ncpu: 1925.2820948368064 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 18.999823111457427,
            "unit": "ns/iter",
            "extra": "iterations: 36718037\ncpu: 19.00014426152468 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1124.8240112976023,
            "unit": "ns/iter",
            "extra": "iterations: 622432\ncpu: 1124.7702560279688 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 814.5541971660946,
            "unit": "ns/iter",
            "extra": "iterations: 867776\ncpu: 814.5085828600951 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1158.2462382989152,
            "unit": "ns/iter",
            "extra": "iterations: 610628\ncpu: 1158.2043404495034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.030355614265254,
            "unit": "ns/iter",
            "extra": "iterations: 14926201\ncpu: 47.02522765169781 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1342.9172090991933,
            "unit": "ns/iter",
            "extra": "iterations: 553986\ncpu: 1342.5086554533875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.47401142050448,
            "unit": "ns/iter",
            "extra": "iterations: 10500420\ncpu: 67.46349193651295 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.54603667166435,
            "unit": "ns/iter",
            "extra": "iterations: 10863155\ncpu: 62.54232771234502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.87515060777704,
            "unit": "ns/iter",
            "extra": "iterations: 3883431\ncpu: 180.64798885315557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 610.8316850955148,
            "unit": "ns/iter",
            "extra": "iterations: 1171352\ncpu: 610.7463853734811 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.42216968337974,
            "unit": "ns/iter",
            "extra": "iterations: 5935926\ncpu: 115.4215871289497 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 320.7111999652322,
            "unit": "ns/iter",
            "extra": "iterations: 2184605\ncpu: 320.7028272845663 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 980.1740589645111,
            "unit": "ns/iter",
            "extra": "iterations: 713310\ncpu: 980.0563569836385 ns\nthreads: 1"
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
          "id": "e4e687c4c1ba408e4f017b6327def8cecb2f888c",
          "message": "Optimize `unevaluatedProperties` through static references (#85)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T10:36:38-04:00",
          "tree_id": "f6d966c065b5a0e533ed9ff720afcbbcb29bc4a5",
          "url": "https://github.com/sourcemeta/blaze/commit/e4e687c4c1ba408e4f017b6327def8cecb2f888c"
        },
        "date": 1729867200937,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2790391750.000026,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2789859000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 492.660464873825,
            "unit": "ns/iter",
            "extra": "iterations: 1419697\ncpu: 492.64033100020623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 741.5117259711068,
            "unit": "ns/iter",
            "extra": "iterations: 945039\ncpu: 741.4582890229922 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.07170134704198,
            "unit": "ns/iter",
            "extra": "iterations: 7296683\ncpu: 96.06502022905471 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.573370523198314,
            "unit": "ns/iter",
            "extra": "iterations: 11210224\ncpu: 62.57252308250038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1923.127679421746,
            "unit": "ns/iter",
            "extra": "iterations: 360199\ncpu: 1922.4178856687568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.06552720761154,
            "unit": "ns/iter",
            "extra": "iterations: 36915353\ncpu: 19.065482050246132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1127.6689613702808,
            "unit": "ns/iter",
            "extra": "iterations: 608648\ncpu: 1127.6567079822826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 817.1404113770594,
            "unit": "ns/iter",
            "extra": "iterations: 868206\ncpu: 817.121742996477 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1176.2900402753073,
            "unit": "ns/iter",
            "extra": "iterations: 610298\ncpu: 1176.2237464320722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.71474278694656,
            "unit": "ns/iter",
            "extra": "iterations: 14851968\ncpu: 47.685666976928566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1263.9872914384812,
            "unit": "ns/iter",
            "extra": "iterations: 543964\ncpu: 1263.7913538395894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.30515825071542,
            "unit": "ns/iter",
            "extra": "iterations: 10902068\ncpu: 64.29633350296457 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.31847294925897,
            "unit": "ns/iter",
            "extra": "iterations: 11413478\ncpu: 61.31023339248569 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 181.45834828219637,
            "unit": "ns/iter",
            "extra": "iterations: 3865951\ncpu: 181.45755080703347 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 597.6964358961977,
            "unit": "ns/iter",
            "extra": "iterations: 1153137\ncpu: 597.5430499585051 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.65401711766009,
            "unit": "ns/iter",
            "extra": "iterations: 6088333\ncpu: 123.38763336368068 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 330.0746987268102,
            "unit": "ns/iter",
            "extra": "iterations: 2080089\ncpu: 328.31431732007735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1039.9401019444585,
            "unit": "ns/iter",
            "extra": "iterations: 707836\ncpu: 1034.5207081866383 ns\nthreads: 1"
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
          "id": "7db4a79cf819c7796abaf2cc4692efdb70c14807",
          "message": "Add various performance related TODOs (#86)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T10:44:35-04:00",
          "tree_id": "f70fc463fe152f073a592d63c32c5baaae31d61c",
          "url": "https://github.com/sourcemeta/blaze/commit/7db4a79cf819c7796abaf2cc4692efdb70c14807"
        },
        "date": 1729867702279,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2797659124.9998817,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2797200000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 495.88088703335757,
            "unit": "ns/iter",
            "extra": "iterations: 1415505\ncpu: 495.77783193983754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 736.3981321154016,
            "unit": "ns/iter",
            "extra": "iterations: 956376\ncpu: 736.371468961998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 97.8371051353534,
            "unit": "ns/iter",
            "extra": "iterations: 7223868\ncpu: 97.8129722193152 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.23173041934888,
            "unit": "ns/iter",
            "extra": "iterations: 11138693\ncpu: 63.23084764074207 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1914.7300105016038,
            "unit": "ns/iter",
            "extra": "iterations: 362803\ncpu: 1914.2123962591238 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.046504410095793,
            "unit": "ns/iter",
            "extra": "iterations: 36991825\ncpu: 19.045667522486408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1128.4429426353533,
            "unit": "ns/iter",
            "extra": "iterations: 624950\ncpu: 1128.2790623249869 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 813.1214023319253,
            "unit": "ns/iter",
            "extra": "iterations: 870008\ncpu: 812.9867771330837 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1158.5322500191817,
            "unit": "ns/iter",
            "extra": "iterations: 601426\ncpu: 1158.4583972093008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.15710184654172,
            "unit": "ns/iter",
            "extra": "iterations: 14841105\ncpu: 47.153766515363905 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1290.037387993861,
            "unit": "ns/iter",
            "extra": "iterations: 545282\ncpu: 1290.0205765090377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 63.97771392100927,
            "unit": "ns/iter",
            "extra": "iterations: 10958904\ncpu: 63.9769268897691 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.113828813461595,
            "unit": "ns/iter",
            "extra": "iterations: 11459067\ncpu: 61.10558564671973 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.09587130691315,
            "unit": "ns/iter",
            "extra": "iterations: 3862772\ncpu: 182.09254908133272 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 598.2088655057094,
            "unit": "ns/iter",
            "extra": "iterations: 1176154\ncpu: 598.207377605313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 122.42717459479098,
            "unit": "ns/iter",
            "extra": "iterations: 5722227\ncpu: 122.42121817257501 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 337.3447043547977,
            "unit": "ns/iter",
            "extra": "iterations: 2149587\ncpu: 337.23873469647793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 975.1710588321977,
            "unit": "ns/iter",
            "extra": "iterations: 713012\ncpu: 975.1420733451912 ns\nthreads: 1"
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
          "id": "bfcdd97baa1d29a2aabb9308c36aa9618f0ea8bb",
          "message": "Optimize `contains` set to `true` (#87)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:04:26-04:00",
          "tree_id": "22fc7bf166ab2e8c95c74d3054164c50b1afb081",
          "url": "https://github.com/sourcemeta/blaze/commit/bfcdd97baa1d29a2aabb9308c36aa9618f0ea8bb"
        },
        "date": 1729869048284,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3154973750.0000105,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3139587000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 518.9650697595519,
            "unit": "ns/iter",
            "extra": "iterations: 1367268\ncpu: 518.7534557965226 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 986.6042232285504,
            "unit": "ns/iter",
            "extra": "iterations: 801851\ncpu: 905.0995758563618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 110.98769860605525,
            "unit": "ns/iter",
            "extra": "iterations: 6534544\ncpu: 108.97975436388532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.38947191859506,
            "unit": "ns/iter",
            "extra": "iterations: 10027791\ncpu: 65.23430733648114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2029.8523884281867,
            "unit": "ns/iter",
            "extra": "iterations: 351612\ncpu: 2017.0727961503028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.029950222534804,
            "unit": "ns/iter",
            "extra": "iterations: 34975867\ncpu: 19.966738780199506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1251.080654763876,
            "unit": "ns/iter",
            "extra": "iterations: 611396\ncpu: 1246.328075420838 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 870.6886708960961,
            "unit": "ns/iter",
            "extra": "iterations: 845186\ncpu: 868.024316540974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1255.777964696183,
            "unit": "ns/iter",
            "extra": "iterations: 587303\ncpu: 1248.0287006877186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 54.97028816760937,
            "unit": "ns/iter",
            "extra": "iterations: 13612321\ncpu: 52.90949280434986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1325.8075423701316,
            "unit": "ns/iter",
            "extra": "iterations: 508673\ncpu: 1321.3695242326578 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 65.66442262826648,
            "unit": "ns/iter",
            "extra": "iterations: 10158620\ncpu: 65.62161002183365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.62180065292416,
            "unit": "ns/iter",
            "extra": "iterations: 11254562\ncpu: 63.588702963296065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 196.07794890954585,
            "unit": "ns/iter",
            "extra": "iterations: 3586580\ncpu: 195.29189367029335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 647.7630615927724,
            "unit": "ns/iter",
            "extra": "iterations: 1099885\ncpu: 647.4258672497583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.30210739775296,
            "unit": "ns/iter",
            "extra": "iterations: 5554101\ncpu: 124.24404957705956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 364.8903745116607,
            "unit": "ns/iter",
            "extra": "iterations: 2078440\ncpu: 363.95469679182395 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1123.4905286195915,
            "unit": "ns/iter",
            "extra": "iterations: 627786\ncpu: 1123.263341329691 ns\nthreads: 1"
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
          "id": "257ad270bf6216065e7aa35ec6137def1e0f1bc3",
          "message": "Optimize out `propertyNames` set to `true` or `{}` (#89)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:16:19-04:00",
          "tree_id": "6efd5218d6aa2dd987e5a701c2b63a823757894d",
          "url": "https://github.com/sourcemeta/blaze/commit/257ad270bf6216065e7aa35ec6137def1e0f1bc3"
        },
        "date": 1729870078260,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3273739292.000016,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3200237999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 570.7704309851795,
            "unit": "ns/iter",
            "extra": "iterations: 1244776\ncpu: 569.2180761839878 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 806.4952758600788,
            "unit": "ns/iter",
            "extra": "iterations: 701080\ncpu: 805.2661607805096 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 104.2075191690101,
            "unit": "ns/iter",
            "extra": "iterations: 6701964\ncpu: 104.01935910130226 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.19246367291858,
            "unit": "ns/iter",
            "extra": "iterations: 11016162\ncpu: 63.18026187341837 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2002.093616958889,
            "unit": "ns/iter",
            "extra": "iterations: 341295\ncpu: 1981.3504446300112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.69716415947501,
            "unit": "ns/iter",
            "extra": "iterations: 35479146\ncpu: 19.91829228358538 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1229.7737294251388,
            "unit": "ns/iter",
            "extra": "iterations: 591681\ncpu: 1180.4587269153465 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 844.35403535888,
            "unit": "ns/iter",
            "extra": "iterations: 833284\ncpu: 827.9926171629372 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1173.0924947783174,
            "unit": "ns/iter",
            "extra": "iterations: 597504\ncpu: 1173.0164149528675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.47560156805029,
            "unit": "ns/iter",
            "extra": "iterations: 14521466\ncpu: 47.46042858207289 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1289.148112497205,
            "unit": "ns/iter",
            "extra": "iterations: 548529\ncpu: 1289.0038630592028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.85042375205872,
            "unit": "ns/iter",
            "extra": "iterations: 10955817\ncpu: 64.84390894809569 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.903842197898406,
            "unit": "ns/iter",
            "extra": "iterations: 11433612\ncpu: 62.77902381154777 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 189.65465932765048,
            "unit": "ns/iter",
            "extra": "iterations: 3704762\ncpu: 189.52715451087033 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 648.9219022503959,
            "unit": "ns/iter",
            "extra": "iterations: 1067073\ncpu: 648.4139323176596 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 118.2611663468097,
            "unit": "ns/iter",
            "extra": "iterations: 5653550\ncpu: 118.2257165851545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 318.53827708892044,
            "unit": "ns/iter",
            "extra": "iterations: 2160274\ncpu: 318.2008393379735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1002.5118347902072,
            "unit": "ns/iter",
            "extra": "iterations: 710321\ncpu: 1002.4003232341357 ns\nthreads: 1"
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
          "id": "d4edf7edb8e398d985ceb427d523197236735923",
          "message": "Don't allow empty children in `LoopItems` (#88)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:16:42-04:00",
          "tree_id": "f0aee869d630161b8c568eebf57cda33bfdc072e",
          "url": "https://github.com/sourcemeta/blaze/commit/d4edf7edb8e398d985ceb427d523197236735923"
        },
        "date": 1729870159492,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3328062917.000011,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3318501000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 528.1149404829731,
            "unit": "ns/iter",
            "extra": "iterations: 1337179\ncpu: 527.5942861800858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 783.6308055436053,
            "unit": "ns/iter",
            "extra": "iterations: 888009\ncpu: 783.6316974264906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 104.23982458308653,
            "unit": "ns/iter",
            "extra": "iterations: 6796380\ncpu: 104.19811723299756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 68.33093017134517,
            "unit": "ns/iter",
            "extra": "iterations: 10301844\ncpu: 68.28884226940343 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2053.6929071571235,
            "unit": "ns/iter",
            "extra": "iterations: 341330\ncpu: 2051.8003105499074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.06291706850798,
            "unit": "ns/iter",
            "extra": "iterations: 33285149\ncpu: 21.056808248026783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1297.480688186371,
            "unit": "ns/iter",
            "extra": "iterations: 555489\ncpu: 1297.383026486573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 949.4493814532964,
            "unit": "ns/iter",
            "extra": "iterations: 813358\ncpu: 949.0298245053243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1320.6699020999065,
            "unit": "ns/iter",
            "extra": "iterations: 537486\ncpu: 1319.031565473334 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 53.79984299197128,
            "unit": "ns/iter",
            "extra": "iterations: 13959796\ncpu: 53.76117244120179 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1426.4192840072712,
            "unit": "ns/iter",
            "extra": "iterations: 505061\ncpu: 1412.5838265080806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 70.47393352851093,
            "unit": "ns/iter",
            "extra": "iterations: 10202148\ncpu: 70.46829746049558 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 65.90054467152372,
            "unit": "ns/iter",
            "extra": "iterations: 10615389\ncpu: 65.86419018653007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.8417339402719,
            "unit": "ns/iter",
            "extra": "iterations: 3694614\ncpu: 190.66565546495505 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 657.4096037915871,
            "unit": "ns/iter",
            "extra": "iterations: 1093818\ncpu: 657.386329352784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.46582734177295,
            "unit": "ns/iter",
            "extra": "iterations: 4934442\ncpu: 131.40107837927775 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 379.13575303284574,
            "unit": "ns/iter",
            "extra": "iterations: 2000331\ncpu: 377.38154335457534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1659.1090203952028,
            "unit": "ns/iter",
            "extra": "iterations: 494036\ncpu: 1462.3327044992682 ns\nthreads: 1"
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
          "id": "98e11a50abbf6db70e8e7d6cdc79fb5bc1df0285",
          "message": "Ensure `LoopPropertiesExcept` is never emitted without children (#90)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:20:10-04:00",
          "tree_id": "ec5022edd896637145ae15a83d717209efe2ffc9",
          "url": "https://github.com/sourcemeta/blaze/commit/98e11a50abbf6db70e8e7d6cdc79fb5bc1df0285"
        },
        "date": 1729870417663,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3031861124.9999776,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3031577999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 549.7559910982475,
            "unit": "ns/iter",
            "extra": "iterations: 1338611\ncpu: 542.9344297932711 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 978.4439171305943,
            "unit": "ns/iter",
            "extra": "iterations: 878878\ncpu: 857.3271830675016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 102.62339784416153,
            "unit": "ns/iter",
            "extra": "iterations: 6932066\ncpu: 102.59755172556059 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 74.44155488089076,
            "unit": "ns/iter",
            "extra": "iterations: 9541464\ncpu: 72.25180538332484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2200.286357466874,
            "unit": "ns/iter",
            "extra": "iterations: 302070\ncpu: 2176.518687721388 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.305775611688844,
            "unit": "ns/iter",
            "extra": "iterations: 34431366\ncpu: 21.271360537946723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1198.0010554392268,
            "unit": "ns/iter",
            "extra": "iterations: 523005\ncpu: 1197.7896960832118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 868.742909855796,
            "unit": "ns/iter",
            "extra": "iterations: 823326\ncpu: 868.3680583389812 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1243.7245839293769,
            "unit": "ns/iter",
            "extra": "iterations: 562705\ncpu: 1243.0189886352532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 51.70533089005056,
            "unit": "ns/iter",
            "extra": "iterations: 14072303\ncpu: 51.56512050657227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1345.649853111853,
            "unit": "ns/iter",
            "extra": "iterations: 515358\ncpu: 1345.1057323258779 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.51226752699279,
            "unit": "ns/iter",
            "extra": "iterations: 10449009\ncpu: 67.22139869914949 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.954870774745,
            "unit": "ns/iter",
            "extra": "iterations: 11010271\ncpu: 63.946654900683164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 184.65906682520375,
            "unit": "ns/iter",
            "extra": "iterations: 3774684\ncpu: 184.65174833178074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 624.6657527226456,
            "unit": "ns/iter",
            "extra": "iterations: 1120054\ncpu: 624.5413167579417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 120.88837908599655,
            "unit": "ns/iter",
            "extra": "iterations: 5851717\ncpu: 120.80830293057619 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 337.3038193755581,
            "unit": "ns/iter",
            "extra": "iterations: 2117100\ncpu: 337.27599074205153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1050.934988145506,
            "unit": "ns/iter",
            "extra": "iterations: 691720\ncpu: 1050.5508009020966 ns\nthreads: 1"
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
          "id": "68f2bb13f9a4db4e484d6035e08fa2a3b1bbd480",
          "message": "Ensure `LoopPropertiesStartsWith` is not emitted with empty children (#91)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:23:23-04:00",
          "tree_id": "7b1bf64f017172f96943b313ac5a11fe9ca36d64",
          "url": "https://github.com/sourcemeta/blaze/commit/68f2bb13f9a4db4e484d6035e08fa2a3b1bbd480"
        },
        "date": 1729870559658,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3149600833.0000224,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3148556000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 524.3751199815157,
            "unit": "ns/iter",
            "extra": "iterations: 1339790\ncpu: 523.9089708088578 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 795.7422766034417,
            "unit": "ns/iter",
            "extra": "iterations: 895817\ncpu: 794.4747643770995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 104.78028094536714,
            "unit": "ns/iter",
            "extra": "iterations: 6573449\ncpu: 104.74957666819971 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 69.00451928171576,
            "unit": "ns/iter",
            "extra": "iterations: 10468699\ncpu: 68.87751763614573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2081.639690949489,
            "unit": "ns/iter",
            "extra": "iterations: 337291\ncpu: 2081.404484554883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.872116396354702,
            "unit": "ns/iter",
            "extra": "iterations: 33670196\ncpu: 20.866198699882844 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1224.729138690195,
            "unit": "ns/iter",
            "extra": "iterations: 564466\ncpu: 1224.5786282964793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 865.3842521279286,
            "unit": "ns/iter",
            "extra": "iterations: 830309\ncpu: 864.8996939693548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1259.4662420139177,
            "unit": "ns/iter",
            "extra": "iterations: 575686\ncpu: 1259.1238974024059 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 51.28082920000452,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 51.26329999999992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1398.4485211397682,
            "unit": "ns/iter",
            "extra": "iterations: 504003\ncpu: 1397.934139280921 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.57102317812316,
            "unit": "ns/iter",
            "extra": "iterations: 10031528\ncpu: 69.55700068823016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 67.32565607450938,
            "unit": "ns/iter",
            "extra": "iterations: 10394856\ncpu: 67.24576078783595 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 193.3285348432679,
            "unit": "ns/iter",
            "extra": "iterations: 3524442\ncpu: 193.17554381658127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 650.2631896749516,
            "unit": "ns/iter",
            "extra": "iterations: 1093033\ncpu: 649.9501844866529 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.77363974889944,
            "unit": "ns/iter",
            "extra": "iterations: 5430229\ncpu: 123.76107895265554 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 351.5438020111417,
            "unit": "ns/iter",
            "extra": "iterations: 2030215\ncpu: 351.4810007807049 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1049.619389570841,
            "unit": "ns/iter",
            "extra": "iterations: 665925\ncpu: 1049.5881668356053 ns\nthreads: 1"
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
          "id": "0c180c2b40e07ccf1d08534626d60b1ca7b2b14c",
          "message": "Ensure `LoopProperties(Evaluate)` is never emitted without children (#92)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:27:15-04:00",
          "tree_id": "c62216bda0f5b94821616ff8536d2675c9075f09",
          "url": "https://github.com/sourcemeta/blaze/commit/0c180c2b40e07ccf1d08534626d60b1ca7b2b14c"
        },
        "date": 1729870710764,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2839454584.000123,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2839075000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 497.61385574178195,
            "unit": "ns/iter",
            "extra": "iterations: 1443647\ncpu: 497.580779788965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 736.3079884573887,
            "unit": "ns/iter",
            "extra": "iterations: 948844\ncpu: 736.116790536695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.97132471684405,
            "unit": "ns/iter",
            "extra": "iterations: 7287112\ncpu: 95.96215894582117 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.48775338702322,
            "unit": "ns/iter",
            "extra": "iterations: 10838262\ncpu: 64.47140694698096 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1975.5829478048984,
            "unit": "ns/iter",
            "extra": "iterations: 350817\ncpu: 1975.4173828520263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.90824584021285,
            "unit": "ns/iter",
            "extra": "iterations: 34477663\ncpu: 19.906482640659277 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1234.7379926371395,
            "unit": "ns/iter",
            "extra": "iterations: 605212\ncpu: 1193.0629267099798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 813.3009888428332,
            "unit": "ns/iter",
            "extra": "iterations: 854231\ncpu: 812.9217974997401 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1179.4359310536372,
            "unit": "ns/iter",
            "extra": "iterations: 607892\ncpu: 1179.2407203911223 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.27345983076326,
            "unit": "ns/iter",
            "extra": "iterations: 14779220\ncpu: 48.27155966282392 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1298.9858634767302,
            "unit": "ns/iter",
            "extra": "iterations: 534502\ncpu: 1298.988591249428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.89100458708458,
            "unit": "ns/iter",
            "extra": "iterations: 10823850\ncpu: 64.88504552446682 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.65718192416995,
            "unit": "ns/iter",
            "extra": "iterations: 11479173\ncpu: 61.638063996421884 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.2064326104675,
            "unit": "ns/iter",
            "extra": "iterations: 3745198\ncpu: 182.0547271466028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 604.6886301788419,
            "unit": "ns/iter",
            "extra": "iterations: 1146113\ncpu: 604.6306079767008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 118.21548664177278,
            "unit": "ns/iter",
            "extra": "iterations: 5986385\ncpu: 118.21257737348995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 324.1826858436252,
            "unit": "ns/iter",
            "extra": "iterations: 2142016\ncpu: 324.18291926857677 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 976.0719526005953,
            "unit": "ns/iter",
            "extra": "iterations: 705659\ncpu: 975.638374909128 ns\nthreads: 1"
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
          "id": "527c3bb9f3effbde5e12582007ad9ceccc3c1f21",
          "message": "Ensure `LoopItemsUnevaluated` is never emitted without children (#93)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:32:09-04:00",
          "tree_id": "5bc2d43a654e0fa65892b417a51ca92b34b4981e",
          "url": "https://github.com/sourcemeta/blaze/commit/527c3bb9f3effbde5e12582007ad9ceccc3c1f21"
        },
        "date": 1729870955006,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4384718874.999976,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4382173000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 595.0348998160948,
            "unit": "ns/iter",
            "extra": "iterations: 1165307\ncpu: 595.0311806245054 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1067.6290220448716,
            "unit": "ns/iter",
            "extra": "iterations: 816469\ncpu: 1066.3478956335143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 122.92828743963308,
            "unit": "ns/iter",
            "extra": "iterations: 5470032\ncpu: 121.45705911775312 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 88.66118419756499,
            "unit": "ns/iter",
            "extra": "iterations: 8372505\ncpu: 88.62437227568076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2623.942811115609,
            "unit": "ns/iter",
            "extra": "iterations: 253266\ncpu: 2623.8342296241926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.348539986115647,
            "unit": "ns/iter",
            "extra": "iterations: 27109297\ncpu: 22.347499457473987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1403.604706816805,
            "unit": "ns/iter",
            "extra": "iterations: 490990\ncpu: 1403.006171205117 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 994.2247177606403,
            "unit": "ns/iter",
            "extra": "iterations: 670530\ncpu: 993.8973647711503 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1509.7052286973017,
            "unit": "ns/iter",
            "extra": "iterations: 514392\ncpu: 1508.2485730726764 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 56.5063593429995,
            "unit": "ns/iter",
            "extra": "iterations: 12374706\ncpu: 56.411845259192354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1596.001537022928,
            "unit": "ns/iter",
            "extra": "iterations: 480149\ncpu: 1593.1783675484066 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 85.5951616069195,
            "unit": "ns/iter",
            "extra": "iterations: 7555153\ncpu: 85.10085765304831 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 73.60096281790571,
            "unit": "ns/iter",
            "extra": "iterations: 10389919\ncpu: 73.5790144273501 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 229.13330165640718,
            "unit": "ns/iter",
            "extra": "iterations: 3186337\ncpu: 228.47363602782724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 605.967604155826,
            "unit": "ns/iter",
            "extra": "iterations: 1153080\ncpu: 605.777569639573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 152.8439444436691,
            "unit": "ns/iter",
            "extra": "iterations: 6068435\ncpu: 152.81485259379085 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 382.4645120747299,
            "unit": "ns/iter",
            "extra": "iterations: 1911143\ncpu: 382.3083882263128 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1161.6691948425237,
            "unit": "ns/iter",
            "extra": "iterations: 501020\ncpu: 1161.596343459345 ns\nthreads: 1"
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
          "id": "f995d37a0fcf8a7ee9cb25370fcec2d7f517543a",
          "message": "Ensure `LoopPropertiesUnevaluated(Except)` always has children (#94)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:32:29-04:00",
          "tree_id": "8f6181f02e8a0568b701347101dd4156b9333863",
          "url": "https://github.com/sourcemeta/blaze/commit/f995d37a0fcf8a7ee9cb25370fcec2d7f517543a"
        },
        "date": 1729871002182,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2760336625.0000362,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2760049000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 491.95037391880106,
            "unit": "ns/iter",
            "extra": "iterations: 1418891\ncpu: 491.944060537419 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 732.0814543330393,
            "unit": "ns/iter",
            "extra": "iterations: 944873\ncpu: 732.0063119593855 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.86060064900198,
            "unit": "ns/iter",
            "extra": "iterations: 7301935\ncpu: 95.84212951772359 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.96226429145753,
            "unit": "ns/iter",
            "extra": "iterations: 11010791\ncpu: 62.961870768412595 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1912.5306123560256,
            "unit": "ns/iter",
            "extra": "iterations: 366976\ncpu: 1912.4493154865738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.2985090664783,
            "unit": "ns/iter",
            "extra": "iterations: 36825049\ncpu: 19.288772704688093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1140.0916102335377,
            "unit": "ns/iter",
            "extra": "iterations: 623009\ncpu: 1140.0798383329923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 836.687269900861,
            "unit": "ns/iter",
            "extra": "iterations: 845288\ncpu: 836.5988870065568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1148.771659591331,
            "unit": "ns/iter",
            "extra": "iterations: 605390\ncpu: 1148.6628454384754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.96859399065345,
            "unit": "ns/iter",
            "extra": "iterations: 14946821\ncpu: 46.96771306754799 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1292.2053419084039,
            "unit": "ns/iter",
            "extra": "iterations: 548568\ncpu: 1292.118752825541 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.73235493718761,
            "unit": "ns/iter",
            "extra": "iterations: 10767077\ncpu: 64.73056707962613 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.127479335777025,
            "unit": "ns/iter",
            "extra": "iterations: 11467890\ncpu: 61.12310111101536 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.51701175827336,
            "unit": "ns/iter",
            "extra": "iterations: 3871146\ncpu: 182.50125415058002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 599.08507232123,
            "unit": "ns/iter",
            "extra": "iterations: 1158097\ncpu: 598.3462525159775 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 121.45791685178351,
            "unit": "ns/iter",
            "extra": "iterations: 6061393\ncpu: 120.60280532874181 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 320.3417904930138,
            "unit": "ns/iter",
            "extra": "iterations: 2115328\ncpu: 320.3342460365484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 982.1225371594142,
            "unit": "ns/iter",
            "extra": "iterations: 712135\ncpu: 981.9458389209906 ns\nthreads: 1"
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
          "id": "fbe713a6104bdfef7ca3f02e8287831c20535a82",
          "message": "Elevate empty children inefficient loop cases (#78)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:53:38-04:00",
          "tree_id": "bc30cc9948ab1615d5d66021d8468568530764c6",
          "url": "https://github.com/sourcemeta/blaze/commit/fbe713a6104bdfef7ca3f02e8287831c20535a82"
        },
        "date": 1729871868171,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3312150458.999895,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3256077000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 496.5322129932481,
            "unit": "ns/iter",
            "extra": "iterations: 1322277\ncpu: 496.41035879774086 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 732.1950571823099,
            "unit": "ns/iter",
            "extra": "iterations: 965158\ncpu: 731.8325082525348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.45343539950048,
            "unit": "ns/iter",
            "extra": "iterations: 7205130\ncpu: 96.44267348403149 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.728998677244995,
            "unit": "ns/iter",
            "extra": "iterations: 11222805\ncpu: 63.710988473915336 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1957.7224780945864,
            "unit": "ns/iter",
            "extra": "iterations: 362811\ncpu: 1957.2477129965728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.48573253694988,
            "unit": "ns/iter",
            "extra": "iterations: 36233947\ncpu: 19.461473518190008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1152.858774137635,
            "unit": "ns/iter",
            "extra": "iterations: 605484\ncpu: 1152.4433345885286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 834.5267050231748,
            "unit": "ns/iter",
            "extra": "iterations: 838625\ncpu: 834.394395588015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1173.2364833506135,
            "unit": "ns/iter",
            "extra": "iterations: 599002\ncpu: 1173.1580195057777 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.62289649823624,
            "unit": "ns/iter",
            "extra": "iterations: 14658949\ncpu: 50.167102702929164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1321.6691778590491,
            "unit": "ns/iter",
            "extra": "iterations: 503612\ncpu: 1316.1203466160441 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.31989798595004,
            "unit": "ns/iter",
            "extra": "iterations: 10963195\ncpu: 64.31081450252398 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 65.39142948102138,
            "unit": "ns/iter",
            "extra": "iterations: 11132138\ncpu: 65.38681069171082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 181.52887716405843,
            "unit": "ns/iter",
            "extra": "iterations: 3807680\ncpu: 181.43462685939983 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 597.9841160267847,
            "unit": "ns/iter",
            "extra": "iterations: 1174832\ncpu: 597.9544309314012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 120.69283096957102,
            "unit": "ns/iter",
            "extra": "iterations: 6014314\ncpu: 119.17917820719053 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 322.66805806301886,
            "unit": "ns/iter",
            "extra": "iterations: 2198990\ncpu: 321.81592458356056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 987.9207257015087,
            "unit": "ns/iter",
            "extra": "iterations: 703595\ncpu: 987.2881416155606 ns\nthreads: 1"
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
          "id": "7e1340f29e40cfce17e8541e3d4fdba2da0eae93",
          "message": "Fix `AssertionPropertyType` optimization not taking place with `required` (#95)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T11:56:25-04:00",
          "tree_id": "c042a7245e6abda3940143f8352b45e6b96a3dcb",
          "url": "https://github.com/sourcemeta/blaze/commit/7e1340f29e40cfce17e8541e3d4fdba2da0eae93"
        },
        "date": 1729872025647,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3010694625.000042,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3010159000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 520.6048836428882,
            "unit": "ns/iter",
            "extra": "iterations: 1343751\ncpu: 520.4491010611345 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 778.2584839929556,
            "unit": "ns/iter",
            "extra": "iterations: 905352\ncpu: 778.1238678436661 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 103.83590429552716,
            "unit": "ns/iter",
            "extra": "iterations: 6814310\ncpu: 103.82357127867697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.21469232270502,
            "unit": "ns/iter",
            "extra": "iterations: 11012350\ncpu: 64.21317884012038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2069.803257413637,
            "unit": "ns/iter",
            "extra": "iterations: 362926\ncpu: 2048.3266561227356 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.511606651082023,
            "unit": "ns/iter",
            "extra": "iterations: 33800749\ncpu: 21.298906719493136 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1247.2335969065293,
            "unit": "ns/iter",
            "extra": "iterations: 552914\ncpu: 1244.4882929352495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 868.2210828863937,
            "unit": "ns/iter",
            "extra": "iterations: 831186\ncpu: 868.0752563204843 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1233.1858218811356,
            "unit": "ns/iter",
            "extra": "iterations: 601194\ncpu: 1232.9830304361 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.19617080000671,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.196299999999994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1343.7231470135691,
            "unit": "ns/iter",
            "extra": "iterations: 511647\ncpu: 1343.6666295316893 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 66.10368421520049,
            "unit": "ns/iter",
            "extra": "iterations: 10688165\ncpu: 66.07270752276001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.419219272789974,
            "unit": "ns/iter",
            "extra": "iterations: 11244619\ncpu: 63.3620401011365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 179.80347087323977,
            "unit": "ns/iter",
            "extra": "iterations: 3897463\ncpu: 179.65225070770367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 628.2184545600805,
            "unit": "ns/iter",
            "extra": "iterations: 1169337\ncpu: 628.1627965248683 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 120.43634083462743,
            "unit": "ns/iter",
            "extra": "iterations: 5600851\ncpu: 120.43366267019097 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 318.9744050733146,
            "unit": "ns/iter",
            "extra": "iterations: 2158123\ncpu: 318.9563338141525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 977.1163386976341,
            "unit": "ns/iter",
            "extra": "iterations: 719580\ncpu: 977.0546707801764 ns\nthreads: 1"
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
          "id": "7e1340f29e40cfce17e8541e3d4fdba2da0eae93",
          "message": "Fix `AssertionPropertyType` optimization not taking place with `required` (#95)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T15:56:25Z",
          "url": "https://github.com/sourcemeta/blaze/commit/7e1340f29e40cfce17e8541e3d4fdba2da0eae93"
        },
        "date": 1729883255510,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3185435374.999997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3184557000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 563.9917705709682,
            "unit": "ns/iter",
            "extra": "iterations: 1282592\ncpu: 563.6913375414782 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 778.2188293523731,
            "unit": "ns/iter",
            "extra": "iterations: 914041\ncpu: 777.8305349541217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 99.31757495696775,
            "unit": "ns/iter",
            "extra": "iterations: 6792028\ncpu: 99.28772378441325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 71.40895144406763,
            "unit": "ns/iter",
            "extra": "iterations: 10385140\ncpu: 69.40994536424148 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2266.425283238314,
            "unit": "ns/iter",
            "extra": "iterations: 329317\ncpu: 2165.0203299556397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.1945493931766,
            "unit": "ns/iter",
            "extra": "iterations: 31794625\ncpu: 29.570406947715156 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1845.164439743284,
            "unit": "ns/iter",
            "extra": "iterations: 453765\ncpu: 1662.283340495632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1168.1813343322074,
            "unit": "ns/iter",
            "extra": "iterations: 702134\ncpu: 1100.7542719765734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1527.946471451817,
            "unit": "ns/iter",
            "extra": "iterations: 415610\ncpu: 1495.0602728519514 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.70305613501875,
            "unit": "ns/iter",
            "extra": "iterations: 13433896\ncpu: 50.67524715093835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1342.526749619214,
            "unit": "ns/iter",
            "extra": "iterations: 539503\ncpu: 1342.429977219774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 68.26764721742805,
            "unit": "ns/iter",
            "extra": "iterations: 10959419\ncpu: 68.2280693894447 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 66.59070816552051,
            "unit": "ns/iter",
            "extra": "iterations: 11253838\ncpu: 66.51632980677347 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.6975767519967,
            "unit": "ns/iter",
            "extra": "iterations: 3651958\ncpu: 190.4915116767509 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 627.4644951437593,
            "unit": "ns/iter",
            "extra": "iterations: 1053884\ncpu: 627.3176174987004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 118.33961760240128,
            "unit": "ns/iter",
            "extra": "iterations: 5930947\ncpu: 118.32461156709036 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 344.2087988247521,
            "unit": "ns/iter",
            "extra": "iterations: 2155697\ncpu: 342.86915090571716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1083.202347270242,
            "unit": "ns/iter",
            "extra": "iterations: 677553\ncpu: 1046.1720337744782 ns\nthreads: 1"
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
          "id": "45dceb0b71f3749f93b8e303ac11632321fedc4f",
          "message": "Unit test `ControlEvaluate` by `patternProperties` (#96)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-25T20:57:54-04:00",
          "tree_id": "16790f1e7337242341be5e45012b51baf100cabc",
          "url": "https://github.com/sourcemeta/blaze/commit/45dceb0b71f3749f93b8e303ac11632321fedc4f"
        },
        "date": 1729904477872,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2795550999.9999323,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2793794000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 489.38019831059245,
            "unit": "ns/iter",
            "extra": "iterations: 1430080\ncpu: 489.2096945625424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 747.4446202718341,
            "unit": "ns/iter",
            "extra": "iterations: 937157\ncpu: 747.4169216043848 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.13296434259337,
            "unit": "ns/iter",
            "extra": "iterations: 7182655\ncpu: 96.09635991148122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.61501910709194,
            "unit": "ns/iter",
            "extra": "iterations: 11176217\ncpu: 62.614031205729084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1921.642976120982,
            "unit": "ns/iter",
            "extra": "iterations: 366813\ncpu: 1921.3277610117407 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.35369278545176,
            "unit": "ns/iter",
            "extra": "iterations: 36528537\ncpu: 19.352677606551783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1145.1428998976517,
            "unit": "ns/iter",
            "extra": "iterations: 614801\ncpu: 1145.0957301630958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 849.6715164985744,
            "unit": "ns/iter",
            "extra": "iterations: 827795\ncpu: 849.6415175254745 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1152.360383580757,
            "unit": "ns/iter",
            "extra": "iterations: 612231\ncpu: 1152.2627896986567 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.44766984109756,
            "unit": "ns/iter",
            "extra": "iterations: 14942865\ncpu: 47.436084044124186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1259.6544650357148,
            "unit": "ns/iter",
            "extra": "iterations: 546457\ncpu: 1259.6105457519964 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 65.08884699239702,
            "unit": "ns/iter",
            "extra": "iterations: 10766746\ncpu: 65.08456686913577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.142588968757316,
            "unit": "ns/iter",
            "extra": "iterations: 11436600\ncpu: 61.1320672227761 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 176.64956370021218,
            "unit": "ns/iter",
            "extra": "iterations: 3941441\ncpu: 176.64732264164417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 596.7559165536431,
            "unit": "ns/iter",
            "extra": "iterations: 1178769\ncpu: 596.7454183135112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.89829755347286,
            "unit": "ns/iter",
            "extra": "iterations: 6062863\ncpu: 115.87396911327222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 317.4661394174736,
            "unit": "ns/iter",
            "extra": "iterations: 2205662\ncpu: 317.4579786023427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 967.8850041739101,
            "unit": "ns/iter",
            "extra": "iterations: 721174\ncpu: 967.7886335336593 ns\nthreads: 1"
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
            "email": "jv@jviotti.com",
            "name": "Juan Cruz Viotti",
            "username": "jviotti"
          },
          "distinct": true,
          "id": "fe1e12f641a5db73752ee2ce0ced55c45c3a16a6",
          "message": "Update README\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-28T09:04:28-04:00",
          "tree_id": "4c65c81a0483adc247961423fcf15c08fb060038",
          "url": "https://github.com/sourcemeta/blaze/commit/fe1e12f641a5db73752ee2ce0ced55c45c3a16a6"
        },
        "date": 1730120879230,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3015077333.000022,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2964413000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 487.5897427179325,
            "unit": "ns/iter",
            "extra": "iterations: 1441103\ncpu: 487.26773866961685 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 737.7417113013893,
            "unit": "ns/iter",
            "extra": "iterations: 950119\ncpu: 737.3476375064594 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.82267453336671,
            "unit": "ns/iter",
            "extra": "iterations: 7346074\ncpu: 95.793753234721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.84113978497308,
            "unit": "ns/iter",
            "extra": "iterations: 11223345\ncpu: 62.73263452206083 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1916.8114055825822,
            "unit": "ns/iter",
            "extra": "iterations: 365891\ncpu: 1916.0624338942462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.66027023954644,
            "unit": "ns/iter",
            "extra": "iterations: 35381054\ncpu: 19.652382317383736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1130.8238252317258,
            "unit": "ns/iter",
            "extra": "iterations: 611461\ncpu: 1130.660827100992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 803.5491935752308,
            "unit": "ns/iter",
            "extra": "iterations: 870571\ncpu: 803.4359058594879 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1153.3450412717937,
            "unit": "ns/iter",
            "extra": "iterations: 613373\ncpu: 1152.4243812492587 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.41661670546234,
            "unit": "ns/iter",
            "extra": "iterations: 14497916\ncpu: 48.4154412261734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1263.8370833835374,
            "unit": "ns/iter",
            "extra": "iterations: 556837\ncpu: 1262.7034482263216 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.53359030615935,
            "unit": "ns/iter",
            "extra": "iterations: 10962508\ncpu: 64.52255268593643 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.55817922926186,
            "unit": "ns/iter",
            "extra": "iterations: 11478985\ncpu: 61.54707929316065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 177.79802757341218,
            "unit": "ns/iter",
            "extra": "iterations: 3964254\ncpu: 177.7933502747309 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 595.4975131795243,
            "unit": "ns/iter",
            "extra": "iterations: 1167153\ncpu: 595.4669182189463 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.6609873942465,
            "unit": "ns/iter",
            "extra": "iterations: 6071435\ncpu: 115.65783047994418 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 318.3234661561136,
            "unit": "ns/iter",
            "extra": "iterations: 2202082\ncpu: 318.2969571523673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 972.0222539786915,
            "unit": "ns/iter",
            "extra": "iterations: 717265\ncpu: 971.9852495242308 ns\nthreads: 1"
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
            "email": "jv@jviotti.com",
            "name": "Juan Cruz Viotti",
            "username": "jviotti"
          },
          "distinct": true,
          "id": "600ab4b9d9174b725fa3f639045cfa9c3e972d0f",
          "message": "Announce `simdjson` future support\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-28T09:05:37-04:00",
          "tree_id": "5726bff2ead311f68567dbc24aebb0708e335d9c",
          "url": "https://github.com/sourcemeta/blaze/commit/600ab4b9d9174b725fa3f639045cfa9c3e972d0f"
        },
        "date": 1730120975385,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2794252207.999989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2793919000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 490.3215417214256,
            "unit": "ns/iter",
            "extra": "iterations: 1427625\ncpu: 490.3178355660629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 730.7155394973614,
            "unit": "ns/iter",
            "extra": "iterations: 959838\ncpu: 730.5389034399564 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 99.85990103238234,
            "unit": "ns/iter",
            "extra": "iterations: 6734525\ncpu: 99.81342410934705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 66.02453462655546,
            "unit": "ns/iter",
            "extra": "iterations: 10711881\ncpu: 65.94107981595381 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1974.8566164819072,
            "unit": "ns/iter",
            "extra": "iterations: 353360\ncpu: 1974.7792619424956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.481391010669,
            "unit": "ns/iter",
            "extra": "iterations: 36454156\ncpu: 19.479315335129442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1218.3807297633862,
            "unit": "ns/iter",
            "extra": "iterations: 624175\ncpu: 1218.1551648175587 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 816.2884432054119,
            "unit": "ns/iter",
            "extra": "iterations: 861199\ncpu: 816.2666236258985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1155.3323478468058,
            "unit": "ns/iter",
            "extra": "iterations: 612557\ncpu: 1155.0125131212283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.74822733705606,
            "unit": "ns/iter",
            "extra": "iterations: 14763946\ncpu: 47.72680691191925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1329.6813487444683,
            "unit": "ns/iter",
            "extra": "iterations: 539524\ncpu: 1329.4478095506406 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.97971542830408,
            "unit": "ns/iter",
            "extra": "iterations: 10508775\ncpu: 64.97893427159676 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.18766515913562,
            "unit": "ns/iter",
            "extra": "iterations: 11444266\ncpu: 61.174303358555214 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 179.17723385804214,
            "unit": "ns/iter",
            "extra": "iterations: 3966680\ncpu: 179.15914568354412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 596.1854248994624,
            "unit": "ns/iter",
            "extra": "iterations: 1175937\ncpu: 596.1144176941456 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 117.73371053169336,
            "unit": "ns/iter",
            "extra": "iterations: 6006212\ncpu: 117.65135829371368 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 321.88197878559515,
            "unit": "ns/iter",
            "extra": "iterations: 2170220\ncpu: 321.84985853968794 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 967.4750410240822,
            "unit": "ns/iter",
            "extra": "iterations: 718479\ncpu: 967.4548595018081 ns\nthreads: 1"
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
            "email": "jv@jviotti.com",
            "name": "Juan Cruz Viotti",
            "username": "jviotti"
          },
          "distinct": true,
          "id": "36175cb4c0481ef9b5f6399b65bd2fdab9a2a2c0",
          "message": "Simplify license file\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-28T09:49:19-04:00",
          "tree_id": "5d475fc123d218ad4924a07ce2b0fb33699043f1",
          "url": "https://github.com/sourcemeta/blaze/commit/36175cb4c0481ef9b5f6399b65bd2fdab9a2a2c0"
        },
        "date": 1730123591440,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2850783792.0000157,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2848394000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 501.9467500000019,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 501.73800000000045 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 747.7075772527865,
            "unit": "ns/iter",
            "extra": "iterations: 937345\ncpu: 747.4270412708227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 97.50438437017816,
            "unit": "ns/iter",
            "extra": "iterations: 7197499\ncpu: 97.50428586374244 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 66.51267456128123,
            "unit": "ns/iter",
            "extra": "iterations: 10895959\ncpu: 66.47877437864803 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2022.2058965286358,
            "unit": "ns/iter",
            "extra": "iterations: 352716\ncpu: 2021.6774969096962 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.056082753906455,
            "unit": "ns/iter",
            "extra": "iterations: 34095116\ncpu: 21.046562798026546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1196.4265491558308,
            "unit": "ns/iter",
            "extra": "iterations: 600456\ncpu: 1181.8601196424047 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 835.5763004254876,
            "unit": "ns/iter",
            "extra": "iterations: 864294\ncpu: 832.8115201540198 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1255.2282891916034,
            "unit": "ns/iter",
            "extra": "iterations: 597168\ncpu: 1255.0672507569045 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.44065839999803,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.419699999999956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1380.1021789007766,
            "unit": "ns/iter",
            "extra": "iterations: 479003\ncpu: 1379.937077638342 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 70.25368422837296,
            "unit": "ns/iter",
            "extra": "iterations: 10848676\ncpu: 70.24221204504579 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.85690549205712,
            "unit": "ns/iter",
            "extra": "iterations: 10840444\ncpu: 63.844894175921205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 186.8550838073984,
            "unit": "ns/iter",
            "extra": "iterations: 3765121\ncpu: 186.83197698028837 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 650.7538643233008,
            "unit": "ns/iter",
            "extra": "iterations: 1085507\ncpu: 650.3311355891769 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.04780614860908,
            "unit": "ns/iter",
            "extra": "iterations: 5593109\ncpu: 123.00707888939725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 341.1683347628258,
            "unit": "ns/iter",
            "extra": "iterations: 2090507\ncpu: 333.05891824327654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1038.344240007966,
            "unit": "ns/iter",
            "extra": "iterations: 709810\ncpu: 1010.292895281837 ns\nthreads: 1"
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
            "name": "Juan Cruz Viotti",
            "username": "jviotti",
            "email": "jv@jviotti.com"
          },
          "id": "36175cb4c0481ef9b5f6399b65bd2fdab9a2a2c0",
          "message": "Simplify license file\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-28T13:49:19Z",
          "url": "https://github.com/sourcemeta/blaze/commit/36175cb4c0481ef9b5f6399b65bd2fdab9a2a2c0"
        },
        "date": 1730142344762,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3085521833.0000296,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3045039000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 527.6983518098904,
            "unit": "ns/iter",
            "extra": "iterations: 1289111\ncpu: 513.4189375468824 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 819.9618203314212,
            "unit": "ns/iter",
            "extra": "iterations: 954068\ncpu: 794.1257855834174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 100.51662244963727,
            "unit": "ns/iter",
            "extra": "iterations: 6988260\ncpu: 100.48209425522228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.55512578191075,
            "unit": "ns/iter",
            "extra": "iterations: 11010964\ncpu: 64.53640208068981 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1963.3636743768259,
            "unit": "ns/iter",
            "extra": "iterations: 361117\ncpu: 1962.676916345675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.917435609678577,
            "unit": "ns/iter",
            "extra": "iterations: 35434247\ncpu: 19.913334125598904 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1170.5616167647604,
            "unit": "ns/iter",
            "extra": "iterations: 606223\ncpu: 1170.3317096184098 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 824.1067736580653,
            "unit": "ns/iter",
            "extra": "iterations: 826983\ncpu: 823.6287807609104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1184.9511991510974,
            "unit": "ns/iter",
            "extra": "iterations: 596547\ncpu: 1182.6679205494293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.88271573662768,
            "unit": "ns/iter",
            "extra": "iterations: 13105424\ncpu: 47.879564980118204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1323.9799803307508,
            "unit": "ns/iter",
            "extra": "iterations: 545014\ncpu: 1321.5385292854864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.97527500327095,
            "unit": "ns/iter",
            "extra": "iterations: 10741963\ncpu: 64.96466241784692 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.20854100968591,
            "unit": "ns/iter",
            "extra": "iterations: 11264523\ncpu: 62.200858394092556 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 181.3584449285754,
            "unit": "ns/iter",
            "extra": "iterations: 3858961\ncpu: 181.30398311877175 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 616.3368818583721,
            "unit": "ns/iter",
            "extra": "iterations: 1162173\ncpu: 616.156974908213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 119.44352145189275,
            "unit": "ns/iter",
            "extra": "iterations: 5897965\ncpu: 119.40881303975124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 325.083465652312,
            "unit": "ns/iter",
            "extra": "iterations: 2196712\ncpu: 324.9333549413858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 998.03728063177,
            "unit": "ns/iter",
            "extra": "iterations: 720535\ncpu: 997.9667885668318 ns\nthreads: 1"
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
          "id": "9f1aaf322f3a5636c5ed570b110589282fe01f87",
          "message": "Improve meta-schema testing for 2019-09 and Draft 4 (#98)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-28T17:20:03-04:00",
          "tree_id": "347a796ff05f721f76a03ca1f1689d0850cfe755",
          "url": "https://github.com/sourcemeta/blaze/commit/9f1aaf322f3a5636c5ed570b110589282fe01f87"
        },
        "date": 1730150607978,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2817061082.9999986,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2816853999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 526.9028825080053,
            "unit": "ns/iter",
            "extra": "iterations: 1346050\ncpu: 526.7478919802386 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 764.7078604402956,
            "unit": "ns/iter",
            "extra": "iterations: 950532\ncpu: 764.6980848619509 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 99.86026221541454,
            "unit": "ns/iter",
            "extra": "iterations: 7035742\ncpu: 99.83666257233422 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.31847999705562,
            "unit": "ns/iter",
            "extra": "iterations: 10805137\ncpu: 65.31199002844674 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2031.3349887478664,
            "unit": "ns/iter",
            "extra": "iterations: 352379\ncpu: 2031.0744964938349 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.06143657369073,
            "unit": "ns/iter",
            "extra": "iterations: 36206023\ncpu: 20.059342060297542 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1150.017968469487,
            "unit": "ns/iter",
            "extra": "iterations: 618194\ncpu: 1149.9254279400936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 839.3981707178019,
            "unit": "ns/iter",
            "extra": "iterations: 793426\ncpu: 839.3107863871346 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1194.5651571829533,
            "unit": "ns/iter",
            "extra": "iterations: 582760\ncpu: 1194.3166998421302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.882980630369296,
            "unit": "ns/iter",
            "extra": "iterations: 14365015\ncpu: 48.87868199232646 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1311.3543754233103,
            "unit": "ns/iter",
            "extra": "iterations: 521241\ncpu: 1311.159329369715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.15300162256493,
            "unit": "ns/iter",
            "extra": "iterations: 10183892\ncpu: 67.15114417945527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 64.19918132866108,
            "unit": "ns/iter",
            "extra": "iterations: 10965084\ncpu: 64.18984113573575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.58784886111576,
            "unit": "ns/iter",
            "extra": "iterations: 3809503\ncpu: 182.57053479154595 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 603.8467616640356,
            "unit": "ns/iter",
            "extra": "iterations: 1170138\ncpu: 603.0160545166456 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 118.66124078258213,
            "unit": "ns/iter",
            "extra": "iterations: 5983111\ncpu: 118.66117810617224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 329.2587324680544,
            "unit": "ns/iter",
            "extra": "iterations: 2057952\ncpu: 329.22876724044147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1012.9164702845123,
            "unit": "ns/iter",
            "extra": "iterations: 724353\ncpu: 1012.7134145920555 ns\nthreads: 1"
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
          "id": "9f1aaf322f3a5636c5ed570b110589282fe01f87",
          "message": "Improve meta-schema testing for 2019-09 and Draft 4 (#98)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-28T21:20:03Z",
          "url": "https://github.com/sourcemeta/blaze/commit/9f1aaf322f3a5636c5ed570b110589282fe01f87"
        },
        "date": 1730228668503,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2778740707.9999866,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2777669000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 495.12588484367893,
            "unit": "ns/iter",
            "extra": "iterations: 1435423\ncpu: 494.66603224276093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 766.0196621410191,
            "unit": "ns/iter",
            "extra": "iterations: 910735\ncpu: 763.821528765229 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 99.62196967372958,
            "unit": "ns/iter",
            "extra": "iterations: 7203721\ncpu: 99.25981308826371 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.520019794857376,
            "unit": "ns/iter",
            "extra": "iterations: 10823013\ncpu: 63.395100791249234 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1931.070371688186,
            "unit": "ns/iter",
            "extra": "iterations: 362589\ncpu: 1930.8693865506143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.76164609060261,
            "unit": "ns/iter",
            "extra": "iterations: 36187680\ncpu: 19.757746282712763 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1140.9866379462917,
            "unit": "ns/iter",
            "extra": "iterations: 621162\ncpu: 1140.866633824992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 828.3446374261443,
            "unit": "ns/iter",
            "extra": "iterations: 866058\ncpu: 828.0738703412492 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1159.998461967532,
            "unit": "ns/iter",
            "extra": "iterations: 613121\ncpu: 1159.7612869237912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.07738997565794,
            "unit": "ns/iter",
            "extra": "iterations: 14733058\ncpu: 47.060019718920465 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1285.0306629352433,
            "unit": "ns/iter",
            "extra": "iterations: 544925\ncpu: 1285.0025232830228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.45981093641285,
            "unit": "ns/iter",
            "extra": "iterations: 10938013\ncpu: 64.4515598948363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.60558992872887,
            "unit": "ns/iter",
            "extra": "iterations: 11455316\ncpu: 61.59638023080284 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 177.89222233241836,
            "unit": "ns/iter",
            "extra": "iterations: 3891938\ncpu: 177.86639972168194 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 606.8162245918921,
            "unit": "ns/iter",
            "extra": "iterations: 1174575\ncpu: 606.69263350574 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.21360672825305,
            "unit": "ns/iter",
            "extra": "iterations: 6077655\ncpu: 116.20583925872772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 318.17491410506443,
            "unit": "ns/iter",
            "extra": "iterations: 2211131\ncpu: 318.0815609749045 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1000.8045690951939,
            "unit": "ns/iter",
            "extra": "iterations: 724870\ncpu: 1000.5449252969502 ns\nthreads: 1"
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
          "id": "5efc2619f216fdccf2c92e385cb6362dc0fd8f1c",
          "message": "Cache compilation of subschemas for performance reasons (#100)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-29T19:20:33-04:00",
          "tree_id": "720c9ebde60e44cd324141c3a26ace71fdbc631b",
          "url": "https://github.com/sourcemeta/blaze/commit/5efc2619f216fdccf2c92e385cb6362dc0fd8f1c"
        },
        "date": 1730244262365,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 644958042.0000985,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 644673000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 508.0745626274594,
            "unit": "ns/iter",
            "extra": "iterations: 1290204\ncpu: 508.063065995765 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 768.6708267143226,
            "unit": "ns/iter",
            "extra": "iterations: 892618\ncpu: 768.6658794691566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 104.10115137415796,
            "unit": "ns/iter",
            "extra": "iterations: 7004413\ncpu: 104.08495330015522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 73.51413416581481,
            "unit": "ns/iter",
            "extra": "iterations: 10410625\ncpu: 73.47916191391006 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2035.2956751457673,
            "unit": "ns/iter",
            "extra": "iterations: 349769\ncpu: 2034.991665928083 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.120793209226917,
            "unit": "ns/iter",
            "extra": "iterations: 35343361\ncpu: 20.117752807945998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1185.7883771793363,
            "unit": "ns/iter",
            "extra": "iterations: 573785\ncpu: 1185.728103732233 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 847.3819136613349,
            "unit": "ns/iter",
            "extra": "iterations: 833115\ncpu: 847.3788132490721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1196.8307708350126,
            "unit": "ns/iter",
            "extra": "iterations: 575350\ncpu: 1196.8210654384297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 51.92494999998871,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 51.910099999999915 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1425.8354115383927,
            "unit": "ns/iter",
            "extra": "iterations: 482227\ncpu: 1425.515369317769 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.06574391866911,
            "unit": "ns/iter",
            "extra": "iterations: 9995145\ncpu: 68.96508254757683 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 67.64058278853761,
            "unit": "ns/iter",
            "extra": "iterations: 10505148\ncpu: 67.63560113574802 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 196.30540911938462,
            "unit": "ns/iter",
            "extra": "iterations: 3630517\ncpu: 196.30427291760319 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 680.5023201779321,
            "unit": "ns/iter",
            "extra": "iterations: 891742\ncpu: 680.1103906735365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 127.60798514580577,
            "unit": "ns/iter",
            "extra": "iterations: 5626422\ncpu: 127.02513249095061 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 338.88735902307474,
            "unit": "ns/iter",
            "extra": "iterations: 2034020\ncpu: 337.3895045279788 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1022.7084951576975,
            "unit": "ns/iter",
            "extra": "iterations: 687474\ncpu: 1022.62631023137 ns\nthreads: 1"
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
          "id": "0e58a7271c6ebfba924a580fd04dd146e8aaa018",
          "message": "Revert \"Cache compilation of subschemas for performance reasons (#100)\" (#103)\n\nThis reverts commit 5efc2619f216fdccf2c92e385cb6362dc0fd8f1c.\r\n\r\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T11:35:05-04:00",
          "tree_id": "347a796ff05f721f76a03ca1f1689d0850cfe755",
          "url": "https://github.com/sourcemeta/blaze/commit/0e58a7271c6ebfba924a580fd04dd146e8aaa018"
        },
        "date": 1730302705894,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2879968959.0000525,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2871813000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 508.6507278461986,
            "unit": "ns/iter",
            "extra": "iterations: 1414722\ncpu: 507.57675359540576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 756.7337122490097,
            "unit": "ns/iter",
            "extra": "iterations: 912956\ncpu: 755.471238482467 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 97.24035335612884,
            "unit": "ns/iter",
            "extra": "iterations: 7242778\ncpu: 97.13455251562324 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.25275129598515,
            "unit": "ns/iter",
            "extra": "iterations: 11200358\ncpu: 63.233782348742714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1922.4870763238787,
            "unit": "ns/iter",
            "extra": "iterations: 366111\ncpu: 1922.3705378969728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.434066450559452,
            "unit": "ns/iter",
            "extra": "iterations: 35882347\ncpu: 19.430501577837155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1175.449894140835,
            "unit": "ns/iter",
            "extra": "iterations: 613551\ncpu: 1175.219337919749 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 808.7124990821401,
            "unit": "ns/iter",
            "extra": "iterations: 857959\ncpu: 807.7309055560926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1155.730701505171,
            "unit": "ns/iter",
            "extra": "iterations: 605384\ncpu: 1154.8802082645077 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.024289688106066,
            "unit": "ns/iter",
            "extra": "iterations: 14931645\ncpu: 47.02288327910282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1275.409544241754,
            "unit": "ns/iter",
            "extra": "iterations: 554680\ncpu: 1274.7746448402672 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.24729330062945,
            "unit": "ns/iter",
            "extra": "iterations: 10936475\ncpu: 64.24464921284051 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.300139698326774,
            "unit": "ns/iter",
            "extra": "iterations: 11483316\ncpu: 61.275854465730944 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 177.03730785417653,
            "unit": "ns/iter",
            "extra": "iterations: 3936919\ncpu: 177.01989804717815 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 596.3330150986287,
            "unit": "ns/iter",
            "extra": "iterations: 1143810\ncpu: 596.0876369327071 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.84415179474813,
            "unit": "ns/iter",
            "extra": "iterations: 5949244\ncpu: 115.73604982414602 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 321.91657076709396,
            "unit": "ns/iter",
            "extra": "iterations: 2209777\ncpu: 321.8397150481712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1033.3674028526536,
            "unit": "ns/iter",
            "extra": "iterations: 723051\ncpu: 1003.3455454732812 ns\nthreads: 1"
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
          "id": "c3f2474a3cbd6ddc301e67a3074949bceed945d1",
          "message": "Implement a common helper for precompiling steps as marks (#104)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T11:51:09-04:00",
          "tree_id": "586ecb0058c3519b7e5be6585271090d8b3e4410",
          "url": "https://github.com/sourcemeta/blaze/commit/c3f2474a3cbd6ddc301e67a3074949bceed945d1"
        },
        "date": 1730303657315,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 2751583542.0000486,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 2750422999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 491.56124108421216,
            "unit": "ns/iter",
            "extra": "iterations: 1417986\ncpu: 491.08242253449635 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 749.9201723971241,
            "unit": "ns/iter",
            "extra": "iterations: 957789\ncpu: 741.042129320758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.30978400531968,
            "unit": "ns/iter",
            "extra": "iterations: 7234021\ncpu: 96.11611578125091 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.617795626099976,
            "unit": "ns/iter",
            "extra": "iterations: 11185861\ncpu: 62.61270366223936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1914.4670722045096,
            "unit": "ns/iter",
            "extra": "iterations: 364783\ncpu: 1913.7076015055532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.39728835212244,
            "unit": "ns/iter",
            "extra": "iterations: 36539405\ncpu: 19.394705524077335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1128.132471853076,
            "unit": "ns/iter",
            "extra": "iterations: 622804\ncpu: 1128.118958773548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 806.9260112426217,
            "unit": "ns/iter",
            "extra": "iterations: 868659\ncpu: 806.86437370706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1171.549027728772,
            "unit": "ns/iter",
            "extra": "iterations: 589136\ncpu: 1171.2422937997335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.948894235969654,
            "unit": "ns/iter",
            "extra": "iterations: 14926105\ncpu: 46.945201042067005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1280.0881068056788,
            "unit": "ns/iter",
            "extra": "iterations: 555326\ncpu: 1279.4538703392238 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.04629337061111,
            "unit": "ns/iter",
            "extra": "iterations: 10928109\ncpu: 64.03450038794452 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.19261642045572,
            "unit": "ns/iter",
            "extra": "iterations: 11453442\ncpu: 61.14843031465998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 181.2080487275184,
            "unit": "ns/iter",
            "extra": "iterations: 3887248\ncpu: 181.1927101126563 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 595.7144651638074,
            "unit": "ns/iter",
            "extra": "iterations: 1175818\ncpu: 595.6874278162077 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.03809520811033,
            "unit": "ns/iter",
            "extra": "iterations: 6034171\ncpu: 116.03582331359122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 327.66540052150333,
            "unit": "ns/iter",
            "extra": "iterations: 2206698\ncpu: 327.48386956438947 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1023.5585431431119,
            "unit": "ns/iter",
            "extra": "iterations: 688441\ncpu: 1017.7342720726969 ns\nthreads: 1"
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
          "id": "35ed20a512db9a1e8244ec24d716cb173dbd4104",
          "message": "Precompile up to 5 highly referenced static schemas (#105)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T12:33:39-04:00",
          "tree_id": "1a2c4286212344509302bd1aafb266a1f8dd0aa1",
          "url": "https://github.com/sourcemeta/blaze/commit/35ed20a512db9a1e8244ec24d716cb173dbd4104"
        },
        "date": 1730306293418,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 9097842916.999979,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 9094202999.999998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 542.7670186728656,
            "unit": "ns/iter",
            "extra": "iterations: 1063523\ncpu: 537.6028539110118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 833.5441552016836,
            "unit": "ns/iter",
            "extra": "iterations: 796486\ncpu: 827.4872376915599 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 97.6849222958337,
            "unit": "ns/iter",
            "extra": "iterations: 7321486\ncpu: 97.67238508685256 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.77173164037526,
            "unit": "ns/iter",
            "extra": "iterations: 10965256\ncpu: 65.50982485041847 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1995.175969673754,
            "unit": "ns/iter",
            "extra": "iterations: 345838\ncpu: 1992.3287782140787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.637794180773685,
            "unit": "ns/iter",
            "extra": "iterations: 34888879\ncpu: 19.629607474633936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1176.733565010906,
            "unit": "ns/iter",
            "extra": "iterations: 520551\ncpu: 1176.061519428451 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 820.5002474281182,
            "unit": "ns/iter",
            "extra": "iterations: 862877\ncpu: 819.3890902179568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1183.5515145393533,
            "unit": "ns/iter",
            "extra": "iterations: 603781\ncpu: 1183.5268085613802 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.21091096618459,
            "unit": "ns/iter",
            "extra": "iterations: 14397900\ncpu: 48.20126546232409 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1298.0996349706043,
            "unit": "ns/iter",
            "extra": "iterations: 532012\ncpu: 1297.7226077607222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 66.7195273608373,
            "unit": "ns/iter",
            "extra": "iterations: 10595144\ncpu: 66.70282159449647 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.04720869255887,
            "unit": "ns/iter",
            "extra": "iterations: 11242993\ncpu: 62.039263032539615 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 181.61183483655208,
            "unit": "ns/iter",
            "extra": "iterations: 3760711\ncpu: 181.61193455173776 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 625.5158421247378,
            "unit": "ns/iter",
            "extra": "iterations: 1137379\ncpu: 625.3394866618821 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.36183704466791,
            "unit": "ns/iter",
            "extra": "iterations: 5373043\ncpu: 125.322466244919 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 351.05424509700947,
            "unit": "ns/iter",
            "extra": "iterations: 2015961\ncpu: 350.9566901343847 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1028.5987711630144,
            "unit": "ns/iter",
            "extra": "iterations: 699035\ncpu: 1028.4635247162194 ns\nthreads: 1"
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
          "id": "df43a0886184e5826036983f536b6f9ea06362a7",
          "message": "Benchmark the OMC JSON v2 schema (#97)\n\nSee: https://github.com/MovieLabs/OMC/blob/main/OMC-JSON\r\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T12:45:04-04:00",
          "tree_id": "dc47298526ca4471528c8b748e23075ba7d6d880",
          "url": "https://github.com/sourcemeta/blaze/commit/df43a0886184e5826036983f536b6f9ea06362a7"
        },
        "date": 1730306920974,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 8403319667.000005,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8402032999.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 496.2594879012967,
            "unit": "ns/iter",
            "extra": "iterations: 1409611\ncpu: 496.2532216334863 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 731.6398038703311,
            "unit": "ns/iter",
            "extra": "iterations: 958550\ncpu: 731.5111366125906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.97594975742948,
            "unit": "ns/iter",
            "extra": "iterations: 7290072\ncpu: 95.97271467277687 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.02654833634079,
            "unit": "ns/iter",
            "extra": "iterations: 11185861\ncpu: 63.02062934627925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1919.5482493597192,
            "unit": "ns/iter",
            "extra": "iterations: 365352\ncpu: 1919.370908055796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.5522899754461,
            "unit": "ns/iter",
            "extra": "iterations: 36381591\ncpu: 19.54944741146702 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1134.308457456646,
            "unit": "ns/iter",
            "extra": "iterations: 625117\ncpu: 1134.0884986330557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 827.7883962599221,
            "unit": "ns/iter",
            "extra": "iterations: 844900\ncpu: 827.7452953012178 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1154.179576687629,
            "unit": "ns/iter",
            "extra": "iterations: 611605\ncpu: 1154.1517809697411 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.41202066501906,
            "unit": "ns/iter",
            "extra": "iterations: 14745690\ncpu: 47.40320731006833 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1266.6681982561702,
            "unit": "ns/iter",
            "extra": "iterations: 554979\ncpu: 1266.6353141289974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.20880627037053,
            "unit": "ns/iter",
            "extra": "iterations: 10934595\ncpu: 64.20786503752528 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.631376891112986,
            "unit": "ns/iter",
            "extra": "iterations: 11419436\ncpu: 62.626560541168665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 179.32421662245835,
            "unit": "ns/iter",
            "extra": "iterations: 3903418\ncpu: 179.3072122944558 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 602.149166456241,
            "unit": "ns/iter",
            "extra": "iterations: 1168205\ncpu: 602.1314752119684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.92103425759338,
            "unit": "ns/iter",
            "extra": "iterations: 6059767\ncpu: 115.9028061639994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 323.40737218050504,
            "unit": "ns/iter",
            "extra": "iterations: 2171108\ncpu: 323.2847007150258 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 58879.45583305156,
            "unit": "ns/iter",
            "extra": "iterations: 11932\ncpu: 58877.80757626575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 982.4232266788366,
            "unit": "ns/iter",
            "extra": "iterations: 718863\ncpu: 982.3832913920983 ns\nthreads: 1"
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
          "id": "df43a0886184e5826036983f536b6f9ea06362a7",
          "message": "Benchmark the OMC JSON v2 schema (#97)\n\nSee: https://github.com/MovieLabs/OMC/blob/main/OMC-JSON\r\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T16:45:04Z",
          "url": "https://github.com/sourcemeta/blaze/commit/df43a0886184e5826036983f536b6f9ea06362a7"
        },
        "date": 1730315127357,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 8514713292.0000105,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8511425999.999998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 502.3960061706798,
            "unit": "ns/iter",
            "extra": "iterations: 1400160\ncpu: 502.3597303165351 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 740.1047252736834,
            "unit": "ns/iter",
            "extra": "iterations: 957553\ncpu: 739.9684403891996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.18088214612507,
            "unit": "ns/iter",
            "extra": "iterations: 7302849\ncpu: 96.18027156250953 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.03545772623724,
            "unit": "ns/iter",
            "extra": "iterations: 11137629\ncpu: 63.033343990897926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1927.712164251452,
            "unit": "ns/iter",
            "extra": "iterations: 366122\ncpu: 1927.4777260039027 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.33660869248962,
            "unit": "ns/iter",
            "extra": "iterations: 35764831\ncpu: 19.335475120796698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1146.238135063474,
            "unit": "ns/iter",
            "extra": "iterations: 615785\ncpu: 1145.4939629903288 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 836.2844839645875,
            "unit": "ns/iter",
            "extra": "iterations: 829168\ncpu: 836.0091079250523 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1150.8706129904508,
            "unit": "ns/iter",
            "extra": "iterations: 608786\ncpu: 1150.8608936473602 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.59958192579493,
            "unit": "ns/iter",
            "extra": "iterations: 14697391\ncpu: 47.598243797147255 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1288.4400414740608,
            "unit": "ns/iter",
            "extra": "iterations: 547812\ncpu: 1288.321540966608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.2055461028041,
            "unit": "ns/iter",
            "extra": "iterations: 10933912\ncpu: 64.19486456448519 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.13073638054929,
            "unit": "ns/iter",
            "extra": "iterations: 11375640\ncpu: 61.12728602522578 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.92613209177318,
            "unit": "ns/iter",
            "extra": "iterations: 3894384\ncpu: 180.92180945689879 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 633.9272326281654,
            "unit": "ns/iter",
            "extra": "iterations: 1123127\ncpu: 628.810455095463 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 118.34396232927585,
            "unit": "ns/iter",
            "extra": "iterations: 5710323\ncpu: 118.12466650310274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 325.3088840724082,
            "unit": "ns/iter",
            "extra": "iterations: 2174926\ncpu: 325.29382608879564 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 60051.87652821415,
            "unit": "ns/iter",
            "extra": "iterations: 11533\ncpu: 60038.2380993673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 975.1279036622612,
            "unit": "ns/iter",
            "extra": "iterations: 708674\ncpu: 974.9983772510349 ns\nthreads: 1"
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
          "id": "5d15059abf74a7b7067cdaa48c45465955bee00c",
          "message": "Ignore meaningless `type` alongside `enum` or `const` (#106)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T17:36:22-04:00",
          "tree_id": "150748fa245d49c99f06ae3e6b8adfa8a72fcee1",
          "url": "https://github.com/sourcemeta/blaze/commit/5d15059abf74a7b7067cdaa48c45465955bee00c"
        },
        "date": 1730324449763,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 9964389417.000008,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 9957442000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 545.520541513215,
            "unit": "ns/iter",
            "extra": "iterations: 1397122\ncpu: 545.3518017753635 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 799.7932858473087,
            "unit": "ns/iter",
            "extra": "iterations: 727091\ncpu: 795.362616233731 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 102.67050464084193,
            "unit": "ns/iter",
            "extra": "iterations: 7205798\ncpu: 102.66399363401514 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 70.48913825008067,
            "unit": "ns/iter",
            "extra": "iterations: 9870555\ncpu: 70.44598809286839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2200.2269764623834,
            "unit": "ns/iter",
            "extra": "iterations: 326796\ncpu: 2199.613826362626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.943197933980557,
            "unit": "ns/iter",
            "extra": "iterations: 34744282\ncpu: 20.9198451704945 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1195.2624025151433,
            "unit": "ns/iter",
            "extra": "iterations: 603043\ncpu: 1194.0939534991685 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 832.8813400248978,
            "unit": "ns/iter",
            "extra": "iterations: 858790\ncpu: 832.470103284854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1224.4639845958227,
            "unit": "ns/iter",
            "extra": "iterations: 580099\ncpu: 1223.9290190122736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 49.79290952451425,
            "unit": "ns/iter",
            "extra": "iterations: 14418215\ncpu: 49.78841000775766 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1358.8225282584197,
            "unit": "ns/iter",
            "extra": "iterations: 550189\ncpu: 1358.6367593681423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 66.10165577709016,
            "unit": "ns/iter",
            "extra": "iterations: 10825189\ncpu: 66.09926163875764 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.24244869333318,
            "unit": "ns/iter",
            "extra": "iterations: 11444079\ncpu: 62.22283156206771 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 187.06466784912234,
            "unit": "ns/iter",
            "extra": "iterations: 3702489\ncpu: 187.01689593135944 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 620.8242810883772,
            "unit": "ns/iter",
            "extra": "iterations: 1137379\ncpu: 620.5759030191333 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 119.13419573778468,
            "unit": "ns/iter",
            "extra": "iterations: 5821012\ncpu: 119.13461095768254 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 322.65572465771584,
            "unit": "ns/iter",
            "extra": "iterations: 2144792\ncpu: 322.6559964789122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 60217.61787607913,
            "unit": "ns/iter",
            "extra": "iterations: 12072\ncpu: 60210.73558648104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 994.4131444204396,
            "unit": "ns/iter",
            "extra": "iterations: 691959\ncpu: 994.3594923976651 ns\nthreads: 1"
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
          "id": "3a5ec6d53d622a0095285729a9087d85d6e04163",
          "message": "Better group `LoopItems*` instructions (#107)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T17:44:26-04:00",
          "tree_id": "285d59adaa7f49627a201b8c706ee72f34c8a937",
          "url": "https://github.com/sourcemeta/blaze/commit/3a5ec6d53d622a0095285729a9087d85d6e04163"
        },
        "date": 1730324935997,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 8744287792.000023,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8741897000.000002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 513.42950812915,
            "unit": "ns/iter",
            "extra": "iterations: 1357958\ncpu: 513.4267775586569 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 761.8564717279811,
            "unit": "ns/iter",
            "extra": "iterations: 922752\ncpu: 761.8450027743103 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 99.47829332225976,
            "unit": "ns/iter",
            "extra": "iterations: 6907713\ncpu: 99.433198802556 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 67.45968251537887,
            "unit": "ns/iter",
            "extra": "iterations: 10553771\ncpu: 67.45835209045187 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1997.4327192476815,
            "unit": "ns/iter",
            "extra": "iterations: 336218\ncpu: 1997.0614303814784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.989077024937338,
            "unit": "ns/iter",
            "extra": "iterations: 35149032\ncpu: 19.987122262712695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1178.1073722736,
            "unit": "ns/iter",
            "extra": "iterations: 585803\ncpu: 1178.092293825743 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 851.2691452478019,
            "unit": "ns/iter",
            "extra": "iterations: 831551\ncpu: 851.2634823360188 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1222.5766586853963,
            "unit": "ns/iter",
            "extra": "iterations: 582615\ncpu: 1222.4625181294682 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.88134847041246,
            "unit": "ns/iter",
            "extra": "iterations: 14180719\ncpu: 48.874249606102545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1325.0160604434557,
            "unit": "ns/iter",
            "extra": "iterations: 532862\ncpu: 1324.9002556008918 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 66.75124641356751,
            "unit": "ns/iter",
            "extra": "iterations: 10585371\ncpu: 66.75099058880406 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.5599641265998,
            "unit": "ns/iter",
            "extra": "iterations: 11072270\ncpu: 63.55047338982861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.2461830931781,
            "unit": "ns/iter",
            "extra": "iterations: 3701099\ncpu: 190.24646463118137 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 626.0602256919746,
            "unit": "ns/iter",
            "extra": "iterations: 1125782\ncpu: 625.9453428816602 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 122.22330832106339,
            "unit": "ns/iter",
            "extra": "iterations: 5759042\ncpu: 122.22015397699755 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 332.2084660604891,
            "unit": "ns/iter",
            "extra": "iterations: 2118695\ncpu: 332.18608624648596 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 61220.99637274335,
            "unit": "ns/iter",
            "extra": "iterations: 11579\ncpu: 61211.935400293696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1044.107143883189,
            "unit": "ns/iter",
            "extra": "iterations: 661363\ncpu: 1044.0484272631 ns\nthreads: 1"
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
          "id": "c6d3c1707a2a272d4bb5c562e4b736a0dcf0715f",
          "message": "Implement new `LoopItemsType(Strict)` steps (#108)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T18:29:01-04:00",
          "tree_id": "4890e9e1d5c0ae959de23096833ab63322a3e381",
          "url": "https://github.com/sourcemeta/blaze/commit/c6d3c1707a2a272d4bb5c562e4b736a0dcf0715f"
        },
        "date": 1730327558348,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 8438338999.999928,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 8436850000.000002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 495.5153067939231,
            "unit": "ns/iter",
            "extra": "iterations: 1390461\ncpu: 495.4831527097848 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 752.0087304131581,
            "unit": "ns/iter",
            "extra": "iterations: 923324\ncpu: 751.8985751480517 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.73642413304417,
            "unit": "ns/iter",
            "extra": "iterations: 7357578\ncpu: 95.72864874827012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.23427693025983,
            "unit": "ns/iter",
            "extra": "iterations: 10921118\ncpu: 63.231163695878 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1030.9400530582411,
            "unit": "ns/iter",
            "extra": "iterations: 684155\ncpu: 1030.889199085002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.028777450008246,
            "unit": "ns/iter",
            "extra": "iterations: 36887146\ncpu: 19.028254449395458 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1132.0808913906544,
            "unit": "ns/iter",
            "extra": "iterations: 617507\ncpu: 1132.0600414246337 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 815.3857873323428,
            "unit": "ns/iter",
            "extra": "iterations: 861485\ncpu: 815.3711324050907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1165.4653501929797,
            "unit": "ns/iter",
            "extra": "iterations: 608950\ncpu: 1165.2828639461322 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.0443021525636,
            "unit": "ns/iter",
            "extra": "iterations: 14944556\ncpu: 47.037529920594686 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1267.489690749822,
            "unit": "ns/iter",
            "extra": "iterations: 549943\ncpu: 1267.409531533272 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.15579399452517,
            "unit": "ns/iter",
            "extra": "iterations: 10914137\ncpu: 64.15321706150472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 60.99373438688871,
            "unit": "ns/iter",
            "extra": "iterations: 11464321\ncpu: 60.99209887790154 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.2759342041,
            "unit": "ns/iter",
            "extra": "iterations: 3851487\ncpu: 180.24518841683658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 599.8176230360514,
            "unit": "ns/iter",
            "extra": "iterations: 1154296\ncpu: 599.7681703826424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.766991687546,
            "unit": "ns/iter",
            "extra": "iterations: 5986795\ncpu: 116.75412303244029 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 318.79079923928856,
            "unit": "ns/iter",
            "extra": "iterations: 2199992\ncpu: 318.77115916785186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 58220.72628523711,
            "unit": "ns/iter",
            "extra": "iterations: 12060\ncpu: 58214.096185737806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 990.2939538511353,
            "unit": "ns/iter",
            "extra": "iterations: 705325\ncpu: 990.2385425158586 ns\nthreads: 1"
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
          "id": "745015c7d5d133419d7fb56f5676fb3c1f120af9",
          "message": "Only emit `ControlLabel` when really needed (#101)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T19:13:15-04:00",
          "tree_id": "7269c47ae45b5057fcd642302d22dfcb431fb27e",
          "url": "https://github.com/sourcemeta/blaze/commit/745015c7d5d133419d7fb56f5676fb3c1f120af9"
        },
        "date": 1730330303928,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 29642821207.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 29614189000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 491.4403400204919,
            "unit": "ns/iter",
            "extra": "iterations: 1419444\ncpu: 491.29588768560075 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 727.074631073548,
            "unit": "ns/iter",
            "extra": "iterations: 961235\ncpu: 727.0074435491834 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.5051545097784,
            "unit": "ns/iter",
            "extra": "iterations: 7328922\ncpu: 96.49331784401569 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.639456498300106,
            "unit": "ns/iter",
            "extra": "iterations: 11220646\ncpu: 62.6374809436104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1022.6313158305335,
            "unit": "ns/iter",
            "extra": "iterations: 682907\ncpu: 1022.4642594086743 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.049801364195012,
            "unit": "ns/iter",
            "extra": "iterations: 36854131\ncpu: 19.048230983929706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1126.61467963777,
            "unit": "ns/iter",
            "extra": "iterations: 620969\ncpu: 1126.5779773225531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 817.1196622233662,
            "unit": "ns/iter",
            "extra": "iterations: 864358\ncpu: 817.0908350475183 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1180.6451161483783,
            "unit": "ns/iter",
            "extra": "iterations: 608833\ncpu: 1180.6242434296335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.86400190119555,
            "unit": "ns/iter",
            "extra": "iterations: 14925341\ncpu: 46.862714895425015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1273.6347650655434,
            "unit": "ns/iter",
            "extra": "iterations: 555155\ncpu: 1273.6136754599975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.45501391390381,
            "unit": "ns/iter",
            "extra": "iterations: 10928279\ncpu: 64.27352376343912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.436249182542845,
            "unit": "ns/iter",
            "extra": "iterations: 11466951\ncpu: 61.10682778708973 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.53612169742445,
            "unit": "ns/iter",
            "extra": "iterations: 3892868\ncpu: 180.53322126514493 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 594.879357606765,
            "unit": "ns/iter",
            "extra": "iterations: 1172117\ncpu: 594.8732080500474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.82577076169612,
            "unit": "ns/iter",
            "extra": "iterations: 6074543\ncpu: 115.81233353685828 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 318.5317624175699,
            "unit": "ns/iter",
            "extra": "iterations: 2215905\ncpu: 318.4391930159446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 55583.01602538912,
            "unit": "ns/iter",
            "extra": "iterations: 12605\ncpu: 55581.19793732694 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 982.2207281870091,
            "unit": "ns/iter",
            "extra": "iterations: 714322\ncpu: 982.2111036759387 ns\nthreads: 1"
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
          "id": "dc33bf9a7022fc55b189a5666843c33b088f7620",
          "message": "Introduce a new `LoopPropertiesTypeStrictAny(Evaluate)` step (#109)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T19:15:48-04:00",
          "tree_id": "ab942df2bcf3c630552da8ed895593c4765eda4d",
          "url": "https://github.com/sourcemeta/blaze/commit/dc33bf9a7022fc55b189a5666843c33b088f7620"
        },
        "date": 1730330465108,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 29780810792.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 29775599000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 508.1412723395093,
            "unit": "ns/iter",
            "extra": "iterations: 1339328\ncpu: 507.9913210206886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 770.1540861090806,
            "unit": "ns/iter",
            "extra": "iterations: 936392\ncpu: 770.0909448179784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 98.51815784558886,
            "unit": "ns/iter",
            "extra": "iterations: 6866178\ncpu: 98.51434087493706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.45615090684227,
            "unit": "ns/iter",
            "extra": "iterations: 11228385\ncpu: 62.45590973234412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1065.1856171880054,
            "unit": "ns/iter",
            "extra": "iterations: 659718\ncpu: 1065.1172167501893 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 18.966892895022855,
            "unit": "ns/iter",
            "extra": "iterations: 37013928\ncpu: 18.96534731466493 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1143.142548567934,
            "unit": "ns/iter",
            "extra": "iterations: 615271\ncpu: 1142.90775934507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 819.5989815765921,
            "unit": "ns/iter",
            "extra": "iterations: 862706\ncpu: 819.5816419498689 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1164.2442526893785,
            "unit": "ns/iter",
            "extra": "iterations: 608415\ncpu: 1164.2332947083821 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.9047272133522,
            "unit": "ns/iter",
            "extra": "iterations: 14883610\ncpu: 46.89500732685138 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1268.530477593288,
            "unit": "ns/iter",
            "extra": "iterations: 554719\ncpu: 1268.4332067226792 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.21770303732126,
            "unit": "ns/iter",
            "extra": "iterations: 10897147\ncpu: 64.21653300629949 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.43494564466157,
            "unit": "ns/iter",
            "extra": "iterations: 11471461\ncpu: 61.245729728758654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 186.28133525902908,
            "unit": "ns/iter",
            "extra": "iterations: 3894016\ncpu: 184.51824543093957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 637.4148158872124,
            "unit": "ns/iter",
            "extra": "iterations: 1084363\ncpu: 631.0820269596082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.84330057552093,
            "unit": "ns/iter",
            "extra": "iterations: 6024719\ncpu: 115.84224924017269 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 318.87244186829145,
            "unit": "ns/iter",
            "extra": "iterations: 2188218\ncpu: 318.85351459498156 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 60261.790602383,
            "unit": "ns/iter",
            "extra": "iterations: 11471\ncpu: 60252.98579025417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1019.4912759620975,
            "unit": "ns/iter",
            "extra": "iterations: 708101\ncpu: 1019.1032070283895 ns\nthreads: 1"
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
          "id": "1618517d3cb855ea38bd0cbd08365aed39540302",
          "message": "Implement a new `AssertionPropertyTypeStrictAny(Evaluate)` (#110)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T20:41:34-04:00",
          "tree_id": "36429f6d0ff393203c57f598d8e9db247df635cc",
          "url": "https://github.com/sourcemeta/blaze/commit/1618517d3cb855ea38bd0cbd08365aed39540302"
        },
        "date": 1730335722943,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 32879888166.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 32826400000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 503.0811292861495,
            "unit": "ns/iter",
            "extra": "iterations: 1421854\ncpu: 501.0001026828375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 759.8925713094916,
            "unit": "ns/iter",
            "extra": "iterations: 939358\ncpu: 759.4942503284148 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 102.0721666763026,
            "unit": "ns/iter",
            "extra": "iterations: 7261260\ncpu: 102.01672987883614 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 69.79031492935968,
            "unit": "ns/iter",
            "extra": "iterations: 10105822\ncpu: 69.7739382308535 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1115.9692437237595,
            "unit": "ns/iter",
            "extra": "iterations: 596171\ncpu: 1115.4433878870402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.019061456040106,
            "unit": "ns/iter",
            "extra": "iterations: 32765860\ncpu: 21.018645626881092 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1206.0341993055574,
            "unit": "ns/iter",
            "extra": "iterations: 565684\ncpu: 1205.514032569428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 839.4274515604941,
            "unit": "ns/iter",
            "extra": "iterations: 845125\ncpu: 839.3066114480115 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1193.6338053493482,
            "unit": "ns/iter",
            "extra": "iterations: 595107\ncpu: 1183.298129580058 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.66770782931022,
            "unit": "ns/iter",
            "extra": "iterations: 14595222\ncpu: 48.32026535807437 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1279.9125767384319,
            "unit": "ns/iter",
            "extra": "iterations: 537866\ncpu: 1279.902429229592 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.45390126916963,
            "unit": "ns/iter",
            "extra": "iterations: 10829040\ncpu: 64.45141951641135 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.14066177301227,
            "unit": "ns/iter",
            "extra": "iterations: 11246787\ncpu: 61.13950588732605 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 184.22971632325212,
            "unit": "ns/iter",
            "extra": "iterations: 3959366\ncpu: 184.19287330345298 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 610.1540796458664,
            "unit": "ns/iter",
            "extra": "iterations: 1102657\ncpu: 610.1063159259818 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 129.42572094311132,
            "unit": "ns/iter",
            "extra": "iterations: 6081721\ncpu: 129.31767175771435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 323.11998224315073,
            "unit": "ns/iter",
            "extra": "iterations: 2173805\ncpu: 323.0933777408777 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 55952.96172210876,
            "unit": "ns/iter",
            "extra": "iterations: 12566\ncpu: 55950.18303358243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 975.3134059758197,
            "unit": "ns/iter",
            "extra": "iterations: 709594\ncpu: 975.2675473580607 ns\nthreads: 1"
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
          "id": "5b9326d897d51e15ce9b6f2855f6fe4c183e212a",
          "message": "Don't print template as JSON in `contrib/validate.cc` (#113)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-30T23:07:11-04:00",
          "tree_id": "3cce57f38c39aae37a04eb9e9cc416737e84e037",
          "url": "https://github.com/sourcemeta/blaze/commit/5b9326d897d51e15ce9b6f2855f6fe4c183e212a"
        },
        "date": 1730344395337,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 30930996624.99992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 30779427000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 512.3862683762517,
            "unit": "ns/iter",
            "extra": "iterations: 1435067\ncpu: 511.4381419125414 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 732.3000174062615,
            "unit": "ns/iter",
            "extra": "iterations: 953678\ncpu: 732.0342924970456 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.63601006346053,
            "unit": "ns/iter",
            "extra": "iterations: 7350162\ncpu: 95.60183843566978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.963640628189836,
            "unit": "ns/iter",
            "extra": "iterations: 11230007\ncpu: 62.94617625794866 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1044.3542544039442,
            "unit": "ns/iter",
            "extra": "iterations: 662490\ncpu: 1044.3131217075124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.31056240457691,
            "unit": "ns/iter",
            "extra": "iterations: 37052917\ncpu: 19.297616973044207 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1166.2679457476224,
            "unit": "ns/iter",
            "extra": "iterations: 609448\ncpu: 1166.1880915188754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 837.221980316451,
            "unit": "ns/iter",
            "extra": "iterations: 851571\ncpu: 836.6254839584803 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1163.0870914068892,
            "unit": "ns/iter",
            "extra": "iterations: 603412\ncpu: 1162.9964269852094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.374632653813954,
            "unit": "ns/iter",
            "extra": "iterations: 14877315\ncpu: 47.31176290883112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1305.9757576422146,
            "unit": "ns/iter",
            "extra": "iterations: 547059\ncpu: 1302.2434508891952 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.98291148868307,
            "unit": "ns/iter",
            "extra": "iterations: 10301541\ncpu: 67.97293725278584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 64.30948325171853,
            "unit": "ns/iter",
            "extra": "iterations: 11003694\ncpu: 64.27950468270035 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 187.44418297113938,
            "unit": "ns/iter",
            "extra": "iterations: 3663004\ncpu: 187.37626276138204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 644.2620407341337,
            "unit": "ns/iter",
            "extra": "iterations: 1132759\ncpu: 644.0143048962792 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 121.77139067433029,
            "unit": "ns/iter",
            "extra": "iterations: 5837614\ncpu: 121.75111269775581 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 351.03133034270604,
            "unit": "ns/iter",
            "extra": "iterations: 2049036\ncpu: 350.85962374501673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 55988.30977620573,
            "unit": "ns/iter",
            "extra": "iterations: 12735\ncpu: 55978.170396545545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 966.7591537473647,
            "unit": "ns/iter",
            "extra": "iterations: 720825\ncpu: 966.6590365206365 ns\nthreads: 1"
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
          "id": "2facf29a9bad8ba9345bd3feb325ae967dc30840",
          "message": "Always unroll `properties` directly inside `anyOf` (#114)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-31T09:06:10-04:00",
          "tree_id": "1ea942b0b079160167f7a585e90f605f04bc8bc4",
          "url": "https://github.com/sourcemeta/blaze/commit/2facf29a9bad8ba9345bd3feb325ae967dc30840"
        },
        "date": 1730380388859,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 36722520583.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 36630719000.00001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 581.6015664754445,
            "unit": "ns/iter",
            "extra": "iterations: 1196827\ncpu: 581.4240487555847 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 863.803350964551,
            "unit": "ns/iter",
            "extra": "iterations: 818809\ncpu: 862.589443936256 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 132.02630090182043,
            "unit": "ns/iter",
            "extra": "iterations: 5849077\ncpu: 130.8281631443724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 87.64072464749505,
            "unit": "ns/iter",
            "extra": "iterations: 7888746\ncpu: 86.42995984406215 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1392.8849011803989,
            "unit": "ns/iter",
            "extra": "iterations: 468328\ncpu: 1353.7776942655541 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 28.729465621258075,
            "unit": "ns/iter",
            "extra": "iterations: 24721006\ncpu: 28.03563091243137 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1528.6888722028775,
            "unit": "ns/iter",
            "extra": "iterations: 539370\ncpu: 1528.05495300074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1083.0931549293932,
            "unit": "ns/iter",
            "extra": "iterations: 684215\ncpu: 1079.9850924051673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1477.2606532148932,
            "unit": "ns/iter",
            "extra": "iterations: 420413\ncpu: 1476.4862171245866 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 65.04259297000355,
            "unit": "ns/iter",
            "extra": "iterations: 12723109\ncpu: 64.34803002945299 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1691.0967848812604,
            "unit": "ns/iter",
            "extra": "iterations: 371246\ncpu: 1656.3949510566956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.62118471179407,
            "unit": "ns/iter",
            "extra": "iterations: 9685900\ncpu: 69.61634953902093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 66.42852464125225,
            "unit": "ns/iter",
            "extra": "iterations: 10518723\ncpu: 66.42593402259928 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 194.2011913644232,
            "unit": "ns/iter",
            "extra": "iterations: 3660341\ncpu: 194.1600523011385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 667.3463437590368,
            "unit": "ns/iter",
            "extra": "iterations: 1066683\ncpu: 666.9432249318656 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 127.9144885203768,
            "unit": "ns/iter",
            "extra": "iterations: 5550974\ncpu: 127.82387379224038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 353.6676588676597,
            "unit": "ns/iter",
            "extra": "iterations: 2013705\ncpu: 352.6435103453566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 21331.200488925697,
            "unit": "ns/iter",
            "extra": "iterations: 33543\ncpu: 21323.197090301954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1057.6706663615398,
            "unit": "ns/iter",
            "extra": "iterations: 646466\ncpu: 1057.260551985712 ns\nthreads: 1"
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
          "id": "d7f32f8ae5436ed2e58486bb9e465fd43aedf6b4",
          "message": "Always evaluate `type` after `properties` (#115)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-31T10:24:30-04:00",
          "tree_id": "3a6e72d05af887e90da8ffeba028a5f24ff5016b",
          "url": "https://github.com/sourcemeta/blaze/commit/d7f32f8ae5436ed2e58486bb9e465fd43aedf6b4"
        },
        "date": 1730385108973,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 46451263583.000015,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 46271955000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 726.0249588218288,
            "unit": "ns/iter",
            "extra": "iterations: 869392\ncpu: 723.8472403702784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1014.6494520702273,
            "unit": "ns/iter",
            "extra": "iterations: 770993\ncpu: 1011.8950496307997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 132.51631695480856,
            "unit": "ns/iter",
            "extra": "iterations: 5589983\ncpu: 132.34226293711515 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 82.19697722949871,
            "unit": "ns/iter",
            "extra": "iterations: 8007687\ncpu: 82.07026573341246 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1464.5559048834768,
            "unit": "ns/iter",
            "extra": "iterations: 506369\ncpu: 1462.569786065104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.54093455378162,
            "unit": "ns/iter",
            "extra": "iterations: 22555834\ncpu: 29.49800038429076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1548.7544182591541,
            "unit": "ns/iter",
            "extra": "iterations: 487296\ncpu: 1545.7463225636861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1230.2605626555146,
            "unit": "ns/iter",
            "extra": "iterations: 602358\ncpu: 1184.3521626673908 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1471.9934673173198,
            "unit": "ns/iter",
            "extra": "iterations: 490457\ncpu: 1461.6204886463015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 65.85711368217524,
            "unit": "ns/iter",
            "extra": "iterations: 10008579\ncpu: 65.06178349593878 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1801.2616549622426,
            "unit": "ns/iter",
            "extra": "iterations: 401846\ncpu: 1796.5837659202593 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.72183224458156,
            "unit": "ns/iter",
            "extra": "iterations: 7760274\ncpu: 82.63123183537087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 80.82849905528973,
            "unit": "ns/iter",
            "extra": "iterations: 7822540\ncpu: 80.75982992736338 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 266.2490301102008,
            "unit": "ns/iter",
            "extra": "iterations: 2925590\ncpu: 265.53823331362054 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 867.1535758242493,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 864.8862210329424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 154.38241618820982,
            "unit": "ns/iter",
            "extra": "iterations: 5325057\ncpu: 154.25938163666655 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 429.0467336979955,
            "unit": "ns/iter",
            "extra": "iterations: 1562256\ncpu: 428.3804958982363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 20581.966243977015,
            "unit": "ns/iter",
            "extra": "iterations: 33831\ncpu: 20581.12382134775 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1114.626684412957,
            "unit": "ns/iter",
            "extra": "iterations: 622101\ncpu: 1114.0586496404862 ns\nthreads: 1"
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
          "id": "686561f77ab063146020d990e9874270635f6986",
          "message": "Recursively consider template size when re-ordering `properties` (#117)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-31T11:30:33-04:00",
          "tree_id": "219b98f53aadd43e8a0913df5075f8ea4048ab24",
          "url": "https://github.com/sourcemeta/blaze/commit/686561f77ab063146020d990e9874270635f6986"
        },
        "date": 1730389030853,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 33683677874.999943,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 33635635000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 527.4672774968413,
            "unit": "ns/iter",
            "extra": "iterations: 1319734\ncpu: 527.4184040117134 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 806.5326802119098,
            "unit": "ns/iter",
            "extra": "iterations: 897332\ncpu: 806.2400538485248 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 130.07073811880008,
            "unit": "ns/iter",
            "extra": "iterations: 6295870\ncpu: 130.00856116787784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 76.70122675992671,
            "unit": "ns/iter",
            "extra": "iterations: 9097053\ncpu: 76.68219587156379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1196.4843964353877,
            "unit": "ns/iter",
            "extra": "iterations: 601369\ncpu: 1196.486682885215 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.97195268622417,
            "unit": "ns/iter",
            "extra": "iterations: 33383090\ncpu: 20.954920590035222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1247.999554339831,
            "unit": "ns/iter",
            "extra": "iterations: 572185\ncpu: 1247.9495268138826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 904.6196635698567,
            "unit": "ns/iter",
            "extra": "iterations: 809202\ncpu: 896.7451884696277 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1242.9669315917183,
            "unit": "ns/iter",
            "extra": "iterations: 575383\ncpu: 1242.78610942624 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 52.01181112555704,
            "unit": "ns/iter",
            "extra": "iterations: 13673210\ncpu: 51.61860309320162 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1429.939635788382,
            "unit": "ns/iter",
            "extra": "iterations: 481643\ncpu: 1429.3532761817319 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 70.40906216013215,
            "unit": "ns/iter",
            "extra": "iterations: 10098387\ncpu: 70.39104363895022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 67.90524996549657,
            "unit": "ns/iter",
            "extra": "iterations: 10446202\ncpu: 67.87548240020556 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 200.5503935948233,
            "unit": "ns/iter",
            "extra": "iterations: 3543873\ncpu: 200.5029525606573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 649.1663165046267,
            "unit": "ns/iter",
            "extra": "iterations: 1086164\ncpu: 648.8955627327084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 137.68143168828277,
            "unit": "ns/iter",
            "extra": "iterations: 5456048\ncpu: 137.63900170966122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 352.80739587430065,
            "unit": "ns/iter",
            "extra": "iterations: 1714875\ncpu: 352.75982214447214 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 19993.410586470105,
            "unit": "ns/iter",
            "extra": "iterations: 35347\ncpu: 19964.29682858494 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1065.0642647855664,
            "unit": "ns/iter",
            "extra": "iterations: 660066\ncpu: 1064.8616956485891 ns\nthreads: 1"
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
          "id": "544b91a2b1b772c7ced9640a6b76c3a947984fc5",
          "message": "Prevent empty children in `Control` steps (#118)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-31T12:36:53-04:00",
          "tree_id": "d5a89fa639f6af00b111ce2c76da5c464befabc7",
          "url": "https://github.com/sourcemeta/blaze/commit/544b91a2b1b772c7ced9640a6b76c3a947984fc5"
        },
        "date": 1730392952946,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 29526657750.000027,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 29523927000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 498.05238372573,
            "unit": "ns/iter",
            "extra": "iterations: 1402783\ncpu: 498.0086014729295 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 749.6026760610467,
            "unit": "ns/iter",
            "extra": "iterations: 938992\ncpu: 749.5537768159958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 97.02542640420829,
            "unit": "ns/iter",
            "extra": "iterations: 7260130\ncpu: 97.01658234769867 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.35478062101769,
            "unit": "ns/iter",
            "extra": "iterations: 11218668\ncpu: 63.33024562274314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1077.724166514365,
            "unit": "ns/iter",
            "extra": "iterations: 634564\ncpu: 1077.6974426535446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.962633451700192,
            "unit": "ns/iter",
            "extra": "iterations: 34743937\ncpu: 20.955512324351698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1245.3613631551236,
            "unit": "ns/iter",
            "extra": "iterations: 585436\ncpu: 1245.0515513224227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 863.9013993886588,
            "unit": "ns/iter",
            "extra": "iterations: 770908\ncpu: 863.8073544443639 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1179.7348539190566,
            "unit": "ns/iter",
            "extra": "iterations: 557636\ncpu: 1179.4270814653282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 49.07351697683835,
            "unit": "ns/iter",
            "extra": "iterations: 14150133\ncpu: 49.07169423778588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1326.4411362363182,
            "unit": "ns/iter",
            "extra": "iterations: 532178\ncpu: 1326.4434080326446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.46371999934584,
            "unit": "ns/iter",
            "extra": "iterations: 10174862\ncpu: 67.46381425124027 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.810938622387894,
            "unit": "ns/iter",
            "extra": "iterations: 10946223\ncpu: 62.627812351347224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 186.27465522219308,
            "unit": "ns/iter",
            "extra": "iterations: 3826015\ncpu: 186.2724009184481 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 616.1607488611182,
            "unit": "ns/iter",
            "extra": "iterations: 1142428\ncpu: 613.2640306435108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 119.0468149024587,
            "unit": "ns/iter",
            "extra": "iterations: 5892504\ncpu: 119.02630867963782 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 316.6837097739922,
            "unit": "ns/iter",
            "extra": "iterations: 2235058\ncpu: 316.00387998879495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 18554.229326085922,
            "unit": "ns/iter",
            "extra": "iterations: 33847\ncpu: 18552.161195970333 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 990.371934480251,
            "unit": "ns/iter",
            "extra": "iterations: 699392\ncpu: 990.3516196925348 ns\nthreads: 1"
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
          "id": "544b91a2b1b772c7ced9640a6b76c3a947984fc5",
          "message": "Prevent empty children in `Control` steps (#118)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-31T16:36:53Z",
          "url": "https://github.com/sourcemeta/blaze/commit/544b91a2b1b772c7ced9640a6b76c3a947984fc5"
        },
        "date": 1730401591035,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 29234193666.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 29221509999.999996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 496.4246147929084,
            "unit": "ns/iter",
            "extra": "iterations: 1409242\ncpu: 496.4009020452112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 746.34872128673,
            "unit": "ns/iter",
            "extra": "iterations: 938678\ncpu: 746.2740151574861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 97.52781512580606,
            "unit": "ns/iter",
            "extra": "iterations: 6976420\ncpu: 97.5256650259025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.76677138159217,
            "unit": "ns/iter",
            "extra": "iterations: 11214893\ncpu: 62.76671565212488 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1025.5076606561838,
            "unit": "ns/iter",
            "extra": "iterations: 680490\ncpu: 1025.4022836485542 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.18466740126865,
            "unit": "ns/iter",
            "extra": "iterations: 36528537\ncpu: 19.184014952474186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1140.7429044569033,
            "unit": "ns/iter",
            "extra": "iterations: 620777\ncpu: 1140.2194346762205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 816.486555935429,
            "unit": "ns/iter",
            "extra": "iterations: 862388\ncpu: 816.4631233273167 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1148.563057977497,
            "unit": "ns/iter",
            "extra": "iterations: 612928\ncpu: 1148.5117338415077 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.86634297667241,
            "unit": "ns/iter",
            "extra": "iterations: 14929511\ncpu: 46.86570109362562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1283.5134955937556,
            "unit": "ns/iter",
            "extra": "iterations: 548994\ncpu: 1283.44025617767 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 63.93264984149175,
            "unit": "ns/iter",
            "extra": "iterations: 10943998\ncpu: 63.92691226734562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.23507526938895,
            "unit": "ns/iter",
            "extra": "iterations: 11463758\ncpu: 61.11634596613085 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 181.76309289731287,
            "unit": "ns/iter",
            "extra": "iterations: 3851974\ncpu: 181.75979380961513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 601.509364840894,
            "unit": "ns/iter",
            "extra": "iterations: 1158749\ncpu: 601.4676172320269 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 117.20051582806772,
            "unit": "ns/iter",
            "extra": "iterations: 5979124\ncpu: 117.1954286280069 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 307.999671772153,
            "unit": "ns/iter",
            "extra": "iterations: 2269765\ncpu: 307.98078215145654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 18534.015020943676,
            "unit": "ns/iter",
            "extra": "iterations: 37481\ncpu: 18532.429764414388 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 989.5803399371615,
            "unit": "ns/iter",
            "extra": "iterations: 709896\ncpu: 989.3251969302621 ns\nthreads: 1"
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
          "id": "1e66a60b8b0fde1d0327de2b27185a0190a2f408",
          "message": "Prioritize properties with `const`/`enum` when unrolling (#121)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-31T16:49:37-04:00",
          "tree_id": "af384acd04ef9cc855f580f84a2fcc4599eabe18",
          "url": "https://github.com/sourcemeta/blaze/commit/1e66a60b8b0fde1d0327de2b27185a0190a2f408"
        },
        "date": 1730408263237,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 36950017667,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 36593684999.99999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 529.8134302484843,
            "unit": "ns/iter",
            "extra": "iterations: 1303684\ncpu: 527.8886601354277 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 826.9717292924352,
            "unit": "ns/iter",
            "extra": "iterations: 886536\ncpu: 826.5462429049758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 103.75046545241302,
            "unit": "ns/iter",
            "extra": "iterations: 6666095\ncpu: 103.71694372792449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 70.26207402780918,
            "unit": "ns/iter",
            "extra": "iterations: 10382368\ncpu: 69.57767245391473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1166.9398376250165,
            "unit": "ns/iter",
            "extra": "iterations: 602187\ncpu: 1164.5668206055486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.830357230565667,
            "unit": "ns/iter",
            "extra": "iterations: 33796996\ncpu: 20.824986930790985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1247.3980525380648,
            "unit": "ns/iter",
            "extra": "iterations: 565762\ncpu: 1246.3739169474102 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 924.643745100037,
            "unit": "ns/iter",
            "extra": "iterations: 789533\ncpu: 924.5199377353379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1381.8059516747458,
            "unit": "ns/iter",
            "extra": "iterations: 505740\ncpu: 1363.552418238631 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 51.30421350114437,
            "unit": "ns/iter",
            "extra": "iterations: 13580630\ncpu: 51.281936110475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1354.817250480138,
            "unit": "ns/iter",
            "extra": "iterations: 506212\ncpu: 1354.2211563534852 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 68.44679289243214,
            "unit": "ns/iter",
            "extra": "iterations: 10330274\ncpu: 68.4320667583453 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 66.05226233913602,
            "unit": "ns/iter",
            "extra": "iterations: 10603008\ncpu: 66.04257961514288 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.20143097937137,
            "unit": "ns/iter",
            "extra": "iterations: 3562595\ncpu: 190.07521202943508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 704.4744375544399,
            "unit": "ns/iter",
            "extra": "iterations: 1114330\ncpu: 702.3126003966474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.14855992029396,
            "unit": "ns/iter",
            "extra": "iterations: 5348697\ncpu: 123.14008439812554 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 331.5881586531801,
            "unit": "ns/iter",
            "extra": "iterations: 2145989\ncpu: 331.5674031879937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 20256.121681806988,
            "unit": "ns/iter",
            "extra": "iterations: 33678\ncpu: 20245.857830037658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1061.6912269147701,
            "unit": "ns/iter",
            "extra": "iterations: 683340\ncpu: 1061.6047648315619 ns\nthreads: 1"
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
          "id": "424f351a1f1eec2a97a6ec9fa668547df4addca4",
          "message": "Don't unroll `properties` when referenced from `anyOf` or `oneOf` (#120)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-31T17:13:45-04:00",
          "tree_id": "47ea1b90d863155b18c961fff017b608f55473fd",
          "url": "https://github.com/sourcemeta/blaze/commit/424f351a1f1eec2a97a6ec9fa668547df4addca4"
        },
        "date": 1730409573439,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 38582686291.00008,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 38562740000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 541.8695339908046,
            "unit": "ns/iter",
            "extra": "iterations: 1304631\ncpu: 541.8405664130314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 808.4133110832829,
            "unit": "ns/iter",
            "extra": "iterations: 852733\ncpu: 808.3690909112167 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 115.0436026199102,
            "unit": "ns/iter",
            "extra": "iterations: 6189651\ncpu: 114.29125810162779 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 75.3665283645994,
            "unit": "ns/iter",
            "extra": "iterations: 9340183\ncpu: 75.30355668620228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1195.372163049749,
            "unit": "ns/iter",
            "extra": "iterations: 575530\ncpu: 1182.0304762566616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.041174930060112,
            "unit": "ns/iter",
            "extra": "iterations: 33159012\ncpu: 22.041187475670384 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1278.2866583658526,
            "unit": "ns/iter",
            "extra": "iterations: 540511\ncpu: 1277.5873201470492 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 995.9153606745737,
            "unit": "ns/iter",
            "extra": "iterations: 616262\ncpu: 982.4749862882925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1319.6288581970593,
            "unit": "ns/iter",
            "extra": "iterations: 506033\ncpu: 1312.6614272191787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 51.642415180209355,
            "unit": "ns/iter",
            "extra": "iterations: 13966759\ncpu: 51.63961087894476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1377.4971919339816,
            "unit": "ns/iter",
            "extra": "iterations: 514411\ncpu: 1376.5335500212839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.57563233799479,
            "unit": "ns/iter",
            "extra": "iterations: 10136114\ncpu: 69.57518433592985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 65.55773070763397,
            "unit": "ns/iter",
            "extra": "iterations: 10852881\ncpu: 65.54075364873165 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 188.22817509155436,
            "unit": "ns/iter",
            "extra": "iterations: 3717255\ncpu: 188.17783552648447 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 633.0322617721916,
            "unit": "ns/iter",
            "extra": "iterations: 1096251\ncpu: 633.0238239235362 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.60126250249016,
            "unit": "ns/iter",
            "extra": "iterations: 5285851\ncpu: 124.55685943474374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 347.0030132820787,
            "unit": "ns/iter",
            "extra": "iterations: 2133554\ncpu: 346.7603819729929 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 9099.874325308476,
            "unit": "ns/iter",
            "extra": "iterations: 80963\ncpu: 9099.230512703114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1069.9606883911667,
            "unit": "ns/iter",
            "extra": "iterations: 656371\ncpu: 1069.5186106638012 ns\nthreads: 1"
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
          "id": "ab0abb93735dfed17107d73b0d47f02793e47f86",
          "message": "Make `contrib/validate.cc` measure individual runs (#123)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-31T17:57:42-04:00",
          "tree_id": "f662c6faebbecf5c06c381a1a91c4b75a38e9269",
          "url": "https://github.com/sourcemeta/blaze/commit/ab0abb93735dfed17107d73b0d47f02793e47f86"
        },
        "date": 1730412278989,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 34579604541.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 34427310000.00001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 545.169936882316,
            "unit": "ns/iter",
            "extra": "iterations: 1139935\ncpu: 544.7319364700548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 790.1360893169359,
            "unit": "ns/iter",
            "extra": "iterations: 838273\ncpu: 790.0958279701292 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 104.95279300903552,
            "unit": "ns/iter",
            "extra": "iterations: 6724110\ncpu: 104.87692795031533 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 68.44445210251176,
            "unit": "ns/iter",
            "extra": "iterations: 10214356\ncpu: 68.43211652305853 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1112.5132202893622,
            "unit": "ns/iter",
            "extra": "iterations: 628428\ncpu: 1112.4186064274675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.737942227975616,
            "unit": "ns/iter",
            "extra": "iterations: 33874355\ncpu: 20.722785717986376 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1273.577257587501,
            "unit": "ns/iter",
            "extra": "iterations: 568339\ncpu: 1262.8149748653484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 912.9968356571808,
            "unit": "ns/iter",
            "extra": "iterations: 768564\ncpu: 912.31439411682 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1309.5300150017486,
            "unit": "ns/iter",
            "extra": "iterations: 572597\ncpu: 1295.3700421063947 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 51.48673506401872,
            "unit": "ns/iter",
            "extra": "iterations: 13930071\ncpu: 51.47504273309144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1385.4208545506576,
            "unit": "ns/iter",
            "extra": "iterations: 512550\ncpu: 1385.369232270021 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 73.41149936168966,
            "unit": "ns/iter",
            "extra": "iterations: 9971510\ncpu: 73.3527820761339 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 66.73881027574211,
            "unit": "ns/iter",
            "extra": "iterations: 10688981\ncpu: 66.71795936394679 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 192.84617353689083,
            "unit": "ns/iter",
            "extra": "iterations: 3590130\ncpu: 192.80276758780437 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 647.7104715160202,
            "unit": "ns/iter",
            "extra": "iterations: 1089613\ncpu: 647.6336093640566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.09381335201525,
            "unit": "ns/iter",
            "extra": "iterations: 5582894\ncpu: 125.08530521983882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 329.31975007124936,
            "unit": "ns/iter",
            "extra": "iterations: 2119324\ncpu: 329.29273674058464 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 9449.480822458934,
            "unit": "ns/iter",
            "extra": "iterations: 80928\ncpu: 9364.262060102932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1075.3441096393015,
            "unit": "ns/iter",
            "extra": "iterations: 672896\ncpu: 1072.840379493999 ns\nthreads: 1"
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
          "id": "9edbfaeceb9a2ab546e93103488e74ba0875f8e9",
          "message": "Implement a tool to study validation traces (#124)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-01T12:51:21-04:00",
          "tree_id": "235b63a7df123440956ff410217cbb1a257dff92",
          "url": "https://github.com/sourcemeta/blaze/commit/9edbfaeceb9a2ab546e93103488e74ba0875f8e9"
        },
        "date": 1730480392172,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 38893839374.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 38813838000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 524.4971393301984,
            "unit": "ns/iter",
            "extra": "iterations: 1255650\ncpu: 524.4072790984718 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 812.2410914560851,
            "unit": "ns/iter",
            "extra": "iterations: 866219\ncpu: 809.856398901439 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 106.12179398084227,
            "unit": "ns/iter",
            "extra": "iterations: 6496881\ncpu: 106.11307179552715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 81.46135236005004,
            "unit": "ns/iter",
            "extra": "iterations: 10265284\ncpu: 80.47677979488961 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1158.0348987819198,
            "unit": "ns/iter",
            "extra": "iterations: 508012\ncpu: 1157.2246324889873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.558374277343447,
            "unit": "ns/iter",
            "extra": "iterations: 32251971\ncpu: 26.473761867142926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1337.4598639761223,
            "unit": "ns/iter",
            "extra": "iterations: 488738\ncpu: 1336.6548130081887 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 892.4513026709307,
            "unit": "ns/iter",
            "extra": "iterations: 767999\ncpu: 892.3761619481284 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1389.9591768019882,
            "unit": "ns/iter",
            "extra": "iterations: 585084\ncpu: 1382.013522844594 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 52.086295853601264,
            "unit": "ns/iter",
            "extra": "iterations: 13716615\ncpu: 52.07130184815996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1367.6734660647824,
            "unit": "ns/iter",
            "extra": "iterations: 509751\ncpu: 1367.4735311946304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 73.03343995917258,
            "unit": "ns/iter",
            "extra": "iterations: 10154199\ncpu: 73.02141705121169 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 75.61398852486556,
            "unit": "ns/iter",
            "extra": "iterations: 8381427\ncpu: 75.6114680710101 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 208.5539574067942,
            "unit": "ns/iter",
            "extra": "iterations: 2853649\ncpu: 208.55403029594765 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 753.3147990293602,
            "unit": "ns/iter",
            "extra": "iterations: 1087497\ncpu: 752.8140307513557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 147.49408248037966,
            "unit": "ns/iter",
            "extra": "iterations: 5508558\ncpu: 142.84645818379485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 340.5318385291894,
            "unit": "ns/iter",
            "extra": "iterations: 2053424\ncpu: 340.1947186747621 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 10445.791602995394,
            "unit": "ns/iter",
            "extra": "iterations: 67405\ncpu: 10237.267265039727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1264.1245497107275,
            "unit": "ns/iter",
            "extra": "iterations: 648472\ncpu: 1228.3043832270298 ns\nthreads: 1"
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
          "id": "9edbfaeceb9a2ab546e93103488e74ba0875f8e9",
          "message": "Implement a tool to study validation traces (#124)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-01T16:51:21Z",
          "url": "https://github.com/sourcemeta/blaze/commit/9edbfaeceb9a2ab546e93103488e74ba0875f8e9"
        },
        "date": 1730488037319,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 35051734417.00003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 34984574000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 547.0893387548207,
            "unit": "ns/iter",
            "extra": "iterations: 1023811\ncpu: 547.0472577458171 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 780.5506499049568,
            "unit": "ns/iter",
            "extra": "iterations: 899824\ncpu: 780.4926296698022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 102.86253340323856,
            "unit": "ns/iter",
            "extra": "iterations: 6853003\ncpu: 102.84469450837686 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 67.92648038452695,
            "unit": "ns/iter",
            "extra": "iterations: 10449633\ncpu: 67.92506492811759 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1096.2579705149492,
            "unit": "ns/iter",
            "extra": "iterations: 638290\ncpu: 1095.9689169499616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.66523578991131,
            "unit": "ns/iter",
            "extra": "iterations: 33994775\ncpu: 20.65214433688699 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1256.1800704210127,
            "unit": "ns/iter",
            "extra": "iterations: 573409\ncpu: 1245.2281007099637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 893.1537513089473,
            "unit": "ns/iter",
            "extra": "iterations: 790764\ncpu: 884.7886347886399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1244.6982861456117,
            "unit": "ns/iter",
            "extra": "iterations: 561658\ncpu: 1244.4459083641702 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.83139578130561,
            "unit": "ns/iter",
            "extra": "iterations: 13846854\ncpu: 50.823313367787065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1363.304407906155,
            "unit": "ns/iter",
            "extra": "iterations: 508019\ncpu: 1361.626238388711 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.21521722758182,
            "unit": "ns/iter",
            "extra": "iterations: 10171314\ncpu: 69.20826552007001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 66.53132389502042,
            "unit": "ns/iter",
            "extra": "iterations: 10605418\ncpu: 66.50346077825452 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 194.56141829726582,
            "unit": "ns/iter",
            "extra": "iterations: 3682331\ncpu: 194.5235232791414 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 660.2957180347348,
            "unit": "ns/iter",
            "extra": "iterations: 1047136\ncpu: 660.1874064113899 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.05969385267434,
            "unit": "ns/iter",
            "extra": "iterations: 5477951\ncpu: 125.05588312126267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 337.4593812602964,
            "unit": "ns/iter",
            "extra": "iterations: 2075089\ncpu: 337.22312633337594 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 9100.200059498331,
            "unit": "ns/iter",
            "extra": "iterations: 77312\ncpu: 9097.837334437108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1062.1200966942129,
            "unit": "ns/iter",
            "extra": "iterations: 656088\ncpu: 1062.0785626318357 ns\nthreads: 1"
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
          "id": "a7885ab63fcbb4f8d974e574a34bd9c5ccf31a2c",
          "message": "Support relative base URIs (#125)\n\nSee: https://github.com/sourcemeta/jsonschema/issues/185\r\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-04T11:46:55-04:00",
          "tree_id": "266838dc292788a2a1e66bf9834c78435c25b391",
          "url": "https://github.com/sourcemeta/blaze/commit/a7885ab63fcbb4f8d974e574a34bd9c5ccf31a2c"
        },
        "date": 1730735614716,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 31074146250.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 31069530000.000004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 521.2759579999329,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 521.2199999999925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 785.6619797925852,
            "unit": "ns/iter",
            "extra": "iterations: 898680\ncpu: 785.604442070592 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 102.55611823473649,
            "unit": "ns/iter",
            "extra": "iterations: 6777298\ncpu: 102.5458818543917 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 67.27259611072401,
            "unit": "ns/iter",
            "extra": "iterations: 10502626\ncpu: 67.22452080079806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1092.204489032542,
            "unit": "ns/iter",
            "extra": "iterations: 627173\ncpu: 1092.1229070766656 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.211266506688084,
            "unit": "ns/iter",
            "extra": "iterations: 36988111\ncpu: 19.208983124334008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1198.909415008684,
            "unit": "ns/iter",
            "extra": "iterations: 589325\ncpu: 1198.764688414715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 877.6640551995679,
            "unit": "ns/iter",
            "extra": "iterations: 802614\ncpu: 877.4529225754857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1335.7647092958932,
            "unit": "ns/iter",
            "extra": "iterations: 551437\ncpu: 1334.6075798323375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.32947201535641,
            "unit": "ns/iter",
            "extra": "iterations: 14610728\ncpu: 47.328237169290794 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1292.5440012408596,
            "unit": "ns/iter",
            "extra": "iterations: 554473\ncpu: 1286.4161104327966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 65.61758819177084,
            "unit": "ns/iter",
            "extra": "iterations: 10721068\ncpu: 65.21085399327723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.12978463607471,
            "unit": "ns/iter",
            "extra": "iterations: 10837423\ncpu: 61.12836972405738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 184.13532530103225,
            "unit": "ns/iter",
            "extra": "iterations: 3821983\ncpu: 184.13556522883408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 604.0921404209513,
            "unit": "ns/iter",
            "extra": "iterations: 1164299\ncpu: 604.0578923455254 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 119.09369797236293,
            "unit": "ns/iter",
            "extra": "iterations: 5955369\ncpu: 119.08716319677316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 318.24201896979224,
            "unit": "ns/iter",
            "extra": "iterations: 2249365\ncpu: 318.2142515776685 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8383.881614575896,
            "unit": "ns/iter",
            "extra": "iterations: 83093\ncpu: 8382.67964810506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 993.7151469426792,
            "unit": "ns/iter",
            "extra": "iterations: 707793\ncpu: 993.5560255611456 ns\nthreads: 1"
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
          "id": "85ad5e81fcdde6b36a00d5c762bd91f3b1f81902",
          "message": "Benchmark OMC schema compilation time (#126)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-04T11:47:15-04:00",
          "tree_id": "2642598de04e83457c99d7f4ba88e7acf87568ed",
          "url": "https://github.com/sourcemeta/blaze/commit/85ad5e81fcdde6b36a00d5c762bd91f3b1f81902"
        },
        "date": 1730735661466,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 34311233000.000015,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 34271357000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6820977707.999987,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6758767999.999996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 514.7881576245488,
            "unit": "ns/iter",
            "extra": "iterations: 1285536\ncpu: 511.1190974037315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 754.9070034590774,
            "unit": "ns/iter",
            "extra": "iterations: 936680\ncpu: 754.7155912371433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 99.69681798834884,
            "unit": "ns/iter",
            "extra": "iterations: 7299879\ncpu: 99.62384308013829 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.81950986270819,
            "unit": "ns/iter",
            "extra": "iterations: 10388069\ncpu: 64.81965031229545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1050.8001970752703,
            "unit": "ns/iter",
            "extra": "iterations: 673854\ncpu: 1050.5584295707986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.522707886959232,
            "unit": "ns/iter",
            "extra": "iterations: 36327026\ncpu: 19.52083828717492 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1179.26118538536,
            "unit": "ns/iter",
            "extra": "iterations: 621570\ncpu: 1179.0240841739385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 827.1781198067894,
            "unit": "ns/iter",
            "extra": "iterations: 853274\ncpu: 826.9617965624145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1141.3225934798145,
            "unit": "ns/iter",
            "extra": "iterations: 585607\ncpu: 1141.2278200226478 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.17272180635604,
            "unit": "ns/iter",
            "extra": "iterations: 14588378\ncpu: 48.171565063641765 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1299.6120998317401,
            "unit": "ns/iter",
            "extra": "iterations: 550206\ncpu: 1299.5078207071604 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 65.36357418847926,
            "unit": "ns/iter",
            "extra": "iterations: 10672196\ncpu: 65.3569330998044 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.98602869088957,
            "unit": "ns/iter",
            "extra": "iterations: 11455691\ncpu: 61.98403919938211 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.57659055846267,
            "unit": "ns/iter",
            "extra": "iterations: 3706214\ncpu: 182.5571863902094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 610.4995643366566,
            "unit": "ns/iter",
            "extra": "iterations: 1159152\ncpu: 610.4643739561301 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 117.14622289596134,
            "unit": "ns/iter",
            "extra": "iterations: 6016951\ncpu: 117.12726262853057 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 315.373035149316,
            "unit": "ns/iter",
            "extra": "iterations: 2152899\ncpu: 315.23680395596983 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8707.462917917954,
            "unit": "ns/iter",
            "extra": "iterations: 83868\ncpu: 8705.97844231413 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 978.5875964544426,
            "unit": "ns/iter",
            "extra": "iterations: 704218\ncpu: 978.4739952685111 ns\nthreads: 1"
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
          "id": "d0f9e61492c0d95c6ae747a8cb8ee498027867ee",
          "message": "Prioritize non-`$ref` `enum`/`const` when unrolling `properties` (#127)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-04T12:12:00-04:00",
          "tree_id": "a63d33337e2f4c6b20a33c76a06a071251035580",
          "url": "https://github.com/sourcemeta/blaze/commit/d0f9e61492c0d95c6ae747a8cb8ee498027867ee"
        },
        "date": 1730737157351,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 38154319208.99994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 37941944000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6336252292.00004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6301215000.000007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 532.5024571340356,
            "unit": "ns/iter",
            "extra": "iterations: 1307214\ncpu: 532.3481847654562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 804.2111400159861,
            "unit": "ns/iter",
            "extra": "iterations: 866444\ncpu: 803.4541182119108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 103.3683822919146,
            "unit": "ns/iter",
            "extra": "iterations: 6758061\ncpu: 103.21836396564025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 67.57803796747496,
            "unit": "ns/iter",
            "extra": "iterations: 10417442\ncpu: 67.56514699097866 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1065.5747897321448,
            "unit": "ns/iter",
            "extra": "iterations: 658446\ncpu: 1065.5665005178805 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.69462172519775,
            "unit": "ns/iter",
            "extra": "iterations: 36291619\ncpu: 19.684599907212863 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1200.8355813959574,
            "unit": "ns/iter",
            "extra": "iterations: 620386\ncpu: 1200.8249702604567 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 901.0261920512704,
            "unit": "ns/iter",
            "extra": "iterations: 784551\ncpu: 892.5512809237372 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1212.9325718156178,
            "unit": "ns/iter",
            "extra": "iterations: 581908\ncpu: 1208.921341517897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.457459568705126,
            "unit": "ns/iter",
            "extra": "iterations: 13410219\ncpu: 50.45353845451771 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1371.271876886472,
            "unit": "ns/iter",
            "extra": "iterations: 505225\ncpu: 1371.2009500717531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.57298091031664,
            "unit": "ns/iter",
            "extra": "iterations: 10031959\ncpu: 69.5427483306105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 65.43261483316621,
            "unit": "ns/iter",
            "extra": "iterations: 10353651\ncpu: 65.42291216885639 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 195.0447198272999,
            "unit": "ns/iter",
            "extra": "iterations: 3569334\ncpu: 194.95793893202267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 628.1318822974439,
            "unit": "ns/iter",
            "extra": "iterations: 1144240\ncpu: 628.0832692442182 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.2624872571311,
            "unit": "ns/iter",
            "extra": "iterations: 5874849\ncpu: 123.21780525763305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 331.0536060883351,
            "unit": "ns/iter",
            "extra": "iterations: 2125766\ncpu: 330.99927273274875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8224.925768060692,
            "unit": "ns/iter",
            "extra": "iterations: 83522\ncpu: 8224.000862048368 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1051.6702965117545,
            "unit": "ns/iter",
            "extra": "iterations: 693969\ncpu: 1030.9668011107267 ns\nthreads: 1"
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
          "id": "d0577f5d651ae74c862f0dfeb3cd393a45988148",
          "message": "Introduce a new `LoopPropertiesWhitelist` step (#132)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-04T14:29:14-04:00",
          "tree_id": "065cd3fdd6f1dc0e4002e523e016ec63e5f08aea",
          "url": "https://github.com/sourcemeta/blaze/commit/d0577f5d651ae74c862f0dfeb3cd393a45988148"
        },
        "date": 1730745339470,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 34413667750,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 34293152000.000008 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6033086166.999965,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6028024000.000002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 513.1204351297313,
            "unit": "ns/iter",
            "extra": "iterations: 1337716\ncpu: 513.1089110095118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 774.6285344316913,
            "unit": "ns/iter",
            "extra": "iterations: 909729\ncpu: 769.9446758320312 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 100.21493737001333,
            "unit": "ns/iter",
            "extra": "iterations: 6972459\ncpu: 100.20940962148381 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.43084237178826,
            "unit": "ns/iter",
            "extra": "iterations: 10874462\ncpu: 65.42263883951281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1068.0023797195538,
            "unit": "ns/iter",
            "extra": "iterations: 664364\ncpu: 1067.7143854874814 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.23238664688353,
            "unit": "ns/iter",
            "extra": "iterations: 35423309\ncpu: 20.225609075651374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1178.8295730398747,
            "unit": "ns/iter",
            "extra": "iterations: 596496\ncpu: 1178.6265121643742 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 875.7558833191947,
            "unit": "ns/iter",
            "extra": "iterations: 824917\ncpu: 875.6359730736547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1203.4841649613784,
            "unit": "ns/iter",
            "extra": "iterations: 584937\ncpu: 1200.0454749827777 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 49.1048313489503,
            "unit": "ns/iter",
            "extra": "iterations: 13817880\ncpu: 49.087703757739604 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1330.2195623644805,
            "unit": "ns/iter",
            "extra": "iterations: 531858\ncpu: 1329.9696535541568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.50087902999847,
            "unit": "ns/iter",
            "extra": "iterations: 10275531\ncpu: 67.49237581979943 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.51823420619643,
            "unit": "ns/iter",
            "extra": "iterations: 10920437\ncpu: 63.518611938332015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 184.48275397245763,
            "unit": "ns/iter",
            "extra": "iterations: 3761156\ncpu: 184.47440095545338 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 625.9302297324451,
            "unit": "ns/iter",
            "extra": "iterations: 1119302\ncpu: 625.8614743831473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.48338376076231,
            "unit": "ns/iter",
            "extra": "iterations: 5722414\ncpu: 124.45866377371506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 340.34205444277023,
            "unit": "ns/iter",
            "extra": "iterations: 2054708\ncpu: 340.2906885065886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8687.634527978715,
            "unit": "ns/iter",
            "extra": "iterations: 80526\ncpu: 8684.325559446475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1035.1153913862481,
            "unit": "ns/iter",
            "extra": "iterations: 675969\ncpu: 1035.1095982212232 ns\nthreads: 1"
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
          "id": "8b37f488a1731e2ba4e643d83dcd9248b8beb603",
          "message": "Simplify `LoopPropertiesWhitelist` (#135)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-04T18:59:07Z",
          "url": "https://github.com/sourcemeta/blaze/commit/8b37f488a1731e2ba4e643d83dcd9248b8beb603"
        },
        "date": 1730747267139,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 34489516166.999916,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 34449870000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6547897999.999918,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6463897000.000003 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 543.3637581227836,
            "unit": "ns/iter",
            "extra": "iterations: 1304364\ncpu: 542.9090345946383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 790.8303084018323,
            "unit": "ns/iter",
            "extra": "iterations: 864262\ncpu: 786.8724993115449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 103.47700003910988,
            "unit": "ns/iter",
            "extra": "iterations: 6876903\ncpu: 103.3716776287238 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 67.32367531870715,
            "unit": "ns/iter",
            "extra": "iterations: 10404899\ncpu: 67.31703979058304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1121.0296748371857,
            "unit": "ns/iter",
            "extra": "iterations: 642632\ncpu: 1120.8810018797612 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.796088758654907,
            "unit": "ns/iter",
            "extra": "iterations: 34536350\ncpu: 20.789081648755577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1230.9578068838114,
            "unit": "ns/iter",
            "extra": "iterations: 570330\ncpu: 1230.7628916592114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1032.4924078336057,
            "unit": "ns/iter",
            "extra": "iterations: 800101\ncpu: 1027.5140263541773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1477.7642359424003,
            "unit": "ns/iter",
            "extra": "iterations: 353612\ncpu: 1465.4847686164378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 51.34727254881108,
            "unit": "ns/iter",
            "extra": "iterations: 13784683\ncpu: 51.339882099574346 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1431.1934556772699,
            "unit": "ns/iter",
            "extra": "iterations: 452331\ncpu: 1431.058229482391 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 70.9077092563131,
            "unit": "ns/iter",
            "extra": "iterations: 9832427\ncpu: 70.87558341394273 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 65.69287083428827,
            "unit": "ns/iter",
            "extra": "iterations: 10523784\ncpu: 65.67770680204009 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 192.2105945551466,
            "unit": "ns/iter",
            "extra": "iterations: 3678229\ncpu: 192.1881427175966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 642.9650737860441,
            "unit": "ns/iter",
            "extra": "iterations: 1081165\ncpu: 642.8251007015583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.49029235215406,
            "unit": "ns/iter",
            "extra": "iterations: 5642613\ncpu: 124.35408914274257 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 344.1933937851918,
            "unit": "ns/iter",
            "extra": "iterations: 2113858\ncpu: 344.07372680662485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8566.714753690649,
            "unit": "ns/iter",
            "extra": "iterations: 80590\ncpu: 8564.759895768753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1025.750569360657,
            "unit": "ns/iter",
            "extra": "iterations: 681027\ncpu: 1025.5393692173714 ns\nthreads: 1"
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
          "id": "8b37f488a1731e2ba4e643d83dcd9248b8beb603",
          "message": "Simplify `LoopPropertiesWhitelist` (#135)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-04T14:59:07-04:00",
          "tree_id": "81cf7b6f413fa28993d4f1092add4f64321cd988",
          "url": "https://github.com/sourcemeta/blaze/commit/8b37f488a1731e2ba4e643d83dcd9248b8beb603"
        },
        "date": 1730747268066,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 36545235499.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 36346185999.99999 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6520330959.000034,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6493952000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 525.497803564863,
            "unit": "ns/iter",
            "extra": "iterations: 1325557\ncpu: 525.4832496829658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 807.4107599638154,
            "unit": "ns/iter",
            "extra": "iterations: 897977\ncpu: 806.8881496964848 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 101.91155382518289,
            "unit": "ns/iter",
            "extra": "iterations: 6086798\ncpu: 101.89708940562718 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 66.34783627901388,
            "unit": "ns/iter",
            "extra": "iterations: 10498373\ncpu: 66.33751725148254 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1082.4358532911972,
            "unit": "ns/iter",
            "extra": "iterations: 658093\ncpu: 1081.4337791163337 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.04356245157246,
            "unit": "ns/iter",
            "extra": "iterations: 35592074\ncpu: 20.03991113302361 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1301.1155351732161,
            "unit": "ns/iter",
            "extra": "iterations: 592668\ncpu: 1287.0156647566646 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1010.7405331044821,
            "unit": "ns/iter",
            "extra": "iterations: 637511\ncpu: 980.6826862595241 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1353.0720911871895,
            "unit": "ns/iter",
            "extra": "iterations: 502877\ncpu: 1343.3762132688526 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 55.18861652287488,
            "unit": "ns/iter",
            "extra": "iterations: 13755428\ncpu: 54.82570226095527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1471.3042266633001,
            "unit": "ns/iter",
            "extra": "iterations: 504890\ncpu: 1469.4586939729422 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 76.45874346706104,
            "unit": "ns/iter",
            "extra": "iterations: 9534187\ncpu: 76.35690384507866 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 67.12083696266727,
            "unit": "ns/iter",
            "extra": "iterations: 10614906\ncpu: 67.12014218496077 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 216.560832584402,
            "unit": "ns/iter",
            "extra": "iterations: 3602806\ncpu: 216.03855439343516 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 680.6502477298417,
            "unit": "ns/iter",
            "extra": "iterations: 1106649\ncpu: 680.3096555457082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.94949832270109,
            "unit": "ns/iter",
            "extra": "iterations: 5605695\ncpu: 123.90738347341383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 341.5486631202671,
            "unit": "ns/iter",
            "extra": "iterations: 2122891\ncpu: 341.4819696348027 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8863.75856329679,
            "unit": "ns/iter",
            "extra": "iterations: 78708\ncpu: 8855.630939675872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1056.8127116205803,
            "unit": "ns/iter",
            "extra": "iterations: 667468\ncpu: 1056.6169464304128 ns\nthreads: 1"
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
          "id": "ac49585aae68878f775158a0bdf0062b163c57ea",
          "message": "Implement a smarter `properties` unroll check for `anyOf`/`oneOf` (#129)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-05T09:49:56-04:00",
          "tree_id": "260737228622bfe754daa2ade0610f7eb0800133",
          "url": "https://github.com/sourcemeta/blaze/commit/ac49585aae68878f775158a0bdf0062b163c57ea"
        },
        "date": 1730815122973,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 38413235416.99989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 38160835000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6050786415.999937,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6042081000.000003 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 524.1936443653176,
            "unit": "ns/iter",
            "extra": "iterations: 1337333\ncpu: 524.1835803049761 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 817.9582108523805,
            "unit": "ns/iter",
            "extra": "iterations: 885852\ncpu: 817.0157091703853 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 109.44671412063504,
            "unit": "ns/iter",
            "extra": "iterations: 6611320\ncpu: 109.41219000139186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 68.80864644756745,
            "unit": "ns/iter",
            "extra": "iterations: 10107573\ncpu: 68.80425201974886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1109.4687484059782,
            "unit": "ns/iter",
            "extra": "iterations: 607729\ncpu: 1108.9432954491267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.5670969968844,
            "unit": "ns/iter",
            "extra": "iterations: 34113725\ncpu: 20.565212388855116 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1235.7039282549126,
            "unit": "ns/iter",
            "extra": "iterations: 578603\ncpu: 1235.5656641946366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 886.5646012739504,
            "unit": "ns/iter",
            "extra": "iterations: 788599\ncpu: 886.2970914241633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1255.6942223022365,
            "unit": "ns/iter",
            "extra": "iterations: 578708\ncpu: 1255.3774960774724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 52.92327193296491,
            "unit": "ns/iter",
            "extra": "iterations: 10938696\ncpu: 52.501047656868536 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1504.5556736274245,
            "unit": "ns/iter",
            "extra": "iterations: 463936\ncpu: 1455.5154159194385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.91469142209837,
            "unit": "ns/iter",
            "extra": "iterations: 10205867\ncpu: 69.91164983827458 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 67.05999244673659,
            "unit": "ns/iter",
            "extra": "iterations: 10681478\ncpu: 66.82511540069646 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 194.07561361904138,
            "unit": "ns/iter",
            "extra": "iterations: 3595146\ncpu: 193.98016102823257 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 642.3957010684254,
            "unit": "ns/iter",
            "extra": "iterations: 1079431\ncpu: 641.8103611995665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 122.4067716685358,
            "unit": "ns/iter",
            "extra": "iterations: 5700279\ncpu: 122.39330741530394 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 342.70540424245496,
            "unit": "ns/iter",
            "extra": "iterations: 2140411\ncpu: 342.67437422065103 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 9021.67482007121,
            "unit": "ns/iter",
            "extra": "iterations: 78086\ncpu: 9018.889429603312 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1041.1374775841925,
            "unit": "ns/iter",
            "extra": "iterations: 622887\ncpu: 1040.9464316962808 ns\nthreads: 1"
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
          "id": "c44f7f3a872f313fb99a580a889d2505705d6172",
          "message": "Simplify `properties` compiler handler (#136)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-05T10:17:53-04:00",
          "tree_id": "d779e54c0dafe6dde8fe0780441ea948d9660680",
          "url": "https://github.com/sourcemeta/blaze/commit/c44f7f3a872f313fb99a580a889d2505705d6172"
        },
        "date": 1730816679334,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 30816324833.00007,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 30810530000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5711790583.000038,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5702214000.000002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 519.0682002479417,
            "unit": "ns/iter",
            "extra": "iterations: 1441593\ncpu: 518.89333535887 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 806.1125148216958,
            "unit": "ns/iter",
            "extra": "iterations: 802872\ncpu: 805.6564433682988 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 100.64525911656688,
            "unit": "ns/iter",
            "extra": "iterations: 6898999\ncpu: 100.61039289902877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.98113988666207,
            "unit": "ns/iter",
            "extra": "iterations: 11217589\ncpu: 62.96549106942638 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1070.8354511557827,
            "unit": "ns/iter",
            "extra": "iterations: 662709\ncpu: 1062.5025463665036 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.342180545503556,
            "unit": "ns/iter",
            "extra": "iterations: 35898540\ncpu: 19.33685882489923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1178.0536038755863,
            "unit": "ns/iter",
            "extra": "iterations: 619694\ncpu: 1178.0120511090965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 830.0331460263913,
            "unit": "ns/iter",
            "extra": "iterations: 860797\ncpu: 829.9204109679764 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1146.922556120554,
            "unit": "ns/iter",
            "extra": "iterations: 628468\ncpu: 1146.887351464195 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.467793095640594,
            "unit": "ns/iter",
            "extra": "iterations: 14893142\ncpu: 47.46674677512706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1278.5597042992326,
            "unit": "ns/iter",
            "extra": "iterations: 555697\ncpu: 1278.3387349580796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.17430222434949,
            "unit": "ns/iter",
            "extra": "iterations: 10900710\ncpu: 64.17187504300199 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 62.844637290922215,
            "unit": "ns/iter",
            "extra": "iterations: 11450444\ncpu: 62.84358929662502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 178.1136473925634,
            "unit": "ns/iter",
            "extra": "iterations: 3804038\ncpu: 178.10994527394337 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 596.8578658550276,
            "unit": "ns/iter",
            "extra": "iterations: 1176846\ncpu: 596.6787498109417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.7269668597511,
            "unit": "ns/iter",
            "extra": "iterations: 6063231\ncpu: 115.71058401040513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 306.24837123786665,
            "unit": "ns/iter",
            "extra": "iterations: 2292999\ncpu: 306.2151357239988 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8114.803448675328,
            "unit": "ns/iter",
            "extra": "iterations: 86410\ncpu: 8114.060872584088 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 967.0450904430606,
            "unit": "ns/iter",
            "extra": "iterations: 720951\ncpu: 966.7369904473303 ns\nthreads: 1"
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
          "id": "d3946e40c0365fbb2ee3d82b65fff9851adae89f",
          "message": "Don't rely on compiled `properties` to decide whether to unroll (#138)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-05T11:39:32-04:00",
          "tree_id": "005e95b10c52880df33974a8debe5dd577902837",
          "url": "https://github.com/sourcemeta/blaze/commit/d3946e40c0365fbb2ee3d82b65fff9851adae89f"
        },
        "date": 1730821867866,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 36269340541.00002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 36176772000.00001 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6361897958.999975,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6346637999.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 508.29272626451433,
            "unit": "ns/iter",
            "extra": "iterations: 1332699\ncpu: 508.16500950327577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 737.9967806348463,
            "unit": "ns/iter",
            "extra": "iterations: 939005\ncpu: 737.9779660385205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 99.47926525219054,
            "unit": "ns/iter",
            "extra": "iterations: 7258926\ncpu: 99.44859611463112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 64.14432079223678,
            "unit": "ns/iter",
            "extra": "iterations: 10616516\ncpu: 64.1388380142783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1034.5528604104725,
            "unit": "ns/iter",
            "extra": "iterations: 682874\ncpu: 1034.5217419318963 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.285609215589137,
            "unit": "ns/iter",
            "extra": "iterations: 36582370\ncpu: 19.281500897836615 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1248.7942653547343,
            "unit": "ns/iter",
            "extra": "iterations: 612697\ncpu: 1237.9691756284183 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 863.1469484031143,
            "unit": "ns/iter",
            "extra": "iterations: 872068\ncpu: 857.1464610557881 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1157.7798980671648,
            "unit": "ns/iter",
            "extra": "iterations: 570572\ncpu: 1152.5837230007774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.203063974029135,
            "unit": "ns/iter",
            "extra": "iterations: 14944970\ncpu: 47.12742815810274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1269.1451837854763,
            "unit": "ns/iter",
            "extra": "iterations: 555675\ncpu: 1269.126737751369 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.15567713158278,
            "unit": "ns/iter",
            "extra": "iterations: 10763270\ncpu: 64.14834896829629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.10630036771133,
            "unit": "ns/iter",
            "extra": "iterations: 11353131\ncpu: 61.09697844585754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 184.42015080486442,
            "unit": "ns/iter",
            "extra": "iterations: 3872024\ncpu: 184.38289638700567 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 600.6173510862748,
            "unit": "ns/iter",
            "extra": "iterations: 1148954\ncpu: 600.5584209637617 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 120.94270947201727,
            "unit": "ns/iter",
            "extra": "iterations: 6055940\ncpu: 120.83508092880666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 306.30377963827544,
            "unit": "ns/iter",
            "extra": "iterations: 2270376\ncpu: 306.2986042840459 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8630.599126127008,
            "unit": "ns/iter",
            "extra": "iterations: 82163\ncpu: 8597.51956476751 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1053.3297757153591,
            "unit": "ns/iter",
            "extra": "iterations: 698220\ncpu: 1053.0864197530896 ns\nthreads: 1"
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
          "id": "dfeff9a24e4e92abdc5c143c9b0194fbb4678198",
          "message": "Don't run non-JSON GoogleBenchmark output on CI (#139)\n\nWe don't really need it, nor read it.\r\n\r\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-05T11:49:16-04:00",
          "tree_id": "84f20e9b3d40274b1e8ccf239babfc0c7605c6ef",
          "url": "https://github.com/sourcemeta/blaze/commit/dfeff9a24e4e92abdc5c143c9b0194fbb4678198"
        },
        "date": 1730822634029,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 43587482333.00002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 42492563000.00001 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6859593165.999968,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6852376000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 589.3874371919994,
            "unit": "ns/iter",
            "extra": "iterations: 1244865\ncpu: 584.5822639402642 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 935.5815029787376,
            "unit": "ns/iter",
            "extra": "iterations: 770297\ncpu: 927.6447915544275 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 132.71692944504773,
            "unit": "ns/iter",
            "extra": "iterations: 6448463\ncpu: 124.89720418648554 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 83.17210166857066,
            "unit": "ns/iter",
            "extra": "iterations: 8541794\ncpu: 82.70054276654245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1232.4849145578341,
            "unit": "ns/iter",
            "extra": "iterations: 566407\ncpu: 1220.191487746443 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.514892207812448,
            "unit": "ns/iter",
            "extra": "iterations: 30419969\ncpu: 23.399432129598576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1475.9885335243146,
            "unit": "ns/iter",
            "extra": "iterations: 501113\ncpu: 1445.2289204231422 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1079.7983598775415,
            "unit": "ns/iter",
            "extra": "iterations: 728848\ncpu: 1050.084516936316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1324.613856758698,
            "unit": "ns/iter",
            "extra": "iterations: 502816\ncpu: 1322.6030993445008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 55.25792707129528,
            "unit": "ns/iter",
            "extra": "iterations: 12281995\ncpu: 55.064832708366744 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1459.7658615867285,
            "unit": "ns/iter",
            "extra": "iterations: 480532\ncpu: 1458.50848642754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 72.36898464247501,
            "unit": "ns/iter",
            "extra": "iterations: 9840583\ncpu: 72.30028952552861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 69.76237708270176,
            "unit": "ns/iter",
            "extra": "iterations: 8986225\ncpu: 69.650715400516 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 209.85145235414004,
            "unit": "ns/iter",
            "extra": "iterations: 3089157\ncpu: 209.51087950531593 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 691.1182760691786,
            "unit": "ns/iter",
            "extra": "iterations: 1050483\ncpu: 690.459531472658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.241886258384,
            "unit": "ns/iter",
            "extra": "iterations: 5324085\ncpu: 131.1038422564618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 350.0706384703946,
            "unit": "ns/iter",
            "extra": "iterations: 2051998\ncpu: 349.75131554709463 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 11363.842483849394,
            "unit": "ns/iter",
            "extra": "iterations: 65479\ncpu: 11345.958246155365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1306.87866231381,
            "unit": "ns/iter",
            "extra": "iterations: 597300\ncpu: 1304.006361962152 ns\nthreads: 1"
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
          "id": "4f7f4f920352a5743e9608952f0586fe7daa2fdc",
          "message": "Remove `LogicalAnd` wrapper when unrolling `properties` (#137)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-05T12:07:17-04:00",
          "tree_id": "54c8e562243e1f1283ec2c80ae71518311e331bf",
          "url": "https://github.com/sourcemeta/blaze/commit/4f7f4f920352a5743e9608952f0586fe7daa2fdc"
        },
        "date": 1730823189552,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 44997161500.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 43629040000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 8261932249.999972,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 7717199000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 687.7846827019318,
            "unit": "ns/iter",
            "extra": "iterations: 1340380\ncpu: 672.5935928617193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 902.8540612151652,
            "unit": "ns/iter",
            "extra": "iterations: 854461\ncpu: 885.9807527786515 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 115.21266302862892,
            "unit": "ns/iter",
            "extra": "iterations: 5568194\ncpu: 114.2372194646949 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 85.08537660374162,
            "unit": "ns/iter",
            "extra": "iterations: 8929027\ncpu: 84.89760418464373 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1299.026218994314,
            "unit": "ns/iter",
            "extra": "iterations: 534498\ncpu: 1293.8439432888488 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.93827829620895,
            "unit": "ns/iter",
            "extra": "iterations: 29090788\ncpu: 24.238807144034734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1635.3769353484686,
            "unit": "ns/iter",
            "extra": "iterations: 442556\ncpu: 1602.1362268277753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1034.8436024927432,
            "unit": "ns/iter",
            "extra": "iterations: 611199\ncpu: 1031.8177876599907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1433.788205844414,
            "unit": "ns/iter",
            "extra": "iterations: 476982\ncpu: 1431.2636535550637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 68.22338955901627,
            "unit": "ns/iter",
            "extra": "iterations: 11526998\ncpu: 68.04468951933485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1848.4674524531722,
            "unit": "ns/iter",
            "extra": "iterations: 397818\ncpu: 1839.5396890035186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 86.01388201541425,
            "unit": "ns/iter",
            "extra": "iterations: 9804196\ncpu: 85.71136276753332 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 85.76511143940154,
            "unit": "ns/iter",
            "extra": "iterations: 8900757\ncpu: 80.66504905144552 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 221.01495406670165,
            "unit": "ns/iter",
            "extra": "iterations: 3413319\ncpu: 210.56367717169186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 829.8986432117696,
            "unit": "ns/iter",
            "extra": "iterations: 951954\ncpu: 793.8303741567507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 174.63960164224716,
            "unit": "ns/iter",
            "extra": "iterations: 4781029\ncpu: 154.97542474642796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 428.50959845703244,
            "unit": "ns/iter",
            "extra": "iterations: 1842692\ncpu: 416.5281012779131 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 6598.37627858927,
            "unit": "ns/iter",
            "extra": "iterations: 99817\ncpu: 6480.308965406684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1249.3486851073653,
            "unit": "ns/iter",
            "extra": "iterations: 608833\ncpu: 1199.7197917984092 ns\nthreads: 1"
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
          "id": "970e8aef78f0140551dde12e0784b30595580f49",
          "message": "Add an example to the README (#141)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-05T13:34:39-04:00",
          "tree_id": "a2798aac48d24428ce263795f6d44802a7b03e04",
          "url": "https://github.com/sourcemeta/blaze/commit/970e8aef78f0140551dde12e0784b30595580f49"
        },
        "date": 1730828351710,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 31467724582.99995,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 31457456999.999996 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6207313499.999941,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6188181000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 496.7067697743636,
            "unit": "ns/iter",
            "extra": "iterations: 1381597\ncpu: 496.39366617038297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 724.2229696413364,
            "unit": "ns/iter",
            "extra": "iterations: 947111\ncpu: 724.2012815815666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 100.30596821262232,
            "unit": "ns/iter",
            "extra": "iterations: 7036378\ncpu: 100.30544123695469 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.49243807829849,
            "unit": "ns/iter",
            "extra": "iterations: 10751037\ncpu: 65.21835986612297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1063.664088411523,
            "unit": "ns/iter",
            "extra": "iterations: 650957\ncpu: 1058.0437724765234 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.655174634607746,
            "unit": "ns/iter",
            "extra": "iterations: 35261997\ncpu: 19.651893226580473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1176.5108070853469,
            "unit": "ns/iter",
            "extra": "iterations: 601411\ncpu: 1176.3968400977053 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 853.5883696943854,
            "unit": "ns/iter",
            "extra": "iterations: 833770\ncpu: 853.5267519819666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1170.216959466209,
            "unit": "ns/iter",
            "extra": "iterations: 612649\ncpu: 1169.958654955764 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.976554164989956,
            "unit": "ns/iter",
            "extra": "iterations: 13848771\ncpu: 48.97633154595426 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1317.937803835965,
            "unit": "ns/iter",
            "extra": "iterations: 536062\ncpu: 1316.6685943043876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 66.40010622521264,
            "unit": "ns/iter",
            "extra": "iterations: 10268748\ncpu: 66.38579503557803 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.56190128218857,
            "unit": "ns/iter",
            "extra": "iterations: 11081911\ncpu: 63.52297902410432 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 183.53310756988776,
            "unit": "ns/iter",
            "extra": "iterations: 3850343\ncpu: 183.52001367150908 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 622.8290935464022,
            "unit": "ns/iter",
            "extra": "iterations: 1136142\ncpu: 622.8297167079513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 121.97640313609726,
            "unit": "ns/iter",
            "extra": "iterations: 5920363\ncpu: 121.96025818011469 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 307.1337433954514,
            "unit": "ns/iter",
            "extra": "iterations: 2203406\ncpu: 307.1095385961525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 5290.075829999523,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5289.11000000008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1036.5236857588834,
            "unit": "ns/iter",
            "extra": "iterations: 667933\ncpu: 1036.5246214814972 ns\nthreads: 1"
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
          "id": "970e8aef78f0140551dde12e0784b30595580f49",
          "message": "Add an example to the README (#141)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-05T17:34:39Z",
          "url": "https://github.com/sourcemeta/blaze/commit/970e8aef78f0140551dde12e0784b30595580f49"
        },
        "date": 1730833535359,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 31191761958.00003,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 31176993000.000004 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5654212832.999974,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5651846999.999996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 482.16008063535486,
            "unit": "ns/iter",
            "extra": "iterations: 1446015\ncpu: 482.13054498051383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 703.1760673562245,
            "unit": "ns/iter",
            "extra": "iterations: 998987\ncpu: 703.1172577821321 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.14163603883664,
            "unit": "ns/iter",
            "extra": "iterations: 7352246\ncpu: 96.13524901098212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.53877471019518,
            "unit": "ns/iter",
            "extra": "iterations: 11219207\ncpu: 62.53249449805099 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1024.5812957833973,
            "unit": "ns/iter",
            "extra": "iterations: 679697\ncpu: 1022.1981265181338 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.049960726242485,
            "unit": "ns/iter",
            "extra": "iterations: 36488741\ncpu: 18.988240783643278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1137.7421751828151,
            "unit": "ns/iter",
            "extra": "iterations: 623497\ncpu: 1137.495449055884 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 827.945267814391,
            "unit": "ns/iter",
            "extra": "iterations: 868045\ncpu: 827.9374917198942 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1111.8660654188761,
            "unit": "ns/iter",
            "extra": "iterations: 580903\ncpu: 1111.8551634265932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.87797177774365,
            "unit": "ns/iter",
            "extra": "iterations: 14919647\ncpu: 46.87744958040915 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1270.9121077489178,
            "unit": "ns/iter",
            "extra": "iterations: 550094\ncpu: 1270.730093402209 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 63.86462055223353,
            "unit": "ns/iter",
            "extra": "iterations: 10954617\ncpu: 63.844587172695626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.02810403144733,
            "unit": "ns/iter",
            "extra": "iterations: 11475222\ncpu: 61.02592176430212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 177.71934697140455,
            "unit": "ns/iter",
            "extra": "iterations: 3949781\ncpu: 177.71972673928013 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 596.5097552298672,
            "unit": "ns/iter",
            "extra": "iterations: 1152510\ncpu: 596.4625035791461 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.51661378602066,
            "unit": "ns/iter",
            "extra": "iterations: 6058613\ncpu: 115.50580966303636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 293.2764938660161,
            "unit": "ns/iter",
            "extra": "iterations: 2382476\ncpu: 293.2533213346096 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 5095.915297869947,
            "unit": "ns/iter",
            "extra": "iterations: 139843\ncpu: 5095.027995680839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1017.3696999000176,
            "unit": "ns/iter",
            "extra": "iterations: 696968\ncpu: 1017.2418245887881 ns\nthreads: 1"
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
          "id": "eb532f894d7419348f446b3ada923c328b4c28c6",
          "message": "Fix README example indentation (#142)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-06T09:16:28-04:00",
          "tree_id": "8bcfba173e4135109f7f0b1b2a3d1789182d7330",
          "url": "https://github.com/sourcemeta/blaze/commit/eb532f894d7419348f446b3ada923c328b4c28c6"
        },
        "date": 1730899260947,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 32787009958.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 32467515000.000008 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 8550500999.999997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 7844386999.999997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 639.3895158357745,
            "unit": "ns/iter",
            "extra": "iterations: 1083558\ncpu: 622.1457457745645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 854.5819334793073,
            "unit": "ns/iter",
            "extra": "iterations: 871579\ncpu: 837.576398697074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 111.72040475288334,
            "unit": "ns/iter",
            "extra": "iterations: 6057721\ncpu: 110.81064974765208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 72.35329549214707,
            "unit": "ns/iter",
            "extra": "iterations: 7799791\ncpu: 71.59358500759784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1156.207789983538,
            "unit": "ns/iter",
            "extra": "iterations: 583878\ncpu: 1143.4409243026964 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.121012857718856,
            "unit": "ns/iter",
            "extra": "iterations: 32155079\ncpu: 21.944869113834397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1438.2279417796003,
            "unit": "ns/iter",
            "extra": "iterations: 536444\ncpu: 1414.97714579714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 917.030176267676,
            "unit": "ns/iter",
            "extra": "iterations: 779553\ncpu: 909.6636149177697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1266.1526393076376,
            "unit": "ns/iter",
            "extra": "iterations: 601313\ncpu: 1265.5621947305283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.277375474450174,
            "unit": "ns/iter",
            "extra": "iterations: 12950013\ncpu: 50.24458276605561 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1356.9689681908183,
            "unit": "ns/iter",
            "extra": "iterations: 500422\ncpu: 1356.7968634472588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 71.08916242507807,
            "unit": "ns/iter",
            "extra": "iterations: 10281719\ncpu: 71.05689233483302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 67.21179713009703,
            "unit": "ns/iter",
            "extra": "iterations: 10554567\ncpu: 67.18181806984651 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 202.08871279283812,
            "unit": "ns/iter",
            "extra": "iterations: 3341863\ncpu: 202.04658299876291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 646.2293510718375,
            "unit": "ns/iter",
            "extra": "iterations: 1047512\ncpu: 645.9544138873764 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.72347873633089,
            "unit": "ns/iter",
            "extra": "iterations: 5607312\ncpu: 126.6972481645394 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 328.9355226220546,
            "unit": "ns/iter",
            "extra": "iterations: 2199314\ncpu: 328.88982655500723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 5188.502876173069,
            "unit": "ns/iter",
            "extra": "iterations: 138726\ncpu: 5187.318887591484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1122.2624559459884,
            "unit": "ns/iter",
            "extra": "iterations: 674738\ncpu: 1117.049877137471 ns\nthreads: 1"
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
          "id": "eb532f894d7419348f446b3ada923c328b4c28c6",
          "message": "Fix README example indentation (#142)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-06T13:16:28Z",
          "url": "https://github.com/sourcemeta/blaze/commit/eb532f894d7419348f446b3ada923c328b4c28c6"
        },
        "date": 1730919968728,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 30994904374.999977,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 30936313000.000004 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5501618875.00002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5500093000.000003 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 490.8347196041405,
            "unit": "ns/iter",
            "extra": "iterations: 1446687\ncpu: 490.8096913845174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 714.2034054201865,
            "unit": "ns/iter",
            "extra": "iterations: 1000229\ncpu: 708.9386530484488 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 106.88171935486895,
            "unit": "ns/iter",
            "extra": "iterations: 6370180\ncpu: 103.90020376190371 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 70.45024121655803,
            "unit": "ns/iter",
            "extra": "iterations: 9484838\ncpu: 69.00666094666093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1080.9881495797247,
            "unit": "ns/iter",
            "extra": "iterations: 640568\ncpu: 1066.7329619962288 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 22.453903091895867,
            "unit": "ns/iter",
            "extra": "iterations: 32423769\ncpu: 20.932174788193386 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1582.2627461862546,
            "unit": "ns/iter",
            "extra": "iterations: 587411\ncpu: 1272.8992136681122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 962.8239123985177,
            "unit": "ns/iter",
            "extra": "iterations: 768572\ncpu: 932.0558125979003 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1220.1360451225512,
            "unit": "ns/iter",
            "extra": "iterations: 585960\ncpu: 1197.100484674723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 48.604649313231185,
            "unit": "ns/iter",
            "extra": "iterations: 13868801\ncpu: 48.549186047157164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1385.7824925572645,
            "unit": "ns/iter",
            "extra": "iterations: 522989\ncpu: 1381.1934859050732 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 71.60012810388002,
            "unit": "ns/iter",
            "extra": "iterations: 10293209\ncpu: 71.29487023920368 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.62751482166969,
            "unit": "ns/iter",
            "extra": "iterations: 10426286\ncpu: 63.56846531928987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 178.59985139595733,
            "unit": "ns/iter",
            "extra": "iterations: 3937982\ncpu: 178.4096524565116 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 603.5673256580118,
            "unit": "ns/iter",
            "extra": "iterations: 1167289\ncpu: 602.7204916691542 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.78494612313233,
            "unit": "ns/iter",
            "extra": "iterations: 6067540\ncpu: 115.7131226164138 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 294.06840378560395,
            "unit": "ns/iter",
            "extra": "iterations: 2379649\ncpu: 294.0425247589023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 4851.876462068749,
            "unit": "ns/iter",
            "extra": "iterations: 136023\ncpu: 4851.216338413316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 970.9293215867235,
            "unit": "ns/iter",
            "extra": "iterations: 716230\ncpu: 970.8571269005785 ns\nthreads: 1"
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
          "id": "2c4e8cf115cedfc64f8a691b613ea01b5e2705a4",
          "message": "Rename `ErrorTraceOutput` to `ErrorOutput` (#143)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T12:37:14-04:00",
          "tree_id": "5b29e47458ed9e1cbfb2d439e780df50ffb1518a",
          "url": "https://github.com/sourcemeta/blaze/commit/2c4e8cf115cedfc64f8a691b613ea01b5e2705a4"
        },
        "date": 1730997742500,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 32555067750.000034,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 32513753000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5675450875.000024,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5649153999.999996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 485.94237195889815,
            "unit": "ns/iter",
            "extra": "iterations: 1425851\ncpu: 485.86212724892255 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 700.864263039148,
            "unit": "ns/iter",
            "extra": "iterations: 981877\ncpu: 700.8413477451902 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 95.935296703959,
            "unit": "ns/iter",
            "extra": "iterations: 7287264\ncpu: 95.90265976366403 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.41922268257494,
            "unit": "ns/iter",
            "extra": "iterations: 11226945\ncpu: 63.41128419173672 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1034.551954008628,
            "unit": "ns/iter",
            "extra": "iterations: 673692\ncpu: 1034.101636949813 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.045102323848415,
            "unit": "ns/iter",
            "extra": "iterations: 36564790\ncpu: 19.044113202892824 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1144.0410870093824,
            "unit": "ns/iter",
            "extra": "iterations: 609268\ncpu: 1143.8874190011486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 820.9682560808217,
            "unit": "ns/iter",
            "extra": "iterations: 856542\ncpu: 820.4804901569335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1126.9678043538916,
            "unit": "ns/iter",
            "extra": "iterations: 618096\ncpu: 1126.5030027697933 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.8625894094161,
            "unit": "ns/iter",
            "extra": "iterations: 14957457\ncpu: 46.849340766950355 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1271.1139942845286,
            "unit": "ns/iter",
            "extra": "iterations: 550782\ncpu: 1270.8403687847594 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 67.55176711259392,
            "unit": "ns/iter",
            "extra": "iterations: 10955131\ncpu: 67.54195819292335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.527127243659486,
            "unit": "ns/iter",
            "extra": "iterations: 10770722\ncpu: 61.522895122536376 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 177.67946534522366,
            "unit": "ns/iter",
            "extra": "iterations: 3946397\ncpu: 177.6754847522958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 596.1440762654297,
            "unit": "ns/iter",
            "extra": "iterations: 1171803\ncpu: 596.1403068604501 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.24473389326447,
            "unit": "ns/iter",
            "extra": "iterations: 6082672\ncpu: 115.24244608290505 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 297.0642403124415,
            "unit": "ns/iter",
            "extra": "iterations: 2368217\ncpu: 297.0521704725521 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 5154.893904982174,
            "unit": "ns/iter",
            "extra": "iterations: 140016\ncpu: 5152.711118729306 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1036.4513031866663,
            "unit": "ns/iter",
            "extra": "iterations: 694183\ncpu: 1036.138885567651 ns\nthreads: 1"
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
          "id": "cf0c89cd419ffb70cc334d395ac5ab1035702e30",
          "message": "Upgrade JSON Toolkit to the latest version (#144)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T12:57:12-04:00",
          "tree_id": "655b4f4d4f70d453b8d0da97862e0813a76a410d",
          "url": "https://github.com/sourcemeta/blaze/commit/cf0c89cd419ffb70cc334d395ac5ab1035702e30"
        },
        "date": 1730998986454,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 45893283916.99996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 45520111000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 7501870542.000006,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 7484120000.000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 637.7015953238738,
            "unit": "ns/iter",
            "extra": "iterations: 1085861\ncpu: 637.1920531265106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 905.64380126134,
            "unit": "ns/iter",
            "extra": "iterations: 690213\ncpu: 904.8815365691459 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.95356674408148,
            "unit": "ns/iter",
            "extra": "iterations: 6191403\ncpu: 128.5532536001932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.5178751084238,
            "unit": "ns/iter",
            "extra": "iterations: 10109617\ncpu: 90.89731094659666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1331.8850791849663,
            "unit": "ns/iter",
            "extra": "iterations: 497064\ncpu: 1326.5635813496901 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 21.935280085766866,
            "unit": "ns/iter",
            "extra": "iterations: 26901349\ncpu: 21.585014193897624 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1260.4596445507761,
            "unit": "ns/iter",
            "extra": "iterations: 557942\ncpu: 1256.8582397453474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 919.7083236906935,
            "unit": "ns/iter",
            "extra": "iterations: 678413\ncpu: 918.9195961751916 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1227.5564465886728,
            "unit": "ns/iter",
            "extra": "iterations: 601923\ncpu: 1227.1735753576336 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 54.57981669999867,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 54.52549999999974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1406.432464643841,
            "unit": "ns/iter",
            "extra": "iterations: 476580\ncpu: 1402.8054051785612 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 70.39530401741753,
            "unit": "ns/iter",
            "extra": "iterations: 9960301\ncpu: 70.30761419760316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 67.83137175832917,
            "unit": "ns/iter",
            "extra": "iterations: 9859849\ncpu: 67.5030621665695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 214.232197468781,
            "unit": "ns/iter",
            "extra": "iterations: 3327392\ncpu: 212.98241986517104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 724.2795687030773,
            "unit": "ns/iter",
            "extra": "iterations: 1039655\ncpu: 719.2385935719193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 143.1489855717628,
            "unit": "ns/iter",
            "extra": "iterations: 4529103\ncpu: 143.0212560853684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 365.9363703509512,
            "unit": "ns/iter",
            "extra": "iterations: 1940149\ncpu: 365.2827695192409 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 5497.274031575748,
            "unit": "ns/iter",
            "extra": "iterations: 121486\ncpu: 5486.360568295947 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1088.6265624137743,
            "unit": "ns/iter",
            "extra": "iterations: 652516\ncpu: 1087.9380735491513 ns\nthreads: 1"
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
          "id": "a5b3c8e4d77a0b88e4a93f304ae75e711b30a2e6",
          "message": "Implement a new `TraceOutput` callback for tracing purposes (#145)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T14:03:31-04:00",
          "tree_id": "16e8df94bb799d090af7db2b1f992aa94b88c7f2",
          "url": "https://github.com/sourcemeta/blaze/commit/a5b3c8e4d77a0b88e4a93f304ae75e711b30a2e6"
        },
        "date": 1731002900712,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 30602772082.999992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 30552715999.999996 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5515459624.9999485,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5512241000.000003 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 493.7818222030762,
            "unit": "ns/iter",
            "extra": "iterations: 1415199\ncpu: 493.7192578570193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 712.8613885791035,
            "unit": "ns/iter",
            "extra": "iterations: 949359\ncpu: 712.8704736564406 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.95648073719593,
            "unit": "ns/iter",
            "extra": "iterations: 7247802\ncpu: 96.94097603659738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.63470181690973,
            "unit": "ns/iter",
            "extra": "iterations: 11221545\ncpu: 62.61062981968985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1030.0338130236148,
            "unit": "ns/iter",
            "extra": "iterations: 681690\ncpu: 1027.8205635992865 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.194256973401686,
            "unit": "ns/iter",
            "extra": "iterations: 36575871\ncpu: 19.10458947102049 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1140.6400600813126,
            "unit": "ns/iter",
            "extra": "iterations: 613169\ncpu: 1140.5354804303377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 822.1180297854498,
            "unit": "ns/iter",
            "extra": "iterations: 854242\ncpu: 821.9485813153644 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1109.7863662365783,
            "unit": "ns/iter",
            "extra": "iterations: 632826\ncpu: 1109.8042747927498 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.358841513603124,
            "unit": "ns/iter",
            "extra": "iterations: 14894124\ncpu: 47.356863686645966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1266.1178165813021,
            "unit": "ns/iter",
            "extra": "iterations: 546171\ncpu: 1266.094318446058 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.5866643872926,
            "unit": "ns/iter",
            "extra": "iterations: 10921118\ncpu: 64.57507372413724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.153425169306196,
            "unit": "ns/iter",
            "extra": "iterations: 11477856\ncpu: 61.141035398945704 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.2897084491688,
            "unit": "ns/iter",
            "extra": "iterations: 3837993\ncpu: 182.28068680688125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 601.6711898616562,
            "unit": "ns/iter",
            "extra": "iterations: 1172254\ncpu: 601.6127904020826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 117.83347201731513,
            "unit": "ns/iter",
            "extra": "iterations: 5931952\ncpu: 117.78298273485616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 298.84758417372444,
            "unit": "ns/iter",
            "extra": "iterations: 2346961\ncpu: 298.8366657988743 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 4856.518656146335,
            "unit": "ns/iter",
            "extra": "iterations: 143974\ncpu: 4855.77257004739 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 989.4099862335111,
            "unit": "ns/iter",
            "extra": "iterations: 707514\ncpu: 989.3599278600985 ns\nthreads: 1"
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
          "id": "e5a41e8ffd3087b69de9a6eba572720f1f7dac59",
          "message": "Get `TraceOutput` to emit instruction names on MSVC (#146)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T14:27:39-04:00",
          "tree_id": "a50042cf843b86dada485ba0f937be87a9992282",
          "url": "https://github.com/sourcemeta/blaze/commit/e5a41e8ffd3087b69de9a6eba572720f1f7dac59"
        },
        "date": 1731004330895,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 30957086915.99998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 30912608000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5609567625.000011,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5596967999.999997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 494.3836341486635,
            "unit": "ns/iter",
            "extra": "iterations: 1371661\ncpu: 494.1446902696805 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 713.0058708832045,
            "unit": "ns/iter",
            "extra": "iterations: 937508\ncpu: 712.9784492505634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.97711965075774,
            "unit": "ns/iter",
            "extra": "iterations: 7227075\ncpu: 96.96813717859631 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 62.740418848508924,
            "unit": "ns/iter",
            "extra": "iterations: 10996434\ncpu: 62.738156751543684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1120.8963207208926,
            "unit": "ns/iter",
            "extra": "iterations: 651133\ncpu: 1103.8681805406845 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.38552760759706,
            "unit": "ns/iter",
            "extra": "iterations: 36918858\ncpu: 19.32305165018905 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1138.8956902046532,
            "unit": "ns/iter",
            "extra": "iterations: 622837\ncpu: 1138.6398046358838 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 815.5081532070781,
            "unit": "ns/iter",
            "extra": "iterations: 868002\ncpu: 815.1536517196956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1117.9417265922227,
            "unit": "ns/iter",
            "extra": "iterations: 625637\ncpu: 1117.6800604823636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.07689405435537,
            "unit": "ns/iter",
            "extra": "iterations: 14892920\ncpu: 47.00246828694439 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1284.7337385874114,
            "unit": "ns/iter",
            "extra": "iterations: 546324\ncpu: 1280.7656262584158 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.56462548875348,
            "unit": "ns/iter",
            "extra": "iterations: 10911755\ncpu: 64.55661806922949 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.0865119182088,
            "unit": "ns/iter",
            "extra": "iterations: 10724846\ncpu: 63.06719928659123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.2419336538972,
            "unit": "ns/iter",
            "extra": "iterations: 3842818\ncpu: 182.23605697693873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 598.659183749915,
            "unit": "ns/iter",
            "extra": "iterations: 1175522\ncpu: 598.6565968140147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 117.90496558037597,
            "unit": "ns/iter",
            "extra": "iterations: 5956484\ncpu: 117.90462292856131 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 303.83935733877934,
            "unit": "ns/iter",
            "extra": "iterations: 2340331\ncpu: 302.64565140571807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 4882.958809399486,
            "unit": "ns/iter",
            "extra": "iterations: 143625\ncpu: 4882.158398607485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 999.9295849750009,
            "unit": "ns/iter",
            "extra": "iterations: 708897\ncpu: 999.8702209206671 ns\nthreads: 1"
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
          "id": "e5a41e8ffd3087b69de9a6eba572720f1f7dac59",
          "message": "Get `TraceOutput` to emit instruction names on MSVC (#146)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T18:27:39Z",
          "url": "https://github.com/sourcemeta/blaze/commit/e5a41e8ffd3087b69de9a6eba572720f1f7dac59"
        },
        "date": 1731006371658,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 32024276167.00004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 31993989000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6029911749.999996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5943608000.000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 532.0857825377329,
            "unit": "ns/iter",
            "extra": "iterations: 1306921\ncpu: 525.1044248275202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 744.6085793645512,
            "unit": "ns/iter",
            "extra": "iterations: 922376\ncpu: 744.0273814583205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 102.65487462746889,
            "unit": "ns/iter",
            "extra": "iterations: 6933576\ncpu: 102.37833983502898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 65.83294867328082,
            "unit": "ns/iter",
            "extra": "iterations: 10670894\ncpu: 65.77237108718354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1086.7769565928622,
            "unit": "ns/iter",
            "extra": "iterations: 649062\ncpu: 1077.6212441954733 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.007215282381996,
            "unit": "ns/iter",
            "extra": "iterations: 35476089\ncpu: 20.00358607737189 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1200.1690205262553,
            "unit": "ns/iter",
            "extra": "iterations: 594697\ncpu: 1199.9976458599865 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 846.819216791469,
            "unit": "ns/iter",
            "extra": "iterations: 821365\ncpu: 846.6406530592243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1166.83986662191,
            "unit": "ns/iter",
            "extra": "iterations: 576407\ncpu: 1166.713797715865 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.0780250000048,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 50.07809999999964 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1332.516247607507,
            "unit": "ns/iter",
            "extra": "iterations: 531309\ncpu: 1332.4750757092443 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 68.19642055507134,
            "unit": "ns/iter",
            "extra": "iterations: 10333781\ncpu: 68.18685242119992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 64.60396346248454,
            "unit": "ns/iter",
            "extra": "iterations: 10787487\ncpu: 64.54274290203114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 191.3949375835224,
            "unit": "ns/iter",
            "extra": "iterations: 3699182\ncpu: 191.36825384639127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 621.9965036977355,
            "unit": "ns/iter",
            "extra": "iterations: 1111746\ncpu: 621.9873964016995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 123.04016770155481,
            "unit": "ns/iter",
            "extra": "iterations: 5650037\ncpu: 122.99034501898024 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 312.7415963138205,
            "unit": "ns/iter",
            "extra": "iterations: 2231253\ncpu: 312.7099436953145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 5081.707374558346,
            "unit": "ns/iter",
            "extra": "iterations: 137893\ncpu: 5080.634985097084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1025.2218189807227,
            "unit": "ns/iter",
            "extra": "iterations: 682800\ncpu: 1025.190392501448 ns\nthreads: 1"
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
          "id": "5d1b7d5d62efeef18bcd265b0e7788f6c33f16f3",
          "message": "Fix runtime crash with `items` inside `properties` (#147)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T17:12:56-04:00",
          "tree_id": "f2e963c2f5fa8b75169acf162eaa9f3fa1491e72",
          "url": "https://github.com/sourcemeta/blaze/commit/5d1b7d5d62efeef18bcd265b0e7788f6c33f16f3"
        },
        "date": 1731014253994,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 32895789250.000008,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 32521046999.999996 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 6289449166.999929,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 6157521999.999993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 515.8628079454629,
            "unit": "ns/iter",
            "extra": "iterations: 1353730\ncpu: 515.701062988929 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 733.4886966484816,
            "unit": "ns/iter",
            "extra": "iterations: 942685\ncpu: 731.5444713769721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 101.66870489663101,
            "unit": "ns/iter",
            "extra": "iterations: 7060865\ncpu: 101.65638346010009 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 67.96784415666957,
            "unit": "ns/iter",
            "extra": "iterations: 10796638\ncpu: 67.47368949482201 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1073.1963706226088,
            "unit": "ns/iter",
            "extra": "iterations: 634489\ncpu: 1072.770371117546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 20.009616633252232,
            "unit": "ns/iter",
            "extra": "iterations: 35453988\ncpu: 20.005309416813745 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1175.500453057511,
            "unit": "ns/iter",
            "extra": "iterations: 598158\ncpu: 1175.3700527285453 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 875.9858081215419,
            "unit": "ns/iter",
            "extra": "iterations: 798203\ncpu: 875.7696976834196 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1201.9891024565522,
            "unit": "ns/iter",
            "extra": "iterations: 608394\ncpu: 1179.817683935078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 50.91800796299441,
            "unit": "ns/iter",
            "extra": "iterations: 14176584\ncpu: 50.18310475922821 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1458.2391257753268,
            "unit": "ns/iter",
            "extra": "iterations: 475896\ncpu: 1426.162438852188 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 69.04241941554821,
            "unit": "ns/iter",
            "extra": "iterations: 10093727\ncpu: 68.97977327898822 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 66.6783962989507,
            "unit": "ns/iter",
            "extra": "iterations: 10688002\ncpu: 66.64407435552482 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 188.83344536927942,
            "unit": "ns/iter",
            "extra": "iterations: 3603010\ncpu: 188.8007527039907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 617.6200718840283,
            "unit": "ns/iter",
            "extra": "iterations: 1114295\ncpu: 617.5034438815545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 120.30258815164312,
            "unit": "ns/iter",
            "extra": "iterations: 5862794\ncpu: 120.27900008084882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 306.0251820490403,
            "unit": "ns/iter",
            "extra": "iterations: 2294849\ncpu: 305.95433512183297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8517.841546894108,
            "unit": "ns/iter",
            "extra": "iterations: 82100\ncpu: 8517.600487210797 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1013.788465168982,
            "unit": "ns/iter",
            "extra": "iterations: 688610\ncpu: 1013.4546405077047 ns\nthreads: 1"
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
          "id": "4db8309470369332d3d0658ade9402a37abe418e",
          "message": "Record keyword location on `TraceOutput` (#148)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T17:33:35-04:00",
          "tree_id": "6216934195b311f9417262c7fd5ee1cbb124865f",
          "url": "https://github.com/sourcemeta/blaze/commit/4db8309470369332d3d0658ade9402a37abe418e"
        },
        "date": 1731015485231,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 30604687624.999996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 30547343000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5550636375.000068,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5548884999.999998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 491.56757150538056,
            "unit": "ns/iter",
            "extra": "iterations: 1427584\ncpu: 491.5423540751414 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 702.9276943666327,
            "unit": "ns/iter",
            "extra": "iterations: 992274\ncpu: 702.8713843152171 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.284721266094,
            "unit": "ns/iter",
            "extra": "iterations: 7321104\ncpu: 96.23794444116747 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.59283125506487,
            "unit": "ns/iter",
            "extra": "iterations: 11067544\ncpu: 63.591976684258476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1027.8301356516909,
            "unit": "ns/iter",
            "extra": "iterations: 667150\ncpu: 1026.2219890579204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.2504797650242,
            "unit": "ns/iter",
            "extra": "iterations: 36643459\ncpu: 19.250529814884658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1173.297486347604,
            "unit": "ns/iter",
            "extra": "iterations: 600441\ncpu: 1167.2220917625436 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 824.1066224834877,
            "unit": "ns/iter",
            "extra": "iterations: 861263\ncpu: 824.0200728465093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1129.5641074630182,
            "unit": "ns/iter",
            "extra": "iterations: 617627\ncpu: 1129.3499150782022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.84635986190648,
            "unit": "ns/iter",
            "extra": "iterations: 14884971\ncpu: 46.84375938656475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1294.9888837166657,
            "unit": "ns/iter",
            "extra": "iterations: 541368\ncpu: 1294.9675636535708 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.20433927564183,
            "unit": "ns/iter",
            "extra": "iterations: 10951874\ncpu: 64.19038422100222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.29086187926628,
            "unit": "ns/iter",
            "extra": "iterations: 11475598\ncpu: 61.25554415552046 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.7820226060383,
            "unit": "ns/iter",
            "extra": "iterations: 3853395\ncpu: 180.71726360780826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 594.8142884866978,
            "unit": "ns/iter",
            "extra": "iterations: 1169669\ncpu: 594.7922018964385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 115.57074464970607,
            "unit": "ns/iter",
            "extra": "iterations: 6077972\ncpu: 115.55712991109571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 294.72096887853235,
            "unit": "ns/iter",
            "extra": "iterations: 2376975\ncpu: 294.69514824514283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8297.91407002369,
            "unit": "ns/iter",
            "extra": "iterations: 84115\ncpu: 8297.604470070715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 993.537977486068,
            "unit": "ns/iter",
            "extra": "iterations: 697795\ncpu: 993.4121052744854 ns\nthreads: 1"
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
          "id": "4db8309470369332d3d0658ade9402a37abe418e",
          "message": "Record keyword location on `TraceOutput` (#148)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T21:33:35Z",
          "url": "https://github.com/sourcemeta/blaze/commit/4db8309470369332d3d0658ade9402a37abe418e"
        },
        "date": 1731092732388,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 30701306666.999928,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 30644555000 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5587281916.000165,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5586037999.999998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 493.18490221007306,
            "unit": "ns/iter",
            "extra": "iterations: 1409756\ncpu: 493.14775039084566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 712.9938721417357,
            "unit": "ns/iter",
            "extra": "iterations: 999044\ncpu: 712.9655951089209 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.84501977891561,
            "unit": "ns/iter",
            "extra": "iterations: 7170515\ncpu: 96.84213755915756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.07195349802756,
            "unit": "ns/iter",
            "extra": "iterations: 11012696\ncpu: 63.05776532830864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1047.0505993642962,
            "unit": "ns/iter",
            "extra": "iterations: 669376\ncpu: 1041.0113299550574 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 19.334310191123947,
            "unit": "ns/iter",
            "extra": "iterations: 36303476\ncpu: 19.325229352693285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1129.627285852836,
            "unit": "ns/iter",
            "extra": "iterations: 600487\ncpu: 1128.8487510970228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 819.8794451952147,
            "unit": "ns/iter",
            "extra": "iterations: 864304\ncpu: 819.7972009848298 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1130.9373473030012,
            "unit": "ns/iter",
            "extra": "iterations: 618872\ncpu: 1130.8477358807602 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 47.79522719058922,
            "unit": "ns/iter",
            "extra": "iterations: 14880921\ncpu: 47.79213598405632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1274.7038367324028,
            "unit": "ns/iter",
            "extra": "iterations: 539287\ncpu: 1274.5384183190044 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 64.2892128516558,
            "unit": "ns/iter",
            "extra": "iterations: 10962165\ncpu: 64.2801855290454 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 61.159649322527606,
            "unit": "ns/iter",
            "extra": "iterations: 11481433\ncpu: 61.15700017584934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 180.66245066456756,
            "unit": "ns/iter",
            "extra": "iterations: 3858790\ncpu: 180.6576672998526 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 600.1070084239196,
            "unit": "ns/iter",
            "extra": "iterations: 1154582\ncpu: 600.0405341500225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 117.45844390474727,
            "unit": "ns/iter",
            "extra": "iterations: 5945253\ncpu: 117.44310965403909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 298.3831584803052,
            "unit": "ns/iter",
            "extra": "iterations: 2376377\ncpu: 298.366799544009 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8328.865154490537,
            "unit": "ns/iter",
            "extra": "iterations: 79973\ncpu: 8327.448013704612 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1011.3078672810228,
            "unit": "ns/iter",
            "extra": "iterations: 702085\ncpu: 1011.2009229651604 ns\nthreads: 1"
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
          "id": "4db8309470369332d3d0658ade9402a37abe418e",
          "message": "Record keyword location on `TraceOutput` (#148)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-11-07T21:33:35Z",
          "url": "https://github.com/sourcemeta/blaze/commit/4db8309470369332d3d0658ade9402a37abe418e"
        },
        "date": 1731352001497,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 31200087917.00002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 31155876000.000004 ns\nthreads: 1"
          },
          {
            "name": "Compiler_2019_09_OMC_JSON_V2",
            "value": 5613681959.000019,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5610247999.999998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 493.6673496168633,
            "unit": "ns/iter",
            "extra": "iterations: 1391512\ncpu: 493.5559305273669 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 703.9795366483348,
            "unit": "ns/iter",
            "extra": "iterations: 1002133\ncpu: 703.50043357518 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 96.10477727934318,
            "unit": "ns/iter",
            "extra": "iterations: 7301478\ncpu: 96.09807767687609 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 63.346793730191834,
            "unit": "ns/iter",
            "extra": "iterations: 11215073\ncpu: 63.345552900100934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1031.1944710685386,
            "unit": "ns/iter",
            "extra": "iterations: 676080\ncpu: 1030.2671281505122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 18.98963318372777,
            "unit": "ns/iter",
            "extra": "iterations: 36627928\ncpu: 18.988379577463522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1153.3276906617532,
            "unit": "ns/iter",
            "extra": "iterations: 620628\ncpu: 1145.5219551808818 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 817.4282846902768,
            "unit": "ns/iter",
            "extra": "iterations: 860416\ncpu: 817.277921377572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1110.9548266629765,
            "unit": "ns/iter",
            "extra": "iterations: 630881\ncpu: 1110.9480234782689 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 46.98978431631425,
            "unit": "ns/iter",
            "extra": "iterations: 14886522\ncpu: 46.98686503133475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1313.6698469700984,
            "unit": "ns/iter",
            "extra": "iterations: 543554\ncpu: 1313.3635296584941 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 70.46284535076768,
            "unit": "ns/iter",
            "extra": "iterations: 10099261\ncpu: 70.16523288189073 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 63.17796378059184,
            "unit": "ns/iter",
            "extra": "iterations: 10825523\ncpu: 63.14059838032811 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 182.01674926639234,
            "unit": "ns/iter",
            "extra": "iterations: 3883991\ncpu: 181.89511767663768 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 596.4292863474263,
            "unit": "ns/iter",
            "extra": "iterations: 1156375\ncpu: 596.4060101610717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 116.76622490544797,
            "unit": "ns/iter",
            "extra": "iterations: 6062023\ncpu: 116.75838247396912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 302.68599267077605,
            "unit": "ns/iter",
            "extra": "iterations: 2371330\ncpu: 302.68625623595074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_OMC_JSON_V2_1",
            "value": 8180.111016154869,
            "unit": "ns/iter",
            "extra": "iterations: 85420\ncpu: 8179.747131819192 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 981.6683261461902,
            "unit": "ns/iter",
            "extra": "iterations: 710062\ncpu: 981.6551230737757 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}