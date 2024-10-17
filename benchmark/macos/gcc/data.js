window.BENCHMARK_DATA = {
  "lastUpdate": 1729208787836,
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
      }
    ]
  }
}