/****************************************************************************//*
 * Copyright (C) 2024 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

// https://www.cfd-online.com/Wiki/Turbulence_free-stream_boundary_conditions
function calc()
{
    var u = document.getElementById("in_u").value;
    var l = document.getElementById("in_l").value;
    var I = 0.01 * document.getElementById("in_I").value;

    // turbulence model constant, usually has a value of 0.09
    var C_mu = 0.09;

    // turbulent energy
    var k = 1.5 * (u*I) ** 2.0;

    // specific dissipation rate
    var omega = Math.sqrt(k) / l;
    
    // dissipation rate
    var epsilon = C_mu * Math.pow(k, 1.5) / l;

    // modified turbulent viscosity
    var nut = k / omega;

    //alert(k);

    document.getElementById("out_k").innerHTML = k.toExponential(2);
    document.getElementById("out_epsilon").innerHTML = epsilon.toExponential(2);
    document.getElementById("out_omega").innerHTML = omega.toExponential(2);
    document.getElementById("out_nut").innerHTML = nut.toExponential(2);
}