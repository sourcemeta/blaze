window.BENCHMARK_DATA = {
  "lastUpdate": 1729019127801,
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
      }
    ]
  }
}