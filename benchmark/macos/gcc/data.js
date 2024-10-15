window.BENCHMARK_DATA = {
  "lastUpdate": 1729024822927,
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
      }
    ]
  }
}