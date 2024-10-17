window.BENCHMARK_DATA = {
  "lastUpdate": 1729192090605,
  "repoUrl": "https://github.com/sourcemeta/blaze",
  "entries": {
    "Benchmark (windows/msvc)": [
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
          "id": "cc8419d9e982c44fc5fea7dd33fc30b7e2e0049b",
          "message": "Initial commit\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T14:23:02-04:00",
          "tree_id": "c0e2622aeac5a0f724bef315a9eb745d98fdcf48",
          "url": "https://github.com/sourcemeta/blaze/commit/cc8419d9e982c44fc5fea7dd33fc30b7e2e0049b"
        },
        "date": 1729017333901,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10598006100.000021,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10593750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2302.379908057789,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1997.6196625218447,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 540.3152678571896,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 544.0848214285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 405.7241202801615,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6699.936607142425,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 153.97375000004234,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 153.45982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5438.290178572304,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4484.458224237869,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4499.1729892254225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5494.741964284344,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 555.5683000000045,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8217.99888392657,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 405.949008662972,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 742.4290178571015,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1091.6507812499533,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1983.2177937699312,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 558.1450000000083,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4800.570871045494,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4865.378228016275 ns\nthreads: 1"
          }
        ]
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
          "id": "a39bf1e160169cf337421e363393d6d35ff41660",
          "message": "Bump JSON Toolkit to the latest version (#1)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-15T14:49:22-04:00",
          "tree_id": "0e7667765467f6f3cd2728d8254450e70fb67c1f",
          "url": "https://github.com/sourcemeta/blaze/commit/a39bf1e160169cf337421e363393d6d35ff41660"
        },
        "date": 1729018566607,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10453383100.00011,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10453125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2308.4314638036917,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2007.5191155342106,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 543.2509000002028,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 412.98718283273706,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 414.3415825980151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6651.550000000839,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 155.20406249999652,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 153.45982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5440.335999999206,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4495.9575000007135,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4492.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5537.38100000146,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 555.5010000000493,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8351.628348212918,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8544.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 411.0948030760594,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 417.13167780662155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 745.9688616072871,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1102.2681250000942,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1964.631835527084,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1949.6394527226034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 569.0002000001186,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4744.092732349813,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4708.436849189396 ns\nthreads: 1"
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
        "date": 1729019284263,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10579113699.999653,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10562500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2333.9079978685445,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2011.240659867947,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 543.7864000004993,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 531.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 409.8617183095661,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 417.13167780662155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6663.263392852059,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6556.919642857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 152.7461830355443,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 149.97209821428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5489.131999993333,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4484.013127654405,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5539.977999997064,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 554.4395535715855,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8366.146205359217,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 410.17395043861967,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 751.7871651785413,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1096.5295312502121,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1968.0806116953188,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 561.3563392858266,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4749.274440345773,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4813.068779171382 ns\nthreads: 1"
          }
        ]
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
        "date": 1729019832139,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10679422299.999943,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10671875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2321.501873323783,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2019.8302855626725,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 2008.9303651163975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 541.5579464285868,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 544.0848214285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 410.32971828879806,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6724.312500000655,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 157.1494642857171,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 156.94754464285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5425.583928572207,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4484.02154282356,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5497.370000000501,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 553.2224107143285,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8335.014508928294,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8544.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 407.6669237648483,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 741.9450892857275,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1094.178750000019,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1987.5591602221757,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 563.2158035714342,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4758.770666898485,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4813.068779171382 ns\nthreads: 1"
          }
        ]
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
        "date": 1729021558732,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10806245499.999931,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10796875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2290.9477779601107,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1993.7518680269677,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 541.7173214285395,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 544.0848214285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 405.65122742637766,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6704.932142856786,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 151.99223214286764,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 149.97209821428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5431.252000000768,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4468.314960221564,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5483.2196428569505,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 553.7835714286692,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8237.454241071568,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 406.91774076266995,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 748.5255357143013,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 753.3482142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1087.89406790455,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1088.1691570673406 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1959.032543562814,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1949.6394527226034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 558.9909000000262,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4773.746159594773,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4757.258711838135 ns\nthreads: 1"
          }
        ]
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
        "date": 1729022447418,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10374998099.999971,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10359375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2323.6919378438665,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2030.8178692163142,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 545.1176999999916,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 406.81675862424606,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6643.034821428679,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 153.25354910713835,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 153.45982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5474.897321428379,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4480.957499999506,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4492.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5565.884000000096,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 549.4798999999375,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8210.706473214455,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 407.4754639520348,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 740.6516964285815,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 739.3973214285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1089.2992187500283,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1968.9366394382184,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1949.6394527226034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 569.4797321428017,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4734.011458939125,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4649.139195659996 ns\nthreads: 1"
          }
        ]
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
        "date": 1729023735650,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10490124100.000002,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10500000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2326.5288766420335,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2010.2737837878547,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 549.6323999998367,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 412.63799081396326,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 414.3415825980151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6681.666071429504,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 157.56475446429315,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 156.94754464285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5429.7410000003765,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4494.378022178577,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5527.028999999857,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 559.2804999998862,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8273.170209060028,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8161.235887339789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 412.32475391401033,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 417.13167780662155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 755.1385714285582,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 753.3482142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1096.7196889642746,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1109.0954870109433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1997.5293750000847,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2001.953125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 568.5797321429422,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4851.240001107911,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4757.258711838135 ns\nthreads: 1"
          }
        ]
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
        "date": 1729024848805,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10457114800,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10437500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2323.4546875002593,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2294.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2007.3879546737394,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 545.01120000009,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 413.7994993838394,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 417.13167780662155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6685.363392855541,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 157.6179687499949,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 156.94754464285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5446.795535714192,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4479.963491128273,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5529.07199999936,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 555.9072999999444,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8262.373883928729,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 413.5596070292874,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 414.3415825980151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 745.7583928569989,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 753.3482142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1106.9420312498578,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1972.9145293877616,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 2008.9303651163975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 564.9814285713919,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4796.688947936208,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4865.378228016275 ns\nthreads: 1"
          }
        ]
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
        "date": 1729086315365,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10624198900.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10609375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2318.722188925743,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2020.324420004515,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 549.7890178572464,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 421.056387218616,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 423.75843674797005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6656.116071427829,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 158.19798380789646,
            "unit": "ns/iter",
            "extra": "iterations: 4072727\ncpu: 161.13282329014442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5423.832999999832,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4449.1600000000635,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4492.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5485.771428571493,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 592.9305357142312,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8256.607336573712,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8161.235887339789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 423.586854131972,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 423.75843674797005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 749.1715178569993,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 753.3482142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1100.5142187499928,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1979.2142671557099,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 2008.9303651163975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 575.004910714329,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4800.555804813052,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4813.068779171382 ns\nthreads: 1"
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
        "date": 1729105675977,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10470733800.000061,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10484375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2310.03391737298,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2008.2976655109776,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 541.7575999999826,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 407.24534264994116,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 404.92472844806025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6639.763392857593,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6696.428571428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 153.18462053571633,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 153.45982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5442.687500000431,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4472.435801997817,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5520.414000000074,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 552.6563999999325,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8172.433035714529,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 409.5982001603843,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 404.92472844806025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 745.0222098215013,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1086.624531250102,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1981.0308759203378,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 2008.9303651163975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 563.3554464286103,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4742.029256276576,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4649.139195659996 ns\nthreads: 1"
          }
        ]
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
        "date": 1729115966824,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10473699799.999964,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10484375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2273.5799402009243,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2249.5789625234793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1981.6789750881073,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 539.447142857138,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 544.0848214285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 414.4310803798702,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 414.3415825980151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6512.614285714083,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6556.919642857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 156.60359374999797,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 156.94754464285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5233.259821428605,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4328.470523004015,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4331.75029832576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5324.907000000394,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 542.199999999988,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 544.0848214285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7890.678571427857,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 408.5870219380312,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 758.1930803571676,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1061.5248437499504,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1992.969255546073,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 551.2042857143383,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 544.0848214285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 3062.4812500000025,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4761.149913280891,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4708.436849189396 ns\nthreads: 1"
          }
        ]
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
        "date": 1729170866556,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10337002700.000084,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10328125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2343.401071428681,
            "unit": "ns/iter",
            "extra": "iterations: 280000\ncpu: 2343.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2016.860554532312,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 560.9224107142755,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 406.23901311436407,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 398.9955179019858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6363.398214286268,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6277.901785714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 157.21227678570568,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 156.94754464285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5484.4439999988035,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4486.907944563114,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5539.380999998684,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 562.8058928570973,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8312.606026785423,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8544.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 414.39630582095987,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 414.3415825980151 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 777.8433035716046,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 784.7377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1108.0059375000671,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1123.046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1871.7699747945271,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1883.3722172966227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 559.4962500000277,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2127.8966382769904,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2131.0012622781946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4820.287719005802,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4865.378228016275 ns\nthreads: 1"
          }
        ]
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
        "date": 1729188191279,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10175385800.000072,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10171875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2348.14860697689,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2024.7731526487353,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 557.5206999999409,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 401.4863839285303,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 401.08816964285717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6348.350000000177,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6417.410714285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 154.54404017857723,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 153.45982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5290.939000000208,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4332.592500000487,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5403.561000000536,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 565.0835999999799,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7946.077008928703,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 404.6670578273946,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 778.4329241071118,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 784.7377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1096.0929687501064,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1098.6328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1858.7140702802797,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1883.3722172966227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 563.3744642857152,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2096.369281662193,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2085.6608098892966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4770.985911594205,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4757.258711838135 ns\nthreads: 1"
          }
        ]
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
        "date": 1729188729251,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10416919100.000086,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10437500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2304.464169124719,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1972.7919562409268,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 539.0879000000268,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 531.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 403.71724536980656,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6227.550892857283,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 154.79178571430808,
            "unit": "ns/iter",
            "extra": "iterations: 4480000\ncpu: 153.45982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5337.5312499994725,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4396.87750000033,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5437.395535714984,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 559.3499107142463,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8038.36160714206,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 411.2408789624817,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 417.13167780662155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 796.1214285714391,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 784.7377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1053.992343750032,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1802.6252702011254,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1799.6667854167727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 543.3361000000332,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2114.1571874998986,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2099.609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4728.053410833311,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4708.436849189396 ns\nthreads: 1"
          }
        ]
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
        "date": 1729189724986,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10154048900.000134,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10156250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2270.1192297778966,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1926.5850296708384,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1949.6394527226034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 503.2685000001038,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 371.68735811103704,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 377.022896295665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6191.362500000456,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.89521428572951,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5344.284000000243,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4354.3631250003045,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5381.428000000596,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 520.3540178570165,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8411.515127164894,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8370.498345989527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 378.0258610667959,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 747.4216964285217,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 753.3482142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1031.3703125000018,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1025.390625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1789.2096332231001,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1799.6667854167727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 506.7183000001023,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2131.9374999997367,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2148.4375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4691.003764289342,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4757.258711838135 ns\nthreads: 1"
          }
        ]
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
        "date": 1729190650356,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10607396200.00004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10593750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2354.225943944296,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1958.4363021749487,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 506.5523000000667,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 374.4595045607542,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6447.270535714113,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6417.410714285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 115.28026562501736,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 114.74609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5313.211999998657,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4345.387500001152,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5359.514285714795,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 515.6136000000515,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8011.633928570103,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 383.9508064374438,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 385.0445740991832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 730.4783482143965,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1048.3610937502165,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1730.630295205371,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1715.9613535369228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 520.1974107141691,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2051.3999680798615,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4762.175138783855,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4813.068779171382 ns\nthreads: 1"
          }
        ]
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
        "date": 1729191703764,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10223716900,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10234375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2285.4202171643547,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2249.5789625234793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1984.8474384454541,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 509.2826000000059,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 371.10614801682124,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6160.0044642854555,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.70625000001726,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5390.165999999681,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4548.890625000013,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4492.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5476.469000000179,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 521.6825999998491,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8092.595982141911,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 376.8201291391922,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 745.7744419644894,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1046.2634614894773,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1046.3164971801352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1753.8894058773965,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1803.1516943180618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 508.45758928557774,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2198.2324999996194,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2197.265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4622.975497713182,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4603.804919207409 ns\nthreads: 1"
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
        "date": 1729192084332,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10519977499.99998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10515625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2322.552206972939,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1992.7871364171601,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1967.0776491764725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 508.37133928567374,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 374.84843306278475,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6321.058928571281,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6556.919642857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 117.55162499998815,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5358.0589999990025,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4413.800625000164,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4492.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5492.572321428619,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 520.6627000000026,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 531.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8133.434151785325,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 381.9187889430721,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 385.0445740991832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 743.8309151785053,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1061.3320312499397,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1758.3360546856622,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 509.7210714285642,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2193.6712499996956,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2197.265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4699.488391714837,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4708.436849189396 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}