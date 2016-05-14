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
The equation of it is an irreduciable polynomial $F \in \mathbb R[X, Y, Z]$ such that

$$F(X(s, t), Y(s, t), Z(s, t)) \equiv 0$$

where $(X(s, t), Y(s, t), Z(s, t)) = S(s, t) \in \mathbb R^3$.

E.g. Let $P(0, 0, 1)$, $Q(1, 0, 0)$, $R(0, 1, 0)$, $S(1, 1, 0)$ be the control points,
we have

$$\begin{align}
S(s, t) &= (1 - s)(1 - t) P + (1 - s)t Q + s(1 - t) R + st S \\
&= (1 - s) (1 - t) \mat{0 \\ 0 \\ 1} +
  (1 - s) t \mat{1 \\ 0 \\ 0} +
  s (1 - t) \mat{0 \\ 1 \\ 0} +
  st \mat{1 \\ 1 \\ 0} \\
&= \mat{t \\ s \\ (1 - s)(1 - t)}
\end{align}$$

## Proof for existence of $F$

### Proof 1
$\Delta = K(X(s, t), Y(s, t))$ has transcendental degree 2 over $K$,
therefore $Z(s, t)$ is algebraic over $\Delta$.
