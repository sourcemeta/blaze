window.BENCHMARK_DATA = {
  "lastUpdate": 1730303810306,
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
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729020435207,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4099114179.611206,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4095452000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 845.9410833840213,
            "unit": "ns/iter",
            "extra": "iterations: 852899\ncpu: 845.4412538882095 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1090.748348955218,
            "unit": "ns/iter",
            "extra": "iterations: 579206\ncpu: 1089.9455461442058 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 184.8970530108067,
            "unit": "ns/iter",
            "extra": "iterations: 3778800\ncpu: 184.7618291521119 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.5083028128763,
            "unit": "ns/iter",
            "extra": "iterations: 5466956\ncpu: 127.40490320390329 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2580.7269773599464,
            "unit": "ns/iter",
            "extra": "iterations: 271107\ncpu: 2579.2214881946957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.892620247731386,
            "unit": "ns/iter",
            "extra": "iterations: 26266318\ncpu: 26.877196872435672 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1617.2078397490818,
            "unit": "ns/iter",
            "extra": "iterations: 438322\ncpu: 1615.2257929102338 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1409.2615644857312,
            "unit": "ns/iter",
            "extra": "iterations: 504810\ncpu: 1408.3437332857904 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1708.338580960717,
            "unit": "ns/iter",
            "extra": "iterations: 411782\ncpu: 1707.165441908583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 498.4383106950866,
            "unit": "ns/iter",
            "extra": "iterations: 1484529\ncpu: 491.2716423862374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2128.6919272396285,
            "unit": "ns/iter",
            "extra": "iterations: 283668\ncpu: 2120.609303834061 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 126.76187742878746,
            "unit": "ns/iter",
            "extra": "iterations: 5509165\ncpu: 126.67219079479379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 509.1861890444606,
            "unit": "ns/iter",
            "extra": "iterations: 1375300\ncpu: 508.8678833708989 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 396.93048804068616,
            "unit": "ns/iter",
            "extra": "iterations: 1763273\ncpu: 396.2596829872623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 990.2111963994702,
            "unit": "ns/iter",
            "extra": "iterations: 725118\ncpu: 989.5837642976785 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 200.0549998784205,
            "unit": "ns/iter",
            "extra": "iterations: 3544250\ncpu: 199.95316357480473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1693.2104142576845,
            "unit": "ns/iter",
            "extra": "iterations: 416863\ncpu: 1692.1482597400066 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729021540668,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3647531032.562256,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3647052999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 839.5775441870752,
            "unit": "ns/iter",
            "extra": "iterations: 916830\ncpu: 839.3355365771192 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1017.1480254297228,
            "unit": "ns/iter",
            "extra": "iterations: 626185\ncpu: 1016.717104370114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 172.51583364044848,
            "unit": "ns/iter",
            "extra": "iterations: 4060537\ncpu: 172.50871005485223 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.03570227268142,
            "unit": "ns/iter",
            "extra": "iterations: 5864071\ncpu: 119.00214032197083 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2420.8208550732425,
            "unit": "ns/iter",
            "extra": "iterations: 288731\ncpu: 2420.5956409252876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.62532984653192,
            "unit": "ns/iter",
            "extra": "iterations: 28416587\ncpu: 24.62410422476147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1519.3624039766896,
            "unit": "ns/iter",
            "extra": "iterations: 461851\ncpu: 1518.808013839962 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1308.18144139192,
            "unit": "ns/iter",
            "extra": "iterations: 535168\ncpu: 1307.8098839990419 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1584.3326851794402,
            "unit": "ns/iter",
            "extra": "iterations: 443850\ncpu: 1584.3257857384217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 419.79426843683297,
            "unit": "ns/iter",
            "extra": "iterations: 1659015\ncpu: 419.7544928767976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1967.8027393341733,
            "unit": "ns/iter",
            "extra": "iterations: 359749\ncpu: 1967.7052611682068 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 117.61779018178095,
            "unit": "ns/iter",
            "extra": "iterations: 5955673\ncpu: 117.61072174378937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 507.479747379294,
            "unit": "ns/iter",
            "extra": "iterations: 1445734\ncpu: 507.36926709892913 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 381.8095981803298,
            "unit": "ns/iter",
            "extra": "iterations: 1734519\ncpu: 381.21807832603724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 932.6791590681306,
            "unit": "ns/iter",
            "extra": "iterations: 744435\ncpu: 931.025542861364 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 192.55120546668405,
            "unit": "ns/iter",
            "extra": "iterations: 3840625\ncpu: 192.4639869812864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1699.1056920066242,
            "unit": "ns/iter",
            "extra": "iterations: 441707\ncpu: 1699.0788011057123 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729022354477,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3732939004.8980713,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3720015000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 765.5452401993915,
            "unit": "ns/iter",
            "extra": "iterations: 917648\ncpu: 765.4776123306531 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1002.4253952642046,
            "unit": "ns/iter",
            "extra": "iterations: 702593\ncpu: 1002.3569833459757 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 178.73296031759347,
            "unit": "ns/iter",
            "extra": "iterations: 3986696\ncpu: 178.690073183408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 128.03854773049957,
            "unit": "ns/iter",
            "extra": "iterations: 5196193\ncpu: 127.92461711872521 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2433.1748452342495,
            "unit": "ns/iter",
            "extra": "iterations: 285261\ncpu: 2432.6073315314734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.612107452999137,
            "unit": "ns/iter",
            "extra": "iterations: 28423164\ncpu: 24.61168643997554 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1517.9947758542055,
            "unit": "ns/iter",
            "extra": "iterations: 461443\ncpu: 1517.8711130085424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1306.0303268557896,
            "unit": "ns/iter",
            "extra": "iterations: 535303\ncpu: 1306.0136035105363 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1576.5002413950904,
            "unit": "ns/iter",
            "extra": "iterations: 441724\ncpu: 1576.5002580797043 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 417.3977582859083,
            "unit": "ns/iter",
            "extra": "iterations: 1662850\ncpu: 417.35153501518414 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1965.968348732932,
            "unit": "ns/iter",
            "extra": "iterations: 355112\ncpu: 1965.8952668453876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 117.78210616682628,
            "unit": "ns/iter",
            "extra": "iterations: 5948840\ncpu: 117.7674975289301 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 470.6083215912778,
            "unit": "ns/iter",
            "extra": "iterations: 1487428\ncpu: 470.5605918404096 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 373.0859558265486,
            "unit": "ns/iter",
            "extra": "iterations: 1867468\ncpu: 372.091516427593 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 904.2258467568,
            "unit": "ns/iter",
            "extra": "iterations: 764559\ncpu: 904.2009838351206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 182.17126492934742,
            "unit": "ns/iter",
            "extra": "iterations: 3814943\ncpu: 182.15003474494978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1556.4040691095283,
            "unit": "ns/iter",
            "extra": "iterations: 449632\ncpu: 1556.1103302256015 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729023739231,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3973776817.3217773,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3864013000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 795.4222194230912,
            "unit": "ns/iter",
            "extra": "iterations: 895874\ncpu: 780.1186327541598 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1011.2808223731521,
            "unit": "ns/iter",
            "extra": "iterations: 697308\ncpu: 1010.4415839198753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 172.9827967537199,
            "unit": "ns/iter",
            "extra": "iterations: 4011254\ncpu: 172.8683847993671 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 120.83920888201418,
            "unit": "ns/iter",
            "extra": "iterations: 5792688\ncpu: 120.77588159417526 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2471.867084157174,
            "unit": "ns/iter",
            "extra": "iterations: 289410\ncpu: 2470.33965654262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.766920110433386,
            "unit": "ns/iter",
            "extra": "iterations: 28448924\ncpu: 24.735417058304233 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1529.8410276125858,
            "unit": "ns/iter",
            "extra": "iterations: 458698\ncpu: 1528.1841211428862 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1305.559550073338,
            "unit": "ns/iter",
            "extra": "iterations: 532210\ncpu: 1304.650419947013 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1588.1932504052113,
            "unit": "ns/iter",
            "extra": "iterations: 437749\ncpu: 1587.3822670068912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.01154475884334,
            "unit": "ns/iter",
            "extra": "iterations: 1669322\ncpu: 417.7642180478064 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2002.0733758766507,
            "unit": "ns/iter",
            "extra": "iterations: 353535\ncpu: 2000.7806864949705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.80073551451478,
            "unit": "ns/iter",
            "extra": "iterations: 5831875\ncpu: 118.735055192369 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 482.00620287206675,
            "unit": "ns/iter",
            "extra": "iterations: 1462740\ncpu: 481.6727511382766 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 378.92009425711973,
            "unit": "ns/iter",
            "extra": "iterations: 1883741\ncpu: 378.4140176383045 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 910.9625756434136,
            "unit": "ns/iter",
            "extra": "iterations: 769484\ncpu: 910.3282199499904 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 184.7575818143438,
            "unit": "ns/iter",
            "extra": "iterations: 3805527\ncpu: 184.640130000391 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1571.1443997954627,
            "unit": "ns/iter",
            "extra": "iterations: 448517\ncpu: 1569.583761596549 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729024821739,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3650646209.716797,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3643551000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 768.0110128923484,
            "unit": "ns/iter",
            "extra": "iterations: 915368\ncpu: 767.5688903260761 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1010.8781820868257,
            "unit": "ns/iter",
            "extra": "iterations: 692555\ncpu: 1010.3688515713562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 172.77430913241395,
            "unit": "ns/iter",
            "extra": "iterations: 4039541\ncpu: 172.66714213322754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 118.61275455794907,
            "unit": "ns/iter",
            "extra": "iterations: 5890372\ncpu: 118.54853988848241 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2412.6952106026624,
            "unit": "ns/iter",
            "extra": "iterations: 287304\ncpu: 2411.240358644498 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.662520953151365,
            "unit": "ns/iter",
            "extra": "iterations: 28366610\ncpu: 24.645243122107228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1517.6754230060687,
            "unit": "ns/iter",
            "extra": "iterations: 461115\ncpu: 1516.8146774665772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1307.408357858709,
            "unit": "ns/iter",
            "extra": "iterations: 536037\ncpu: 1306.6896501547458 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1575.2613594076768,
            "unit": "ns/iter",
            "extra": "iterations: 444518\ncpu: 1574.4334312671247 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 425.25393414414225,
            "unit": "ns/iter",
            "extra": "iterations: 1660483\ncpu: 424.50118429396736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1958.763889042333,
            "unit": "ns/iter",
            "extra": "iterations: 359052\ncpu: 1957.7387119414416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 117.6111815475032,
            "unit": "ns/iter",
            "extra": "iterations: 5950812\ncpu: 117.54933612421249 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 471.76625574255144,
            "unit": "ns/iter",
            "extra": "iterations: 1496974\ncpu: 471.33350345430085 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 371.4772984140191,
            "unit": "ns/iter",
            "extra": "iterations: 1802665\ncpu: 371.2619926608673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 908.6237551667463,
            "unit": "ns/iter",
            "extra": "iterations: 777907\ncpu: 907.9568637382076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 182.50635949217363,
            "unit": "ns/iter",
            "extra": "iterations: 3835679\ncpu: 182.18912479381103 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1561.8962378253434,
            "unit": "ns/iter",
            "extra": "iterations: 448092\ncpu: 1561.0655847459852 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729086292793,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3837419033.050537,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3834875000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 791.6566762611283,
            "unit": "ns/iter",
            "extra": "iterations: 886435\ncpu: 791.152199540857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1044.181540264183,
            "unit": "ns/iter",
            "extra": "iterations: 677953\ncpu: 1043.6608437458053 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 187.08623638375357,
            "unit": "ns/iter",
            "extra": "iterations: 3923063\ncpu: 186.92256535263397 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 132.07639278650362,
            "unit": "ns/iter",
            "extra": "iterations: 5136974\ncpu: 131.97049469201144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2496.767950474524,
            "unit": "ns/iter",
            "extra": "iterations: 278977\ncpu: 2495.44227660344 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.474650333687983,
            "unit": "ns/iter",
            "extra": "iterations: 27425813\ncpu: 25.46075844679605 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1668.5267936253558,
            "unit": "ns/iter",
            "extra": "iterations: 446377\ncpu: 1666.7928679121023 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1383.7927665934853,
            "unit": "ns/iter",
            "extra": "iterations: 496549\ncpu: 1382.9974483887831 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1650.5945432092171,
            "unit": "ns/iter",
            "extra": "iterations: 418700\ncpu: 1649.4841175065699 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 435.9475094952161,
            "unit": "ns/iter",
            "extra": "iterations: 1618823\ncpu: 435.66776602506854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2039.5894455477046,
            "unit": "ns/iter",
            "extra": "iterations: 343343\ncpu: 2037.8367987697468 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 122.38096133098517,
            "unit": "ns/iter",
            "extra": "iterations: 5709671\ncpu: 122.31195107388854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 490.4126111264205,
            "unit": "ns/iter",
            "extra": "iterations: 1428848\ncpu: 490.08991859176115 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 385.17883519492057,
            "unit": "ns/iter",
            "extra": "iterations: 1825941\ncpu: 384.0595068515323 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 934.6830110450696,
            "unit": "ns/iter",
            "extra": "iterations: 699175\ncpu: 934.1323702935548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 188.90730908672495,
            "unit": "ns/iter",
            "extra": "iterations: 3700825\ncpu: 188.8116838812965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1609.3365819873159,
            "unit": "ns/iter",
            "extra": "iterations: 432109\ncpu: 1608.0109416836924 ns\nthreads: 1"
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
        "date": 1729105728807,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3671083927.154541,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3670020000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 763.7515074144736,
            "unit": "ns/iter",
            "extra": "iterations: 919142\ncpu: 763.6709017757863 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1013.3954979184487,
            "unit": "ns/iter",
            "extra": "iterations: 688434\ncpu: 1013.2256686915507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 180.81787344142472,
            "unit": "ns/iter",
            "extra": "iterations: 3979534\ncpu: 178.99331931829192 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 124.03888857067489,
            "unit": "ns/iter",
            "extra": "iterations: 5494721\ncpu: 123.09960778718334 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2410.414754903225,
            "unit": "ns/iter",
            "extra": "iterations: 284941\ncpu: 2410.214746210619 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.801662816960054,
            "unit": "ns/iter",
            "extra": "iterations: 28331822\ncpu: 24.800452297067263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1530.5790639235222,
            "unit": "ns/iter",
            "extra": "iterations: 460802\ncpu: 1530.4816385345555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1310.5181317473864,
            "unit": "ns/iter",
            "extra": "iterations: 528043\ncpu: 1310.5220597565008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1584.5960594945038,
            "unit": "ns/iter",
            "extra": "iterations: 443718\ncpu: 1584.4139746415547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.62781392242226,
            "unit": "ns/iter",
            "extra": "iterations: 1671091\ncpu: 418.609160123536 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1964.1128516934816,
            "unit": "ns/iter",
            "extra": "iterations: 360596\ncpu: 1964.059501491976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 117.68935828911631,
            "unit": "ns/iter",
            "extra": "iterations: 5948891\ncpu: 117.68277482307178 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 479.81175152575065,
            "unit": "ns/iter",
            "extra": "iterations: 1488817\ncpu: 476.73824251066554 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 379.4678958020304,
            "unit": "ns/iter",
            "extra": "iterations: 1816422\ncpu: 377.09849363198634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 932.5194394971468,
            "unit": "ns/iter",
            "extra": "iterations: 770416\ncpu: 932.3741978359717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 182.40527561563596,
            "unit": "ns/iter",
            "extra": "iterations: 3828442\ncpu: 182.37105329008614 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1561.218951563206,
            "unit": "ns/iter",
            "extra": "iterations: 448422\ncpu: 1561.054096364585 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729115963040,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3694895267.4865723,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3694573000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 763.4930046543715,
            "unit": "ns/iter",
            "extra": "iterations: 900264\ncpu: 763.446055823626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1017.5332941069547,
            "unit": "ns/iter",
            "extra": "iterations: 689771\ncpu: 1017.5101591687666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 172.27651752131422,
            "unit": "ns/iter",
            "extra": "iterations: 4030702\ncpu: 172.25684260458843 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.13034157378405,
            "unit": "ns/iter",
            "extra": "iterations: 5861714\ncpu: 119.12096018331857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2452.3057390303525,
            "unit": "ns/iter",
            "extra": "iterations: 288654\ncpu: 2452.2854351576643 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.64020508629492,
            "unit": "ns/iter",
            "extra": "iterations: 28265013\ncpu: 24.639790542463146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1533.553694472941,
            "unit": "ns/iter",
            "extra": "iterations: 457155\ncpu: 1533.4908291498514 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1308.1466686266656,
            "unit": "ns/iter",
            "extra": "iterations: 535164\ncpu: 1308.094341173916 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1659.5145536192856,
            "unit": "ns/iter",
            "extra": "iterations: 437968\ncpu: 1657.6850363496917 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 462.47071919398803,
            "unit": "ns/iter",
            "extra": "iterations: 1525975\ncpu: 462.378479332885 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2161.396884895666,
            "unit": "ns/iter",
            "extra": "iterations: 325693\ncpu: 2161.250011513909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 128.10377892766542,
            "unit": "ns/iter",
            "extra": "iterations: 5489464\ncpu: 128.0724311153147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 512.2043519079125,
            "unit": "ns/iter",
            "extra": "iterations: 1358696\ncpu: 512.1830048811528 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 383.5083731818145,
            "unit": "ns/iter",
            "extra": "iterations: 1762545\ncpu: 383.4738971203567 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 920.1105745381129,
            "unit": "ns/iter",
            "extra": "iterations: 777864\ncpu: 919.7546100603724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 184.02338284768197,
            "unit": "ns/iter",
            "extra": "iterations: 3750616\ncpu: 183.88712680796937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 810.5988788242593,
            "unit": "ns/iter",
            "extra": "iterations: 863760\ncpu: 810.5677503010143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1593.3094378748654,
            "unit": "ns/iter",
            "extra": "iterations: 444665\ncpu: 1593.2893301698987 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729170894508,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3646899938.583374,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3646382000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 769.6577256160145,
            "unit": "ns/iter",
            "extra": "iterations: 909091\ncpu: 769.5962230403771 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1015.1254666410042,
            "unit": "ns/iter",
            "extra": "iterations: 691754\ncpu: 1015.10074390607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 175.82509486744445,
            "unit": "ns/iter",
            "extra": "iterations: 3963154\ncpu: 175.8238514072376 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 120.63363278704479,
            "unit": "ns/iter",
            "extra": "iterations: 5814823\ncpu: 120.6244798852866 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2408.9594597659066,
            "unit": "ns/iter",
            "extra": "iterations: 286493\ncpu: 2408.690613732272 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.560192786849576,
            "unit": "ns/iter",
            "extra": "iterations: 27399834\ncpu: 25.55880448034833 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1508.577009757235,
            "unit": "ns/iter",
            "extra": "iterations: 462553\ncpu: 1508.4563282477875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1294.5124645223793,
            "unit": "ns/iter",
            "extra": "iterations: 540015\ncpu: 1294.4399692601123 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1571.937545040977,
            "unit": "ns/iter",
            "extra": "iterations: 446005\ncpu: 1571.7671326554657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 420.4774652301157,
            "unit": "ns/iter",
            "extra": "iterations: 1662581\ncpu: 420.4462820157322 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2004.352958461177,
            "unit": "ns/iter",
            "extra": "iterations: 353296\ncpu: 2004.2966804039659 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 121.75398362403142,
            "unit": "ns/iter",
            "extra": "iterations: 5864022\ncpu: 121.74596207176562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 507.2429903159727,
            "unit": "ns/iter",
            "extra": "iterations: 1330293\ncpu: 507.2446446008503 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 450.14616671887177,
            "unit": "ns/iter",
            "extra": "iterations: 1832691\ncpu: 449.89035249259155 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1017.2676350430413,
            "unit": "ns/iter",
            "extra": "iterations: 712729\ncpu: 1017.0120761186939 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 185.39369752917943,
            "unit": "ns/iter",
            "extra": "iterations: 3767593\ncpu: 185.38148892409558 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 596.047884250235,
            "unit": "ns/iter",
            "extra": "iterations: 1161806\ncpu: 596.0315233352209 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1718.0960254663573,
            "unit": "ns/iter",
            "extra": "iterations: 444939\ncpu: 1694.7289403716027 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729188208334,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4003935098.6480713,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4003435000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 808.9746385503357,
            "unit": "ns/iter",
            "extra": "iterations: 876051\ncpu: 808.9095269567638 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1049.1051461505513,
            "unit": "ns/iter",
            "extra": "iterations: 657363\ncpu: 1049.08094918637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 188.7803151122341,
            "unit": "ns/iter",
            "extra": "iterations: 3811017\ncpu: 188.7469932566555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.09841473004305,
            "unit": "ns/iter",
            "extra": "iterations: 5339476\ncpu: 127.08194586884534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2501.608264478455,
            "unit": "ns/iter",
            "extra": "iterations: 282876\ncpu: 2501.4352578515054 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.916538963040928,
            "unit": "ns/iter",
            "extra": "iterations: 26100315\ncpu: 26.91657169654844 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1568.232552042442,
            "unit": "ns/iter",
            "extra": "iterations: 443408\ncpu: 1567.2428102334663 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1321.388643050835,
            "unit": "ns/iter",
            "extra": "iterations: 540424\ncpu: 1320.043151303425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1722.3905156233243,
            "unit": "ns/iter",
            "extra": "iterations: 401553\ncpu: 1697.0910440215891 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 422.50799057369056,
            "unit": "ns/iter",
            "extra": "iterations: 1659424\ncpu: 422.2591694467475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1973.3726808448268,
            "unit": "ns/iter",
            "extra": "iterations: 357234\ncpu: 1973.2640230213249 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 122.80889964834442,
            "unit": "ns/iter",
            "extra": "iterations: 5547674\ncpu: 122.7581144818532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 488.7020512036885,
            "unit": "ns/iter",
            "extra": "iterations: 1443847\ncpu: 488.6521909869988 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 371.864554105985,
            "unit": "ns/iter",
            "extra": "iterations: 1884791\ncpu: 371.83910576822495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 933.8898788832806,
            "unit": "ns/iter",
            "extra": "iterations: 747512\ncpu: 933.4258179132905 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 198.604959131445,
            "unit": "ns/iter",
            "extra": "iterations: 3616375\ncpu: 198.09035290864378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 635.5301335157495,
            "unit": "ns/iter",
            "extra": "iterations: 1116891\ncpu: 635.4711426629798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1662.8537518278745,
            "unit": "ns/iter",
            "extra": "iterations: 424353\ncpu: 1662.8349510902522 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729188794957,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3951804876.3275146,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3949197000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 829.8539496001027,
            "unit": "ns/iter",
            "extra": "iterations: 860278\ncpu: 829.2412452718768 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1124.8643628861032,
            "unit": "ns/iter",
            "extra": "iterations: 639485\ncpu: 1124.0936065740405 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 186.45380743792404,
            "unit": "ns/iter",
            "extra": "iterations: 3208757\ncpu: 186.34879487602197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 129.19338975983885,
            "unit": "ns/iter",
            "extra": "iterations: 5403945\ncpu: 129.08569572784344 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2563.554552592493,
            "unit": "ns/iter",
            "extra": "iterations: 270829\ncpu: 2561.723449113656 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.66852394052823,
            "unit": "ns/iter",
            "extra": "iterations: 24165430\ncpu: 27.63004837902742 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1646.493528079748,
            "unit": "ns/iter",
            "extra": "iterations: 427084\ncpu: 1645.2875780876795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1558.348339636821,
            "unit": "ns/iter",
            "extra": "iterations: 493994\ncpu: 1538.4113977092811 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 2199.584079351205,
            "unit": "ns/iter",
            "extra": "iterations: 326314\ncpu: 2146.2058017737495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 476.8554622709232,
            "unit": "ns/iter",
            "extra": "iterations: 1354646\ncpu: 472.74786180301015 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2131.3224844912884,
            "unit": "ns/iter",
            "extra": "iterations: 326959\ncpu: 2129.603405931627 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 129.02328120579793,
            "unit": "ns/iter",
            "extra": "iterations: 5486280\ncpu: 128.90355577914352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 509.24737859320084,
            "unit": "ns/iter",
            "extra": "iterations: 1397987\ncpu: 508.6513680027068 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 397.73311065157054,
            "unit": "ns/iter",
            "extra": "iterations: 1722789\ncpu: 397.4119871905369 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 992.0198121813635,
            "unit": "ns/iter",
            "extra": "iterations: 717118\ncpu: 988.3185194068478 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 196.38510030095352,
            "unit": "ns/iter",
            "extra": "iterations: 3571082\ncpu: 196.26600565318958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 644.4320329816476,
            "unit": "ns/iter",
            "extra": "iterations: 1100802\ncpu: 644.0804068306605 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1793.0376519283807,
            "unit": "ns/iter",
            "extra": "iterations: 417985\ncpu: 1791.432706915324 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729189791998,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4575093030.929565,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4429173000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 864.1936601792431,
            "unit": "ns/iter",
            "extra": "iterations: 805227\ncpu: 824.4780664334412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1181.550063933258,
            "unit": "ns/iter",
            "extra": "iterations: 645977\ncpu: 1135.2602337234916 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 189.23189135891997,
            "unit": "ns/iter",
            "extra": "iterations: 3709120\ncpu: 184.89992235355018 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 131.17832818901755,
            "unit": "ns/iter",
            "extra": "iterations: 5468152\ncpu: 127.07620417281746 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2480.7510354442848,
            "unit": "ns/iter",
            "extra": "iterations: 283440\ncpu: 2479.2654530059294 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.11115156406681,
            "unit": "ns/iter",
            "extra": "iterations: 26309558\ncpu: 26.108078288506416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1586.673453223183,
            "unit": "ns/iter",
            "extra": "iterations: 421725\ncpu: 1586.4248028928785 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1357.4825726357662,
            "unit": "ns/iter",
            "extra": "iterations: 515874\ncpu: 1354.6156619639698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1673.8366603434483,
            "unit": "ns/iter",
            "extra": "iterations: 407244\ncpu: 1672.866880788912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 480.5562630766195,
            "unit": "ns/iter",
            "extra": "iterations: 1537593\ncpu: 479.56253703027966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2282.60127346644,
            "unit": "ns/iter",
            "extra": "iterations: 295095\ncpu: 2271.017807824599 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 143.69867597677663,
            "unit": "ns/iter",
            "extra": "iterations: 5028772\ncpu: 142.0647028737835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 606.2634140944505,
            "unit": "ns/iter",
            "extra": "iterations: 1092419\ncpu: 605.5606868793004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 507.8458786010742,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 507.2480000000006 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1285.4931867272933,
            "unit": "ns/iter",
            "extra": "iterations: 567243\ncpu: 1284.1498264412216 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 232.564693499441,
            "unit": "ns/iter",
            "extra": "iterations: 3230362\ncpu: 232.48075602672446 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 868.4072085700236,
            "unit": "ns/iter",
            "extra": "iterations: 991544\ncpu: 793.6299347280616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1992.6292784635,
            "unit": "ns/iter",
            "extra": "iterations: 375389\ncpu: 1953.2245217627628 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729190682275,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4349333047.866821,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4299223000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 824.2729610195024,
            "unit": "ns/iter",
            "extra": "iterations: 854086\ncpu: 823.6301730739062 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1102.9721965472866,
            "unit": "ns/iter",
            "extra": "iterations: 615060\ncpu: 1102.2908334146275 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.19849145398737,
            "unit": "ns/iter",
            "extra": "iterations: 3790997\ncpu: 184.98933130255705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.44878190274383,
            "unit": "ns/iter",
            "extra": "iterations: 5498303\ncpu: 127.36256986928495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2540.025044405515,
            "unit": "ns/iter",
            "extra": "iterations: 266166\ncpu: 2538.5736720693108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.16742640951988,
            "unit": "ns/iter",
            "extra": "iterations: 26010605\ncpu: 27.12462858899281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1618.232110922954,
            "unit": "ns/iter",
            "extra": "iterations: 430798\ncpu: 1616.7484528711814 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1384.6925809804832,
            "unit": "ns/iter",
            "extra": "iterations: 502913\ncpu: 1383.9292283158338 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1793.5504336890617,
            "unit": "ns/iter",
            "extra": "iterations: 418999\ncpu: 1792.5937770734522 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 462.7375833827369,
            "unit": "ns/iter",
            "extra": "iterations: 1522729\ncpu: 462.4315948537142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2170.0137005585984,
            "unit": "ns/iter",
            "extra": "iterations: 326961\ncpu: 2168.273891993233 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 129.60383155083358,
            "unit": "ns/iter",
            "extra": "iterations: 5506565\ncpu: 129.53084182244245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 519.4129437461677,
            "unit": "ns/iter",
            "extra": "iterations: 1302713\ncpu: 519.1289255576614 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 414.72719848182925,
            "unit": "ns/iter",
            "extra": "iterations: 1793791\ncpu: 409.11789612056145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1002.1202792670946,
            "unit": "ns/iter",
            "extra": "iterations: 707392\ncpu: 990.4423572785637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 199.22554879941458,
            "unit": "ns/iter",
            "extra": "iterations: 3660303\ncpu: 198.97806274507877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 702.0660928807495,
            "unit": "ns/iter",
            "extra": "iterations: 963895\ncpu: 701.573304146198 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1711.854724825968,
            "unit": "ns/iter",
            "extra": "iterations: 407978\ncpu: 1710.3520287858676 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729191635248,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3602471351.623535,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3602046000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 756.9506146658006,
            "unit": "ns/iter",
            "extra": "iterations: 865480\ncpu: 756.9233257845351 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 999.6838546845514,
            "unit": "ns/iter",
            "extra": "iterations: 699287\ncpu: 999.5667015116829 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 173.12398702106887,
            "unit": "ns/iter",
            "extra": "iterations: 4051184\ncpu: 173.11556325261935 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 118.73539743642347,
            "unit": "ns/iter",
            "extra": "iterations: 5901197\ncpu: 118.72472652582157 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2393.8722658497722,
            "unit": "ns/iter",
            "extra": "iterations: 294895\ncpu: 2393.7638820597103 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.960193992212265,
            "unit": "ns/iter",
            "extra": "iterations: 28018044\ncpu: 24.95959389599071 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1499.047152465075,
            "unit": "ns/iter",
            "extra": "iterations: 468146\ncpu: 1498.9041880097268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1291.836688868874,
            "unit": "ns/iter",
            "extra": "iterations: 542194\ncpu: 1291.799614160247 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1572.2433494825775,
            "unit": "ns/iter",
            "extra": "iterations: 441426\ncpu: 1572.2068931145877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.3370825907265,
            "unit": "ns/iter",
            "extra": "iterations: 1672441\ncpu: 418.3202875318177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1967.598921368821,
            "unit": "ns/iter",
            "extra": "iterations: 356902\ncpu: 1967.34397677794 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 117.65772537236622,
            "unit": "ns/iter",
            "extra": "iterations: 5956991\ncpu: 117.64798704580879 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 473.17179838016216,
            "unit": "ns/iter",
            "extra": "iterations: 1484945\ncpu: 473.0282939772163 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 365.5031821382749,
            "unit": "ns/iter",
            "extra": "iterations: 1916249\ncpu: 365.4921672496633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 916.4330633715831,
            "unit": "ns/iter",
            "extra": "iterations: 766166\ncpu: 916.3771297603894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 181.19681057419027,
            "unit": "ns/iter",
            "extra": "iterations: 3852441\ncpu: 181.19368992283083 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 625.0812694990236,
            "unit": "ns/iter",
            "extra": "iterations: 1114703\ncpu: 625.0786083826821 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1571.9512589600101,
            "unit": "ns/iter",
            "extra": "iterations: 443912\ncpu: 1571.8701003802566 ns\nthreads: 1"
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
        "date": 1729192148581,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4117516756.0577393,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4116734999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 947.9302963988943,
            "unit": "ns/iter",
            "extra": "iterations: 853763\ncpu: 947.6775170626973 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1083.0688695092133,
            "unit": "ns/iter",
            "extra": "iterations: 537651\ncpu: 1081.9974295593245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 187.97929393926745,
            "unit": "ns/iter",
            "extra": "iterations: 3743376\ncpu: 187.96936241510315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 128.11798595505243,
            "unit": "ns/iter",
            "extra": "iterations: 5432631\ncpu: 128.08931804865819 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2584.8281708436543,
            "unit": "ns/iter",
            "extra": "iterations: 271899\ncpu: 2584.64356249931 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.965898901034723,
            "unit": "ns/iter",
            "extra": "iterations: 25858407\ncpu: 26.965930267862195 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1616.4172393375939,
            "unit": "ns/iter",
            "extra": "iterations: 433203\ncpu: 1616.1730181923965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1423.3041449569134,
            "unit": "ns/iter",
            "extra": "iterations: 501063\ncpu: 1421.857131737927 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1701.7418027158164,
            "unit": "ns/iter",
            "extra": "iterations: 401388\ncpu: 1701.6178859358033 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 472.74581595465224,
            "unit": "ns/iter",
            "extra": "iterations: 1554457\ncpu: 469.83416073908796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2105.2053138741185,
            "unit": "ns/iter",
            "extra": "iterations: 331960\ncpu: 2104.4372816001933 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 126.75238230652717,
            "unit": "ns/iter",
            "extra": "iterations: 5532678\ncpu: 126.75326487462284 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 516.8398079622392,
            "unit": "ns/iter",
            "extra": "iterations: 1399776\ncpu: 516.5233580229996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 390.13052306477675,
            "unit": "ns/iter",
            "extra": "iterations: 1759081\ncpu: 390.0980114048186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 982.1958274608397,
            "unit": "ns/iter",
            "extra": "iterations: 741282\ncpu: 980.0278436546453 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 194.694989101538,
            "unit": "ns/iter",
            "extra": "iterations: 3594961\ncpu: 194.68500492773032 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 671.7654659991397,
            "unit": "ns/iter",
            "extra": "iterations: 1037298\ncpu: 671.4589250148014 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1698.5951313636685,
            "unit": "ns/iter",
            "extra": "iterations: 412797\ncpu: 1698.3166059830817 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729195902427,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4186587095.26062,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4185815000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 768.8004915483799,
            "unit": "ns/iter",
            "extra": "iterations: 841680\ncpu: 768.754158349966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1033.3281453214481,
            "unit": "ns/iter",
            "extra": "iterations: 693859\ncpu: 1033.2718895337537 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 178.9956374995767,
            "unit": "ns/iter",
            "extra": "iterations: 4020701\ncpu: 178.96456364201214 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 124.4484572298337,
            "unit": "ns/iter",
            "extra": "iterations: 5618744\ncpu: 124.43332531256061 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2462.036738689145,
            "unit": "ns/iter",
            "extra": "iterations: 287382\ncpu: 2462.001795519552 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.12929065246058,
            "unit": "ns/iter",
            "extra": "iterations: 27528275\ncpu: 25.124857986924358 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1504.9767171337178,
            "unit": "ns/iter",
            "extra": "iterations: 464336\ncpu: 1504.8477826401538 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1304.115731020665,
            "unit": "ns/iter",
            "extra": "iterations: 528230\ncpu: 1303.8335573519157 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1571.9038114938364,
            "unit": "ns/iter",
            "extra": "iterations: 449037\ncpu: 1571.8905123631253 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.9114752029646,
            "unit": "ns/iter",
            "extra": "iterations: 1666980\ncpu: 418.86165400904696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1991.9919314317626,
            "unit": "ns/iter",
            "extra": "iterations: 355876\ncpu: 1991.1682720947772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 119.30752555566185,
            "unit": "ns/iter",
            "extra": "iterations: 5822368\ncpu: 119.30455100055477 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 482.18212116044634,
            "unit": "ns/iter",
            "extra": "iterations: 1432038\ncpu: 479.09552679468004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 369.86024409793527,
            "unit": "ns/iter",
            "extra": "iterations: 1901667\ncpu: 369.8113286921431 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 976.3967314983381,
            "unit": "ns/iter",
            "extra": "iterations: 725494\ncpu: 976.2368813525732 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 182.9492682782845,
            "unit": "ns/iter",
            "extra": "iterations: 3802426\ncpu: 182.93926035641496 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 638.1857680964579,
            "unit": "ns/iter",
            "extra": "iterations: 1095770\ncpu: 638.1695063745112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1602.928664177985,
            "unit": "ns/iter",
            "extra": "iterations: 441802\ncpu: 1602.865084359054 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729196866911,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3723864793.777466,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3721642000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 769.3132676025431,
            "unit": "ns/iter",
            "extra": "iterations: 919528\ncpu: 768.5606093561041 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1024.4990215679175,
            "unit": "ns/iter",
            "extra": "iterations: 682767\ncpu: 1023.792889814535 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 174.8747166342537,
            "unit": "ns/iter",
            "extra": "iterations: 4033978\ncpu: 174.74983750531118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 121.21519878524957,
            "unit": "ns/iter",
            "extra": "iterations: 5903088\ncpu: 121.12677297035033 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2382.2828087646226,
            "unit": "ns/iter",
            "extra": "iterations: 293547\ncpu: 2380.988393681424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.07047481966368,
            "unit": "ns/iter",
            "extra": "iterations: 27591535\ncpu: 25.055256983708986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1499.5678649600516,
            "unit": "ns/iter",
            "extra": "iterations: 452363\ncpu: 1498.6614731974068 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1303.7685964604814,
            "unit": "ns/iter",
            "extra": "iterations: 538275\ncpu: 1303.036551948354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1577.9965553660722,
            "unit": "ns/iter",
            "extra": "iterations: 445786\ncpu: 1577.0504232972783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 420.2591957426644,
            "unit": "ns/iter",
            "extra": "iterations: 1667195\ncpu: 420.0348489528816 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2155.2973203254087,
            "unit": "ns/iter",
            "extra": "iterations: 340662\ncpu: 2122.4821083654756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 119.08968396846984,
            "unit": "ns/iter",
            "extra": "iterations: 5929289\ncpu: 119.02944855614277 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 492.4180341320232,
            "unit": "ns/iter",
            "extra": "iterations: 1463667\ncpu: 491.48952596457934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 366.8178025826329,
            "unit": "ns/iter",
            "extra": "iterations: 1867150\ncpu: 366.58758000160753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 918.1888831426352,
            "unit": "ns/iter",
            "extra": "iterations: 777268\ncpu: 916.9758693269241 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 182.72044115447258,
            "unit": "ns/iter",
            "extra": "iterations: 3843894\ncpu: 182.6252232761883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 638.6564016398779,
            "unit": "ns/iter",
            "extra": "iterations: 1103318\ncpu: 638.3318318018923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1584.6922580291975,
            "unit": "ns/iter",
            "extra": "iterations: 445988\ncpu: 1583.8968761491365 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729197030722,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3683755636.21521,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3683213000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 803.8152754685891,
            "unit": "ns/iter",
            "extra": "iterations: 919782\ncpu: 793.2597071914873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1031.3669140188595,
            "unit": "ns/iter",
            "extra": "iterations: 668188\ncpu: 1025.6424838518503 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 174.9166101336648,
            "unit": "ns/iter",
            "extra": "iterations: 4019316\ncpu: 174.85736379025684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 120.23657603937359,
            "unit": "ns/iter",
            "extra": "iterations: 5730894\ncpu: 120.20306081389758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2398.2007595788677,
            "unit": "ns/iter",
            "extra": "iterations: 292006\ncpu: 2390.8549824318648 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.012190826380472,
            "unit": "ns/iter",
            "extra": "iterations: 27998432\ncpu: 25.011543503579052 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1506.014844623776,
            "unit": "ns/iter",
            "extra": "iterations: 463064\ncpu: 1505.6558056769688 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1302.0407634924456,
            "unit": "ns/iter",
            "extra": "iterations: 538110\ncpu: 1301.7803051420765 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1569.7641634725412,
            "unit": "ns/iter",
            "extra": "iterations: 444693\ncpu: 1569.6514224419982 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 421.3209018762646,
            "unit": "ns/iter",
            "extra": "iterations: 1666191\ncpu: 421.2590273263989 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1971.9653595237776,
            "unit": "ns/iter",
            "extra": "iterations: 356742\ncpu: 1971.848002197666 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.61687467289634,
            "unit": "ns/iter",
            "extra": "iterations: 5918661\ncpu: 118.61196307745954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 473.35411038825805,
            "unit": "ns/iter",
            "extra": "iterations: 1476491\ncpu: 473.35540819415513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 365.3611134519155,
            "unit": "ns/iter",
            "extra": "iterations: 1916784\ncpu: 365.3525905892355 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 906.9982597232604,
            "unit": "ns/iter",
            "extra": "iterations: 762677\ncpu: 905.1656205707019 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 182.51595274493548,
            "unit": "ns/iter",
            "extra": "iterations: 3834482\ncpu: 182.51565661281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 635.2559282296584,
            "unit": "ns/iter",
            "extra": "iterations: 1104432\ncpu: 635.1744607182724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1612.4494743083271,
            "unit": "ns/iter",
            "extra": "iterations: 442332\ncpu: 1612.1420109781855 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729197733176,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3719614028.930664,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3717217000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 763.8410591925949,
            "unit": "ns/iter",
            "extra": "iterations: 884967\ncpu: 763.4589764364084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 997.7627315616592,
            "unit": "ns/iter",
            "extra": "iterations: 706721\ncpu: 997.0907897175836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 172.53264677652334,
            "unit": "ns/iter",
            "extra": "iterations: 4062894\ncpu: 172.44407557765453 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.79021184748625,
            "unit": "ns/iter",
            "extra": "iterations: 5892107\ncpu: 119.70946895567252 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2435.7490667684233,
            "unit": "ns/iter",
            "extra": "iterations: 292354\ncpu: 2429.034663455949 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.080636230006753,
            "unit": "ns/iter",
            "extra": "iterations: 28003472\ncpu: 25.064570564678565 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1498.7662147224219,
            "unit": "ns/iter",
            "extra": "iterations: 468005\ncpu: 1497.8942532665249 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1295.5281003702512,
            "unit": "ns/iter",
            "extra": "iterations: 538230\ncpu: 1294.8237742229132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1636.5617430909363,
            "unit": "ns/iter",
            "extra": "iterations: 434354\ncpu: 1634.7702565188738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.5100962332606,
            "unit": "ns/iter",
            "extra": "iterations: 1594595\ncpu: 418.1851818173267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1965.117004073455,
            "unit": "ns/iter",
            "extra": "iterations: 356049\ncpu: 1963.9403565239656 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.20207153428177,
            "unit": "ns/iter",
            "extra": "iterations: 5921064\ncpu: 118.13586206803356 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 471.71825879243676,
            "unit": "ns/iter",
            "extra": "iterations: 1469943\ncpu: 471.43936873742774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 363.9789495571634,
            "unit": "ns/iter",
            "extra": "iterations: 1908657\ncpu: 363.7945424452912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 919.6275786951899,
            "unit": "ns/iter",
            "extra": "iterations: 751129\ncpu: 919.0791461919313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 192.71892916137563,
            "unit": "ns/iter",
            "extra": "iterations: 3820627\ncpu: 192.57912379303235 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 667.2663325774325,
            "unit": "ns/iter",
            "extra": "iterations: 1016260\ncpu: 666.9179147068712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1568.7382206316956,
            "unit": "ns/iter",
            "extra": "iterations: 446286\ncpu: 1567.8488682145498 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729204919670,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3672581911.087036,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3672184000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 766.9301475301104,
            "unit": "ns/iter",
            "extra": "iterations: 900229\ncpu: 766.4094358213295 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1015.8374091894451,
            "unit": "ns/iter",
            "extra": "iterations: 692672\ncpu: 1015.8314469186001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 174.96318511912554,
            "unit": "ns/iter",
            "extra": "iterations: 4016525\ncpu: 174.94998786264262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 122.5822361180441,
            "unit": "ns/iter",
            "extra": "iterations: 5735072\ncpu: 122.58032680322052 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2572.803752012643,
            "unit": "ns/iter",
            "extra": "iterations: 293256\ncpu: 2569.6047139700436 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.91576264047841,
            "unit": "ns/iter",
            "extra": "iterations: 25764563\ncpu: 26.907384379079094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1656.3038174004919,
            "unit": "ns/iter",
            "extra": "iterations: 428696\ncpu: 1652.5929796405856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1429.2983274019755,
            "unit": "ns/iter",
            "extra": "iterations: 478155\ncpu: 1416.933839445369 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1726.7254555581585,
            "unit": "ns/iter",
            "extra": "iterations: 444191\ncpu: 1716.8132627630923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 460.77346595061056,
            "unit": "ns/iter",
            "extra": "iterations: 1509662\ncpu: 460.14074673668637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2155.1271482400875,
            "unit": "ns/iter",
            "extra": "iterations: 329458\ncpu: 2154.274596458424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 132.06637647473144,
            "unit": "ns/iter",
            "extra": "iterations: 5276846\ncpu: 131.89678076638938 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 493.6615533052313,
            "unit": "ns/iter",
            "extra": "iterations: 1372065\ncpu: 492.824319547545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 378.6703610262367,
            "unit": "ns/iter",
            "extra": "iterations: 1758463\ncpu: 378.32072668006066 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 950.4167147076749,
            "unit": "ns/iter",
            "extra": "iterations: 720320\ncpu: 947.2276210573051 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 201.7162442333074,
            "unit": "ns/iter",
            "extra": "iterations: 3503153\ncpu: 200.81166880236074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 754.464289949321,
            "unit": "ns/iter",
            "extra": "iterations: 906924\ncpu: 744.2916936810575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1705.5168091596186,
            "unit": "ns/iter",
            "extra": "iterations: 401985\ncpu: 1705.143226737321 ns\nthreads: 1"
          }
        ]
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
        "date": 1729207765826,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3688812971.1151123,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3688484999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 772.2687452803319,
            "unit": "ns/iter",
            "extra": "iterations: 913445\ncpu: 772.1822331941173 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1018.1562132564229,
            "unit": "ns/iter",
            "extra": "iterations: 689567\ncpu: 1017.7792730800642 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 175.77197900588473,
            "unit": "ns/iter",
            "extra": "iterations: 3937119\ncpu: 175.7503392709238 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 120.08195503458258,
            "unit": "ns/iter",
            "extra": "iterations: 5839806\ncpu: 120.08087254953345 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2398.3543886903626,
            "unit": "ns/iter",
            "extra": "iterations: 296126\ncpu: 2398.320309597942 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.00273343546259,
            "unit": "ns/iter",
            "extra": "iterations: 28027579\ncpu: 25.001802688701712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1515.1060602578389,
            "unit": "ns/iter",
            "extra": "iterations: 463782\ncpu: 1515.0997667007352 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1293.507700044896,
            "unit": "ns/iter",
            "extra": "iterations: 541465\ncpu: 1293.110358010214 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1617.013663337262,
            "unit": "ns/iter",
            "extra": "iterations: 441128\ncpu: 1616.5648065867476 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 421.69943761417227,
            "unit": "ns/iter",
            "extra": "iterations: 1664982\ncpu: 421.68443863056683 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2028.8833733544516,
            "unit": "ns/iter",
            "extra": "iterations: 345563\ncpu: 2028.8630437865172 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 121.11416553858928,
            "unit": "ns/iter",
            "extra": "iterations: 5776864\ncpu: 121.10844222747835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 475.6213712689871,
            "unit": "ns/iter",
            "extra": "iterations: 1476454\ncpu: 475.3368543821896 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 368.75728462712937,
            "unit": "ns/iter",
            "extra": "iterations: 1851622\ncpu: 367.83749599000237 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 927.0606646594313,
            "unit": "ns/iter",
            "extra": "iterations: 761921\ncpu: 927.019992886403 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 184.09221008008723,
            "unit": "ns/iter",
            "extra": "iterations: 3817897\ncpu: 184.0811839606977 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 680.9839038487075,
            "unit": "ns/iter",
            "extra": "iterations: 1032220\ncpu: 680.8916703803475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1593.1120092450788,
            "unit": "ns/iter",
            "extra": "iterations: 442048\ncpu: 1592.854169682925 ns\nthreads: 1"
          }
        ]
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
        "date": 1729208785757,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4478436231.613159,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4392402000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 842.1478174597952,
            "unit": "ns/iter",
            "extra": "iterations: 834705\ncpu: 841.0707974673688 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1160.7521351634825,
            "unit": "ns/iter",
            "extra": "iterations: 641478\ncpu: 1160.0163996271117 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 200.05360858788077,
            "unit": "ns/iter",
            "extra": "iterations: 3689006\ncpu: 200.0137706471608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 130.63264250521163,
            "unit": "ns/iter",
            "extra": "iterations: 5298936\ncpu: 130.60810698600616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2572.743861432803,
            "unit": "ns/iter",
            "extra": "iterations: 277674\ncpu: 2572.2105778718915 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.271635405097438,
            "unit": "ns/iter",
            "extra": "iterations: 25804549\ncpu: 27.257558347561137 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1608.6822236885814,
            "unit": "ns/iter",
            "extra": "iterations: 431013\ncpu: 1608.2206337163873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1432.0584110318312,
            "unit": "ns/iter",
            "extra": "iterations: 497201\ncpu: 1430.0534391523752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1821.2476787484884,
            "unit": "ns/iter",
            "extra": "iterations: 416699\ncpu: 1820.1123592809179 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 518.6669826507568,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 518.6550000000008 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2231.649149693618,
            "unit": "ns/iter",
            "extra": "iterations: 327138\ncpu: 2231.465008650781 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 129.64395105367646,
            "unit": "ns/iter",
            "extra": "iterations: 5222633\ncpu: 129.5162803896042 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 506.43193239830924,
            "unit": "ns/iter",
            "extra": "iterations: 1346465\ncpu: 506.2976014972546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 403.8499228037253,
            "unit": "ns/iter",
            "extra": "iterations: 1698938\ncpu: 403.63038557027903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 979.4465994389657,
            "unit": "ns/iter",
            "extra": "iterations: 687717\ncpu: 979.3025328732617 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 204.2365554983534,
            "unit": "ns/iter",
            "extra": "iterations: 3511130\ncpu: 204.19864829841043 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 728.0707164333555,
            "unit": "ns/iter",
            "extra": "iterations: 962941\ncpu: 728.0362971355474 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1706.829052994465,
            "unit": "ns/iter",
            "extra": "iterations: 411047\ncpu: 1706.6442523604358 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729211629824,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3956085920.3338623,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3954806999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 814.8170203506382,
            "unit": "ns/iter",
            "extra": "iterations: 862908\ncpu: 814.6754926365255 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1078.8879784635647,
            "unit": "ns/iter",
            "extra": "iterations: 649694\ncpu: 1078.4461608080114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.42863398104575,
            "unit": "ns/iter",
            "extra": "iterations: 3763400\ncpu: 185.4171759579106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 133.0902423385275,
            "unit": "ns/iter",
            "extra": "iterations: 5359919\ncpu: 132.60312329346763 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2537.739415522558,
            "unit": "ns/iter",
            "extra": "iterations: 275674\ncpu: 2536.735419372147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.159195657044226,
            "unit": "ns/iter",
            "extra": "iterations: 25943510\ncpu: 27.03589452622257 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1762.5881749564137,
            "unit": "ns/iter",
            "extra": "iterations: 405503\ncpu: 1732.9810137039715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1385.2979914306106,
            "unit": "ns/iter",
            "extra": "iterations: 499686\ncpu: 1385.1518753777361 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1677.7270046813626,
            "unit": "ns/iter",
            "extra": "iterations: 417079\ncpu: 1677.2673762045076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 450.56852013803575,
            "unit": "ns/iter",
            "extra": "iterations: 1560393\ncpu: 450.49099810111903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2101.2900887988103,
            "unit": "ns/iter",
            "extra": "iterations: 335598\ncpu: 2100.9839152795894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 126.42909971911864,
            "unit": "ns/iter",
            "extra": "iterations: 5515589\ncpu: 126.41913674133419 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 502.3862093588174,
            "unit": "ns/iter",
            "extra": "iterations: 1395729\ncpu: 502.1992091587981 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 393.2315335941527,
            "unit": "ns/iter",
            "extra": "iterations: 1771636\ncpu: 393.23201831527575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 979.4661160216978,
            "unit": "ns/iter",
            "extra": "iterations: 725291\ncpu: 977.556594525511 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 199.17759446594044,
            "unit": "ns/iter",
            "extra": "iterations: 3568734\ncpu: 198.95458725699353 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 723.9587189073885,
            "unit": "ns/iter",
            "extra": "iterations: 973209\ncpu: 723.6143521073074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1701.6796914097647,
            "unit": "ns/iter",
            "extra": "iterations: 407602\ncpu: 1700.9607411151121 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729212071390,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3746723890.3045654,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3744312000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 774.0633634346303,
            "unit": "ns/iter",
            "extra": "iterations: 874530\ncpu: 773.6143985912429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1012.119898638377,
            "unit": "ns/iter",
            "extra": "iterations: 681431\ncpu: 1011.4846550861342 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 176.04320050857845,
            "unit": "ns/iter",
            "extra": "iterations: 4049590\ncpu: 175.94991097864212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.05599230674923,
            "unit": "ns/iter",
            "extra": "iterations: 5861812\ncpu: 118.991874867362 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2374.5975489352513,
            "unit": "ns/iter",
            "extra": "iterations: 291849\ncpu: 2373.343749678765 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.06515148229674,
            "unit": "ns/iter",
            "extra": "iterations: 27923712\ncpu: 25.043482757593235 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1544.8826465536943,
            "unit": "ns/iter",
            "extra": "iterations: 464900\ncpu: 1541.077651107766 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1301.8843968891563,
            "unit": "ns/iter",
            "extra": "iterations: 537226\ncpu: 1301.132111997558 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1577.8811237025425,
            "unit": "ns/iter",
            "extra": "iterations: 442707\ncpu: 1576.912043405683 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 419.18990613899524,
            "unit": "ns/iter",
            "extra": "iterations: 1668108\ncpu: 418.9542883314504 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1985.496004158297,
            "unit": "ns/iter",
            "extra": "iterations: 357646\ncpu: 1984.2665652628557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 120.79504094400505,
            "unit": "ns/iter",
            "extra": "iterations: 5938696\ncpu: 120.69215194716145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 474.51154167630057,
            "unit": "ns/iter",
            "extra": "iterations: 1456582\ncpu: 474.2644080456857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 370.11583684622263,
            "unit": "ns/iter",
            "extra": "iterations: 1902991\ncpu: 368.75266357013817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 920.9687130217485,
            "unit": "ns/iter",
            "extra": "iterations: 730697\ncpu: 920.4800348160752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 185.70279235482553,
            "unit": "ns/iter",
            "extra": "iterations: 3702685\ncpu: 185.6090917806945 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 741.6861480105231,
            "unit": "ns/iter",
            "extra": "iterations: 994135\ncpu: 730.3183169287904 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1585.7647061581874,
            "unit": "ns/iter",
            "extra": "iterations: 440831\ncpu: 1584.8726609516975 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729267189889,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3687824964.5233154,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3687070000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 760.8707774827861,
            "unit": "ns/iter",
            "extra": "iterations: 921853\ncpu: 760.8208684030959 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1003.1121585699327,
            "unit": "ns/iter",
            "extra": "iterations: 700525\ncpu: 1003.0905392384278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 172.23974724852292,
            "unit": "ns/iter",
            "extra": "iterations: 4051840\ncpu: 172.22052203443386 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 136.81450571391144,
            "unit": "ns/iter",
            "extra": "iterations: 5858721\ncpu: 132.684249685213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2509.5243621150785,
            "unit": "ns/iter",
            "extra": "iterations: 262933\ncpu: 2501.61067648412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.62542505489107,
            "unit": "ns/iter",
            "extra": "iterations: 27553306\ncpu: 25.58836315322739 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1615.339845194503,
            "unit": "ns/iter",
            "extra": "iterations: 447379\ncpu: 1600.8194394461955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1359.3759798233461,
            "unit": "ns/iter",
            "extra": "iterations: 499722\ncpu: 1343.080752898609 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1584.6700812125653,
            "unit": "ns/iter",
            "extra": "iterations: 416845\ncpu: 1582.7729731674865 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 436.2042595162268,
            "unit": "ns/iter",
            "extra": "iterations: 1656178\ncpu: 436.03948367868645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2032.183057660832,
            "unit": "ns/iter",
            "extra": "iterations: 356708\ncpu: 2031.0590174596566 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 124.9982281525934,
            "unit": "ns/iter",
            "extra": "iterations: 5740434\ncpu: 124.92731385815098 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 506.7607904892091,
            "unit": "ns/iter",
            "extra": "iterations: 1364948\ncpu: 506.32624832594416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 399.4632940408344,
            "unit": "ns/iter",
            "extra": "iterations: 1777182\ncpu: 397.1033917741689 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 993.0356497420639,
            "unit": "ns/iter",
            "extra": "iterations: 716237\ncpu: 990.7781921347251 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 211.00310697695826,
            "unit": "ns/iter",
            "extra": "iterations: 3419054\ncpu: 210.93524700107065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 813.623714949709,
            "unit": "ns/iter",
            "extra": "iterations: 847837\ncpu: 813.6245528326771 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1891.045126459428,
            "unit": "ns/iter",
            "extra": "iterations: 398322\ncpu: 1890.829529877829 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729274421710,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4103177309.036255,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4091846000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 849.1926701532915,
            "unit": "ns/iter",
            "extra": "iterations: 830171\ncpu: 849.0768769325838 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1099.3512603087083,
            "unit": "ns/iter",
            "extra": "iterations: 637860\ncpu: 1099.2898128115874 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 186.58559949038593,
            "unit": "ns/iter",
            "extra": "iterations: 3781392\ncpu: 186.5664813380892 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.94060547257594,
            "unit": "ns/iter",
            "extra": "iterations: 5422741\ncpu: 127.91022104872789 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2557.040156908505,
            "unit": "ns/iter",
            "extra": "iterations: 272731\ncpu: 2556.750057749211 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.00978973433835,
            "unit": "ns/iter",
            "extra": "iterations: 26007609\ncpu: 27.00205928195852 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1621.8247649500427,
            "unit": "ns/iter",
            "extra": "iterations: 432876\ncpu: 1621.582162097231 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1402.9607946723556,
            "unit": "ns/iter",
            "extra": "iterations: 502458\ncpu: 1402.4515481891017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1682.4541044798505,
            "unit": "ns/iter",
            "extra": "iterations: 413282\ncpu: 1682.364583988659 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 452.5010814984016,
            "unit": "ns/iter",
            "extra": "iterations: 1548697\ncpu: 452.37770848655185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2224.1639382702124,
            "unit": "ns/iter",
            "extra": "iterations: 327748\ncpu: 2221.5360581910495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 128.3528897280039,
            "unit": "ns/iter",
            "extra": "iterations: 5184840\ncpu: 128.2843829317784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 514.3488382614685,
            "unit": "ns/iter",
            "extra": "iterations: 1353834\ncpu: 514.2144457887747 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 399.5934280640964,
            "unit": "ns/iter",
            "extra": "iterations: 1753863\ncpu: 398.81450261508513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 992.792327816981,
            "unit": "ns/iter",
            "extra": "iterations: 685086\ncpu: 992.694347862898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 198.49473848372708,
            "unit": "ns/iter",
            "extra": "iterations: 3344114\ncpu: 198.49323318523224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 745.509869034216,
            "unit": "ns/iter",
            "extra": "iterations: 979802\ncpu: 741.188525845017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1915.4318443166783,
            "unit": "ns/iter",
            "extra": "iterations: 385713\ncpu: 1886.8199931036822 ns\nthreads: 1"
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
        "date": 1729278514145,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4005428075.7904053,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4003663000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 823.6997920004092,
            "unit": "ns/iter",
            "extra": "iterations: 847724\ncpu: 823.5994262283475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1209.5018633037628,
            "unit": "ns/iter",
            "extra": "iterations: 638482\ncpu: 1201.0487374741974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 185.51574761278184,
            "unit": "ns/iter",
            "extra": "iterations: 3709572\ncpu: 185.49687133717842 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 127.10985525885285,
            "unit": "ns/iter",
            "extra": "iterations: 5545038\ncpu: 127.09236618396449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2564.319732943825,
            "unit": "ns/iter",
            "extra": "iterations: 269574\ncpu: 2563.700505241599 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.10918260356183,
            "unit": "ns/iter",
            "extra": "iterations: 25943318\ncpu: 27.107326826892358 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1619.590336673234,
            "unit": "ns/iter",
            "extra": "iterations: 432954\ncpu: 1619.4399405017625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1394.4366863462792,
            "unit": "ns/iter",
            "extra": "iterations: 498881\ncpu: 1393.8253812031344 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1696.7345341903624,
            "unit": "ns/iter",
            "extra": "iterations: 418623\ncpu: 1694.9713704215983 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 449.0410142660554,
            "unit": "ns/iter",
            "extra": "iterations: 1561378\ncpu: 448.95662677455437 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2116.299000373185,
            "unit": "ns/iter",
            "extra": "iterations: 326468\ncpu: 2115.971550044726 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 127.49924320895788,
            "unit": "ns/iter",
            "extra": "iterations: 5509772\ncpu: 127.36189446677635 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 503.7594659559585,
            "unit": "ns/iter",
            "extra": "iterations: 1398322\ncpu: 503.6715434642392 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 399.5149100390883,
            "unit": "ns/iter",
            "extra": "iterations: 1761246\ncpu: 398.7710972799941 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1007.083240775615,
            "unit": "ns/iter",
            "extra": "iterations: 705610\ncpu: 1006.9996173523623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 195.56122275705394,
            "unit": "ns/iter",
            "extra": "iterations: 3557290\ncpu: 195.55026438665396 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 716.4304870873601,
            "unit": "ns/iter",
            "extra": "iterations: 977217\ncpu: 715.9341272204629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1686.3525105639203,
            "unit": "ns/iter",
            "extra": "iterations: 415381\ncpu: 1686.0256005931992 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729280020273,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3699413061.141968,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3697199000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 767.5925858377852,
            "unit": "ns/iter",
            "extra": "iterations: 913671\ncpu: 767.1612648316508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1022.199734831091,
            "unit": "ns/iter",
            "extra": "iterations: 696178\ncpu: 1021.2373846918467 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 174.56267106903414,
            "unit": "ns/iter",
            "extra": "iterations: 4015949\ncpu: 174.47059213152355 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.32700185309683,
            "unit": "ns/iter",
            "extra": "iterations: 5875786\ncpu: 119.22268782423309 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2387.477055509561,
            "unit": "ns/iter",
            "extra": "iterations: 291860\ncpu: 2386.274241074487 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.1133523576082,
            "unit": "ns/iter",
            "extra": "iterations: 27853712\ncpu: 25.09590104184312 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1507.424704170581,
            "unit": "ns/iter",
            "extra": "iterations: 464083\ncpu: 1506.5236175425512 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1294.3113970445368,
            "unit": "ns/iter",
            "extra": "iterations: 538192\ncpu: 1293.2968160061841 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1575.283245004437,
            "unit": "ns/iter",
            "extra": "iterations: 446679\ncpu: 1574.280411660276 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 419.9542681475069,
            "unit": "ns/iter",
            "extra": "iterations: 1670920\ncpu: 419.72446316999117 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1981.0541062443874,
            "unit": "ns/iter",
            "extra": "iterations: 354221\ncpu: 1979.9955395078227 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 119.33937298394622,
            "unit": "ns/iter",
            "extra": "iterations: 5878747\ncpu: 119.2599375343081 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 478.09349108554875,
            "unit": "ns/iter",
            "extra": "iterations: 1458978\ncpu: 477.8015843967472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 369.3560431928441,
            "unit": "ns/iter",
            "extra": "iterations: 1894503\ncpu: 369.1516983609937 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 920.2722701594593,
            "unit": "ns/iter",
            "extra": "iterations: 764927\ncpu: 919.7452828832056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 182.03625578375863,
            "unit": "ns/iter",
            "extra": "iterations: 3837383\ncpu: 181.90730505659715 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 667.0234782580203,
            "unit": "ns/iter",
            "extra": "iterations: 1050263\ncpu: 666.6739664255516 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1583.4202562597627,
            "unit": "ns/iter",
            "extra": "iterations: 441930\ncpu: 1582.6058425542467 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729280666570,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4216989278.793335,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4212415000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 839.7508646505753,
            "unit": "ns/iter",
            "extra": "iterations: 871319\ncpu: 839.1507587921303 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1100.7581761564202,
            "unit": "ns/iter",
            "extra": "iterations: 645733\ncpu: 1100.1280715094335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 188.4372928953173,
            "unit": "ns/iter",
            "extra": "iterations: 3764169\ncpu: 188.11801489253014 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 134.0132832588773,
            "unit": "ns/iter",
            "extra": "iterations: 5481383\ncpu: 133.91437890765883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2798.265850991803,
            "unit": "ns/iter",
            "extra": "iterations: 229460\ncpu: 2796.7358145210546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.3728808805451,
            "unit": "ns/iter",
            "extra": "iterations: 25920070\ncpu: 27.354285694444517 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1532.063193028457,
            "unit": "ns/iter",
            "extra": "iterations: 456737\ncpu: 1531.154690773906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1376.9778511031523,
            "unit": "ns/iter",
            "extra": "iterations: 524521\ncpu: 1376.225165436656 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1687.9876011424521,
            "unit": "ns/iter",
            "extra": "iterations: 424217\ncpu: 1686.8819495682612 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 439.0490880745043,
            "unit": "ns/iter",
            "extra": "iterations: 1610925\ncpu: 436.8577059763798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2126.754004040983,
            "unit": "ns/iter",
            "extra": "iterations: 325441\ncpu: 2125.432874161529 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 134.53533243040226,
            "unit": "ns/iter",
            "extra": "iterations: 5104385\ncpu: 134.3928798474253 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 504.4739359521633,
            "unit": "ns/iter",
            "extra": "iterations: 1366227\ncpu: 504.14169826829664 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 391.87235091800363,
            "unit": "ns/iter",
            "extra": "iterations: 1743514\ncpu: 391.66132305217974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 983.939202174285,
            "unit": "ns/iter",
            "extra": "iterations: 692350\ncpu: 983.1313641944107 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 213.0257541005896,
            "unit": "ns/iter",
            "extra": "iterations: 3543873\ncpu: 212.8476387274607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 747.0403832760336,
            "unit": "ns/iter",
            "extra": "iterations: 964719\ncpu: 746.4919836760776 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1654.0024015638564,
            "unit": "ns/iter",
            "extra": "iterations: 414000\ncpu: 1653.043478260865 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729281641085,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3648833036.4227295,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3646306999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 749.0636453081219,
            "unit": "ns/iter",
            "extra": "iterations: 940708\ncpu: 748.611683965694 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1019.5126077085768,
            "unit": "ns/iter",
            "extra": "iterations: 698066\ncpu: 1018.9237120845291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 172.7494293606616,
            "unit": "ns/iter",
            "extra": "iterations: 4071590\ncpu: 172.66055766911694 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.21482606311808,
            "unit": "ns/iter",
            "extra": "iterations: 5684310\ncpu: 119.14814638891949 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2473.6717641204136,
            "unit": "ns/iter",
            "extra": "iterations: 279140\ncpu: 2472.297055241094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.12556660924745,
            "unit": "ns/iter",
            "extra": "iterations: 27977953\ncpu: 25.111665603269806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1510.6351053867672,
            "unit": "ns/iter",
            "extra": "iterations: 466014\ncpu: 1509.2550867570499 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1293.3091348879016,
            "unit": "ns/iter",
            "extra": "iterations: 542148\ncpu: 1292.5179102385343 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1561.811247972407,
            "unit": "ns/iter",
            "extra": "iterations: 448560\ncpu: 1560.7923131799523 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.5612480754879,
            "unit": "ns/iter",
            "extra": "iterations: 1672852\ncpu: 418.33826303821286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2145.2880466904803,
            "unit": "ns/iter",
            "extra": "iterations: 295557\ncpu: 2143.975612149267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 119.37902041742858,
            "unit": "ns/iter",
            "extra": "iterations: 5896872\ncpu: 119.31393457412698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 470.23090685016473,
            "unit": "ns/iter",
            "extra": "iterations: 1496718\ncpu: 469.9489148924515 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 282.8268892076517,
            "unit": "ns/iter",
            "extra": "iterations: 2488243\ncpu: 282.3345629827942 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 926.8710907944356,
            "unit": "ns/iter",
            "extra": "iterations: 776475\ncpu: 925.7941337454507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 181.75049944418436,
            "unit": "ns/iter",
            "extra": "iterations: 3851148\ncpu: 181.65596336469062 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 672.8796737293644,
            "unit": "ns/iter",
            "extra": "iterations: 1044340\ncpu: 672.4582032671389 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1578.3586259831397,
            "unit": "ns/iter",
            "extra": "iterations: 437107\ncpu: 1577.50619413554 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729286749418,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3971025943.7561035,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3896289000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 763.9224764593976,
            "unit": "ns/iter",
            "extra": "iterations: 915428\ncpu: 763.544484110165 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1027.9583533546374,
            "unit": "ns/iter",
            "extra": "iterations: 671721\ncpu: 1026.9933499175988 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 176.01542154983176,
            "unit": "ns/iter",
            "extra": "iterations: 4039168\ncpu: 175.98401452972482 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 125.99505088019885,
            "unit": "ns/iter",
            "extra": "iterations: 5697635\ncpu: 125.94014885123418 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2526.0378853124807,
            "unit": "ns/iter",
            "extra": "iterations: 288078\ncpu: 2525.0557140774386 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.872721092177272,
            "unit": "ns/iter",
            "extra": "iterations: 26416091\ncpu: 26.87021331051594 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1557.8131145630925,
            "unit": "ns/iter",
            "extra": "iterations: 407816\ncpu: 1557.415599191794 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1350.2530219404857,
            "unit": "ns/iter",
            "extra": "iterations: 514211\ncpu: 1350.185040771206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1665.8870402981054,
            "unit": "ns/iter",
            "extra": "iterations: 415174\ncpu: 1665.7449647617652 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 433.4175583676603,
            "unit": "ns/iter",
            "extra": "iterations: 1505966\ncpu: 433.28733849236994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2221.83986978432,
            "unit": "ns/iter",
            "extra": "iterations: 338955\ncpu: 2194.143765396584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 160.39772032959903,
            "unit": "ns/iter",
            "extra": "iterations: 5371311\ncpu: 157.68217479866632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 544.2777146827644,
            "unit": "ns/iter",
            "extra": "iterations: 1297762\ncpu: 543.8886328926259 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 343.80505037136817,
            "unit": "ns/iter",
            "extra": "iterations: 2162897\ncpu: 342.5794201018381 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 967.2969007968774,
            "unit": "ns/iter",
            "extra": "iterations: 740200\ncpu: 965.2864090786261 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 195.99711225089135,
            "unit": "ns/iter",
            "extra": "iterations: 3610090\ncpu: 195.980709622197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 771.8658340364599,
            "unit": "ns/iter",
            "extra": "iterations: 984889\ncpu: 771.729606077433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1998.9006746643129,
            "unit": "ns/iter",
            "extra": "iterations: 300208\ncpu: 1998.1113094920938 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729360239736,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3644559144.973755,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3644284000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 824.5863583251403,
            "unit": "ns/iter",
            "extra": "iterations: 803130\ncpu: 816.6448769190548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1036.1289636743759,
            "unit": "ns/iter",
            "extra": "iterations: 679592\ncpu: 1036.0377991500793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 172.19349459793182,
            "unit": "ns/iter",
            "extra": "iterations: 4056772\ncpu: 172.19109183360553 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.28118301018954,
            "unit": "ns/iter",
            "extra": "iterations: 5868151\ncpu: 119.25085090686996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2408.2074181913135,
            "unit": "ns/iter",
            "extra": "iterations: 291244\ncpu: 2408.022139511897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.017690504568375,
            "unit": "ns/iter",
            "extra": "iterations: 28007506\ncpu: 25.015472637942125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1525.1432844015533,
            "unit": "ns/iter",
            "extra": "iterations: 466322\ncpu: 1525.1478592045864 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1287.2103815558908,
            "unit": "ns/iter",
            "extra": "iterations: 531503\ncpu: 1287.1837035726944 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1561.6129764661603,
            "unit": "ns/iter",
            "extra": "iterations: 447087\ncpu: 1561.2464688080872 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 421.78081380461356,
            "unit": "ns/iter",
            "extra": "iterations: 1676342\ncpu: 421.7385235232436 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1970.0540310770705,
            "unit": "ns/iter",
            "extra": "iterations: 354004\ncpu: 1969.8026011005502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 134.0058570689844,
            "unit": "ns/iter",
            "extra": "iterations: 5366452\ncpu: 133.75168547114623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 474.4219011363018,
            "unit": "ns/iter",
            "extra": "iterations: 1478334\ncpu: 474.39550196369527 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 304.363713195043,
            "unit": "ns/iter",
            "extra": "iterations: 2463644\ncpu: 304.0232273818769 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 914.1251253706296,
            "unit": "ns/iter",
            "extra": "iterations: 733868\ncpu: 913.1996489831964 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 181.1315464988585,
            "unit": "ns/iter",
            "extra": "iterations: 3856176\ncpu: 181.1180298824549 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 672.3568729911112,
            "unit": "ns/iter",
            "extra": "iterations: 1050609\ncpu: 672.1920333825459 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1580.4341962413243,
            "unit": "ns/iter",
            "extra": "iterations: 444953\ncpu: 1580.382647155996 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729361432344,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3688693046.569824,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3688257000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 759.3153022325389,
            "unit": "ns/iter",
            "extra": "iterations: 912742\ncpu: 759.2002997561189 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1014.1325432606872,
            "unit": "ns/iter",
            "extra": "iterations: 680901\ncpu: 1013.9491644159727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 178.28960670548045,
            "unit": "ns/iter",
            "extra": "iterations: 3992039\ncpu: 178.28357889289154 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 120.50537589651769,
            "unit": "ns/iter",
            "extra": "iterations: 5872138\ncpu: 120.49018602764444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2420.0790059933884,
            "unit": "ns/iter",
            "extra": "iterations: 285346\ncpu: 2419.9708424158734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.129504320106456,
            "unit": "ns/iter",
            "extra": "iterations: 27947905\ncpu: 25.127607954871735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1509.6979653295894,
            "unit": "ns/iter",
            "extra": "iterations: 465122\ncpu: 1509.4878332996486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1299.728321961598,
            "unit": "ns/iter",
            "extra": "iterations: 540290\ncpu: 1299.6631438671818 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1579.9917264071278,
            "unit": "ns/iter",
            "extra": "iterations: 443372\ncpu: 1579.7727416255452 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 421.55575171828866,
            "unit": "ns/iter",
            "extra": "iterations: 1665929\ncpu: 421.54497580629265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2007.2167935905654,
            "unit": "ns/iter",
            "extra": "iterations: 347505\ncpu: 2007.15673155782 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 125.41304526703537,
            "unit": "ns/iter",
            "extra": "iterations: 5337074\ncpu: 125.34002713846536 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 507.112979888916,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 503.57300000000293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 284.07347260812264,
            "unit": "ns/iter",
            "extra": "iterations: 2424679\ncpu: 284.0664681799109 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 921.054126350759,
            "unit": "ns/iter",
            "extra": "iterations: 759244\ncpu: 919.0932032390108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 212.35942106695322,
            "unit": "ns/iter",
            "extra": "iterations: 3284473\ncpu: 212.3013341866412 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 684.6809269893611,
            "unit": "ns/iter",
            "extra": "iterations: 1024290\ncpu: 684.6156850110809 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1581.2189005417179,
            "unit": "ns/iter",
            "extra": "iterations: 446047\ncpu: 1581.1853907772083 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729362517904,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3679382801.055908,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3678703000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 802.096405826258,
            "unit": "ns/iter",
            "extra": "iterations: 857559\ncpu: 801.8946801327945 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1023.1129792564009,
            "unit": "ns/iter",
            "extra": "iterations: 695362\ncpu: 1022.8542830928354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 175.9478130117583,
            "unit": "ns/iter",
            "extra": "iterations: 3993155\ncpu: 175.94233131446163 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.49425332852685,
            "unit": "ns/iter",
            "extra": "iterations: 5844926\ncpu: 119.48363418116844 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2419.8864769080615,
            "unit": "ns/iter",
            "extra": "iterations: 291012\ncpu: 2419.834920896737 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.263293848404427,
            "unit": "ns/iter",
            "extra": "iterations: 27996752\ncpu: 25.23867768661168 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1609.8330324619071,
            "unit": "ns/iter",
            "extra": "iterations: 432689\ncpu: 1594.8937920769863 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1288.7508036888044,
            "unit": "ns/iter",
            "extra": "iterations: 529685\ncpu: 1288.724430557784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1569.414619141043,
            "unit": "ns/iter",
            "extra": "iterations: 443833\ncpu: 1568.655327566895 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.44974869639253,
            "unit": "ns/iter",
            "extra": "iterations: 1655876\ncpu: 418.32600991861693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1980.5085364423235,
            "unit": "ns/iter",
            "extra": "iterations: 352727\ncpu: 1980.4834900645494 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 119.12648841489421,
            "unit": "ns/iter",
            "extra": "iterations: 5885518\ncpu: 119.08994246555663 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 470.214922395894,
            "unit": "ns/iter",
            "extra": "iterations: 1489289\ncpu: 470.19282355540366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 286.4378721566362,
            "unit": "ns/iter",
            "extra": "iterations: 2472162\ncpu: 286.4189320926379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 921.8304630855741,
            "unit": "ns/iter",
            "extra": "iterations: 757404\ncpu: 921.8316776779617 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 212.8545845198496,
            "unit": "ns/iter",
            "extra": "iterations: 3282024\ncpu: 212.84701147828372 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 675.2666601353719,
            "unit": "ns/iter",
            "extra": "iterations: 1041667\ncpu: 675.2081039334093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1599.3205107359954,
            "unit": "ns/iter",
            "extra": "iterations: 446953\ncpu: 1599.0003423178787 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729363662689,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3650653123.855591,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3649909000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 755.127605720941,
            "unit": "ns/iter",
            "extra": "iterations: 918900\ncpu: 755.0810751986074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1036.106836792338,
            "unit": "ns/iter",
            "extra": "iterations: 673556\ncpu: 1036.0890556984125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 173.6507447240244,
            "unit": "ns/iter",
            "extra": "iterations: 4045775\ncpu: 173.63990829939897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 121.6846259348882,
            "unit": "ns/iter",
            "extra": "iterations: 5792736\ncpu: 121.68256934201706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2511.4795704849116,
            "unit": "ns/iter",
            "extra": "iterations: 275135\ncpu: 2510.901920875207 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.995211830285754,
            "unit": "ns/iter",
            "extra": "iterations: 27931623\ncpu: 24.993320295064805 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1506.525156516039,
            "unit": "ns/iter",
            "extra": "iterations: 466589\ncpu: 1506.4607181052263 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1292.951405902741,
            "unit": "ns/iter",
            "extra": "iterations: 540674\ncpu: 1292.9473213063739 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1598.0784967720763,
            "unit": "ns/iter",
            "extra": "iterations: 445202\ncpu: 1598.0116890759646 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 422.03293478450735,
            "unit": "ns/iter",
            "extra": "iterations: 1658304\ncpu: 421.92324205935773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1998.5719200647734,
            "unit": "ns/iter",
            "extra": "iterations: 355038\ncpu: 1998.4987522462384 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 120.07760676713646,
            "unit": "ns/iter",
            "extra": "iterations: 5891016\ncpu: 120.07436408252829 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 480.4131529754299,
            "unit": "ns/iter",
            "extra": "iterations: 1440181\ncpu: 480.3993386942339 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 306.4275059174857,
            "unit": "ns/iter",
            "extra": "iterations: 2430134\ncpu: 302.9018152908452 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 919.5035989305603,
            "unit": "ns/iter",
            "extra": "iterations: 759986\ncpu: 919.3590408244347 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 209.85477289885625,
            "unit": "ns/iter",
            "extra": "iterations: 3334953\ncpu: 209.84733517983602 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 670.531884424421,
            "unit": "ns/iter",
            "extra": "iterations: 1045385\ncpu: 670.528082955082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1440.0628849546488,
            "unit": "ns/iter",
            "extra": "iterations: 483756\ncpu: 1439.8663789182965 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729363819607,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3913076877.593994,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3908795999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 764.6036538706732,
            "unit": "ns/iter",
            "extra": "iterations: 935766\ncpu: 764.568278821842 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1025.5294962305222,
            "unit": "ns/iter",
            "extra": "iterations: 680305\ncpu: 1025.3650935977237 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 173.6006679261896,
            "unit": "ns/iter",
            "extra": "iterations: 4041384\ncpu: 173.556385634228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 120.86058144227792,
            "unit": "ns/iter",
            "extra": "iterations: 5847514\ncpu: 120.85717109869282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2506.041031761704,
            "unit": "ns/iter",
            "extra": "iterations: 284783\ncpu: 2503.5728958540367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.044207579603583,
            "unit": "ns/iter",
            "extra": "iterations: 27956165\ncpu: 25.039092450627606 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1530.8268778088275,
            "unit": "ns/iter",
            "extra": "iterations: 458385\ncpu: 1530.7961647959644 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1296.465502180864,
            "unit": "ns/iter",
            "extra": "iterations: 536160\ncpu: 1296.3443748134916 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1581.1603214205704,
            "unit": "ns/iter",
            "extra": "iterations: 441164\ncpu: 1581.07642509362 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.67884711486755,
            "unit": "ns/iter",
            "extra": "iterations: 1673820\ncpu: 418.64656892616915 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1985.8191766623738,
            "unit": "ns/iter",
            "extra": "iterations: 353630\ncpu: 1985.5922857223727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.45691825022475,
            "unit": "ns/iter",
            "extra": "iterations: 5928686\ncpu: 118.4501928420561 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 478.4472782800372,
            "unit": "ns/iter",
            "extra": "iterations: 1468312\ncpu: 478.418755686802 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 298.61805561783905,
            "unit": "ns/iter",
            "extra": "iterations: 2322934\ncpu: 296.101826397134 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 934.2408085537352,
            "unit": "ns/iter",
            "extra": "iterations: 728855\ncpu: 930.2152005542888 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 210.4472513321466,
            "unit": "ns/iter",
            "extra": "iterations: 3340523\ncpu: 210.2856349140536 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 681.3511911253548,
            "unit": "ns/iter",
            "extra": "iterations: 980873\ncpu: 681.2727029900908 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1471.063551976854,
            "unit": "ns/iter",
            "extra": "iterations: 471733\ncpu: 1470.946488797689 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729366588287,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3748144865.0360107,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3739103000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 808.3279587214785,
            "unit": "ns/iter",
            "extra": "iterations: 932687\ncpu: 807.6707405592658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1045.3571202237347,
            "unit": "ns/iter",
            "extra": "iterations: 623458\ncpu: 1044.8626852169689 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 175.5730958387618,
            "unit": "ns/iter",
            "extra": "iterations: 3978629\ncpu: 175.56122976030184 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.33920482256892,
            "unit": "ns/iter",
            "extra": "iterations: 5862499\ncpu: 119.32283485250902 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2446.291945311642,
            "unit": "ns/iter",
            "extra": "iterations: 284500\ncpu: 2445.9718804920963 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.98756684091269,
            "unit": "ns/iter",
            "extra": "iterations: 27874342\ncpu: 24.986275909221483 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1471.5590132354002,
            "unit": "ns/iter",
            "extra": "iterations: 473979\ncpu: 1471.5905135037576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1261.52361217501,
            "unit": "ns/iter",
            "extra": "iterations: 553920\ncpu: 1261.4745811669547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1539.442557717116,
            "unit": "ns/iter",
            "extra": "iterations: 455394\ncpu: 1539.0013922010378 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.67070365167115,
            "unit": "ns/iter",
            "extra": "iterations: 1664855\ncpu: 418.66829243387485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1960.2225446294256,
            "unit": "ns/iter",
            "extra": "iterations: 354702\ncpu: 1960.1750201577665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.47899703269015,
            "unit": "ns/iter",
            "extra": "iterations: 5874011\ncpu: 118.46538932256027 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 488.77634141229566,
            "unit": "ns/iter",
            "extra": "iterations: 1428872\ncpu: 488.75056688072794 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 282.2256429048731,
            "unit": "ns/iter",
            "extra": "iterations: 2479948\ncpu: 282.19785253561815 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 903.2747455237186,
            "unit": "ns/iter",
            "extra": "iterations: 775288\ncpu: 903.2372486095472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 209.2205395457705,
            "unit": "ns/iter",
            "extra": "iterations: 3354595\ncpu: 208.70716137119365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 667.977088532762,
            "unit": "ns/iter",
            "extra": "iterations: 1045572\ncpu: 667.9511310555346 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1455.577056535444,
            "unit": "ns/iter",
            "extra": "iterations: 481192\ncpu: 1455.5167168198946 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729368214824,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3830832242.9656982,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3830009000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 751.3191864804704,
            "unit": "ns/iter",
            "extra": "iterations: 966878\ncpu: 751.2147344339197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1010.8918060528316,
            "unit": "ns/iter",
            "extra": "iterations: 693736\ncpu: 1010.8081460382629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 173.47301888326226,
            "unit": "ns/iter",
            "extra": "iterations: 4025001\ncpu: 173.47001901365957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.3982644870189,
            "unit": "ns/iter",
            "extra": "iterations: 5887449\ncpu: 119.3792082105511 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2439.857247978349,
            "unit": "ns/iter",
            "extra": "iterations: 287598\ncpu: 2439.5371316907626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.07911567422265,
            "unit": "ns/iter",
            "extra": "iterations: 28013222\ncpu: 25.077265299935828 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1537.752849632223,
            "unit": "ns/iter",
            "extra": "iterations: 475715\ncpu: 1515.9643904438608 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1276.8763368661187,
            "unit": "ns/iter",
            "extra": "iterations: 535762\ncpu: 1272.7199764074342 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1618.9519934132575,
            "unit": "ns/iter",
            "extra": "iterations: 455255\ncpu: 1601.3794466837282 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 418.6710588568261,
            "unit": "ns/iter",
            "extra": "iterations: 1595995\ncpu: 418.6623391677297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1973.3157286359058,
            "unit": "ns/iter",
            "extra": "iterations: 355045\ncpu: 1972.2119731301625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 117.94849483999108,
            "unit": "ns/iter",
            "extra": "iterations: 5936379\ncpu: 117.93367640442061 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 470.49174025472036,
            "unit": "ns/iter",
            "extra": "iterations: 1475881\ncpu: 470.43291430677533 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 282.0840191066471,
            "unit": "ns/iter",
            "extra": "iterations: 2472441\ncpu: 282.0136051780415 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 918.7954236985805,
            "unit": "ns/iter",
            "extra": "iterations: 745943\ncpu: 918.0205458057795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 207.86734827294583,
            "unit": "ns/iter",
            "extra": "iterations: 3367716\ncpu: 207.85957010626817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 671.5598010860108,
            "unit": "ns/iter",
            "extra": "iterations: 1045931\ncpu: 671.5567279294708 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1452.242283319409,
            "unit": "ns/iter",
            "extra": "iterations: 483512\ncpu: 1452.214215986364 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729368868164,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3648149967.1936035,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3647642000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 714.3913322755697,
            "unit": "ns/iter",
            "extra": "iterations: 976672\ncpu: 714.3544608630111 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1011.85445374783,
            "unit": "ns/iter",
            "extra": "iterations: 689519\ncpu: 1010.179559954112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 174.72466271546097,
            "unit": "ns/iter",
            "extra": "iterations: 4013623\ncpu: 174.71396790381152 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 123.10061726441879,
            "unit": "ns/iter",
            "extra": "iterations: 5807249\ncpu: 123.09477344608437 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2479.993218121683,
            "unit": "ns/iter",
            "extra": "iterations: 278194\ncpu: 2479.855784093114 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.771185718727697,
            "unit": "ns/iter",
            "extra": "iterations: 28018829\ncpu: 26.764430447824907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1562.9911071285055,
            "unit": "ns/iter",
            "extra": "iterations: 431460\ncpu: 1562.7474157511701 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1274.300035865218,
            "unit": "ns/iter",
            "extra": "iterations: 546952\ncpu: 1273.395105969083 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1552.8913415082525,
            "unit": "ns/iter",
            "extra": "iterations: 447837\ncpu: 1552.8417705549125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 420.05106521466325,
            "unit": "ns/iter",
            "extra": "iterations: 1652616\ncpu: 420.0092459470313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1978.2678094540936,
            "unit": "ns/iter",
            "extra": "iterations: 351732\ncpu: 1978.1964677652365 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.27932561045927,
            "unit": "ns/iter",
            "extra": "iterations: 5921214\ncpu: 118.27219891056181 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 478.8859610075831,
            "unit": "ns/iter",
            "extra": "iterations: 1478128\ncpu: 478.2441033523508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 281.53884650862017,
            "unit": "ns/iter",
            "extra": "iterations: 2490093\ncpu: 281.5292440884738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 919.8885373317443,
            "unit": "ns/iter",
            "extra": "iterations: 769527\ncpu: 918.7111043537107 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 209.97316901854316,
            "unit": "ns/iter",
            "extra": "iterations: 3365530\ncpu: 209.9595011781213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 655.6495345114198,
            "unit": "ns/iter",
            "extra": "iterations: 1071188\ncpu: 654.9653282150258 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1434.5804447126427,
            "unit": "ns/iter",
            "extra": "iterations: 485747\ncpu: 1434.4236814638098 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729369193119,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3718080997.467041,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3708805000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 715.5064559304333,
            "unit": "ns/iter",
            "extra": "iterations: 980420\ncpu: 715.4280818424754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1010.3150694328115,
            "unit": "ns/iter",
            "extra": "iterations: 696157\ncpu: 1010.2534342109607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 175.31929650851882,
            "unit": "ns/iter",
            "extra": "iterations: 3990855\ncpu: 175.31255833649698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.22965282193539,
            "unit": "ns/iter",
            "extra": "iterations: 5871695\ncpu: 119.22111076954778 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2486.9655857444604,
            "unit": "ns/iter",
            "extra": "iterations: 284435\ncpu: 2486.712254117817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.081330933287788,
            "unit": "ns/iter",
            "extra": "iterations: 28005377\ncpu: 25.079469560434728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1483.8562940812226,
            "unit": "ns/iter",
            "extra": "iterations: 468557\ncpu: 1483.7831896652929 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1275.4009314523532,
            "unit": "ns/iter",
            "extra": "iterations: 549011\ncpu: 1275.2749944900909 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1554.154170753222,
            "unit": "ns/iter",
            "extra": "iterations: 452943\ncpu: 1554.1138730480434 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 424.64310799780355,
            "unit": "ns/iter",
            "extra": "iterations: 1665973\ncpu: 424.6239284790328 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1967.6229889230356,
            "unit": "ns/iter",
            "extra": "iterations: 354845\ncpu: 1967.5689385506375 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.38686963767898,
            "unit": "ns/iter",
            "extra": "iterations: 5874800\ncpu: 118.348879961871 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 471.54984209817934,
            "unit": "ns/iter",
            "extra": "iterations: 1479171\ncpu: 471.5452101210729 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 281.439122406162,
            "unit": "ns/iter",
            "extra": "iterations: 2420378\ncpu: 281.0457705366675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 912.8291827489717,
            "unit": "ns/iter",
            "extra": "iterations: 776053\ncpu: 912.8075015495054 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 213.10748589237411,
            "unit": "ns/iter",
            "extra": "iterations: 3361764\ncpu: 211.18585361732687 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 670.5146431711316,
            "unit": "ns/iter",
            "extra": "iterations: 1025356\ncpu: 666.6806455513995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1442.3103622753213,
            "unit": "ns/iter",
            "extra": "iterations: 483025\ncpu: 1441.745251280996 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729369968792,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3698044776.916504,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3688664000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 748.4257608474854,
            "unit": "ns/iter",
            "extra": "iterations: 979679\ncpu: 748.3706397707823 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1015.2781648275208,
            "unit": "ns/iter",
            "extra": "iterations: 689811\ncpu: 1015.0983385304087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 173.23842916710234,
            "unit": "ns/iter",
            "extra": "iterations: 4043929\ncpu: 173.23474274647268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.37388571373106,
            "unit": "ns/iter",
            "extra": "iterations: 5804889\ncpu: 119.35611516430387 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2587.530375896352,
            "unit": "ns/iter",
            "extra": "iterations: 270041\ncpu: 2587.0627052928994 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.07347634814805,
            "unit": "ns/iter",
            "extra": "iterations: 27998432\ncpu: 25.07347554320181 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1505.169847039441,
            "unit": "ns/iter",
            "extra": "iterations: 473504\ncpu: 1504.8468439548546 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1397.9188806921113,
            "unit": "ns/iter",
            "extra": "iterations: 495621\ncpu: 1397.109888402634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1539.510337261136,
            "unit": "ns/iter",
            "extra": "iterations: 452486\ncpu: 1539.3316036297267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 419.2981737792702,
            "unit": "ns/iter",
            "extra": "iterations: 1671686\ncpu: 419.08767555629464 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1979.19556359706,
            "unit": "ns/iter",
            "extra": "iterations: 353150\ncpu: 1978.7484071924125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 118.66957176746446,
            "unit": "ns/iter",
            "extra": "iterations: 5937739\ncpu: 118.66873906044049 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 471.3333922796146,
            "unit": "ns/iter",
            "extra": "iterations: 1480476\ncpu: 471.3342195348005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 281.6454453815313,
            "unit": "ns/iter",
            "extra": "iterations: 2473699\ncpu: 281.62763537520124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 926.8970633994837,
            "unit": "ns/iter",
            "extra": "iterations: 761789\ncpu: 921.2761013876539 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 210.04204402935235,
            "unit": "ns/iter",
            "extra": "iterations: 3329370\ncpu: 210.01270510637278 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 667.228129745956,
            "unit": "ns/iter",
            "extra": "iterations: 1055473\ncpu: 667.1861809823624 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1494.5955518260305,
            "unit": "ns/iter",
            "extra": "iterations: 465534\ncpu: 1493.7791869122361 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729372522529,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3599632024.7650146,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3599419999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 714.1737220576119,
            "unit": "ns/iter",
            "extra": "iterations: 982967\ncpu: 714.1175644757146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1018.8346823245361,
            "unit": "ns/iter",
            "extra": "iterations: 694886\ncpu: 1018.8304268613853 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 173.15103081270993,
            "unit": "ns/iter",
            "extra": "iterations: 4046196\ncpu: 173.14756872875142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 119.00375137592191,
            "unit": "ns/iter",
            "extra": "iterations: 5852060\ncpu: 118.96665447722684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2583.465600294491,
            "unit": "ns/iter",
            "extra": "iterations: 271997\ncpu: 2583.49172968819 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.0009461723925,
            "unit": "ns/iter",
            "extra": "iterations: 27911465\ncpu: 25.00008509048158 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1479.3124710950972,
            "unit": "ns/iter",
            "extra": "iterations: 472919\ncpu: 1479.2575472755384 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1266.0467046612744,
            "unit": "ns/iter",
            "extra": "iterations: 552129\ncpu: 1265.8961945487376 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1538.5065037769057,
            "unit": "ns/iter",
            "extra": "iterations: 453950\ncpu: 1538.3896904945475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 420.27387341273675,
            "unit": "ns/iter",
            "extra": "iterations: 1673828\ncpu: 420.2719753762031 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1984.9245593283106,
            "unit": "ns/iter",
            "extra": "iterations: 355022\ncpu: 1981.9081634377587 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 123.87145819901103,
            "unit": "ns/iter",
            "extra": "iterations: 5484733\ncpu: 123.10006704063818 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 473.78271723335047,
            "unit": "ns/iter",
            "extra": "iterations: 1477451\ncpu: 473.6238291489899 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 282.70661297120296,
            "unit": "ns/iter",
            "extra": "iterations: 2488562\ncpu: 282.3570399290826 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 923.2263651325076,
            "unit": "ns/iter",
            "extra": "iterations: 769028\ncpu: 923.0327114227281 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 210.77479703944883,
            "unit": "ns/iter",
            "extra": "iterations: 3339137\ncpu: 210.76733299651954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 655.8509435482116,
            "unit": "ns/iter",
            "extra": "iterations: 1067122\ncpu: 655.8256694173649 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1489.8752858723617,
            "unit": "ns/iter",
            "extra": "iterations: 469742\ncpu: 1489.6645392577184 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729373242906,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3885792016.983032,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3884434999.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 711.3059847573672,
            "unit": "ns/iter",
            "extra": "iterations: 875383\ncpu: 710.9596599431334 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 967.1366184258675,
            "unit": "ns/iter",
            "extra": "iterations: 760365\ncpu: 966.5963057215943 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 134.3149634546795,
            "unit": "ns/iter",
            "extra": "iterations: 5174644\ncpu: 134.28305406130343 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 98.82020268928252,
            "unit": "ns/iter",
            "extra": "iterations: 7122580\ncpu: 98.81405333460629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2317.996395417853,
            "unit": "ns/iter",
            "extra": "iterations: 305095\ncpu: 2317.910814664287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.388545293927308,
            "unit": "ns/iter",
            "extra": "iterations: 27909907\ncpu: 25.385466171564094 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1423.8431501290572,
            "unit": "ns/iter",
            "extra": "iterations: 497873\ncpu: 1423.7606779238888 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1196.9086225745268,
            "unit": "ns/iter",
            "extra": "iterations: 570930\ncpu: 1196.7824426812374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1482.8843688157658,
            "unit": "ns/iter",
            "extra": "iterations: 478263\ncpu: 1482.8180310833168 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 399.94156355925026,
            "unit": "ns/iter",
            "extra": "iterations: 1747113\ncpu: 399.69767267486384 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2056.5694171640753,
            "unit": "ns/iter",
            "extra": "iterations: 364172\ncpu: 2035.3267137506489 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 100.66619493764141,
            "unit": "ns/iter",
            "extra": "iterations: 6726242\ncpu: 100.3909761200978 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 462.4103788019176,
            "unit": "ns/iter",
            "extra": "iterations: 1523030\ncpu: 462.398639554046 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 199.64053933568368,
            "unit": "ns/iter",
            "extra": "iterations: 3518684\ncpu: 199.62122202505194 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 852.9597668450276,
            "unit": "ns/iter",
            "extra": "iterations: 827638\ncpu: 852.9006643000878 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.03884810254095,
            "unit": "ns/iter",
            "extra": "iterations: 5313577\ncpu: 131.03000107084193 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 680.5257059974339,
            "unit": "ns/iter",
            "extra": "iterations: 1042272\ncpu: 680.5008673359741 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1291.8488744422189,
            "unit": "ns/iter",
            "extra": "iterations: 558258\ncpu: 1291.5318723600938 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729375868656,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3618195056.915283,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3617331000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 581.2099872293784,
            "unit": "ns/iter",
            "extra": "iterations: 1222942\ncpu: 581.2041781212843 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 879.3741273962581,
            "unit": "ns/iter",
            "extra": "iterations: 758766\ncpu: 879.161691483277 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 132.4281935823549,
            "unit": "ns/iter",
            "extra": "iterations: 5272752\ncpu: 132.4088445654187 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 98.11611392348101,
            "unit": "ns/iter",
            "extra": "iterations: 7115774\ncpu: 98.11286867739206 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2299.3584057509856,
            "unit": "ns/iter",
            "extra": "iterations: 303211\ncpu: 2298.907361540318 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.05427792033762,
            "unit": "ns/iter",
            "extra": "iterations: 27980861\ncpu: 25.053625047492346 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1404.0441387408612,
            "unit": "ns/iter",
            "extra": "iterations: 496901\ncpu: 1403.3600254376665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1197.4026072271124,
            "unit": "ns/iter",
            "extra": "iterations: 571158\ncpu: 1197.3569485151224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1475.2539499594895,
            "unit": "ns/iter",
            "extra": "iterations: 463180\ncpu: 1475.1586856081856 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 401.09194248403327,
            "unit": "ns/iter",
            "extra": "iterations: 1751576\ncpu: 401.0508250855235 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1913.523452398197,
            "unit": "ns/iter",
            "extra": "iterations: 362986\ncpu: 1913.4209032855256 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.57749365518474,
            "unit": "ns/iter",
            "extra": "iterations: 6934950\ncpu: 98.5656709853712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 501.18184089660645,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500.92399999999947 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 204.85461010678526,
            "unit": "ns/iter",
            "extra": "iterations: 3267440\ncpu: 204.84140489190202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 870.662135315333,
            "unit": "ns/iter",
            "extra": "iterations: 763692\ncpu: 870.5459792691307 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.31706755239384,
            "unit": "ns/iter",
            "extra": "iterations: 5335895\ncpu: 131.28163129147026 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 662.0503762874547,
            "unit": "ns/iter",
            "extra": "iterations: 1059498\ncpu: 661.965383606194 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1220.560592629672,
            "unit": "ns/iter",
            "extra": "iterations: 571807\ncpu: 1220.4170288226603 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729378214044,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3784544944.7631836,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3766122000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 562.4259006819209,
            "unit": "ns/iter",
            "extra": "iterations: 1241157\ncpu: 562.4018556878783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 886.1176534000153,
            "unit": "ns/iter",
            "extra": "iterations: 785952\ncpu: 885.8861609869308 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 132.39636334147264,
            "unit": "ns/iter",
            "extra": "iterations: 5329232\ncpu: 132.19690942334648 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 98.27521629692521,
            "unit": "ns/iter",
            "extra": "iterations: 7084016\ncpu: 98.24116715716063 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2282.0392736512304,
            "unit": "ns/iter",
            "extra": "iterations: 306680\ncpu: 2281.6747097952234 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.057795441450967,
            "unit": "ns/iter",
            "extra": "iterations: 27962642\ncpu: 25.055679645721547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1414.8603717288581,
            "unit": "ns/iter",
            "extra": "iterations: 497201\ncpu: 1414.8402758642915 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1197.0105104620375,
            "unit": "ns/iter",
            "extra": "iterations: 582518\ncpu: 1196.917520145298 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1570.4583257747163,
            "unit": "ns/iter",
            "extra": "iterations: 477744\ncpu: 1569.847031045917 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 398.64740596135397,
            "unit": "ns/iter",
            "extra": "iterations: 1712890\ncpu: 398.6327201396473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1918.8091399330835,
            "unit": "ns/iter",
            "extra": "iterations: 364498\ncpu: 1918.4878929376787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.27907822781538,
            "unit": "ns/iter",
            "extra": "iterations: 7121638\ncpu: 98.2748631705229 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 452.81696586462505,
            "unit": "ns/iter",
            "extra": "iterations: 1540130\ncpu: 452.8189178835564 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 199.36463347685773,
            "unit": "ns/iter",
            "extra": "iterations: 3517323\ncpu: 199.1298496043721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 843.992014560964,
            "unit": "ns/iter",
            "extra": "iterations: 819701\ncpu: 843.9028377420553 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.50695805046698,
            "unit": "ns/iter",
            "extra": "iterations: 5351641\ncpu: 131.41464459219145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 656.670715994993,
            "unit": "ns/iter",
            "extra": "iterations: 1062699\ncpu: 656.6553652539433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1229.8955234013545,
            "unit": "ns/iter",
            "extra": "iterations: 567422\ncpu: 1229.6844323977555 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729378859399,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3730587959.289551,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3730125999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 573.031845259993,
            "unit": "ns/iter",
            "extra": "iterations: 1224119\ncpu: 572.9295926294749 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 956.47852398623,
            "unit": "ns/iter",
            "extra": "iterations: 790362\ncpu: 956.075823483417 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 137.92466772745792,
            "unit": "ns/iter",
            "extra": "iterations: 4676706\ncpu: 137.8356903341795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 98.22355627852342,
            "unit": "ns/iter",
            "extra": "iterations: 7144315\ncpu: 98.20983537260041 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2289.996419563634,
            "unit": "ns/iter",
            "extra": "iterations: 305314\ncpu: 2289.8327623364867 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.04166687145674,
            "unit": "ns/iter",
            "extra": "iterations: 27988916\ncpu: 25.039412030105098 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1421.413017533205,
            "unit": "ns/iter",
            "extra": "iterations: 495130\ncpu: 1421.380243572392 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1200.8064098265972,
            "unit": "ns/iter",
            "extra": "iterations: 582043\ncpu: 1200.799597280613 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1474.04199588678,
            "unit": "ns/iter",
            "extra": "iterations: 473956\ncpu: 1473.4722210500559 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 422.403680844568,
            "unit": "ns/iter",
            "extra": "iterations: 1659240\ncpu: 422.3879607531153 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1946.1257024032977,
            "unit": "ns/iter",
            "extra": "iterations: 362174\ncpu: 1946.0949709255763 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.14923430623848,
            "unit": "ns/iter",
            "extra": "iterations: 7140963\ncpu: 98.14390580094052 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 458.4777132690099,
            "unit": "ns/iter",
            "extra": "iterations: 1518458\ncpu: 458.4427096435987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 201.0189120048582,
            "unit": "ns/iter",
            "extra": "iterations: 3417952\ncpu: 201.00399303442498 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 853.9677368233247,
            "unit": "ns/iter",
            "extra": "iterations: 841629\ncpu: 849.6998083478552 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.38051664265578,
            "unit": "ns/iter",
            "extra": "iterations: 5331262\ncpu: 131.37714860008705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 659.1062143243494,
            "unit": "ns/iter",
            "extra": "iterations: 1060494\ncpu: 659.0636062061645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1246.4330101570308,
            "unit": "ns/iter",
            "extra": "iterations: 557356\ncpu: 1246.4206001191355 ns\nthreads: 1"
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
        "date": 1729537667520,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3653921127.319336,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3651804000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 573.1654043660994,
            "unit": "ns/iter",
            "extra": "iterations: 1219172\ncpu: 572.8149924702989 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 879.8726709656421,
            "unit": "ns/iter",
            "extra": "iterations: 795147\ncpu: 879.2034680379853 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 139.86786892732292,
            "unit": "ns/iter",
            "extra": "iterations: 5302870\ncpu: 135.0621455928583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 99.00360767808398,
            "unit": "ns/iter",
            "extra": "iterations: 6814376\ncpu: 98.68372393891975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2293.4876693191673,
            "unit": "ns/iter",
            "extra": "iterations: 304312\ncpu: 2290.790373038198 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.241673040733126,
            "unit": "ns/iter",
            "extra": "iterations: 27961302\ncpu: 25.22346777700127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1418.8078889338165,
            "unit": "ns/iter",
            "extra": "iterations: 490564\ncpu: 1418.0922366908258 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1205.4725128420866,
            "unit": "ns/iter",
            "extra": "iterations: 583572\ncpu: 1204.7425167759932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1474.8013316524411,
            "unit": "ns/iter",
            "extra": "iterations: 472080\ncpu: 1473.5934587358097 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 424.46803842148944,
            "unit": "ns/iter",
            "extra": "iterations: 1664064\ncpu: 424.2000307680469 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2142.378634937319,
            "unit": "ns/iter",
            "extra": "iterations: 354049\ncpu: 2139.175650827991 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 101.06511048449032,
            "unit": "ns/iter",
            "extra": "iterations: 7000980\ncpu: 101.0024310882187 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 504.85638994083723,
            "unit": "ns/iter",
            "extra": "iterations: 1437375\ncpu: 504.5781372293241 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 214.54943062350975,
            "unit": "ns/iter",
            "extra": "iterations: 3364349\ncpu: 214.42840799215458 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 919.5221817617661,
            "unit": "ns/iter",
            "extra": "iterations: 809651\ncpu: 917.2705276717986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 143.68936480569525,
            "unit": "ns/iter",
            "extra": "iterations: 4939038\ncpu: 143.59051297033992 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 711.6415496094721,
            "unit": "ns/iter",
            "extra": "iterations: 975460\ncpu: 711.1414102064668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1324.4348700900084,
            "unit": "ns/iter",
            "extra": "iterations: 522108\ncpu: 1323.7146337539427 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729623116264,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3657309293.7469482,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3656997000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 575.4863257631781,
            "unit": "ns/iter",
            "extra": "iterations: 1206065\ncpu: 575.4482552764579 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 882.2145086973628,
            "unit": "ns/iter",
            "extra": "iterations: 789943\ncpu: 882.1712452670635 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 132.95161879492954,
            "unit": "ns/iter",
            "extra": "iterations: 5264306\ncpu: 132.9349015805691 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 98.11327521179987,
            "unit": "ns/iter",
            "extra": "iterations: 7117365\ncpu: 98.11327647240233 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2342.761526892237,
            "unit": "ns/iter",
            "extra": "iterations: 300807\ncpu: 2342.521949289748 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.625906197697503,
            "unit": "ns/iter",
            "extra": "iterations: 27384399\ncpu: 25.624553600756393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1639.7628871246159,
            "unit": "ns/iter",
            "extra": "iterations: 469682\ncpu: 1637.1949531810903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1218.591448854136,
            "unit": "ns/iter",
            "extra": "iterations: 505412\ncpu: 1217.3672172405861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1480.490446438705,
            "unit": "ns/iter",
            "extra": "iterations: 450109\ncpu: 1480.2769995712179 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 422.094248596096,
            "unit": "ns/iter",
            "extra": "iterations: 1659826\ncpu: 422.04785320870985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1950.7962158974708,
            "unit": "ns/iter",
            "extra": "iterations: 360397\ncpu: 1950.6266700333326 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 99.25067010169535,
            "unit": "ns/iter",
            "extra": "iterations: 7136376\ncpu: 99.2163249245836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 454.2949725647389,
            "unit": "ns/iter",
            "extra": "iterations: 1535546\ncpu: 454.2775012926997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 201.9701117329545,
            "unit": "ns/iter",
            "extra": "iterations: 3483020\ncpu: 201.96323879851366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 848.6900229016065,
            "unit": "ns/iter",
            "extra": "iterations: 801447\ncpu: 847.559476796344 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.6757068241517,
            "unit": "ns/iter",
            "extra": "iterations: 5315231\ncpu: 131.58769581227963 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 659.8413457102715,
            "unit": "ns/iter",
            "extra": "iterations: 1060799\ncpu: 659.7215872186915 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1226.9323000293207,
            "unit": "ns/iter",
            "extra": "iterations: 570483\ncpu: 1226.9147371613158 ns\nthreads: 1"
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
        "date": 1729624052483,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4280150890.350342,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4278340000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 614.0465922487402,
            "unit": "ns/iter",
            "extra": "iterations: 1139731\ncpu: 613.9861072481141 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 944.0249006589091,
            "unit": "ns/iter",
            "extra": "iterations: 727999\ncpu: 943.9545933442223 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 152.66988136680212,
            "unit": "ns/iter",
            "extra": "iterations: 5079936\ncpu: 152.63519067956742 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 136.1340540066188,
            "unit": "ns/iter",
            "extra": "iterations: 5115090\ncpu: 136.13465256720772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3128.299238299159,
            "unit": "ns/iter",
            "extra": "iterations: 217031\ncpu: 3128.2904285562986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 32.485355553145176,
            "unit": "ns/iter",
            "extra": "iterations: 21339121\ncpu: 32.48484321355133 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1753.1635562078004,
            "unit": "ns/iter",
            "extra": "iterations: 340769\ncpu: 1752.0079584704063 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1355.5559541928021,
            "unit": "ns/iter",
            "extra": "iterations: 542581\ncpu: 1355.3791968388125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1812.880039191555,
            "unit": "ns/iter",
            "extra": "iterations: 405252\ncpu: 1812.376003079567 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 451.99474482075095,
            "unit": "ns/iter",
            "extra": "iterations: 1555175\ncpu: 451.94399344125145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2088.298597037233,
            "unit": "ns/iter",
            "extra": "iterations: 335690\ncpu: 2087.4378146504228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 108.47865667409103,
            "unit": "ns/iter",
            "extra": "iterations: 6507088\ncpu: 108.46157298011032 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 506.1688423156738,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 506.1719999999958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 217.78249453273165,
            "unit": "ns/iter",
            "extra": "iterations: 3230168\ncpu: 217.78000401217486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 907.0391430280596,
            "unit": "ns/iter",
            "extra": "iterations: 764000\ncpu: 907.041884816752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 140.3365592595983,
            "unit": "ns/iter",
            "extra": "iterations: 4925588\ncpu: 140.3170545323721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 758.2427419600406,
            "unit": "ns/iter",
            "extra": "iterations: 1005704\ncpu: 756.731602936847 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1364.8215203076252,
            "unit": "ns/iter",
            "extra": "iterations: 529421\ncpu: 1358.7296310497675 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729624521863,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4928909063.339233,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4915794999.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 733.7992923728291,
            "unit": "ns/iter",
            "extra": "iterations: 920847\ncpu: 733.7701051314707 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1055.0872138042569,
            "unit": "ns/iter",
            "extra": "iterations: 654940\ncpu: 1053.7362201117653 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 152.68250748895858,
            "unit": "ns/iter",
            "extra": "iterations: 4535294\ncpu: 152.19410252124797 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 115.4920168746497,
            "unit": "ns/iter",
            "extra": "iterations: 5459494\ncpu: 115.43084395733402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2754.8010402440855,
            "unit": "ns/iter",
            "extra": "iterations: 260808\ncpu: 2752.549768412016 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 29.150439182411205,
            "unit": "ns/iter",
            "extra": "iterations: 24935435\ncpu: 29.086719361422855 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1596.6162198210886,
            "unit": "ns/iter",
            "extra": "iterations: 443288\ncpu: 1595.2225189944243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1405.6825344598526,
            "unit": "ns/iter",
            "extra": "iterations: 506241\ncpu: 1405.1825118866313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1781.7489844370548,
            "unit": "ns/iter",
            "extra": "iterations: 430174\ncpu: 1781.2396844067732 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 432.01212828542845,
            "unit": "ns/iter",
            "extra": "iterations: 1562493\ncpu: 431.98401528838986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2121.2220244751657,
            "unit": "ns/iter",
            "extra": "iterations: 334172\ncpu: 2120.8150293860645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 109.00252591792398,
            "unit": "ns/iter",
            "extra": "iterations: 6390476\ncpu: 108.92678417069436 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 490.2109942898865,
            "unit": "ns/iter",
            "extra": "iterations: 1414948\ncpu: 487.1380432355076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 210.46990091825296,
            "unit": "ns/iter",
            "extra": "iterations: 3302744\ncpu: 210.1731166569369 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1065.517021610552,
            "unit": "ns/iter",
            "extra": "iterations: 803102\ncpu: 1048.9364987261904 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 155.1087190317753,
            "unit": "ns/iter",
            "extra": "iterations: 4441822\ncpu: 152.67045820386264 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 703.8875545265256,
            "unit": "ns/iter",
            "extra": "iterations: 960496\ncpu: 703.8571737935348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1351.9247767188065,
            "unit": "ns/iter",
            "extra": "iterations: 561410\ncpu: 1351.6574339609203 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729627616597,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3705668687.8204346,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3687378999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 571.6977782899266,
            "unit": "ns/iter",
            "extra": "iterations: 1213235\ncpu: 571.3262475942423 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 941.4601333826428,
            "unit": "ns/iter",
            "extra": "iterations: 796994\ncpu: 934.4838229647903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 143.33498125949063,
            "unit": "ns/iter",
            "extra": "iterations: 4606021\ncpu: 143.21949465710202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 105.9333148717608,
            "unit": "ns/iter",
            "extra": "iterations: 6426853\ncpu: 105.86316506694638 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2345.5357383082414,
            "unit": "ns/iter",
            "extra": "iterations: 300407\ncpu: 2344.0033021867002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.27685366435392,
            "unit": "ns/iter",
            "extra": "iterations: 27936194\ncpu: 25.259310556047865 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1414.910009102804,
            "unit": "ns/iter",
            "extra": "iterations: 493312\ncpu: 1414.1111507524636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1204.1370728210418,
            "unit": "ns/iter",
            "extra": "iterations: 582755\ncpu: 1203.0338650033007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1465.112350726436,
            "unit": "ns/iter",
            "extra": "iterations: 473683\ncpu: 1464.2577419920055 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 403.7307604213699,
            "unit": "ns/iter",
            "extra": "iterations: 1735431\ncpu: 403.5107129007145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1916.9201863990963,
            "unit": "ns/iter",
            "extra": "iterations: 363274\ncpu: 1915.463259137736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.47061441230561,
            "unit": "ns/iter",
            "extra": "iterations: 7127366\ncpu: 98.41251312195824 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 456.2091532868793,
            "unit": "ns/iter",
            "extra": "iterations: 1513775\ncpu: 455.9237667420861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 201.6815897099506,
            "unit": "ns/iter",
            "extra": "iterations: 3511342\ncpu: 201.56794752547518 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 850.5065561519582,
            "unit": "ns/iter",
            "extra": "iterations: 825676\ncpu: 849.215672975842 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.63661529077606,
            "unit": "ns/iter",
            "extra": "iterations: 5307413\ncpu: 131.4666863121444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 666.680490269554,
            "unit": "ns/iter",
            "extra": "iterations: 1050877\ncpu: 666.3006231937728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1240.3488815883265,
            "unit": "ns/iter",
            "extra": "iterations: 569268\ncpu: 1239.6849989811467 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729627626922,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3643121242.5231934,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3642700000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 572.5935676781033,
            "unit": "ns/iter",
            "extra": "iterations: 1221214\ncpu: 572.5646774439199 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 879.8912441720747,
            "unit": "ns/iter",
            "extra": "iterations: 789702\ncpu: 879.8622771627784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 131.94365299835448,
            "unit": "ns/iter",
            "extra": "iterations: 5295048\ncpu: 131.94365754569182 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 98.5453709796588,
            "unit": "ns/iter",
            "extra": "iterations: 7126931\ncpu: 98.54353858624411 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2345.716698086494,
            "unit": "ns/iter",
            "extra": "iterations: 290466\ncpu: 2345.4242493097267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.04663290582321,
            "unit": "ns/iter",
            "extra": "iterations: 27955495\ncpu: 25.045129767868524 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1413.2061537665002,
            "unit": "ns/iter",
            "extra": "iterations: 497067\ncpu: 1413.1656295831328 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1202.5905657608887,
            "unit": "ns/iter",
            "extra": "iterations: 584346\ncpu: 1202.4057664465927 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1464.3628652733607,
            "unit": "ns/iter",
            "extra": "iterations: 476888\ncpu: 1464.2976967338254 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 402.33249358094724,
            "unit": "ns/iter",
            "extra": "iterations: 1736417\ncpu: 402.3376873181955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1953.5221251473201,
            "unit": "ns/iter",
            "extra": "iterations: 367205\ncpu: 1947.1003935131616 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.4929660551845,
            "unit": "ns/iter",
            "extra": "iterations: 7040483\ncpu: 98.45716550980933 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 462.93787142846645,
            "unit": "ns/iter",
            "extra": "iterations: 1525151\ncpu: 462.89842776223225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 208.0303594805944,
            "unit": "ns/iter",
            "extra": "iterations: 3247853\ncpu: 207.81728729717824 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 870.1827376203412,
            "unit": "ns/iter",
            "extra": "iterations: 806610\ncpu: 870.0970729348755 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 132.5371894805139,
            "unit": "ns/iter",
            "extra": "iterations: 5222127\ncpu: 132.42420186257425 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 669.446256563938,
            "unit": "ns/iter",
            "extra": "iterations: 1053566\ncpu: 669.4113135769356 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1253.8265591128768,
            "unit": "ns/iter",
            "extra": "iterations: 552003\ncpu: 1253.5910130923266 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729631427196,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3842440843.5821533,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3839887000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 604.440319526728,
            "unit": "ns/iter",
            "extra": "iterations: 1157714\ncpu: 604.0593790867177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 927.0926171151041,
            "unit": "ns/iter",
            "extra": "iterations: 768344\ncpu: 926.3949480961647 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 140.0755453839074,
            "unit": "ns/iter",
            "extra": "iterations: 4912384\ncpu: 140.00574873625519 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 103.0810577085986,
            "unit": "ns/iter",
            "extra": "iterations: 6869817\ncpu: 103.02312274111509 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2422.4916119315617,
            "unit": "ns/iter",
            "extra": "iterations: 287036\ncpu: 2419.5606126060866 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.993595235752945,
            "unit": "ns/iter",
            "extra": "iterations: 26932400\ncpu: 25.979229478249255 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1464.2863121805246,
            "unit": "ns/iter",
            "extra": "iterations: 479176\ncpu: 1463.4768853198007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1250.1006123535115,
            "unit": "ns/iter",
            "extra": "iterations: 563489\ncpu: 1249.3074398967847 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1536.5995959607274,
            "unit": "ns/iter",
            "extra": "iterations: 453491\ncpu: 1535.8276128963928 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 67.19608714477965,
            "unit": "ns/iter",
            "extra": "iterations: 10528216\ncpu: 67.06824783989991 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2084.017963587355,
            "unit": "ns/iter",
            "extra": "iterations: 332736\ncpu: 2061.613411232926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 101.96377149840555,
            "unit": "ns/iter",
            "extra": "iterations: 6882583\ncpu: 101.90912336255143 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 81.02908554825817,
            "unit": "ns/iter",
            "extra": "iterations: 8650305\ncpu: 80.97887877941884 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 214.18969411695176,
            "unit": "ns/iter",
            "extra": "iterations: 3255572\ncpu: 214.06530096707968 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 882.2441576814564,
            "unit": "ns/iter",
            "extra": "iterations: 803849\ncpu: 880.5559253043817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 137.66203204480925,
            "unit": "ns/iter",
            "extra": "iterations: 5050906\ncpu: 137.590958928952 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 689.0633821315357,
            "unit": "ns/iter",
            "extra": "iterations: 1015641\ncpu: 688.5690908500168 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1286.0701564477524,
            "unit": "ns/iter",
            "extra": "iterations: 553955\ncpu: 1285.0466193102252 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729633080690,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4003192901.611328,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4002319000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 630.2939973705926,
            "unit": "ns/iter",
            "extra": "iterations: 1108402\ncpu: 630.1811075764923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 953.6369658640763,
            "unit": "ns/iter",
            "extra": "iterations: 734076\ncpu: 953.5988099324859 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 144.82624901401442,
            "unit": "ns/iter",
            "extra": "iterations: 4865368\ncpu: 144.7968581204957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 106.82863718446865,
            "unit": "ns/iter",
            "extra": "iterations: 6528146\ncpu: 106.8024520284935 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2544.277568802324,
            "unit": "ns/iter",
            "extra": "iterations: 272940\ncpu: 2544.2844581226664 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.159047419482324,
            "unit": "ns/iter",
            "extra": "iterations: 25828924\ncpu: 27.132063263649695 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1541.9504276549362,
            "unit": "ns/iter",
            "extra": "iterations: 456044\ncpu: 1541.717465858555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1301.831556023621,
            "unit": "ns/iter",
            "extra": "iterations: 525707\ncpu: 1301.690865824502 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1625.4157427378955,
            "unit": "ns/iter",
            "extra": "iterations: 439439\ncpu: 1625.1584406481886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 70.8485171334656,
            "unit": "ns/iter",
            "extra": "iterations: 9440833\ncpu: 70.83453335102934 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2089.75524214236,
            "unit": "ns/iter",
            "extra": "iterations: 332625\ncpu: 2089.0853062758356 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 107.63403945330113,
            "unit": "ns/iter",
            "extra": "iterations: 6433764\ncpu: 107.24406428336475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 85.53943457540045,
            "unit": "ns/iter",
            "extra": "iterations: 7949035\ncpu: 85.52950137972692 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 224.40036038322384,
            "unit": "ns/iter",
            "extra": "iterations: 3081501\ncpu: 224.39681181346398 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 941.383277670358,
            "unit": "ns/iter",
            "extra": "iterations: 748831\ncpu: 941.296500812607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 143.82751909986146,
            "unit": "ns/iter",
            "extra": "iterations: 4910730\ncpu: 143.63444946067068 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 717.8000640102246,
            "unit": "ns/iter",
            "extra": "iterations: 980914\ncpu: 717.7683262752906 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1443.094959608526,
            "unit": "ns/iter",
            "extra": "iterations: 525664\ncpu: 1427.248204176053 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729633709407,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3993216991.4245605,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3992206000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 508.181095123291,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 508.0699999999991 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 788.1213530317652,
            "unit": "ns/iter",
            "extra": "iterations: 841609\ncpu: 788.0666675380132 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 112.84289696420154,
            "unit": "ns/iter",
            "extra": "iterations: 6217469\ncpu: 112.82018454776379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 79.0839387659299,
            "unit": "ns/iter",
            "extra": "iterations: 8717636\ncpu: 79.07005981896916 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1880.4143136603177,
            "unit": "ns/iter",
            "extra": "iterations: 371583\ncpu: 1880.1882755669665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.09146343201004,
            "unit": "ns/iter",
            "extra": "iterations: 27901452\ncpu: 25.09037880895955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1373.1415844351668,
            "unit": "ns/iter",
            "extra": "iterations: 504308\ncpu: 1372.8951355124236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1162.7701374873764,
            "unit": "ns/iter",
            "extra": "iterations: 600503\ncpu: 1162.7169223134595 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1429.9402577852395,
            "unit": "ns/iter",
            "extra": "iterations: 488343\ncpu: 1429.8269863599955 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 61.21323684181833,
            "unit": "ns/iter",
            "extra": "iterations: 11456628\ncpu: 61.20832412469005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1914.2592048389254,
            "unit": "ns/iter",
            "extra": "iterations: 372123\ncpu: 1914.1762266777366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 79.95692048746454,
            "unit": "ns/iter",
            "extra": "iterations: 8473140\ncpu: 79.91972279461918 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 79.84652760176333,
            "unit": "ns/iter",
            "extra": "iterations: 9312969\ncpu: 79.84456943859679 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 191.82104595033812,
            "unit": "ns/iter",
            "extra": "iterations: 3680994\ncpu: 191.80878860438187 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 817.181996773913,
            "unit": "ns/iter",
            "extra": "iterations: 858991\ncpu: 817.1540796120086 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.34986098986582,
            "unit": "ns/iter",
            "extra": "iterations: 5566645\ncpu: 125.84743593313475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 663.4503533427375,
            "unit": "ns/iter",
            "extra": "iterations: 1057051\ncpu: 663.3539914346602 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1048.0208876169706,
            "unit": "ns/iter",
            "extra": "iterations: 667710\ncpu: 1047.9220020667672 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729634429681,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4406446933.746338,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4402368000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 652.7921815266947,
            "unit": "ns/iter",
            "extra": "iterations: 1133420\ncpu: 642.2244181327308 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 916.4580254820122,
            "unit": "ns/iter",
            "extra": "iterations: 707979\ncpu: 913.1866905656796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 127.01703839505863,
            "unit": "ns/iter",
            "extra": "iterations: 5711069\ncpu: 126.91599418602736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 90.61967912402898,
            "unit": "ns/iter",
            "extra": "iterations: 7515729\ncpu: 90.56194016575095 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2333.2239963913644,
            "unit": "ns/iter",
            "extra": "iterations: 337400\ncpu: 2324.5672791938364 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 30.46918080412938,
            "unit": "ns/iter",
            "extra": "iterations: 20189260\ncpu: 30.41810348670525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1592.7505494843008,
            "unit": "ns/iter",
            "extra": "iterations: 454416\ncpu: 1591.3766240625348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1294.3490515300307,
            "unit": "ns/iter",
            "extra": "iterations: 549731\ncpu: 1293.4853592029558 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1567.4693142971666,
            "unit": "ns/iter",
            "extra": "iterations: 458869\ncpu: 1566.2378587352853 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 65.01097765730538,
            "unit": "ns/iter",
            "extra": "iterations: 10560618\ncpu: 64.97252338830926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2028.217382290901,
            "unit": "ns/iter",
            "extra": "iterations: 359612\ncpu: 2026.9373658276095 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 85.47065076514241,
            "unit": "ns/iter",
            "extra": "iterations: 8514572\ncpu: 85.38890739311364 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 80.26964708329217,
            "unit": "ns/iter",
            "extra": "iterations: 8801599\ncpu: 80.01023450398017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 201.76563543500583,
            "unit": "ns/iter",
            "extra": "iterations: 3409977\ncpu: 201.65678536834596 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 862.3024385145538,
            "unit": "ns/iter",
            "extra": "iterations: 836050\ncpu: 861.72477722624 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 138.17222270648887,
            "unit": "ns/iter",
            "extra": "iterations: 4844492\ncpu: 138.10385072366688 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 726.7320895486197,
            "unit": "ns/iter",
            "extra": "iterations: 914817\ncpu: 726.0151483848717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1136.412649110973,
            "unit": "ns/iter",
            "extra": "iterations: 544832\ncpu: 1135.3921942910818 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729687254759,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3919193029.4036865,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3917825999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 507.47502291876145,
            "unit": "ns/iter",
            "extra": "iterations: 1377329\ncpu: 507.4357687959806 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 871.0545411557822,
            "unit": "ns/iter",
            "extra": "iterations: 846218\ncpu: 870.9942355279601 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 114.64804020080729,
            "unit": "ns/iter",
            "extra": "iterations: 5932958\ncpu: 114.57050597695128 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 79.66860840282011,
            "unit": "ns/iter",
            "extra": "iterations: 8850676\ncpu: 79.66159872985956 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1908.524054052026,
            "unit": "ns/iter",
            "extra": "iterations: 360238\ncpu: 1908.2190107651086 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.135167869386272,
            "unit": "ns/iter",
            "extra": "iterations: 27922153\ncpu: 25.127324529738072 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1378.0064829378566,
            "unit": "ns/iter",
            "extra": "iterations: 511139\ncpu: 1377.9402471734693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1164.813273956713,
            "unit": "ns/iter",
            "extra": "iterations: 598598\ncpu: 1164.783377157958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1450.2869534751128,
            "unit": "ns/iter",
            "extra": "iterations: 480551\ncpu: 1450.1270416667517 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 63.91498255859494,
            "unit": "ns/iter",
            "extra": "iterations: 11361608\ncpu: 63.90829537509142 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1930.7364899517293,
            "unit": "ns/iter",
            "extra": "iterations: 353216\ncpu: 1930.7392643594887 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 79.68206579086466,
            "unit": "ns/iter",
            "extra": "iterations: 8776329\ncpu: 79.62577519598455 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 75.79087150281507,
            "unit": "ns/iter",
            "extra": "iterations: 9232393\ncpu: 75.78890976586452 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 191.13635482176352,
            "unit": "ns/iter",
            "extra": "iterations: 3604086\ncpu: 191.1325090466764 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 805.511049518705,
            "unit": "ns/iter",
            "extra": "iterations: 873155\ncpu: 804.037083908354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 127.88702280790443,
            "unit": "ns/iter",
            "extra": "iterations: 5530187\ncpu: 127.77633016749722 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 607.8202124987113,
            "unit": "ns/iter",
            "extra": "iterations: 1139082\ncpu: 607.7911862359364 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1047.36280860272,
            "unit": "ns/iter",
            "extra": "iterations: 670209\ncpu: 1046.798834393457 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729695545622,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3747111082.0770264,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3746686000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 506.9505339396855,
            "unit": "ns/iter",
            "extra": "iterations: 1418673\ncpu: 506.67067040819126 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 827.9516172130542,
            "unit": "ns/iter",
            "extra": "iterations: 875208\ncpu: 827.9014817049208 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 113.91810050939442,
            "unit": "ns/iter",
            "extra": "iterations: 6041201\ncpu: 113.91029697571726 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.88733630213449,
            "unit": "ns/iter",
            "extra": "iterations: 9014346\ncpu: 78.88414755768187 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1950.6577270698735,
            "unit": "ns/iter",
            "extra": "iterations: 363801\ncpu: 1949.6702867776605 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.971725973961636,
            "unit": "ns/iter",
            "extra": "iterations: 28727967\ncpu: 23.96427843292913 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1409.5203415698015,
            "unit": "ns/iter",
            "extra": "iterations: 514895\ncpu: 1408.4055972576916 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1187.9418990463807,
            "unit": "ns/iter",
            "extra": "iterations: 595329\ncpu: 1187.8087578465038 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1487.200996611332,
            "unit": "ns/iter",
            "extra": "iterations: 487204\ncpu: 1487.1388576448492 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.702646259452656,
            "unit": "ns/iter",
            "extra": "iterations: 11535166\ncpu: 60.69622231704341 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1926.086299165973,
            "unit": "ns/iter",
            "extra": "iterations: 361057\ncpu: 1925.8510429101225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 81.01064398567388,
            "unit": "ns/iter",
            "extra": "iterations: 8920607\ncpu: 80.69024899314589 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 76.72441192444845,
            "unit": "ns/iter",
            "extra": "iterations: 9426467\ncpu: 76.68206975105296 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 192.49432382566837,
            "unit": "ns/iter",
            "extra": "iterations: 3540951\ncpu: 192.478517776721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 824.3472670388824,
            "unit": "ns/iter",
            "extra": "iterations: 821548\ncpu: 822.7833309800515 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 127.55303286269549,
            "unit": "ns/iter",
            "extra": "iterations: 5549346\ncpu: 127.53412744492758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 610.3767501378053,
            "unit": "ns/iter",
            "extra": "iterations: 1146864\ncpu: 610.3339192790082 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1075.5094077953318,
            "unit": "ns/iter",
            "extra": "iterations: 654157\ncpu: 1075.2403475006745 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729697014652,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3646914005.279541,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3646324000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 493.05960380302383,
            "unit": "ns/iter",
            "extra": "iterations: 1427136\ncpu: 493.0350015695772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 805.7972674756477,
            "unit": "ns/iter",
            "extra": "iterations: 867227\ncpu: 805.732524471677 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 111.42064150987002,
            "unit": "ns/iter",
            "extra": "iterations: 6303807\ncpu: 111.41600623242435 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.68811363612423,
            "unit": "ns/iter",
            "extra": "iterations: 8847432\ncpu: 78.68430071008174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1899.9151499654865,
            "unit": "ns/iter",
            "extra": "iterations: 370835\ncpu: 1899.8368546658205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.762746866701214,
            "unit": "ns/iter",
            "extra": "iterations: 29314460\ncpu: 23.761276857905592 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1387.3754699192345,
            "unit": "ns/iter",
            "extra": "iterations: 507673\ncpu: 1387.3320030807245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1162.6251735343153,
            "unit": "ns/iter",
            "extra": "iterations: 593819\ncpu: 1162.5697392639836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1478.6549153335934,
            "unit": "ns/iter",
            "extra": "iterations: 487391\ncpu: 1463.8021629451525 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.9314279319894,
            "unit": "ns/iter",
            "extra": "iterations: 11273049\ncpu: 60.75783046804825 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1887.7977012406109,
            "unit": "ns/iter",
            "extra": "iterations: 364635\ncpu: 1886.848492327948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 79.13398458998404,
            "unit": "ns/iter",
            "extra": "iterations: 8866483\ncpu: 79.13261661923895 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.29115008594047,
            "unit": "ns/iter",
            "extra": "iterations: 9434089\ncpu: 74.26864427503315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 194.65989183509555,
            "unit": "ns/iter",
            "extra": "iterations: 3597695\ncpu: 194.53372228607586 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 806.0803048493353,
            "unit": "ns/iter",
            "extra": "iterations: 881834\ncpu: 804.868036387796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.15366710332043,
            "unit": "ns/iter",
            "extra": "iterations: 5482156\ncpu: 125.11701600611161 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 632.1883103647847,
            "unit": "ns/iter",
            "extra": "iterations: 1105060\ncpu: 632.1358116301367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1076.5661888001625,
            "unit": "ns/iter",
            "extra": "iterations: 659270\ncpu: 1076.5528539141765 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729697860520,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3819937705.9936523,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3806260000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 508.989793509364,
            "unit": "ns/iter",
            "extra": "iterations: 1371688\ncpu: 508.6287843882873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 809.7142086264886,
            "unit": "ns/iter",
            "extra": "iterations: 865951\ncpu: 809.168186190674 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 113.83627540702052,
            "unit": "ns/iter",
            "extra": "iterations: 6156823\ncpu: 113.76191909366243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 79.93865431506786,
            "unit": "ns/iter",
            "extra": "iterations: 8837491\ncpu: 79.89518744630122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1991.2110255383686,
            "unit": "ns/iter",
            "extra": "iterations: 349066\ncpu: 1989.7440598626044 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.48067504439753,
            "unit": "ns/iter",
            "extra": "iterations: 29463760\ncpu: 24.419218728363287 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1446.6614054711151,
            "unit": "ns/iter",
            "extra": "iterations: 504239\ncpu: 1445.7291086171422 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1215.6908389036776,
            "unit": "ns/iter",
            "extra": "iterations: 561262\ncpu: 1214.942397668112 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1469.7761841135114,
            "unit": "ns/iter",
            "extra": "iterations: 471139\ncpu: 1468.9507767346768 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 62.00166419838811,
            "unit": "ns/iter",
            "extra": "iterations: 11553062\ncpu: 61.950416261939885 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1910.8710189272263,
            "unit": "ns/iter",
            "extra": "iterations: 371126\ncpu: 1909.7476328794005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 80.39047112169519,
            "unit": "ns/iter",
            "extra": "iterations: 8824790\ncpu: 80.22706489332903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.41653472778019,
            "unit": "ns/iter",
            "extra": "iterations: 9417463\ncpu: 74.37034793765591 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 200.78789108163622,
            "unit": "ns/iter",
            "extra": "iterations: 3501103\ncpu: 200.67533003170692 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 836.6160790284658,
            "unit": "ns/iter",
            "extra": "iterations: 849020\ncpu: 836.0945560764177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.48091740103663,
            "unit": "ns/iter",
            "extra": "iterations: 5539991\ncpu: 126.41211872004844 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 600.2206254423471,
            "unit": "ns/iter",
            "extra": "iterations: 1170823\ncpu: 599.849849208632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1070.6200941231098,
            "unit": "ns/iter",
            "extra": "iterations: 664061\ncpu: 1067.6624587199115 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729702601070,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3691862106.323242,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3689174999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 490.351385979827,
            "unit": "ns/iter",
            "extra": "iterations: 1432181\ncpu: 490.0756259159984 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 804.782252310792,
            "unit": "ns/iter",
            "extra": "iterations: 870777\ncpu: 803.871714572157 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 121.64554468835257,
            "unit": "ns/iter",
            "extra": "iterations: 5583607\ncpu: 121.389990377188 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 84.92333475681001,
            "unit": "ns/iter",
            "extra": "iterations: 8369702\ncpu: 84.85558984059419 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1891.6687915048112,
            "unit": "ns/iter",
            "extra": "iterations: 366922\ncpu: 1890.6007271300195 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.813110712798437,
            "unit": "ns/iter",
            "extra": "iterations: 29255775\ncpu: 23.790960929936062 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1365.2667549973598,
            "unit": "ns/iter",
            "extra": "iterations: 511251\ncpu: 1364.45503285079 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1165.704366866487,
            "unit": "ns/iter",
            "extra": "iterations: 599007\ncpu: 1165.023113252434 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1495.683582547137,
            "unit": "ns/iter",
            "extra": "iterations: 447731\ncpu: 1494.6385217909888 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 62.603066895471,
            "unit": "ns/iter",
            "extra": "iterations: 11436040\ncpu: 62.56195326354222 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1906.7353248713384,
            "unit": "ns/iter",
            "extra": "iterations: 366195\ncpu: 1905.703245538582 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 79.48411912408885,
            "unit": "ns/iter",
            "extra": "iterations: 8921744\ncpu: 79.44298782838884 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.18886512187689,
            "unit": "ns/iter",
            "extra": "iterations: 9456904\ncpu: 74.13948581903752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 191.35203484649819,
            "unit": "ns/iter",
            "extra": "iterations: 3627977\ncpu: 191.2363281244618 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 793.1865882947509,
            "unit": "ns/iter",
            "extra": "iterations: 889555\ncpu: 792.7536802108912 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 127.23775298235486,
            "unit": "ns/iter",
            "extra": "iterations: 5600672\ncpu: 127.05671747961614 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 593.2301422019173,
            "unit": "ns/iter",
            "extra": "iterations: 1171646\ncpu: 591.5378877237679 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1063.0200663039386,
            "unit": "ns/iter",
            "extra": "iterations: 657555\ncpu: 1062.414550874069 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729703604087,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5014497041.7022705,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5005043000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 576.8080770574039,
            "unit": "ns/iter",
            "extra": "iterations: 1302447\ncpu: 574.4932423353888 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 924.3608832720497,
            "unit": "ns/iter",
            "extra": "iterations: 783875\ncpu: 896.09440280657 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 124.58419444796806,
            "unit": "ns/iter",
            "extra": "iterations: 5684310\ncpu: 124.46242375943604 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 87.32937278972925,
            "unit": "ns/iter",
            "extra": "iterations: 7937228\ncpu: 87.2467062808327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2155.1983036867505,
            "unit": "ns/iter",
            "extra": "iterations: 296434\ncpu: 2152.637686635133 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.58016327717525,
            "unit": "ns/iter",
            "extra": "iterations: 26606157\ncpu: 26.552538196327983 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1592.5689795371777,
            "unit": "ns/iter",
            "extra": "iterations: 418385\ncpu: 1589.1487505527236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1532.1332283577606,
            "unit": "ns/iter",
            "extra": "iterations: 553679\ncpu: 1523.142470637316 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1748.4547813085662,
            "unit": "ns/iter",
            "extra": "iterations: 402973\ncpu: 1718.7925741923152 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 68.65619790971952,
            "unit": "ns/iter",
            "extra": "iterations: 10577693\ncpu: 68.57081217993384 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2107.7672515703616,
            "unit": "ns/iter",
            "extra": "iterations: 350300\ncpu: 2106.1461604339147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 86.11791502168178,
            "unit": "ns/iter",
            "extra": "iterations: 5968978\ncpu: 86.06950804643645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 87.82167358021844,
            "unit": "ns/iter",
            "extra": "iterations: 5771387\ncpu: 87.71444368572108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 211.84805062404487,
            "unit": "ns/iter",
            "extra": "iterations: 2891941\ncpu: 211.61358409455917 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 875.5929205700556,
            "unit": "ns/iter",
            "extra": "iterations: 822050\ncpu: 874.8336475883452 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 145.0431693140603,
            "unit": "ns/iter",
            "extra": "iterations: 5188683\ncpu: 144.7964734018247 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 741.3827906362918,
            "unit": "ns/iter",
            "extra": "iterations: 944109\ncpu: 737.825823077634 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1213.3273344556733,
            "unit": "ns/iter",
            "extra": "iterations: 453462\ncpu: 1211.6847718221225 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729705577193,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3672455072.402954,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3669912000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 485.47576037897903,
            "unit": "ns/iter",
            "extra": "iterations: 1380126\ncpu: 485.4274174966635 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 797.706301000441,
            "unit": "ns/iter",
            "extra": "iterations: 872687\ncpu: 797.6788928905773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 110.7556576200112,
            "unit": "ns/iter",
            "extra": "iterations: 6337193\ncpu: 110.74587755178032 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.70537229926092,
            "unit": "ns/iter",
            "extra": "iterations: 9022246\ncpu: 77.68797259573734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1878.4546368547192,
            "unit": "ns/iter",
            "extra": "iterations: 371903\ncpu: 1877.822980723469 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.799897498544357,
            "unit": "ns/iter",
            "extra": "iterations: 29424746\ncpu: 23.798200331109104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1373.8685788025489,
            "unit": "ns/iter",
            "extra": "iterations: 511774\ncpu: 1373.8603367892858 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1220.5740604729033,
            "unit": "ns/iter",
            "extra": "iterations: 604209\ncpu: 1220.5263410508592 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1433.8701183116889,
            "unit": "ns/iter",
            "extra": "iterations: 464962\ncpu: 1433.775233244867 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.903635857077404,
            "unit": "ns/iter",
            "extra": "iterations: 11506345\ncpu: 60.896748706909264 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1886.213444070343,
            "unit": "ns/iter",
            "extra": "iterations: 371686\ncpu: 1885.9924775213512 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.51010823925576,
            "unit": "ns/iter",
            "extra": "iterations: 9039957\ncpu: 78.50811679745796 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.99214910080443,
            "unit": "ns/iter",
            "extra": "iterations: 9339684\ncpu: 74.98551342850551 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 188.53536311497115,
            "unit": "ns/iter",
            "extra": "iterations: 3713823\ncpu: 188.50763754761613 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 817.7023210862807,
            "unit": "ns/iter",
            "extra": "iterations: 868217\ncpu: 817.6078100290597 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.50678049908052,
            "unit": "ns/iter",
            "extra": "iterations: 5629861\ncpu: 124.33646230342158 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 633.6591979096864,
            "unit": "ns/iter",
            "extra": "iterations: 1145682\ncpu: 612.0607638070625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1079.4825797778794,
            "unit": "ns/iter",
            "extra": "iterations: 624248\ncpu: 1076.5545103869024 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729706520079,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4896731138.22937,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4850889000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 556.7072354109808,
            "unit": "ns/iter",
            "extra": "iterations: 1307483\ncpu: 556.0079939853908 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1096.1330820264839,
            "unit": "ns/iter",
            "extra": "iterations: 725742\ncpu: 1095.5821765861688 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 131.9930472464458,
            "unit": "ns/iter",
            "extra": "iterations: 4854066\ncpu: 131.7561401101673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 104.95615844541766,
            "unit": "ns/iter",
            "extra": "iterations: 6912829\ncpu: 104.59972321028042 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2228.136256911734,
            "unit": "ns/iter",
            "extra": "iterations: 254703\ncpu: 2227.2411396803336 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.947350489079433,
            "unit": "ns/iter",
            "extra": "iterations: 25987526\ncpu: 26.940579107068555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1523.8862872169116,
            "unit": "ns/iter",
            "extra": "iterations: 412269\ncpu: 1523.5392425819045 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1302.7767132096064,
            "unit": "ns/iter",
            "extra": "iterations: 549451\ncpu: 1301.1951930199416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1928.7897659696953,
            "unit": "ns/iter",
            "extra": "iterations: 416610\ncpu: 1927.1524927390117 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 67.50108434676896,
            "unit": "ns/iter",
            "extra": "iterations: 10220918\ncpu: 67.49237201589911 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2186.1716808751185,
            "unit": "ns/iter",
            "extra": "iterations: 332327\ncpu: 2185.016565009762 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 98.07125283044084,
            "unit": "ns/iter",
            "extra": "iterations: 8084635\ncpu: 97.69816448114254 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 87.1442853614754,
            "unit": "ns/iter",
            "extra": "iterations: 7647432\ncpu: 87.13813996646145 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 214.37559392864767,
            "unit": "ns/iter",
            "extra": "iterations: 2844395\ncpu: 214.35173384849895 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 924.0655427897038,
            "unit": "ns/iter",
            "extra": "iterations: 775589\ncpu: 923.6103142257058 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 158.6175756945708,
            "unit": "ns/iter",
            "extra": "iterations: 4316538\ncpu: 158.45105498897473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 749.5122709223335,
            "unit": "ns/iter",
            "extra": "iterations: 1048438\ncpu: 741.1129699610293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1274.8561979431906,
            "unit": "ns/iter",
            "extra": "iterations: 584059\ncpu: 1274.355844186971 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729708016271,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3838638067.2454834,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3837886000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 541.0533118873407,
            "unit": "ns/iter",
            "extra": "iterations: 1364629\ncpu: 540.6656314646693 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 970.7971911371538,
            "unit": "ns/iter",
            "extra": "iterations: 737052\ncpu: 970.2069867526301 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 114.49479919563683,
            "unit": "ns/iter",
            "extra": "iterations: 6113430\ncpu: 114.4696185283875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 81.58344525346645,
            "unit": "ns/iter",
            "extra": "iterations: 8403260\ncpu: 81.51800610715368 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1952.5383045645037,
            "unit": "ns/iter",
            "extra": "iterations: 360585\ncpu: 1951.6091906207962 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.510596498671017,
            "unit": "ns/iter",
            "extra": "iterations: 28453550\ncpu: 25.498540603896526 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1439.2471296679062,
            "unit": "ns/iter",
            "extra": "iterations: 499618\ncpu: 1439.0734521174147 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1258.6803564866084,
            "unit": "ns/iter",
            "extra": "iterations: 577010\ncpu: 1258.5189164832514 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1548.3795245657543,
            "unit": "ns/iter",
            "extra": "iterations: 445644\ncpu: 1547.8363895845102 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 66.15662641839651,
            "unit": "ns/iter",
            "extra": "iterations: 10726983\ncpu: 66.13611674410207 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2037.4236338599817,
            "unit": "ns/iter",
            "extra": "iterations: 345229\ncpu: 2037.2129803695477 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 99.63900299293542,
            "unit": "ns/iter",
            "extra": "iterations: 6743413\ncpu: 99.56263986797202 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 96.67386110968914,
            "unit": "ns/iter",
            "extra": "iterations: 7104363\ncpu: 96.13289748848712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 235.83163544538147,
            "unit": "ns/iter",
            "extra": "iterations: 3117665\ncpu: 235.7754922353758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1023.9153410649777,
            "unit": "ns/iter",
            "extra": "iterations: 637163\ncpu: 1023.5465650077001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 176.9124670194204,
            "unit": "ns/iter",
            "extra": "iterations: 4656546\ncpu: 164.1426928886773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 719.2591704232758,
            "unit": "ns/iter",
            "extra": "iterations: 925045\ncpu: 712.8355917820247 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1426.987751487192,
            "unit": "ns/iter",
            "extra": "iterations: 583576\ncpu: 1422.8480951923993 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729709749569,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4711162090.301514,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4476024000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 529.9264286453943,
            "unit": "ns/iter",
            "extra": "iterations: 1339303\ncpu: 529.4768995514831 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 854.5677129473518,
            "unit": "ns/iter",
            "extra": "iterations: 812282\ncpu: 854.144250395799 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 118.97094804115979,
            "unit": "ns/iter",
            "extra": "iterations: 5899407\ncpu: 118.94076811448996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 86.26260987434118,
            "unit": "ns/iter",
            "extra": "iterations: 8384941\ncpu: 86.23256860125774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2035.1036389622689,
            "unit": "ns/iter",
            "extra": "iterations: 344834\ncpu: 2033.5552758718718 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.04623067858637,
            "unit": "ns/iter",
            "extra": "iterations: 27059729\ncpu: 26.038656928160595 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1479.3580630671506,
            "unit": "ns/iter",
            "extra": "iterations: 417596\ncpu: 1478.687535321217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1265.3251473407618,
            "unit": "ns/iter",
            "extra": "iterations: 528685\ncpu: 1264.3237466544347 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1552.9514353394688,
            "unit": "ns/iter",
            "extra": "iterations: 437957\ncpu: 1552.513146267787 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 74.75576903931494,
            "unit": "ns/iter",
            "extra": "iterations: 10699601\ncpu: 70.87797012243716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2306.921793387731,
            "unit": "ns/iter",
            "extra": "iterations: 327014\ncpu: 2188.884879546444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 95.33350205837048,
            "unit": "ns/iter",
            "extra": "iterations: 7740794\ncpu: 90.13584394572442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 89.5358206226121,
            "unit": "ns/iter",
            "extra": "iterations: 8373106\ncpu: 85.99843355619771 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 244.76881866050027,
            "unit": "ns/iter",
            "extra": "iterations: 3065309\ncpu: 229.23757441745724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 954.8205244755443,
            "unit": "ns/iter",
            "extra": "iterations: 685797\ncpu: 920.9766155290879 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 152.9405631979499,
            "unit": "ns/iter",
            "extra": "iterations: 4782858\ncpu: 146.48898211069528 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 891.7519962872382,
            "unit": "ns/iter",
            "extra": "iterations: 1055186\ncpu: 751.6684262300648 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1293.2064951857346,
            "unit": "ns/iter",
            "extra": "iterations: 554363\ncpu: 1240.0683306786345 ns\nthreads: 1"
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
        "date": 1729710423582,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3618607759.475708,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3616599000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 491.21733458409494,
            "unit": "ns/iter",
            "extra": "iterations: 1430925\ncpu: 490.9125216206301 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 790.188390994692,
            "unit": "ns/iter",
            "extra": "iterations: 885347\ncpu: 789.7897660465335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 110.47908772574542,
            "unit": "ns/iter",
            "extra": "iterations: 6345925\ncpu: 110.40880565087042 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.21034016119071,
            "unit": "ns/iter",
            "extra": "iterations: 8979885\ncpu: 78.16347314024614 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1889.975459429295,
            "unit": "ns/iter",
            "extra": "iterations: 373564\ncpu: 1888.9025709115451 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.890897744817178,
            "unit": "ns/iter",
            "extra": "iterations: 29323056\ncpu: 23.878479787372807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1380.9010298623539,
            "unit": "ns/iter",
            "extra": "iterations: 506355\ncpu: 1380.091042845436 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1167.1991194161703,
            "unit": "ns/iter",
            "extra": "iterations: 598178\ncpu: 1166.5892092320366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1435.9365322601898,
            "unit": "ns/iter",
            "extra": "iterations: 486984\ncpu: 1435.2114237839455 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.577200970926306,
            "unit": "ns/iter",
            "extra": "iterations: 11546392\ncpu: 60.54376120263366 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1884.576103137356,
            "unit": "ns/iter",
            "extra": "iterations: 372947\ncpu: 1883.5732691240341 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.03436833272025,
            "unit": "ns/iter",
            "extra": "iterations: 8899964\ncpu: 77.99357390659098 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.73314244268408,
            "unit": "ns/iter",
            "extra": "iterations: 9384259\ncpu: 74.68975440682124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 194.00877969825387,
            "unit": "ns/iter",
            "extra": "iterations: 3582560\ncpu: 193.88091197356124 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 795.9377934901866,
            "unit": "ns/iter",
            "extra": "iterations: 888190\ncpu: 794.6238980398311 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.14967670695138,
            "unit": "ns/iter",
            "extra": "iterations: 5619872\ncpu: 126.06817379470594 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 585.8849416245912,
            "unit": "ns/iter",
            "extra": "iterations: 1192362\ncpu: 585.5419746687685 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1046.7309313630012,
            "unit": "ns/iter",
            "extra": "iterations: 668698\ncpu: 1044.9664871137645 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729717616458,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4281020164.489746,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4279429999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 547.6308865160945,
            "unit": "ns/iter",
            "extra": "iterations: 1275255\ncpu: 546.8757228946367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 860.1197908318798,
            "unit": "ns/iter",
            "extra": "iterations: 805431\ncpu: 859.6838214570839 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 119.71220533684314,
            "unit": "ns/iter",
            "extra": "iterations: 5474353\ncpu: 119.67204160930056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 83.22564952984447,
            "unit": "ns/iter",
            "extra": "iterations: 8525461\ncpu: 83.22447313992751 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2009.9329939010354,
            "unit": "ns/iter",
            "extra": "iterations: 346931\ncpu: 2008.8317273463638 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.39823211795598,
            "unit": "ns/iter",
            "extra": "iterations: 27603612\ncpu: 25.39008300797737 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1464.1453695883843,
            "unit": "ns/iter",
            "extra": "iterations: 473748\ncpu: 1464.1307192853576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1241.1164858660363,
            "unit": "ns/iter",
            "extra": "iterations: 566137\ncpu: 1241.0476616084122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1806.71851667623,
            "unit": "ns/iter",
            "extra": "iterations: 415724\ncpu: 1806.2440465308682 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 71.16561892333196,
            "unit": "ns/iter",
            "extra": "iterations: 10099553\ncpu: 70.75748797991348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2144.0224546816585,
            "unit": "ns/iter",
            "extra": "iterations: 324677\ncpu: 2144.0262168247214 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 90.15119246651334,
            "unit": "ns/iter",
            "extra": "iterations: 7508232\ncpu: 90.1382642411691 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 83.09598253326273,
            "unit": "ns/iter",
            "extra": "iterations: 8125457\ncpu: 83.04726737216156 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 222.6804654324616,
            "unit": "ns/iter",
            "extra": "iterations: 3224157\ncpu: 222.1064296806897 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 911.1679984562679,
            "unit": "ns/iter",
            "extra": "iterations: 780214\ncpu: 910.9821151632777 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 141.33047335811,
            "unit": "ns/iter",
            "extra": "iterations: 4601782\ncpu: 141.27005581750706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 650.3359780677029,
            "unit": "ns/iter",
            "extra": "iterations: 997961\ncpu: 649.5995334487001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1225.7751268319025,
            "unit": "ns/iter",
            "extra": "iterations: 591951\ncpu: 1225.6504339041535 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729719800833,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3946655988.6932373,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3945719999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 532.5578412517351,
            "unit": "ns/iter",
            "extra": "iterations: 1332800\ncpu: 532.2974189675875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 898.1772635576856,
            "unit": "ns/iter",
            "extra": "iterations: 761747\ncpu: 897.9411799455734 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 122.36177391366682,
            "unit": "ns/iter",
            "extra": "iterations: 5580535\ncpu: 122.34292948615122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 83.11433245823812,
            "unit": "ns/iter",
            "extra": "iterations: 8126589\ncpu: 83.09784092686391 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2081.6259684896045,
            "unit": "ns/iter",
            "extra": "iterations: 351261\ncpu: 2080.3021115352976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.198663027078652,
            "unit": "ns/iter",
            "extra": "iterations: 26411207\ncpu: 25.19468345388385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1444.3140268434117,
            "unit": "ns/iter",
            "extra": "iterations: 471066\ncpu: 1444.1946563751144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1294.910941207806,
            "unit": "ns/iter",
            "extra": "iterations: 534372\ncpu: 1293.7055085221518 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1615.0862945328179,
            "unit": "ns/iter",
            "extra": "iterations: 406346\ncpu: 1614.1367209225607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 64.27431295907165,
            "unit": "ns/iter",
            "extra": "iterations: 10487206\ncpu: 64.21014329269377 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2074.9221575876372,
            "unit": "ns/iter",
            "extra": "iterations: 340328\ncpu: 2074.2195764086387 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.67866963741487,
            "unit": "ns/iter",
            "extra": "iterations: 8135940\ncpu: 82.64244819897881 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 80.01955967281577,
            "unit": "ns/iter",
            "extra": "iterations: 8194994\ncpu: 80.00420744664355 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 204.10129619810712,
            "unit": "ns/iter",
            "extra": "iterations: 3343731\ncpu: 204.0651595478232 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 869.0812084259197,
            "unit": "ns/iter",
            "extra": "iterations: 822349\ncpu: 869.0276269564381 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 138.92387647878542,
            "unit": "ns/iter",
            "extra": "iterations: 5108408\ncpu: 138.8596995384855 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 625.2376798312367,
            "unit": "ns/iter",
            "extra": "iterations: 1118568\ncpu: 623.8592557627272 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1137.5640278679348,
            "unit": "ns/iter",
            "extra": "iterations: 603776\ncpu: 1137.5129186983213 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729720794704,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4015878200.531006,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4014821000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 499.9410166971804,
            "unit": "ns/iter",
            "extra": "iterations: 1356984\ncpu: 499.91746402315766 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 827.5683938388673,
            "unit": "ns/iter",
            "extra": "iterations: 830240\ncpu: 827.222248988245 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 118.04546924446237,
            "unit": "ns/iter",
            "extra": "iterations: 5932807\ncpu: 118.01243492330022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.19950596698065,
            "unit": "ns/iter",
            "extra": "iterations: 9077234\ncpu: 77.19730481774508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1956.208323691362,
            "unit": "ns/iter",
            "extra": "iterations: 366921\ncpu: 1956.0695626579052 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.032377365501112,
            "unit": "ns/iter",
            "extra": "iterations: 29370670\ncpu: 24.02822271333957 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1496.3472329071512,
            "unit": "ns/iter",
            "extra": "iterations: 484701\ncpu: 1496.3183488377383 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1214.3172950586406,
            "unit": "ns/iter",
            "extra": "iterations: 573089\ncpu: 1213.7451600013267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1448.1504003406317,
            "unit": "ns/iter",
            "extra": "iterations: 472230\ncpu: 1448.1396776994286 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.42176019550064,
            "unit": "ns/iter",
            "extra": "iterations: 11625203\ncpu: 60.41322461207772 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1885.3206650010854,
            "unit": "ns/iter",
            "extra": "iterations: 370649\ncpu: 1885.0205990033714 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.37140253978716,
            "unit": "ns/iter",
            "extra": "iterations: 9088076\ncpu: 77.36698064584836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.33207280577956,
            "unit": "ns/iter",
            "extra": "iterations: 9299483\ncpu: 74.32423931523951 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 192.43943918066105,
            "unit": "ns/iter",
            "extra": "iterations: 3642096\ncpu: 192.41310498130795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 799.4032203226883,
            "unit": "ns/iter",
            "extra": "iterations: 894775\ncpu: 799.3484395518448 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.87773881123427,
            "unit": "ns/iter",
            "extra": "iterations: 5597850\ncpu: 124.86079476942076 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 572.9267757044811,
            "unit": "ns/iter",
            "extra": "iterations: 1223413\ncpu: 571.790556418807 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1060.5853672553258,
            "unit": "ns/iter",
            "extra": "iterations: 660010\ncpu: 1060.5112043756953 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729722885775,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3884517192.840576,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3881742000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 489.0506237426862,
            "unit": "ns/iter",
            "extra": "iterations: 1416070\ncpu: 488.7738600492913 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 788.0450734267478,
            "unit": "ns/iter",
            "extra": "iterations: 895049\ncpu: 787.6295040830177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 111.03459819364056,
            "unit": "ns/iter",
            "extra": "iterations: 6331747\ncpu: 110.963530286349 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 79.19651052570966,
            "unit": "ns/iter",
            "extra": "iterations: 8986341\ncpu: 79.15079118408723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1903.4140223914171,
            "unit": "ns/iter",
            "extra": "iterations: 372600\ncpu: 1900.9125067096088 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.067136326944603,
            "unit": "ns/iter",
            "extra": "iterations: 28982747\ncpu: 26.042804017162354 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1477.2253949948802,
            "unit": "ns/iter",
            "extra": "iterations: 475266\ncpu: 1476.3921677544793 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1167.0255038586945,
            "unit": "ns/iter",
            "extra": "iterations: 598705\ncpu: 1166.4358907976393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1435.6640300067743,
            "unit": "ns/iter",
            "extra": "iterations: 488909\ncpu: 1434.8314307979597 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.781868618172346,
            "unit": "ns/iter",
            "extra": "iterations: 11580393\ncpu: 60.74681576005217 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1894.097682043965,
            "unit": "ns/iter",
            "extra": "iterations: 362946\ncpu: 1893.1356179707125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.30296379257703,
            "unit": "ns/iter",
            "extra": "iterations: 8957592\ncpu: 78.25719233472547 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.73631519919363,
            "unit": "ns/iter",
            "extra": "iterations: 9364924\ncpu: 74.69553410150485 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 193.80238412596347,
            "unit": "ns/iter",
            "extra": "iterations: 3615497\ncpu: 193.69453217635103 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 811.4384826914336,
            "unit": "ns/iter",
            "extra": "iterations: 874060\ncpu: 806.9388829142127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 127.95571741445845,
            "unit": "ns/iter",
            "extra": "iterations: 5486194\ncpu: 127.89011835892087 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 578.1203434467665,
            "unit": "ns/iter",
            "extra": "iterations: 1207667\ncpu: 577.2534978599244 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1103.9385606081505,
            "unit": "ns/iter",
            "extra": "iterations: 669619\ncpu: 1103.2243708735864 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729777868076,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3667955875.3967285,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3667619999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 500.43487548828125,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 500.413 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 805.7481260364448,
            "unit": "ns/iter",
            "extra": "iterations: 876150\ncpu: 805.5321577355473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 118.01697916427901,
            "unit": "ns/iter",
            "extra": "iterations: 6067593\ncpu: 118.00494858504835 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 82.3389353563304,
            "unit": "ns/iter",
            "extra": "iterations: 8623770\ncpu: 82.31840598717271 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2004.3748777933781,
            "unit": "ns/iter",
            "extra": "iterations: 349260\ncpu: 2003.8395464696794 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.902761937160108,
            "unit": "ns/iter",
            "extra": "iterations: 27000860\ncpu: 25.860546664069215 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1441.0126621382215,
            "unit": "ns/iter",
            "extra": "iterations: 488612\ncpu: 1440.9122166463353 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1241.9063867126404,
            "unit": "ns/iter",
            "extra": "iterations: 560242\ncpu: 1241.2885860039066 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1521.7801195089057,
            "unit": "ns/iter",
            "extra": "iterations: 456317\ncpu: 1517.276367086915 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 66.48207235048076,
            "unit": "ns/iter",
            "extra": "iterations: 10792476\ncpu: 66.48150063062447 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2009.7761461577902,
            "unit": "ns/iter",
            "extra": "iterations: 350039\ncpu: 2009.447518705056 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.9095454462866,
            "unit": "ns/iter",
            "extra": "iterations: 8415181\ncpu: 82.89281002987327 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 79.78288196004674,
            "unit": "ns/iter",
            "extra": "iterations: 8923905\ncpu: 79.78233744083997 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 205.79859824837797,
            "unit": "ns/iter",
            "extra": "iterations: 3399791\ncpu: 205.66175979641034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 850.8032976122998,
            "unit": "ns/iter",
            "extra": "iterations: 810045\ncpu: 850.2675777271595 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 133.2847645300035,
            "unit": "ns/iter",
            "extra": "iterations: 5154639\ncpu: 133.26539453102308 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 603.4604807144826,
            "unit": "ns/iter",
            "extra": "iterations: 1167503\ncpu: 602.2374246575836 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1095.2329176254912,
            "unit": "ns/iter",
            "extra": "iterations: 640779\ncpu: 1094.9484923819318 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729789086495,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5531661987.3046875,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5479588000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 615.8464052103136,
            "unit": "ns/iter",
            "extra": "iterations: 1231549\ncpu: 613.5257306043048 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 994.3653673598387,
            "unit": "ns/iter",
            "extra": "iterations: 760828\ncpu: 983.2734862544484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 167.947964682133,
            "unit": "ns/iter",
            "extra": "iterations: 4928675\ncpu: 163.23656966628985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 124.20691369803241,
            "unit": "ns/iter",
            "extra": "iterations: 5644524\ncpu: 118.10420152345907 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2589.2700075717626,
            "unit": "ns/iter",
            "extra": "iterations: 309782\ncpu: 2546.248652278052 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 32.13338427682445,
            "unit": "ns/iter",
            "extra": "iterations: 21455939\ncpu: 31.969796334711752 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1747.7264126383925,
            "unit": "ns/iter",
            "extra": "iterations: 390374\ncpu: 1735.6125151777533 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1769.202943171062,
            "unit": "ns/iter",
            "extra": "iterations: 478659\ncpu: 1766.5749521057753 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1655.9132438371314,
            "unit": "ns/iter",
            "extra": "iterations: 402114\ncpu: 1647.5626314925637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 70.94064286159414,
            "unit": "ns/iter",
            "extra": "iterations: 10507513\ncpu: 70.34775974105379 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2156.431831958746,
            "unit": "ns/iter",
            "extra": "iterations: 328969\ncpu: 2154.4461636202846 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 109.49647796966666,
            "unit": "ns/iter",
            "extra": "iterations: 8164884\ncpu: 107.66595091859259 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 89.22669588885958,
            "unit": "ns/iter",
            "extra": "iterations: 8644216\ncpu: 89.19848833023185 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 232.3936850842719,
            "unit": "ns/iter",
            "extra": "iterations: 3277215\ncpu: 232.30822512407588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 935.5982774063456,
            "unit": "ns/iter",
            "extra": "iterations: 621752\ncpu: 934.6733102587523 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 153.3054918204448,
            "unit": "ns/iter",
            "extra": "iterations: 4869193\ncpu: 152.5410884308754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 697.4163641910015,
            "unit": "ns/iter",
            "extra": "iterations: 1035059\ncpu: 697.2723294034473 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1298.2505310810368,
            "unit": "ns/iter",
            "extra": "iterations: 569940\ncpu: 1297.5944836298536 ns\nthreads: 1"
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
        "date": 1729796859763,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3693754196.166992,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3693149999.999999 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 487.97506699547745,
            "unit": "ns/iter",
            "extra": "iterations: 1440477\ncpu: 487.94670098863077 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 785.8058972794133,
            "unit": "ns/iter",
            "extra": "iterations: 893336\ncpu: 785.6730278417074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 109.85175262002176,
            "unit": "ns/iter",
            "extra": "iterations: 6376331\ncpu: 109.84984938830814 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.58486772191765,
            "unit": "ns/iter",
            "extra": "iterations: 9022944\ncpu: 77.5791138679349 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1878.736459176194,
            "unit": "ns/iter",
            "extra": "iterations: 372808\ncpu: 1878.6640844617073 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.629768825144847,
            "unit": "ns/iter",
            "extra": "iterations: 25563679\ncpu: 25.625615155001736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1405.5701129534002,
            "unit": "ns/iter",
            "extra": "iterations: 490605\ncpu: 1405.356651481334 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1167.1011749507645,
            "unit": "ns/iter",
            "extra": "iterations: 595309\ncpu: 1166.404337915268 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1461.510075922442,
            "unit": "ns/iter",
            "extra": "iterations: 488111\ncpu: 1461.1676442448513 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 62.54555210628816,
            "unit": "ns/iter",
            "extra": "iterations: 11203047\ncpu: 62.544413140460925 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1888.5787344656176,
            "unit": "ns/iter",
            "extra": "iterations: 369265\ncpu: 1888.1968234194972 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 83.82344590299591,
            "unit": "ns/iter",
            "extra": "iterations: 8997198\ncpu: 83.81487214130445 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 77.05635874829379,
            "unit": "ns/iter",
            "extra": "iterations: 8689391\ncpu: 77.0556877921591 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 196.86331863001232,
            "unit": "ns/iter",
            "extra": "iterations: 3586727\ncpu: 196.82791581293893 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 825.4541008479608,
            "unit": "ns/iter",
            "extra": "iterations: 880669\ncpu: 825.1908492293929 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 133.5432920233454,
            "unit": "ns/iter",
            "extra": "iterations: 5292005\ncpu: 133.53691086837668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 607.5938047842161,
            "unit": "ns/iter",
            "extra": "iterations: 1123415\ncpu: 607.5484126524948 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1099.6400679057742,
            "unit": "ns/iter",
            "extra": "iterations: 629576\ncpu: 1099.622603148784 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729797340166,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5668861150.741577,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 5660917000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 809.4543258752127,
            "unit": "ns/iter",
            "extra": "iterations: 852058\ncpu: 803.2939072222798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1136.4912741498945,
            "unit": "ns/iter",
            "extra": "iterations: 492573\ncpu: 1135.616446699271 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 167.0428296697284,
            "unit": "ns/iter",
            "extra": "iterations: 4275880\ncpu: 166.85103417308304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 112.50428695322027,
            "unit": "ns/iter",
            "extra": "iterations: 6157473\ncpu: 112.32562448913671 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 3529.5163891724424,
            "unit": "ns/iter",
            "extra": "iterations: 230703\ncpu: 3516.61226772084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 36.7074866519452,
            "unit": "ns/iter",
            "extra": "iterations: 22173160\ncpu: 36.62725565503517 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1840.115898847325,
            "unit": "ns/iter",
            "extra": "iterations: 374064\ncpu: 1832.3174643911254 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1648.1169846689227,
            "unit": "ns/iter",
            "extra": "iterations: 458175\ncpu: 1634.4846401484144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1868.6395057638977,
            "unit": "ns/iter",
            "extra": "iterations: 346808\ncpu: 1867.3098659777127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 77.10246390440781,
            "unit": "ns/iter",
            "extra": "iterations: 10505463\ncpu: 77.05600409996228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2449.080302687189,
            "unit": "ns/iter",
            "extra": "iterations: 284363\ncpu: 2440.0818671908773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 93.96502704129858,
            "unit": "ns/iter",
            "extra": "iterations: 6594877\ncpu: 93.75519816366581 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 99.589332475227,
            "unit": "ns/iter",
            "extra": "iterations: 5889529\ncpu: 99.535124116037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 258.23954117305186,
            "unit": "ns/iter",
            "extra": "iterations: 2881453\ncpu: 257.41526931030995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 1141.5519170777359,
            "unit": "ns/iter",
            "extra": "iterations: 704793\ncpu: 1135.4780765416197 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 191.64204251748603,
            "unit": "ns/iter",
            "extra": "iterations: 3891526\ncpu: 188.0897108229523 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 505.8834972329655,
            "unit": "ns/iter",
            "extra": "iterations: 1216679\ncpu: 504.9351554518482 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1457.086278024298,
            "unit": "ns/iter",
            "extra": "iterations: 417978\ncpu: 1456.3278450062005 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729798234162,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3908737182.6171875,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3905923999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 497.35039606417325,
            "unit": "ns/iter",
            "extra": "iterations: 1422452\ncpu: 496.99322015786817 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 790.9899359598162,
            "unit": "ns/iter",
            "extra": "iterations: 885717\ncpu: 790.5549966863014 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 113.65955450427458,
            "unit": "ns/iter",
            "extra": "iterations: 6320542\ncpu: 113.57380427184884 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.61496367236703,
            "unit": "ns/iter",
            "extra": "iterations: 9021316\ncpu: 77.56695364623086 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1875.5549146964104,
            "unit": "ns/iter",
            "extra": "iterations: 371804\ncpu: 1874.3908080601614 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.809043674752694,
            "unit": "ns/iter",
            "extra": "iterations: 29453718\ncpu: 23.795909229524014 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1592.2730571203665,
            "unit": "ns/iter",
            "extra": "iterations: 509684\ncpu: 1491.053280071571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1173.2207937885332,
            "unit": "ns/iter",
            "extra": "iterations: 533748\ncpu: 1172.2273432406273 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1436.9960955424085,
            "unit": "ns/iter",
            "extra": "iterations: 488851\ncpu: 1434.727555021875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.075079741034784,
            "unit": "ns/iter",
            "extra": "iterations: 11003867\ncpu: 60.032895708390484 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1899.4620653729412,
            "unit": "ns/iter",
            "extra": "iterations: 371720\ncpu: 1898.1706660927641 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.09933035602938,
            "unit": "ns/iter",
            "extra": "iterations: 9005300\ncpu: 82.04113133377004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 85.67256212168508,
            "unit": "ns/iter",
            "extra": "iterations: 8671200\ncpu: 85.51930528646534 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 201.72572672303986,
            "unit": "ns/iter",
            "extra": "iterations: 3420758\ncpu: 201.29135121514034 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 794.4667062741332,
            "unit": "ns/iter",
            "extra": "iterations: 865159\ncpu: 794.0413265076099 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.99984930616193,
            "unit": "ns/iter",
            "extra": "iterations: 5587172\ncpu: 125.91862215804339 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 404.295620657324,
            "unit": "ns/iter",
            "extra": "iterations: 1728784\ncpu: 404.082291367804 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1049.8751102629878,
            "unit": "ns/iter",
            "extra": "iterations: 665222\ncpu: 1049.2211622586144 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729798659345,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4127115011.21521,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4123461000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 531.9378286645942,
            "unit": "ns/iter",
            "extra": "iterations: 1325933\ncpu: 531.5985046001562 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 846.6775429234415,
            "unit": "ns/iter",
            "extra": "iterations: 823995\ncpu: 846.0342599166248 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 120.14762299690166,
            "unit": "ns/iter",
            "extra": "iterations: 5834987\ncpu: 119.95296647618927 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 85.10319600614662,
            "unit": "ns/iter",
            "extra": "iterations: 8396406\ncpu: 85.04745959163958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2013.0242663131457,
            "unit": "ns/iter",
            "extra": "iterations: 349040\ncpu: 2011.895484758195 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.691993738879223,
            "unit": "ns/iter",
            "extra": "iterations: 27338624\ncpu: 25.67356718465418 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1585.4689302534819,
            "unit": "ns/iter",
            "extra": "iterations: 472083\ncpu: 1574.8078198113499 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1404.7076292083214,
            "unit": "ns/iter",
            "extra": "iterations: 490025\ncpu: 1386.0884648742424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1689.6217890804005,
            "unit": "ns/iter",
            "extra": "iterations: 380032\ncpu: 1673.8406239474568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 65.41750654761182,
            "unit": "ns/iter",
            "extra": "iterations: 10724682\ncpu: 65.347019147048 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2061.1725438706217,
            "unit": "ns/iter",
            "extra": "iterations: 342885\ncpu: 2059.1189465855923 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 84.92349171563998,
            "unit": "ns/iter",
            "extra": "iterations: 8073725\ncpu: 84.87655945675623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 80.39408450313893,
            "unit": "ns/iter",
            "extra": "iterations: 8724698\ncpu: 80.34467210211756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 206.87740411964907,
            "unit": "ns/iter",
            "extra": "iterations: 3396673\ncpu: 206.65486492223508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 855.1504119512224,
            "unit": "ns/iter",
            "extra": "iterations: 827678\ncpu: 851.8711382929162 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 137.37221245209662,
            "unit": "ns/iter",
            "extra": "iterations: 5139161\ncpu: 137.2506134756235 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 437.57121706623576,
            "unit": "ns/iter",
            "extra": "iterations: 1569141\ncpu: 437.3220762187711 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1145.111391845617,
            "unit": "ns/iter",
            "extra": "iterations: 613997\ncpu: 1144.539794168374 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729799501811,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3633292913.4368896,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3630856999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 484.83725421999367,
            "unit": "ns/iter",
            "extra": "iterations: 1447094\ncpu: 484.55801765469295 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 787.3737141475939,
            "unit": "ns/iter",
            "extra": "iterations: 891288\ncpu: 786.910628214449 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 112.65005709006003,
            "unit": "ns/iter",
            "extra": "iterations: 6318032\ncpu: 112.29493614467297 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 81.93497006834698,
            "unit": "ns/iter",
            "extra": "iterations: 8379621\ncpu: 81.12037525324828 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1893.1576848420707,
            "unit": "ns/iter",
            "extra": "iterations: 375984\ncpu: 1891.4608068428454 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.864126598091577,
            "unit": "ns/iter",
            "extra": "iterations: 29393486\ncpu: 23.8503864427649 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1389.6636576854557,
            "unit": "ns/iter",
            "extra": "iterations: 507920\ncpu: 1388.48637580721 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1177.14302158703,
            "unit": "ns/iter",
            "extra": "iterations: 601091\ncpu: 1176.5290114142472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1435.6016134084873,
            "unit": "ns/iter",
            "extra": "iterations: 487363\ncpu: 1434.7683348961668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 59.884224321536315,
            "unit": "ns/iter",
            "extra": "iterations: 11716069\ncpu: 59.84780390077935 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1913.6292675760599,
            "unit": "ns/iter",
            "extra": "iterations: 364121\ncpu: 1912.3670428236744 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 79.42071689370924,
            "unit": "ns/iter",
            "extra": "iterations: 8858293\ncpu: 79.35885615885577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 73.75397992747543,
            "unit": "ns/iter",
            "extra": "iterations: 9483553\ncpu: 73.70718548206571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.59735324510427,
            "unit": "ns/iter",
            "extra": "iterations: 3704841\ncpu: 190.4173485447827 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 797.8957758407303,
            "unit": "ns/iter",
            "extra": "iterations: 895255\ncpu: 797.4833985847584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.03839486717187,
            "unit": "ns/iter",
            "extra": "iterations: 5597269\ncpu: 125.85566282413785 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 411.3326674776108,
            "unit": "ns/iter",
            "extra": "iterations: 1712274\ncpu: 410.75552160460336 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1056.112514591235,
            "unit": "ns/iter",
            "extra": "iterations: 657357\ncpu: 1055.5056080638049 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729801002628,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3681953907.0129395,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3680602000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 489.1919082226944,
            "unit": "ns/iter",
            "extra": "iterations: 1440884\ncpu: 489.0650461799837 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 785.9410059125253,
            "unit": "ns/iter",
            "extra": "iterations: 864294\ncpu: 785.859904152985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 109.97990493555237,
            "unit": "ns/iter",
            "extra": "iterations: 6361034\ncpu: 109.97504493766267 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.90062803575711,
            "unit": "ns/iter",
            "extra": "iterations: 9051646\ncpu: 77.87368175909653 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1923.598166153543,
            "unit": "ns/iter",
            "extra": "iterations: 354689\ncpu: 1923.5753011793433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.018031504262048,
            "unit": "ns/iter",
            "extra": "iterations: 29385096\ncpu: 24.016868959693046 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1376.1818638803575,
            "unit": "ns/iter",
            "extra": "iterations: 509591\ncpu: 1376.1644142066903 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1163.5855801105463,
            "unit": "ns/iter",
            "extra": "iterations: 600853\ncpu: 1163.5757830950326 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1438.526267817805,
            "unit": "ns/iter",
            "extra": "iterations: 487499\ncpu: 1438.468591730445 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 59.67220749411669,
            "unit": "ns/iter",
            "extra": "iterations: 11711365\ncpu: 59.663924743187486 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1907.6204570182747,
            "unit": "ns/iter",
            "extra": "iterations: 364876\ncpu: 1907.6042271895128 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.45575956044392,
            "unit": "ns/iter",
            "extra": "iterations: 9043460\ncpu: 77.44756984605442 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 73.7047951555407,
            "unit": "ns/iter",
            "extra": "iterations: 9516300\ncpu: 73.69597427571667 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 189.63472273050263,
            "unit": "ns/iter",
            "extra": "iterations: 3692762\ncpu: 189.63258395748255 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 792.9034995041499,
            "unit": "ns/iter",
            "extra": "iterations: 894969\ncpu: 791.5413829976223 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.4998974642573,
            "unit": "ns/iter",
            "extra": "iterations: 5630268\ncpu: 124.48199623890059 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 344.63173143465247,
            "unit": "ns/iter",
            "extra": "iterations: 2048395\ncpu: 344.5995523324359 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1050.8057018127442,
            "unit": "ns/iter",
            "extra": "iterations: 665481\ncpu: 1050.7151969778267 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729802720540,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4314466238.021851,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4304466000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 588.6346794483447,
            "unit": "ns/iter",
            "extra": "iterations: 1328778\ncpu: 582.0453077940784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 1011.0142665239048,
            "unit": "ns/iter",
            "extra": "iterations: 809127\ncpu: 999.354860238258 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 118.09019920630085,
            "unit": "ns/iter",
            "extra": "iterations: 5972340\ncpu: 118.0840340637004 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 82.7971871848615,
            "unit": "ns/iter",
            "extra": "iterations: 8445335\ncpu: 82.79505786330543 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1976.788898151306,
            "unit": "ns/iter",
            "extra": "iterations: 340528\ncpu: 1976.6920781844658 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.965980660458218,
            "unit": "ns/iter",
            "extra": "iterations: 27310572\ncpu: 25.96547593364212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1473.747970152467,
            "unit": "ns/iter",
            "extra": "iterations: 431609\ncpu: 1473.2153407366409 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1228.6070955614832,
            "unit": "ns/iter",
            "extra": "iterations: 553360\ncpu: 1228.5763336706668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1585.7166950936191,
            "unit": "ns/iter",
            "extra": "iterations: 450619\ncpu: 1585.3437160883204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 65.6441754494369,
            "unit": "ns/iter",
            "extra": "iterations: 10605418\ncpu: 65.64059992732022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1980.9860105866776,
            "unit": "ns/iter",
            "extra": "iterations: 366580\ncpu: 1977.579246003604 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.99848127151824,
            "unit": "ns/iter",
            "extra": "iterations: 8648595\ncpu: 78.99132749307851 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 78.97169873865754,
            "unit": "ns/iter",
            "extra": "iterations: 9209072\ncpu: 78.90501887703758 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 204.48019214042466,
            "unit": "ns/iter",
            "extra": "iterations: 3523803\ncpu: 204.46545961848625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 840.8623183632757,
            "unit": "ns/iter",
            "extra": "iterations: 829433\ncpu: 840.8334368176808 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 137.67456118352857,
            "unit": "ns/iter",
            "extra": "iterations: 5300581\ncpu: 137.6600036863883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 391.50032907133624,
            "unit": "ns/iter",
            "extra": "iterations: 1771018\ncpu: 391.4765406111075 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1202.5435942966085,
            "unit": "ns/iter",
            "extra": "iterations: 600364\ncpu: 1202.5304648513272 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729864807336,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3925325155.2581787,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3923790000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 512.3315767501311,
            "unit": "ns/iter",
            "extra": "iterations: 1356721\ncpu: 511.96671976036396 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 837.5328283643634,
            "unit": "ns/iter",
            "extra": "iterations: 864945\ncpu: 836.9295157495565 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 121.23730976765437,
            "unit": "ns/iter",
            "extra": "iterations: 5890867\ncpu: 121.19608200286966 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 84.38662314463669,
            "unit": "ns/iter",
            "extra": "iterations: 8082394\ncpu: 84.3472862124761 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2083.755380266859,
            "unit": "ns/iter",
            "extra": "iterations: 342892\ncpu: 2083.116549817433 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.29501917381408,
            "unit": "ns/iter",
            "extra": "iterations: 27285130\ncpu: 26.2647456691612 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1592.9834782837272,
            "unit": "ns/iter",
            "extra": "iterations: 436164\ncpu: 1592.4354142019986 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1287.4212881343085,
            "unit": "ns/iter",
            "extra": "iterations: 547204\ncpu: 1286.6627436933911 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1555.728891094192,
            "unit": "ns/iter",
            "extra": "iterations: 453077\ncpu: 1554.8173930700518 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 65.02474977817985,
            "unit": "ns/iter",
            "extra": "iterations: 10974883\ncpu: 64.85126082893102 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2020.153734954039,
            "unit": "ns/iter",
            "extra": "iterations: 321878\ncpu: 2016.959841927681 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 89.27042986060889,
            "unit": "ns/iter",
            "extra": "iterations: 8301117\ncpu: 89.21980017869889 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 82.73743908936974,
            "unit": "ns/iter",
            "extra": "iterations: 9076410\ncpu: 82.71893843490979 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 207.53709280536503,
            "unit": "ns/iter",
            "extra": "iterations: 3306285\ncpu: 207.5329259274373 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 847.9364539227475,
            "unit": "ns/iter",
            "extra": "iterations: 823510\ncpu: 847.8828429527292 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 137.76766344403956,
            "unit": "ns/iter",
            "extra": "iterations: 5152059\ncpu: 137.65447950033177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 367.01140693929847,
            "unit": "ns/iter",
            "extra": "iterations: 1808033\ncpu: 366.9855583388137 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1173.1391620969903,
            "unit": "ns/iter",
            "extra": "iterations: 600621\ncpu: 1172.8544289993235 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729866355322,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3904969930.6488037,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3901273000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 487.69505056534774,
            "unit": "ns/iter",
            "extra": "iterations: 1440824\ncpu: 487.34265947818784 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 806.7085801060808,
            "unit": "ns/iter",
            "extra": "iterations: 875755\ncpu: 805.6830962997636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 111.24652978643596,
            "unit": "ns/iter",
            "extra": "iterations: 6325454\ncpu: 111.17336399885292 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.81824085020914,
            "unit": "ns/iter",
            "extra": "iterations: 8976546\ncpu: 77.77401240967302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1859.134679754847,
            "unit": "ns/iter",
            "extra": "iterations: 371227\ncpu: 1858.116462434037 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.805535285555447,
            "unit": "ns/iter",
            "extra": "iterations: 29307219\ncpu: 23.79191966320651 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1388.5768619536568,
            "unit": "ns/iter",
            "extra": "iterations: 505576\ncpu: 1387.7438802474776 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1179.318194334664,
            "unit": "ns/iter",
            "extra": "iterations: 588903\ncpu: 1178.5455329655301 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1444.2079784603272,
            "unit": "ns/iter",
            "extra": "iterations: 483974\ncpu: 1443.3296003504292 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.33784787952462,
            "unit": "ns/iter",
            "extra": "iterations: 11614402\ncpu: 60.303319964299575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1938.2313628734983,
            "unit": "ns/iter",
            "extra": "iterations: 366513\ncpu: 1936.9926851162156 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.90270252264551,
            "unit": "ns/iter",
            "extra": "iterations: 8995579\ncpu: 77.85457723177137 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.39421424362936,
            "unit": "ns/iter",
            "extra": "iterations: 9436633\ncpu: 74.35522818361204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.2285601895515,
            "unit": "ns/iter",
            "extra": "iterations: 3692899\ncpu: 190.10213926782146 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 784.3135558230949,
            "unit": "ns/iter",
            "extra": "iterations: 886323\ncpu: 783.8000367811705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.00329496257585,
            "unit": "ns/iter",
            "extra": "iterations: 5557629\ncpu: 124.9271946724039 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 347.49331843845926,
            "unit": "ns/iter",
            "extra": "iterations: 2026542\ncpu: 346.2208037139122 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1044.2451515162686,
            "unit": "ns/iter",
            "extra": "iterations: 666813\ncpu: 1043.6929094063873 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729867406666,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3669759035.1104736,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3665581999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 489.4755278546196,
            "unit": "ns/iter",
            "extra": "iterations: 1371178\ncpu: 489.13270195408626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 790.7087005868511,
            "unit": "ns/iter",
            "extra": "iterations: 879463\ncpu: 790.0514291107199 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 112.63848762794125,
            "unit": "ns/iter",
            "extra": "iterations: 6258885\ncpu: 112.57883792400736 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.45339771576391,
            "unit": "ns/iter",
            "extra": "iterations: 8980807\ncpu: 78.40965739493106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1869.6448493164328,
            "unit": "ns/iter",
            "extra": "iterations: 376164\ncpu: 1868.6689848044996 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.860809356559532,
            "unit": "ns/iter",
            "extra": "iterations: 29423262\ncpu: 23.84317551194698 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1384.8655058304314,
            "unit": "ns/iter",
            "extra": "iterations: 504181\ncpu: 1384.129905728302 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1202.282593735923,
            "unit": "ns/iter",
            "extra": "iterations: 597234\ncpu: 1195.439308545724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1526.694808704254,
            "unit": "ns/iter",
            "extra": "iterations: 436627\ncpu: 1524.2506762064631 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 63.59488979840663,
            "unit": "ns/iter",
            "extra": "iterations: 11049201\ncpu: 63.55192560982472 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1953.5538254185324,
            "unit": "ns/iter",
            "extra": "iterations: 355276\ncpu: 1952.4482374266795 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 80.14576114482209,
            "unit": "ns/iter",
            "extra": "iterations: 8794080\ncpu: 80.07693812200931 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.98527304401082,
            "unit": "ns/iter",
            "extra": "iterations: 9335698\ncpu: 74.94426233582108 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 189.73618944253218,
            "unit": "ns/iter",
            "extra": "iterations: 3644770\ncpu: 189.60702595774134 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 806.5193355198339,
            "unit": "ns/iter",
            "extra": "iterations: 878966\ncpu: 806.0118366353184 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.87664161520995,
            "unit": "ns/iter",
            "extra": "iterations: 5592707\ncpu: 125.7984729040875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 339.7892559608757,
            "unit": "ns/iter",
            "extra": "iterations: 2050459\ncpu: 339.60054797486623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1055.1613569160847,
            "unit": "ns/iter",
            "extra": "iterations: 663633\ncpu: 1053.0609538705876 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729867816863,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3658109903.3355713,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3657705000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 507.63308243198264,
            "unit": "ns/iter",
            "extra": "iterations: 1408799\ncpu: 500.5142678267095 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 802.6840924925064,
            "unit": "ns/iter",
            "extra": "iterations: 873188\ncpu: 802.3289371819138 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 127.18638298713307,
            "unit": "ns/iter",
            "extra": "iterations: 5911513\ncpu: 123.61031769700926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 80.83018970992114,
            "unit": "ns/iter",
            "extra": "iterations: 8019889\ncpu: 80.38590060286371 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2150.2003178088316,
            "unit": "ns/iter",
            "extra": "iterations: 346137\ncpu: 2100.390885689773 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.213288090994208,
            "unit": "ns/iter",
            "extra": "iterations: 26248983\ncpu: 26.717454158128675 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1582.1285315304124,
            "unit": "ns/iter",
            "extra": "iterations: 456624\ncpu: 1548.3745926626716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1352.7223600509653,
            "unit": "ns/iter",
            "extra": "iterations: 535815\ncpu: 1315.101294290007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1592.2852674780438,
            "unit": "ns/iter",
            "extra": "iterations: 445576\ncpu: 1564.5815753092647 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 63.26577568061816,
            "unit": "ns/iter",
            "extra": "iterations: 11468266\ncpu: 63.218537135430914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2018.755927970377,
            "unit": "ns/iter",
            "extra": "iterations: 350401\ncpu: 2018.2647880571083 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 80.24281784302757,
            "unit": "ns/iter",
            "extra": "iterations: 8197297\ncpu: 80.22290762430583 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 75.03962461849805,
            "unit": "ns/iter",
            "extra": "iterations: 9347542\ncpu: 75.0333082215625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.01535084937737,
            "unit": "ns/iter",
            "extra": "iterations: 3684075\ncpu: 189.99803207046568 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 801.4453146722001,
            "unit": "ns/iter",
            "extra": "iterations: 882568\ncpu: 800.9241214274691 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.32506180290397,
            "unit": "ns/iter",
            "extra": "iterations: 5601927\ncpu: 126.26119547791305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 345.7665169441858,
            "unit": "ns/iter",
            "extra": "iterations: 2049342\ncpu: 345.7641525914171 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1051.792527948694,
            "unit": "ns/iter",
            "extra": "iterations: 652735\ncpu: 1050.9931289114252 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729869445038,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3769068956.375122,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3768407000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 497.29439261525187,
            "unit": "ns/iter",
            "extra": "iterations: 1414307\ncpu: 497.13393202465886 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 800.7742475926897,
            "unit": "ns/iter",
            "extra": "iterations: 874344\ncpu: 800.6905748767072 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 111.73499142896924,
            "unit": "ns/iter",
            "extra": "iterations: 6303183\ncpu: 111.73481715507857 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 82.90788300443701,
            "unit": "ns/iter",
            "extra": "iterations: 8253160\ncpu: 82.87904269394988 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2020.5776847112688,
            "unit": "ns/iter",
            "extra": "iterations: 350577\ncpu: 2019.5762985021831 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.848823806730877,
            "unit": "ns/iter",
            "extra": "iterations: 26194272\ncpu: 25.837862567816376 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1472.6798072061465,
            "unit": "ns/iter",
            "extra": "iterations: 476268\ncpu: 1471.8582814717754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1239.473857576885,
            "unit": "ns/iter",
            "extra": "iterations: 560700\ncpu: 1239.475655430712 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1503.0427662095547,
            "unit": "ns/iter",
            "extra": "iterations: 464857\ncpu: 1502.92455529335 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 63.87847606520244,
            "unit": "ns/iter",
            "extra": "iterations: 11137806\ncpu: 63.8606023484339 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1943.6807723415634,
            "unit": "ns/iter",
            "extra": "iterations: 360212\ncpu: 1943.566566355364 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.44683228000942,
            "unit": "ns/iter",
            "extra": "iterations: 8635685\ncpu: 82.41037045700504 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 80.19707184349345,
            "unit": "ns/iter",
            "extra": "iterations: 8514054\ncpu: 78.06598360780926 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 201.91623476606384,
            "unit": "ns/iter",
            "extra": "iterations: 3573051\ncpu: 196.48697989477367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 853.4826481661828,
            "unit": "ns/iter",
            "extra": "iterations: 858759\ncpu: 825.1884405287129 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 140.19627899939331,
            "unit": "ns/iter",
            "extra": "iterations: 5420978\ncpu: 135.51576855689086 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 372.2535711043489,
            "unit": "ns/iter",
            "extra": "iterations: 1849860\ncpu: 363.5907582195399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1149.95454987661,
            "unit": "ns/iter",
            "extra": "iterations: 647303\ncpu: 1111.86260530231 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870318870,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3966126918.7927246,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3963691999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 505.05196354580994,
            "unit": "ns/iter",
            "extra": "iterations: 1327996\ncpu: 504.35317576257705 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 846.6697017731598,
            "unit": "ns/iter",
            "extra": "iterations: 798367\ncpu: 846.1960476823318 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 114.42619368201674,
            "unit": "ns/iter",
            "extra": "iterations: 6226872\ncpu: 114.36769536936053 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.08583120571201,
            "unit": "ns/iter",
            "extra": "iterations: 9018294\ncpu: 78.04391828432294 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1868.943714018247,
            "unit": "ns/iter",
            "extra": "iterations: 375486\ncpu: 1867.768705091535 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.40270112940385,
            "unit": "ns/iter",
            "extra": "iterations: 28205108\ncpu: 24.389695653709225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1387.5842695373492,
            "unit": "ns/iter",
            "extra": "iterations: 497307\ncpu: 1386.7027811794362 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1185.808144974308,
            "unit": "ns/iter",
            "extra": "iterations: 586643\ncpu: 1185.1534919874603 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1467.2932091942607,
            "unit": "ns/iter",
            "extra": "iterations: 477236\ncpu: 1466.4966599334482 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.02876796678619,
            "unit": "ns/iter",
            "extra": "iterations: 11480680\ncpu: 59.99723012922587 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1926.6642615096316,
            "unit": "ns/iter",
            "extra": "iterations: 360017\ncpu: 1925.3257485063186 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.93211049345697,
            "unit": "ns/iter",
            "extra": "iterations: 9033424\ncpu: 77.88829573371086 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 76.47110287298511,
            "unit": "ns/iter",
            "extra": "iterations: 9449882\ncpu: 76.43270042948717 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 200.96711047845835,
            "unit": "ns/iter",
            "extra": "iterations: 3590443\ncpu: 200.8657427509642 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 809.6143840373012,
            "unit": "ns/iter",
            "extra": "iterations: 861326\ncpu: 808.0239073242898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 129.11819892421727,
            "unit": "ns/iter",
            "extra": "iterations: 5492953\ncpu: 129.05317048953387 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 357.3944631751015,
            "unit": "ns/iter",
            "extra": "iterations: 1980646\ncpu: 356.698269150571 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1126.6088169699779,
            "unit": "ns/iter",
            "extra": "iterations: 664818\ncpu: 1120.5202025215897 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870504690,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3881785154.3426514,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3871237000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 555.8209419250488,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 555.6010000000002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 788.0475692494158,
            "unit": "ns/iter",
            "extra": "iterations: 883381\ncpu: 787.9714415410792 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 110.96107047041185,
            "unit": "ns/iter",
            "extra": "iterations: 6329400\ncpu: 110.93800360223716 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.4271404340179,
            "unit": "ns/iter",
            "extra": "iterations: 9047902\ncpu: 77.4202682566633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1889.8597303487627,
            "unit": "ns/iter",
            "extra": "iterations: 367902\ncpu: 1889.641806785501 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.349405076189697,
            "unit": "ns/iter",
            "extra": "iterations: 28927891\ncpu: 24.341594760572118 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1397.8980360917935,
            "unit": "ns/iter",
            "extra": "iterations: 493674\ncpu: 1397.8313623970507 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1173.352878199494,
            "unit": "ns/iter",
            "extra": "iterations: 595537\ncpu: 1173.29233951879 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1537.1080038348584,
            "unit": "ns/iter",
            "extra": "iterations: 483415\ncpu: 1511.651479577589 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.196721361812074,
            "unit": "ns/iter",
            "extra": "iterations: 10913286\ncpu: 59.98037621299402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1936.5655925807287,
            "unit": "ns/iter",
            "extra": "iterations: 364585\ncpu: 1936.1026921019732 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.93360181471994,
            "unit": "ns/iter",
            "extra": "iterations: 8880882\ncpu: 77.93178650498898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 73.6286799162482,
            "unit": "ns/iter",
            "extra": "iterations: 9512421\ncpu: 73.6253157844887 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 191.62952198922656,
            "unit": "ns/iter",
            "extra": "iterations: 3453618\ncpu: 191.60486191582237 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 794.6554188960077,
            "unit": "ns/iter",
            "extra": "iterations: 887278\ncpu: 794.5457906090296 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.93347343883454,
            "unit": "ns/iter",
            "extra": "iterations: 5587841\ncpu: 126.886394942161 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 341.94287498365514,
            "unit": "ns/iter",
            "extra": "iterations: 2035831\ncpu: 341.9090287946305 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1057.4820176256587,
            "unit": "ns/iter",
            "extra": "iterations: 663161\ncpu: 1054.9821234964097 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870526742,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3619274139.404297,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3618915000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 528.9885112409391,
            "unit": "ns/iter",
            "extra": "iterations: 1404297\ncpu: 524.4780840520203 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 798.1118837959548,
            "unit": "ns/iter",
            "extra": "iterations: 881879\ncpu: 798.0822765935011 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 113.01429591452806,
            "unit": "ns/iter",
            "extra": "iterations: 6367399\ncpu: 113.01459198646093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.33442100061313,
            "unit": "ns/iter",
            "extra": "iterations: 9047084\ncpu: 77.32546752080555 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1865.7304036619337,
            "unit": "ns/iter",
            "extra": "iterations: 376565\ncpu: 1865.6301037005576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.278611090558766,
            "unit": "ns/iter",
            "extra": "iterations: 28997875\ncpu: 24.27577882862107 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1388.1357549119662,
            "unit": "ns/iter",
            "extra": "iterations: 504668\ncpu: 1387.9798203967757 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1177.340996614514,
            "unit": "ns/iter",
            "extra": "iterations: 595598\ncpu: 1177.2940809069191 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1534.876328099943,
            "unit": "ns/iter",
            "extra": "iterations: 482300\ncpu: 1534.6423387932841 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.23437903997738,
            "unit": "ns/iter",
            "extra": "iterations: 10981253\ncpu: 60.23347244617727 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1935.3978010967228,
            "unit": "ns/iter",
            "extra": "iterations: 367541\ncpu: 1935.2289948604416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.3824277670602,
            "unit": "ns/iter",
            "extra": "iterations: 8964245\ncpu: 77.37517214221626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 75.19398525806612,
            "unit": "ns/iter",
            "extra": "iterations: 9500285\ncpu: 75.12648304761402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 192.42179530059528,
            "unit": "ns/iter",
            "extra": "iterations: 3591291\ncpu: 192.40267636345735 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 807.9590054899734,
            "unit": "ns/iter",
            "extra": "iterations: 900136\ncpu: 807.581298825954 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 137.1692358397138,
            "unit": "ns/iter",
            "extra": "iterations: 5090909\ncpu: 136.80798458585647 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 344.71401263258076,
            "unit": "ns/iter",
            "extra": "iterations: 2023045\ncpu: 344.27459596795774 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1048.0102950981357,
            "unit": "ns/iter",
            "extra": "iterations: 668111\ncpu: 1047.6597451621128 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729870827385,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3646123886.1083984,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3644081000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 516.7435186205271,
            "unit": "ns/iter",
            "extra": "iterations: 1352526\ncpu: 514.2429794325575 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 880.1510323547418,
            "unit": "ns/iter",
            "extra": "iterations: 772371\ncpu: 877.2778884758754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 113.28080867658295,
            "unit": "ns/iter",
            "extra": "iterations: 5999674\ncpu: 112.87496620649723 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.49377994215489,
            "unit": "ns/iter",
            "extra": "iterations: 9047317\ncpu: 78.34101535294941 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1881.3850901995595,
            "unit": "ns/iter",
            "extra": "iterations: 370233\ncpu: 1879.7892138194043 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.07854419111671,
            "unit": "ns/iter",
            "extra": "iterations: 29029623\ncpu: 24.066554360695584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1394.2288483958405,
            "unit": "ns/iter",
            "extra": "iterations: 505466\ncpu: 1393.522017306799 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1170.8299413352909,
            "unit": "ns/iter",
            "extra": "iterations: 586343\ncpu: 1170.1614925052374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1440.3915113611836,
            "unit": "ns/iter",
            "extra": "iterations: 483930\ncpu: 1439.7206207509307 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 59.84428903332736,
            "unit": "ns/iter",
            "extra": "iterations: 11739648\ncpu: 59.775131247546916 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1922.1754850924758,
            "unit": "ns/iter",
            "extra": "iterations: 365165\ncpu: 1921.9585666753374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.5792141772304,
            "unit": "ns/iter",
            "extra": "iterations: 9044395\ncpu: 77.55543626743416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 73.66627288580241,
            "unit": "ns/iter",
            "extra": "iterations: 9512033\ncpu: 73.66553501233645 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 189.59085789272686,
            "unit": "ns/iter",
            "extra": "iterations: 3655123\ncpu: 189.5492983409861 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 789.8217924007738,
            "unit": "ns/iter",
            "extra": "iterations: 892846\ncpu: 789.8114568469798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.44527638759011,
            "unit": "ns/iter",
            "extra": "iterations: 5585032\ncpu: 125.4277504587259 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 344.76325933143386,
            "unit": "ns/iter",
            "extra": "iterations: 2041001\ncpu: 344.10223218900757 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1075.583362133285,
            "unit": "ns/iter",
            "extra": "iterations: 665557\ncpu: 1075.2437432105687 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729871055843,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 5223230123.519897,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4937885000.000001 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 552.5095735542943,
            "unit": "ns/iter",
            "extra": "iterations: 1287498\ncpu: 552.3752269906439 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 942.234016525634,
            "unit": "ns/iter",
            "extra": "iterations: 775632\ncpu: 938.8937021680393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 123.65953926565703,
            "unit": "ns/iter",
            "extra": "iterations: 5835570\ncpu: 123.57970172579557 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 85.1158354665972,
            "unit": "ns/iter",
            "extra": "iterations: 8356812\ncpu: 85.0618633038532 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2078.7108834025375,
            "unit": "ns/iter",
            "extra": "iterations: 344453\ncpu: 2077.0293770122535 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 26.382812227611186,
            "unit": "ns/iter",
            "extra": "iterations: 26592613\ncpu: 26.323212389846713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1730.12085987005,
            "unit": "ns/iter",
            "extra": "iterations: 471415\ncpu: 1717.5291409904253 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1543.7068773212545,
            "unit": "ns/iter",
            "extra": "iterations: 369528\ncpu: 1537.1419757095518 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1854.8308517340417,
            "unit": "ns/iter",
            "extra": "iterations: 391378\ncpu: 1848.0624869052415 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 73.55563946154564,
            "unit": "ns/iter",
            "extra": "iterations: 10193086\ncpu: 73.38768651613452 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2363.793764307318,
            "unit": "ns/iter",
            "extra": "iterations: 315654\ncpu: 2359.4537056397144 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 93.35818906206859,
            "unit": "ns/iter",
            "extra": "iterations: 7894796\ncpu: 92.96402338958465 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 87.06570817943235,
            "unit": "ns/iter",
            "extra": "iterations: 8198449\ncpu: 86.98938055234584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 215.55296910090743,
            "unit": "ns/iter",
            "extra": "iterations: 3091914\ncpu: 215.38826759088394 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 889.8868242389265,
            "unit": "ns/iter",
            "extra": "iterations: 816669\ncpu: 888.9954191967576 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 146.70728630611944,
            "unit": "ns/iter",
            "extra": "iterations: 4679739\ncpu: 146.6707865545495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 395.68571410182966,
            "unit": "ns/iter",
            "extra": "iterations: 1805650\ncpu: 395.6769030543017 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1178.6948810665326,
            "unit": "ns/iter",
            "extra": "iterations: 588127\ncpu: 1178.0567802532394 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729871196909,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4150923013.687134,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4148234000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 522.7489757123215,
            "unit": "ns/iter",
            "extra": "iterations: 1364177\ncpu: 522.4307402924987 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 839.2816402956589,
            "unit": "ns/iter",
            "extra": "iterations: 818618\ncpu: 838.673227317259 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 121.30227401432448,
            "unit": "ns/iter",
            "extra": "iterations: 5793455\ncpu: 121.23214903714631 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 82.6634820506175,
            "unit": "ns/iter",
            "extra": "iterations: 8390971\ncpu: 82.62130807030553 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2037.316453077704,
            "unit": "ns/iter",
            "extra": "iterations: 347937\ncpu: 2026.303612435585 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.361534753036164,
            "unit": "ns/iter",
            "extra": "iterations: 27577513\ncpu: 25.342350486789783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1469.801444676597,
            "unit": "ns/iter",
            "extra": "iterations: 473943\ncpu: 1468.8749490972514 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1243.8317469560843,
            "unit": "ns/iter",
            "extra": "iterations: 566600\ncpu: 1243.1097776208953 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1522.2280431802608,
            "unit": "ns/iter",
            "extra": "iterations: 444699\ncpu: 1521.4695782990293 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 63.04220593793794,
            "unit": "ns/iter",
            "extra": "iterations: 11231448\ncpu: 63.00567834174181 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2081.734996983179,
            "unit": "ns/iter",
            "extra": "iterations: 341508\ncpu: 2077.851763355469 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.19853559162495,
            "unit": "ns/iter",
            "extra": "iterations: 8214902\ncpu: 82.15387109913189 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 79.53856573095987,
            "unit": "ns/iter",
            "extra": "iterations: 8840393\ncpu: 79.4742948644932 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 204.55097909368,
            "unit": "ns/iter",
            "extra": "iterations: 3466994\ncpu: 204.4384847507681 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 840.019369226492,
            "unit": "ns/iter",
            "extra": "iterations: 865255\ncpu: 839.4970268880289 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 143.91618701133734,
            "unit": "ns/iter",
            "extra": "iterations: 5253954\ncpu: 141.69747203725075 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 373.13504899640105,
            "unit": "ns/iter",
            "extra": "iterations: 1890814\ncpu: 372.5310897846116 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1136.4575530676705,
            "unit": "ns/iter",
            "extra": "iterations: 573071\ncpu: 1135.6969729754203 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729871252547,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3638870000.8392334,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3638102000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 496.8903689949775,
            "unit": "ns/iter",
            "extra": "iterations: 1420985\ncpu: 496.69982441756974 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 791.6682247822275,
            "unit": "ns/iter",
            "extra": "iterations: 880769\ncpu: 791.501517423979 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 111.21725221859025,
            "unit": "ns/iter",
            "extra": "iterations: 6284114\ncpu: 111.2158372683882 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.56115879974777,
            "unit": "ns/iter",
            "extra": "iterations: 9022828\ncpu: 77.55694777734854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1862.178435738834,
            "unit": "ns/iter",
            "extra": "iterations: 376174\ncpu: 1862.1196573925893 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.203501547114357,
            "unit": "ns/iter",
            "extra": "iterations: 28691229\ncpu: 24.04846442792668 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1395.9859272968386,
            "unit": "ns/iter",
            "extra": "iterations: 506710\ncpu: 1388.6167630399993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1172.8834155398104,
            "unit": "ns/iter",
            "extra": "iterations: 598669\ncpu: 1172.870150283382 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1442.559332595969,
            "unit": "ns/iter",
            "extra": "iterations: 487153\ncpu: 1442.4687931717544 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.243156893552815,
            "unit": "ns/iter",
            "extra": "iterations: 11612090\ncpu: 60.24135190133738 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1911.7114189445715,
            "unit": "ns/iter",
            "extra": "iterations: 367728\ncpu: 1911.5161206108874 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.52997309822675,
            "unit": "ns/iter",
            "extra": "iterations: 9012025\ncpu: 78.52319539726075 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 78.68459876819578,
            "unit": "ns/iter",
            "extra": "iterations: 9378726\ncpu: 78.64138476803794 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 196.16750396689244,
            "unit": "ns/iter",
            "extra": "iterations: 3513986\ncpu: 196.0724943127262 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 792.9282119105593,
            "unit": "ns/iter",
            "extra": "iterations: 885359\ncpu: 792.7631616101481 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.01638041810688,
            "unit": "ns/iter",
            "extra": "iterations: 5611807\ncpu: 123.98234650621413 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 346.21577660984934,
            "unit": "ns/iter",
            "extra": "iterations: 2028004\ncpu: 345.41204060741427 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1045.1225774678978,
            "unit": "ns/iter",
            "extra": "iterations: 670974\ncpu: 1045.0643393037542 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729872043880,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4053214788.4368896,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4050252999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 528.1830903864683,
            "unit": "ns/iter",
            "extra": "iterations: 1329232\ncpu: 527.7919881555661 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 851.7411519120046,
            "unit": "ns/iter",
            "extra": "iterations: 817098\ncpu: 850.9297538361376 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 119.85846552056141,
            "unit": "ns/iter",
            "extra": "iterations: 5871991\ncpu: 119.68308534532825 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 83.22419670871216,
            "unit": "ns/iter",
            "extra": "iterations: 8424701\ncpu: 83.1755334699711 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2006.816966867027,
            "unit": "ns/iter",
            "extra": "iterations: 349561\ncpu: 2005.272327290521 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.55582936990721,
            "unit": "ns/iter",
            "extra": "iterations: 27407451\ncpu: 25.543017480903313 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1488.8762927212226,
            "unit": "ns/iter",
            "extra": "iterations: 472529\ncpu: 1488.1351197492597 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1259.9834870134932,
            "unit": "ns/iter",
            "extra": "iterations: 554767\ncpu: 1258.8582233622406 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1546.2932117644223,
            "unit": "ns/iter",
            "extra": "iterations: 451232\ncpu: 1544.8837848379508 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 64.85133678534439,
            "unit": "ns/iter",
            "extra": "iterations: 10150959\ncpu: 64.79860671292248 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2062.1061703671235,
            "unit": "ns/iter",
            "extra": "iterations: 340060\ncpu: 2060.5481385637854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 83.82972689383382,
            "unit": "ns/iter",
            "extra": "iterations: 8332738\ncpu: 83.77426483347952 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 79.98888720073445,
            "unit": "ns/iter",
            "extra": "iterations: 8746939\ncpu: 79.93402034700367 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 204.71188683944138,
            "unit": "ns/iter",
            "extra": "iterations: 3429759\ncpu: 204.184608889429 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 856.9797472866663,
            "unit": "ns/iter",
            "extra": "iterations: 828540\ncpu: 856.5005914017408 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 134.70052987347526,
            "unit": "ns/iter",
            "extra": "iterations: 5216601\ncpu: 134.59127888063514 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 368.6595800504069,
            "unit": "ns/iter",
            "extra": "iterations: 1902525\ncpu: 368.44561832301713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1122.879297283456,
            "unit": "ns/iter",
            "extra": "iterations: 623597\ncpu: 1122.1045001820078 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729872179095,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3739682912.826538,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3739143000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 533.1009717713703,
            "unit": "ns/iter",
            "extra": "iterations: 1331761\ncpu: 521.7437663364515 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 805.0278756157475,
            "unit": "ns/iter",
            "extra": "iterations: 879695\ncpu: 804.9255707944243 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 113.55566157758861,
            "unit": "ns/iter",
            "extra": "iterations: 6312562\ncpu: 113.55151838508665 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 85.35739616155703,
            "unit": "ns/iter",
            "extra": "iterations: 8279712\ncpu: 85.35707522194005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1919.8384674371177,
            "unit": "ns/iter",
            "extra": "iterations: 371014\ncpu: 1919.7334871460348 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.044420031257605,
            "unit": "ns/iter",
            "extra": "iterations: 28175023\ncpu: 24.04335215626976 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1460.6835769253187,
            "unit": "ns/iter",
            "extra": "iterations: 491628\ncpu: 1460.3358637018248 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1252.780423111843,
            "unit": "ns/iter",
            "extra": "iterations: 558682\ncpu: 1252.6177682474126 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1486.0128180660595,
            "unit": "ns/iter",
            "extra": "iterations: 455231\ncpu: 1485.2503454290218 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 65.52210748562736,
            "unit": "ns/iter",
            "extra": "iterations: 10655625\ncpu: 65.51075136371631 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1929.8863813770897,
            "unit": "ns/iter",
            "extra": "iterations: 343996\ncpu: 1929.8509284991708 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.20419061535986,
            "unit": "ns/iter",
            "extra": "iterations: 9010401\ncpu: 78.17598794992588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 78.23285010422707,
            "unit": "ns/iter",
            "extra": "iterations: 9371444\ncpu: 78.20769136538607 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 201.20938485239583,
            "unit": "ns/iter",
            "extra": "iterations: 3422832\ncpu: 201.1828217102102 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 801.8918692390804,
            "unit": "ns/iter",
            "extra": "iterations: 823888\ncpu: 801.7922338958689 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 127.24457930147787,
            "unit": "ns/iter",
            "extra": "iterations: 5472555\ncpu: 127.23819130186868 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 350.3311076983955,
            "unit": "ns/iter",
            "extra": "iterations: 2026706\ncpu: 350.32362858747166 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1054.5203882955677,
            "unit": "ns/iter",
            "extra": "iterations: 651375\ncpu: 1054.3880253310363 ns\nthreads: 1"
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
        "date": 1729883296315,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4122435092.9260254,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4120429000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 615.3813911758183,
            "unit": "ns/iter",
            "extra": "iterations: 1327065\ncpu: 608.6695075222385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 882.0226292914431,
            "unit": "ns/iter",
            "extra": "iterations: 719528\ncpu: 881.7863933022765 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 123.41268007350104,
            "unit": "ns/iter",
            "extra": "iterations: 5733851\ncpu: 123.38130167665669 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 84.51112568862781,
            "unit": "ns/iter",
            "extra": "iterations: 7352555\ncpu: 84.50463818359724 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1948.9742696251942,
            "unit": "ns/iter",
            "extra": "iterations: 348965\ncpu: 1948.3415242216306 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 27.784588204560933,
            "unit": "ns/iter",
            "extra": "iterations: 26493575\ncpu: 27.772960047860696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1547.833100407314,
            "unit": "ns/iter",
            "extra": "iterations: 405308\ncpu: 1546.8384537191475 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1236.8708418070578,
            "unit": "ns/iter",
            "extra": "iterations: 577534\ncpu: 1236.7358458549625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1475.1855791512546,
            "unit": "ns/iter",
            "extra": "iterations: 477786\ncpu: 1475.041127199205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 62.021481840376964,
            "unit": "ns/iter",
            "extra": "iterations: 11368435\ncpu: 62.004136893072854 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1955.233447861718,
            "unit": "ns/iter",
            "extra": "iterations: 353539\ncpu: 1954.7631237289168 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 79.01674042459351,
            "unit": "ns/iter",
            "extra": "iterations: 8723176\ncpu: 78.99473769645371 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 76.44366242676475,
            "unit": "ns/iter",
            "extra": "iterations: 9347042\ncpu: 76.43230874537633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 203.82937077776992,
            "unit": "ns/iter",
            "extra": "iterations: 3487098\ncpu: 203.0834808772226 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 792.3754615313655,
            "unit": "ns/iter",
            "extra": "iterations: 898738\ncpu: 792.3566156098883 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 131.26790829965552,
            "unit": "ns/iter",
            "extra": "iterations: 5264385\ncpu: 131.24553010465584 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 385.5218102803919,
            "unit": "ns/iter",
            "extra": "iterations: 1753270\ncpu: 380.6949300450013 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1092.3171961700657,
            "unit": "ns/iter",
            "extra": "iterations: 611738\ncpu: 1084.1781939326938 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1729904680486,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3896411895.751953,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3895437000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 511.08364231219605,
            "unit": "ns/iter",
            "extra": "iterations: 1388393\ncpu: 510.9360245982228 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 816.2920271990516,
            "unit": "ns/iter",
            "extra": "iterations: 860120\ncpu: 816.2070408780177 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 113.27682459833454,
            "unit": "ns/iter",
            "extra": "iterations: 6192389\ncpu: 113.26969284390873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 79.59836145052131,
            "unit": "ns/iter",
            "extra": "iterations: 8700732\ncpu: 79.59560184131625 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1916.7730349250955,
            "unit": "ns/iter",
            "extra": "iterations: 359004\ncpu: 1916.627669886691 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.959153865553965,
            "unit": "ns/iter",
            "extra": "iterations: 27960073\ncpu: 24.934627316602512 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1453.469158165997,
            "unit": "ns/iter",
            "extra": "iterations: 480707\ncpu: 1452.745643396077 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1213.9098727217722,
            "unit": "ns/iter",
            "extra": "iterations: 576065\ncpu: 1213.6738041714061 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1514.3115177169095,
            "unit": "ns/iter",
            "extra": "iterations: 459957\ncpu: 1514.3024239222373 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 62.181229171201664,
            "unit": "ns/iter",
            "extra": "iterations: 11212917\ncpu: 62.17160084213588 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2196.920321216606,
            "unit": "ns/iter",
            "extra": "iterations: 320114\ncpu: 2196.6830566610647 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 81.1612975896377,
            "unit": "ns/iter",
            "extra": "iterations: 8964360\ncpu: 81.15861031908577 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 77.49365884201552,
            "unit": "ns/iter",
            "extra": "iterations: 8850788\ncpu: 77.47626539015496 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 214.85197431310235,
            "unit": "ns/iter",
            "extra": "iterations: 3472773\ncpu: 214.83321829558005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 792.922806445581,
            "unit": "ns/iter",
            "extra": "iterations: 879364\ncpu: 792.8229948007873 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 133.83628257880358,
            "unit": "ns/iter",
            "extra": "iterations: 5438414\ncpu: 133.42970947044506 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 361.4629553080775,
            "unit": "ns/iter",
            "extra": "iterations: 1875600\ncpu: 361.4635316698637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1173.8236972976183,
            "unit": "ns/iter",
            "extra": "iterations: 569972\ncpu: 1173.8085379632691 ns\nthreads: 1"
          }
        ]
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
        "date": 1730121132623,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4410489797.592163,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4366879000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 539.348302543287,
            "unit": "ns/iter",
            "extra": "iterations: 1313025\ncpu: 538.8983454237355 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 854.7777785984539,
            "unit": "ns/iter",
            "extra": "iterations: 809099\ncpu: 854.1748290382269 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 119.4122638651885,
            "unit": "ns/iter",
            "extra": "iterations: 5843169\ncpu: 119.3422610230851 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 83.51418288382543,
            "unit": "ns/iter",
            "extra": "iterations: 8347444\ncpu: 83.46626823731876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 2045.7687743864042,
            "unit": "ns/iter",
            "extra": "iterations: 339840\ncpu: 2031.856167608289 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.89536162274176,
            "unit": "ns/iter",
            "extra": "iterations: 27289491\ncpu: 25.87329312957875 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1527.8440941169056,
            "unit": "ns/iter",
            "extra": "iterations: 446340\ncpu: 1527.071290944126 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1309.9790077151386,
            "unit": "ns/iter",
            "extra": "iterations: 549028\ncpu: 1309.0060980496444 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1534.0676950457087,
            "unit": "ns/iter",
            "extra": "iterations: 448893\ncpu: 1533.205017676819 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 64.43934603896584,
            "unit": "ns/iter",
            "extra": "iterations: 11009578\ncpu: 64.40519336890125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2055.6235423356757,
            "unit": "ns/iter",
            "extra": "iterations: 322254\ncpu: 2054.4198054950416 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 86.85108442266078,
            "unit": "ns/iter",
            "extra": "iterations: 8461566\ncpu: 86.77329941053459 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 91.82260135658079,
            "unit": "ns/iter",
            "extra": "iterations: 9170105\ncpu: 90.42001154839548 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 223.64633505017554,
            "unit": "ns/iter",
            "extra": "iterations: 3169630\ncpu: 223.48160510848265 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 859.0710009759724,
            "unit": "ns/iter",
            "extra": "iterations: 835711\ncpu: 858.5085035377028 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 134.8679190079594,
            "unit": "ns/iter",
            "extra": "iterations: 5352623\ncpu: 134.74010779387953 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 360.13572298307434,
            "unit": "ns/iter",
            "extra": "iterations: 1933841\ncpu: 359.94582801791876 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1112.761209410412,
            "unit": "ns/iter",
            "extra": "iterations: 615298\ncpu: 1112.1635370178385 ns\nthreads: 1"
          }
        ]
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
        "date": 1730121217177,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3661417007.446289,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3661256000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 518.7389850616455,
            "unit": "ns/iter",
            "extra": "iterations: 1000000\ncpu: 518.6800000000007 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 806.4289798945523,
            "unit": "ns/iter",
            "extra": "iterations: 880415\ncpu: 805.5530630441319 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 112.50691131980221,
            "unit": "ns/iter",
            "extra": "iterations: 6335931\ncpu: 112.5058022254346 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.60579099259134,
            "unit": "ns/iter",
            "extra": "iterations: 9024456\ncpu: 77.60301562775653 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1869.3708354866858,
            "unit": "ns/iter",
            "extra": "iterations: 374197\ncpu: 1869.3255157042993 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.732924453907092,
            "unit": "ns/iter",
            "extra": "iterations: 29328954\ncpu: 23.729179022204477 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1389.4083162620084,
            "unit": "ns/iter",
            "extra": "iterations: 503651\ncpu: 1389.2358001870314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1178.083845546123,
            "unit": "ns/iter",
            "extra": "iterations: 595304\ncpu: 1177.9662155806104 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1443.0916745336121,
            "unit": "ns/iter",
            "extra": "iterations: 484543\ncpu: 1443.0628447836402 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.60199841794388,
            "unit": "ns/iter",
            "extra": "iterations: 11539539\ncpu: 60.60086109159127 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1925.434185077832,
            "unit": "ns/iter",
            "extra": "iterations: 362488\ncpu: 1925.0871752995995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.71799348610183,
            "unit": "ns/iter",
            "extra": "iterations: 9038089\ncpu: 77.7128882001495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.62512428874282,
            "unit": "ns/iter",
            "extra": "iterations: 9367932\ncpu: 74.62020433111604 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 196.51562600173426,
            "unit": "ns/iter",
            "extra": "iterations: 3555845\ncpu: 196.4604756394058 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 797.467570807068,
            "unit": "ns/iter",
            "extra": "iterations: 883872\ncpu: 797.4310759929018 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.17043200192109,
            "unit": "ns/iter",
            "extra": "iterations: 5503534\ncpu: 125.16775584560754 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 346.9255703358715,
            "unit": "ns/iter",
            "extra": "iterations: 2024619\ncpu: 346.8731647781636 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1055.7560191072128,
            "unit": "ns/iter",
            "extra": "iterations: 664193\ncpu: 1054.0219484396812 ns\nthreads: 1"
          }
        ]
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
        "date": 1730123780458,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3661230087.2802734,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3656965999.9999995 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 499.21976129762663,
            "unit": "ns/iter",
            "extra": "iterations: 1418351\ncpu: 498.9251602741495 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 800.4285398515386,
            "unit": "ns/iter",
            "extra": "iterations: 844554\ncpu: 799.8837256113874 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 110.64551482091352,
            "unit": "ns/iter",
            "extra": "iterations: 6316435\ncpu: 110.58928018732084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.78422204575658,
            "unit": "ns/iter",
            "extra": "iterations: 8973324\ncpu: 77.74476882813985 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1876.9057837049195,
            "unit": "ns/iter",
            "extra": "iterations: 375247\ncpu: 1874.8664213171544 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.922476284092596,
            "unit": "ns/iter",
            "extra": "iterations: 29460164\ncpu: 23.908624541261833 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1383.2660908559933,
            "unit": "ns/iter",
            "extra": "iterations: 506718\ncpu: 1382.125758311329 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1175.1659655314572,
            "unit": "ns/iter",
            "extra": "iterations: 596394\ncpu: 1174.5406560092842 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1440.4553653454263,
            "unit": "ns/iter",
            "extra": "iterations: 486385\ncpu: 1439.668164108681 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.64490899741042,
            "unit": "ns/iter",
            "extra": "iterations: 11538018\ncpu: 60.602609564311706 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1917.274619013628,
            "unit": "ns/iter",
            "extra": "iterations: 363297\ncpu: 1915.8567232870093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.9535353167808,
            "unit": "ns/iter",
            "extra": "iterations: 9001479\ncpu: 77.90853036484343 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 74.55090002795903,
            "unit": "ns/iter",
            "extra": "iterations: 9394586\ncpu: 74.51312915758098 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 196.54795880614034,
            "unit": "ns/iter",
            "extra": "iterations: 3560692\ncpu: 196.44692660864936 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 796.187890984572,
            "unit": "ns/iter",
            "extra": "iterations: 892106\ncpu: 795.7709061479231 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.39506511555513,
            "unit": "ns/iter",
            "extra": "iterations: 5601344\ncpu: 125.32956376183908 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 346.78752294179003,
            "unit": "ns/iter",
            "extra": "iterations: 2024052\ncpu: 346.3507854541294 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1132.004658338673,
            "unit": "ns/iter",
            "extra": "iterations: 617502\ncpu: 1122.0676208336133 ns\nthreads: 1"
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
        "date": 1730142512388,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3733227014.541626,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3676627000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 498.343123846865,
            "unit": "ns/iter",
            "extra": "iterations: 1414461\ncpu: 497.42764204880837 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 846.2335313992904,
            "unit": "ns/iter",
            "extra": "iterations: 818455\ncpu: 839.7101856546776 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 110.79198487089597,
            "unit": "ns/iter",
            "extra": "iterations: 6316150\ncpu: 110.72552108483798 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.6990833433519,
            "unit": "ns/iter",
            "extra": "iterations: 9010285\ncpu: 77.65381450198304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1864.4702976781196,
            "unit": "ns/iter",
            "extra": "iterations: 369780\ncpu: 1863.54859646276 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.808645475505923,
            "unit": "ns/iter",
            "extra": "iterations: 29364756\ncpu: 23.79130955489638 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1387.4625713687221,
            "unit": "ns/iter",
            "extra": "iterations: 506795\ncpu: 1386.6494341893674 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1177.2215391409597,
            "unit": "ns/iter",
            "extra": "iterations: 594950\ncpu: 1175.927388856205 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1441.6531143054822,
            "unit": "ns/iter",
            "extra": "iterations: 484064\ncpu: 1440.8322040060814 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.68147021119598,
            "unit": "ns/iter",
            "extra": "iterations: 11580010\ncpu: 60.6492567795711 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1945.9203058517915,
            "unit": "ns/iter",
            "extra": "iterations: 362854\ncpu: 1932.1848456955174 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 80.74781891788831,
            "unit": "ns/iter",
            "extra": "iterations: 8702463\ncpu: 79.08703547489951 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 79.06829812200834,
            "unit": "ns/iter",
            "extra": "iterations: 9197215\ncpu: 76.56480793370606 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 205.0607476582118,
            "unit": "ns/iter",
            "extra": "iterations: 3483246\ncpu: 200.48684474194465 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 794.4335731753723,
            "unit": "ns/iter",
            "extra": "iterations: 889216\ncpu: 793.8476140780213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 126.83383121437737,
            "unit": "ns/iter",
            "extra": "iterations: 5561647\ncpu: 126.47350685866965 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 356.0386261515019,
            "unit": "ns/iter",
            "extra": "iterations: 2013722\ncpu: 349.17878436050074 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1120.2177541876858,
            "unit": "ns/iter",
            "extra": "iterations: 650733\ncpu: 1081.7908420196902 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730150823238,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3755146980.2856445,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3747021000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 496.4121192424372,
            "unit": "ns/iter",
            "extra": "iterations: 1410235\ncpu: 496.14355054299443 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 794.6742163166219,
            "unit": "ns/iter",
            "extra": "iterations: 879773\ncpu: 794.245788402236 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 110.94609812735061,
            "unit": "ns/iter",
            "extra": "iterations: 6333065\ncpu: 110.87269750113093 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 79.20360652260094,
            "unit": "ns/iter",
            "extra": "iterations: 9012721\ncpu: 79.14823947174239 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1882.6552951491037,
            "unit": "ns/iter",
            "extra": "iterations: 336734\ncpu: 1881.49696793314 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.81723440577937,
            "unit": "ns/iter",
            "extra": "iterations: 29404969\ncpu: 23.804752183210933 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1400.85314864394,
            "unit": "ns/iter",
            "extra": "iterations: 507066\ncpu: 1400.076124212629 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1175.9311374798926,
            "unit": "ns/iter",
            "extra": "iterations: 593341\ncpu: 1175.0679626049791 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1444.1516662545826,
            "unit": "ns/iter",
            "extra": "iterations: 485168\ncpu: 1443.0465323351877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 60.719777659049896,
            "unit": "ns/iter",
            "extra": "iterations: 11538779\ncpu: 60.59869939445065 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1923.714577440524,
            "unit": "ns/iter",
            "extra": "iterations: 364578\ncpu: 1922.3979505071597 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.86199021637417,
            "unit": "ns/iter",
            "extra": "iterations: 8950377\ncpu: 82.81684670936225 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 75.9676170028358,
            "unit": "ns/iter",
            "extra": "iterations: 9269068\ncpu: 75.91842027699022 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 196.43469974402444,
            "unit": "ns/iter",
            "extra": "iterations: 3519109\ncpu: 196.33123043361257 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 796.4434501198518,
            "unit": "ns/iter",
            "extra": "iterations: 878679\ncpu: 795.3439196794304 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 127.48587261320768,
            "unit": "ns/iter",
            "extra": "iterations: 5481383\ncpu: 127.36949780739623 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 360.5453119765978,
            "unit": "ns/iter",
            "extra": "iterations: 2026536\ncpu: 356.13529688098424 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1131.7812271912237,
            "unit": "ns/iter",
            "extra": "iterations: 665830\ncpu: 1124.8036285538342 ns\nthreads: 1"
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
        "date": 1730229027887,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 4360606908.798218,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 4302983000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 537.3977326383033,
            "unit": "ns/iter",
            "extra": "iterations: 1278913\ncpu: 537.0826631678626 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 871.6629481445277,
            "unit": "ns/iter",
            "extra": "iterations: 803711\ncpu: 870.9561023800841 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 118.21408118119744,
            "unit": "ns/iter",
            "extra": "iterations: 5731269\ncpu: 118.14259634297385 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 81.29557578216864,
            "unit": "ns/iter",
            "extra": "iterations: 8538668\ncpu: 81.22508100795099 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1957.0091744422461,
            "unit": "ns/iter",
            "extra": "iterations: 359770\ncpu: 1955.6077493954467 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 24.783288485119638,
            "unit": "ns/iter",
            "extra": "iterations: 28259079\ncpu: 24.762590458096692 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1479.3586194237025,
            "unit": "ns/iter",
            "extra": "iterations: 474776\ncpu: 1478.2760712420181 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1241.1110361261983,
            "unit": "ns/iter",
            "extra": "iterations: 553977\ncpu: 1240.1706208019457 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1527.4019642477197,
            "unit": "ns/iter",
            "extra": "iterations: 450990\ncpu: 1526.534956429189 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 64.36780456663625,
            "unit": "ns/iter",
            "extra": "iterations: 10949305\ncpu: 64.3299277899374 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 2024.7706610942214,
            "unit": "ns/iter",
            "extra": "iterations: 344836\ncpu: 2023.054437471728 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 82.47029225257356,
            "unit": "ns/iter",
            "extra": "iterations: 8531799\ncpu: 82.41345113732729 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 78.895972181362,
            "unit": "ns/iter",
            "extra": "iterations: 8938376\ncpu: 78.83165801035877 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 206.6723830287402,
            "unit": "ns/iter",
            "extra": "iterations: 3417785\ncpu: 206.3447525224676 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 845.7015859982142,
            "unit": "ns/iter",
            "extra": "iterations: 815794\ncpu: 839.8039210879288 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 133.51353940505274,
            "unit": "ns/iter",
            "extra": "iterations: 5303754\ncpu: 133.35347001388106 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 382.03734852541106,
            "unit": "ns/iter",
            "extra": "iterations: 1923320\ncpu: 381.72846952145125 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1144.5646900987222,
            "unit": "ns/iter",
            "extra": "iterations: 620920\ncpu: 1143.419442118148 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730244385987,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 427563905.7159424,
            "unit": "ns/iter",
            "extra": "iterations: 2\ncpu: 427174000.0000002 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 488.5986721393524,
            "unit": "ns/iter",
            "extra": "iterations: 1440098\ncpu: 488.3126009479908 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 791.8915478123552,
            "unit": "ns/iter",
            "extra": "iterations: 880237\ncpu: 791.4709333963461 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 111.01083458443875,
            "unit": "ns/iter",
            "extra": "iterations: 6179651\ncpu: 110.93765651167033 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.16611172931859,
            "unit": "ns/iter",
            "extra": "iterations: 8742241\ncpu: 78.11887135117867 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1873.5040072769116,
            "unit": "ns/iter",
            "extra": "iterations: 361221\ncpu: 1872.327467118468 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.40252021881281,
            "unit": "ns/iter",
            "extra": "iterations: 29301208\ncpu: 23.38637369490025 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1396.2601108540252,
            "unit": "ns/iter",
            "extra": "iterations: 504585\ncpu: 1395.4299077459684 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1173.0801174296637,
            "unit": "ns/iter",
            "extra": "iterations: 598204\ncpu: 1172.3425453524212 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1445.5332528457393,
            "unit": "ns/iter",
            "extra": "iterations: 484034\ncpu: 1444.7869364548756 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 59.693039637389106,
            "unit": "ns/iter",
            "extra": "iterations: 11730795\ncpu: 59.659213207629975 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1918.6300331616198,
            "unit": "ns/iter",
            "extra": "iterations: 366671\ncpu: 1917.386430887633 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.06659248291872,
            "unit": "ns/iter",
            "extra": "iterations: 8984265\ncpu: 77.99146619116894 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 73.69016404578089,
            "unit": "ns/iter",
            "extra": "iterations: 9508027\ncpu: 73.6430386661713 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.41213096535145,
            "unit": "ns/iter",
            "extra": "iterations: 3691535\ncpu: 190.31351456778805 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 794.8469052875083,
            "unit": "ns/iter",
            "extra": "iterations: 899465\ncpu: 794.4466988709958 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.28971988368856,
            "unit": "ns/iter",
            "extra": "iterations: 5624794\ncpu: 124.22303821259914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 368.630714135664,
            "unit": "ns/iter",
            "extra": "iterations: 2046305\ncpu: 365.2217044868673 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1059.8893481386312,
            "unit": "ns/iter",
            "extra": "iterations: 594631\ncpu: 1056.598125560226 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730302994298,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3785195112.2283936,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3782743000 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 517.6476017053958,
            "unit": "ns/iter",
            "extra": "iterations: 1340329\ncpu: 517.3050795737464 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 797.3049969525224,
            "unit": "ns/iter",
            "extra": "iterations: 883258\ncpu: 796.6777544047154 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 112.28695180053656,
            "unit": "ns/iter",
            "extra": "iterations: 6312790\ncpu: 112.20997372001914 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 78.35178471129258,
            "unit": "ns/iter",
            "extra": "iterations: 8594546\ncpu: 78.2932571423786 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1964.74669580221,
            "unit": "ns/iter",
            "extra": "iterations: 349619\ncpu: 1963.7004853855224 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 25.80284247843391,
            "unit": "ns/iter",
            "extra": "iterations: 28828413\ncpu: 25.78539443014084 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1569.1324180639106,
            "unit": "ns/iter",
            "extra": "iterations: 436259\ncpu: 1568.231257120198 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1283.4986971922544,
            "unit": "ns/iter",
            "extra": "iterations: 500136\ncpu: 1281.2954876273689 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1549.0834155346572,
            "unit": "ns/iter",
            "extra": "iterations: 456002\ncpu: 1547.850667321632 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 62.99823534886859,
            "unit": "ns/iter",
            "extra": "iterations: 10847668\ncpu: 62.96579135718393 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1945.0095824251857,
            "unit": "ns/iter",
            "extra": "iterations: 363576\ncpu: 1943.9566968116696 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 78.05344327716729,
            "unit": "ns/iter",
            "extra": "iterations: 8914586\ncpu: 78.0084459334399 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 75.16521489639692,
            "unit": "ns/iter",
            "extra": "iterations: 9343923\ncpu: 75.11288352868482 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 197.07127418433475,
            "unit": "ns/iter",
            "extra": "iterations: 3487654\ncpu: 196.95101635655323 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 802.7334299572002,
            "unit": "ns/iter",
            "extra": "iterations: 898484\ncpu: 799.9018346459196 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 125.88682708436941,
            "unit": "ns/iter",
            "extra": "iterations: 5568859\ncpu: 125.81679658256783 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 349.59912634171053,
            "unit": "ns/iter",
            "extra": "iterations: 2009058\ncpu: 349.4224656530545 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1100.7543403879752,
            "unit": "ns/iter",
            "extra": "iterations: 664030\ncpu: 1100.1792087706872 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "jv@jviotti.com",
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
        "date": 1730303808820,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Compiler_Draft6_AdaptiveCard",
            "value": 3611009120.941162,
            "unit": "ns/iter",
            "extra": "iterations: 1\ncpu: 3608901000.0000005 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Meta_1_No_Callback",
            "value": 488.3040293390006,
            "unit": "ns/iter",
            "extra": "iterations: 1423687\ncpu: 487.91904400335204 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Required_Properties",
            "value": 798.7269207210276,
            "unit": "ns/iter",
            "extra": "iterations: 876655\ncpu: 798.2615738232255 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Many_Optional_Properties_Minimal_Match",
            "value": 111.37876666264765,
            "unit": "ns/iter",
            "extra": "iterations: 6149251\ncpu: 111.30932856700744 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Few_Optional_Properties_Minimal_Match",
            "value": 77.4506537963445,
            "unit": "ns/iter",
            "extra": "iterations: 9053285\ncpu: 77.41112756308898 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Items_Schema",
            "value": 1866.4297656478168,
            "unit": "ns/iter",
            "extra": "iterations: 374500\ncpu: 1865.4953271028069 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Object",
            "value": 23.80999073176559,
            "unit": "ns/iter",
            "extra": "iterations: 29437987\ncpu: 23.79751713321971 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Optional",
            "value": 1381.181493059243,
            "unit": "ns/iter",
            "extra": "iterations: 505696\ncpu: 1380.4637568816054 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Closed",
            "value": 1243.5219653818447,
            "unit": "ns/iter",
            "extra": "iterations: 597346\ncpu: 1212.5635728706654 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Properties_Triad_Required",
            "value": 1473.7757031963129,
            "unit": "ns/iter",
            "extra": "iterations: 478813\ncpu: 1472.2929410855627 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Non_Recursive_Ref",
            "value": 59.71117091084874,
            "unit": "ns/iter",
            "extra": "iterations: 11740633\ncpu: 59.66535194482291 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Pattern_Properties_True",
            "value": 1917.5498838099331,
            "unit": "ns/iter",
            "extra": "iterations: 362679\ncpu: 1916.554308355325 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Ref_To_Single_Property",
            "value": 77.74248857313715,
            "unit": "ns/iter",
            "extra": "iterations: 9038673\ncpu: 77.70023320901173 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Additional_Properties_Type",
            "value": 73.84741079329595,
            "unit": "ns/iter",
            "extra": "iterations: 9460994\ncpu: 73.80799522756315 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft4_Nested_Oneof",
            "value": 190.33748603675474,
            "unit": "ns/iter",
            "extra": "iterations: 3683280\ncpu: 190.23804869572902 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft6_Property_Names",
            "value": 810.145438487664,
            "unit": "ns/iter",
            "extra": "iterations: 877556\ncpu: 809.5449179311637 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_Draft7_If_Then_Else",
            "value": 124.74370862414008,
            "unit": "ns/iter",
            "extra": "iterations: 5604394\ncpu: 124.65968666728213 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2019_09_Unevaluated_Properties",
            "value": 339.56313371731164,
            "unit": "ns/iter",
            "extra": "iterations: 2065469\ncpu: 338.98741641728725 ns\nthreads: 1"
          },
          {
            "name": "Evaluator_2020_12_Dynamic_Ref",
            "value": 1048.6969692397317,
            "unit": "ns/iter",
            "extra": "iterations: 667862\ncpu: 1048.1147302885906 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}