---
layout: default
---

$\def\mat#1{\left(\begin{matrix}#1\end{matrix}\right)}$

Bézier Surface
======

## Definition
A bilinear Bézier surface has the parameterized form

$$S(s, t) = \mat{1 - s & s} \mat{P & Q \\ R & S} \mat{1 - t \\ t}$$

where $P, Q, R, S \in \mathbb R^3$.
The equation of it is an irreduciable polynomial $F \in \mathbb R[X, Y, Z]$ such
that

$$F(X(s, t), Y(s, t), Z(s, t)) \equiv 0$$

where $(X(s, t), Y(s, t), Z(s, t)) = S(s, t) \in \mathbb R^3$.

E.g. Let $P(0, 0, 1)$, $Q(1, 0, 0)$, $R(0, 1, 0)$, $S(1, 1, 0)$ be the control
points, we have

$$\begin{align}
S(s, t) &= (1 - s)(1 - t) P + (1 - s)t Q + s(1 - t) R + st S \\
&= (1 - s) (1 - t) \mat{0 \\ 0 \\ 1} +
  (1 - s) t \mat{1 \\ 0 \\ 0} +
  s (1 - t) \mat{0 \\ 1 \\ 0} +
  st \mat{1 \\ 1 \\ 0} \\
&= \mat{t \\ s \\ (1 - s)(1 - t)}
\end{align}$$

Therefore the surface can be defined by $F(X, Y, Z) = Z - (1 - X)(1 - Y)$.

And for $O(0, 0, 0)$, $A(1, 0, 0)$, $B(0, 1, 0)$, and $C(1, 1, 1)$, the equation
is

$$G(X, Y, Z) = Z - XY$$

Those two sufaces are bi-rational equivalent and their coordinate rings are
isomorphic:

$$\mathbb C[X, Y, Z] / (Z - (1 - X)(1 - Y)) \cong \mathbb C[X, Y, Z] / (Z - XY)
\cong \mathbb C[X, Y]$$


More generally, let the control points be $O(0, 0, 0)$, $P(a, 0, 0)$,
$Q(b, c, 0)$ and $R(d, e, f)$ where $c, f \neq 0$. The we have

$$\begin{cases}
X &= at + & bs + & (d - a - b) & st \\
Y &=      & cs + & (e - c) & st \\
Z &=      &      &       f & st
\end{cases}$$

and

$$F(X, Y, Z) = (X - {b \over c} Y + {ac - cd + be \over cf} Z)
 (Y + {c - e \over f} Z) - {ac \over f} Z$$

A biquadratic Bézier surface has the form

$$S(s, t) = \mat{(1 - s)^2 & 2(1 - s) s & s^2}
\mat{P_{00} & P_{01} & P_{02} \\
     P_{10} & P_{11} & P_{12} \\
     P_{20} & P_{21} & P_{22}}
\mat{(1 - t)^2 \\ 2(1 - t)t \\ t^2}$$

Where $P_{ij}$ are control points.

## Proof for existence of $F$

We can prove that the Bézier surface is an algebraic surface without compute the
equation of it.

### Proof 1
$\Delta = K(X(s, t), Y(s, t))$ has transcendental degree 2 over $K$,
therefore $Z(s, t)$ is algebraic over $\Delta$.
