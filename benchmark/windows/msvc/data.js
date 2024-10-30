window.BENCHMARK_DATA = {
  "lastUpdate": 1730306466590,
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
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729195856541,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10205197199.99993,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10218750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2362.2546428571563,
            "unit": "ns/iter",
            "extra": "iterations: 280000\ncpu: 2343.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1972.5540095473903,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 506.97869999999057,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 365.02238906354677,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6348.625000001107,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6277.901785714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 120.26329687500949,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 119.62890625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5340.673000000606,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4373.959999999499,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5596.351785714302,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 528.4308928569966,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 530.1339285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8161.097098212825,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 370.0942522321274,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 366.2109375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 738.7994419644375,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1037.379999999999,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1025.390625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1761.7350033028167,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 513.4992999999213,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2187.447499999706,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2197.265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4742.038251819591,
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
          "id": "b4e3b8319ff13bafa2f21c10d6b65bf652f61ca9",
          "message": "Report all `dependentSchemas` steps (#22)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T16:20:47-04:00",
          "tree_id": "3e02f14df9fdb1114fcf5373ccbb318863144c71",
          "url": "https://github.com/sourcemeta/blaze/commit/b4e3b8319ff13bafa2f21c10d6b65bf652f61ca9"
        },
        "date": 1729196822015,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10336131000.000023,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10328125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2290.8225000001894,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2294.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1911.86206416292,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 512.5230357143503,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 361.30552729048316,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6156.561607143984,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.85382142859778,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5287.289000000328,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4341.92999999965,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4492.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5373.257142857873,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 541.4165000001958,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8103.972098213928,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 367.03796951071826,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 741.3452008927989,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1021.7861509884414,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1025.3901672365325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1719.2227326636596,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 510.7352999998511,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2173.4979614931826,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2131.0012622781946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4720.74625166618,
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
          "id": "28802968317fb9426f7048ee645e50ff975287e7",
          "message": "Always mark `ControlEvaluate` with `report` true (#23)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T16:24:02-04:00",
          "tree_id": "70bc6b86448b578459b7714241158197e96c3512",
          "url": "https://github.com/sourcemeta/blaze/commit/28802968317fb9426f7048ee645e50ff975287e7"
        },
        "date": 1729197097712,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10277257199.999895,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10281250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2236.9156250000797,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2294.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1913.5577383457037,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1904.2990003337056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 492.69214285711115,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 488.28125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 353.925966693095,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 352.95760504275023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6077.010714286806,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5998.883928571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.88679687500047,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5298.761999999897,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4344.52750000105,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5371.06964285832,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 510.746700000027,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8074.569196429491,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 358.57273061202693,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 352.9575262575846 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 732.4165178569534,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1006.1126562497691,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1736.6098415556173,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 505.6231249998941,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2149.328437500486,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2148.4375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4617.7055080485225,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4652.615498145427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729197686412,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10390422400.000034,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10390625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2277.8546006084966,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1977.128679831122,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 513.4539000000586,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 361.96831036278496,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 359.9329714405408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6082.616964286151,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5998.883928571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.75631250000151,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5265.067999999928,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4307.509999999581,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5338.359999999511,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 521.7964999999367,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7986.1718749997735,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 367.8427378851889,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 750.4892857143222,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1062.7301562498915,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1757.7148497443984,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 516.8226785714174,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2296.2697586276195,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4724.469474262394,
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
          "id": "41304832027085370a67b9dd5cdc50dedcfa4af8",
          "message": "Report evaluation of `ControlEvaluate` (#25)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T18:35:28-04:00",
          "tree_id": "851f22b2096627e30b867f1f94059fc429d4761e",
          "url": "https://github.com/sourcemeta/blaze/commit/41304832027085370a67b9dd5cdc50dedcfa4af8"
        },
        "date": 1729204962759,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10270589699.99996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10281250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2329.3433824292374,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1910.0382232484174,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 514.3987000000152,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 367.80318159835747,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6125.548214285459,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 114.82924999999764,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5251.405000000204,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4354.510000000289,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5333.876785714762,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 519.7491071428877,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8122.495535715249,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 374.46271884594734,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 732.2186383929007,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1013.8564062501132,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1711.845862603227,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 513.9122000000498,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2310.146417247214,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4648.679126516349,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4603.804919207409 ns\nthreads: 1"
          }
        ]
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
        "date": 1729207780453,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10664875899.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10671875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2357.020695289578,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1909.3602762145122,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1883.3722172966227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 510.2328571428164,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 367.7132865050696,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6038.375892856607,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5998.883928571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 115.72850000000302,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 114.74609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5271.617857142172,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4306.093125000388,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5353.8678571426,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 507.59709999999814,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8037.2823660709455,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 373.7628618280167,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 727.4863839285471,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1009.005156249998,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1726.1826833599116,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 509.206517857105,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2302.189394877925,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4662.819336650218,
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
        "date": 1729208815957,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10322577400,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10328125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2304.164839102101,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2249.5789625234793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1907.960453535918,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1883.3722172966227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 504.2519642858321,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 359.91412990686797,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6047.585937500242,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 5929.129464285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 113.18453124999905,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5270.812499998913,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4333.326302086947,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4331.75029832576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5318.083035713731,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 502.44535714288725,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8072.463169642877,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 367.4592083686504,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 717.4919642855976,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 725.4464285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1006.4459374998337,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1685.7158482146417,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1708.984375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 506.70880000006946,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2407.6925137361727,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2406.5263320018616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4648.6489925202095,
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
          "id": "dbb3acf5c0b1ac7580ca3b807db3aaf4ac05254c",
          "message": "Fix `ErrorTraceOutput` crashing on `$dynamicAnchor` (#26)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-17T20:25:02-04:00",
          "tree_id": "a2431c3bc0c7e36e0a8b8072d74e31f6e2c4fa51",
          "url": "https://github.com/sourcemeta/blaze/commit/dbb3acf5c0b1ac7580ca3b807db3aaf4ac05254c"
        },
        "date": 1729211531760,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10143698999.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10140625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2356.351388000531,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2406.5263320018616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1898.178034087453,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1883.3722172966227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 510.7278571429674,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 360.35220805143376,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 352.95760504275023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6255.38169642884,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 6277.901785714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 113.6831562499907,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5313.862000000427,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4368.318750000811,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5384.5079999996415,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 517.4279464284837,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8051.18526785569,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 368.83380913677814,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 719.914955357329,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 714.9832589285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1007.6593715807918,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1004.4638372929297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1708.4692577218077,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 507.0311000001766,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2348.6893429805,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4637.479852150933,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4652.615498145427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729211923869,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10208928000.000015,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10218750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2318.2875911966066,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1900.0136607263687,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1883.3722172966227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 506.6260000000966,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 363.23711666226836,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6018.361607142911,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5998.883928571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.9180156249987,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5264.041000000361,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4312.628125001083,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5327.0709999992505,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 510.7705000000351,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8023.853794641514,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 368.7365770113771,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 718.9564285714109,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 725.4464285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1000.3165625001031,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1692.2619471460641,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 504.5580000000882,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2325.790261394457,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4635.101417638165,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4603.804919207409 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729267175306,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10233485700.000074,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10218750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2284.776875000105,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2294.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2042.8541996140648,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 500.258400000007,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 360.98090897235807,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6087.406250000324,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.7261093749965,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5350.802000000385,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4383.154375000231,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5438.462499999528,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 512.4722321428163,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8080.5279017859275,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 368.62107703197705,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 729.0727678571482,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 714.9832589285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1006.5955774127726,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1025.3901672365325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 2044.884374999967,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2001.953125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 519.6826999999757,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 531.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2337.9640201293123,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4585.922722888975,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4652.615498145427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729274323829,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10258883599.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10250000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2282.6532142858014,
            "unit": "ns/iter",
            "extra": "iterations: 280000\ncpu: 2287.9464285714284 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1948.2245073432528,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 503.4173214285026,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 360.5974558302564,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6120.349107142431,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.84182812499675,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5393.728999999894,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4360.68499999962,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5450.3732142856215,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 533.5415178572183,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 530.1339285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8033.226190955367,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 7951.97342869005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 364.1497385447075,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 359.9329714405408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 741.46506696428,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1059.9551562501474,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1788.9815921996772,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1803.1516943180618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 525.8837500000319,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2321.1908245640834,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4686.697514950035,
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
          "id": "f3aee3d5514dcf53470ab6bfe4e332a4225e0032",
          "message": "Get rid of `AnnotationWhenArraySizeEqual` (#29)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-18T17:52:57Z",
          "url": "https://github.com/sourcemeta/blaze/commit/f3aee3d5514dcf53470ab6bfe4e332a4225e0032"
        },
        "date": 1729278465633,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10413667799.999985,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10390625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2291.2226660465067,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1922.426627166723,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 494.3748000000596,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 354.71561076508027,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 360.63051595883644 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6171.4500000005855,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.38129687500609,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5305.314285713792,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4342.093125000446,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5380.549000000202,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 504.573660714312,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8038.171875000951,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 359.9054982312162,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 352.9575262575846 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 734.4412946428085,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1053.2045744621646,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1067.242827123738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1786.6928452615807,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1799.6667854167727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 526.0329000000183,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 531.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2335.8877947683645,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4581.416725464398,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4652.615498145427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729280075326,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10248491899.999977,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10234375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2266.717113038756,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2249.5789625234793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1931.3055636654644,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1967.0776491764725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 493.72920000007525,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 355.7947681158596,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6127.108035714051,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.20118750000074,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5381.421999999247,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4406.800624999363,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5439.3179999999575,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 518.1524000000763,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 531.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8153.912946427612,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 365.1670631771099,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 736.78767857146,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 725.4464285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1057.7764062499994,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1794.6480616195495,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1803.1516943180618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 531.7542857143159,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 530.1339285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2346.2699260378267,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4626.514568113474,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4603.804919207409 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729280643954,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10243581800.00013,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10250000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2291.346884657442,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2249.5789625234793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1950.7455810229344,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 496.8550999999479,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 356.43650921589295,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 352.95760504275023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6109.058928570578,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.74435937501903,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5300.807000000987,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4317.899545580312,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4331.75029832576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5366.011000000981,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 518.9454999999725,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8052.210937500145,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 363.64819034139936,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 742.8502232141707,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 1059.5258662830897,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1046.3164971801352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1791.49194766124,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1803.1516943180618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 536.6976785712804,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 530.1339285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2334.264917114513,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4654.7373989677035,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4603.804919207409 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729281682629,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10442603599.999985,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10453125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2230.922733345066,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2197.263172697352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1934.6811023937498,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 517.7152678572027,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 370.3287731555484,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6187.607142856727,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6277.901785714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 117.68112499996874,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5411.530999999742,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4456.171229195896,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5519.516964286351,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 522.6541964286671,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8128.406249997714,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 386.4614955356568,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 735.6231026786222,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 799.464397321259,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 802.1763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1711.7059073395992,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 509.3669642856671,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2330.627755996044,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4685.574464504278,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4753.759313322502 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729286770207,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10357893199.999922,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10343750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2241.7642391023483,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2249.5789625234793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1971.407222552673,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 500.9717948380872,
            "unit": "ns/iter",
            "extra": "iterations: 1445161\ncpu: 497.3494302710909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 362.0275157093399,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6177.556000000095,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 6093.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.62103124999112,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5303.5892857146955,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4331.4643749994275,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5371.165999999904,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 513.8740178571157,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7926.703124999181,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 367.18616657392437,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 761.9925223213896,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 767.2991071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 814.8462053571797,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 819.6149553571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1759.8302319913348,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1757.8140694768476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 502.2920999999769,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2292.25558900032,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4679.9855000230245,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4753.759313322502 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729360342564,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10604398200.000105,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10609375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2229.0762500002616,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2246.09375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1940.958607998712,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 503.04049999999734,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 366.1986234909883,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6128.115178572306,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.79704687500349,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5248.310000000629,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4325.190624999919,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5344.2199999994955,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 516.3215000000037,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7923.176339286187,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 368.6303448874476,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 747.2186383928405,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 803.3561383928857,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 802.1763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1699.31250046035,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 511.4124107142816,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2302.622653322921,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4684.4910368104365,
            "unit": "ns/iter",
            "extra": "iterations: 149333\ncpu: 4603.804919207409 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729361475653,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10313580399.999865,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10312500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2139.5121875002587,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2197.265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1957.9867388245898,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1949.6394527226034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 495.7004999998844,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 370.6676123807224,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6191.045535715034,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.02426562498147,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5291.340000001128,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4336.374999999748,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5386.526785713387,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 546.6625999999906,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 546.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7941.733258929012,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 377.287807627205,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 813.4352678571385,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 819.6149553571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 796.8391741070795,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 802.1763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1788.3174002835142,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1757.8140694768476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 571.2524000000485,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2332.520499419529,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4729.241359914209,
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
          "id": "5e631d57f77a8429b7d55a1bff6ff0b62415aeae",
          "message": "Fix failed `if` incorrectly showing up on error traces (#34)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T14:22:28-04:00",
          "tree_id": "fd4856558b2355016002438323f4b429e0a50ac0",
          "url": "https://github.com/sourcemeta/blaze/commit/5e631d57f77a8429b7d55a1bff6ff0b62415aeae"
        },
        "date": 1729362533011,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10227107100.000011,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10218750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2172.087187500082,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2197.265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1965.4643587773144,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1949.6394527226034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 490.7968999999639,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 363.85397074035353,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 359.9329714405408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6208.005357142912,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6277.901785714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.75271875000448,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5289.794000000256,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4331.215722671601,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4331.75029832576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5355.3629999998975,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 513.448482142869,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7928.520089286144,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 367.9142557295933,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 752.7159598213881,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 800.5505580356446,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 802.1763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1761.2785527152914,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 571.53059999996,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2316.327883562694,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4726.788452653283,
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
          "id": "bfb48266713d223adc8d9145274151a680a468d4",
          "message": "Reduce unnecessary instructions in array/object `items` (#37)\n\nSigned-off-by: Juan Cruz Viotti <jv@jviotti.com>",
          "timestamp": "2024-10-19T14:41:21-04:00",
          "tree_id": "fc7db4361a4c3f6a0ad4652e809f8327533e191b",
          "url": "https://github.com/sourcemeta/blaze/commit/bfb48266713d223adc8d9145274151a680a468d4"
        },
        "date": 1729363666147,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10321426900.000006,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10312500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2190.432812499665,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2197.265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2077.89093749966,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2050.78125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 492.78490000006065,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 358.6658151189675,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 352.95760504275023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6166.243749999824,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.14448437499878,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5310.832000000119,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4361.550625000632,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5411.7937499995605,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 491.58986438191977,
            "unit": "ns/iter",
            "extra": "iterations: 1445161\ncpu: 497.3494302710909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8011.139508928368,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 366.95018447322406,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 709.6013392856752,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 714.9832589285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 812.184933035555,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 819.6149553571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1938.7789272086961,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1904.2990003337056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 584.7677678571829,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2340.3620085242223,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4118.381688222761,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729363825180,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10189223699.999956,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10203125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2195.799375000007,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2197.265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1908.476882568541,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1883.3722172966227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 501.26960000000054,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 373.7777912400843,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 377.022896295665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6335.10178571482,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6277.901785714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 120.4568437500164,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 119.62890625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5294.549000000188,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4338.203125000462,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4394.53125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5389.4062500004575,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 518.2453000001033,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8001.155133927946,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 391.71194196426944,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 749.6540178571565,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 817.016629464286,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 819.6149553571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1831.5104745629496,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1841.5195013566977 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 584.016250000019,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2592.3017857142636,
            "unit": "ns/iter",
            "extra": "iterations: 280000\ncpu: 2622.7678571428573 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4795.354464286155,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 4882.8125 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729366607946,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10251646899.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10250000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2182.946249999418,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2148.4375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 2094.05687499995,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2099.609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 497.0756199482971,
            "unit": "ns/iter",
            "extra": "iterations: 1445161\ncpu: 497.3494302710909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 367.5439181939386,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6167.270535714562,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 113.85798214283632,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 111.60714285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5358.899000000292,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4347.427166327591,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4331.75029832576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5471.530357143349,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 508.8146999999026,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8095.2399553549785,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 368.28767045932716,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 726.1901785715302,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 808.6367187498666,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 802.1763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1802.1766090863161,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1799.6667854167727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 574.2264285714782,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2373.369002936733,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4144.593372949559,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729368257418,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10736130200.000048,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10734375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2084.4187499999834,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2099.609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1915.302960091887,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1925.2249332365475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 505.0791964285801,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 502.23214285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 358.3615784982403,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6111.390178570478,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5998.883928571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.13325000000405,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5470.197321429282,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4446.484079154773,
            "unit": "ns/iter",
            "extra": "iterations: 154483\ncpu: 4450.327867791278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5506.004999999732,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 508.4488999999621,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8337.142857142155,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 364.3803635034598,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 359.9329714405408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 737.4982142856876,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 802.601450892837,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 802.1763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1767.8129176902266,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1757.8140694768476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 580.2208000000064,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2351.3930229989296,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4109.713968877677,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729368952801,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10393139299.999802,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10390625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2080.102812499973,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2099.609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1970.8262844039898,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 504.86799999998766,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 364.89686450436744,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6220.081250000525,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.87348214284805,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5281.039999999848,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4313.043125000604,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5377.172999999403,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 522.113392857193,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8145.974794756608,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8161.235887339789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 370.40564814190066,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 750.5611607143692,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 842.5238839286919,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 837.0535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1758.959469446674,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 578.3365178570779,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2285.044547941187,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2249.5789625234793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4079.2401431966873,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729369153609,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10388068999.999973,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10375000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2088.2808351349427,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2085.6608098892966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1963.0878124999638,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 1953.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 504.10240000007894,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 361.27981048574003,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 359.9329714405408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6224.2044642865885,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6277.901785714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 114.73434375000481,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 114.74609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5299.019642857315,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4317.826249999967,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5381.968000000369,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 518.9083928571441,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8341.478794641993,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 367.9180057289142,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 368.30350566008826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 748.2482142856993,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 832.5154017857019,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 837.0535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1780.8803922675772,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 580.221874999966,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2302.0852655298518,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4091.606889987163,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729370007661,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10373047000.000042,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10390625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2067.4552761777736,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1950.2412837514967,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1949.6394527226034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 487.4150892856984,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 488.28125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 354.88615984173373,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 360.63051595883644 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6021.076000000676,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 6093.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.48524999999643,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5260.712000000467,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4290.443330159852,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5333.129000000554,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 513.9791000000287,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 515.625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8047.489955357788,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 362.6962059239047,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 735.5023437500512,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 732.421875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 787.3251116070941,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 784.7377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1760.8266614523527,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1757.8140694768476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 829.9907366070717,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 819.6149553571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2275.48468749994,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2294.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4040.9917125148495,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729372657532,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10750448200.000051,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10765625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 2090.6556249997266,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2099.609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1965.0569476081037,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 491.52170000002116,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 359.1664245163771,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 352.95760504275023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 6019.511607143661,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 6138.392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.57564062500803,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5288.927678571602,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4329.8243750001575,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5379.841999999826,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 511.0966071428484,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 516.1830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7962.577008928662,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 370.4372464480901,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 369.0011325446934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 739.9901785714036,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 749.8604910714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 801.3459821429235,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 802.1763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1793.5382085162005,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1799.6667854167727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 571.1901785714092,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2294.462394573105,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4025.077187361885,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 3989.9482322352997 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729373243036,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10371158799.999989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10375000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1692.8249601619057,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1691.5759208198554,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 384.82751116067755,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 311.4026339285861,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 313.8950892857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5544.742999999245,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 117.9878035714158,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 119.97767857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5105.17899999968,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4134.752841628136,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5191.317999999683,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 455.9888867886869,
            "unit": "ns/iter",
            "extra": "iterations: 1544828\ncpu: 455.1477575497078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7973.271205357386,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 319.3834249037109,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 314.9414554596024 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 685.6531250000281,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 683.59375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 591.4383928571607,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1626.4508928571786,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 402.37449776782597,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 401.08816964285717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2302.882474461314,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3468.423544411283,
            "unit": "ns/iter",
            "extra": "iterations: 213333\ncpu: 3588.8727951137425 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729375919196,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10506345100.00009,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10500000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1672.7703530557521,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1701.2662268306867,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 382.1248883928747,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 309.6663839285847,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 313.8950892857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5638.831999999638,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 117.15565624999867,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5145.420000000058,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4116.901130533827,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5177.494999999226,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 452.56309208997783,
            "unit": "ns/iter",
            "extra": "iterations: 1493333\ncpu: 449.9163950706239 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7838.79910714269,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 319.8887946428641,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 320.8705357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 673.0641071429083,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 683.59375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 587.4166964285824,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1621.768690779827,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 393.39882812499434,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2285.979033505568,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3449.449999017736,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3452.852147950264 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729378243266,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10508922400.000074,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10500000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1619.457142856971,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1755.9077080974914,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 385.34218750000247,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 301.6197767857014,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 299.94419642857144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5670.012500000813,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.0501874999924,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5061.994000000141,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4142.594656081156,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4171.309515518722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5155.979999999545,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 457.3673574016118,
            "unit": "ns/iter",
            "extra": "iterations: 1544828\ncpu: 455.1477575497078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7823.1886160714685,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7672.991071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 309.48254464289806,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 313.8950892857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 689.5328125000282,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 680.1060267857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 611.3494642856868,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1650.8758928571256,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1674.107142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 396.8489955357463,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 401.08816964285717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2293.0246729636997,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3444.016775029708,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3452.852147950264 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729378900789,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10451481299.999954,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10437500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1668.5235701850738,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1790.7973275912266,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 397.42716082915877,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 398.9955179019858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 313.48892857145927,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 306.91964285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5728.399107142528,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5719.866071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 113.43906249999593,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5167.703571428563,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4204.825645167125,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5283.7750000003325,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 452.45567791363993,
            "unit": "ns/iter",
            "extra": "iterations: 1544828\ncpu: 445.0333629374921 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7826.021205357136,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 319.15790924341997,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 314.9414554596024 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 670.7016071427827,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 683.59375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 633.4830357143264,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 627.7901785714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1713.8307719882896,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 405.8098970620674,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2295.6744467921626,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3508.235282562747,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3529.5821956824925 ns\nthreads: 1"
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
        "date": 1729537684573,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10490136500.000063,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10484375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1713.701620289331,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1775.7705519394897,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1803.1516943180618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 386.50434169564016,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 385.0445740991832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 314.34679911668593,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 314.9414554596024 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5713.03303571418,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5719.866071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.29087499999255,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 111.60714285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5139.829464285738,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4190.272772199469,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5237.474000000475,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 452.7803750001169,
            "unit": "ns/iter",
            "extra": "iterations: 1600000\ncpu: 449.21875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7999.803571429201,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 320.7034375000108,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 320.8705357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 668.4662500000676,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 669.6428571428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 639.3667857143522,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 641.7410714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1740.0549508564761,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 417.4933563619407,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 417.13167780662155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2332.9396953793416,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2354.210542175734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3516.6429315053556,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3529.5821956824925 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729623175100,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10369467199.999918,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10359375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1680.8848119074557,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1712.178808809175,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 392.7696986607237,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 311.052053571359,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 306.91964285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5583.076785713713,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 115.08357142856443,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5120.755000000372,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4139.028241504536,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5169.0642857136845,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 466.4269791132445,
            "unit": "ns/iter",
            "extra": "iterations: 1493333\ncpu: 470.8427390273971 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7777.779017855226,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7672.991071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 316.90665178568827,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 320.8705357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 682.7444642857878,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 683.59375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 596.4431249998776,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 613.8392857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1636.4480336281267,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 403.55648644835594,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2322.0305557693714,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3490.4358757782566,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3529.5821956824925 ns\nthreads: 1"
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
        "date": 1729624064236,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10741663199.999949,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10750000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1685.5977678572133,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1674.107142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1710.9805953255116,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 395.80221893740725,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 398.9955179019858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 309.84843749999004,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 306.91964285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5558.016964286593,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 114.759124999994,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5093.8350000001265,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4131.932353692016,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5172.895000000608,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 463.26351858555023,
            "unit": "ns/iter",
            "extra": "iterations: 1493333\ncpu: 460.3795670490105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7887.2779017861,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 315.91115873606304,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 314.9414554596024 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 674.8682142857984,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 669.6428571428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 592.7400000000489,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 593.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1620.9527761479844,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 405.92336699696847,
            "unit": "ns/iter",
            "extra": "iterations: 1659259\ncpu: 404.92472844806025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2308.0815758016465,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3473.5616492176464,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3452.852147950264 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729624331699,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10304944900.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10312500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1620.1178571425396,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1704.477831822902,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 384.57762276777885,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 303.78812457721335,
            "unit": "ns/iter",
            "extra": "iterations: 2357895\ncpu: 304.8269749077037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5491.190000000189,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.60290625003222,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5036.683000000721,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4118.457065255206,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4171.309515518722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5116.466964285645,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 459.98708928285646,
            "unit": "ns/iter",
            "extra": "iterations: 1493333\ncpu: 460.3795670490105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7959.191964285343,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 309.9174390496384,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 307.6172355651931 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 678.9528571429416,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 683.59375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 594.2955357143984,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1576.2281249998011,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 393.4574601135339,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 389.92743794966793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2288.4249999997055,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2294.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3474.4662044039665,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3452.852147950264 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729627604155,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10352918000.000046,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10359375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1627.0518792062956,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1700.3859818842718,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 389.4642857143233,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 321.2828571427906,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 320.8705357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5513.614999999845,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.2115000000079,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5041.9860000010885,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4115.2215799613505,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5151.599999999235,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 463.4923356009349,
            "unit": "ns/iter",
            "extra": "iterations: 1493333\ncpu: 460.3795670490105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7946.545758927519,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 305.73515784207,
            "unit": "ns/iter",
            "extra": "iterations: 2357895\ncpu: 304.8269749077037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 680.8570312499184,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 680.1060267857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 590.055178571447,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1592.4700892858216,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 397.279343871456,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 398.9955179019858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2274.913197641316,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3423.7767388869715,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3452.852147950264 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729627768284,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10281547799.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10281250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1606.1301339284232,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1695.4973690868073,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 387.70000000003836,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 303.795122344296,
            "unit": "ns/iter",
            "extra": "iterations: 2357895\ncpu: 304.8269749077037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5485.5794642857545,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.97390625000025,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5086.899107142122,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4207.831201860953,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5156.064285714024,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 461.4936521191152,
            "unit": "ns/iter",
            "extra": "iterations: 1493333\ncpu: 460.3795670490105 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7919.770089285397,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 309.31669642854894,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 306.91964285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 678.1442857142597,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 683.59375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 591.7513392857035,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1590.2511160713775,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 406.81411830359843,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 401.08816964285717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2285.311250000177,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2246.09375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3522.801960361069,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3452.852147950264 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729631397243,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10663928300.00018,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10671875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1678.8068445485874,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1688.0569053190366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1753.7681113161254,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 391.2732700893175,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 300.12795311069345,
            "unit": "ns/iter",
            "extra": "iterations: 2357895\ncpu: 298.2003015401449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5679.183035713972,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5719.866071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 115.88371428570912,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5027.0732142852885,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4096.5972783051375,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4049.244844087123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5102.687000000969,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 203.53536144932718,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 204.03179892715184 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7891.921874999699,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 303.19000634035854,
            "unit": "ns/iter",
            "extra": "iterations: 2357895\ncpu: 304.8269749077037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 209.968852233521,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 213.09987887946968 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 590.8474999998248,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1631.7825892860428,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 408.9219460302804,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 417.13167780662155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2273.5956250002687,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2246.09375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3522.479816928256,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3529.5821956824925 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729632885222,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10522878100.00007,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10515625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1711.2816219094993,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1766.4072992809222,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1764.7867646517202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 400.6880713978561,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 398.9955179019858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 314.5348660714222,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 313.8950892857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5477.733999999828,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.98962499999965,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5112.726999999495,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4090.8187663954604,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5122.744999999895,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 205.0890645049718,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 204.03179892715184 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7798.422991070554,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 319.23696428570736,
            "unit": "ns/iter",
            "extra": "iterations: 2240000\ncpu: 320.8705357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 217.212781249998,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 214.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 599.0643750000199,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1651.407532539706,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 397.865959821418,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 401.08816964285717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2317.201096873767,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3653.547015262688,
            "unit": "ns/iter",
            "extra": "iterations: 203636\ncpu: 3683.0422911469486 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729633621630,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10365719100.000092,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10375000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1517.6495535715871,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1623.5303571429579,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 341.9367559041674,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 260.5715714285647,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 4964.016999999785,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.51064285713953,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4990.629999999783,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4059.128421199495,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 3989.9482322352997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5082.6799999993,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 196.20623454433837,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 194.96371897483397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7736.583705356839,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 263.2271389833559,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 210.88471875000184,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 209.9609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 569.102410714249,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1609.775990871384,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1590.403205717148 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 387.47148437501266,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2317.0896014623518,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2301.8947523496067 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3017.915178571481,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729634460722,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10312050300.00001,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10296875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1466.3883928570494,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1595.0508928571796,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 333.2500364453018,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 329.58989524842116 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 253.81422338453427,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 4946.0017857145185,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 4882.8125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.97642857143006,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 111.60714285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4943.31000000102,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 3986.7193080356246,
            "unit": "ns/iter",
            "extra": "iterations: 179200\ncpu: 4010.8816964285716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5013.003571428547,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 195.57660674791043,
            "unit": "ns/iter",
            "extra": "iterations: 3733333\ncpu: 196.70760684889348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7708.162946428334,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7672.991071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 257.7803463295016,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 215.10143749999602,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 214.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 573.7156250000502,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1513.5036100431093,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1538.0852508547987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 380.55245535715903,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2273.907060371827,
            "unit": "ns/iter",
            "extra": "iterations: 298667\ncpu: 2249.5789625234793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 2996.0163536040664,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 2982.0093388580467 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729687233927,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10271067099.999983,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10265625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1520.433205163642,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1538.0852508547987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1828.265918094535,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1841.5195013566977 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 339.2444592569145,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 265.0498578147327,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 266.81083780405527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5165.243999999802,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 118.77435714284599,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5311.724000000595,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4301.92749999918,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4296.875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5391.956000000846,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 203.5112476111228,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 204.03179892715184 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8335.340401785123,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8544.921875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 268.6994316383015,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 266.81083780405527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 216.87704612155466,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 213.09987887946968 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 597.083499999826,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 593.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1560.1064732143145,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 399.931529017802,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2167.0040624997,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2148.4375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3066.7424107144416,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729695350627,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10325226300.000053,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10312500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1475.1873325056358,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1679.3700892857746,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1674.107142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 339.56359551623126,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 336.91407754080706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 278.69961255806066,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 276.2276662398363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5033.872000000201,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 119.81842857143275,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4980.218000000605,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4041.6086310558944,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5126.603999999588,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 209.1905937500016,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 209.9609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7868.158482142411,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 283.88786981640436,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 284.59822699099226 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 219.5337812499787,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 219.7265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 597.2805000000108,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 593.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1520.6723214285591,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 388.78510044642366,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2123.475624999927,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2148.4375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3095.267857143012,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729697045359,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10180560600.000034,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10187500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1482.8805210351093,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1646.0441964285217,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 342.6515593480013,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 264.1548153640388,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 4989.222000001519,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 124.12517857143257,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 125.55803571428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4929.826999998568,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4002.611022123732,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 3989.9482322352997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5047.724107143381,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.24054641786347,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 213.09987887946968 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7731.6484375015,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7672.991071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 262.19048045494964,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 220.76675000000992,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 219.7265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 600.1508928570892,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1533.324330357593,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 386.0960379463866,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2182.1881250005504,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2246.09375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3051.208919838935,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3048.276213054892 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729697879691,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10259417799.999937,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10265625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1487.7778849207768,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1595.4689732140537,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 344.153648365467,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 259.97860714288174,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 262.2767857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 4895.436491461806,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4973.497744194415 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.2705156250039,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4908.62949431259,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 4973.497744194415 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 3996.667968749281,
            "unit": "ns/iter",
            "extra": "iterations: 179200\ncpu: 4010.8816964285716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 4962.5399999990805,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 196.72378542175008,
            "unit": "ns/iter",
            "extra": "iterations: 3733333\ncpu: 196.70760684889348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7702.912946427886,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7672.991071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 261.05425049344166,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 209.66862500003458,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 209.9609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 579.0984999998727,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1504.9975446430608,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 387.933872767857,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2068.980746630382,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2085.6608098892966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 2998.76249999999,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 2999.441964285714 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729702562788,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10453657399.999998,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10437500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1455.488591299845,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1622.601792900396,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 342.44879599128876,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 249.50257142856054,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5270.376999999371,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 114.74594642856621,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4987.889000000223,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4015.413097476715,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 3989.9482322352997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5077.305000000933,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 193.34674940593686,
            "unit": "ns/iter",
            "extra": "iterations: 3733333\ncpu: 196.70760684889348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7851.446428570291,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 250.26250000000314,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 205.16204441239222,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 208.56583890331078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 564.3676999999343,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1525.0183035716093,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 390.97979910713525,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2120.6247551612646,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2131.0012622781946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3187.7604496256226,
            "unit": "ns/iter",
            "extra": "iterations: 213333\ncpu: 3222.6612854082587 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729703476754,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10656109199.999947,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10656250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1436.9321428571168,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1429.966517857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1645.436160714299,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 342.87396555818776,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 260.2185714285708,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 262.2767857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5063.820999999962,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 115.16239062499876,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 114.74609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5085.791071428909,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4120.877379072559,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5191.31399999992,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 213.3839056524997,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 213.09987887946968 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7936.138392857624,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 265.2484314842894,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 240.7541918801308,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 240.6528749271345 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 585.5612500000567,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1546.9793763484422,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1538.0852508547987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 388.58478175959993,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 389.92743794966793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2072.060705425054,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2085.6608098892966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3092.8866071425277,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729705533639,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10391035999.999985,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10390625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1472.0090080317727,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1637.8694196428662,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 345.560371328473,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 263.0540653149336,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5481.8809999994755,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 109.73629687500265,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5046.004000000721,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4071.528890126864,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5127.219642857434,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.75840624998676,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 209.9609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7768.62834821479,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 263.08169031616615,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 266.81083780405527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 235.0323286794618,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 235.4212906895881 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 577.8393750000126,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1500.191964285794,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 383.7693638392941,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2068.692598987065,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3132.36383928585,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729706469030,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10282774899.999935,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10296875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1467.6655055063943,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1620.3040712250934,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 346.3436792243822,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 352.9575262575846 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 263.3632142857323,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 267.85714285714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5481.736607142653,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.3944062499961,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4990.225892857073,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 4882.8125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4050.368236442519,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4049.244844087123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5111.176999999998,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.98597044706645,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 208.56583890331078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7735.959821428193,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 258.99341781221096,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 235.21463892691125,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 235.4212906895881 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 576.2925892856938,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1542.3462886073714,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1534.5971866536697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 384.5561634721348,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 385.0445740991832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2069.2807916079473,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2085.6608098892966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3048.4156250000383,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 2999.441964285714 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729708041550,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10300998499.999992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10296875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1495.6422340884694,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1634.3136020658196,
            "unit": "ns/iter",
            "extra": "iterations: 373333\ncpu: 1632.2559216570728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 360.4581723418912,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 247.34775000000906,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5463.854999999285,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.47544642857636,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 111.60714285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5008.340000000544,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4046.7871485944434,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 3989.9482322352997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5103.628999999046,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 208.05582106893107,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 208.56583890331078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7715.664062499477,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7672.991071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 253.59174999997387,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 232.37776424358623,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 235.4212906895881 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 569.6507999999767,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1505.5397321430366,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 386.8768973214515,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2021.6740420469562,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 1994.9799051115012 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3112.8607142854034,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729709694675,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10444747599.999914,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10453125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1502.2508025665916,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1589.832863951042,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1572.9621163200113 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 336.517489014744,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 259.44433524308613,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5318.99732142855,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 115.27673214284765,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5014.907691881787,
            "unit": "ns/iter",
            "extra": "iterations: 144516\ncpu: 5081.617260372554 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4024.0464749172193,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 3989.9482322352997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5047.045999999682,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.40234375000466,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 209.9609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7744.258928571922,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7672.991071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 261.1122326389393,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 242.77232781559303,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 245.8844591646809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 562.3703999999634,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1478.9118303572784,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1464.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 376.8042719992555,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2030.2990293516596,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3059.87678571386,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
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
        "date": 1729710522350,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 11131506700.000046,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 11140625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1495.1888191121127,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1443.9167661085867 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1600.7308035713866,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 344.7836928957328,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 257.4255357142923,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5346.594999999752,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.0861607142749,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5042.4571428574645,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4067.2713977295903,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5061.3580357148985,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 210.90168924546467,
            "unit": "ns/iter",
            "extra": "iterations: 3446154\ncpu: 208.56583890331078 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7770.219866071975,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 258.12182625543096,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 239.03135714285943,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 239.95535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 565.3926999999612,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 593.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1490.138839285647,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1464.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 390.8434151786036,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2049.2140504621875,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2131.0012622781946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3040.0222232588444,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3048.276213054892 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729717460047,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10203994099.999931,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10218750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1448.4000899998086,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1443.9167661085867 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1594.0765625000859,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 330.5150258008453,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 329.9385571538291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 249.78717857140154,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5319.747999999436,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 114.46760937500855,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 114.74609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4996.883999999682,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4027.7990575017884,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5027.007999999569,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 211.30346874997485,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 209.9609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7722.410714285287,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 252.28674999997986,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 241.56352214693587,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 240.6528749271345 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 557.064196428517,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1500.8227678572032,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 375.07664730771836,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2008.3498977119975,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3000.861363337552,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 2982.0093388580467 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729719800964,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10215908200.000057,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10203125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1474.6729910713543,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1464.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1570.86160714291,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 339.0784260574442,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 254.99124575853935,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5491.7009999996935,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.77998214285675,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 4968.454999999494,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4053.9081180211188,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5083.6455357148625,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 229.11449451844177,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 230.1897064520417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7660.454241071233,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7672.991071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 261.1664580877941,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 277.771447420907,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 276.2276662398363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 569.9858928571595,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1511.690178571509,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 379.9417892961173,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2030.3550000001283,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2001.953125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3000.1092189209126,
            "unit": "ns/iter",
            "extra": "iterations: 213333\ncpu: 3002.934379584968 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729720794757,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10525444100.000072,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10515625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1501.7950892856545,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1647.661887726348,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 339.7530107583773,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 246.36853571430655,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5481.631249999453,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.06889062499903,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5137.113392857527,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4115.454302759934,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5145.532999999887,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 218.08978124997935,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 214.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7911.463169643084,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 251.44771428573773,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 261.0996344241058,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 577.499285714213,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1511.5267857141694,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 391.50351562497065,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2028.109049228868,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3118.6616071430253,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729722877194,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10174725999.999964,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10171875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1472.2765625000886,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1653.2654017856275,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1674.107142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 340.58301953872524,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 256.01523017927764,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5442.019999999276,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 113.49034374999789,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5016.271428571275,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4059.3489565194104,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5350.958999999875,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 227.92443749999336,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 224.609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7764.188616070962,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 257.89369231667285,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 265.5279828360352,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 266.81083780405527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 576.9845000000942,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1540.21540178587,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 378.46911098767004,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2052.9190545969877,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3101.1611607141276,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729777908407,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10245454099.99996,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10234375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1495.7312295842517,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1641.5187500002608,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 331.2254111289819,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 252.2019999999462,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5424.5035714290325,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.27421874999277,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5111.331999999038,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4133.955498233982,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5215.103571428261,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 221.52871875000812,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 219.7265625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7970.1886160726035,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 255.05366763636258,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 271.37700765072333,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 272.73996753303425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 582.7202678570335,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1535.7291055387582,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1534.5971866536697 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 382.7871280737443,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2061.8993749998535,
            "unit": "ns/iter",
            "extra": "iterations: 320000\ncpu: 2050.78125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3054.691964285285,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 2999.441964285714 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729788866867,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10331853900.000055,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10328125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1503.4808035712745,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1620.1075892853721,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 340.3020285174908,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 252.22917857141576,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5495.775605083148,
            "unit": "ns/iter",
            "extra": "iterations: 129486\ncpu: 5430.123719938835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.94067187499947,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5220.699107143544,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4175.621662668021,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5236.171999999897,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 223.67421875003402,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 224.609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8112.309151785878,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 258.0031298216187,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 271.22563934041847,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 272.73996753303425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 590.8692857141367,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1528.013392857527,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 392.6849888392171,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2081.9381048416976,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2040.320357500399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3131.237946428809,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
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
        "date": 1729796899377,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10388959800.000067,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10406250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1511.5343749998137,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1628.5931058527844,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 349.0507879039596,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 344.9358412917786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 256.484071428531,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5457.433999999921,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.39860937500856,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5204.337000000123,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4167.98523574007,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4171.309515518722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5218.306000001576,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 225.58631249999908,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 224.609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8014.726562500638,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 264.2088890271816,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 273.9275769610696,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 272.73996753303425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 595.4957999999806,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 609.375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1522.259151785578,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 402.2305245535865,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 409.80747767857144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 2127.7895622654596,
            "unit": "ns/iter",
            "extra": "iterations: 344615\ncpu: 2131.0012622781946 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3175.507142857319,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3208.7053571428573 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729797268638,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10170729899.99997,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10171875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1464.8357142854302,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1464.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1576.5591517857201,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 347.63762266235466,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 352.95760504275023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 255.79789285716615,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5321.082000000388,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 117.92881249998997,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5053.82900000086,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4053.226199596705,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5069.936607142722,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 254.8607859312882,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7642.562499999681,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7498.604910714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 257.6702857143281,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 262.2767857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 336.8029487852083,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 580.1613392857722,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1580.0136160711377,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 382.9137173369053,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 385.0445740991832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1213.4555357139984,
            "unit": "ns/iter",
            "extra": "iterations: 560000\ncpu: 1199.7767857142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3078.721229574274,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3114.5430872517377 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729798025751,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10553227499.999935,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10546875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1471.1031249997777,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1578.3921875000472,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 341.1968096077216,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 251.18578571428836,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5331.300000000283,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.25368749999863,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5004.559999999856,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4034.142930102296,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 3989.9482322352997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5102.781999999024,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 257.494107142853,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7725.969866072546,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 254.69842857144644,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 364.9899526803461,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 360.63051595883644 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 582.6364285713988,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1624.8990235050471,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 384.9772321428294,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1200.8319642857502,
            "unit": "ns/iter",
            "extra": "iterations: 560000\ncpu: 1199.7767857142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3049.3967063770865,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3048.276213054892 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729798585053,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10264926900.000092,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10265625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1524.1933035713575,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1621.6665479910064,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 355.5303194432659,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 258.89392857140234,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 262.2767857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5434.893999999986,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.45805357141317,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 108.81696428571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5084.087000000181,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4108.911368015331,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5160.382999999911,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 237.61717857143236,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 239.95535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7802.890625000661,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 262.44574609134366,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 278.3737241797207,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 276.2276662398363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 570.2738392857651,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1558.3345982140681,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 385.33091517857696,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1246.4948214285089,
            "unit": "ns/iter",
            "extra": "iterations: 560000\ncpu: 1227.6785714285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3055.9326346856183,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3048.276213054892 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729799403247,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10244934399.99992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10234375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1410.3429641328444,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1381.1377762777784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1625.5734375002971,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 342.61733167552234,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 246.484023829875,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 251.1160434022273 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5275.590000001102,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.25326562499305,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5064.676785713524,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4092.751352229208,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5120.217999999568,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 233.3987685938855,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 235.4212906895881 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8020.612723212496,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 256.2649285714055,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 287.0363845073256,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 288.783469250738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 558.4826785715385,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1657.4766802614558,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 382.01428571430336,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 374.9302455357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1213.5767857143621,
            "unit": "ns/iter",
            "extra": "iterations: 560000\ncpu: 1227.6785714285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3047.1429964924023,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3048.276213054892 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729801016379,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10526288699.999895,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10531250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1506.3218944994817,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1615.1850446429908,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 347.3922208658376,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 344.9358412917786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 261.4491210469174,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5549.103999999261,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.25235937498466,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5109.626999999364,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4145.6275689160175,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5210.273214286432,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 230.3952533040885,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 230.1897064520417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8045.267857144418,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 264.13580420249366,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 266.81083780405527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 277.18556351849037,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 276.2276662398363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 580.4384821429056,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1711.2199924861645,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1726.4218349853784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 405.11956227151785,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 408.0635978543037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1037.4289062500707,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3152.4352678573564,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729802670810,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10790883200.000053,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10796875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1496.3671874999666,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1616.4003015180779,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 346.91096483735265,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 256.95129272101514,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5515.216999999666,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.88964062497797,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5106.966999999258,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4130.757712933563,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4171.309515518722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5172.80892857132,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 251.4431428571535,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8019.159598214388,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 258.9997169196709,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 334.77333355835594,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 597.2112499999785,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1695.9270089285742,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1708.984375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 392.8005725446624,
            "unit": "ns/iter",
            "extra": "iterations: 1858370\ncpu: 386.76366923701954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1040.0734375000554,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1025.390625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3157.5147321427316,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729864806372,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10976096099.99995,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10953125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1505.6265625000367,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1620.8074191021615,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 352.7735023560045,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 352.95760504275023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 260.3613866232353,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5545.189000000619,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 120.67100000001219,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 119.62890625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5131.949999999961,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4138.334842259594,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5165.811000000531,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 260.8739290568699,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8049.906250000254,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 265.1252573716481,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 344.03333588692016,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 587.660892857197,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1656.1167410714515,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 397.0186383928415,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1032.0257812500345,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1025.390625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3202.40625000017,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3208.7053571428573 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729866375354,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10468326199.999865,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10484375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1528.1551213594976,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1538.0852508547987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1796.5634844444269,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1803.1516943180618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 334.23619284943567,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 329.58989524842116 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 253.68414285716358,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5469.184821427981,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.43739285716136,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 111.60714285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5068.796000000475,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4076.030278557979,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4049.244844087123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5155.311000000893,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 256.352194480047,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7925.435267855465,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 254.64635714286032,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 337.2355370680885,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 576.8307000000732,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 562.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1526.879910714334,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 385.6027901785503,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1029.4636029178753,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1046.3164971801352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3220.21383928574,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3208.7053571428573 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729867482967,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10495353400,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10500000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1492.7685267855293,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1643.9795910851417,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1649.691975652695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 334.23965460010015,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 245.64246428570058,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5470.556999999872,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.05589062499155,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5269.055357143567,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4212.7460434170935,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5309.283035713414,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 251.29775000002448,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8245.414062499583,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 251.85507142858955,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 334.78042236061845,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 329.9385571538291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 575.3500000000348,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1515.9770089286135,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 385.69525669642144,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 986.7523273427859,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 983.537507349327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3088.554173434621,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3114.5430872517377 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729867881041,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10260559199.999989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10250000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1492.5258928570884,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1642.0604910710576,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 343.11807712177614,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 256.43681501954103,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5469.173000001319,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 118.41787499999867,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 119.62890625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5277.115999999751,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4240.548196184162,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5353.9580357145105,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 258.68335753048797,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8220.910714286892,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 257.2284260165493,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 257.39396172348387 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 343.27070209456065,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 576.5387000001283,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1550.5986607143386,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 392.39186641111013,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 389.92743794966793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 993.9637080518266,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1004.4638372929297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3080.67187500021,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729869290342,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10477814599.999989,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10484375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1475.7437499999883,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1464.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1600.9278788429265,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 335.96847125563045,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 247.4729285714261,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5268.855000000485,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 114.28012500000965,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5356.5500000001975,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4307.259260151668,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5389.081000000715,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 255.95674999997138,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8426.643631054152,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8370.498345989527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 249.74210714284646,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 339.98474732412853,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 561.0621428572366,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1531.6263392859091,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 382.6280691964382,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 991.3001378124354,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1004.4638372929297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 2990.440181687939,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 2982.0093388580467 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729869843798,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10523753099.999794,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10515625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1464.9877232143028,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1429.966517857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1593.4270089285212,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 337.02572453534475,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 251.16789285708103,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5289.083000000119,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.57494642857688,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 111.60714285714286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5235.572321428857,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4237.31422441342,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5288.756250000201,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 252.6740714285682,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8276.73660714266,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 253.4155714285394,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 336.9953014293864,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 567.2619642857463,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 558.0357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1512.5987890187503,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1538.0852508547987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 380.6913504464303,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 983.5009375002812,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 976.5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3011.359821428528,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 2999.441964285714 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729869897912,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10417091000.000027,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10437500000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1502.7988839284894,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1611.1323660713392,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 332.57821293244666,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 329.9385571538291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 247.29085255763164,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 243.09431888813924 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5492.589000000407,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 114.21987500000341,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 114.74609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5242.066999999224,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4238.725000000442,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4199.21875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5324.653999999782,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 256.42729046553825,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8193.482142857532,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 248.77917857143726,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 342.014345175998,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 576.1984821428915,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1521.9948290212599,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1496.232256987328 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 386.1029017856613,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1009.0585937499341,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3053.9187500003045,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870148818,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10225100399.999973,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10218750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1488.4119024949196,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1621.2924107138958,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 333.80742715740973,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 249.16135714282257,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5478.9290000007895,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.79357812501678,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5192.336607141864,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4210.06291961525,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5295.122321429955,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 257.2471989842805,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8212.371651785994,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 251.96085714282748,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 343.07972445011114,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 578.9119000000937,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1564.6633928569593,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 383.26278870306516,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 376.67403987963576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 995.9690625002792,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 976.5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3036.6323280552797,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3048.276213054892 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870269838,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10252318099.99991,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10265625000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1476.3615507313214,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1614.8507266624122,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 331.04152047528163,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 247.3910714285564,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5512.568000001465,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.52842187502898,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5209.835999999086,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4236.468666755883,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5270.4607142857185,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 256.48060714282957,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8339.6426801664,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8370.498345989527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 252.2093571428741,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 341.67162648726475,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 576.6773999998804,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1531.9892857143761,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 379.35719866068393,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 374.9302455357143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1023.7119090572031,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1025.3901672365325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3077.192320253048,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3114.5430872517377 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870470855,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10752754600.000004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10750000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1498.0343749998935,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1611.9912946427817,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 346.9230824519605,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 344.9358412917786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 253.45361845772175,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 249.02344861711825 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5492.120535714256,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 116.9851249999887,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 117.1875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5215.33482142798,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4229.340625000333,
            "unit": "ns/iter",
            "extra": "iterations: 160000\ncpu: 4199.21875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5328.211999999439,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 256.9058571428481,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 262.2767857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8287.14559309899,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8161.235887339789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 257.0886967450348,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 345.2055722847176,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 582.1517857143022,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1525.795312500173,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 388.51065848215836,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 999.6642412214254,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1004.4638372929297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3147.325892857314,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870798088,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10295449700.000063,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10296875000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1454.3396855628412,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1443.9167661085867 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1605.0408482146038,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 334.22629745958375,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 329.9385571538291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 251.95410714283233,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5425.861999999597,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.38590624998557,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5187.691964284877,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4190.135964224558,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5319.259999998849,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 252.1705357142829,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8273.115298592997,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8161.235887339789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 252.1281496485306,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 249.02344861711825 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 337.27570316504676,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 580.1833035714513,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 571.9866071428571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1523.52956538868,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1538.0852508547987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 389.5500000000242,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 981.0324999996567,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 976.5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3132.030206296762,
            "unit": "ns/iter",
            "extra": "iterations: 213333\ncpu: 3149.4189834671615 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870830040,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10595734900.000025,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10593750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1476.3565284122617,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1629.7203125001301,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 339.80133434390586,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 252.09189285711935,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5449.209821429285,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.08054687500635,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5175.791964286906,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4182.409025709643,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5228.345000000445,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 250.51603571431053,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8254.286830357165,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 254.84532142854732,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 262.2767857142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 335.1989133573429,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 579.1476000001694,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1540.0040178568424,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 390.8626674107296,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1011.3462895775759,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1025.3901672365325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3161.5450892853605,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729871992497,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10480968599.999983,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10500000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1494.3201587855765,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1630.995535714267,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 340.0717160586413,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 248.08493882979633,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 245.8844591646809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5752.301785714207,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5719.866071428572 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.3179531249896,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5205.994642857093,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4282.918891554161,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4237.581813579547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5240.423999999848,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 250.10178571428855,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8315.279017857081,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8370.535714285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 252.1239642857154,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 334.3467572594823,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 329.9385571538291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 583.7574000000815,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 593.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1544.3127232142979,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 391.03297991070565,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1004.3213373564793,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1004.4638372929297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 4033.7232142860303,
            "unit": "ns/iter",
            "extra": "iterations: 179200\ncpu: 4010.8816964285716 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729872259020,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10254906600.000027,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10250000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1534.0098214287375,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1628.6881696428527,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 342.71751022903226,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 248.58671428570946,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5608.49600000097,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.29371428571865,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5090.106999999762,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4094.259697750368,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5173.063000000866,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 254.57928571427146,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8050.3493303574205,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 251.23917857143854,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 337.161185328397,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 595.6729464285461,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1555.8986607141023,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 390.602008928566,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1020.6157812499229,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1025.390625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3135.681250000236,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
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
        "date": 1729883292355,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10240499499.99994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10234375000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1491.930941102263,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1603.1988371435568,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 338.53603776144365,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 246.24747251703542,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 251.1160434022273 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5505.886607143192,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.36595312500219,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5075.277000000824,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4184.6460988462295,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4171.309515518722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5160.667000000103,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 252.75549999999416,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7929.982142856419,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 249.37396770381912,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 245.8844591646809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 336.7273729058534,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 593.3549107142865,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1555.7692384957409,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1538.0852508547987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 395.04698660713143,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 401.08816964285717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1015.018750000074,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1025.390625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3091.4160541842316,
            "unit": "ns/iter",
            "extra": "iterations: 235789\ncpu: 3114.5430872517377 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729904811469,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10284827199.999994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10281250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1480.542731900409,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1475.3062610239906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1619.129241071501,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 339.8253946740524,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 247.15760714286714,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5532.2840000008,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.91168750000813,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5080.750892857517,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4094.797687861655,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4171.309515518722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5111.663000000135,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 251.62160714285977,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7960.203124999867,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 250.39550000002464,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 336.0621676674906,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 589.8987500000683,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1532.1988918755794,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 392.02968749999354,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1007.8871875000673,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3070.206250000191,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
          }
        ]
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
        "date": 1730121088689,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10400970899.999947,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10406250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1481.9220982144848,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1464.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1595.7970982142401,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 341.7266755845333,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 247.57678571428903,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5523.639000000458,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 110.98812500000221,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 109.86328125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5064.275999999381,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4108.028880344241,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4049.244844087123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5176.576999999725,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 250.99199999999655,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7958.23772321442,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 249.7816428571095,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 335.0735211052378,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 593.627455357166,
            "unit": "ns/iter",
            "extra": "iterations: 896000\ncpu: 592.9129464285714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1560.4796874999495,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 393.66333705353236,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1041.537812499982,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3119.1790178571714,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
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
        "date": 1730121274325,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10383396299.999958,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10375000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1477.7995535715554,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1612.4633928572712,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 345.4340677795603,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 247.93192857146096,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5531.019642857262,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.14060937501336,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5167.364999999791,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4187.7649325618495,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4261.990157160433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5225.843999999142,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 252.5120357142896,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8061.715401786224,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 250.98025000001405,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 336.64852135135186,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 591.9381249999641,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1552.7613839288229,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 390.59920131258804,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 389.92743794966793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1036.393593749807,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3113.662053570871,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
          }
        ]
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
        "date": 1730123792417,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10590884100.00004,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10578125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1498.730133928713,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1607.5472717318457,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 344.20972871253207,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 252.7355357142775,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5547.616071429015,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 115.65692187499364,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 114.74609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5087.332999999035,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4094.7477772358297,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5158.236999999417,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 255.1613975518429,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7936.035714285948,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 255.15171428570022,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 344.04497427771986,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 593.6058928570885,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1559.6332589285262,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 392.1784598214398,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1046.5134374999964,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1049.8046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3116.8946428568997,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
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
        "date": 1730142578929,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10225975300.000072,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10218750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1500.9482142855595,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1603.8263392858757,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 342.62622006675304,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 251.11524999999799,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 245.53571428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5525.649107142832,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.20810937500049,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5097.719000000325,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4111.822740258053,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4049.244844087123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5171.134000000848,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5312.5 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 252.18507142856845,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7938.502232143207,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 253.24146428573613,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 335.5527793655363,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 589.9994642856907,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 585.9375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1528.4221078473013,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1538.0852508547987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 391.76004464287166,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1013.2563780105307,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1004.4638372929297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3102.213392856815,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730150841878,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10584095000.000048,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10578125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1477.156696428545,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1464.84375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1597.267410714309,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 342.0152782115601,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 248.96260614255232,
            "unit": "ns/iter",
            "extra": "iterations: 2986667\ncpu: 245.8844591646809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5520.725000000733,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5440.848214285715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 114.56324999999521,
            "unit": "ns/iter",
            "extra": "iterations: 5600000\ncpu: 114.39732142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5132.945000000291,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4159.395152055536,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5187.694999999621,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 256.87236414608964,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8047.958268042133,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 7951.97342869005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 251.26371428573944,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 340.82531413830674,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 593.6106999999993,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 593.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1523.994866071275,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 391.35719866071184,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1020.7876562500218,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1025.390625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3065.526339285997,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3069.1964285714284 ns\nthreads: 1"
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
        "date": 1730228864055,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10282172699.999933,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10281250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1505.3449529710335,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1607.766071428429,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 341.9242786572914,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 344.9358412917786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 249.442071428559,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5534.860999999864,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 112.18446875000511,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5078.158999999687,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4119.926526916734,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5109.086607142947,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 252.63592857141606,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7909.611607142304,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 251.99585714286093,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 336.71152136118576,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 336.9141151428305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 589.6726785714179,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1568.406473214117,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 391.1163504464505,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1024.6653461316362,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 1004.4638372929297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3100.310714285927,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730244448587,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 1474601300.0000176,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 1468750000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1524.517857142931,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1627.7973214283545,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 346.83637110062125,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 254.28721428568224,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5405.956999999262,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5468.75 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 115.10470312501299,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 114.74609375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5149.817999999868,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4141.306365487931,
            "unit": "ns/iter",
            "extra": "iterations: 165926\ncpu: 4143.413328833335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5218.399107143057,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 259.53582408642797,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7979.831473215222,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 254.47263189607756,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 344.63352327970233,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 577.2637000000032,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1547.9093750000925,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 385.24894906268935,
            "unit": "ns/iter",
            "extra": "iterations: 1866667\ncpu: 385.0445740991832 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1016.0681250001246,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3186.0660714286837,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730302926360,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10482093200.000008,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10500000000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1512.3064900418085,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1614.4060267860384,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1604.3526785714287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 340.91955072856797,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 253.75646428569456,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 251.11607142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5516.06785714398,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5580.357142857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.52741912822883,
            "unit": "ns/iter",
            "extra": "iterations: 7466667\ncpu: 110.90959326296459 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5072.766000000684,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4083.7569932917627,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5147.728571427836,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5161.830357142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 253.7132500000488,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7921.065848212854,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 255.946892857131,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 341.89437644743924,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 593.5024107141577,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1620.8075892859395,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1639.2299107142858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 390.21646205356876,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1024.410000000131,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1025.390625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3133.6642857147417,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730303834489,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 10287936199.99999,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 10281250000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1482.0515624998723,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1499.720982142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1610.1718012242259,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1611.3270459863531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 340.78573378826474,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 255.0346428571564,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5546.991999999591,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.4508593750152,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5001.154999999926,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4049.0302249460374,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5068.201785714369,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 258.1524110782426,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 7947.345982142196,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7847.377232142857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 262.5444068100005,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 343.38246993175306,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 571.6945000000351,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 578.125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1575.1974719658617,
            "unit": "ns/iter",
            "extra": "iterations: 407273\ncpu: 1572.9621163200113 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 390.3116071428363,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 383.64955357142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 986.2800954108425,
            "unit": "ns/iter",
            "extra": "iterations: 746667\ncpu: 983.537507349327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3238.2927160817526,
            "unit": "ns/iter",
            "extra": "iterations: 213333\ncpu: 3295.9035873493553 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730306460859,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 32453490600.000122,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 32453125000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 1501.0372093583094,
            "unit": "ns/iter",
            "extra": "iterations: 497778\ncpu: 1506.6957559393948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1602.812276785873,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1569.4754464285713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 356.07934178932413,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 360.97936879372185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 256.994999999977,
            "unit": "ns/iter",
            "extra": "iterations: 2800000\ncpu: 256.69642857142856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 5325.060714286321,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 111.99332812498852,
            "unit": "ns/iter",
            "extra": "iterations: 6400000\ncpu: 112.3046875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 5043.084821427409,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5022.321428571428 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 4085.3402047500113,
            "unit": "ns/iter",
            "extra": "iterations: 172308\ncpu: 4080.628873877011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 5117.543999999725,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5156.25 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 258.8445160198024,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 254.95257834609725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 8075.040178572936,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8021.763392857143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 260.9752080792214,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 260.88170807507623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 343.65290291910145,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 345.28453655633274 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 591.2385714284239,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 599.8883928571429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1542.7138392856778,
            "unit": "ns/iter",
            "extra": "iterations: 448000\ncpu: 1534.5982142857142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 388.921540178571,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 392.36886160714283 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 1011.9662500002846,
            "unit": "ns/iter",
            "extra": "iterations: 640000\ncpu: 1000.9765625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 3113.1651785715676,
            "unit": "ns/iter",
            "extra": "iterations: 224000\ncpu: 3138.9508928571427 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}