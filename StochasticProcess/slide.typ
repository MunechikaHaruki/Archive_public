#import "@preview/slydst:0.1.4": *
#import "@preview/showybox:2.0.4": showybox
#set text(font: ("Hiragino Kaku Gothic ProN", "New Computer Modern"))
#show figure.caption: it => it.body
#show link: underline

#show: slides.with(
  title: "入門確率過程",
  subtitle: "1.2節 有限状態Markov連鎖",
  authors: ("棟近春樹",),
)

== 
状態が2種類より多い場合のMarkov連鎖について考察する。
各時刻はN個の状態$1,2,...,N$をとるとする


#showybox(title: "def N状態のMarkov連鎖",frame: (title-color:olive.lighten(10%)))[
  各時刻に取りうる状態の全体$S={1,2,...,N}$を#text(red)[状態空間]とよぶ
  
任意の時刻$n=1,2,...$と状態空間の値$, i_0,i_1,... in S$に対し、  
  
  #align(center)[
      $P(X_n=i_n | X_0=i_0,X_1=i_1,...,X_(n-1)=i_(n-1)) \
      =P(X_n=i_n|X_(n-1)=i_(n-1))$
  ]
  が成り立つようなの確率過程${X_n}_"n=0,1,2,.."$
]
#text(red)[N状態のMarkov連鎖]のように、「過去のことを忘れる」性質を#text(blue)[Markov性]という

#showybox(title: "def Markov連鎖の時刻nでのの分布",frame: (title-color:olive.lighten(10%)))[
   $0 <= p_i <= 1$かつ$sum_(i_in S)p_i=1 $を満たす$bold(p)=(p_1,p_2,..,p_N)$ を#text(red)[分布]という

   $p_i^((n)):=P(X_n=i)$とおき、$bold(p)^((n))=(p_i^((n)))_(i in S)$を#text(red)[Markov連鎖の時刻nでの分布]という
]

状態$i,j in S$に対し、$P(X_n=j|X_(n-1)=i)$はnによらず$p_(i j)$と仮定。
これはiからjへ推移する確率で推移確率とよぶ。行列
#align(center)[
  $P=(p_(i j))_(i,j in S)=mat(
    p_11,p_12,dots p_(1N);
    p_21,p_22,dots p_(2N);
    dots.v,dots.v,dots.down;
    p_(N 1),p_(N 2),dots p_(N N);
  )$
]
は推移確率行列とよぶ #h(2em) ($0<=p_(i j)<=1$かつ$sum_(j in S)p_(i j)=1$)

特に、$sum_(i in S)p_(i j)=1$を満たすとき、Pは#text(red)[二重確率行列]という


== Markov連鎖に関する確率計算
状態空間$S={1,2,dots,N}$,
初期分布$v=(v_i)_(i in S)$,推移確立行列$P=(p_(i j))_(i,j in S)$のマルコフ連鎖${X_n}$で成り立つ定理を述べる

#showybox(title: "Th 1.4",frame: (title-color:olive.lighten(10%)))[
  任意の時刻nと各時刻の状態$i_0,dots,i_n in S$に対し\
  $P(X_0=i_0,X_1=i_1,dots,X_(n-1)=i_(n-1))=v_(i_0)p_(i_0i_1)p_(i_1i_2) dots p_(i_(n-1)i_n)$
]
Pf.以下のような式変形を繰り返せば示せる

#align(center)[
  $
    P(X_0=i_0,X_1=i_1,X_2=i_2) \
    =^"条件付き確率" P(X_0=i_0,X_1=i_1)P(X_2=i_2|X_0=i_0,X_1=i_1) \
    =^"Markov性から" P(X_0=i_0,X_1=i_1)P(X_2=i_2|X_1=i_1) \
    =P(X_0=i_0,X_1=i_1)p_(1 2)
  $
]


==

#showybox(title: "Th 1.5",frame: (title-color:olive.lighten(10%)))[
  推移確率行列$P$のn乗を$P^n = (p_(i j)^((n)))_(i,j in S)$とすると、
  #align(center)[
    $P(X_0=i,X_n=j)=v_i p_(i j)^((n)) quad (forall i,j in S)$
  ]
]

この定理が意味するところ:\
初期分布$bold(p)^((0))$が$bold(v)$で与えられた時、$bold(p)^((n))=bold(p)^((n-1)) P=dots= bold(v) P^n$で計算できる

#align(center)[
  $
    mat(p_1^((n)),p_2^((n)),dots,p_N^((n)))=mat(p_1^((n-1)),p_2^((n-1)),dots,p_N^((n-1)))
mat(
    p_11,p_12,dots p_(1N);
    p_21,p_22,dots p_(2N);
    dots.v,dots.v,dots.down;
    p_(N 1),p_(N 2),dots p_(N N);
  )$
  
]

== 定常分布
状態空間$S={1,2,dots,N}$,推移確率行列$P=(p_(i j))_(i,j in S)$のMarkov連鎖${X_n}$で、
#align(center)[
  $bold(pi)P=bold(pi)$
]
が成り立つ分布$bold(pi)$を、#text(red)[定常分布]という。

この時、任意のnに対し、$bold(pi) P^n = bold(pi)$が成り立つ

#showybox(title:"Th1.6 定常分布と二重確率行列の関係",frame: (title-color:olive.lighten(10%)))[
  #text(red)[二重確率行列]:$sum_(i in S)p_(i j)=1$を満たす推移確率行列P

  状態空間が$S={1,2,dots,N}$であるMarkov連鎖が、S上の一様分布
  #align(center)[
    $(pi_1,pi_2,dots,pi_n)=(1/N,1/N,dots,1/N)$
  ]
  を定常分布にもつための必要十分条件は、推移確立行列$P=(p_(i　j))_(i,j in S)$が二重確率行列であること
]

Pf.S上の一様分布が定常分布であるとは、任意の$j in S$に対し、$sum_(i in S)(1/N)p_(i j)=(1/N)$が成り立つこと

これは$sum_(i in S)p_(i j)=1$,すなわち二重確率行列であることと同値

==

#showybox(title: "N頂点完全グラフ上の単純ランダムウォーク",frame: (title-color:olive.lighten(10%)))[
  $N >=3$,状態空間$S={1,2,dots,N}$とし、推移確率行列$P=(p_(i j))_(i,j in S)$が、
  #align(center)[
    $p_(i j)=cases(1/(N-1) quad (j eq.not i),0 quad (j=1))$
  ]
  で与えられるMarkov連鎖
]

現在の状態以外の(N-1)個の状態を等確率で選んで推移することを意味する

Pは対称行列なので二重確率行列となり、Th1.6から一様分布$mat(1/N,1/N,dots,1/N)$を定常分布としてもつ

== 可逆な定常分布

状態空間$S={1,2,dots,N}$上のMarkov連鎖の推移確率行列$P=(p_(i j))_(i j in S)$に対し、分布$bold(pi)=(pi_i)_(i in S)$が下式の#text(red)[詳細釣り合い条件]
#align(center)[
  $pi_i p_(i j)=pi_j p_(j i)$ $(forall i,j in S)$
]
を満たすとき、$bold(pi)$はPに対し#text(red)[可逆]という

#showybox(title:"Th1.7 可逆ならば定常分布",frame: (title-color:olive.lighten(10%)))[
  状態空間$S={1,2,dots,N}$上のMarkov連鎖の推移確率行列$P=(p_(i j))_(i,j in S) $について、分布$bold(pi)=(pi_i)_(i in S)$がPに対して可逆であるとき、$bold(pi)$はPに対する定常分布となる
]
Pf.任意の$j in S$に対し、\
$sum_(i in S)pi_i p_(i j)=^"釣り合い条件" sum_(i in S)pi_j p_(j i)=pi_j sum_(i in S)p_(j i)=^"推移確率行列の定義"  pi_j dot 1 = pi_j $

$sum_(i in S)pi_i p_(i j)=pi_j$定常分布の条件そのもの

#showybox(title:"Th1.8 ",frame: (title-color:olive.lighten(10%)))[
  二状態のMarkov連鎖においては、全ての定常分布が可逆
]

Pf.
p18より、推移確率行列$P=mat(1-a,a;b,1-b)$に対する定常分布は、$mat(b/(a+b),a/(a+b))$

$pi_1 p_(1 2)=pi_2 p_(2 1)$は自明


#showybox(title:"Th1.9 (Th1.6より強い定理)",frame: (title-color:olive.lighten(10%)))[
  推移確率行列Pが対称 \
  $arrow.l.r.double$Markov連鎖が一様分布を可逆な定常分布としてもつ
]
Pf.状態空間S上の一様分布が可逆な定常分布であるとは、\
$forall i,j in S (1/N p_(i j)=1/N p_(j i))$が成立すること。
これは$p_(i j)=p_(j i)$と同値


== 可逆な定常分布が容易にわかる場合
#showybox(title:"Th1.10 有限グラフG上の単純ランダムウォーク",frame: (title-color:olive.lighten(10%)))[
  有限グラフ$G=(V,E)$#h(1em) (V:頂点集合、E:辺集合)に対し、
  #align(center)[
    $p_(i j)=cases(1/deg(i) quad (j tilde i),0 quad (j tilde.not i))$
  ]
  で推移確率行列が与えられる確率過程を#text(red)[単純ランダムウォーク]という
  (deg:次数　ノードに繋がる辺の数)(隣接するノードに等確率で遷移)
  #line(length: 100%)

  総次数$Delta :=sum_(i in V)deg(i)$とおいた時、
    #align(center)[
    $pi_i:=deg(i)/Delta  quad [i in V]$
  ]
  とすれば$bold(pi)=(pi_i)_(i in V)$はG上の単純ランダムウォークの可逆な定常分布である
]

==

Pf.釣り合い条件を示していく\
(i)$i,j in V$が$i tilde j$を満たすとき\
$pi_i p_(i j)=deg(i)/Delta dot 1/deg(i)=1/Delta=deg(j)/Delta dot 1/deg(j)=pi_j p_(j i)$

(ii)$i,j in V$が$i tilde.not j$を満たすとき\
$pi_i p_(i j)= deg(i)/Delta dot 0=0=deg(j)/Delta dot 0 = pi_j p_(j i)$
である。


(i),(ii)から、$bold(pi)=(pi_i)_(i in V)$は、定義から可逆な定常分布

== エーレンフェストモデル
#showybox(title:"Th1.11 エーレンフェストモデル",frame: (title-color:olive.lighten(10%)))[
  N個の気体分子が入った容器が2つの部分に分けられ、単位時間ごとに一つの気体分子が下式に従い移動
  (iは一方の分子数)
  $
    p_(i,i-1)&=i/N   &(i=1,2,dots,N)\
    p_(i,i+1)&=1-i/N &(i=0,1,dots,N-1)\
    p_(i j)  &=0     &(text("上記以外"))\
  $

  #line(length: 100%)
  二項分布$B(N,1/2)$はエーレンフェストモデルの可逆な定常分布。
  #align(center)[
    $pi_i=1/2^N vec(N,i) quad [i=0,1,dots,N]$
  ]
  は詳細釣り合い条件を満たし、このモデルの定常分布は他にない
]
==
Pf.
(i)可逆な定常分布を導出\
任意の$i=0,1,dots,N-1$に対し、$pi_i p_(i,i+1)=pi_(i+1)p_(i+1,i)$(釣り合い条件)が成り立つような分布を求める。この式を変形すれば、
$
  pi_i (1-i/N)=pi_(i+1)(i+1)/N arrow.l.r pi_(i+1)=(N-i)/(i+1) pi_i
$
となる。計算すれば、一般に$i=0,dots,N$に対し、$pi_i=vec(N,i)pi_0$となる。
$pi_0$の値は$bold(pi)=(pi_i)_(i in S)$を確率分布とするよう、$sum_(i in S)pi_i=1$となるように決めると、$pi_0=1/2^N$と決まる

$
  1=sum_(i in S)pi_i=pi_0 sum_(i=0)^N vec(N,i)=pi_0 sum_(i=0)^N vec(N,i)1^i 1^(N-i)=pi_0 (1+1)^N = pi_0 2^N
$

==

(ii)エーレンフェストモデルは、定常分布であれば可逆\
$bold(pi)=(pi_i)_(i in S)$が定常分布であるという式は、
$
  pi_0=pi_1 dot pi_(1,0) , quad pi_i=pi_(i+1)dot p_(i+1,i)+pi_(i-1)dot p_(i,i-1)
$
で、この式は、$p_(i,i+1)+p_(i,i-1)=1$に注意すれば、
$
  pi_0 dot p_(0 ,1)-pi_1 dot p_(1,0)=0\
  pi_i dot p_(i,i+1)-pi_(i+1)p_(i+1,i)=pi_(i-1)dot p_(i-1,i)-pi_i dot p_(i,i-1)
$
に変形でき、これは帰納的に
$
  pi_i dot pi_(i,i+1)=pi_(i+1)dot p_(i+1,i) quad [i=0,1,dots,N-1] text("釣り合い条件式")
$
に変形できる。

よって、エーレンフェストモデルの定常分布は、可逆なものに限られる