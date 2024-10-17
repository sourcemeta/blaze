window.BENCHMARK_DATA = {
  "lastUpdate": 1729196907179,
  "repoUrl": "https://github.com/sourcemeta/blaze",
  "entries": {
    "Benchmark (linux/llvm)": [
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
        "date": 1729018399478,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4905545630.000006,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4905437053 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 950.3956741993435,
            "unit": "ns/iter",
            "extra": "iterations: 718341\ncpu: 950.3303458942212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1589.8608742328013,
            "unit": "ns/iter",
            "extra": "iterations: 445259\ncpu: 1589.7832003395774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 177.80032010088928,
            "unit": "ns/iter",
            "extra": "iterations: 3933135\ncpu: 177.79423691279342 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 123.47202235302153,
            "unit": "ns/iter",
            "extra": "iterations: 5650779\ncpu: 123.47111469055841 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3566.269534952521,
            "unit": "ns/iter",
            "extra": "iterations: 196238\ncpu: 3566.2801649018065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.455743745074805,
            "unit": "ns/iter",
            "extra": "iterations: 20836501\ncpu: 33.45529674104114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1702.4544121831152,
            "unit": "ns/iter",
            "extra": "iterations: 414738\ncpu: 1702.4399066398557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1407.7667171124767,
            "unit": "ns/iter",
            "extra": "iterations: 492938\ncpu: 1407.7541901821317 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1784.1432261819018,
            "unit": "ns/iter",
            "extra": "iterations: 395235\ncpu: 1784.1332726099663 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 483.74336973146853,
            "unit": "ns/iter",
            "extra": "iterations: 1403186\ncpu: 483.74313455236876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2334.2698267479404,
            "unit": "ns/iter",
            "extra": "iterations: 296216\ncpu: 2334.283387798094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 125.96650779780394,
            "unit": "ns/iter",
            "extra": "iterations: 5557204\ncpu: 125.96831914034458 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 608.4669438157387,
            "unit": "ns/iter",
            "extra": "iterations: 1152689\ncpu: 608.0360366065805 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 463.32695297187973,
            "unit": "ns/iter",
            "extra": "iterations: 1510416\ncpu: 463.3310730288869 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1202.4553956758266,
            "unit": "ns/iter",
            "extra": "iterations: 567232\ncpu: 1202.4639371544633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 202.05884673727775,
            "unit": "ns/iter",
            "extra": "iterations: 3462316\ncpu: 202.06372150895527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1809.1717818102127,
            "unit": "ns/iter",
            "extra": "iterations: 386141\ncpu: 1809.1692153902288 ns\nthreads: 1"
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
        "date": 1729019127251,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4954712632.999986,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4954553366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 954.3438910818618,
            "unit": "ns/iter",
            "extra": "iterations: 733395\ncpu: 954.3193885968676 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1572.4223729069718,
            "unit": "ns/iter",
            "extra": "iterations: 448471\ncpu: 1572.4116052097015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 180.29557237481075,
            "unit": "ns/iter",
            "extra": "iterations: 3743858\ncpu: 180.2913529305864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 125.16993397741956,
            "unit": "ns/iter",
            "extra": "iterations: 5588694\ncpu: 125.16388658960402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3603.026973047303,
            "unit": "ns/iter",
            "extra": "iterations: 195269\ncpu: 3602.9125565245854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.594175985226926,
            "unit": "ns/iter",
            "extra": "iterations: 20718148\ncpu: 33.593585295365216 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1692.788307684655,
            "unit": "ns/iter",
            "extra": "iterations: 400605\ncpu: 1692.7831504848918 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1412.401589485735,
            "unit": "ns/iter",
            "extra": "iterations: 489089\ncpu: 1412.3828362527047 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1768.2903611932572,
            "unit": "ns/iter",
            "extra": "iterations: 395993\ncpu: 1768.2700072981063 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 478.1711831275388,
            "unit": "ns/iter",
            "extra": "iterations: 1459513\ncpu: 478.16828764115087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2316.8368674738613,
            "unit": "ns/iter",
            "extra": "iterations: 301865\ncpu: 2316.822112533748 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 125.71639378402112,
            "unit": "ns/iter",
            "extra": "iterations: 5565213\ncpu: 125.71550325207646 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 593.3648491830023,
            "unit": "ns/iter",
            "extra": "iterations: 1178846\ncpu: 593.3495087568683 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 466.03237477667847,
            "unit": "ns/iter",
            "extra": "iterations: 1506049\ncpu: 466.0188665840222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1249.425624396998,
            "unit": "ns/iter",
            "extra": "iterations: 588728\ncpu: 1249.378004783193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 209.0795899210533,
            "unit": "ns/iter",
            "extra": "iterations: 3360036\ncpu: 209.0785932055493 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1826.0955150567859,
            "unit": "ns/iter",
            "extra": "iterations: 389258\ncpu: 1826.0163901576889 ns\nthreads: 1"
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
        "date": 1729019733218,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4898442454.000019,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4898140769.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 952.2393723051317,
            "unit": "ns/iter",
            "extra": "iterations: 734943\ncpu: 952.2328126126796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1565.3030805844558,
            "unit": "ns/iter",
            "extra": "iterations: 453810\ncpu: 1565.2950882527948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 176.64001764140465,
            "unit": "ns/iter",
            "extra": "iterations: 3759337\ncpu: 176.49012551947314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 121.93020279295445,
            "unit": "ns/iter",
            "extra": "iterations: 5744184\ncpu: 121.92793545610664 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3569.914676727593,
            "unit": "ns/iter",
            "extra": "iterations: 195609\ncpu: 3569.86006267606 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 32.34297684797143,
            "unit": "ns/iter",
            "extra": "iterations: 21623375\ncpu: 32.34198033378236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1698.7912407401452,
            "unit": "ns/iter",
            "extra": "iterations: 408619\ncpu: 1698.7831990191328 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1399.6681831629635,
            "unit": "ns/iter",
            "extra": "iterations: 500276\ncpu: 1399.6488678249623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1762.2355628783482,
            "unit": "ns/iter",
            "extra": "iterations: 395716\ncpu: 1762.197189398457 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.63874225286884,
            "unit": "ns/iter",
            "extra": "iterations: 1454092\ncpu: 480.6329957114124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2327.1365454490747,
            "unit": "ns/iter",
            "extra": "iterations: 300259\ncpu: 2327.1485217762056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 127.004724404265,
            "unit": "ns/iter",
            "extra": "iterations: 5473706\ncpu: 127.0024919131575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 597.7926483329634,
            "unit": "ns/iter",
            "extra": "iterations: 1170374\ncpu: 597.7958943038714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 466.23393601410265,
            "unit": "ns/iter",
            "extra": "iterations: 1499799\ncpu: 466.21576824627755 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1228.582144249061,
            "unit": "ns/iter",
            "extra": "iterations: 567033\ncpu: 1228.565836556246 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 208.24104504470017,
            "unit": "ns/iter",
            "extra": "iterations: 3359397\ncpu: 208.23554286677057 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1906.4563601777636,
            "unit": "ns/iter",
            "extra": "iterations: 377969\ncpu: 1906.4485976363128 ns\nthreads: 1"
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
        "date": 1729021427870,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5066383874.999986,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5062039954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 960.5289215887863,
            "unit": "ns/iter",
            "extra": "iterations: 727830\ncpu: 960.4829465671938 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1566.9551564820465,
            "unit": "ns/iter",
            "extra": "iterations: 449764\ncpu: 1566.8217665264433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 178.10833163987786,
            "unit": "ns/iter",
            "extra": "iterations: 3892427\ncpu: 178.09772720207715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 125.10622744966118,
            "unit": "ns/iter",
            "extra": "iterations: 5588885\ncpu: 125.0971614194959 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3550.795532936733,
            "unit": "ns/iter",
            "extra": "iterations: 195117\ncpu: 3550.6356493795956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.0091833597179,
            "unit": "ns/iter",
            "extra": "iterations: 21198342\ncpu: 33.00593173749159 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1689.3963693454364,
            "unit": "ns/iter",
            "extra": "iterations: 407640\ncpu: 1685.7280320871366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1414.7460715975105,
            "unit": "ns/iter",
            "extra": "iterations: 486330\ncpu: 1414.6165875023155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1761.0107271651516,
            "unit": "ns/iter",
            "extra": "iterations: 393487\ncpu: 1760.7883335408799 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 498.34585483413366,
            "unit": "ns/iter",
            "extra": "iterations: 1454405\ncpu: 498.29533658093885 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2337.565812685475,
            "unit": "ns/iter",
            "extra": "iterations: 299304\ncpu: 2337.375307379786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 127.68984955437928,
            "unit": "ns/iter",
            "extra": "iterations: 5449278\ncpu: 127.68225607135423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 596.0949153927601,
            "unit": "ns/iter",
            "extra": "iterations: 1174899\ncpu: 596.0785820738631 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 464.74291636944264,
            "unit": "ns/iter",
            "extra": "iterations: 1493055\ncpu: 464.7271895543031 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1225.8248344521678,
            "unit": "ns/iter",
            "extra": "iterations: 571134\ncpu: 1225.7819723567504 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 203.45868873432872,
            "unit": "ns/iter",
            "extra": "iterations: 3437549\ncpu: 203.4547251544638 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1842.3712337794625,
            "unit": "ns/iter",
            "extra": "iterations: 385466\ncpu: 1842.2921891943784 ns\nthreads: 1"
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
        "date": 1729022134393,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4892212854.999969,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4888885507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 960.6635538362237,
            "unit": "ns/iter",
            "extra": "iterations: 729454\ncpu: 960.6119796450499 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1587.1867338085594,
            "unit": "ns/iter",
            "extra": "iterations: 428744\ncpu: 1587.0906974791474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 176.09110369666115,
            "unit": "ns/iter",
            "extra": "iterations: 3832457\ncpu: 176.08066939824786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 122.18556930148569,
            "unit": "ns/iter",
            "extra": "iterations: 5745945\ncpu: 122.18103810600329 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3584.8137053129612,
            "unit": "ns/iter",
            "extra": "iterations: 196785\ncpu: 3584.6030947480826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 32.409282676453905,
            "unit": "ns/iter",
            "extra": "iterations: 21653130\ncpu: 32.40679559952764 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1702.1736929176996,
            "unit": "ns/iter",
            "extra": "iterations: 411030\ncpu: 1702.0764640050613 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1406.0990072525722,
            "unit": "ns/iter",
            "extra": "iterations: 493479\ncpu: 1406.0364534255752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1792.0578312823652,
            "unit": "ns/iter",
            "extra": "iterations: 392573\ncpu: 1792.0120945658532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 468.68868915658504,
            "unit": "ns/iter",
            "extra": "iterations: 1399206\ncpu: 468.5951818388429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2363.577656008085,
            "unit": "ns/iter",
            "extra": "iterations: 293815\ncpu: 2363.440842026447 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 125.80289349987446,
            "unit": "ns/iter",
            "extra": "iterations: 5605599\ncpu: 125.79578988793193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 598.3436012798388,
            "unit": "ns/iter",
            "extra": "iterations: 1173555\ncpu: 598.298904610352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 464.728502885902,
            "unit": "ns/iter",
            "extra": "iterations: 1497294\ncpu: 464.720535178797 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1230.259388217564,
            "unit": "ns/iter",
            "extra": "iterations: 572393\ncpu: 1230.2199363025093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 201.91372648579207,
            "unit": "ns/iter",
            "extra": "iterations: 3430798\ncpu: 201.91218923410807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1806.1083274660236,
            "unit": "ns/iter",
            "extra": "iterations: 387741\ncpu: 1806.0324907605866 ns\nthreads: 1"
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
        "date": 1729023587009,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4875065967.000011,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4874914713.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 962.0959745376479,
            "unit": "ns/iter",
            "extra": "iterations: 739915\ncpu: 962.0655386091644 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1550.3363173979587,
            "unit": "ns/iter",
            "extra": "iterations: 448270\ncpu: 1550.282619849645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 176.91203780616843,
            "unit": "ns/iter",
            "extra": "iterations: 3954699\ncpu: 176.90970412666016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 122.95024182279997,
            "unit": "ns/iter",
            "extra": "iterations: 5715342\ncpu: 122.94785281440724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3565.118377702369,
            "unit": "ns/iter",
            "extra": "iterations: 196684\ncpu: 3565.0993725976614 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 32.70159925878659,
            "unit": "ns/iter",
            "extra": "iterations: 21424300\ncpu: 32.697011524297174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1693.5072680050905,
            "unit": "ns/iter",
            "extra": "iterations: 415451\ncpu: 1693.4844085102695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1408.0932404016496,
            "unit": "ns/iter",
            "extra": "iterations: 498861\ncpu: 1408.0548509504654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1820.0196420180582,
            "unit": "ns/iter",
            "extra": "iterations: 395886\ncpu: 1819.9974209747265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.4256091523969,
            "unit": "ns/iter",
            "extra": "iterations: 1454480\ncpu: 480.4119939772282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2322.4254414682346,
            "unit": "ns/iter",
            "extra": "iterations: 300871\ncpu: 2322.4129676838193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 128.02813850099596,
            "unit": "ns/iter",
            "extra": "iterations: 5502603\ncpu: 128.02402862790584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 595.0057130915363,
            "unit": "ns/iter",
            "extra": "iterations: 1177121\ncpu: 594.9771884113846 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 466.3046069571719,
            "unit": "ns/iter",
            "extra": "iterations: 1499493\ncpu: 466.29463958818206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1220.012091608928,
            "unit": "ns/iter",
            "extra": "iterations: 572215\ncpu: 1219.9813531627105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 203.54189135657495,
            "unit": "ns/iter",
            "extra": "iterations: 3435661\ncpu: 203.5284767618233 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1834.467031267719,
            "unit": "ns/iter",
            "extra": "iterations: 388004\ncpu: 1834.3833774909542 ns\nthreads: 1"
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
        "date": 1729024637335,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5028195906.999997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5025107548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 974.8287367650341,
            "unit": "ns/iter",
            "extra": "iterations: 718362\ncpu: 974.7657740804781 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1590.1953535539021,
            "unit": "ns/iter",
            "extra": "iterations: 444727\ncpu: 1590.0985256123427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 189.44524352804345,
            "unit": "ns/iter",
            "extra": "iterations: 3836478\ncpu: 189.43616410676682 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 124.13345722946195,
            "unit": "ns/iter",
            "extra": "iterations: 5650432\ncpu: 124.12403281731383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3603.4892687046945,
            "unit": "ns/iter",
            "extra": "iterations: 196528\ncpu: 3603.2797667507944 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.68530146995132,
            "unit": "ns/iter",
            "extra": "iterations: 20839805\ncpu: 33.68338633686827 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1764.0290567790266,
            "unit": "ns/iter",
            "extra": "iterations: 404656\ncpu: 1764.0179658771904 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1432.3174956235919,
            "unit": "ns/iter",
            "extra": "iterations: 491843\ncpu: 1432.2860546963138 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1811.2563027820697,
            "unit": "ns/iter",
            "extra": "iterations: 386258\ncpu: 1811.2077083193135 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 487.92761732698193,
            "unit": "ns/iter",
            "extra": "iterations: 1434708\ncpu: 487.92003390236954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2391.476000758859,
            "unit": "ns/iter",
            "extra": "iterations: 295176\ncpu: 2391.458638236174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 126.91440929062206,
            "unit": "ns/iter",
            "extra": "iterations: 5485794\ncpu: 126.9136094064048 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 608.079683321889,
            "unit": "ns/iter",
            "extra": "iterations: 1152211\ncpu: 608.0658308243871 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 469.45502939635895,
            "unit": "ns/iter",
            "extra": "iterations: 1493042\ncpu: 469.4327808594802 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1232.9375969757737,
            "unit": "ns/iter",
            "extra": "iterations: 567152\ncpu: 1232.908269740738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 214.27660160934607,
            "unit": "ns/iter",
            "extra": "iterations: 3272396\ncpu: 214.2727475525581 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1836.9862491151468,
            "unit": "ns/iter",
            "extra": "iterations: 381430\ncpu: 1836.808580866739 ns\nthreads: 1"
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
        "date": 1729086173992,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4906467399.999997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4902722343 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 953.8877112739266,
            "unit": "ns/iter",
            "extra": "iterations: 735479\ncpu: 953.8160736064528 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1569.1962059731152,
            "unit": "ns/iter",
            "extra": "iterations: 445068\ncpu: 1569.154551664015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 184.9341135852422,
            "unit": "ns/iter",
            "extra": "iterations: 3937959\ncpu: 184.93141345554906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 123.47811754189216,
            "unit": "ns/iter",
            "extra": "iterations: 5669587\ncpu: 123.4753947686136 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3645.542493349353,
            "unit": "ns/iter",
            "extra": "iterations: 196972\ncpu: 3645.4890492049603 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.69861615351625,
            "unit": "ns/iter",
            "extra": "iterations: 20811268\ncpu: 33.696173774707006 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1735.741930498836,
            "unit": "ns/iter",
            "extra": "iterations: 407677\ncpu: 1735.7322120207941 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1430.8261953863423,
            "unit": "ns/iter",
            "extra": "iterations: 491201\ncpu: 1430.7966087202603 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1781.0133480870777,
            "unit": "ns/iter",
            "extra": "iterations: 387696\ncpu: 1780.972991725476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 481.4231514145826,
            "unit": "ns/iter",
            "extra": "iterations: 1454477\ncpu: 481.41764015518896 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2346.221208231931,
            "unit": "ns/iter",
            "extra": "iterations: 296847\ncpu: 2346.2066350678915 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 126.19435247774733,
            "unit": "ns/iter",
            "extra": "iterations: 5605290\ncpu: 126.19321212640202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 593.2307241721282,
            "unit": "ns/iter",
            "extra": "iterations: 1164295\ncpu: 593.1889795970974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 465.04187113331477,
            "unit": "ns/iter",
            "extra": "iterations: 1503709\ncpu: 465.03730442525693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1229.4337746182864,
            "unit": "ns/iter",
            "extra": "iterations: 566905\ncpu: 1229.3798308358546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 205.93379137253157,
            "unit": "ns/iter",
            "extra": "iterations: 3420959\ncpu: 205.9268348436791 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1833.2920799411522,
            "unit": "ns/iter",
            "extra": "iterations: 384833\ncpu: 1833.1691876736118 ns\nthreads: 1"
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
        "date": 1729105541826,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5228062936.000015,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5227627601 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1033.7866236554148,
            "unit": "ns/iter",
            "extra": "iterations: 679513\ncpu: 1033.682875824303 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1640.1618954905716,
            "unit": "ns/iter",
            "extra": "iterations: 431445\ncpu: 1640.0919630543872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.1824980352819,
            "unit": "ns/iter",
            "extra": "iterations: 3729547\ncpu: 185.16917121569972 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 134.02205058657552,
            "unit": "ns/iter",
            "extra": "iterations: 5424799\ncpu: 134.014230757674 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3781.9372400264165,
            "unit": "ns/iter",
            "extra": "iterations: 185596\ncpu: 3781.6155897756435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.745273248204214,
            "unit": "ns/iter",
            "extra": "iterations: 20731097\ncpu: 33.74339804594039 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1854.5627949980221,
            "unit": "ns/iter",
            "extra": "iterations: 381782\ncpu: 1854.4101031478701 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1503.0807077807206,
            "unit": "ns/iter",
            "extra": "iterations: 458221\ncpu: 1502.930622996326 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1911.1249045175166,
            "unit": "ns/iter",
            "extra": "iterations: 366560\ncpu: 1910.9604403099067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 502.64887246910786,
            "unit": "ns/iter",
            "extra": "iterations: 1403997\ncpu: 502.6228175701228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2513.850841899807,
            "unit": "ns/iter",
            "extra": "iterations: 278121\ncpu: 2513.672365625028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 134.63857085126625,
            "unit": "ns/iter",
            "extra": "iterations: 5228679\ncpu: 134.62707330092348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 579.3017194742072,
            "unit": "ns/iter",
            "extra": "iterations: 1203333\ncpu: 579.2902953712719 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 522.2351283647723,
            "unit": "ns/iter",
            "extra": "iterations: 1339698\ncpu: 522.2165570150902 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1259.8643449539347,
            "unit": "ns/iter",
            "extra": "iterations: 554045\ncpu: 1259.8133454863757 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 221.80497862011256,
            "unit": "ns/iter",
            "extra": "iterations: 3159510\ncpu: 221.78729296631505 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1928.1363796859007,
            "unit": "ns/iter",
            "extra": "iterations: 362510\ncpu: 1928.019356707401 ns\nthreads: 1"
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
        "date": 1729115813865,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5193981269.999995,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5192967716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 993.2011178310248,
            "unit": "ns/iter",
            "extra": "iterations: 697601\ncpu: 993.1498664709486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1578.832286675323,
            "unit": "ns/iter",
            "extra": "iterations: 434080\ncpu: 1578.673286030226 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 182.58096247229494,
            "unit": "ns/iter",
            "extra": "iterations: 3845825\ncpu: 182.56701669992788 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 131.2978818051259,
            "unit": "ns/iter",
            "extra": "iterations: 5345731\ncpu: 131.29115288442313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3517.931164936004,
            "unit": "ns/iter",
            "extra": "iterations: 199041\ncpu: 3517.7571203922785 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 32.24739039554847,
            "unit": "ns/iter",
            "extra": "iterations: 21579803\ncpu: 32.24446284333551 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1823.0624713844318,
            "unit": "ns/iter",
            "extra": "iterations: 382223\ncpu: 1822.9898907182446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1490.842290597449,
            "unit": "ns/iter",
            "extra": "iterations: 471126\ncpu: 1490.7657887698829 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1919.0397242680751,
            "unit": "ns/iter",
            "extra": "iterations: 364412\ncpu: 1918.907739042623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 481.3396716332242,
            "unit": "ns/iter",
            "extra": "iterations: 1456542\ncpu: 481.30212242420663 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2462.1850206138474,
            "unit": "ns/iter",
            "extra": "iterations: 286941\ncpu: 2462.0894678696973 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 133.5882905721702,
            "unit": "ns/iter",
            "extra": "iterations: 5245141\ncpu: 133.5827507782919 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 604.4118834859029,
            "unit": "ns/iter",
            "extra": "iterations: 1160821\ncpu: 604.4045679738742 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 465.02061712669456,
            "unit": "ns/iter",
            "extra": "iterations: 1492303\ncpu: 464.9893339355339 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1234.1726569644602,
            "unit": "ns/iter",
            "extra": "iterations: 558709\ncpu: 1234.1617622053698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 208.26338566245678,
            "unit": "ns/iter",
            "extra": "iterations: 3337657\ncpu: 208.26289969280828 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1162.636128744206,
            "unit": "ns/iter",
            "extra": "iterations: 609177\ncpu: 1162.6130155931671 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1838.4434487724682,
            "unit": "ns/iter",
            "extra": "iterations: 377746\ncpu: 1838.3454040545744 ns\nthreads: 1"
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
        "date": 1729170746762,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5217532136.999978,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5217350344 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 978.7215249152293,
            "unit": "ns/iter",
            "extra": "iterations: 700393\ncpu: 978.708142428608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1654.0632890756503,
            "unit": "ns/iter",
            "extra": "iterations: 429379\ncpu: 1653.9910615097624 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 183.84745187980525,
            "unit": "ns/iter",
            "extra": "iterations: 3768896\ncpu: 183.84578746667435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 131.788798406815,
            "unit": "ns/iter",
            "extra": "iterations: 5335741\ncpu: 131.78541462188673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3561.7097008563674,
            "unit": "ns/iter",
            "extra": "iterations: 198199\ncpu: 3561.7100237639897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.45449290973327,
            "unit": "ns/iter",
            "extra": "iterations: 20550424\ncpu: 33.45226697025816 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1805.8198206366806,
            "unit": "ns/iter",
            "extra": "iterations: 386032\ncpu: 1805.7333588925276 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1498.764570349421,
            "unit": "ns/iter",
            "extra": "iterations: 469172\ncpu: 1498.674692863171 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1901.943112161574,
            "unit": "ns/iter",
            "extra": "iterations: 369833\ncpu: 1901.847952994999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 488.20206774720134,
            "unit": "ns/iter",
            "extra": "iterations: 1433831\ncpu: 488.19640599205894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2469.521284661895,
            "unit": "ns/iter",
            "extra": "iterations: 283561\ncpu: 2469.5187984243234 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 134.9249428333927,
            "unit": "ns/iter",
            "extra": "iterations: 5156856\ncpu: 134.92364805222357 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 613.9968453679089,
            "unit": "ns/iter",
            "extra": "iterations: 1143081\ncpu: 613.9712653783955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 477.96882105641794,
            "unit": "ns/iter",
            "extra": "iterations: 1467144\ncpu: 477.96407237462716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1274.454441264801,
            "unit": "ns/iter",
            "extra": "iterations: 565402\ncpu: 1274.4315778861717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 213.6769127866535,
            "unit": "ns/iter",
            "extra": "iterations: 3281665\ncpu: 213.67297118992892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 747.5393746903087,
            "unit": "ns/iter",
            "extra": "iterations: 938255\ncpu: 747.5010791309392 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1840.3221684093912,
            "unit": "ns/iter",
            "extra": "iterations: 380537\ncpu: 1840.3035788898276 ns\nthreads: 1"
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
        "date": 1729187955518,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5234415408.000018,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5234043366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1008.9705740079083,
            "unit": "ns/iter",
            "extra": "iterations: 698736\ncpu: 1008.8815060337522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1630.5914389286372,
            "unit": "ns/iter",
            "extra": "iterations: 430063\ncpu: 1630.523800001396 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 183.64737482470665,
            "unit": "ns/iter",
            "extra": "iterations: 3825935\ncpu: 183.6421640723118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 132.44292692703388,
            "unit": "ns/iter",
            "extra": "iterations: 5288755\ncpu: 132.43506004721326 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3710.1851872780817,
            "unit": "ns/iter",
            "extra": "iterations: 194657\ncpu: 3709.991199905477 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 34.42614164996522,
            "unit": "ns/iter",
            "extra": "iterations: 20370933\ncpu: 34.42451290768076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1837.602412028239,
            "unit": "ns/iter",
            "extra": "iterations: 383163\ncpu: 1837.5516242434687 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1504.9664867820566,
            "unit": "ns/iter",
            "extra": "iterations: 468263\ncpu: 1504.8952767995745 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1919.9226856255916,
            "unit": "ns/iter",
            "extra": "iterations: 366827\ncpu: 1919.7584120034749 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 492.13510511081466,
            "unit": "ns/iter",
            "extra": "iterations: 1424972\ncpu: 491.3115780520607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2492.9148405248884,
            "unit": "ns/iter",
            "extra": "iterations: 282928\ncpu: 2492.8549418933508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 135.88390475869883,
            "unit": "ns/iter",
            "extra": "iterations: 5163054\ncpu: 135.87828308594126 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 613.1263641936939,
            "unit": "ns/iter",
            "extra": "iterations: 1143441\ncpu: 613.0899906510256 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 481.2940040108645,
            "unit": "ns/iter",
            "extra": "iterations: 1453555\ncpu: 481.2723742823634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1276.9786805567762,
            "unit": "ns/iter",
            "extra": "iterations: 545230\ncpu: 1276.9335803239014 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 211.5011769574211,
            "unit": "ns/iter",
            "extra": "iterations: 3305982\ncpu: 211.4860474134462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 763.8155143397167,
            "unit": "ns/iter",
            "extra": "iterations: 917448\ncpu: 763.758992335263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1864.8148728953415,
            "unit": "ns/iter",
            "extra": "iterations: 375596\ncpu: 1864.7056065559789 ns\nthreads: 1"
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
        "date": 1729188603907,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5229269178.000038,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5229117960.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1019.5586909148864,
            "unit": "ns/iter",
            "extra": "iterations: 684203\ncpu: 1019.5448909168759 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1619.0786590620341,
            "unit": "ns/iter",
            "extra": "iterations: 414307\ncpu: 1619.0052617986182 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 199.26404480484064,
            "unit": "ns/iter",
            "extra": "iterations: 3516585\ncpu: 199.2644608334508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 134.8684206887364,
            "unit": "ns/iter",
            "extra": "iterations: 5206852\ncpu: 134.86659328899697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3707.1465002571463,
            "unit": "ns/iter",
            "extra": "iterations: 188771\ncpu: 3707.1540914653224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 33.169487337163424,
            "unit": "ns/iter",
            "extra": "iterations: 21148695\ncpu: 33.16799050721563 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1827.8629158753938,
            "unit": "ns/iter",
            "extra": "iterations: 387616\ncpu: 1827.8225047469657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1497.740841853667,
            "unit": "ns/iter",
            "extra": "iterations: 468490\ncpu: 1497.6939358364075 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1892.363941666482,
            "unit": "ns/iter",
            "extra": "iterations: 370422\ncpu: 1892.3486078040723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 495.62291294613647,
            "unit": "ns/iter",
            "extra": "iterations: 1369095\ncpu: 495.6206640152806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2451.855601622352,
            "unit": "ns/iter",
            "extra": "iterations: 287988\ncpu: 2451.841038515492 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 145.86457419606134,
            "unit": "ns/iter",
            "extra": "iterations: 4802903\ncpu: 145.86278277949856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 624.4925400008871,
            "unit": "ns/iter",
            "extra": "iterations: 1121850\ncpu: 624.4720229977256 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 508.3874949164454,
            "unit": "ns/iter",
            "extra": "iterations: 1381902\ncpu: 508.3807737451713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1249.796969931274,
            "unit": "ns/iter",
            "extra": "iterations: 556159\ncpu: 1249.7725182906352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 219.9878398464499,
            "unit": "ns/iter",
            "extra": "iterations: 3180223\ncpu: 219.9887875787329 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 770.6477964155586,
            "unit": "ns/iter",
            "extra": "iterations: 916416\ncpu: 770.6326755534571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1934.4036999424413,
            "unit": "ns/iter",
            "extra": "iterations: 364330\ncpu: 1934.3929459555907 ns\nthreads: 1"
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
        "date": 1729189604502,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5408372566.999958,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5408047918.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 980.9211334530019,
            "unit": "ns/iter",
            "extra": "iterations: 714701\ncpu: 980.8874522352712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1573.9926065352006,
            "unit": "ns/iter",
            "extra": "iterations: 449992\ncpu: 1573.9908131700124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 180.24629143005413,
            "unit": "ns/iter",
            "extra": "iterations: 3888089\ncpu: 180.24119586768686 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.05009477469464,
            "unit": "ns/iter",
            "extra": "iterations: 5463484\ncpu: 127.04773840282135 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3586.6251804157337,
            "unit": "ns/iter",
            "extra": "iterations: 195382\ncpu: 3586.5251404940086 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 31.25871137848703,
            "unit": "ns/iter",
            "extra": "iterations: 22380241\ncpu: 31.257953388437567 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1804.8981879484763,
            "unit": "ns/iter",
            "extra": "iterations: 387351\ncpu: 1804.81339663509 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1490.6848684379156,
            "unit": "ns/iter",
            "extra": "iterations: 469588\ncpu: 1490.6393774968715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1883.4297117290419,
            "unit": "ns/iter",
            "extra": "iterations: 371456\ncpu: 1883.3291103118554 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 464.41267582407403,
            "unit": "ns/iter",
            "extra": "iterations: 1522047\ncpu: 464.39384591934487 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2399.656690276318,
            "unit": "ns/iter",
            "extra": "iterations: 286042\ncpu: 2399.557260821836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 129.98465638544818,
            "unit": "ns/iter",
            "extra": "iterations: 5382630\ncpu: 129.97929636627478 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 605.2817973584728,
            "unit": "ns/iter",
            "extra": "iterations: 1156920\ncpu: 605.2759810531419 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 477.9948175760636,
            "unit": "ns/iter",
            "extra": "iterations: 1462829\ncpu: 477.96986865860646 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1252.6481350538652,
            "unit": "ns/iter",
            "extra": "iterations: 565700\ncpu: 1252.5699381297554 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 208.00593112105727,
            "unit": "ns/iter",
            "extra": "iterations: 3371538\ncpu: 207.99514553891993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 753.3843200106355,
            "unit": "ns/iter",
            "extra": "iterations: 931544\ncpu: 753.3490044485296 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1867.3184987992345,
            "unit": "ns/iter",
            "extra": "iterations: 380149\ncpu: 1867.2305648574634 ns\nthreads: 1"
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
        "date": 1729190551195,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5312041257.999965,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5311619529 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 976.962994252921,
            "unit": "ns/iter",
            "extra": "iterations: 719672\ncpu: 976.9252159317023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1538.3553180559804,
            "unit": "ns/iter",
            "extra": "iterations: 461381\ncpu: 1538.314514468521 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 180.20887722791045,
            "unit": "ns/iter",
            "extra": "iterations: 3915434\ncpu: 180.2063761003251 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 125.40850478904697,
            "unit": "ns/iter",
            "extra": "iterations: 5576270\ncpu: 125.39964815190093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3447.703874270222,
            "unit": "ns/iter",
            "extra": "iterations: 202593\ncpu: 3447.6220698642046 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.40355127405485,
            "unit": "ns/iter",
            "extra": "iterations: 23079548\ncpu: 30.402771579408707 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1825.0001579168922,
            "unit": "ns/iter",
            "extra": "iterations: 386279\ncpu: 1824.9466706706808 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1504.3774964073518,
            "unit": "ns/iter",
            "extra": "iterations: 466921\ncpu: 1504.320497471735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1895.5309399813377,
            "unit": "ns/iter",
            "extra": "iterations: 369635\ncpu: 1895.4004139218405 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 501.2597759999835,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 501.2265819999992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2475.3062445093465,
            "unit": "ns/iter",
            "extra": "iterations: 284570\ncpu: 2475.150989211787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 128.5379325277329,
            "unit": "ns/iter",
            "extra": "iterations: 5177298\ncpu: 128.52868040433447 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 601.8132539636097,
            "unit": "ns/iter",
            "extra": "iterations: 1164844\ncpu: 601.7816557410267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 468.10429557249023,
            "unit": "ns/iter",
            "extra": "iterations: 1497379\ncpu: 468.09778553058425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1248.1886003728462,
            "unit": "ns/iter",
            "extra": "iterations: 563843\ncpu: 1248.1691339610488 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 203.40568526550476,
            "unit": "ns/iter",
            "extra": "iterations: 3428547\ncpu: 203.39961505559023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 729.8286515781604,
            "unit": "ns/iter",
            "extra": "iterations: 943236\ncpu: 729.7781658036789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1852.845747525499,
            "unit": "ns/iter",
            "extra": "iterations: 379579\ncpu: 1852.7008317109187 ns\nthreads: 1"
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
        "date": 1729191539327,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5185867568.999981,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5184953439.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 968.4003942639464,
            "unit": "ns/iter",
            "extra": "iterations: 720837\ncpu: 968.3875161791091 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1679.987866711854,
            "unit": "ns/iter",
            "extra": "iterations: 415551\ncpu: 1679.9308845364344 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 179.36692429848938,
            "unit": "ns/iter",
            "extra": "iterations: 3909196\ncpu: 179.35929382921688 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 130.08214326743584,
            "unit": "ns/iter",
            "extra": "iterations: 5370641\ncpu: 130.0745808554325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3473.2320479971177,
            "unit": "ns/iter",
            "extra": "iterations: 202178\ncpu: 3473.07983064429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.10777186473936,
            "unit": "ns/iter",
            "extra": "iterations: 24075226\ncpu: 29.10560432537578 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1784.9251843670513,
            "unit": "ns/iter",
            "extra": "iterations: 392966\ncpu: 1784.8352071171566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1474.9557864917047,
            "unit": "ns/iter",
            "extra": "iterations: 473724\ncpu: 1474.8764998184615 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1866.060871710954,
            "unit": "ns/iter",
            "extra": "iterations: 376891\ncpu: 1865.9834832882707 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 477.58219267299137,
            "unit": "ns/iter",
            "extra": "iterations: 1474000\ncpu: 477.55668724559007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2469.6479691339914,
            "unit": "ns/iter",
            "extra": "iterations: 283549\ncpu: 2469.538940359511 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 135.46994292442963,
            "unit": "ns/iter",
            "extra": "iterations: 5157022\ncpu: 135.46249657263473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 592.1466148566524,
            "unit": "ns/iter",
            "extra": "iterations: 1187158\ncpu: 592.1152635116821 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 462.2031935469312,
            "unit": "ns/iter",
            "extra": "iterations: 1509231\ncpu: 462.1820655684925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1283.5696527128512,
            "unit": "ns/iter",
            "extra": "iterations: 542836\ncpu: 1283.5161945781015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 201.56636846926918,
            "unit": "ns/iter",
            "extra": "iterations: 3465825\ncpu: 201.5531892118044 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 783.7243401957053,
            "unit": "ns/iter",
            "extra": "iterations: 892992\ncpu: 783.6867228373819 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1855.166066356159,
            "unit": "ns/iter",
            "extra": "iterations: 380914\ncpu: 1855.1146426752496 ns\nthreads: 1"
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
        "date": 1729191945960,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5254180197.000039,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5253860912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 976.1014188065781,
            "unit": "ns/iter",
            "extra": "iterations: 723002\ncpu: 975.9986805015753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1623.2832061085678,
            "unit": "ns/iter",
            "extra": "iterations: 427459\ncpu: 1623.247663518607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 180.9178308527149,
            "unit": "ns/iter",
            "extra": "iterations: 3851117\ncpu: 180.91186946540446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.93555269921643,
            "unit": "ns/iter",
            "extra": "iterations: 5514428\ncpu: 127.93559005575891 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3456.432265111202,
            "unit": "ns/iter",
            "extra": "iterations: 201425\ncpu: 3456.320163832689 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 28.471068147142578,
            "unit": "ns/iter",
            "extra": "iterations: 24554632\ncpu: 28.470699173988876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1760.7334752583683,
            "unit": "ns/iter",
            "extra": "iterations: 395044\ncpu: 1760.6389465477264 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1470.9895736058181,
            "unit": "ns/iter",
            "extra": "iterations: 447614\ncpu: 1470.965789720608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1846.0975707651314,
            "unit": "ns/iter",
            "extra": "iterations: 381190\ncpu: 1846.0567407329715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 474.03149485191074,
            "unit": "ns/iter",
            "extra": "iterations: 1475892\ncpu: 474.02625395354056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2468.4193180127168,
            "unit": "ns/iter",
            "extra": "iterations: 282058\ncpu: 2468.2460096859477 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 132.31357958256896,
            "unit": "ns/iter",
            "extra": "iterations: 5355658\ncpu: 132.3112919084825 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 592.7102308864778,
            "unit": "ns/iter",
            "extra": "iterations: 1188636\ncpu: 592.697129314608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 456.55738632136405,
            "unit": "ns/iter",
            "extra": "iterations: 1531114\ncpu: 456.55712964547297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1270.5081702689877,
            "unit": "ns/iter",
            "extra": "iterations: 552185\ncpu: 1270.4557258889697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 201.92798042247443,
            "unit": "ns/iter",
            "extra": "iterations: 3416571\ncpu: 201.92789407859559 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 765.3364313625099,
            "unit": "ns/iter",
            "extra": "iterations: 917465\ncpu: 765.3155455521431 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1900.9828154174338,
            "unit": "ns/iter",
            "extra": "iterations: 384007\ncpu: 1900.9422171991716 ns\nthreads: 1"
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
        "date": 1729195768913,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5323986226.000045,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5323438283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 971.4845561079401,
            "unit": "ns/iter",
            "extra": "iterations: 719702\ncpu: 971.4528916134736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1579.7818899552367,
            "unit": "ns/iter",
            "extra": "iterations: 444074\ncpu: 1579.734080355976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 182.39994249150078,
            "unit": "ns/iter",
            "extra": "iterations: 3849866\ncpu: 182.39696602427216 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 128.6042121212366,
            "unit": "ns/iter",
            "extra": "iterations: 5421164\ncpu: 128.5984921319481 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3542.6553320772223,
            "unit": "ns/iter",
            "extra": "iterations: 198478\ncpu: 3542.5965043984725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.126339756112678,
            "unit": "ns/iter",
            "extra": "iterations: 23772517\ncpu: 29.12416043282248 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1794.8141747305197,
            "unit": "ns/iter",
            "extra": "iterations: 392078\ncpu: 1794.7795719219132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1492.9644251859966,
            "unit": "ns/iter",
            "extra": "iterations: 465020\ncpu: 1492.9170422777522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1867.982890850692,
            "unit": "ns/iter",
            "extra": "iterations: 374478\ncpu: 1867.9493054331629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 476.2840263631875,
            "unit": "ns/iter",
            "extra": "iterations: 1475694\ncpu: 476.2666711391383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2464.1954229862336,
            "unit": "ns/iter",
            "extra": "iterations: 285033\ncpu: 2464.0908807050464 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 130.7826949982183,
            "unit": "ns/iter",
            "extra": "iterations: 5362831\ncpu: 130.7796171462422 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 588.6369346416967,
            "unit": "ns/iter",
            "extra": "iterations: 1189290\ncpu: 588.6337949532905 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 466.9342918122981,
            "unit": "ns/iter",
            "extra": "iterations: 1501198\ncpu: 466.9151757463027 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1227.9339994786692,
            "unit": "ns/iter",
            "extra": "iterations: 567844\ncpu: 1227.9081666795787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 205.76822562816238,
            "unit": "ns/iter",
            "extra": "iterations: 3394931\ncpu: 205.76094388958055 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 796.4612249313353,
            "unit": "ns/iter",
            "extra": "iterations: 887413\ncpu: 796.440970551479 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1895.6047070918214,
            "unit": "ns/iter",
            "extra": "iterations: 375476\ncpu: 1895.5159717265599 ns\nthreads: 1"
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
        "date": 1729196702489,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5247561737.000012,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5247294273 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 970.0855519139162,
            "unit": "ns/iter",
            "extra": "iterations: 723736\ncpu: 970.0466648059506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1591.6970965498244,
            "unit": "ns/iter",
            "extra": "iterations: 446951\ncpu: 1591.6377835601666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 178.22126551700586,
            "unit": "ns/iter",
            "extra": "iterations: 3970804\ncpu: 178.20935760113036 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 129.3620465811068,
            "unit": "ns/iter",
            "extra": "iterations: 5256122\ncpu: 129.35747610120157 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3854.155922739273,
            "unit": "ns/iter",
            "extra": "iterations: 184104\ncpu: 3853.9720484074246 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.72884863035896,
            "unit": "ns/iter",
            "extra": "iterations: 21390967\ncpu: 29.727989295668575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1769.5252834018484,
            "unit": "ns/iter",
            "extra": "iterations: 396169\ncpu: 1769.4998069005903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1493.5355146851523,
            "unit": "ns/iter",
            "extra": "iterations: 482392\ncpu: 1493.4797674919996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1855.026087071606,
            "unit": "ns/iter",
            "extra": "iterations: 377505\ncpu: 1854.971168593796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 477.6698349379473,
            "unit": "ns/iter",
            "extra": "iterations: 1465994\ncpu: 477.658879231429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2451.721396167615,
            "unit": "ns/iter",
            "extra": "iterations: 287444\ncpu: 2451.6463137167643 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 129.7768950151476,
            "unit": "ns/iter",
            "extra": "iterations: 5400722\ncpu: 129.7730012764958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 596.5218250183808,
            "unit": "ns/iter",
            "extra": "iterations: 1174432\ncpu: 596.5133162243524 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 471.7053402222104,
            "unit": "ns/iter",
            "extra": "iterations: 1480650\ncpu: 471.6758383142542 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1239.2545747455697,
            "unit": "ns/iter",
            "extra": "iterations: 562381\ncpu: 1239.217016577728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 207.87623941582777,
            "unit": "ns/iter",
            "extra": "iterations: 3367413\ncpu: 207.87008483960844 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 785.1695698108786,
            "unit": "ns/iter",
            "extra": "iterations: 893514\ncpu: 785.1437034002823 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 2078.606950525649,
            "unit": "ns/iter",
            "extra": "iterations: 341672\ncpu: 2078.5069189163864 ns\nthreads: 1"
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
        "date": 1729196906815,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5254078958.9999695,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5253909183 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 974.5491256968032,
            "unit": "ns/iter",
            "extra": "iterations: 720631\ncpu: 974.5428908831288 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1593.7058784577089,
            "unit": "ns/iter",
            "extra": "iterations: 437938\ncpu: 1593.7124638647485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 178.64975762193384,
            "unit": "ns/iter",
            "extra": "iterations: 3909801\ncpu: 178.6505346435788 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.76768068129921,
            "unit": "ns/iter",
            "extra": "iterations: 5500085\ncpu: 127.767702317328 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3553.8874885899236,
            "unit": "ns/iter",
            "extra": "iterations: 198291\ncpu: 3553.908745227978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.347177048916855,
            "unit": "ns/iter",
            "extra": "iterations: 22211065\ncpu: 30.346717863371186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1795.9805373349125,
            "unit": "ns/iter",
            "extra": "iterations: 394242\ncpu: 1795.9240999183257 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1486.5778753243562,
            "unit": "ns/iter",
            "extra": "iterations: 474303\ncpu: 1486.57992886404 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1872.2366024169614,
            "unit": "ns/iter",
            "extra": "iterations: 376915\ncpu: 1872.2345091068282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 473.17206551324745,
            "unit": "ns/iter",
            "extra": "iterations: 1479884\ncpu: 473.1799046411747 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2446.6575535806287,
            "unit": "ns/iter",
            "extra": "iterations: 286950\ncpu: 2446.668262763544 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 131.13499995808752,
            "unit": "ns/iter",
            "extra": "iterations: 5368935\ncpu: 131.1373400870008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 582.4520729099278,
            "unit": "ns/iter",
            "extra": "iterations: 1200824\ncpu: 582.4486660826211 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 467.5303233377018,
            "unit": "ns/iter",
            "extra": "iterations: 1498186\ncpu: 467.5333002711302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1254.7294304230797,
            "unit": "ns/iter",
            "extra": "iterations: 583872\ncpu: 1254.7395730571056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 206.66870492995858,
            "unit": "ns/iter",
            "extra": "iterations: 3396519\ncpu: 206.66046855618936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 785.8547797032254,
            "unit": "ns/iter",
            "extra": "iterations: 889187\ncpu: 785.8547313444756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1859.1108209093939,
            "unit": "ns/iter",
            "extra": "iterations: 375218\ncpu: 1859.0133575681332 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}