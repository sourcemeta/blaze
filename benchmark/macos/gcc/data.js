window.BENCHMARK_DATA = {
  "lastUpdate": 1729019266831,
  "repoUrl": "https://github.com/sourcemeta/blaze",
  "entries": {
    "Benchmark (macos/gcc)": [
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729018563470,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3693786859.512329,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3691525000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 777.533176029031,
            "unit": "ns/iter",
            "extra": "iterations: 916506\ncpu: 777.0238274490281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1042.8096423954166,
            "unit": "ns/iter",
            "extra": "iterations: 644010\ncpu: 1041.6391049828417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 173.0308734600692,
            "unit": "ns/iter",
            "extra": "iterations: 4051723\ncpu: 172.9237166509161 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 124.00964354450275,
            "unit": "ns/iter",
            "extra": "iterations: 5657206\ncpu: 123.93803584313545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2532.793535486147,
            "unit": "ns/iter",
            "extra": "iterations: 277164\ncpu: 2531.49398911835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.766382931837846,
            "unit": "ns/iter",
            "extra": "iterations: 27158837\ncpu: 25.75224410382521 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1623.5775769683542,
            "unit": "ns/iter",
            "extra": "iterations: 445616\ncpu: 1621.9458008689112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1425.5997059320673,
            "unit": "ns/iter",
            "extra": "iterations: 538797\ncpu: 1409.5605580580423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1580.6432801022174,
            "unit": "ns/iter",
            "extra": "iterations: 419342\ncpu: 1579.636668876472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 419.59993538124536,
            "unit": "ns/iter",
            "extra": "iterations: 1673668\ncpu: 419.3388413950665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1992.5318733601814,
            "unit": "ns/iter",
            "extra": "iterations: 355252\ncpu: 1991.4933624581954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 119.07763713170336,
            "unit": "ns/iter",
            "extra": "iterations: 5761601\ncpu: 118.98567776560698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 475.7646256572542,
            "unit": "ns/iter",
            "extra": "iterations: 1490710\ncpu: 475.1279591604024 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 375.8059949258525,
            "unit": "ns/iter",
            "extra": "iterations: 1888075\ncpu: 373.79447320683784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 924.9510125091086,
            "unit": "ns/iter",
            "extra": "iterations: 761341\ncpu: 924.3335115276857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 184.22794468899383,
            "unit": "ns/iter",
            "extra": "iterations: 3791141\ncpu: 184.1303185505363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1569.3247653069657,
            "unit": "ns/iter",
            "extra": "iterations: 444718\ncpu: 1568.4681078795998 ns\nthreads: 1"
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
        "date": 1729019265149,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3677564859.390259,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3674910000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 776.362705924444,
            "unit": "ns/iter",
            "extra": "iterations: 914865\ncpu: 775.9188514152352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1038.5882432408714,
            "unit": "ns/iter",
            "extra": "iterations: 690621\ncpu: 1037.8080017839022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 175.04132237011612,
            "unit": "ns/iter",
            "extra": "iterations: 4070359\ncpu: 174.92511102829013 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 120.06001408735894,
            "unit": "ns/iter",
            "extra": "iterations: 5836981\ncpu: 119.98685621899419 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2474.2597722926653,
            "unit": "ns/iter",
            "extra": "iterations: 289483\ncpu: 2472.4560682319902 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.042522444701074,
            "unit": "ns/iter",
            "extra": "iterations: 27856262\ncpu: 25.021986079826473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1519.9369632227103,
            "unit": "ns/iter",
            "extra": "iterations: 455367\ncpu: 1518.836454991248 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1303.9880296909637,
            "unit": "ns/iter",
            "extra": "iterations: 524011\ncpu: 1302.8982216022162 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1591.9195219137353,
            "unit": "ns/iter",
            "extra": "iterations: 437333\ncpu: 1590.4676756613403 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 422.4251539500966,
            "unit": "ns/iter",
            "extra": "iterations: 1673132\ncpu: 422.086243045976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1998.906472260611,
            "unit": "ns/iter",
            "extra": "iterations: 347465\ncpu: 1997.6055142244552 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 120.0699995914499,
            "unit": "ns/iter",
            "extra": "iterations: 5778820\ncpu: 119.99058631346841 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 471.5962252352162,
            "unit": "ns/iter",
            "extra": "iterations: 1486348\ncpu: 471.351258251769 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 373.4250712717524,
            "unit": "ns/iter",
            "extra": "iterations: 1893258\ncpu: 373.2259417364146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 926.0544723397688,
            "unit": "ns/iter",
            "extra": "iterations: 763384\ncpu: 924.4325267493125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 186.24024993092846,
            "unit": "ns/iter",
            "extra": "iterations: 3737420\ncpu: 185.98471672972252 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1597.7230277418653,
            "unit": "ns/iter",
            "extra": "iterations: 439792\ncpu: 1596.907174300573 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}