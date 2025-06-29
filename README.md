# 3D Rigidbody Physics

<p>This repository will cover the basics of kinematics, energy and dynamics.

<img width="1191" alt="Image" src="https://github.com/user-attachments/assets/7dfc0dc6-a83b-4487-9ff3-a487c60974ab" />

## Useful formulas

$$ ax^2 + bx + c $$
$$ a \in (-\infty, 0) U (0, \infty) $$
$$ b^2 - 4ac \ge 0 $$

$$ x = \frac{-b ± \sqrt{b^2 - 4ac}}{2a} $$


## Vectors

$$
\vec{A} = \begin{bmatrix}
rsin(ϕ)cos(θ) \\
rsin(ϕ)sin(θ) \\
rcos(ϕ)
\end{bmatrix}
$$

Where $r$ is the magnitude of $\vec{A}$
<p></p>
Magnitude:

$$ ||\vec{A}|| = \sqrt{\vec{A}_x^2 + \vec{A}_y^2 + \vec{A}_z^2 } $$
<p></p>

Angle between vectors $\vec{a}$ and $\vec{b}$:

$$ cos(θ) = \frac{\sum \vec{a}_n\vec{b}_n}{||\vec{a}|| * ||\vec{b}||} $$
$$ θ = cos^{-1}\frac{\sum \vec{a}_n\vec{b}_n}{||\vec{a}|| * ||\vec{b}||} $$
<p></p>

## Derivatives / Differentiation
<p>By first principle:</p>

$$f'(x) = \lim_{h \to 0} \frac{1}{h}(f(x+h) - f(x)) = \frac{df}{dx} = \frac{d}{dx}$$

<p>Product rule:</p>

$$\frac{d}{dx}[f(x)g(x)] = f'(x)g(x) + f(x)g'(x)$$

<p>Quotient rule:</p>

$$\frac{d}{dx}\frac{f(x)}{g(x)} = \frac{f'(x)g(x) - f(x)g'(x)}{g(x)^2}$$

<p>Chain rule:</p>

$$\frac{d}{dx}f(g(x)) = f'(g(x))g'(x)$$

### Partial derivatives

$$f(x,y) = x^3  + y^2$$
$$\frac{∂f(x,y)}{∂x} = \lim_{h \to 0} \frac{f(x+h, y) - f(x, y)}{h} = 3x^2 → \frac{∂f}{∂x}$$
$$\frac{∂f(x,y)}{∂y} = \lim_{h \to 0} \frac{f(x, y+h) - f(x, y)}{h} = 2y → \frac{∂f}{∂y}$$

<p>Product rule</p>

$$u_x = \frac{∂}{∂x}(f(x,y)g(x,y))$$
$$u_y = \frac{∂}{∂y}(f(x,y)g(x,y))$$
$$u_x = \frac{∂f(x, y)}{∂x}g(x, y) + \frac{∂g(x, y)}{∂x}f(x, y)$$
$$u_y = \frac{∂f(x, y)}{∂y}g(x, y) + \frac{∂g(x, y)}{∂y}f(x, y)$$

<p>Quotient rule</p>

$$u_x = \frac{\frac{∂f}{∂x}g(x,y) - \frac{∂g}{∂x}f(x,y)}{g(x, y)^2}$$
$$u_y = \frac{\frac{∂f}{∂y}g(x,y) - \frac{∂g}{∂y}f(x,y)}{g(x, y)^2}$$

### Common derivatives

$\frac{d}{dx}[c] = 0$
<p></p>

$\frac{d}{dx}[ax^b] = abx^{b-1}$
<p></p>

$\frac{d}{dx}[ax^2 + bx + c] = 2ax + b$
<p></p>

$\frac{d}{dx}[\sqrt{a}] = \frac{a'}{2\sqrt{a}}$
<p></p>

$\frac{d}{dx}[ac^x] = ac^xln(c)$
<p></p>

$\frac{d}{dx}[ln(x)] = \frac{1}{x}$
<p></p>

$\frac{d}{dx}[sin(x)] = cos(x)$
<p></p>

$\frac{d}{dx}[cos(x)] = -sin(x)$
<p></p>

$\frac{d}{dx}[tan(x)] = sec^2(x)$

| Translation | Angular | 
|----------|----------|
| $v = \frac{dx}{dt}$| $ω = \frac{dθ}{dt}$
| $a = \frac{dv}{dt}$ | $α = \frac{dω}{dt}$

## Integrals / Integration

$$\int_{a}^{b} f(x)dx = \lim_{n \to \infty} \sum_{i=1}^{n}f(x_{i}^*)Δx$$

$$F(x) = \int_{a}^{b} f(x)dx$$

$$F'(x) = \frac{d}{dx}\int_{a}^{b} f(x)dx = \frac{dF}{dx}(b) - \frac{dF}{dx}(a)$$

$$\int_{a}^{b} f'(x)dx = f(b) - f(a)$$

<p>U-substitution</p>

$$\int tan(x)dx → \int \frac{sin(x)}{cos(x)}dx$$
$$u = cos(x) → \frac{du}{dx} = -sin(x) → dx = -\frac{du}{sin(x)}$$
$$-\int \frac{sin(x)}{cos(x)}\frac{du}{sin(x)} → -\int \frac{1}{cos(x)}du → -\int \frac{1}{u}du → -ln|u| = ln|\frac{1}{u}| = ln|\frac{1}{cos(x)}| = ln|sec(x)|+ C$$

<p>Integration by parts</p>

$$\int xcos(x)dx → \int udv → uv - \int vdu$$
$$u = x → du = dx$$
$$v = \int cos(x)dx → v = sin(x)$$
$$\int xcos(x)dx = uv - \int vdu →xsin(x) - \int sin(x)dx →xsin(x) + cos(x) + C$$

<p>Trigonometric substitution</p>

$$\int \frac{dx}{x^2 + 1}$$
$$x = tan(θ) → θ = tan^{-1}(x)$$
$$\frac{dx}{dθ} = sec^2(θ) → dx = sec^2(θ)dθ$$
$$\int \frac{dx}{tan^2(θ) + 1} → \int \frac{sec^2(θ)dθ}{tan^2(θ) + 1} → \int \frac{sec^2(θ)dθ}{sec^2(θ)} → \int dθ → θ → tan^{-1}(x) + C = arctan(x) + C$$
### Common integrals


$\int ax^bdx = \frac{ax^{b+1}}{b+1} + C$
<p></p>

$\int \frac{1}{x}dx = ln|x| + C$
<p></p>

$\int sin(x)dx = -cos(x) + C$
<p></p>

$\int cos(x)dx = sin(x) + C$
<p></p>

$\int sec^2(x)dx = tan(x) + C$
<p></p>

$\int sin^2(x)dx = \frac{x}{2} - \frac{sin(2x)}{4}+ C$
<p></p>

$\int cos^2(x)dx = \frac{x}{2} + \frac{sin(2x)}{4}+ C$

## Mass of a rigid body
$$m = \int_{Ω}ρ(x)dV, Ω \in \mathbb{R}^3$$
$$m = \int\int \int_{Ω}  ρ(x)dxdydz$$
$$m = \sum_{i} ρ_{i}V_{i}$$

## 2D Kinematics

<p></p>

| Translation | Angular | 
|----------|----------|
| $Δx = v_0t$| $Δθ = ω_0t$
| $Δx = v_0t + \frac{1}{2}at^2$ | $Δθ = ω_0t + \frac{1}{2}αt^2$
| $Δx = v_1t - \frac{1}{2}at^2$ | $Δθ = ω_1t - \frac{1}{2}αt^2$
| $v_1^2 = v_0^2 + 2aΔx$ | $ω_1^2 = ω_0^2 + 2αΔθ$

### Projectile example

$$\vec{v}_x = \vec{v}cos(θ)$$
$$\vec{v}_y = \vec{v}sin(θ)$$
$$g = -9.8m/s^2$$
$$Δy = v_yt + \frac{1}{2}gt^2, Δx = v_xt$$

## Forces

$\vec{F}_{net} = \sum \vec{F}_n = m\vec{a}$
<p></p>

$\vec{F}_{gravity} = mgsin(θ)$
<p></p>

$\vec{F}_{s} = -kx$
<p></p>

$\vec{T} = mg - m\vec{a}$
<p></p>


$\vec{f}_{friction} = μ_sN$ (static friction)
<p></p>

$\vec{f}_{friction} = μ_kN$ (kinetic friction)
<p></p>

$g = 9.8m/s^2$
<p></p>

### Inclined plane example at angle $θ$ with external force $X$ at angle $ϕ$ in 2D

$$\vec{F}_{nety} = \sum \vec{F}_y = \vec{N} - mgcos(θ) -Xsin(ϕ) = 0$$
$$\vec{N} = mgcos(θ) + Xsin(ϕ)$$

$$\vec{F}_{netx} = \sum \vec{F}_x = \vec{X}cos(ϕ) - mgsin(θ) -\vec{f} = m\vec{a}$$
$$m\vec{a} = Xcos(ϕ) - mgsin(θ) - μ_kN$$
$$m\vec{a} = Xcos(ϕ) - mgsin(θ) - μ_k(mgcos(θ) + Xsin(ϕ))$$
$$m\vec{a} = Xcos(ϕ) - mgsin(θ) - μ_kmgcos(θ) - μ_kXsin(ϕ)$$
$$\vec{a} = \frac{Xcos(ϕ)}{m} - gsin(θ) - μ_kgcos(θ) - \frac{μ_kXsin(ϕ)}{m}$$
$$\vec{a} = \frac{Xcos(ϕ) - μ_kXsin(ϕ)}{m} - g(sin(θ) - μ_kcos(θ))$$

## Torque and inertia

$τ_{net} = \sum τ_n = Iα$

$τ = rFsin(ϕ)$

### Inertia of a rod where $L$ is the length of the rod, $M$ is the mass of the rod and $h$ is the pivot of the rod
$$ I = \int_{-h}^{L-h} x^{2}dm → \int_{-h}^{L-h} x^{2}λdx → λ\int_{-h}^{L-h} x^{2}dx → \frac{M}{L}\int_{-h}^{L-h} x^{2}dx → \frac{Mx^{3}}{3L}_{-h}^{L-h} → \frac{M(L-h)^3}{3L} + \frac{Mh}{3L} $$
$$ I = \frac{M(L-h)^3}{3L} + \frac{Mh}{3L} $$

### Parallel Axis Theorem

$$I = I_{CM} + Md^2$$

## Energy

<p></p>

$U_g = mgh$
<p></p>

$U_s = \frac{1}{2}kx^2$
<p></p>

$K = \frac{1}{2}mv^2, \frac{1}{2}Iω^2$
<p></p>

$$K = \int pdv → \int mvdv → \frac{1}{2}mv^2$$
$$K = \int \vec{F}d\vec{x} → \int F(x)dx → max → \frac{1}{2}mv^2$$
$$U_{g} = -\int mgdy → -mgy$$
$$U_{s} = \int F_{s}dx → -\int kxdx → -\frac{1}{2}kx^2$$
$$W = \int Fdx → \int \frac{dE}{dx}dx → dE → ΔE$$

## Strings and Waves

$f = \frac{1}{T}$
<p></p>

$ω = \frac{2\pi}{T}, ω = \sqrt{\frac{k}{m}}$
<p></p>


$v = \frac{λ}{T}, v = λf$

$$x(t) = Acos(ωt + ϕ)$$
$$v(t) = \frac{d}{dt}Acos(ωt + ϕ) = -Aωsin(ωt + ϕ)$$
$$a(t) = -\frac{d}{dt}Aωsin(ωt + ϕ) = -Aω^2cos(ωt + ϕ)$$

$$E = \frac{1}{2}kx^2 + \frac{1}{2}mv^2$$
$$E = \frac{1}{2}k(Acos(ωt + ϕ))^2 + \frac{1}{2}m(-Aωsin(ωt + ϕ))^2$$
$$E = \frac{1}{2}k(Acos(ωt + ϕ))^2 + \frac{1}{2}m(-Aωsin(ωt + ϕ))^2$$
$$E = \frac{1}{2}kA^2cos^2(ωt + ϕ) + \frac{1}{2}mA^2ω^2sin^2(ωt + ϕ)$$
$$E = \frac{1}{2}kA^2cos^2(ωt + ϕ) + \frac{1}{2}mA^2\frac{k}{m}sin^2(ωt + ϕ)$$
$$E = \frac{1}{2}kA^2cos^2(ωt + ϕ) + \frac{1}{2}kA^2sin^2(ωt + ϕ)$$
$$E = \frac{1}{2}kA^2(cos^2(ωt + ϕ) + sin^2(ωt + ϕ)) → \frac{1}{2}kA^2$$
