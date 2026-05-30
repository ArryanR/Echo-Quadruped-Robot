# IK Derivations

### Distance from hip to target foot distance
Compute straight line distance and convert to triangle problem:
<code> r = √(x^2 + z^2) </code>

### Knee angle
Law of Cosines:
<code> r^2 = L1^2 + L2^2 - 2 * L1 * L2 * cos(θ₂) </code>

Rearrange for θ₂
<code> cos(θ₂) = (r^2 - L1^2 - L2^2) / (2* L1 * L2) </code>

So:
<code> θ₂ = acos(clamp(cos(θ₂), -1, 1)) </code>

### Hip angle decompositions
<code> α = atan2(z, x) </code>

Internal angle correction:
<code> β = atan2(L2 * sin(θ₂), L1 + L2 * cos(θ₂)) </code>

Finally:
<code> θ₁ = α + β </code>

### Servo mapping

Convert radians into degrees:
<code> deg = rad × 180 / π </code>
Map to servo center:
<code>servo_angle = center + θ</code>

### Gait generation (i.e. how it moves)
<code>x = StepLength * (0.5 - p)</code>
<code> z = StandHeight </code>

Foot moves forward and lifts (with sine wave):
<code>z = StandHeight + StepLift · sin(π*s)</code>

### PLEASE NOTE:
- +X = forward
- +Z = upward/downward
- Origin = hip joint

<h5> Sources:</h5>  

https://www.youtube.com/watch?v=WAsMAeKDc4U

