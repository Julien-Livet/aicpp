| Task     |   Train cost |   Test cost | Program                              |
|:---------|-------------:|------------:|:-------------------------------------|
| 00576224 |     28.9488  |    18.5552  | upscale(I, THREE)                    |
| 007bbfb7 |     88.5749  |    29.9207  | upscale(I, THREE)                    |
| 009d5c81 |     39.9222  |    20.8574  | switch(I, EIGHT, THREE)              |
| 00d62c1b |     54.0189  |    23.0608  | I                                    |
| 00dbd492 |    103.779   |    43.1152  | I                                    |
| 017c7c7b |    146.557   |    48.1857  | switch(I, THREE, ONE)                |
| 025d127b |     49.244   |    14.0118  | I                                    |
| 03560426 |     48.5583  |    30.3992  | hmirror(I)                           |
| 045e512c |     52.275   |    19.3075  | I                                    |
| 0520fde7 |      8.08846 |     3.02733 | crop(I, ORIGIN, THREE_BY_THREE)      |
| 05269061 |     49.2063  |    14.6019  | switch(I, FOUR, ZERO)                |
| 05a7bcf2 |    287.787   |   113.309   | replace(I, ZERO, ONE)                |
| 05f2a901 |     25.2275  |     7.10456 | I                                    |
| 0607ce86 |     57.6678  |    26.4939  | I                                    |
| 0692e18c |     69.6173  |    12.1975  | upscale(I, THREE)                    |
| 06df4c85 |     69.3232  |    25.0332  | I                                    |
| 070dd51e |     54.8666  |    29.3991  | I                                    |
| 08ed6ac7 |     29.9643  |    14.9127  | I                                    |
| 09629e4f |    107.97    |    26.8825  | switch(I, ONE, EIGHT)                |
| 0962bcdd |     54.7902  |    18.3364  | I                                    |
| 09c534e7 |     42.2642  |    63.478   | I                                    |
| 0a1d4ef5 |     50.2024  |    27.1085  | crop(I, UNITY, THREE_BY_THREE)       |
| 0a2355a6 |     61.1818  |    16.102   | switch(I, FOUR, EIGHT)               |
| 0a938d79 |    105.674   |    24.7239  | switch(I, ONE, ZERO)                 |
| 0b148d64 |    536.031   |    60.3865  | downscale(I, FOUR)                   |
| 0b17323b |      6.42222 |     3.03732 | I                                    |
| 0bb8deee |    322.635   |   126.643   | downscale(I, SIX)                    |
| 0becf7df |     46.2931  |     8.10401 | I                                    |
| 0c786b71 |     53.1558  |    12.7489  | upscale(I, TWO)                      |
| 0c9aba6e |     95.011   |    22.9311  | tophalf(I)                           |
| 0ca9ddb6 |     55.6623  |    18.2162  | I                                    |
| 0d3d703e |     38.5967  |     8.34847 | I                                    |
| 0d87d2a6 |     21.3063  |    13.2939  | I                                    |
| 0e206a2e |     67.7321  |    29.9546  | switch(I, TWO, EIGHT)                |
| 0e671a1a |     93.7102  |    23.0371  | I                                    |
| 0f63c0b9 |    202.616   |    44.3144  | switch(I, ONE, ZERO)                 |
| 103eff5b |     17.1255  |    12.1154  | replace(I, EIGHT, TWO)               |
| 10fcaaa3 |    137.068   |    48.603   | upscale(I, TWO)                      |
| 11852cab |     15.6785  |     6.9582  | I                                    |
| 1190bc91 |     91.8211  |    38.9907  | switch(I, ZERO, ONE)                 |
| 1190e5a7 |    115.802   |    49.5382  | downscale(I, SIX)                    |
| 11dc524f |     32.383   |    10.6422  | replace(I, TWO, EIGHT)               |
| 11e1fe23 |     17.6665  |    13.4029  | I                                    |
| 12422b43 |     87.5556  |    17.5933  | I                                    |
| 12997ef3 |    332.599   |   288.795   | compress(I)                          |
| 12eac192 |     37.1324  |    10.3906  | switch(I, TWO, ONE)                  |
| 13713586 |    127.94    |    35.1483  | switch(I, TWO, ZERO)                 |
| 137eaa0f |     41.1158  |    19.1097  | crop(I, TWO_BY_TWO, THREE_BY_THREE)  |
| 137f0df0 |     24.7266  |     8.04331 | switch(I, ONE, ZERO)                 |
| 13f06aa5 |     45.1952  |    22.4036  | I                                    |
| 140c817e |    154.937   |    67.3064  | switch(I, EIGHT, ONE)                |
| 14754a24 |     37.0596  |    11.6605  | I                                    |
| 1478ab18 |     11.2196  |     4.25    | I                                    |
| 14b8e18c |     48.6043  |    28.6043  | I                                    |
| 150deff5 |     39.3895  |    14.9697  | I                                    |
| 15113be4 |     41.4519  |    23.2663  | I                                    |
| 15660dd6 |    871.148   |   572.945   | downscale(I, TWO)                    |
| 15663ba9 |     38.1676  |     5.79019 | I                                    |
| 15696249 |    456.732   |   114.392   | vupscale(I, THREE)                   |
| 17829a00 |     36.7213  |    32.4829  | I                                    |
| 178fcbfb |     39.4695  |    16.4843  | I                                    |
| 17b80ad2 |     92.497   |    32.5914  | switch(I, ONE, ZERO)                 |
| 17b866bd |     57.422   |    95.9928  | switch(I, ZERO, ONE)                 |
| 17cae0c1 |     56.2302  |    19.0831  | switch(I, ZERO, FOUR)                |
| 18286ef8 |     19.2904  |     6.41143 | I                                    |
| 182e5d0f |     36.7924  |    12.0612  | I                                    |
| 18419cfa |     16.5375  |     8.26956 | I                                    |
| 18447a8d |     80.2789  |    34.5401  | vmirror(I)                           |
| 184a9768 |    108.568   |    86.6876  | replace(I, EIGHT, ZERO)              |
| 195ba7dc |     93.9012  |    26.2676  | righthalf(I)                         |
| 1990f7a8 |    317.659   |   107.22    | crop(I, TWO_BY_ZERO, UP)             |
| 19bb5feb |     21.7089  |     7.40312 | downscale(I, TEN)                    |
| 1a07d186 |     36.9182  |    19.8507  | I                                    |
| 1a244afd |      7.68336 |     3.51098 | switch(I, SIX, NINE)                 |
| 1a2e2828 |     28       |     9       | crop(I, ZERO_BY_TWO, UNITY)          |
| 1a6449f1 |    320.062   |   200.695   | downscale(I, FIVE)                   |
| 1acc24af |     35.8759  |    10.4756  | I                                    |
| 1b2d62fb |    149.436   |    34.8674  | lefthalf(I)                          |
| 1b59e163 |     31.2449  |    17.1636  | switch(I, THREE, ONE)                |
| 1b60fb0c |     15.5348  |     6.88145 | dmirror(I)                           |
| 1b8318e3 |     57.9299  |    24.7895  | switch(I, SIX, NEG_ONE)              |
| 1be83260 |   1142.74    |  2348.16    | compress(I)                          |
| 1bfc4729 |     57.934   |    37.0078  | switch(I, ZERO, ONE)                 |
| 1c02dbbe |     56.4768  |    31.4378  | I                                    |
| 1c0d0a4b |     50.5171  |    24.5417  | switch(I, EIGHT, THREE)              |
| 1c56ad9f |     89.4265  |    42.1933  | I                                    |
| 1c786137 |    385.771   |   288.148   | downscale(I, FOUR)                   |
| 1caeab9d |     28.7562  |    12.5198  | rot180(I)                            |
| 1cf80156 |      0       |     0       | compress(I)                          |
| 1d0a4b61 |     74.3492  |    34.2164  | I                                    |
| 1d398264 |     93.8701  |    38.4428  | I                                    |
| 1d61978c |     31.3664  |     6.72774 | I                                    |
| 1da012fc |     37.0826  |    25.7594  | switch(I, ONE, EIGHT)                |
| 25ff71a9 |     13.7879  |     5.02042 | I                                    |
| 2dee498d |     72.2008  |    63.8418  | downscale(I, TWO)                    |
| 32597951 |     19.2998  |     5.68454 | I                                    |
| 3c9b0459 |      0       |     0       | rot180(I)                            |
| 4c4377d9 |     31.922   |     0       | vconcat(I, I)                        |
| 5582e5ca |     28.1247  |    11.0107  | switch(I, FIVE, FOUR)                |
| 5614dbcf |      5.22896 |     0       | downscale(I, THREE)                  |
| 5bd6f4ac |     41.2239  |    16.5496  | crop(I, ZERO_BY_TWO, THREE_BY_THREE) |
| 6150a2bd |      0       |     0       | rot180(I)                            |
| 67a3c6ac |      0       |     0       | vmirror(I)                           |
| 68b16354 |      0       |     0       | hmirror(I)                           |
| 6d0aefbc |     26.9247  |     0       | hconcat(I, I)                        |
| 6fa7a44f |     39.609   |    13.2606  | vconcat(I, I)                        |
| 74dd1130 |      0       |     0       | dmirror(I)                           |
| 8be77c9e |      6.19338 |     1.59986 | vconcat(I, I)                        |
| 90f3ed37 |     11.9866  |     3.22894 | I                                    |
| 9172f3a0 |      0       |     0       | upscale(I, THREE)                    |
| 9dfd6313 |      0       |     0       | dmirror(I)                           |
| a416b8f3 |      0       |     0       | hconcat(I, I)                        |
| b1948b0a |      0       |     0       | switch(I, TWO, SIX)                  |
| c59eb873 |      0       |     0       | upscale(I, TWO)                      |
| c8f0f002 |      8.2508  |     3.36176 | replace(I, SEVEN, FOUR)              |
| c909285e |    211.403   |    33.1436  | downscale(I, FOUR)                   |
| c9e6f938 |     34.5416  |    14.2222  | hconcat(I, I)                        |
| d10ecb37 |      0       |     0       | crop(I, ORIGIN, TWO_BY_TWO)          |
| d511f180 |     24.1299  |     8.37475 | I                                    |
| ed36ccf7 |      0       |     0       | rot270(I)                            |