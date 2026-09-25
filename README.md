# Hydrogen orbitals

## Someone said

<p align="center">
  <img src="imgs/orbitali_atomici_idrogeno.png" width="700">
</p>

## I mean, it's trivial.

<table>
  <tr>
    <td align="center">
      <img src="imgs/1s.png" width="220"><br>
      <b>1s</b>
    </td>
    <td align="center">
      <img src="imgs/2p.png" width="220"><br>
      <b>2p</b>
    </td>
    <td align="center">
      <img src="imgs/3d.png" width="220"><br>
      <b>3d</b>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="imgs/4e.png" width="220"><br>
      <b>4e</b>
    </td>
    <td align="center">
      <img src="imgs/5f.png" width="220"><br>
      <b>5f</b>
    </td>
  </tr>
</table>

## We don't have gta VI yet, but at least we have this

<p align="center">
  <img src="imgs/betterthangtavi_.gif" width="400">
</p>

# Some Words , about
if you see closely. The main file is called "HF.c" this is beacuse the aim of the project was to to a complete Hartree Fock simulation. The complete source code now is lik 1200 loc. probably i need other 1000 loc to do the HF alghoritm. i think that i can , but i will do it in the future now i am busy. In fact if you are smart enough, you should remember that the Hydrogen atom has an analytical solution. There is no need to do a numerical simulation with this sophisticated thecniques.

# Ramanujan??
I found this formula for the spherical harmonics in Cartesian coordinates really useful:

```math
Y_\ell^m(x,y,z)
=
(-1)^m
\sqrt{
\frac{2\ell+1}{4\pi}
\frac{(\ell-m)!}{(\ell+m)!}
}
\frac{(x+iy)^m}{2^\ell}
\sum_{k=0}^{\left\lfloor(\ell-m)/2\right\rfloor}
(-1)^k
\frac{(2\ell-2k)!}
{k!(\ell-k)!(\ell-m-2k)!}
\frac{z^{\ell-m-2k}}
{\left(x^2+y^2+z^2\right)^{(\ell-2k)/2}}
```

# How to use??
off course , you should install openGl and then compile with "make". Then you can lunch the program with ./HF n l m specifing the quantum numbers of choice.
