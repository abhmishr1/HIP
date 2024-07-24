.. meta::
  :description: This chapter describes the texture fetching modes of the HIP ecosystem
  ROCm software.
  :keywords: AMD, ROCm, HIP, Texture, Texture Fetching

*******************************************************************************
Texture Fetching
*******************************************************************************

Textures are more than just a buffer, that is interpreted as 1D, 2D or 3D array. Because
of its legacy as a graphics functionality, textures are indexed with floats. This can
happen two different ways, either the index will be in the range of [0..size-1] or in
[0..1]. The difference is mathematically just a division, so for the explanations on this
page, we'll use the [0..size-1] indices.

Using float indices isn't trivial. You as a developer, have to decide what happens, when
the index is a fraction. There is no rule for how to choose between filtering methods, as
it is very dependent of the application.

.. _texture_fetching_nearest:
Nearest point sampling
===============================================================================

In this mode the ``tex(x) = T[floor(x)]`` and similarly for 2D and 3D variants. In
practice this will not interpolate between neighboring values, which results in a
pixelated look.

.. _texture_fetching_linear:
Linear filtering
===============================================================================

Linear filtering method simply does a linear interpolation between values.

* For one dimensional textures it is ``tex(x) = (1-α)T[i] + αT[i+1]``
* For two dimensional textures it is ``tex(x,y) = (1-α)(1-β)T[i,j] + α(1-β)T[i+1,j] + (1-α)βT[i,j+1] + αβT[i+1,j+1]``
* For three dimensional textures it is ``tex(x,y,z) = (1-α)(1-β)(1-γ)T[i,j,k] + α(1-β)(1-γ)T[i+1,j,k] + (1-α)β(1-γ)T[i,j+1,k] + αβ(1-γ)T[i+1,j+1,k] + (1-α)(1-β)γT[i,j,k+1] + α(1-β)γT[i+1,j,k+1] + (1-α)βγT[i,j+1,k+1] + αβγT[i+1,j+1,k+1]``

Where ``i = round(x')``, ``α = frac(x')``, ``x' = x - 0.5``, ``j = round(y')``,
``β = frac(y')``, ``y' = y - 0.5``, ``k = round(z')``, ``γ = frac(z')`` and
``z' = z - 0.5``