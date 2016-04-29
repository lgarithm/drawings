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

## Proof for existence of $F$

### Proof 1
$\Delta = K(X(s, t), Y(s, t))$ has transcendental degree 2 over $K$,
therefore $Z(s, t)$ is algebraic over $\Delta$.
