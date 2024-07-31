.. meta::
  :description: This chapter describes the texture fetching modes of the HIP ecosystem
  ROCm software.
  :keywords: AMD, ROCm, HIP, Texture, Texture Fetching

*******************************************************************************
Texture Fetching
*******************************************************************************

Textures are more than just a buffer, that is interpreted as 1D, 2D or 3D array. Because of its legacy as a graphics functionality, textures are indexed with floats. This can happen two different ways, either the index will be in the range of [0..size-1] or in [0..1]. The difference is mathematically just a division, so for the explanations on this page, we'll use the [0..size-1] indices.

Using float indices isn't trivial. You as a developer, have to decide what happens, when the index is a fraction. There is no rule for how to choose between filtering methods, as it is very dependent of the application.

Textures also have a mechanism to handle, what happens when indexing out of bounds. As a developer, you have to decide what happens. There is no rule for how to choose between addressing modes, as it is very dependent of the application.

.. _texture_fetching_nearest:
Nearest point sampling
===============================================================================

In this mode the ``tex(x) = T[floor(x)]`` and similarly for 2D and 3D variants. In practice this will not interpolate between neighboring values, which results in a pixelated look.

.. image:: ../data/understand/textures/nearest.png
  :width: 300
  :alt: Texture upscaled with nearest point sampling

.. _texture_fetching_linear:
Linear filtering
===============================================================================

Linear filtering method simply does a linear interpolation between values.

* For one dimensional textures it is ``tex(x) = (1-α)T[i] + αT[i+1]``
* For two dimensional textures it is ``tex(x,y) = (1-α)(1-β)T[i,j] + α(1-β)T[i+1,j] + (1-α)βT[i,j+1] + αβT[i+1,j+1]``
* For three dimensional textures it is ``tex(x,y,z) = (1-α)(1-β)(1-γ)T[i,j,k] + α(1-β)(1-γ)T[i+1,j,k] + (1-α)β(1-γ)T[i,j+1,k] + αβ(1-γ)T[i+1,j+1,k] + (1-α)(1-β)γT[i,j,k+1] + α(1-β)γT[i+1,j,k+1] + (1-α)βγT[i,j+1,k+1] + αβγT[i+1,j+1,k+1]``

Where ``i = round(x')``, ``α = frac(x')``, ``x' = x - 0.5``, ``j = round(y')``, ``β = frac(y')``, ``y' = y - 0.5``, ``k = round(z')``, ``γ = frac(z')`` and ``z' = z - 0.5``

.. image:: ../data/understand/textures/linear.png
  :width: 300
  :alt: Texture upscaled with linear filtering

.. _texture_fetching_border:
Address mode border
===============================================================================

This is probably the simplest address mode. When indexing out of bounds, the texture fetching returns a border value. This has to be set before texture fetching.

.. image:: ../data/understand/textures/border.png
  :width: 300
  :alt: Texture with yellow border color

.. _texture_fetching_wrap:
Address mode wrap
===============================================================================

This addressing mode is very simple. Mathematically it uses modulo of the index.

``tex(x) = T[x mod (size-1)]``

This creates a repeating image effect.

.. image:: ../data/understand/textures/wrap.png
  :width: 300
  :alt: Texture with wrap addressing

.. _texture_fetching_mirror:
Address mode mirror
===============================================================================

Similar to wrapping mirror mode also creates a repeating image, but this time neighboring instances are mirrored.

.. image:: ../data/understand/textures/mirror.png
  :width: 300
  :alt: Texture with mirror addressing

.. _texture_fetching_clamp:
Address mode clamp
===============================================================================

This mode simply clamps the index to be between [0..size-1]. This means that when indexing out of bounds, the values on the edge of the texture will repeat.

.. image:: ../data/understand/textures/clamp.png
  :width: 300
  :alt: Texture with clamp addressing
