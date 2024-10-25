window.BENCHMARK_DATA = {
  "lastUpdate": 1729870973420,
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
        "date": 1729197586998,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5204187308.999963,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5203852544 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1000.2831765650477,
            "unit": "ns/iter",
            "extra": "iterations: 697420\ncpu: 1000.2207980843687 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1653.0256061973728,
            "unit": "ns/iter",
            "extra": "iterations: 436574\ncpu: 1652.9658019029996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.34290462317045,
            "unit": "ns/iter",
            "extra": "iterations: 3779010\ncpu: 185.33385013535263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 129.50204395781705,
            "unit": "ns/iter",
            "extra": "iterations: 4127776\ncpu: 129.50099327095293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3636.155014818914,
            "unit": "ns/iter",
            "extra": "iterations: 192659\ncpu: 3635.93940589332 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.135282101195582,
            "unit": "ns/iter",
            "extra": "iterations: 23301390\ncpu: 30.133241278739195 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1829.6381388248446,
            "unit": "ns/iter",
            "extra": "iterations: 382597\ncpu: 1829.539651382523 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1525.2270115255276,
            "unit": "ns/iter",
            "extra": "iterations: 458893\ncpu: 1525.2164970919116 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1914.9048677355643,
            "unit": "ns/iter",
            "extra": "iterations: 364913\ncpu: 1914.7889962813042 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.10284412283335,
            "unit": "ns/iter",
            "extra": "iterations: 1458411\ncpu: 480.0892553607993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2462.001727279005,
            "unit": "ns/iter",
            "extra": "iterations: 285420\ncpu: 2461.89457641371 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 134.2475017450298,
            "unit": "ns/iter",
            "extra": "iterations: 5297898\ncpu: 134.24230100315222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 599.7932500538101,
            "unit": "ns/iter",
            "extra": "iterations: 943889\ncpu: 599.7801235102854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 500.2326808239393,
            "unit": "ns/iter",
            "extra": "iterations: 1393441\ncpu: 500.20677445259537 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1261.8172085789197,
            "unit": "ns/iter",
            "extra": "iterations: 555502\ncpu: 1261.7937847208466 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 211.65830055464926,
            "unit": "ns/iter",
            "extra": "iterations: 3313128\ncpu: 211.6465823234122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 837.4360792610654,
            "unit": "ns/iter",
            "extra": "iterations: 844147\ncpu: 837.3992219364627 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1903.7027600736285,
            "unit": "ns/iter",
            "extra": "iterations: 374048\ncpu: 1903.6049357301702 ns\nthreads: 1"
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
        "date": 1729204800573,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5220890472.000008,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5219830665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 979.9387599191882,
            "unit": "ns/iter",
            "extra": "iterations: 713389\ncpu: 979.9293527093917 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1592.8087111466543,
            "unit": "ns/iter",
            "extra": "iterations: 445039\ncpu: 1592.7493837618722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.25706747108833,
            "unit": "ns/iter",
            "extra": "iterations: 3824883\ncpu: 185.25488335198767 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 126.86346576368405,
            "unit": "ns/iter",
            "extra": "iterations: 5547268\ncpu: 126.85360451306835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3663.249670218994,
            "unit": "ns/iter",
            "extra": "iterations: 191036\ncpu: 3663.131090475093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.326607118112687,
            "unit": "ns/iter",
            "extra": "iterations: 22796971\ncpu: 30.32442288056605 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1808.6651069912466,
            "unit": "ns/iter",
            "extra": "iterations: 389611\ncpu: 1808.6004604592786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1606.8515073039312,
            "unit": "ns/iter",
            "extra": "iterations: 468784\ncpu: 1606.6194665346948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1869.4235587568405,
            "unit": "ns/iter",
            "extra": "iterations: 374850\ncpu: 1869.3348085900998 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 482.9676153600923,
            "unit": "ns/iter",
            "extra": "iterations: 1462854\ncpu: 482.92961020033545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2454.721293684993,
            "unit": "ns/iter",
            "extra": "iterations: 284737\ncpu: 2454.550511524669 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 129.17029063857265,
            "unit": "ns/iter",
            "extra": "iterations: 5447522\ncpu: 129.15445297880387 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 605.8347862482046,
            "unit": "ns/iter",
            "extra": "iterations: 1154002\ncpu: 605.8070783239527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 477.66797822458926,
            "unit": "ns/iter",
            "extra": "iterations: 1462383\ncpu: 477.6320259466892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1238.109560045972,
            "unit": "ns/iter",
            "extra": "iterations: 565991\ncpu: 1238.0254933382346 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 205.72582251099973,
            "unit": "ns/iter",
            "extra": "iterations: 3398678\ncpu: 205.71050655578415 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 833.3674283082034,
            "unit": "ns/iter",
            "extra": "iterations: 861779\ncpu: 833.31943340462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1980.6664698300922,
            "unit": "ns/iter",
            "extra": "iterations: 352238\ncpu: 1980.5331139740683 ns\nthreads: 1"
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
        "date": 1729207663206,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5395002528.00002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5394448756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 992.0725470939483,
            "unit": "ns/iter",
            "extra": "iterations: 706672\ncpu: 991.9959797473239 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1602.8361657860091,
            "unit": "ns/iter",
            "extra": "iterations: 442667\ncpu: 1602.6839543042531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 181.27390548700026,
            "unit": "ns/iter",
            "extra": "iterations: 3863088\ncpu: 181.26434474182307 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 123.67466327033628,
            "unit": "ns/iter",
            "extra": "iterations: 5624096\ncpu: 123.67188877999257 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3615.101460351026,
            "unit": "ns/iter",
            "extra": "iterations: 192351\ncpu: 3614.964777932012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.09391372700909,
            "unit": "ns/iter",
            "extra": "iterations: 23980275\ncpu: 29.09283016979581 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1824.5336342413173,
            "unit": "ns/iter",
            "extra": "iterations: 385500\ncpu: 1824.4673359273677 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1504.6377714862062,
            "unit": "ns/iter",
            "extra": "iterations: 468348\ncpu: 1504.588099020385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1900.5583438131084,
            "unit": "ns/iter",
            "extra": "iterations: 367374\ncpu: 1900.4977597761388 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.18719100347914,
            "unit": "ns/iter",
            "extra": "iterations: 1449450\ncpu: 480.18031943150856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2481.295170390242,
            "unit": "ns/iter",
            "extra": "iterations: 282176\ncpu: 2481.216113347696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 127.8256356548029,
            "unit": "ns/iter",
            "extra": "iterations: 5494059\ncpu: 127.82265807484009 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 610.6236011241544,
            "unit": "ns/iter",
            "extra": "iterations: 1147886\ncpu: 610.5985637946625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 486.1816789382562,
            "unit": "ns/iter",
            "extra": "iterations: 1431762\ncpu: 486.1611671492883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1250.0114667434136,
            "unit": "ns/iter",
            "extra": "iterations: 556130\ncpu: 1249.9670059158848 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 203.3943095822543,
            "unit": "ns/iter",
            "extra": "iterations: 3447058\ncpu: 203.38185867484736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 812.1560923839709,
            "unit": "ns/iter",
            "extra": "iterations: 860279\ncpu: 812.1292871266189 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1837.2544869112994,
            "unit": "ns/iter",
            "extra": "iterations: 377654\ncpu: 1837.148299766453 ns\nthreads: 1"
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
        "date": 1729208678315,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5272553952.999999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5272064421 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 989.6605215731505,
            "unit": "ns/iter",
            "extra": "iterations: 699691\ncpu: 989.608655820926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1583.3070737394762,
            "unit": "ns/iter",
            "extra": "iterations: 440347\ncpu: 1583.1968106970194 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 184.97976942285297,
            "unit": "ns/iter",
            "extra": "iterations: 3794652\ncpu: 184.7250873070837 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 126.70201472066582,
            "unit": "ns/iter",
            "extra": "iterations: 5556949\ncpu: 126.69778290209267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3635.5602733703176,
            "unit": "ns/iter",
            "extra": "iterations: 191096\ncpu: 3635.5640254113105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.723122060287615,
            "unit": "ns/iter",
            "extra": "iterations: 23541211\ncpu: 29.722109835386117 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1825.826624799752,
            "unit": "ns/iter",
            "extra": "iterations: 379616\ncpu: 1825.829909698218 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1511.2908227406513,
            "unit": "ns/iter",
            "extra": "iterations: 465335\ncpu: 1511.2158165622618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1904.0134815882232,
            "unit": "ns/iter",
            "extra": "iterations: 367835\ncpu: 1904.0165237130798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 484.2812688066386,
            "unit": "ns/iter",
            "extra": "iterations: 1455604\ncpu: 484.25293623815315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2492.0805657860656,
            "unit": "ns/iter",
            "extra": "iterations: 282651\ncpu: 2491.9991544342706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 128.80654240833425,
            "unit": "ns/iter",
            "extra": "iterations: 5425525\ncpu: 128.79847609217575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 606.6487409687999,
            "unit": "ns/iter",
            "extra": "iterations: 1156961\ncpu: 606.6253356854706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 476.17119877941235,
            "unit": "ns/iter",
            "extra": "iterations: 1451126\ncpu: 476.1452161976273 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1228.921337355338,
            "unit": "ns/iter",
            "extra": "iterations: 575165\ncpu: 1228.8992271782881 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 205.00415407721275,
            "unit": "ns/iter",
            "extra": "iterations: 3411588\ncpu: 205.00102913950954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 811.7193476599457,
            "unit": "ns/iter",
            "extra": "iterations: 860962\ncpu: 811.6816758463176 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1859.025335277144,
            "unit": "ns/iter",
            "extra": "iterations: 378642\ncpu: 1858.9820754168834 ns\nthreads: 1"
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
        "date": 1729211481273,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5179486359.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5179266725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 982.3258307445554,
            "unit": "ns/iter",
            "extra": "iterations: 721040\ncpu: 982.320557805392 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1597.9808189133319,
            "unit": "ns/iter",
            "extra": "iterations: 445908\ncpu: 1597.9843106649796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 186.54135988662475,
            "unit": "ns/iter",
            "extra": "iterations: 3902090\ncpu: 186.5402494560607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 126.58027126866212,
            "unit": "ns/iter",
            "extra": "iterations: 5538937\ncpu: 126.57934527870624 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3503.8785091111044,
            "unit": "ns/iter",
            "extra": "iterations: 197949\ncpu: 3503.8311686343422 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.432603257942986,
            "unit": "ns/iter",
            "extra": "iterations: 23080767\ncpu: 30.432701088313063 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1798.814877936416,
            "unit": "ns/iter",
            "extra": "iterations: 390780\ncpu: 1798.778990736474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1492.720401718383,
            "unit": "ns/iter",
            "extra": "iterations: 469284\ncpu: 1492.6969617545028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1870.2550663030156,
            "unit": "ns/iter",
            "extra": "iterations: 374040\ncpu: 1870.20906854882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.19031147795926,
            "unit": "ns/iter",
            "extra": "iterations: 1459397\ncpu: 480.1921307224836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2486.917917978171,
            "unit": "ns/iter",
            "extra": "iterations: 282437\ncpu: 2486.8650035229107 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 129.37608016393497,
            "unit": "ns/iter",
            "extra": "iterations: 5422788\ncpu: 129.37669147309475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 595.9474008245629,
            "unit": "ns/iter",
            "extra": "iterations: 1177585\ncpu: 595.9243324261105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 461.8712709798596,
            "unit": "ns/iter",
            "extra": "iterations: 1516216\ncpu: 461.8671633856909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1224.1396320165084,
            "unit": "ns/iter",
            "extra": "iterations: 582037\ncpu: 1224.105752727058 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 205.00466901988193,
            "unit": "ns/iter",
            "extra": "iterations: 3428771\ncpu: 205.00526165206108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 825.3072076622352,
            "unit": "ns/iter",
            "extra": "iterations: 849471\ncpu: 825.288390068642 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1880.6063831240558,
            "unit": "ns/iter",
            "extra": "iterations: 365965\ncpu: 1880.4640498408367 ns\nthreads: 1"
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
        "date": 1729211886251,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5288315447.999991,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5287975041.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 966.8095313301111,
            "unit": "ns/iter",
            "extra": "iterations: 721830\ncpu: 966.7903536843859 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1574.3923644443325,
            "unit": "ns/iter",
            "extra": "iterations: 443766\ncpu: 1574.3579701914978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 180.64796337222472,
            "unit": "ns/iter",
            "extra": "iterations: 3717616\ncpu: 180.64151246390185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 126.51389677507034,
            "unit": "ns/iter",
            "extra": "iterations: 5537112\ncpu: 126.50867997613207 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3527.044492202975,
            "unit": "ns/iter",
            "extra": "iterations: 200080\ncpu: 3526.9021091563363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.64827824245737,
            "unit": "ns/iter",
            "extra": "iterations: 22859200\ncpu: 30.646732869041724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1772.8338634727436,
            "unit": "ns/iter",
            "extra": "iterations: 386062\ncpu: 1772.7125617128888 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1477.5035705761848,
            "unit": "ns/iter",
            "extra": "iterations: 473453\ncpu: 1477.4444348224658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1860.2057462158596,
            "unit": "ns/iter",
            "extra": "iterations: 377431\ncpu: 1860.1301456425142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.2318875178268,
            "unit": "ns/iter",
            "extra": "iterations: 1453528\ncpu: 480.2119161103186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2499.2795094461826,
            "unit": "ns/iter",
            "extra": "iterations: 282130\ncpu: 2499.180140360834 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 130.5787281183355,
            "unit": "ns/iter",
            "extra": "iterations: 5408868\ncpu: 130.57657147484431 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 597.0772431063607,
            "unit": "ns/iter",
            "extra": "iterations: 1175613\ncpu: 597.0314133987961 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 462.5876195136178,
            "unit": "ns/iter",
            "extra": "iterations: 1512380\ncpu: 462.5675451936694 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1242.0459821577945,
            "unit": "ns/iter",
            "extra": "iterations: 567307\ncpu: 1241.9794308901494 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 205.7387864876116,
            "unit": "ns/iter",
            "extra": "iterations: 3400674\ncpu: 205.7326465283057 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 814.215877210141,
            "unit": "ns/iter",
            "extra": "iterations: 858312\ncpu: 814.1400819282509 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1864.1819174874374,
            "unit": "ns/iter",
            "extra": "iterations: 382657\ncpu: 1864.1080863541006 ns\nthreads: 1"
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
        "date": 1729267067804,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5253446066.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5253137927 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 974.4618878192264,
            "unit": "ns/iter",
            "extra": "iterations: 716700\ncpu: 974.4191795730433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1602.4230001901535,
            "unit": "ns/iter",
            "extra": "iterations: 436579\ncpu: 1602.323787905509 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 183.41660210394014,
            "unit": "ns/iter",
            "extra": "iterations: 3848970\ncpu: 183.41080133126522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 128.42001833264104,
            "unit": "ns/iter",
            "extra": "iterations: 5464571\ncpu: 128.4150236130156 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3574.6363855876743,
            "unit": "ns/iter",
            "extra": "iterations: 190504\ncpu: 3574.422206357874 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.077418443178946,
            "unit": "ns/iter",
            "extra": "iterations: 23317945\ncpu: 30.07719839805782 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1821.9142914682247,
            "unit": "ns/iter",
            "extra": "iterations: 382354\ncpu: 1821.860563770749 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1516.09053788634,
            "unit": "ns/iter",
            "extra": "iterations: 464336\ncpu: 1516.021966851591 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1922.483032423545,
            "unit": "ns/iter",
            "extra": "iterations: 363841\ncpu: 1922.3300672546532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.1277965572587,
            "unit": "ns/iter",
            "extra": "iterations: 1460814\ncpu: 480.1138906116717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2440.8800640607533,
            "unit": "ns/iter",
            "extra": "iterations: 286603\ncpu: 2440.736461237323 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 130.49743452230518,
            "unit": "ns/iter",
            "extra": "iterations: 5370150\ncpu: 130.39745407484006 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 604.3484144892027,
            "unit": "ns/iter",
            "extra": "iterations: 1161140\ncpu: 604.2801987701749 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 467.0201218177973,
            "unit": "ns/iter",
            "extra": "iterations: 1503393\ncpu: 466.99808499840054 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1241.322551218696,
            "unit": "ns/iter",
            "extra": "iterations: 561269\ncpu: 1241.24754796719 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 202.90618393242391,
            "unit": "ns/iter",
            "extra": "iterations: 3454323\ncpu: 202.90480884387483 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 816.4721176840939,
            "unit": "ns/iter",
            "extra": "iterations: 842595\ncpu: 816.4572683198919 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1843.4334190731668,
            "unit": "ns/iter",
            "extra": "iterations: 379831\ncpu: 1843.3307418299198 ns\nthreads: 1"
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
        "date": 1729274236325,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5208147355.999984,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5207916878 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1014.2595103327128,
            "unit": "ns/iter",
            "extra": "iterations: 690959\ncpu: 1014.2238598817003 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1583.4516289799103,
            "unit": "ns/iter",
            "extra": "iterations: 443437\ncpu: 1583.4293484756563 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 184.73031712274218,
            "unit": "ns/iter",
            "extra": "iterations: 3772924\ncpu: 184.72619856641688 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 131.74189152875545,
            "unit": "ns/iter",
            "extra": "iterations: 5258297\ncpu: 131.740283403543 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3642.541672245123,
            "unit": "ns/iter",
            "extra": "iterations: 194206\ncpu: 3642.4681317775994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.03613437610071,
            "unit": "ns/iter",
            "extra": "iterations: 23290481\ncpu: 30.035525243123978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1788.1129305648283,
            "unit": "ns/iter",
            "extra": "iterations: 392914\ncpu: 1788.0645993779797 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1487.2632134152598,
            "unit": "ns/iter",
            "extra": "iterations: 467347\ncpu: 1487.2227894904665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1881.4475761774456,
            "unit": "ns/iter",
            "extra": "iterations: 374553\ncpu: 1881.3608354491912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 467.9011882864398,
            "unit": "ns/iter",
            "extra": "iterations: 1498881\ncpu: 467.88517700871466 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2374.336163830967,
            "unit": "ns/iter",
            "extra": "iterations: 292057\ncpu: 2374.2896112745166 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 135.48128655229675,
            "unit": "ns/iter",
            "extra": "iterations: 5188969\ncpu: 135.4779951470128 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 574.9211691893732,
            "unit": "ns/iter",
            "extra": "iterations: 1217151\ncpu: 574.9065448740562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 493.7643490784832,
            "unit": "ns/iter",
            "extra": "iterations: 1421938\ncpu: 493.7544196723063 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1236.5990960765016,
            "unit": "ns/iter",
            "extra": "iterations: 563322\ncpu: 1236.5537649869832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 214.20039212198824,
            "unit": "ns/iter",
            "extra": "iterations: 3271431\ncpu: 214.19566544426561 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 829.6338731212107,
            "unit": "ns/iter",
            "extra": "iterations: 842615\ncpu: 829.615402051944 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1897.888637112441,
            "unit": "ns/iter",
            "extra": "iterations: 370258\ncpu: 1897.8396064365936 ns\nthreads: 1"
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
        "date": 1729278350578,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5354298738.000011,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5354038167 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1023.5501950642102,
            "unit": "ns/iter",
            "extra": "iterations: 684390\ncpu: 1023.5418796300356 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1581.3496036722138,
            "unit": "ns/iter",
            "extra": "iterations: 444203\ncpu: 1581.2570986688527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.96885216565698,
            "unit": "ns/iter",
            "extra": "iterations: 3828035\ncpu: 185.96803451379108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 130.157321668937,
            "unit": "ns/iter",
            "extra": "iterations: 5384592\ncpu: 130.1548661439903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3604.3284829482404,
            "unit": "ns/iter",
            "extra": "iterations: 194555\ncpu: 3604.359363676081 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.147796628856153,
            "unit": "ns/iter",
            "extra": "iterations: 24054209\ncpu: 29.147530978881914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1773.3573707040355,
            "unit": "ns/iter",
            "extra": "iterations: 393748\ncpu: 1773.3721364933933 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1480.6041543866531,
            "unit": "ns/iter",
            "extra": "iterations: 466543\ncpu: 1480.573295494732 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1873.5156501936397,
            "unit": "ns/iter",
            "extra": "iterations: 378941\ncpu: 1873.4626261080214 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 465.69833279923745,
            "unit": "ns/iter",
            "extra": "iterations: 1504078\ncpu: 465.69294278621163 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2403.3091908987944,
            "unit": "ns/iter",
            "extra": "iterations: 295303\ncpu: 2403.26164989857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 133.90642050108278,
            "unit": "ns/iter",
            "extra": "iterations: 5250883\ncpu: 133.9007502166778 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 577.3976062702202,
            "unit": "ns/iter",
            "extra": "iterations: 1214757\ncpu: 577.3831449417431 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 489.0151532910701,
            "unit": "ns/iter",
            "extra": "iterations: 1424773\ncpu: 489.00610974520316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1233.5352930325832,
            "unit": "ns/iter",
            "extra": "iterations: 563794\ncpu: 1233.5098457947424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 211.6700573535966,
            "unit": "ns/iter",
            "extra": "iterations: 3291860\ncpu: 211.66832823996094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 837.4780336882789,
            "unit": "ns/iter",
            "extra": "iterations: 835188\ncpu: 837.4651695187183 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1896.3885885788864,
            "unit": "ns/iter",
            "extra": "iterations: 368508\ncpu: 1896.3348801111508 ns\nthreads: 1"
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
        "date": 1729279928285,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5319901292.999987,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5319678675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1018.3732006382087,
            "unit": "ns/iter",
            "extra": "iterations: 691912\ncpu: 1018.3218126004463 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1595.9438253426406,
            "unit": "ns/iter",
            "extra": "iterations: 443474\ncpu: 1595.8817427853733 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.00454122282665,
            "unit": "ns/iter",
            "extra": "iterations: 3791710\ncpu: 185.0020465700171 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 131.9314598921709,
            "unit": "ns/iter",
            "extra": "iterations: 5310584\ncpu: 131.9278439056797 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3601.2805036685304,
            "unit": "ns/iter",
            "extra": "iterations: 194493\ncpu: 3601.287681304725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.53423642571941,
            "unit": "ns/iter",
            "extra": "iterations: 23061797\ncpu: 30.53283861617544 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1782.6040369336556,
            "unit": "ns/iter",
            "extra": "iterations: 395845\ncpu: 1782.5804822594673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1490.9371896249718,
            "unit": "ns/iter",
            "extra": "iterations: 476641\ncpu: 1490.8473819918956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1865.1326968085446,
            "unit": "ns/iter",
            "extra": "iterations: 376000\ncpu: 1865.0347074468084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 467.25566277909223,
            "unit": "ns/iter",
            "extra": "iterations: 1500500\ncpu: 467.24710429856657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2397.7188832105194,
            "unit": "ns/iter",
            "extra": "iterations: 294881\ncpu: 2397.724315910482 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 135.1077186647631,
            "unit": "ns/iter",
            "extra": "iterations: 5193761\ncpu: 135.10223400730212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 577.8300571386545,
            "unit": "ns/iter",
            "extra": "iterations: 1217215\ncpu: 577.7909637985057 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 491.03116313456593,
            "unit": "ns/iter",
            "extra": "iterations: 1420300\ncpu: 490.9877004858131 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1228.894317643542,
            "unit": "ns/iter",
            "extra": "iterations: 561598\ncpu: 1228.8388277736035 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 213.59493374389163,
            "unit": "ns/iter",
            "extra": "iterations: 3278792\ncpu: 213.57879578820408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 839.9619806308275,
            "unit": "ns/iter",
            "extra": "iterations: 834522\ncpu: 839.9110245146301 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1896.4981683380524,
            "unit": "ns/iter",
            "extra": "iterations: 366061\ncpu: 1896.333561892695 ns\nthreads: 1"
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
        "date": 1729280510435,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5173816086.000045,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5173565865 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 999.9900038062427,
            "unit": "ns/iter",
            "extra": "iterations: 701467\ncpu: 999.9753687628919 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1668.328779275222,
            "unit": "ns/iter",
            "extra": "iterations: 444146\ncpu: 1668.2626591256017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 184.11988045553696,
            "unit": "ns/iter",
            "extra": "iterations: 3779682\ncpu: 184.11587667957255 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 130.1951618094017,
            "unit": "ns/iter",
            "extra": "iterations: 5394124\ncpu: 130.18596272536553 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3600.680215925328,
            "unit": "ns/iter",
            "extra": "iterations: 194697\ncpu: 3600.6134968695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.130873709100676,
            "unit": "ns/iter",
            "extra": "iterations: 23308845\ncpu: 30.12945347570844 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1776.2501784811075,
            "unit": "ns/iter",
            "extra": "iterations: 393599\ncpu: 1776.2125284871133 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1484.9819408084074,
            "unit": "ns/iter",
            "extra": "iterations: 473277\ncpu: 1484.863842950322 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1851.1773943859237,
            "unit": "ns/iter",
            "extra": "iterations: 375305\ncpu: 1851.0683790517064 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 465.9462010140926,
            "unit": "ns/iter",
            "extra": "iterations: 1486831\ncpu: 465.9171217172634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2342.056188973924,
            "unit": "ns/iter",
            "extra": "iterations: 299258\ncpu: 2341.9470824505993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 133.970788707202,
            "unit": "ns/iter",
            "extra": "iterations: 5242630\ncpu: 133.96050531889543 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 574.1291916876686,
            "unit": "ns/iter",
            "extra": "iterations: 1211982\ncpu: 574.1100008085941 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 489.6767930952431,
            "unit": "ns/iter",
            "extra": "iterations: 1421857\ncpu: 489.6451513759841 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1250.417507951068,
            "unit": "ns/iter",
            "extra": "iterations: 555896\ncpu: 1250.3411231597265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 211.42479668590647,
            "unit": "ns/iter",
            "extra": "iterations: 3307321\ncpu: 211.41621874623038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 813.9989554292997,
            "unit": "ns/iter",
            "extra": "iterations: 858726\ncpu: 813.9642284034724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1886.7768039004247,
            "unit": "ns/iter",
            "extra": "iterations: 369200\ncpu: 1886.7674052004386 ns\nthreads: 1"
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
        "date": 1729281534695,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5128398649.000019,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5128259312.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 949.1510013385533,
            "unit": "ns/iter",
            "extra": "iterations: 738861\ncpu: 949.1380164875405 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1556.765196249466,
            "unit": "ns/iter",
            "extra": "iterations: 444205\ncpu: 1556.7333460902066 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 186.79394782698898,
            "unit": "ns/iter",
            "extra": "iterations: 3748604\ncpu: 186.78820382200936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.45333604616762,
            "unit": "ns/iter",
            "extra": "iterations: 5494873\ncpu: 127.45104682128216 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3516.3035793327344,
            "unit": "ns/iter",
            "extra": "iterations: 198808\ncpu: 3516.1755714055735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.277519179204955,
            "unit": "ns/iter",
            "extra": "iterations: 23823067\ncpu: 29.276592094544302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1766.6979327859272,
            "unit": "ns/iter",
            "extra": "iterations: 396137\ncpu: 1766.6291030628274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1454.6954911837881,
            "unit": "ns/iter",
            "extra": "iterations: 480991\ncpu: 1454.633880883427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1873.8425443279796,
            "unit": "ns/iter",
            "extra": "iterations: 378316\ncpu: 1873.7775774749111 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 481.1998490392075,
            "unit": "ns/iter",
            "extra": "iterations: 1465281\ncpu: 481.1857213735789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2361.492381089652,
            "unit": "ns/iter",
            "extra": "iterations: 298271\ncpu: 2361.409888993568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 130.9816509330031,
            "unit": "ns/iter",
            "extra": "iterations: 5341307\ncpu: 130.97818736125876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 595.8349753778299,
            "unit": "ns/iter",
            "extra": "iterations: 1177394\ncpu: 595.8107056771165 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 353.89343995226403,
            "unit": "ns/iter",
            "extra": "iterations: 1970382\ncpu: 353.88485938259583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1242.0741248156905,
            "unit": "ns/iter",
            "extra": "iterations: 564224\ncpu: 1242.0246551015152 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 206.26966554164426,
            "unit": "ns/iter",
            "extra": "iterations: 3284654\ncpu: 206.26019909555114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 826.5118380496019,
            "unit": "ns/iter",
            "extra": "iterations: 839961\ncpu: 826.4924276246164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1850.704880165596,
            "unit": "ns/iter",
            "extra": "iterations: 367549\ncpu: 1850.68168325856 ns\nthreads: 1"
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
        "date": 1729286633407,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5204466901.000046,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5203989792 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1200.051887606695,
            "unit": "ns/iter",
            "extra": "iterations: 590854\ncpu: 1199.943703520667 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1979.0247477913838,
            "unit": "ns/iter",
            "extra": "iterations: 350900\ncpu: 1978.8125277856936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 219.59260851230044,
            "unit": "ns/iter",
            "extra": "iterations: 3194269\ncpu: 219.58718974513422 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 142.8879009854421,
            "unit": "ns/iter",
            "extra": "iterations: 4898027\ncpu: 142.88303576113415 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3623.7813854271085,
            "unit": "ns/iter",
            "extra": "iterations: 193139\ncpu: 3623.676310843489 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 31.26720446422198,
            "unit": "ns/iter",
            "extra": "iterations: 22379177\ncpu: 31.2617041279042 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1928.407995734803,
            "unit": "ns/iter",
            "extra": "iterations: 363869\ncpu: 1927.884801947953 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1605.6586036310048,
            "unit": "ns/iter",
            "extra": "iterations: 435816\ncpu: 1605.5811948161643 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 2012.249502802338,
            "unit": "ns/iter",
            "extra": "iterations: 348453\ncpu: 2012.1383429042098 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 479.433440938508,
            "unit": "ns/iter",
            "extra": "iterations: 1455940\ncpu: 479.4084090003706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2453.653987408113,
            "unit": "ns/iter",
            "extra": "iterations: 285900\ncpu: 2453.5300209863567 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 148.74492025792242,
            "unit": "ns/iter",
            "extra": "iterations: 4804427\ncpu: 148.74016818238672 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 597.1507737350505,
            "unit": "ns/iter",
            "extra": "iterations: 1173593\ncpu: 597.1228160017992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 583.5964678253573,
            "unit": "ns/iter",
            "extra": "iterations: 1195694\ncpu: 583.5805532184661 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1209.7045216972128,
            "unit": "ns/iter",
            "extra": "iterations: 567287\ncpu: 1209.5119419271011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 281.59235820660547,
            "unit": "ns/iter",
            "extra": "iterations: 2487034\ncpu: 281.5677735004828 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 860.7962031918171,
            "unit": "ns/iter",
            "extra": "iterations: 814895\ncpu: 860.760134741287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1868.0201116897504,
            "unit": "ns/iter",
            "extra": "iterations: 371923\ncpu: 1867.9269821979249 ns\nthreads: 1"
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
        "date": 1729360049302,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5292492609.999954,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5292244835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1001.3791601906897,
            "unit": "ns/iter",
            "extra": "iterations: 697444\ncpu: 1001.3549976772327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1629.332254654376,
            "unit": "ns/iter",
            "extra": "iterations: 433246\ncpu: 1629.2177538857834 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 187.02626632247666,
            "unit": "ns/iter",
            "extra": "iterations: 3751039\ncpu: 187.02659529799587 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 131.72143652232307,
            "unit": "ns/iter",
            "extra": "iterations: 5322855\ncpu: 131.62050666418685 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3677.228944576994,
            "unit": "ns/iter",
            "extra": "iterations: 190426\ncpu: 3677.2395733775825 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.43009021001706,
            "unit": "ns/iter",
            "extra": "iterations: 23799907\ncpu: 29.42695061791634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1810.1270016478213,
            "unit": "ns/iter",
            "extra": "iterations: 375066\ncpu: 1810.0903121050674 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1484.6217252860026,
            "unit": "ns/iter",
            "extra": "iterations: 468247\ncpu: 1484.580287754114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1892.8510388626469,
            "unit": "ns/iter",
            "extra": "iterations: 368143\ncpu: 1892.8444870607348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 466.03140439190906,
            "unit": "ns/iter",
            "extra": "iterations: 1501860\ncpu: 465.9998142303549 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2456.9848677441414,
            "unit": "ns/iter",
            "extra": "iterations: 288721\ncpu: 2456.945507947119 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 134.93147022021577,
            "unit": "ns/iter",
            "extra": "iterations: 5185264\ncpu: 134.92917159087773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 578.706050196749,
            "unit": "ns/iter",
            "extra": "iterations: 1211911\ncpu: 578.6954231787645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 366.66702916305155,
            "unit": "ns/iter",
            "extra": "iterations: 1897950\ncpu: 366.6602987433817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1226.9611271541414,
            "unit": "ns/iter",
            "extra": "iterations: 568263\ncpu: 1226.9282673691607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 209.74374168428648,
            "unit": "ns/iter",
            "extra": "iterations: 3318265\ncpu: 209.74422506942616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 834.1333120055904,
            "unit": "ns/iter",
            "extra": "iterations: 837719\ncpu: 834.0642960228936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1931.1799228073676,
            "unit": "ns/iter",
            "extra": "iterations: 365579\ncpu: 1931.1250673588968 ns\nthreads: 1"
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
        "date": 1729361282567,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5183186113.999966,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5182987831 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 956.3492202686243,
            "unit": "ns/iter",
            "extra": "iterations: 726404\ncpu: 956.3085665827831 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1551.555637561372,
            "unit": "ns/iter",
            "extra": "iterations: 456607\ncpu: 1551.4273609471604 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 181.1510005474373,
            "unit": "ns/iter",
            "extra": "iterations: 3865284\ncpu: 181.1377303711705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 132.92163589321723,
            "unit": "ns/iter",
            "extra": "iterations: 5272618\ncpu: 132.91627214412264 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3592.7709451623177,
            "unit": "ns/iter",
            "extra": "iterations: 194866\ncpu: 3592.6556608130695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 31.0108439049399,
            "unit": "ns/iter",
            "extra": "iterations: 22584392\ncpu: 31.00846345564671 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1798.6425424233487,
            "unit": "ns/iter",
            "extra": "iterations: 392413\ncpu: 1798.5578077178907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1480.69934265189,
            "unit": "ns/iter",
            "extra": "iterations: 475395\ncpu: 1480.6380252211302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1872.9074170374452,
            "unit": "ns/iter",
            "extra": "iterations: 373060\ncpu: 1872.8799281616912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 473.62793750695886,
            "unit": "ns/iter",
            "extra": "iterations: 1480805\ncpu: 473.5980037884799 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2394.990500135926,
            "unit": "ns/iter",
            "extra": "iterations: 294320\ncpu: 2394.8559527045377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 138.74588651732728,
            "unit": "ns/iter",
            "extra": "iterations: 5025243\ncpu: 138.74095043762023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 589.7944852807514,
            "unit": "ns/iter",
            "extra": "iterations: 1185083\ncpu: 589.7643186173444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 361.926697809995,
            "unit": "ns/iter",
            "extra": "iterations: 1935140\ncpu: 361.921454778466 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1212.3424450959678,
            "unit": "ns/iter",
            "extra": "iterations: 569630\ncpu: 1212.2837210118878 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 240.8976214293644,
            "unit": "ns/iter",
            "extra": "iterations: 2892031\ncpu: 240.88363160699157 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 841.2717401868906,
            "unit": "ns/iter",
            "extra": "iterations: 833399\ncpu: 841.2101778379871 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1921.7610858472458,
            "unit": "ns/iter",
            "extra": "iterations: 367676\ncpu: 1921.6345124511824 ns\nthreads: 1"
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
        "date": 1729362413030,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5225001818.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5224615060.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 982.8053013824426,
            "unit": "ns/iter",
            "extra": "iterations: 730036\ncpu: 982.7289613114973 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1543.105391384567,
            "unit": "ns/iter",
            "extra": "iterations: 450682\ncpu: 1542.9968580950629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.20073367192012,
            "unit": "ns/iter",
            "extra": "iterations: 3591251\ncpu: 185.1857564397474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 134.28133542158375,
            "unit": "ns/iter",
            "extra": "iterations: 5206895\ncpu: 134.28047060676272 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3591.689883151978,
            "unit": "ns/iter",
            "extra": "iterations: 193756\ncpu: 3591.5415677450032 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.376704925402834,
            "unit": "ns/iter",
            "extra": "iterations: 22368574\ncpu: 30.374667021688552 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1805.6774121118715,
            "unit": "ns/iter",
            "extra": "iterations: 383015\ncpu: 1805.6283357048658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1487.4156020393089,
            "unit": "ns/iter",
            "extra": "iterations: 473092\ncpu: 1487.3652355144463 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1898.1170598330534,
            "unit": "ns/iter",
            "extra": "iterations: 359517\ncpu: 1898.0834230370174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 467.1875214793822,
            "unit": "ns/iter",
            "extra": "iterations: 1481073\ncpu: 467.1561232970967 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2362.4592103695973,
            "unit": "ns/iter",
            "extra": "iterations: 293935\ncpu: 2362.440138125776 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 139.5034592008799,
            "unit": "ns/iter",
            "extra": "iterations: 5038736\ncpu: 139.50005934027857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 590.5747966798099,
            "unit": "ns/iter",
            "extra": "iterations: 1192700\ncpu: 590.5450448562091 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 360.00561670028895,
            "unit": "ns/iter",
            "extra": "iterations: 1952926\ncpu: 359.99754317367854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1248.0269402617917,
            "unit": "ns/iter",
            "extra": "iterations: 561316\ncpu: 1247.9473950502017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 243.4363739504819,
            "unit": "ns/iter",
            "extra": "iterations: 2903347\ncpu: 243.42354151949465 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 818.2469952190444,
            "unit": "ns/iter",
            "extra": "iterations: 855470\ncpu: 818.2072556606324 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1877.53737103398,
            "unit": "ns/iter",
            "extra": "iterations: 373645\ncpu: 1877.422280506899 ns\nthreads: 1"
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
        "date": 1729363531038,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5189349552.0000105,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5189128395.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 988.1643380495042,
            "unit": "ns/iter",
            "extra": "iterations: 712440\ncpu: 988.154696535848 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1594.2586941608415,
            "unit": "ns/iter",
            "extra": "iterations: 447513\ncpu: 1594.1623841095113 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 182.7166109047802,
            "unit": "ns/iter",
            "extra": "iterations: 3887362\ncpu: 182.70607908396485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 130.50806345647638,
            "unit": "ns/iter",
            "extra": "iterations: 5373006\ncpu: 130.50225683723403 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3579.546461167926,
            "unit": "ns/iter",
            "extra": "iterations: 194259\ncpu: 3579.381732635294 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.440031917282234,
            "unit": "ns/iter",
            "extra": "iterations: 23567170\ncpu: 29.439028954261314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1772.8729183217893,
            "unit": "ns/iter",
            "extra": "iterations: 395234\ncpu: 1772.8356846829986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1471.0223055652639,
            "unit": "ns/iter",
            "extra": "iterations: 477011\ncpu: 1470.9611245862263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1890.6942477876735,
            "unit": "ns/iter",
            "extra": "iterations: 366120\ncpu: 1890.600103791109 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 465.8314589397698,
            "unit": "ns/iter",
            "extra": "iterations: 1502975\ncpu: 465.8222092849191 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2354.792290493429,
            "unit": "ns/iter",
            "extra": "iterations: 297425\ncpu: 2354.722232495581 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 132.14077476650567,
            "unit": "ns/iter",
            "extra": "iterations: 5252447\ncpu: 132.13679319372497 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 571.2558494790935,
            "unit": "ns/iter",
            "extra": "iterations: 1225451\ncpu: 571.2167193955519 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 361.8142106878093,
            "unit": "ns/iter",
            "extra": "iterations: 1935698\ncpu: 361.80065795387486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1206.6367373566611,
            "unit": "ns/iter",
            "extra": "iterations: 528835\ncpu: 1206.6018663666384 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 245.1248860588926,
            "unit": "ns/iter",
            "extra": "iterations: 2876486\ncpu: 245.12261001791828 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 839.428882335519,
            "unit": "ns/iter",
            "extra": "iterations: 839939\ncpu: 839.4198019141874 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1623.9194438262866,
            "unit": "ns/iter",
            "extra": "iterations: 431376\ncpu: 1623.902345053963 ns\nthreads: 1"
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
        "date": 1729363556514,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5253378931.000043,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5253199754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 965.1675919653047,
            "unit": "ns/iter",
            "extra": "iterations: 729134\ncpu: 965.1485817421765 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1596.1551708235834,
            "unit": "ns/iter",
            "extra": "iterations: 444523\ncpu: 1596.0375031213225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 181.044186533109,
            "unit": "ns/iter",
            "extra": "iterations: 3871270\ncpu: 181.04304065590864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 131.2384254534243,
            "unit": "ns/iter",
            "extra": "iterations: 5325241\ncpu: 131.23539216347208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3602.976746684831,
            "unit": "ns/iter",
            "extra": "iterations: 195456\ncpu: 3602.967041175514 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.638039060193556,
            "unit": "ns/iter",
            "extra": "iterations: 23066348\ncpu: 29.6361493375544 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1785.4274493528087,
            "unit": "ns/iter",
            "extra": "iterations: 390348\ncpu: 1785.3224507362668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1496.1721408876192,
            "unit": "ns/iter",
            "extra": "iterations: 477998\ncpu: 1496.0925673329157 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1887.7584599666754,
            "unit": "ns/iter",
            "extra": "iterations: 370953\ncpu: 1887.626122446782 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 469.10217365081854,
            "unit": "ns/iter",
            "extra": "iterations: 1550341\ncpu: 469.0753698702417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2394.221299719957,
            "unit": "ns/iter",
            "extra": "iterations: 294248\ncpu: 2394.098750033986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 132.7503063725488,
            "unit": "ns/iter",
            "extra": "iterations: 5271360\ncpu: 132.74664583712692 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 577.7555165190903,
            "unit": "ns/iter",
            "extra": "iterations: 1198310\ncpu: 577.7468768515671 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 361.43208738609917,
            "unit": "ns/iter",
            "extra": "iterations: 1935502\ncpu: 361.43088356405764 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1243.0687343246298,
            "unit": "ns/iter",
            "extra": "iterations: 568566\ncpu: 1243.0015970001718 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 243.2986167269071,
            "unit": "ns/iter",
            "extra": "iterations: 2884969\ncpu: 243.29766455029548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 845.4453900148524,
            "unit": "ns/iter",
            "extra": "iterations: 835122\ncpu: 845.3945315774231 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1635.5502606957666,
            "unit": "ns/iter",
            "extra": "iterations: 428277\ncpu: 1635.5256317757014 ns\nthreads: 1"
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
        "date": 1729366473344,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5306807200.000037,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5305106143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 985.3599686978208,
            "unit": "ns/iter",
            "extra": "iterations: 688771\ncpu: 985.3300458352626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1598.461434576894,
            "unit": "ns/iter",
            "extra": "iterations: 433173\ncpu: 1598.4030652880037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 182.38937747421448,
            "unit": "ns/iter",
            "extra": "iterations: 3801224\ncpu: 182.37797509433832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 130.22940911081696,
            "unit": "ns/iter",
            "extra": "iterations: 5392737\ncpu: 130.2216412556367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3642.0902622107637,
            "unit": "ns/iter",
            "extra": "iterations: 194500\ncpu: 3641.889501285343 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.10730215867488,
            "unit": "ns/iter",
            "extra": "iterations: 24056804\ncpu: 29.106800304811898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1778.0359019619086,
            "unit": "ns/iter",
            "extra": "iterations: 395438\ncpu: 1777.9886505596287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1461.5604029366498,
            "unit": "ns/iter",
            "extra": "iterations: 479182\ncpu: 1461.5233293404167 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1847.4623348746538,
            "unit": "ns/iter",
            "extra": "iterations: 377365\ncpu: 1847.4035615385596 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 466.18213711740515,
            "unit": "ns/iter",
            "extra": "iterations: 1503296\ncpu: 466.1735486557525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2485.794413174007,
            "unit": "ns/iter",
            "extra": "iterations: 281949\ncpu: 2485.6209669124564 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 132.7551350330548,
            "unit": "ns/iter",
            "extra": "iterations: 5263452\ncpu: 132.74561789487205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 575.4325340373656,
            "unit": "ns/iter",
            "extra": "iterations: 1219615\ncpu: 575.3679046256403 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 366.7842185140043,
            "unit": "ns/iter",
            "extra": "iterations: 1908857\ncpu: 366.7583726806151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1293.4746379231324,
            "unit": "ns/iter",
            "extra": "iterations: 569078\ncpu: 1293.378041322985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 239.3335935484334,
            "unit": "ns/iter",
            "extra": "iterations: 2864297\ncpu: 239.3218035699519 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 832.9421086617358,
            "unit": "ns/iter",
            "extra": "iterations: 840903\ncpu: 832.934005467934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1640.7381533436796,
            "unit": "ns/iter",
            "extra": "iterations: 426154\ncpu: 1640.7053834998621 ns\nthreads: 1"
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
        "date": 1729368113612,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5227329664.000024,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5226820880 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 903.7158117796158,
            "unit": "ns/iter",
            "extra": "iterations: 780532\ncpu: 903.6298434913623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1581.392740701609,
            "unit": "ns/iter",
            "extra": "iterations: 439216\ncpu: 1581.2857705548063 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.7254132070596,
            "unit": "ns/iter",
            "extra": "iterations: 3765243\ncpu: 185.71893155368718 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 129.55656589445437,
            "unit": "ns/iter",
            "extra": "iterations: 5405227\ncpu: 129.55229798859526 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3593.97273159486,
            "unit": "ns/iter",
            "extra": "iterations: 195611\ncpu: 3593.8140288634095 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.730672611260612,
            "unit": "ns/iter",
            "extra": "iterations: 23543183\ncpu: 29.729494478295486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1722.9747199519027,
            "unit": "ns/iter",
            "extra": "iterations: 406091\ncpu: 1722.8943660411064 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1432.6892286519535,
            "unit": "ns/iter",
            "extra": "iterations: 482493\ncpu: 1432.6641588582631 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1807.5872996628889,
            "unit": "ns/iter",
            "extra": "iterations: 387659\ncpu: 1807.4394687083218 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 484.2939523255613,
            "unit": "ns/iter",
            "extra": "iterations: 1449582\ncpu: 484.28520704589306 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2379.6014194122326,
            "unit": "ns/iter",
            "extra": "iterations: 296038\ncpu: 2379.4815158864694 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 131.85840773411758,
            "unit": "ns/iter",
            "extra": "iterations: 5314012\ncpu: 131.8547061993839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 572.9811330516736,
            "unit": "ns/iter",
            "extra": "iterations: 1198339\ncpu: 572.9327410690969 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 357.83354544052446,
            "unit": "ns/iter",
            "extra": "iterations: 1956558\ncpu: 357.79535490386667 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1215.4179862947863,
            "unit": "ns/iter",
            "extra": "iterations: 550597\ncpu: 1215.300292228253 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 235.15509985248144,
            "unit": "ns/iter",
            "extra": "iterations: 2978694\ncpu: 235.13636647470318 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 833.0913666464756,
            "unit": "ns/iter",
            "extra": "iterations: 813612\ncpu: 833.0385638363236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1627.3384272211338,
            "unit": "ns/iter",
            "extra": "iterations: 426786\ncpu: 1627.2126522425717 ns\nthreads: 1"
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
        "date": 1729368756312,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5228561008.999918,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5228041033 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 957.6902430286915,
            "unit": "ns/iter",
            "extra": "iterations: 728597\ncpu: 957.5819760443701 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1580.6775133064305,
            "unit": "ns/iter",
            "extra": "iterations: 441888\ncpu: 1580.5682548519087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 182.677283894075,
            "unit": "ns/iter",
            "extra": "iterations: 3829939\ncpu: 182.66623463193542 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 130.90724107053393,
            "unit": "ns/iter",
            "extra": "iterations: 5282230\ncpu: 130.89803946439275 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3637.36126032505,
            "unit": "ns/iter",
            "extra": "iterations: 192490\ncpu: 3637.0976622162198 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.641489239320457,
            "unit": "ns/iter",
            "extra": "iterations: 22748419\ncpu: 30.639314582696908 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1743.749581584576,
            "unit": "ns/iter",
            "extra": "iterations: 402710\ncpu: 1743.6129025849855 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1449.4600228740408,
            "unit": "ns/iter",
            "extra": "iterations: 488767\ncpu: 1449.2663518609063 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1831.7792218409488,
            "unit": "ns/iter",
            "extra": "iterations: 379177\ncpu: 1831.629154721939 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 506.5853924594456,
            "unit": "ns/iter",
            "extra": "iterations: 1382423\ncpu: 506.5559644189946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2498.1622912879093,
            "unit": "ns/iter",
            "extra": "iterations: 282147\ncpu: 2498.1192711600756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 132.52310312774708,
            "unit": "ns/iter",
            "extra": "iterations: 5284436\ncpu: 132.517585036511 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 575.4692872834943,
            "unit": "ns/iter",
            "extra": "iterations: 1216711\ncpu: 575.453763465607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 381.66652392870463,
            "unit": "ns/iter",
            "extra": "iterations: 1842537\ncpu: 381.6519299205377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1232.2301878367202,
            "unit": "ns/iter",
            "extra": "iterations: 568792\ncpu: 1232.19210713231 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 256.5431292096495,
            "unit": "ns/iter",
            "extra": "iterations: 2710889\ncpu: 256.53211031510233 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 894.7022649413046,
            "unit": "ns/iter",
            "extra": "iterations: 781124\ncpu: 894.6616363087048 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1686.2510700533587,
            "unit": "ns/iter",
            "extra": "iterations: 419138\ncpu: 1686.163096641203 ns\nthreads: 1"
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
        "date": 1729369157330,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5227045077.999947,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5226787752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 920.6533698009662,
            "unit": "ns/iter",
            "extra": "iterations: 762686\ncpu: 920.6328003922986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1587.4884867604687,
            "unit": "ns/iter",
            "extra": "iterations: 443750\ncpu: 1587.4414512676042 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 180.81277718434256,
            "unit": "ns/iter",
            "extra": "iterations: 3876707\ncpu: 180.80887283975827 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 129.39796591938247,
            "unit": "ns/iter",
            "extra": "iterations: 5347674\ncpu: 129.3968476762044 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3610.3590960371853,
            "unit": "ns/iter",
            "extra": "iterations: 193238\ncpu: 3610.2526987445467 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.63567414113252,
            "unit": "ns/iter",
            "extra": "iterations: 23276580\ncpu: 29.634778519868416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1721.4583956349788,
            "unit": "ns/iter",
            "extra": "iterations: 405955\ncpu: 1721.4008202879636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1417.6238739671562,
            "unit": "ns/iter",
            "extra": "iterations: 459245\ncpu: 1417.5664950081105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1803.325944810224,
            "unit": "ns/iter",
            "extra": "iterations: 390290\ncpu: 1803.285538958213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 517.756828969447,
            "unit": "ns/iter",
            "extra": "iterations: 1391535\ncpu: 517.746965760833 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2468.7729927984183,
            "unit": "ns/iter",
            "extra": "iterations: 283828\ncpu: 2468.6662908522094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 131.20513329818823,
            "unit": "ns/iter",
            "extra": "iterations: 5336569\ncpu: 131.20393252668578 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 576.5161714779471,
            "unit": "ns/iter",
            "extra": "iterations: 1218256\ncpu: 576.4983238334152 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 371.7140772297443,
            "unit": "ns/iter",
            "extra": "iterations: 1872698\ncpu: 371.70574540048665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1222.3302212661952,
            "unit": "ns/iter",
            "extra": "iterations: 570896\ncpu: 1222.2857298001704 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 246.10042601719,
            "unit": "ns/iter",
            "extra": "iterations: 2846364\ncpu: 246.0897369415851 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 832.9816404143937,
            "unit": "ns/iter",
            "extra": "iterations: 851163\ncpu: 832.9462923082913 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1638.6342272337524,
            "unit": "ns/iter",
            "extra": "iterations: 429056\ncpu: 1638.542439681535 ns\nthreads: 1"
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
        "date": 1729369855788,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5211429083.999974,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5211288650 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 899.0542917137984,
            "unit": "ns/iter",
            "extra": "iterations: 773875\ncpu: 899.0556356000653 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1584.2812528309723,
            "unit": "ns/iter",
            "extra": "iterations: 441560\ncpu: 1584.270481927712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.5866723090452,
            "unit": "ns/iter",
            "extra": "iterations: 3776183\ncpu: 185.5851745002821 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 128.9814786062638,
            "unit": "ns/iter",
            "extra": "iterations: 5435984\ncpu: 128.97998154519942 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3732.6186345682036,
            "unit": "ns/iter",
            "extra": "iterations: 187340\ncpu: 3732.5568485107383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.45269789068757,
            "unit": "ns/iter",
            "extra": "iterations: 23065853\ncpu: 30.452020699169445 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1739.582368026758,
            "unit": "ns/iter",
            "extra": "iterations: 405139\ncpu: 1739.584421642941 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1440.4009198659608,
            "unit": "ns/iter",
            "extra": "iterations: 488332\ncpu: 1440.3604760695605 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1809.1638469446561,
            "unit": "ns/iter",
            "extra": "iterations: 387154\ncpu: 1809.1554988454204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 479.3596961221551,
            "unit": "ns/iter",
            "extra": "iterations: 1462693\ncpu: 479.35688418554037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2391.527677341834,
            "unit": "ns/iter",
            "extra": "iterations: 294826\ncpu: 2391.5307130307397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 130.24862127079453,
            "unit": "ns/iter",
            "extra": "iterations: 5028725\ncpu: 130.2466577512195 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 598.0333435269157,
            "unit": "ns/iter",
            "extra": "iterations: 1144510\ncpu: 598.0339009707214 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 371.0619712228319,
            "unit": "ns/iter",
            "extra": "iterations: 1917632\ncpu: 371.0624760120804 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1256.0785041583183,
            "unit": "ns/iter",
            "extra": "iterations: 555754\ncpu: 1256.0685932984693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 237.88466884293427,
            "unit": "ns/iter",
            "extra": "iterations: 2949099\ncpu: 237.87768976219485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 804.2638207771402,
            "unit": "ns/iter",
            "extra": "iterations: 868059\ncpu: 804.2597035454969 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1658.303956449569,
            "unit": "ns/iter",
            "extra": "iterations: 420478\ncpu: 1658.305840020167 ns\nthreads: 1"
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
        "date": 1729372242205,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5138505482.000028,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5138246428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 894.1434393451557,
            "unit": "ns/iter",
            "extra": "iterations: 757714\ncpu: 894.1234185985742 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1558.6735457896084,
            "unit": "ns/iter",
            "extra": "iterations: 446084\ncpu: 1558.610564378011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 182.98271790010153,
            "unit": "ns/iter",
            "extra": "iterations: 3799654\ncpu: 182.9772279265428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.61894443423918,
            "unit": "ns/iter",
            "extra": "iterations: 5499610\ncpu: 127.61196303010603 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3753.565730244192,
            "unit": "ns/iter",
            "extra": "iterations: 187273\ncpu: 3753.4404105236677 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.945340275748624,
            "unit": "ns/iter",
            "extra": "iterations: 22603462\ncpu: 30.944550662194978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1729.9861151330688,
            "unit": "ns/iter",
            "extra": "iterations: 407494\ncpu: 1729.949155079584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1429.4752353117526,
            "unit": "ns/iter",
            "extra": "iterations: 487226\ncpu: 1429.375269382174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1808.3215873203305,
            "unit": "ns/iter",
            "extra": "iterations: 388529\ncpu: 1808.2942869129463 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.4676303151992,
            "unit": "ns/iter",
            "extra": "iterations: 1459730\ncpu: 480.46219574852853 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2389.5212800140785,
            "unit": "ns/iter",
            "extra": "iterations: 292528\ncpu: 2389.423197095657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 130.51568193387428,
            "unit": "ns/iter",
            "extra": "iterations: 5402650\ncpu: 130.51538134063847 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 600.233776945045,
            "unit": "ns/iter",
            "extra": "iterations: 1168815\ncpu: 600.1999212877994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 360.9892928619256,
            "unit": "ns/iter",
            "extra": "iterations: 1940201\ncpu: 360.96994228948427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1254.949511353847,
            "unit": "ns/iter",
            "extra": "iterations: 556026\ncpu: 1254.8257221784565 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 233.98742922023897,
            "unit": "ns/iter",
            "extra": "iterations: 2992734\ncpu: 233.97720779728422 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 798.4998256980645,
            "unit": "ns/iter",
            "extra": "iterations: 872050\ncpu: 798.44751791755 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1673.8258846951578,
            "unit": "ns/iter",
            "extra": "iterations: 417884\ncpu: 1673.7937800920902 ns\nthreads: 1"
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
        "date": 1729373124530,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5177240717.000018,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5176850903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 862.5964099297546,
            "unit": "ns/iter",
            "extra": "iterations: 817867\ncpu: 862.5446582390534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1414.9229541557202,
            "unit": "ns/iter",
            "extra": "iterations: 494368\ncpu: 1414.854076315619 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 148.6999074136882,
            "unit": "ns/iter",
            "extra": "iterations: 4745842\ncpu: 148.68713159856577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 107.17189131460322,
            "unit": "ns/iter",
            "extra": "iterations: 6541302\ncpu: 107.16585153842485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3446.691324031076,
            "unit": "ns/iter",
            "extra": "iterations: 204104\ncpu: 3446.5122094618428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.462671791934476,
            "unit": "ns/iter",
            "extra": "iterations: 22847842\ncpu: 29.46172491914121 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1670.9779663437166,
            "unit": "ns/iter",
            "extra": "iterations: 420130\ncpu: 1670.9520791183695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1380.2495927280918,
            "unit": "ns/iter",
            "extra": "iterations: 508260\ncpu: 1380.2077932554175 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1752.3556814446806,
            "unit": "ns/iter",
            "extra": "iterations: 398587\ncpu: 1752.3129780951217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 464.52040247281764,
            "unit": "ns/iter",
            "extra": "iterations: 1506288\ncpu: 464.5092147052891 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2398.5556482213633,
            "unit": "ns/iter",
            "extra": "iterations: 290171\ncpu: 2398.5181393040666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 108.95230410908364,
            "unit": "ns/iter",
            "extra": "iterations: 6128117\ncpu: 108.94735821786686 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 579.4842604653453,
            "unit": "ns/iter",
            "extra": "iterations: 1199146\ncpu: 579.4711286198701 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 284.726811997353,
            "unit": "ns/iter",
            "extra": "iterations: 2415732\ncpu: 284.7168725669899 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1197.4957244623029,
            "unit": "ns/iter",
            "extra": "iterations: 588464\ncpu: 1197.482012493541 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 169.21565361675178,
            "unit": "ns/iter",
            "extra": "iterations: 4140385\ncpu: 169.21237807595162 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 801.5366756216371,
            "unit": "ns/iter",
            "extra": "iterations: 874750\ncpu: 801.5094335524461 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1473.200840142767,
            "unit": "ns/iter",
            "extra": "iterations: 473491\ncpu: 1473.1448559740354 ns\nthreads: 1"
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
        "date": 1729375758007,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5227880411.000001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5227732409.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 874.8438119242126,
            "unit": "ns/iter",
            "extra": "iterations: 805420\ncpu: 874.8298055672819 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1424.3537605075758,
            "unit": "ns/iter",
            "extra": "iterations: 495239\ncpu: 1424.3057614606269 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 147.5762465107523,
            "unit": "ns/iter",
            "extra": "iterations: 4521020\ncpu: 147.56347041154444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 107.05672800548496,
            "unit": "ns/iter",
            "extra": "iterations: 6546643\ncpu: 107.05177111383658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3509.5808189976556,
            "unit": "ns/iter",
            "extra": "iterations: 200782\ncpu: 3509.299135380657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.393906644323156,
            "unit": "ns/iter",
            "extra": "iterations: 21389101\ncpu: 29.39259920274348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1664.598569867729,
            "unit": "ns/iter",
            "extra": "iterations: 421919\ncpu: 1664.4877286872613 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1371.8572272586598,
            "unit": "ns/iter",
            "extra": "iterations: 511162\ncpu: 1371.777835598107 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1756.6757283256538,
            "unit": "ns/iter",
            "extra": "iterations: 398860\ncpu: 1756.5477561049026 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 464.88562552668026,
            "unit": "ns/iter",
            "extra": "iterations: 1505843\ncpu: 464.86002259199654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2395.2000934793264,
            "unit": "ns/iter",
            "extra": "iterations: 293113\ncpu: 2395.0348602757263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 107.73001522700787,
            "unit": "ns/iter",
            "extra": "iterations: 6502263\ncpu: 107.7239604119365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 584.3911075982694,
            "unit": "ns/iter",
            "extra": "iterations: 1207008\ncpu: 584.3610166626906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 287.83853442996696,
            "unit": "ns/iter",
            "extra": "iterations: 2437659\ncpu: 287.8236816552276 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1191.2397615014945,
            "unit": "ns/iter",
            "extra": "iterations: 589857\ncpu: 1191.232569927969 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 167.33372504451492,
            "unit": "ns/iter",
            "extra": "iterations: 4193566\ncpu: 167.32657766683562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 802.4250126327681,
            "unit": "ns/iter",
            "extra": "iterations: 878668\ncpu: 802.3795802282539 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1481.517881956723,
            "unit": "ns/iter",
            "extra": "iterations: 468489\ncpu: 1481.4246460429108 ns\nthreads: 1"
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
        "date": 1729378107625,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5305335044.999992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5304936167 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 800.056221902802,
            "unit": "ns/iter",
            "extra": "iterations: 873752\ncpu: 800.0258345617518 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1452.2885371132654,
            "unit": "ns/iter",
            "extra": "iterations: 480420\ncpu: 1452.2768848091268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 148.89680052216664,
            "unit": "ns/iter",
            "extra": "iterations: 4703580\ncpu: 148.89652243610192 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 107.83175099960808,
            "unit": "ns/iter",
            "extra": "iterations: 6492520\ncpu: 107.83055254354262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3336.842913131862,
            "unit": "ns/iter",
            "extra": "iterations: 210756\ncpu: 3336.6177570270766 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.626700335458047,
            "unit": "ns/iter",
            "extra": "iterations: 22848065\ncpu: 30.624940624074735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1726.0260657258214,
            "unit": "ns/iter",
            "extra": "iterations: 409580\ncpu: 1725.935900190442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1402.6895810208073,
            "unit": "ns/iter",
            "extra": "iterations: 501767\ncpu: 1402.6021898610325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1801.3022436416913,
            "unit": "ns/iter",
            "extra": "iterations: 389679\ncpu: 1801.1587255151014 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 469.1319752128776,
            "unit": "ns/iter",
            "extra": "iterations: 1493682\ncpu: 469.11099551310133 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2318.03617003019,
            "unit": "ns/iter",
            "extra": "iterations: 302958\ncpu: 2317.959628067259 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 109.52318915084287,
            "unit": "ns/iter",
            "extra": "iterations: 6405517\ncpu: 109.51382363047345 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 597.4214584479538,
            "unit": "ns/iter",
            "extra": "iterations: 1172685\ncpu: 597.3966751514687 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 281.07105248564466,
            "unit": "ns/iter",
            "extra": "iterations: 2488794\ncpu: 281.0591185931826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1204.6354240255985,
            "unit": "ns/iter",
            "extra": "iterations: 559129\ncpu: 1204.648351274928 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 166.05182515758912,
            "unit": "ns/iter",
            "extra": "iterations: 4204541\ncpu: 166.04992673397658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 831.34259807071,
            "unit": "ns/iter",
            "extra": "iterations: 840031\ncpu: 831.323307116046 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1437.2386429990943,
            "unit": "ns/iter",
            "extra": "iterations: 484657\ncpu: 1437.223347645859 ns\nthreads: 1"
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
        "date": 1729378749366,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5171164351.000016,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5170887882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 861.4876935769399,
            "unit": "ns/iter",
            "extra": "iterations: 801167\ncpu: 861.4781000715203 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1422.9531170427153,
            "unit": "ns/iter",
            "extra": "iterations: 488941\ncpu: 1422.92623854412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 148.10604523764246,
            "unit": "ns/iter",
            "extra": "iterations: 4729293\ncpu: 148.1023489134635 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 107.42412872498524,
            "unit": "ns/iter",
            "extra": "iterations: 6517460\ncpu: 107.41793336667959 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3463.9828144887792,
            "unit": "ns/iter",
            "extra": "iterations: 204300\ncpu: 3463.8416984826194 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.96275546168522,
            "unit": "ns/iter",
            "extra": "iterations: 22616014\ncpu: 30.961543179094225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1723.768877522228,
            "unit": "ns/iter",
            "extra": "iterations: 407429\ncpu: 1723.7021763301104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1413.6184700778952,
            "unit": "ns/iter",
            "extra": "iterations: 495450\ncpu: 1413.5235381976004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1799.3353256088828,
            "unit": "ns/iter",
            "extra": "iterations: 389839\ncpu: 1799.2626007146525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 463.0056757333186,
            "unit": "ns/iter",
            "extra": "iterations: 1513637\ncpu: 462.9893541185897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2421.004441302399,
            "unit": "ns/iter",
            "extra": "iterations: 290005\ncpu: 2420.936235582142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 109.33122096647612,
            "unit": "ns/iter",
            "extra": "iterations: 6399930\ncpu: 109.32313150300054 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 582.4295227193086,
            "unit": "ns/iter",
            "extra": "iterations: 1204679\ncpu: 582.4085262547105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 284.62668929648436,
            "unit": "ns/iter",
            "extra": "iterations: 2455164\ncpu: 284.6146367411717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1173.98512313074,
            "unit": "ns/iter",
            "extra": "iterations: 596967\ncpu: 1173.9742347566973 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 167.82311557450174,
            "unit": "ns/iter",
            "extra": "iterations: 4163046\ncpu: 167.818014261673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 821.0677404374098,
            "unit": "ns/iter",
            "extra": "iterations: 852696\ncpu: 821.0219855610924 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1473.226827349872,
            "unit": "ns/iter",
            "extra": "iterations: 478042\ncpu: 1473.1796724973997 ns\nthreads: 1"
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
        "date": 1729537570293,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5465406156.000029,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5464811224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 791.2591785411281,
            "unit": "ns/iter",
            "extra": "iterations: 888322\ncpu: 791.2144436364288 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1443.7139399806304,
            "unit": "ns/iter",
            "extra": "iterations: 485510\ncpu: 1443.6447920743133 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 147.64366032507075,
            "unit": "ns/iter",
            "extra": "iterations: 4760528\ncpu: 147.63364420921397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 107.35538413272153,
            "unit": "ns/iter",
            "extra": "iterations: 6534200\ncpu: 107.34814560313406 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3501.044788169392,
            "unit": "ns/iter",
            "extra": "iterations: 203134\ncpu: 3500.7879035513515 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.766955987178402,
            "unit": "ns/iter",
            "extra": "iterations: 23557726\ncpu: 29.765024816062443 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1690.1098879759652,
            "unit": "ns/iter",
            "extra": "iterations: 411965\ncpu: 1689.9822679111066 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1405.577464131255,
            "unit": "ns/iter",
            "extra": "iterations: 492699\ncpu: 1405.5420753847677 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1779.6937895189499,
            "unit": "ns/iter",
            "extra": "iterations: 393641\ncpu: 1779.6579777004965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 463.36964702718745,
            "unit": "ns/iter",
            "extra": "iterations: 1511193\ncpu: 463.36390917639204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2362.492490419801,
            "unit": "ns/iter",
            "extra": "iterations: 291228\ncpu: 2362.382336176468 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 109.56232755080563,
            "unit": "ns/iter",
            "extra": "iterations: 6406597\ncpu: 109.55645969303201 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 582.8110420016429,
            "unit": "ns/iter",
            "extra": "iterations: 1208549\ncpu: 582.8108698943952 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 285.5849200292422,
            "unit": "ns/iter",
            "extra": "iterations: 2455522\ncpu: 285.57731390718504 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1195.1265034422483,
            "unit": "ns/iter",
            "extra": "iterations: 583328\ncpu: 1195.126138296126 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 169.63375597639342,
            "unit": "ns/iter",
            "extra": "iterations: 4127281\ncpu: 169.62724539472805 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 808.3071937753597,
            "unit": "ns/iter",
            "extra": "iterations: 866235\ncpu: 808.2841018892093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1478.9631124227271,
            "unit": "ns/iter",
            "extra": "iterations: 467610\ncpu: 1478.8511302153506 ns\nthreads: 1"
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
        "date": 1729623018470,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5401888799.999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5401647974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 914.0420048804573,
            "unit": "ns/iter",
            "extra": "iterations: 801145\ncpu: 914.028330701684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1443.2088747010039,
            "unit": "ns/iter",
            "extra": "iterations: 487115\ncpu: 1443.161366412449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.87841503164154,
            "unit": "ns/iter",
            "extra": "iterations: 4668661\ncpu: 149.87812993918374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 112.38570489862964,
            "unit": "ns/iter",
            "extra": "iterations: 6090436\ncpu: 112.38329390539546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3460.7602332514116,
            "unit": "ns/iter",
            "extra": "iterations: 201671\ncpu: 3460.778971691522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.424016412986887,
            "unit": "ns/iter",
            "extra": "iterations: 23673935\ncpu: 29.42227724288341 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1679.9462546774885,
            "unit": "ns/iter",
            "extra": "iterations: 411273\ncpu: 1679.917599745181 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1398.2585556343497,
            "unit": "ns/iter",
            "extra": "iterations: 500635\ncpu: 1398.2212170543437 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1771.9073166314809,
            "unit": "ns/iter",
            "extra": "iterations: 397601\ncpu: 1771.8740848237294 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 467.0586991422983,
            "unit": "ns/iter",
            "extra": "iterations: 1498642\ncpu: 467.03868635738206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2376.497022585182,
            "unit": "ns/iter",
            "extra": "iterations: 296566\ncpu: 2376.492635703356 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 114.91149355073578,
            "unit": "ns/iter",
            "extra": "iterations: 6096358\ncpu: 114.90572125193425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 600.3335788068761,
            "unit": "ns/iter",
            "extra": "iterations: 1163737\ncpu: 600.3042139246232 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 287.3677942098115,
            "unit": "ns/iter",
            "extra": "iterations: 2436773\ncpu: 287.3393430573952 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1181.3099845115166,
            "unit": "ns/iter",
            "extra": "iterations: 585597\ncpu: 1181.2756332426559 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 173.9834668182666,
            "unit": "ns/iter",
            "extra": "iterations: 4186490\ncpu: 173.98326641171948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 810.957821274401,
            "unit": "ns/iter",
            "extra": "iterations: 868471\ncpu: 810.934559703205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1480.170773192091,
            "unit": "ns/iter",
            "extra": "iterations: 467995\ncpu: 1480.1671000758568 ns\nthreads: 1"
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
          "id": "8ef793e4b5a28f105d1e582291b146f9e96d3194",
          "message": "Remove the `report` flag from instruction steps (#51)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-22T19:05:15Z",
          "url": "https://github.com/sourcemeta/blaze/commit/8ef793e4b5a28f105d1e582291b146f9e96d3194"
        },
        "date": 1729623939695,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5235064053.0000305,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5234804357 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 793.7589714166801,
            "unit": "ns/iter",
            "extra": "iterations: 876701\ncpu: 793.7390524249429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1434.62992423087,
            "unit": "ns/iter",
            "extra": "iterations: 492945\ncpu: 1434.5915690391428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 147.81530355905556,
            "unit": "ns/iter",
            "extra": "iterations: 4746177\ncpu: 147.811743009163 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 107.08523735982826,
            "unit": "ns/iter",
            "extra": "iterations: 6537943\ncpu: 107.07886088942675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3428.901033929827,
            "unit": "ns/iter",
            "extra": "iterations: 203302\ncpu: 3428.796799834728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.70451597004929,
            "unit": "ns/iter",
            "extra": "iterations: 23544731\ncpu: 29.703464184831894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1684.5979597422756,
            "unit": "ns/iter",
            "extra": "iterations: 412889\ncpu: 1684.5896088294937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1392.0357872090801,
            "unit": "ns/iter",
            "extra": "iterations: 501995\ncpu: 1391.9781392244963 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1766.0846350068161,
            "unit": "ns/iter",
            "extra": "iterations: 397117\ncpu: 1766.0423678663979 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 462.4040715084532,
            "unit": "ns/iter",
            "extra": "iterations: 1509416\ncpu: 462.38876558881026 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2383.390616715123,
            "unit": "ns/iter",
            "extra": "iterations: 296101\ncpu: 2383.3555003191523 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 109.19138380977094,
            "unit": "ns/iter",
            "extra": "iterations: 6408865\ncpu: 109.18797166112867 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 581.9033142653133,
            "unit": "ns/iter",
            "extra": "iterations: 1207779\ncpu: 581.8819668167782 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 285.4145907407039,
            "unit": "ns/iter",
            "extra": "iterations: 2423537\ncpu: 285.40212218753015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1174.9464282669567,
            "unit": "ns/iter",
            "extra": "iterations: 586578\ncpu: 1174.8965116318716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 167.76226548710545,
            "unit": "ns/iter",
            "extra": "iterations: 4188256\ncpu: 167.7571254001666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 814.4383398718661,
            "unit": "ns/iter",
            "extra": "iterations: 870222\ncpu: 814.391991928495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1500.8276613398243,
            "unit": "ns/iter",
            "extra": "iterations: 473643\ncpu: 1500.7551890347756 ns\nthreads: 1"
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
        "date": 1729624429246,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5233360478.000009,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5233158127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 780.2563592438754,
            "unit": "ns/iter",
            "extra": "iterations: 870072\ncpu: 780.2510562344268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1452.8807720732082,
            "unit": "ns/iter",
            "extra": "iterations: 481716\ncpu: 1452.8510782286662 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 156.41235164722139,
            "unit": "ns/iter",
            "extra": "iterations: 4636499\ncpu: 156.40818125917832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 111.98946134600124,
            "unit": "ns/iter",
            "extra": "iterations: 6373869\ncpu: 111.98558159886859 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3541.1059720624744,
            "unit": "ns/iter",
            "extra": "iterations: 198156\ncpu: 3541.043758452939 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.361770556808363,
            "unit": "ns/iter",
            "extra": "iterations: 23068743\ncpu: 30.360438407935856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1716.5953218549566,
            "unit": "ns/iter",
            "extra": "iterations: 413882\ncpu: 1716.537571095141 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1392.2726197198783,
            "unit": "ns/iter",
            "extra": "iterations: 502924\ncpu: 1392.1927150026618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1801.1380886253119,
            "unit": "ns/iter",
            "extra": "iterations: 391017\ncpu: 1801.0799121265845 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 470.94396451401104,
            "unit": "ns/iter",
            "extra": "iterations: 1482275\ncpu: 470.93084616552323 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2457.5086810655753,
            "unit": "ns/iter",
            "extra": "iterations: 292706\ncpu: 2457.470513074549 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 111.48718844417637,
            "unit": "ns/iter",
            "extra": "iterations: 6283585\ncpu: 111.48518369688675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 599.4036440983901,
            "unit": "ns/iter",
            "extra": "iterations: 1167806\ncpu: 599.3996811114183 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 292.1701559865002,
            "unit": "ns/iter",
            "extra": "iterations: 2398605\ncpu: 292.1653573639675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1205.7915928344744,
            "unit": "ns/iter",
            "extra": "iterations: 581837\ncpu: 1205.7600771350048 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 173.51686903581364,
            "unit": "ns/iter",
            "extra": "iterations: 4003163\ncpu: 173.51378597374105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 814.7767351982516,
            "unit": "ns/iter",
            "extra": "iterations: 861112\ncpu: 814.7369076264164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1485.727956457773,
            "unit": "ns/iter",
            "extra": "iterations: 463367\ncpu: 1485.6917928985013 ns\nthreads: 1"
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
        "date": 1729627487502,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5183937977.99996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5183854000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 794.0962299702684,
            "unit": "ns/iter",
            "extra": "iterations: 894794\ncpu: 794.0856688802115 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1450.8587909763114,
            "unit": "ns/iter",
            "extra": "iterations: 482108\ncpu: 1450.8405295079099 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 144.56388722342174,
            "unit": "ns/iter",
            "extra": "iterations: 4836820\ncpu: 144.56338813517985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 106.64375198098239,
            "unit": "ns/iter",
            "extra": "iterations: 6575012\ncpu: 106.64425935648477 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3540.2424360145455,
            "unit": "ns/iter",
            "extra": "iterations: 198209\ncpu: 3540.201413659321 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.006028619139418,
            "unit": "ns/iter",
            "extra": "iterations: 24059075\ncpu: 29.004138687792462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1688.5159771081007,
            "unit": "ns/iter",
            "extra": "iterations: 417441\ncpu: 1688.4422541149522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1385.3688340211618,
            "unit": "ns/iter",
            "extra": "iterations: 508131\ncpu: 1385.3331778616143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1769.8101532466965,
            "unit": "ns/iter",
            "extra": "iterations: 398769\ncpu: 1769.7477512043351 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 467.00294570255096,
            "unit": "ns/iter",
            "extra": "iterations: 1499812\ncpu: 466.98107229439336 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2338.6723672936905,
            "unit": "ns/iter",
            "extra": "iterations: 299967\ncpu: 2338.6207316138107 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 109.50184792382599,
            "unit": "ns/iter",
            "extra": "iterations: 6396097\ncpu: 109.50010858184301 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 593.5572389158133,
            "unit": "ns/iter",
            "extra": "iterations: 1178595\ncpu: 593.5318493630106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 289.3343042318766,
            "unit": "ns/iter",
            "extra": "iterations: 2378896\ncpu: 289.3207954446096 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1208.4725581538787,
            "unit": "ns/iter",
            "extra": "iterations: 583452\ncpu: 1208.4268097461347 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 168.40021641461345,
            "unit": "ns/iter",
            "extra": "iterations: 4176243\ncpu: 168.39637683918352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 800.6586750233807,
            "unit": "ns/iter",
            "extra": "iterations: 875623\ncpu: 800.6173958427337 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1482.7030489924614,
            "unit": "ns/iter",
            "extra": "iterations: 468909\ncpu: 1482.6893533713378 ns\nthreads: 1"
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
        "date": 1729627491154,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5176108283.000019,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5175667626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 794.7612923055144,
            "unit": "ns/iter",
            "extra": "iterations: 868711\ncpu: 794.7054751234872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1453.8523545808935,
            "unit": "ns/iter",
            "extra": "iterations: 486456\ncpu: 1453.737641225517 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 146.99523361092193,
            "unit": "ns/iter",
            "extra": "iterations: 4753074\ncpu: 146.9857706822995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 109.29687177845838,
            "unit": "ns/iter",
            "extra": "iterations: 6445867\ncpu: 109.29164594925705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3552.557895217609,
            "unit": "ns/iter",
            "extra": "iterations: 197132\ncpu: 3552.3014528336303 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.91358892067971,
            "unit": "ns/iter",
            "extra": "iterations: 23305692\ncpu: 29.910910304658586 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1663.0772800429895,
            "unit": "ns/iter",
            "extra": "iterations: 420639\ncpu: 1662.9344164473557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1377.9561742829571,
            "unit": "ns/iter",
            "extra": "iterations: 505913\ncpu: 1377.845811433982 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1740.678460642199,
            "unit": "ns/iter",
            "extra": "iterations: 401674\ncpu: 1740.5493410078832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 468.00488872981606,
            "unit": "ns/iter",
            "extra": "iterations: 1497526\ncpu: 467.9781392777163 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2354.4883425250487,
            "unit": "ns/iter",
            "extra": "iterations: 298092\ncpu: 2354.332997866431 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 110.19109115235972,
            "unit": "ns/iter",
            "extra": "iterations: 6353549\ncpu: 110.1861145636872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 590.959647622829,
            "unit": "ns/iter",
            "extra": "iterations: 1186002\ncpu: 590.9338297911795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 292.7094740750581,
            "unit": "ns/iter",
            "extra": "iterations: 2397015\ncpu: 292.705515818633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1198.3355604210567,
            "unit": "ns/iter",
            "extra": "iterations: 585069\ncpu: 1198.263469778779 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 169.2668548645247,
            "unit": "ns/iter",
            "extra": "iterations: 4147408\ncpu: 169.25987556565457 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 796.674022537486,
            "unit": "ns/iter",
            "extra": "iterations: 876760\ncpu: 796.6199758200645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1502.394246621188,
            "unit": "ns/iter",
            "extra": "iterations: 465848\ncpu: 1502.2586444505516 ns\nthreads: 1"
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
        "date": 1729631263117,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5158910112.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5158745479 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 770.6666354522396,
            "unit": "ns/iter",
            "extra": "iterations: 907700\ncpu: 770.6552308031281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1451.8434130225455,
            "unit": "ns/iter",
            "extra": "iterations: 481579\ncpu: 1451.8220416587947 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 149.3561538399336,
            "unit": "ns/iter",
            "extra": "iterations: 4700626\ncpu: 149.35534267138027 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 110.48265964902541,
            "unit": "ns/iter",
            "extra": "iterations: 6325391\ncpu: 110.4820272770491 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3453.7192186420534,
            "unit": "ns/iter",
            "extra": "iterations: 202980\ncpu: 3453.664627056858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.33742280624666,
            "unit": "ns/iter",
            "extra": "iterations: 23068091\ncpu: 30.336499149409494 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1684.3420429667772,
            "unit": "ns/iter",
            "extra": "iterations: 415670\ncpu: 1684.3234103976727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1379.8034081348035,
            "unit": "ns/iter",
            "extra": "iterations: 506318\ncpu: 1379.7955770879164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1756.9979861924744,
            "unit": "ns/iter",
            "extra": "iterations: 397754\ncpu: 1757.0021269427814 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 79.13139611148667,
            "unit": "ns/iter",
            "extra": "iterations: 8858390\ncpu: 79.13162324079204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2340.0427545397706,
            "unit": "ns/iter",
            "extra": "iterations: 301161\ncpu: 2340.0307410322075 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 111.28444752206454,
            "unit": "ns/iter",
            "extra": "iterations: 6162047\ncpu: 111.28380666359774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 102.8541756426057,
            "unit": "ns/iter",
            "extra": "iterations: 6805228\ncpu: 102.85360828468934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 283.9403392213601,
            "unit": "ns/iter",
            "extra": "iterations: 2460930\ncpu: 283.9409958836696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1193.907756799171,
            "unit": "ns/iter",
            "extra": "iterations: 588748\ncpu: 1193.9018068851185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 166.83428299564343,
            "unit": "ns/iter",
            "extra": "iterations: 4197457\ncpu: 166.83328215155004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 783.9857078113951,
            "unit": "ns/iter",
            "extra": "iterations: 893635\ncpu: 783.9886340620053 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1445.2673477071396,
            "unit": "ns/iter",
            "extra": "iterations: 483378\ncpu: 1445.247243358204 ns\nthreads: 1"
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
        "date": 1729632787781,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5266336959,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5266096297.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 780.0062665571778,
            "unit": "ns/iter",
            "extra": "iterations: 903686\ncpu: 779.9621085199948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1441.9667289284855,
            "unit": "ns/iter",
            "extra": "iterations: 482371\ncpu: 1441.9592740857136 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 146.951001106075,
            "unit": "ns/iter",
            "extra": "iterations: 4702249\ncpu: 146.9503973524158 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 108.04969210699443,
            "unit": "ns/iter",
            "extra": "iterations: 6462797\ncpu: 108.04923827872035 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3527.9861640143295,
            "unit": "ns/iter",
            "extra": "iterations: 199263\ncpu: 3527.968850213028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.649177879608857,
            "unit": "ns/iter",
            "extra": "iterations: 23794751\ncpu: 29.648413299218806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1695.241306847708,
            "unit": "ns/iter",
            "extra": "iterations: 413055\ncpu: 1695.1753398457815 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1389.3711293333558,
            "unit": "ns/iter",
            "extra": "iterations: 503660\ncpu: 1389.362536234761 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1774.5732749184558,
            "unit": "ns/iter",
            "extra": "iterations: 392822\ncpu: 1774.536291246418 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 78.56231100294272,
            "unit": "ns/iter",
            "extra": "iterations: 8838431\ncpu: 78.55464516269917 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2370.990270047638,
            "unit": "ns/iter",
            "extra": "iterations: 296096\ncpu: 2370.784769128932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 110.58584568059285,
            "unit": "ns/iter",
            "extra": "iterations: 6339125\ncpu: 110.58004093624892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 105.7846073462238,
            "unit": "ns/iter",
            "extra": "iterations: 6296705\ncpu: 105.78019075055948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 286.1686683044164,
            "unit": "ns/iter",
            "extra": "iterations: 2451326\ncpu: 286.1671287295119 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1193.3807879533174,
            "unit": "ns/iter",
            "extra": "iterations: 576024\ncpu: 1193.3490514284088 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 165.10127979180658,
            "unit": "ns/iter",
            "extra": "iterations: 4249910\ncpu: 165.0953799021627 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 802.5646162354072,
            "unit": "ns/iter",
            "extra": "iterations: 875198\ncpu: 802.5502160653946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1469.8722489932065,
            "unit": "ns/iter",
            "extra": "iterations: 477507\ncpu: 1469.7687279977085 ns\nthreads: 1"
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
        "date": 1729633484297,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5247525661.999987,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5247323105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 698.138439467287,
            "unit": "ns/iter",
            "extra": "iterations: 996775\ncpu: 698.1097248626824 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1373.3277836968346,
            "unit": "ns/iter",
            "extra": "iterations: 512466\ncpu: 1373.2973504583717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.70985924112517,
            "unit": "ns/iter",
            "extra": "iterations: 5391845\ncpu: 128.70601083673586 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 90.10591675515104,
            "unit": "ns/iter",
            "extra": "iterations: 7750870\ncpu: 90.10400587288927 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3147.1397122947947,
            "unit": "ns/iter",
            "extra": "iterations: 222450\ncpu: 3146.9074533603025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 31.991066697537185,
            "unit": "ns/iter",
            "extra": "iterations: 23288476\ncpu: 31.99052728911927 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1651.3422751713624,
            "unit": "ns/iter",
            "extra": "iterations: 424223\ncpu: 1651.3136958627852 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1351.5303312977562,
            "unit": "ns/iter",
            "extra": "iterations: 517782\ncpu: 1351.4918556458138 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1731.6260131751153,
            "unit": "ns/iter",
            "extra": "iterations: 403188\ncpu: 1731.575738861276 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 78.02702433567266,
            "unit": "ns/iter",
            "extra": "iterations: 8967658\ncpu: 78.0239607710286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2306.4816226909275,
            "unit": "ns/iter",
            "extra": "iterations: 306873\ncpu: 2306.423416201488 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 93.51082074457831,
            "unit": "ns/iter",
            "extra": "iterations: 7509742\ncpu: 93.5077198391105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 101.26367457109482,
            "unit": "ns/iter",
            "extra": "iterations: 6913215\ncpu: 101.26207531517572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 275.7616187698757,
            "unit": "ns/iter",
            "extra": "iterations: 2549022\ncpu: 275.75131324876696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1118.9000603158258,
            "unit": "ns/iter",
            "extra": "iterations: 611779\ncpu: 1118.8412433247925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 160.3994704254787,
            "unit": "ns/iter",
            "extra": "iterations: 4386918\ncpu: 160.39428204493447 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 825.3061620409264,
            "unit": "ns/iter",
            "extra": "iterations: 861338\ncpu: 825.2789624978833 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1342.8117685442826,
            "unit": "ns/iter",
            "extra": "iterations: 521050\ncpu: 1342.788513578347 ns\nthreads: 1"
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
        "date": 1729634314065,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5212560951.9999895,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5212206328 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 691.0670526873673,
            "unit": "ns/iter",
            "extra": "iterations: 1009445\ncpu: 691.0333618968841 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1350.1919585805242,
            "unit": "ns/iter",
            "extra": "iterations: 533662\ncpu: 1350.1148311103289 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 129.86569975852825,
            "unit": "ns/iter",
            "extra": "iterations: 5427265\ncpu: 129.8595718101107 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 90.76076145688326,
            "unit": "ns/iter",
            "extra": "iterations: 7714685\ncpu: 90.75561257523806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3170.4153986895767,
            "unit": "ns/iter",
            "extra": "iterations: 222993\ncpu: 3170.303287547142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.097941298408692,
            "unit": "ns/iter",
            "extra": "iterations: 24054919\ncpu: 29.095928529212618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1628.1819143136706,
            "unit": "ns/iter",
            "extra": "iterations: 425552\ncpu: 1628.119501259541 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1338.7427062619574,
            "unit": "ns/iter",
            "extra": "iterations: 521509\ncpu: 1338.6287446621222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1704.2868924644122,
            "unit": "ns/iter",
            "extra": "iterations: 407651\ncpu: 1704.2136312679213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 77.35477410382798,
            "unit": "ns/iter",
            "extra": "iterations: 9052411\ncpu: 77.35348328749102 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2297.4444012287445,
            "unit": "ns/iter",
            "extra": "iterations: 303388\ncpu: 2297.355211807981 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 91.77454342594866,
            "unit": "ns/iter",
            "extra": "iterations: 7596851\ncpu: 91.77170646100612 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 101.27535518666608,
            "unit": "ns/iter",
            "extra": "iterations: 6919038\ncpu: 101.26977016169022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 274.55977054493087,
            "unit": "ns/iter",
            "extra": "iterations: 2547601\ncpu: 274.54671983564134 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1195.4996472550822,
            "unit": "ns/iter",
            "extra": "iterations: 585409\ncpu: 1195.4678165180246 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 158.0471697602507,
            "unit": "ns/iter",
            "extra": "iterations: 4433582\ncpu: 158.03901247343606 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 818.1008518409544,
            "unit": "ns/iter",
            "extra": "iterations: 875046\ncpu: 817.2367875517385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1331.8219318551278,
            "unit": "ns/iter",
            "extra": "iterations: 526613\ncpu: 1331.8090704179358 ns\nthreads: 1"
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
        "date": 1729687130886,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5394315145.999997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5393806895 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 689.0575541051855,
            "unit": "ns/iter",
            "extra": "iterations: 1018294\ncpu: 689.0109968240996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1351.0689623066644,
            "unit": "ns/iter",
            "extra": "iterations: 526273\ncpu: 1351.003025045937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 131.81531939211203,
            "unit": "ns/iter",
            "extra": "iterations: 5288108\ncpu: 131.8084314843799 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 93.49697337605255,
            "unit": "ns/iter",
            "extra": "iterations: 7483751\ncpu: 93.49117681761464 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3219.110601609144,
            "unit": "ns/iter",
            "extra": "iterations: 223966\ncpu: 3218.870516060472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 35.1561833307286,
            "unit": "ns/iter",
            "extra": "iterations: 19929534\ncpu: 35.1544017536988 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1658.439831980816,
            "unit": "ns/iter",
            "extra": "iterations: 420190\ncpu: 1658.3556034175024 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1326.6590979109906,
            "unit": "ns/iter",
            "extra": "iterations: 522587\ncpu: 1326.562692910461 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1705.4319187998028,
            "unit": "ns/iter",
            "extra": "iterations: 409063\ncpu: 1705.3116757076539 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 78.13732695099782,
            "unit": "ns/iter",
            "extra": "iterations: 8971014\ncpu: 78.13559258741549 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2313.2623091710716,
            "unit": "ns/iter",
            "extra": "iterations: 304854\ncpu: 2313.199967853465 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 97.17519630665696,
            "unit": "ns/iter",
            "extra": "iterations: 7291398\ncpu: 97.17473315816791 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 101.84531449702214,
            "unit": "ns/iter",
            "extra": "iterations: 6888396\ncpu: 101.84402246909148 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 268.99823735243774,
            "unit": "ns/iter",
            "extra": "iterations: 2600066\ncpu: 268.9971496877388 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1130.3669531481578,
            "unit": "ns/iter",
            "extra": "iterations: 622728\ncpu: 1130.3622432265754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 160.76857284020838,
            "unit": "ns/iter",
            "extra": "iterations: 4361705\ncpu: 160.76627992952328 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 739.3751070225715,
            "unit": "ns/iter",
            "extra": "iterations: 950734\ncpu: 739.3658731043589 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1283.342064445693,
            "unit": "ns/iter",
            "extra": "iterations: 549300\ncpu: 1283.3368068450702 ns\nthreads: 1"
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
        "date": 1729695246554,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5188454880.999984,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5188159355.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 697.9938646181791,
            "unit": "ns/iter",
            "extra": "iterations: 996515\ncpu: 697.9878717329898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1374.4560119050705,
            "unit": "ns/iter",
            "extra": "iterations: 503318\ncpu: 1374.4446592412758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 139.32433634256438,
            "unit": "ns/iter",
            "extra": "iterations: 5066620\ncpu: 139.32341541303657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 90.18175858155739,
            "unit": "ns/iter",
            "extra": "iterations: 7765372\ncpu: 90.18115049736208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3061.7540931132553,
            "unit": "ns/iter",
            "extra": "iterations: 228066\ncpu: 3061.726618610402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 28.174002090188715,
            "unit": "ns/iter",
            "extra": "iterations: 24836989\ncpu: 28.17311667690478 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1642.8987285741775,
            "unit": "ns/iter",
            "extra": "iterations: 424720\ncpu: 1642.892929459409 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1340.941035577871,
            "unit": "ns/iter",
            "extra": "iterations: 520212\ncpu: 1340.9299843140877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1726.7332302491823,
            "unit": "ns/iter",
            "extra": "iterations: 403554\ncpu: 1726.6965536210787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 77.32202744703659,
            "unit": "ns/iter",
            "extra": "iterations: 9037770\ncpu: 77.32135770217658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2271.631563979471,
            "unit": "ns/iter",
            "extra": "iterations: 309435\ncpu: 2271.627782894628 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 92.67564002456108,
            "unit": "ns/iter",
            "extra": "iterations: 7559749\ncpu: 92.67420148473194 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 100.5663445690144,
            "unit": "ns/iter",
            "extra": "iterations: 6947479\ncpu: 100.56325265610703 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 273.898633886603,
            "unit": "ns/iter",
            "extra": "iterations: 2559524\ncpu: 273.8957864821738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1132.1658233064793,
            "unit": "ns/iter",
            "extra": "iterations: 618755\ncpu: 1132.1188709586218 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 159.6841386485724,
            "unit": "ns/iter",
            "extra": "iterations: 4375119\ncpu: 159.67838840497828 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 725.163922956767,
            "unit": "ns/iter",
            "extra": "iterations: 963355\ncpu: 725.1320779982462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1284.8776611622447,
            "unit": "ns/iter",
            "extra": "iterations: 542714\ncpu: 1284.8357587974529 ns\nthreads: 1"
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
        "date": 1729696864706,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5241730667.000013,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5241255948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 690.805815011361,
            "unit": "ns/iter",
            "extra": "iterations: 1013446\ncpu: 690.7483960664903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1364.3498472350966,
            "unit": "ns/iter",
            "extra": "iterations: 514516\ncpu: 1364.335744661003 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 135.43395170227006,
            "unit": "ns/iter",
            "extra": "iterations: 5169891\ncpu: 135.42644167933133 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 89.96427306405319,
            "unit": "ns/iter",
            "extra": "iterations: 7761007\ncpu: 89.9587880799487 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3039.819157404923,
            "unit": "ns/iter",
            "extra": "iterations: 227369\ncpu: 3039.784522076449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.577926771994623,
            "unit": "ns/iter",
            "extra": "iterations: 25352513\ncpu: 27.577955092656886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1613.2599278731057,
            "unit": "ns/iter",
            "extra": "iterations: 431462\ncpu: 1613.2392423898298 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1326.953015190002,
            "unit": "ns/iter",
            "extra": "iterations: 528043\ncpu: 1326.9090433922993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1697.852316250056,
            "unit": "ns/iter",
            "extra": "iterations: 410966\ncpu: 1697.7860844936065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 75.8891084242262,
            "unit": "ns/iter",
            "extra": "iterations: 9175440\ncpu: 75.88626539980642 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2236.3768777799237,
            "unit": "ns/iter",
            "extra": "iterations: 310939\ncpu: 2236.334776274445 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 90.80609621740618,
            "unit": "ns/iter",
            "extra": "iterations: 7695198\ncpu: 90.80199521831675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 99.92145215152128,
            "unit": "ns/iter",
            "extra": "iterations: 7008938\ncpu: 99.92061022654202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 275.7538282944998,
            "unit": "ns/iter",
            "extra": "iterations: 2580849\ncpu: 275.7447119145675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1143.994096712304,
            "unit": "ns/iter",
            "extra": "iterations: 614234\ncpu: 1143.995220062712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 157.29027709733148,
            "unit": "ns/iter",
            "extra": "iterations: 4449700\ncpu: 157.28358788232885 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 767.7013449771682,
            "unit": "ns/iter",
            "extra": "iterations: 918826\ncpu: 767.6785267286747 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1276.6021157565667,
            "unit": "ns/iter",
            "extra": "iterations: 547511\ncpu: 1276.534559123018 ns\nthreads: 1"
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
        "date": 1729697736624,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5229752676.999965,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5229422187 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 669.901047975015,
            "unit": "ns/iter",
            "extra": "iterations: 1040292\ncpu: 669.8672766876989 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1358.3049540115926,
            "unit": "ns/iter",
            "extra": "iterations: 518065\ncpu: 1358.2168588883637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.62413157730367,
            "unit": "ns/iter",
            "extra": "iterations: 5438020\ncpu: 128.61933442686876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 89.78621685815631,
            "unit": "ns/iter",
            "extra": "iterations: 7800297\ncpu: 89.780959109634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3093.040569949633,
            "unit": "ns/iter",
            "extra": "iterations: 228371\ncpu: 3092.9761528390254 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.090549744732954,
            "unit": "ns/iter",
            "extra": "iterations: 24070990\ncpu: 29.089921228831894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1634.9418551940125,
            "unit": "ns/iter",
            "extra": "iterations: 427966\ncpu: 1634.930597290437 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1337.9974075906907,
            "unit": "ns/iter",
            "extra": "iterations: 525380\ncpu: 1337.9714435265905 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1722.2203306689166,
            "unit": "ns/iter",
            "extra": "iterations: 407719\ncpu: 1722.20868784629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 76.59289916970336,
            "unit": "ns/iter",
            "extra": "iterations: 9136847\ncpu: 76.59309168688073 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2404.015739275011,
            "unit": "ns/iter",
            "extra": "iterations: 293152\ncpu: 2403.9849224975437 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 91.63410073513423,
            "unit": "ns/iter",
            "extra": "iterations: 7636938\ncpu: 91.63226727780176 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 100.2471447824199,
            "unit": "ns/iter",
            "extra": "iterations: 6902889\ncpu: 100.24580128696819 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 268.2564312173575,
            "unit": "ns/iter",
            "extra": "iterations: 2589673\ncpu: 268.25273075017594 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1150.6759641918345,
            "unit": "ns/iter",
            "extra": "iterations: 611704\ncpu: 1150.6256097720475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 157.44564399005853,
            "unit": "ns/iter",
            "extra": "iterations: 4445387\ncpu: 157.440594260972 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 764.1056039050904,
            "unit": "ns/iter",
            "extra": "iterations: 924748\ncpu: 764.1075395675385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1303.8348916698367,
            "unit": "ns/iter",
            "extra": "iterations: 544170\ncpu: 1303.7992722862377 ns\nthreads: 1"
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
        "date": 1729702466460,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5136497290.000023,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5136046940 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 712.3150975557587,
            "unit": "ns/iter",
            "extra": "iterations: 959195\ncpu: 712.3055322431828 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1404.1303215590756,
            "unit": "ns/iter",
            "extra": "iterations: 497669\ncpu: 1404.1120403320278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 133.16607907409818,
            "unit": "ns/iter",
            "extra": "iterations: 5264986\ncpu: 133.16360784245208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 92.87290521889267,
            "unit": "ns/iter",
            "extra": "iterations: 7540585\ncpu: 92.86977124453858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3180.4989900851447,
            "unit": "ns/iter",
            "extra": "iterations: 216850\ncpu: 3180.442245792017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.241581841070055,
            "unit": "ns/iter",
            "extra": "iterations: 24035689\ncpu: 29.240751866942517 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1625.358068135977,
            "unit": "ns/iter",
            "extra": "iterations: 419719\ncpu: 1625.3073151322653 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1339.210596708752,
            "unit": "ns/iter",
            "extra": "iterations: 524125\ncpu: 1339.1686944908174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1726.019377302163,
            "unit": "ns/iter",
            "extra": "iterations: 406971\ncpu: 1725.9329559108658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 80.80272883283551,
            "unit": "ns/iter",
            "extra": "iterations: 8667222\ncpu: 80.80073199924962 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2351.7386221587003,
            "unit": "ns/iter",
            "extra": "iterations: 299991\ncpu: 2351.697747599094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 94.72853301678697,
            "unit": "ns/iter",
            "extra": "iterations: 7469063\ncpu: 94.72614235547324 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 109.262935540561,
            "unit": "ns/iter",
            "extra": "iterations: 6405144\ncpu: 109.25922102610029 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 271.5498555495686,
            "unit": "ns/iter",
            "extra": "iterations: 2568009\ncpu: 271.54305650797966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1084.5420576532952,
            "unit": "ns/iter",
            "extra": "iterations: 639408\ncpu: 1084.5300778219823 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 160.00677524860916,
            "unit": "ns/iter",
            "extra": "iterations: 4382865\ncpu: 160.00080883166578 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 747.6984338795584,
            "unit": "ns/iter",
            "extra": "iterations: 938242\ncpu: 747.6654008240948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1322.0450608346682,
            "unit": "ns/iter",
            "extra": "iterations: 531193\ncpu: 1322.021427240197 ns\nthreads: 1"
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
        "date": 1729703351754,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5240407704.000006,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5240241672 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 679.0025599345562,
            "unit": "ns/iter",
            "extra": "iterations: 1031667\ncpu: 678.9899463683533 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1375.2864269634833,
            "unit": "ns/iter",
            "extra": "iterations: 503734\ncpu: 1375.2882989831937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 130.48229564624592,
            "unit": "ns/iter",
            "extra": "iterations: 5354954\ncpu: 130.47932792700004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 93.64991527053128,
            "unit": "ns/iter",
            "extra": "iterations: 7479098\ncpu: 93.64871205057075 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3035.301947531644,
            "unit": "ns/iter",
            "extra": "iterations: 230805\ncpu: 3035.2248954745332 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.252822051827565,
            "unit": "ns/iter",
            "extra": "iterations: 24278080\ncpu: 30.25201350353897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1639.855771988164,
            "unit": "ns/iter",
            "extra": "iterations: 428925\ncpu: 1639.7711371451892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1325.006123704484,
            "unit": "ns/iter",
            "extra": "iterations: 526642\ncpu: 1324.9480557950167 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1712.5390927885064,
            "unit": "ns/iter",
            "extra": "iterations: 411150\ncpu: 1712.496825975923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 80.58710152655992,
            "unit": "ns/iter",
            "extra": "iterations: 8605561\ncpu: 80.58349060566769 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2242.236863092778,
            "unit": "ns/iter",
            "extra": "iterations: 313468\ncpu: 2242.1688976227238 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 94.81322494422616,
            "unit": "ns/iter",
            "extra": "iterations: 7392379\ncpu: 94.81077214791061 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 109.83915008491249,
            "unit": "ns/iter",
            "extra": "iterations: 6369248\ncpu: 109.83795575239017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 264.1138922528585,
            "unit": "ns/iter",
            "extra": "iterations: 2656423\ncpu: 264.1075246675703 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1055.434542863805,
            "unit": "ns/iter",
            "extra": "iterations: 668827\ncpu: 1055.422074766715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 155.51648928168703,
            "unit": "ns/iter",
            "extra": "iterations: 4361136\ncpu: 155.51418850501383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 744.088426107122,
            "unit": "ns/iter",
            "extra": "iterations: 930076\ncpu: 744.0733929270317 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1281.948652365659,
            "unit": "ns/iter",
            "extra": "iterations: 549704\ncpu: 1281.9208683218587 ns\nthreads: 1"
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
        "date": 1729705421491,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5168981606.999978,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5168640625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 677.4355173153982,
            "unit": "ns/iter",
            "extra": "iterations: 1029633\ncpu: 677.3935615894204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1363.9067529059362,
            "unit": "ns/iter",
            "extra": "iterations: 513764\ncpu: 1363.8165616898038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 127.02740795430188,
            "unit": "ns/iter",
            "extra": "iterations: 5570901\ncpu: 127.02556426689327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.05032512077742,
            "unit": "ns/iter",
            "extra": "iterations: 7700369\ncpu: 91.04727968231126 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3103.0402155005418,
            "unit": "ns/iter",
            "extra": "iterations: 225336\ncpu: 3102.999906805835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.719426359668798,
            "unit": "ns/iter",
            "extra": "iterations: 23553574\ncpu: 29.718799533353252 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1645.4556659488967,
            "unit": "ns/iter",
            "extra": "iterations: 426354\ncpu: 1645.394836215912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1337.2270123315204,
            "unit": "ns/iter",
            "extra": "iterations: 518267\ncpu: 1337.1249182371241 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1726.7389354898928,
            "unit": "ns/iter",
            "extra": "iterations: 398775\ncpu: 1726.6513021127207 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 77.27143664555132,
            "unit": "ns/iter",
            "extra": "iterations: 9080152\ncpu: 77.26615997177156 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2373.627118070522,
            "unit": "ns/iter",
            "extra": "iterations: 295493\ncpu: 2373.503423092937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 94.1496956520465,
            "unit": "ns/iter",
            "extra": "iterations: 7514754\ncpu: 94.14378408128869 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 100.89552294707697,
            "unit": "ns/iter",
            "extra": "iterations: 6941888\ncpu: 100.8919324252995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 268.14727440346684,
            "unit": "ns/iter",
            "extra": "iterations: 2613061\ncpu: 268.14058301738856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1071.2721497980249,
            "unit": "ns/iter",
            "extra": "iterations: 653787\ncpu: 1071.221159184872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 158.78767075011373,
            "unit": "ns/iter",
            "extra": "iterations: 4483306\ncpu: 158.78557899014723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 766.263642492365,
            "unit": "ns/iter",
            "extra": "iterations: 918179\ncpu: 766.2234705868906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1284.101442246102,
            "unit": "ns/iter",
            "extra": "iterations: 546370\ncpu: 1284.054613174222 ns\nthreads: 1"
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
        "date": 1729706341416,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4787538671.999983,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4787256963 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 645.8200845781141,
            "unit": "ns/iter",
            "extra": "iterations: 1083259\ncpu: 645.8130622501175 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1263.54309278868,
            "unit": "ns/iter",
            "extra": "iterations: 549129\ncpu: 1263.5029328263486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 121.37899400906993,
            "unit": "ns/iter",
            "extra": "iterations: 6031784\ncpu: 121.37512003082361 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 85.67808123105434,
            "unit": "ns/iter",
            "extra": "iterations: 8134549\ncpu: 85.67681687085526 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2931.742115595328,
            "unit": "ns/iter",
            "extra": "iterations: 235338\ncpu: 2931.645705325958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 28.077539674082967,
            "unit": "ns/iter",
            "extra": "iterations: 25801037\ncpu: 28.077544673882628 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1539.3216503954889,
            "unit": "ns/iter",
            "extra": "iterations: 459502\ncpu: 1539.334412037379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1235.418364812398,
            "unit": "ns/iter",
            "extra": "iterations: 563654\ncpu: 1235.4119566258714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1613.5108253537833,
            "unit": "ns/iter",
            "extra": "iterations: 440078\ncpu: 1613.4943010102754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 71.49856054814583,
            "unit": "ns/iter",
            "extra": "iterations: 9701957\ncpu: 71.49760136022036 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2316.7848933597593,
            "unit": "ns/iter",
            "extra": "iterations: 303403\ncpu: 2316.7648902614665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 87.24449722239265,
            "unit": "ns/iter",
            "extra": "iterations: 8151974\ncpu: 87.24215006083197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 94.98365842421994,
            "unit": "ns/iter",
            "extra": "iterations: 7413055\ncpu: 94.98251544066527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 249.50701924365555,
            "unit": "ns/iter",
            "extra": "iterations: 2788762\ncpu: 249.50361988581346 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1079.9800603898507,
            "unit": "ns/iter",
            "extra": "iterations: 639180\ncpu: 1079.9734018586348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 146.1463729352103,
            "unit": "ns/iter",
            "extra": "iterations: 4775473\ncpu: 146.1475765856078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 701.0226049826687,
            "unit": "ns/iter",
            "extra": "iterations: 969565\ncpu: 701.0036232743562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1183.2861635535328,
            "unit": "ns/iter",
            "extra": "iterations: 597480\ncpu: 1183.2799507933355 ns\nthreads: 1"
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
        "date": 1729707894936,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5184932026.000012,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5184636836.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 703.7706182490004,
            "unit": "ns/iter",
            "extra": "iterations: 1005032\ncpu: 703.7423554672886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1378.7094596085064,
            "unit": "ns/iter",
            "extra": "iterations: 498657\ncpu: 1378.6678698985475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 130.5670338032315,
            "unit": "ns/iter",
            "extra": "iterations: 5348600\ncpu: 130.55985678495298 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 95.71411125889095,
            "unit": "ns/iter",
            "extra": "iterations: 7324017\ncpu: 95.71265358887085 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3154.0705569979027,
            "unit": "ns/iter",
            "extra": "iterations: 220701\ncpu: 3153.987725474739 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.631362247501333,
            "unit": "ns/iter",
            "extra": "iterations: 23007082\ncpu: 30.630605697845553 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1657.9735552099796,
            "unit": "ns/iter",
            "extra": "iterations: 421255\ncpu: 1657.9449905639115 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1363.4343595723835,
            "unit": "ns/iter",
            "extra": "iterations: 514500\ncpu: 1363.386513119535 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1732.922949861237,
            "unit": "ns/iter",
            "extra": "iterations: 401985\ncpu: 1732.835003793674 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 80.17595092336435,
            "unit": "ns/iter",
            "extra": "iterations: 8733117\ncpu: 80.17112721609004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2372.094076797507,
            "unit": "ns/iter",
            "extra": "iterations: 293473\ncpu: 2371.872557271027 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.29553335627597,
            "unit": "ns/iter",
            "extra": "iterations: 7093223\ncpu: 98.29194006730086 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 108.60392759978092,
            "unit": "ns/iter",
            "extra": "iterations: 6434566\ncpu: 108.60230309239188 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 271.14321725158266,
            "unit": "ns/iter",
            "extra": "iterations: 2572239\ncpu: 271.1363570803494 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1091.6495884050487,
            "unit": "ns/iter",
            "extra": "iterations: 662909\ncpu: 1091.64132482739 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 156.71557522619872,
            "unit": "ns/iter",
            "extra": "iterations: 4462375\ncpu: 156.70776032942118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 726.8533491776383,
            "unit": "ns/iter",
            "extra": "iterations: 966909\ncpu: 726.8198765344018 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1293.7464000297907,
            "unit": "ns/iter",
            "extra": "iterations: 535560\ncpu: 1293.703112629773 ns\nthreads: 1"
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
        "date": 1729709591925,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5247553735.999987,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5247219502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 687.1457542309786,
            "unit": "ns/iter",
            "extra": "iterations: 1008451\ncpu: 687.1112319785498 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1404.8157975619206,
            "unit": "ns/iter",
            "extra": "iterations: 501052\ncpu: 1404.762589511668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.78756971856407,
            "unit": "ns/iter",
            "extra": "iterations: 5503914\ncpu: 128.78298934176664 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 94.26894219890228,
            "unit": "ns/iter",
            "extra": "iterations: 7417869\ncpu: 94.26492568148608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3167.881613286969,
            "unit": "ns/iter",
            "extra": "iterations: 221089\ncpu: 3167.699397075378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.40772433414204,
            "unit": "ns/iter",
            "extra": "iterations: 23811088\ncpu: 29.406258840419166 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1640.1462384262156,
            "unit": "ns/iter",
            "extra": "iterations: 429634\ncpu: 1640.0005446496289 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1345.4633165237663,
            "unit": "ns/iter",
            "extra": "iterations: 527281\ncpu: 1345.4245098913132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1726.9942938130912,
            "unit": "ns/iter",
            "extra": "iterations: 404999\ncpu: 1726.9474146849755 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 81.96665537513492,
            "unit": "ns/iter",
            "extra": "iterations: 8534419\ncpu: 81.96368024583735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2312.2282862178095,
            "unit": "ns/iter",
            "extra": "iterations: 308744\ncpu: 2312.1533859767346 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 96.40101095656735,
            "unit": "ns/iter",
            "extra": "iterations: 7351849\ncpu: 96.39741090982675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 110.72283690581627,
            "unit": "ns/iter",
            "extra": "iterations: 6322494\ncpu: 110.7197227866092 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 269.6405372028519,
            "unit": "ns/iter",
            "extra": "iterations: 2566107\ncpu: 269.62808721538045 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1062.89518881295,
            "unit": "ns/iter",
            "extra": "iterations: 658403\ncpu: 1062.8528591151646 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 162.66150672015075,
            "unit": "ns/iter",
            "extra": "iterations: 4311285\ncpu: 162.6598294939911 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 722.4733510728952,
            "unit": "ns/iter",
            "extra": "iterations: 971465\ncpu: 722.4734529808102 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1337.0938264885372,
            "unit": "ns/iter",
            "extra": "iterations: 529083\ncpu: 1337.0559760944905 ns\nthreads: 1"
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
        "date": 1729710352147,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5357789891.999971,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5357556990 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 694.2324734881075,
            "unit": "ns/iter",
            "extra": "iterations: 1011810\ncpu: 694.2063470414403 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1434.9068671964758,
            "unit": "ns/iter",
            "extra": "iterations: 487841\ncpu: 1434.8818938957563 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 130.9709771298849,
            "unit": "ns/iter",
            "extra": "iterations: 5366871\ncpu: 130.9715195315857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 95.86695837347645,
            "unit": "ns/iter",
            "extra": "iterations: 7298881\ncpu: 95.86624579849983 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3157.9123291136902,
            "unit": "ns/iter",
            "extra": "iterations: 221419\ncpu: 3157.886075720691 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.10203935865995,
            "unit": "ns/iter",
            "extra": "iterations: 23940958\ncpu: 29.10066744196286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1648.6904848611139,
            "unit": "ns/iter",
            "extra": "iterations: 422884\ncpu: 1648.6500647931819 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1339.9028921299184,
            "unit": "ns/iter",
            "extra": "iterations: 511699\ncpu: 1339.9091262636834 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1732.4237537853244,
            "unit": "ns/iter",
            "extra": "iterations: 404525\ncpu: 1732.4308065014502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 81.93517686369688,
            "unit": "ns/iter",
            "extra": "iterations: 8548815\ncpu: 81.93246455795335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2346.56559218199,
            "unit": "ns/iter",
            "extra": "iterations: 307186\ncpu: 2346.4289030099003 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 97.06237171761076,
            "unit": "ns/iter",
            "extra": "iterations: 7166806\ncpu: 97.06173614857153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 111.3085550022815,
            "unit": "ns/iter",
            "extra": "iterations: 6292003\ncpu: 111.305158150751 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 268.21632032075115,
            "unit": "ns/iter",
            "extra": "iterations: 2596922\ncpu: 268.20693728960686 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1033.131591553992,
            "unit": "ns/iter",
            "extra": "iterations: 651288\ncpu: 1033.1351276240325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 162.71267507083053,
            "unit": "ns/iter",
            "extra": "iterations: 4298903\ncpu: 162.7130486545061 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 723.8152498183724,
            "unit": "ns/iter",
            "extra": "iterations: 973087\ncpu: 723.7945959611009 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1369.2364661311435,
            "unit": "ns/iter",
            "extra": "iterations: 515503\ncpu: 1369.222169415116 ns\nthreads: 1"
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
        "date": 1729717302208,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5220202790.0000305,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5220029713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 676.5448813520522,
            "unit": "ns/iter",
            "extra": "iterations: 1030907\ncpu: 676.5408024196163 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1421.7133230251873,
            "unit": "ns/iter",
            "extra": "iterations: 492816\ncpu: 1421.7189498717564 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 125.41121627364033,
            "unit": "ns/iter",
            "extra": "iterations: 5556373\ncpu: 125.41016468836781 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 94.25838680344368,
            "unit": "ns/iter",
            "extra": "iterations: 7434060\ncpu: 94.2555121965654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3074.818171489939,
            "unit": "ns/iter",
            "extra": "iterations: 228853\ncpu: 3074.742140151095 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.109732076505242,
            "unit": "ns/iter",
            "extra": "iterations: 24042423\ncpu: 29.10983689123177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1633.4187182712535,
            "unit": "ns/iter",
            "extra": "iterations: 429420\ncpu: 1633.409242699455 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1337.216138328566,
            "unit": "ns/iter",
            "extra": "iterations: 530563\ncpu: 1337.2013333006632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1714.948809047647,
            "unit": "ns/iter",
            "extra": "iterations: 410092\ncpu: 1714.9115832544924 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 76.5033418468619,
            "unit": "ns/iter",
            "extra": "iterations: 9142699\ncpu: 76.50288421395038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2326.8372751136026,
            "unit": "ns/iter",
            "extra": "iterations: 302486\ncpu: 2326.8008535932204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 99.80983653093898,
            "unit": "ns/iter",
            "extra": "iterations: 6707324\ncpu: 99.80801449281397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 99.96767877934356,
            "unit": "ns/iter",
            "extra": "iterations: 7001592\ncpu: 99.96802184417488 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 259.5547180765357,
            "unit": "ns/iter",
            "extra": "iterations: 2697381\ncpu: 259.55108455201525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1029.6469363419562,
            "unit": "ns/iter",
            "extra": "iterations: 657482\ncpu: 1029.640057066199 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 155.18299271714432,
            "unit": "ns/iter",
            "extra": "iterations: 4504141\ncpu: 155.17405694004705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 723.2632766116145,
            "unit": "ns/iter",
            "extra": "iterations: 946081\ncpu: 723.2293207452632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1258.0485507038122,
            "unit": "ns/iter",
            "extra": "iterations: 555028\ncpu: 1257.9735995301085 ns\nthreads: 1"
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
        "date": 1729719626442,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5135891635.999996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5135610100 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 683.8460410714424,
            "unit": "ns/iter",
            "extra": "iterations: 1023825\ncpu: 683.8260903963077 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1370.0662998668604,
            "unit": "ns/iter",
            "extra": "iterations: 507452\ncpu: 1370.0021598101885 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 127.7006485222209,
            "unit": "ns/iter",
            "extra": "iterations: 5475834\ncpu: 127.69790410008784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 92.39504725926743,
            "unit": "ns/iter",
            "extra": "iterations: 7540108\ncpu: 92.39256785181331 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3122.7291724145593,
            "unit": "ns/iter",
            "extra": "iterations: 224726\ncpu: 3122.721024714541 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.58688750928667,
            "unit": "ns/iter",
            "extra": "iterations: 23584276\ncpu: 29.584995231568698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1648.3288850563129,
            "unit": "ns/iter",
            "extra": "iterations: 422111\ncpu: 1648.324734489271 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1339.3692446411642,
            "unit": "ns/iter",
            "extra": "iterations: 522361\ncpu: 1339.3627376469547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1751.6302422434796,
            "unit": "ns/iter",
            "extra": "iterations: 405790\ncpu: 1751.5729983488982 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 80.1540714270604,
            "unit": "ns/iter",
            "extra": "iterations: 8728205\ncpu: 80.15249859507196 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2390.6792340506413,
            "unit": "ns/iter",
            "extra": "iterations: 293962\ncpu: 2390.6328607098876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.60635865218387,
            "unit": "ns/iter",
            "extra": "iterations: 7098454\ncpu: 98.60366144515378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 108.67399447097917,
            "unit": "ns/iter",
            "extra": "iterations: 6437308\ncpu: 108.67149948394585 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 265.641948068302,
            "unit": "ns/iter",
            "extra": "iterations: 2634076\ncpu: 265.63914746575153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1075.66375929181,
            "unit": "ns/iter",
            "extra": "iterations: 642504\ncpu: 1075.64434151383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 162.44057873327813,
            "unit": "ns/iter",
            "extra": "iterations: 4305403\ncpu: 162.43590437410853 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 720.4929103803205,
            "unit": "ns/iter",
            "extra": "iterations: 973536\ncpu: 720.4813032081 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1322.634069822859,
            "unit": "ns/iter",
            "extra": "iterations: 530399\ncpu: 1322.5429610538508 ns\nthreads: 1"
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
        "date": 1729720653023,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5230102908.999982,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5229727137 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 687.5131843590032,
            "unit": "ns/iter",
            "extra": "iterations: 999859\ncpu: 687.4601788852224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1365.6248435141742,
            "unit": "ns/iter",
            "extra": "iterations: 512826\ncpu: 1365.526024421537 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.4043629384139,
            "unit": "ns/iter",
            "extra": "iterations: 5464299\ncpu: 128.40242838102395 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.32037243257356,
            "unit": "ns/iter",
            "extra": "iterations: 7676987\ncpu: 91.31796054884553 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3120.679994589612,
            "unit": "ns/iter",
            "extra": "iterations: 221790\ncpu: 3120.6070697506693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.172615665424566,
            "unit": "ns/iter",
            "extra": "iterations: 24063349\ncpu: 29.171134200813064 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1655.9684345643122,
            "unit": "ns/iter",
            "extra": "iterations: 423026\ncpu: 1655.9275032740304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1354.669540196853,
            "unit": "ns/iter",
            "extra": "iterations: 520962\ncpu: 1354.5745946921293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1736.3312917952082,
            "unit": "ns/iter",
            "extra": "iterations: 405250\ncpu: 1736.2191190623082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 79.2783728309702,
            "unit": "ns/iter",
            "extra": "iterations: 8834411\ncpu: 79.27400796725453 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2392.1759856862136,
            "unit": "ns/iter",
            "extra": "iterations: 294541\ncpu: 2392.0260778635243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 92.28931075650733,
            "unit": "ns/iter",
            "extra": "iterations: 7543546\ncpu: 92.28407011768714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 107.79674368575483,
            "unit": "ns/iter",
            "extra": "iterations: 6497653\ncpu: 107.79401824012444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 267.92254135226824,
            "unit": "ns/iter",
            "extra": "iterations: 2616906\ncpu: 267.915539572304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1070.7926738116244,
            "unit": "ns/iter",
            "extra": "iterations: 655566\ncpu: 1070.7615053251675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 163.49962661671395,
            "unit": "ns/iter",
            "extra": "iterations: 4298532\ncpu: 163.4909148053335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 719.1883376263364,
            "unit": "ns/iter",
            "extra": "iterations: 971346\ncpu: 719.1156570367283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1324.056054795323,
            "unit": "ns/iter",
            "extra": "iterations: 528804\ncpu: 1323.9613694298828 ns\nthreads: 1"
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
        "date": 1729722781409,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5253989129.999979,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5253724967 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 690.408656080236,
            "unit": "ns/iter",
            "extra": "iterations: 1009279\ncpu: 690.3931856305347 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1366.002279002566,
            "unit": "ns/iter",
            "extra": "iterations: 508117\ncpu: 1365.9281425341012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 129.68097961989332,
            "unit": "ns/iter",
            "extra": "iterations: 5395113\ncpu: 129.67893332354683 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 94.20584488354419,
            "unit": "ns/iter",
            "extra": "iterations: 7683917\ncpu: 94.04963432062061 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3147.8721175611067,
            "unit": "ns/iter",
            "extra": "iterations: 221774\ncpu: 3147.755318477367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 28.857276509835998,
            "unit": "ns/iter",
            "extra": "iterations: 24319963\ncpu: 28.85651232281887 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1634.972480981718,
            "unit": "ns/iter",
            "extra": "iterations: 430902\ncpu: 1634.9549271063945 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1344.8795224688085,
            "unit": "ns/iter",
            "extra": "iterations: 520678\ncpu: 1344.8507753352355 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1723.0004213961508,
            "unit": "ns/iter",
            "extra": "iterations: 410540\ncpu: 1722.9469333073537 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 81.18656246233961,
            "unit": "ns/iter",
            "extra": "iterations: 8654919\ncpu: 81.18171862729152 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2369.7707139292543,
            "unit": "ns/iter",
            "extra": "iterations: 296612\ncpu: 2369.644377166127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 93.06448567808101,
            "unit": "ns/iter",
            "extra": "iterations: 7458850\ncpu: 93.06352132031063 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 109.69259290831745,
            "unit": "ns/iter",
            "extra": "iterations: 6369801\ncpu: 109.68951588911473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 299.97196330671585,
            "unit": "ns/iter",
            "extra": "iterations: 2316500\ncpu: 299.9669298510677 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1100.1896263314914,
            "unit": "ns/iter",
            "extra": "iterations: 646830\ncpu: 1100.1389654159484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 167.16358423233004,
            "unit": "ns/iter",
            "extra": "iterations: 4155590\ncpu: 167.15657608185663 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 781.7796758140828,
            "unit": "ns/iter",
            "extra": "iterations: 901458\ncpu: 781.7256267069589 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1421.3945930194748,
            "unit": "ns/iter",
            "extra": "iterations: 490736\ncpu: 1421.2988613022094 ns\nthreads: 1"
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
        "date": 1729777756374,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5258232754.999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5257749177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 693.1383007887264,
            "unit": "ns/iter",
            "extra": "iterations: 1017731\ncpu: 693.1164993500245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1385.7164201545168,
            "unit": "ns/iter",
            "extra": "iterations: 512145\ncpu: 1385.644395630144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 132.26814878602818,
            "unit": "ns/iter",
            "extra": "iterations: 5304611\ncpu: 132.26271653095762 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 90.72761172272553,
            "unit": "ns/iter",
            "extra": "iterations: 7717454\ncpu: 90.7260723549504 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3154.6667755516505,
            "unit": "ns/iter",
            "extra": "iterations: 220416\ncpu: 3154.438906431478 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.405995061178814,
            "unit": "ns/iter",
            "extra": "iterations: 23797989\ncpu: 29.404866058220342 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1632.9119126907021,
            "unit": "ns/iter",
            "extra": "iterations: 426713\ncpu: 1632.7866341077026 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1359.154936576171,
            "unit": "ns/iter",
            "extra": "iterations: 519206\ncpu: 1359.1530144104659 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1715.8015442996445,
            "unit": "ns/iter",
            "extra": "iterations: 408988\ncpu: 1715.7177643353837 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 80.1587222795016,
            "unit": "ns/iter",
            "extra": "iterations: 8720937\ncpu: 80.15584059373421 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2319.738136966,
            "unit": "ns/iter",
            "extra": "iterations: 301272\ncpu: 2319.5776341644723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 92.27049160998908,
            "unit": "ns/iter",
            "extra": "iterations: 7590875\ncpu: 92.26593535000892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 108.17065225553688,
            "unit": "ns/iter",
            "extra": "iterations: 6484989\ncpu: 108.16743019918783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 265.98220375643655,
            "unit": "ns/iter",
            "extra": "iterations: 2642243\ncpu: 265.96606822309707 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1082.9468230527154,
            "unit": "ns/iter",
            "extra": "iterations: 655472\ncpu: 1082.902043107868 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 158.86872991356367,
            "unit": "ns/iter",
            "extra": "iterations: 4409070\ncpu: 158.86079717491472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 724.0360944149413,
            "unit": "ns/iter",
            "extra": "iterations: 943664\ncpu: 723.9880836823296 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1360.4610417530112,
            "unit": "ns/iter",
            "extra": "iterations: 511676\ncpu: 1360.369372415353 ns\nthreads: 1"
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
        "date": 1729788724519,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5128421736.999996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5128316798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 737.205129447342,
            "unit": "ns/iter",
            "extra": "iterations: 949498\ncpu: 737.1892484239037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1347.85922203931,
            "unit": "ns/iter",
            "extra": "iterations: 519435\ncpu: 1347.8220932359197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 139.64943688364778,
            "unit": "ns/iter",
            "extra": "iterations: 5007047\ncpu: 139.6491097447258 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.84198682727687,
            "unit": "ns/iter",
            "extra": "iterations: 7617713\ncpu: 91.84282959990733 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3345.435793183892,
            "unit": "ns/iter",
            "extra": "iterations: 216192\ncpu: 3345.4627599541177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 36.5118164783502,
            "unit": "ns/iter",
            "extra": "iterations: 19159854\ncpu: 36.51034506839142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1686.7020649181693,
            "unit": "ns/iter",
            "extra": "iterations: 415416\ncpu: 1686.715039863655 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1568.7229134069942,
            "unit": "ns/iter",
            "extra": "iterations: 447380\ncpu: 1568.6877307881473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 2000.6397921349385,
            "unit": "ns/iter",
            "extra": "iterations: 349265\ncpu: 2000.6397663665118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 90.8060528611665,
            "unit": "ns/iter",
            "extra": "iterations: 7638272\ncpu: 90.79986743074882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2521.7267737731554,
            "unit": "ns/iter",
            "extra": "iterations: 257812\ncpu: 2521.7054403984334 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 113.40201228596925,
            "unit": "ns/iter",
            "extra": "iterations: 7453215\ncpu: 113.4028060373948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 115.17889725699317,
            "unit": "ns/iter",
            "extra": "iterations: 6080764\ncpu: 115.17868478368857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 310.0791465115205,
            "unit": "ns/iter",
            "extra": "iterations: 2273821\ncpu: 310.07471872236306 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1069.111828315666,
            "unit": "ns/iter",
            "extra": "iterations: 635492\ncpu: 1069.0486725245974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 189.65605957525804,
            "unit": "ns/iter",
            "extra": "iterations: 3677634\ncpu: 189.64546009744367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 729.8063366360689,
            "unit": "ns/iter",
            "extra": "iterations: 809420\ncpu: 729.781340960196 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1343.0916792892908,
            "unit": "ns/iter",
            "extra": "iterations: 467412\ncpu: 1343.0248816889616 ns\nthreads: 1"
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
          "id": "517cb182ae8921d69291c3aef727a0db572a9e28",
          "message": "Implement a `LoopPropertiesStartsWith` step (#76)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-24T19:05:00Z",
          "url": "https://github.com/sourcemeta/blaze/commit/517cb182ae8921d69291c3aef727a0db572a9e28"
        },
        "date": 1729796734067,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5128514456.999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5128208076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 705.4366949571407,
            "unit": "ns/iter",
            "extra": "iterations: 990087\ncpu: 705.4121152989579 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1348.466780215044,
            "unit": "ns/iter",
            "extra": "iterations: 508447\ncpu: 1348.3724222977028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 137.58702338895654,
            "unit": "ns/iter",
            "extra": "iterations: 5059996\ncpu: 137.58009097240395 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.61548940103964,
            "unit": "ns/iter",
            "extra": "iterations: 7641974\ncpu: 91.61211291742153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3251.5428601525086,
            "unit": "ns/iter",
            "extra": "iterations: 218338\ncpu: 3251.364292976943 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.345146965086002,
            "unit": "ns/iter",
            "extra": "iterations: 23081979\ncpu: 30.342792444270035 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1663.8891779163316,
            "unit": "ns/iter",
            "extra": "iterations: 421721\ncpu: 1663.7756953056637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1364.1062521212048,
            "unit": "ns/iter",
            "extra": "iterations: 512658\ncpu: 1364.0295791736382 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1733.8481510776912,
            "unit": "ns/iter",
            "extra": "iterations: 403289\ncpu: 1733.743355261364 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 78.28884909202135,
            "unit": "ns/iter",
            "extra": "iterations: 8940402\ncpu: 78.28812451610129 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2294.3976576913988,
            "unit": "ns/iter",
            "extra": "iterations: 299192\ncpu: 2294.3385986256303 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 92.5715923602617,
            "unit": "ns/iter",
            "extra": "iterations: 7547174\ncpu: 92.56407577193781 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 102.04989554224841,
            "unit": "ns/iter",
            "extra": "iterations: 6859711\ncpu: 102.0421246609369 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 277.4160916973133,
            "unit": "ns/iter",
            "extra": "iterations: 2525352\ncpu: 277.40620079893733 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1073.587952675931,
            "unit": "ns/iter",
            "extra": "iterations: 660213\ncpu: 1073.551340249282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 161.06841664814976,
            "unit": "ns/iter",
            "extra": "iterations: 4350827\ncpu: 161.0620773935623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 714.8851446637417,
            "unit": "ns/iter",
            "extra": "iterations: 982105\ncpu: 714.8657679168736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1356.7337719920122,
            "unit": "ns/iter",
            "extra": "iterations: 515359\ncpu: 1356.6641739059532 ns\nthreads: 1"
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
        "date": 1729797249753,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5405461067.999966,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5405296992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 700.7378903375962,
            "unit": "ns/iter",
            "extra": "iterations: 998975\ncpu: 700.7089246477636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1354.3032714531187,
            "unit": "ns/iter",
            "extra": "iterations: 518852\ncpu: 1354.3098629281558 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 130.59471917446373,
            "unit": "ns/iter",
            "extra": "iterations: 5389574\ncpu: 130.59025741181026 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 89.83737597867774,
            "unit": "ns/iter",
            "extra": "iterations: 7821034\ncpu: 89.83616245626862 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3238.1826142311033,
            "unit": "ns/iter",
            "extra": "iterations: 218351\ncpu: 3238.1378972388457 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 28.534695301893144,
            "unit": "ns/iter",
            "extra": "iterations: 24575604\ncpu: 28.53451369903262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1634.6667383307654,
            "unit": "ns/iter",
            "extra": "iterations: 427922\ncpu: 1634.674858969627 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1328.3448140544165,
            "unit": "ns/iter",
            "extra": "iterations: 527493\ncpu: 1328.3138733594583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1735.7833470248195,
            "unit": "ns/iter",
            "extra": "iterations: 411446\ncpu: 1735.792716419651 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 76.9194179258083,
            "unit": "ns/iter",
            "extra": "iterations: 9118219\ncpu: 76.91665543457546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2286.6895162752717,
            "unit": "ns/iter",
            "extra": "iterations: 303375\ncpu: 2286.7017684384073 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 91.45580720762246,
            "unit": "ns/iter",
            "extra": "iterations: 7720139\ncpu: 91.45100133559781 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 100.22215550592827,
            "unit": "ns/iter",
            "extra": "iterations: 6984801\ncpu: 100.22027084236191 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 271.1259429012279,
            "unit": "ns/iter",
            "extra": "iterations: 2592000\ncpu: 271.1150169753081 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1070.0466155488134,
            "unit": "ns/iter",
            "extra": "iterations: 653001\ncpu: 1070.0302985753428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 157.9319617031722,
            "unit": "ns/iter",
            "extra": "iterations: 4430446\ncpu: 157.93321259304315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 482.0736701090017,
            "unit": "ns/iter",
            "extra": "iterations: 1453371\ncpu: 482.06728908172835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1333.678866664116,
            "unit": "ns/iter",
            "extra": "iterations: 526940\ncpu: 1333.6881124985796 ns\nthreads: 1"
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
        "date": 1729798160746,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5243272512.999966,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5242840610 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 700.1391291914099,
            "unit": "ns/iter",
            "extra": "iterations: 1007064\ncpu: 700.0784180548601 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1354.9617192824742,
            "unit": "ns/iter",
            "extra": "iterations: 516448\ncpu: 1354.8877021500723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 130.5068690491121,
            "unit": "ns/iter",
            "extra": "iterations: 5358238\ncpu: 130.50205664623337 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.40542276678296,
            "unit": "ns/iter",
            "extra": "iterations: 7724507\ncpu: 91.39914637917978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3209.4269749448326,
            "unit": "ns/iter",
            "extra": "iterations: 220753\ncpu: 3209.3383963071797 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.75201130552441,
            "unit": "ns/iter",
            "extra": "iterations: 23566534\ncpu: 29.750864552250274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1648.5518379055604,
            "unit": "ns/iter",
            "extra": "iterations: 420397\ncpu: 1648.4810857356238 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1346.9691350939838,
            "unit": "ns/iter",
            "extra": "iterations: 514079\ncpu: 1346.8953623859377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1751.0410675928492,
            "unit": "ns/iter",
            "extra": "iterations: 401314\ncpu: 1750.9916698644918 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 78.61450505714159,
            "unit": "ns/iter",
            "extra": "iterations: 8905432\ncpu: 78.6079424333373 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2368.0416762250006,
            "unit": "ns/iter",
            "extra": "iterations: 296428\ncpu: 2367.91425236482 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 93.39757628072343,
            "unit": "ns/iter",
            "extra": "iterations: 7541715\ncpu: 93.39336662814752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 102.0477489122301,
            "unit": "ns/iter",
            "extra": "iterations: 6760887\ncpu: 102.0434397143454 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 271.94344394316283,
            "unit": "ns/iter",
            "extra": "iterations: 2570989\ncpu: 271.9349036499188 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1071.0042751372519,
            "unit": "ns/iter",
            "extra": "iterations: 667347\ncpu: 1070.9469196684788 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 160.2725335215484,
            "unit": "ns/iter",
            "extra": "iterations: 4366894\ncpu: 160.2674981348304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 466.22030896975633,
            "unit": "ns/iter",
            "extra": "iterations: 1504419\ncpu: 466.2009805778839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1347.5936252838178,
            "unit": "ns/iter",
            "extra": "iterations: 520933\ncpu: 1347.5216256217175 ns\nthreads: 1"
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
        "date": 1729798426698,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5192480895.000017,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5192233143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 702.9527402849417,
            "unit": "ns/iter",
            "extra": "iterations: 1014712\ncpu: 702.929547497221 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1377.955927105387,
            "unit": "ns/iter",
            "extra": "iterations: 509338\ncpu: 1377.9352983676854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 133.3210966227309,
            "unit": "ns/iter",
            "extra": "iterations: 5229401\ncpu: 133.3164796503462 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 90.75036964149548,
            "unit": "ns/iter",
            "extra": "iterations: 7707468\ncpu: 90.74739862689022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3059.485165396135,
            "unit": "ns/iter",
            "extra": "iterations: 228149\ncpu: 3059.357880157269 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 28.478361006662496,
            "unit": "ns/iter",
            "extra": "iterations: 24588898\ncpu: 28.476971761808976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1661.6482523763334,
            "unit": "ns/iter",
            "extra": "iterations: 421973\ncpu: 1661.5425963272512 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1350.236959524636,
            "unit": "ns/iter",
            "extra": "iterations: 521971\ncpu: 1350.197792597672 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1729.9424536487477,
            "unit": "ns/iter",
            "extra": "iterations: 401068\ncpu: 1729.8945714941071 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 76.77521817473581,
            "unit": "ns/iter",
            "extra": "iterations: 9119296\ncpu: 76.77285527303859 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2283.4069082477167,
            "unit": "ns/iter",
            "extra": "iterations: 300134\ncpu: 2283.385241258907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 92.88310314747979,
            "unit": "ns/iter",
            "extra": "iterations: 7494017\ncpu: 92.87975847933089 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 100.29489059787309,
            "unit": "ns/iter",
            "extra": "iterations: 6986747\ncpu: 100.29075863202132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 267.7835494078479,
            "unit": "ns/iter",
            "extra": "iterations: 2580977\ncpu: 267.7726535339142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1055.304733512384,
            "unit": "ns/iter",
            "extra": "iterations: 659130\ncpu: 1055.2653877080395 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 157.06296072702222,
            "unit": "ns/iter",
            "extra": "iterations: 4449218\ncpu: 157.05556661867374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 465.88442095952314,
            "unit": "ns/iter",
            "extra": "iterations: 1506216\ncpu: 465.84700667102163 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1308.6382458430844,
            "unit": "ns/iter",
            "extra": "iterations: 540613\ncpu: 1308.582694089853 ns\nthreads: 1"
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
        "date": 1729799313141,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5253331099.000036,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5253084761 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 695.562919072468,
            "unit": "ns/iter",
            "extra": "iterations: 1005196\ncpu: 695.5313749756274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1499.2104858856355,
            "unit": "ns/iter",
            "extra": "iterations: 469946\ncpu: 1499.1742008656327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 132.0315900849754,
            "unit": "ns/iter",
            "extra": "iterations: 5155605\ncpu: 132.03172935087147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 96.16967802473019,
            "unit": "ns/iter",
            "extra": "iterations: 7275621\ncpu: 96.1685063034483 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3128.5917438559727,
            "unit": "ns/iter",
            "extra": "iterations: 224124\ncpu: 3128.4485731113123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.700036992293274,
            "unit": "ns/iter",
            "extra": "iterations: 23556258\ncpu: 29.700070613931924 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1662.0472259058056,
            "unit": "ns/iter",
            "extra": "iterations: 420786\ncpu: 1661.996052625322 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1357.662632336335,
            "unit": "ns/iter",
            "extra": "iterations: 506569\ncpu: 1357.6483223410821 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1751.5607384276773,
            "unit": "ns/iter",
            "extra": "iterations: 398685\ncpu: 1751.4903344745865 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 81.11181564770699,
            "unit": "ns/iter",
            "extra": "iterations: 8630259\ncpu: 81.10886394023638 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2362.724576896389,
            "unit": "ns/iter",
            "extra": "iterations: 298272\ncpu: 2362.6582180023624 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.08511167766875,
            "unit": "ns/iter",
            "extra": "iterations: 7080556\ncpu: 98.0842123132704 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 109.68168268333815,
            "unit": "ns/iter",
            "extra": "iterations: 6385848\ncpu: 109.68179308370675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 267.477608399694,
            "unit": "ns/iter",
            "extra": "iterations: 2617812\ncpu: 267.47033438612107 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1076.238478359995,
            "unit": "ns/iter",
            "extra": "iterations: 647065\ncpu: 1076.2247656726925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 160.40360521311055,
            "unit": "ns/iter",
            "extra": "iterations: 4334612\ncpu: 160.39774701864886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 467.3546412925605,
            "unit": "ns/iter",
            "extra": "iterations: 1474363\ncpu: 467.3451022577209 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1346.3402828167318,
            "unit": "ns/iter",
            "extra": "iterations: 519559\ncpu: 1346.2696556117805 ns\nthreads: 1"
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
        "date": 1729800869368,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5218053548.9999895,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5217709362 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 682.0306239381524,
            "unit": "ns/iter",
            "extra": "iterations: 1027105\ncpu: 681.9903817039153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1408.3981640331117,
            "unit": "ns/iter",
            "extra": "iterations: 498375\ncpu: 1408.3565046400804 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.87883597669764,
            "unit": "ns/iter",
            "extra": "iterations: 5446592\ncpu: 128.8735328440243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 95.99651810432022,
            "unit": "ns/iter",
            "extra": "iterations: 7300908\ncpu: 95.99465217203124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3170.4730775831968,
            "unit": "ns/iter",
            "extra": "iterations: 221414\ncpu: 3170.2399577262513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 28.208350146432892,
            "unit": "ns/iter",
            "extra": "iterations: 24831828\ncpu: 28.20779984461873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1651.5435747153713,
            "unit": "ns/iter",
            "extra": "iterations: 425522\ncpu: 1651.4521011839543 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1350.358319814049,
            "unit": "ns/iter",
            "extra": "iterations: 519014\ncpu: 1350.3065023294162 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1731.4642168205464,
            "unit": "ns/iter",
            "extra": "iterations: 405386\ncpu: 1731.3883015200304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 76.17318279203576,
            "unit": "ns/iter",
            "extra": "iterations: 9131935\ncpu: 76.16814946667927 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2399.184625580368,
            "unit": "ns/iter",
            "extra": "iterations: 292733\ncpu: 2399.1366193767044 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.85598028388021,
            "unit": "ns/iter",
            "extra": "iterations: 7273643\ncpu: 98.85166099023563 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 100.61516280700357,
            "unit": "ns/iter",
            "extra": "iterations: 6961310\ncpu: 100.61232124413391 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 270.14876672576565,
            "unit": "ns/iter",
            "extra": "iterations: 2596219\ncpu: 270.1301689110198 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1044.3247560002426,
            "unit": "ns/iter",
            "extra": "iterations: 650513\ncpu: 1044.3046703140483 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 162.82645642860265,
            "unit": "ns/iter",
            "extra": "iterations: 4332739\ncpu: 162.81841440252887 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 412.31094207988474,
            "unit": "ns/iter",
            "extra": "iterations: 1681609\ncpu: 412.2904676414073 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1314.0391081770215,
            "unit": "ns/iter",
            "extra": "iterations: 538941\ncpu: 1313.9775114530157 ns\nthreads: 1"
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
        "date": 1729802511086,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5201793559.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5201619968 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 700.3851440441542,
            "unit": "ns/iter",
            "extra": "iterations: 1000353\ncpu: 700.3513549716953 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1362.578079698837,
            "unit": "ns/iter",
            "extra": "iterations: 513232\ncpu: 1362.5298422545739 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 126.61851505605331,
            "unit": "ns/iter",
            "extra": "iterations: 5558028\ncpu: 126.61751272213793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 93.96883692989753,
            "unit": "ns/iter",
            "extra": "iterations: 7489153\ncpu: 93.9676785879524 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3082.6906574301343,
            "unit": "ns/iter",
            "extra": "iterations: 227796\ncpu: 3082.647074575498 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.708033707388,
            "unit": "ns/iter",
            "extra": "iterations: 23432133\ncpu: 29.707904867217994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1657.338778400698,
            "unit": "ns/iter",
            "extra": "iterations: 423625\ncpu: 1657.3219616406009 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1351.6676095093378,
            "unit": "ns/iter",
            "extra": "iterations: 520412\ncpu: 1351.5724791127034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1738.7768993309235,
            "unit": "ns/iter",
            "extra": "iterations: 402984\ncpu: 1738.6861934965164 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 76.69981411141357,
            "unit": "ns/iter",
            "extra": "iterations: 8995173\ncpu: 76.69617371450208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2336.3720986089475,
            "unit": "ns/iter",
            "extra": "iterations: 299770\ncpu: 2336.380641825397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 96.31707206762232,
            "unit": "ns/iter",
            "extra": "iterations: 7208008\ncpu: 96.31626629715184 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 102.2162583769852,
            "unit": "ns/iter",
            "extra": "iterations: 6851508\ncpu: 102.21663216331369 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 265.6760139521187,
            "unit": "ns/iter",
            "extra": "iterations: 2615804\ncpu: 265.6739721324697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1050.9510741158726,
            "unit": "ns/iter",
            "extra": "iterations: 660264\ncpu: 1050.930589885258 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 159.77106406718138,
            "unit": "ns/iter",
            "extra": "iterations: 4399008\ncpu: 159.7699135805166 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 458.60903723791597,
            "unit": "ns/iter",
            "extra": "iterations: 1524603\ncpu: 458.593101286042 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1414.5444164762705,
            "unit": "ns/iter",
            "extra": "iterations: 491034\ncpu: 1414.5076919317164 ns\nthreads: 1"
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
        "date": 1729864514765,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5189496840.999993,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5189254845.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 680.7417230057822,
            "unit": "ns/iter",
            "extra": "iterations: 1029480\ncpu: 680.7134922485141 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1359.0008374755373,
            "unit": "ns/iter",
            "extra": "iterations: 517030\ncpu: 1358.941782875268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 127.73397535009953,
            "unit": "ns/iter",
            "extra": "iterations: 5474831\ncpu: 127.73177217707727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 95.00465440879304,
            "unit": "ns/iter",
            "extra": "iterations: 7386545\ncpu: 94.99921614232363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3076.5802422072843,
            "unit": "ns/iter",
            "extra": "iterations: 225592\ncpu: 3076.5076775772186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.042359580557456,
            "unit": "ns/iter",
            "extra": "iterations: 23328536\ncpu: 30.0408467552357 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1655.2409807088277,
            "unit": "ns/iter",
            "extra": "iterations: 420349\ncpu: 1655.2078273054046 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1352.7113624841418,
            "unit": "ns/iter",
            "extra": "iterations: 518751\ncpu: 1352.713103203654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1742.7629225952194,
            "unit": "ns/iter",
            "extra": "iterations: 393787\ncpu: 1742.6769827343244 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 77.68479295497083,
            "unit": "ns/iter",
            "extra": "iterations: 9016058\ncpu: 77.68042086685772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2325.6828659193693,
            "unit": "ns/iter",
            "extra": "iterations: 301125\ncpu: 2325.5849066002443 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.1992148037835,
            "unit": "ns/iter",
            "extra": "iterations: 7221125\ncpu: 98.19243940521704 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 102.82493742510735,
            "unit": "ns/iter",
            "extra": "iterations: 6810639\ncpu: 102.82187824079385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 267.1028973027541,
            "unit": "ns/iter",
            "extra": "iterations: 2624510\ncpu: 267.1003783563414 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1069.3759454214005,
            "unit": "ns/iter",
            "extra": "iterations: 673377\ncpu: 1069.3153864774101 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 159.87429648999688,
            "unit": "ns/iter",
            "extra": "iterations: 4387642\ncpu: 159.86959259666116 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 415.5420486696627,
            "unit": "ns/iter",
            "extra": "iterations: 1649529\ncpu: 415.53171238577704 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1327.55662076393,
            "unit": "ns/iter",
            "extra": "iterations: 527492\ncpu: 1327.4780963502715 ns\nthreads: 1"
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
        "date": 1729866249470,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5223858446.000009,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5223591578.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 700.6229838085674,
            "unit": "ns/iter",
            "extra": "iterations: 1001331\ncpu: 700.6080396991601 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1377.7314702045812,
            "unit": "ns/iter",
            "extra": "iterations: 508249\ncpu: 1377.681504538129 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 129.27330063378918,
            "unit": "ns/iter",
            "extra": "iterations: 5423522\ncpu: 129.2656244410919 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 99.23146092516103,
            "unit": "ns/iter",
            "extra": "iterations: 7072710\ncpu: 99.23007022767806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3205.334106031114,
            "unit": "ns/iter",
            "extra": "iterations: 219577\ncpu: 3205.093926048722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.53191386581212,
            "unit": "ns/iter",
            "extra": "iterations: 23744068\ncpu: 29.530148330100833 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1645.1466049346934,
            "unit": "ns/iter",
            "extra": "iterations: 429815\ncpu: 1645.0843409373817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1321.1905062060926,
            "unit": "ns/iter",
            "extra": "iterations: 529883\ncpu: 1321.1610751807486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1706.443702775439,
            "unit": "ns/iter",
            "extra": "iterations: 410935\ncpu: 1706.3894800880926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 80.77328469670536,
            "unit": "ns/iter",
            "extra": "iterations: 8665348\ncpu: 80.7705920177701 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2318.2821561044275,
            "unit": "ns/iter",
            "extra": "iterations: 303566\ncpu: 2318.1564239736954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 101.78026481853638,
            "unit": "ns/iter",
            "extra": "iterations: 6812514\ncpu: 101.77569367196895 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 109.27488542263292,
            "unit": "ns/iter",
            "extra": "iterations: 6403970\ncpu: 109.26951937626227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 270.9181773261869,
            "unit": "ns/iter",
            "extra": "iterations: 2588439\ncpu: 270.8973257627474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1054.204054129335,
            "unit": "ns/iter",
            "extra": "iterations: 681922\ncpu: 1054.1821777270723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 161.33434761278477,
            "unit": "ns/iter",
            "extra": "iterations: 4349886\ncpu: 161.33190754884137 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 412.5657283561887,
            "unit": "ns/iter",
            "extra": "iterations: 1697981\ncpu: 412.5368664313679 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1323.1360568948683,
            "unit": "ns/iter",
            "extra": "iterations: 528132\ncpu: 1323.101866578814 ns\nthreads: 1"
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
        "date": 1729867268741,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5338571682.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5338299568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 684.0088986738274,
            "unit": "ns/iter",
            "extra": "iterations: 1029704\ncpu: 683.9916403160526 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1347.1099185347377,
            "unit": "ns/iter",
            "extra": "iterations: 519976\ncpu: 1347.0761323599547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.7627144682923,
            "unit": "ns/iter",
            "extra": "iterations: 5428658\ncpu: 128.76291857029864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.42246505270009,
            "unit": "ns/iter",
            "extra": "iterations: 7618758\ncpu: 91.42070085439106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3106.8342059181937,
            "unit": "ns/iter",
            "extra": "iterations: 224429\ncpu: 3106.839361223371 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.129287486418725,
            "unit": "ns/iter",
            "extra": "iterations: 24011009\ncpu: 29.128009322723543 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1619.2681290280013,
            "unit": "ns/iter",
            "extra": "iterations: 430263\ncpu: 1619.2143502927286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1321.238520843734,
            "unit": "ns/iter",
            "extra": "iterations: 530113\ncpu: 1321.1981445465412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1700.3592586012173,
            "unit": "ns/iter",
            "extra": "iterations: 410899\ncpu: 1700.3406433211096 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 75.37039679306827,
            "unit": "ns/iter",
            "extra": "iterations: 9234486\ncpu: 75.37053562049903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2293.020926639282,
            "unit": "ns/iter",
            "extra": "iterations: 306786\ncpu: 2292.9295078654145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 93.44560147110744,
            "unit": "ns/iter",
            "extra": "iterations: 7471930\ncpu: 93.44574480756658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 99.5714345113407,
            "unit": "ns/iter",
            "extra": "iterations: 7022712\ncpu: 99.56897335388393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 264.5092646742513,
            "unit": "ns/iter",
            "extra": "iterations: 2645263\ncpu: 264.50588202382863 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1046.498729092508,
            "unit": "ns/iter",
            "extra": "iterations: 695566\ncpu: 1046.467407837647 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 155.3579962591739,
            "unit": "ns/iter",
            "extra": "iterations: 4498466\ncpu: 155.35056328090442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 396.7640019891704,
            "unit": "ns/iter",
            "extra": "iterations: 1763553\ncpu: 396.7515441838162 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1276.4625827073635,
            "unit": "ns/iter",
            "extra": "iterations: 549679\ncpu: 1276.420876547951 ns\nthreads: 1"
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
        "date": 1729867737802,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5242781809.999997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5242427748 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 690.4903254203285,
            "unit": "ns/iter",
            "extra": "iterations: 1033740\ncpu: 690.4783552924332 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1357.6468816777387,
            "unit": "ns/iter",
            "extra": "iterations: 482487\ncpu: 1357.5112054832562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 129.67320964662397,
            "unit": "ns/iter",
            "extra": "iterations: 5378589\ncpu: 129.66857683306898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 91.85537651141964,
            "unit": "ns/iter",
            "extra": "iterations: 7524898\ncpu: 91.85165991618766 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3100.81532568749,
            "unit": "ns/iter",
            "extra": "iterations: 227135\ncpu: 3100.6572875162333 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.262313530240338,
            "unit": "ns/iter",
            "extra": "iterations: 23911786\ncpu: 29.26114373054363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1622.803375832117,
            "unit": "ns/iter",
            "extra": "iterations: 415305\ncpu: 1622.6451932916775 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1339.908686857296,
            "unit": "ns/iter",
            "extra": "iterations: 531435\ncpu: 1339.8395871555338 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1711.4865095019122,
            "unit": "ns/iter",
            "extra": "iterations: 389867\ncpu: 1711.3733375740946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 75.55813111591479,
            "unit": "ns/iter",
            "extra": "iterations: 9242692\ncpu: 75.55728742232245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2332.4021432375125,
            "unit": "ns/iter",
            "extra": "iterations: 302253\ncpu: 2332.3324665098444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 93.39852070657429,
            "unit": "ns/iter",
            "extra": "iterations: 7481004\ncpu: 93.39565531578354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 98.9232801552403,
            "unit": "ns/iter",
            "extra": "iterations: 7076787\ncpu: 98.91890444067359 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 263.14676105048187,
            "unit": "ns/iter",
            "extra": "iterations: 2654410\ncpu: 263.13871368778774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1047.5105472529192,
            "unit": "ns/iter",
            "extra": "iterations: 667662\ncpu: 1047.4637960524938 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 157.5232128065567,
            "unit": "ns/iter",
            "extra": "iterations: 4492197\ncpu: 157.51464795510978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 383.07434877963937,
            "unit": "ns/iter",
            "extra": "iterations: 1822962\ncpu: 383.052770710525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1277.1550354031085,
            "unit": "ns/iter",
            "extra": "iterations: 549668\ncpu: 1277.0875819585647 ns\nthreads: 1"
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
        "date": 1729869168685,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5226695278.000023,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5226572599 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 706.7190484593056,
            "unit": "ns/iter",
            "extra": "iterations: 986106\ncpu: 706.7222134334445 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1467.0290324473128,
            "unit": "ns/iter",
            "extra": "iterations: 477328\ncpu: 1467.0321099956427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 134.41726175896085,
            "unit": "ns/iter",
            "extra": "iterations: 5205495\ncpu: 134.4149945394243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 93.02790739047187,
            "unit": "ns/iter",
            "extra": "iterations: 7565917\ncpu: 93.02039699880385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3108.773312486561,
            "unit": "ns/iter",
            "extra": "iterations: 226413\ncpu: 3108.5457327980284 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.014360175966925,
            "unit": "ns/iter",
            "extra": "iterations: 23667398\ncpu: 30.013464598009445 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1644.9529910813196,
            "unit": "ns/iter",
            "extra": "iterations: 425281\ncpu: 1644.8670196881583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1342.7839172668264,
            "unit": "ns/iter",
            "extra": "iterations: 523804\ncpu: 1342.7093951172585 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1733.789957402522,
            "unit": "ns/iter",
            "extra": "iterations: 403780\ncpu: 1733.7090618653729 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 77.73795762617566,
            "unit": "ns/iter",
            "extra": "iterations: 9013962\ncpu: 77.73610782916536 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2318.5473015620883,
            "unit": "ns/iter",
            "extra": "iterations: 302601\ncpu: 2318.465497470267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 95.14630532111616,
            "unit": "ns/iter",
            "extra": "iterations: 7434029\ncpu: 95.14786342641419 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 101.95863830230053,
            "unit": "ns/iter",
            "extra": "iterations: 6881028\ncpu: 101.95643877629922 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 272.5425111702631,
            "unit": "ns/iter",
            "extra": "iterations: 2555446\ncpu: 272.5375660452224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1053.2963106289071,
            "unit": "ns/iter",
            "extra": "iterations: 658947\ncpu: 1053.2426811261005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 159.6130273665375,
            "unit": "ns/iter",
            "extra": "iterations: 4401872\ncpu: 159.6034652984006 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 398.8383018407565,
            "unit": "ns/iter",
            "extra": "iterations: 1749989\ncpu: 398.82670462499925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1333.5440755182203,
            "unit": "ns/iter",
            "extra": "iterations: 523953\ncpu: 1333.523877141652 ns\nthreads: 1"
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
        "date": 1729870416472,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5177550006.999979,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5177286674 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 727.6298030571239,
            "unit": "ns/iter",
            "extra": "iterations: 992623\ncpu: 727.6073181862598 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1354.3054077654308,
            "unit": "ns/iter",
            "extra": "iterations: 517626\ncpu: 1354.2928968019385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.27799264341752,
            "unit": "ns/iter",
            "extra": "iterations: 5451986\ncpu: 128.27608618217306 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 92.78090546625498,
            "unit": "ns/iter",
            "extra": "iterations: 7561850\ncpu: 92.77728386572082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3107.361190134944,
            "unit": "ns/iter",
            "extra": "iterations: 225319\ncpu: 3107.1579582724994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.107626702489963,
            "unit": "ns/iter",
            "extra": "iterations: 24003021\ncpu: 29.106595998895305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1640.7635382818942,
            "unit": "ns/iter",
            "extra": "iterations: 427473\ncpu: 1640.6717055814054 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1334.0413423760917,
            "unit": "ns/iter",
            "extra": "iterations: 521523\ncpu: 1333.9727030255592 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1727.9926791265664,
            "unit": "ns/iter",
            "extra": "iterations: 402411\ncpu: 1727.9075845342218 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 74.93145364998593,
            "unit": "ns/iter",
            "extra": "iterations: 9346858\ncpu: 74.92764905597167 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2327.5667349322175,
            "unit": "ns/iter",
            "extra": "iterations: 295415\ncpu: 2327.4500346969508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 95.61632757538693,
            "unit": "ns/iter",
            "extra": "iterations: 7278227\ncpu: 95.61538998440159 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 99.19656695237543,
            "unit": "ns/iter",
            "extra": "iterations: 7070802\ncpu: 99.1930001716919 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 264.72630131081416,
            "unit": "ns/iter",
            "extra": "iterations: 2649271\ncpu: 264.7117920363757 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1010.2474791522834,
            "unit": "ns/iter",
            "extra": "iterations: 669616\ncpu: 1010.2017633987242 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 156.63237176892406,
            "unit": "ns/iter",
            "extra": "iterations: 4472434\ncpu: 156.62418763474193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 396.99726649933416,
            "unit": "ns/iter",
            "extra": "iterations: 1738796\ncpu: 396.97243552435094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1292.08991988886,
            "unit": "ns/iter",
            "extra": "iterations: 547365\ncpu: 1292.002996172568 ns\nthreads: 1"
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
        "date": 1729870546783,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5194063829.000015,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5193873205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 711.2555134887643,
            "unit": "ns/iter",
            "extra": "iterations: 1017958\ncpu: 711.2486890421804 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1389.0657471218642,
            "unit": "ns/iter",
            "extra": "iterations: 504235\ncpu: 1389.0647218062993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 128.8787973170381,
            "unit": "ns/iter",
            "extra": "iterations: 4828837\ncpu: 128.8756276097121 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 117.36218281125419,
            "unit": "ns/iter",
            "extra": "iterations: 5996469\ncpu: 117.35735663771449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3193.43283927645,
            "unit": "ns/iter",
            "extra": "iterations: 220285\ncpu: 3193.3379667249224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 35.57144318360481,
            "unit": "ns/iter",
            "extra": "iterations: 20296184\ncpu: 35.56962254579478 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1890.1843657538755,
            "unit": "ns/iter",
            "extra": "iterations: 423826\ncpu: 1890.1117982379587 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1531.0683653363844,
            "unit": "ns/iter",
            "extra": "iterations: 454748\ncpu: 1530.9486440841981 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1969.0449043674382,
            "unit": "ns/iter",
            "extra": "iterations: 401275\ncpu: 1968.9791614229634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 90.45090886240457,
            "unit": "ns/iter",
            "extra": "iterations: 7749963\ncpu: 90.4469663919686 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2846.797446035822,
            "unit": "ns/iter",
            "extra": "iterations: 245579\ncpu: 2846.6652563940684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 117.97713051603735,
            "unit": "ns/iter",
            "extra": "iterations: 5947139\ncpu: 117.97098487188559 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 102.27083443318287,
            "unit": "ns/iter",
            "extra": "iterations: 6856990\ncpu: 102.26668654905481 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 295.7621078887072,
            "unit": "ns/iter",
            "extra": "iterations: 2376653\ncpu: 295.74836124583555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1098.4562641439254,
            "unit": "ns/iter",
            "extra": "iterations: 643831\ncpu: 1098.4549780920777 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 183.1253581237946,
            "unit": "ns/iter",
            "extra": "iterations: 3817814\ncpu: 183.12516429558914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 422.52539129467823,
            "unit": "ns/iter",
            "extra": "iterations: 1440730\ncpu: 422.52144537838325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1492.2290885418051,
            "unit": "ns/iter",
            "extra": "iterations: 480801\ncpu: 1492.2295045143446 ns\nthreads: 1"
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
        "date": 1729870778247,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5204254778.000007,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5204002524 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 684.6213264911282,
            "unit": "ns/iter",
            "extra": "iterations: 1012928\ncpu: 684.6107482466671 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1417.1046068772187,
            "unit": "ns/iter",
            "extra": "iterations: 494413\ncpu: 1417.081051671377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 127.28687469200013,
            "unit": "ns/iter",
            "extra": "iterations: 5387645\ncpu: 127.27952194326099 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 96.89230193837938,
            "unit": "ns/iter",
            "extra": "iterations: 7219155\ncpu: 96.89150890928357 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3099.739170921817,
            "unit": "ns/iter",
            "extra": "iterations: 226589\ncpu: 3099.686904483443 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.090173004067523,
            "unit": "ns/iter",
            "extra": "iterations: 24072382\ncpu: 29.08992192795877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1655.675024731014,
            "unit": "ns/iter",
            "extra": "iterations: 422546\ncpu: 1655.6275624429052 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1354.0548265122995,
            "unit": "ns/iter",
            "extra": "iterations: 515973\ncpu: 1354.0195785438393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1750.5382590530721,
            "unit": "ns/iter",
            "extra": "iterations: 403068\ncpu: 1750.495715363166 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 78.29041607886238,
            "unit": "ns/iter",
            "extra": "iterations: 8937897\ncpu: 78.28855803552007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2303.510927713033,
            "unit": "ns/iter",
            "extra": "iterations: 304135\ncpu: 2303.49091686258 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 99.99726332142498,
            "unit": "ns/iter",
            "extra": "iterations: 6946742\ncpu: 99.99500269334914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 103.54289619725236,
            "unit": "ns/iter",
            "extra": "iterations: 6882708\ncpu: 103.53980148511286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 273.4746152340189,
            "unit": "ns/iter",
            "extra": "iterations: 2569159\ncpu: 273.4677577370655 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1072.0400143724946,
            "unit": "ns/iter",
            "extra": "iterations: 642894\ncpu: 1072.0319959433455 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 158.94828694650985,
            "unit": "ns/iter",
            "extra": "iterations: 4394171\ncpu: 158.9436282748216 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 429.0026319765408,
            "unit": "ns/iter",
            "extra": "iterations: 1634893\ncpu: 428.9990745571727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1304.4615062839805,
            "unit": "ns/iter",
            "extra": "iterations: 535490\ncpu: 1304.4213542736538 ns\nthreads: 1"
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
        "date": 1729870972571,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5200140610.000006,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5199904822 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 688.9629128417912,
            "unit": "ns/iter",
            "extra": "iterations: 1013100\ncpu: 688.9268769124469 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1403.9937936773872,
            "unit": "ns/iter",
            "extra": "iterations: 498685\ncpu: 1403.9393805709017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 127.16717103024146,
            "unit": "ns/iter",
            "extra": "iterations: 5501653\ncpu: 127.16199404070011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 96.91265003625834,
            "unit": "ns/iter",
            "extra": "iterations: 7230169\ncpu: 96.90784198820249 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3083.4826194648404,
            "unit": "ns/iter",
            "extra": "iterations: 226489\ncpu: 3083.485330413397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.212716525093274,
            "unit": "ns/iter",
            "extra": "iterations: 24062973\ncpu: 29.212953195766804 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1659.9015054141034,
            "unit": "ns/iter",
            "extra": "iterations: 421678\ncpu: 1659.8835390985575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1342.2513023753602,
            "unit": "ns/iter",
            "extra": "iterations: 512717\ncpu: 1342.2499449013803 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1737.85937110832,
            "unit": "ns/iter",
            "extra": "iterations: 405507\ncpu: 1737.8117739027937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 78.47022823283729,
            "unit": "ns/iter",
            "extra": "iterations: 8920364\ncpu: 78.46647255650112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2311.664564120867,
            "unit": "ns/iter",
            "extra": "iterations: 300588\ncpu: 2311.5337804569717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 100.23232159189547,
            "unit": "ns/iter",
            "extra": "iterations: 7056546\ncpu: 100.22797286377798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 101.84612070637911,
            "unit": "ns/iter",
            "extra": "iterations: 6882271\ncpu: 101.84312445702841 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 270.26585116182696,
            "unit": "ns/iter",
            "extra": "iterations: 2596592\ncpu: 270.25492645744845 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1073.5143068403113,
            "unit": "ns/iter",
            "extra": "iterations: 649165\ncpu: 1073.4628515092436 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 159.14242729758354,
            "unit": "ns/iter",
            "extra": "iterations: 4395934\ncpu: 159.1395030043678 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 421.3335170165149,
            "unit": "ns/iter",
            "extra": "iterations: 1651394\ncpu: 421.3340444497195 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1299.8345388922176,
            "unit": "ns/iter",
            "extra": "iterations: 539722\ncpu: 1299.8458317430075 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}