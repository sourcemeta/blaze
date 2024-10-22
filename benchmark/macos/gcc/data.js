window.BENCHMARK_DATA = {
  "lastUpdate": 1729624523826,
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
      }
    ]
  }
}