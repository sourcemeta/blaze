window.BENCHMARK_DATA = {
  "lastUpdate": 1729361283552,
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
      }
    ]
  }
}