# IK Derivations

Compute straight line distance and convert to triangle problem:
<code> r = √(x^2 + z^2) </code>

Law of Cosines:
<code> r^2 = L1^2 + L2^2 - 2 * L1 * L2 * cos(θ₂) </code>

Rearrange for θ^2
<code> cos(θ₂) = (r^2 - L1^2 - L2^2) / (2* L1 * L2) </code>

So:
<code> θ₂ = acos(clamp(cos(θ₂), -1, 1)) </code>

### Hip angle decompositions
